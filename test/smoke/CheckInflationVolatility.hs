-- Smoke test: construct a ConstantYoYOptionletVolatility surface, query its
-- volatility/totalVariance, and wire each of the 3 YoY inflation cap/floor
-- pricing engines (Black/UnitDisplacedBlack/Bachelier) so a broken ctor or
-- shim signature shows up immediately, not just "the build succeeded".
--
-- Run with: .claude/skills/run-hasquant/driver.sh smoke/CheckInflationVolatility.hs
import qualified QuantLib.InterestRate as IR
import QuantLib.InterestRate(VolatilityType(..))
import QuantLib.Index(addFixing)
import QuantLib.Index.Inflation
import QuantLib.PricingEngine
import QuantLib.Quote(simpleQuote)
import QuantLib.Settings(setEvaluationDate)
import QuantLib.TermStructure.InflationVolatility
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), Frequency(..), TimeUnit(..))

import SmokeCheck (checkWith)

main :: IO ()
main = do
  setEvaluationDate $ Just today
  dc <- dayCounter Actual365FixedStandard
  cal <- calendar Null
  volQ <- simpleQuote 0.03
  vol <- constantYoYOptionletVolatility volQ 0 cal Unadjusted dc (0, Months) Monthly False (-1.0) 100.0 ShiftedLognormal 0.0

  v <- yoyOptionletVolatility vol (2 `january` 2025) 0.03 Nothing True
  putStrLn ("yoyOptionletVolatility -> " ++ show v ++ " (should be ~0.03)")
  checkWith "yoyOptionletVolatility" "should equal the constant quote" (abs (v - 0.03) < 1e-10)

  tv <- yoyOptionletTotalVariance vol (2 `january` 2025) 0.03 Nothing True
  putStrLn ("yoyOptionletTotalVariance -> " ++ show tv)

  yii <- yoyInflationIndex YYUKRPI
  addFixing yii (1 `january` 2020) 0.03 False
  nominalQ <- simpleQuote 0.02
  nominalCurve <- flatForward today nominalQ dc IR.Continuous Annual

  _ <- yoyInflationBlackCapFloorEngine yii vol nominalCurve
  _ <- yoyInflationUnitDisplacedBlackCapFloorEngine yii vol nominalCurve
  _ <- yoyInflationBachelierCapFloorEngine yii vol nominalCurve
  putStrLn "all 3 YoY inflation cap/floor engines constructed OK"
  where
    today = 2 `january` 2024
