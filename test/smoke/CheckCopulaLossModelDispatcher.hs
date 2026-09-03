-- Smoke test for Gaussian/Student-T copula dispatch through nth-to-default pricing.
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
        b <- digitalBasket refDate (fromList [(n, notional) | n <- names]) p 0.0 1.0 FaceValue lm
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

  -- The two policies must reach distinct dispatch arms.
  checkWith "Gaussian and Student-T arms give different fairPremium"
    "gaussFair /= studentFair" (gaussFair /= studentFair)

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
