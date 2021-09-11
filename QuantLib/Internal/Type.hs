{-# LANGUAGE FlexibleInstances #-}
module QuantLib.Internal.Type
(
    CCalendar
  , Calendar
  , peekCalendar
  , CCurrency
  , Currency
  , peekCurrency
  , CSchedule
  , Schedule
  , peekSchedule
  , CDayCounter
  , DayCounter
  , peekDayCounter

  , withSimpleType

  , CQuote
  , Quote
  , asQuote
  , peekQuote
  , CSimpleQuote
  , SimpleQuote
  , peekSimpleQuote

  , InterestRate
  , CInterestRate
  , peekInterestRate
  , TimeGrid
  , CTimeGrid
  , peekTimeGrid
  , QlClaim
  , CQlClaim
  , peekClaim
  , CQlCallability
  , QlCallability
  , peekCallability

  , SimpleType(..)

  , withCalendar
  , withCurrency
  , withMaybeCurrency
  , withDayCounter
  , withSchedule
  , withInterestRate
  , withInterestRateArray
  , withTimeGrid

  , CDividend
  , Dividend
  , withDividend
  , withDividendArray
  , peekDividend

  , CDefaultProbabilityHelper
  , DefaultProbabilityHelper
  , withDefaultProbabilityHelper
  , withDefaultProbabilityHelperArray
  , peekDefaultProbabilityHelper

  , withQuote
  , withSimpleQuote
  , withQuoteArray
  , withQuoteArrayRaw
  , withMaybeQuote

  , GenQuote

  , withLeg
  , withCouponLeg
  , peekLeg
  , peekCouponLeg
  , Leg
  , CLeg
  , CouponLeg
  , CCouponLeg
  , asLeg
  , GenLeg
  , withLegArray

  , CRateHelper
  , CSwapRateHelper
  , CBondHelper
  , COISRateHelper
  , CCalibrationHelper
  , CBlackCalibrationHelper
  , CBlackCalculator
  , CBlackScholesCalculator
  , RateHelper
  , SwapRateHelper
  , BondHelper
  , OISRateHelper
  , CalibrationHelper
  , BlackCalibrationHelper
  , BlackCalculator
  , BlackScholesCalculator
  , GenRateHelper
  , GenCalibrationHelper
  , GenBlackCalculator
  , peekRateHelper
  , peekSwapRateHelper
  , peekBondHelper
  , peekOISRateHelper
  , peekCalibrationHelper
  , peekBlackCalibrationHelper
  , withRateHelper
  , withSwapRateHelper
  , withBondHelper
  , withOISRateHelper
  , withCalibrationHelper
  , withBlackCalibrationHelper
  , asRateHelper
  , asCalibrationHelper
  , peekBlackCalculator
  , peekBlackScholesCalculator
  , withBlackCalculator
  , withBlackScholesCalculator
  , asBlackCalculator
  , withRateHelperArray
  , withBondHelperArray
  , withCalibrationHelperArray

  , CSmileSection
  , SmileSection
  , withSmileSection
  , peekSmileSection
  , CPricingEngine
  , PricingEngine
  , withPricingEngine
  , peekPricingEngine
  , CFloatingRateCouponPricer
  , FloatingRateCouponPricer
  , withFloatingRateCouponPricer
  , peekFloatingRateCouponPricer
  , withFloatingRateCouponPricerArray

  , QlOptimizationMethod
  , COptimizationMethod
  , peekOptimizationMethod
  , QlFdmSchemeDesc
  , CFdmSchemeDesc
  , peekFdmSchemeDesc
  , QlFittedBondDiscountCurveFittingMethod
  , CFittedBondDiscountCurveFittingMethod
  , peekFittedBondDiscountCurveFittingMethod
  , QlEndCriteria
  , CEndCriteria
  , peekEndCriteria
  , QlConstraint
  , CConstraint
  , peekConstraint
  , QlRounding
  , CRounding
  , peekRounding
  , QlLmVolatilityModel
  , CLmVolatilityModel
  , peekLmVolatilityModel
  , QlLmCorrelationModel
  , CLmCorrelationModel
  , peekLmCorrelationModel

  , AffineModel
  , CAffineModel
  , peekAffineModel
  , withAffineModel
  , AssetSwap
  , CAssetSwap
  , peekAssetSwap
  , withAssetSwap
  , BarrierOption
  , CBarrierOption
  , peekBarrierOption
  , withBarrierOption
  , BatesDetJumpModel
  , CBatesDetJumpModel
  , peekBatesDetJumpModel
  , withBatesDetJumpModel
  , BatesDoubleExpDetJumpModel
  , CBatesDoubleExpDetJumpModel
  , peekBatesDoubleExpDetJumpModel
  , withBatesDoubleExpDetJumpModel
  , BatesDoubleExpModel
  , CBatesDoubleExpModel
  , peekBatesDoubleExpModel
  , withBatesDoubleExpModel
  , BatesModel
  , CBatesModel
  , peekBatesModel
  , withBatesModel
  , BatesProcess
  , CBatesProcess
  , peekBatesProcess
  , withBatesProcess
  , BlackProcess
  , CBlackProcess
  , peekBlackProcess
  , withBlackProcess
  , BlackVarianceCurve
  , CBlackVarianceCurve
  , peekBlackVarianceCurve
  , withBlackVarianceCurve
  , BlackVolTermStructure
  , CBlackVolTermStructure
  , peekBlackVolTermStructure
  , withBlackVolTermStructure
  , BMAIndex
  , CBMAIndex
  , peekBMAIndex
  , withBMAIndex
  , BMASwap
  , CBMASwap
  , peekBMASwap
  , withBMASwap
  , Bond
  , CBond
  , peekBond
  , withBond
  , CalibratedModel
  , CCalibratedModel
  , peekCalibratedModel
  , withCalibratedModel
  , CallableBond
  , CCallableBond
  , peekCallableBond
  , withCallableBond
  , CallableBondVolatilityStructure
  , CCallableBondVolatilityStructure
  , peekCallableBondVolatilityStructure
  , withCallableBondVolatilityStructure
  , CapFloor
  , CCapFloor
  , peekCapFloor
  , withCapFloor
  , CapFloorTermVolSurface
  , CCapFloorTermVolSurface
  , peekCapFloorTermVolSurface
  , withCapFloorTermVolSurface
  , CdsOption
  , CCdsOption
  , peekCdsOption
  , withCdsOption
  , ConvertibleBond
  , CConvertibleBond
  , peekConvertibleBond
  , withConvertibleBond
  , CreditDefaultSwap
  , CCreditDefaultSwap
  , peekCreditDefaultSwap
  , withCreditDefaultSwap
  , DefaultProbabilityTermStructure
  , CDefaultProbabilityTermStructure
  , peekDefaultProbabilityTermStructure
  , withDefaultProbabilityTermStructure
  , DividendVanillaOption
  , CDividendVanillaOption
  , peekDividendVanillaOption
  , withDividendVanillaOption
  , ExtendedOrnsteinUhlenbeckProcess
  , CExtendedOrnsteinUhlenbeckProcess
  , peekExtendedOrnsteinUhlenbeckProcess
  , withExtendedOrnsteinUhlenbeckProcess
  , ExtOUWithJumpsProcess
  , CExtOUWithJumpsProcess
  , peekExtOUWithJumpsProcess
  , withExtOUWithJumpsProcess
  , FittedBondDiscountCurve
  , CFittedBondDiscountCurve
  , peekFittedBondDiscountCurve
  , withFittedBondDiscountCurve
  , FixedRateBond
  , CFixedRateBond
  , peekFixedRateBond
  , withFixedRateBond
  , FixedRateBondForward
  , CFixedRateBondForward
  , peekFixedRateBondForward
  , withFixedRateBondForward
  , Forward
  , CForward
  , peekForward
  , withForward
  , ForwardRateAgreement
  , CForwardRateAgreement
  , peekForwardRateAgreement
  , withForwardRateAgreement
  , ForwardVanillaOption
  , CForwardVanillaOption
  , peekForwardVanillaOption
  , withForwardVanillaOption
  , G2
  , CG2
  , peekG2
  , withG2
  , GeneralizedBlackScholesProcess
  , CGeneralizedBlackScholesProcess
  , peekGeneralizedBlackScholesProcess
  , withGeneralizedBlackScholesProcess
  , GJRGARCHModel
  , CGJRGARCHModel
  , peekGJRGARCHModel
  , withGJRGARCHModel
  , GJRGARCHProcess
  , CGJRGARCHProcess
  , peekGJRGARCHProcess
  , withGJRGARCHProcess
  , HestonModel
  , CHestonModel
  , peekHestonModel
  , withHestonModel
  , HestonProcess
  , CHestonProcess
  , peekHestonProcess
  , withHestonProcess
  , HullWhite
  , CHullWhite
  , peekHullWhite
  , withHullWhite
  , HullWhiteForwardProcess
  , CHullWhiteForwardProcess
  , peekHullWhiteForwardProcess
  , withHullWhiteForwardProcess
  , HullWhiteProcess
  , CHullWhiteProcess
  , peekHullWhiteProcess
  , withHullWhiteProcess
  , HybridHestonHullWhiteProcess
  , CHybridHestonHullWhiteProcess
  , peekHybridHestonHullWhiteProcess
  , withHybridHestonHullWhiteProcess
  , IborIndex
  , CIborIndex
  , peekIborIndex
  , withIborIndex
  , OvernightIborIndex
  , COvernightIndex
  , peekOvernightIborIndex
  , withOvernightIborIndex
  , Index
  , CIndex
  , peekIndex
  , withIndex
  , Instrument
  , CInstrument
  , peekInstrument
  , withInstrument
  , InterestRateIndex
  , CInterestRateIndex
  , peekInterestRateIndex
  , withInterestRateIndex
  , KlugeExtOUProcess
  , CKlugeExtOUProcess
  , peekKlugeExtOUProcess
  , withKlugeExtOUProcess
  , LiborForwardModel
  , CLiborForwardModel
  , peekLiborForwardModel
  , withLiborForwardModel
  , LiborForwardModelProcess
  , CLiborForwardModelProcess
  , peekLiborForwardModelProcess
  , withLiborForwardModelProcess
  , LocalVolTermStructure
  , CLocalVolTermStructure
  , peekLocalVolTermStructure
  , withLocalVolTermStructure
  , MargrabeOption
  , CMargrabeOption
  , peekMargrabeOption
  , withMargrabeOption
  , Merton76Process
  , CMerton76Process
  , peekMerton76Process
  , withMerton76Process
  , MultiAssetOption
  , CMultiAssetOption
  , peekMultiAssetOption
  , withMultiAssetOption
  , OneAssetOption
  , COneAssetOption
  , peekOneAssetOption
  , withOneAssetOption
  , OneFactorAffineModel
  , COneFactorAffineModel
  , peekOneFactorAffineModel
  , withOneFactorAffineModel
  , Option
  , COption
  , peekOption
  , withOption
  , OptionletVolatilityStructure
  , COptionletVolatilityStructure
  , peekOptionletVolatilityStructure
  , withOptionletVolatilityStructure
  , OvernightIndexedSwap
  , COvernightIndexedSwap
  , peekOvernightIndexedSwap
  , withOvernightIndexedSwap
  , OvernightIndexedSwapIndex
  , COvernightIndexedSwapIndex
  , peekOvernightIndexedSwapIndex
  , withOvernightIndexedSwapIndex
  , PiecewiseTimeDependentHestonModel
  , CPiecewiseTimeDependentHestonModel
  , peekPiecewiseTimeDependentHestonModel
  , withPiecewiseTimeDependentHestonModel
  , QuantoBarrierOption
  , CQuantoBarrierOption
  , peekQuantoBarrierOption
  , withQuantoBarrierOption
  , QuantoForwardVanillaOption
  , CQuantoForwardVanillaOption
  , peekQuantoForwardVanillaOption
  , withQuantoForwardVanillaOption
  , QuantoVanillaOption
  , CQuantoVanillaOption
  , peekQuantoVanillaOption
  , withQuantoVanillaOption
  , ShortRateModel
  , CShortRateModel
  , peekShortRateModel
  , withShortRateModel
  , StochasticProcess1D
  , CStochasticProcess1D
  , peekStochasticProcess1D
  , withStochasticProcess1D
  , StochasticProcessArray
  , CStochasticProcessArray
  , peekStochasticProcessArray
  , withStochasticProcessArray
  , StochasticProcess
  , CStochasticProcess
  , peekStochasticProcess
  , withStochasticProcess
  , Swap
  , CSwap
  , peekSwap
  , withSwap
  , SwapIndex
  , CSwapIndex
  , peekSwapIndex
  , withSwapIndex
  , Swaption
  , CSwaption
  , peekSwaption
  , withSwaption
  , SwaptionVolatilityStructure
  , CSwaptionVolatilityStructure
  , peekSwaptionVolatilityStructure
  , withSwaptionVolatilityStructure
  , TermStructure
  , CTermStructure
  , peekTermStructure
  , withTermStructure
  , VanillaOption
  , CVanillaOption
  , peekVanillaOption
  , withVanillaOption
  , VanillaSwap
  , CVanillaSwap
  , peekVanillaSwap
  , withVanillaSwap
  , VarianceGammaProcess
  , CVarianceGammaProcess
  , peekVarianceGammaProcess
  , withVarianceGammaProcess
  , VolatilityTermStructure
  , CVolatilityTermStructure
  , peekVolatilityTermStructure
  , withVolatilityTermStructure
  , YieldTermStructure
  , CYieldTermStructure
  , peekYieldTermStructure
  , withYieldTermStructure
  
  , withInstrumentArray
  , withMaybeYieldTermStructure
  , withStochasticProcess1DArray
)
  where

import Control.Monad((>=>))

import Foreign.Ptr
import Foreign.ForeignPtr
import Foreign.C.Types
import Foreign.C.String
import QuantLib.Internal

import Foreign.Marshal.Array(withArray)
import System.IO.Unsafe(unsafePerformIO)
import Foreign.Marshal.Utils(withMany)

data CCalendar
data CCurrency
data CDayCounter
data CSchedule
data CQlCallability
data CQlClaim
data CTimeGrid
data CInterestRate
data CDividend
data CSmileSection
data CPricingEngine
data CFloatingRateCouponPricer
data CDefaultProbabilityHelper
data CConstraint
data CEndCriteria
data CFdmSchemeDesc
data CFittedBondDiscountCurveFittingMethod
data COptimizationMethod
data CRounding
data CLmVolatilityModel
data CLmCorrelationModel

newtype SimpleType a = SimpleType {ptr :: ForeignPtr a}
newtype Meta a = Meta {_fin :: FinalizerPtr a}
newtype Calendar = Calendar {getCCalendar :: SimpleType CCalendar}
newtype Currency = Currency {getCCurrency :: SimpleType CCurrency}
newtype DayCounter = DayCounter {getCDayCounter :: SimpleType CDayCounter}
newtype Schedule = Schedule {getCSchedule :: SimpleType CSchedule}
newtype InterestRate = InterestRate {getCInterestRate :: SimpleType CInterestRate}
newtype TimeGrid = TimeGrid {getCTimeGrid :: SimpleType CTimeGrid}
newtype Dividend = Dividend {getCDividend :: SimpleType CDividend}
newtype SmileSection = SmileSection {getCSmileSection :: SimpleType CSmileSection}
newtype PricingEngine = PricingEngine {getCPricingEngine :: SimpleType CPricingEngine}
newtype FloatingRateCouponPricer = FloatingRateCouponPricer {getCFloatingRateCouponPricer :: SimpleType CFloatingRateCouponPricer}
newtype DefaultProbabilityHelper = DefaultProbabilityHelper {getCDefaultProbabilityHelper :: SimpleType CDefaultProbabilityHelper}
-- special cases: those types will be represented as enums so no need to wrap them
type QlClaim = SimpleType CQlClaim
type QlCallability = SimpleType CQlCallability
type QlConstraint = SimpleType CConstraint
type QlEndCriteria = SimpleType CEndCriteria
type QlFdmSchemeDesc = SimpleType CFdmSchemeDesc
type QlFittedBondDiscountCurveFittingMethod = SimpleType CFittedBondDiscountCurveFittingMethod
type QlOptimizationMethod = SimpleType COptimizationMethod
type QlRounding = SimpleType CRounding
type QlLmCorrelationModel = SimpleType CLmCorrelationModel
type QlLmVolatilityModel = SimpleType CLmVolatilityModel

calendarMeta :: Meta CCalendar
calendarMeta = Meta qlFreeCalendar

currencyMeta :: Meta CCurrency
currencyMeta = Meta qlFreeCurrency

dayCounterMeta :: Meta CDayCounter
dayCounterMeta = Meta qlFreeDayCounter

scheduleMeta :: Meta CSchedule
scheduleMeta = Meta qlFreeSchedule

callabilityMeta :: Meta CQlCallability
callabilityMeta = Meta qlFreeCallability

claimMeta :: Meta CQlClaim
claimMeta = Meta qlFreeClaim

optimizationMethodMeta :: Meta COptimizationMethod
optimizationMethodMeta = Meta qlFreeOptimizationMethod

fittedBondDiscountCurveFittingMethodMeta :: Meta CFittedBondDiscountCurveFittingMethod
fittedBondDiscountCurveFittingMethodMeta = Meta qlFreeFittedBondDiscountCurveFittingMethod

fdmSchemeDescMeta :: Meta CFdmSchemeDesc
fdmSchemeDescMeta = Meta qlFreeFdmSchemeDesc

endCritetiaMeta :: Meta CEndCriteria
endCritetiaMeta = Meta qlFreeEndCriteria

constraintMeta :: Meta CConstraint
constraintMeta = Meta qlFreeConstraint

lmCorrelationModelMeta :: Meta CLmCorrelationModel
lmCorrelationModelMeta = Meta qlFreeLmCorrelationModel

lmVolatilityModelMeta :: Meta CLmVolatilityModel
lmVolatilityModelMeta = Meta qlFreeLmVolatilityModel

timeGridMeta :: Meta CTimeGrid
timeGridMeta = Meta qlFreeTimeGrid

interestRateMeta :: Meta CInterestRate
interestRateMeta = Meta qlFreeInterestRate

dividendMeta :: Meta CDividend
dividendMeta = Meta qlFreeDividend

roundingMeta :: Meta CRounding
roundingMeta = Meta qlFreeRounding

floatingRateCouponPricerMeta :: Meta CFloatingRateCouponPricer
floatingRateCouponPricerMeta = Meta qlFreeFloatingRateCouponPricer

pricingEngineMeta :: Meta CPricingEngine
pricingEngineMeta = Meta qlFreePricingEngine

smileSectionMeta :: Meta CSmileSection
smileSectionMeta = Meta qlFreeSmileSection

defaultProbabilityHelperMeta :: Meta CDefaultProbabilityHelper
defaultProbabilityHelperMeta = Meta qlFreeDefaultProbabilityHelper

peekSimpleType :: Meta a -> Ptr a -> IO (SimpleType a)
peekSimpleType (Meta f) = newForeignPtr f >=> return . SimpleType

peekCalendar :: Ptr CCalendar -> IO Calendar
peekCalendar = peekSimpleType calendarMeta >=> return . Calendar

peekSchedule :: Ptr CSchedule -> IO Schedule
peekSchedule = peekSimpleType scheduleMeta >=> return . Schedule

peekDayCounter :: Ptr CDayCounter -> IO DayCounter
peekDayCounter = peekSimpleType dayCounterMeta >=> return . DayCounter

peekCurrency :: Ptr CCurrency -> IO Currency
peekCurrency = peekSimpleType currencyMeta >=> return . Currency

peekCallability :: Ptr CQlCallability -> IO (SimpleType CQlCallability)
peekCallability = peekSimpleType callabilityMeta

peekClaim :: Ptr CQlClaim -> IO (SimpleType CQlClaim)
peekClaim = peekSimpleType claimMeta

peekRounding :: Ptr CRounding -> IO (SimpleType CRounding)
peekRounding = peekSimpleType roundingMeta

peekConstraint :: Ptr CConstraint -> IO (SimpleType CConstraint)
peekConstraint = peekSimpleType constraintMeta

peekLmVolatilityModel :: Ptr CLmVolatilityModel -> IO (SimpleType CLmVolatilityModel)
peekLmVolatilityModel = peekSimpleType lmVolatilityModelMeta

peekLmCorrelationModel :: Ptr CLmCorrelationModel -> IO (SimpleType CLmCorrelationModel)
peekLmCorrelationModel = peekSimpleType lmCorrelationModelMeta

peekEndCriteria :: Ptr CEndCriteria -> IO (SimpleType CEndCriteria)
peekEndCriteria = peekSimpleType endCritetiaMeta

peekFittedBondDiscountCurveFittingMethod :: Ptr CFittedBondDiscountCurveFittingMethod -> IO (SimpleType CFittedBondDiscountCurveFittingMethod)
peekFittedBondDiscountCurveFittingMethod = peekSimpleType fittedBondDiscountCurveFittingMethodMeta

peekFdmSchemeDesc :: Ptr CFdmSchemeDesc -> IO (SimpleType CFdmSchemeDesc)
peekFdmSchemeDesc = peekSimpleType fdmSchemeDescMeta

peekOptimizationMethod :: Ptr COptimizationMethod -> IO (SimpleType COptimizationMethod)
peekOptimizationMethod = peekSimpleType optimizationMethodMeta

peekInterestRate :: Ptr CInterestRate -> IO InterestRate
peekInterestRate = peekSimpleType interestRateMeta >=> return . InterestRate

peekDividend :: Ptr CDividend -> IO Dividend
peekDividend = peekSimpleType dividendMeta >=> return . Dividend

peekFloatingRateCouponPricer :: Ptr CFloatingRateCouponPricer -> IO FloatingRateCouponPricer
peekFloatingRateCouponPricer = peekSimpleType floatingRateCouponPricerMeta >=> return . FloatingRateCouponPricer

peekPricingEngine :: Ptr CPricingEngine -> IO PricingEngine
peekPricingEngine = peekSimpleType pricingEngineMeta >=> return . PricingEngine

peekSmileSection :: Ptr CSmileSection -> IO SmileSection
peekSmileSection = peekSimpleType smileSectionMeta >=> return . SmileSection

peekDefaultProbabilityHelper :: Ptr CDefaultProbabilityHelper -> IO DefaultProbabilityHelper
peekDefaultProbabilityHelper = peekSimpleType defaultProbabilityHelperMeta >=> return . DefaultProbabilityHelper

peekTimeGrid :: Ptr CTimeGrid -> IO TimeGrid
peekTimeGrid = peekSimpleType timeGridMeta >=> return . TimeGrid

withSimpleType :: SimpleType a -> (Ptr a -> IO b) -> IO b
withSimpleType = withForeignPtr . ptr

withMaybeSimpleType :: Maybe (SimpleType a) -> (Ptr a -> IO b) -> IO b
withMaybeSimpleType x f = maybe (f nullPtr) (`withSimpleType` f) x

withMaybeCurrency :: Maybe Currency -> (Ptr CCurrency -> IO b) -> IO b
withMaybeCurrency = withMaybeSimpleType . (getCCurrency <$>)

foreign import ccall "ql.h &qlFreeCalendar" qlFreeCalendar :: FinalizerPtr CCalendar
foreign import ccall "ql.h &qlFreeCurrency" qlFreeCurrency :: FinalizerPtr CCurrency
foreign import ccall "ql.h &qlFreeSchedule" qlFreeSchedule :: FinalizerPtr CSchedule
foreign import ccall "ql.h &qlFreeDayCounter" qlFreeDayCounter :: FinalizerPtr CDayCounter
foreign import ccall "ql.h &qlFreeTimeGrid" qlFreeTimeGrid :: FinalizerPtr CTimeGrid
foreign import ccall "ql.h &qlFreeInterestRate" qlFreeInterestRate :: FinalizerPtr CInterestRate
foreign import ccall "ql.h &qlFreeDefaultProbabilityHelper" qlFreeDefaultProbabilityHelper :: FinalizerPtr CDefaultProbabilityHelper
foreign import ccall "ql.h &qlFreeDividend" qlFreeDividend :: FinalizerPtr CDividend
foreign import ccall "ql.h &qlFreeCallability" qlFreeCallability :: FinalizerPtr CQlCallability
foreign import ccall "ql.h &qlFreeClaim" qlFreeClaim :: FinalizerPtr CQlClaim
foreign import ccall "ql.h &qlFreeSmileSection" qlFreeSmileSection :: FinalizerPtr CSmileSection
foreign import ccall "ql.h &qlFreePricingEngine" qlFreePricingEngine :: FinalizerPtr CPricingEngine
foreign import ccall "ql.h &qlFreeFloatingCouponPricer" qlFreeFloatingRateCouponPricer :: FinalizerPtr CFloatingRateCouponPricer
foreign import ccall "ql.h &qlFreeConstraint" qlFreeConstraint :: FinalizerPtr CConstraint
foreign import ccall "ql.h &qlFreeEndCriteria" qlFreeEndCriteria :: FinalizerPtr CEndCriteria
foreign import ccall "ql.h &qlFreeFdmSchemeDesc" qlFreeFdmSchemeDesc :: FinalizerPtr CFdmSchemeDesc
foreign import ccall "ql.h &qlFreeFittedBondDiscountCurveFittingMethod" qlFreeFittedBondDiscountCurveFittingMethod :: FinalizerPtr CFittedBondDiscountCurveFittingMethod
foreign import ccall "ql.h &qlFreeOptimizationMethod" qlFreeOptimizationMethod :: FinalizerPtr COptimizationMethod
foreign import ccall "ql.h &qlFreeRounding" qlFreeRounding :: FinalizerPtr CRounding
foreign import ccall "ql.h &qlFreeLmVolatilityModel" qlFreeLmVolatilityModel :: FinalizerPtr CLmVolatilityModel
foreign import ccall "ql.h &qlFreeLmCorrelationModel" qlFreeLmCorrelationModel :: FinalizerPtr CLmCorrelationModel

showSimpleType :: (Ptr a -> IO CString) -> SimpleType a -> String
showSimpleType f x = unsafePerformIO $ withSimpleType x (f >=> peekDynString)

foreign import ccall safe "ql.h qlCalendarName" qlCalendarName :: Ptr CCalendar -> IO CString
instance Show Calendar where show x = showSimpleType qlCalendarName (getCCalendar x)
instance Eq Calendar where x == y = show x == show y

foreign import ccall safe "ql.h qlCurrencyName" qlCurrencyName :: Ptr CCurrency -> IO CString
instance Show Currency where show x = showSimpleType qlCurrencyName (getCCurrency x)
instance Eq Currency where x == y = show x == show y

foreign import ccall safe "ql.h qlDayCounterName" qlDayCounterName :: Ptr CDayCounter -> IO CString
instance Show DayCounter where show x = showSimpleType qlDayCounterName (getCDayCounter x)
instance Eq DayCounter where x == y = show x == show y

withCalendar :: Calendar -> (Ptr CCalendar -> IO b) -> IO b
withCalendar = withSimpleType . getCCalendar

withCurrency :: Currency -> (Ptr CCurrency -> IO b) -> IO b
withCurrency = withSimpleType . getCCurrency

withDayCounter :: DayCounter -> (Ptr CDayCounter -> IO b) -> IO b
withDayCounter = withSimpleType . getCDayCounter

withSchedule :: Schedule -> (Ptr CSchedule -> IO b) -> IO b
withSchedule = withSimpleType . getCSchedule

withInterestRate :: InterestRate -> (Ptr CInterestRate -> IO b) -> IO b
withInterestRate = withSimpleType . getCInterestRate

withDefaultProbabilityHelper :: DefaultProbabilityHelper -> (Ptr CDefaultProbabilityHelper -> IO b) -> IO b
withDefaultProbabilityHelper = withSimpleType . getCDefaultProbabilityHelper

withDividend :: Dividend -> (Ptr CDividend -> IO b) -> IO b
withDividend = withSimpleType . getCDividend

withFloatingRateCouponPricer :: FloatingRateCouponPricer -> (Ptr CFloatingRateCouponPricer -> IO b) -> IO b
withFloatingRateCouponPricer = withSimpleType . getCFloatingRateCouponPricer

withSmileSection :: SmileSection -> (Ptr CSmileSection -> IO b) -> IO b
withSmileSection = withSimpleType . getCSmileSection

withPricingEngine :: PricingEngine -> (Ptr CPricingEngine -> IO b) -> IO b
withPricingEngine = withSimpleType . getCPricingEngine

withTimeGrid :: TimeGrid -> (Ptr CTimeGrid -> IO b) -> IO b
withTimeGrid = withSimpleType . getCTimeGrid

withSimpleArray :: (t -> SimpleType a) -> [t] -> ((CUInt, Ptr (Ptr a)) -> IO b) -> IO b
withSimpleArray c x f = withMany withSimpleType (map c x) (`withArray` (\px -> f (fromIntegral $ length x, px)))

withInterestRateArray :: [InterestRate] -> ((CUInt, Ptr (Ptr CInterestRate)) -> IO b) -> IO b
withInterestRateArray = withSimpleArray getCInterestRate

withDefaultProbabilityHelperArray :: [DefaultProbabilityHelper] -> ((CUInt, Ptr (Ptr CDefaultProbabilityHelper)) -> IO b) -> IO b
withDefaultProbabilityHelperArray = withSimpleArray getCDefaultProbabilityHelper

withDividendArray :: [Dividend] -> ((CUInt, Ptr (Ptr CDividend)) -> IO b) -> IO b
withDividendArray = withSimpleArray getCDividend

withFloatingRateCouponPricerArray :: [FloatingRateCouponPricer] -> ((CUInt, Ptr (Ptr CFloatingRateCouponPricer)) -> IO b) -> IO b
withFloatingRateCouponPricerArray = withSimpleArray getCFloatingRateCouponPricer

---- class hierarchies
newtype MetaConv a b = MetaConv {_upcast :: Ptr a -> IO (Ptr b)}
-- we can infer upcast just from two types so actually we don't need to drag it around with the cast function
data GenObject b a = GenObject {getObject :: !(ForeignPtr a), _getMeta :: !(MetaConv a b)}

asGenObject :: Meta c -> MetaConv c c -> GenObject c a -> IO (GenObject c c)
asGenObject m0 m (GenObject p (MetaConv k)) = withForeignPtr p (\qq -> GenObject <$> (k qq >>= newForeignPtr (_fin m0)) <*> return m)

withGenObject :: GenObject c a -> (Ptr c -> IO b) -> IO b
withGenObject (GenObject p (MetaConv k)) ff = withForeignPtr p (k >=> ff)

withSubObject :: GenObject c a -> (Ptr a -> IO b) -> IO b
withSubObject = withForeignPtr . getObject

peekGenObject :: Meta c -> MetaConv c c -> Ptr c -> IO (GenObject c c)
peekGenObject m0 m p = GenObject <$> newForeignPtr (_fin m0) p <*> return m

peekSubObject :: Meta a -> MetaConv a c -> Ptr a -> IO (GenObject c a)
peekSubObject m0 m p = GenObject <$> newForeignPtr (_fin m0) p <*> return m

withGenArray :: [GenObject c a] -> ((CUInt, Ptr (Ptr c)) -> IO b) -> IO b
withGenArray x f = withMany withGenObject x (`withArray` (\px -> f (fromIntegral $ length x, px)))

withSubArray :: [GenObject c a] -> ((CUInt, Ptr (Ptr a)) -> IO b) -> IO b
withSubArray x f = withMany withSubObject x (`withArray` (\px -> f (fromIntegral $ length x, px)))

withGenArrayRaw :: [GenObject c a] -> (Ptr (Ptr c) -> IO b) -> IO b -- pass an array without length
withGenArrayRaw x f = withMany withGenObject x (`withArray` f)

withGenMaybe :: Maybe (GenObject c a) -> (Ptr c -> IO b) -> IO b
withGenMaybe x f = maybe (f nullPtr) (`withGenObject` f) x

---- instantiations
data CQuote
data CSimpleQuote
newtype GenQuote a = GenQuote {getQuote :: GenObject CQuote a}
type Quote = GenQuote CQuote
type SimpleQuote = GenQuote CSimpleQuote
foreign import ccall "ql.h &qlFreeQuote" qlFreeQuote :: FinalizerPtr CQuote
foreign import ccall "ql.h &qlFreeSimpleQuote" qlFreeSimpleQuote :: FinalizerPtr CSimpleQuote
foreign import ccall safe "ql.h qlSimpleQuoteAsQuote" qlSimpleQuoteAsQuote :: Ptr CSimpleQuote -> IO (Ptr CQuote)

quoteMeta :: Meta CQuote
quoteMeta = Meta qlFreeQuote

simpleQuoteMeta :: Meta CSimpleQuote
simpleQuoteMeta = Meta qlFreeSimpleQuote

quoteMetaConv :: MetaConv CQuote CQuote
quoteMetaConv = MetaConv return

simpleQuoteMetaConv :: MetaConv CSimpleQuote CQuote
simpleQuoteMetaConv = MetaConv qlSimpleQuoteAsQuote

-- Haskell does not allow function arguments like [forall a.GenQuote a]
-- let's at least provide a way to convert all quote classes to the most generic one
asQuote :: GenQuote a -> IO (GenQuote CQuote)
asQuote (GenQuote q) = GenQuote <$> asGenObject quoteMeta quoteMetaConv q

withQuote :: GenQuote a -> (Ptr CQuote -> IO b) -> IO b
withQuote = withGenObject . getQuote

withSimpleQuote :: GenQuote CSimpleQuote -> (Ptr CSimpleQuote-> IO b) -> IO b
withSimpleQuote = withSubObject . getQuote

peekQuote :: Ptr CQuote -> IO (GenQuote CQuote)
peekQuote p = GenQuote <$> peekGenObject quoteMeta quoteMetaConv p

peekSimpleQuote :: Ptr CSimpleQuote -> IO (GenQuote CSimpleQuote)
peekSimpleQuote p = GenQuote <$> peekSubObject simpleQuoteMeta simpleQuoteMetaConv p

withQuoteArray :: [GenQuote a] -> ((CUInt, Ptr (Ptr CQuote)) -> IO b) -> IO b
withQuoteArray x = withGenArray (map getQuote x)

withQuoteArrayRaw :: [GenQuote a] -> (Ptr (Ptr CQuote) -> IO b) -> IO b
withQuoteArrayRaw x = withGenArrayRaw (map getQuote x)

withMaybeQuote :: Maybe (GenQuote a) -> (Ptr CQuote -> IO b) -> IO b
withMaybeQuote x = withGenMaybe (getQuote <$> x)

data CLeg
data CCouponLeg
newtype GenLeg a = GenLeg {getLeg :: GenObject CLeg a}
type Leg = GenLeg CLeg
type CouponLeg = GenLeg CCouponLeg
foreign import ccall "ql.h &qlFreeLeg" qlFreeLeg :: FinalizerPtr CLeg
foreign import ccall "ql.h &qlFreeCouponLeg" qlFreeCouponLeg :: FinalizerPtr CCouponLeg
foreign import ccall safe "ql.h qlCouponLegAsLeg" qlCouponLegAsLeg :: Ptr CCouponLeg -> IO (Ptr CLeg)

legMeta :: Meta CLeg
legMeta = Meta qlFreeLeg

couponLegMeta :: Meta CCouponLeg
couponLegMeta = Meta qlFreeCouponLeg

legMetaConv :: MetaConv CLeg CLeg
legMetaConv = MetaConv return

couponLegMetaConv :: MetaConv CCouponLeg CLeg
couponLegMetaConv = MetaConv qlCouponLegAsLeg

asLeg :: GenLeg a -> IO (GenLeg CLeg)
asLeg (GenLeg q) = GenLeg <$> asGenObject legMeta legMetaConv q

withLeg :: GenLeg a -> (Ptr CLeg -> IO b) -> IO b
withLeg = withGenObject . getLeg

withCouponLeg :: GenLeg CCouponLeg -> (Ptr CCouponLeg-> IO b) -> IO b
withCouponLeg = withSubObject . getLeg

peekLeg :: Ptr CLeg -> IO (GenLeg CLeg)
peekLeg p = GenLeg <$> peekGenObject legMeta legMetaConv p

peekCouponLeg :: Ptr CCouponLeg -> IO (GenLeg CCouponLeg)
peekCouponLeg p = GenLeg <$> peekSubObject couponLegMeta couponLegMetaConv p

withLegArray :: [GenLeg a] -> ((CUInt, Ptr (Ptr CLeg)) -> IO b) -> IO b
withLegArray x = withGenArray (map getLeg x)

data CRateHelper
data CSwapRateHelper
data CBondHelper
data COISRateHelper
data CCalibrationHelper
data CBlackCalibrationHelper
data CBlackCalculator
data CBlackScholesCalculator
newtype GenRateHelper a = GenRateHelper {getRateHelper :: GenObject CRateHelper a}
newtype GenCalibrationHelper a = GenCalibrationHelper {getCalibrationHelper :: GenObject CCalibrationHelper a}
newtype GenBlackCalculator a = GenBlackCalculator {getBlackCalculator :: GenObject CBlackCalculator a}
type RateHelper = GenRateHelper CRateHelper
type SwapRateHelper = GenRateHelper CSwapRateHelper
type BondHelper = GenRateHelper CBondHelper
type OISRateHelper = GenRateHelper COISRateHelper
type CalibrationHelper = GenCalibrationHelper CCalibrationHelper
type BlackCalibrationHelper = GenCalibrationHelper CBlackCalibrationHelper
type BlackCalculator = GenBlackCalculator CBlackCalculator
type BlackScholesCalculator = GenBlackCalculator CBlackScholesCalculator
foreign import ccall "ql.h &qlFreeRateHelper" qlFreeRateHelper :: FinalizerPtr CRateHelper
foreign import ccall "ql.h &qlFreeBondHelper" qlFreeBondHelper :: FinalizerPtr CBondHelper
foreign import ccall "ql.h &qlFreeSwapRateHelper" qlFreeSwapRateHelper :: FinalizerPtr CSwapRateHelper
foreign import ccall "ql.h &qlFreeOISRateHelper" qlFreeOISRateHelper :: FinalizerPtr COISRateHelper
foreign import ccall safe "ql.h qlSwapRateHelperAsRateHelper" qlSwapRateHelperAsRateHelper :: Ptr CSwapRateHelper -> IO (Ptr CRateHelper)
foreign import ccall safe "ql.h qlBondHelperAsRateHelper" qlBondHelperAsRateHelper :: Ptr CBondHelper -> IO (Ptr CRateHelper)
foreign import ccall safe "ql.h qlOISRateHelperAsRateHelper" qlOISRateHelperAsRateHelper :: Ptr COISRateHelper -> IO (Ptr CRateHelper)
foreign import ccall "ql.h &qlFreeCalibrationHelper" qlFreeCalibrationHelper :: FinalizerPtr CCalibrationHelper
foreign import ccall "ql.h &qlFreeBondHelper" qlFreeBlackCalibrationHelper :: FinalizerPtr CBlackCalibrationHelper
foreign import ccall safe "ql.h qlBlackCalibrationHelperAsCalibrationHelper" qlBlackCalibrationHelperAsCalibrationHelper :: Ptr CBlackCalibrationHelper -> IO (Ptr CCalibrationHelper)
foreign import ccall "ql.h &qlFreeBlackCalculator" qlFreeBlackCalculator :: FinalizerPtr CBlackCalculator
foreign import ccall "ql.h &qlFreeBlackScholesCalculator" qlFreeBlackScholesCalculator :: FinalizerPtr CBlackScholesCalculator
foreign import ccall safe "ql.h qlBlackScholesCalculatorAsBlackCalculator" qlBlackScholesCalculatorAsBlackCalculator :: Ptr CBlackScholesCalculator -> IO (Ptr CBlackCalculator)

rateHelperMeta :: Meta CRateHelper
rateHelperMeta = Meta qlFreeRateHelper

bondHelperMeta :: Meta CBondHelper
bondHelperMeta = Meta qlFreeBondHelper

swapRateHelperMeta :: Meta CSwapRateHelper
swapRateHelperMeta = Meta qlFreeSwapRateHelper

oisRateHelperMeta :: Meta COISRateHelper
oisRateHelperMeta = Meta qlFreeOISRateHelper

rateHelperMetaConv :: MetaConv CRateHelper CRateHelper
rateHelperMetaConv = MetaConv return

bondHelperMetaConv :: MetaConv CBondHelper CRateHelper
bondHelperMetaConv = MetaConv qlBondHelperAsRateHelper

swapRateHelperMetaConv :: MetaConv CSwapRateHelper CRateHelper
swapRateHelperMetaConv = MetaConv qlSwapRateHelperAsRateHelper

oisRateHelperMetaConv :: MetaConv COISRateHelper CRateHelper
oisRateHelperMetaConv = MetaConv qlOISRateHelperAsRateHelper

asRateHelper :: GenRateHelper a -> IO (GenRateHelper CRateHelper)
asRateHelper (GenRateHelper q) = GenRateHelper <$> asGenObject rateHelperMeta rateHelperMetaConv q

withRateHelper :: GenRateHelper a -> (Ptr CRateHelper -> IO b) -> IO b
withRateHelper = withGenObject . getRateHelper

peekRateHelper :: Ptr CRateHelper -> IO (GenRateHelper CRateHelper)
peekRateHelper p = GenRateHelper <$> peekGenObject rateHelperMeta rateHelperMetaConv p

withBondHelper :: GenRateHelper CBondHelper -> (Ptr CBondHelper-> IO b) -> IO b
withBondHelper = withSubObject . getRateHelper

peekBondHelper :: Ptr CBondHelper -> IO (GenRateHelper CBondHelper)
peekBondHelper p = GenRateHelper <$> peekSubObject bondHelperMeta bondHelperMetaConv p

withSwapRateHelper :: GenRateHelper CSwapRateHelper -> (Ptr CSwapRateHelper-> IO b) -> IO b
withSwapRateHelper = withSubObject . getRateHelper

peekSwapRateHelper :: Ptr CSwapRateHelper -> IO (GenRateHelper CSwapRateHelper)
peekSwapRateHelper p = GenRateHelper <$> peekSubObject swapRateHelperMeta swapRateHelperMetaConv p

withOISRateHelper :: GenRateHelper COISRateHelper -> (Ptr COISRateHelper-> IO b) -> IO b
withOISRateHelper = withSubObject . getRateHelper

peekOISRateHelper :: Ptr COISRateHelper -> IO (GenRateHelper COISRateHelper)
peekOISRateHelper p = GenRateHelper <$> peekSubObject oisRateHelperMeta oisRateHelperMetaConv p

calibrationHelperMeta :: Meta CCalibrationHelper
calibrationHelperMeta = Meta qlFreeCalibrationHelper

blackCalibrationHelperMeta :: Meta CBlackCalibrationHelper
blackCalibrationHelperMeta = Meta qlFreeBlackCalibrationHelper

calibrationHelperMetaConv :: MetaConv CCalibrationHelper CCalibrationHelper
calibrationHelperMetaConv = MetaConv return

blackCalibrationHelperMetaConv :: MetaConv CBlackCalibrationHelper CCalibrationHelper
blackCalibrationHelperMetaConv = MetaConv qlBlackCalibrationHelperAsCalibrationHelper

asCalibrationHelper :: GenCalibrationHelper a -> IO (GenCalibrationHelper CCalibrationHelper)
asCalibrationHelper (GenCalibrationHelper q) = GenCalibrationHelper <$> asGenObject calibrationHelperMeta calibrationHelperMetaConv q

withCalibrationHelper :: GenCalibrationHelper a -> (Ptr CCalibrationHelper -> IO b) -> IO b
withCalibrationHelper = withGenObject . getCalibrationHelper

peekCalibrationHelper :: Ptr CCalibrationHelper -> IO (GenCalibrationHelper CCalibrationHelper)
peekCalibrationHelper p = GenCalibrationHelper <$> peekGenObject calibrationHelperMeta calibrationHelperMetaConv p

withBlackCalibrationHelper :: GenCalibrationHelper CBlackCalibrationHelper -> (Ptr CBlackCalibrationHelper-> IO b) -> IO b
withBlackCalibrationHelper = withSubObject . getCalibrationHelper

peekBlackCalibrationHelper :: Ptr CBlackCalibrationHelper -> IO (GenCalibrationHelper CBlackCalibrationHelper)
peekBlackCalibrationHelper p = GenCalibrationHelper <$> peekSubObject blackCalibrationHelperMeta blackCalibrationHelperMetaConv p

blackCalculatorMeta :: Meta CBlackCalculator
blackCalculatorMeta = Meta qlFreeBlackCalculator

blackScholesCalculatorMeta :: Meta CBlackScholesCalculator
blackScholesCalculatorMeta = Meta qlFreeBlackScholesCalculator

blackCalculatorMetaConv :: MetaConv CBlackCalculator CBlackCalculator
blackCalculatorMetaConv = MetaConv return

blackScholesCalculatorMetaConv :: MetaConv CBlackScholesCalculator CBlackCalculator
blackScholesCalculatorMetaConv = MetaConv qlBlackScholesCalculatorAsBlackCalculator

asBlackCalculator :: GenBlackCalculator a -> IO (GenBlackCalculator CBlackCalculator)
asBlackCalculator (GenBlackCalculator q) = GenBlackCalculator <$> asGenObject blackCalculatorMeta blackCalculatorMetaConv q

withBlackCalculator :: GenBlackCalculator a -> (Ptr CBlackCalculator -> IO b) -> IO b
withBlackCalculator = withGenObject . getBlackCalculator

peekBlackCalculator :: Ptr CBlackCalculator -> IO (GenBlackCalculator CBlackCalculator)
peekBlackCalculator p = GenBlackCalculator <$> peekGenObject blackCalculatorMeta blackCalculatorMetaConv p

withBlackScholesCalculator :: GenBlackCalculator CBlackScholesCalculator -> (Ptr CBlackScholesCalculator-> IO b) -> IO b
withBlackScholesCalculator = withSubObject . getBlackCalculator

peekBlackScholesCalculator :: Ptr CBlackScholesCalculator -> IO (GenBlackCalculator CBlackScholesCalculator)
peekBlackScholesCalculator p = GenBlackCalculator <$> peekSubObject blackScholesCalculatorMeta blackScholesCalculatorMetaConv p

withRateHelperArray :: [GenRateHelper a] -> ((CUInt, Ptr (Ptr CRateHelper)) -> IO b) -> IO b
withRateHelperArray x = withGenArray (map getRateHelper x)

withBondHelperArray :: [BondHelper] -> ((CUInt, Ptr (Ptr CBondHelper)) -> IO b) -> IO b
withBondHelperArray x = withSubArray (map getRateHelper x)

withCalibrationHelperArray :: [GenCalibrationHelper a] -> ((CUInt, Ptr (Ptr CCalibrationHelper)) -> IO b) -> IO b
withCalibrationHelperArray x = withGenArray (map getCalibrationHelper x)

--bondMeta :: MetaConv CBond ()
--bondMeta = MetaConv qlFreeBond undefined
--
--fixedRateBondMeta :: MetaConv CFixedRateBond CBond
--fixedRateBondMeta = MetaConv qlFreeFixedRateBond qlFixedRateBondAsBond
--
--floatingRateBondMeta :: MetaConv CFloatingRateBond CBond
--floatingRateBondMeta = MetaConv qlFreeFloatingRateBond qlFloatingRateBondAsBond
--
--
--data CBond
--data CFixedRateBond
--data CFloatingRateBond
--
--type Bond = ComplexType CBond ()
--type FixedRateBond = ComplexType CFixedRateBond CBond
--type FloatingRateBond = ComplexType CFloatingRateBond CBond
--
--peekBond :: Ptr CBond -> IO Bond
--peekBond = peekComplexType bondMeta
--
--peekFixedRateBond :: Ptr CFixedRateBond -> IO FixedRateBond
--peekFixedRateBond = peekComplexType fixedRateBondMeta
--
--peekFloatingRateBond :: Ptr CFloatingRateBond -> IO FloatingRateBond
--peekFloatingRateBond = peekComplexType floatingRateBondMeta
--
--fixedRateBondAsBond :: FixedRateBond -> Bond
--fixedRateBondAsBond = asBond
--
--floatingRateBondAsBond :: FloatingRateBond -> Bond
--floatingRateBondAsBond = asBond
--
--withBond :: Bond -> (Ptr CBond -> IO b) -> IO b
--withBond = withComplexType
--
--withFixedRateBond :: FixedRateBond -> (Ptr CFixedRateBond -> IO b) -> IO b
--withFixedRateBond = withComplexType
--
--withFloatingRateBond :: FloatingRateBond -> (Ptr CFloatingRateBond -> IO b) -> IO b
--withFloatingRateBond = withComplexType
--
--asBond :: ComplexType a CBond -> Bond
--asBond = createCast bondMeta
--
--foreign import ccall "QuantLib/Instrument/Bond.chs.h &qlFreeBond"
--  qlFreeBond :: FinalizerPtr CBond
--
--foreign import ccall "QuantLib/Instrument/Bond.chs.h &qlFreeFixedRateBond"
--  qlFreeFixedRateBond :: FinalizerPtr CFixedRateBond
--
--foreign import ccall "QuantLib/Instrument/Bond.chs.h &qlFreeFloatingRateBond"
--  qlFreeFloatingRateBond :: FinalizerPtr CFloatingRateBond
--
--foreign import ccall safe "QuantLib/Instrument/Bond.chs.h qlFixedRateBondAsBond"
--  qlFixedRateBondAsBond :: Ptr CFixedRateBond -> IO (Ptr CBond)
--
--foreign import ccall safe "QuantLib/Instrument/Bond.chs.h qlFloatingRateBondAsBond"
--  qlFloatingRateBondAsBond :: Ptr CFloatingRateBond -> IO (Ptr CBond)

------

-- temporary storage before hierarchies are migrated off type classes

data CAffineModel
newtype AffineModel = AffineModel {getCAffineModel :: SimpleType CAffineModel}
affineModelMeta :: Meta CAffineModel
affineModelMeta = Meta qlFreeAffineModel
peekAffineModel :: Ptr CAffineModel -> IO AffineModel
peekAffineModel = peekSimpleType affineModelMeta >=> return . AffineModel
withAffineModel :: AffineModel -> (Ptr CAffineModel -> IO b) -> IO b
withAffineModel = withSimpleType . getCAffineModel
data CAssetSwap
newtype AssetSwap = AssetSwap {getCAssetSwap :: SimpleType CAssetSwap}
assetSwapMeta :: Meta CAssetSwap
assetSwapMeta = Meta qlFreeAssetSwap
peekAssetSwap :: Ptr CAssetSwap -> IO AssetSwap
peekAssetSwap = peekSimpleType assetSwapMeta >=> return . AssetSwap
withAssetSwap :: AssetSwap -> (Ptr CAssetSwap -> IO b) -> IO b
withAssetSwap = withSimpleType . getCAssetSwap
data CBarrierOption
newtype BarrierOption = BarrierOption {getCBarrierOption :: SimpleType CBarrierOption}
barrierOptionMeta :: Meta CBarrierOption
barrierOptionMeta = Meta qlFreeBarrierOption
peekBarrierOption :: Ptr CBarrierOption -> IO BarrierOption
peekBarrierOption = peekSimpleType barrierOptionMeta >=> return . BarrierOption
withBarrierOption :: BarrierOption -> (Ptr CBarrierOption -> IO b) -> IO b
withBarrierOption = withSimpleType . getCBarrierOption
data CBatesDetJumpModel
newtype BatesDetJumpModel = BatesDetJumpModel {getCBatesDetJumpModel :: SimpleType CBatesDetJumpModel}
batesDetJumpModelMeta :: Meta CBatesDetJumpModel
batesDetJumpModelMeta = Meta qlFreeBatesDetJumpModel
peekBatesDetJumpModel :: Ptr CBatesDetJumpModel -> IO BatesDetJumpModel
peekBatesDetJumpModel = peekSimpleType batesDetJumpModelMeta >=> return . BatesDetJumpModel
withBatesDetJumpModel :: BatesDetJumpModel -> (Ptr CBatesDetJumpModel -> IO b) -> IO b
withBatesDetJumpModel = withSimpleType . getCBatesDetJumpModel
data CBatesDoubleExpDetJumpModel
newtype BatesDoubleExpDetJumpModel = BatesDoubleExpDetJumpModel {getCBatesDoubleExpDetJumpModel :: SimpleType CBatesDoubleExpDetJumpModel}
batesDoubleExpDetJumpModelMeta :: Meta CBatesDoubleExpDetJumpModel
batesDoubleExpDetJumpModelMeta = Meta qlFreeBatesDoubleExpDetJumpModel
peekBatesDoubleExpDetJumpModel :: Ptr CBatesDoubleExpDetJumpModel -> IO BatesDoubleExpDetJumpModel
peekBatesDoubleExpDetJumpModel = peekSimpleType batesDoubleExpDetJumpModelMeta >=> return . BatesDoubleExpDetJumpModel
withBatesDoubleExpDetJumpModel :: BatesDoubleExpDetJumpModel -> (Ptr CBatesDoubleExpDetJumpModel -> IO b) -> IO b
withBatesDoubleExpDetJumpModel = withSimpleType . getCBatesDoubleExpDetJumpModel
data CBatesDoubleExpModel
newtype BatesDoubleExpModel = BatesDoubleExpModel {getCBatesDoubleExpModel :: SimpleType CBatesDoubleExpModel}
batesDoubleExpModelMeta :: Meta CBatesDoubleExpModel
batesDoubleExpModelMeta = Meta qlFreeBatesDoubleExpModel
peekBatesDoubleExpModel :: Ptr CBatesDoubleExpModel -> IO BatesDoubleExpModel
peekBatesDoubleExpModel = peekSimpleType batesDoubleExpModelMeta >=> return . BatesDoubleExpModel
withBatesDoubleExpModel :: BatesDoubleExpModel -> (Ptr CBatesDoubleExpModel -> IO b) -> IO b
withBatesDoubleExpModel = withSimpleType . getCBatesDoubleExpModel
data CBatesModel
newtype BatesModel = BatesModel {getCBatesModel :: SimpleType CBatesModel}
batesModelMeta :: Meta CBatesModel
batesModelMeta = Meta qlFreeBatesModel
peekBatesModel :: Ptr CBatesModel -> IO BatesModel
peekBatesModel = peekSimpleType batesModelMeta >=> return . BatesModel
withBatesModel :: BatesModel -> (Ptr CBatesModel -> IO b) -> IO b
withBatesModel = withSimpleType . getCBatesModel
data CBatesProcess
newtype BatesProcess = BatesProcess {getCBatesProcess :: SimpleType CBatesProcess}
batesProcessMeta :: Meta CBatesProcess
batesProcessMeta = Meta qlFreeBatesProcess
peekBatesProcess :: Ptr CBatesProcess -> IO BatesProcess
peekBatesProcess = peekSimpleType batesProcessMeta >=> return . BatesProcess
withBatesProcess :: BatesProcess -> (Ptr CBatesProcess -> IO b) -> IO b
withBatesProcess = withSimpleType . getCBatesProcess
data CBlackProcess
newtype BlackProcess = BlackProcess {getCBlackProcess :: SimpleType CBlackProcess}
blackProcessMeta :: Meta CBlackProcess
blackProcessMeta = Meta qlFreeBlackProcess
peekBlackProcess :: Ptr CBlackProcess -> IO BlackProcess
peekBlackProcess = peekSimpleType blackProcessMeta >=> return . BlackProcess
withBlackProcess :: BlackProcess -> (Ptr CBlackProcess -> IO b) -> IO b
withBlackProcess = withSimpleType . getCBlackProcess
data CBlackVarianceCurve
newtype BlackVarianceCurve = BlackVarianceCurve {getCBlackVarianceCurve :: SimpleType CBlackVarianceCurve}
blackVarianceCurveMeta :: Meta CBlackVarianceCurve
blackVarianceCurveMeta = Meta qlFreeBlackVarianceCurve
peekBlackVarianceCurve :: Ptr CBlackVarianceCurve -> IO BlackVarianceCurve
peekBlackVarianceCurve = peekSimpleType blackVarianceCurveMeta >=> return . BlackVarianceCurve
withBlackVarianceCurve :: BlackVarianceCurve -> (Ptr CBlackVarianceCurve -> IO b) -> IO b
withBlackVarianceCurve = withSimpleType . getCBlackVarianceCurve
data CBlackVolTermStructure
newtype BlackVolTermStructure = BlackVolTermStructure {getCBlackVolTermStructure :: SimpleType CBlackVolTermStructure}
blackVolTermStructureMeta :: Meta CBlackVolTermStructure
blackVolTermStructureMeta = Meta qlFreeBlackVolTermStructure
peekBlackVolTermStructure :: Ptr CBlackVolTermStructure -> IO BlackVolTermStructure
peekBlackVolTermStructure = peekSimpleType blackVolTermStructureMeta >=> return . BlackVolTermStructure
withBlackVolTermStructure :: BlackVolTermStructure -> (Ptr CBlackVolTermStructure -> IO b) -> IO b
withBlackVolTermStructure = withSimpleType . getCBlackVolTermStructure
data CBMAIndex
newtype BMAIndex = BMAIndex {getCBMAIndex :: SimpleType CBMAIndex}
bMAIndexMeta :: Meta CBMAIndex
bMAIndexMeta = Meta qlFreeBMAIndex
peekBMAIndex :: Ptr CBMAIndex -> IO BMAIndex
peekBMAIndex = peekSimpleType bMAIndexMeta >=> return . BMAIndex
withBMAIndex :: BMAIndex -> (Ptr CBMAIndex -> IO b) -> IO b
withBMAIndex = withSimpleType . getCBMAIndex
data CBMASwap
newtype BMASwap = BMASwap {getCBMASwap :: SimpleType CBMASwap}
bMASwapMeta :: Meta CBMASwap
bMASwapMeta = Meta qlFreeBMASwap
peekBMASwap :: Ptr CBMASwap -> IO BMASwap
peekBMASwap = peekSimpleType bMASwapMeta >=> return . BMASwap
withBMASwap :: BMASwap -> (Ptr CBMASwap -> IO b) -> IO b
withBMASwap = withSimpleType . getCBMASwap
data CBond
newtype Bond = Bond {getCBond :: SimpleType CBond}
bondMeta :: Meta CBond
bondMeta = Meta qlFreeBond
peekBond :: Ptr CBond -> IO Bond
peekBond = peekSimpleType bondMeta >=> return . Bond
withBond :: Bond -> (Ptr CBond -> IO b) -> IO b
withBond = withSimpleType . getCBond
data CCalibratedModel
newtype CalibratedModel = CalibratedModel {getCCalibratedModel :: SimpleType CCalibratedModel}
calibratedModelMeta :: Meta CCalibratedModel
calibratedModelMeta = Meta qlFreeCalibratedModel
peekCalibratedModel :: Ptr CCalibratedModel -> IO CalibratedModel
peekCalibratedModel = peekSimpleType calibratedModelMeta >=> return . CalibratedModel
withCalibratedModel :: CalibratedModel -> (Ptr CCalibratedModel -> IO b) -> IO b
withCalibratedModel = withSimpleType . getCCalibratedModel
data CCallableBond
newtype CallableBond = CallableBond {getCCallableBond :: SimpleType CCallableBond}
callableBondMeta :: Meta CCallableBond
callableBondMeta = Meta qlFreeCallableBond
peekCallableBond :: Ptr CCallableBond -> IO CallableBond
peekCallableBond = peekSimpleType callableBondMeta >=> return . CallableBond
withCallableBond :: CallableBond -> (Ptr CCallableBond -> IO b) -> IO b
withCallableBond = withSimpleType . getCCallableBond
data CCallableBondVolatilityStructure
newtype CallableBondVolatilityStructure = CallableBondVolatilityStructure {getCCallableBondVolatilityStructure :: SimpleType CCallableBondVolatilityStructure}
callableBondVolatilityStructureMeta :: Meta CCallableBondVolatilityStructure
callableBondVolatilityStructureMeta = Meta qlFreeCallableBondVolatilityStructure
peekCallableBondVolatilityStructure :: Ptr CCallableBondVolatilityStructure -> IO CallableBondVolatilityStructure
peekCallableBondVolatilityStructure = peekSimpleType callableBondVolatilityStructureMeta >=> return . CallableBondVolatilityStructure
withCallableBondVolatilityStructure :: CallableBondVolatilityStructure -> (Ptr CCallableBondVolatilityStructure -> IO b) -> IO b
withCallableBondVolatilityStructure = withSimpleType . getCCallableBondVolatilityStructure
data CCapFloor
newtype CapFloor = CapFloor {getCCapFloor :: SimpleType CCapFloor}
capFloorMeta :: Meta CCapFloor
capFloorMeta = Meta qlFreeCapFloor
peekCapFloor :: Ptr CCapFloor -> IO CapFloor
peekCapFloor = peekSimpleType capFloorMeta >=> return . CapFloor
withCapFloor :: CapFloor -> (Ptr CCapFloor -> IO b) -> IO b
withCapFloor = withSimpleType . getCCapFloor
data CCapFloorTermVolSurface
newtype CapFloorTermVolSurface = CapFloorTermVolSurface {getCCapFloorTermVolSurface :: SimpleType CCapFloorTermVolSurface}
capFloorTermVolSurfaceMeta :: Meta CCapFloorTermVolSurface
capFloorTermVolSurfaceMeta = Meta qlFreeCapFloorTermVolSurface
peekCapFloorTermVolSurface :: Ptr CCapFloorTermVolSurface -> IO CapFloorTermVolSurface
peekCapFloorTermVolSurface = peekSimpleType capFloorTermVolSurfaceMeta >=> return . CapFloorTermVolSurface
withCapFloorTermVolSurface :: CapFloorTermVolSurface -> (Ptr CCapFloorTermVolSurface -> IO b) -> IO b
withCapFloorTermVolSurface = withSimpleType . getCCapFloorTermVolSurface
data CCdsOption
newtype CdsOption = CdsOption {getCCdsOption :: SimpleType CCdsOption}
cdsOptionMeta :: Meta CCdsOption
cdsOptionMeta = Meta qlFreeCdsOption
peekCdsOption :: Ptr CCdsOption -> IO CdsOption
peekCdsOption = peekSimpleType cdsOptionMeta >=> return . CdsOption
withCdsOption :: CdsOption -> (Ptr CCdsOption -> IO b) -> IO b
withCdsOption = withSimpleType . getCCdsOption
data CConvertibleBond
newtype ConvertibleBond = ConvertibleBond {getCConvertibleBond :: SimpleType CConvertibleBond}
convertibleBondMeta :: Meta CConvertibleBond
convertibleBondMeta = Meta qlFreeConvertibleBond
peekConvertibleBond :: Ptr CConvertibleBond -> IO ConvertibleBond
peekConvertibleBond = peekSimpleType convertibleBondMeta >=> return . ConvertibleBond
withConvertibleBond :: ConvertibleBond -> (Ptr CConvertibleBond -> IO b) -> IO b
withConvertibleBond = withSimpleType . getCConvertibleBond
data CCreditDefaultSwap
newtype CreditDefaultSwap = CreditDefaultSwap {getCCreditDefaultSwap :: SimpleType CCreditDefaultSwap}
creditDefaultSwapMeta :: Meta CCreditDefaultSwap
creditDefaultSwapMeta = Meta qlFreeCreditDefaultSwap
peekCreditDefaultSwap :: Ptr CCreditDefaultSwap -> IO CreditDefaultSwap
peekCreditDefaultSwap = peekSimpleType creditDefaultSwapMeta >=> return . CreditDefaultSwap
withCreditDefaultSwap :: CreditDefaultSwap -> (Ptr CCreditDefaultSwap -> IO b) -> IO b
withCreditDefaultSwap = withSimpleType . getCCreditDefaultSwap
data CDefaultProbabilityTermStructure
newtype DefaultProbabilityTermStructure = DefaultProbabilityTermStructure {getCDefaultProbabilityTermStructure :: SimpleType CDefaultProbabilityTermStructure}
defaultProbabilityTermStructureMeta :: Meta CDefaultProbabilityTermStructure
defaultProbabilityTermStructureMeta = Meta qlFreeDefaultProbabilityTermStructure
peekDefaultProbabilityTermStructure :: Ptr CDefaultProbabilityTermStructure -> IO DefaultProbabilityTermStructure
peekDefaultProbabilityTermStructure = peekSimpleType defaultProbabilityTermStructureMeta >=> return . DefaultProbabilityTermStructure
withDefaultProbabilityTermStructure :: DefaultProbabilityTermStructure -> (Ptr CDefaultProbabilityTermStructure -> IO b) -> IO b
withDefaultProbabilityTermStructure = withSimpleType . getCDefaultProbabilityTermStructure
data CDividendVanillaOption
newtype DividendVanillaOption = DividendVanillaOption {getCDividendVanillaOption :: SimpleType CDividendVanillaOption}
dividendVanillaOptionMeta :: Meta CDividendVanillaOption
dividendVanillaOptionMeta = Meta qlFreeDividendVanillaOption
peekDividendVanillaOption :: Ptr CDividendVanillaOption -> IO DividendVanillaOption
peekDividendVanillaOption = peekSimpleType dividendVanillaOptionMeta >=> return . DividendVanillaOption
withDividendVanillaOption :: DividendVanillaOption -> (Ptr CDividendVanillaOption -> IO b) -> IO b
withDividendVanillaOption = withSimpleType . getCDividendVanillaOption
data CExtendedOrnsteinUhlenbeckProcess
newtype ExtendedOrnsteinUhlenbeckProcess = ExtendedOrnsteinUhlenbeckProcess {getCExtendedOrnsteinUhlenbeckProcess :: SimpleType CExtendedOrnsteinUhlenbeckProcess}
extendedOrnsteinUhlenbeckProcessMeta :: Meta CExtendedOrnsteinUhlenbeckProcess
extendedOrnsteinUhlenbeckProcessMeta = Meta qlFreeExtendedOrnsteinUhlenbeckProcess
peekExtendedOrnsteinUhlenbeckProcess :: Ptr CExtendedOrnsteinUhlenbeckProcess -> IO ExtendedOrnsteinUhlenbeckProcess
peekExtendedOrnsteinUhlenbeckProcess = peekSimpleType extendedOrnsteinUhlenbeckProcessMeta >=> return . ExtendedOrnsteinUhlenbeckProcess
withExtendedOrnsteinUhlenbeckProcess :: ExtendedOrnsteinUhlenbeckProcess -> (Ptr CExtendedOrnsteinUhlenbeckProcess -> IO b) -> IO b
withExtendedOrnsteinUhlenbeckProcess = withSimpleType . getCExtendedOrnsteinUhlenbeckProcess
data CExtOUWithJumpsProcess
newtype ExtOUWithJumpsProcess = ExtOUWithJumpsProcess {getCExtOUWithJumpsProcess :: SimpleType CExtOUWithJumpsProcess}
extOUWithJumpsProcessMeta :: Meta CExtOUWithJumpsProcess
extOUWithJumpsProcessMeta = Meta qlFreeExtOUWithJumpsProcess
peekExtOUWithJumpsProcess :: Ptr CExtOUWithJumpsProcess -> IO ExtOUWithJumpsProcess
peekExtOUWithJumpsProcess = peekSimpleType extOUWithJumpsProcessMeta >=> return . ExtOUWithJumpsProcess
withExtOUWithJumpsProcess :: ExtOUWithJumpsProcess -> (Ptr CExtOUWithJumpsProcess -> IO b) -> IO b
withExtOUWithJumpsProcess = withSimpleType . getCExtOUWithJumpsProcess
data CFittedBondDiscountCurve
newtype FittedBondDiscountCurve = FittedBondDiscountCurve {getCFittedBondDiscountCurve :: SimpleType CFittedBondDiscountCurve}
fittedBondDiscountCurveMeta :: Meta CFittedBondDiscountCurve
fittedBondDiscountCurveMeta = Meta qlFreeFittedBondDiscountCurve
peekFittedBondDiscountCurve :: Ptr CFittedBondDiscountCurve -> IO FittedBondDiscountCurve
peekFittedBondDiscountCurve = peekSimpleType fittedBondDiscountCurveMeta >=> return . FittedBondDiscountCurve
withFittedBondDiscountCurve :: FittedBondDiscountCurve -> (Ptr CFittedBondDiscountCurve -> IO b) -> IO b
withFittedBondDiscountCurve = withSimpleType . getCFittedBondDiscountCurve
data CFixedRateBond
newtype FixedRateBond = FixedRateBond {getCFixedRateBond :: SimpleType CFixedRateBond}
fixedRateBondMeta :: Meta CFixedRateBond
fixedRateBondMeta = Meta qlFreeFixedRateBond
peekFixedRateBond :: Ptr CFixedRateBond -> IO FixedRateBond
peekFixedRateBond = peekSimpleType fixedRateBondMeta >=> return . FixedRateBond
withFixedRateBond :: FixedRateBond -> (Ptr CFixedRateBond -> IO b) -> IO b
withFixedRateBond = withSimpleType . getCFixedRateBond
data CFixedRateBondForward
newtype FixedRateBondForward = FixedRateBondForward {getCFixedRateBondForward :: SimpleType CFixedRateBondForward}
fixedRateBondForwardMeta :: Meta CFixedRateBondForward
fixedRateBondForwardMeta = Meta qlFreeFixedRateBondForward
peekFixedRateBondForward :: Ptr CFixedRateBondForward -> IO FixedRateBondForward
peekFixedRateBondForward = peekSimpleType fixedRateBondForwardMeta >=> return . FixedRateBondForward
withFixedRateBondForward :: FixedRateBondForward -> (Ptr CFixedRateBondForward -> IO b) -> IO b
withFixedRateBondForward = withSimpleType . getCFixedRateBondForward
data CForward
newtype Forward = Forward {getCForward :: SimpleType CForward}
forwardMeta :: Meta CForward
forwardMeta = Meta qlFreeForward
peekForward :: Ptr CForward -> IO Forward
peekForward = peekSimpleType forwardMeta >=> return . Forward
withForward :: Forward -> (Ptr CForward -> IO b) -> IO b
withForward = withSimpleType . getCForward
data CForwardRateAgreement
newtype ForwardRateAgreement = ForwardRateAgreement {getCForwardRateAgreement :: SimpleType CForwardRateAgreement}
forwardRateAgreementMeta :: Meta CForwardRateAgreement
forwardRateAgreementMeta = Meta qlFreeForwardRateAgreement
peekForwardRateAgreement :: Ptr CForwardRateAgreement -> IO ForwardRateAgreement
peekForwardRateAgreement = peekSimpleType forwardRateAgreementMeta >=> return . ForwardRateAgreement
withForwardRateAgreement :: ForwardRateAgreement -> (Ptr CForwardRateAgreement -> IO b) -> IO b
withForwardRateAgreement = withSimpleType . getCForwardRateAgreement
data CForwardVanillaOption
newtype ForwardVanillaOption = ForwardVanillaOption {getCForwardVanillaOption :: SimpleType CForwardVanillaOption}
forwardVanillaOptionMeta :: Meta CForwardVanillaOption
forwardVanillaOptionMeta = Meta qlFreeForwardVanillaOption
peekForwardVanillaOption :: Ptr CForwardVanillaOption -> IO ForwardVanillaOption
peekForwardVanillaOption = peekSimpleType forwardVanillaOptionMeta >=> return . ForwardVanillaOption
withForwardVanillaOption :: ForwardVanillaOption -> (Ptr CForwardVanillaOption -> IO b) -> IO b
withForwardVanillaOption = withSimpleType . getCForwardVanillaOption
data CG2
newtype G2 = G2 {getCG2 :: SimpleType CG2}
g2Meta :: Meta CG2
g2Meta = Meta qlFreeG2
peekG2 :: Ptr CG2 -> IO G2
peekG2 = peekSimpleType g2Meta >=> return . G2
withG2 :: G2 -> (Ptr CG2 -> IO b) -> IO b
withG2 = withSimpleType . getCG2
data CGeneralizedBlackScholesProcess
newtype GeneralizedBlackScholesProcess = GeneralizedBlackScholesProcess {getCGeneralizedBlackScholesProcess :: SimpleType CGeneralizedBlackScholesProcess}
generalizedBlackScholesProcessMeta :: Meta CGeneralizedBlackScholesProcess
generalizedBlackScholesProcessMeta = Meta qlFreeGeneralizedBlackScholesProcess
peekGeneralizedBlackScholesProcess :: Ptr CGeneralizedBlackScholesProcess -> IO GeneralizedBlackScholesProcess
peekGeneralizedBlackScholesProcess = peekSimpleType generalizedBlackScholesProcessMeta >=> return . GeneralizedBlackScholesProcess
withGeneralizedBlackScholesProcess :: GeneralizedBlackScholesProcess -> (Ptr CGeneralizedBlackScholesProcess -> IO b) -> IO b
withGeneralizedBlackScholesProcess = withSimpleType . getCGeneralizedBlackScholesProcess
data CGJRGARCHModel
newtype GJRGARCHModel = GJRGARCHModel {getCGJRGARCHModel :: SimpleType CGJRGARCHModel}
gJRGARCHModelMeta :: Meta CGJRGARCHModel
gJRGARCHModelMeta = Meta qlFreeGJRGARCHModel
peekGJRGARCHModel :: Ptr CGJRGARCHModel -> IO GJRGARCHModel
peekGJRGARCHModel = peekSimpleType gJRGARCHModelMeta >=> return . GJRGARCHModel
withGJRGARCHModel :: GJRGARCHModel -> (Ptr CGJRGARCHModel -> IO b) -> IO b
withGJRGARCHModel = withSimpleType . getCGJRGARCHModel
data CGJRGARCHProcess
newtype GJRGARCHProcess = GJRGARCHProcess {getCGJRGARCHProcess :: SimpleType CGJRGARCHProcess}
gJRGARCHProcessMeta :: Meta CGJRGARCHProcess
gJRGARCHProcessMeta = Meta qlFreeGJRGARCHProcess
peekGJRGARCHProcess :: Ptr CGJRGARCHProcess -> IO GJRGARCHProcess
peekGJRGARCHProcess = peekSimpleType gJRGARCHProcessMeta >=> return . GJRGARCHProcess
withGJRGARCHProcess :: GJRGARCHProcess -> (Ptr CGJRGARCHProcess -> IO b) -> IO b
withGJRGARCHProcess = withSimpleType . getCGJRGARCHProcess
data CHestonModel
newtype HestonModel = HestonModel {getCHestonModel :: SimpleType CHestonModel}
hestonModelMeta :: Meta CHestonModel
hestonModelMeta = Meta qlFreeHestonModel
peekHestonModel :: Ptr CHestonModel -> IO HestonModel
peekHestonModel = peekSimpleType hestonModelMeta >=> return . HestonModel
withHestonModel :: HestonModel -> (Ptr CHestonModel -> IO b) -> IO b
withHestonModel = withSimpleType . getCHestonModel
data CHestonProcess
newtype HestonProcess = HestonProcess {getCHestonProcess :: SimpleType CHestonProcess}
hestonProcessMeta :: Meta CHestonProcess
hestonProcessMeta = Meta qlFreeHestonProcess
peekHestonProcess :: Ptr CHestonProcess -> IO HestonProcess
peekHestonProcess = peekSimpleType hestonProcessMeta >=> return . HestonProcess
withHestonProcess :: HestonProcess -> (Ptr CHestonProcess -> IO b) -> IO b
withHestonProcess = withSimpleType . getCHestonProcess
data CHullWhite
newtype HullWhite = HullWhite {getCHullWhite :: SimpleType CHullWhite}
hullWhiteMeta :: Meta CHullWhite
hullWhiteMeta = Meta qlFreeHullWhite
peekHullWhite :: Ptr CHullWhite -> IO HullWhite
peekHullWhite = peekSimpleType hullWhiteMeta >=> return . HullWhite
withHullWhite :: HullWhite -> (Ptr CHullWhite -> IO b) -> IO b
withHullWhite = withSimpleType . getCHullWhite
data CHullWhiteForwardProcess
newtype HullWhiteForwardProcess = HullWhiteForwardProcess {getCHullWhiteForwardProcess :: SimpleType CHullWhiteForwardProcess}
hullWhiteForwardProcessMeta :: Meta CHullWhiteForwardProcess
hullWhiteForwardProcessMeta = Meta qlFreeHullWhiteForwardProcess
peekHullWhiteForwardProcess :: Ptr CHullWhiteForwardProcess -> IO HullWhiteForwardProcess
peekHullWhiteForwardProcess = peekSimpleType hullWhiteForwardProcessMeta >=> return . HullWhiteForwardProcess
withHullWhiteForwardProcess :: HullWhiteForwardProcess -> (Ptr CHullWhiteForwardProcess -> IO b) -> IO b
withHullWhiteForwardProcess = withSimpleType . getCHullWhiteForwardProcess
data CHullWhiteProcess
newtype HullWhiteProcess = HullWhiteProcess {getCHullWhiteProcess :: SimpleType CHullWhiteProcess}
hullWhiteProcessMeta :: Meta CHullWhiteProcess
hullWhiteProcessMeta = Meta qlFreeHullWhiteProcess
peekHullWhiteProcess :: Ptr CHullWhiteProcess -> IO HullWhiteProcess
peekHullWhiteProcess = peekSimpleType hullWhiteProcessMeta >=> return . HullWhiteProcess
withHullWhiteProcess :: HullWhiteProcess -> (Ptr CHullWhiteProcess -> IO b) -> IO b
withHullWhiteProcess = withSimpleType . getCHullWhiteProcess
data CHybridHestonHullWhiteProcess
newtype HybridHestonHullWhiteProcess = HybridHestonHullWhiteProcess {getCHybridHestonHullWhiteProcess :: SimpleType CHybridHestonHullWhiteProcess}
hybridHestonHullWhiteProcessMeta :: Meta CHybridHestonHullWhiteProcess
hybridHestonHullWhiteProcessMeta = Meta qlFreeHybridHestonHullWhiteProcess
peekHybridHestonHullWhiteProcess :: Ptr CHybridHestonHullWhiteProcess -> IO HybridHestonHullWhiteProcess
peekHybridHestonHullWhiteProcess = peekSimpleType hybridHestonHullWhiteProcessMeta >=> return . HybridHestonHullWhiteProcess
withHybridHestonHullWhiteProcess :: HybridHestonHullWhiteProcess -> (Ptr CHybridHestonHullWhiteProcess -> IO b) -> IO b
withHybridHestonHullWhiteProcess = withSimpleType . getCHybridHestonHullWhiteProcess
data COvernightIndex
newtype OvernightIborIndex = OvernightIborIndex {getCOvernightIndex :: SimpleType COvernightIndex}
overnightIborIndexMeta :: Meta COvernightIndex
overnightIborIndexMeta = Meta qlFreeOvernightIborIndex
peekOvernightIborIndex :: Ptr COvernightIndex -> IO OvernightIborIndex
peekOvernightIborIndex = peekSimpleType overnightIborIndexMeta >=> return . OvernightIborIndex
withOvernightIborIndex :: OvernightIborIndex -> (Ptr COvernightIndex -> IO b) -> IO b
withOvernightIborIndex = withSimpleType . getCOvernightIndex
data CIborIndex
newtype IborIndex = IborIndex {getCIborIndex :: SimpleType CIborIndex}
iborIndexMeta :: Meta CIborIndex
iborIndexMeta = Meta qlFreeIborIndex
peekIborIndex :: Ptr CIborIndex -> IO IborIndex
peekIborIndex = peekSimpleType iborIndexMeta >=> return . IborIndex
withIborIndex :: IborIndex -> (Ptr CIborIndex -> IO b) -> IO b
withIborIndex = withSimpleType . getCIborIndex
data CIndex
newtype Index = Index {getCIndex :: SimpleType CIndex}
indexMeta :: Meta CIndex
indexMeta = Meta qlFreeIndex
peekIndex :: Ptr CIndex -> IO Index
peekIndex = peekSimpleType indexMeta >=> return . Index
withIndex :: Index -> (Ptr CIndex -> IO b) -> IO b
withIndex = withSimpleType . getCIndex
data CInstrument
newtype Instrument = Instrument {getCInstrument :: SimpleType CInstrument}
instrumentMeta :: Meta CInstrument
instrumentMeta = Meta qlFreeInstrument
peekInstrument :: Ptr CInstrument -> IO Instrument
peekInstrument = peekSimpleType instrumentMeta >=> return . Instrument
withInstrument :: Instrument -> (Ptr CInstrument -> IO b) -> IO b
withInstrument = withSimpleType . getCInstrument
data CInterestRateIndex
newtype InterestRateIndex = InterestRateIndex {getCInterestRateIndex :: SimpleType CInterestRateIndex}
interestRateIndexMeta :: Meta CInterestRateIndex
interestRateIndexMeta = Meta qlFreeInterestRateIndex
peekInterestRateIndex :: Ptr CInterestRateIndex -> IO InterestRateIndex
peekInterestRateIndex = peekSimpleType interestRateIndexMeta >=> return . InterestRateIndex
withInterestRateIndex :: InterestRateIndex -> (Ptr CInterestRateIndex -> IO b) -> IO b
withInterestRateIndex = withSimpleType . getCInterestRateIndex
data CKlugeExtOUProcess
newtype KlugeExtOUProcess = KlugeExtOUProcess {getCKlugeExtOUProcess :: SimpleType CKlugeExtOUProcess}
klugeExtOUProcessMeta :: Meta CKlugeExtOUProcess
klugeExtOUProcessMeta = Meta qlFreeKlugeExtOUProcess
peekKlugeExtOUProcess :: Ptr CKlugeExtOUProcess -> IO KlugeExtOUProcess
peekKlugeExtOUProcess = peekSimpleType klugeExtOUProcessMeta >=> return . KlugeExtOUProcess
withKlugeExtOUProcess :: KlugeExtOUProcess -> (Ptr CKlugeExtOUProcess -> IO b) -> IO b
withKlugeExtOUProcess = withSimpleType . getCKlugeExtOUProcess
data CLiborForwardModel
newtype LiborForwardModel = LiborForwardModel {getCLiborForwardModel :: SimpleType CLiborForwardModel}
liborForwardModelMeta :: Meta CLiborForwardModel
liborForwardModelMeta = Meta qlFreeLiborForwardModel
peekLiborForwardModel :: Ptr CLiborForwardModel -> IO LiborForwardModel
peekLiborForwardModel = peekSimpleType liborForwardModelMeta >=> return . LiborForwardModel
withLiborForwardModel :: LiborForwardModel -> (Ptr CLiborForwardModel -> IO b) -> IO b
withLiborForwardModel = withSimpleType . getCLiborForwardModel
data CLiborForwardModelProcess
newtype LiborForwardModelProcess = LiborForwardModelProcess {getCLiborForwardModelProcess :: SimpleType CLiborForwardModelProcess}
liborForwardModelProcessMeta :: Meta CLiborForwardModelProcess
liborForwardModelProcessMeta = Meta qlFreeLiborForwardModelProcess
peekLiborForwardModelProcess :: Ptr CLiborForwardModelProcess -> IO LiborForwardModelProcess
peekLiborForwardModelProcess = peekSimpleType liborForwardModelProcessMeta >=> return . LiborForwardModelProcess
withLiborForwardModelProcess :: LiborForwardModelProcess -> (Ptr CLiborForwardModelProcess -> IO b) -> IO b
withLiborForwardModelProcess = withSimpleType . getCLiborForwardModelProcess
data CLocalVolTermStructure
newtype LocalVolTermStructure = LocalVolTermStructure {getCLocalVolTermStructure :: SimpleType CLocalVolTermStructure}
localVolTermStructureMeta :: Meta CLocalVolTermStructure
localVolTermStructureMeta = Meta qlFreeLocalVolTermStructure
peekLocalVolTermStructure :: Ptr CLocalVolTermStructure -> IO LocalVolTermStructure
peekLocalVolTermStructure = peekSimpleType localVolTermStructureMeta >=> return . LocalVolTermStructure
withLocalVolTermStructure :: LocalVolTermStructure -> (Ptr CLocalVolTermStructure -> IO b) -> IO b
withLocalVolTermStructure = withSimpleType . getCLocalVolTermStructure
data CMargrabeOption
newtype MargrabeOption = MargrabeOption {getCMargrabeOption :: SimpleType CMargrabeOption}
margrabeOptionMeta :: Meta CMargrabeOption
margrabeOptionMeta = Meta qlFreeMargrabeOption
peekMargrabeOption :: Ptr CMargrabeOption -> IO MargrabeOption
peekMargrabeOption = peekSimpleType margrabeOptionMeta >=> return . MargrabeOption
withMargrabeOption :: MargrabeOption -> (Ptr CMargrabeOption -> IO b) -> IO b
withMargrabeOption = withSimpleType . getCMargrabeOption
data CMerton76Process
newtype Merton76Process = Merton76Process {getCMerton76Process :: SimpleType CMerton76Process}
merton76ProcessMeta :: Meta CMerton76Process
merton76ProcessMeta = Meta qlFreeMerton76Process
peekMerton76Process :: Ptr CMerton76Process -> IO Merton76Process
peekMerton76Process = peekSimpleType merton76ProcessMeta >=> return . Merton76Process
withMerton76Process :: Merton76Process -> (Ptr CMerton76Process -> IO b) -> IO b
withMerton76Process = withSimpleType . getCMerton76Process
data CMultiAssetOption
newtype MultiAssetOption = MultiAssetOption {getCMultiAssetOption :: SimpleType CMultiAssetOption}
multiAssetOptionMeta :: Meta CMultiAssetOption
multiAssetOptionMeta = Meta qlFreeMultiAssetOption
peekMultiAssetOption :: Ptr CMultiAssetOption -> IO MultiAssetOption
peekMultiAssetOption = peekSimpleType multiAssetOptionMeta >=> return . MultiAssetOption
withMultiAssetOption :: MultiAssetOption -> (Ptr CMultiAssetOption -> IO b) -> IO b
withMultiAssetOption = withSimpleType . getCMultiAssetOption
data COneAssetOption
newtype OneAssetOption = OneAssetOption {getCOneAssetOption :: SimpleType COneAssetOption}
oneAssetOptionMeta :: Meta COneAssetOption
oneAssetOptionMeta = Meta qlFreeOneAssetOption
peekOneAssetOption :: Ptr COneAssetOption -> IO OneAssetOption
peekOneAssetOption = peekSimpleType oneAssetOptionMeta >=> return . OneAssetOption
withOneAssetOption :: OneAssetOption -> (Ptr COneAssetOption -> IO b) -> IO b
withOneAssetOption = withSimpleType . getCOneAssetOption
data COneFactorAffineModel
newtype OneFactorAffineModel = OneFactorAffineModel {getCOneFactorAffineModel :: SimpleType COneFactorAffineModel}
oneFactorAffineModelMeta :: Meta COneFactorAffineModel
oneFactorAffineModelMeta = Meta qlFreeOneFactorAffineModel
peekOneFactorAffineModel :: Ptr COneFactorAffineModel -> IO OneFactorAffineModel
peekOneFactorAffineModel = peekSimpleType oneFactorAffineModelMeta >=> return . OneFactorAffineModel
withOneFactorAffineModel :: OneFactorAffineModel -> (Ptr COneFactorAffineModel -> IO b) -> IO b
withOneFactorAffineModel = withSimpleType . getCOneFactorAffineModel
data COption
newtype Option = Option {getCOption :: SimpleType COption}
optionMeta :: Meta COption
optionMeta = Meta qlFreeOption
peekOption :: Ptr COption -> IO Option
peekOption = peekSimpleType optionMeta >=> return . Option
withOption :: Option -> (Ptr COption -> IO b) -> IO b
withOption = withSimpleType . getCOption
data COptionletVolatilityStructure
newtype OptionletVolatilityStructure = OptionletVolatilityStructure {getCOptionletVolatilityStructure :: SimpleType COptionletVolatilityStructure}
optionletVolatilityStructureMeta :: Meta COptionletVolatilityStructure
optionletVolatilityStructureMeta = Meta qlFreeOptionletVolatilityStructure
peekOptionletVolatilityStructure :: Ptr COptionletVolatilityStructure -> IO OptionletVolatilityStructure
peekOptionletVolatilityStructure = peekSimpleType optionletVolatilityStructureMeta >=> return . OptionletVolatilityStructure
withOptionletVolatilityStructure :: OptionletVolatilityStructure -> (Ptr COptionletVolatilityStructure -> IO b) -> IO b
withOptionletVolatilityStructure = withSimpleType . getCOptionletVolatilityStructure
data COvernightIndexedSwap
newtype OvernightIndexedSwap = OvernightIndexedSwap {getCOvernightIndexedSwap :: SimpleType COvernightIndexedSwap}
overnightIndexedSwapMeta :: Meta COvernightIndexedSwap
overnightIndexedSwapMeta = Meta qlFreeOvernightIndexedSwap
peekOvernightIndexedSwap :: Ptr COvernightIndexedSwap -> IO OvernightIndexedSwap
peekOvernightIndexedSwap = peekSimpleType overnightIndexedSwapMeta >=> return . OvernightIndexedSwap
withOvernightIndexedSwap :: OvernightIndexedSwap -> (Ptr COvernightIndexedSwap -> IO b) -> IO b
withOvernightIndexedSwap = withSimpleType . getCOvernightIndexedSwap
data COvernightIndexedSwapIndex
newtype OvernightIndexedSwapIndex = OvernightIndexedSwapIndex {getCOvernightIndexedSwapIndex :: SimpleType COvernightIndexedSwapIndex}
overnightIndexedSwapIndexMeta :: Meta COvernightIndexedSwapIndex
overnightIndexedSwapIndexMeta = Meta qlFreeOvernightIndexedSwapIndex
peekOvernightIndexedSwapIndex :: Ptr COvernightIndexedSwapIndex -> IO OvernightIndexedSwapIndex
peekOvernightIndexedSwapIndex = peekSimpleType overnightIndexedSwapIndexMeta >=> return . OvernightIndexedSwapIndex
withOvernightIndexedSwapIndex :: OvernightIndexedSwapIndex -> (Ptr COvernightIndexedSwapIndex -> IO b) -> IO b
withOvernightIndexedSwapIndex = withSimpleType . getCOvernightIndexedSwapIndex
data CPiecewiseTimeDependentHestonModel
newtype PiecewiseTimeDependentHestonModel = PiecewiseTimeDependentHestonModel {getCPiecewiseTimeDependentHestonModel :: SimpleType CPiecewiseTimeDependentHestonModel}
piecewiseTimeDependentHestonModelMeta :: Meta CPiecewiseTimeDependentHestonModel
piecewiseTimeDependentHestonModelMeta = Meta qlFreePiecewiseTimeDependentHestonModel
peekPiecewiseTimeDependentHestonModel :: Ptr CPiecewiseTimeDependentHestonModel -> IO PiecewiseTimeDependentHestonModel
peekPiecewiseTimeDependentHestonModel = peekSimpleType piecewiseTimeDependentHestonModelMeta >=> return . PiecewiseTimeDependentHestonModel
withPiecewiseTimeDependentHestonModel :: PiecewiseTimeDependentHestonModel -> (Ptr CPiecewiseTimeDependentHestonModel -> IO b) -> IO b
withPiecewiseTimeDependentHestonModel = withSimpleType . getCPiecewiseTimeDependentHestonModel
data CQuantoBarrierOption
newtype QuantoBarrierOption = QuantoBarrierOption {getCQuantoBarrierOption :: SimpleType CQuantoBarrierOption}
quantoBarrierOptionMeta :: Meta CQuantoBarrierOption
quantoBarrierOptionMeta = Meta qlFreeQuantoBarrierOption
peekQuantoBarrierOption :: Ptr CQuantoBarrierOption -> IO QuantoBarrierOption
peekQuantoBarrierOption = peekSimpleType quantoBarrierOptionMeta >=> return . QuantoBarrierOption
withQuantoBarrierOption :: QuantoBarrierOption -> (Ptr CQuantoBarrierOption -> IO b) -> IO b
withQuantoBarrierOption = withSimpleType . getCQuantoBarrierOption
data CQuantoForwardVanillaOption
newtype QuantoForwardVanillaOption = QuantoForwardVanillaOption {getCQuantoForwardVanillaOption :: SimpleType CQuantoForwardVanillaOption}
quantoForwardVanillaOptionMeta :: Meta CQuantoForwardVanillaOption
quantoForwardVanillaOptionMeta = Meta qlFreeQuantoForwardVanillaOption
peekQuantoForwardVanillaOption :: Ptr CQuantoForwardVanillaOption -> IO QuantoForwardVanillaOption
peekQuantoForwardVanillaOption = peekSimpleType quantoForwardVanillaOptionMeta >=> return . QuantoForwardVanillaOption
withQuantoForwardVanillaOption :: QuantoForwardVanillaOption -> (Ptr CQuantoForwardVanillaOption -> IO b) -> IO b
withQuantoForwardVanillaOption = withSimpleType . getCQuantoForwardVanillaOption
data CQuantoVanillaOption
newtype QuantoVanillaOption = QuantoVanillaOption {getCQuantoVanillaOption :: SimpleType CQuantoVanillaOption}
quantoVanillaOptionMeta :: Meta CQuantoVanillaOption
quantoVanillaOptionMeta = Meta qlFreeQuantoVanillaOption
peekQuantoVanillaOption :: Ptr CQuantoVanillaOption -> IO QuantoVanillaOption
peekQuantoVanillaOption = peekSimpleType quantoVanillaOptionMeta >=> return . QuantoVanillaOption
withQuantoVanillaOption :: QuantoVanillaOption -> (Ptr CQuantoVanillaOption -> IO b) -> IO b
withQuantoVanillaOption = withSimpleType . getCQuantoVanillaOption
data CShortRateModel
newtype ShortRateModel = ShortRateModel {getCShortRateModel :: SimpleType CShortRateModel}
shortRateModelMeta :: Meta CShortRateModel
shortRateModelMeta = Meta qlFreeShortRateModel
peekShortRateModel :: Ptr CShortRateModel -> IO ShortRateModel
peekShortRateModel = peekSimpleType shortRateModelMeta >=> return . ShortRateModel
withShortRateModel :: ShortRateModel -> (Ptr CShortRateModel -> IO b) -> IO b
withShortRateModel = withSimpleType . getCShortRateModel
data CStochasticProcess1D
newtype StochasticProcess1D = StochasticProcess1D {getCStochasticProcess1D :: SimpleType CStochasticProcess1D}
stochasticProcess1DMeta :: Meta CStochasticProcess1D
stochasticProcess1DMeta = Meta qlFreeStochasticProcess1D
peekStochasticProcess1D :: Ptr CStochasticProcess1D -> IO StochasticProcess1D
peekStochasticProcess1D = peekSimpleType stochasticProcess1DMeta >=> return . StochasticProcess1D
withStochasticProcess1D :: StochasticProcess1D -> (Ptr CStochasticProcess1D -> IO b) -> IO b
withStochasticProcess1D = withSimpleType . getCStochasticProcess1D
data CStochasticProcessArray
newtype StochasticProcessArray = StochasticProcessArray {getCStochasticProcessArray :: SimpleType CStochasticProcessArray}
stochasticProcessArrayMeta :: Meta CStochasticProcessArray
stochasticProcessArrayMeta = Meta qlFreeStochasticProcessArray
peekStochasticProcessArray :: Ptr CStochasticProcessArray -> IO StochasticProcessArray
peekStochasticProcessArray = peekSimpleType stochasticProcessArrayMeta >=> return . StochasticProcessArray
withStochasticProcessArray :: StochasticProcessArray -> (Ptr CStochasticProcessArray -> IO b) -> IO b
withStochasticProcessArray = withSimpleType . getCStochasticProcessArray
data CStochasticProcess
newtype StochasticProcess = StochasticProcess {getCStochasticProcess :: SimpleType CStochasticProcess}
stochasticProcessMeta :: Meta CStochasticProcess
stochasticProcessMeta = Meta qlFreeStochasticProcess
peekStochasticProcess :: Ptr CStochasticProcess -> IO StochasticProcess
peekStochasticProcess = peekSimpleType stochasticProcessMeta >=> return . StochasticProcess
withStochasticProcess :: StochasticProcess -> (Ptr CStochasticProcess -> IO b) -> IO b
withStochasticProcess = withSimpleType . getCStochasticProcess
data CSwap
newtype Swap = Swap {getCSwap :: SimpleType CSwap}
swapMeta :: Meta CSwap
swapMeta = Meta qlFreeSwap
peekSwap :: Ptr CSwap -> IO Swap
peekSwap = peekSimpleType swapMeta >=> return . Swap
withSwap :: Swap -> (Ptr CSwap -> IO b) -> IO b
withSwap = withSimpleType . getCSwap
data CSwapIndex
newtype SwapIndex = SwapIndex {getCSwapIndex :: SimpleType CSwapIndex}
swapIndexMeta :: Meta CSwapIndex
swapIndexMeta = Meta qlFreeSwapIndex
peekSwapIndex :: Ptr CSwapIndex -> IO SwapIndex
peekSwapIndex = peekSimpleType swapIndexMeta >=> return . SwapIndex
withSwapIndex :: SwapIndex -> (Ptr CSwapIndex -> IO b) -> IO b
withSwapIndex = withSimpleType . getCSwapIndex
data CSwaption
newtype Swaption = Swaption {getCSwaption :: SimpleType CSwaption}
swaptionMeta :: Meta CSwaption
swaptionMeta = Meta qlFreeSwaption
peekSwaption :: Ptr CSwaption -> IO Swaption
peekSwaption = peekSimpleType swaptionMeta >=> return . Swaption
withSwaption :: Swaption -> (Ptr CSwaption -> IO b) -> IO b
withSwaption = withSimpleType . getCSwaption
data CSwaptionVolatilityStructure
newtype SwaptionVolatilityStructure = SwaptionVolatilityStructure {getCSwaptionVolatilityStructure :: SimpleType CSwaptionVolatilityStructure}
swaptionVolatilityStructureMeta :: Meta CSwaptionVolatilityStructure
swaptionVolatilityStructureMeta = Meta qlFreeSwaptionVolatilityStructure
peekSwaptionVolatilityStructure :: Ptr CSwaptionVolatilityStructure -> IO SwaptionVolatilityStructure
peekSwaptionVolatilityStructure = peekSimpleType swaptionVolatilityStructureMeta >=> return . SwaptionVolatilityStructure
withSwaptionVolatilityStructure :: SwaptionVolatilityStructure -> (Ptr CSwaptionVolatilityStructure -> IO b) -> IO b
withSwaptionVolatilityStructure = withSimpleType . getCSwaptionVolatilityStructure
data CTermStructure
newtype TermStructure = TermStructure {getCTermStructure :: SimpleType CTermStructure}
termStructureMeta :: Meta CTermStructure
termStructureMeta = Meta qlFreeTermStructure
peekTermStructure :: Ptr CTermStructure -> IO TermStructure
peekTermStructure = peekSimpleType termStructureMeta >=> return . TermStructure
withTermStructure :: TermStructure -> (Ptr CTermStructure -> IO b) -> IO b
withTermStructure = withSimpleType . getCTermStructure
data CVanillaOption
newtype VanillaOption = VanillaOption {getCVanillaOption :: SimpleType CVanillaOption}
vanillaOptionMeta :: Meta CVanillaOption
vanillaOptionMeta = Meta qlFreeVanillaOption
peekVanillaOption :: Ptr CVanillaOption -> IO VanillaOption
peekVanillaOption = peekSimpleType vanillaOptionMeta >=> return . VanillaOption
withVanillaOption :: VanillaOption -> (Ptr CVanillaOption -> IO b) -> IO b
withVanillaOption = withSimpleType . getCVanillaOption
data CVanillaSwap
newtype VanillaSwap = VanillaSwap {getCVanillaSwap :: SimpleType CVanillaSwap}
vanillaSwapMeta :: Meta CVanillaSwap
vanillaSwapMeta = Meta qlFreeVanillaSwap
peekVanillaSwap :: Ptr CVanillaSwap -> IO VanillaSwap
peekVanillaSwap = peekSimpleType vanillaSwapMeta >=> return . VanillaSwap
withVanillaSwap :: VanillaSwap -> (Ptr CVanillaSwap -> IO b) -> IO b
withVanillaSwap = withSimpleType . getCVanillaSwap
data CVarianceGammaProcess
newtype VarianceGammaProcess = VarianceGammaProcess {getCVarianceGammaProcess :: SimpleType CVarianceGammaProcess}
varianceGammaProcessMeta :: Meta CVarianceGammaProcess
varianceGammaProcessMeta = Meta qlFreeVarianceGammaProcess
peekVarianceGammaProcess :: Ptr CVarianceGammaProcess -> IO VarianceGammaProcess
peekVarianceGammaProcess = peekSimpleType varianceGammaProcessMeta >=> return . VarianceGammaProcess
withVarianceGammaProcess :: VarianceGammaProcess -> (Ptr CVarianceGammaProcess -> IO b) -> IO b
withVarianceGammaProcess = withSimpleType . getCVarianceGammaProcess
data CVolatilityTermStructure
newtype VolatilityTermStructure = VolatilityTermStructure {getCVolatilityTermStructure :: SimpleType CVolatilityTermStructure}
volatilityTermStructureMeta :: Meta CVolatilityTermStructure
volatilityTermStructureMeta = Meta qlFreeVolatilityTermStructure
peekVolatilityTermStructure :: Ptr CVolatilityTermStructure -> IO VolatilityTermStructure
peekVolatilityTermStructure = peekSimpleType volatilityTermStructureMeta >=> return . VolatilityTermStructure
withVolatilityTermStructure :: VolatilityTermStructure -> (Ptr CVolatilityTermStructure -> IO b) -> IO b
withVolatilityTermStructure = withSimpleType . getCVolatilityTermStructure
data CYieldTermStructure
newtype YieldTermStructure = YieldTermStructure {getCYieldTermStructure :: SimpleType CYieldTermStructure}
yieldTermStructureMeta :: Meta CYieldTermStructure
yieldTermStructureMeta = Meta qlFreeYieldTermStructure
peekYieldTermStructure :: Ptr CYieldTermStructure -> IO YieldTermStructure
peekYieldTermStructure = peekSimpleType yieldTermStructureMeta >=> return . YieldTermStructure
withYieldTermStructure :: YieldTermStructure -> (Ptr CYieldTermStructure -> IO b) -> IO b
withYieldTermStructure = withSimpleType . getCYieldTermStructure

foreign import ccall "ql.h &qlFreeAffineModel" qlFreeAffineModel :: FinalizerPtr CAffineModel
foreign import ccall "ql.h &qlFreeAssetSwap" qlFreeAssetSwap :: FinalizerPtr CAssetSwap
foreign import ccall "ql.h &qlFreeBarrierOption" qlFreeBarrierOption :: FinalizerPtr CBarrierOption
foreign import ccall "ql.h &qlFreeBatesDetJumpModel" qlFreeBatesDetJumpModel :: FinalizerPtr CBatesDetJumpModel
foreign import ccall "ql.h &qlFreeBatesDoubleExpDetJumpModel" qlFreeBatesDoubleExpDetJumpModel :: FinalizerPtr CBatesDoubleExpDetJumpModel
foreign import ccall "ql.h &qlFreeBatesDoubleExpModel" qlFreeBatesDoubleExpModel :: FinalizerPtr CBatesDoubleExpModel
foreign import ccall "ql.h &qlFreeBatesModel" qlFreeBatesModel :: FinalizerPtr CBatesModel
foreign import ccall "ql.h &qlFreeBatesProcess" qlFreeBatesProcess :: FinalizerPtr CBatesProcess
foreign import ccall "ql.h &qlFreeBlackProcess" qlFreeBlackProcess :: FinalizerPtr CBlackProcess
foreign import ccall "ql.h &qlFreeBlackVarianceCurve" qlFreeBlackVarianceCurve :: FinalizerPtr CBlackVarianceCurve
foreign import ccall "ql.h &qlFreeBlackVolTermStructure" qlFreeBlackVolTermStructure :: FinalizerPtr CBlackVolTermStructure
foreign import ccall "ql.h &qlFreeBMAIndex" qlFreeBMAIndex :: FinalizerPtr CBMAIndex
foreign import ccall "ql.h &qlFreeBMASwap" qlFreeBMASwap :: FinalizerPtr CBMASwap
foreign import ccall "ql.h &qlFreeBond" qlFreeBond :: FinalizerPtr CBond
foreign import ccall "ql.h &qlFreeCalibratedModel" qlFreeCalibratedModel :: FinalizerPtr CCalibratedModel
foreign import ccall "ql.h &qlFreeCallableBond" qlFreeCallableBond :: FinalizerPtr CCallableBond
foreign import ccall "ql.h &qlFreeCallableBondVolatilityStructure" qlFreeCallableBondVolatilityStructure :: FinalizerPtr CCallableBondVolatilityStructure
foreign import ccall "ql.h &qlFreeCapFloor" qlFreeCapFloor :: FinalizerPtr CCapFloor
foreign import ccall "ql.h &qlFreeCapFloorTermVolSurface" qlFreeCapFloorTermVolSurface :: FinalizerPtr CCapFloorTermVolSurface
foreign import ccall "ql.h &qlFreeCdsOption" qlFreeCdsOption :: FinalizerPtr CCdsOption
foreign import ccall "ql.h &qlFreeConvertibleBond" qlFreeConvertibleBond :: FinalizerPtr CConvertibleBond
foreign import ccall "ql.h &qlFreeCreditDefaultSwap" qlFreeCreditDefaultSwap :: FinalizerPtr CCreditDefaultSwap
foreign import ccall "ql.h &qlFreeDefaultProbabilityTermStructure" qlFreeDefaultProbabilityTermStructure :: FinalizerPtr CDefaultProbabilityTermStructure
foreign import ccall "ql.h &qlFreeDividendVanillaOption" qlFreeDividendVanillaOption :: FinalizerPtr CDividendVanillaOption
foreign import ccall "ql.h &qlFreeExtendedOrnsteinUhlenbeckProcess" qlFreeExtendedOrnsteinUhlenbeckProcess :: FinalizerPtr CExtendedOrnsteinUhlenbeckProcess
foreign import ccall "ql.h &qlFreeExtOUWithJumpsProcess" qlFreeExtOUWithJumpsProcess :: FinalizerPtr CExtOUWithJumpsProcess
foreign import ccall "ql.h &qlFreeFittedBondDiscountCurve" qlFreeFittedBondDiscountCurve :: FinalizerPtr CFittedBondDiscountCurve
foreign import ccall "ql.h &qlFreeFixedRateBond" qlFreeFixedRateBond :: FinalizerPtr CFixedRateBond
foreign import ccall "ql.h &qlFreeFixedRateBondForward" qlFreeFixedRateBondForward :: FinalizerPtr CFixedRateBondForward
foreign import ccall "ql.h &qlFreeForward" qlFreeForward :: FinalizerPtr CForward
foreign import ccall "ql.h &qlFreeForwardRateAgreement" qlFreeForwardRateAgreement :: FinalizerPtr CForwardRateAgreement
foreign import ccall "ql.h &qlFreeForwardVanillaOption" qlFreeForwardVanillaOption :: FinalizerPtr CForwardVanillaOption
foreign import ccall "ql.h &qlFreeG2" qlFreeG2 :: FinalizerPtr CG2
foreign import ccall "ql.h &qlFreeGeneralizedBlackScholesProcess" qlFreeGeneralizedBlackScholesProcess :: FinalizerPtr CGeneralizedBlackScholesProcess
foreign import ccall "ql.h &qlFreeGJRGARCHModel" qlFreeGJRGARCHModel :: FinalizerPtr CGJRGARCHModel
foreign import ccall "ql.h &qlFreeGJRGARCHProcess" qlFreeGJRGARCHProcess :: FinalizerPtr CGJRGARCHProcess
foreign import ccall "ql.h &qlFreeHestonModel" qlFreeHestonModel :: FinalizerPtr CHestonModel
foreign import ccall "ql.h &qlFreeHestonProcess" qlFreeHestonProcess :: FinalizerPtr CHestonProcess
foreign import ccall "ql.h &qlFreeHullWhite" qlFreeHullWhite :: FinalizerPtr CHullWhite
foreign import ccall "ql.h &qlFreeHullWhiteForwardProcess" qlFreeHullWhiteForwardProcess :: FinalizerPtr CHullWhiteForwardProcess
foreign import ccall "ql.h &qlFreeHullWhiteProcess" qlFreeHullWhiteProcess :: FinalizerPtr CHullWhiteProcess
foreign import ccall "ql.h &qlFreeHybridHestonHullWhiteProcess" qlFreeHybridHestonHullWhiteProcess :: FinalizerPtr CHybridHestonHullWhiteProcess
foreign import ccall "ql.h &qlFreeIborIndex" qlFreeIborIndex :: FinalizerPtr CIborIndex
foreign import ccall "ql.h &qlFreeOvernightIndex" qlFreeOvernightIborIndex :: FinalizerPtr COvernightIndex
foreign import ccall "ql.h &qlFreeIndex" qlFreeIndex :: FinalizerPtr CIndex
foreign import ccall "ql.h &qlFreeInstrument" qlFreeInstrument :: FinalizerPtr CInstrument
foreign import ccall "ql.h &qlFreeInterestRateIndex" qlFreeInterestRateIndex :: FinalizerPtr CInterestRateIndex
foreign import ccall "ql.h &qlFreeKlugeExtOUProcess" qlFreeKlugeExtOUProcess :: FinalizerPtr CKlugeExtOUProcess
foreign import ccall "ql.h &qlFreeLiborForwardModel" qlFreeLiborForwardModel :: FinalizerPtr CLiborForwardModel
foreign import ccall "ql.h &qlFreeLiborForwardModelProcess" qlFreeLiborForwardModelProcess :: FinalizerPtr CLiborForwardModelProcess
foreign import ccall "ql.h &qlFreeLocalVolTermStructure" qlFreeLocalVolTermStructure :: FinalizerPtr CLocalVolTermStructure
foreign import ccall "ql.h &qlFreeMargrabeOption" qlFreeMargrabeOption :: FinalizerPtr CMargrabeOption
foreign import ccall "ql.h &qlFreeMerton76Process" qlFreeMerton76Process :: FinalizerPtr CMerton76Process
foreign import ccall "ql.h &qlFreeMultiAssetOption" qlFreeMultiAssetOption :: FinalizerPtr CMultiAssetOption
foreign import ccall "ql.h &qlFreeOneAssetOption" qlFreeOneAssetOption :: FinalizerPtr COneAssetOption
foreign import ccall "ql.h &qlFreeOneFactorAffineModel" qlFreeOneFactorAffineModel :: FinalizerPtr COneFactorAffineModel
foreign import ccall "ql.h &qlFreeOption" qlFreeOption :: FinalizerPtr COption
foreign import ccall "ql.h &qlFreeOptionletVolatilityStructure" qlFreeOptionletVolatilityStructure :: FinalizerPtr COptionletVolatilityStructure
foreign import ccall "ql.h &qlFreeOvernightIndexedSwap" qlFreeOvernightIndexedSwap :: FinalizerPtr COvernightIndexedSwap
foreign import ccall "ql.h &qlFreeOvernightIndexedSwapIndex" qlFreeOvernightIndexedSwapIndex :: FinalizerPtr COvernightIndexedSwapIndex
foreign import ccall "ql.h &qlFreePiecewiseTimeDependentHestonModel" qlFreePiecewiseTimeDependentHestonModel :: FinalizerPtr CPiecewiseTimeDependentHestonModel
foreign import ccall "ql.h &qlFreeQuantoBarrierOption" qlFreeQuantoBarrierOption :: FinalizerPtr CQuantoBarrierOption
foreign import ccall "ql.h &qlFreeQuantoForwardVanillaOption" qlFreeQuantoForwardVanillaOption :: FinalizerPtr CQuantoForwardVanillaOption
foreign import ccall "ql.h &qlFreeQuantoVanillaOption" qlFreeQuantoVanillaOption :: FinalizerPtr CQuantoVanillaOption
foreign import ccall "ql.h &qlFreeShortRateModel" qlFreeShortRateModel :: FinalizerPtr CShortRateModel
foreign import ccall "ql.h &qlFreeStochasticProcess1D" qlFreeStochasticProcess1D :: FinalizerPtr CStochasticProcess1D
foreign import ccall "ql.h &qlFreeStochasticProcessArray" qlFreeStochasticProcessArray :: FinalizerPtr CStochasticProcessArray
foreign import ccall "ql.h &qlFreeStochasticProcess" qlFreeStochasticProcess :: FinalizerPtr CStochasticProcess
foreign import ccall "ql.h &qlFreeSwap" qlFreeSwap :: FinalizerPtr CSwap
foreign import ccall "ql.h &qlFreeSwapIndex" qlFreeSwapIndex :: FinalizerPtr CSwapIndex
foreign import ccall "ql.h &qlFreeSwaption" qlFreeSwaption :: FinalizerPtr CSwaption
foreign import ccall "ql.h &qlFreeSwaptionVolatilityStructure" qlFreeSwaptionVolatilityStructure :: FinalizerPtr CSwaptionVolatilityStructure
foreign import ccall "ql.h &qlFreeTermStructure" qlFreeTermStructure :: FinalizerPtr CTermStructure
foreign import ccall "ql.h &qlFreeVanillaOption" qlFreeVanillaOption :: FinalizerPtr CVanillaOption
foreign import ccall "ql.h &qlFreeVanillaSwap" qlFreeVanillaSwap :: FinalizerPtr CVanillaSwap
foreign import ccall "ql.h &qlFreeVarianceGammaProcess" qlFreeVarianceGammaProcess :: FinalizerPtr CVarianceGammaProcess
foreign import ccall "ql.h &qlFreeVolatilityTermStructure" qlFreeVolatilityTermStructure :: FinalizerPtr CVolatilityTermStructure
foreign import ccall "ql.h &qlFreeYieldTermStructure" qlFreeYieldTermStructure :: FinalizerPtr CYieldTermStructure

withInstrumentArray :: [Instrument] -> ((CUInt, Ptr (Ptr CInstrument)) -> IO b) -> IO b
withInstrumentArray = withSimpleArray getCInstrument

withMaybeYieldTermStructure :: Maybe YieldTermStructure -> (Ptr CYieldTermStructure -> IO b) -> IO b
withMaybeYieldTermStructure = withMaybeSimpleType . (getCYieldTermStructure <$>)

withStochasticProcess1DArray :: [StochasticProcess1D] -> ((CUInt, Ptr (Ptr CStochasticProcess1D)) -> IO b) -> IO b
withStochasticProcess1DArray = withSimpleArray getCStochasticProcess1D

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
