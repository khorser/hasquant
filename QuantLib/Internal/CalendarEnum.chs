{-# LANGUAGE TemplateHaskell, StandaloneDeriving #-}
-- suppress warnings about unused Extra_ constructors
{-# OPTIONS_GHC -Wno-unused-top-binds #-}
module QuantLib.Internal.CalendarEnum
  (
    mapCalendar
  , CalendarConstructor(..)
  , JointCalendarRule(..)

  , mapDayCounter
  , DayCounterConstructor(..)
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

import QuantLib.Internal.Syntax
import QuantLib.Internal.Type
--import{-# SOURCE #-} QuantLib.Time.Schedule
import QuantLib.Time.Date(Weekday)

{#enum JointCalendarRule{} deriving(Show, Eq)#}

{#enum CalendarCountry{} add prefix = "Country__" deriving(Show, Eq)#}

{#enum AustriaMarket{} add prefix = "Austria__" deriving(Show, Eq)#}
{#enum BrazilMarket{} add prefix = "Brazil__" deriving(Show, Eq)#}
{#enum CanadaMarket{} add prefix = "Canada__" deriving(Show, Eq)#}
{#enum ChinaMarket{} add prefix = "China__" deriving(Show, Eq)#}
{#enum FranceMarket{} add prefix= "France__" deriving(Show, Eq)#}
{#enum GermanyMarket{} add prefix = "Germany__" deriving(Show, Eq)#}
{#enum IndonesiaMarket{} add prefix = "Indonesia__" deriving(Show, Eq)#}
{#enum IsraelMarket{} add prefix = "Israel__" deriving(Show, Eq)#}
{#enum ItalyMarket{} add prefix = "Italy__" deriving(Show, Eq)#}
{#enum RomaniaMarket{} add prefix = "Romania__" deriving(Show, Eq)#}
{#enum RussiaMarket{} add prefix = "Russia__" deriving(Show, Eq)#}
{#enum SouthKoreaMarket{} add prefix = "SouthKorea__" deriving(Show, Eq)#}
{#enum UnitedKingdomMarket{} add prefix = "UnitedKingdom__" deriving(Show, Eq)#}
{#enum UnitedStatesMarket{} add prefix = "UnitedStates__" deriving(Show, Eq)#}

data CalendarExtra =
   Extra__Bespoke String [Weekday]
  | Extra__Joint2 Calendar Calendar JointCalendarRule
  | Extra__Joint3 Calendar Calendar Calendar JointCalendarRule
  | Extra__Joint4 Calendar Calendar Calendar Calendar JointCalendarRule

$(mergeEnums "CalendarConstructor" "mapCalendar" ''CalendarCountry "Market" ''CalendarExtra)

deriving instance Show CalendarConstructor
deriving instance Eq CalendarConstructor

{#enum DayCounterType{} add prefix = "DayCounter__" deriving(Show, Eq)#}

{#enum ActualActualConvention{} add prefix = "ActualActual__" deriving(Show, Eq)#}
{#enum Thirty360Convention{} add prefix = "Thirty360__" deriving(Show, Eq)#}
{#enum Actual365FixedConvention{} add prefix = "Actual365Fixed__" deriving(Show, Eq)#}

-- TODO add the second (Schedule) argument to Actua/Actual constructor

data DayCounterExtra = Extra__Business252 Calendar

$(mergeEnums "DayCounterConstructor" "mapDayCounter" ''DayCounterType "Convention" ''DayCounterExtra)

deriving instance Show DayCounterConstructor
deriving instance Eq DayCounterConstructor

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
