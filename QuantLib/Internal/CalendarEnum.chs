{-# LANGUAGE TemplateHaskell #-}
-- suppress warnings about unused Extra_ constructors
{-# OPTIONS_GHC -w #-}
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
import {-# SOURCE #-} QuantLib.Time.Calendar
import {-# SOURCE #-} QuantLib.Time.Schedule
import QuantLib.Time.Date(Weekday)

{#enum JointCalendarRule {} deriving(Show, Eq)#}

{#enum CalendarCountry {} add prefix = "Country_" deriving(Show, Eq)#}

{#enum AustriaMarket {} add prefix = "Austria_" deriving(Show, Eq)#}
{#enum BrazilMarket {} add prefix = "Brazil_" deriving(Show, Eq)#}
{#enum CanadaMarket {} add prefix = "Canada_" deriving(Show, Eq)#}
{#enum ChinaMarket {} add prefix = "China_" deriving(Show, Eq)#}
{#enum FranceMarket {} add prefix= "France_" deriving(Show, Eq)#}
{#enum GermanyMarket {} add prefix = "Germany_" deriving(Show, Eq)#}
{#enum IndonesiaMarket {} add prefix = "Indonesia_" deriving(Show, Eq)#}
{#enum IsraelMarket {} add prefix = "Israel_" deriving(Show, Eq)#}
{#enum ItalyMarket {} add prefix = "Italy_" deriving(Show, Eq)#}
{#enum RomaniaMarket {} add prefix = "Romania_" deriving(Show, Eq)#}
{#enum RussiaMarket {} add prefix = "Russia_" deriving(Show, Eq)#}
{#enum SouthKoreaMarket {} add prefix = "SouthKorea_" deriving(Show, Eq)#}
{#enum UnitedKingdomMarket {} add prefix = "UnitedKingdom_" deriving(Show, Eq)#}
{#enum UnitedStatesMarket {} add prefix = "UnitedStates_" deriving(Show, Eq)#}

data CalendarExtra =
   Extra_Bespoke String [Weekday]
  | Extra_Joint2 Calendar Calendar JointCalendarRule
  | Extra_Joint3 Calendar Calendar Calendar JointCalendarRule
  | Extra_Joint4 Calendar Calendar Calendar Calendar JointCalendarRule

$(mergeEnums "CalendarConstructor" "mapCalendar" ''CalendarCountry "Market" ''CalendarExtra [''Show, ''Eq])
  
{#enum DayCounterType {} add prefix = "DayCounter_" deriving(Show, Eq)#}

{#enum ActualActualConvention {} add prefix = "ActualActual_" deriving(Show, Eq)#}
{#enum Thirty360Convention {} add prefix = "Thirty360_" deriving(Show, Eq)#}
{#enum Actual365FixedConvention {} add prefix = "Actual365Fixed_" deriving(Show, Eq)#}

-- TODO add the second (Schedule) argument to Actua/Actual constructor

data DayCounterExtra = Extra_Business252 Calendar

$(mergeEnums "DayCounterConstructor" "mapDayCounter" ''DayCounterType "Convention" ''DayCounterExtra [''Show, ''Eq])

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
