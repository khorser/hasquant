{-# LANGUAGE FlexibleInstances, RankNTypes #-}
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

  , withStandalone

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

  , Standalone(..)

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
  , BondForward
  , CBondForward
  , peekBondForward
  , withBondForward
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
  , withIndex
  , Instrument
  , CInstrument
  , peekInstrument
  , withInstrument
  , InterestRateIndex
  , CInterestRateIndex
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

  , asIndex
  , asInterestRateIndex
  , asIborIndex
  , asSwapIndex

  , GenInterestRateIndex
  , GenIndex
  , GenIborIndex
  , GenSwapIndex
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

newtype Standalone a = Standalone {ptr :: ForeignPtr a}
newtype Meta a = Meta {getFinalizer :: FinalizerPtr a}
peekStandalone :: Meta a -> Ptr a -> IO (Standalone a)
peekStandalone (Meta f) = newForeignPtr f >=> return . Standalone
withStandalone :: Standalone a -> (Ptr a -> IO b) -> IO b
withStandalone = withForeignPtr . ptr
withMaybeStandalone :: Maybe (Standalone a) -> (Ptr a -> IO b) -> IO b
withMaybeStandalone x f = maybe (f nullPtr) (`withStandalone` f) x
withStandaloneArray :: (t -> Standalone a) -> [t] -> ((CUInt, Ptr (Ptr a)) -> IO b) -> IO b
withStandaloneArray c x f = withMany withStandalone (map c x) (`withArray` (\px -> f (fromIntegral $ length x, px)))
showStandalone :: (Ptr a -> IO CString) -> Standalone a -> String
showStandalone f x = unsafePerformIO $ withStandalone x (f >=> peekDynString)

data CCalendar
newtype Calendar = Calendar {getCCalendar :: Standalone CCalendar}
foreign import ccall "ql.h &qlFreeCalendar" qlFreeCalendar :: FinalizerPtr CCalendar
calendarMeta :: Meta CCalendar
calendarMeta = Meta qlFreeCalendar
peekCalendar :: Ptr CCalendar -> IO Calendar
peekCalendar = peekStandalone calendarMeta >=> return . Calendar
withCalendar :: Calendar -> (Ptr CCalendar -> IO b) -> IO b
withCalendar = withStandalone . getCCalendar
foreign import ccall safe "ql.h qlCalendarName" qlCalendarName :: Ptr CCalendar -> IO CString
instance Show Calendar where show x = showStandalone qlCalendarName (getCCalendar x)
instance Eq Calendar where x == y = show x == show y

data CCurrency
newtype Currency = Currency {getCCurrency :: Standalone CCurrency}
foreign import ccall "ql.h &qlFreeCurrency" qlFreeCurrency :: FinalizerPtr CCurrency
currencyMeta :: Meta CCurrency
currencyMeta = Meta qlFreeCurrency
peekCurrency :: Ptr CCurrency -> IO Currency
peekCurrency = peekStandalone currencyMeta >=> return . Currency
withCurrency :: Currency -> (Ptr CCurrency -> IO b) -> IO b
withCurrency = withStandalone . getCCurrency
withMaybeCurrency :: Maybe Currency -> (Ptr CCurrency -> IO b) -> IO b
withMaybeCurrency = withMaybeStandalone . (getCCurrency <$>)
foreign import ccall safe "ql.h qlCurrencyName" qlCurrencyName :: Ptr CCurrency -> IO CString
instance Show Currency where show x = showStandalone qlCurrencyName (getCCurrency x)
instance Eq Currency where x == y = show x == show y

data CDayCounter
newtype DayCounter = DayCounter {getCDayCounter :: Standalone CDayCounter}
foreign import ccall "ql.h &qlFreeDayCounter" qlFreeDayCounter :: FinalizerPtr CDayCounter
dayCounterMeta :: Meta CDayCounter
dayCounterMeta = Meta qlFreeDayCounter
peekDayCounter :: Ptr CDayCounter -> IO DayCounter
peekDayCounter = peekStandalone dayCounterMeta >=> return . DayCounter
withDayCounter :: DayCounter -> (Ptr CDayCounter -> IO b) -> IO b
withDayCounter = withStandalone . getCDayCounter
foreign import ccall safe "ql.h qlDayCounterName" qlDayCounterName :: Ptr CDayCounter -> IO CString
instance Show DayCounter where show x = showStandalone qlDayCounterName (getCDayCounter x)
instance Eq DayCounter where x == y = show x == show y

data CSchedule
newtype Schedule = Schedule {getCSchedule :: Standalone CSchedule}
foreign import ccall "ql.h &qlFreeSchedule" qlFreeSchedule :: FinalizerPtr CSchedule
scheduleMeta :: Meta CSchedule
scheduleMeta = Meta qlFreeSchedule
peekSchedule :: Ptr CSchedule -> IO Schedule
peekSchedule = peekStandalone scheduleMeta >=> return . Schedule
withSchedule :: Schedule -> (Ptr CSchedule -> IO b) -> IO b
withSchedule = withStandalone . getCSchedule

data CInterestRate
newtype InterestRate = InterestRate {getCInterestRate :: Standalone CInterestRate}
foreign import ccall "ql.h &qlFreeInterestRate" qlFreeInterestRate :: FinalizerPtr CInterestRate
interestRateMeta :: Meta CInterestRate
interestRateMeta = Meta qlFreeInterestRate
peekInterestRate :: Ptr CInterestRate -> IO InterestRate
peekInterestRate = peekStandalone interestRateMeta >=> return . InterestRate
withInterestRate :: InterestRate -> (Ptr CInterestRate -> IO b) -> IO b
withInterestRate = withStandalone . getCInterestRate
withInterestRateArray :: [InterestRate] -> ((CUInt, Ptr (Ptr CInterestRate)) -> IO b) -> IO b
withInterestRateArray = withStandaloneArray getCInterestRate

data CTimeGrid
newtype TimeGrid = TimeGrid {getCTimeGrid :: Standalone CTimeGrid}
foreign import ccall "ql.h &qlFreeTimeGrid" qlFreeTimeGrid :: FinalizerPtr CTimeGrid
timeGridMeta :: Meta CTimeGrid
timeGridMeta = Meta qlFreeTimeGrid
peekTimeGrid :: Ptr CTimeGrid -> IO TimeGrid
peekTimeGrid = peekStandalone timeGridMeta >=> return . TimeGrid
withTimeGrid :: TimeGrid -> (Ptr CTimeGrid -> IO b) -> IO b
withTimeGrid = withStandalone . getCTimeGrid

data CDividend
newtype Dividend = Dividend {getCDividend :: Standalone CDividend}
foreign import ccall "ql.h &qlFreeDividend" qlFreeDividend :: FinalizerPtr CDividend
dividendMeta :: Meta CDividend
dividendMeta = Meta qlFreeDividend
peekDividend :: Ptr CDividend -> IO Dividend
peekDividend = peekStandalone dividendMeta >=> return . Dividend
withDividend :: Dividend -> (Ptr CDividend -> IO b) -> IO b
withDividend = withStandalone . getCDividend
withDividendArray :: [Dividend] -> ((CUInt, Ptr (Ptr CDividend)) -> IO b) -> IO b
withDividendArray = withStandaloneArray getCDividend

data CSmileSection
newtype SmileSection = SmileSection {getCSmileSection :: Standalone CSmileSection}
foreign import ccall "ql.h &qlFreeSmileSection" qlFreeSmileSection :: FinalizerPtr CSmileSection
smileSectionMeta :: Meta CSmileSection
smileSectionMeta = Meta qlFreeSmileSection
peekSmileSection :: Ptr CSmileSection -> IO SmileSection
peekSmileSection = peekStandalone smileSectionMeta >=> return . SmileSection
withSmileSection :: SmileSection -> (Ptr CSmileSection -> IO b) -> IO b
withSmileSection = withStandalone . getCSmileSection

data CPricingEngine
newtype PricingEngine = PricingEngine {getCPricingEngine :: Standalone CPricingEngine}
foreign import ccall "ql.h &qlFreePricingEngine" qlFreePricingEngine :: FinalizerPtr CPricingEngine
pricingEngineMeta :: Meta CPricingEngine
pricingEngineMeta = Meta qlFreePricingEngine
peekPricingEngine :: Ptr CPricingEngine -> IO PricingEngine
peekPricingEngine = peekStandalone pricingEngineMeta >=> return . PricingEngine
withPricingEngine :: PricingEngine -> (Ptr CPricingEngine -> IO b) -> IO b
withPricingEngine = withStandalone . getCPricingEngine

data CFloatingRateCouponPricer
newtype FloatingRateCouponPricer = FloatingRateCouponPricer {getCFloatingRateCouponPricer :: Standalone CFloatingRateCouponPricer}
foreign import ccall "ql.h &qlFreeFloatingCouponPricer" qlFreeFloatingRateCouponPricer :: FinalizerPtr CFloatingRateCouponPricer
floatingRateCouponPricerMeta :: Meta CFloatingRateCouponPricer
floatingRateCouponPricerMeta = Meta qlFreeFloatingRateCouponPricer
peekFloatingRateCouponPricer :: Ptr CFloatingRateCouponPricer -> IO FloatingRateCouponPricer
peekFloatingRateCouponPricer = peekStandalone floatingRateCouponPricerMeta >=> return . FloatingRateCouponPricer
withFloatingRateCouponPricer :: FloatingRateCouponPricer -> (Ptr CFloatingRateCouponPricer -> IO b) -> IO b
withFloatingRateCouponPricer = withStandalone . getCFloatingRateCouponPricer
withFloatingRateCouponPricerArray :: [FloatingRateCouponPricer] -> ((CUInt, Ptr (Ptr CFloatingRateCouponPricer)) -> IO b) -> IO b
withFloatingRateCouponPricerArray = withStandaloneArray getCFloatingRateCouponPricer

data CDefaultProbabilityHelper
newtype DefaultProbabilityHelper = DefaultProbabilityHelper {getCDefaultProbabilityHelper :: Standalone CDefaultProbabilityHelper}
foreign import ccall "ql.h &qlFreeDefaultProbabilityHelper" qlFreeDefaultProbabilityHelper :: FinalizerPtr CDefaultProbabilityHelper
defaultProbabilityHelperMeta :: Meta CDefaultProbabilityHelper
defaultProbabilityHelperMeta = Meta qlFreeDefaultProbabilityHelper
peekDefaultProbabilityHelper :: Ptr CDefaultProbabilityHelper -> IO DefaultProbabilityHelper
peekDefaultProbabilityHelper = peekStandalone defaultProbabilityHelperMeta >=> return . DefaultProbabilityHelper
withDefaultProbabilityHelper :: DefaultProbabilityHelper -> (Ptr CDefaultProbabilityHelper -> IO b) -> IO b
withDefaultProbabilityHelper = withStandalone . getCDefaultProbabilityHelper
withDefaultProbabilityHelperArray :: [DefaultProbabilityHelper] -> ((CUInt, Ptr (Ptr CDefaultProbabilityHelper)) -> IO b) -> IO b
withDefaultProbabilityHelperArray = withStandaloneArray getCDefaultProbabilityHelper

-- special cases: those types will be represented as enums so no need to wrap them
data CQlClaim
type QlClaim = Standalone CQlClaim
foreign import ccall "ql.h &qlFreeClaim" qlFreeClaim :: FinalizerPtr CQlClaim
claimMeta :: Meta CQlClaim
claimMeta = Meta qlFreeClaim
peekClaim :: Ptr CQlClaim -> IO (Standalone CQlClaim)
peekClaim = peekStandalone claimMeta

data CQlCallability
type QlCallability = Standalone CQlCallability
foreign import ccall "ql.h &qlFreeCallability" qlFreeCallability :: FinalizerPtr CQlCallability
callabilityMeta :: Meta CQlCallability
callabilityMeta = Meta qlFreeCallability
peekCallability :: Ptr CQlCallability -> IO (Standalone CQlCallability)
peekCallability = peekStandalone callabilityMeta

data CConstraint
type QlConstraint = Standalone CConstraint
foreign import ccall "ql.h &qlFreeConstraint" qlFreeConstraint :: FinalizerPtr CConstraint
constraintMeta :: Meta CConstraint
constraintMeta = Meta qlFreeConstraint
peekConstraint :: Ptr CConstraint -> IO (Standalone CConstraint)
peekConstraint = peekStandalone constraintMeta

data CEndCriteria
type QlEndCriteria = Standalone CEndCriteria
foreign import ccall "ql.h &qlFreeEndCriteria" qlFreeEndCriteria :: FinalizerPtr CEndCriteria
endCritetiaMeta :: Meta CEndCriteria
endCritetiaMeta = Meta qlFreeEndCriteria
peekEndCriteria :: Ptr CEndCriteria -> IO (Standalone CEndCriteria)
peekEndCriteria = peekStandalone endCritetiaMeta

data CFdmSchemeDesc
type QlFdmSchemeDesc = Standalone CFdmSchemeDesc
foreign import ccall "ql.h &qlFreeFdmSchemeDesc" qlFreeFdmSchemeDesc :: FinalizerPtr CFdmSchemeDesc
fdmSchemeDescMeta :: Meta CFdmSchemeDesc
fdmSchemeDescMeta = Meta qlFreeFdmSchemeDesc
peekFdmSchemeDesc :: Ptr CFdmSchemeDesc -> IO (Standalone CFdmSchemeDesc)
peekFdmSchemeDesc = peekStandalone fdmSchemeDescMeta

data CFittedBondDiscountCurveFittingMethod
type QlFittedBondDiscountCurveFittingMethod = Standalone CFittedBondDiscountCurveFittingMethod
foreign import ccall "ql.h &qlFreeFittedBondDiscountCurveFittingMethod" qlFreeFittedBondDiscountCurveFittingMethod :: FinalizerPtr CFittedBondDiscountCurveFittingMethod
fittedBondDiscountCurveFittingMethodMeta :: Meta CFittedBondDiscountCurveFittingMethod
fittedBondDiscountCurveFittingMethodMeta = Meta qlFreeFittedBondDiscountCurveFittingMethod
peekFittedBondDiscountCurveFittingMethod :: Ptr CFittedBondDiscountCurveFittingMethod -> IO (Standalone CFittedBondDiscountCurveFittingMethod)
peekFittedBondDiscountCurveFittingMethod = peekStandalone fittedBondDiscountCurveFittingMethodMeta

data COptimizationMethod
type QlOptimizationMethod = Standalone COptimizationMethod
foreign import ccall "ql.h &qlFreeOptimizationMethod" qlFreeOptimizationMethod :: FinalizerPtr COptimizationMethod
optimizationMethodMeta :: Meta COptimizationMethod
optimizationMethodMeta = Meta qlFreeOptimizationMethod
peekOptimizationMethod :: Ptr COptimizationMethod -> IO (Standalone COptimizationMethod)
peekOptimizationMethod = peekStandalone optimizationMethodMeta

data CRounding
type QlRounding = Standalone CRounding
foreign import ccall "ql.h &qlFreeRounding" qlFreeRounding :: FinalizerPtr CRounding
roundingMeta :: Meta CRounding
roundingMeta = Meta qlFreeRounding
peekRounding :: Ptr CRounding -> IO (Standalone CRounding)
peekRounding = peekStandalone roundingMeta

data CLmCorrelationModel
type QlLmCorrelationModel = Standalone CLmCorrelationModel
foreign import ccall "ql.h &qlFreeLmCorrelationModel" qlFreeLmCorrelationModel :: FinalizerPtr CLmCorrelationModel
lmCorrelationModelMeta :: Meta CLmCorrelationModel
lmCorrelationModelMeta = Meta qlFreeLmCorrelationModel
peekLmCorrelationModel :: Ptr CLmCorrelationModel -> IO (Standalone CLmCorrelationModel)
peekLmCorrelationModel = peekStandalone lmCorrelationModelMeta

data CLmVolatilityModel
type QlLmVolatilityModel = Standalone CLmVolatilityModel
foreign import ccall "ql.h &qlFreeLmVolatilityModel" qlFreeLmVolatilityModel :: FinalizerPtr CLmVolatilityModel
lmVolatilityModelMeta :: Meta CLmVolatilityModel
lmVolatilityModelMeta = Meta qlFreeLmVolatilityModel
peekLmVolatilityModel :: Ptr CLmVolatilityModel -> IO (Standalone CLmVolatilityModel)
peekLmVolatilityModel = peekStandalone lmVolatilityModelMeta

---- class hierarchies
data Upcast a b = Upcast {_upcast :: Ptr a -> IO (Ptr b), _fi :: FinalizerPtr b}
-- we can infer upcast just from two types so actually we don't need to drag it around with the cast function
data GenObject b a = GenObject {getObject :: !(ForeignPtr a), _getMeta :: !(Upcast a b)}

asGenObject :: Meta c -> Upcast c c -> GenObject c a -> IO (GenObject c c)
asGenObject m0 m (GenObject p (Upcast k _fi)) = withForeignPtr p (\qq -> GenObject <$> (k qq >>= newForeignPtr (getFinalizer m0)) <*> return m)

-- TODO: OPTIMIZE: call the finalizer without creating a temp foreign ptr
withGenObject :: GenObject c a -> (Ptr c -> IO b) -> IO b
withGenObject (GenObject p (Upcast k fi)) ff =
    withForeignPtr p (\x -> do
      pp <- k x
      if fi /= nullFunPtr then
         do xx <- newForeignPtr fi pp
            withForeignPtr xx ff
      else ff pp)

withSubObject :: GenObject c a -> (Ptr a -> IO b) -> IO b
withSubObject = withForeignPtr . getObject

peekGenObject :: Meta c -> Upcast c c -> Ptr c -> IO (GenObject c c)
peekGenObject m0 m p = GenObject <$> newForeignPtr (getFinalizer m0) p <*> return m

peekSubObject :: Meta a -> Upcast a c -> Ptr a -> IO (GenObject c a)
peekSubObject m0 m p = GenObject <$> newForeignPtr (getFinalizer m0) p <*> return m

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

quoteUpcast :: Upcast CQuote CQuote
quoteUpcast = Upcast return nullFunPtr

simpleQuoteUpcast :: Upcast CSimpleQuote CQuote
simpleQuoteUpcast = Upcast qlSimpleQuoteAsQuote qlFreeQuote

-- Haskell does not allow function arguments like [forall a.GenQuote a]
-- let's at least provide a way to convert all quote classes to the most generic one
asQuote :: GenQuote a -> IO Quote
asQuote (GenQuote q) = GenQuote <$> asGenObject quoteMeta quoteUpcast q

withQuote :: GenQuote a -> (Ptr CQuote -> IO b) -> IO b
withQuote = withGenObject . getQuote

withSimpleQuote :: GenQuote CSimpleQuote -> (Ptr CSimpleQuote-> IO b) -> IO b
withSimpleQuote = withSubObject . getQuote

peekQuote :: Ptr CQuote -> IO (GenQuote CQuote)
peekQuote p = GenQuote <$> peekGenObject quoteMeta quoteUpcast p

peekSimpleQuote :: Ptr CSimpleQuote -> IO (GenQuote CSimpleQuote)
peekSimpleQuote p = GenQuote <$> peekSubObject simpleQuoteMeta simpleQuoteUpcast p

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

legUpcast :: Upcast CLeg CLeg
legUpcast = Upcast return nullFunPtr 

couponLegUpcast :: Upcast CCouponLeg CLeg
couponLegUpcast = Upcast qlCouponLegAsLeg qlFreeLeg

asLeg :: GenLeg a -> IO Leg
asLeg (GenLeg q) = GenLeg <$> asGenObject legMeta legUpcast q

withLeg :: GenLeg a -> (Ptr CLeg -> IO b) -> IO b
withLeg = withGenObject . getLeg

withCouponLeg :: GenLeg CCouponLeg -> (Ptr CCouponLeg-> IO b) -> IO b
withCouponLeg = withSubObject . getLeg

peekLeg :: Ptr CLeg -> IO Leg
peekLeg p = GenLeg <$> peekGenObject legMeta legUpcast p

peekCouponLeg :: Ptr CCouponLeg -> IO (GenLeg CCouponLeg)
peekCouponLeg p = GenLeg <$> peekSubObject couponLegMeta couponLegUpcast p

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

rateHelperUpcast :: Upcast CRateHelper CRateHelper
rateHelperUpcast = Upcast return nullFunPtr

bondHelperUpcast :: Upcast CBondHelper CRateHelper
bondHelperUpcast = Upcast qlBondHelperAsRateHelper qlFreeRateHelper

swapRateHelperUpcast :: Upcast CSwapRateHelper CRateHelper
swapRateHelperUpcast = Upcast qlSwapRateHelperAsRateHelper qlFreeRateHelper

oisRateHelperUpcast :: Upcast COISRateHelper CRateHelper
oisRateHelperUpcast = Upcast qlOISRateHelperAsRateHelper qlFreeRateHelper

asRateHelper :: GenRateHelper a -> IO (GenRateHelper CRateHelper)
asRateHelper (GenRateHelper q) = GenRateHelper <$> asGenObject rateHelperMeta rateHelperUpcast q

withRateHelper :: GenRateHelper a -> (Ptr CRateHelper -> IO b) -> IO b
withRateHelper = withGenObject . getRateHelper

peekRateHelper :: Ptr CRateHelper -> IO (GenRateHelper CRateHelper)
peekRateHelper p = GenRateHelper <$> peekGenObject rateHelperMeta rateHelperUpcast p

withBondHelper :: GenRateHelper CBondHelper -> (Ptr CBondHelper-> IO b) -> IO b
withBondHelper = withSubObject . getRateHelper

peekBondHelper :: Ptr CBondHelper -> IO (GenRateHelper CBondHelper)
peekBondHelper p = GenRateHelper <$> peekSubObject bondHelperMeta bondHelperUpcast p

withSwapRateHelper :: GenRateHelper CSwapRateHelper -> (Ptr CSwapRateHelper-> IO b) -> IO b
withSwapRateHelper = withSubObject . getRateHelper

peekSwapRateHelper :: Ptr CSwapRateHelper -> IO (GenRateHelper CSwapRateHelper)
peekSwapRateHelper p = GenRateHelper <$> peekSubObject swapRateHelperMeta swapRateHelperUpcast p

withOISRateHelper :: GenRateHelper COISRateHelper -> (Ptr COISRateHelper-> IO b) -> IO b
withOISRateHelper = withSubObject . getRateHelper

peekOISRateHelper :: Ptr COISRateHelper -> IO (GenRateHelper COISRateHelper)
peekOISRateHelper p = GenRateHelper <$> peekSubObject oisRateHelperMeta oisRateHelperUpcast p

calibrationHelperMeta :: Meta CCalibrationHelper
calibrationHelperMeta = Meta qlFreeCalibrationHelper

blackCalibrationHelperMeta :: Meta CBlackCalibrationHelper
blackCalibrationHelperMeta = Meta qlFreeBlackCalibrationHelper

calibrationHelperUpcast :: Upcast CCalibrationHelper CCalibrationHelper
calibrationHelperUpcast = Upcast return nullFunPtr

blackCalibrationHelperUpcast :: Upcast CBlackCalibrationHelper CCalibrationHelper
blackCalibrationHelperUpcast = Upcast qlBlackCalibrationHelperAsCalibrationHelper qlFreeCalibrationHelper

asCalibrationHelper :: GenCalibrationHelper a -> IO (GenCalibrationHelper CCalibrationHelper)
asCalibrationHelper (GenCalibrationHelper q) = GenCalibrationHelper <$> asGenObject calibrationHelperMeta calibrationHelperUpcast q

withCalibrationHelper :: GenCalibrationHelper a -> (Ptr CCalibrationHelper -> IO b) -> IO b
withCalibrationHelper = withGenObject . getCalibrationHelper

peekCalibrationHelper :: Ptr CCalibrationHelper -> IO (GenCalibrationHelper CCalibrationHelper)
peekCalibrationHelper p = GenCalibrationHelper <$> peekGenObject calibrationHelperMeta calibrationHelperUpcast p

withBlackCalibrationHelper :: GenCalibrationHelper CBlackCalibrationHelper -> (Ptr CBlackCalibrationHelper-> IO b) -> IO b
withBlackCalibrationHelper = withSubObject . getCalibrationHelper

peekBlackCalibrationHelper :: Ptr CBlackCalibrationHelper -> IO (GenCalibrationHelper CBlackCalibrationHelper)
peekBlackCalibrationHelper p = GenCalibrationHelper <$> peekSubObject blackCalibrationHelperMeta blackCalibrationHelperUpcast p

blackCalculatorMeta :: Meta CBlackCalculator
blackCalculatorMeta = Meta qlFreeBlackCalculator

blackScholesCalculatorMeta :: Meta CBlackScholesCalculator
blackScholesCalculatorMeta = Meta qlFreeBlackScholesCalculator

blackCalculatorUpcast :: Upcast CBlackCalculator CBlackCalculator
blackCalculatorUpcast = Upcast return nullFunPtr

blackScholesCalculatorUpcast :: Upcast CBlackScholesCalculator CBlackCalculator
blackScholesCalculatorUpcast = Upcast qlBlackScholesCalculatorAsBlackCalculator qlFreeBlackCalculator

asBlackCalculator :: GenBlackCalculator a -> IO (GenBlackCalculator CBlackCalculator)
asBlackCalculator (GenBlackCalculator q) = GenBlackCalculator <$> asGenObject blackCalculatorMeta blackCalculatorUpcast q

withBlackCalculator :: GenBlackCalculator a -> (Ptr CBlackCalculator -> IO b) -> IO b
withBlackCalculator = withGenObject . getBlackCalculator

peekBlackCalculator :: Ptr CBlackCalculator -> IO (GenBlackCalculator CBlackCalculator)
peekBlackCalculator p = GenBlackCalculator <$> peekGenObject blackCalculatorMeta blackCalculatorUpcast p

withBlackScholesCalculator :: GenBlackCalculator CBlackScholesCalculator -> (Ptr CBlackScholesCalculator-> IO b) -> IO b
withBlackScholesCalculator = withSubObject . getBlackCalculator

peekBlackScholesCalculator :: Ptr CBlackScholesCalculator -> IO (GenBlackCalculator CBlackScholesCalculator)
peekBlackScholesCalculator p = GenBlackCalculator <$> peekSubObject blackScholesCalculatorMeta blackScholesCalculatorUpcast p

withRateHelperArray :: [GenRateHelper a] -> ((CUInt, Ptr (Ptr CRateHelper)) -> IO b) -> IO b
withRateHelperArray x = withGenArray (map getRateHelper x)

withBondHelperArray :: [BondHelper] -> ((CUInt, Ptr (Ptr CBondHelper)) -> IO b) -> IO b
withBondHelperArray x = withSubArray (map getRateHelper x)

withCalibrationHelperArray :: [GenCalibrationHelper a] -> ((CUInt, Ptr (Ptr CCalibrationHelper)) -> IO b) -> IO b
withCalibrationHelperArray x = withGenArray (map getCalibrationHelper x)

foreign import ccall "ql.h qlInterestRateIndexAsIndex" qlInterestRateIndexAsIndex :: Ptr CInterestRateIndex -> IO (Ptr CIndex)
foreign import ccall "ql.h qlBMAIndexAsInterestRateIndex" qlBMAIndexAsInterestRateIndex :: Ptr CBMAIndex -> IO (Ptr CInterestRateIndex)
foreign import ccall "ql.h qlSwapIndexAsInterestRateIndex" qlSwapIndexAsInterestRateIndex :: Ptr CSwapIndex -> IO (Ptr CInterestRateIndex)
foreign import ccall "ql.h qlOvernightIndexedSwapIndexAsSwapIndex" qlOvernightIndexedSwapIndexAsSwapIndex :: Ptr COvernightIndexedSwapIndex -> IO (Ptr CSwapIndex)
foreign import ccall "ql.h qlIborIndexAsInterestRateIndex" qlIborIndexAsInterestRateIndex :: Ptr CIborIndex -> IO (Ptr CInterestRateIndex)
foreign import ccall "ql.h qlOvernightIndexAsIborIndex" qlOvernightIndexAsIborIndex :: Ptr COvernightIndex -> IO (Ptr CIborIndex)

interestRateIndexUpcast :: Upcast CInterestRateIndex CIndex
interestRateIndexUpcast = Upcast qlInterestRateIndexAsIndex qlFreeIndex

bmaIndexUpcast :: Upcast CBMAIndex CInterestRateIndex
bmaIndexUpcast = Upcast qlBMAIndexAsInterestRateIndex qlFreeInterestRateIndex

iborIndexUpcast :: Upcast CIborIndex CInterestRateIndex
iborIndexUpcast = Upcast qlIborIndexAsInterestRateIndex qlFreeInterestRateIndex

swapIndexUpcast :: Upcast CSwapIndex CInterestRateIndex
swapIndexUpcast = Upcast qlSwapIndexAsInterestRateIndex qlFreeInterestRateIndex

overnightIndexUpcast :: Upcast COvernightIndex CIborIndex
overnightIndexUpcast = Upcast qlOvernightIndexAsIborIndex qlFreeIborIndex

overnightIndexedSwapIndexUpcast :: Upcast COvernightIndexedSwapIndex CSwapIndex
overnightIndexedSwapIndexUpcast = Upcast qlOvernightIndexedSwapIndexAsSwapIndex qlFreeSwapIndex

data GenObject2 a b = GenObject2 !a !(forall r. a -> (Ptr b -> IO r) -> IO r)

newtype GenIndex a = GenIndex (GenObject2 a CIndex)
newtype NestedInterestRateIndex a = NestedInterestRateIndex (GenObject2 a CInterestRateIndex)
newtype NestedIborIndex a = NestedIborIndex (GenObject2 a CIborIndex)
newtype NestedSwapIndex a = NestedSwapIndex (GenObject2 a CSwapIndex)

type GenInterestRateIndex a = GenIndex (NestedInterestRateIndex a)
type GenIborIndex a = GenIndex (NestedInterestRateIndex (NestedIborIndex a))
type GenSwapIndex a = GenIndex (NestedInterestRateIndex (NestedSwapIndex a))

type Index = GenIndex (ForeignPtr CIndex)
type InterestRateIndex = GenIndex (ForeignPtr CInterestRateIndex)
type IborIndex = GenIborIndex (ForeignPtr CIborIndex)
type SwapIndex = GenSwapIndex (ForeignPtr CSwapIndex)
type BMAIndex = GenInterestRateIndex (ForeignPtr CBMAIndex)
type OvernightIborIndex = GenIborIndex (ForeignPtr COvernightIndex)
type OvernightIndexedSwapIndex = GenSwapIndex (ForeignPtr COvernightIndexedSwapIndex)

-- FIXME free casted Ptr after call
-- and then TODO optimization: don't create a temp ForeignPtr, rather call the finalizer directly
withNested :: Upcast a b -> GenObject2 c a -> (Ptr b -> IO r) -> IO r
--withNested (Upcast u fi) (GenObject2 p w) f = w p (\pp -> do
--  cp <- u pp
--  fp <- newForeignPtr fi cp
--  withForeignPtr fp f)
withNested (Upcast u _fi) (GenObject2 p w) f = w p (u >=> f)

withIndex :: GenIndex a -> (Ptr CIndex -> IO b) -> IO b
withIndex (GenIndex (GenObject2 x w)) = w x

withInterestRateIndex :: GenInterestRateIndex a -> (Ptr CInterestRateIndex -> IO b) -> IO b
withInterestRateIndex (GenIndex (GenObject2 (NestedInterestRateIndex (GenObject2 x w)) _)) = w x 

withBMAIndex :: BMAIndex -> (Ptr CBMAIndex -> IO b) -> IO b
withBMAIndex (GenIndex (GenObject2 (NestedInterestRateIndex (GenObject2 x _)) _)) = withForeignPtr x

newNested :: Meta a -> Upcast a b -> Ptr a -> IO (GenObject2 (ForeignPtr a) b)
newNested (Meta f) u x = do
  p <- newForeignPtr f x
  return $ GenObject2 p (withNestedForeign u)
  where 
    withNestedForeign :: Upcast a b -> ForeignPtr a -> (Ptr b -> IO r) -> IO r
    withNestedForeign (Upcast fu _fi) p ff = withForeignPtr p (fu >=> ff)
--    withNestedForeign (Upcast fu fi) p ff = withForeignPtr p (\pp -> do
--      cp <- fu pp
--      fp <- newForeignPtr fi cp
--      withForeignPtr fp ff)

newGenForeign :: Meta a -> Ptr a -> IO (GenObject2 (ForeignPtr a) a)
newGenForeign (Meta f) x = do
  p <- newForeignPtr f x
  return $ GenObject2 p withForeignPtr

peekBMAIndex :: Ptr CBMAIndex -> IO BMAIndex
peekBMAIndex x = do
  np <- newNested bMAIndexMeta bmaIndexUpcast x
  return $ GenIndex $ GenObject2 (NestedInterestRateIndex np) withNestedInterestRateIndex

withNestedInterestRateIndex :: NestedInterestRateIndex a -> (Ptr CIndex -> IO b) -> IO b
withNestedInterestRateIndex (NestedInterestRateIndex o) = withNested interestRateIndexUpcast o

withIborIndex :: GenIborIndex a -> (Ptr CIborIndex -> IO b) -> IO b
withIborIndex (GenIndex (GenObject2 (NestedInterestRateIndex (GenObject2 (NestedIborIndex (GenObject2 x w)) _)) _)) = w x

withSwapIndex :: GenSwapIndex a -> (Ptr CSwapIndex -> IO b) -> IO b
withSwapIndex (GenIndex (GenObject2 (NestedInterestRateIndex (GenObject2 (NestedSwapIndex (GenObject2 x w)) _)) _)) = w x

withOvernightIborIndex :: OvernightIborIndex -> (Ptr COvernightIndex -> IO b) -> IO b
withOvernightIborIndex (GenIndex (GenObject2 (NestedInterestRateIndex (GenObject2 (NestedIborIndex (GenObject2 x _)) _)) _)) = withForeignPtr x

withOvernightIndexedSwapIndex :: OvernightIndexedSwapIndex -> (Ptr COvernightIndexedSwapIndex -> IO b) -> IO b
withOvernightIndexedSwapIndex (GenIndex (GenObject2 (NestedInterestRateIndex (GenObject2 (NestedSwapIndex (GenObject2 x _)) _)) _)) = withForeignPtr x

peekSwapIndex :: Ptr CSwapIndex -> IO SwapIndex
peekSwapIndex x = do
  p <- newForeignPtr qlFreeSwapIndex x
  return $ GenIndex $ GenObject2 (NestedInterestRateIndex $ GenObject2 (NestedSwapIndex $ GenObject2 p withForeignPtr) withNestedSwapIndex) withNestedInterestRateIndex

withNestedSwapIndex :: NestedSwapIndex a -> (Ptr CInterestRateIndex -> IO b) -> IO b
withNestedSwapIndex (NestedSwapIndex o) = withNested swapIndexUpcast o

peekOvernightIndexedSwapIndex :: Ptr COvernightIndexedSwapIndex -> IO OvernightIndexedSwapIndex
peekOvernightIndexedSwapIndex x = do
  np <- newNested overnightIndexedSwapIndexMeta overnightIndexedSwapIndexUpcast x
  return $ GenIndex $ GenObject2 (NestedInterestRateIndex $ GenObject2 (NestedSwapIndex np) withNestedSwapIndex) withNestedInterestRateIndex

peekIborIndex :: Ptr CIborIndex -> IO IborIndex
peekIborIndex x = do
  p <- newForeignPtr qlFreeIborIndex x
  return $ GenIndex $ GenObject2 (NestedInterestRateIndex $ GenObject2 (NestedIborIndex $ GenObject2 p withForeignPtr) withNestedIborIndex) withNestedInterestRateIndex

withNestedIborIndex :: NestedIborIndex a -> (Ptr CInterestRateIndex -> IO b) -> IO b
withNestedIborIndex (NestedIborIndex o) = withNested iborIndexUpcast o

peekOvernightIborIndex :: Ptr COvernightIndex -> IO OvernightIborIndex
peekOvernightIborIndex x = do
  np <- newNested overnightIborIndexMeta overnightIndexUpcast x
  return $ GenIndex $ GenObject2 (NestedInterestRateIndex $ GenObject2 (NestedIborIndex np) withNestedIborIndex) withNestedInterestRateIndex

asIndex :: GenIndex a -> IO Index
asIndex (GenIndex (GenObject2 x w)) = w x (\p -> do
  fp <- newGenForeign indexMeta p
  return $ GenIndex fp)

asInterestRateIndex :: GenInterestRateIndex a -> IO InterestRateIndex
asInterestRateIndex (GenIndex (GenObject2 (NestedInterestRateIndex (GenObject2 x w)) _)) = w x (\p -> do {fp <- newNested interestRateIndexMeta interestRateIndexUpcast p; return $ GenIndex fp})

asIborIndex :: GenIborIndex a -> IO IborIndex
asIborIndex (GenIndex (GenObject2 (NestedInterestRateIndex (GenObject2 (NestedIborIndex (GenObject2 x w)) _)) _)) = w x (\p -> do
  fp <- newGenForeign iborIndexMeta p
  return $ GenIndex $ GenObject2 (NestedInterestRateIndex $ GenObject2 (NestedIborIndex fp) withNestedIborIndex) withNestedInterestRateIndex)

asSwapIndex :: GenSwapIndex a -> IO SwapIndex
asSwapIndex (GenIndex (GenObject2 (NestedInterestRateIndex (GenObject2 (NestedSwapIndex (GenObject2 x w)) _)) _)) = w x (\p -> do
  fp <- newGenForeign swapIndexMeta p
  return $ GenIndex $ GenObject2 (NestedInterestRateIndex $ GenObject2 (NestedSwapIndex fp) withNestedSwapIndex) withNestedInterestRateIndex)

-- TEMPORARY STORAGE BEFORE HIERARCHIES ARE MIGRATED OFF TYPE CLASSES

data CAffineModel
newtype AffineModel = AffineModel {getCAffineModel :: Standalone CAffineModel}
affineModelMeta :: Meta CAffineModel
affineModelMeta = Meta qlFreeAffineModel
peekAffineModel :: Ptr CAffineModel -> IO AffineModel
peekAffineModel = peekStandalone affineModelMeta >=> return . AffineModel
withAffineModel :: AffineModel -> (Ptr CAffineModel -> IO b) -> IO b
withAffineModel = withStandalone . getCAffineModel
data CAssetSwap
newtype AssetSwap = AssetSwap {getCAssetSwap :: Standalone CAssetSwap}
assetSwapMeta :: Meta CAssetSwap
assetSwapMeta = Meta qlFreeAssetSwap
peekAssetSwap :: Ptr CAssetSwap -> IO AssetSwap
peekAssetSwap = peekStandalone assetSwapMeta >=> return . AssetSwap
withAssetSwap :: AssetSwap -> (Ptr CAssetSwap -> IO b) -> IO b
withAssetSwap = withStandalone . getCAssetSwap
data CBarrierOption
newtype BarrierOption = BarrierOption {getCBarrierOption :: Standalone CBarrierOption}
barrierOptionMeta :: Meta CBarrierOption
barrierOptionMeta = Meta qlFreeBarrierOption
peekBarrierOption :: Ptr CBarrierOption -> IO BarrierOption
peekBarrierOption = peekStandalone barrierOptionMeta >=> return . BarrierOption
withBarrierOption :: BarrierOption -> (Ptr CBarrierOption -> IO b) -> IO b
withBarrierOption = withStandalone . getCBarrierOption
data CBatesDetJumpModel
newtype BatesDetJumpModel = BatesDetJumpModel {getCBatesDetJumpModel :: Standalone CBatesDetJumpModel}
batesDetJumpModelMeta :: Meta CBatesDetJumpModel
batesDetJumpModelMeta = Meta qlFreeBatesDetJumpModel
peekBatesDetJumpModel :: Ptr CBatesDetJumpModel -> IO BatesDetJumpModel
peekBatesDetJumpModel = peekStandalone batesDetJumpModelMeta >=> return . BatesDetJumpModel
withBatesDetJumpModel :: BatesDetJumpModel -> (Ptr CBatesDetJumpModel -> IO b) -> IO b
withBatesDetJumpModel = withStandalone . getCBatesDetJumpModel
data CBatesDoubleExpDetJumpModel
newtype BatesDoubleExpDetJumpModel = BatesDoubleExpDetJumpModel {getCBatesDoubleExpDetJumpModel :: Standalone CBatesDoubleExpDetJumpModel}
batesDoubleExpDetJumpModelMeta :: Meta CBatesDoubleExpDetJumpModel
batesDoubleExpDetJumpModelMeta = Meta qlFreeBatesDoubleExpDetJumpModel
peekBatesDoubleExpDetJumpModel :: Ptr CBatesDoubleExpDetJumpModel -> IO BatesDoubleExpDetJumpModel
peekBatesDoubleExpDetJumpModel = peekStandalone batesDoubleExpDetJumpModelMeta >=> return . BatesDoubleExpDetJumpModel
withBatesDoubleExpDetJumpModel :: BatesDoubleExpDetJumpModel -> (Ptr CBatesDoubleExpDetJumpModel -> IO b) -> IO b
withBatesDoubleExpDetJumpModel = withStandalone . getCBatesDoubleExpDetJumpModel
data CBatesDoubleExpModel
newtype BatesDoubleExpModel = BatesDoubleExpModel {getCBatesDoubleExpModel :: Standalone CBatesDoubleExpModel}
batesDoubleExpModelMeta :: Meta CBatesDoubleExpModel
batesDoubleExpModelMeta = Meta qlFreeBatesDoubleExpModel
peekBatesDoubleExpModel :: Ptr CBatesDoubleExpModel -> IO BatesDoubleExpModel
peekBatesDoubleExpModel = peekStandalone batesDoubleExpModelMeta >=> return . BatesDoubleExpModel
withBatesDoubleExpModel :: BatesDoubleExpModel -> (Ptr CBatesDoubleExpModel -> IO b) -> IO b
withBatesDoubleExpModel = withStandalone . getCBatesDoubleExpModel
data CBatesModel
newtype BatesModel = BatesModel {getCBatesModel :: Standalone CBatesModel}
batesModelMeta :: Meta CBatesModel
batesModelMeta = Meta qlFreeBatesModel
peekBatesModel :: Ptr CBatesModel -> IO BatesModel
peekBatesModel = peekStandalone batesModelMeta >=> return . BatesModel
withBatesModel :: BatesModel -> (Ptr CBatesModel -> IO b) -> IO b
withBatesModel = withStandalone . getCBatesModel
data CBatesProcess
newtype BatesProcess = BatesProcess {getCBatesProcess :: Standalone CBatesProcess}
batesProcessMeta :: Meta CBatesProcess
batesProcessMeta = Meta qlFreeBatesProcess
peekBatesProcess :: Ptr CBatesProcess -> IO BatesProcess
peekBatesProcess = peekStandalone batesProcessMeta >=> return . BatesProcess
withBatesProcess :: BatesProcess -> (Ptr CBatesProcess -> IO b) -> IO b
withBatesProcess = withStandalone . getCBatesProcess
data CBlackProcess
newtype BlackProcess = BlackProcess {getCBlackProcess :: Standalone CBlackProcess}
blackProcessMeta :: Meta CBlackProcess
blackProcessMeta = Meta qlFreeBlackProcess
peekBlackProcess :: Ptr CBlackProcess -> IO BlackProcess
peekBlackProcess = peekStandalone blackProcessMeta >=> return . BlackProcess
withBlackProcess :: BlackProcess -> (Ptr CBlackProcess -> IO b) -> IO b
withBlackProcess = withStandalone . getCBlackProcess
data CBlackVarianceCurve
newtype BlackVarianceCurve = BlackVarianceCurve {getCBlackVarianceCurve :: Standalone CBlackVarianceCurve}
blackVarianceCurveMeta :: Meta CBlackVarianceCurve
blackVarianceCurveMeta = Meta qlFreeBlackVarianceCurve
peekBlackVarianceCurve :: Ptr CBlackVarianceCurve -> IO BlackVarianceCurve
peekBlackVarianceCurve = peekStandalone blackVarianceCurveMeta >=> return . BlackVarianceCurve
withBlackVarianceCurve :: BlackVarianceCurve -> (Ptr CBlackVarianceCurve -> IO b) -> IO b
withBlackVarianceCurve = withStandalone . getCBlackVarianceCurve
data CBlackVolTermStructure
newtype BlackVolTermStructure = BlackVolTermStructure {getCBlackVolTermStructure :: Standalone CBlackVolTermStructure}
blackVolTermStructureMeta :: Meta CBlackVolTermStructure
blackVolTermStructureMeta = Meta qlFreeBlackVolTermStructure
peekBlackVolTermStructure :: Ptr CBlackVolTermStructure -> IO BlackVolTermStructure
peekBlackVolTermStructure = peekStandalone blackVolTermStructureMeta >=> return . BlackVolTermStructure
withBlackVolTermStructure :: BlackVolTermStructure -> (Ptr CBlackVolTermStructure -> IO b) -> IO b
withBlackVolTermStructure = withStandalone . getCBlackVolTermStructure
data CBMAIndex
bMAIndexMeta :: Meta CBMAIndex
bMAIndexMeta = Meta qlFreeBMAIndex
data CBMASwap
newtype BMASwap = BMASwap {getCBMASwap :: Standalone CBMASwap}
bMASwapMeta :: Meta CBMASwap
bMASwapMeta = Meta qlFreeBMASwap
peekBMASwap :: Ptr CBMASwap -> IO BMASwap
peekBMASwap = peekStandalone bMASwapMeta >=> return . BMASwap
withBMASwap :: BMASwap -> (Ptr CBMASwap -> IO b) -> IO b
withBMASwap = withStandalone . getCBMASwap
data CBond
newtype Bond = Bond {getCBond :: Standalone CBond}
bondMeta :: Meta CBond
bondMeta = Meta qlFreeBond
peekBond :: Ptr CBond -> IO Bond
peekBond = peekStandalone bondMeta >=> return . Bond
withBond :: Bond -> (Ptr CBond -> IO b) -> IO b
withBond = withStandalone . getCBond
data CCalibratedModel
newtype CalibratedModel = CalibratedModel {getCCalibratedModel :: Standalone CCalibratedModel}
calibratedModelMeta :: Meta CCalibratedModel
calibratedModelMeta = Meta qlFreeCalibratedModel
peekCalibratedModel :: Ptr CCalibratedModel -> IO CalibratedModel
peekCalibratedModel = peekStandalone calibratedModelMeta >=> return . CalibratedModel
withCalibratedModel :: CalibratedModel -> (Ptr CCalibratedModel -> IO b) -> IO b
withCalibratedModel = withStandalone . getCCalibratedModel
data CCallableBond
newtype CallableBond = CallableBond {getCCallableBond :: Standalone CCallableBond}
callableBondMeta :: Meta CCallableBond
callableBondMeta = Meta qlFreeCallableBond
peekCallableBond :: Ptr CCallableBond -> IO CallableBond
peekCallableBond = peekStandalone callableBondMeta >=> return . CallableBond
withCallableBond :: CallableBond -> (Ptr CCallableBond -> IO b) -> IO b
withCallableBond = withStandalone . getCCallableBond
data CCallableBondVolatilityStructure
newtype CallableBondVolatilityStructure = CallableBondVolatilityStructure {getCCallableBondVolatilityStructure :: Standalone CCallableBondVolatilityStructure}
callableBondVolatilityStructureMeta :: Meta CCallableBondVolatilityStructure
callableBondVolatilityStructureMeta = Meta qlFreeCallableBondVolatilityStructure
peekCallableBondVolatilityStructure :: Ptr CCallableBondVolatilityStructure -> IO CallableBondVolatilityStructure
peekCallableBondVolatilityStructure = peekStandalone callableBondVolatilityStructureMeta >=> return . CallableBondVolatilityStructure
withCallableBondVolatilityStructure :: CallableBondVolatilityStructure -> (Ptr CCallableBondVolatilityStructure -> IO b) -> IO b
withCallableBondVolatilityStructure = withStandalone . getCCallableBondVolatilityStructure
data CCapFloor
newtype CapFloor = CapFloor {getCCapFloor :: Standalone CCapFloor}
capFloorMeta :: Meta CCapFloor
capFloorMeta = Meta qlFreeCapFloor
peekCapFloor :: Ptr CCapFloor -> IO CapFloor
peekCapFloor = peekStandalone capFloorMeta >=> return . CapFloor
withCapFloor :: CapFloor -> (Ptr CCapFloor -> IO b) -> IO b
withCapFloor = withStandalone . getCCapFloor
data CCapFloorTermVolSurface
newtype CapFloorTermVolSurface = CapFloorTermVolSurface {getCCapFloorTermVolSurface :: Standalone CCapFloorTermVolSurface}
capFloorTermVolSurfaceMeta :: Meta CCapFloorTermVolSurface
capFloorTermVolSurfaceMeta = Meta qlFreeCapFloorTermVolSurface
peekCapFloorTermVolSurface :: Ptr CCapFloorTermVolSurface -> IO CapFloorTermVolSurface
peekCapFloorTermVolSurface = peekStandalone capFloorTermVolSurfaceMeta >=> return . CapFloorTermVolSurface
withCapFloorTermVolSurface :: CapFloorTermVolSurface -> (Ptr CCapFloorTermVolSurface -> IO b) -> IO b
withCapFloorTermVolSurface = withStandalone . getCCapFloorTermVolSurface
data CCdsOption
newtype CdsOption = CdsOption {getCCdsOption :: Standalone CCdsOption}
cdsOptionMeta :: Meta CCdsOption
cdsOptionMeta = Meta qlFreeCdsOption
peekCdsOption :: Ptr CCdsOption -> IO CdsOption
peekCdsOption = peekStandalone cdsOptionMeta >=> return . CdsOption
withCdsOption :: CdsOption -> (Ptr CCdsOption -> IO b) -> IO b
withCdsOption = withStandalone . getCCdsOption
data CConvertibleBond
newtype ConvertibleBond = ConvertibleBond {getCConvertibleBond :: Standalone CConvertibleBond}
convertibleBondMeta :: Meta CConvertibleBond
convertibleBondMeta = Meta qlFreeConvertibleBond
peekConvertibleBond :: Ptr CConvertibleBond -> IO ConvertibleBond
peekConvertibleBond = peekStandalone convertibleBondMeta >=> return . ConvertibleBond
withConvertibleBond :: ConvertibleBond -> (Ptr CConvertibleBond -> IO b) -> IO b
withConvertibleBond = withStandalone . getCConvertibleBond
data CCreditDefaultSwap
newtype CreditDefaultSwap = CreditDefaultSwap {getCCreditDefaultSwap :: Standalone CCreditDefaultSwap}
creditDefaultSwapMeta :: Meta CCreditDefaultSwap
creditDefaultSwapMeta = Meta qlFreeCreditDefaultSwap
peekCreditDefaultSwap :: Ptr CCreditDefaultSwap -> IO CreditDefaultSwap
peekCreditDefaultSwap = peekStandalone creditDefaultSwapMeta >=> return . CreditDefaultSwap
withCreditDefaultSwap :: CreditDefaultSwap -> (Ptr CCreditDefaultSwap -> IO b) -> IO b
withCreditDefaultSwap = withStandalone . getCCreditDefaultSwap
data CDefaultProbabilityTermStructure
newtype DefaultProbabilityTermStructure = DefaultProbabilityTermStructure {getCDefaultProbabilityTermStructure :: Standalone CDefaultProbabilityTermStructure}
defaultProbabilityTermStructureMeta :: Meta CDefaultProbabilityTermStructure
defaultProbabilityTermStructureMeta = Meta qlFreeDefaultProbabilityTermStructure
peekDefaultProbabilityTermStructure :: Ptr CDefaultProbabilityTermStructure -> IO DefaultProbabilityTermStructure
peekDefaultProbabilityTermStructure = peekStandalone defaultProbabilityTermStructureMeta >=> return . DefaultProbabilityTermStructure
withDefaultProbabilityTermStructure :: DefaultProbabilityTermStructure -> (Ptr CDefaultProbabilityTermStructure -> IO b) -> IO b
withDefaultProbabilityTermStructure = withStandalone . getCDefaultProbabilityTermStructure
data CDividendVanillaOption
newtype DividendVanillaOption = DividendVanillaOption {getCDividendVanillaOption :: Standalone CDividendVanillaOption}
dividendVanillaOptionMeta :: Meta CDividendVanillaOption
dividendVanillaOptionMeta = Meta qlFreeDividendVanillaOption
peekDividendVanillaOption :: Ptr CDividendVanillaOption -> IO DividendVanillaOption
peekDividendVanillaOption = peekStandalone dividendVanillaOptionMeta >=> return . DividendVanillaOption
withDividendVanillaOption :: DividendVanillaOption -> (Ptr CDividendVanillaOption -> IO b) -> IO b
withDividendVanillaOption = withStandalone . getCDividendVanillaOption
data CExtendedOrnsteinUhlenbeckProcess
newtype ExtendedOrnsteinUhlenbeckProcess = ExtendedOrnsteinUhlenbeckProcess {getCExtendedOrnsteinUhlenbeckProcess :: Standalone CExtendedOrnsteinUhlenbeckProcess}
extendedOrnsteinUhlenbeckProcessMeta :: Meta CExtendedOrnsteinUhlenbeckProcess
extendedOrnsteinUhlenbeckProcessMeta = Meta qlFreeExtendedOrnsteinUhlenbeckProcess
peekExtendedOrnsteinUhlenbeckProcess :: Ptr CExtendedOrnsteinUhlenbeckProcess -> IO ExtendedOrnsteinUhlenbeckProcess
peekExtendedOrnsteinUhlenbeckProcess = peekStandalone extendedOrnsteinUhlenbeckProcessMeta >=> return . ExtendedOrnsteinUhlenbeckProcess
withExtendedOrnsteinUhlenbeckProcess :: ExtendedOrnsteinUhlenbeckProcess -> (Ptr CExtendedOrnsteinUhlenbeckProcess -> IO b) -> IO b
withExtendedOrnsteinUhlenbeckProcess = withStandalone . getCExtendedOrnsteinUhlenbeckProcess
data CExtOUWithJumpsProcess
newtype ExtOUWithJumpsProcess = ExtOUWithJumpsProcess {getCExtOUWithJumpsProcess :: Standalone CExtOUWithJumpsProcess}
extOUWithJumpsProcessMeta :: Meta CExtOUWithJumpsProcess
extOUWithJumpsProcessMeta = Meta qlFreeExtOUWithJumpsProcess
peekExtOUWithJumpsProcess :: Ptr CExtOUWithJumpsProcess -> IO ExtOUWithJumpsProcess
peekExtOUWithJumpsProcess = peekStandalone extOUWithJumpsProcessMeta >=> return . ExtOUWithJumpsProcess
withExtOUWithJumpsProcess :: ExtOUWithJumpsProcess -> (Ptr CExtOUWithJumpsProcess -> IO b) -> IO b
withExtOUWithJumpsProcess = withStandalone . getCExtOUWithJumpsProcess
data CFittedBondDiscountCurve
newtype FittedBondDiscountCurve = FittedBondDiscountCurve {getCFittedBondDiscountCurve :: Standalone CFittedBondDiscountCurve}
fittedBondDiscountCurveMeta :: Meta CFittedBondDiscountCurve
fittedBondDiscountCurveMeta = Meta qlFreeFittedBondDiscountCurve
peekFittedBondDiscountCurve :: Ptr CFittedBondDiscountCurve -> IO FittedBondDiscountCurve
peekFittedBondDiscountCurve = peekStandalone fittedBondDiscountCurveMeta >=> return . FittedBondDiscountCurve
withFittedBondDiscountCurve :: FittedBondDiscountCurve -> (Ptr CFittedBondDiscountCurve -> IO b) -> IO b
withFittedBondDiscountCurve = withStandalone . getCFittedBondDiscountCurve
data CFixedRateBond
newtype FixedRateBond = FixedRateBond {getCFixedRateBond :: Standalone CFixedRateBond}
fixedRateBondMeta :: Meta CFixedRateBond
fixedRateBondMeta = Meta qlFreeFixedRateBond
peekFixedRateBond :: Ptr CFixedRateBond -> IO FixedRateBond
peekFixedRateBond = peekStandalone fixedRateBondMeta >=> return . FixedRateBond
withFixedRateBond :: FixedRateBond -> (Ptr CFixedRateBond -> IO b) -> IO b
withFixedRateBond = withStandalone . getCFixedRateBond
data CBondForward
newtype BondForward = BondForward {getCBondForward :: Standalone CBondForward}
bondForwardMeta :: Meta CBondForward
bondForwardMeta = Meta qlFreeBondForward
peekBondForward :: Ptr CBondForward -> IO BondForward
peekBondForward = peekStandalone bondForwardMeta >=> return . BondForward
withBondForward :: BondForward -> (Ptr CBondForward -> IO b) -> IO b
withBondForward = withStandalone . getCBondForward
data CForward
newtype Forward = Forward {getCForward :: Standalone CForward}
forwardMeta :: Meta CForward
forwardMeta = Meta qlFreeForward
peekForward :: Ptr CForward -> IO Forward
peekForward = peekStandalone forwardMeta >=> return . Forward
withForward :: Forward -> (Ptr CForward -> IO b) -> IO b
withForward = withStandalone . getCForward
data CForwardRateAgreement
newtype ForwardRateAgreement = ForwardRateAgreement {getCForwardRateAgreement :: Standalone CForwardRateAgreement}
forwardRateAgreementMeta :: Meta CForwardRateAgreement
forwardRateAgreementMeta = Meta qlFreeForwardRateAgreement
peekForwardRateAgreement :: Ptr CForwardRateAgreement -> IO ForwardRateAgreement
peekForwardRateAgreement = peekStandalone forwardRateAgreementMeta >=> return . ForwardRateAgreement
withForwardRateAgreement :: ForwardRateAgreement -> (Ptr CForwardRateAgreement -> IO b) -> IO b
withForwardRateAgreement = withStandalone . getCForwardRateAgreement
data CForwardVanillaOption
newtype ForwardVanillaOption = ForwardVanillaOption {getCForwardVanillaOption :: Standalone CForwardVanillaOption}
forwardVanillaOptionMeta :: Meta CForwardVanillaOption
forwardVanillaOptionMeta = Meta qlFreeForwardVanillaOption
peekForwardVanillaOption :: Ptr CForwardVanillaOption -> IO ForwardVanillaOption
peekForwardVanillaOption = peekStandalone forwardVanillaOptionMeta >=> return . ForwardVanillaOption
withForwardVanillaOption :: ForwardVanillaOption -> (Ptr CForwardVanillaOption -> IO b) -> IO b
withForwardVanillaOption = withStandalone . getCForwardVanillaOption
data CG2
newtype G2 = G2 {getCG2 :: Standalone CG2}
g2Meta :: Meta CG2
g2Meta = Meta qlFreeG2
peekG2 :: Ptr CG2 -> IO G2
peekG2 = peekStandalone g2Meta >=> return . G2
withG2 :: G2 -> (Ptr CG2 -> IO b) -> IO b
withG2 = withStandalone . getCG2
data CGeneralizedBlackScholesProcess
newtype GeneralizedBlackScholesProcess = GeneralizedBlackScholesProcess {getCGeneralizedBlackScholesProcess :: Standalone CGeneralizedBlackScholesProcess}
generalizedBlackScholesProcessMeta :: Meta CGeneralizedBlackScholesProcess
generalizedBlackScholesProcessMeta = Meta qlFreeGeneralizedBlackScholesProcess
peekGeneralizedBlackScholesProcess :: Ptr CGeneralizedBlackScholesProcess -> IO GeneralizedBlackScholesProcess
peekGeneralizedBlackScholesProcess = peekStandalone generalizedBlackScholesProcessMeta >=> return . GeneralizedBlackScholesProcess
withGeneralizedBlackScholesProcess :: GeneralizedBlackScholesProcess -> (Ptr CGeneralizedBlackScholesProcess -> IO b) -> IO b
withGeneralizedBlackScholesProcess = withStandalone . getCGeneralizedBlackScholesProcess
data CGJRGARCHModel
newtype GJRGARCHModel = GJRGARCHModel {getCGJRGARCHModel :: Standalone CGJRGARCHModel}
gJRGARCHModelMeta :: Meta CGJRGARCHModel
gJRGARCHModelMeta = Meta qlFreeGJRGARCHModel
peekGJRGARCHModel :: Ptr CGJRGARCHModel -> IO GJRGARCHModel
peekGJRGARCHModel = peekStandalone gJRGARCHModelMeta >=> return . GJRGARCHModel
withGJRGARCHModel :: GJRGARCHModel -> (Ptr CGJRGARCHModel -> IO b) -> IO b
withGJRGARCHModel = withStandalone . getCGJRGARCHModel
data CGJRGARCHProcess
newtype GJRGARCHProcess = GJRGARCHProcess {getCGJRGARCHProcess :: Standalone CGJRGARCHProcess}
gJRGARCHProcessMeta :: Meta CGJRGARCHProcess
gJRGARCHProcessMeta = Meta qlFreeGJRGARCHProcess
peekGJRGARCHProcess :: Ptr CGJRGARCHProcess -> IO GJRGARCHProcess
peekGJRGARCHProcess = peekStandalone gJRGARCHProcessMeta >=> return . GJRGARCHProcess
withGJRGARCHProcess :: GJRGARCHProcess -> (Ptr CGJRGARCHProcess -> IO b) -> IO b
withGJRGARCHProcess = withStandalone . getCGJRGARCHProcess
data CHestonModel
newtype HestonModel = HestonModel {getCHestonModel :: Standalone CHestonModel}
hestonModelMeta :: Meta CHestonModel
hestonModelMeta = Meta qlFreeHestonModel
peekHestonModel :: Ptr CHestonModel -> IO HestonModel
peekHestonModel = peekStandalone hestonModelMeta >=> return . HestonModel
withHestonModel :: HestonModel -> (Ptr CHestonModel -> IO b) -> IO b
withHestonModel = withStandalone . getCHestonModel
data CHestonProcess
newtype HestonProcess = HestonProcess {getCHestonProcess :: Standalone CHestonProcess}
hestonProcessMeta :: Meta CHestonProcess
hestonProcessMeta = Meta qlFreeHestonProcess
peekHestonProcess :: Ptr CHestonProcess -> IO HestonProcess
peekHestonProcess = peekStandalone hestonProcessMeta >=> return . HestonProcess
withHestonProcess :: HestonProcess -> (Ptr CHestonProcess -> IO b) -> IO b
withHestonProcess = withStandalone . getCHestonProcess
data CHullWhite
newtype HullWhite = HullWhite {getCHullWhite :: Standalone CHullWhite}
hullWhiteMeta :: Meta CHullWhite
hullWhiteMeta = Meta qlFreeHullWhite
peekHullWhite :: Ptr CHullWhite -> IO HullWhite
peekHullWhite = peekStandalone hullWhiteMeta >=> return . HullWhite
withHullWhite :: HullWhite -> (Ptr CHullWhite -> IO b) -> IO b
withHullWhite = withStandalone . getCHullWhite
data CHullWhiteForwardProcess
newtype HullWhiteForwardProcess = HullWhiteForwardProcess {getCHullWhiteForwardProcess :: Standalone CHullWhiteForwardProcess}
hullWhiteForwardProcessMeta :: Meta CHullWhiteForwardProcess
hullWhiteForwardProcessMeta = Meta qlFreeHullWhiteForwardProcess
peekHullWhiteForwardProcess :: Ptr CHullWhiteForwardProcess -> IO HullWhiteForwardProcess
peekHullWhiteForwardProcess = peekStandalone hullWhiteForwardProcessMeta >=> return . HullWhiteForwardProcess
withHullWhiteForwardProcess :: HullWhiteForwardProcess -> (Ptr CHullWhiteForwardProcess -> IO b) -> IO b
withHullWhiteForwardProcess = withStandalone . getCHullWhiteForwardProcess
data CHullWhiteProcess
newtype HullWhiteProcess = HullWhiteProcess {getCHullWhiteProcess :: Standalone CHullWhiteProcess}
hullWhiteProcessMeta :: Meta CHullWhiteProcess
hullWhiteProcessMeta = Meta qlFreeHullWhiteProcess
peekHullWhiteProcess :: Ptr CHullWhiteProcess -> IO HullWhiteProcess
peekHullWhiteProcess = peekStandalone hullWhiteProcessMeta >=> return . HullWhiteProcess
withHullWhiteProcess :: HullWhiteProcess -> (Ptr CHullWhiteProcess -> IO b) -> IO b
withHullWhiteProcess = withStandalone . getCHullWhiteProcess
data CHybridHestonHullWhiteProcess
newtype HybridHestonHullWhiteProcess = HybridHestonHullWhiteProcess {getCHybridHestonHullWhiteProcess :: Standalone CHybridHestonHullWhiteProcess}
hybridHestonHullWhiteProcessMeta :: Meta CHybridHestonHullWhiteProcess
hybridHestonHullWhiteProcessMeta = Meta qlFreeHybridHestonHullWhiteProcess
peekHybridHestonHullWhiteProcess :: Ptr CHybridHestonHullWhiteProcess -> IO HybridHestonHullWhiteProcess
peekHybridHestonHullWhiteProcess = peekStandalone hybridHestonHullWhiteProcessMeta >=> return . HybridHestonHullWhiteProcess
withHybridHestonHullWhiteProcess :: HybridHestonHullWhiteProcess -> (Ptr CHybridHestonHullWhiteProcess -> IO b) -> IO b
withHybridHestonHullWhiteProcess = withStandalone . getCHybridHestonHullWhiteProcess
data COvernightIndex
overnightIborIndexMeta :: Meta COvernightIndex
overnightIborIndexMeta = Meta qlFreeOvernightIborIndex
data CIborIndex
iborIndexMeta :: Meta CIborIndex
iborIndexMeta = Meta qlFreeIborIndex
data CIndex
indexMeta :: Meta CIndex
indexMeta = Meta qlFreeIndex
data CInstrument
newtype Instrument = Instrument {getCInstrument :: Standalone CInstrument}
instrumentMeta :: Meta CInstrument
instrumentMeta = Meta qlFreeInstrument
peekInstrument :: Ptr CInstrument -> IO Instrument
peekInstrument = peekStandalone instrumentMeta >=> return . Instrument
withInstrument :: Instrument -> (Ptr CInstrument -> IO b) -> IO b
withInstrument = withStandalone . getCInstrument
data CInterestRateIndex
interestRateIndexMeta :: Meta CInterestRateIndex
interestRateIndexMeta = Meta qlFreeInterestRateIndex
data CKlugeExtOUProcess
newtype KlugeExtOUProcess = KlugeExtOUProcess {getCKlugeExtOUProcess :: Standalone CKlugeExtOUProcess}
klugeExtOUProcessMeta :: Meta CKlugeExtOUProcess
klugeExtOUProcessMeta = Meta qlFreeKlugeExtOUProcess
peekKlugeExtOUProcess :: Ptr CKlugeExtOUProcess -> IO KlugeExtOUProcess
peekKlugeExtOUProcess = peekStandalone klugeExtOUProcessMeta >=> return . KlugeExtOUProcess
withKlugeExtOUProcess :: KlugeExtOUProcess -> (Ptr CKlugeExtOUProcess -> IO b) -> IO b
withKlugeExtOUProcess = withStandalone . getCKlugeExtOUProcess
data CLiborForwardModel
newtype LiborForwardModel = LiborForwardModel {getCLiborForwardModel :: Standalone CLiborForwardModel}
liborForwardModelMeta :: Meta CLiborForwardModel
liborForwardModelMeta = Meta qlFreeLiborForwardModel
peekLiborForwardModel :: Ptr CLiborForwardModel -> IO LiborForwardModel
peekLiborForwardModel = peekStandalone liborForwardModelMeta >=> return . LiborForwardModel
withLiborForwardModel :: LiborForwardModel -> (Ptr CLiborForwardModel -> IO b) -> IO b
withLiborForwardModel = withStandalone . getCLiborForwardModel
data CLiborForwardModelProcess
newtype LiborForwardModelProcess = LiborForwardModelProcess {getCLiborForwardModelProcess :: Standalone CLiborForwardModelProcess}
liborForwardModelProcessMeta :: Meta CLiborForwardModelProcess
liborForwardModelProcessMeta = Meta qlFreeLiborForwardModelProcess
peekLiborForwardModelProcess :: Ptr CLiborForwardModelProcess -> IO LiborForwardModelProcess
peekLiborForwardModelProcess = peekStandalone liborForwardModelProcessMeta >=> return . LiborForwardModelProcess
withLiborForwardModelProcess :: LiborForwardModelProcess -> (Ptr CLiborForwardModelProcess -> IO b) -> IO b
withLiborForwardModelProcess = withStandalone . getCLiborForwardModelProcess
data CLocalVolTermStructure
newtype LocalVolTermStructure = LocalVolTermStructure {getCLocalVolTermStructure :: Standalone CLocalVolTermStructure}
localVolTermStructureMeta :: Meta CLocalVolTermStructure
localVolTermStructureMeta = Meta qlFreeLocalVolTermStructure
peekLocalVolTermStructure :: Ptr CLocalVolTermStructure -> IO LocalVolTermStructure
peekLocalVolTermStructure = peekStandalone localVolTermStructureMeta >=> return . LocalVolTermStructure
withLocalVolTermStructure :: LocalVolTermStructure -> (Ptr CLocalVolTermStructure -> IO b) -> IO b
withLocalVolTermStructure = withStandalone . getCLocalVolTermStructure
data CMargrabeOption
newtype MargrabeOption = MargrabeOption {getCMargrabeOption :: Standalone CMargrabeOption}
margrabeOptionMeta :: Meta CMargrabeOption
margrabeOptionMeta = Meta qlFreeMargrabeOption
peekMargrabeOption :: Ptr CMargrabeOption -> IO MargrabeOption
peekMargrabeOption = peekStandalone margrabeOptionMeta >=> return . MargrabeOption
withMargrabeOption :: MargrabeOption -> (Ptr CMargrabeOption -> IO b) -> IO b
withMargrabeOption = withStandalone . getCMargrabeOption
data CMerton76Process
newtype Merton76Process = Merton76Process {getCMerton76Process :: Standalone CMerton76Process}
merton76ProcessMeta :: Meta CMerton76Process
merton76ProcessMeta = Meta qlFreeMerton76Process
peekMerton76Process :: Ptr CMerton76Process -> IO Merton76Process
peekMerton76Process = peekStandalone merton76ProcessMeta >=> return . Merton76Process
withMerton76Process :: Merton76Process -> (Ptr CMerton76Process -> IO b) -> IO b
withMerton76Process = withStandalone . getCMerton76Process
data CMultiAssetOption
newtype MultiAssetOption = MultiAssetOption {getCMultiAssetOption :: Standalone CMultiAssetOption}
multiAssetOptionMeta :: Meta CMultiAssetOption
multiAssetOptionMeta = Meta qlFreeMultiAssetOption
peekMultiAssetOption :: Ptr CMultiAssetOption -> IO MultiAssetOption
peekMultiAssetOption = peekStandalone multiAssetOptionMeta >=> return . MultiAssetOption
withMultiAssetOption :: MultiAssetOption -> (Ptr CMultiAssetOption -> IO b) -> IO b
withMultiAssetOption = withStandalone . getCMultiAssetOption
data COneAssetOption
newtype OneAssetOption = OneAssetOption {getCOneAssetOption :: Standalone COneAssetOption}
oneAssetOptionMeta :: Meta COneAssetOption
oneAssetOptionMeta = Meta qlFreeOneAssetOption
peekOneAssetOption :: Ptr COneAssetOption -> IO OneAssetOption
peekOneAssetOption = peekStandalone oneAssetOptionMeta >=> return . OneAssetOption
withOneAssetOption :: OneAssetOption -> (Ptr COneAssetOption -> IO b) -> IO b
withOneAssetOption = withStandalone . getCOneAssetOption
data COneFactorAffineModel
newtype OneFactorAffineModel = OneFactorAffineModel {getCOneFactorAffineModel :: Standalone COneFactorAffineModel}
oneFactorAffineModelMeta :: Meta COneFactorAffineModel
oneFactorAffineModelMeta = Meta qlFreeOneFactorAffineModel
peekOneFactorAffineModel :: Ptr COneFactorAffineModel -> IO OneFactorAffineModel
peekOneFactorAffineModel = peekStandalone oneFactorAffineModelMeta >=> return . OneFactorAffineModel
withOneFactorAffineModel :: OneFactorAffineModel -> (Ptr COneFactorAffineModel -> IO b) -> IO b
withOneFactorAffineModel = withStandalone . getCOneFactorAffineModel
data COption
newtype Option = Option {getCOption :: Standalone COption}
optionMeta :: Meta COption
optionMeta = Meta qlFreeOption
peekOption :: Ptr COption -> IO Option
peekOption = peekStandalone optionMeta >=> return . Option
withOption :: Option -> (Ptr COption -> IO b) -> IO b
withOption = withStandalone . getCOption
data COptionletVolatilityStructure
newtype OptionletVolatilityStructure = OptionletVolatilityStructure {getCOptionletVolatilityStructure :: Standalone COptionletVolatilityStructure}
optionletVolatilityStructureMeta :: Meta COptionletVolatilityStructure
optionletVolatilityStructureMeta = Meta qlFreeOptionletVolatilityStructure
peekOptionletVolatilityStructure :: Ptr COptionletVolatilityStructure -> IO OptionletVolatilityStructure
peekOptionletVolatilityStructure = peekStandalone optionletVolatilityStructureMeta >=> return . OptionletVolatilityStructure
withOptionletVolatilityStructure :: OptionletVolatilityStructure -> (Ptr COptionletVolatilityStructure -> IO b) -> IO b
withOptionletVolatilityStructure = withStandalone . getCOptionletVolatilityStructure
data COvernightIndexedSwap
newtype OvernightIndexedSwap = OvernightIndexedSwap {getCOvernightIndexedSwap :: Standalone COvernightIndexedSwap}
overnightIndexedSwapMeta :: Meta COvernightIndexedSwap
overnightIndexedSwapMeta = Meta qlFreeOvernightIndexedSwap
peekOvernightIndexedSwap :: Ptr COvernightIndexedSwap -> IO OvernightIndexedSwap
peekOvernightIndexedSwap = peekStandalone overnightIndexedSwapMeta >=> return . OvernightIndexedSwap
withOvernightIndexedSwap :: OvernightIndexedSwap -> (Ptr COvernightIndexedSwap -> IO b) -> IO b
withOvernightIndexedSwap = withStandalone . getCOvernightIndexedSwap
data COvernightIndexedSwapIndex
overnightIndexedSwapIndexMeta :: Meta COvernightIndexedSwapIndex
overnightIndexedSwapIndexMeta = Meta qlFreeOvernightIndexedSwapIndex
data CPiecewiseTimeDependentHestonModel
newtype PiecewiseTimeDependentHestonModel = PiecewiseTimeDependentHestonModel {getCPiecewiseTimeDependentHestonModel :: Standalone CPiecewiseTimeDependentHestonModel}
piecewiseTimeDependentHestonModelMeta :: Meta CPiecewiseTimeDependentHestonModel
piecewiseTimeDependentHestonModelMeta = Meta qlFreePiecewiseTimeDependentHestonModel
peekPiecewiseTimeDependentHestonModel :: Ptr CPiecewiseTimeDependentHestonModel -> IO PiecewiseTimeDependentHestonModel
peekPiecewiseTimeDependentHestonModel = peekStandalone piecewiseTimeDependentHestonModelMeta >=> return . PiecewiseTimeDependentHestonModel
withPiecewiseTimeDependentHestonModel :: PiecewiseTimeDependentHestonModel -> (Ptr CPiecewiseTimeDependentHestonModel -> IO b) -> IO b
withPiecewiseTimeDependentHestonModel = withStandalone . getCPiecewiseTimeDependentHestonModel
data CQuantoBarrierOption
newtype QuantoBarrierOption = QuantoBarrierOption {getCQuantoBarrierOption :: Standalone CQuantoBarrierOption}
quantoBarrierOptionMeta :: Meta CQuantoBarrierOption
quantoBarrierOptionMeta = Meta qlFreeQuantoBarrierOption
peekQuantoBarrierOption :: Ptr CQuantoBarrierOption -> IO QuantoBarrierOption
peekQuantoBarrierOption = peekStandalone quantoBarrierOptionMeta >=> return . QuantoBarrierOption
withQuantoBarrierOption :: QuantoBarrierOption -> (Ptr CQuantoBarrierOption -> IO b) -> IO b
withQuantoBarrierOption = withStandalone . getCQuantoBarrierOption
data CQuantoForwardVanillaOption
newtype QuantoForwardVanillaOption = QuantoForwardVanillaOption {getCQuantoForwardVanillaOption :: Standalone CQuantoForwardVanillaOption}
quantoForwardVanillaOptionMeta :: Meta CQuantoForwardVanillaOption
quantoForwardVanillaOptionMeta = Meta qlFreeQuantoForwardVanillaOption
peekQuantoForwardVanillaOption :: Ptr CQuantoForwardVanillaOption -> IO QuantoForwardVanillaOption
peekQuantoForwardVanillaOption = peekStandalone quantoForwardVanillaOptionMeta >=> return . QuantoForwardVanillaOption
withQuantoForwardVanillaOption :: QuantoForwardVanillaOption -> (Ptr CQuantoForwardVanillaOption -> IO b) -> IO b
withQuantoForwardVanillaOption = withStandalone . getCQuantoForwardVanillaOption
data CQuantoVanillaOption
newtype QuantoVanillaOption = QuantoVanillaOption {getCQuantoVanillaOption :: Standalone CQuantoVanillaOption}
quantoVanillaOptionMeta :: Meta CQuantoVanillaOption
quantoVanillaOptionMeta = Meta qlFreeQuantoVanillaOption
peekQuantoVanillaOption :: Ptr CQuantoVanillaOption -> IO QuantoVanillaOption
peekQuantoVanillaOption = peekStandalone quantoVanillaOptionMeta >=> return . QuantoVanillaOption
withQuantoVanillaOption :: QuantoVanillaOption -> (Ptr CQuantoVanillaOption -> IO b) -> IO b
withQuantoVanillaOption = withStandalone . getCQuantoVanillaOption
data CShortRateModel
newtype ShortRateModel = ShortRateModel {getCShortRateModel :: Standalone CShortRateModel}
shortRateModelMeta :: Meta CShortRateModel
shortRateModelMeta = Meta qlFreeShortRateModel
peekShortRateModel :: Ptr CShortRateModel -> IO ShortRateModel
peekShortRateModel = peekStandalone shortRateModelMeta >=> return . ShortRateModel
withShortRateModel :: ShortRateModel -> (Ptr CShortRateModel -> IO b) -> IO b
withShortRateModel = withStandalone . getCShortRateModel
data CStochasticProcess1D
newtype StochasticProcess1D = StochasticProcess1D {getCStochasticProcess1D :: Standalone CStochasticProcess1D}
stochasticProcess1DMeta :: Meta CStochasticProcess1D
stochasticProcess1DMeta = Meta qlFreeStochasticProcess1D
peekStochasticProcess1D :: Ptr CStochasticProcess1D -> IO StochasticProcess1D
peekStochasticProcess1D = peekStandalone stochasticProcess1DMeta >=> return . StochasticProcess1D
withStochasticProcess1D :: StochasticProcess1D -> (Ptr CStochasticProcess1D -> IO b) -> IO b
withStochasticProcess1D = withStandalone . getCStochasticProcess1D
data CStochasticProcessArray
newtype StochasticProcessArray = StochasticProcessArray {getCStochasticProcessArray :: Standalone CStochasticProcessArray}
stochasticProcessArrayMeta :: Meta CStochasticProcessArray
stochasticProcessArrayMeta = Meta qlFreeStochasticProcessArray
peekStochasticProcessArray :: Ptr CStochasticProcessArray -> IO StochasticProcessArray
peekStochasticProcessArray = peekStandalone stochasticProcessArrayMeta >=> return . StochasticProcessArray
withStochasticProcessArray :: StochasticProcessArray -> (Ptr CStochasticProcessArray -> IO b) -> IO b
withStochasticProcessArray = withStandalone . getCStochasticProcessArray
data CStochasticProcess
newtype StochasticProcess = StochasticProcess {getCStochasticProcess :: Standalone CStochasticProcess}
stochasticProcessMeta :: Meta CStochasticProcess
stochasticProcessMeta = Meta qlFreeStochasticProcess
peekStochasticProcess :: Ptr CStochasticProcess -> IO StochasticProcess
peekStochasticProcess = peekStandalone stochasticProcessMeta >=> return . StochasticProcess
withStochasticProcess :: StochasticProcess -> (Ptr CStochasticProcess -> IO b) -> IO b
withStochasticProcess = withStandalone . getCStochasticProcess
data CSwap
newtype Swap = Swap {getCSwap :: Standalone CSwap}
swapMeta :: Meta CSwap
swapMeta = Meta qlFreeSwap
peekSwap :: Ptr CSwap -> IO Swap
peekSwap = peekStandalone swapMeta >=> return . Swap
withSwap :: Swap -> (Ptr CSwap -> IO b) -> IO b
withSwap = withStandalone . getCSwap
data CSwapIndex
swapIndexMeta :: Meta CSwapIndex
swapIndexMeta = Meta qlFreeSwapIndex
data CSwaption
newtype Swaption = Swaption {getCSwaption :: Standalone CSwaption}
swaptionMeta :: Meta CSwaption
swaptionMeta = Meta qlFreeSwaption
peekSwaption :: Ptr CSwaption -> IO Swaption
peekSwaption = peekStandalone swaptionMeta >=> return . Swaption
withSwaption :: Swaption -> (Ptr CSwaption -> IO b) -> IO b
withSwaption = withStandalone . getCSwaption
data CSwaptionVolatilityStructure
newtype SwaptionVolatilityStructure = SwaptionVolatilityStructure {getCSwaptionVolatilityStructure :: Standalone CSwaptionVolatilityStructure}
swaptionVolatilityStructureMeta :: Meta CSwaptionVolatilityStructure
swaptionVolatilityStructureMeta = Meta qlFreeSwaptionVolatilityStructure
peekSwaptionVolatilityStructure :: Ptr CSwaptionVolatilityStructure -> IO SwaptionVolatilityStructure
peekSwaptionVolatilityStructure = peekStandalone swaptionVolatilityStructureMeta >=> return . SwaptionVolatilityStructure
withSwaptionVolatilityStructure :: SwaptionVolatilityStructure -> (Ptr CSwaptionVolatilityStructure -> IO b) -> IO b
withSwaptionVolatilityStructure = withStandalone . getCSwaptionVolatilityStructure
data CTermStructure
newtype TermStructure = TermStructure {getCTermStructure :: Standalone CTermStructure}
termStructureMeta :: Meta CTermStructure
termStructureMeta = Meta qlFreeTermStructure
peekTermStructure :: Ptr CTermStructure -> IO TermStructure
peekTermStructure = peekStandalone termStructureMeta >=> return . TermStructure
withTermStructure :: TermStructure -> (Ptr CTermStructure -> IO b) -> IO b
withTermStructure = withStandalone . getCTermStructure
data CVanillaOption
newtype VanillaOption = VanillaOption {getCVanillaOption :: Standalone CVanillaOption}
vanillaOptionMeta :: Meta CVanillaOption
vanillaOptionMeta = Meta qlFreeVanillaOption
peekVanillaOption :: Ptr CVanillaOption -> IO VanillaOption
peekVanillaOption = peekStandalone vanillaOptionMeta >=> return . VanillaOption
withVanillaOption :: VanillaOption -> (Ptr CVanillaOption -> IO b) -> IO b
withVanillaOption = withStandalone . getCVanillaOption
data CVanillaSwap
newtype VanillaSwap = VanillaSwap {getCVanillaSwap :: Standalone CVanillaSwap}
vanillaSwapMeta :: Meta CVanillaSwap
vanillaSwapMeta = Meta qlFreeVanillaSwap
peekVanillaSwap :: Ptr CVanillaSwap -> IO VanillaSwap
peekVanillaSwap = peekStandalone vanillaSwapMeta >=> return . VanillaSwap
withVanillaSwap :: VanillaSwap -> (Ptr CVanillaSwap -> IO b) -> IO b
withVanillaSwap = withStandalone . getCVanillaSwap
data CVarianceGammaProcess
newtype VarianceGammaProcess = VarianceGammaProcess {getCVarianceGammaProcess :: Standalone CVarianceGammaProcess}
varianceGammaProcessMeta :: Meta CVarianceGammaProcess
varianceGammaProcessMeta = Meta qlFreeVarianceGammaProcess
peekVarianceGammaProcess :: Ptr CVarianceGammaProcess -> IO VarianceGammaProcess
peekVarianceGammaProcess = peekStandalone varianceGammaProcessMeta >=> return . VarianceGammaProcess
withVarianceGammaProcess :: VarianceGammaProcess -> (Ptr CVarianceGammaProcess -> IO b) -> IO b
withVarianceGammaProcess = withStandalone . getCVarianceGammaProcess
data CVolatilityTermStructure
newtype VolatilityTermStructure = VolatilityTermStructure {getCVolatilityTermStructure :: Standalone CVolatilityTermStructure}
volatilityTermStructureMeta :: Meta CVolatilityTermStructure
volatilityTermStructureMeta = Meta qlFreeVolatilityTermStructure
peekVolatilityTermStructure :: Ptr CVolatilityTermStructure -> IO VolatilityTermStructure
peekVolatilityTermStructure = peekStandalone volatilityTermStructureMeta >=> return . VolatilityTermStructure
withVolatilityTermStructure :: VolatilityTermStructure -> (Ptr CVolatilityTermStructure -> IO b) -> IO b
withVolatilityTermStructure = withStandalone . getCVolatilityTermStructure
data CYieldTermStructure
newtype YieldTermStructure = YieldTermStructure {getCYieldTermStructure :: Standalone CYieldTermStructure}
yieldTermStructureMeta :: Meta CYieldTermStructure
yieldTermStructureMeta = Meta qlFreeYieldTermStructure
peekYieldTermStructure :: Ptr CYieldTermStructure -> IO YieldTermStructure
peekYieldTermStructure = peekStandalone yieldTermStructureMeta >=> return . YieldTermStructure
withYieldTermStructure :: YieldTermStructure -> (Ptr CYieldTermStructure -> IO b) -> IO b
withYieldTermStructure = withStandalone . getCYieldTermStructure

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
foreign import ccall "ql.h &qlFreeBondForward" qlFreeBondForward :: FinalizerPtr CBondForward
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
withInstrumentArray = withStandaloneArray getCInstrument

withMaybeYieldTermStructure :: Maybe YieldTermStructure -> (Ptr CYieldTermStructure -> IO b) -> IO b
withMaybeYieldTermStructure = withMaybeStandalone . (getCYieldTermStructure <$>)

withStochasticProcess1DArray :: [StochasticProcess1D] -> ((CUInt, Ptr (Ptr CStochasticProcess1D)) -> IO b) -> IO b
withStochasticProcess1DArray = withStandaloneArray getCStochasticProcess1D

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
