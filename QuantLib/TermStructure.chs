{-# LANGUAGE TypeFamilies, FlexibleInstances #-}
module QuantLib.TermStructure
  (
    -- * Types
    TermStructure
  , GenTermStructure
  , Reference(..)
  , CalendarReference(..)
  , TermPoint(..)
  , TermInterval(..)
  , RatePoint(..)
  , HasHelperUnderlying(..)

    -- * Constructors
  , asTermStructure

    -- * Mutators
  , setExtrapolation

    -- * Inspectors
  , referenceDate
  , maxDate
  , allowsExtrapolation
  , timeFromReference
  ) where
import QuantLib.Internal hiding(maxDate)
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

-- Pointer aliases for the HasHelperUnderlying instances below. The helper types and the
-- instruments they build are declared in QuantLib.Internal.Type; these are the c2hs-local
-- mappings the {#fun#} hooks need, copied from the modules that construct them
-- (QuantLib.TermStructure.Yield, .Inflation, QuantLib.Model).
{#pointer *QlBondHelper as BondHelper foreign -> CBondHelper' nocode#}
{#pointer *QlSwapRateHelper as SwapRateHelper foreign -> CSwapRateHelper' nocode#}
{#pointer *QlOISRateHelper as OISRateHelper foreign -> COISRateHelper' nocode#}
{#pointer *QlZeroCouponInflationSwapHelper as ZeroCouponInflationSwapHelper foreign -> CZeroCouponInflationSwapHelper nocode#}
{#pointer *QlYearOnYearInflationSwapHelper as YearOnYearInflationSwapHelper foreign -> CYearOnYearInflationSwapHelper nocode#}
{#pointer *QlSwaptionHelper as SwaptionHelper foreign -> CSwaptionHelper' nocode#}
{#pointer *QlBond as Bond foreign -> CBond' nocode#}
{#pointer *QlVanillaSwap as VanillaSwap foreign -> CVanillaSwap' nocode#}
{#pointer *QlOvernightIndexedSwap as OvernightIndexedSwap foreign -> COvernightIndexedSwap' nocode#}
{#pointer *QlZeroCouponInflationSwap as ZeroCouponInflationSwap foreign -> CZeroCouponInflationSwap' nocode#}
{#pointer *QlYearOnYearInflationSwap as YearOnYearInflationSwap foreign -> CYearOnYearInflationSwap' nocode#}
{#pointer *QlFixedVsFloatingSwap as FixedVsFloatingSwap foreign -> CFixedVsFloatingSwap' nocode#}

-- |Bootstrap and calibration helpers that build and hold the instrument whose market quote
-- they match. The class lives here, in the term-structure root module, because its instances
-- span "QuantLib.TermStructure.Yield", ".Inflation" and "QuantLib.Model", and an instance must
-- share a module with its class to stay non-orphan.
class HasHelperUnderlying h where
  type HelperUnderlying h
  -- |The instrument the helper prices. For helpers that build it internally --
  -- 'QuantLib.TermStructure.Yield.fixedRateBondHelper' and
  -- 'QuantLib.TermStructure.Yield.cpiBondHelper' among them -- this is the only way to reach it.
  helperInstrument :: h -> IO (HelperUnderlying h)

instance HasHelperUnderlying BondHelper where
  type HelperUnderlying BondHelper = Bond
  helperInstrument = qlBondHelperBond
instance HasHelperUnderlying SwapRateHelper where
  type HelperUnderlying SwapRateHelper = VanillaSwap
  helperInstrument = qlSwapRateHelperSwap
instance HasHelperUnderlying OISRateHelper where
  type HelperUnderlying OISRateHelper = OvernightIndexedSwap
  helperInstrument = qlOISRateHelperSwap
instance HasHelperUnderlying ZeroCouponInflationSwapHelper where
  type HelperUnderlying ZeroCouponInflationSwapHelper = ZeroCouponInflationSwap
  helperInstrument = qlZeroCouponInflationSwapHelperSwap
instance HasHelperUnderlying YearOnYearInflationSwapHelper where
  type HelperUnderlying YearOnYearInflationSwapHelper = YearOnYearInflationSwap
  helperInstrument = qlYearOnYearInflationSwapHelperSwap
-- 'QuantLib.Model.helperSwaption' reaches the swaption wrapped around this swap.
instance HasHelperUnderlying SwaptionHelper where
  type HelperUnderlying SwaptionHelper = FixedVsFloatingSwap
  helperInstrument = qlSwaptionHelperUnderlying

{#fun qlBondHelperBond{withGenRateHelper*`BondHelper',preErrorCheck-`String'errorCheck*-}->`Bond'peekBond*#}
{#fun qlSwapRateHelperSwap{withGenRateHelper*`SwapRateHelper',preErrorCheck-`String'errorCheck*-}->`VanillaSwap'peekVanillaSwap*#}
{#fun qlOISRateHelperSwap{withGenRateHelper*`OISRateHelper',preErrorCheck-`String'errorCheck*-}->`OvernightIndexedSwap'peekOvernightIndexedSwap*#}
{#fun qlZeroCouponInflationSwapHelperSwap{withZeroCouponInflationSwapHelper*`ZeroCouponInflationSwapHelper',preErrorCheck-`String'errorCheck*-}->`ZeroCouponInflationSwap'peekZeroCouponInflationSwap*#}
{#fun qlYearOnYearInflationSwapHelperSwap{withYearOnYearInflationSwapHelper*`YearOnYearInflationSwapHelper',preErrorCheck-`String'errorCheck*-}->`YearOnYearInflationSwap'peekYearOnYearInflationSwap*#}
{#fun qlSwaptionHelperUnderlying{withSwaptionHelper*`SwaptionHelper',preErrorCheck-`String'errorCheck*-}->`FixedVsFloatingSwap'peekFixedVsFloatingSwap*#}

{#pointer *QlTermStructure as TermStructure foreign -> CTermStructure' nocode#}

-- |A term-structure reference point. 'ReferenceDate' stays fixed for the object's lifetime;
-- 'SettlementDays' follows the global evaluation date using the supplied calendar.
data Reference
  = ReferenceDate !Day
  | SettlementDays !Word !Calendar
  deriving (Eq, Show)

-- |Reference-point variants for constructors that take a calendar independently in both
-- upstream overloads.
data CalendarReference
  = CalendarReferenceDate !Day
  | CalendarSettlementDays !Word
  deriving (Eq, Show)

-- |A date or year-fraction coordinate measured from a term structure's reference date.
data TermPoint = DatePoint !Day | TimePoint !Double
  deriving (Eq, Show)

-- |A same-representation interval. Keeping both endpoints in one constructor prevents mixed
-- date/time intervals that upstream does not accept.
data TermInterval
  = DateInterval !Day !Day
  | TimeInterval !Double !Double
  deriving (Eq, Show)

-- |A date or year-fraction coordinate where a date needs its day-counting rule.
data RatePoint
  = RateAtDate !Day !DayCounter
  | RateAtTime !Double
  deriving (Eq, Show)

-- |the date at which discount = 1.0 and/or variance = 0.0
{#fun qlTermStructureReferenceDate as referenceDate{withTermStructure*`GenTermStructure t',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |the latest date for which the curve can return values
{#fun qlTermStructureMaxDate as maxDate{withTermStructure*`GenTermStructure t',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |Whether calls beyond the term structure's maximum date are allowed by default.
{#fun qlTermStructureAllowsExtrapolation as allowsExtrapolation{withTermStructure*`GenTermStructure t'}->`Bool'#}

-- |Enable or disable default extrapolation for any term structure.
{#fun qlTermStructureSetExtrapolation as setExtrapolation{withTermStructure*`GenTermStructure t',`Bool'}->`()'#}

-- |Converts a date to a time (as a fraction of year) according to the term structure's day counter.
{#fun qlTermStructureTimeFromReference as timeFromReference{withTermStructure*`GenTermStructure t' -- ^term structure
  ,withDay*`Day' -- ^date
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
