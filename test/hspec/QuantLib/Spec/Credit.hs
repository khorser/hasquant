module QuantLib.Spec.Credit (spec) where

import Test.Hspec
import Data.List.NonEmpty(fromList)
import Data.Time.Calendar(fromGregorian, addGregorianYearsClip)

import QuantLib.Currency(currency, Ccy(..))
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), TimeUnit(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.TermStructure.Credit(flatHazardRate)
import QuantLib.Instrument.Credit(Claim(..))
import QuantLib.Credit

-- |Builds a small pool/basket/Gaussian-LHP-loss-model chain and checks the loss model actually
-- wired up -- 'basketNotional' alone can't tell (it's a plain constructor echo, computed before
-- any loss model is consulted), so the discriminating check is 'basketExpectedTrancheLoss', which
-- throws if no loss model is attached. Fixture shape follows
-- ~/Src/QuantLib/test-suite/cdo.cpp (an EUR corporate default key, a single shared flat hazard
-- curve, five equal-notional names); numeric golden-value coverage against that fixture is
-- Step 7's SyntheticCDO test, not this one.
spec :: Spec
spec =
  describe "portfolio credit scaffolding (Pool, Issuer, Basket, GaussianLHPLossModel)" $
    it "wires a basket to a Gaussian LHP loss model over a small pool" $ do
      let refDate = fromGregorian 2006 8 31
          names = ["issuer-0", "issuer-1", "issuer-2", "issuer-3", "issuer-4"]
          notionalPerName = 100.0

      eur <- currency EUR
      dc <- dayCounter (Actual360 False)
      hazardQuote <- simpleQuote 0.01
      dts <- flatHazardRate refDate hazardQuote dc
      key <- northAmericaCorpDefaultKey eur SeniorSec (0, Weeks) 10.0 FullRestructuring

      iss <- issuer (fromList [(key, dts)])
      p <- pool (fromList [(n, iss, key) | n <- names])

      correlQuote <- simpleQuote 0.3
      lossModel <- gaussianLHPLossModel correlQuote (fromList (replicate (length names) 0.4))

      b <- basket refDate (fromList [(n, notionalPerName) | n <- names]) p 0.0 1.0 FaceValue lossModel

      notional <- basketNotional b
      notional `shouldBe` notionalPerName * fromIntegral (length names)

      let futureDate = addGregorianYearsClip 5 refDate
      etl <- basketExpectedTrancheLoss b futureDate
      etl `shouldSatisfy` (\x -> x > 0 && x < notional)

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
