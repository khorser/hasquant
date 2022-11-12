module QuantLib.Method
  (
    pathGenerator
  , sobolPathGenerator
  , next
  , antithetic
  , weight
  , assetNumber
  , pathSize
  , valueAt
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

import QuantLib.Internal
import QuantLib.Internal.Type
{#import QuantLib.Math#}

{#pointer *PolymorphicPathGenerator as PathGenerator foreign -> CPathGenerator nocode#}
{#pointer *SamplePath as SamplePath foreign -> CSamplePath nocode#}
{#pointer *QlStochasticProcess as StochasticProcess foreign -> CStochasticProcess nocode#}

{#fun qlPathGenerator as pathGenerator{fromEnumC`RngTrait',withStochasticProcess*`StochasticProcess',withTimeGrid*`TimeGrid',fromIntegral`Word',fromIntegral`Word',`Bool',preErrorCheck-`String'errorCheck*-}->`PathGenerator'peekPathGenerator*#}
{#fun qlSobolPathGenerator as sobolPathGenerator{fromEnumC`SobolDirectionIntegers',withStochasticProcess*`StochasticProcess',withTimeGrid*`TimeGrid',fromIntegral`Word',fromIntegral`Word',`Bool',preErrorCheck-`String'errorCheck*-}->`PathGenerator'peekPathGenerator*#}

{#fun qlPathGeneratorNext as next{withPathGenerator*`PathGenerator',preErrorCheck-`String'errorCheck*-}->`SamplePath'peekSamplePath*#}
{#fun qlPathGeneratorAntithetic as antithetic{withPathGenerator*`PathGenerator',preErrorCheck-`String'errorCheck*-}->`SamplePath'peekSamplePath*#}
{#fun pure qlSamplePathWeight as weight{withSamplePath*`SamplePath'}->`Double'#}
{#fun pure qlSamplePathAssetNumber as assetNumber{withSamplePath*`SamplePath'}->`Word'fromIntegral#}
{#fun pure qlSamplePathSize as pathSize{withSamplePath*`SamplePath'}->`Word'fromIntegral#}
{#fun qlSamplePathAt as valueAt{withSamplePath*`SamplePath',fromIntegral`Word',fromIntegral`Word',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
