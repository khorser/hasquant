-- Ownership check for fxCashSpotQuote under Haskell GC.
--
-- The quote is a hasquant-defined C++ class holding copies of its spot and curve handles. The
-- hspec specs check its value and notifications with every Haskell reference held; this checks
-- that the copied handles alone keep the spot quote and both curves alive once Haskell drops them,
-- and that a curve built inside a function still notifies the quote after collection.
import Data.Time.Calendar(Day, fromGregorian, diffDays)

import QuantLib.InterestRate
import QuantLib.Quote
import QuantLib.Context
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import QuantLib.TermStructure.Yield(Reference(..), flatForward)

import SmokeCheck

evalDate, settleDate :: Day
evalDate = fromGregorian 2026 12 23
-- Two TARGET business days later, past Christmas and the weekend.
settleDate = fromGregorian 2026 12 28

expected :: Double -> Double -> Double -> Double
expected spot rd rf = spot * exp (-(rd - rf) * fromIntegral (diffDays settleDate evalDate) / 365)

-- |Build the quote and return it with only the domestic rate quote: the spot quote and both
-- curves have no Haskell reference left on return.
cashSpotDroppingInputs :: IO (Quote, SimpleQuote)
cashSpotDroppingInputs = do
  dc <- dayCounter Actual365FixedStandard
  cal <- calendar TARGET
  spot <- simpleQuote 1.25
  rdQ <- simpleQuote 0.05
  rfQ <- simpleQuote 0.01
  dom <- flatForward (ReferenceDate evalDate) rdQ dc Continuous Annual
  for <- flatForward (ReferenceDate evalDate) rfQ dc Continuous Annual
  q <- fxCashSpotQuote spot dom for cal 2
  pure (q, rdQ)

main :: IO ()
main = do
  setEvaluationDate (Just evalDate)
  (q, rdQ) <- cashSpotDroppingInputs
  collectGarbage
  collectGarbage
  v0 <- value q
  checkClose "cash spot reads its dropped inputs" (expected 1.25 0.05 0.01) v0 1.0e-14
  _ <- setValue rdQ 0.06
  collectGarbage
  v1 <- value q
  checkClose "a dropped curve still moves the quote" (expected 1.25 0.06 0.01) v1 1.0e-14
  putStrLn "fxCashSpotQuote ownership: OK"
