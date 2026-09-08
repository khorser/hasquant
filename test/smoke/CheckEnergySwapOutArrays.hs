-- Smoke test for the four EnergySwap/Commodity out-array bindings the hspec suite never calls:
-- secondaryCostAmounts, pricingErrors, dailyPositions and paymentCashFlows. Each is a
-- multi-out-array shim staged through OutStringArrayResult/OutArrayResult/OutPtrArrayResult
-- (cbits/qlaux.h), so this is the only place that exercises those spines end to end -- run it
-- under QLTRACK_ALLOCATIONS and tools/alloc-summary.py to prove they balance. Ownership, not
-- pricing, is the point: the values asserted here are the ones the construction fixes.
--
-- Run with: cabal exec -- ghc -itest/smoke -package hasquant test/smoke/CheckEnergySwapOutArrays.hs \
--   -o /tmp/checkenergyswapoutarrays -outputdir /tmp/checkenergyswapoutarrays_build && /tmp/checkenergyswapoutarrays
import Data.List.NonEmpty (fromList)
import Data.Time.Calendar (addDays)

import qualified QuantLib.Settings as Settings
import QuantLib.Commodity
import QuantLib.Index (addFixing)
import QuantLib.Index.Commodity (CommodityIndex, commodityIndex)
import QuantLib.Instrument (npv)
import QuantLib.Instrument.Energy
import QuantLib.InterestRate (Compounding(..))
import QuantLib.Quote (simpleQuote)
import QuantLib.TermStructure.Commodity (commodityCurve)
import QuantLib.TermStructure.Yield (Reference(..), YieldTermStructure, flatForward)
import QuantLib.Time.Calendar (calendar, CalendarConstructor(..))
import QuantLib.Time.Date
import QuantLib.Time.Schedule (dayCounter, DayCounterConstructor(..), Frequency(..))

import SmokeCheck (checkEq, checkWith)

-- A flat zero curve, as in the Energy hspec spec: pay/receive/discount all point at it, so the
-- legs discount identically and the arithmetic below stays exact.
flatZeroCurve :: Day -> IO YieldTermStructure
flatZeroCurve evalDate = do
  q <- simpleQuote 0.0
  dc <- dayCounter Actual365FixedStandard
  flatForward (ReferenceDate evalDate) q dc Continuous Annual

flatIndex :: CommodityType -> UnitOfMeasure -> Day -> Double -> IO CommodityIndex
flatIndex ct bbl evalDate price = do
  usd <- commoditySettingsCurrency
  cal <- calendar Null
  curve <- commodityCurve "flat curve" ct usd bbl cal
             (fromList [(evalDate, price), (addDays 400 evalDate, price)])
             =<< dayCounter Actual365FixedStandard
  idx <- commodityIndex "flat index" ct usd bbl cal 1 (Just curve)
  addFixing idx (addDays (-30) evalDate) price False
  pure idx

main :: IO ()
main = Settings.keepingSettingsGc $ do
  evalDate <- today
  Settings.setEvaluationDate (Just evalDate)
  ct <- commodityType "CL" "Crude Oil"
  bbl <- barrelUnitOfMeasure
  usd <- commoditySettingsCurrency
  cal <- calendar Null
  idx <- flatIndex ct bbl evalDate 100
  ts <- flatZeroCurve evalDate
  let pp = pricingPeriod (addDays 10 evalDate) (addDays 14 evalDate) (addDays 20 evalDate)
             (ct, bbl, 1000)
      -- Two secondary costs, so the three parallel arrays of secondaryCostAmounts (keys as a
      -- char** spine, amounts as a double array, currencies as a Currency** spine) are all
      -- non-empty and of the same length.
      secCosts = [ ("brokerage", Right (25.0, usd))
                 , ("freight", Left (0.5, usd, bbl))
                 ]
  swp <- energyVanillaSwap True cal (100, usd) bbl idx usd usd [pp] ct secCosts ts ts ts

  -- Pricing populates dailyPositions/paymentCashFlows/secondaryCostAmounts; before it they are
  -- all empty, which would exercise only the zero-length spine.
  _ <- npv swp

  amounts <- secondaryCostAmounts swp
  checkEq "secondaryCostAmounts keys" ["brokerage", "freight"] (map fst amounts)
  checkWith "secondaryCostAmounts currencies" "every entry resolves to the base currency" $
    all ((== usd) . snd . snd) amounts

  -- Two more diagnostics on top of whatever pricing itself recorded, so both char** spines of
  -- qlCommodityPricingErrors carry several entries -- and the upstream-recorded ones prove the
  -- spine is not just echoing what this test put in.
  addPricingError swp Warning "smoke warning" "first detail"
  addPricingError swp Fatal "smoke error" "second detail"
  errs <- pricingErrors swp
  checkWith "pricingErrors from upstream" "pricing records at least one diagnostic of its own" $
    length errs > 2
  checkEq "pricingErrors messages" ["smoke warning", "smoke error"]
    (drop (length errs - 2) (map pricingErrorMessage errs))
  checkEq "pricingErrors levels" [Warning, Fatal]
    (drop (length errs - 2) (map pricingErrorLevel errs))
  checkEq "pricingErrors details" ["first detail", "second detail"]
    (drop (length errs - 2) (map pricingErrorDetail errs))

  positions <- dailyPositions swp
  checkWith "dailyPositions non-empty" "the priced swap reports at least one day" $
    not (null positions)
  checkWith "dailyPositions quantity" "every day carries the pricing period's daily quantity" $
    all ((> 0) . edpQuantityAmount) positions

  flows <- paymentCashFlows swp
  checkWith "paymentCashFlows non-empty" "the priced swap reports at least one cash flow" $
    not (null flows)
  checkWith "paymentCashFlows discount factors" "a zero-rate curve discounts every flow at 1" $
    all (\f -> abs (discountFactor f - 1) < 1e-12) flows

  putStrLn "CheckEnergySwapOutArrays: OK"

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
