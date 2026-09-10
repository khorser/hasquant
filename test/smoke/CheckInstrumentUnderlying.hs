-- Exercise every HasInstrumentUnderlying instance. Pricing the returned handle checks that
-- the accessor preserves the upstream shared object and its configured engine.
--
-- Run with: .claude/skills/run-hasquant/driver.sh test/smoke/CheckInstrumentUnderlying.hs
import Data.List.NonEmpty(fromList)

import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Instrument
import QuantLib.Instrument.Credit
import QuantLib.Instrument.Option(BermudanExercise(..), EuropeanExercise(..))
import QuantLib.Instrument.Swap
import QuantLib.PricingEngine
import QuantLib.Quote(simpleQuote)
import QuantLib.Settings
import QuantLib.TermStructure.Credit
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

import SmokeCheck (checkWith)

main :: IO ()
main = do
  cal <- calendar TARGET
  today <- evaluationDate >>= \d -> adjust cal d Following
  setEvaluationDate (Just today)
  settl <- advance cal today (2, Days) Following False
  dc365 <- dayCounter Actual365FixedStandard
  thirty360bb <- dayCounter Thirty360BondBasis
  act360 <- dayCounter (Actual360 False)

  flatQ <- simpleQuote 0.03
  ts <- flatForward (ReferenceDate settl) flatQ dc365 Continuous Annual
  euribor6m <- IR.iborIndex IR.Euribor6M (Just ts)
  swapEngine <- discountingSwapEngine ts Nothing Nothing Nothing

  start <- advance cal settl (1, Years) ModifiedFollowing False
  maturity <- advance cal start (10, Years) ModifiedFollowing False
  fixedSchedule <- schedule (Just start) maturity (1, Years) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
  floatSchedule <- schedule (Just start) maturity (6, Months) cal ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing

  vswp <- vanillaSwap Payer 1.0 fixedSchedule 0.04 thirty360bb floatSchedule euribor6m 0.0 act360 (Just ModifiedFollowing) Nothing
  setPricingEngine vswp swapEngine
  vswpNpv <- npv vswp
  exDates <- fixedLeg vswp >>= CF.toCouponLeg >>= CF.couponAccrualStartDates
  let bermudan = Bermudan (BermudanExercise (fromList exDates) False)

  -- Swaption -> FixedVsFloatingSwap
  swpn <- swaption vswp bermudan Physical PhysicalOTC
  underlyingSwap swpn >>= npv >>= \v ->
    checkWith "Swaption underlying" "same NPV as the swap the swaption was built from" (v == vswpNpv)

  -- NonstandardSwaption -> NonstandardSwap
  nsSwap <- nonstandardSwapFromVanilla vswp
  setPricingEngine nsSwap swapEngine
  nsNpv <- npv nsSwap
  nsSwpn <- nonstandardSwaption nsSwap bermudan Physical PhysicalOTC
  underlyingSwap nsSwpn >>= npv >>= \v ->
    checkWith "NonstandardSwaption underlying" "same NPV as the nonstandard swap it wraps" (v == nsNpv)

  -- FloatFloatSwaption -> FloatFloatSwap
  -- two Ibor legs, not a CMS leg: a CMS leg would need a coupon pricer before it can price.
  euribor3m <- IR.iborIndex IR.Euribor3M (Just ts)
  ffSwap <- floatFloatSwap Payer 1.0 1.0 fixedSchedule euribor3m thirty360bb floatSchedule
              euribor6m act360 defaultFloatFloatSwapOpts
  setPricingEngine ffSwap swapEngine
  ffNpv <- npv ffSwap
  ffSwpn <- floatFloatSwaption ffSwap bermudan Physical PhysicalOTC
  underlyingSwap ffSwpn >>= npv >>= \v ->
    checkWith "FloatFloatSwaption underlying" "same NPV as the float-float swap it wraps" (v == ffNpv)

  -- IrregularSwaption -> IrregularSwap
  fixedL <- fixedLeg vswp
  floatL <- floatingLeg vswp
  irr <- irregularSwap Payer fixedL floatL
  setPricingEngine irr swapEngine
  irrNpv <- npv irr
  irrSwpn <- irregularSwaption irr bermudan IrregularPhysical
  underlyingSwap irrSwpn >>= npv >>= \v ->
    checkWith "IrregularSwaption underlying" "same NPV as the irregular swap it wraps" (v == irrNpv)

  -- CdsOption -> CreditDefaultSwap
  hazardQ <- simpleQuote 0.01234
  probCurve <- flatHazardRate (SettlementDays 0 cal) hazardQ act360
  cdsIssue <- advance cal today (-1, Years) ModifiedFollowing False
  cdsMaturity <- advance cal cdsIssue (10, Years) ModifiedFollowing False
  cdsSched <- schedule (Just cdsIssue) cdsMaturity (6, Months) cal ModifiedFollowing ModifiedFollowing
                Forward False Nothing Nothing
  -- Buyer, since upstream requires a receiver (Seller) CDS option to knock out.
  cds <- creditDefaultSwap Buyer 10000 0.0120 cdsSched ModifiedFollowing act360 True True
           Nothing FaceValue act360 True Nothing 3
  cdsEngine <- midPointCdsEngine probCurve 0.4 ts Nothing
  setPricingEngine cds cdsEngine
  cdsNpv <- npv cds
  cdsExercise <- advance cal today (1, Years) ModifiedFollowing False
  opt <- cdsOption cds (European (EuropeanExercise cdsExercise)) False
  underlyingSwap opt >>= npv >>= \v ->
    checkWith "CdsOption underlying" "same NPV as the CDS it wraps" (v == cdsNpv)

  putStrLn "instrument underlyings: all checks passed"
