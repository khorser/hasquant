module QuantLib.Example.Bond
  (
    Result(..)
  , run
  ) where
import Control.Monad((>=>))

import Data.List(zip4)
import qualified Data.List.NonEmpty as NE
import Data.Time.Calendar(fromGregorian)

import qualified QuantLib.CashFlow as CF
import QuantLib.InterestRate
import QuantLib.Index
import qualified QuantLib.Index.InterestRate as I
import QuantLib.Instrument
import QuantLib.Instrument.Bond
import QuantLib.Math
import QuantLib.PricingEngine
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule

data Result = Result
  { npvR :: (Double, Double, Double)
  , cleanPriceR :: (Double, Double, Double)
  , dirtyPriceR :: (Double, Double, Double)
  , accruedAmountR :: (Double, Double, Double)
  , previousCoupon :: (Double, Double)
  , nextCoupon :: (Double, Double)
  , yieldR :: (Double, Double, Double)
  , cleanPriceFromYieldR :: Double
  , yieldFromCleanPriceR :: Double
  , nextCouponDate :: (Day, Day, Day)
  , tradable :: (Bool, Bool, Bool)
  , cfnpvR :: Double
  , cfnpvbpsR :: (Double, Double)
  , bpsR :: Double
  }

-- This example works with a fixed set of three bonds (and a two-bond subset) all the
-- way through, and every Result field is correspondingly a tuple. Keeping them as
-- tuples rather than lists carries that arity in the types, so there is no list
-- length to re-check: these replace a pair of `error`-throwing listToTuple/listToTriple
-- converters, and with them the `!!` and `fromJust` uses further down.
mapPair :: Applicative f => (a -> f b) -> (a, a) -> f (b, b)
mapPair f (x, y) = (,) <$> f x <*> f y

mapTriple :: Applicative f => (a -> f b) -> (a, a, a) -> f (b, b, b)
mapTriple f (x, y, z) = (,,) <$> f x <*> f y <*> f z

zipTriple :: (a -> b -> c) -> (a, a, a) -> (b, b, b) -> (c, c, c)
zipTriple f (x, y, z) (x', y', z') = (f x x', f y y', f z z')

sequenceTriple :: Applicative f => (f a, f a, f a) -> f (a, a, a)
sequenceTriple (x, y, z) = (,,) <$> x <*> y <*> z

-- |Calendars, day counters, settlement dates and the discount curve, built once
-- and threaded through bond construction and pricing.
data MarketData = MarketData
  { targetCal :: Calendar
  , nyseCal :: Calendar
  , usGovBondCal :: Calendar
  , actual365Fixeddc :: DayCounter
  , actActBond :: DayCounter
  , actActISDA :: DayCounter
  , actual360dc :: DayCounter
  , thirty360Europeandc :: DayCounter
  , settlDate :: Day
  , todaysDate :: Day
  , discountCurve :: YieldTermStructure
  }

