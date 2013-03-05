module QuantLib.Example.Bond
  (
    Result(..)
  , run
  )
where

import Control.Applicative
import Control.Monad(join, (>=>))

import Data.List(zip4)
import Data.Time.Calendar(Day, fromGregorian)

import QuantLib.CashFlow.CouponPricer
import qualified QuantLib.CashFlow.Leg as Leg
import QuantLib.Compounding
import QuantLib.Index
import QuantLib.Index.Ibor
import QuantLib.Instrument
import QuantLib.Instrument.Bond
import QuantLib.Math.Interpolation
import QuantLib.PricingEngine
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.TermStructure.Trait
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield
import QuantLib.Time.BusinessDayConvention
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.DateGenerationRule
import QuantLib.Time.DayCounter
import QuantLib.Time.Frequency
import QuantLib.Time.Period
import QuantLib.Time.Schedule
import QuantLib.Time.Unit
import QuantLib.Types

data Result = Result
  { npvR :: (Double, Double, Double)
  , cleanPriceR :: (Double, Double, Double)
  , dirtyPriceR :: (Double, Double, Double)
  , accruedAmountR :: (Double, Double, Double)
  , previousCoupon :: (Double, Double)
  , nextCoupon :: (Double, Double)
  , yieldR :: (Double, Double, Double)
  , cleanPriceFromYield :: Double
  , yieldFromCleanPrice :: Double
  , nextCouponDate :: (Day, Day, Day)
  , tradable :: (Bool, Bool, Bool)
  , cfnpvR :: Double
  , cfnpvbpsR :: (Double, Double)
  , bpsR :: Double
  }

listToTuple :: [a] -> (a, a)
listToTuple [x, y] = (x, y)
listToTuple _ = error "Invalid list"

listToTriple :: [a] -> (a, a, a)
listToTriple [x, y, z] = (x, y, z)
listToTriple _ = error "Invalid list"

(<-*>) :: (Applicative m, Monad m) => m (a -> m b) -> m a -> m b
(<-*>) f x = join $ f <*> x

infixl 4 <-*>

