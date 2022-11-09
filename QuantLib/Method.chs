module QuantLib.Method
  (
    pathGenerator
  , sobolPathGenerator
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

import QuantLib.Internal
import QuantLib.Internal.Type
{#import QuantLib.Math#}

{#pointer *PolymorphicPathGenerator as PathGenerator foreign -> CPathGenerator nocode#}
{#pointer *QlStochasticProcess as StochasticProcess foreign -> CStochasticProcess nocode#}

{#fun qlPathGenerator as pathGenerator{fromEnumC`RngTrait', withStochasticProcess*`StochasticProcess', withTimeGrid*`TimeGrid', fromIntegral`Word', fromIntegral`Word', `Bool', preErrorCheck-`String'errorCheck*-}->`PathGenerator'peekPathGenerator*#}
{#fun qlSobolPathGenerator as sobolPathGenerator{fromEnumC`SobolDirectionIntegers', withStochasticProcess*`StochasticProcess', withTimeGrid*`TimeGrid', fromIntegral`Word', fromIntegral`Word', `Bool', preErrorCheck-`String'errorCheck*-}->`PathGenerator'peekPathGenerator*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
