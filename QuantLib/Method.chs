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
  ) where
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

import QuantLib.Internal
import QuantLib.Internal.Type
{#import QuantLib.Math#}
import Foreign.C.Types(CDouble)
import Data.Vector.Storable(Vector)

{#pointer *PolymorphicPathGenerator as PathGenerator foreign -> CPathGenerator nocode#}
{#pointer *SamplePath as SamplePath foreign -> CSamplePath nocode#}
{#pointer *QlStochasticProcess as StochasticProcess foreign -> CStochasticProcess' nocode#}

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

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
