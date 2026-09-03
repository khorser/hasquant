-- Smoke test for the Gaussian/Student-T copula dispatcher behind QuantLib.Credit.constantLossModel
-- (cbits/qlTermStructureAux.cpp's dispatchCopulaPolicy, added alongside NthToDefault). A green
-- `stack build` only proves this compiles; it does not prove the enum->template dispatch picks
-- the right C++ type for both arms, or that the TCopulaPolicy arm's extra initTraits::tOrders
-- field is actually wired up (GaussianCopulaPolicy's initTraits is an unrelated bare int -- see
-- the c2hs-shim-patterns skill's "differing initTraits per dispatcher arm" note). This exercises
-- both arms end to end against a freshly built library and checks each returns a distinct,
-- finite fair premium on a digital-type payoff (NthToDefault) -- deliberately NOT
-- basketExpectedTrancheLoss: ConstantLossModel has no distribution-type loss integration of its
-- own (see its upstream doc comment and QuantLib.Credit.constantLossModel's haddock), and
-- calling that on a ConstantLossModel-backed basket throws "Not implemented for this model",
-- caught the hard way while first writing this script with expectedTrancheLoss instead.
--
-- Run with: .claude/skills/run-hasquant/driver.sh test/smoke/CheckCopulaLossModelDispatcher.hs
import Data.List.NonEmpty(fromList)
import Data.Time.Calendar(fromGregorian)

import QuantLib.Currency(currency, Ccy(..))
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..), BusinessDayConvention(..))
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), TimeUnit(..), schedule, DateGenerationRule(..), Frequency(..))
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.TermStructure.Credit(flatHazardRate)
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.Settings(setEvaluationDate)
import QuantLib.Instrument(setPricingEngine)
import QuantLib.Instrument.Credit(Claim(..), ProtectionSide(..), nthToDefault, ntdFairPremium)
import QuantLib.PricingEngine(integralNtdEngine)
import QuantLib.Credit

import SmokeCheck(checkWith, report)

main :: IO ()
main = do
  let refDate = fromGregorian 2006 8 31
      names = ["Name0", "Name1"]
      notional = 100.0

  setEvaluationDate (Just refDate)

  eur <- currency EUR
  key <- northAmericaCorpDefaultKey eur SeniorSec (0, Days) 1.0 FullRestructuring
  dc <- dayCounter (Actual360 False)
  hazardQuote <- simpleQuote 0.01
  dts <- flatHazardRate refDate hazardQuote dc

  iss <- issuer (fromList [(key, dts)])
  p <- pool (fromList [(n, iss, key) | n <- names])

  rateQuote <- simpleQuote 0.05
  yieldTS <- flatForward refDate rateQuote dc Continuous Annual

  target <- calendar TARGET
  sched <- schedule (Just $ fromGregorian 2006 9 1) (fromGregorian 2011 9 1) (3, Months) target
    Following Following Backward False Nothing Nothing
  engine <- integralNtdEngine (1, Weeks) yieldTS

  correlQuote <- simpleQuote 0.2
  let recoveries = fromList [0.4, 0.4]

      priceFirstToDefault lm = do
        b <- basket refDate (fromList [(n, notional) | n <- names]) p 0.0 1.0 FaceValue lm
        ntd <- nthToDefault b 1 Seller sched 0.0 0.02 dc (notional * fromIntegral (length names)) True
        setPricingEngine ntd engine
        ntdFairPremium ntd

  gaussLM <- constantLossModel correlQuote recoveries GaussianQuadrature []
  gaussFair <- priceFirstToDefault gaussLM
  report "Gaussian arm 1st-to-default fairPremium" gaussFair
  checkWith "Gaussian arm fairPremium is a finite positive rate"
    "0 < fairPremium < 1" (gaussFair > 0 && gaussFair < 1)

  studentLM <- constantLossModel correlQuote recoveries GaussianQuadrature [5, 5]
  studentFair <- priceFirstToDefault studentLM
  report "Student-T arm 1st-to-default fairPremium" studentFair
  checkWith "Student-T arm fairPremium is a finite positive rate"
    "0 < fairPremium < 1" (studentFair > 0 && studentFair < 1)

  -- Not a tight numeric check (no upstream reference for this ad hoc 2-name fixture) -- just
  -- confirms the two arms are actually distinct code paths rather than one silently dispatching
  -- to the other (e.g. an untaken switch arm falling through to the same default).
  checkWith "Gaussian and Student-T arms give different fairPremium"
    "gaussFair /= studentFair" (gaussFair /= studentFair)

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
