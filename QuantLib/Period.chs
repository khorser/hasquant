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
  , fromPeriod
  , toPeriod
  )
where

import Foreign.C.Types(CInt)

import QuantLib.Utility

#include "ql.h"

#include "qlEnum.h"

{#enum TimeUnit {} deriving(Show, Eq, Bounded) #}

{#enum Frequency {} deriving(Show, Eq, Bounded) #}

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual)
{#fun qlPeriodFromFrequency1 as fromFrequency {`Frequency', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int' #}

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M)
{#fun qlPeriodToFrequency1 as toFrequency {`Int', `TimeUnit', preErrorCheck- `String' errorCheck*-} -> `Frequency' #}

{#fun qlPeriodParserParse1 as parse {`String', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int' #}

{#fun qlPeriodAdd1 as addPeriod {fromPeriod `Int, TimeUnit'&, fromPeriod `Int, TimeUnit'&, preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int' #} 

{#fun qlPeriodDivide1 as dividePeriod {fromPeriod `Int, TimeUnit'&, `Int', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int' #}

{#fun qlPeriodsLT1 as periodLT {fromPeriod `Int, TimeUnit'&, fromPeriod `Int, TimeUnit'&, preErrorCheck- `String' errorCheck*-} -> `Bool' #}

{#fun qlPeriodNormalize1 as normalize {fromPeriod `Int, TimeUnit'&, preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int' #}

fromPeriod :: (Int, TimeUnit) -> (CInt, CInt)
fromPeriod (x, u) = (fromIntegral x, fromIntegral $ fromEnum u)

toPeriod :: (CInt, CInt) -> (Int, TimeUnit)
toPeriod (x, u) = (fromIntegral x, toEnum $ fromIntegral u)

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
