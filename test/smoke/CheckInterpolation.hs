-- Smoke test: construct an interpolatedZeroCurve with every Interpolation case (including the
-- nested Cubic/LogCubic (NaturalSpline/Parabolic True/False, Kruger, FritschButland)
-- Approximation cases) and query a discount factor at a non-knot date. This guards generated
-- enum ordinals and the NaturalSpline/Parabolic Bool payloads end to end.
import Control.Monad
import Data.List.NonEmpty(fromList)
import QuantLib.Math(Approximation(..), Interpolation(..))
import QuantLib.Quote(simpleQuote)
import QuantLib.TermStructure.Yield(TermPoint(..), interpolatedZeroCurve, discount)
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..))

-- Abcd is excluded because the curve dispatcher does not support it.
interpolations :: [(String, Interpolation)]
interpolations =
  [ ("BackwardFlat", BackwardFlat)
  , ("ForwardFlat", ForwardFlat)
  , ("Linear", Linear)
  , ("LogLinear", LogLinear)
  ] ++ concatMap (\(nm, approx) ->
       [("Cubic " ++ nm, Cubic approx), ("LogCubic " ++ nm, LogCubic approx)])
     [ ("NaturalSpline True", NaturalSpline True)
     , ("NaturalSpline False", NaturalSpline False)
     , ("Parabolic True", Parabolic True)
     , ("Parabolic False", Parabolic False)
     , ("Kruger", Kruger)
     , ("FritschButland", FritschButland)
     ]

main :: IO ()
main = do
  cal <- calendar Null
  dc <- dayCounter Actual365FixedStandard
  let knots = [(1 `january` 2024, 0.02), (1 `january` 2025, 0.025), (1 `january` 2026, 0.03), (1 `january` 2027, 0.032)]
      queryDate = 1 `july` 2025 -- between knots -- exercises the interpolator, not just endpoints
  forM_ interpolations $ \(nm, interp) -> do
    curve <- interpolatedZeroCurve (fromList knots) dc cal [] interp
    d <- discount curve (DatePoint queryDate) True
    putStrLn (nm ++ ": discount(" ++ show queryDate ++ ") = " ++ show d)
