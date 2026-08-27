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
  ) where
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

import QuantLib.Internal.Syntax
import QuantLib.Internal.Type
import QuantLib.Time.Date(Weekday)

{#enum JointCalendarRule{} deriving(Show, Eq, Read)#}
{#enum CalendarCountry{} add prefix = "Country__" deriving(Show, Eq, Read)#}
{#enum AustriaMarket{} add prefix = "Austria__" deriving(Show, Eq, Read)#}
{#enum BrazilMarket{} add prefix = "Brazil__" deriving(Show, Eq, Read)#}
{#enum CanadaMarket{} add prefix = "Canada__" deriving(Show, Eq, Read)#}
{#enum ChinaMarket{} add prefix = "China__" deriving(Show, Eq, Read)#}
{#enum FranceMarket{} add prefix= "France__" deriving(Show, Eq, Read)#}
{#enum GermanyMarket{} add prefix = "Germany__" deriving(Show, Eq, Read)#}
{#enum IndonesiaMarket{} add prefix = "Indonesia__" deriving(Show, Eq, Read)#}
{#enum IsraelMarket{} add prefix = "Israel__" deriving(Show, Eq, Read)#}
{#enum ItalyMarket{} add prefix = "Italy__" deriving(Show, Eq, Read)#}
{#enum RomaniaMarket{} add prefix = "Romania__" deriving(Show, Eq, Read)#}
{#enum RussiaMarket{} add prefix = "Russia__" deriving(Show, Eq, Read)#}
{#enum SouthKoreaMarket{} add prefix = "SouthKorea__" deriving(Show, Eq, Read)#}
{#enum UnitedKingdomMarket{} add prefix = "UnitedKingdom__" deriving(Show, Eq, Read)#}
{#enum UnitedStatesMarket{} add prefix = "UnitedStates__" deriving(Show, Eq, Read)#}
{#enum AustraliaMarket{} add prefix = "Australia__" deriving(Show, Eq, Read)#}
{#enum NewZealandMarket{} add prefix = "NewZealand__" deriving(Show, Eq, Read)#}
{#enum PolandMarket{} add prefix = "Poland__" deriving(Show, Eq, Read)#}

data CalendarExtra =
   Extra__Bespoke !String ![Weekday]
  | Extra__Joint2 !Calendar !Calendar !JointCalendarRule
  | Extra__Joint3 !Calendar !Calendar !Calendar !JointCalendarRule
  | Extra__Joint4 !Calendar !Calendar !Calendar !Calendar !JointCalendarRule

$(deriveCrossEnum CrossEnumSpec
    { crossTypeName = "CalendarConstructor"
    , crossMapperFn = "mapCalendar"
    , crossMainEnum = ''CalendarCountry
    , crossSubSuffix = "Market"
    , crossExtraType = ''CalendarExtra
    })

deriving instance Show CalendarConstructor
deriving instance Eq CalendarConstructor

{#enum DayCounterType{} add prefix = "DayCounter__" deriving(Show, Eq, Read)#}
{#enum ActualActualConvention{} add prefix = "ActualActual__" deriving(Show, Eq, Read)#}
{#enum Thirty360Convention{} add prefix = "Thirty360__" deriving(Show, Eq, Read)#}
{#enum Actual365FixedConvention{} add prefix = "Actual365Fixed__" deriving(Show, Eq, Read)#}
-- these three don't have a real named Convention enum upstream, just a plain
-- includeLastDay bool -- this marker tells deriveCrossEnum to give them a single
-- constructor carrying a runtime Bool instead of cross-producting named values
type Actual360Convention = Bool
type Actual36525Convention = Bool
type Actual366Convention = Bool

data DayCounterExtra = Extra__Business252 !Calendar
  | Extra__ActualActualBond' !Schedule
  | Extra__ActualActualISMA' !Schedule

$(deriveCrossEnum CrossEnumSpec
    { crossTypeName = "DayCounterConstructor"
    , crossMapperFn = "mapDayCounter"
    , crossMainEnum = ''DayCounterType
    , crossSubSuffix = "Convention"
    , crossExtraType = ''DayCounterExtra
    })

deriving instance Show DayCounterConstructor
deriving instance Eq DayCounterConstructor

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
