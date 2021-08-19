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

  , asIndex
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
  )
  where

import QuantLib.Internal
import QuantLib.Type
import Control.Exception(throwIO)
{#import QuantLib.TermStructure.Yield#}
import QuantLib.Internal.TermStructure
{#import QuantLib.Index#}(Index)
{#import QuantLib.Time.Schedule#}(TimeUnit(..), Schedule, DayCounter)
import QuantLib.Internal.Schedule
{#import QuantLib.Currency#}(Currency)
import QuantLib.Internal.Currency
{#import QuantLib.Time.Calendar#}(Calendar, BusinessDayConvention)
import QuantLib.Internal.Calendar

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlInterestRateIndex as InterestRateIndex foreign finalizer qlFreeInterestRateIndex newtype#}
instance ForeignObject InterestRateIndex where
  withObject = withInterestRateIndex
  constructor = InterestRateIndex
  finalizer=qlFreeInterestRateIndex

{#pointer *QlBMAIndex as BMAIndex foreign finalizer qlFreeBMAIndex newtype#}
instance ForeignObject BMAIndex where
  withObject = withBMAIndex
  constructor = BMAIndex
  finalizer=qlFreeBMAIndex

{#pointer *QlOvernightIndex as OvernightIborIndex foreign finalizer qlFreeOvernightIndex newtype#}
instance ForeignObject OvernightIborIndex where
  withObject = withOvernightIborIndex
  constructor = OvernightIborIndex
  finalizer=qlFreeOvernightIndex

{#pointer *QlIborIndex as IborIndex foreign finalizer qlFreeIborIndex newtype#}
instance ForeignObject IborIndex where
  withObject = withIborIndex
  constructor = IborIndex
  finalizer=qlFreeIborIndex

{#pointer *QlSwapIndex as SwapIndex foreign finalizer qlFreeSwapIndex newtype#}
instance ForeignObject SwapIndex where
  withObject = withSwapIndex
  constructor = SwapIndex
  finalizer=qlFreeSwapIndex

{#pointer *QlOvernightIndexedSwapIndex as OvernightIndexedSwapIndex foreign finalizer qlFreeOvernightIndexedSwapIndex newtype#}
instance ForeignObject OvernightIndexedSwapIndex where
  withObject = withOvernightIndexedSwapIndex
  constructor = OvernightIndexedSwapIndex
  finalizer=qlFreeOvernightIndexedSwapIndex

{#fun qlBMAIndex as bmaIndex {withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `BMAIndex' peekObject*#}

-- |This method returns a schedule of fixing dates between start and end.
{#fun qlBMAIndexFixingSchedule as fixingSchedule {`BMAIndex', withDay* `Day', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Schedule' peekObject*#}

-- |It can be overridden to implement particular conventions.
{#fun qlInterestRateIndexForecastFixing as forecastFixing {`InterestRateIndex', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlInterestRateIndexCurrency as currency {`InterestRateIndex', preErrorCheck- `String' errorCheck*-} -> `Currency' peekObject*#}

{#fun qlInterestRateIndexDayCounter as dayCounter {`InterestRateIndex', preErrorCheck- `String' errorCheck*-} -> `DayCounter' peekObject*#}

{#fun pure qlInterestRateIndexFixingDays as fixingDays {`InterestRateIndex'} -> `Word' fromIntegral#}

{#fun qlInterestRateIndexTenor as tenor {`InterestRateIndex', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#}

{#fun qlInterestRateIndexAsIndex as asIndex {`InterestRateIndex'} -> `Index' peekObject*#}

class IsInterestRateIndex a where asInterestRateIndex :: a -> IO InterestRateIndex

{#fun qlBMAIndexAsInterestRateIndex {`BMAIndex'} -> `InterestRateIndex'#}
instance IsInterestRateIndex BMAIndex where asInterestRateIndex = qlBMAIndexAsInterestRateIndex

{#fun qlSwapIndexAsInterestRateIndex {`SwapIndex'} -> `InterestRateIndex'#}
instance IsInterestRateIndex SwapIndex where asInterestRateIndex = qlSwapIndexAsInterestRateIndex

{#fun qlOvernightIndexedSwapIndexAsSwapIndex as asSwapIndex {`OvernightIndexedSwapIndex'} -> `SwapIndex'#}

{#fun qlIborIndexAsInterestRateIndex {`IborIndex'} -> `InterestRateIndex'#}
instance IsInterestRateIndex IborIndex where asInterestRateIndex = qlIborIndexAsInterestRateIndex

{#fun qlOvernightIndexAsIborIndex as asIborIndex {`OvernightIborIndex'} -> `IborIndex'#}

{#enum OvernightIborIndexType {} deriving (Show, Eq)#}

{#fun qlCreateONIndex as overnightIborIndex {`OvernightIborIndexType', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `OvernightIborIndex'#}

{#enum LiborSwapIndexType {} deriving (Show, Eq)#}

{#fun qlCreateLiborSwapIndex as liborSwapIndex {`LiborSwapIndexType', fromEnumQuantity `(Int, TimeUnit)'&, withMaybeObject* `Maybe YieldTermStructure', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `SwapIndex'#}

{#fun qlOvernightIndexedSwapIndex as overnightIndexedSwapIndex {`String', fromEnumQuantity `(Int, TimeUnit)'&, fromIntegral `Word', `Currency', `OvernightIborIndex', preErrorCheck- `String' errorCheck*-} -> `OvernightIndexedSwapIndex'#}

{#fun qlSwapIndex as swapIndex {`String', fromEnumQuantity `(Int, TimeUnit)'&, fromIntegral `Word', `Currency', `Calendar', fromEnumQuantity `(Int, TimeUnit)'&, `BusinessDayConvention', `DayCounter', `IborIndex', preErrorCheck- `String' errorCheck*-} -> `SwapIndex'#}

{#fun qlSwapIndex1 as swapIndex' {`String', fromEnumQuantity `(Int, TimeUnit)'&, fromIntegral `Word', `Currency', `Calendar', fromEnumQuantity `(Int, TimeUnit)'&, `BusinessDayConvention', `DayCounter', `IborIndex', `YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `SwapIndex'#}

{#enum IborIndexType {} deriving (Show, Eq)#}

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
iborIndex c ts = do
  t <- iborIndexType c
  qlCreateIbor t (iborIndexTenor c) ts

{#fun qlIborIndex {`String', fromEnumQuantity `(Word, TimeUnit)'&, fromIntegral `Word', `Currency', `Calendar', `BusinessDayConvention', `Bool', `DayCounter', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `IborIndex'#}

{#fun qlLibor {`String',fromEnumQuantity `(Word, TimeUnit)'&,fromIntegral `Word',`Currency',`Calendar',`DayCounter', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `IborIndex'#}

{#fun qlDailyTenorLibor {`String', fromIntegral `Word', `Currency', `Calendar', `DayCounter', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `IborIndex'#}

{#fun qlCreateIbor {`IborIndexType', fromEnumQuantity `(Word, TimeUnit)'&, withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `IborIndex'#}

{#fun qlOvernightIndex as overnightIndex {`String', fromIntegral `Word', `Currency', `Calendar', `DayCounter', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `OvernightIborIndex'#}

{#fun pure qlIborIndexBusinessDayConvention as businessDayConvention {`IborIndex'} -> `BusinessDayConvention'#}

{#fun pure qlIborIndexEndOfMonth as endOfMonth {`IborIndex'} -> `Bool'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
