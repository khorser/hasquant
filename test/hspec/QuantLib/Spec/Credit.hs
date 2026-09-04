module QuantLib.Spec.Credit (spec) where

import Test.Hspec
import Data.List.NonEmpty(fromList)
import Data.Time.Calendar(fromGregorian, addGregorianYearsClip)

import QuantLib.Currency(currency, Ccy(..))
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..), BusinessDayConvention(..))
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), TimeUnit(..), schedule, DateGenerationRule(..), Frequency(..))
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Quote(simpleQuote, setValue)
import QuantLib.TermStructure.Credit(flatHazardRate)
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.Instrument(setPricingEngine)
import QuantLib.Instrument.Credit(Claim(..), ProtectionSide(..), syntheticCDO, fairPremium, nthToDefault, ntdFairPremium)
import QuantLib.PricingEngine(midPointCDOEngine, integralCDOEngine, integralNtdEngine)
import qualified QuantLib.Settings as Settings
import QuantLib.Credit
import QuantLib.Spec.Helpers(closePrec)

-- |Builds a small pool/basket/Gaussian-LHP-loss-model chain and checks the loss model actually
-- wired up -- 'basketNotional' alone can't tell (it's a plain constructor echo, computed before
-- any loss model is consulted), so the discriminating check is 'basketExpectedTrancheLoss', which
-- throws if no loss model is attached. Fixture shape follows
-- ~/Src/QuantLib/test-suite/cdo.cpp (an EUR corporate default key, a single shared flat hazard
-- curve, five equal-notional names); numeric golden-value coverage against that fixture is
-- the 'SyntheticCDO' test below.
spec :: Spec
spec =
  describe "portfolio credit scaffolding (Pool, Issuer, Basket, GaussianLHPLossModel)" $ do
    it "wires a basket to a Gaussian LHP loss model over a small pool" $ Settings.keepingSettings' $ do
      let refDate = fromGregorian 2006 8 31
          names = ["issuer-0", "issuer-1", "issuer-2", "issuer-3", "issuer-4"]
          notionalPerName = 100.0

      Settings.setEvaluationDate (Just refDate)

      eur <- currency EUR
      dc <- dayCounter (Actual360 False)
      hazardQuote <- simpleQuote 0.01
      dts <- flatHazardRate refDate hazardQuote dc
      key <- northAmericaCorpDefaultKey eur SeniorSec (0, Weeks) 10.0 FullRestructuring

      iss <- issuer (fromList [(key, dts)])
      p <- pool (fromList [(n, iss, key) | n <- names])

      correlQuote <- simpleQuote 0.3
      lossModel <- gaussianLHPLossModel correlQuote (fromList (replicate (length names) 0.4))

      b <- basket refDate (fromList [(n, notionalPerName) | n <- names]) p 0.0 1.0 FaceValue lossModel

      notional <- basketNotional (trancheBasketAsBasket b)
      notional `shouldBe` notionalPerName * fromIntegral (length names)

      let futureDate = addGregorianYearsClip 5 refDate
      etl <- basketExpectedTrancheLoss b futureDate
      etl `shouldSatisfy` (\x -> x > 0 && x < notional)

    -- Ports test-suite/cdo.cpp's testHW, data set 1 only (corr=0.1, the "gaussian" branch of
    -- hwData7): a 100-name pool, the Gaussian LHP loss model (the only loss model hasquant
    -- binds -- IHGaussPoolLossModel/HomogGaussPoolLossModel/RandomDefaultLM are deliberately
    -- out of scope), and both CDO engines. Checked at upstream's own LHP-row tolerance (10bp
    -- absolute / 50% relative, cdo.cpp's absoluteTolerance/relativeToleranceMidp[3]) -- LHP is a
    -- crude approximation for a 100-name pool, so this is a wiring check against Hull-White
    -- Table 7, not a tight numeric regression. Do not tighten this tolerance later.
    it "prices a synthetic CDO tranche against Hull-White Table 7 (Gaussian LHP)" $ Settings.keepingSettings' $ do
      let refDate = fromGregorian 2006 8 31
          poolSize = 100 :: Int
          names = ["issuer-" ++ show i | i <- [0 .. poolSize - 1]]
          notionals = replicate poolSize 100.0
          recovery = 0.4
          -- (attachment, detachment, expected spread in bp) -- Hull-White Table 7, corr=0.1
          tranches = [ (0.00, 0.03, 2279.0)
                     , (0.03, 0.06,  450.0)
                     , (0.06, 0.10,   89.0)
                     , (0.10, 1.00,    1.0)
                     ]
          absTol = 10.0 :: Double
          relTol = 0.5 :: Double

      Settings.setEvaluationDate (Just refDate)

      eur <- currency EUR
      key <- northAmericaCorpDefaultKey eur SeniorSec (0, Weeks) 10.0 FullRestructuring
      act360 <- dayCounter (Actual360 False)
      hazardQuote <- simpleQuote 0.01
      dts <- flatHazardRate refDate hazardQuote act360

      iss <- issuer (fromList [(key, dts)])
      p <- pool (fromList [(n, iss, key) | n <- names])

      rateQuote <- simpleQuote 0.05
      yieldTS <- flatForward refDate rateQuote act360 Continuous Annual

      correlQuote <- simpleQuote 0.1
      lossModel <- gaussianLHPLossModel correlQuote (fromList (replicate poolSize recovery))

      target <- calendar TARGET
      sched <- schedule (Just $ fromGregorian 2006 9 1) (fromGregorian 2011 9 1) (3, Months) target
        Following Following Backward False Nothing Nothing

      midPEngine <- midPointCDOEngine yieldTS
      integralEngine <- integralCDOEngine yieldTS (3, Months)

      mapM_ (\(att, det, expected) -> do
        b <- basket refDate (fromList (zip names notionals)) p att det FaceValue lossModel
        cdo <- syntheticCDO b Seller sched 0.0 0.02 act360 Following Nothing

        setPricingEngine cdo midPEngine
        midFair <- (* 1e4) <$> fairPremium cdo
        (abs (midFair - expected) < absTol || abs ((midFair - expected) / expected) < relTol)
          `shouldBe` True

        setPricingEngine cdo integralEngine
        intFair <- (* 1e4) <$> fairPremium cdo
        (abs (intFair - expected) < absTol || abs ((intFair - expected) / expected) < relTol)
          `shouldBe` True
        ) tranches

    -- Ports test-suite/nthtodefault.cpp's testGauss/testStudent: the load-bearing numeric
    -- check for this credit slice (unlike the SyntheticCDO test above, whose LHP row is an
    -- intentionally loose wiring check -- see its comment). A 10-name symmetric basket (equal
    -- notional, equal hazard rate for every name) priced through IntegralNtdEngine, sweeping
    -- correlation on a shared SimpleQuote (mutating it re-prices without rebuilding the basket
    -- or loss model, since ConstantLossModel holds a Handle<Quote> onto it) and checked against
    -- Hull-White Table 3, at upstream's own tolerances.
    it "prices nth-to-default swaps against Hull-White Table 3" $ Settings.keepingSettings' $ do
      let refDate = fromGregorian 2006 8 31
          poolSize = 10 :: Int
          names = ["Name" ++ show i | i <- [0 .. poolSize - 1]]
          namesNotional = 100.0
          recovery = 0.4
          -- Hull-White Table 3: rank -> spread (bp) at correlation 0.0, 0.3, 0.6 (Gaussian copula)
          hwData :: [(Int, [Double])]
          hwData = [ (1, [603, 440, 293]), (2, [98, 139, 137]), (3, [12, 53, 79])
                   , (4, [1, 21, 49]),     (5, [0, 8, 31]),      (6, [0, 3, 19])
                   , (7, [0, 1, 12]),      (8, [0, 0, 7]),       (9, [0, 0, 3])
                   , (10, [0, 0, 1])
                   ]
          hwCorrelation = [0.0, 0.3, 0.6] :: [Double]
          -- Hull-White Table 3, "5/5" (Student-T, 5 degrees of freedom on both factors) column,
          -- at correlation 0.3 -- the only case testStudent actually checks numerically.
          hwDataStudent :: [(Int, Double)]
          hwDataStudent = zip [1 .. poolSize] [455, 116, 44, 22, 13, 8, 5, 4, 2, 1]

      Settings.setEvaluationDate (Just refDate)

      eur <- currency EUR
      key <- northAmericaCorpDefaultKey eur SeniorSec (0, Days) 1.0 FullRestructuring
      dc365 <- dayCounter Actual365FixedStandard
      act360 <- dayCounter (Actual360 False)
      hazardQuote <- simpleQuote 0.01
      dts <- flatHazardRate refDate hazardQuote dc365

      iss <- issuer (fromList [(key, dts)])
      p <- pool (fromList [(n, iss, key) | n <- names])

      rateQuote <- simpleQuote 0.05
      yieldTS <- flatForward refDate rateQuote dc365 Continuous Annual

      target <- calendar TARGET
      sched <- schedule (Just $ fromGregorian 2006 9 1) (fromGregorian 2011 9 1) (3, Months) target
        Following Following Backward False Nothing Nothing

      engine <- integralNtdEngine (1, Weeks) yieldTS

      let buildNtds correlQuote = do
            lossModel <- constantLossModel correlQuote (fromList (replicate poolSize recovery)) GaussianQuadrature []
            b <- digitalBasket refDate (fromList [(n, namesNotional / fromIntegral poolSize) | n <- names]) p 0.0 1.0 FaceValue lossModel
            mapM (\i -> do
              ntd <- nthToDefault b (fromIntegral i) Seller sched 0.0 0.02 act360 (namesNotional * fromIntegral poolSize) True
              setPricingEngine ntd engine
              return ntd
              ) [1 .. poolSize]

      -- Gaussian copula: sweep correlation on the shared quote, re-pricing the same NTDs.
      gaussCorrelQuote <- simpleQuote 0.0
      gaussNtds <- buildNtds gaussCorrelQuote
      mapM_ (\(j, corr) -> do
        _ <- setValue gaussCorrelQuote corr
        mapM_ (\(rank, spreads) -> do
          fair <- (* 1e4) <$> ntdFairPremium (gaussNtds !! (rank - 1))
          let expected = spreads !! j
          (abs (fair - expected) < 1.0 || abs ((fair - expected) / expected) < 0.015)
            `shouldBe` True
          ) hwData
        ) (zip [0 ..] hwCorrelation)

      -- Student-T copula (5 degrees of freedom on both factors), correlation 0.3 -- the one
      -- case testStudent actually checks (the rest is commented out upstream, pending a proper
      -- Student-T reference table).
      studentCorrelQuote <- simpleQuote 0.3
      studentLossModel <- constantLossModel studentCorrelQuote (fromList (replicate poolSize recovery)) GaussianQuadrature [5, 5]
      studentBasket <- digitalBasket refDate (fromList [(n, namesNotional / fromIntegral poolSize) | n <- names]) p 0.0 1.0 FaceValue studentLossModel
      studentNtds <- mapM (\i -> do
        ntd <- nthToDefault studentBasket (fromIntegral i) Seller sched 0.0 0.02 act360 (namesNotional * fromIntegral poolSize) True
        setPricingEngine ntd engine
        return ntd
        ) [1 .. poolSize]
      mapM_ (\(rank, expected) -> do
        fair <- (* 1e4) <$> ntdFairPremium (studentNtds !! (rank - 1))
        (abs (fair - expected) < 1.0 || abs ((fair - expected) / expected) < 0.017)
          `shouldBe` True
        ) hwDataStudent

    -- No golden reference exists for these (upstream has none either); checks structural
    -- invariants of GaussianLHPLossModel's risk surface on the equity tranche of the CDO
    -- fixture above (correlation 0.1, 100 names) -- an equity tranche (attach = 0) is what
    -- makes "any portfolio loss at all reaches the tranche" a true invariant.
    it "computes tranche-loss risk outputs on a Basket" $ Settings.keepingSettings' $ do
      let refDate = fromGregorian 2006 8 31
          poolSize = 100 :: Int
          names = ["issuer-" ++ show i | i <- [0 .. poolSize - 1]]
          notionals = replicate poolSize 100.0
          recovery = 0.4

      Settings.setEvaluationDate (Just refDate)

      eur <- currency EUR
      key <- northAmericaCorpDefaultKey eur SeniorSec (0, Weeks) 10.0 FullRestructuring
      act360 <- dayCounter (Actual360 False)
      hazardQuote <- simpleQuote 0.01
      dts <- flatHazardRate refDate hazardQuote act360

      iss <- issuer (fromList [(key, dts)])
      p <- pool (fromList [(n, iss, key) | n <- names])

      correlQuote <- simpleQuote 0.1
      lossModel <- gaussianLHPLossModel correlQuote (fromList (replicate poolSize recovery))
      b <- basket refDate (fromList (zip names notionals)) p 0.0 0.03 FaceValue lossModel

      let futureDate = addGregorianYearsClip 5 refDate
          bb = trancheBasketAsBasket b

      -- No default has been recorded on the pool, so the live notional never drops.
      full <- basketNotional bb
      remaining <- basketRemainingNotional bb futureDate
      remaining `shouldBe` full

      -- GaussianLHPLossModel's expectedRecovery is just the recovery quote passed in.
      rr <- basketRecoveryRate bb futureDate 0
      rr `shouldSatisfy` closePrec recovery 1.0e-12

      -- Certain to lose at least 0% of the tranche.
      p0 <- basketProbOverLoss b futureDate 0.0
      p0 `shouldSatisfy` closePrec 1.0 1.0e-6

      -- percentile is a monotone non-decreasing function of its probability argument.
      pctLo <- basketPercentile b futureDate 0.5
      pctHi <- basketPercentile b futureDate 0.95
      pctLo `shouldSatisfy` (<= pctHi)

      -- expected shortfall past a percentile is never below that percentile itself.
      es <- basketExpectedShortfall b futureDate 0.95
      es `shouldSatisfy` (>= pctHi)

    -- Reuses the nth-to-default Gaussian fixture (10 names, correlation 0.3) to check
    -- ConstantLossModel's defaultCorrelation/probAtLeastNEvents on a DigitalBasket. Both
    -- have closed forms at the diagonal/n=0 edge cases (derived above from
    -- DefaultLatentModel::defaultCorrelation/probAtLeastNEvents), so these are exact checks,
    -- not pinned regression values.
    it "computes digital-loss risk outputs on a Basket" $ Settings.keepingSettings' $ do
      let refDate = fromGregorian 2006 8 31
          poolSize = 10 :: Int
          names = ["Name" ++ show i | i <- [0 .. poolSize - 1]]
          namesNotional = 100.0
          recovery = 0.4

      Settings.setEvaluationDate (Just refDate)

      eur <- currency EUR
      key <- northAmericaCorpDefaultKey eur SeniorSec (0, Days) 1.0 FullRestructuring
      dc365 <- dayCounter Actual365FixedStandard
      hazardQuote <- simpleQuote 0.01
      dts <- flatHazardRate refDate hazardQuote dc365

      iss <- issuer (fromList [(key, dts)])
      p <- pool (fromList [(n, iss, key) | n <- names])

      correlQuote <- simpleQuote 0.3
      lossModel <- constantLossModel correlQuote (fromList (replicate poolSize recovery)) GaussianQuadrature []
      b <- digitalBasket refDate (fromList [(n, namesNotional / fromIntegral poolSize) | n <- names]) p 0.0 1.0 FaceValue lossModel

      let futureDate = addGregorianYearsClip 5 refDate

      -- Self-correlation is always 1 (E[1_i*1_i] = p_i, per the closed form).
      selfCorr <- basketDefaultCorrelation b futureDate 0 0
      selfCorr `shouldSatisfy` closePrec 1.0 1.0e-9

      -- Certain to have at least 0 defaults.
      p0 <- basketProbAtLeastNEvents b 0 futureDate
      p0 `shouldSatisfy` closePrec 1.0 1.0e-6

      -- probAtLeastNEvents is non-increasing in n.
      p1 <- basketProbAtLeastNEvents b 1 futureDate
      p2 <- basketProbAtLeastNEvents b 2 futureDate
      (p0 >= p1 && p1 >= p2) `shouldBe` True

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
