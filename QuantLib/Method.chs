-- |Monte Carlo path generation ('pathGenerator'\/'sobolPathGenerator'\/'next'\/'asset') plus
-- 'lsmRegress', a standalone Longstaff-Schwartz early-exercise regression primitive.
--
-- === Custom early exercise with a Haskell payoff
--
-- 'lsmRegress' lets a Haskell-defined payoff drive early exercise, something no bound pricing
-- engine offers: every early-exercise engine in "QuantLib.PricingEngine" (e.g.
-- @mcAmericanEngine@) computes its payoff entirely on the C++ side against a bound @Payoff@.
-- 'lsmRegress' is pure regression -- it never sees a payoff at all, so it works for any
-- underlying-state-dependent early-exercise payoff, not just a vanilla put\/call. The pattern,
-- worked in full in @test\/example\/QuantLib\/Example\/AmericanLSM.hs@:
--
-- 1. Draw two path sets with 'pathGenerator': a /calibration/ set used only to fit each date's
--    regression, and a separate /pricing/ set evaluated against the frozen fit. Splitting the
--    sets avoids the in-sample bias a single-pass fit-and-price would have (the same reason
--    @mcAmericanEngine@ exposes its own @nCalibrationSamples@ parameter). Use a fixed nonzero
--    seed for each -- seed @0@ means \"seed from entropy\" for 'PseudoRandom'.
-- 2. Read out the state at every exercise date, across all paths, with 'asset' (or 'assetAt'),
--    and transpose ('Data.List.transpose') into one state list per exercise date.
-- 3. Walk exercise dates *strictly backward*. At each date:
--
--     * discount both the calibration and pricing cashflow vectors by the one-step discount
--       factor (@discount(t[i+1]) \/ discount(t[i])@ from the underlying yield curve);
--     * compute the Haskell payoff at this date for every path in both sets;
--     * restrict the regression's fit inputs to *in-the-money calibration paths only*
--       (@fitStates@\/@fitTargets@ below);
--     * call 'lsmRegress' twice against that one fit -- once evaluating at the calibration
--       states (to keep the backward recursion's own targets self-consistent), once at the
--       pricing states (the actual out-of-sample continuation-value estimate);
--     * exercise wherever @payoff > continuationValue@ (@max(exercise, continuation)@), on each
--       path set independently.
--
-- 4. The pricing set's cashflows, discounted all the way back and averaged, are the estimated
--    price. Never evaluate the fit on the calibration set's own state for the reported price --
--    that reintroduces the in-sample bias step 1 split the paths to avoid.
--
-- A rough sketch (see the full example for discounting, ITM filtering, and the backward
-- recursion itself):
--
-- > step df calibS priceS calibCF priceCF = do
-- >   let calibTargets = map (* df) calibCF  -- discount to this date
-- >       (fitStates, fitTargets) = -- ITM calibration paths only
-- >         unzip $ filter (inTheMoney . fst) $ zip calibS calibTargets
-- >   contCalib <- lsmRegress Monomial order fitStates fitTargets calibS
-- >   contPrice <- lsmRegress Monomial order fitStates fitTargets priceS
-- >   -- exercise wherever payoff > continuation, on each path set
-- >   ...
--
-- Validated in the example against both @mcAmericanEngine@ pricing the equivalent bound vanilla
-- option (same process\/grid\/seed) and the published Longstaff-Schwartz (2001) reference value
-- for the same benchmark fixture.
--
-- The same pattern extends to a Haskell-defined /basket/ payoff (several correlated underlyings)
-- via 'lsmRegressMulti' \/ 'lsmBasisSize' in place of 'lsmRegress': read each exercise date's state
-- for every underlying (still with 'asset'\/'assetAt', once per underlying) into a 'Matrix' of one
-- row per path, and guard the ITM-fit-size check with 'lsmBasisSize' instead of the basis order --
-- the multi-asset basis has combinatorially many more terms than the scalar case.
--
-- === Finite-difference PDE solving
--
-- This module also binds a full-grid finite-difference (FDM) driver, built up across two related
-- issues (custom step-condition\/operator hooks, then custom inner-value calculators) and spread
-- across several functions with no single overview until now. Worked in full in
-- @test\/example\/QuantLib\/Example\/Fdm.hs@.
--
-- [@Rolling a grid back@] 'fdmRollback' takes a precomputed initial grid (a plain @[Double]@) and
--   rolls it back through time via three Haskell-defined operator callbacks
--   ('QuantLib.Internal.Type.withFdmApply' et al.) plus an optional step condition (e.g.
--   American\/Bermudan early exercise). These callbacks cross the language boundary once per outer
--   timestep, over the /whole/ grid -- CLAUDE.md's \"coarsen the language-boundary crossing\"
--   pattern. 'fdmSolve' is the sibling that instead derives its own initial grid from a mesher and
--   an 'FdmInnerValueCalculator' (below), reusing the same operator\/step-condition machinery.
--
-- [@Building a grid@] 'Fdm1dMesher's ('predefined1dMesher', 'uniform1dMesher',
--   'concentrating1dMesher', 'fdmBlackScholesMesher', and the other process-specific meshers) each
--   describe one PDE dimension; 'fdmMesherComposite' combines one or more into the multi-dimensional
--   'FdmMesher' 'fdmSolve' and 'FdmInnerValueCalculator' operate over. 'fdmMesherLocations' reads a
--   dimension's real-valued node locations back out, e.g. to map a flat result array back to
--   coordinates.
--
-- [@Custom inner values, fully general@] 'withCustomFdmInnerValueCalculator' wraps a Haskell
--   @t -> location -> value@ pair of functions as an 'FdmInnerValueCalculator'. Unlike every
--   callback above, this one crosses the language boundary once /per grid node/ -- there is no
--   batched shape for it anywhere in QuantLib or QuantLib-SWIG, so the real per-call cost is
--   accepted, matching QuantLib-SWIG's own @FdmInnerValueCalculatorDelegate@ precedent. Because the
--   two callbacks are stored /inside/ the returned calculator and invoked again on every later
--   'fdmSolve'\/'fdmInnerValue' call (not just during construction), the calculator is only valid
--   /inside/ this continuation -- it cannot be built with a plain @IO FdmInnerValueCalculator@
--   smart constructor the way the native calculators below can.
--
-- [@Custom inner values, native@] QuantLib's own concrete 'FdmInnerValueCalculator' subclasses are
--   bound directly, for the common cases that don't need a per-node Haskell callback at all:
--   'fdmZeroInnerValue' (always 0), 'fdmCellAveragingInnerValue'\/'fdmLogInnerValue' (a payoff
--   cell-averaged -- Simpson-integrated across each grid cell, not just evaluated at its center --
--   with an identity or @exp@ value mapping respectively), and 'fdmLogBasketInnerValue' (the
--   multi-asset counterpart, one @exp@ mapping per dimension). These hold no Haskell callback, so
--   they're plain @IO FdmInnerValueCalculator@ constructors -- except
--   'withCustomCellAveragingInnerValue', the one native constructor that /does/ take an explicit
--   @gridMapping@ callback, which needs the same continuation treatment as the fully custom case
--   above. 'fdmAffineG2ModelSwapInnerValue'\/'fdmAffineHullWhiteModelSwapInnerValue' price a swap
--   under a calibrated 'QuantLib.Model.G2'\/'QuantLib.Model.HullWhite' model directly -- the same
--   calculator @fdG2SwaptionEngine@\/@fdHullWhiteSwaptionEngine@ use internally.
--
-- [@Inspecting a calculator directly@] 'fdmInnerValue'\/'fdmAvgInnerValue' evaluate any bound
--   calculator (custom or native) at a single mesher node, without assembling a whole 'fdmSolve' --
--   useful for a targeted self-consistency check, as @Fdm.hs@'s own tests do throughout.
module QuantLib.Method
  (
    PathGenerator
  , SamplePath
  , pathGenerator
  , sobolPathGenerator
  , next
  , antithetic
  , weight
  , assetNumber
  , pathSize
  , assetAt
  , asset
  , asset'
  , lsmRegress
  , lsmBasisSize
  , lsmRegressMulti
  , fdmRollback
  , Fdm1dMesher
  , FdmMesher
  , predefined1dMesher
  , uniform1dMesher
  , concentrating1dMesher
  , concentrating1dMesherMulti
  , fdmBlackScholesMesher
  , fdmCev1dMesher
  , exponentialJump1dMesher
  , fdmSimpleProcess1dMesher
  , fdmHestonVarianceMesher
  , fdmHestonLocalVolatilityVarianceMesher
  , fdmMesherComposite
  , fdmMesherLocations
  , FdmInnerValueCalculator
  , withCustomFdmInnerValueCalculator
  , fdmZeroInnerValue
  , fdmCellAveragingInnerValue
  , withCustomCellAveragingInnerValue
  , fdmLogInnerValue
  , fdmLogBasketInnerValue
  , fdmAffineG2ModelSwapInnerValue
  , fdmAffineHullWhiteModelSwapInnerValue
  , fdmInnerValue
  , fdmAvgInnerValue
  , fdmSolve
  ) where
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

import QuantLib.Internal
import QuantLib.Internal.Type
import QuantLib.Internal.Common
{#import QuantLib.Math#}
import Foreign.C.Types(CDouble, CUInt)
import Foreign.C.String(CString)
import Foreign.Ptr(Ptr, FunPtr)
import Data.Time.Calendar(Day)
import Data.Vector.Storable(Vector)

{#pointer *PolymorphicPathGenerator as PathGenerator foreign -> CPathGenerator nocode#}
{#pointer *SamplePath as SamplePath foreign -> CSamplePath nocode#}
{#pointer *QlStochasticProcess as StochasticProcess foreign -> CStochasticProcess' nocode#}
-- Local redeclaration needed for fdmRollback's FdmScheme argument -- c2hs's cross-module enum\/
-- pointer-type import needs the pointee type known in *this* file (see the c2hs-shim-patterns
-- skill's "Cross-module enum imports" section); QuantLib.PricingEngine has the same declaration.
{#pointer *FdmSchemeDesc as QlFdmSchemeDesc foreign -> CFdmSchemeDesc nocode#}
-- Local redeclarations for the mesher-constructor argument types, same reasoning as
-- FdmSchemeDesc above -- QuantLib.PricingEngine has the same declarations.
{#pointer *QlDividend as Dividend foreign -> CDividend nocode#}
{#pointer *QlGeneralizedBlackScholesProcess as GeneralizedBlackScholesProcess foreign -> CGeneralizedBlackScholesProcess' nocode#}
{#pointer *QlStochasticProcess1D as StochasticProcess1D foreign -> CStochasticProcess1D' nocode#}
{#pointer *QlHestonProcess as HestonProcess foreign -> CHestonProcess' nocode#}
{#pointer *QlLocalVolTermStructure as LocalVolTermStructure foreign -> CLocalVolTermStructure' nocode#}
{#pointer *QlFdmQuantoHelper as FdmQuantoHelper foreign -> CFdmQuantoHelper nocode#}
-- Local redeclaration for Payoff arguments (fdmCellAveragingInnerValue/fdmLogInnerValue/
-- fdmLogBasketInnerValue), same reasoning as the redeclarations above -- QuantLib.Internal.Common
-- has the same declaration.
{#pointer *QlPayoff nocode#}
{#pointer *QlBasketPayoff nocode#}
-- Local redeclarations for fdmAffineG2ModelSwapInnerValue/fdmAffineHullWhiteModelSwapInnerValue's
-- argument types, same reasoning as the redeclarations above -- QuantLib.Model and
-- QuantLib.Instrument.Swap have the same declarations.
{#pointer *QlG2 as G2 foreign -> CG2' nocode#}
{#pointer *QlHullWhite as HullWhite foreign -> CHullWhite' nocode#}
{#pointer *QlFixedVsFloatingSwap as FixedVsFloatingSwap foreign -> CFixedVsFloatingSwap' nocode#}
{#pointer *QlFdm1dMesher as Fdm1dMesher foreign -> CFdm1dMesher nocode#}
{#pointer *QlFdmMesher as FdmMesher foreign -> CFdmMesher nocode#}
{#pointer *QlFdmInnerValueCalculator as FdmInnerValueCalculator foreign -> CFdmInnerValueCalculator nocode#}

-- |build a multi-asset path generator driven by a pseudo-random number generator (Mersenne Twister, Poisson, or Ziggurat, chosen by the RNG trait) over the given process and time grid.
{#fun qlPathGenerator as pathGenerator{fromEnumC`RngTrait',withStochasticProcess*`GenStochasticProcess p',withTimeGrid*`TimeGrid'
  ,fromIntegral`Word' -- ^seed
  ,fromIntegral`Word' -- ^dimension
  ,`Bool' -- ^brownian bridge
  ,preErrorCheck-`String'errorCheck*-}->`PathGenerator'peekPathGenerator*#}

-- |build a multi-asset path generator driven by a low-discrepancy (Sobol) sequence, using the given direction integers, over the given process and time grid.
{#fun qlSobolPathGenerator as sobolPathGenerator{fromEnumC`SobolDirectionIntegers',withStochasticProcess*`GenStochasticProcess p',withTimeGrid*`TimeGrid'
  ,fromIntegral`Word' -- ^seed
  ,fromIntegral`Word' -- ^dimension
  ,`Bool' -- ^brownian bridge
  ,preErrorCheck-`String'errorCheck*-}->`PathGenerator'peekPathGenerator*#}

-- |draw the next weighted sample path from the generator.
{#fun qlPathGeneratorNext as next{withPathGenerator*`PathGenerator',preErrorCheck-`String'errorCheck*-}->`SamplePath'peekSamplePath*#}

-- |draw the antithetic (sign-flipped) counterpart of the last drawn sample path.
{#fun qlPathGeneratorAntithetic as antithetic{withPathGenerator*`PathGenerator',preErrorCheck-`String'errorCheck*-}->`SamplePath'peekSamplePath*#}

-- |the weight associated with a sample path.
{#fun pure qlSamplePathWeight as weight{withSamplePath*`SamplePath'}->`Double'#}

-- |the number of correlated asset paths in a sample.
{#fun pure qlSamplePathAssetNumber as assetNumber{withSamplePath*`SamplePath'}->`Word'fromIntegral#}

-- |the number of time steps in each asset path of a sample.
{#fun pure qlSamplePathSize as pathSize{withSamplePath*`SamplePath'}->`Word'fromIntegral#}

-- |the value of one asset's path at a given time step.
{#fun qlSamplePathAt as assetAt{withSamplePath*`SamplePath',fromIntegral`Word' -- ^asset
  ,fromIntegral`Word' -- ^point
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the full simulated path (values at every time step) of a single asset, as a list.
{#fun qlSamplePathAssetPath as asset{withSamplePath*`SamplePath',fromIntegral`Word',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |the full simulated path (values at every time step) of a single asset, as a storable vector.
{#fun qlSamplePathAssetPath as asset'{withSamplePath*`SamplePath',fromIntegral`Word',preArray-`Vector CDouble'&peekDoubleVector*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |one step of Longstaff-Schwartz early-exercise regression: fit a polynomial basis of the given
-- order/type against the (in-the-money) fit states and their continuation targets, then evaluate the
-- fitted continuation value at each of the given eval states. This is the same per-exercise-date
-- regression @LongstaffSchwartzPathPricer@ performs internally against a bound @Payoff@, exposed so it
-- can be driven from a Haskell-defined payoff instead: call it once per exercise date, walking dates
-- strictly backward, batched across all paths rather than per path. See this module's header for the
-- full backward-induction pattern.
{#fun qlLsmRegress as lsmRegress{`PolynomialType',fromIntegral`Word' -- ^basis order
  ,withDoubleArray*`[Double]'& -- ^fit states (in-the-money paths only)
  ,withDoubleArray*`[Double]'& -- ^fit targets (continuation value at these states)
  ,withDoubleArray*`[Double]'& -- ^eval states (all paths' state at this date)
  ,preArray-`[Double]'&peekDoubleArray* -- ^continuation value estimate per eval state
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |number of basis terms 'lsmRegressMulti' fits for a given number of underlyings and order --
-- @C(dim+order, order)@, the binomial coefficient @LsmBasisSystem::multiPathBasisSystem@ actually
-- returns (not @order+1@, which only coincides at @dim=1@ -- 'lsmRegress' uses that special case
-- directly rather than calling this). Use it to size the \"enough in-the-money calibration paths to
-- fit\" guard before calling 'lsmRegressMulti': the underlying least-squares solve requires at least
-- this many fit rows, and undershooting it throws rather than returning a degenerate fit.
lsmBasisSize :: Word -> Word -> Word
lsmBasisSize dim order = fromInteger $ binomial (toInteger dim + toInteger order) (toInteger order)
  where binomial n k = product [n - k + 1 .. n] `div` product [1 .. k]

-- |multi-asset counterpart of 'lsmRegress', for a Haskell-defined basket (several correlated
-- underlyings) early-exercise payoff -- 'lsmRegress' itself only regresses against one state
-- variable. Fit\/eval states are 'Matrix' rows: one row per path, one column per underlying, and the
-- two matrices' column counts must agree. Regresses against
-- @LsmBasisSystem::multiPathBasisSystem@'s combinatorial basis; see 'lsmBasisSize' for its size and
-- this module's header for the surrounding backward-induction pattern (identical to the scalar case,
-- just with 'Matrix'-shaped states).
lsmRegressMulti :: PolynomialType -> Word -> Matrix Double -- ^fit states (in-the-money paths only)
  -> [Double] -- ^fit targets (continuation value at these states)
  -> Matrix Double -- ^eval states (all paths' state at this date)
  -> IO [Double] -- ^continuation value estimate per eval row
lsmRegressMulti p order (Matrix fr fc fd) t (Matrix er ec ed) = qlLsmRegressMulti p order fr fc fd t er ec ed
{#fun qlLsmRegressMulti{`PolynomialType',fromIntegral`Word' -- ^basis order
  ,fromIntegral`Word' -- ^fit rows
  ,fromIntegral`Word' -- ^fit columns (underlyings)
  ,withDoubleArrayRaw*`[Double]' -- ^fit states, row-major
  ,withDoubleArray*`[Double]'& -- ^fit targets
  ,fromIntegral`Word' -- ^eval rows
  ,fromIntegral`Word' -- ^eval columns (underlyings)
  ,withDoubleArrayRaw*`[Double]' -- ^eval states, row-major
  ,preArray-`[Double]'&peekDoubleArray* -- ^continuation value estimate per eval row
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Drive @FdmBackwardSolver::rollback@ with a Haskell-defined 'FdmLinearOpComposite' (the
-- @apply@\/@apply_direction@\/@solve_splitting@ callbacks) and an optional Haskell-defined step
-- condition (e.g. American\/Bermudan early exercise, or a barrier), instead of a bound mesher +
-- @FdmInnerValueCalculator@ as every concrete FDM pricing engine in "QuantLib.PricingEngine"
-- uses. This is the coarsened-callback shape from CLAUDE.md's \"coarsen the language-boundary
-- crossing\" bullet, modeled on QuantLib-SWIG's @FdmLinearOpCompositeDelegate@\/
-- @FdmStepConditionDelegate@ (@SWIG\/fdm.i@): each callback crosses once per outer iteration over
-- the whole grid array, not once per grid node.
--
-- The grid is a plain @[Double]@ in and out -- no mesher, no @FdmInnerValueCalculator@, no
-- @FdmSolverDesc@ is bound; callers manage their own grid geometry entirely in Haskell. Boundary
-- conditions are always the empty @FdmBoundaryConditionSet()@ (not bound).
--
-- /Only DouglasScheme::step's three virtuals are implemented -- 'apply', 'apply_direction' and/
-- /'solve_splitting'; @apply_mixed@\/@preconditioner@ are unimplemented and @QL_FAIL@ at the C++/
-- /level if called./ This makes 'fdmRollback' safe to drive with 'QuantLib.Internal.Common.Douglas'
-- or 'QuantLib.Internal.Common.CrankNicolson' in one dimension (the two schemes
-- @DouglasScheme::step@ itself is used for) -- anything needing mixed derivatives across more than
-- one PDE direction (Craig-Sneyd, Hundsdorfer, or any genuinely multi-dimensional operator) will
-- throw partway through 'fdmRollback' rather than silently mispricing.
{#fun qlFdmRollback as fdmRollback{fromIntegral`Int' -- ^number of PDE directions\/dimensions the operator has (e.g. 1 for a 1D Black-Scholes-in-log-spot operator) -- /not/ the grid array length, which is the length of every @[Double]@ passed to\/returned from the callbacks below
  ,withFdmApply*`(Double,Double) -> [Double] -> [Double]' -- ^@apply(r)@: whole-grid operator application at the current @(t1,t2)@ time pair (no direction argument -- QuantLib's own 'FdmLinearOp' base method)
  ,withFdmApplyDirection*`Int -> (Double,Double) -> [Double] -> [Double]' -- ^@apply_direction(direction, r)@
  ,withFdmSolveSplitting*`Int -> Double -> (Double,Double) -> [Double] -> [Double]' -- ^@solve_splitting(direction, r, s)@ -- the implicit per-direction solve (e.g. a tridiagonal\/Thomas-algorithm solve for a 1D operator)
  ,withMaybeFdmStepCondition*`Maybe (Double -> [Double] -> [Double])' -- ^optional step condition @applyTo(a, t)@, e.g. American\/Bermudan early exercise (@max(a_i, intrinsic_i)@ at every step) or a barrier knockout
  ,withDoubleArray*`[Double]'& -- ^stopping times at which the step condition above is applied (ignored if there is no step condition); pass every rollback step's time to apply it at every step
  ,withFdmSchemeDesc*`FdmScheme' -- ^the finite-difference scheme (see the haddock above for which schemes are actually safe to use here)
  ,withDoubleArray*`[Double]'& -- ^initial grid values, at time \'from\'
  ,`Double' -- ^from (start time of the rollback, e.g. option maturity)
  ,`Double' -- ^to (end time of the rollback, e.g. 0)
  ,fromIntegral`Int' -- ^steps
  ,fromIntegral`Int' -- ^dampingSteps
  ,preArray-`[Double]'&peekDoubleArray* -- ^grid values at time \'to\'
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |'Predefined1dMesher(points)' -- an 'Fdm1dMesher' over an explicit, caller-supplied set of grid points.
{#fun qlPredefined1dMesher as predefined1dMesher{withDoubleArray*`[Double]'& -- ^points
  ,preErrorCheck-`String'errorCheck*-}->`Fdm1dMesher'peekFdm1dMesher*#}

-- |'Uniform1dMesher(start, end, size)' -- an evenly spaced 'Fdm1dMesher'.
{#fun qlUniform1dMesher as uniform1dMesher{`Double' -- ^start
  ,`Double' -- ^end
  ,fromIntegral`Word' -- ^size
  ,preErrorCheck-`String'errorCheck*-}->`Fdm1dMesher'peekFdm1dMesher*#}

-- |'Concentrating1dMesher(start, end, size, cPoint, requireCPoint)' -- an 'Fdm1dMesher' with grid
-- points concentrated near @cPoint@ (e.g. a strike or barrier), or plain uniform spacing when
-- @cPoint@ is 'Nothing' for both coordinates.
{#fun qlConcentrating1dMesher as concentrating1dMesher{`Double' -- ^start
  ,`Double' -- ^end
  ,fromIntegral`Word' -- ^size
  ,fromMaybeDouble`Maybe Double' -- ^concentration point location
  ,fromMaybeDouble`Maybe Double' -- ^concentration point density
  ,`Bool' -- ^requireCPoint: force the concentration point itself onto the grid
  ,preErrorCheck-`String'errorCheck*-}->`Fdm1dMesher'peekFdm1dMesher*#}

-- |Multi-concentration-point overload of 'concentrating1dMesher'
-- (@Concentrating1dMesher(start, end, size, cPoints, tol)@) -- a distinct upstream constructor,
-- not a defaulted-arg variant of the single-point one.
concentrating1dMesherMulti :: Double -> Double -> Word
  -> [(Double, Double, Bool)] -- ^concentration points: (location, density, requireCPoint)
  -> Double -- ^tol
  -> IO Fdm1dMesher
concentrating1dMesherMulti start end size cPoints tol =
  let (locs, densities, reqs) = unzip3 cPoints
  in qlConcentrating1dMesherMulti start end size (fromIntegral (length cPoints)) locs densities reqs tol
{#fun qlConcentrating1dMesherMulti{`Double',`Double',fromIntegral`Word'
  ,fromIntegral`Word' -- ^number of concentration points
  ,withDoubleArrayRaw*`[Double]' -- ^locations
  ,withDoubleArrayRaw*`[Double]' -- ^densities
  ,withBoolArrayRaw*`[Bool]' -- ^requireCPoint per point
  ,`Double' -- ^tol
  ,preErrorCheck-`String'errorCheck*-}->`Fdm1dMesher'peekFdm1dMesher*#}

-- |'FdmBlackScholesMesher(size, process, maturity, strike, ...)' -- the standard log-spot mesher
-- for a Black-Scholes-family process, reusing the same 'GeneralizedBlackScholesProcess'\/
-- 'Dividend'\/'FdmQuantoHelper' plumbing "QuantLib.PricingEngine"'s @fd*@ engines already use.
{#fun qlFdmBlackScholesMesher as fdmBlackScholesMesher{fromIntegral`Word' -- ^size
  ,withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess'
  ,`Double' -- ^maturity
  ,`Double' -- ^strike
  ,fromMaybeDouble`Maybe Double' -- ^xMinConstraint
  ,fromMaybeDouble`Maybe Double' -- ^xMaxConstraint
  ,`Double' -- ^eps
  ,`Double' -- ^scaleFactor
  ,fromMaybeDouble`Maybe Double' -- ^concentration point location
  ,fromMaybeDouble`Maybe Double' -- ^concentration point density
  ,withDividendArray*`[Dividend]'&
  ,withMaybeFdmQuantoHelper*`Maybe FdmQuantoHelper'
  ,`Double' -- ^spotAdjustment
  ,preErrorCheck-`String'errorCheck*-}->`Fdm1dMesher'peekFdm1dMesher*#}

-- |'FdmCEV1dMesher(size, f0, alpha, beta, maturity, eps, scaleFactor, cPoint)' -- the standard
-- mesher for a CEV process.
{#fun qlFdmCev1dMesher as fdmCev1dMesher{fromIntegral`Word' -- ^size
  ,`Double' -- ^f0
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^maturity
  ,`Double' -- ^eps
  ,`Double' -- ^scaleFactor
  ,fromMaybeDouble`Maybe Double' -- ^concentration point location
  ,fromMaybeDouble`Maybe Double' -- ^concentration point density
  ,preErrorCheck-`String'errorCheck*-}->`Fdm1dMesher'peekFdm1dMesher*#}

-- |'ExponentialJump1dMesher(steps, beta, jumpIntensity, eta, eps)' -- mesher for the jump-diffusion
-- component of a jump-diffusion process.
{#fun qlExponentialJump1dMesher as exponentialJump1dMesher{fromIntegral`Word' -- ^steps
  ,`Double' -- ^beta
  ,`Double' -- ^jumpIntensity
  ,`Double' -- ^eta
  ,`Double' -- ^eps
  ,preErrorCheck-`String'errorCheck*-}->`Fdm1dMesher'peekFdm1dMesher*#}

-- |'FdmSimpleProcess1dMesher(size, process, maturity, tAvgSteps, epsilon, mandatoryPoint)' --
-- generic mesher for any bound one-dimensional 'StochasticProcess1D'.
{#fun qlFdmSimpleProcess1dMesher as fdmSimpleProcess1dMesher{fromIntegral`Word' -- ^size
  ,withStochasticProcess1D*`StochasticProcess1D'
  ,`Double' -- ^maturity
  ,fromIntegral`Word' -- ^tAvgSteps
  ,`Double' -- ^epsilon
  ,fromMaybeDouble`Maybe Double' -- ^mandatoryPoint
  ,preErrorCheck-`String'errorCheck*-}->`Fdm1dMesher'peekFdm1dMesher*#}

-- |'FdmHestonVarianceMesher(size, process, maturity, tAvgSteps, epsilon, mixingFactor)' -- variance
-- mesher for a Heston-family process.
{#fun qlFdmHestonVarianceMesher as fdmHestonVarianceMesher{fromIntegral`Word' -- ^size
  ,withHestonProcess*`GenHestonProcess hp'
  ,`Double' -- ^maturity
  ,fromIntegral`Word' -- ^tAvgSteps
  ,`Double' -- ^epsilon
  ,`Double' -- ^mixingFactor
  ,preErrorCheck-`String'errorCheck*-}->`Fdm1dMesher'peekFdm1dMesher*#}

-- |'FdmHestonLocalVolatilityVarianceMesher(size, process, leverageFct, maturity, tAvgSteps, epsilon, mixingFactor)'
-- -- Heston variance mesher accounting for a local-volatility leverage function.
{#fun qlFdmHestonLocalVolatilityVarianceMesher as fdmHestonLocalVolatilityVarianceMesher{fromIntegral`Word' -- ^size
  ,withHestonProcess*`GenHestonProcess hp'
  ,withLocalVolTermStructure*`LocalVolTermStructure' -- ^leverageFct
  ,`Double' -- ^maturity
  ,fromIntegral`Word' -- ^tAvgSteps
  ,`Double' -- ^epsilon
  ,`Double' -- ^mixingFactor
  ,preErrorCheck-`String'errorCheck*-}->`Fdm1dMesher'peekFdm1dMesher*#}

-- |'FdmMesherComposite' -- combine one or more 'Fdm1dMesher's into the multi-dimensional
-- 'FdmMesher' the operator\/step-condition callbacks and 'fdmSolve' operate over; the sole
-- concrete 'FdmMesher' upstream.
{#fun qlFdmMesherComposite as fdmMesherComposite{withFdm1dMesherArray*`[Fdm1dMesher]'&
  ,preErrorCheck-`String'errorCheck*-}->`FdmMesher'peekFdmMesher*#}

-- |Real-valued node locations along one dimension of a mesher, e.g. to map 'fdmSolve''s flat
-- result array back to coordinates (mirrors how @Fdm1DimSolver@\/@FdmNdimSolver@ build their own
-- @x_@ arrays from this same call upstream).
{#fun qlFdmMesherLocations as fdmMesherLocations{withFdmMesher*`FdmMesher'
  ,fromIntegral`Int' -- ^direction
  ,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- Raw import, not a {#fun#}: 'withCustomFdmInnerValueCalculator' below needs the two
-- 'FunPtr's kept alive for as long as the returned 'FdmInnerValueCalculator' can be called into
-- (i.e. across the whole continuation, which typically includes a later 'fdmSolve' call), not
-- just for the duration of this one construction call the way a plain {#fun#}-generated
-- 'withFdmInnerValue' bracket would provide -- see the haddock below.
foreign import ccall "ql.h qlFdmInnerValueCalculatorFromFunctions"
  c_qlFdmInnerValueCalculatorFromFunctions :: Ptr CFdmMesher -> FunPtr FdmInnerValueFun -> FunPtr FdmInnerValueFun
    -> Ptr CString -> IO (Ptr CFdmInnerValueCalculator)

-- |Wraps a Haskell @t -> location -> value@ pair of @innerValue@\/@avgInnerValue@ functions as a
-- real 'FdmInnerValueCalculator' object, valid only inside the continuation -- the fully custom
-- counterpart to constructors built from QuantLib's own concrete subclasses (bound alongside
-- this, which need no such bracket: they hold no Haskell callback). Unlike every callback
-- 'fdmRollback' takes, this crosses the language boundary once /per grid node/, not once per outer
-- iteration over the whole grid -- there is no batched \"whole-grid inner value\" shape anywhere
-- in QuantLib or QuantLib-SWIG. Per CLAUDE.md's \"coarsen the language-boundary crossing\" bullet,
-- this is the one case where that coarsening isn't available, so the real per-call FFI cost across
-- every node (and, if a step condition also calls the calculator, every node at every exercise
-- date) is accepted -- matching QuantLib-SWIG's own accepted-cost precedent,
-- @FdmInnerValueCalculatorDelegate@ (@SWIG\/fdm.i@).
withCustomFdmInnerValueCalculator :: FdmMesher
  -> (Double -> [Double] -> Double) -- ^innerValue(t, location)
  -> (Double -> [Double] -> Double) -- ^avgInnerValue(t, location)
  -> (FdmInnerValueCalculator -> IO b) -> IO b
withCustomFdmInnerValueCalculator mesher iv aiv k =
  withFdmMesher mesher $ \mesher' ->
  withFdmInnerValue iv $ \ivFp ->
  withFdmInnerValue aiv $ \aivFp ->
  preErrorCheck $ \errPtr -> do
    res <- c_qlFdmInnerValueCalculatorFromFunctions mesher' ivFp aivFp errPtr
    errorCheck errPtr
    peekFdmInnerValueCalculator res >>= k

-- |'FdmZeroInnerValue' -- an 'FdmInnerValueCalculator' whose @innerValue@\/@avgInnerValue@ are
-- always 0.
{#fun qlFdmZeroInnerValue as fdmZeroInnerValue{preErrorCheck-`String'errorCheck*-}->`FdmInnerValueCalculator'peekFdmInnerValueCalculator*#}

-- |'FdmCellAveragingInnerValue(payoff, mesher, direction)' -- cell-averages @payoff@ over each
-- grid cell along @direction@ (Simpson-integrating across the cell straddling a kink, e.g. a
-- strike, rather than just evaluating at the cell center), with the identity value mapping. See
-- 'withCustomCellAveragingInnerValue' for the @gridMapping@-taking overload (e.g. to reproduce
-- 'fdmLogInnerValue' by hand), and 'fdmLogInnerValue' for the common log-mapped case QuantLib
-- itself gives its own dedicated subclass.
{#fun qlFdmCellAveragingInnerValue as fdmCellAveragingInnerValue{withPayoff*`Payoff'
  ,withFdmMesher*`FdmMesher'
  ,fromIntegral`Int' -- ^direction
  ,preErrorCheck-`String'errorCheck*-}->`FdmInnerValueCalculator'peekFdmInnerValueCalculator*#}

-- Raw import, not a {#fun#}: same FunPtr-lifetime hazard as
-- 'c_qlFdmInnerValueCalculatorFromFunctions' above -- 'gridMapping' is stored inside the C++
-- object and invoked again on every later 'innerValue'\/'avgInnerValue' call, not just during
-- construction.
foreign import ccall "ql.h qlFdmCellAveragingInnerValueMapped"
  c_qlFdmCellAveragingInnerValueMapped :: QlPayoff -> Ptr CFdmMesher -> CUInt -> FunPtr FdmGridMappingFun
    -> Ptr CString -> IO (Ptr CFdmInnerValueCalculator)

-- |As 'fdmCellAveragingInnerValue', but with an explicit @gridMapping :: Double -> Double@ applied
-- to each node's location before the payoff sees it (e.g. @exp@ on a log-spot grid, reproducing
-- 'fdmLogInnerValue' by hand) -- a genuine per-node Haskell callback (see CLAUDE.md's "coarsen the
-- language-boundary crossing" bullet and 'withCustomFdmInnerValueCalculator' above), so the
-- resulting 'FdmInnerValueCalculator' is only valid inside this continuation.
withCustomCellAveragingInnerValue :: Payoff -> FdmMesher -> Int -> (Double -> Double)
  -> (FdmInnerValueCalculator -> IO b) -> IO b
withCustomCellAveragingInnerValue payoff mesher direction mapping k =
  withPayoff payoff $ \payoff' ->
  withFdmMesher mesher $ \mesher' ->
  withFdmGridMapping mapping $ \mappingFp ->
  preErrorCheck $ \errPtr -> do
    res <- c_qlFdmCellAveragingInnerValueMapped payoff' mesher' (fromIntegral direction) mappingFp errPtr
    errorCheck errPtr
    peekFdmInnerValueCalculator res >>= k

-- |'FdmLogInnerValue(payoff, mesher, direction)' -- 'fdmCellAveragingInnerValue' with the
-- @gridMapping = exp@ QuantLib itself gives its own dedicated subclass (the standard shape for a
-- log-spot grid, e.g. 'fdmBlackScholesMesher''s own grid).
{#fun qlFdmLogInnerValue as fdmLogInnerValue{withPayoff*`Payoff'
  ,withFdmMesher*`FdmMesher'
  ,fromIntegral`Int' -- ^direction
  ,preErrorCheck-`String'errorCheck*-}->`FdmInnerValueCalculator'peekFdmInnerValueCalculator*#}

-- |'FdmLogBasketInnerValue(payoff, mesher)' -- the multi-asset counterpart to 'fdmLogInnerValue':
-- evaluates a 'BasketPayoff' with each dimension's location exponentiated first (@exp@ on every
-- mesher direction, i.e. a log-spot grid per underlying), no cell averaging.
{#fun qlFdmLogBasketInnerValue as fdmLogBasketInnerValue{withBasketPayoff*`BasketPayoff'
  ,withFdmMesher*`FdmMesher'
  ,preErrorCheck-`String'errorCheck*-}->`FdmInnerValueCalculator'peekFdmInnerValueCalculator*#}

-- |'FdmAffineModelSwapInnerValue\<G2\>(disModel, fwdModel, swap, exerciseDates, mesher, direction)'
-- -- the swap-NPV-under-the-model 'FdmInnerValueCalculator' used internally by
-- 'QuantLib.PricingEngine.fdG2SwaptionEngine'. @exerciseDates@ pairs each exercise time (the same
-- @Time@-as-@Double@ year-fraction convention used throughout, not a dedicated type) with the
-- 'Data.Time.Calendar.Day' it corresponds to (upstream's @std::map\<Time, Date\>@).
fdmAffineG2ModelSwapInnerValue :: G2 -> G2 -> GenFixedVsFloatingSwap f -> [(Double, Day)] -> FdmMesher -> Int -> IO FdmInnerValueCalculator
fdmAffineG2ModelSwapInnerValue disModel fwdModel swap exerciseDates =
  let (times, dates) = unzip exerciseDates
  in qlFdmAffineG2ModelSwapInnerValue disModel fwdModel swap (fromIntegral (length exerciseDates)) times dates
{#fun qlFdmAffineG2ModelSwapInnerValue{withG2*`G2'
  ,withG2*`G2'
  ,withFixedVsFloatingSwap*`GenFixedVsFloatingSwap f'
  ,fromIntegral`Int' -- ^number of exercise dates
  ,withDoubleArrayRaw*`[Double]' -- ^exercise times
  ,withDayPtr*`[Day]' -- ^exercise dates
  ,withFdmMesher*`FdmMesher'
  ,fromIntegral`Int' -- ^direction
  ,preErrorCheck-`String'errorCheck*-}->`FdmInnerValueCalculator'peekFdmInnerValueCalculator*#}

-- |As 'fdmAffineG2ModelSwapInnerValue', but for 'HullWhite' -- used internally by
-- 'QuantLib.PricingEngine.fdHullWhiteSwaptionEngine'.
fdmAffineHullWhiteModelSwapInnerValue :: HullWhite -> HullWhite -> GenFixedVsFloatingSwap f -> [(Double, Day)] -> FdmMesher -> Int -> IO FdmInnerValueCalculator
fdmAffineHullWhiteModelSwapInnerValue disModel fwdModel swap exerciseDates =
  let (times, dates) = unzip exerciseDates
  in qlFdmAffineHullWhiteModelSwapInnerValue disModel fwdModel swap (fromIntegral (length exerciseDates)) times dates
{#fun qlFdmAffineHullWhiteModelSwapInnerValue{withHullWhite*`HullWhite'
  ,withHullWhite*`HullWhite'
  ,withFixedVsFloatingSwap*`GenFixedVsFloatingSwap f'
  ,fromIntegral`Int' -- ^number of exercise dates
  ,withDoubleArrayRaw*`[Double]' -- ^exercise times
  ,withDayPtr*`[Day]' -- ^exercise dates
  ,withFdmMesher*`FdmMesher'
  ,fromIntegral`Int' -- ^direction
  ,preErrorCheck-`String'errorCheck*-}->`FdmInnerValueCalculator'peekFdmInnerValueCalculator*#}

-- |Evaluate an 'FdmInnerValueCalculator''s @innerValue@ at the mesher node given by its
-- coordinates (one index per PDE dimension), at time @t@ -- lets any bound calculator (native or
-- built via 'withCustomFdmInnerValueCalculator') be inspected directly without assembling a whole
-- 'fdmSolve'.
{#fun qlFdmInnerValueCalculatorEval as fdmInnerValue{withFdmInnerValueCalculator*`FdmInnerValueCalculator'
  ,withFdmMesher*`FdmMesher'
  ,withIntArray*`[Int]'& -- ^node coordinates
  ,`Double' -- ^t
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |As 'fdmInnerValue', but for @avgInnerValue@.
{#fun qlFdmInnerValueCalculatorAvgEval as fdmAvgInnerValue{withFdmInnerValueCalculator*`FdmInnerValueCalculator'
  ,withFdmMesher*`FdmMesher'
  ,withIntArray*`[Int]'& -- ^node coordinates
  ,`Double' -- ^t
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Sibling of 'fdmRollback' that derives its own initial grid from a mesher and an
-- 'FdmInnerValueCalculator' (@avgInnerValue(t, location)@ per node, called once per mesher node at
-- @t = maturity@ -- mirroring @Fdm1DimSolver@\/@FdmNdimSolver@'s own constructor loop) instead of
-- taking a precomputed grid array. Everything else (operator\/step-condition\/scheme\/rollback) is
-- identical to 'fdmRollback', reusing the same callback machinery. The calculator can be either
-- fully custom ('fdmInnerValueCalculator') or one of QuantLib's own native subclasses.
--
-- @Fdm1DimSolver@\/@FdmNdimSolver@ themselves (their own @LazyObject@ caching and cubic-spline
-- interpolation) are /not/ bound; combine this function's result with 'fdmMesherLocations' for
-- interpolation.
{#fun qlFdmSolve as fdmSolve{withFdmMesher*`FdmMesher'
  ,withFdmInnerValueCalculator*`FdmInnerValueCalculator'
  ,fromIntegral`Int' -- ^number of PDE directions\/dimensions the operator has
  ,withFdmApply*`(Double,Double) -> [Double] -> [Double]' -- ^@apply(r)@
  ,withFdmApplyDirection*`Int -> (Double,Double) -> [Double] -> [Double]' -- ^@apply_direction(direction, r)@
  ,withFdmSolveSplitting*`Int -> Double -> (Double,Double) -> [Double] -> [Double]' -- ^@solve_splitting(direction, r, s)@
  ,withMaybeFdmStepCondition*`Maybe (Double -> [Double] -> [Double])' -- ^optional step condition
  ,withDoubleArray*`[Double]'& -- ^stopping times at which the step condition above is applied
  ,withFdmSchemeDesc*`FdmScheme' -- ^the finite-difference scheme
  ,`Double' -- ^maturity (start time of the rollback, and the time at which avgInnerValue builds the initial grid)
  ,`Double' -- ^to (end time of the rollback, e.g. 0)
  ,fromIntegral`Int' -- ^steps
  ,fromIntegral`Int' -- ^dampingSteps
  ,preArray-`[Double]'&peekDoubleArray* -- ^grid values at time \'to\'
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
