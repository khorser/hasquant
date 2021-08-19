module QuantLib.TermStructure.Yield
  (
    YieldTermStructure
  , BondHelper
  , RateHelper
  , SwapRateHelper
  , OISRateHelper
  , FittingMethod
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

  , helperBond
  , helperSwap
  , helperOIS
  )
  where

import QuantLib.Internal hiding (maxDate)
import QuantLib.Internal.Enum
{#import QuantLib.Quote#}(Quote)
import QuantLib.Internal.Quote
import {-# SOURCE #-} QuantLib.Index.InterestRate
import QuantLib.Internal.Index
{#import QuantLib.Time.Calendar#}(Calendar, BusinessDayConvention)
import QuantLib.Internal.Calendar
{#import QuantLib.Time.Schedule#}(TimeUnit, Frequency, Schedule, DayCounter)
import QuantLib.Internal.Schedule
{#import QuantLib.TermStructure#}
{#import QuantLib.InterestRate#}
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

{#pointer *FittedBondDiscountCurveFittingMethod as FittingMethodObject foreign finalizer qlFreeFittedBondDiscountCurveFittingMethod newtype#}
instance ForeignObject FittingMethodObject where
  withObject = withFittingMethodObject
  constructor = FittingMethodObject
  finalizer = qlFreeFittedBondDiscountCurveFittingMethod

{#enum BootstrapTrait {} deriving(Show, Eq)#}

{#fun qlDepositRateHelper1 as depositRateHelper' {`Quote', `IborIndex', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlDepositRateHelper as depositRateHelper {`Quote', fromEnumQuantity `(Int, TimeUnit)'&, fromIntegral `Word', `Calendar', `BusinessDayConvention', `Bool', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlFixedRateBondHelper as fixedRateBondHelper {`Quote', fromIntegral `Word', `Double', `Schedule', withDoubleArray* `[Double]'&, `DayCounter', `BusinessDayConvention', `Double', withMaybeDay* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `BondHelper'#}

-- |Returns a discount factor from the given YieldTermStructure object
{#fun qlYieldTSDiscount as discount' {`YieldTermStructure', withDay* `Day', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlSwapRateHelper1 as swapRateHelper' {`Quote', fromEnumQuantity `(Int, TimeUnit)'&, `Calendar', `Frequency', `BusinessDayConvention', `DayCounter', `IborIndex', withMaybeObject* `Maybe Quote', fromEnumQuantity `(Int, TimeUnit)'&, withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `SwapRateHelper'#}

{#fun qlFlatForward as flatForward {withDay* `Day', `Quote', `DayCounter', `Compounding', `Frequency', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

{#fun qlFlatForward1 as flatForward' {fromIntegral `Word', `Calendar', `Quote', `DayCounter', `Compounding', `Frequency', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

-- |The resulting interest rate has the required daycounting rule.
{#fun qlYieldTermStructureZeroRate as zeroRate' {`YieldTermStructure', withDay* `Day', `DayCounter', `Compounding', `Frequency', `Bool', preErrorCheck- `String' errorCheck*-} -> `InterestRate' peekObject*#}

-- |The resulting interest rate has the required day-counting rule. /Warning/ dates are not adjusted for holidays
{#fun qlYieldTermStructureForwardRate1 as forwardRateForPeriod {`YieldTermStructure', withDay* `Day', fromEnumQuantity `(Int, TimeUnit)'&, `DayCounter', `Compounding', `Frequency', `Bool', preErrorCheck- `String' errorCheck*-} -> `InterestRate' peekObject*#}

-- |The resulting interest rate has the required day-counting rule.
{#fun qlYieldTermStructureForwardRate as forwardRate' {`YieldTermStructure', withDay* `Day', withDay* `Day', `DayCounter', `Compounding', `Frequency', `Bool', preErrorCheck- `String' errorCheck*-} -> `InterestRate' peekObject*#}

-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed times t1 and t2.
{#fun qlYieldTermStructureForwardRate2 as forwardRate {`YieldTermStructure', `Double', `Double', `Compounding', `Frequency', `Bool', preErrorCheck- `String' errorCheck*-} -> `InterestRate' peekObject*#}

-- |The resulting interest rate has the same day-counting rule used by the term structure. The same rule should be used for calculating the passed time t.
{#fun qlYieldTermStructureZeroRate1 as zeroRate {`YieldTermStructure', `Double', `Compounding', `Frequency', `Bool', preErrorCheck- `String' errorCheck*-} -> `InterestRate' peekObject*#}

-- |The same day-counting rule used by the term structure should be used for calculating the passed time t.
{#fun qlYieldTermStructureDiscount1 as discount {`YieldTermStructure', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlFraRateHelper as fraRateHelper {`Quote', fromIntegral `Word', fromIntegral `Word', fromIntegral `Word', `Calendar', `BusinessDayConvention', `Bool', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

-- |/Warning/ Setting a pricing engine to the passed bond from external code will cause the bootstrap to fail or to give wrong results. It is advised to discard the bond after creating the helper, so that the helper has sole ownership of it.
{#fun qlBondHelper as bondHelper {`Quote', withObject* `Bond', preErrorCheck- `String' errorCheck*-} -> `BondHelper'#}

{#fun qlOISRateHelper as oisRateHelper {fromIntegral `Word', fromEnumQuantity `(Int, TimeUnit)'&, `Quote', `OvernightIborIndex', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `OISRateHelper'#}

{#fun qlSwapRateHelper as swapRateHelper {`Quote', `SwapIndex', withMaybeObject* `Maybe Quote', fromEnumQuantity `(Int, TimeUnit)'&, withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `SwapRateHelper'#}

{#fun qlForwardSpreadedTermStructure as forwardSpreadedTermStructure {`YieldTermStructure', `Quote', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

{#fun qlZeroSpreadedTermStructure as zeroSpreadedTermStructure {`YieldTermStructure', `Quote', `Compounding', `Frequency', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

{#fun qlBMASwapRateHelper as bmaSwapRateHelper {`Quote', fromEnumQuantity `(Int, TimeUnit)'&, fromIntegral `Word', `Calendar', fromEnumQuantity `(Int, TimeUnit)'&, `BusinessDayConvention', `DayCounter', `BMAIndex', `IborIndex', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlDatedOISRateHelper as datedOISRateHelper {withDay* `Day', withDay* `Day', `Quote', `OvernightIborIndex', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlFraRateHelper1 as fraIborRateHelper' {`Quote', fromIntegral `Word', `IborIndex', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlFraRateHelper2 as fraRateHelper' {`Quote', fromEnumQuantity `(Int, TimeUnit)'&, fromIntegral `Word', fromIntegral `Word', `Calendar', `BusinessDayConvention', `Bool', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlFraRateHelper3 as fraIborRateHelper {`Quote', fromEnumQuantity `(Int, TimeUnit)'&, `IborIndex', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlFuturesRateHelper1 as futuresRateHelper' {`Quote', withDay* `Day', withDay* `Day', `DayCounter', withMaybeObject* `Maybe Quote', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlFuturesRateHelper2 as futuresIborRateHelper {`Quote', withDay* `Day', `IborIndex', withMaybeObject* `Maybe Quote', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlFuturesRateHelper as futuresRateHelper {`Quote', withDay* `Day', fromIntegral `Word', `Calendar', `BusinessDayConvention', `Bool', `DayCounter', withMaybeObject* `Maybe Quote', preErrorCheck- `String' errorCheck*-} -> `RateHelper'#}

{#fun qlRateHelperImpliedQuote as impliedQuote {`RateHelper', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |the date at which discount = 1.0 and/or variance = 0.0
{#fun qlTermStructureReferenceDate as referenceDate {withObject* `TermStructure', preErrorCheck- `String' errorCheck*-} -> `Day' toDay#}

{#fun qlTermStructureMaxDate as maxDate {withObject* `TermStructure', preErrorCheck- `String' errorCheck*-} -> `Day' toDay#}

{#fun qlImpliedTermStructure as impliedTermStructure {`YieldTermStructure', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

{#fun qlYieldTermStructureAsTermStructure {`YieldTermStructure'} -> `TermStructure' peekObject*#}
instance IsTermStructure YieldTermStructure where asTermStructure = qlYieldTermStructureAsTermStructure

{#fun qlFittedBondDiscountCurveAsYieldTermStructure as asYieldTermStructure {`FittedBondDiscountCurve'} -> `YieldTermStructure'#}

class IsRateHelper a where asRateHelper :: a -> IO RateHelper

{#fun qlSwapRateHelperAsRateHelper {`SwapRateHelper'} -> `RateHelper'#}
instance IsRateHelper SwapRateHelper where asRateHelper = qlSwapRateHelperAsRateHelper

{#fun qlBondHelperAsRateHelper {`BondHelper'} -> `RateHelper'#}
instance IsRateHelper BondHelper where asRateHelper = qlBondHelperAsRateHelper

{#fun qlOISRateHelperAsRateHelper {`OISRateHelper'} -> `RateHelper'#}
instance IsRateHelper OISRateHelper where asRateHelper = qlOISRateHelperAsRateHelper 

{#fun qlDriftTermStructure as driftTermStructure {`YieldTermStructure', `YieldTermStructure', withObject* `BlackVolTermStructure', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

piecewiseZeroSpreadedTermStructure :: YieldTermStructure
  -> [(Quote, Day)]  -- ^spreads, ^dates
  -> Compounding
  -> Frequency
  -> DayCounter
  -> IO YieldTermStructure
piecewiseZeroSpreadedTermStructure ts = uncurry (qlPiecewiseZeroSpreadedTermStructure ts) . unzip

{#fun qlPiecewiseZeroSpreadedTermStructure {`YieldTermStructure', withObjectArray* `[Quote]'&, withDayArray* `[Day]'&, `Compounding', `Frequency', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

{#fun qlQuantoTermStructure as quantoTermStructure {`YieldTermStructure', `YieldTermStructure', `YieldTermStructure', withObject* `BlackVolTermStructure', `Double', withObject* `BlackVolTermStructure', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

piecewiseYieldCurve :: Day -- ^referenceDate
  -> [RateHelper] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Quote, Day)] -- ^jumps and jumpDates
  -> BootstrapTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
piecewiseYieldCurve d r dc qd t i = qlPiecewiseYieldCurve d r dc qs ds t i' a aa
  where (qs, ds) = unzip qd
        (i', (a, aa)) = qlInterpolation i

{#fun qlPiecewiseYieldCurve {withDay* `Day', withObjectArray* `[RateHelper]'&, `DayCounter', withObjectArray* `[Quote]'&, withDayArray* `[Day]'&, `BootstrapTrait', `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

piecewiseYieldCurve' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> [RateHelper] -- ^instruments
  -> DayCounter -- ^dayCounter
  -> [(Quote, Day)] -- ^jumps and jumpDates
  -> BootstrapTrait -- ^bootstrap trait
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
piecewiseYieldCurve' s cal r dc qd t i = qlPiecewiseYieldCurve1 s cal r dc qs ds t i' a aa
  where (qs, ds) = unzip qd
        (i', (a, aa)) = qlInterpolation i

{#fun qlPiecewiseYieldCurve1 {fromIntegral `Word', `Calendar', withObjectArray* `[RateHelper]'&, `DayCounter', withObjectArray* `[Quote]'&, withDayArray* `[Day]'&, `BootstrapTrait', `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

interpolatedDiscountCurve :: [(Double, Day)] -- ^dates, dfs
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Quote, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedDiscountCurve r dc c qd i = qlInterpolatedDiscountCurve rs rd dc c qs ds i' a aa
  where (rs, rd) = unzip r
        (qs, ds) = unzip qd
        (i', (a, aa)) = qlInterpolation i

{#fun qlInterpolatedDiscountCurve {withDoubleArray* `[Double]'&, withDayArray* `[Day]'&, `DayCounter', `Calendar', withObjectArray* `[Quote]'&, withDayArray* `[Day]'&, `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

interpolatedForwardCurve :: [(Double, Day)] -- ^dates, forwards
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Quote, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedForwardCurve r dc c qd i = qlInterpolatedForwardCurve rs rd dc c qs ds i' a aa
  where (rs, rd) = unzip r
        (qs, ds) = unzip qd
        (i', (a, aa)) = qlInterpolation i

{#fun qlInterpolatedForwardCurve {withDoubleArray* `[Double]'&, withDayArray* `[Day]'&, `DayCounter', `Calendar', withObjectArray* `[Quote]'&, withDayArray* `[Day]'&, `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

interpolatedZeroCurve :: [(Double, Day)] -- ^dates, yields
  -> DayCounter -- ^dayCounter
  -> Calendar -- ^cal
  -> [(Quote, Day)] -- ^jumps, jumpDates
  -> Interpolation -- ^interpolator
  -> IO YieldTermStructure
interpolatedZeroCurve r dc c qd i = qlInterpolatedZeroCurve rs rd dc c qs ds i' a aa
  where (rs, rd) = unzip r
        (qs, ds) = unzip qd
        (i', (a, aa)) = qlInterpolation i

{#fun qlInterpolatedZeroCurve {withDoubleArray* `[Double]'&, withDayArray* `[Day]'&, `DayCounter', `Calendar', withObjectArray* `[Quote]'&, withDayArray* `[Day]'&, `Int', `Int', `Int', preErrorCheck- `String' errorCheck*-} -> `YieldTermStructure'#}

data FittingMethod =
  CubicSplies
    [Double] -- ^knotVector (year fraction)
    Bool -- ^constrainAtZero
  | ExponentialSplines Bool
  | NelsonSiegel
  | SimplePolynomial
    Word -- ^degree
    Bool -- ^constrainAtZero
  | Svensson
  deriving (Show, Eq)

fittingMethod :: FittingMethod -> IO FittingMethodObject
fittingMethod (CubicSplies k c) = qlCubicBSplinesFitting k c
fittingMethod (ExponentialSplines c) = qlExponentialSplinesFitting c
fittingMethod NelsonSiegel = qlNelsonSiegelFitting
fittingMethod (SimplePolynomial d c) = qlSimplePolynomialFitting d c
fittingMethod Svensson = qlSvenssonFitting

{#fun qlCubicBSplinesFitting {withDoubleArray* `[Double]'&, `Bool', preErrorCheck- `String' errorCheck*-} -> `FittingMethodObject'#}
{#fun qlExponentialSplinesFitting {`Bool', preErrorCheck- `String' errorCheck*-} -> `FittingMethodObject'#}
{#fun qlNelsonSiegelFitting {preErrorCheck- `String' errorCheck*-} -> `FittingMethodObject'#}
{#fun qlSimplePolynomialFitting {fromIntegral `Word', `Bool', preErrorCheck- `String' errorCheck*-} -> `FittingMethodObject'#}
{#fun qlSvenssonFitting {preErrorCheck- `String' errorCheck*-} -> `FittingMethodObject'#}

-- |reference date based on current evaluation date
fittedBondDiscountCurve' :: Word -- ^settlementDays
  -> Calendar -- ^calendar
  -> [BondHelper] -- ^bonds
  -> DayCounter -- ^dayCounter
  -> FittingMethod -- ^fittingMethod
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> [Double] -- ^guess
  -> Double -- ^simplexLambda
  -> IO FittedBondDiscountCurve
fittedBondDiscountCurve' se c h dc fm a m g l = do {fmo <- fittingMethod fm; qlFittedBondDiscountCurve se c h dc fmo a m g l}

-- |curve reference date fixed for life of curve
fittedBondDiscountCurve :: Day -- ^referenceDate
  -> [BondHelper] -- ^bonds
  -> DayCounter -- ^dayCounter
  -> FittingMethod -- ^fittingMethod
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> [Double] -- ^guess
  -> Double -- ^simplexLambda
  -> IO FittedBondDiscountCurve
fittedBondDiscountCurve d h dc fm a m g l = do {fmo <- fittingMethod fm; qlFittedBondDiscountCurve1 d h dc fmo a m g l}

{#fun qlFittedBondDiscountCurve {fromIntegral `Word', `Calendar', withObjectArray* `[BondHelper]'&, `DayCounter', `FittingMethodObject', `Double', fromIntegral `Word', withDoubleArray* `[Double]'&, `Double', preErrorCheck- `String' errorCheck*-} -> `FittedBondDiscountCurve'#}

{#fun qlFittedBondDiscountCurve1 {withDay* `Day', withObjectArray* `[BondHelper]'&, `DayCounter', `FittingMethodObject', `Double', fromIntegral `Word', withDoubleArray* `[Double]'&, `Double', preErrorCheck- `String' errorCheck*-} -> `FittedBondDiscountCurve'#}

-- |final value of cost function after optimization
{#fun qlFittedBondDiscountCurveFittingMethodMinimumCostValue as minimumCostValue {`FittedBondDiscountCurve', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |final number of iterations used in the optimization problem
{#fun qlFittedBondDiscountCurveFittingMethodNumberOfIterations as numberOfIterations {`FittedBondDiscountCurve', preErrorCheck- `String' errorCheck*-} -> `Int'#}

-- TODO introduce a type class for all underlyings
{#fun qlBondHelperBond as helperBond {`BondHelper', preErrorCheck- `String' errorCheck*-} -> `Bond' peekObject*#}

{#fun qlSwapRateHelperSwap as helperSwap {`SwapRateHelper', preErrorCheck- `String' errorCheck*-} -> `VanillaSwap' peekObject*#}

{#fun qlOISRateHelperSwap as helperOIS {`OISRateHelper', preErrorCheck- `String' errorCheck*-} -> `OvernightIndexedSwap' peekObject*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
