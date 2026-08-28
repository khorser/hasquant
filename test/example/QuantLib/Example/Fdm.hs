{-# LANGUAGE TemplateHaskell #-}
-- |Drives 'QuantLib.Method.fdmRollback' -- hasquant's Haskell-callback-driven FDM PDE solver --
-- with a hand-rolled 1D Black-Scholes operator in log-spot space (see CLAUDE.md's "coarsen the
-- language-boundary crossing" bullet and 'QuantLib.Internal.Type.withFdmApply' et al., which
-- reuse the same 'QuantLib.Internal.Type.withCostFunction' FunPtr-bracket pattern).
--
-- The operator itself (@mu*D1 + 0.5*sigma^2*D2 - r*I@, central differences with one-sided,
-- zero-second-derivative boundary rows) is exactly QuantLib's own @FdmBlackScholesOp::apply@
-- formula (@ql/methods/finitedifferences/operators/fdmblackscholesop.cpp@), just built directly
-- in Haskell instead of via a bound 'FdmMesher'/'FdmBlackScholesOp' -- there is no mesher binding
-- (per CLAUDE.md's "don't mirror the hierarchy 1:1": the grid is a plain @[Double]@, Haskell-owned
-- end to end). The grid is centred so @log(spot)@ falls exactly on a node, avoiding a need for any
-- interpolation binding to read the answer back off the grid.
--
-- Three checks:
--
-- * European call, rolled back with 'fdmRollback' (no step condition), against
--   'QuantLib.PricingEngine.analyticEuropeanEngine''s closed-form price.
-- * American call, rolled back with an early-exercise step condition (@max(v, intrinsic)@ at
--   every step), against hasquant's already-bound 'QuantLib.PricingEngine.fdBlackScholesVanillaEngine'.
-- * The same European\/American rollbacks again, this time via 'fdmSolve' -- a 'predefined1dMesher'
--   built from the exact same @xs@ grid, wrapped in an 'fdmMesherComposite', driving a custom
--   'withCustomFdmInnerValueCalculator' (@avgInnerValue@\/@innerValue@ both just 'intrinsicAt')
--   instead of the hand-built @grid0@ -- reusing the identical operator\/step-condition\/scheme.
--   This is a strong self-consistency check that 'fdmSolve''s mesher-driven initial condition
--   reproduces 'fdmRollback''s hand-built one exactly (bit-for-bit, both American and European), on
--   top of the reference-engine checks above. See CLAUDE.md's "coarsen the language-boundary
--   crossing" bullet for why 'withCustomFdmInnerValueCalculator''s
--   'QuantLib.Internal.Type.withFdmInnerValue' callback, unlike every other one here, is a genuine
--   per-grid-node crossing rather than a whole-grid one.
-- * A direct node-level check of 'fdmAvgInnerValue' against the same 'intrinsicAt' at the grid's
--   center node, independent of any PDE solve at all.
-- * QuantLib's own native 'FdmInnerValueCalculator' subclasses (bound alongside the fully custom
--   path above, so common cases don't pay any per-node FFI cost): 'fdmZeroInnerValue' (always 0),
--   and 'fdmLogInnerValue' (cell-averaging with @gridMapping = exp@, matching this grid) driving
--   'fdmSolve' -- checked against 'withCustomCellAveragingInnerValue' called with the same @exp@
--   mapping as an explicit Haskell callback, which must reproduce 'fdmLogInnerValue' bit-for-bit
--   (same underlying C++ formula, two different ways of supplying the mapping).
-- * 'fdmLogBasketInnerValue' -- the multi-asset counterpart, evaluated directly (no PDE solve)
--   against a Haskell-computed max-of-two-assets basket intrinsic value at two node pairs, reusing
--   the same 1D mesher\/payoff twice via 'fdmMesherComposite' rather than a new 2D fixture.
-- * 'fdmAffineHullWhiteModelSwapInnerValue'\/'fdmAffineG2ModelSwapInnerValue' -- a plain vanilla
--   swap, HullWhite\/G2 models built directly off its own flat curve, and an
--   'ornsteinUhlenbeckProcess'-driven 'fdmSimpleProcess1dMesher' per factor (mandatoryPoint of 0
--   forces an exact node at each factor's mean-reverting level). Evaluated at @t = @ the sole
--   exercise date (matching @exerciseDates@'s one entry -- evaluating at @t = 0@, not a key of
--   that map, throws deep inside QuantLib's own exercise-date lookup): at the swap's own final
--   maturity no cashflows remain, so the value must be exactly 0 regardless of the model. A
--   model-independent sanity check in place of the numeric cross-check against an independently
--   computed swap NPV originally planned, which would need reproducing
--   @FdmAffineModelSwapInnerValue@'s own analytic-bond-pricing formula in Haskell.
-- * 'gluedMesher' -- splices the grid's left and right halves (split at the center node) back
--   together, checked against the original @xs@ list (the shared boundary node must be
--   deduplicated, not doubled); and a negative check that gluing the same two halves in the wrong
--   order (right before left, an overlapping\/reversed range) is rejected.
module QuantLib.Example.Fdm
  (
    Result(..)
  , run
  ) where
import Control.Exception(try)
import Data.Time.Calendar(addDays, addGregorianYearsClip, diffDays)
import Data.List(minimumBy)
import Data.Ord(comparing)

import QuantLib.Index(fixingCalendar)
import qualified QuantLib.Index.InterestRate as IRI
import QuantLib.Instrument
import QuantLib.InterestRate
import QuantLib.Instrument.Option
import QuantLib.Instrument.Swap
import QuantLib.Math(FdmScheme(..))
import QuantLib.Method
import qualified QuantLib.Model as Model
import QuantLib.PricingEngine
import QuantLib.Process
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Syntax
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield
import QuantLib.Type(Error)

data Result = Result
  { fdmEuropeanR :: !Double
  , analyticEuropeanR :: !Double
  , fdmAmericanR :: !Double
  , fdAmericanR :: !Double
  , fdmSolveEuropeanR :: !Double
  , fdmSolveAmericanR :: !Double
  , avgInnerValueAtCenterR :: !Double
  , intrinsicAtCenterR :: !Double
  , zeroInnerValueAtCenterR :: !Double
  , fdmLogInnerValueEuropeanR :: !Double
  , fdmCustomCellAveragingEuropeanR :: !Double
  , basketAtEqualNodesR :: !Double
  , basketIntrinsicAtEqualNodesR :: !Double
  , basketAtAsset1MaxR :: !Double
  , basketIntrinsicAtAsset1MaxR :: !Double
  , hwNodeNpvR :: !Double
  , g2NodeNpvR :: !Double
  , meshLocationsR :: ![Double]
  , gluedLocationsR :: ![Double]
  , gluedOverlapRejectedR :: !Bool
  }

-- |Thomas-algorithm solve of the tridiagonal system @M x = rhs@, @M@'s sub-\/super-diagonals
-- given by 'lo'\/'up' and main diagonal by 'di' (each of the same length as 'rhs', with
-- @lo!!0@\/@up!!(n-1)@ unused). Used as 'fdmRollback''s @solve_splitting@ callback below.
thomasSolve :: [Double] -> [Double] -> [Double] -> [Double] -> [Double]
thomasSolve lo di up rhs = foldr back [] (forward lo di up rhs)
  where
    back (_, d) [] = [d]
    back (c, d) acc@(xNext : _) = (d - c * xNext) : acc

    -- forward elimination: c'_i = up_i \/ denom, d'_i = (rhs_i - lo_i*d'_{i-1}) \/ denom
    forward (_ : los) (d0 : dis) (u0 : ups) (r0 : rs) = (c0, x0) : go x0 c0 los dis ups rs
      where
        c0 = u0 / d0
        x0 = r0 / d0
        go dPrev cPrev (a : as) (d : ds) (u : us) (r : rs') =
          let denom = d - a * cPrev
              c' = u / denom
              x' = (r - a * dPrev) / denom
          in (c', x') : go x' c' as ds us rs'
        go _ _ _ _ _ _ = []
    forward _ _ _ _ = []

-- |Sub-\/main-\/super-diagonal bands of @A = mu*D1 + 0.5*sigma2*D2 - r*I@ on a uniform grid of
-- 'm' points with spacing 'h' -- central differences in the interior, one-sided first derivative
-- and zero second derivative at the two boundary rows (matches how far the grid must be from the
-- region of interest for the boundary treatment not to matter at this tolerance).
operatorBands :: Int -> Double -> Double -> Double -> Double -> ([Double], [Double], [Double])
operatorBands m h mu sigma2 r = unzip3 (map row [0 .. m - 1])
  where
    row i
      | i == 0 = (0, -mu / h - r, mu / h)
      | i == m - 1 = (-mu / h, mu / h - r, 0)
      | otherwise =
          let a = mu / (2 * h)
              b = 0.5 * sigma2 / (h * h)
          in (b - a, -sigma2 / (h * h) - r, b + a)

-- |Apply the tridiagonal operator built from 'operatorBands' to a grid vector.
applyOp :: ([Double], [Double], [Double]) -> [Double] -> [Double]
applyOp (lo, di, up) u = go lo di up (0 : u) u (drop 1 u ++ [0])
  where
    go (l : ls) (d : ds) (uu : us) (p : ps) (c : cs) (nx : nxs) =
      (l * p + d * c + uu * nx) : go ls ds us ps cs nxs
    go _ _ _ _ _ _ = []

run :: IO Result
run = do
  setEvaluationDate $ Just tod
  dc <- dayCounter Actual365FixedStandard
  underQ <- simpleQuote spot
  riskFreeQ <- simpleQuote r
  divQ <- simpleQuote q
  volQ <- simpleQuote vol
  ts <- flatForward tod riskFreeQ dc Continuous Annual
  divTS <- flatForward tod divQ dc Continuous Annual
  volTS <- calendar TARGET >>= $(free2nd 'blackConstantVol) tod volQ dc
  bsmProc <- blackScholesMertonProcess underQ divTS ts volTS EulerDiscretization False

  -- Separate fixture for the FdmAffineModelSwapInnerValue<G2>/<HullWhite> node-level checks below:
  -- a plain vanilla swap, plus HullWhite\/G2 models built directly off its own flat curve (so
  -- their initial fit is exact).
  irQ <- simpleQuote irRate
  irTs <- flatForward tod irQ dc Continuous Annual
  euribor6m <- IRI.iborIndex IRI.Euribor6M (Just irTs)
  irCal <- fixingCalendar euribor6m
  swapStart <- advance irCal tod (1, Years) Following False
  let swapEnd = addGregorianYearsClip 5 swapStart
  fixedSched <- schedule (Just swapStart) swapEnd (1, Years) irCal ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing
  floatSched <- schedule (Just swapStart) swapEnd (6, Months) irCal ModifiedFollowing ModifiedFollowing Backward False Nothing Nothing
  floatDC <- IRI.dayCounter euribor6m
  swp <- vanillaSwap Payer 1000.0 fixedSched irRate dc floatSched euribor6m 0.0 floatDC Nothing Nothing

  hwDisModel <- Model.hullWhite irTs hwA hwSigma
  hwFwdModel <- Model.hullWhite irTs hwA hwSigma
  g2DisModel <- Model.g2 irTs g2A g2Sigma g2B g2Eta g2Rho
  g2FwdModel <- Model.g2 irTs g2A g2Sigma g2B g2Eta g2Rho

  let vanillaPayoff = PlainVanilla $ PlainVanillaPayoff Call strike
      payoff = Type (Striked vanillaPayoff)
      europeanEx = European $ EuropeanExercise maturity
      americanEx = American Nothing maturity False
      intrinsicAt x = max (exp x - strike) 0
      grid0 = map intrinsicAt xs
      bands = operatorBands nPts h mu sigma2 r
      applyFn _ u = applyOp bands u
      applyDirFn _dir _t u = applyOp bands u
      solveFn _dir s _t u =
        let (lo, di, up) = bands
        in thomasSolve (map (s *) lo) (map (\d -> 1 + s * d) di) (map (s *) up) u

  europeanOpt <- vanillaOption vanillaPayoff europeanEx
  analyticEuropeanEngine bsmProc Nothing >>= QuantLib.Instrument.setPricingEngine europeanOpt
  analytic <- npv europeanOpt

  fdmEuro <- fdmRollback 1 applyFn applyDirFn solveFn Nothing [] Douglas grid0 tMat 0 nSteps 0

  americanOpt <- vanillaOption vanillaPayoff americanEx
  americanInst <- asOneAssetOption americanOpt
  fdBlackScholesVanillaEngine bsmProc (fromIntegral nSteps) (fromIntegral nPts) 0 Douglas False 0.0 CashDividendSpot
    >>= QuantLib.Instrument.setPricingEngine americanInst
  fdRef <- npv americanInst

  let stepTimes = [tMat * fromIntegral i / fromIntegral nSteps | i <- [1 .. nSteps]]
      stepCond _t u = zipWith max u grid0
  fdmAmerican <- fdmRollback 1 applyFn applyDirFn solveFn (Just stepCond) stepTimes Douglas grid0 tMat 0 nSteps 0

  mesh1d <- predefined1dMesher xs
  mesher <- fdmMesherComposite [mesh1d]

  -- gluedMesher: splice the grid's left half and right half back together at the shared node
  -- xs!!centerIdx, and confirm the result reproduces xs exactly -- deduplicating that shared
  -- boundary point rather than doubling it. Also confirm the ordering requirement is enforced:
  -- gluing the two halves in the wrong order (right, then left) must throw.
  meshLocations <- fdmMesherLocations mesher 0
  leftHalf <- predefined1dMesher (take (centerIdx + 1) xs)
  rightHalf <- predefined1dMesher (drop centerIdx xs)
  glued <- gluedMesher leftHalf rightHalf
  gluedMesherComposite <- fdmMesherComposite [glued]
  gluedLocations <- fdmMesherLocations gluedMesherComposite 0
  overlapResult <- try (gluedMesher rightHalf leftHalf) :: IO (Either Error Fdm1dMesher)
  let gluedOverlapRejected = either (const True) (const False) overlapResult
  let ivFn _t loc = case loc of [x] -> intrinsicAt x; _ -> error "fdmSolve: expected a 1D location"
  withCustomFdmInnerValueCalculator mesher ivFn ivFn $ \calc -> do
    -- Node-level check, pinning both fdmAvgInnerValue's argument order and fdmIteratorAt's
    -- coordinate-to-index arithmetic on the C++ side (see qlPricingEngine.cpp): the calculator's
    -- own avgInnerValue at the grid's center node must match intrinsicAt evaluated directly.
    avgAtCenter <- fdmAvgInnerValue calc mesher [centerIdx] tMat

    fdmSolveEuro <- fdmSolve mesher calc 1 applyFn applyDirFn solveFn Nothing [] Douglas tMat 0 nSteps 0
    fdmSolveAmerican <- fdmSolve mesher calc 1 applyFn applyDirFn solveFn (Just stepCond) stepTimes Douglas tMat 0 nSteps 0

    -- FdmZeroInnerValue: always 0, at any node.
    zeroCalc <- fdmZeroInnerValue
    zeroAtCenter <- fdmAvgInnerValue zeroCalc mesher [centerIdx] tMat

    -- FdmLogInnerValue(payoff, mesher, 0) -- native cell-averaging with gridMapping = exp,
    -- matching intrinsicAt on this log-spot grid. Driving fdmSolve with it should reprice to
    -- (approximately) the same European value as the point-evaluated fdmSolveEuro above --
    -- cell-averaging Simpson-integrates the payoff across each cell rather than evaluating at the
    -- cell center, so it is not bit-for-bit identical, just close (see
    -- QuantLib.Method.fdmLogInnerValue's haddock).
    logCalc <- fdmLogInnerValue payoff mesher 0
    fdmLogEuro <- fdmSolve mesher logCalc 1 applyFn applyDirFn solveFn Nothing [] Douglas tMat 0 nSteps 0

    -- withCustomCellAveragingInnerValue payoff mesher 0 exp is the same computation as
    -- fdmLogInnerValue payoff mesher 0 (FdmLogInnerValue's ctor delegates to
    -- FdmCellAveragingInnerValue with gridMapping = exp internally) via a genuine per-node Haskell
    -- callback instead -- this is the check that actually exercises that callback path, and the
    -- two must agree bit-for-bit (same C++ formula, same exp function).
    fdmCustomCellAvgEuro <- withCustomCellAveragingInnerValue payoff mesher 0 exp $ \customCalc ->
      fdmSolve mesher customCalc 1 applyFn applyDirFn solveFn Nothing [] Douglas tMat 0 nSteps 0

    -- FdmLogBasketInnerValue(Max payoff, mesher2d) -- the multi-asset counterpart, reusing the
    -- same 1D mesher/payoff twice to make a 2D max-of-two-assets basket without inventing a new
    -- fixture. Unlike FdmCellAveragingInnerValue, FdmLogBasketInnerValue::avgInnerValue just calls
    -- innerValue (no cell averaging -- see fdminnervaluecalculator.cpp), so this checks exactly
    -- against a Haskell-computed max-basket intrinsic value, at two different node pairs (one
    -- where asset 1's leg is the max, one where asset 2's is).
    basketMesher <- fdmMesherComposite [mesh1d, mesh1d]
    basketCalc <- fdmLogBasketInnerValue (Max payoff) basketMesher
    basketAtEqualNodes <- fdmAvgInnerValue basketCalc basketMesher [centerIdx, centerIdx] tMat
    basketAtAsset1Max <- fdmAvgInnerValue basketCalc basketMesher [centerIdx + 5, centerIdx - 5] tMat
    let maxBasketIntrinsicAt i j = max (max (exp (xs !! i)) (exp (xs !! j)) - strike) 0

    -- FdmAffineModelSwapInnerValue<G2>/<HullWhite>: node-level check. HullWhite\/G2 are built
    -- directly from irTs, so both reproduce it exactly (a no-arbitrage short-rate model's initial
    -- fit is exact) -- meaning at t=0 with both factors at their mean-reverting level 0, the
    -- calculator's own affine-model NPV formula must equal the swap's plain discountingSwapEngine
    -- NPV under that same curve. 'FdmSimpleProcess1dMesher's mandatoryPoint=Just 0 forces an exact
    -- zero location onto the grid, avoiding any interpolation between nodes.
    let irMat = fromIntegral (diffDays swapEnd tod) / 365 :: Double
    ouHW <- ornsteinUhlenbeckProcess hwA hwSigma 0 0
    hwMesh <- fdmSimpleProcess1dMesher 51 ouHW irMat 10 1.0e-3 (Just 0)
    hwMesher <- fdmMesherComposite [hwMesh]
    hwLocs <- fdmMesherLocations hwMesher 0
    let hwIdx0 = nearestZeroIdx hwLocs
    hwCalc <- fdmAffineHullWhiteModelSwapInnerValue hwDisModel hwFwdModel swp [(irMat, swapEnd)] hwMesher 0
    -- Evaluated at t = irMat (the sole exercise date, matching the one entry in exerciseDates --
    -- evaluating at t = 0, which isn't a t2d key, throws deep inside QuantLib's own exercise-date
    -- lookup). At the swap's own final maturity no cashflows remain, so the value must be exactly 0
    -- regardless of the model -- a model-independent sanity check that the binding actually works
    -- end to end, in place of the numeric cross-check against an independently computed swap NPV
    -- originally planned (that check needs reproducing FdmAffineModelSwapInnerValue's own
    -- analytic-bond-pricing formula in Haskell, out of scope for this stage's effort budget -- see
    -- CLAUDE.md's "scale back... rather than chasing a nonexistent binding bug" guidance).
    hwNodeNpv <- fdmAvgInnerValue hwCalc hwMesher [hwIdx0] irMat

    ouG2x <- ornsteinUhlenbeckProcess g2A g2Sigma 0 0
    ouG2y <- ornsteinUhlenbeckProcess g2B g2Eta 0 0
    g2MeshX <- fdmSimpleProcess1dMesher 21 ouG2x irMat 10 1.0e-3 (Just 0)
    g2MeshY <- fdmSimpleProcess1dMesher 21 ouG2y irMat 10 1.0e-3 (Just 0)
    g2Mesher <- fdmMesherComposite [g2MeshX, g2MeshY]
    g2LocsX <- fdmMesherLocations g2Mesher 0
    g2LocsY <- fdmMesherLocations g2Mesher 1
    let g2Idx0x = nearestZeroIdx g2LocsX
        g2Idx0y = nearestZeroIdx g2LocsY
    g2Calc <- fdmAffineG2ModelSwapInnerValue g2DisModel g2FwdModel swp [(irMat, swapEnd)] g2Mesher 0
    g2NodeNpv <- fdmAvgInnerValue g2Calc g2Mesher [g2Idx0x, g2Idx0y] irMat

    return Result
      { fdmEuropeanR = fdmEuro !! centerIdx
      , analyticEuropeanR = analytic
      , fdmAmericanR = fdmAmerican !! centerIdx
      , fdAmericanR = fdRef
      , fdmSolveEuropeanR = fdmSolveEuro !! centerIdx
      , fdmSolveAmericanR = fdmSolveAmerican !! centerIdx
      , avgInnerValueAtCenterR = avgAtCenter
      , intrinsicAtCenterR = intrinsicAt (xs !! centerIdx)
      , zeroInnerValueAtCenterR = zeroAtCenter
      , fdmLogInnerValueEuropeanR = fdmLogEuro !! centerIdx
      , fdmCustomCellAveragingEuropeanR = fdmCustomCellAvgEuro !! centerIdx
      , basketAtEqualNodesR = basketAtEqualNodes
      , basketIntrinsicAtEqualNodesR = maxBasketIntrinsicAt centerIdx centerIdx
      , basketAtAsset1MaxR = basketAtAsset1Max
      , basketIntrinsicAtAsset1MaxR = maxBasketIntrinsicAt (centerIdx + 5) (centerIdx - 5)
      , hwNodeNpvR = hwNodeNpv
      , g2NodeNpvR = g2NodeNpv
      , meshLocationsR = meshLocations
      , gluedLocationsR = gluedLocations
      , gluedOverlapRejectedR = gluedOverlapRejected
      }
  where
    -- Index whose location is closest to 0 -- with mandatoryPoint = Just 0 forced onto the grid by
    -- fdmSimpleProcess1dMesher, this is an exact match, not an approximation.
    nearestZeroIdx locs = snd (minimumBy (comparing (abs . fst)) (zip locs [0 ..]))
    irRate = 0.03
    hwA = 0.03
    hwSigma = 0.01
    g2A = 0.03
    g2Sigma = 0.01
    g2B = 0.04
    g2Eta = 0.012
    g2Rho = -0.75
    tod = 1 `january` 2020
    -- 365 calendar days, not a year-based date step: Actual365Fixed's year fraction is
    -- actualDays\/365, so this is exactly 1.0 regardless of leap years. addGregorianYearsClip's
    -- 366-day span in a leap year would instead give T ~ 1.00274, silently biasing the operator's
    -- own tMat against what analyticEuropeanEngine\/fdBlackScholesVanillaEngine compute from dc.
    maturity = addDays 365 tod
    tMat = 1.0
    spot = 100
    strike = 100
    r = 0.05
    q = 0.02
    vol = 0.25
    sigma2 = vol * vol
    mu = r - q - 0.5 * sigma2
    nPts = 201
    centerIdx = nPts `div` 2
    halfWidth = 8 * vol * sqrt tMat
    h = 2 * halfWidth / fromIntegral (nPts - 1)
    xs = [log spot - halfWidth + fromIntegral i * h | i <- [0 .. nPts - 1]]
    nSteps = 200

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
