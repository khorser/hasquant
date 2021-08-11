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
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

{#enum ExerciseType {} deriving(Show, Eq, Bounded) #}

{#enum PositionType {} deriving(Show, Eq, Bounded) #}

{#enum SettlementType {} deriving(Show, Eq, Bounded) #}

{#enum CallabilityType {} add prefix="Callability" deriving(Show, Eq, Bounded) #}

{#enum SettlementMethod {} deriving(Show, Eq, Bounded) #}

{#enum BondPriceType {} deriving(Show, Eq, Bounded) #}

{#enum OptionType {} deriving(Show, Eq, Bounded) #}

{#enum BarrierType {} deriving(Show, Eq, Bounded) #}

{#enum SwapType {} deriving(Show, Eq, Bounded) #}

{#enum AverageType {} deriving(Show, Eq, Bounded) #}

{#enum ProtectionSide {} deriving(Show, Eq, Bounded) #}

{#enum Seniority {} deriving(Show, Eq, Bounded) #}

{#enum PricingModel {} deriving(Show, Eq, Bounded) #}

{#enum RestructuringType {} deriving(Show, Eq, Bounded) #}

{#enum AtomicDefaultType {} deriving(Show, Eq, Bounded) #}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
