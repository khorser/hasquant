{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts, TypeOperators #-}
module QuantLib.Instrument
  (
    PositionType(..)
  , SettlementType(..)
  , SettlementMethod(..)
  , CallabilityType(..)
  , OptionType(..)
  , BarrierType(..)
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
  )
  where

import QuantLib.Type
import QuantLib.Internal
import QuantLib.Internal.Enum

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

{#enum SettlementType {} deriving(Show, Eq)#}

{#enum SettlementMethod {} deriving(Show, Eq)#}

{#enum BarrierType {} deriving(Show, Eq)#}

{#enum AverageType {} deriving(Show, Eq)#}

{#enum Seniority {} deriving(Show, Eq)#}

{#enum PricingModel {} deriving(Show, Eq)#}

{#enum RestructuringType {} deriving(Show, Eq)#}

{#enum AtomicDefaultType {} deriving(Show, Eq)#}

{#pointer *QlInstrument as Instrument foreign finalizer qlFreeInstrument newtype#}
instance ForeignObject Instrument where
  withObject = withInstrument
  constructor = Instrument
  finalizer = qlFreeInstrument

asInstrument :: (a`Derives` Instrument) => a -> IO Instrument
asInstrument = cast

-- |Returns the net present value of the given Instrument
{#fun qlInstrumentNPV as npv {`Instrument', preErrorCheck-`String'errorCheck*-} ->`Double'#}

-- |returns the error estimate on the NPV when available.
{#fun qlInstrumentErrorEstimate as errorEstimate {`Instrument', preErrorCheck-`String'errorCheck*-} ->`Double'#}

-- |returns whether the instrument might have value greater than zero.
{#fun qlInstrumentIsExpired as isExpired {`Instrument', preErrorCheck-`String'errorCheck*-} ->`Bool'#}

-- |returns the date the net present value refers to.
{#fun qlInstrumentValuationDate as valuationDate {`Instrument', preErrorCheck-`String'errorCheck*-} ->`Day' toDay#}

composite :: [(Instrument, Double)] -> IO Instrument
composite = (uncurry qlCompositeInstrument) . unzip
{#fun qlCompositeInstrument {withObjectArray*`[Instrument]'&, withDoubleArray*`[Double]'&, preErrorCheck-`String'errorCheck*-} ->`Instrument'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
