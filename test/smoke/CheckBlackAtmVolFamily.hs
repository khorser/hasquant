-- Smoke test: AbcdAtmVolCurve, SabrVolSurface and OptionletStripper2.
--
-- 1. AbcdAtmVolCurve fits an ABCD functional form to quoted ATM vols. With flat input
--    quotes the fit should stay close to flat and converge with a small rms error.
-- 2. SabrVolSurface's own volatilitySpreads(Date) linearly interpolates the raw quoted
--    vol-spread quotes across optionTenors -- at a date landing exactly on a grid tenor
--    that's the identity, so with flat spread quotes the surface must echo the input
--    value back exactly.
-- 3. OptionletStripper2 reconciles OptionletStripper1's forward-forward stripping
--    against an ATM CapFloorTermVolCurve (upstream: optionletstripper.cpp's
--    testFlatTermVolatilityStripping2). With flat term-vol inputs on both the surface
--    and the ATM curve, stripping via either path must produce the same caplet vols, so
--    pricing the same cap through each stripped structure's engine gives matching NPVs.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckBlackAtmVolFamily.hs -o /tmp/checkblackatmvol -outputdir /tmp/checkblackatmvol_build && /tmp/checkblackatmvol
import Control.Monad(forM_)
import Text.Printf(printf)

