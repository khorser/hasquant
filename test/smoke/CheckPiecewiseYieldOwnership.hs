-- Concrete yield leaves and their upcasts must share ownership and observe live quotes.
module Main (main) where

import Control.Monad (unless)
import Data.List.NonEmpty (fromList)
import qualified QuantLib.Context as Context
import QuantLib.Math (Interpolation(..))
import qualified QuantLib.Quote as Quote
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

main :: IO ()
main = Context.keepingSettingsGc $ do
  Context.setEvaluationDate (Just (2 `january` 2025))
  cal <- calendar Null
  dc <- dayCounter Actual365FixedStandard
  quote <- Quote.simpleQuote 0.04
  (leaf, parent) <- do
    helpers <- mapM (\n -> depositRateHelper quote (DepositTenor (n, Years) 0 cal Unadjusted False dc)) [1,2,3]
    curve <- piecewiseYieldCurve (SettlementDays 0 cal) (fromList helpers) dc [] (Iterative Discount LogLinear defaultIterativeBootstrapOpts) False
    base <- asYieldTermStructure curve
    pure (curve, base)
  Context.collectGarbage
  nodes <- piecewiseYieldCurveNodes leaf
  before <- discount parent (TimePoint 2) False
  _ <- Quote.setValue quote 0.05
  changed <- piecewiseYieldCurveNodes leaf
  unless (nodes /= changed) (fail "leaf failed to observe the quote")
  after <- discount parent (TimePoint 2) False
  unless (after < before) (fail "upcast failed to observe the quote")
  Context.collectGarbage
  final <- discount parent (TimePoint 2) False
  unless (final == after) (fail "upcast failed after leaf collection")
  putStrLn "piecewise yield ownership and live upcasts passed"
