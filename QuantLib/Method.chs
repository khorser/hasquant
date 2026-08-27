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
-- regression 'LongstaffSchwartzPathPricer' performs internally against a bound 'Payoff', exposed so it
-- can be driven from a Haskell-defined payoff instead: call it once per exercise date, walking dates
-- strictly backward, batched across all paths rather than per path.
{#fun qlLsmRegress as lsmRegress{`PolynomialType',fromIntegral`Word' -- ^basis order
  ,withDoubleArray*`[Double]'& -- ^fit states (in-the-money paths only)
  ,withDoubleArray*`[Double]'& -- ^fit targets (continuation value at these states)
  ,withDoubleArray*`[Double]'& -- ^eval states (all paths' state at this date)
  ,preArray-`[Double]'&peekDoubleArray* -- ^continuation value estimate per eval state
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
