module QuantLib.Calendar
  (
   JointCalendarRule(..)
  , CalendarConstructor(..)
  , AustriaMarket(..)
  , BrazilMarket(..)
  , CanadaMarket(..)
  , ChinaMarket(..)
  , FranceMarket(..)
  , GermanyMarket(..)
  , IndonesiaMarket(..)
  , IsraelMarket(..)
  , ItalyMarket(..)
  , RomaniaMarket(..)
  , RussiaMarket(..)
  , SouthKoreaMarket(..)
  , UnitedKingdomMarket(..)
  , UnitedStatesMarket(..)
  , calendar
  , adjust
  , advance
  , addHoliday
  , advance'
  , businessDaysBetween
  , endOfMonth
  , isBusinessDay
  , isEndOfMonth
  , isHoliday
  , isWeekend
  , removeHoliday
  , holidays
  )
  where

import QuantLib.Type
import QuantLib.Utility
{#import QuantLib.Date #}(Day, fromDay, toDay, BusinessDayConvention, Weekday, peekDayArray)
{#import QuantLib.Period #}

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum JointCalendarRule {} deriving(Show, Eq, Bounded) #}

{#enum CalendarCountry {} deriving(Show, Eq, Bounded) #}

{#enum AustriaMarket {} deriving(Show, Eq, Bounded) #}
{#enum BrazilMarket {} deriving(Show, Eq, Bounded) #}
{#enum CanadaMarket {} deriving(Show, Eq, Bounded) #}
{#enum ChinaMarket {} deriving(Show, Eq, Bounded) #}
{#enum FranceMarket {} deriving(Show, Eq, Bounded) #}
{#enum GermanyMarket {} deriving(Show, Eq, Bounded) #}
{#enum IndonesiaMarket {} deriving(Show, Eq, Bounded) #}
{#enum IsraelMarket {} deriving(Show, Eq, Bounded) #}
{#enum ItalyMarket {} deriving(Show, Eq, Bounded) #}
{#enum RomaniaMarket {} deriving(Show, Eq, Bounded) #}
{#enum RussiaMarket {} deriving(Show, Eq, Bounded) #}
{#enum SouthKoreaMarket {} deriving(Show, Eq, Bounded) #}
{#enum UnitedKingdomMarket {} deriving(Show, Eq, Bounded) #}
{#enum UnitedStatesMarket {} deriving(Show, Eq, Bounded) #}

data CalendarConstructor = Argentina
  | Australia
  | Austria AustriaMarket
  | Botswana
  | Brazil BrazilMarket
  | Canada CanadaMarket
  | China ChinaMarket
  | CzechRepublic
  | Denmark
  | Finland
  | France FranceMarket
  | Germany GermanyMarket
  | HongKong
  | Hungary
  | Iceland
  | India
  | Indonesia IndonesiaMarket
  | Israel IsraelMarket
  | Italy ItalyMarket
  | Japan
  | Mexico
  | NewZealand
  | Norway
  | NullCalendar
  | Poland
  | Romania RomaniaMarket
  | Russia RussiaMarket
  | SaudiArabia
  | Singapore
  | Slovakia
  | SouthAfrica
  | SouthKorea SouthKoreaMarket
  | Sweden
  | Switzerland
  | Taiwan
  | TARGET
  | Thailand
  | Turkey
  | Ukraine
  | UnitedKingdom UnitedKingdomMarket
  | UnitedStates UnitedStatesMarket
  | WeekendsOnly
  | Bespoke String [Weekday]
  | Joint2 Calendar Calendar JointCalendarRule
  | Joint3 Calendar Calendar Calendar JointCalendarRule
  | Joint4 Calendar Calendar Calendar Calendar JointCalendarRule
  deriving (Show, Eq)

country :: CalendarConstructor -> CalendarCountry
country Argentina = CountryArgentina
country Australia = CountryAustralia
country (Austria _) = CountryAustria
country Botswana = CountryBotswana
country (Brazil _) = CountryBrazil
country (Canada _) = CountryCanada
country (China _) = CountryChina
country CzechRepublic = CountryCzechRepublic
country Denmark = CountryDenmark
country Finland = CountryFinland
country (France _) = CountryFrance
country (Germany _) = CountryGermany
country HongKong = CountryHongKong
country Hungary = CountryHungary
country Iceland = CountryIceland
country India = CountryIndia
country (Indonesia _) = CountryIndonesia
country (Israel _) = CountryIsrael
country (Italy _) = CountryItaly
country Japan = CountryJapan
country Mexico = CountryMexico
country NewZealand = CountryNewZealand
country Norway = CountryNorway
country NullCalendar = CountryNullCalendar
country Poland = CountryPoland
country (Romania _) = CountryRomania
country (Russia _) = CountryRussia
country SaudiArabia = CountrySaudiArabia
country Singapore = CountrySingapore
country Slovakia = CountrySlovakia
country SouthAfrica = CountrySouthAfrica
country (SouthKorea _) = CountrySouthKorea
country Sweden = CountrySweden
country Switzerland = CountrySwitzerland
country Taiwan = CountryTaiwan
country TARGET = CountryTARGET
country Thailand = CountryThailand
country Turkey = CountryTurkey
country Ukraine = CountryUkraine
country (UnitedKingdom _) = CountryUnitedKingdom
country (UnitedStates _) = CountryUnitedStates
country WeekendsOnly = CountryWeekendsOnly
country x = error ("Internal error: no country defined for calendar " ++ (show x))

market :: CalendarConstructor -> Int
market (Austria x) = fromEnum x
market (Brazil x) = fromEnum x
market (Canada x) = fromEnum x
market (China x) = fromEnum x
market (France x) = fromEnum x
market (Germany x) = fromEnum x
market (Indonesia x) = fromEnum x
market (Israel x) = fromEnum x
market (Italy x) = fromEnum x
market (Romania x) = fromEnum x
market (Russia x) = fromEnum x
market (SouthKorea x) = fromEnum x
market (UnitedKingdom x) = fromEnum x
market (UnitedStates x) = fromEnum x
market _ = {#const NO_MARKET #}

{#pointer *Calendar foreign finalizer qlFreeCalendar newtype #}

instance ForeignObject Calendar where
  withObject = withCalendar
  
{#fun pure qlCalendarName {`Calendar'} -> `String' peekDynString* #}

instance Named Calendar where
  name = qlCalendarName

instance Show Calendar where
  show = name

instance Eq Calendar where
  x == y = name x == name y

{#fun qlCalendar {`CalendarCountry', `Int', preErrorCheck- `String' errorCheck*-} -> `Calendar' #}

calendar :: CalendarConstructor -> IO Calendar
calendar (Bespoke n w) = qlBespokeCalendar n w
calendar (Joint2 c1 c2 r) = qlJointCalendar2 c1 c2 r
calendar (Joint3 c1 c2 c3 r) = qlJointCalendar3 c1 c2 c3 r
calendar (Joint4 c1 c2 c3 c4 r) = qlJointCalendar4 c1 c2 c3 c4 r
calendar x = qlCalendar (country x) (market x)

-- |Adjusts a non-business day to the appropriate near business day with respect to the given convention
{#fun qlCalendarAdjust as adjust {`Calendar', fromDay* `Day', `BusinessDayConvention'} -> `Day' toDay #}

-- |Advances the given date of the given number of business days and returns the result
{#fun qlCalendarAdvance as advance {`Calendar', fromDay* `Day', `Int', `TimeUnit', `BusinessDayConvention', `Bool'} -> `Day' toDay #}

-- |Adds a date to the set of holidays for the given calendar.
{#fun qlCalendarAddHoliday as addHoliday {`Calendar', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `()' #}

-- |Advances the given date as specified by the given period and returns the result. The input date is not modified.
{#fun qlCalendarAdvance1 as advance' {`Calendar', fromDay* `Day', fromPeriod `Int, TimeUnit'&, `BusinessDayConvention', `Bool', preErrorCheck- `String' errorCheck*-} -> `Day' toDay #}

-- |Calculates the number of business days between two given dates and returns the result.
{#fun qlCalendarBusinessDaysBetween as businessDaysBetween {`Calendar', fromDay* `Day', fromDay* `Day', `Bool', `Bool', preErrorCheck- `String' errorCheck*-} -> `Int' #}

-- |last business day of the month to which the given date belongs
{#fun qlCalendarEndOfMonth as endOfMonth {`Calendar', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Day' toDay #}

-- |Returns true iff the date is a business day for the given market.
{#fun qlCalendarIsBusinessDay as isBusinessDay {`Calendar', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Bool' #}

-- |Returns true iff the date is last business day for the month in given market.
{#fun qlCalendarIsEndOfMonth as isEndOfMonth {`Calendar', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Bool' #}

-- |Returns true iff the date is a holiday for the given market.
{#fun qlCalendarIsHoliday as isHoliday {`Calendar', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Bool' #}

-- |Returns true iff the weekday is part of the weekend for the given market.
{#fun qlCalendarIsWeekend as isWeekend {`Calendar', `Weekday', preErrorCheck- `String' errorCheck*-} -> `Bool' #}

-- |Removes a date from the set of holidays for the given calendar.
{#fun qlCalendarRemoveHoliday as removeHoliday {`Calendar', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `()' #}

{#fun qlBespokeCalendar {`String', withEnumArray* `[Weekday]'&, preErrorCheck- `String' errorCheck*-} -> `Calendar' #}

{#fun qlJointCalendar3 {`Calendar', `Calendar', `Calendar', `JointCalendarRule', preErrorCheck- `String' errorCheck*-} -> `Calendar' #}

{#fun qlJointCalendar2 {`Calendar', `Calendar', `JointCalendarRule', preErrorCheck- `String' errorCheck*-} -> `Calendar' #}

{#fun qlJointCalendar4 {`Calendar', `Calendar', `Calendar', `Calendar', `JointCalendarRule', preErrorCheck- `String' errorCheck*-} -> `Calendar' #}

-- |Returns the holidays between two dates.
{#fun qlCalendarHolidayList as holidays {`Calendar', fromDay* `Day', fromDay* `Day', `Bool', preArray- `[Day]'& peekDayArray*, preErrorCheck- `String' errorCheck*-} -> `()' #}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
