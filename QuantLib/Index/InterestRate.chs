{-# LANGUAGE TemplateHaskell, StandaloneDeriving #-}
-- suppress warnings about unused Extra_ constructors
{-# OPTIONS_GHC -Wno-unused-top-binds #-}
module QuantLib.Index.InterestRate
  (
    InterestRateIndex
  , BMAIndex
  , OvernightIborIndex
  , IborIndex
  , SwapIndex
  , OvernightIndexedSwapIndex
  , GenInterestRateIndex
  , GenIborIndex
  , GenSwapIndex

  , bmaIndex

  , fixingSchedule
  , forecastFixing
  , currency
  , dayCounter
  , fixingDays
  , tenor

  , asInterestRateIndex
  , asIborIndex
  , asSwapIndex

  , OvernightIborIndexType(..)
  , overnightIborIndex

  , LiborSwapIndexType(..)
  , liborSwapIndex

  , overnightIndexedSwapIndex
  , swapIndex
  , swapIndex'

  , IborConstructor(..)
  , iborIndex
  , overnightIndex
  , businessDayConvention
  , endOfMonth

  , underlyingSwap
  , underlyingOIS
  ) where
import QuantLib.Internal
import QuantLib.Internal.Syntax
{#import QuantLib.Time.Schedule#}(TimeUnit(..))
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
import QuantLib.Internal.Type
-- Plain (non-c2hs) import: QuantLib.CashFlow is later in exposed-modules than
-- this file, so a {#import#} here would need its .chi before it exists.
-- overnightIndexedSwapIndex below marshals RateAveragingType as a plain Int
-- via fromEnum instead, per CLAUDE.md's cross-module enum-import workaround.
import QuantLib.CashFlow (RateAveragingType)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Currency foreign -> CCurrency nocode#}

{#pointer *QlInterestRateIndex as InterestRateIndex foreign -> CInterestRateIndex' nocode#}
{#pointer *QlBMAIndex as BMAIndex foreign -> CBMAIndex' nocode#}
{#pointer *QlOvernightIndex as OvernightIndex foreign -> COvernightIndex' nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}
{#pointer *QlIndex as Index foreign -> CIndex' nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign -> CSwapIndex' nocode#}
{#pointer *QlOvernightIndex as OvernightIborIndex foreign -> COvernightIndex' nocode#}
{#pointer *QlOvernightIndexedSwapIndex as OvernightIndexedSwapIndex foreign -> COvernightIndexedSwapIndex' nocode#}

{#pointer *QlVanillaSwap as VanillaSwap foreign -> CVanillaSwap' nocode#}
{#pointer *QlOvernightIndexedSwap as OvernightIndexedSwap foreign -> COvernightIndexedSwap' nocode#}

{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}

{#enum OvernightIborIndexType{} deriving (Show, Eq)#}
{#enum LiborSwapIndexType{} deriving (Show, Eq)#}
{#enum IborIndexType{} add prefix = "Ibor__" deriving (Show, Eq)#}
{#enum IborDailyTenorIndexType{} add prefix = "Ibor__" deriving (Show, Eq)#}
{#enum IborONIndexType{} add prefix = "Ibor__" deriving (Show, Eq)#}

-- non-enum-ordinal IborConstructor cases -- convenience shortcuts and the fully generic
-- constructors -- merged into IborConstructor by deriveIborConstructor below, alongside the
-- plain-tenor/daily-tenor/overnight cases generated straight from IborIndexType/
-- IborDailyTenorIndexType/IborONIndexType
data IborExtra =
      Extra__Ibor String -- ^familyName
      (Word, TimeUnit) -- ^tenor
      Word -- ^settlementDays
      Currency
      Calendar -- ^fixingCalendar
      BusinessDayConvention
      Bool -- ^endOfMonth
      DayCounter
    | Extra__Libor String (Word, TimeUnit) Word -- ^settlementDays
      Currency Calendar DayCounter
    | Extra__DailyTenorLibor String Word -- ^settlementDays
      Currency Calendar DayCounter
    -- convenience shortcuts
    | Extra__Bbsw1M
    | Extra__Bbsw2M
    | Extra__Bbsw3M
    | Extra__Bbsw4M
    | Extra__Bbsw5M
    | Extra__Bbsw6M

    | Extra__BiborSW
    | Extra__Bibor1M
    | Extra__Bibor2M
    | Extra__Bibor3M
    | Extra__Bibor6M
    | Extra__Bibor9M
    | Extra__Bibor1Y

    | Extra__Bkbm1M
    | Extra__Bkbm2M
    | Extra__Bkbm3M
    | Extra__Bkbm4M
    | Extra__Bkbm5M
    | Extra__Bkbm6M

    | Extra__EuriborSW
    | Extra__Euribor2W
    | Extra__Euribor3W
    | Extra__Euribor1M
    | Extra__Euribor2M
    | Extra__Euribor3M
    | Extra__Euribor4M
    | Extra__Euribor5M
    | Extra__Euribor6M
    | Extra__Euribor7M
    | Extra__Euribor8M
    | Extra__Euribor9M
    | Extra__Euribor10M
    | Extra__Euribor11M
    | Extra__Euribor1Y

    | Extra__Euribor365_SW
    | Extra__Euribor365_2W
    | Extra__Euribor365_3W
    | Extra__Euribor365_1M
    | Extra__Euribor365_2M
    | Extra__Euribor365_3M
    | Extra__Euribor365_4M
    | Extra__Euribor365_5M
    | Extra__Euribor365_6M
    | Extra__Euribor365_7M
    | Extra__Euribor365_8M
    | Extra__Euribor365_9M
    | Extra__Euribor365_10M
    | Extra__Euribor365_11M
    | Extra__Euribor365_1Y

    | Extra__EurLiborSW
    | Extra__EurLibor2W
    | Extra__EurLibor1M
    | Extra__EurLibor2M
    | Extra__EurLibor3M
    | Extra__EurLibor4M
    | Extra__EurLibor5M
    | Extra__EurLibor6M
    | Extra__EurLibor7M
    | Extra__EurLibor8M
    | Extra__EurLibor9M
    | Extra__EurLibor10M
    | Extra__EurLibor11M
    | Extra__EurLibor1Y

$(deriveIborConstructor "IborConstructor" "iborIndexOrdinal" "iborIndexTenor"
  ''IborIndexType ''IborDailyTenorIndexType ''IborONIndexType ''IborExtra)

deriving instance Show IborConstructor
deriving instance Eq IborConstructor

iborIndex :: IborConstructor -> Maybe (GenYieldTermStructure y) -> IO IborIndex
iborIndex (Ibor n p s cr ca bd b dc) ts = qlIborIndex n p s cr ca bd b dc ts
iborIndex (Libor n p s cr ca dc) ts = qlLibor n p s cr ca dc ts
iborIndex (DailyTenorLibor n c cr ca dc) ts = qlDailyTenorLibor n c cr ca dc ts
iborIndex Bbsw1M ts = iborIndex (Bbsw (1, Months)) ts
iborIndex Bbsw2M ts = iborIndex (Bbsw (2, Months)) ts
iborIndex Bbsw3M ts = iborIndex (Bbsw (3, Months)) ts
iborIndex Bbsw4M ts = iborIndex (Bbsw (4, Months)) ts
iborIndex Bbsw5M ts = iborIndex (Bbsw (5, Months)) ts
iborIndex Bbsw6M ts = iborIndex (Bbsw (6, Months)) ts
iborIndex BiborSW ts = iborIndex (Bibor (1, Weeks)) ts
iborIndex Bibor1M ts = iborIndex (Bibor (1, Months)) ts
iborIndex Bibor2M ts = iborIndex (Bibor (2, Months)) ts
iborIndex Bibor3M ts = iborIndex (Bibor (3, Months)) ts
iborIndex Bibor6M ts = iborIndex (Bibor (6, Months)) ts
iborIndex Bibor9M ts = iborIndex (Bibor (9, Months)) ts
iborIndex Bibor1Y ts = iborIndex (Bibor (1, Years)) ts
iborIndex Bkbm1M ts = iborIndex (Bkbm (1, Months)) ts
iborIndex Bkbm2M ts = iborIndex (Bkbm (2, Months)) ts
iborIndex Bkbm3M ts = iborIndex (Bkbm (3, Months)) ts
iborIndex Bkbm4M ts = iborIndex (Bkbm (4, Months)) ts
iborIndex Bkbm5M ts = iborIndex (Bkbm (5, Months)) ts
iborIndex Bkbm6M ts = iborIndex (Bkbm (6, Months)) ts
iborIndex EuriborSW ts = iborIndex (Euribor (1, Weeks)) ts
iborIndex Euribor2W ts = iborIndex (Euribor (2, Weeks)) ts
iborIndex Euribor3W ts = iborIndex (Euribor (3, Weeks)) ts
iborIndex Euribor1M ts = iborIndex (Euribor (1, Months)) ts
iborIndex Euribor2M ts = iborIndex (Euribor (2, Months)) ts
iborIndex Euribor3M ts = iborIndex (Euribor (3, Months)) ts
iborIndex Euribor4M ts = iborIndex (Euribor (4, Months)) ts
iborIndex Euribor5M ts = iborIndex (Euribor (5, Months)) ts
iborIndex Euribor6M ts = iborIndex (Euribor (6, Months)) ts
iborIndex Euribor7M ts = iborIndex (Euribor (7, Months)) ts
iborIndex Euribor8M ts = iborIndex (Euribor (8, Months)) ts
iborIndex Euribor9M ts = iborIndex (Euribor (9, Months)) ts
iborIndex Euribor10M ts = iborIndex (Euribor (10, Months)) ts
iborIndex Euribor11M ts = iborIndex (Euribor (11, Months)) ts
iborIndex Euribor1Y ts = iborIndex (Euribor (1, Years)) ts
iborIndex Euribor365_SW ts = iborIndex (Euribor (365, Weeks)) ts
iborIndex Euribor365_2W ts = iborIndex (Euribor365 (2, Weeks)) ts
iborIndex Euribor365_3W ts = iborIndex (Euribor365 (3, Weeks)) ts
iborIndex Euribor365_1M ts = iborIndex (Euribor365 (1, Months)) ts
iborIndex Euribor365_2M ts = iborIndex (Euribor365 (2, Months)) ts
iborIndex Euribor365_3M ts = iborIndex (Euribor365 (3, Months)) ts
iborIndex Euribor365_4M ts = iborIndex (Euribor365 (4, Months)) ts
iborIndex Euribor365_5M ts = iborIndex (Euribor365 (5, Months)) ts
iborIndex Euribor365_6M ts = iborIndex (Euribor365 (6, Months)) ts
iborIndex Euribor365_7M ts = iborIndex (Euribor365 (7, Months)) ts
iborIndex Euribor365_8M ts = iborIndex (Euribor365 (8, Months)) ts
iborIndex Euribor365_9M ts = iborIndex (Euribor365 (9, Months)) ts
iborIndex Euribor365_10M ts = iborIndex (Euribor365 (10, Months)) ts
iborIndex Euribor365_11M ts = iborIndex (Euribor365 (11, Months)) ts
iborIndex Euribor365_1Y ts = iborIndex (Euribor365 (1, Years)) ts
iborIndex EurLiborSW ts = iborIndex (EurLibor (1, Weeks)) ts
iborIndex EurLibor2W ts = iborIndex (EurLibor (2, Weeks)) ts
iborIndex EurLibor1M ts = iborIndex (EurLibor (1, Months)) ts
iborIndex EurLibor2M ts = iborIndex (EurLibor (2, Months)) ts
iborIndex EurLibor3M ts = iborIndex (EurLibor (3, Months)) ts
iborIndex EurLibor4M ts = iborIndex (EurLibor (4, Months)) ts
iborIndex EurLibor5M ts = iborIndex (EurLibor (5, Months)) ts
iborIndex EurLibor6M ts = iborIndex (EurLibor (6, Months)) ts
iborIndex EurLibor7M ts = iborIndex (EurLibor (7, Months)) ts
iborIndex EurLibor8M ts = iborIndex (EurLibor (8, Months)) ts
iborIndex EurLibor9M ts = iborIndex (EurLibor (9, Months)) ts
iborIndex EurLibor10M ts = iborIndex (EurLibor (10, Months)) ts
iborIndex EurLibor11M ts = iborIndex (EurLibor (11, Months)) ts
iborIndex EurLibor1Y ts = iborIndex (EurLibor (1, Years)) ts
iborIndex c ts = qlCreateIbor (iborIndexOrdinal c) (iborIndexTenor c) ts

{#fun qlBMAIndex as bmaIndex{withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`BMAIndex'peekBMAIndex*#}
-- |This method returns a schedule of fixing dates between start and end.
{#fun qlBMAIndexFixingSchedule as fixingSchedule{withBMAIndex*`BMAIndex',withDay*`Day',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Schedule'peekSchedule*#}
-- |It can be overridden to implement particular conventions.
{#fun qlInterestRateIndexForecastFixing as forecastFixing{withInterestRateIndex*`GenInterestRateIndex a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlInterestRateIndexCurrency as currency{withInterestRateIndex*`GenInterestRateIndex a',preErrorCheck-`String'errorCheck*-}->`Currency'peekCurrency*#}
{#fun qlInterestRateIndexDayCounter as dayCounter{withInterestRateIndex*`GenInterestRateIndex a',preErrorCheck-`String'errorCheck*-}->`DayCounter'peekDayCounter*#}
{#fun pure qlInterestRateIndexFixingDays as fixingDays{withInterestRateIndex*`GenInterestRateIndex a'}->`Word'fromIntegral#}
{#fun qlInterestRateIndexTenor as tenor{withInterestRateIndex*`GenInterestRateIndex a',preEnum-`TimeUnit'peekEnum*,preErrorCheck-`String'errorCheck*-}->`Word'fromIntegral#}
{#fun qlCreateONIndex as overnightIborIndex{`OvernightIborIndexType',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`OvernightIborIndex'peekOvernightIborIndex*#}
{#fun qlCreateLiborSwapIndex as liborSwapIndex{`LiborSwapIndexType',fromEnumQuantity`(Int,TimeUnit)'&
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure f)' -- ^forwarding
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure d)' -- ^discounting
  ,preErrorCheck-`String'errorCheck*-}->`SwapIndex'peekSwapIndex*#}
-- | Construct an overnight-indexed swap index.
overnightIndexedSwapIndex :: String -> (Int, TimeUnit) -> Word -> Currency
  -> OvernightIborIndex -> Bool -> RateAveragingType -> IO OvernightIndexedSwapIndex
overnightIndexedSwapIndex familyName tenr settlementDays ccy idx telescopicValueDates averagingMethod =
  overnightIndexedSwapIndex_ familyName tenr settlementDays ccy idx telescopicValueDates (fromEnum averagingMethod)

{#fun qlOvernightIndexedSwapIndex as overnightIndexedSwapIndex_{`String',fromEnumQuantity`(Int,TimeUnit)'&,fromIntegral`Word' -- ^settlementDays
  ,withCurrency*`Currency',withOvernightIborIndex*`OvernightIborIndex'
  ,`Bool' -- ^telescopicValueDates
  ,`Int' -- ^averagingMethod
  ,preErrorCheck-`String'errorCheck*-}->`OvernightIndexedSwapIndex'peekOvernightIndexedSwapIndex*#}
{#fun qlSwapIndex as swapIndex{`String',fromEnumQuantity`(Int,TimeUnit)'&,fromIntegral`Word' -- ^settlementDays
  ,withCurrency*`Currency',withCalendar*`Calendar',fromEnumQuantity`(Int,TimeUnit)'& -- ^fixedLegTenor
  ,`BusinessDayConvention',withDayCounter*`DayCounter',withIborIndex*`GenIborIndex a',preErrorCheck-`String'errorCheck*-}->`SwapIndex'peekSwapIndex*#}
{#fun qlSwapIndex1 as swapIndex'{`String' -- ^familyName
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^settlementDays
  ,withCurrency*`Currency',withCalendar*`Calendar',fromEnumQuantity`(Int,TimeUnit)'& -- ^fixedLegTenor
  ,`BusinessDayConvention' -- ^fixedLegConvention
  ,withDayCounter*`DayCounter' -- ^fixedLegDayCounter
  ,withIborIndex*`GenIborIndex a',withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`SwapIndex'peekSwapIndex*#}

{#fun qlIborIndex{`String' -- ^familyName
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^settlementDays
  ,withCurrency*`Currency',withCalendar*`Calendar',`BusinessDayConvention'
  ,`Bool' -- ^endOfMonth
  ,withDayCounter*`DayCounter',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`IborIndex'peekIborIndex*#}
{#fun qlLibor{`String' -- ^familyName
  ,fromEnumQuantity`(Word,TimeUnit)'&,fromIntegral`Word' -- settlementDays
  ,withCurrency*`Currency',withCalendar*`Calendar',withDayCounter*`DayCounter',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`IborIndex'peekIborIndex*#}
{#fun qlDailyTenorLibor{`String' -- ^familyName
  ,fromIntegral`Word' -- ^settlementDays
  ,withCurrency*`Currency',withCalendar*`Calendar',withDayCounter*`DayCounter',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`IborIndex'peekIborIndex*#}
{#fun qlCreateIbor{fromIntegral`Int',fromEnumQuantity`(Word,TimeUnit)'&,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`IborIndex'peekIborIndex*#}
{#fun qlOvernightIndex as overnightIndex{`String',fromIntegral`Word' -- ^settlementDays
  ,withCurrency*`Currency',withCalendar*`Calendar',withDayCounter*`DayCounter',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`OvernightIborIndex'peekOvernightIborIndex*#}
{#fun pure qlIborIndexBusinessDayConvention as businessDayConvention{withIborIndex*`GenIborIndex a'}->`BusinessDayConvention'#}
{#fun pure qlIborIndexEndOfMonth as endOfMonth{withIborIndex*`GenIborIndex a'}->`Bool'#}
{#fun qlOvernightIndexedSwapIndexUnderlyingSwap as underlyingOIS {withOvernightIndexedSwapIndex*`OvernightIndexedSwapIndex',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`OvernightIndexedSwap'peekOvernightIndexedSwap*#}
{#fun qlSwapIndexUnderlyingSwap as underlyingSwap{withSwapIndex*`GenSwapIndex a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`VanillaSwap'peekVanillaSwap*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
