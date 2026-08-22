-- Smoke test: ConstNotionalCrossCurrencySwap, ConstNotionalCrossCurrencyBasisSwap,
-- ConstNotionalCrossCurrencyFixedVsFloatingSwap, and DiscountingConstNotionalCrossCurrencySwapEngine.
--
-- No cached upstream golden values are used here (see CLAUDE.md's guidance to prefer them where
-- available -- a full port of test-suite/constnotionalcrosscurrency*.cpp's fixtures is left as
-- follow-up work). Instead, each check is a martingale-style self-consistency check: build both
-- legs from the *same* index/schedule/nominal/spread, price with matching (in fact identical)
-- discount curves and spotFX=1 -- under that symmetry the pay and receive legs must have equal
-- in-currency NPV, so the swap's total NPV, and (for the basis swap) its fair pay/rec spreads,
-- must come out at zero. This is the same style of check CLAUDE.md prescribes for FX/equity
-- process examples (comparing simulated vs. discount-curve-implied forwards in TARF).
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant test/smoke/CheckConstNotionalCrossCurrencySwap.hs -o /tmp/checkxccy -outputdir /tmp/checkxccy_build && /tmp/checkxccy
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Currency
import QuantLib.Instrument
import QuantLib.Instrument.Swap
import QuantLib.CashFlow (RateAveragingType(..))
import QuantLib.InterestRate (Compounding(..))
import QuantLib.PricingEngine
import QuantLib.Quote
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

import SmokeCheck (checkClose, checkEq)

main :: IO ()
main = do
  let today = 11 `september` 2018
  cal <- calendar UnitedStatesSettlement
  setEvaluationDate (Just today)

  usd <- currency USD
  eur <- currency EUR
  flatDC <- dayCounter Actual365FixedStandard
  q <- simpleQuote 0.03
  curve <- flatForward today q flatDC Continuous Annual
  fxQuote <- simpleQuote 1.0
  legDC <- dayCounter (Actual360 False)
  usdLibor3m <- IR.iborIndex (IR.UsdLibor (3, Months)) (Just curve)

  spot <- advance cal today (2, Days) Following False
  maturity <- advance cal spot (5, Years) Following False
  sched <- schedule (Just spot) maturity (3, Months) cal ModifiedFollowing ModifiedFollowing
    Forward False Nothing Nothing

  engine <- discountingConstNotionalCrossCurrencySwapEngine usd curve eur curve fxQuote
    (Just False) (Just today) (Just today) Nothing

  -- ConstNotionalCrossCurrencyBasisSwap: identical index/schedule/nominal/spread on both legs,
  -- one tagged USD, the other EUR -- symmetric under the shared curve + spotFX=1.
  basisSwap <- constNotionalCrossCurrencyBasisSwap 100 usd sched usdLibor3m 0 1
    100 eur sched usdLibor3m 0 1 defaultConstNotionalCrossCurrencyBasisSwapOpts
  setPricingEngine basisSwap engine
  basisNPV <- npv basisSwap
  checkClose "ConstNotionalCrossCurrencyBasisSwap NPV (symmetric legs)" 0 basisNPV 1e-6
  payFair <- fairPaySpread basisSwap
  checkClose "ConstNotionalCrossCurrencyBasisSwap fairPaySpread" 0 payFair 1e-6
  recFair <- fairRecSpread basisSwap
  checkClose "ConstNotionalCrossCurrencyBasisSwap fairRecSpread" 0 recFair 1e-6

  -- Base-class getters, reached generically over the leaf.
  payCcy <- legCurrency basisSwap 0
  checkEq "ConstNotionalCrossCurrencySwap.legCurrency(0)" (show usd) (show payCcy)
  inCcyNpv0 <- inCcyLegNPV basisSwap 0
  inCcyNpv1 <- inCcyLegNPV basisSwap 1
  checkClose "inCcyLegNPV(0) == inCcyLegNPV(1) (symmetric legs, spotFX=1)" inCcyNpv0 inCcyNpv1 1e-6

  -- ConstNotionalCrossCurrencyFixedVsFloatingSwap: solve the fair fixed rate against a first
  -- guess, then rebuild at that rate and confirm the rebuilt swap reprices to zero.
  guess <- constNotionalCrossCurrencyFixedVsFloatingSwap Payer 100 usd sched 0.03 legDC
    ModifiedFollowing 0 cal 100 eur sched usdLibor3m 0 ModifiedFollowing 0 cal
    False False Nothing False 0 AveragingCompound
  setPricingEngine guess engine
  fair <- xccyFairRate guess

  priced <- constNotionalCrossCurrencyFixedVsFloatingSwap Payer 100 usd sched fair legDC
    ModifiedFollowing 0 cal 100 eur sched usdLibor3m 0 ModifiedFollowing 0 cal
    False False Nothing False 0 AveragingCompound
  setPricingEngine priced engine
  pricedNPV <- npv priced
  checkClose "ConstNotionalCrossCurrencyFixedVsFloatingSwap NPV at its own fair rate" 0 pricedNPV 1e-6

  putStrLn "ConstNotionalCrossCurrencySwap family: OK"

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
