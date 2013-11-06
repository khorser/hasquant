{-# OPTIONS_GHC -F -pgmF htfpp #-}
{-# LANGUAGE CPP #-}
module QuantLib.Test.HUnit (htf_thisModulesTests)
where

import Test.Framework
import Test.HUnit.Lang

#if __GLASGOW_HASKELL__ < 706
import Prelude hiding(catch)
#endif
import Data.Time.Calendar(fromGregorian, addDays)
import Control.Arrow((&&&))

import qualified QuantLib.CashFlow.Leg as Leg
import qualified QuantLib.Compounding as Compounding
import qualified QuantLib.Currency as Currency
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
import qualified QuantLib.Example.BermudanSwaption as BermudanSwaptionExample
import qualified QuantLib.Example.CallableBond as CallableBondExample
import qualified QuantLib.Example.CDS as CDSExample
import qualified QuantLib.Example.ConvertibleBond as ConvertibleBondExample
import qualified QuantLib.Example.EquityOption as EquityOptionExample
import qualified QuantLib.Example.FRA as FRAExample
import qualified QuantLib.Example.Replication as ReplicationExample
import qualified QuantLib.Example.Repo as RepoExample
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
      cleanFromYield = BondExample.cleanPriceFromYieldR r
      yieldFromClean = BondExample.yieldFromCleanPriceR r
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

test_replication :: IO ()
test_replication = do
  (ReplicationExample.Result npvInit npvOut npvIn) <- Settings.keepingSettings' ReplicationExample.run
  subAssert $ assertListsAreClose id npvInit [4.260726, 4.322358, 4.295464, 4.280909] 1.0e-6
  subAssert $ assertListsAreClose id npvOut [2.513058, 2.539365, 2.528362, 2.522105] 1.0e-6
  subAssert $ assertListsAreClose id npvIn [5.739125, 5.851239, 5.799867, 5.773678] 1.0e-6

test_bermudanSwaption :: IO ()
test_bermudanSwaption = do
  (BermudanSwaptionExample.Result g2v g2p hwv hwp hw2v hw2p bkv bkp npvA _npvO npvI) <- Settings.keepingSettings' $ BermudanSwaptionExample.run False
  subAssert $ assertListsAreClose id g2v [10.04549, 10.51234, 10.70500, 10.83817, 10.94387] 1.0e-5
  subAssert $ assertListsAreClose id hwv [10.62037, 10.62959, 10.63414, 10.64428, 10.66132] 1.0e-5
  subAssert $ assertListsAreClose id hw2v [10.31185, 10.54619, 10.66914, 10.74020, 10.79725] 1.0e-5
  subAssert $ assertListsAreClose id bkv [10.32593, 10.56575, 10.67858, 10.73678, 10.77792] 1.0e-5
  subAssert $ assertListsAreClose id g2p [0.050056, 0.0094424, 0.050053, 0.0094424, -0.763] 1.0e-4 -- NB low precision!
  subAssert $ assertListsAreClose id hwp [0.046414, 0.0058693] 1.0e-5
  subAssert $ assertListsAreClose id hw2p [0.055229, 0.0061063] 1.0e-5
  subAssert $ assertListsAreClose id bkp [0.043389, 0.12075] 1.0e-5
  subAssert $ assertListsAreClose id npvA [14.11, 14.113, 12.904, 12.91, 13.158, 13.157, 13.002] 1.0e-3
  --subAssert $ assertListsAreClose id npvO [3.194, 3.1808, 2.4921, 2.4596, 2.615, 2.5829, 3.2751] 1.0e-3
  subAssert $ assertListsAreClose id npvI [42.609, 42.705, 42.253, 42.215, 42.364, 42.311, 41.825] 1.0e-3

test_equityOption :: IO ()
test_equityOption = do
  (EquityOptionExample.Result analyticEuro analyticHeston bates baw bjs bin int fd mc) <- Settings.keepingSettings' EquityOptionExample.run
  subAssert $ assertListsAreClose id analyticEuro   [3.844308] 1.0e-6
  subAssert $ assertListsAreClose id analyticHeston [3.844306] 1.0e-6
  subAssert $ assertListsAreClose id bates          [3.844306] 1.0e-6
  subAssert $ assertListsAreClose id baw            [4.459628] 1.0e-6
  subAssert $ assertListsAreClose id bjs            [4.453064] 1.0e-6
  subAssert $ assertListsAreClose id int            [3.844309] 1.0e-6
  subAssert $ assertListsAreClose id fd [3.844342, 4.360807, 4.486118] 1.0e-6
  subAssert $ assertListsAreClose id mc [3.834522, 3.844613, 4.481675] 1.0e-6
  subAssert $ assertListsAreClose id (head bin) [3.844132, 4.361174, 4.486552] 1.0e-6
  subAssert $ assertListsAreClose id (bin!!1)   [3.843504, 4.360861, 4.486415] 1.0e-6
  subAssert $ assertListsAreClose id (bin!!2)   [3.836911, 4.354455, 4.480097] 1.0e-6
  subAssert $ assertListsAreClose id (bin!!3)   [3.843557, 4.360909, 4.486461] 1.0e-6
  subAssert $ assertListsAreClose id (bin!!4)   [3.844171, 4.361176, 4.486413] 1.0e-6
  subAssert $ assertListsAreClose id (bin!!5)   [3.844308, 4.360713, 4.486076] 1.0e-6
  subAssert $ assertListsAreClose id (bin!!6)   [3.844308, 4.360713, 4.486076] 1.0e-6

test_cds :: IO ()
test_cds = do
  (CDSExample.Result probs fairSpread npv defNpv cpnNpv) <- Settings.keepingSettings' CDSExample.run
  subAssert $ assertListsAreClose id probs [97.040061, 94.175780] 1.0e-6
  subAssert $ assertListsAreClose id fairSpread [1.500000, 1.500000, 1.500000, 1.500000] 1.0e-6
  subAssert $ assertListsAreClose id npv [-7.18501e-11, -1.52795e-10, -2.05728e-09, -6.25732e-10] 1.0e-10
  subAssert $ assertListsAreClose id defNpv [-5218.16, -8882.83, -16142.9, -30195.6] 1.0e-1
  subAssert $ assertListsAreClose id cpnNpv [5218.16, 8882.83, 16142.9, 30195.6] 1.0e-1

test_convertibleBond :: IO ()
test_convertibleBond = do
  (ConvertibleBondExample.Result jr crr ad tr ti lr j) <- Settings.keepingSettings' ConvertibleBondExample.run
  subAssert $ assertListsAreClose id jr [105.690844, 108.141608] 1.0e-6
  subAssert $ assertListsAreClose id crr [105.698533, 108.166210] 1.0e-6
  subAssert $ assertListsAreClose id ad [105.626388, 108.085800] 1.0e-6
  subAssert $ assertListsAreClose id tr [105.699036, 108.166649] 1.0e-6
  subAssert $ assertListsAreClose id ti [105.712848, 108.174293] 1.0e-6
  subAssert $ assertListsAreClose id lr [105.668326, 108.155630] 1.0e-6
  subAssert $ assertListsAreClose id j [105.668327, 108.155630] 1.0e-6

test_callableBond :: IO ()
test_callableBond = do
  (CallableBondExample.Result ps ys) <- Settings.keepingSettings' CallableBondExample.run
  subAssert $ assertListsAreClose id ps [96.47, 95.64, 92.31, 87.08, 77.34] 1.0e-2
  subAssert $ assertListsAreClose id ys [5.48, 5.67, 6.49, 7.85, 10.64] 1.0e-2

test_evalDate :: IO ()
test_evalDate = do
  t1 <- Settings.evaluationDate
  t2 <- today
  assertEqual t1 t2

test_nullEvalDate :: IO ()
test_nullEvalDate = do
  Settings.setEvaluationDate (december 29 2012)
  t0 <- Settings.evaluationDate
  assertEqual t0 (fromGregorian 2012 12 29)
  t2 <- today
  Settings.resetEvaluationDate
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
  let (Left m) = Leg.startDate l
  assertBool (not $ null m)

test_singleLegToday :: IO ()
test_singleLegToday = do
  t <- today
  l <- Leg.leg [(100, t)]
  let (Right sd) = Leg.startDate l
  assertEqual sd t

test_twoLegsUnsorted :: IO ()
test_twoLegsUnsorted = do
  t <- today
  l <- Leg.leg [(100, t), (-1000, addDays (-10) t)]
  let (Right sd) = Leg.startDate l
  assertEqual sd (addDays (-10) t)

test_threeLegsSorted :: IO ()
test_threeLegsSorted = do
  t <- today
  l <- Leg.leg [(100, t), (1000, addDays (-10) t), (-2000, addDays 10 t)]
  let (Right sd) = Leg.startDate l
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
  _ <- Bond.fixedRateBondFromSchedule
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
  _ <- Bond.fixedRateBond
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
  _ <- Bond.fixedRateBondFromSchedule'
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
  assertEqual (Right Frequency.Monthly) (Period.toFrequency p)

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
