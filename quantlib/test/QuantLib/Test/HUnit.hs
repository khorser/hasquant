{-# OPTIONS_GHC -F -pgmF htfpp #-}
{-# LANGUAGE CPP #-}
module QuantLib.Test.HUnit (htf_thisModulesTests)
where

import Test.Framework
import Test.HUnit.Lang

import Control.Exception(catch)
#if __GLASGOW_HASKELL__ < 706
import Prelude hiding(catch)
#endif
import Data.Time.Calendar(fromGregorian, addDays)
import Control.Arrow((&&&))

import qualified QuantLib.CashFlow.Leg as Leg
import qualified QuantLib.Compounding as Compounding
import qualified QuantLib.Currency as Currency
import qualified QuantLib.Error as Error
import qualified QuantLib.Instrument.Bond as Bond
import qualified QuantLib.InterestRate as InterestRate
import qualified QuantLib.Settings as Settings
import qualified QuantLib.Time.BusinessDayConvention as BusinessDayConvention
import qualified QuantLib.Time.Calendar as Calendar
import QuantLib.Time.Date
import qualified QuantLib.Time.DateGenerationRule as DateGenerationRule
import qualified QuantLib.Time.DayCounter as DayCounter
import qualified QuantLib.Time.Frequency as Frequency
import qualified QuantLib.Time.Period as Period
import qualified QuantLib.Time.Schedule as Schedule
import qualified QuantLib.Time.Unit as Unit
import QuantLib.Utilities

import qualified QuantLib.Example.Bond as BondExample
import qualified QuantLib.Example.Repo as RepoExample
import qualified QuantLib.Example.FRA as FRAExample
import qualified QuantLib.Example.Swap as SwapExample

{-# ANN module "HLint: ignore Use camelCase" #-}

assertListsAreClose :: (a -> Double) -> [a] -> [Double] -> Double -> Assertion
assertListsAreClose f x1 x2 e = assertBool $ all (\(x, y) -> abs(f x - y) < e) (zip x1 x2)

assertClose :: Double -> Double -> Double -> Assertion
assertClose x1 x2 e = assertBool $ abs(x1 - x2) < e

assertRecordMemberClose :: (a -> Double) -> a -> Double -> Double -> Assertion
assertRecordMemberClose f x1 x2 e = assertBool $ abs(f x1 - x2) < e

test_bondEval :: IO ()
test_bondEval = do
  r <- Settings.keepingSettings' BondExample.run
  let (fixnpv, znpv, fnpv) = BondExample.npvR r
      (fixy, zy, fy) = BondExample.yieldR r
      (fixclean, zclean, fclean) = BondExample.cleanPriceR r
      (fixdirty, zdirty, fdirty) = BondExample.dirtyPriceR r
      (fixaccrual, zaccrual, faccrual) = BondExample.accruedAmountR r
      (fixprev, fprev) = BondExample.previousCoupon r
      (fixnext, fnext) = BondExample.nextCoupon r
      (fixnextD, znextD, fnextD) = BondExample.nextCouponDate r
      cleanFromYield = BondExample.cleanPriceFromYield r
      yieldFromClean = BondExample.yieldFromCleanPrice r
      tradable = BondExample.tradable r

  subAssert $ assertClose fixnpv 107.6682891 1e-7
  subAssert $ assertClose znpv 100.9221782 1e-7
  subAssert $ assertClose fnpv 102.3593146 1e-7
  subAssert $ assertClose fixy 0.0364756 1e-7
  subAssert $ assertClose zy 0.0300006 1e-7
  subAssert $ assertClose fy 0.0220096 1e-7

  subAssert $ assertClose fixclean 106.1275283 1e-7
  subAssert $ assertClose zclean 100.9221782 1e-7
  subAssert $ assertClose fclean 101.7972017 1e-7
  subAssert $ assertClose fixdirty 107.6682891 1e-7
  subAssert $ assertClose zdirty 100.9221782 1e-7
  subAssert $ assertClose fdirty 102.3593146 1e-7
  subAssert $ assertClose fixaccrual 1.5407609 1e-7
  subAssert $ assertClose zaccrual 0.0 1e-7
  subAssert $ assertClose faccrual 0.5621129 1e-7
  subAssert $ assertClose fixprev 0.045 1e-7
  subAssert $ assertClose fprev 0.0288625 1e-7
  subAssert $ assertClose fixnext 0.045 1e-7
  subAssert $ assertClose fnext 0.0342984 1e-7

  assertEqual fixnextD (fromGregorian 2008 11 17)
  assertEqual znextD (fromGregorian 2013 08 15)
  assertEqual fnextD (fromGregorian 2008 10 21)
  subAssert $ assertClose cleanFromYield 101.79720 1e-5 -- because of difference in QL versions?
  subAssert $ assertClose yieldFromClean 0.0220096 1e-7

  assertEqual tradable (True, True, False)

test_repoEval :: IO ()
test_repoEval = do
  r <- Settings.keepingSettings' RepoExample.run

  subAssert $ assertRecordMemberClose RepoExample.cleanPriceR r 89.9769362 1e-7
  subAssert $ assertRecordMemberClose RepoExample.dirtyPriceR r 93.2880473 1e-7
  subAssert $ assertRecordMemberClose RepoExample.accruedAmountSettlement r 3.3111111 1e-7
  subAssert $ assertRecordMemberClose RepoExample.accruedAmountDelivery r 3.3333333 1e-7
  subAssert $ assertRecordMemberClose RepoExample.spotIncomeR r 3.9834025 1e-7
  subAssert $ assertRecordMemberClose RepoExample.fwdIncomeR r 4.0846473 1e-7
  subAssert $ assertRecordMemberClose RepoExample.npvR r (-0.00002806598) 1e-11
  subAssert $ assertRecordMemberClose RepoExample.cleanForwardPriceR r 88.2411379 1e-7
  subAssert $ assertRecordMemberClose RepoExample.forwardPriceR r 91.5744712 1e-7
  subAssert $ assertRecordMemberClose RepoExample.impliedYieldR r 0.050000633 1e-9
  subAssert $ assertRecordMemberClose RepoExample.zeroRateR r 0.05 1e-7

test_fraEval :: IO ()
test_fraEval = do
  (FRAExample.Result it1 it2) <- Settings.keepingSettings' FRAExample.run
  let
    fwdRates1   = [3.0e-2, 3.1e-2, 3.2e-2, 3.3e-2, 3.4e-2]
    spots1      = [99.73470, 99.49489, 99.23917, 98.41684, 97.60271]
    fwdValues1  = [100.76667, 100.79222, 100.83556, 100.84333, 100.85944]
    implYields1 = [3.00399e-2, 3.06805e-2, 3.11347e-2, 3.19277e-2, 3.26419e-2]
    zRates1     = [3.00399e-2, 3.06805e-2, 3.11347e-2, 3.19277e-2, 3.26419e-2]
  subAssert $ assertListsAreClose FRAExample.fwdRateR it1 fwdRates1 1.0e-5
  subAssert $ assertListsAreClose FRAExample.spotR it1 spots1 1.0e-5
  subAssert $ assertListsAreClose FRAExample.fwdValueR it1 fwdValues1 1.0e-5
  subAssert $ assertListsAreClose FRAExample.implYieldR it1 implYields1 1.0e-5
  subAssert $ assertListsAreClose FRAExample.zRateR it1 zRates1 1.0e-5
  subAssert $ assertListsAreClose FRAExample.npvR it1 (repeat 0.0) 1.0e-5
  let
    fwdRates2   = [4.0e-2, 4.1e-2, 4.2e-2, 4.3e-2, 4.4e-2]
    spots2      = [99.64687, 99.32793, 98.98812, 97.91433, 96.86156]
    fwdValues2  = [101.02222, 101.04778, 101.09667, 101.09889, 101.11222]
    implYields2 = [4.00710e-2, 4.07408e-2, 4.12277e-2, 4.21173e-2, 4.29299e-2]
    zRates2     = [4.00710e-2, 4.07408e-2, 4.12277e-2, 4.21174e-2, 4.29299e-2]
    npvs2       = [0.25208, 0.25121, 0.25567, 0.24751, 0.24215]
  subAssert $ assertListsAreClose FRAExample.fwdRateR it2 fwdRates2 1.0e-5
  subAssert $ assertListsAreClose FRAExample.spotR it2 spots2 1.0e-5
  subAssert $ assertListsAreClose FRAExample.fwdValueR it2 fwdValues2 1.0e-5
  subAssert $ assertListsAreClose FRAExample.implYieldR it2 implYields2 1.0e-5
  subAssert $ assertListsAreClose FRAExample.zRateR it2 zRates2 1.0e-5
  subAssert $ assertListsAreClose FRAExample.npvR it2 npvs2 1.0e-5

test_swapEval :: IO ()
test_swapEval = do
  (SwapExample.Result it1 it2) <- Settings.keepingSettings' SwapExample.run
  let
    spotNpvs1         = [19065.88091, 19076.13635, 19056.02274]
    spotFairSpreads1  = [-4.19298e-3, -4.19258e-3, -4.19271e-3]
    spotFairRates1    = [4.43e-2, 4.43e-2, 4.43e-2]
    fwdNpvs1          = [40049.45742, 40092.78967, 37238.92028]
    fwdFairSpreads1   = [-9.23115e-3, -9.23433e-3, -8.58372e-3]
    fwdFairRates1     = [4.94794e-2, 4.94846e-2, 4.88132e-2]
    (spots1, fwds1)   = unzip $ map (SwapExample.spotSwap &&& SwapExample.forwardSwap) it1
  subAssert $ assertListsAreClose SwapExample.spotNpvR spots1 spotNpvs1 1.0e-5
  subAssert $ assertListsAreClose SwapExample.spotFairSpreadR spots1 spotFairSpreads1 1.0e-5
  subAssert $ assertListsAreClose SwapExample.spotFairRateR spots1 spotFairRates1 1.0e-5
  subAssert $ assertListsAreClose SwapExample.spotNpvR fwds1 fwdNpvs1 1.0e-5
  subAssert $ assertListsAreClose SwapExample.spotFairSpreadR fwds1 fwdFairSpreads1 1.0e-5
  subAssert $ assertListsAreClose SwapExample.spotFairRateR fwds1 fwdFairRates1 1.0e-5
  let
    spotNpvs2         = [26539.06205, 26553.33709, 26525.34]
    spotFairSpreads2  = [-5.84826e-3, -5.84770e-3, -5.84788e-3]
    spotFairRates2    = [4.6e-2, 4.6e-2, 4.6e-2]
    fwdNpvs2          = [45736.03965, 45782.39565, 42922.59585]
    fwdFairSpreads2   = [-1.05779e-2, -1.05808e-2, -9.92761e-3]
    fwdFairRates2     = [5.08660e-2, 5.08713e-2, 5.01964e-2]
    (spots2, fwds2)   = unzip $ map (SwapExample.spotSwap &&& SwapExample.forwardSwap) it2
  subAssert $ assertListsAreClose SwapExample.spotNpvR spots2 spotNpvs2 1.0e-5
  subAssert $ assertListsAreClose SwapExample.spotFairSpreadR spots2 spotFairSpreads2 1.0e-5
  subAssert $ assertListsAreClose SwapExample.spotFairRateR spots2 spotFairRates2 1.0e-5
  subAssert $ assertListsAreClose SwapExample.spotNpvR fwds2 fwdNpvs2 1.0e-5
  subAssert $ assertListsAreClose SwapExample.spotFairSpreadR fwds2 fwdFairSpreads2 1.0e-5
  subAssert $ assertListsAreClose SwapExample.spotFairRateR fwds2 fwdFairRates2 1.0e-5

test_evalDate :: IO ()
test_evalDate = do
  t1 <- Settings.evaluationDate
  t2 <- today
  assertEqual t1 t2

test_nullEvalDate :: IO ()
test_nullEvalDate = do
  Settings.setEvaluationDate $ Just (december 29 2012)
  t0 <- Settings.evaluationDate
  assertEqual t0 (fromGregorian 2012 12 29)
  t2 <- today
  Settings.setEvaluationDate Nothing
  t1 <- Settings.evaluationDate
  assertEqual t1 t2

test_defaultTodaysHistFixings :: IO ()
test_defaultTodaysHistFixings = do
  e1 <- Settings.enforceTodaysHistoricFixings
  assertEqual e1 False

test_setTodaysHistFixings :: IO ()
test_setTodaysHistFixings = do
  Settings.setEnforceTodaysHistoricFixings True
  e1 <- Settings.enforceTodaysHistoricFixings
  assertEqual e1 True

test_minDate :: IO ()
test_minDate = assertEqual minDate (fromGregorian 1901 01 01)

test_maxDate :: IO ()
test_maxDate = assertEqual maxDate (fromGregorian 2199 12 31)

test_leapYears :: IO ()
test_leapYears = assertEqual
                  [False, True, False]
                  (map isLeap [fromGregorian 2100 10 10, fromGregorian 2012 1 1, fromGregorian 1981 5 5])

test_emptyLegStart :: IO ()
test_emptyLegStart = do
  l <- Leg.leg []
  catch (Leg.startDate l >> assertBool False)
        (assertBool . not . null . Error.message)

test_singleLegToday :: IO ()
test_singleLegToday = do
  t <- today
  l <- Leg.leg [(100, t)]
  sd <- Leg.startDate l
  assertEqual sd t

test_twoLegsUnsorted :: IO ()
test_twoLegsUnsorted = do
  t <- today
  l <- Leg.leg [(100, t), (-1000, addDays (-10) t)]
  sd <- Leg.startDate l
  assertEqual sd (addDays (-10) t)

test_threeLegsSorted :: IO ()
test_threeLegsSorted = do
  t <- today
  l <- Leg.leg [(100, t), (1000, addDays (-10) t), (-2000, addDays 10 t)]
  sd <- Leg.startDate l
  assertEqual sd (addDays (-10) t)

test_calAdjust :: IO ()
test_calAdjust = do
  c <- Calendar.russia
  a <- Calendar.adjust
          c
          (fromGregorian 2012 12 22)
          BusinessDayConvention.Preceding
  assertEqual (fromGregorian 2012 12 21) a

test_calAdvance :: IO ()
test_calAdvance = do
  c <- Calendar.russia
  a <- Calendar.advance
        c
        (fromGregorian 2012 12 20)
        1
        Unit.Months
        BusinessDayConvention.Preceding
        False
  assertEqual (fromGregorian 2013 01 18) a

test_currency :: IO ()
test_currency = do
  c <- Currency.gbp
  assertEqual "British pound sterling" (show c)

test_a365fCounter :: IO ()
test_a365fCounter = do
  c1 <- DayCounter.a365F
  c2 <- DayCounter.actual365Fixed
  assertEqual (show c1) (show c2)

test_bondStatics :: IO ()
test_bondStatics = do
  c <- Calendar.unitedKingdomSettlement
  l <- Leg.leg [(1000, fromGregorian 2013 1 1)]
  b <- Bond.bond' 2 c 1000 m i l
  assertEqual m (Bond.maturityDate b)
  where i = Just (fromGregorian 2012 1 1)
        m = Just (fromGregorian 2013 1 1)

test_fixedBondWithSchedule :: IO ()
test_fixedBondWithSchedule = do
  c <- Calendar.russia
  tenor <- Period.period 1 Unit.Months
  s <- Schedule.schedule
    (Just $ fromGregorian 2012 12 20)
    (fromGregorian 2013 12 21)
    tenor
    c
    BusinessDayConvention.Following
    BusinessDayConvention.Unadjusted
    DateGenerationRule.Forward
    False
    (Just $ fromGregorian 2012 12 21)
    (Just $ fromGregorian 2013 12 21)
  cnt <- DayCounter.actual365Fixed
  _ <- Bond.fixedRateBond
        1
        100
        s
        [3]
        cnt
        BusinessDayConvention.Following
        100
        (Just $ fromGregorian 2012 10 11)
        c
  assertEqual True True

test_fixedBondWithCalendars :: IO ()
test_fixedBondWithCalendars = do
  c <- Calendar.russia
  tenor <- Period.period 1 Unit.Months
  cnt <- DayCounter.actual365Fixed
  _ <- Bond.fixedRateBond'
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
  assertEqual True True

test_fixedBond :: IO ()
test_fixedBond = do
  dc <- DayCounter.actual365Fixed
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
  _ <- Bond.fixedRateBond''
          3
          100
          s
          [r1, r2]
          BusinessDayConvention.Preceding
          100
          (Just (fromGregorian 2012 12 21))
          cal
  assertEqual True True

test_frequency :: IO ()
test_frequency = do
  p <- Period.period 1 Unit.Months
  f <- Period.toFrequency p
  assertEqual Frequency.Monthly f

test_truncateSchedule :: IO ()
test_truncateSchedule = do
  tenor <- Period.period 1 Unit.Months
  cal <- Calendar.russia
  s <- Schedule.schedule
    (Just $ 20 `december` 2012)
    (21 `december` 2013)
    tenor
    cal
    BusinessDayConvention.Following
    BusinessDayConvention.Unadjusted
    DateGenerationRule.Forward
    False
    (Just $ 21 `december` 2012)
    (Just $ 21 `december` 2013)
  truncated <- Schedule.until s (15 `april` 2013)
  assertEqual [fromGregorian 2012 12 20,
               fromGregorian 2012 12 21,
               fromGregorian 2013 01 21,
               fromGregorian 2013 02 21,
               fromGregorian 2013 03 21,
               fromGregorian 2013 04 15]
              (Schedule.dates truncated)

test_enums :: IO ()
test_enums = mapM_
  (\(n, l) -> assertBoolVerbose ("Error checking " ++ n ++ " length") l)
  checkEnums

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