import QuantLib.CashFlow(iborLeg)
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(Euribor6M))
import QuantLib.Instrument(npv, setPricingEngine)
import QuantLib.Instrument.CapFloor(cap)
import qualified QuantLib.InterestRate as IR
import QuantLib.Math(objectMatrix)
import QuantLib.PricingEngine(blackCapFloorEngine')
import QuantLib.Quote(simpleQuote)
import QuantLib.Settings(setEvaluationDate)
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.TermStructure.Yield(flatForward, relinkableYieldTermStructure)
import QuantLib.TermStructure.Volatility

import SmokeCheck (checkClose, checkWith, report)

main :: IO ()
main = do
  refDate <- today
  setEvaluationDate (Just refDate)
  cal <- calendar TARGET
  dc <- dayCounter Actual365FixedStandard
  let tenors = [(n, Years) | n <- [1 .. 10 :: Word]]

  -- 1. AbcdAtmVolCurve: flat input quotes, expect a near-flat fit.
  abcdQs <- mapM (const (simpleQuote 0.18)) tenors
  abcdCurve <- abcdAtmVolCurve 0 cal tenors abcdQs (replicate 10 True) Following dc
  rmsErr <- abcdAtmVolCurveRmsError abcdCurve
  maxErr <- abcdAtmVolCurveMaxError abcdCurve
  a <- abcdAtmVolCurveA abcdCurve
  b <- abcdAtmVolCurveB abcdCurve
  c <- abcdAtmVolCurveC abcdCurve
  d <- abcdAtmVolCurveD abcdCurve
  endC <- abcdAtmVolCurveEndCriteria abcdCurve
  printf "AbcdAtmVolCurve: a=%.6f b=%.6f c=%.6f d=%.6f rms=%.2e max=%.2e endCriteria=%s\n"
    a b c d rmsErr maxErr (show endC)
  checkWith "AbcdAtmVolCurve rmsError" "small (< 0.05) on flat input" (rmsErr < 0.05)
  atmv <- atmVolForPeriod abcdCurve (5, Years) False
  checkClose "AbcdAtmVolCurve atmVol at 5Y" 0.18 atmv 0.05
  ks <- abcdAtmVolCurveK abcdCurve
  checkWith "AbcdAtmVolCurve k length" "matches optionTenors (10)" (length ks == 10)

  -- 2. SabrVolSurface: flat vol-spread quotes echoed exactly at a grid tenor.
  let sabrTenors = [(n, Years) | n <- [1 .. 5 :: Word]]
  atmQs <- mapM (const (simpleQuote 0.18)) sabrTenors
  atmCurve <- abcdAtmVolCurve 0 cal sabrTenors atmQs (replicate 5 True) Following dc
  idx <- iborIndex Euribor6M Nothing
  let spreads = [-0.01, 0, 0.01]
  spreadQs <- mapM (const (simpleQuote 0.02)) [1 .. (5 * 3 :: Int)]
  let volSpreads = either error id $ objectMatrix 5 3 spreadQs
  surf <- sabrVolSurface idx atmCurve sabrTenors spreads volSpreads
  vs <- sabrVolSurfaceVolatilitySpreadsForPeriod surf (3, Years)
  checkWith "SabrVolSurface volatilitySpreads length" "matches atmRateSpreads (3)" (length vs == 3)
  forM_ vs $ \v -> checkClose "SabrVolSurface volatilitySpreads at grid tenor" 0.02 v 1.0e-8
  d3 <- sabrVolSurfaceOptionDateFromTenor surf (3, Years)
  checkWith "SabrVolSurface optionDateFromTenor(3Y)" "after the evaluation date" (d3 > refDate)
  curveBack <- sabrVolSurfaceAtmCurve surf
  vBack <- atmVolForPeriod curveBack (3, Years) False
  checkClose "SabrVolSurface atmCurve roundtrip atmVol at 3Y" 0.18 vBack 1.0e-6
  _ <- sabrVolSurfaceIndex surf
  putStrLn "SabrVolSurface: OK, echoes flat vol spreads and round-trips its ATM curve"

  -- 3. OptionletStripper2 vs OptionletStripper1 on flat term vol inputs.
  -- Pinned to a fixed historical date (rather than `today`) so the cap's first floating
  -- coupon never lands on a real-world Euribor6M fixing hasquant hasn't recorded.
  let capEvalDate = 11 `december` 2012
  setEvaluationDate (Just capEvalDate)
  discountQ <- simpleQuote 0.02
  discountFF <- flatForward capEvalDate discountQ dc IR.Continuous Annual
  discountH <- relinkableYieldTermStructure (Just discountFF)
  forecastFF <- flatForward capEvalDate discountQ dc IR.Continuous Annual
  forecastH <- relinkableYieldTermStructure (Just forecastFF)
  capIdx <- iborIndex Euribor6M (Just forecastH)
  settle <- advance cal capEvalDate (2, Days) Following False
  maturity <- advance cal settle (5, Years) ModifiedFollowing False
  floatDC <- dayCounter (Actual360 False)
  floatSch <- schedule (Just settle) maturity (6, Months) cal
    ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
  leg <- iborLeg floatSch capIdx [1000000] floatDC ModifiedFollowing [2] [1.0] [0.0] [] [] False False
  capfl <- cap leg [0.05]

  flatVolQ <- simpleQuote 0.18
  let capMatrix = either error id $ objectMatrix 10 3 (replicate 30 flatVolQ)
  capVolSurface <- capFloorTermVolSurface 0 cal Following tenors [0.02, 0.05, 0.08] capMatrix dc
  curveVolQs <- mapM (const (simpleQuote 0.18)) tenors
  capVolCurve <- capFloorTermVolCurve 0 cal Following (zipWith (\(n, u) q -> (n, u, q)) tenors curveVolQs) dc

  stripper1 <- optionletStripper1 capVolSurface capIdx Nothing 1.0e-6 100
    (Just discountH) IR.ShiftedLognormal 0 False Nothing
  stripper2 <- optionletStripper2 capVolSurface capIdx Nothing 1.0e-6 100
    (Just discountH) IR.ShiftedLognormal 0 False Nothing capVolCurve
  vol2 <- optionletStripper2AsOptionletVolatilityStructure stripper2

  eng1 <- blackCapFloorEngine' discountH stripper1
  setPricingEngine capfl eng1
  price1 <- npv capfl

  eng2 <- blackCapFloorEngine' discountH vol2
  setPricingEngine capfl eng2
  price2 <- npv capfl

  report "OptionletStripper1-stripped cap NPV" price1
  report "OptionletStripper2-stripped cap NPV" price2
  checkWith "OptionletStripper2 vs OptionletStripper1 cap NPV" "match within 1e-5 relative"
    (price1 > 1 && abs (price1 - price2) / abs price1 < 1.0e-5)

  atmStrikes <- optionletStripper2AtmCapFloorStrikes stripper2
  atmPrices <- optionletStripper2AtmCapFloorPrices stripper2
  spreadsVol <- optionletStripper2SpreadsVol stripper2
  checkWith "OptionletStripper2 atmCapFloorStrikes length" "matches optionTenors (10)" (length atmStrikes == 10)
  checkWith "OptionletStripper2 atmCapFloorPrices length" "matches optionTenors (10)" (length atmPrices == 10)
  checkWith "OptionletStripper2 spreadsVol length" "matches optionTenors (10)" (length spreadsVol == 10)
  putStrLn "OptionletStripper2: OK, reprices the same as OptionletStripper1 and diagnostic getters are shaped correctly"
