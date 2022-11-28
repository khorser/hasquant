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

{#fun qlPathGenerator as pathGenerator{fromEnumC`RngTrait',withStochasticProcess*`GenStochasticProcess a',withTimeGrid*`TimeGrid'
  ,fromIntegral`Word' -- ^seed
  ,fromIntegral`Word' -- ^dimension
  ,`Bool' -- ^brownian bridge
  ,preErrorCheck-`String'errorCheck*-}->`PathGenerator'peekPathGenerator*#}
{#fun qlSobolPathGenerator as sobolPathGenerator{fromEnumC`SobolDirectionIntegers',withStochasticProcess*`GenStochasticProcess a',withTimeGrid*`TimeGrid'
  ,fromIntegral`Word' -- ^seed
  ,fromIntegral`Word' -- ^dimension
  ,`Bool' -- ^brownian bridge
  ,preErrorCheck-`String'errorCheck*-}->`PathGenerator'peekPathGenerator*#}

{#fun qlPathGeneratorNext as next{withPathGenerator*`PathGenerator',preErrorCheck-`String'errorCheck*-}->`SamplePath'peekSamplePath*#}
{#fun qlPathGeneratorAntithetic as antithetic{withPathGenerator*`PathGenerator',preErrorCheck-`String'errorCheck*-}->`SamplePath'peekSamplePath*#}
{#fun pure qlSamplePathWeight as weight{withSamplePath*`SamplePath'}->`Double'#}
{#fun pure qlSamplePathAssetNumber as assetNumber{withSamplePath*`SamplePath'}->`Word'fromIntegral#}
{#fun pure qlSamplePathSize as pathSize{withSamplePath*`SamplePath'}->`Word'fromIntegral#}
{#fun qlSamplePathAt as assetAt{withSamplePath*`SamplePath',fromIntegral`Word' -- ^asset
  ,fromIntegral`Word' -- ^point
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlSamplePathAssetPath as asset{withSamplePath*`SamplePath',fromIntegral`Word',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}
{#fun qlSamplePathAssetPath as asset'{withSamplePath*`SamplePath',fromIntegral`Word',preArray-`Vector CDouble'&peekDoubleVector*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
