module QuantLib.Time.Period
  (
    fromFrequency
  , toFrequency
  , parse
  , add
  , divide
  , lessThan
  , normalize
  , TimeUnit(..)
  , Frequency(..)
  )
where

import QuantLib.Internal

#include "qlTypesC2HS.h"
#include "ql.h"

#include "qlEnumC2HS.h"

{#enum TimeUnit {} deriving(Show, Eq, Bounded)#}

{#enum Frequency {} deriving(Show, Eq, Bounded)#}

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual)
{#fun qlPeriodFromFrequency1 as fromFrequency {`Frequency', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#}

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M)
{#fun qlPeriodToFrequency1 as toFrequency {fromEnumQuantity `Int, TimeUnit'&, preErrorCheck- `String' errorCheck*-} -> `Frequency'#}

{#fun qlPeriodParserParse1 as parse {`String', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#}

{#fun qlPeriodAdd1 as addPeriod {fromEnumQuantity `Int, TimeUnit'&, fromEnumQuantity `Int, TimeUnit'&, preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#} 

add :: (Int, TimeUnit) -> (Int, TimeUnit) -> IO (Int, TimeUnit)
add = addPeriod

{#fun qlPeriodDivide1 as divide {fromEnumQuantity `Int, TimeUnit'&, `Int', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#}

-- less than
{#fun qlPeriodsLT1 as lessThan {fromEnumQuantity `Int, TimeUnit'&, fromEnumQuantity `Int, TimeUnit'&, preErrorCheck- `String' errorCheck*-} -> `Bool'#}

{#fun qlPeriodNormalize1 as normalize {fromEnumQuantity `Int, TimeUnit'&, preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
