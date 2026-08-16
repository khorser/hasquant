-- Smoke test: LinearTsrPricer's Settings strategy is dispatched through a plain int
-- switch in cbits/qlInstrument.cpp (qlLinearTsrPricer), not a c2hs {#enum#} -- see the
-- CPIInterpolationType gotcha in CLAUDE.md for why an enum-dispatched shim needs an
-- end-to-end value check, not just a clean build. This constructs the same CMS coupon
-- leg under two different LinearTsrPricerStrategy values and asserts the resulting
-- coupon rates differ; a stale/misordered switch case would silently alias two
-- strategies to the same behaviour instead.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckLinearTsrPricer.hs -o /tmp/checklinearts -outputdir /tmp/checklinearts_build && /tmp/checklinearts
import qualified QuantLib.CashFlow as CF
import qualified QuantLib.InterestRate as IR
import QuantLib.Index.InterestRate(liborSwapIndex, LiborSwapIndexType(EurLiborSwapIsdaFixA))
import QuantLib.Quote(simpleQuote, asQuote)
import QuantLib.Settings(setEvaluationDate)
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.TermStructure.Volatility(constantSwaptionVolatility')
import QuantLib.TermStructure.Yield(flatForward')

import SmokeCheck (checkWith)

main :: IO ()
main = do
  let refDate = 11 `december` 2012
  setEvaluationDate (Just refDate)
  cal <- calendar TARGET
  dc <- dayCounter Actual365FixedStandard
  fwdRateQ <- simpleQuote 0.05
  fwdCurve <- flatForward' 0 cal fwdRateQ dc IR.Continuous Annual
  swapIdx <- liborSwapIndex EurLiborSwapIsdaFixA (10, Years) (Just fwdCurve) (Just fwdCurve)
  volQ <- simpleQuote 0.15
  atmVol <- constantSwaptionVolatility' refDate cal ModifiedFollowing volQ dc IR.ShiftedLognormal 0
  meanRevQ <- simpleQuote 0.0 >>= asQuote
  startDate <- addPeriod refDate (20, Years)
  endDate <- addPeriod startDate (1, Years)
  sch <- schedule (Just startDate) endDate (1, Years) cal Unadjusted Unadjusted Backward False Nothing Nothing
  let mkLeg = CF.cmsLeg sch swapIdx [1.0] dc Unadjusted [] [] [] [] [] False False
      bounds = Just (0.0001, 2.0)

  legRateBound <- mkLeg
  pricerRateBound <- CF.linearTsrPricer atmVol meanRevQ Nothing (CF.LinearTsrPricerSettings CF.LinearTsrRateBound bounds)
  CF.setCouponPricer legRateBound pricerRateBound
  rateRateBound <- CF.nextCouponRate legRateBound True Nothing

  legVegaRatio <- mkLeg
  pricerVegaRatio <- CF.linearTsrPricer atmVol meanRevQ Nothing (CF.LinearTsrPricerSettings (CF.LinearTsrVegaRatio 0.01) bounds)
  CF.setCouponPricer legVegaRatio pricerVegaRatio
  rateVegaRatio <- CF.nextCouponRate legVegaRatio True Nothing

  legPriceThreshold <- mkLeg
  pricerPriceThreshold <- CF.linearTsrPricer atmVol meanRevQ Nothing (CF.LinearTsrPricerSettings (CF.LinearTsrPriceThreshold 1.0e-8) bounds)
  CF.setCouponPricer legPriceThreshold pricerPriceThreshold
  ratePriceThreshold <- CF.nextCouponRate legPriceThreshold True Nothing

  legBSStdDevs <- mkLeg
  pricerBSStdDevs <- CF.linearTsrPricer atmVol meanRevQ Nothing (CF.LinearTsrPricerSettings (CF.LinearTsrBSStdDevs 3.0) bounds)
  CF.setCouponPricer legBSStdDevs pricerBSStdDevs
  rateBSStdDevs <- CF.nextCouponRate legBSStdDevs True Nothing

  putStrLn ("RateBound=" ++ show rateRateBound ++ ", VegaRatio=" ++ show rateVegaRatio
    ++ ", PriceThreshold=" ++ show ratePriceThreshold ++ ", BSStdDevs=" ++ show rateBSStdDevs)
  checkWith "LinearTsrPricer strategy dispatch (RateBound vs VegaRatio)"
    "coupon rates differ (equality means the strategy switch may be stale/misordered)"
    (rateRateBound /= rateVegaRatio)
  checkWith "LinearTsrPricer strategy dispatch (VegaRatio vs PriceThreshold)"
    "coupon rates differ (equality means the strategy switch may be stale/misordered)"
    (rateVegaRatio /= ratePriceThreshold)
  checkWith "LinearTsrPricer strategy dispatch (PriceThreshold vs BSStdDevs)"
    "coupon rates differ (equality means the strategy switch may be stale/misordered)"
    (ratePriceThreshold /= rateBSStdDevs)

  -- Nothing (upstream's own default-bounds overload) must reach a genuinely different code
  -- path from Just explicit bounds -- see the defaultBounds_/normal-vol-adjustment note on
  -- LinearTsrPricerSettings in QuantLib.CashFlow. That adjustment (lower bound -> min(-upper,
  -- lower)) only fires under Normal vol -- both checks above use ShiftedLognormal, where
  -- Just/Nothing are indistinguishable by design (confirmed: they give identical rates there),
  -- so this needs its own Normal-vol fixture to actually exercise the haveBounds branch.
  normalVolQ <- simpleQuote 0.008
  atmVolNormal <- constantSwaptionVolatility' refDate cal ModifiedFollowing normalVolQ dc IR.Normal 0

  -- Deliberately NOT upstream's own default bounds (0.0001, 2.0): passing those exact
  -- numbers as Just would make Just and Nothing coincide even with haveBounds wired
  -- correctly, since defaultBounds_'s min(-upper, lower) adjustment (only applied when
  -- Nothing) would then be computed from the very same numbers this Just already pins --
  -- both collapse to the identical adjusted lower bound (-2.0) and mask the wiring
  -- entirely. Confirmed empirically: the first version of this check used (0.0001, 2.0)
  -- and passed even with a Just/Nothing mixup, for exactly this reason.
  legExplicitBounds <- mkLeg
  pricerExplicitBounds <- CF.linearTsrPricer atmVolNormal meanRevQ Nothing
    (CF.LinearTsrPricerSettings CF.LinearTsrRateBound (Just (0.001, 1.0)))
  CF.setCouponPricer legExplicitBounds pricerExplicitBounds
  rateExplicitBounds <- CF.nextCouponRate legExplicitBounds True Nothing

  legDefaultBounds <- mkLeg
  pricerDefaultBounds <- CF.linearTsrPricer atmVolNormal meanRevQ Nothing
    (CF.LinearTsrPricerSettings CF.LinearTsrRateBound Nothing)
  CF.setCouponPricer legDefaultBounds pricerDefaultBounds
  rateDefaultBounds <- CF.nextCouponRate legDefaultBounds True Nothing

  putStrLn ("Normal vol, RateBound (Just explicit bounds)=" ++ show rateExplicitBounds
    ++ ", RateBound (Nothing/default bounds)=" ++ show rateDefaultBounds)
  checkWith "LinearTsrPricerSettings Just vs Nothing bounds (Normal vol)"
    "coupon rates differ (equality means haveBounds/defaultBounds_ may not be wired through)"
    (rateExplicitBounds /= rateDefaultBounds)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
