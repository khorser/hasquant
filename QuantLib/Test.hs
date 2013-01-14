{-# LANGUAGE ScopedTypeVariables #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
module Main(main)

where

import Control.Exception(catch)
import Data.List(zip4)
import Data.Word(Word)
import Data.Time.Calendar(Day, fromGregorian, addDays)
import Data.Time.Clock(getCurrentTime)
import Data.Time.LocalTime(localDay, getTimeZone, utcToLocalTime)
import Prelude hiding(catch)
import System.Mem(performGC)

import Test.HUnit(runTestTT, test, assertEqual, (~:), (~?=), (~=?),
  Test(TestList), assertBool, assertFailure)
import Test.QuickCheck(Arbitrary, elements, arbitrary, Property,
  quickCheck, quickCheckWith, (==>), stdArgs, Args(..), arbitraryBoundedEnum)
import Test.QuickCheck.Monadic as QC(assert, monadicIO, pick, pre, run)

--import qualified QuantLib.Internal as Internal(toQlEnum)
import qualified QuantLib.CashFlow.Leg as Leg
import qualified QuantLib.CashFlow.CouponPricer as CouponPricer
import qualified QuantLib.Compounding as Compounding
import qualified QuantLib.Currency as Currency
import qualified QuantLib.Error as Error
import qualified QuantLib.Index as Index
import qualified QuantLib.Index.Ibor as Ibor
import qualified QuantLib.Instrument as Instrument
import qualified QuantLib.Instrument.Bond as Bond
import qualified QuantLib.InterestRate as InterestRate
import qualified QuantLib.Math.Interpolation as Interpolation
import qualified QuantLib.PricingEngine as Pricing
import qualified QuantLib.Quote as Quote
import qualified QuantLib.Settings as Settings
import qualified QuantLib.TermStructure.Yield as Yield
import qualified QuantLib.TermStructure.Volatility as Vol
import qualified QuantLib.Time.BusinessDayConvention as BusinessDayConvention
import qualified QuantLib.Time.Calendar as Calendar
import qualified QuantLib.Time.Date as Date
import qualified QuantLib.Time.DateGenerationRule as DateGenerationRule
import qualified QuantLib.Time.DayCounter as DayCounter
import qualified QuantLib.Time.Frequency as Frequency
import qualified QuantLib.Time.Period as Period
import qualified QuantLib.Time.Schedule as Schedule
import qualified QuantLib.Time.Unit as Unit
import qualified QuantLib.Utilities as Utilities

today :: IO Day
today =
  do now <- getCurrentTime
     tz <- getTimeZone now
     return $ localDay $ utcToLocalTime tz now

-- HUnit --
settings :: Test
settings = TestList
  [
    "default evaluation date"
      ~: do t1 <- Settings.evaluationDate
            t2 <- today
            assertEqual "default valuation date" t1 t2
  , "null evaluation date"
      ~: do Settings.setEvaluationDate $ Just (fromGregorian 2012 12 29)
            t0 <- Settings.evaluationDate
            assertEqual "new valuation date" t0 (fromGregorian 2012 12 29)
            Settings.setEvaluationDate Nothing
            t1 <- Settings.evaluationDate
            t2 <- today
            assertEqual "new valuation date" t1 t2
  , "enforce today's historic fixings 1"
      ~: do e1 <- Settings.enforceTodaysHistoricFixings
            assertEqual "default enforce today's historic fixings" e1 False
  , "enforce today's historic fixings 2"
      ~: do Settings.setEnforceTodaysHistoricFixings True
            e1 <- Settings.enforceTodaysHistoricFixings
            assertEqual "new enforce today's historic fixings" e1 True
  ]

date :: Test
date = test
  [
    "min date" ~: "min date" ~:
      Date.minDate ~?= fromGregorian 1901 01 01
  , "max date" ~: "max date" ~:
      Date.maxDate ~?= fromGregorian 2199 12 31
  , "leap years" ~: "leap year" ~:
      [False, True, False] ~=? map Date.isLeap
            [ fromGregorian 2100 10 10,
              fromGregorian 2012 1 1,
              fromGregorian 1981 5 5]
  ]

leg :: Test
leg = TestList
  [
    "start date of an empty leg"
      ~: catch
          (do l <- Leg.leg []
              print $ Leg.startDate l
              assertFailure "start date of empty leg didn't return an error")
          (assertBool "exception message not empty" . not . null . Error.message)
  , "single leg today"
      ~: do t <- today
            l <- Leg.leg [(100, t)]
            assertEqual "today's leg start date" t (Leg.startDate l)
  , "two legs unsorted"
      ~: do t <- today
            l <- Leg.leg [(100, t), (-1000, addDays (-10) t)]
            assertEqual "today's leg start date" (addDays (-10) t) (Leg.startDate l)
  , "three legs sorted"
      ~: do t <- today
            l <- Leg.leg [(100, t), (1000, addDays (-10) t), (-2000, addDays 10 t)]
            assertEqual "today's leg start date" (addDays (-10) t) (Leg.startDate l)
  ]

calendar :: Test
calendar = TestList
  [
    "GBP" ~: do c1 <- Calendar.londonStockExchange
                c2 <- Calendar.gbp
                assertEqual "GBP calendar name" (Utilities.name c1) (Utilities.name c2)
  , "adjust" ~: do c <- Calendar.russia 
                   a <- Calendar.adjust
                            c
                            (fromGregorian 2012 12 22)
                            BusinessDayConvention.Preceding
                   assertEqual "Russian Calendar adjust" (fromGregorian 2012 12 21) a
  , "advance" ~: do c <- Calendar.russia 
                    a <- Calendar.advance
                            c
                            (fromGregorian 2012 12 20)
                            1
                            Unit.Months
                            BusinessDayConvention.Preceding
                            False
                    assertEqual "Russian Calendar advance" (fromGregorian 2013 01 18) a
                              
  ]

currency :: Test
currency = TestList
  [
    "GBP" ~: do c <- Currency.gbp
                assertEqual "GBP currency name " "British pound sterling" (Utilities.name c)
  ]

dayCounter :: Test
dayCounter = TestList
  [
    "ACT/365" ~: do c1 <- DayCounter.a365F
                    c2 <- DayCounter.actual365Fixed
                    assertEqual "ACT/365 names" (Utilities.name c1) (Utilities.name c2)
  ]

bond :: Test
bond = TestList
  [
    "bond statics"
      ~: do c <- Calendar.gbp
            l <- Leg.leg [(1000, fromGregorian 2013 1 1)] 
            b <- Bond.bond' 2 c 1000 m i l
            assertEqual "matirity date" m (Bond.maturityDate b)
            assertEqual "issue date" i (Bond.issueDate b)
  , "special bond statics"
      ~: do c <- Calendar.gbp
            l <- Leg.leg [] 
            b <- Bond.bond 3 c Nothing l
            assertEqual "issue date" Nothing (Bond.issueDate b)
  , "fixed rate bond with schedule"
      ~: do c <- Calendar.russia
            tenor <- Period.period 1 Unit.Months
            s <- Schedule.schedule
              (Just (fromGregorian 2012 12 20))
              (fromGregorian 2013 12 21)
              tenor
              c
              BusinessDayConvention.Following
              BusinessDayConvention.Unadjusted
              DateGenerationRule.Forward
              False
              (Just (fromGregorian 2012 12 21))
              (Just (fromGregorian 2013 12 21))
            cnt <- DayCounter.actual365Fixed
            b <- Bond.fixedRateBond
                  1
                  100
                  s
                  [3]
                  cnt
                  BusinessDayConvention.Following
                  100
                  (Just $ fromGregorian 2012 10 11)
                  c
            assertEqual "issue date" (Just $ fromGregorian 2012 10 11) (Bond.issueDate b)
            assertEqual "maturity date" (Just $ fromGregorian 2013 12 21) (Bond.maturityDate b)
            assertEqual "fixed rate bond frequency" Frequency.Monthly (Bond.frequency b)
  , "fixed rate bond with calendars"
      ~: do c <- Calendar.russia
            tenor <- Period.period 1 Unit.Months
            cnt <- DayCounter.actual365Fixed
            b <- Bond.fixedRateBond'
                  1
                  c
                  100
                  (fromGregorian 2012 12 20)
                  (fromGregorian 2013 12 21)
                  tenor
                  [0.12]
                  cnt
                  BusinessDayConvention.Following
                  BusinessDayConvention.Unadjusted
                  100
                  (Just $ fromGregorian 2012 10 01)
                  Nothing
                  DateGenerationRule.Forward
                  False
                  c
            assertEqual "issue date" (Just $ fromGregorian 2012 10 01) (Bond.issueDate b)
            assertEqual "maturity date" (Just $ fromGregorian 2013 12 21) (Bond.maturityDate b)
            assertEqual "fixed rate bond frequency" Frequency.Monthly (Bond.frequency b)
  , "fixed rate bond''"
      ~: do dc <- DayCounter.actual365Fixed
            r1 <- InterestRate.interestRate 0.12 dc Compounding.Simple Frequency.Annual
            r2 <- InterestRate.interestRate 0.125 dc Compounding.Simple Frequency.Monthly
            cal <- Calendar.russia
            tenor <- Period.period 6 Unit.Months
            s <- Schedule.schedule
              (Just (fromGregorian 2012 12 20))
              (fromGregorian 2013 12 21)
              tenor
              cal
              BusinessDayConvention.Following
              BusinessDayConvention.Unadjusted
              DateGenerationRule.Forward
              False
              (Just (fromGregorian 2012 12 21))
              (Just (fromGregorian 2013 12 21))
            b <- Bond.fixedRateBond''
                    3
                    100
                    s
                    [r1, r2]
                    BusinessDayConvention.Preceding
                    100
                    (Just (fromGregorian 2012 12 21))
                    cal
            assertEqual "issue date" (Just $ fromGregorian 2012 12 21) (Bond.issueDate b)
            assertEqual "maturity date" (Just $ fromGregorian 2013 12 21) (Bond.maturityDate b)
            assertEqual "fixed rate bond frequency" Frequency.Semiannual (Bond.frequency b)
  ]
  where i = Just (fromGregorian 2012 1 1)
        m = Just (fromGregorian 2013 1 1)

frequency :: Test
frequency = TestList
  [
    "1M period to frequency"
      ~: do p <- Period.period 1 Unit.Months
            assertEqual "Monthly frequency" Frequency.Monthly (Period.toFrequency p)
  ]

schedule :: Test
schedule = TestList
  [
    "schedule truncation"
      ~: do tenor <- Period.period 1 Unit.Months
            cal <- Calendar.russia
            s <- Schedule.schedule
              (Just (fromGregorian 2012 12 20))
              (fromGregorian 2013 12 21)
              tenor
              cal
              BusinessDayConvention.Following
              BusinessDayConvention.Unadjusted
              DateGenerationRule.Forward
              False
              (Just (fromGregorian 2012 12 21))
              (Just (fromGregorian 2013 12 21))
            truncated <- Schedule.until s (fromGregorian 2013 4 15)
            assertEqual "Schedule dates" [fromGregorian 2012 12 20,
                                          fromGregorian 2012 12 21,
                                          fromGregorian 2013 01 21,
                                          fromGregorian 2013 02 21,
                                          fromGregorian 2013 03 21,
                                          fromGregorian 2013 04 15]
                                         (Schedule.dates truncated)
  ]

bondval :: Test
bondval = TestList
  [
    "bond valuation (QuantLib Bond example)"
      ~: do zcBondsDayCounter <- DayCounter.actual365Fixed
            cal <- Calendar.target
            settlementDate <- Calendar.adjust cal
                                              (fromGregorian 2008 09 18)
                                              BusinessDayConvention.Following
            todaysDate <- Calendar.advance  cal
                                            settlementDate
                                            (-(fromIntegral fixingDays))
                                            Unit.Days
                                            BusinessDayConvention.Following
                                            False
            Settings.setEvaluationDate (Just todaysDate)
            gcal <- Calendar.unitedStatesGovernmentBond
            actact <- DayCounter.actualActualBond
            depoBondHelpers <- mapM
              (\(q, p) -> do tenor <- Period.period p Unit.Months
                             rate <- Quote.simpleQuote q
                             Yield.depositRateHelper
                               rate
                               tenor
                               fixingDays
                               cal
                               BusinessDayConvention.ModifiedFollowing
                               True
                               zcBondsDayCounter)
              $ zip zcQuotes zcTenors
            quotes <- mapM Quote.simpleQuote marketQuotes
            p6m <- Period.fromFrequency Frequency.Semiannual
            bondBondHelpers <- mapM
              (\(q, c, i, m) -> do s <- Schedule.schedule
                                          i
                                          m
                                          p6m
                                          gcal
                                          BusinessDayConvention.Unadjusted
                                          BusinessDayConvention.Unadjusted
                                          DateGenerationRule.Backward
                                          False
                                          Nothing
                                          Nothing
                                   Yield.fixedRateBondHelper
                                     q
                                     settlementDays
                                     100.0
                                     s
                                     [c]
                                     actact
                                     BusinessDayConvention.Unadjusted
                                     redemption
                                     i)
              $ zip4 quotes couponRates issueDates maturities
            tsdc <- DayCounter.actualActualISDA
            ts <- Yield.piecewiseYieldCurve
                    settlementDate
                    (depoBondHelpers ++ bondBondHelpers)
                    tsdc
                    []
                    tolerance
                    Yield.Discount
                    Interpolation.LogLinear
                    --(Interpolation.Cubic $ Interpolation.NaturalSpline True)
                    --(Interpolation.LogCubic $ Interpolation.Parabolic False)
                    --(Interpolation.LogCubic Interpolation.Kruger)
                    --(Interpolation.Cubic Interpolation.FritschButland)
                    --Interpolation.Abcd
            --df <- Yield.discount ts (fromGregorian 2011 08 03) True
            pricing <- Pricing.discountingBondEngine ts
            -- Fixed 4.5% US Treasury Note
            fixedSchedule <- Schedule.schedule (Just (fromGregorian 2007 05 15))
                                               (fromGregorian 2017 05 15)
                                               p6m
                                               gcal
                                               BusinessDayConvention.Unadjusted
                                               BusinessDayConvention.Unadjusted
                                               DateGenerationRule.Backward
                                               False
                                               Nothing
                                               Nothing
            nocal <- Calendar.noCalendar
            fixedBond <- Bond.fixedRateBond settlementDays
                                            faceAmount
                                            fixedSchedule
                                            [0.045]
                                            actact
                                            BusinessDayConvention.ModifiedFollowing
                                            100.0
                                            (Just (fromGregorian 2007 05 15))
                                            nocal
            Instrument.setPricingEngine fixedBond pricing
            npv <- Instrument.npv fixedBond
            assertBool "Fixed rate bond NPV" $ abs(npv-107.67) < 0.01
            zcBond <- Bond.zeroCouponBond settlementDays
                                         gcal
                                         faceAmount
                                         (fromGregorian 2013 08 15)
                                         BusinessDayConvention.Following
                                         116.92
                                         (Just $ fromGregorian 2003 08 15)
            Instrument.setPricingEngine zcBond pricing
            znpv <- Instrument.npv zcBond
            assertBool "Zero coupon bond NPV" $ abs(znpv-100.92) < 0.01

            act360 <- DayCounter.actual360
            thirty360European <- DayCounter.thirty360European
            depoLiborHelpers <-
              mapM (\(q, (n, u)) ->
                do quote <- Quote.simpleQuote q
                   p <- Period.period n u
                   Yield.depositRateHelper quote p fixingDays cal
                                                  BusinessDayConvention.ModifiedFollowing
                                                  True act360
                   )
                   $ zip liborDepoQuotes liborDepoTerms

            eur6M <- Ibor.euribor p6m Nothing
            v <- Quote.simpleQuote 0.0
            q0 <- Quote.simpleQuote 0 -- is this the same as empty quote?

            swapLiborHelpers <-
              mapM (\(q, n) ->
                do quote <- Quote.simpleQuote q
                   p <- Period.period n Unit.Years
                   p1d <- Period.period 1 Unit.Days
                   Yield.swapRateHelper' quote p cal Frequency.Annual BusinessDayConvention.Unadjusted
                                         thirty360European eur6M q0 p1d Nothing)
                    $ zip liborSwapQuotes liborSwapTerms

            fwdCurve <- Yield.piecewiseYieldCurve
                          settlementDate
                          (depoLiborHelpers ++ swapLiborHelpers)
                          tsdc
                          []
                          tolerance
                          Yield.Discount
                          Interpolation.LogLinear

            p3m <- Period.period 3 Unit.Months
            usd3m <- Ibor.usdLibor p3m (Just fwdCurve)
            Index.addFixing usd3m (fromGregorian 2008 07 17) 0.0278625 False

            pq <- Period.fromFrequency Frequency.Quarterly
            nyse <- Calendar.unitedStatesNYSE
            floatSchedule <- Schedule.schedule (Just $ fromGregorian 2005 10 21)
                                               (fromGregorian 2010 10 21)
                                               pq
                                               nyse
                                               BusinessDayConvention.Unadjusted
                                               BusinessDayConvention.Unadjusted
                                               DateGenerationRule.Backward
                                               True
                                               Nothing
                                               Nothing
            floater <- Bond.floatingRateBond settlementDays
                                             faceAmount
                                             floatSchedule
                                             usd3m
                                             act360
                                             BusinessDayConvention.ModifiedFollowing
                                             2
                                             [1.0]
                                             [0.001]
                                             []
                                             []
                                             True
                                             100.0
                                             (Just $ fromGregorian 2005 10 21)
            Instrument.setPricingEngine floater pricing
            act365 <- DayCounter.actual365Fixed
            vol <- Vol.constantOptionletVol settlementDays
                                            cal
                                            BusinessDayConvention.ModifiedFollowing
                                            v
                                            act365
            couponPricer <- CouponPricer.blackIborCouponPricer vol
            Bond.setCouponPricer floater couponPricer

            fnpv <- Instrument.npv floater
            assertBool "Floating rate bond NPV" $ abs(fnpv-102.36) < 0.01
 
            putStrLn $ "\nData from QL Bond Example: " ++ show [100.9221782070444 :: Double, 107.66828913260427, 102.35931459949143]
            putStrLn $ "Ours: " ++ show [znpv, npv, fnpv]
  ]
  where zcQuotes = [0.0096, 0.0145, 0.0194]
        zcTenors = [3, 6, 12]
        fixingDays = 3 :: Word
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
        liborDepoTerms = [(1, Unit.Weeks), (1, Unit.Months), (3, Unit.Months),
                          (6, Unit.Months), (9, Unit.Months), (1, Unit.Years)]
        liborSwapQuotes = [0.0295, 0.0323, 0.0359, 0.0412, 0.0433]
        liborSwapTerms = [2, 3, 5, 10, 15]


-- QuickCheck --
instance Arbitrary Day where
  arbitrary = do
    y <- elements [1900 .. 2300]
    m <- elements [1 .. 12]
    d <- elements [1 .. 31]
    return (fromGregorian y m d)

setAndGetEvaluationDate :: Day -> IO Day
setAndGetEvaluationDate d =
  do Settings.setEvaluationDate (Just d)
     Settings.evaluationDate

setAndGetEvaluationDateWithExceptions :: Day -> IO Day
setAndGetEvaluationDateWithExceptions d =
  do catch (Settings.setEvaluationDate (Just d))
           (\(_ :: Error.Error) -> return ())
     Settings.evaluationDate

prop_validEvaluationDate :: Property
prop_validEvaluationDate = monadicIO
  $ do d1 <- pick arbitrary
       pre (Date.isValid d1)
       d2 <- run $ setAndGetEvaluationDate d1
       assert $ d1 == d2

prop_invalidEvaluationDate :: Day -> Property
prop_invalidEvaluationDate d =
  not (Date.isValid d)
    ==> monadicIO
          $ do t <- run today
               _ <- run $ Settings.setEvaluationDate (Just t)
               d2 <- run $ setAndGetEvaluationDateWithExceptions d
               assert $ t == d2

prop_singleLegStartDate :: (Double, Day) -> Property
prop_singleLegStartDate flow@(_, d) =
  Date.isValid d
    ==> monadicIO
          $ do l <- run $ Leg.leg [flow]
               assert $ d == Leg.startDate l

prop_legStartDate :: [(Double, Day)] -> Property
prop_legStartDate flows =
  not (null flows) && all Date.isValid (map snd flows)
    ==> monadicIO
          $ do l <- run $ Leg.leg flows
               assert $ minimum (map snd flows) == Leg.startDate l

prop_quoteValue :: Double -> Property
prop_quoteValue val =
  val > 0
    ==> monadicIO
          $ do q <- run $ Quote.simpleQuote val
               assert $ Quote.value q == val

prop_scheduleDates :: [Day] -> Property
prop_scheduleDates dates =
  all Date.isValid dates
    ==> monadicIO
      $ do c <- run Calendar.russia
           s <- run $ Schedule.schedule' dates c BusinessDayConvention.Unadjusted
           assert $ dates == Schedule.dates s

instance Arbitrary Frequency.Frequency where
  arbitrary = arbitraryBoundedEnum

prop_frequencyFromPeriodFromFrequency :: Frequency.Frequency -> Property
prop_frequencyFromPeriodFromFrequency freq =
  freq /= Frequency.OtherFrequency
    ==> monadicIO
      $ do p <- run $ Period.fromFrequency freq
           assert $ Period.toFrequency p == freq

-- Main --
main :: IO ()
main = do putStrLn $ "QuantLib version " ++ Utilities.version
            ++ ", Boost " ++ Utilities.boostVersion
          _ <- runTestTT $ test
            [
              settings
              , date
              , leg
              , currency
              , calendar
              , dayCounter
              , bond
              , frequency
              , schedule
              , bondval
            ]
          -- if we don't do GC we have a chance of getting 
          -- "could not notify one or more observers: year 2200 out of bounds"
          -- from one of the outstanding rate helpers
          -- when QuickCheck sets evaluation date to some border value like 27Nov2199
          performGC
          putStrLn "-- Done with HUnit --"
          quickCheckWith stdArgs{maxSuccess = 500} prop_validEvaluationDate
          quickCheck prop_invalidEvaluationDate
          quickCheck prop_singleLegStartDate
          quickCheckWith stdArgs{maxDiscardRatio = 20} prop_legStartDate
          quickCheckWith stdArgs{maxDiscardRatio = 20} prop_scheduleDates
          quickCheck prop_frequencyFromPeriodFromFrequency
          quickCheckWith stdArgs{maxSuccess = 10} prop_quoteValue
          return ()
