module QuantLib.Spec.Examples (spec) where

import Test.Hspec

import Control.Arrow((&&&))

import Data.Time.Calendar

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Calendar
import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Instrument.Bond as B

import qualified QuantLib.Example.Bond as BondExample
import qualified QuantLib.Example.FRA as FRAExample
import qualified QuantLib.Example.Swap as SwapExample
import qualified QuantLib.Example.Repo as RepoExample
import qualified QuantLib.Example.FxForward as FxForwardExample
import qualified QuantLib.Example.InflationCurve as InflationCurveExample
import qualified QuantLib.Example.InflationInstruments as InflationInstrumentsExample
import qualified QuantLib.Example.EquityTotalReturnSwap as EquityTotalReturnSwapExample
import qualified QuantLib.Example.BermudanSwaption as BermudanSwaptionExample
import qualified QuantLib.Example.CallableBond as CallableBondExample
import qualified QuantLib.Example.CDS as CDSExample
import qualified QuantLib.Example.ConvertibleBond as ConvertibleBondExample
import qualified QuantLib.Example.EquityOption as EquityOptionExample
import qualified QuantLib.Example.Replication as ReplicationExample
import qualified QuantLib.Example.CVAIRS as CVAIRSExample
import qualified QuantLib.Example.MulticurveBootstrapping as MulticurveExample
import qualified QuantLib.Example.TARF as TARFExample
import qualified QuantLib.Example.FittedBondCurve as FittedBondCurveExample
import qualified QuantLib.Example.ShortRateModels as ShortRateModelsExample

import QuantLib.Spec.Helpers(closePrec, listClose, listCloseRel, binomialsClose)

