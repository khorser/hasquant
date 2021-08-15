module QuantLib.Instrument
  (
     ExerciseType(..)
   , PositionType(..)
   , SettlementType(..)
   , SettlementMethod(..)
   , CallabilityType(..)
   , BondPriceType(..)
   , OptionType(..)
   , BarrierType(..)
   , SwapType(..)
   , AverageType(..)
   , ProtectionSide(..)
   , Seniority(..)
   , PricingModel(..)

   , Instrument
   , IsInstrument(..)
  )
  where

import QuantLib.Internal

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

{#enum ExerciseType {} deriving(Show, Eq)#}

{#enum PositionType {} deriving(Show, Eq)#}

{#enum SettlementType {} deriving(Show, Eq)#}

{#enum CallabilityType {} add prefix="Callability" deriving(Show, Eq)#}

{#enum SettlementMethod {} deriving(Show, Eq)#}

{#enum BondPriceType {} deriving(Show, Eq)#}

{#enum OptionType {} deriving(Show, Eq)#}

{#enum BarrierType {} deriving(Show, Eq)#}

{#enum SwapType {} deriving(Show, Eq)#}

{#enum AverageType {} deriving(Show, Eq)#}

{#enum ProtectionSide {} deriving(Show, Eq)#}

{#enum Seniority {} deriving(Show, Eq)#}

{#enum PricingModel {} deriving(Show, Eq)#}

{#enum RestructuringType {} deriving(Show, Eq)#}

{#enum AtomicDefaultType {} deriving(Show, Eq)#}

{#pointer *QlInstrument as Instrument foreign finalizer qlFreeInstrument newtype#}
instance ForeignObject Instrument where
  withObject = withInstrument
  peekObject = newForeignPtr qlFreeInstrument >=> return . Instrument

class IsInstrument a where asInstrument :: a -> IO Instrument

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
