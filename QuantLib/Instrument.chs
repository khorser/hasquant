module QuantLib.Instrument
  (
    PositionType(..)
  , SettlementType(..)
  , SettlementMethod(..)
  , CallabilityType(..)
  , OptionType(..)
  , BarrierType(..)
  , DoubleBarrierType(..)
  , AverageType(..)
  , Seniority(..)
  , PricingModel(..)

  , Instrument
  , asInstrument
  , Callability(..)

  , Exercise(..)
  , ExerciseType(..)

  , npv
  , errorEstimate
  , isExpired
  , valuationDate
  , composite
  , setPricingEngine
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type
import QuantLib.Internal.Enum

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

{#enum SettlementType{} deriving(Show, Eq)#}
{#enum SettlementMethod{} deriving(Show, Eq)#}
{#enum BarrierType{} deriving(Show, Eq)#}
{#enum DoubleBarrierType{} deriving(Show, Eq)#}
{#enum AverageType{} deriving(Show, Eq)#}
{#enum Seniority{} deriving(Show, Eq)#}
{#enum PricingModel{} deriving(Show, Eq)#}
{#enum RestructuringType{} deriving(Show, Eq)#}
{#enum AtomicDefaultType{} deriving(Show, Eq)#}

{#pointer *QlPricingEngine as PricingEngine foreign -> CPricingEngine nocode#}
{#pointer *QlInstrument as Instrument foreign -> CInstrument' nocode#}

-- |Returns the net present value of the given Instrument
{#fun qlInstrumentNPV as npv{withInstrument*`GenInstrument a',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns the error estimate on the NPV when available.
{#fun qlInstrumentErrorEstimate as errorEstimate{withInstrument*`GenInstrument a',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns whether the instrument might have value greater than zero.
{#fun qlInstrumentIsExpired as isExpired{withInstrument*`GenInstrument a',preErrorCheck-`String'errorCheck*-}->`Bool'#}
-- |returns the date the net present value refers to.
{#fun qlInstrumentValuationDate as valuationDate{withInstrument*`GenInstrument a',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

composite :: [(Instrument, Double)] -> IO Instrument
composite = (uncurry qlCompositeInstrument) . unzip
{#fun qlCompositeInstrument{withInstrumentArray*`[Instrument]'&,withDoubleArray*`[Double]'&,preErrorCheck-`String'errorCheck*-}->`Instrument'peekInstrument*#}
{#fun qlInstrumentSetPricingEngine as setPricingEngine{withInstrument*`GenInstrument a',withPricingEngine*`PricingEngine',preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
