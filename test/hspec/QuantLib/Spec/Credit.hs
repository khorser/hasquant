module QuantLib.Spec.Credit (spec) where

import Test.Hspec
import Data.List.NonEmpty(fromList)
import Data.Time.Calendar(fromGregorian, addGregorianYearsClip)

import QuantLib.Currency(currency, Ccy(..))
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..), BusinessDayConvention(..))
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), TimeUnit(..), schedule, DateGenerationRule(..), Frequency(..))
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.TermStructure.Credit(flatHazardRate)
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.Instrument(setPricingEngine)
import QuantLib.Instrument.Credit(Claim(..), ProtectionSide(..), syntheticCDO, fairPremium)
import QuantLib.PricingEngine(midPointCDOEngine, integralCDOEngine)
import qualified QuantLib.Settings as Settings
import QuantLib.Credit

-- |Builds a small pool/basket/Gaussian-LHP-loss-model chain and checks the loss model actually
-- wired up -- 'basketNotional' alone can't tell (it's a plain constructor echo, computed before
-- any loss model is consulted), so the discriminating check is 'basketExpectedTrancheLoss', which
-- throws if no loss model is attached. Fixture shape follows
-- ~/Src/QuantLib/test-suite/cdo.cpp (an EUR corporate default key, a single shared flat hazard
-- curve, five equal-notional names); numeric golden-value coverage against that fixture is
-- the 'SyntheticCDO' test below.
spec :: Spec
spec =
  describe "portfolio credit scaffolding (Pool, Issuer, Basket, GaussianLHPLossModel)" $ do
    it "wires a basket to a Gaussian LHP loss model over a small pool" $ Settings.keepingSettings' $ do
      let refDate = fromGregorian 2006 8 31
          names = ["issuer-0", "issuer-1", "issuer-2", "issuer-3", "issuer-4"]
          notionalPerName = 100.0

      Settings.setEvaluationDate (Just refDate)

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

    -- Ports test-suite/cdo.cpp's testHW, data set 1 only (corr=0.1, the "gaussian" branch of
    -- hwData7): a 100-name pool, the Gaussian LHP loss model (the only loss model hasquant
    -- binds -- IHGaussPoolLossModel/HomogGaussPoolLossModel/RandomDefaultLM are deliberately
    -- out of scope), and both CDO engines. Checked at upstream's own LHP-row tolerance (10bp
    -- absolute / 50% relative, cdo.cpp's absoluteTolerance/relativeToleranceMidp[3]) -- LHP is a
    -- crude approximation for a 100-name pool, so this is a wiring check against Hull-White
    -- Table 7, not a tight numeric regression. Do not tighten this tolerance later.
    it "prices a synthetic CDO tranche against Hull-White Table 7 (Gaussian LHP)" $ Settings.keepingSettings' $ do
      let refDate = fromGregorian 2006 8 31
          poolSize = 100 :: Int
          names = ["issuer-" ++ show i | i <- [0 .. poolSize - 1]]
          notionals = replicate poolSize 100.0
          recovery = 0.4
          -- (attachment, detachment, expected spread in bp) -- Hull-White Table 7, corr=0.1
          tranches = [ (0.00, 0.03, 2279.0)
                     , (0.03, 0.06,  450.0)
                     , (0.06, 0.10,   89.0)
                     , (0.10, 1.00,    1.0)
                     ]
          absTol = 10.0 :: Double
          relTol = 0.5 :: Double

      Settings.setEvaluationDate (Just refDate)

      eur <- currency EUR
      key <- northAmericaCorpDefaultKey eur SeniorSec (0, Weeks) 10.0 FullRestructuring
      act360 <- dayCounter (Actual360 False)
      hazardQuote <- simpleQuote 0.01
      dts <- flatHazardRate refDate hazardQuote act360

      iss <- issuer (fromList [(key, dts)])
      p <- pool (fromList [(n, iss, key) | n <- names])

      rateQuote <- simpleQuote 0.05
      yieldTS <- flatForward refDate rateQuote act360 Continuous Annual

      correlQuote <- simpleQuote 0.1
      lossModel <- gaussianLHPLossModel correlQuote (fromList (replicate poolSize recovery))

      target <- calendar TARGET
      sched <- schedule (Just $ fromGregorian 2006 9 1) (fromGregorian 2011 9 1) (3, Months) target
        Following Following Backward False Nothing Nothing

      midPEngine <- midPointCDOEngine yieldTS
      integralEngine <- integralCDOEngine yieldTS (3, Months)

      mapM_ (\(att, det, expected) -> do
        b <- basket refDate (fromList (zip names notionals)) p att det FaceValue lossModel
        cdo <- syntheticCDO b Seller sched 0.0 0.02 act360 Following Nothing

        setPricingEngine cdo midPEngine
        midFair <- (* 1e4) <$> fairPremium cdo
        (abs (midFair - expected) < absTol || abs ((midFair - expected) / expected) < relTol)
          `shouldBe` True

        setPricingEngine cdo integralEngine
        intFair <- (* 1e4) <$> fairPremium cdo
        (abs (intFair - expected) < absTol || abs ((intFair - expected) / expected) < relTol)
          `shouldBe` True
        ) tranches

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
