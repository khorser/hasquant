-- Smoke test for the direct CMS, capped/floored CMS, and digital CMS coupon bindings.
import Control.Monad (unless)

import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.InterestRate
import QuantLib.Quote
import qualified QuantLib.TermStructure.Volatility as Vol
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
  settlement <- advance cal today (2, Days) Following False
  dc <- dayCounter Actual365FixedStandard
  curveQuote <- simpleQuote 0.05
  curve <- TS.flatForward today curveQuote dc Continuous Annual
  swapIndex <- IR.liborSwapIndex IR.EuriborSwapIsdaFixA (10, Years) (Just curve) (Just curve)
  volQuote <- simpleQuote 0.15
  vol <- Vol.constantSwaptionVolatility 2 cal Following volQuote dc ShiftedLognormal 0
  meanReversion <- simpleQuote 0.0
  pricer <- CF.analyticHaganPricer vol CF.NonParallelShifts meanReversion

  start <- advance cal settlement (20, Years) Unadjusted False
  end <- advance cal start (1, Years) Unadjusted False
  let cms = CF.cmsCoupon end 1.0 start end 2 swapIndex 1.0 0.0 Nothing Nothing dc False Nothing Preceding
  plain <- cms
  CF.setFloatingRateCouponPricer plain pricer
  plainRate <- CF.floatingRateCouponRate plain
  plainAmount <- CF.floatingRateCouponAmount plain
  unless (plainRate > 0 && plainAmount > 0) $ error "CMS coupon was not priced"

  capped <- CF.cappedFlooredCmsCoupon end 1.0 start end 2 swapIndex 1.0 0.0 (Just 0.03) Nothing Nothing Nothing dc False Nothing Preceding
  CF.setFloatingRateCouponPricer capped pricer
  cappedRate <- CF.floatingRateCouponRate capped
  unless (cappedRate < plainRate) $
    error "CMS cap was not applied"

  floored <- CF.cappedFlooredCmsCoupon end 1.0 start end 2 swapIndex 1.0 0.0 Nothing (Just 0.06) Nothing Nothing dc False Nothing Preceding
  CF.setFloatingRateCouponPricer floored pricer
  flooredRate <- CF.floatingRateCouponRate floored
  unless (flooredRate > plainRate) $
    error "CMS floor was not applied"

  replication <- CF.digitalReplication CF.ReplicationCentral 1.0e-4
  digital <- CF.digitalCmsCoupon plain (Just 0.03) CF.Long False (Just 0.005)
    Nothing CF.Long False Nothing (Just replication) False
  CF.setFloatingRateCouponPricer digital pricer
  digitalRate <- CF.floatingRateCouponRate digital
  callRate <- CF.digitalCmsCouponCallOptionRate digital
  unless (callRate > 0 && digitalRate > plainRate) $
    error "digital CMS call was not applied"

  schedule' <- schedule (Just start) end (1, Years) cal Unadjusted Unadjusted Backward False Nothing Nothing
  let legOpts = CF.defaultDigitalCmsLegOpts
        { CF.dcmlCallStrikes = [0.03]
        , CF.dcmlCallPayoffs = [0.005]
        , CF.dcmlReplication = Just replication
        }
      build opts = do
        leg <- CF.digitalCmsLeg schedule' swapIndex [1.0] dc Unadjusted [2] [1.0] [0.0] False opts
        CF.setCouponPricer leg pricer
        CF.npv leg curve False Nothing Nothing
  defaultNpv <- build legOpts
  explicitFalseNpv <- build (legOpts { CF.dcmlNakedOption = False })
  nakedNpv <- build (legOpts { CF.dcmlNakedOption = True })
  unless (abs (defaultNpv - explicitFalseNpv) < 1.0e-12 && nakedNpv < defaultNpv) $
    error "digital CMS leg options were not applied"

  putStrLn "CMS coupons: OK"