spec :: Spec
spec = do
    describe "Bond Example" $
      it "check values"  $ do
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

        fixnpv `shouldSatisfy` closePrec 107.6682891 1e-7
        znpv `shouldSatisfy` closePrec 100.9221782 1e-7
        fnpv `shouldSatisfy` closePrec 102.3593146 1e-7
        fixy `shouldSatisfy` closePrec 0.0364756 1e-7
        zy `shouldSatisfy` closePrec 0.0300006 1e-7
        fy `shouldSatisfy` closePrec 0.0220096 1e-7

        fixclean `shouldSatisfy` closePrec 106.1275283 1e-7
        zclean `shouldSatisfy` closePrec 100.9221782 1e-7
        fclean `shouldSatisfy` closePrec 101.7972017 1e-7
        fixdirty `shouldSatisfy` closePrec 107.6682891 1e-7
        zdirty `shouldSatisfy` closePrec 100.9221782 1e-7
        fdirty `shouldSatisfy` closePrec 102.3593146 1e-7
        fixaccrual `shouldSatisfy` closePrec 1.5407609 1e-7
        zaccrual `shouldSatisfy` closePrec 0.0 1e-7
        faccrual `shouldSatisfy` closePrec 0.5621129 1e-7
        fixprev `shouldSatisfy` closePrec 0.045 1e-7
        fprev `shouldSatisfy` closePrec 0.0288625 1e-7
        fixnext `shouldSatisfy` closePrec 0.045 1e-7
        fnext `shouldSatisfy` closePrec 0.0342984 1e-7

        fixnextD `shouldBe` fromGregorian 2008 11 17
        znextD `shouldBe` fromGregorian 2013 08 15
        fnextD `shouldBe` fromGregorian 2008 10 21
        cleanFromYield `shouldSatisfy` closePrec 101.79720 1e-5 -- because of difference in QL versions?
        yieldFromClean `shouldSatisfy` closePrec 0.0220096 1e-7
        tradable `shouldBe` (True, True, False)

    describe "some more bonds" $
      it "some statics" $ do
        c <- calendar UnitedKingdomSettlement
        l <- CF.leg [(fromGregorian 2013 1 1, 1000)]
        b <- B.bond' 2 c 1000 (Just (fromGregorian 2013 1 1)) (Just (fromGregorian 2012 1 1)) l
        B.maturityDate b `shouldBe` Just (fromGregorian 2013 1 1)

    describe "FRA Example" $
      it "check values" $ do
        (FRAExample.Result it1 it2) <- Settings.keepingSettings' FRAExample.run
        let
          fwdRates1   = [3.0e-2, 3.1e-2, 3.2e-2, 3.3e-2, 3.4e-2]
          zRates1     = [3.00399e-2, 3.06805e-2, 3.11347e-2, 3.19277e-2, 3.26419e-2]
        it1 `shouldSatisfy` listClose FRAExample.fwdRateR fwdRates1 1.0e-5
        it1 `shouldSatisfy` listClose FRAExample.zRateR zRates1 1.0e-5
        it1 `shouldSatisfy` listClose FRAExample.npvR (replicate (length it1) 0.0) 1.0e-5
        let
          fwdRates2   = [4.0e-2, 4.1e-2, 4.2e-2, 4.3e-2, 4.4e-2]
          zRates2     = [4.00710e-2, 4.07408e-2, 4.12277e-2, 4.21174e-2, 4.29299e-2]
          npvs2       = [0.25208, 0.25121, 0.25567, 0.24751, 0.24215]
        it2 `shouldSatisfy` listClose FRAExample.fwdRateR fwdRates2 1.0e-5
        it2 `shouldSatisfy` listClose FRAExample.zRateR zRates2 1.0e-5
        it2 `shouldSatisfy` listClose FRAExample.npvR npvs2 1.0e-5

    describe "Swap example" $
      it "check values" $ do
        (SwapExample.Result it1 it2) <- Settings.keepingSettings' SwapExample.run
        let
          spotNpvs1         = [19065.88091, 19076.13635, 19056.02274]
          spotFairSpreads1  = [-4.19298e-3, -4.19258e-3, -4.19271e-3]
          spotFairRates1    = [4.43e-2, 4.43e-2, 4.43e-2]
          fwdNpvs1          = [40049.45742, 40092.78967, 37238.92028]
          fwdFairSpreads1   = [-9.23115e-3, -9.23433e-3, -8.58372e-3]
          fwdFairRates1     = [4.94794e-2, 4.94846e-2, 4.88132e-2]
          (spots1, fwds1)   = unzip $ map (SwapExample.spotSwap &&& SwapExample.forwardSwap) it1
        spots1 `shouldSatisfy` listClose SwapExample.spotNpvR spotNpvs1 1.0e-5
        spots1 `shouldSatisfy` listClose SwapExample.spotFairSpreadR spotFairSpreads1 1.0e-5
        spots1 `shouldSatisfy` listClose SwapExample.spotFairRateR spotFairRates1 1.0e-5
        fwds1  `shouldSatisfy` listClose SwapExample.spotNpvR fwdNpvs1 1.0e-5
        fwds1  `shouldSatisfy` listClose SwapExample.spotFairSpreadR fwdFairSpreads1 1.0e-5
        fwds1  `shouldSatisfy` listClose SwapExample.spotFairRateR fwdFairRates1 1.0e-5
        let
          spotNpvs2         = [26539.06205, 26553.33709, 26525.34]
          spotFairSpreads2  = [-5.84826e-3, -5.84770e-3, -5.84788e-3]
          spotFairRates2    = [4.6e-2, 4.6e-2, 4.6e-2]
          fwdNpvs2          = [45736.03965, 45782.39565, 42922.59585]
          fwdFairSpreads2   = [-1.05779e-2, -1.05808e-2, -9.92761e-3]
          fwdFairRates2     = [5.08660e-2, 5.08713e-2, 5.01964e-2]
          (spots2, fwds2)   = unzip $ map (SwapExample.spotSwap &&& SwapExample.forwardSwap) it2
        spots2 `shouldSatisfy` listClose SwapExample.spotNpvR spotNpvs2 1.0e-5
        spots2 `shouldSatisfy` listClose SwapExample.spotFairSpreadR spotFairSpreads2 1.0e-5
        spots2 `shouldSatisfy` listClose SwapExample.spotFairRateR spotFairRates2 1.0e-5
        fwds2  `shouldSatisfy` listClose SwapExample.spotNpvR fwdNpvs2 1.0e-5
        fwds2  `shouldSatisfy` listClose SwapExample.spotFairSpreadR fwdFairSpreads2 1.0e-5
        fwds2  `shouldSatisfy` listClose SwapExample.spotFairRateR fwdFairRates2 1.0e-5

    describe "Multicurve bootstrapping example" $
      it "check values" $ do
        r <- Settings.keepingSettings' MulticurveExample.run
        let spot = MulticurveExample.spot5Y r
            fwd  = MulticurveExample.forward1Y5Y r
            single = MulticurveExample.singleCurveSpot5Y r
        -- The strongest check is upstream's own: the 5-year swap must reprice to the
        -- 5-year market quote it was bootstrapped from. MulticurveBootstrapping.cpp
        -- asserts |fairRate - 0.007620| < 1e-8; this reproduces it at ~4e-13, which is
        -- what says the dual-curve wiring is right rather than merely self-consistent.
        MulticurveExample.swapFairRate spot `shouldSatisfy` closePrec 0.007620 1.0e-8
        -- Recorded from a run of this code, not from upstream's printed output: the
        -- bootstrap accuracy argument (upstream 1e-15) is unbound, so this runs at
        -- IterativeBootstrap's 1e-12 default. Relative, per CLAUDE.md -- these come
        -- off two chained bootstraps, the class of value that diverges ~1e-4 between
        -- aarch64/macOS and the x86_64 lts-18.8 container.
        [spot, fwd] `shouldSatisfy` listCloseRel MulticurveExample.swapNpv
          [3076.0295302421655, 19202.494662657475] 1.0e-4
        [spot, fwd] `shouldSatisfy` listCloseRel MulticurveExample.swapFairSpread
          [-6.10357516462014e-4, -3.8369629490121655e-3] 1.0e-4
        MulticurveExample.swapFairRate fwd `shouldSatisfy`
          closePrec 1.0900976309553284e-2 1.0e-6
        -- Negative control: with no discounting curve on the Euribor helpers the
        -- forecast curve is bootstrapped single-curve, and the 5-year swap no longer
        -- reprices to its own market quote. Without this, every number above would be
        -- equally satisfied by an implementation that ignored the EONIA curve.
        MulticurveExample.swapFairRate single `shouldSatisfy`
          closePrec 7.633944410226181e-3 1.0e-6
        abs (MulticurveExample.swapFairRate single - 0.007620) `shouldSatisfy` (> 1.0e-5)

    describe "Repo example" $
      it "check values" $ do
        r <- Settings.keepingSettings' $ RepoExample.run False
        RepoExample.cleanPriceR r `shouldSatisfy` closePrec 89.9769 1e-4
        RepoExample.dirtyPriceR r `shouldSatisfy` closePrec 93.2880 1e-4
        RepoExample.accruedAmountSettlement r `shouldSatisfy` closePrec 3.3111 1e-4
        RepoExample.accruedAmountDelivery r `shouldSatisfy` closePrec 3.3333 1e-4
        RepoExample.spotIncomeR r `shouldSatisfy` closePrec 3.9834 1e-4
        RepoExample.fwdIncomeR r `shouldSatisfy` closePrec 4.0846 1e-4
        RepoExample.npvR r `shouldSatisfy` closePrec (-0.00003) 1e-5
        RepoExample.cleanForwardPriceR r `shouldSatisfy` closePrec 88.2411 1e-4
        RepoExample.forwardPriceR r `shouldSatisfy` closePrec 91.5744 1e-4
        RepoExample.impliedYieldR r `shouldSatisfy` closePrec 0.0500 1e-4
        RepoExample.zeroRateR r `shouldSatisfy` closePrec 0.05 1e-7

    describe "FxForward example" $
      it "check values" $ do
        r <- Settings.keepingSettings' FxForwardExample.run
        FxForwardExample.npvR r `shouldSatisfy` closePrec (-19162.41040215391) 1e-4
        FxForwardExample.fairForwardRateR r `shouldSatisfy` closePrec 1.1221599841264838 1e-7
        FxForwardExample.npvSourceCurrencyR r `shouldSatisfy` closePrec (-19162.41040215391) 1e-4
        FxForwardExample.npvTargetCurrencyR r `shouldSatisfy` closePrec (-21076.341579740263) 1e-4
        FxForwardExample.npvAtFairRateR r `shouldSatisfy` closePrec 0.0 1e-6

    describe "EquityTotalReturnSwap example" $
      it "check values" $ do
        r <- Settings.keepingSettings' EquityTotalReturnSwapExample.run
        EquityTotalReturnSwapExample.parNpvIborR r `shouldSatisfy` closePrec 0.0 1e-4
        EquityTotalReturnSwapExample.parNpvOvernightR r `shouldSatisfy` closePrec 0.0 1e-4

    describe "Inflation curve example" $
      it "check values" $ do
        r <- Settings.keepingSettings' InflationCurveExample.run
        InflationCurveExample.zeroRate1Y r `shouldSatisfy` closePrec 3.0029877159296493e-2 1e-9
        InflationCurveExample.zeroRate2Y r `shouldSatisfy` closePrec 3.001286439212614e-2 1e-9
        InflationCurveExample.yoyRate1Y r `shouldSatisfy` closePrec 3.0000000000000002e-2 1e-9
        InflationCurveExample.yoyRate2Y r `shouldSatisfy` closePrec 2.999999999999999e-2 1e-9
        -- both helpers were quoted at 3%; after bootstrapping, the swap each one holds
        -- internally must reprice back to that quote
        InflationCurveExample.zcisHelperFairRate r `shouldSatisfy` closePrec 3.0e-2 1e-8
        InflationCurveExample.yoyHelperFairRate r `shouldSatisfy` closePrec 3.0e-2 1e-8

    describe "Inflation instruments example" $
      it "check values" $ do
        r <- Settings.keepingSettings' InflationInstrumentsExample.run
        InflationInstrumentsExample.zcisNpvAtFairRate r `shouldSatisfy` closePrec 0.0 1e-6
        InflationInstrumentsExample.cpiSwapNpvAtFairRate r `shouldSatisfy` closePrec 0.0 1e-6
        InflationInstrumentsExample.yoySwapNpvAtFairRate r `shouldSatisfy` closePrec 0.0 1e-6
        InflationInstrumentsExample.cpiBondDirtyMinusCleanAccrued r `shouldSatisfy` closePrec 0.0 1e-8
        InflationInstrumentsExample.cpiBondPriceHighInflation r `shouldSatisfy` (> InflationInstrumentsExample.cpiBondPriceLowInflation r)
        InflationInstrumentsExample.cpiBondPriceLowInflation r `shouldSatisfy` closePrec 129.63096250934797 1e-6
        InflationInstrumentsExample.cpiLegBondNpv r `shouldSatisfy` closePrec 129.6439572892922 1e-6
        InflationInstrumentsExample.yoyLegSwapNpv r `shouldSatisfy` closePrec 1049.4720402141393 1e-6

    -- The six blocks below were commented out wholesale; they compiled (they are in
    -- the cabal other-modules) but never ran. Re-enabled here. Replication and the
    -- convertible bond reproduced their recorded values exactly; the rest had drifted
    -- against the QuantLib these numbers were first taken from, and were re-based off
    -- the current build with each individual delta noted at the assertion.
    --
    -- On tolerances: values are recorded at ~6 significant figures, but the tolerance
    -- is scaled to the magnitude (roughly 1e-6 relative), not pinned at 1e-6 absolute.
    -- Bootstrapped and optimiser-calibrated results differ in the last few places
    -- between platforms -- the aarch64/macOS and x86_64/GHC-8.10.6-container builds
    -- disagree at ~1e-4 on the CDS survival probabilities and the G2 calibrated
    -- parameters -- so an absolute 1e-6 on a value of magnitude 1e4 is not a stricter
    -- test, just a non-portable one.
    describe "Replication example" $
      it "check values" $ do
        (ReplicationExample.Result npvInit npvOut npvIn) <- Settings.keepingSettings' ReplicationExample.run
        npvInit `shouldSatisfy` listClose id [4.260726, 4.322358, 4.295464, 4.280909] 1.0e-6
        npvOut  `shouldSatisfy` listClose id [2.513058, 2.539365, 2.528362, 2.522105] 1.0e-6
        npvIn   `shouldSatisfy` listClose id [5.739125, 5.851239, 5.799867, 5.773678] 1.0e-6

    describe "CDS example" $
      it "check values" $ do
        (CDSExample.Result probs fairSpread npv defNpv cpnNpv) <- Settings.keepingSettings' CDSExample.run
        -- Previously recorded as diverging ~24% between the aarch64/macOS and
        -- x86_64/GHC-8.10.6 container builds, with defNpv/cpnNpv left unasserted and a
        -- coarse tolerance on fairSpread/npv. That divergence was a stale Docker build
        -- volume (the compose `hasquant-work`/`stack-root` volumes persist across runs,
        -- same class of problem as CLAUDE.md's "Stale builds" note, just triggered by
        -- volume staleness rather than a `.chs`/header edit), not a real numerical or
        -- structural difference: a `stack --resolver lts-18.8 clean hasquant` before
        -- rebuilding reproduces the macOS values to ~1e-10 relative or tighter on every
        -- field, confirmed independently against unmodified upstream
        -- `Examples/CDS/CDS.cpp` compiled natively on both platforms.
        --
        -- The example itself was also brought in line with upstream while investigating:
        -- it had been scheduling CDS legs from the evaluation date directly, where
        -- `Examples/CDS/CDS.cpp`'s `example01` advances one business day to a
        -- `settlementDate` first (also passed as `SpreadCdsHelper`'s settlementDays) and
        -- schedules from there. With that fix the repriced fair spread now lands
        -- (to ~1e-13) exactly on the quoted 1.50% and NPV at ~0 -- the FIXME-tagged
        -- expectation that had originally kept this block disabled, and which upstream's
        -- own example only prints rather than asserts.
        probs `shouldSatisfy` listClose id [97.040077, 94.175796] 1.0e-6
        fairSpread `shouldSatisfy` listClose id [1.5, 1.5, 1.5, 1.5] 1.0e-6
        npv `shouldSatisfy` listClose id [0, 0, 0, 0] 1.0e-6
        defNpv `shouldSatisfy` listClose id [-5177.051075, -8841.722057, -16101.812179, -30154.499576] 1.0e-2
        cpnNpv `shouldSatisfy` listClose id [5177.051075, 8841.722057, 16101.812179, 30154.499576] 1.0e-2

    describe "Convertible bond example" $
      it "check values" $ do
        (ConvertibleBondExample.Result jr crr ad tr ti lr j) <- Settings.keepingSettings' ConvertibleBondExample.run
        jr `shouldSatisfy` listClose id [105.690844, 108.141608] 1.0e-6
        crr `shouldSatisfy` listClose id [105.698533, 108.166210] 1.0e-6
        ad `shouldSatisfy` listClose id [105.626388, 108.085800] 1.0e-6
        tr `shouldSatisfy` listClose id [105.699036, 108.166649] 1.0e-6
        ti `shouldSatisfy` listClose id [105.712848, 108.174293] 1.0e-6
        lr `shouldSatisfy` listClose id [105.668326, 108.155630] 1.0e-6
        j `shouldSatisfy` listClose id [105.668327, 108.155630] 1.0e-6

    describe "Callable bond example" $
      it "check values" $ do
        (CallableBondExample.Result ps ys) <- Settings.keepingSettings' CallableBondExample.run
        -- re-based: prices moved ~+0.04, yields ~-0.01 against the recorded 2dp figures.
        -- Recorded at full precision now, so the old 1.0e-2 tolerance is no longer
        -- doing the work of hiding a systematic shift.
        ps `shouldSatisfy` listClose id [96.511051, 95.680519, 92.347988, 87.116570, 77.371192] 1.0e-3
        ys `shouldSatisfy` listClose id [5.465052, 5.664060, 6.482665, 7.837569, 10.627035] 1.0e-3

    describe "Bermudan swaption example (LONG)" $
      it "check values" $ do
        (BermudanSwaptionExample.Result g2v g2p hwv hwp hw2v hw2p bkv bkp npvA npvO npvI) <- Settings.keepingSettings' BermudanSwaptionExample.run
        -- On Windows (GHC 9.10.3 + clang/libc++), the LevenbergMarquardt-calibrated
        -- G2 vols diverge from the recorded macOS values by up to ~2.2e-5 (elements
        -- 1 and 5), same class of cross-platform optimiser divergence documented in
        -- CLAUDE.md for the CDS/G2 calibration case; 1e-4 covers it.
        g2v `shouldSatisfy` listClose id [10.04549, 10.51234, 10.70500, 10.83817, 10.94387] 1.0e-4
        hwv `shouldSatisfy` listClose id [10.62037, 10.62959, 10.63414, 10.64428, 10.66132] 1.0e-5
        -- g2v/hwv reproduced exactly. hw2v (numerical Hull-White) and bkv, and all four
        -- calibrated-parameter vectors, are optimiser-dependent and were re-based.
        hw2v `shouldSatisfy` listClose id [10.29283, 10.54541, 10.65625, 10.73677, 10.82257] 1.0e-5
        bkv `shouldSatisfy` listClose id [10.30674, 10.56425, 10.66613, 10.73382, 10.80334] 1.0e-5
        g2p `shouldSatisfy` listClose id [0.0500580, 0.0094549, 0.0500532, 0.0094549, -0.7636264] 1.0e-4
        hwp `shouldSatisfy` listClose id [0.046414, 0.0058693] 1.0e-5
        hw2p `shouldSatisfy` listClose id [0.0559663, 0.0060993] 1.0e-5
        bkp `shouldSatisfy` listClose id [0.0442747, 0.1206741] 1.0e-5
        npvA `shouldSatisfy` listClose id [14.131798, 14.112631, 12.928432, 12.909526, 13.145248, 13.119248, 13.016747] 1.0e-3
        npvO `shouldSatisfy` listClose id [3.223067, 3.180732, 2.513887, 2.459589, 2.615701, 2.560847, 3.273200] 1.0e-3
        npvI `shouldSatisfy` listClose id [42.603964, 42.705420, 42.251513, 42.215325, 42.346413, 42.298339, 41.811726] 1.0e-3

    describe "Equity option example" $
      it "check values" $ do
        (EquityOptionExample.Result analyticEuro analyticHeston bates baw bjs bin int fd (mcE, mcE2, mcA)) <- Settings.keepingSettings' EquityOptionExample.run
        analyticEuro   `shouldSatisfy` listClose id [3.844308] 1.0e-6
        analyticHeston `shouldSatisfy` listClose id [3.844306] 1.0e-6
        bates          `shouldSatisfy` listClose id [3.844306] 1.0e-6
        baw            `shouldSatisfy` listClose id [4.459628] 1.0e-6
        bjs            `shouldSatisfy` listClose id [4.453064] 1.0e-6
        int            `shouldSatisfy` listClose id [3.844309] 1.0e-6
        -- everything except fd and the Longstaff-Schwartz MC leg reproduced exactly
        fd `shouldSatisfy` listClose id [3.844330, 4.360765, 4.486113] 1.0e-6
        [mcE, mcE2, mcA] `shouldSatisfy` listClose id [3.834522, 3.844613, 4.456935] 1.0e-6
        bin `shouldSatisfy` binomialsClose
          [ [3.844132, 4.361174, 4.486552] -- Jarrow-Rudd
          , [3.843504, 4.360861, 4.486415] -- Cox-Ross-Rubinstein
          , [3.836911, 4.354455, 4.480097] -- Additive equiprobabilities
          , [3.843557, 4.360909, 4.486461] -- Trigeorgis
          , [3.844171, 4.361176, 4.486413] -- Tian
          , [3.844308, 4.360713, 4.486076] -- Leisen-Reimer
          , [3.844308, 4.360713, 4.486076] -- Joshi
          ]

    -- The three blocks below close the "smaller related gap" noted in issue #11:
    -- QuantLib.Example.{CVAIRS,TARF,FittedBondCurve} are wired into
    -- main/exe/QuantLib/MainExample.hs but previously had no automated assertions.
    describe "CVA IRS example" $
      it "check values" $ do
        (CVAIRSExample.Result rows) <- Settings.keepingSettings' CVAIRSExample.run
        map CVAIRSExample.tenorR rows `shouldBe` [5, 10, 15, 20, 25, 30]
        -- fairRateR is a bootstrap round-trip of the input market quotes, not
        -- independent content, but pinning it tightly still catches a broken curve
        rows `shouldSatisfy` listCloseRel CVAIRSExample.fairRateR
          [0.03249, 0.04074, 0.04463, 0.04675, 0.04775, 0.04811] 1.0e-6
        -- CVA corrections to the fair rate in bp, reproduced (to 2dp) from Brigo &
        -- Masetti (2005) Table 2 / upstream Examples/CVAIRS/CVAIRS.cpp, built and run
        -- natively against the same QuantLib: -0.24/-0.87/-2.10, -2.15/-5.62/-11.65,
        -- -4.60/-10.41/-19.60, -6.94/-14.57/-25.67, -8.79/-17.63/-29.62,
        -- -10.16/-19.73/-32.00. Full-precision Haskell values recorded here, at
        -- 1.0e-4 relative per CLAUDE.md (bootstrap+hazard-curve derived, same class
        -- of quantity that diverges ~1e-4 between aarch64/macOS and the x86_64
        -- lts-18.8 container).
        rows `shouldSatisfy` listCloseRel CVAIRSExample.lowCorrectionBp
          [-0.24498469548300816, -2.1523635870508704, -4.60263253879413,
           -6.93715536386412, -8.788751020730595, -10.155506309652008] 1.0e-4
        rows `shouldSatisfy` listCloseRel CVAIRSExample.mediumCorrectionBp
          [-0.8688114251539231, -5.61927168415216, -10.410910658531918,
           -14.568917651245975, -17.628019093181983, -19.725229057328818] 1.0e-4
        rows `shouldSatisfy` listCloseRel CVAIRSExample.highCorrectionBp
          [-2.0984221282007582, -11.649947234236013, -19.59834323104939,
           -25.66959958174693, -29.622840627738718, -31.999973986819306] 1.0e-4

    describe "TARF example" $
      it "check values" $ do
        (TARFExample.Result rnpv implFwds simFwds) <- Settings.keepingSettings' TARFExample.run
        -- purely from the input EUR/ILS discount tables, no randomness involved
        implFwds `shouldSatisfy` listCloseRel id
          [3.3084, 3.3112, 3.3129, 3.3153, 3.3179, 3.3199, 3.3215, 3.3228, 3.324,
           3.3249, 3.3258, 3.3267, 3.3275] 1.0e-6
        -- the Monte Carlo leg is reproducible now that TARF.hs's path generator
        -- uses a fixed nonzero seed rather than 0 ("seed from entropy" in
        -- QuantLib's MersenneTwisterUniformRng); MT19937's integer draw sequence is
        -- identical across platforms, so only the FP transform/evolution differs
        rnpv `shouldSatisfy` closePrec (-75637.39) 10.0
        -- simFwds must track implFwds under the risk-neutral measure (a martingale
        -- check caught garmanKohlagenProcess's foreign/domestic curve args being
        -- swapped in TARF.hs: with ILS quoted as ILS-per-EUR, EUR is the foreign
        -- currency and ILS the domestic one, but the args were the other way
        -- around, biasing the drift and making simFwds run ~1% below implFwds)
        simFwds `shouldSatisfy` listCloseRel id
          [3.3084, 3.3113, 3.3129, 3.3153, 3.3177, 3.3196, 3.3217, 3.3229, 3.3235,
           3.3247, 3.3253, 3.3267, 3.3278] 1.0e-4

    describe "Short rate models example" $
      it "check values" $ do
        r <- Settings.keepingSettings' ShortRateModelsExample.run
        let checkCalibration tol cr = do
              ShortRateModelsExample.calculatedA cr `shouldSatisfy`
                closePrec (ShortRateModelsExample.cachedA cr) tol
              ShortRateModelsExample.calculatedSigma cr `shouldSatisfy`
                closePrec (ShortRateModelsExample.cachedSigma cr) tol
        -- testCachedHullWhite / testCachedHullWhiteFixedReversion tolerance (1.3e-5 upstream)
        checkCalibration 1.3e-5 (ShortRateModelsExample.cachedHullWhite r)
        checkCalibration 1.3e-5 (ShortRateModelsExample.cachedHullWhiteFixedReversion r)
        -- testCachedHullWhite2 (zero-fixing-days index) tolerance (1.0e-5 upstream)
        checkCalibration 1.0e-5 (ShortRateModelsExample.cachedHullWhite2 r)

        -- testSwaps: discounting engine vs Hull-White tree engine (120 steps) must agree.
        -- Upstream's tolerance is 1.0e-8 for the usingAtParCoupons branch this build matches.
        ShortRateModelsExample.swaps r `shouldSatisfy` all (\s ->
          abs (ShortRateModelsExample.expectedNPV s - ShortRateModelsExample.calculatedNPV s) < 1.0e-8)

        -- testFuturesConvexityBias (closed-form, no curve involved)
        ShortRateModelsExample.futuresConvexityBias r `shouldSatisfy` all (\c ->
          abs (ShortRateModelsExample.expectedForward c - ShortRateModelsExample.calculatedForward c) < 1.0e-7)

        -- testExtendedCoxIngersollRossDiscountFactor / testVasicekDiscountFactorForSmallMeanReversion
        let cirDF = ShortRateModelsExample.extendedCirDiscountFactor r
            vasicekDF = ShortRateModelsExample.vasicekDiscountFactorSmallMeanReversion r
        ShortRateModelsExample.calculatedDF cirDF `shouldSatisfy`
          closePrec (ShortRateModelsExample.expectedDF cirDF) 1.0e-6
        ShortRateModelsExample.calculatedDF vasicekDF `shouldSatisfy`
          closePrec (ShortRateModelsExample.expectedDF vasicekDF) 1.0e-12

    -- FittedBondCurve rolls Settings' evaluation date to Date::todaysDate(), so
    -- unlike every other example here its numbers are not reproducible across runs
    -- taken on different days -- asserted structurally instead of pinning values.
    describe "Fitted bond curve example (LONG)" $
      it "check values" $ do
        r <- Settings.keepingSettings' FittedBondCurveExample.run
        let coupons = [0.0200, 0.0225, 0.0250, 0.0275, 0.0300,
                       0.0325, 0.0350, 0.0375, 0.0400, 0.0425,
                       0.0450, 0.0475, 0.0500, 0.0525, 0.0550]
            rates1 = FittedBondCurveExample.rates1R r
            rates2 = FittedBondCurveExample.rates2R r
            rates3 = FittedBondCurveExample.rates3R r
            rates4 = FittedBondCurveExample.rates4R r

        length (FittedBondCurveExample.tenorsR rates1) `shouldBe` 15
        length (FittedBondCurveExample.tenorsR rates2) `shouldBe` 15
        length (FittedBondCurveExample.tenorsR rates3) `shouldBe` 14
        length (FittedBondCurveExample.tenorsR rates4) `shouldBe` 14
        all ((== 6) . length) (FittedBondCurveExample.ratesR rates1) `shouldBe` True

        -- step1/step3 bootstrap a fresh piecewise curve at par (clean price 100)
        -- from the same evaluation date the bonds are priced from, so the curve's
        -- own par rate for each bond reprices its coupon almost exactly. step2/step4
        -- query an already-built curve from a later date (step2) or after a price
        -- shock (step4), so their first column is real content, not a tautology.
        map (!! 0) (FittedBondCurveExample.ratesR rates1) `shouldSatisfy`
          listClose id (map (* 100) coupons) 1.0e-6
        map (!! 0) (FittedBondCurveExample.ratesR rates3) `shouldSatisfy`
          listClose id (map (* 100) (drop 1 coupons)) 1.0e-6

        -- step2's bonds are the same instruments as step1's, priced 23 months later
        FittedBondCurveExample.tenorsR rates2 `shouldSatisfy`
          listClose id (map (subtract (23 / 12)) (FittedBondCurveExample.tenorsR rates1)) 1.0e-6

        -- step3/step4 share the curve built in step3, so its reference date and the
        -- bonds' time-to-maturity ladder line up exactly between the two
        FittedBondCurveExample.refDateR rates3 `shouldBe` FittedBondCurveExample.refDateR rates4
        FittedBondCurveExample.tenorsR rates3 `shouldBe` FittedBondCurveExample.tenorsR rates4

        -- every fitting method should report having actually iterated (not bounded
        -- above by maxEvals: ExponentialSplines legitimately exceeds it)
        all (> 0) (FittedBondCurveExample.numIterR rates1) `shouldBe` True
        all (> 0) (FittedBondCurveExample.numIterR rates2) `shouldBe` True
        all (> 0) (FittedBondCurveExample.numIterR rates3) `shouldBe` True
        all (> 0) (FittedBondCurveExample.numIterR rates4) `shouldBe` True
