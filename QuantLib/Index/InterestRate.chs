{-# LANGUAGE TemplateHaskell, StandaloneDeriving, PatternSynonyms #-}
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

  -- The bundled names are the fixed-tenor shortcut pattern synonyms defined below;
  -- @Euribor3M@ and @Euribor (3, Months)@ are the same value, usable interchangeably
  -- in expressions and in patterns.
  , IborConstructor(.., Bbsw1M, Bbsw2M, Bbsw3M, Bbsw4M, Bbsw5M, Bbsw6M
                      , BiborSW, Bibor1M, Bibor2M, Bibor3M, Bibor6M, Bibor9M, Bibor1Y
                      , Bkbm1M, Bkbm2M, Bkbm3M, Bkbm4M, Bkbm5M, Bkbm6M
                      , EuriborSW, Euribor2W, Euribor3W
                      , Euribor1M, Euribor2M, Euribor3M, Euribor4M, Euribor5M, Euribor6M
                      , Euribor7M, Euribor8M, Euribor9M, Euribor10M, Euribor11M, Euribor1Y
                      , Euribor365_SW, Euribor365_2W, Euribor365_3W
                      , Euribor365_1M, Euribor365_2M, Euribor365_3M, Euribor365_4M
                      , Euribor365_5M, Euribor365_6M, Euribor365_7M, Euribor365_8M
                      , Euribor365_9M, Euribor365_10M, Euribor365_11M, Euribor365_1Y
                      , EurLiborSW, EurLibor2W
                      , EurLibor1M, EurLibor2M, EurLibor3M, EurLibor4M, EurLibor5M, EurLibor6M
                      , EurLibor7M, EurLibor8M, EurLibor9M, EurLibor10M, EurLibor11M, EurLibor1Y)
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

-- the fully generic, non-enum-ordinal IborConstructor cases, merged into IborConstructor by
-- deriveIborConstructor below alongside the plain-tenor/daily-tenor/overnight cases generated
-- straight from IborIndexType/IborDailyTenorIndexType/IborONIndexType
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
    | Extra__CustomIbor String -- ^familyName
      (Word, TimeUnit) -- ^tenor
      Word -- ^settlementDays
      Currency
      Calendar -- ^fixingCalendar
      Calendar -- ^valueCalendar
      Calendar -- ^maturityCalendar
      BusinessDayConvention
      Bool -- ^endOfMonth
      DayCounter

$(deriveIborConstructor IborConstructorSpec
    { iborTypeName = "IborConstructor"
    , iborOrdinalFn = "iborIndexOrdinal"
    , iborTenorFn = "iborIndexTenor"
    , iborTenorEnum = ''IborIndexType
    , iborDailyTenorEnum = ''IborDailyTenorIndexType
    , iborOvernightEnum = ''IborONIndexType
    , iborExtraType = ''IborExtra
    })

deriving instance Show IborConstructor
deriving instance Eq IborConstructor

-- Fixed-tenor shortcuts, mirroring upstream's thin @Euribor3M@-style subclasses (whose
-- constructors only delegate to the parameterized one). They are bidirectional pattern
-- synonyms, not constructors: each is *defined* as the parameterized case it stands for,
-- so there is a single list to keep right and no separate dispatch clause that can drift
-- out of step with it -- @Euribor365_SW@ used to expand, via such a clause, to
-- @Euribor (365, Weeks)@: wrong family and wrong tenor both.
pattern Bbsw1M, Bbsw2M, Bbsw3M, Bbsw4M, Bbsw5M, Bbsw6M :: IborConstructor
pattern Bbsw1M = Bbsw (1, Months)
pattern Bbsw2M = Bbsw (2, Months)
pattern Bbsw3M = Bbsw (3, Months)
pattern Bbsw4M = Bbsw (4, Months)
pattern Bbsw5M = Bbsw (5, Months)
pattern Bbsw6M = Bbsw (6, Months)

pattern BiborSW, Bibor1M, Bibor2M, Bibor3M, Bibor6M, Bibor9M, Bibor1Y :: IborConstructor
pattern BiborSW = Bibor (1, Weeks)
pattern Bibor1M = Bibor (1, Months)
pattern Bibor2M = Bibor (2, Months)
pattern Bibor3M = Bibor (3, Months)
pattern Bibor6M = Bibor (6, Months)
pattern Bibor9M = Bibor (9, Months)
pattern Bibor1Y = Bibor (1, Years)