buildMarketData :: IO MarketData
buildMarketData = do
  actual365Fixeddc' <- dayCounter Actual365FixedStandard
  actActBond' <- dayCounter ActualActualBond
  actActISDA' <- dayCounter ActualActualISDA
  actual360dc' <- dayCounter (Actual360 False)
  thirty360Europeandc' <- dayCounter Thirty360European

  targetCal' <- calendar TARGET
  nyseCal' <- calendar UnitedStatesNYSE
  usGovBondCal' <- calendar UnitedStatesGovernmentBond

  settlDate' <- adjust targetCal' (18 `september` 2008) Following
  todaysDate' <- advance targetCal'
                        settlDate'
                        (-(fromIntegral fixDays), Days)
                        Following
                        False
  setEvaluationDate (Just todaysDate')
  discDepoHelpers <- mapM
    (\(q, p) -> do
      r <- simpleQuote q
      depositRateHelper
        r
        (p, Months)
        fixDays
        targetCal'
        ModifiedFollowing
        True
        actual365Fixeddc')
    $ zip zcQuotes zcTenors
  quotes <- mapM simpleQuote marketQuotes
  discBondHelpers <- mapM
    (\(q, c, i, m) -> do
      s <- schedule i m (6, Months) usGovBondCal' Unadjusted
             Unadjusted Backward False Nothing Nothing
      fixedRateBondHelper q settlementDays 100.0 s (c NE.:| [])
            actActBond' Unadjusted redemption i >>= asRateHelper)
    $ zip4 quotes couponRates issueDates maturities
  ts <- piecewiseYieldCurve
          settlDate'
          (NE.fromList (discDepoHelpers ++ discBondHelpers))
          actActISDA'
          []
          Discount
          LogLinear
          --(Cubic $ NaturalSpline True)
          --(LogCubic $ Parabolic False)
          --(LogCubic Kruger)
          --(Cubic FritschButland)
          --Abcd

  --df <- discount ts (fromGregorian 2011 08 03) True
  return MarketData
    { targetCal = targetCal'
    , nyseCal = nyseCal'
    , usGovBondCal = usGovBondCal'
    , actual365Fixeddc = actual365Fixeddc'
    , actActBond = actActBond'
    , actActISDA = actActISDA'
    , actual360dc = actual360dc'
    , thirty360Europeandc = thirty360Europeandc'
    , settlDate = settlDate'
    , todaysDate = todaysDate'
    , discountCurve = ts
    }

buildBonds :: MarketData -> IO (Bond, Bond, Bond, PricingEngine)
buildBonds md = do
  pricing <- discountingBondEngine (discountCurve md) Nothing
  -- Fixed 4.5% US Treasury Note
  fixedSchedule <- schedule (Just (15 `may` 2007))
                                     (15 `may` 2017)
                                     (6, Months)
                                     (usGovBondCal md)
                                     Unadjusted
                                     Unadjusted
                                     Backward
                                     False
                                     Nothing
                                     Nothing
  fixedBond <- fixedRateBond settlementDays
                                  faceAmount
                                  fixedSchedule
                                  (0.045 NE.:| [])
                                  (actActBond md)
                                  ModifiedFollowing
                                  100.0
                                  (Just $ 15 `may` 2007)
                                  (usGovBondCal md)
                                  (0, Days) (usGovBondCal md) Unadjusted False (actActBond md) >>= asBond
  zcBond <- zeroCouponBond settlementDays
                               (usGovBondCal md)
                               faceAmount
                               (15 `august` 2013)
                               Following
                               116.92
                               (Just $ 15 `august` 2003)
  depoLiborHelpers <-
    mapM (\(q, p) ->
      do
        quote <- simpleQuote q
        depositRateHelper quote p fixDays (targetCal md)
                                       ModifiedFollowing
                                       True (actual360dc md)) $
          zip liborDepoQuotes liborDepoTerms

  eur6M <- I.iborIndex I.Euribor6M Nothing

  swapLiborHelpers <-
    mapM (\(q, n) ->
      do
        quote <- simpleQuote q
        swapRateHelper' quote (n, Years) (targetCal md) Annual Unadjusted
                              (thirty360Europeandc md) eur6M Nothing (1, Days) Nothing
                              Nothing LastRelevantDate Nothing False Nothing Nothing Nothing >>= asRateHelper) $
          zip liborSwapQuotes liborSwapTerms

  fwdCurve <- piecewiseYieldCurve
                (settlDate md)
                (NE.fromList (depoLiborHelpers ++ swapLiborHelpers))
                (actActISDA md)
                []
                Discount
                LogLinear

  usd3m <- I.iborIndex (I.UsdLibor (3, Months)) (Just fwdCurve)
  I.asInterestRateIndex usd3m >>= asIndex >>= (\i -> addFixing i (fromGregorian 2008 07 17) 0.0278625 False)

  floatSchedule <- schedule (Just $ fromGregorian 2005 10 21)
                                     (fromGregorian 2010 10 21)
                                     (3, Months)
                                     (nyseCal md)
                                     Unadjusted
                                     Unadjusted
                                     Backward
                                     True
                                     Nothing
                                     Nothing
  floater <- floatingRateBond settlementDays
                                   faceAmount
                                   floatSchedule
                                   usd3m
                                   (actual360dc md)
                                   ModifiedFollowing
                                   2
                                   [1.0]
                                   [0.001]
                                   []
                                   []
                                   True
                                   100.0
                                   (Just $ fromGregorian 2005 10 21)
                                   (0, Days) (nyseCal md) Unadjusted False ModifiedFollowing
  volval <- simpleQuote 0
  vol <- constantOptionletVolatility'
          settlementDays (targetCal md) ModifiedFollowing volval (actual365Fixeddc md) ShiftedLognormal 0.0
  cf <- cashFlows floater
  CF.blackIborCouponPricer vol CF.Black76 Nothing Nothing >>= CF.setCouponPricer cf

  return (fixedBond, zcBond, floater, pricing)

priceBonds :: MarketData -> PricingEngine -> (Bond, Bond, Bond) -> IO Result
priceBonds md pricing allBonds@(fixedBond, _, floater) = do
  let twoBonds = (fixedBond, floater)

  -- some cash flows smoke check
  cfs <- cashFlows fixedBond
  cfnpv <- CF.npv cfs (discountCurve md) True (Just $ 1 `may` 2012) (Just $ 3 `may` 2012)
  cfnpvbps <- CF.npvbps cfs (discountCurve md) True (1 `may` 2012) (3 `may` 2012)
  bbps <- bps fixedBond (discountCurve md) (3 `may` 2012)

  bNpv <-
    mapTriple (asInstrument >=>
      (\y -> setPricingEngine y pricing >> npv y))
    allBonds

  bCleanPrice <- mapTriple (\b -> cleanPrice b (discountCurve md) (settlDate md)) allBonds
  bYield <- mapTriple (\b -> yield b (actual360dc md) Compounded Annual 1e-8 100 (0.05, Clean)) allBonds
  bAccruedAmount <- mapTriple (`accruedAmount` settlDate md) allBonds
  bPreviousCoupon <- mapPair (`previousCouponRate` todaysDate md) twoBonds
  bNextCoupon <- mapPair (`nextCouponRate` todaysDate md) twoBonds

  let (_, _, floaterYield) = bYield
      (_, _, floaterCleanPrice) = bCleanPrice
  fCleanFromYield <- cleanPriceFromYield floater floaterYield (actual360dc md) Compounded Annual (settlDate md)
  fYieldFromClean <- yieldFromPrice floater (floaterCleanPrice, Clean) (actual360dc md) Compounded Annual (settlDate md) 1e-8 100

  let bDirtyPrice = zipTriple (+) bCleanPrice bAccruedAmount

  bNextCouponDate <- mapTriple (`nextCashFlowDate` todaysDate md) allBonds
    >>= maybe (fail "a bond has no next cash flow date") pure . sequenceTriple
  bTradable <- mapTriple (`isTradable` (10 `february` 2013)) allBonds

  return Result {
      npvR = bNpv
    , cleanPriceR = bCleanPrice
    , dirtyPriceR = bDirtyPrice
    , accruedAmountR = bAccruedAmount
    , previousCoupon = bPreviousCoupon
    , nextCoupon = bNextCoupon
    , yieldR = bYield
    , nextCouponDate = bNextCouponDate
    , cleanPriceFromYieldR = fCleanFromYield
    , yieldFromCleanPriceR = fYieldFromClean
    , tradable = bTradable
    , cfnpvR = cfnpv
    , cfnpvbpsR = cfnpvbps
    , bpsR = bbps
    }

run :: IO Result
run = do
  md <- buildMarketData
  (fixedBond, zcBond, floater, pricing) <- buildBonds md
  priceBonds md pricing (fixedBond, zcBond, floater)

zcQuotes :: [Double]
zcQuotes = [0.0096, 0.0145, 0.0194]

zcTenors :: [Int]
zcTenors = [3, 6, 12]

fixDays :: Word
fixDays = 3

settlementDays :: Word
settlementDays = 3

redemption :: Double
redemption = 100.0

faceAmount :: Double
faceAmount = 100.0

issueDates :: [Maybe Day]
issueDates = map Just [
  fromGregorian 2005 03 15,
  fromGregorian 2005 06 15,
  fromGregorian 2006 06 30,
  fromGregorian 2002 11 15,
  fromGregorian 1987 05 15]

maturities :: [Day]
maturities = [
  fromGregorian 2010 08 31,
  fromGregorian 2011 08 31,
  fromGregorian 2013 08 31,
  fromGregorian 2018 08 15,
  fromGregorian 2038 05 15]

couponRates :: [Double]
couponRates = [0.02375, 0.04625, 0.03125, 0.04000, 0.04500]

marketQuotes :: [Double]
marketQuotes = [100.390625, 106.21875, 100.59375, 101.6875, 102.140625]

liborDepoQuotes :: [Double]
liborDepoQuotes = [0.043375, 0.031875, 0.0320375,
                      0.03385, 0.0338125, 0.0335125]

liborDepoTerms :: [(Int, TimeUnit)]
liborDepoTerms = [(1, Weeks), (1, Months), (3, Months),
                  (6, Months), (9, Months), (1, Years)]

liborSwapQuotes :: [Double]
liborSwapQuotes = [0.0295, 0.0323, 0.0359, 0.0412, 0.0433]

liborSwapTerms :: [Int]
liborSwapTerms = [2, 3, 5, 10, 15]

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
