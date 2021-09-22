{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts, FunctionalDependencies, FlexibleInstances #-}
module QuantLib.Index.InterestRate
  (
    InterestRateIndex
  , BMAIndex
  , OvernightIborIndex
  , IborIndex
  , SwapIndex
  , OvernightIndexedSwapIndex

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

  , underlying
  )
  where

import QuantLib.Internal
import QuantLib.Type
import Control.Exception(throwIO)
{#import QuantLib.Time.Schedule#}(TimeUnit(..))
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Currency foreign -> CCurrency nocode#}

{#pointer *QlInterestRateIndex as InterestRateIndex foreign -> CInterestRateIndex nocode#}

{#pointer *QlBMAIndex as BMAIndex foreign -> CBMAIndex nocode#}

{#pointer *QlOvernightIndex as OvernightIndex foreign -> COvernightIndex nocode#}

{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex nocode#}

{#pointer *QlIndex as Index foreign -> CIndex nocode#}

{#pointer *QlSwapIndex as SwapIndex foreign -> CSwapIndex nocode#}

{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure nocode#}

{#pointer *QlOvernightIndex as OvernightIborIndex foreign -> COvernightIndex nocode#}

{#pointer *QlOvernightIndexedSwapIndex as OvernightIndexedSwapIndex foreign -> COvernightIndexedSwapIndex nocode#}

{#pointer *QlVanillaSwap as VanillaSwap foreign -> CVanillaSwap nocode#}

{#pointer *QlOvernightIndexedSwap as OvernightIndexedSwap foreign -> COvernightIndexedSwap nocode#}

{#fun qlBMAIndex as bmaIndex{withMaybeYieldTermStructure*`Maybe YieldTermStructure', preErrorCheck-`String'errorCheck*-}->`BMAIndex'peekBMAIndex*#}

-- |This method returns a schedule of fixing dates between start and end.
{#fun qlBMAIndexFixingSchedule as fixingSchedule{withBMAIndex*`BMAIndex', withDay*`Day', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Schedule'peekSchedule*#}

-- |It can be overridden to implement particular conventions.
{#fun qlInterestRateIndexForecastFixing as forecastFixing{withInterestRateIndex*`GenInterestRateIndex a', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlInterestRateIndexCurrency as currency{withInterestRateIndex*`GenInterestRateIndex a', preErrorCheck-`String'errorCheck*-}->`Currency'peekCurrency*#}

{#fun qlInterestRateIndexDayCounter as dayCounter{withInterestRateIndex*`GenInterestRateIndex a', preErrorCheck-`String'errorCheck*-}->`DayCounter'peekDayCounter*#}

{#fun pure qlInterestRateIndexFixingDays as fixingDays{withInterestRateIndex*`GenInterestRateIndex a'}->`Word'fromIntegral#}

{#fun qlInterestRateIndexTenor as tenor{withInterestRateIndex*`GenInterestRateIndex a', preEnum-`TimeUnit'peekEnum*, preErrorCheck-`String'errorCheck*-}->`Word'fromIntegral#}

{#enum OvernightIborIndexType{} deriving (Show, Eq)#}

{#fun qlCreateONIndex as overnightIborIndex{`OvernightIborIndexType', withMaybeYieldTermStructure*`Maybe YieldTermStructure', preErrorCheck-`String'errorCheck*-}->`OvernightIborIndex'peekOvernightIborIndex*#}

{#enum LiborSwapIndexType{} deriving (Show, Eq)#}

{#fun qlCreateLiborSwapIndex as liborSwapIndex{`LiborSwapIndexType', fromEnumQuantity`(Int, TimeUnit)'&, withMaybeYieldTermStructure*`Maybe YieldTermStructure', withMaybeYieldTermStructure*`Maybe YieldTermStructure', preErrorCheck-`String'errorCheck*-}->`SwapIndex'peekSwapIndex*#}

{#fun qlOvernightIndexedSwapIndex as overnightIndexedSwapIndex{`String', fromEnumQuantity`(Int, TimeUnit)'&, fromIntegral`Word', withCurrency*`Currency',withOvernightIborIndex*`OvernightIborIndex', preErrorCheck-`String'errorCheck*-}->`OvernightIndexedSwapIndex'peekOvernightIndexedSwapIndex*#}

{#fun qlSwapIndex as swapIndex{`String', fromEnumQuantity`(Int, TimeUnit)'&, fromIntegral`Word', withCurrency*`Currency', withCalendar*`Calendar', fromEnumQuantity`(Int, TimeUnit)'&,`BusinessDayConvention', withDayCounter*`DayCounter',withIborIndex*`GenIborIndex a', preErrorCheck-`String'errorCheck*-}->`SwapIndex'peekSwapIndex*#}

{#fun qlSwapIndex1 as swapIndex'{`String', fromEnumQuantity`(Int, TimeUnit)'&, fromIntegral`Word', withCurrency*`Currency', withCalendar*`Calendar', fromEnumQuantity`(Int, TimeUnit)'&,`BusinessDayConvention', withDayCounter*`DayCounter',withIborIndex*`GenIborIndex a',withYieldTermStructure*`YieldTermStructure', preErrorCheck-`String'errorCheck*-}->`SwapIndex'peekSwapIndex*#}

{#enum IborIndexType{} add prefix = "Ibor" deriving (Show, Eq)#}

-- |for some indices without a dedicated overnight constructor you can use (0, Days) tenor
data IborConstructor =
    Bbsw (Word, TimeUnit)
    | Bibor (Word, TimeUnit)
    | Bkbm (Word, TimeUnit)
    | Cdor (Word, TimeUnit)

    | EurLibor (Word, TimeUnit)
    | AudLibor (Word, TimeUnit)
    | CadLibor (Word, TimeUnit)
    | ChfLibor (Word, TimeUnit)
    | DkkLibor (Word, TimeUnit)
    | GbpLibor (Word, TimeUnit)
    | JpyLibor (Word, TimeUnit)
    | NzdLibor (Word, TimeUnit)
    | SekLibor (Word, TimeUnit)
    | UsdLibor (Word, TimeUnit)

    | EurDailyTenorLibor Word
    | ChfDailyTenorLibor Word
    | GbpDailyTenorLibor Word
    | JpyDailyTenorLibor Word
    | UsdDailyTenorLibor Word

    | CadLiborON
    | EurLiborON
    | GbpLiborON
    | UsdLiborON

    | Euribor (Word, TimeUnit)
    | Euribor365 (Word, TimeUnit)
    | Jibar (Word, TimeUnit)
    | Mosprime (Word, TimeUnit)
    | Pribor (Word, TimeUnit)
    | Robor (Word, TimeUnit)
    | Shibor (Word, TimeUnit)
    | THBFIX (Word, TimeUnit)
    | TRLibor (Word, TimeUnit)
    | Tibor (Word, TimeUnit)
    | Wibor (Word, TimeUnit)
    | Zibor (Word, TimeUnit)

    | Ibor String (Word, TimeUnit) Word Currency Calendar BusinessDayConvention Bool DayCounter
    | Libor String (Word, TimeUnit) Word Currency Calendar DayCounter
    | DailyTenorLibor String Word Currency Calendar DayCounter
    -- convenience shortcuts
    | Bbsw1M
    | Bbsw2M
    | Bbsw3M
    | Bbsw4M
    | Bbsw5M
    | Bbsw6M

    | BiborSW
    | Bibor1M
    | Bibor2M
    | Bibor3M
    | Bibor6M
    | Bibor9M
    | Bibor1Y

    | Bkbm1M
    | Bkbm2M
    | Bkbm3M
    | Bkbm4M
    | Bkbm5M
    | Bkbm6M

    | EuriborSW
    | Euribor2W
    | Euribor3W
    | Euribor1M
    | Euribor2M
    | Euribor3M
    | Euribor4M
    | Euribor5M
    | Euribor6M
    | Euribor7M
    | Euribor8M
    | Euribor9M
    | Euribor10M
    | Euribor11M
    | Euribor1Y

    | Euribor365_SW
    | Euribor365_2W
    | Euribor365_3W
    | Euribor365_1M
    | Euribor365_2M
    | Euribor365_3M
    | Euribor365_4M
    | Euribor365_5M
    | Euribor365_6M
    | Euribor365_7M
    | Euribor365_8M
    | Euribor365_9M
    | Euribor365_10M
    | Euribor365_11M
    | Euribor365_1Y

    | EurLiborSW
    | EurLibor2W
    | EurLibor1M
    | EurLibor2M
    | EurLibor3M
    | EurLibor4M
    | EurLibor5M
    | EurLibor6M
    | EurLibor7M
    | EurLibor8M
    | EurLibor9M
    | EurLibor10M
    | EurLibor11M
    | EurLibor1Y
    deriving (Show, Eq)

iborIndexType :: IborConstructor -> IO IborIndexType
iborIndexType (Bbsw _) = return IborBbsw
iborIndexType (Bibor _) = return IborBibor
iborIndexType (Bkbm _) = return IborBkbm
iborIndexType (Cdor _) = return IborCdor
iborIndexType (EurLibor _) = return IborEurLibor
iborIndexType (AudLibor _) = return IborAudLibor
iborIndexType (CadLibor _) = return IborCadLibor
iborIndexType (ChfLibor _) = return IborChfLibor
iborIndexType (DkkLibor _) = return IborDkkLibor
iborIndexType (GbpLibor _) = return IborGbpLibor
iborIndexType (JpyLibor _) = return IborJpyLibor
iborIndexType (NzdLibor _) = return IborNzdLibor
iborIndexType (SekLibor _) = return IborSekLibor
iborIndexType (UsdLibor _) = return IborUsdLibor
iborIndexType (EurDailyTenorLibor _) = return IborEurDailyTenorLibor
iborIndexType (ChfDailyTenorLibor _) = return IborChfDailyTenorLibor
iborIndexType (GbpDailyTenorLibor _) = return IborGbpDailyTenorLibor
iborIndexType (JpyDailyTenorLibor _) = return IborJpyDailyTenorLibor
iborIndexType (UsdDailyTenorLibor _) = return IborUsdDailyTenorLibor
iborIndexType CadLiborON = return IborCadLiborON
iborIndexType EurLiborON = return IborEurLiborON
iborIndexType GbpLiborON = return IborGbpLiborON
iborIndexType UsdLiborON = return IborUsdLiborON
iborIndexType (Euribor _) = return IborEuribor
iborIndexType (Euribor365 _) = return IborEuribor365
iborIndexType (Jibar _) = return IborJibar
iborIndexType (Mosprime _) = return IborMosprime
iborIndexType (Pribor _) = return IborPribor
iborIndexType (Robor _) = return IborRobor
iborIndexType (Shibor _) = return IborShibor
iborIndexType (THBFIX _) = return IborTHBFIX
iborIndexType (TRLibor _) = return IborTRLibor
iborIndexType (Tibor _) = return IborTibor
iborIndexType (Wibor _) = return IborWibor
iborIndexType (Zibor _) = return IborZibor
iborIndexType x = throwIO $ EnumConversion $ "No type defined for Ibor constructor " ++ show x

iborIndexTenor :: IborConstructor -> (Word, TimeUnit)
iborIndexTenor (Bbsw p) = p
iborIndexTenor (Bibor p) = p
iborIndexTenor (Bkbm p) = p
iborIndexTenor (Cdor p) = p
iborIndexTenor (EurLibor p) = p
iborIndexTenor (AudLibor p) = p
iborIndexTenor (CadLibor p) = p
iborIndexTenor (ChfLibor p) = p
iborIndexTenor (DkkLibor p) = p
iborIndexTenor (GbpLibor p) = p
iborIndexTenor (JpyLibor p) = p
iborIndexTenor (NzdLibor p) = p
iborIndexTenor (SekLibor p) = p
iborIndexTenor (UsdLibor p) = p
iborIndexTenor (EurDailyTenorLibor d) = (d, Days)
iborIndexTenor (ChfDailyTenorLibor d) = (d, Days)
iborIndexTenor (GbpDailyTenorLibor d) = (d, Days)
iborIndexTenor (JpyDailyTenorLibor d) = (d, Days)
iborIndexTenor (UsdDailyTenorLibor d) = (d, Days)
iborIndexTenor CadLiborON = (0, Days)
iborIndexTenor EurLiborON = (0, Days)
iborIndexTenor GbpLiborON = (0, Days)
iborIndexTenor UsdLiborON = (0, Days)
iborIndexTenor (Euribor p) = p
iborIndexTenor (Euribor365 p) = p
iborIndexTenor (Jibar p) = p
iborIndexTenor (Mosprime p) = p
iborIndexTenor (Pribor p) = p
iborIndexTenor (Robor p) = p
iborIndexTenor (Shibor p) = p
iborIndexTenor (THBFIX p) = p
iborIndexTenor (TRLibor p) = p
iborIndexTenor (Tibor p) = p
iborIndexTenor (Wibor p) = p
iborIndexTenor (Zibor p) = p
iborIndexTenor _ = (0, Days)

iborIndex :: IborConstructor -> Maybe YieldTermStructure -> IO IborIndex
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
iborIndex c ts = do
  t <- iborIndexType c
  qlCreateIbor t (iborIndexTenor c) ts

{#fun qlIborIndex{`String', fromEnumQuantity`(Word, TimeUnit)'&, fromIntegral`Word', withCurrency*`Currency', withCalendar*`Calendar',`BusinessDayConvention',`Bool', withDayCounter*`DayCounter', withMaybeYieldTermStructure*`Maybe YieldTermStructure', preErrorCheck-`String'errorCheck*-}->`IborIndex'peekIborIndex*#}

{#fun qlLibor{`String',fromEnumQuantity`(Word, TimeUnit)'&,fromIntegral`Word',withCurrency*`Currency', withCalendar*`Calendar',withDayCounter*`DayCounter', withMaybeYieldTermStructure*`Maybe YieldTermStructure', preErrorCheck-`String'errorCheck*-}->`IborIndex'peekIborIndex*#}

{#fun qlDailyTenorLibor{`String', fromIntegral`Word', withCurrency*`Currency', withCalendar*`Calendar', withDayCounter*`DayCounter', withMaybeYieldTermStructure*`Maybe YieldTermStructure', preErrorCheck-`String'errorCheck*-}->`IborIndex'peekIborIndex*#}

{#fun qlCreateIbor{`IborIndexType', fromEnumQuantity`(Word, TimeUnit)'&, withMaybeYieldTermStructure*`Maybe YieldTermStructure', preErrorCheck-`String'errorCheck*-}->`IborIndex'peekIborIndex*#}

{#fun qlOvernightIndex as overnightIndex{`String', fromIntegral`Word', withCurrency*`Currency', withCalendar*`Calendar', withDayCounter*`DayCounter', withMaybeYieldTermStructure*`Maybe YieldTermStructure', preErrorCheck-`String'errorCheck*-}->`OvernightIborIndex'peekOvernightIborIndex*#}

{#fun pure qlIborIndexBusinessDayConvention as businessDayConvention{withIborIndex*`IborIndex'}->`BusinessDayConvention'#}

{#fun pure qlIborIndexEndOfMonth as endOfMonth{withIborIndex*`IborIndex'}->`Bool'#}

class HasUnderlying a b | a -> b where underlying :: a -> Day -> IO b

instance HasUnderlying OvernightIndexedSwapIndex OvernightIndexedSwap where underlying = qlOvernightIndexedSwapIndexUnderlyingSwap
{#fun qlOvernightIndexedSwapIndexUnderlyingSwap{withOvernightIndexedSwapIndex*`OvernightIndexedSwapIndex', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`OvernightIndexedSwap'peekOvernightIndexedSwap*#}
instance HasUnderlying SwapIndex VanillaSwap where underlying = qlSwapIndexUnderlyingSwap
{#fun qlSwapIndexUnderlyingSwap{withSwapIndex*`GenSwapIndex a', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`VanillaSwap'peekVanillaSwap*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