pattern Bkbm1M, Bkbm2M, Bkbm3M, Bkbm4M, Bkbm5M, Bkbm6M :: IborConstructor
pattern Bkbm1M = Bkbm (1, Months)
pattern Bkbm2M = Bkbm (2, Months)
pattern Bkbm3M = Bkbm (3, Months)
pattern Bkbm4M = Bkbm (4, Months)
pattern Bkbm5M = Bkbm (5, Months)
pattern Bkbm6M = Bkbm (6, Months)

pattern EuriborSW, Euribor2W, Euribor3W, Euribor1M, Euribor2M, Euribor3M, Euribor4M
  , Euribor5M, Euribor6M, Euribor7M, Euribor8M, Euribor9M, Euribor10M, Euribor11M
  , Euribor1Y :: IborConstructor
pattern EuriborSW = Euribor (1, Weeks)
pattern Euribor2W = Euribor (2, Weeks)
pattern Euribor3W = Euribor (3, Weeks)
pattern Euribor1M = Euribor (1, Months)
pattern Euribor2M = Euribor (2, Months)
pattern Euribor3M = Euribor (3, Months)
pattern Euribor4M = Euribor (4, Months)
pattern Euribor5M = Euribor (5, Months)
pattern Euribor6M = Euribor (6, Months)
pattern Euribor7M = Euribor (7, Months)
pattern Euribor8M = Euribor (8, Months)
pattern Euribor9M = Euribor (9, Months)
pattern Euribor10M = Euribor (10, Months)
pattern Euribor11M = Euribor (11, Months)
pattern Euribor1Y = Euribor (1, Years)

pattern Euribor365_SW, Euribor365_2W, Euribor365_3W, Euribor365_1M, Euribor365_2M
  , Euribor365_3M, Euribor365_4M, Euribor365_5M, Euribor365_6M, Euribor365_7M
  , Euribor365_8M, Euribor365_9M, Euribor365_10M, Euribor365_11M
  , Euribor365_1Y :: IborConstructor
pattern Euribor365_SW = Euribor365 (1, Weeks)
pattern Euribor365_2W = Euribor365 (2, Weeks)
pattern Euribor365_3W = Euribor365 (3, Weeks)
pattern Euribor365_1M = Euribor365 (1, Months)
pattern Euribor365_2M = Euribor365 (2, Months)
pattern Euribor365_3M = Euribor365 (3, Months)
pattern Euribor365_4M = Euribor365 (4, Months)
pattern Euribor365_5M = Euribor365 (5, Months)
pattern Euribor365_6M = Euribor365 (6, Months)
pattern Euribor365_7M = Euribor365 (7, Months)
pattern Euribor365_8M = Euribor365 (8, Months)
pattern Euribor365_9M = Euribor365 (9, Months)
pattern Euribor365_10M = Euribor365 (10, Months)
pattern Euribor365_11M = Euribor365 (11, Months)
pattern Euribor365_1Y = Euribor365 (1, Years)

pattern EurLiborSW, EurLibor2W, EurLibor1M, EurLibor2M, EurLibor3M, EurLibor4M
  , EurLibor5M, EurLibor6M, EurLibor7M, EurLibor8M, EurLibor9M, EurLibor10M
  , EurLibor11M, EurLibor1Y :: IborConstructor
pattern EurLiborSW = EurLibor (1, Weeks)
pattern EurLibor2W = EurLibor (2, Weeks)
pattern EurLibor1M = EurLibor (1, Months)
pattern EurLibor2M = EurLibor (2, Months)
pattern EurLibor3M = EurLibor (3, Months)
pattern EurLibor4M = EurLibor (4, Months)
pattern EurLibor5M = EurLibor (5, Months)
pattern EurLibor6M = EurLibor (6, Months)
pattern EurLibor7M = EurLibor (7, Months)
pattern EurLibor8M = EurLibor (8, Months)
pattern EurLibor9M = EurLibor (9, Months)
pattern EurLibor10M = EurLibor (10, Months)
pattern EurLibor11M = EurLibor (11, Months)
pattern EurLibor1Y = EurLibor (1, Years)

iborIndex :: IborConstructor -> Maybe (GenYieldTermStructure y) -> IO IborIndex
iborIndex (Ibor n p s cr ca bd b dc) ts = qlIborIndex n p s cr ca bd b dc ts
iborIndex (Libor n p s cr ca dc) ts = qlLibor n p s cr ca dc ts
iborIndex (DailyTenorLibor n c cr ca dc) ts = qlDailyTenorLibor n c cr ca dc ts
iborIndex (CustomIbor n p s cr fc vc mc bd b dc) ts = qlCustomIborIndex n p s cr fc vc mc bd b dc ts
iborIndex c ts = qlCreateIbor (iborIndexOrdinal c) (iborIndexTenor c) ts

