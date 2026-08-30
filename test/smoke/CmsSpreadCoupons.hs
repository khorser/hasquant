-- Smoke test for CMS-spread coupon construction and CMS-pricer handoff.
import Control.Monad (unless)

import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Index as Index
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.InterestRate
import qualified QuantLib.Quote as Quote
import qualified QuantLib.Settings as Settings
import qualified QuantLib.TermStructure.Volatility as Vol
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

main :: IO ()
main = do
  let refDate = 23 `february` 2018
  Settings.setEvaluationDate (Just refDate)
  cal <- calendar TARGET
  dc <- dayCounter (Actual360 False)
  curveQuote <- Quote.simpleQuote 0.02
  curve <- TS.flatForward refDate curveQuote dc Continuous Annual
  cms10y <- IR.liborSwapIndex IR.EurLiborSwapIsdaFixA (10, Years) (Just curve) (Just curve)
  cms2y <- IR.liborSwapIndex IR.EurLiborSwapIsdaFixA (2, Years) (Just curve) (Just curve)
  spreadIndex <- IR.swapSpreadIndex "cms10y2y" cms10y cms2y 1.0 (-1.0)
  volQuote <- Quote.simpleQuote 0.20
  vol <- Vol.constantSwaptionVolatility' refDate cal Following volQuote dc ShiftedLognormal 0
  meanReversion <- Quote.simpleQuote 0.01 >>= Quote.asQuote
  correlation <- Quote.simpleQuote 0.6 >>= Quote.asQuote
  cmsPricer <- CF.linearTsrPricer vol meanReversion (Just curve)
    (CF.LinearTsrPricerSettings CF.LinearTsrRateBound Nothing)
  spreadPricer <- CF.lognormalCmsSpreadPricer cmsPricer correlation (Just curve) 32 Nothing Nothing Nothing
  valueDate <- advance cal refDate (2, Days) Following False
  payDate <- addPeriod valueDate (1, Years)
  plain <- CF.cmsSpreadCoupon payDate 10000 valueDate payDate 2 spreadIndex
    1.0 0.0 Nothing Nothing dc False Nothing Preceding
  capped <- CF.cappedFlooredCmsSpreadCoupon payDate 10000 valueDate payDate 2 spreadIndex
    1.0 0.0 (Just 0.015) Nothing Nothing Nothing dc False Nothing Preceding
  CF.setFloatingRateCouponPricer plain spreadPricer
  CF.setFloatingRateCouponPricer capped spreadPricer
  Index.addFixing cms10y refDate 0.05 False
  Index.addFixing cms2y refDate 0.03 False
  plainRate <- CF.floatingRateCouponRate plain
  cappedRate <- CF.floatingRateCouponRate capped
  Index.clearFixings cms10y
  Index.clearFixings cms2y
  unless (abs (plainRate - 0.02) < 1.0e-12 && abs (cappedRate - 0.015) < 1.0e-12) $
    error "CMS-spread coupon did not reproduce the fixed spread or cap"
  putStrLn "CMS-spread coupons: OK"
