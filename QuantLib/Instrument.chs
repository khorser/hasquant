module QuantLib.Instrument
  (
    PositionType(..)
  , SettlementType(..)
  , SettlementMethod(..)
  , CallabilityType(..)
  , OptionType(..)
  , BarrierType(..)
  , DoubleBarrierType(..)
  , PartialBarrierRange(..)
  , AverageType(..)
  , Seniority(..)
  , PricingModel(..)

  , Instrument
  , asInstrument
  , Callability(..)

  , Exercise(..)
  , ExerciseType(..)

  , AdditionalResultVal(..)
  , npv
  , errorEstimate
  , isExpired
  , valuationDate
  , composite
  , additionalResults
  , setPricingEngine
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type hiding(ptr)
import QuantLib.Internal.Common

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

{#enum SettlementType{} deriving(Show, Eq, Read)#}
{#enum SettlementMethod{} deriving(Show, Eq, Read)#}
{#enum BarrierType{} deriving(Show, Eq, Read)#}
{#enum DoubleBarrierType{} deriving(Show, Eq, Read)#}
{#enum PartialBarrierRange{} deriving(Show, Eq, Read)#}
{#enum AverageType{} deriving(Show, Eq, Read)#}
{#enum Seniority{} deriving(Show, Eq, Read)#}
{#enum PricingModel{} deriving(Show, Eq, Read)#}
{#enum RestructuringType{} deriving(Show, Eq, Read)#}
{#enum AtomicDefaultType{} deriving(Show, Eq, Read)#}

{#pointer *QlPricingEngine as PricingEngine foreign -> CPricingEngine nocode#}
{#pointer *QlInstrument as Instrument foreign -> CInstrument' nocode#}

-- |Returns the net present value of the given Instrument
{#fun qlInstrumentNPV as npv{withInstrument*`GenInstrument i',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the error estimate on the NPV when available.
{#fun qlInstrumentErrorEstimate as errorEstimate{withInstrument*`GenInstrument i',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns whether the instrument might have value greater than zero.
{#fun qlInstrumentIsExpired as isExpired{withInstrument*`GenInstrument i',preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |returns the date the net present value refers to.
{#fun qlInstrumentValuationDate as valuationDate{withInstrument*`GenInstrument i',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |Re-registers `struct QlAdditionalResult*` with c2hs as `RawResultPtr` (the type is defined in
-- `QuantLib.Internal.Common`, `nocode` here too) -- c2hs's pointer-type table is per-file, so
-- without this the `{#fun#}` below infers the out-parameter as the opaque `Ptr (Ptr ())` instead
-- of `Ptr RawResultPtr`, which fails to typecheck against `peekAdditionalResults`'s signature.
{#pointer *QlAdditionalResult as RawResultPtr nocode#}

-- |Returns QuantLib's `additionalResults()` map for the given Instrument, as an association list
-- keyed by the C++ result name. The map's values are populated by the pricing engine;
-- `additionalResults()` calls `calculate()` internally, so this is safe and idempotent after
-- pricing.
{#fun qlInstrumentAdditionalResults as additionalResults{withInstrument*`GenInstrument i',preArray-`[(String, AdditionalResultVal)]'&peekAdditionalResults*,preErrorCheck-`String'errorCheck*-}->`()'#}

composite :: [(Instrument, Double)] -> IO Instrument
composite = (uncurry qlCompositeInstrument) . unzip
-- |Builds a composite instrument whose NPV is the sum of the given instruments' NPVs, each scaled by its paired multiplier.
{#fun qlCompositeInstrument{withInstrumentArray*`[GenInstrument i]'& -- ^instruments
  ,withDoubleArray*`[Double]'& -- ^multipliers
  ,preErrorCheck-`String'errorCheck*-}->`Instrument'peekInstrument*#}

-- |Sets the pricing engine used to compute the instrument's results.
{#fun qlInstrumentSetPricingEngine as setPricingEngine{withInstrument*`GenInstrument i',withPricingEngine*`PricingEngine',preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