{#fun qlBMAIndex as bmaIndex{withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`BMAIndex'peekBMAIndex*#}
-- |This method returns a schedule of fixing dates between start and end.
{#fun qlBMAIndexFixingSchedule as fixingSchedule{withBMAIndex*`BMAIndex',withDay*`Day',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Schedule'peekSchedule*#}
-- |It can be overridden to implement particular conventions.
{#fun qlInterestRateIndexForecastFixing as forecastFixing{withInterestRateIndex*`GenInterestRateIndex ridx',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlInterestRateIndexCurrency as currency{withInterestRateIndex*`GenInterestRateIndex ridx',preErrorCheck-`String'errorCheck*-}->`Currency'peekCurrency*#}
{#fun qlInterestRateIndexDayCounter as dayCounter{withInterestRateIndex*`GenInterestRateIndex ridx',preErrorCheck-`String'errorCheck*-}->`DayCounter'peekDayCounter*#}
{#fun pure qlInterestRateIndexFixingDays as fixingDays{withInterestRateIndex*`GenInterestRateIndex ridx'}->`Word'fromIntegral#}
{#fun qlInterestRateIndexTenor as tenor{withInterestRateIndex*`GenInterestRateIndex ridx',preEnum-`TimeUnit'peekEnum*,preErrorCheck-`String'errorCheck*-}->`Word'fromIntegral#}
{#fun qlCreateONIndex as overnightIborIndex{`OvernightIborIndexType',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`OvernightIborIndex'peekOvernightIborIndex*#}
{#fun qlCreateLiborSwapIndex as liborSwapIndex{`LiborSwapIndexType',fromEnumQuantity`(Int,TimeUnit)'&
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y1)' -- ^forwarding
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y2)' -- ^discounting
  ,preErrorCheck-`String'errorCheck*-}->`SwapIndex'peekSwapIndex*#}
-- | Construct an overnight-indexed swap index.
-- RateAveragingType (QuantLib.CashFlow) is later in exposed-modules than this file,
-- so averagingMethod is marshalled as a plain Int via fromEnum in the unexported
-- glue binding below instead of a {#import#}'d enum type, per CLAUDE.md's
-- cross-module workaround. The public signature stays fully typed.
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
  ,`BusinessDayConvention',withDayCounter*`DayCounter',withIborIndex*`GenIborIndex ibor',preErrorCheck-`String'errorCheck*-}->`SwapIndex'peekSwapIndex*#}
{#fun qlSwapIndex1 as swapIndex'{`String' -- ^familyName
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^settlementDays
  ,withCurrency*`Currency',withCalendar*`Calendar',fromEnumQuantity`(Int,TimeUnit)'& -- ^fixedLegTenor
  ,`BusinessDayConvention' -- ^fixedLegConvention
  ,withDayCounter*`DayCounter' -- ^fixedLegDayCounter
  ,withIborIndex*`GenIborIndex ibor',withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`SwapIndex'peekSwapIndex*#}

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
{#fun qlCustomIborIndex{`String' -- ^familyName
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^tenor
  ,fromIntegral`Word' -- ^settlementDays
  ,withCurrency*`Currency',withCalendar*`Calendar' -- ^fixingCalendar
  ,withCalendar*`Calendar' -- ^valueCalendar
  ,withCalendar*`Calendar' -- ^maturityCalendar
  ,`BusinessDayConvention'
  ,`Bool' -- ^endOfMonth
  ,withDayCounter*`DayCounter',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`IborIndex'peekIborIndex*#}
{#fun qlCreateIbor{fromIntegral`Int',fromEnumQuantity`(Word,TimeUnit)'&,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`IborIndex'peekIborIndex*#}
{#fun qlOvernightIndex as overnightIndex{`String',fromIntegral`Word' -- ^settlementDays
  ,withCurrency*`Currency',withCalendar*`Calendar',withDayCounter*`DayCounter',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)',preErrorCheck-`String'errorCheck*-}->`OvernightIborIndex'peekOvernightIborIndex*#}
{#fun pure qlIborIndexBusinessDayConvention as businessDayConvention{withIborIndex*`GenIborIndex ibor'}->`BusinessDayConvention'#}
{#fun pure qlIborIndexEndOfMonth as endOfMonth{withIborIndex*`GenIborIndex ibor'}->`Bool'#}
{#fun qlOvernightIndexedSwapIndexUnderlyingSwap as underlyingOIS {withOvernightIndexedSwapIndex*`OvernightIndexedSwapIndex',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`OvernightIndexedSwap'peekOvernightIndexedSwap*#}
{#fun qlSwapIndexUnderlyingSwap as underlyingSwap{withSwapIndex*`GenSwapIndex sidx',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`VanillaSwap'peekVanillaSwap*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
