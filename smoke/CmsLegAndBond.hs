-- Smoke test for cmsLeg/cmsLegFull, the widened iborLeg/iborLegFull, and cmsRateBond.
-- Checks (all directional, not just "differs" -- mirrors the CPIInterpolationType
-- gotcha in CLAUDE.md where a silently-wrong wiring can still produce *some*
-- different-looking output):
-- 1. A capped cmsLeg NPV < an uncapped cmsLeg NPV, and a floored cmsLeg NPV > uncapped,
--    proving caps/floors actually reach CappedFlooredCmsCoupon inside the leg builder
--    and aren't silently dropped.
-- 2. Same directional check for cmsRateBond (with/without caps/floors).
-- 3. iborLegFull/cmsLegFull build and price without error under non-default opts
--    (nonzero paymentLag, a nonzero exCouponPeriod) -- this is what would catch a
--    silent miswiring of the newly-widened fields specifically.
--
-- Run with: cabal exec -- ghc -package hasquant smoke/CmsLegAndBond.hs -o /tmp/cmslegbond -outputdir /tmp/cmslegbond_build && /tmp/cmslegbond
import Control.Monad (unless)

import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.InterestRate
import qualified QuantLib.Instrument.Bond as Bond
import QuantLib.Quote
import QuantLib.TermStructure.Volatility
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

main :: IO ()
main = do
  cal <- calendar TARGET
  today <- evaluationDate >>= \d -> adjust cal d Following
  setEvaluationDate (Just today)
  settl <- advance cal today (2, Days) Following False
  dc365 <- dayCounter Actual365FixedStandard
  thirty360bb <- dayCounter Thirty360BondBasis

  flatQ <- simpleQuote 0.03
  ts <- TS.flatForward today flatQ dc365 Continuous Annual
  swapBase <- IR.liborSwapIndex IR.EuriborSwapIsdaFixA (10, Years) (Just ts) (Just ts)
  euribor6m <- IR.iborIndex IR.Euribor6M (Just ts)

  volQ <- simpleQuote 0.20
  swaptionVol <- constantSwaptionVolatility 2 cal Following volQ dc365 ShiftedLognormal 0.0
  reversionQ <- simpleQuote 0.01
  pricer <- CF.analyticHaganPricer swaptionVol CF.Standard reversionQ

  optionletVol <- constantOptionletVolatility today cal Following volQ dc365 ShiftedLognormal 0.0
  iborPricer <- CF.blackIborCouponPricer optionletVol CF.Black76 Nothing Nothing

  start <- advance cal settl (1, Years) ModifiedFollowing False
  maturity <- advance cal start (10, Years) ModifiedFollowing False
  sched <- schedule (Just start) maturity (1, Years) cal ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing

  let buildCmsLeg caps floors = do
        leg <- CF.cmsLeg sched swapBase [1000000] thirty360bb Following [2] [1.0] [0.0] caps floors False False
        CF.setCouponPricer leg pricer
        CF.npv leg ts False Nothing Nothing

  uncappedNpv <- buildCmsLeg [] []
  cappedNpv <- buildCmsLeg [0.03] []
  flooredNpv <- buildCmsLeg [] [0.03]

  putStrLn $ "cmsLeg NPV uncapped=" ++ show uncappedNpv ++ " capped=" ++ show cappedNpv ++ " floored=" ++ show flooredNpv
  unless (cappedNpv < uncappedNpv) $ error "capped cmsLeg NPV should be lower than uncapped"
  unless (flooredNpv > uncappedNpv) $ error "floored cmsLeg NPV should be higher than uncapped"

  -- iborLeg/iborLegFull: directional caps/floors check, plus a non-default IborLegOpts
  -- exercise to prove the newly-widened fields (paymentLag, exCouponPeriod, ...) wire
  -- through without error.
  let buildIborLeg caps floors = do
        leg <- CF.iborLeg sched euribor6m [1000000] thirty360bb Following [2] [1.0] [0.0] caps floors False False
        CF.setCouponPricer leg iborPricer
        CF.npv leg ts False Nothing Nothing
  iborUncapped <- buildIborLeg [] []
  iborCapped <- buildIborLeg [0.03] []
  iborFloored <- buildIborLeg [] [0.03]
  putStrLn $ "iborLeg NPV uncapped=" ++ show iborUncapped ++ " capped=" ++ show iborCapped ++ " floored=" ++ show iborFloored
  unless (iborCapped < iborUncapped) $ error "capped iborLeg NPV should be lower than uncapped"
  unless (iborFloored > iborUncapped) $ error "floored iborLeg NPV should be higher than uncapped"

  iborFullLeg <- CF.iborLegFull sched euribor6m [1000000] thirty360bb Following [2] [1.0] [0.0] [] [] False False
    CF.defaultIborLegOpts { CF.ilgPaymentLag = 2, CF.ilgExCouponPeriod = (2, Days) }
  CF.setCouponPricer iborFullLeg iborPricer
  iborFullNpv <- CF.npv iborFullLeg ts False Nothing Nothing
  putStrLn $ "iborLegFull (non-default opts) NPV=" ++ show iborFullNpv

  cmsFullLeg <- CF.cmsLegFull sched swapBase [1000000] thirty360bb Following [2] [1.0] [0.0] [] [] False False
    CF.defaultCmsLegOpts { CF.cmslExCouponPeriod = (2, Days) }
  CF.setCouponPricer cmsFullLeg pricer
  cmsFullNpv <- CF.npv cmsFullLeg ts False Nothing Nothing
  putStrLn $ "cmsLegFull (non-default opts) NPV=" ++ show cmsFullNpv

  -- cmsRateBond: same directional caps/floors check.
  let buildCmsRateBond caps floors = do
        bond <- Bond.cmsRateBond 2 100 sched swapBase thirty360bb Following 2 [1.0] [0.0] caps floors False 100 Nothing
        leg <- Bond.cashFlows bond
        CF.setCouponPricer leg pricer
        CF.npv leg ts False Nothing Nothing

  bondUncapped <- buildCmsRateBond [] []
  bondCapped <- buildCmsRateBond [0.03] []
  bondFloored <- buildCmsRateBond [] [0.03]
  putStrLn $ "cmsRateBond NPV uncapped=" ++ show bondUncapped ++ " capped=" ++ show bondCapped ++ " floored=" ++ show bondFloored
  unless (bondCapped < bondUncapped) $ error "capped cmsRateBond NPV should be lower than uncapped"
  unless (bondFloored > bondUncapped) $ error "floored cmsRateBond NPV should be higher than uncapped"

  putStrLn "OK"
