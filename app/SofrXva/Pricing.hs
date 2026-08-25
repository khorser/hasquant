-- |Prices a single fixed 7Y SOFR OIS (effective 1 Dec 2021, fixed rate 2.78%) on every
-- (scenario, timestep) pair covered by the given curve data, seeding daily interpolated
-- fixings between consecutive timesteps. One 'RelinkableYieldTermStructure' drives both
-- the 'Sofr' index's forecasting and the engine's discounting, so a single handle
-- relink is enough to move the whole pricing setup to the next timestep's curve.
module SofrXva.Pricing
  ( buildSofrProfile
  ) where

import Control.Monad (filterM, forM, when)
import Data.List (nub, sort)
import Data.Time.Calendar (Day, addDays, addGregorianYearsClip, diffDays, fromGregorian)
import qualified Data.Map.Strict as Map

import QuantLib.CashFlow (RateAveragingType(..))
import QuantLib.Index (fixingCalendar, isValidFixingDate, addFixings)
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Instrument (npv, setPricingEngine)
import QuantLib.Instrument.Swap (SwapType(..), overnightIndexedSwap)
import QuantLib.Math (Interpolation(..))
import QuantLib.PricingEngine (discountingSwapEngine)
import QuantLib.Settings (setEvaluationDate)
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar (CalendarConstructor(..), calendar, BusinessDayConvention(..))
import QuantLib.Time.Schedule (DayCounterConstructor(..), DateGenerationRule(..), TimeUnit(..), dayCounter, schedule)

-- |Prices the swap on every (scenario, timestep) pair present in 'curves'. 'curves'
-- gives, per (scen, ts), the valuation date and its (pillar date, discount factor)
-- points (see 'SofrXva.Data.loadSofrCurve'); 'hist' the historical SOFR fixings;
-- 'quotes' the per-(scen, ts, date) SOFR quotes.
buildSofrProfile
  :: Map.Map (Int, Int) (Day, [(Day, Double)])
  -> Map.Map Day Double
  -> Map.Map (Int, Int, Day) Double
  -> IO (Map.Map (Int, Int) Double)
buildSofrProfile curves hist quotes = do
  tsh <- TS.relinkableYieldTermStructure (Nothing :: Maybe TS.YieldTermStructure)
  index <- IR.overnightIborIndex IR.Sofr (Just tsh)

  histBDs <- filterM (isValidFixingDate index) (Map.keys hist)
  when (not (null histBDs)) $
    addFixings index histBDs (map (hist Map.!) histBDs) True

  cal <- fixingCalendar index
  dc <- dayCounter (Actual360 False)
  paymentCal <- calendar UnitedStatesNYSE

  let effectiveDate = fromGregorian 2021 12 1
      terminationDate = addGregorianYearsClip 7 effectiveDate
  fixedSched <- schedule (Just effectiveDate) terminationDate (6, Months) cal
    ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing
  swap <- overnightIndexedSwap Payer 1000000 fixedSched 0.0278 dc index 0 2
    ModifiedFollowing paymentCal False AveragingCompound Nothing 0 False
  engine <- discountingSwapEngine tsh (Just False) Nothing Nothing
  setPricingEngine swap engine

  let d0 = fst (curves Map.! (0, 0))
      scens = sort (nub (map fst (Map.keys curves)))
      lookupQuote scen ts date = case Map.lookup (scen, ts, date) quotes of
        Just v -> v
        -- mirrors getQuote's synthetic (scen, ts, d0) row, which falls back to the
        -- historical fixing whenever no real quote is recorded for the valuation date
        Nothing | date == d0 -> hist Map.! d0
        Nothing -> error ("SofrXva.Pricing.buildSofrProfile: no quote for "
          ++ show (scen, ts, date))

  results <- forM scens $ \scen -> do
    let tss = sort [ts | (s, ts) <- Map.keys curves, s == scen]
    (_, npvs) <- foldDates d0 tss $ \d1 ts -> do
      let (d2, points) = curves Map.! (scen, ts)
      setEvaluationDate (Just d2)
      addInterpolatedFixings index d1 d2
        (lookupQuote scen (max 0 (ts - 1)) d1) (lookupQuote scen ts d2)
      curve <- TS.interpolatedDiscountCurve points dc cal [] LogLinear True
      TS.linkTo tsh curve
      v <- npv swap
      pure (d2, ((scen, ts), v))
    pure npvs
  pure (Map.fromList (concat results))
  where
    foldDates :: Monad m => Day -> [Int] -> (Day -> Int -> m (Day, a)) -> m (Day, [a])
    foldDates d0 xs f = go d0 xs []
      where
        go d [] acc = pure (d, reverse acc)
        go d (x:rest) acc = do
          (d', a) <- f d x
          go d' rest (a : acc)

-- |Adds daily interpolated fixings for every business day between 'd1' and 'd2'
-- (inclusive), linearly interpolating between the two quote values known at those
-- dates.
addInterpolatedFixings :: IR.OvernightIborIndex -> Day -> Day -> Double -> Double -> IO ()
addInterpolatedFixings index d1 d2 v1 v2 = do
  let n = fromIntegral (diffDays d2 d1) :: Int
      allDates = [addDays i d1 | i <- [0 .. fromIntegral n]]
      values = linspace v1 v2 (n + 1)
  pairs <- filterM (\(d, _) -> isValidFixingDate index d) (zip allDates values)
  when (not (null pairs)) $
    addFixings index (map fst pairs) (map snd pairs) True

-- |@numpy.linspace@'s behaviour for the cases this module needs: 'num' evenly spaced
-- points from 'a' to 'b' inclusive, with 'num' == 1 returning just 'a'.
linspace :: Double -> Double -> Int -> [Double]
linspace a _ 1 = [a]
linspace a b num = [a + (b - a) * fromIntegral i / fromIntegral (num - 1) | i <- [0 .. num - 1]]