run :: IO Result
run = do
  actual365Fixeddc <- actual365Fixed
  actActBond <- actualActualBond
  actActISDA <- actualActualISDA
  actual360dc <- actual360
  thirty360Europeandc <- thirty360European

  p1d <- period 1 Days
  p3m <- period 3 Months
  pq <- fromFrequency Quarterly
  p6m <- fromFrequency Semiannual

  targetCal <- target
  nyseCal <- unitedStatesNYSE
  usGovBondCal <- unitedStatesGovernmentBond

  settlDate <- adjust targetCal (18 `september` 2008) Following
  todaysDate <- advance targetCal
                        settlDate
                        (-(fromIntegral fixingDays))
                        Days
                        Following
                        False
  setEvaluationDate (Just todaysDate)
  discDepoHelpers <- mapM
    (\(q, p) -> do
      tenor <- period p Months
      rate <- simpleQuote q >>= asQuote
      depositRateHelper
        rate
        tenor
        fixingDays
        targetCal
        ModifiedFollowing
        True
        actual365Fixeddc)
    $ zip zcQuotes zcTenors
  quotes <- mapM (simpleQuote >=> asQuote) marketQuotes
  discBondHelpers <- mapM
    (\(q, c, i, m) -> do
      s <- schedule i m p6m usGovBondCal Unadjusted
             Unadjusted Backward False Nothing Nothing
      fixedRateBondHelper q settlementDays 100.0 s [c]
            actActBond Unadjusted redemption i >>= asRateHelper)
    $ zip4 quotes couponRates issueDates maturities
  ts <- piecewiseYieldCurve
          settlDate
          (discDepoHelpers ++ discBondHelpers)
          actActISDA
          []
          tolerance
          Discount
          LogLinear
          --(Cubic $ NaturalSpline True)
          --(LogCubic $ Parabolic False)
          --(LogCubic Kruger)
          --(Cubic FritschButland)
          --Abcd

  --df <- discount ts (fromGregorian 2011 08 03) True
  pricing <- discountingBondEngine ts Nothing
  -- Fixed 4.5% US Treasury Note
  fixedSchedule <- schedule (Just (15 `may` 2007))
                                     (15 `may` 2017)
                                     p6m
                                     usGovBondCal
                                     Unadjusted
                                     Unadjusted
                                     Backward
                                     False
                                     Nothing
                                     Nothing
  fixedBond <- fixedRateBond settlementDays
                                  faceAmount
                                  fixedSchedule
                                  [0.045]
                                  actActBond
                                  ModifiedFollowing
                                  100.0
                                  (Just $ 15 `may` 2007)
                                  usGovBondCal >>= asBond
  zcBond <- zeroCouponBond settlementDays
                               usGovBondCal
                               faceAmount
                               (15 `august` 2013)
                               Following
                               116.92
                               (Just $ 15 `august` 2003)
  depoLiborHelpers <-
    mapM (\(q, (n, u)) ->
      do
        quote <- simpleQuote q >>= asQuote
        p <- period n u
        depositRateHelper quote p fixingDays targetCal
                                       ModifiedFollowing
                                       True actual360dc) $
          zip liborDepoQuotes liborDepoTerms

  eur6M <- euribor6M Nothing
  spread <- simpleQuote 0 >>= asQuote

  swapLiborHelpers <-
    mapM (\(q, n) ->
      do
        quote <- simpleQuote q >>= asQuote
        p <- period n Years
        swapRateHelper' quote p targetCal Annual Unadjusted
                              thirty360Europeandc eur6M spread (Just p1d) Nothing >>= asRateHelper) $
          zip liborSwapQuotes liborSwapTerms

  fwdCurve <- piecewiseYieldCurve
                settlDate
                (depoLiborHelpers ++ swapLiborHelpers)
                actActISDA
                []
                tolerance
                Discount
                LogLinear

  usd3m <- usdLibor p3m (Just fwdCurve)
  asInterestRateIndex usd3m >>= asIndex >>= (\i -> addFixing i (fromGregorian 2008 07 17) 0.0278625 False)

  floatSchedule <- schedule (Just $ fromGregorian 2005 10 21)
                                     (fromGregorian 2010 10 21)
                                     pq
                                     nyseCal
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
                                   actual360dc
                                   ModifiedFollowing
                                   2
                                   [1.0]
                                   [0.001]
                                   []
                                   []
                                   True
                                   100.0
                                   (Just $ fromGregorian 2005 10 21)
  volval <- simpleQuote 0 >>= asQuote
  vol <- constantOptionletVolatility'
          settlementDays targetCal ModifiedFollowing volval actual365Fixeddc
  setCouponPricer <$> cashflows floater <-*> blackIborCouponPricer vol

  let allBonds = [fixedBond, zcBond, floater]
      twoBonds = [fixedBond, floater]

  -- some cash flows smoke check
  cfs <- cashflows fixedBond
  cfnpv <- Leg.npv cfs ts True (Just $ 1 `may` 2012) (Just $ 3 `may` 2012)
  cfnpvbps <- Leg.npvbps cfs ts True (1 `may` 2012) (3 `may` 2012)
  bbps <- bps fixedBond ts (Just $ 3 `may` 2012)

  [fixnpv, znpv, fnpv] <-
    mapM (asInstrument >=>
      (\y -> setPricingEngine y pricing >> npv y))
    allBonds

  bCleanPrice <- mapM cleanPrice allBonds
  bDirtyPrice <- mapM dirtyPrice allBonds
  bAccruedAmount <- mapM (`accruedAmount` Nothing) allBonds
  bPreviousCoupon <- mapM (`previousCouponRate` Nothing) twoBonds
  bNextCoupon <- mapM (`nextCouponRate` Nothing) twoBonds

  bYield <- mapM
    (\b -> yield b actual360dc Compounded Annual 1e-8 100)
    allBonds

  fCleanFromYield <- cleanPrice' floater (bYield!!2) actual360dc Compounded Annual (Just settlDate)
  fYieldFromClean <- yield' floater (bCleanPrice!!2) actual360dc Compounded Annual (Just settlDate) 1e-8 100

  bNextCouponDate <- mapM (`nextCashFlowDate` Nothing) allBonds

  bTradable <- mapM (`isTradable` (Just $ 10 `february` 2013)) allBonds

  return Result {
      npvR = (fixnpv, znpv, fnpv)
    , cleanPriceR = listToTriple bCleanPrice
    , dirtyPriceR = listToTriple bDirtyPrice
    , accruedAmountR = listToTriple bAccruedAmount
    , previousCoupon = listToTuple bPreviousCoupon
    , nextCoupon = listToTuple bNextCoupon
    , yieldR = listToTriple bYield
    , nextCouponDate = listToTriple bNextCouponDate
    , cleanPriceFromYield = fCleanFromYield
    , yieldFromCleanPrice = fYieldFromClean
    , tradable = listToTriple bTradable
    , cfnpvR = cfnpv
    , cfnpvbpsR = cfnpvbps
    , bpsR = bbps
    }

 where zcQuotes = [0.0096, 0.0145, 0.0194]
       zcTenors = [3, 6, 12]
       fixingDays = 3
       settlementDays = 3
       redemption = 100.0
       faceAmount = 100.0
       issueDates = map Just [
         fromGregorian 2005 03 15,
         fromGregorian 2005 06 15,
         fromGregorian 2006 06 30,
         fromGregorian 2002 11 15,
         fromGregorian 1987 05 15]
       maturities = [
         fromGregorian 2010 08 31,
         fromGregorian 2011 08 31,
         fromGregorian 2013 08 31,
         fromGregorian 2018 08 15,
         fromGregorian 2038 05 15]
       couponRates = [0.02375, 0.04625, 0.03125, 0.04000, 0.04500]
       marketQuotes = [100.390625, 106.21875, 100.59375, 101.6875, 102.140625]
       tolerance = 1.0e-15
       liborDepoQuotes = [0.043375, 0.031875, 0.0320375,
                             0.03385, 0.0338125, 0.0335125]
       liborDepoTerms = [(1, Weeks), (1, Months), (3, Months),
                         (6, Months), (9, Months), (1, Years)]
       liborSwapQuotes = [0.0295, 0.0323, 0.0359, 0.0412, 0.0433]
       liborSwapTerms = [2, 3, 5, 10, 15]

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
