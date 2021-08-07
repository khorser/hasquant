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
  )
  where

import QuantLib.Type
import QuantLib.Utility

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

{#fun qlCalendar {`CalendarCountry', `Int', preErrorCheck- `String' errorCheck*-} -> `Calendar' #}

calendar :: CalendarConstructor -> IO Calendar
calendar x = qlCalendar (country x) (market x)

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
