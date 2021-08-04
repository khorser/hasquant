module QuantLib.Period
  (
    fromFrequency
  , toFrequency
  , parse
  , addPeriod
  , dividePeriod
  , periodLT
  , normalize
  , TimeUnit(..)
  , Frequency(..)
  , marshalPeriod
  , unmarshalPeriod
  )
where

import Foreign.C.Types(CInt)

import QuantLib.Utility

#include "ql.h"

#include "qlEnum.h"

{#enum TimeUnit {} deriving(Show, Eq, Bounded) #}

{#enum Frequency {} deriving(Show, Eq, Bounded) #}

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual)
{#fun qlPeriodFromFrequency1 as fromFrequency {`Frequency', minEnumByRef- `TimeUnit' unmarshalEnumByRef*, preErrorCheck- `String' errorCheck*-} -> `Int' #}

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M)
{#fun qlPeriodToFrequency1 as toFrequency {`Int', `TimeUnit', preErrorCheck- `String' errorCheck*-} -> `Frequency' #}

{#fun qlPeriodParserParse1 as parse {`String', minEnumByRef- `TimeUnit' unmarshalEnumByRef*, preErrorCheck- `String' errorCheck*-} -> `Int' #}

{#fun qlPeriodAdd1 as addPeriod {marshalPeriod `Int, TimeUnit'&, marshalPeriod `Int, TimeUnit'&, minEnumByRef- `TimeUnit' unmarshalEnumByRef*, preErrorCheck- `String' errorCheck*-} -> `Int' #} 

{#fun qlPeriodDivide1 as dividePeriod {marshalPeriod `Int, TimeUnit'&, `Int', minEnumByRef- `TimeUnit' unmarshalEnumByRef*, preErrorCheck- `String' errorCheck*-} -> `Int' #}

{#fun qlPeriodsLT1 as periodLT {marshalPeriod `Int, TimeUnit'&, marshalPeriod `Int, TimeUnit'&, preErrorCheck- `String' errorCheck*-} -> `Bool' #}

{#fun qlPeriodNormalize1 as normalize {marshalPeriod `Int, TimeUnit'&, minEnumByRef- `TimeUnit' unmarshalEnumByRef*, preErrorCheck- `String' errorCheck*-} -> `Int' #}

marshalPeriod :: (Int, TimeUnit) -> (CInt, CInt)
marshalPeriod (x, u) = (fromIntegral x, fromIntegral $ fromEnum u)

unmarshalPeriod :: (CInt, CInt) -> (Int, TimeUnit)
unmarshalPeriod (x, u) = (fromIntegral x, toEnum $ fromIntegral u)

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
