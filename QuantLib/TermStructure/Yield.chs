{-# LANGUAGE MultiParamTypeClasses, FunctionalDependencies, FlexibleContexts, TypeOperators #-}
module QuantLib.TermStructure.Yield
  (
    YieldTermStructure
  , BondHelper
  , RateHelper
  , SwapRateHelper
  , OISRateHelper
  , FittingMethod(..)
  , FittedBondDiscountCurve
  , fittedBondDiscountCurve
  , fittedBondDiscountCurve'

  , BootstrapTrait(..)
  , depositRateHelper'
  , depositRateHelper
  , fixedRateBondHelper
  , discount'
  , swapRateHelper'
  , flatForward
  , flatForward'
  , zeroRate'
  , forwardRateForPeriod
  , forwardRate'
  , forwardRate
  , zeroRate
  , discount
  , fraRateHelper
  , bondHelper
  , oisRateHelper
  , swapRateHelper
  , forwardSpreadedTermStructure
  , zeroSpreadedTermStructure
  , bmaSwapRateHelper
  , datedOISRateHelper
  , fraIborRateHelper'
  , fraRateHelper'
  , fraIborRateHelper
  , futuresRateHelper'
  , futuresIborRateHelper
  , futuresRateHelper
  , impliedQuote
  , referenceDate
  , maxDate
  , impliedTermStructure

  , asYieldTermStructure
  , asTermStructure
  , asRateHelper

  , driftTermStructure
  , piecewiseZeroSpreadedTermStructure
  , quantoTermStructure
  , minimumCostValue
  , numberOfIterations

  , piecewiseYieldCurve
  , piecewiseYieldCurve'
  , interpolatedZeroCurve
  , interpolatedForwardCurve
  , interpolatedDiscountCurve

  , underlying
  )
  where

import QuantLib.Internal hiding (maxDate)
import QuantLib.Type
import QuantLib.Internal.Enum
{#import QuantLib.Quote#}()
import {-# SOURCE #-} QuantLib.Index.InterestRate
import QuantLib.Internal.Index
{#import QuantLib.InterestRate#}(Compounding)
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
import QuantLib.Internal.Type
{#import QuantLib.Time.Schedule#}(TimeUnit, Frequency)
{#import QuantLib.TermStructure#}
import {-# SOURCE #-} QuantLib.Instrument.Bond(Bond)
import {-# SOURCE #-} QuantLib.TermStructure.Volatility(BlackVolTermStructure)
import {-# SOURCE #-} QuantLib.Instrument.Swap(VanillaSwap, OvernightIndexedSwap)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

-- breaking recursive dependencies with Index.InterestRate TermStructure.Volatilitiy modules
-- if you put all pointer declarations in a separate module
-- ch2s will not attach finalizers to foreign ptrs in other modules
-- I don't want to create extra modules just to workaround the issue with cyclic dependencies and this will not help with finalizers anyway
{#pointer *QlIborIndex as IborIndex foreign newtype nocode#}
{#pointer *QlOvernightIndex as OvernightIborIndex foreign newtype nocode#}
{#pointer *QlBMAIndex as BMAIndex foreign newtype nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign newtype nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign newtype nocode#}
{#pointer *QlBlackVolTermStructure as BlackVolTermStructure foreign newtype nocode#}
{#pointer *QlBond as Bond foreign newtype nocode#}
{#pointer *QlSwap as Swap foreign newtype nocode#}
{#pointer *QlVanillaSwap as VanillaSwap foreign newtype nocode#}
{#pointer *QlOvernightIndexedSwap as OvernightIndexedSwap foreign newtype nocode#}

{#pointer *QlYieldTermStructure as YieldTermStructure foreign finalizer qlFreeYieldTermStructure newtype#}
instance ForeignObject YieldTermStructure where
  withObject = withYieldTermStructure
  constructor = YieldTermStructure
  finalizer = qlFreeYieldTermStructure

{#pointer *QlRateHelper as RateHelper foreign finalizer qlFreeRateHelper newtype#}
instance ForeignObject RateHelper where
  withObject = withRateHelper
  constructor = RateHelper
  finalizer = qlFreeRateHelper

{#pointer *QlBondHelper as BondHelper foreign finalizer qlFreeBondHelper newtype#}
instance ForeignObject BondHelper where
  withObject = withBondHelper
  constructor = BondHelper
  finalizer = qlFreeBondHelper

{#pointer *QlSwapRateHelper as SwapRateHelper foreign finalizer qlFreeSwapRateHelper newtype#}
instance ForeignObject SwapRateHelper where
  withObject = withSwapRateHelper
  constructor = SwapRateHelper
  finalizer = qlFreeSwapRateHelper

{#pointer *QlOISRateHelper as OISRateHelper foreign finalizer qlFreeOISRateHelper newtype#}
instance ForeignObject OISRateHelper where
  withObject = withOISRateHelper
  constructor = OISRateHelper
  finalizer = qlFreeOISRateHelper

{#pointer *QlFittedBondDiscountCurve as FittedBondDiscountCurve foreign finalizer qlFreeFittedBondDiscountCurve newtype#}
instance ForeignObject FittedBondDiscountCurve where
  withObject = withFittedBondDiscountCurve
  constructor = FittedBondDiscountCurve
  finalizer = qlFreeFittedBondDiscountCurve

{#enum BootstrapTrait {} deriving(Show, Eq)#}

{#fun qlDepositRateHelper1 as depositRateHelper' {withComplexType *`Quote', `IborIndex', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlDepositRateHelper as depositRateHelper {withComplexType *`Quote', fromEnumQuantity `(Int, TimeUnit)'&, fromIntegral `Word', withSimpleType* `Calendar', `BusinessDayConvention', `Bool', withSimpleType* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlFixedRateBondHelper as fixedRateBondHelper {withComplexType *`Quote', fromIntegral `Word', `Double', withSimpleType* `Schedule', withDoubleArray* `[Double]'&, withSimpleType* `DayCounter', `BusinessDayConvention', `Double', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `BondHelper'#}

-- |Returns a discount factor from the given YieldTermStructure object
{#fun qlYieldTSDiscount as discount' {`YieldTermStructure', withDay* `Day', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlSwapRateHelper1 as swapRateHelper' {withComplexType *`Quote', fromEnumQuantity `(Int, TimeUnit)'&, withSimpleType* `Calendar', `Frequency', `BusinessDayConvention', withSimpleType* `DayCounter', `IborIndex', withMaybeComplexType* `Maybe Quote', fromEnumQuantity `(Int, TimeUnit)'&, withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `SwapRateHelper'#}

{#fun qlFlatForward as flatForward {withDay* `Day', withComplexType *`Quote', withSimpleType* `DayCounter', `Compounding', `Frequency', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

{#fun qlFlatForward1 as flatForward' {fromIntegral `Word', withSimpleType* `Calendar', withComplexType *`Quote', withSimpleType* `DayCounter', `Compounding', `Frequency', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

-- |The resulting interest rate has the required daycounting rule.
{#fun qlYieldTermStructureZeroRate as zeroRate' {`YieldTermStructure', withDay* `Day', withSimpleType* `DayCounter', `Compounding', `Frequency', `Bool', preErrorCheck- `String' errorCheck*-} -> `InterestRate' peekInterestRate*#}

-- |The resulting interest rate has the required day-counting rule. /Warning/ dates are not adjusted for holidays
{#fun qlYieldTermStructureForwardRate1 as forwardRateForPeriod {`YieldTermStructure', withDay* `Day', fromEnumQuantity `(Int, TimeUnit)'&, withSimpleType* `DayCounter', `Compounding', `Frequency', `Bool', preErrorCheck- `String' errorCheck*-} -> `InterestRate' peekInterestRate*#}

-- |The resulting interest rate has the required day-counting rule.
{#fun qlYieldTermStructureForwardRate as forwardRate' {`YieldTermStructure', withDay* `Day', withDay* `Day', withSimpleType* `DayCounter', `Compounding', `Frequency', `Bool', preErrorCheck- `String' errorCheck*-} -> `InterestRate' peekInterestRate*#}

-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed times t1 and t2.
{#fun qlYieldTermStructureForwardRate2 as forwardRate {`YieldTermStructure', `Double', `Double', `Compounding', `Frequency', `Bool', preErrorCheck- `String' errorCheck*-} -> `InterestRate' peekInterestRate*#}

-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed time t.
{#fun qlYieldTermStructureZeroRate1 as zeroRate {`YieldTermStructure', `Double', `Compounding', `Frequency', `Bool', preErrorCheck- `String' errorCheck*-} -> `InterestRate' peekInterestRate*#}

-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
{#fun qlYieldTermStructureDiscount1 as discount {`YieldTermStructure', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlFraRateHelper as fraRateHelper {withComplexType *`Quote', fromIntegral `Word', fromIntegral `Word', fromIntegral `Word', withSimpleType* `Calendar', `BusinessDayConvention', `Bool', withSimpleType* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

-- |/Warning/ Setting a pricing engine to the passed bond from external code will cause the bootstrap to fail or to give wrong results. It is advised to discard the bond after creating the helper, so that the helper has sole ownership of it.
{#fun qlBondHelper as bondHelper {withComplexType *`Quote', withObject* `Bond', preErrorCheck- `String' errorCheck*-} -> `BondHelper'#}

{#fun qlOISRateHelper as oisRateHelper {fromIntegral `Word', fromEnumQuantity `(Int, TimeUnit)'&, withComplexType *`Quote', `OvernightIborIndex', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `OISRateHelper'#}

{#fun qlSwapRateHelper as swapRateHelper {withComplexType *`Quote', `SwapIndex', withMaybeComplexType* `Maybe Quote', fromEnumQuantity `(Int, TimeUnit)'&, withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `SwapRateHelper'#}

{#fun qlForwardSpreadedTermStructure as forwardSpreadedTermStructure {`YieldTermStructure', withComplexType *`Quote', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

{#fun qlZeroSpreadedTermStructure as zeroSpreadedTermStructure {`YieldTermStructure', withComplexType *`Quote', `Compounding', `Frequency', withSimpleType* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

{#fun qlBMASwapRateHelper as bmaSwapRateHelper {withComplexType *`Quote', fromEnumQuantity `(Int, TimeUnit)'&, fromIntegral `Word', withSimpleType* `Calendar', fromEnumQuantity `(Int, TimeUnit)'&, `BusinessDayConvention', withSimpleType* `DayCounter', `BMAIndex', `IborIndex', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlDatedOISRateHelper as datedOISRateHelper {withDay* `Day', withDay* `Day', withComplexType *`Quote', `OvernightIborIndex', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlFraRateHelper1 as fraIborRateHelper' {withComplexType *`Quote', fromIntegral `Word', `IborIndex', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlFraRateHelper2 as fraRateHelper' {withComplexType *`Quote', fromEnumQuantity `(Int, TimeUnit)'&, fromIntegral `Word', fromIntegral `Word', withSimpleType* `Calendar', `BusinessDayConvention', `Bool', withSimpleType* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlFraRateHelper3 as fraIborRateHelper {withComplexType *`Quote', fromEnumQuantity `(Int, TimeUnit)'&, `IborIndex', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlFuturesRateHelper1 as futuresRateHelper' {withComplexType *`Quote', withDay* `Day', withDay* `Day', withSimpleType* `DayCounter', withMaybeComplexType* `Maybe Quote', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlFuturesRateHelper2 as futuresIborRateHelper {withComplexType *`Quote', withDay* `Day', `IborIndex', withMaybeComplexType* `Maybe Quote', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlFuturesRateHelper as futuresRateHelper {withComplexType *`Quote', withDay* `Day', fromIntegral `Word', withSimpleType* `Calendar', `BusinessDayConvention', `Bool', withSimpleType* `DayCounter', withMaybeComplexType* `Maybe Quote', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlRateHelperImpliedQuote as impliedQuote {`RateHelper', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |the date at which discount = 1.0 and/or variance = 0.0
{#fun qlTermStructureReferenceDate as referenceDate {withObject* `TermStructure', preErrorCheck- `String' errorCheck*-} -> `Day' toDay#}

{#fun qlTermStructureMaxDate as maxDate {withObject* `TermStructure', preErrorCheck- `String' errorCheck*-} -> `Day' toDay#}

{#fun qlImpliedTermStructure as impliedTermStructure {`YieldTermStructure', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

instance YieldTermStructure `Derives` TermStructure where cast = qlYieldTermStructureAsTermStructure
instance FittedBondDiscountCurve `Derives` YieldTermStructure where cast = qlFittedBondDiscountCurveAsYieldTermStructure
{#fun qlYieldTermStructureAsTermStructure {`YieldTermStructure'} -> `TermStructure' peekObject*#}
{#fun qlFittedBondDiscountCurveAsYieldTermStructure {`FittedBondDiscountCurve'} -> `YieldTermStructure'#}

asYieldTermStructure :: (a `Derives` YieldTermStructure) => a -> IO YieldTermStructure
asYieldTermStructure = cast

{#fun qlSwapRateHelperAsRateHelper {`SwapRateHelper'} -> `RateHelper'#}
instance SwapRateHelper `Derives` RateHelper where cast = qlSwapRateHelperAsRateHelper

{#fun qlBondHelperAsRateHelper {`BondHelper'} -> `RateHelper'#}
instance BondHelper `Derives` RateHelper where cast = qlBondHelperAsRateHelper

{#fun qlOISRateHelperAsRateHelper {`OISRateHelper'} -> `RateHelper'#}
instance OISRateHelper `Derives` RateHelper where cast = qlOISRateHelperAsRateHelper 

asRateHelper :: (a `Derives` RateHelper) => a -> IO RateHelper
asRateHelper = cast

{#fun qlDriftTermStructure as driftTermStructure {`YieldTermStructure', `YieldTermStructure', withObject* `BlackVolTermStructure', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

piecewiseZeroSpreadedTermStructure :: YieldTermStructure
  -> [(Quote, Day)]  -- ^spreads, ^dates
  -> Compounding
  -> Frequency
  -> DayCounter
  -> IO YieldTermStructure
piecewiseZeroSpreadedTermStructure ts = uncurry (qlPiecewiseZeroSpreadedTermStructure ts) . unzip

{#fun qlPiecewiseZeroSpreadedTermStructure {`YieldTermStructure', withComplexArray* `[Quote]'&, withDayArray* `[Day]'&, `Compounding', `Frequency', withSimpleType* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

{#fun qlQuantoTermStructure as quantoTermStructure {`YieldTermStructure', `YieldTermStructure', `YieldTermStructure', withObject* `BlackVolTermStructure', `Double', withObject* `BlackVolTermStructure', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

piecewiseYieldCurve :: Day -- ^referenceDate
  -> [RateHelper] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Quote, Day)] -- ^jumps and jumpDates
  -> BootstrapTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
piecewiseYieldCurve d r dc qd t i = uncurry' (qlPiecewiseYieldCurve d r dc qs ds t) (qlInterpolation i)
  where (qs, ds) = unzip qd

{#fun qlPiecewiseYieldCurve {withDay* `Day', withObjectArray* `[RateHelper]'&, withSimpleType* `DayCounter', withComplexArray* `[Quote]'&, withDayArray* `[Day]'&, `BootstrapTrait', `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

piecewiseYieldCurve' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> [RateHelper] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Quote, Day)] -- ^jumps and jumpDates
  -> BootstrapTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
piecewiseYieldCurve' s cal r dc qd t i = uncurry' (qlPiecewiseYieldCurve1 s cal r dc qs ds t) (qlInterpolation i)
  where (qs, ds) = unzip qd

{#fun qlPiecewiseYieldCurve1 {fromIntegral `Word', withSimpleType* `Calendar', withObjectArray* `[RateHelper]'&, withSimpleType* `DayCounter', withComplexArray* `[Quote]'&, withDayArray* `[Day]'&, `BootstrapTrait', `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

interpolatedDiscountCurve :: [(Double, Day)] -- ^dates, dfs
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Quote, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedDiscountCurve r dc c qd i = uncurry' (qlInterpolatedDiscountCurve rs rd dc c qs ds) (qlInterpolation i)
  where (rs, rd) = unzip r
        (qs, ds) = unzip qd

{#fun qlInterpolatedDiscountCurve {withDoubleArray* `[Double]'&, withDayArray* `[Day]'&, withSimpleType* `DayCounter', withSimpleType* `Calendar', withComplexArray* `[Quote]'&, withDayArray* `[Day]'&, `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

interpolatedForwardCurve :: [(Double, Day)] -- ^dates, forwards
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Quote, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedForwardCurve r dc c qd i = uncurry' (qlInterpolatedForwardCurve rs rd dc c qs ds) (qlInterpolation i)
  where (rs, rd) = unzip r
        (qs, ds) = unzip qd

{#fun qlInterpolatedForwardCurve {withDoubleArray* `[Double]'&, withDayArray* `[Day]'&, withSimpleType* `DayCounter', withSimpleType* `Calendar', withComplexArray* `[Quote]'&, withDayArray* `[Day]'&, `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

interpolatedZeroCurve :: [(Double, Day)] -- ^dates, yields
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Quote, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedZeroCurve r dc c qd i = uncurry' (qlInterpolatedZeroCurve rs rd dc c qs ds) (qlInterpolation i)
  where (rs, rd) = unzip r
        (qs, ds) = unzip qd

{#fun qlInterpolatedZeroCurve {withDoubleArray* `[Double]'&, withDayArray* `[Day]'&, withSimpleType* `DayCounter', withSimpleType* `Calendar', withComplexArray* `[Quote]'&, withDayArray* `[Day]'&, `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

{#pointer *FittedBondDiscountCurveFittingMethod as FittingMethodObject foreign newtype nocode#}

-- |reference date based on current evaluation date
{#fun qlFittedBondDiscountCurve as fittedBondDiscountCurve {fromIntegral `Word', withSimpleType* `Calendar', withObjectArray* `[BondHelper]'&, withSimpleType* `DayCounter', withEnumObject* `FittingMethod', `Double', fromIntegral `Word', withDoubleArray* `[Double]'&, `Double', preErrorCheck- `String' errorCheck*-} -> `FittedBondDiscountCurve'#}

-- |curve reference date fixed for life of curve
{#fun qlFittedBondDiscountCurve1 as fittedBondDiscountCurve' {withDay* `Day', withObjectArray* `[BondHelper]'&, withSimpleType* `DayCounter', withEnumObject* `FittingMethod', `Double', fromIntegral `Word', withDoubleArray* `[Double]'&, `Double', preErrorCheck- `String' errorCheck*-} -> `FittedBondDiscountCurve'#}

-- |final value of cost function after optimization
{#fun qlFittedBondDiscountCurveFittingMethodMinimumCostValue as minimumCostValue {`FittedBondDiscountCurve', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |final number of iterations used in the optimization problem
{#fun qlFittedBondDiscountCurveFittingMethodNumberOfIterations as numberOfIterations {`FittedBondDiscountCurve', preErrorCheck- `String' errorCheck*-} -> `Int'#}

class HelperUnderlying a b | a -> b where underlying :: a -> IO b

instance HelperUnderlying BondHelper Bond where underlying = qlBondHelperBond
{#fun qlBondHelperBond {`BondHelper', preErrorCheck- `String' errorCheck*-} -> `Bond' peekObject*#}

instance HelperUnderlying SwapRateHelper VanillaSwap where underlying = qlSwapRateHelperSwap
{#fun qlSwapRateHelperSwap {`SwapRateHelper', preErrorCheck- `String' errorCheck*-} -> `VanillaSwap' peekObject*#}

instance HelperUnderlying OISRateHelper OvernightIndexedSwap where underlying = qlOISRateHelperSwap
{#fun qlOISRateHelperSwap {`OISRateHelper', preErrorCheck- `String' errorCheck*-} -> `OvernightIndexedSwap' peekObject*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
