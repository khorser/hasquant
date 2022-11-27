{-# LANGUAGE RankNTypes, DuplicateRecordFields #-}
--{-# LANGUAGE FlexibleContexts, TypeFamilies #-}
module QuantLib.Internal.Type
(
    Standalone(..)
  , withStandalone

  , CCalendar
  , Calendar
  , peekCalendar
  , withCalendar
  , CCurrency
  , Currency
  , peekCurrency
  , withCurrency
  , withMaybeCurrency
  , CDayCounter
  , DayCounter
  , peekDayCounter
  , withDayCounter
  , CSchedule
  , Schedule
  , peekSchedule
  , withSchedule
  , InterestRate
  , CInterestRate
  , peekInterestRate
  , withInterestRate
  , withInterestRateArray
  , TimeGrid
  , CTimeGrid
  , peekTimeGrid
  , withTimeGrid
  , CDividend
  , Dividend
  , peekDividend
  , withDividend
  , withDividendArray
  , CSmileSection
  , SmileSection
  , peekSmileSection
  , withSmileSection
  , CPricingEngine
  , PricingEngine
  , peekPricingEngine
  , withPricingEngine
  , CFloatingRateCouponPricer
  , FloatingRateCouponPricer
  , peekFloatingRateCouponPricer
  , withFloatingRateCouponPricer
  , withFloatingRateCouponPricerArray
  , CDefaultProbabilityHelper
  , DefaultProbabilityHelper
  , peekDefaultProbabilityHelper
  , withDefaultProbabilityHelper
  , withDefaultProbabilityHelperArray
  , CPathGenerator
  , PathGenerator
  , peekPathGenerator
  , withPathGenerator
  , CSamplePath
  , SamplePath
  , peekSamplePath
  , withSamplePath

  , CQlClaim
  , QlClaim
  , peekClaim
  , CQlCallability
  , QlCallability
  , peekCallability
  , CConstraint
  , QlConstraint
  , peekConstraint
  , CEndCriteria
  , QlEndCriteria
  , peekEndCriteria
  , CFdmSchemeDesc
  , QlFdmSchemeDesc
  , peekFdmSchemeDesc
  , CFittedBondDiscountCurveFittingMethod
  , QlFittedBondDiscountCurveFittingMethod
  , peekFittedBondDiscountCurveFittingMethod
  , COptimizationMethod
  , QlOptimizationMethod
  , peekOptimizationMethod
  , CRounding
  , QlRounding
  , peekRounding
  , CLmCorrelationModel
  , QlLmCorrelationModel
  , peekLmCorrelationModel
  , CLmVolatilityModel
  , QlLmVolatilityModel
  , peekLmVolatilityModel

  , GenQuote
  , CQuote
  , Quote
  , asQuote
  , peekQuote
  , withQuote
  , withMaybeQuote
  , withQuoteArray
  , withQuoteArrayRaw
  , CSimpleQuote
  , SimpleQuote
  , peekSimpleQuote
  , withSimpleQuote

  , GenLeg
  , CLeg
  , Leg
  , asLeg
  , peekLeg
  , withLeg
  , withLegArray
  , CCouponLeg
  , CouponLeg
  , peekCouponLeg
  , withCouponLeg

  , GenRateHelper
  , CRateHelper
  , RateHelper
  , asRateHelper
  , peekRateHelper
  , withRateHelper
  , withRateHelperArray
  , CBondHelper
  , BondHelper
  , peekBondHelper
  , withBondHelper
  , withBondHelperArray
  , CSwapRateHelper
  , SwapRateHelper
  , peekSwapRateHelper
  , withSwapRateHelper
  , COISRateHelper
  , OISRateHelper
  , peekOISRateHelper
  , withOISRateHelper

  , GenCalibrationHelper
  , CCalibrationHelper
  , CalibrationHelper
  , asCalibrationHelper
  , peekCalibrationHelper
  , withCalibrationHelper
  , withCalibrationHelperArray
  , CBlackCalibrationHelper
  , BlackCalibrationHelper
  , withBlackCalibrationHelper
  , peekBlackCalibrationHelper

  , GenBlackCalculator
  , CBlackCalculator
  , BlackCalculator
  , asBlackCalculator
  , peekBlackCalculator
  , withBlackCalculator
  , CBlackScholesCalculator
  , BlackScholesCalculator
  , peekBlackScholesCalculator
  , withBlackScholesCalculator

  , GenIndex
  , CIndex
  , CIndex'
  , Index
  , asIndex
  , withIndex
  , GenInterestRateIndex
  , CInterestRateIndex
  , CInterestRateIndex'
  , InterestRateIndex
  , asInterestRateIndex
  , withInterestRateIndex
  , CBMAIndex
  , CBMAIndex'
  , BMAIndex
  , peekBMAIndex
  , withBMAIndex
  , GenIborIndex
  , CIborIndex
  , CIborIndex'
  , IborIndex
  , asIborIndex
  , peekIborIndex
  , withIborIndex
  , COvernightIndex
  , COvernightIndex'
  , OvernightIborIndex
  , peekOvernightIborIndex
  , withOvernightIborIndex
  , GenSwapIndex
  , CSwapIndex
  , CSwapIndex'
  , SwapIndex
  , asSwapIndex
  , peekSwapIndex
  , withSwapIndex
  , OvernightIndexedSwapIndex
  , COvernightIndexedSwapIndex
  , COvernightIndexedSwapIndex'
  , peekOvernightIndexedSwapIndex
  , withOvernightIndexedSwapIndex

  , GenTermStructure
  , TermStructure
  , CTermStructure
  , CTermStructure'
  , asTermStructure
  , withTermStructure
  , withTermStructureDescendant
  , GenVolatilityTermStructure
  , VolatilityTermStructure
  , CVolatilityTermStructure
  , CVolatilityTermStructure'
  , peekVolatilityTermStructure
  , withVolatilityTermStructure
  , withVolatilityTermStructureDescendant
  , OptionletVolatilityStructure
  , COptionletVolatilityStructure
  , COptionletVolatilityStructure'
  , peekOptionletVolatilityStructure
  , SwaptionVolatilityStructure
  , CSwaptionVolatilityStructure
  , CSwaptionVolatilityStructure'
  , peekSwaptionVolatilityStructure
  , CapFloorTermVolSurface
  , CCapFloorTermVolSurface
  , CCapFloorTermVolSurface'
  , peekCapFloorTermVolSurface
  , LocalVolTermStructure
  , CLocalVolTermStructure
  , CLocalVolTermStructure'
  , peekLocalVolTermStructure
  , GenBlackVolTermStructure
  , BlackVolTermStructure
  , CBlackVolTermStructure
  , CBlackVolTermStructure'
  , asBlackVolTermStructure
  , asVolatilityTermStructure
  , peekBlackVolTermStructure
  , withBlackVolTermStructure
  , BlackVarianceCurve
  , CBlackVarianceCurve
  , CBlackVarianceCurve'
  , peekBlackVarianceCurve
  , withBlackVarianceCurve
  , GenYieldTermStructure
  , YieldTermStructure
  , CYieldTermStructure
  , CYieldTermStructure'
  , asYieldTermStructure
  , peekYieldTermStructure
  , withYieldTermStructure
  , withMaybeYieldTermStructure
  , FittedBondDiscountCurve
  , CFittedBondDiscountCurve
  , CFittedBondDiscountCurve'
  , peekFittedBondDiscountCurve
  , withFittedBondDiscountCurve
  , CallableBondVolatilityStructure
  , CCallableBondVolatilityStructure
  , CCallableBondVolatilityStructure'
  , peekCallableBondVolatilityStructure
  , DefaultProbabilityTermStructure
  , CDefaultProbabilityTermStructure
  , CDefaultProbabilityTermStructure'
  , peekDefaultProbabilityTermStructure

  , BatesProcess
  , CBatesProcess
  , CBatesProcess'
  , peekBatesProcess
  , withBatesProcess
  , BlackProcess
  , CBlackProcess
  , CBlackProcess'
  , peekBlackProcess
  , withBlackProcess
  , ExtendedOrnsteinUhlenbeckProcess
  , CExtendedOrnsteinUhlenbeckProcess
  , CExtendedOrnsteinUhlenbeckProcess'
  , peekExtendedOrnsteinUhlenbeckProcess
  , ExtOUWithJumpsProcess
  , CExtOUWithJumpsProcess
  , CExtOUWithJumpsProcess'
  , peekExtOUWithJumpsProcess
  , GeneralizedBlackScholesProcess
  , GenGeneralizedBlackScholesProcess
  , CGeneralizedBlackScholesProcess
  , CGeneralizedBlackScholesProcess'
  , peekGeneralizedBlackScholesProcess
  , withGeneralizedBlackScholesProcess
  , GJRGARCHProcess
  , CGJRGARCHProcess
  , CGJRGARCHProcess'
  , peekGJRGARCHProcess
  , HestonProcess
  , GenHestonProcess
  , CHestonProcess
  , CHestonProcess'
  , peekHestonProcess
  , withHestonProcess
  , HullWhiteForwardProcess
  , CHullWhiteForwardProcess
  , CHullWhiteForwardProcess'
  , peekHullWhiteForwardProcess
  , HullWhiteProcess
  , CHullWhiteProcess
  , CHullWhiteProcess'
  , peekHullWhiteProcess
  , HybridHestonHullWhiteProcess
  , CHybridHestonHullWhiteProcess
  , CHybridHestonHullWhiteProcess'
  , peekHybridHestonHullWhiteProcess
  , KlugeExtOUProcess
  , CKlugeExtOUProcess
  , CKlugeExtOUProcess'
  , peekKlugeExtOUProcess
  , LiborForwardModelProcess
  , CLiborForwardModelProcess
  , CLiborForwardModelProcess'
  , peekLiborForwardModelProcess
  , withStochasticProcess1DArray
  , StochasticProcess1D
  , GenStochasticProcess1D
  , CStochasticProcess1D
  , CStochasticProcess1D'
  , peekStochasticProcess1D
  , withStochasticProcess1D
  , withStochasticProcess1DDescendant
  , StochasticProcessArray
  , CStochasticProcessArray
  , CStochasticProcessArray'
  , peekStochasticProcessArray
  , StochasticProcess
  , GenStochasticProcess
  , CStochasticProcess
  , CStochasticProcess'
  , peekStochasticProcess
  , withStochasticProcess
  , withStochasticProcessDescendant
  , VarianceGammaProcess
  , CVarianceGammaProcess
  , CVarianceGammaProcess'
  , peekVarianceGammaProcess
  , Merton76Process
  , CMerton76Process
  , CMerton76Process'
  , peekMerton76Process
  , asStochasticProcess
  , asHestonProcess
  , asStochasticProcess1D
  , asGeneralizedBlackScholesProcess

  , AffineModel
  , CAffineModel
  , peekAffineModel
  , withAffineModel
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
  , CalibratedModel
  , CCalibratedModel
  , peekCalibratedModel
  , withCalibratedModel
  , G2
  , CG2
  , peekG2
  , withG2
  , GJRGARCHModel
  , CGJRGARCHModel
  , peekGJRGARCHModel
  , withGJRGARCHModel
  , HestonModel
  , CHestonModel
  , peekHestonModel
  , withHestonModel
  , HullWhite
  , CHullWhite
  , peekHullWhite
  , withHullWhite
  , PiecewiseTimeDependentHestonModel
  , CPiecewiseTimeDependentHestonModel
  , peekPiecewiseTimeDependentHestonModel
  , withPiecewiseTimeDependentHestonModel
  , ShortRateModel
  , CShortRateModel
  , peekShortRateModel
  , withShortRateModel
  , OneFactorAffineModel
  , COneFactorAffineModel
  , peekOneFactorAffineModel
  , withOneFactorAffineModel
  , LiborForwardModel
  , CLiborForwardModel
  , peekLiborForwardModel
  , withLiborForwardModel

  , AssetSwap
  , CAssetSwap
  , peekAssetSwap
  , withAssetSwap
  , BarrierOption
  , CBarrierOption
  , peekBarrierOption
  , withBarrierOption
  , BMASwap
  , CBMASwap
  , peekBMASwap
  , withBMASwap
  , Bond
  , CBond
  , peekBond
  , withBond
  , CallableBond
  , CCallableBond
  , peekCallableBond
  , withCallableBond
  , CapFloor
  , CCapFloor
  , peekCapFloor
  , withCapFloor
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
  , DividendVanillaOption
  , CDividendVanillaOption
  , peekDividendVanillaOption
  , withDividendVanillaOption
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
  , Instrument
  , CInstrument
  , peekInstrument
  , withInstrument
  , withInstrumentArray
  , Option
  , COption
  , peekOption
  , withOption
  , OvernightIndexedSwap
  , COvernightIndexedSwap
  , peekOvernightIndexedSwap
  , withOvernightIndexedSwap
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
  , Swap
  , CSwap
  , peekSwap
  , withSwap
  , Swaption
  , CSwaption
  , peekSwaption
  , withSwaption
  , VanillaOption
  , CVanillaOption
  , peekVanillaOption
  , withVanillaOption
  , VanillaSwap
  , CVanillaSwap
  , peekVanillaSwap
  , withVanillaSwap
  , MargrabeOption
  , CMargrabeOption
  , peekMargrabeOption
  , withMargrabeOption
  , MultiAssetOption
  , CMultiAssetOption
  , peekMultiAssetOption
  , withMultiAssetOption
  , OneAssetOption
  , COneAssetOption
  , peekOneAssetOption
  , withOneAssetOption
)
  where
import Foreign.Ptr
import Foreign.ForeignPtr
import Foreign.C.Types
import Foreign.C.String
import Foreign.Marshal.Array(withArray)
import Foreign.Marshal.Utils(withMany)

import Data.Functor((<&>))
--import Data.Kind(Type)
import Control.Monad((>=>))
import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Internal

(<.>) :: Functor f => (a1 -> b) -> (a2 -> f a1) -> a2 -> f b
f1 <.> f2 = fmap f1 . f2

(<^>) :: Applicative f => (t -> a) -> t -> f a
f <^> x = pure $ f x

-- STANDALONE TYPES
newtype Standalone a = Standalone {_ptr :: ForeignPtr a}
peekStandalone :: Finalizable a => Ptr a -> IO (Standalone a)
peekStandalone = Standalone <.> newForeignPtr finalize
withStandalone :: Standalone a -> (Ptr a -> IO b) -> IO b
withStandalone (Standalone p) = withForeignPtr p
withMaybeStandalone :: Maybe (Standalone a) -> (Ptr a -> IO b) -> IO b
withMaybeStandalone x f = maybe (f nullPtr) (`withStandalone` f) x
withStandaloneArray :: (t -> Standalone a) -> [t] -> ((CUInt, Ptr (Ptr a)) -> IO b) -> IO b
withStandaloneArray c x f = withMany withStandalone (map c x) (`withArray` (\px -> f (fromIntegral $ length x, px)))
showStandalone :: (Ptr a -> IO CString) -> Standalone a -> String
showStandalone f x = unsafePerformIO $ withStandalone x (f >=> peekDynString)

data CCalendar
newtype Calendar = Calendar {getCCalendar :: Standalone CCalendar}
instance Finalizable CCalendar where finalize = qlFreeCalendar
foreign import ccall "ql.h &qlFreeCalendar" qlFreeCalendar :: FinalizerPtr CCalendar
peekCalendar :: Ptr CCalendar -> IO Calendar
peekCalendar = Calendar <.> peekStandalone
withCalendar :: Calendar -> (Ptr CCalendar -> IO b) -> IO b
withCalendar = withStandalone . getCCalendar
foreign import ccall safe "ql.h qlCalendarName" qlCalendarName :: Ptr CCalendar -> IO CString
instance Show Calendar where show x = showStandalone qlCalendarName (getCCalendar x)
instance Eq Calendar where x == y = show x == show y

data CCurrency
newtype Currency = Currency {getCCurrency :: Standalone CCurrency}
foreign import ccall "ql.h &qlFreeCurrency" qlFreeCurrency :: FinalizerPtr CCurrency
instance Finalizable CCurrency where finalize = qlFreeCurrency
peekCurrency :: Ptr CCurrency -> IO Currency
peekCurrency = Currency <.> peekStandalone
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
instance Finalizable CDayCounter where finalize = qlFreeDayCounter
peekDayCounter :: Ptr CDayCounter -> IO DayCounter
peekDayCounter = DayCounter <.> peekStandalone
withDayCounter :: DayCounter -> (Ptr CDayCounter -> IO b) -> IO b
withDayCounter = withStandalone . getCDayCounter
foreign import ccall safe "ql.h qlDayCounterName" qlDayCounterName :: Ptr CDayCounter -> IO CString
instance Show DayCounter where show x = showStandalone qlDayCounterName (getCDayCounter x)
instance Eq DayCounter where x == y = show x == show y

data CSchedule
newtype Schedule = Schedule {getCSchedule :: Standalone CSchedule}
foreign import ccall "ql.h &qlFreeSchedule" qlFreeSchedule :: FinalizerPtr CSchedule
instance Finalizable CSchedule where finalize = qlFreeSchedule
peekSchedule :: Ptr CSchedule -> IO Schedule
peekSchedule = Schedule <.> peekStandalone
withSchedule :: Schedule -> (Ptr CSchedule -> IO b) -> IO b
withSchedule = withStandalone . getCSchedule

data CInterestRate
newtype InterestRate = InterestRate {getCInterestRate :: Standalone CInterestRate}
foreign import ccall "ql.h &qlFreeInterestRate" qlFreeInterestRate :: FinalizerPtr CInterestRate
instance Finalizable CInterestRate where finalize = qlFreeInterestRate
peekInterestRate :: Ptr CInterestRate -> IO InterestRate
peekInterestRate = InterestRate <.> peekStandalone
withInterestRate :: InterestRate -> (Ptr CInterestRate -> IO b) -> IO b
withInterestRate = withStandalone . getCInterestRate
withInterestRateArray :: [InterestRate] -> ((CUInt, Ptr (Ptr CInterestRate)) -> IO b) -> IO b
withInterestRateArray = withStandaloneArray getCInterestRate

data CTimeGrid
newtype TimeGrid = TimeGrid {getCTimeGrid :: Standalone CTimeGrid}
foreign import ccall "ql.h &qlFreeTimeGrid" qlFreeTimeGrid :: FinalizerPtr CTimeGrid
instance Finalizable CTimeGrid where finalize = qlFreeTimeGrid
peekTimeGrid :: Ptr CTimeGrid -> IO TimeGrid
peekTimeGrid = TimeGrid <.> peekStandalone
withTimeGrid :: TimeGrid -> (Ptr CTimeGrid -> IO b) -> IO b
withTimeGrid = withStandalone . getCTimeGrid

data CDividend
newtype Dividend = Dividend {getCDividend :: Standalone CDividend}
foreign import ccall "ql.h &qlFreeDividend" qlFreeDividend :: FinalizerPtr CDividend
instance Finalizable CDividend where finalize = qlFreeDividend
peekDividend :: Ptr CDividend -> IO Dividend
peekDividend = Dividend <.> peekStandalone
withDividend :: Dividend -> (Ptr CDividend -> IO b) -> IO b
withDividend = withStandalone . getCDividend
withDividendArray :: [Dividend] -> ((CUInt, Ptr (Ptr CDividend)) -> IO b) -> IO b
withDividendArray = withStandaloneArray getCDividend

data CSmileSection
newtype SmileSection = SmileSection {getCSmileSection :: Standalone CSmileSection}
foreign import ccall "ql.h &qlFreeSmileSection" qlFreeSmileSection :: FinalizerPtr CSmileSection
instance Finalizable CSmileSection where finalize = qlFreeSmileSection
peekSmileSection :: Ptr CSmileSection -> IO SmileSection
peekSmileSection = SmileSection <.> peekStandalone
withSmileSection :: SmileSection -> (Ptr CSmileSection -> IO b) -> IO b
withSmileSection = withStandalone . getCSmileSection

data CPricingEngine
newtype PricingEngine = PricingEngine {getCPricingEngine :: Standalone CPricingEngine}
foreign import ccall "ql.h &qlFreePricingEngine" qlFreePricingEngine :: FinalizerPtr CPricingEngine
instance Finalizable CPricingEngine where finalize = qlFreePricingEngine
peekPricingEngine :: Ptr CPricingEngine -> IO PricingEngine
peekPricingEngine = PricingEngine <.> peekStandalone
withPricingEngine :: PricingEngine -> (Ptr CPricingEngine -> IO b) -> IO b
withPricingEngine = withStandalone . getCPricingEngine

data CFloatingRateCouponPricer
newtype FloatingRateCouponPricer = FloatingRateCouponPricer {getCFloatingRateCouponPricer :: Standalone CFloatingRateCouponPricer}
foreign import ccall "ql.h &qlFreeFloatingCouponPricer" qlFreeFloatingRateCouponPricer :: FinalizerPtr CFloatingRateCouponPricer
instance Finalizable CFloatingRateCouponPricer where finalize = qlFreeFloatingRateCouponPricer
peekFloatingRateCouponPricer :: Ptr CFloatingRateCouponPricer -> IO FloatingRateCouponPricer
peekFloatingRateCouponPricer = FloatingRateCouponPricer <.> peekStandalone
withFloatingRateCouponPricer :: FloatingRateCouponPricer -> (Ptr CFloatingRateCouponPricer -> IO b) -> IO b
withFloatingRateCouponPricer = withStandalone . getCFloatingRateCouponPricer
withFloatingRateCouponPricerArray :: [FloatingRateCouponPricer] -> ((CUInt, Ptr (Ptr CFloatingRateCouponPricer)) -> IO b) -> IO b
withFloatingRateCouponPricerArray = withStandaloneArray getCFloatingRateCouponPricer

data CDefaultProbabilityHelper
newtype DefaultProbabilityHelper = DefaultProbabilityHelper {getCDefaultProbabilityHelper :: Standalone CDefaultProbabilityHelper}
foreign import ccall "ql.h &qlFreeDefaultProbabilityHelper" qlFreeDefaultProbabilityHelper :: FinalizerPtr CDefaultProbabilityHelper
instance Finalizable CDefaultProbabilityHelper where finalize = qlFreeDefaultProbabilityHelper
peekDefaultProbabilityHelper :: Ptr CDefaultProbabilityHelper -> IO DefaultProbabilityHelper
peekDefaultProbabilityHelper = DefaultProbabilityHelper <.> peekStandalone
withDefaultProbabilityHelper :: DefaultProbabilityHelper -> (Ptr CDefaultProbabilityHelper -> IO b) -> IO b
withDefaultProbabilityHelper = withStandalone . getCDefaultProbabilityHelper
withDefaultProbabilityHelperArray :: [DefaultProbabilityHelper] -> ((CUInt, Ptr (Ptr CDefaultProbabilityHelper)) -> IO b) -> IO b
withDefaultProbabilityHelperArray = withStandaloneArray getCDefaultProbabilityHelper

data CPathGenerator
newtype PathGenerator = PathGenerator {getCPathGenerator :: Standalone CPathGenerator}
foreign import ccall "ql.h &qlFreePathGenerator" qlFreePathGenerator :: FinalizerPtr CPathGenerator
instance Finalizable CPathGenerator where finalize = qlFreePathGenerator
peekPathGenerator :: Ptr CPathGenerator -> IO PathGenerator
peekPathGenerator = PathGenerator <.> peekStandalone
withPathGenerator :: PathGenerator -> (Ptr CPathGenerator -> IO b) -> IO b
withPathGenerator = withStandalone . getCPathGenerator

data CSamplePath
newtype SamplePath = SamplePath {getCSamplePath :: Standalone CSamplePath}
foreign import ccall "ql.h &qlFreeSamplePath" qlFreeSamplePath :: FinalizerPtr CSamplePath
instance Finalizable CSamplePath where finalize = qlFreeSamplePath
peekSamplePath :: Ptr CSamplePath -> IO SamplePath
peekSamplePath = SamplePath <.> peekStandalone
withSamplePath :: SamplePath -> (Ptr CSamplePath -> IO b) -> IO b
withSamplePath = withStandalone . getCSamplePath

-- special cases: those types will be represented as enums so no need to wrap them
data CQlClaim
type QlClaim = Standalone CQlClaim
foreign import ccall "ql.h &qlFreeClaim" qlFreeClaim :: FinalizerPtr CQlClaim
instance Finalizable CQlClaim where finalize = qlFreeClaim
peekClaim :: Ptr CQlClaim -> IO (Standalone CQlClaim)
peekClaim = peekStandalone

data CQlCallability
type QlCallability = Standalone CQlCallability
foreign import ccall "ql.h &qlFreeCallability" qlFreeCallability :: FinalizerPtr CQlCallability
instance Finalizable CQlCallability where finalize = qlFreeCallability
peekCallability :: Ptr CQlCallability -> IO (Standalone CQlCallability)
peekCallability = peekStandalone

data CConstraint
type QlConstraint = Standalone CConstraint
foreign import ccall "ql.h &qlFreeConstraint" qlFreeConstraint :: FinalizerPtr CConstraint
instance Finalizable CConstraint where finalize = qlFreeConstraint
peekConstraint :: Ptr CConstraint -> IO (Standalone CConstraint)
peekConstraint = peekStandalone

data CEndCriteria
type QlEndCriteria = Standalone CEndCriteria
foreign import ccall "ql.h &qlFreeEndCriteria" qlFreeEndCriteria :: FinalizerPtr CEndCriteria
instance Finalizable CEndCriteria where finalize = qlFreeEndCriteria
peekEndCriteria :: Ptr CEndCriteria -> IO (Standalone CEndCriteria)
peekEndCriteria = peekStandalone

data CFdmSchemeDesc
type QlFdmSchemeDesc = Standalone CFdmSchemeDesc
foreign import ccall "ql.h &qlFreeFdmSchemeDesc" qlFreeFdmSchemeDesc :: FinalizerPtr CFdmSchemeDesc
instance Finalizable CFdmSchemeDesc where finalize = qlFreeFdmSchemeDesc
peekFdmSchemeDesc :: Ptr CFdmSchemeDesc -> IO (Standalone CFdmSchemeDesc)
peekFdmSchemeDesc = peekStandalone

data CFittedBondDiscountCurveFittingMethod
type QlFittedBondDiscountCurveFittingMethod = Standalone CFittedBondDiscountCurveFittingMethod
foreign import ccall "ql.h &qlFreeFittedBondDiscountCurveFittingMethod" qlFreeFittedBondDiscountCurveFittingMethod :: FinalizerPtr CFittedBondDiscountCurveFittingMethod
instance Finalizable CFittedBondDiscountCurveFittingMethod where finalize = qlFreeFittedBondDiscountCurveFittingMethod
peekFittedBondDiscountCurveFittingMethod :: Ptr CFittedBondDiscountCurveFittingMethod -> IO (Standalone CFittedBondDiscountCurveFittingMethod)
peekFittedBondDiscountCurveFittingMethod = peekStandalone

data COptimizationMethod
type QlOptimizationMethod = Standalone COptimizationMethod
foreign import ccall "ql.h &qlFreeOptimizationMethod" qlFreeOptimizationMethod :: FinalizerPtr COptimizationMethod
instance Finalizable COptimizationMethod where finalize = qlFreeOptimizationMethod
peekOptimizationMethod :: Ptr COptimizationMethod -> IO (Standalone COptimizationMethod)
peekOptimizationMethod = peekStandalone

data CRounding
type QlRounding = Standalone CRounding
foreign import ccall "ql.h &qlFreeRounding" qlFreeRounding :: FinalizerPtr CRounding
instance Finalizable CRounding where finalize = qlFreeRounding
peekRounding :: Ptr CRounding -> IO (Standalone CRounding)
peekRounding = peekStandalone

data CLmCorrelationModel
type QlLmCorrelationModel = Standalone CLmCorrelationModel
foreign import ccall "ql.h &qlFreeLmCorrelationModel" qlFreeLmCorrelationModel :: FinalizerPtr CLmCorrelationModel
instance Finalizable CLmCorrelationModel where finalize = qlFreeLmCorrelationModel
peekLmCorrelationModel :: Ptr CLmCorrelationModel -> IO (Standalone CLmCorrelationModel)
peekLmCorrelationModel = peekStandalone

data CLmVolatilityModel
type QlLmVolatilityModel = Standalone CLmVolatilityModel
foreign import ccall "ql.h &qlFreeLmVolatilityModel" qlFreeLmVolatilityModel :: FinalizerPtr CLmVolatilityModel
instance Finalizable CLmVolatilityModel where finalize = qlFreeLmVolatilityModel
peekLmVolatilityModel :: Ptr CLmVolatilityModel -> IO (Standalone CLmVolatilityModel)
peekLmVolatilityModel = peekStandalone

-- TYPE HIERARCHIES
newtype Meta a = Meta (FinalizerPtr a)
class Finalizable a where
  finalize :: FinalizerPtr a
data Upcast a p = Upcast {_upcast :: Ptr a -> IO (Ptr p), _baseFinalizer :: FinalizerPtr p}
-- we can infer upcast just from two types, actually we don't need to drag it around with the cast function
data GenObject a p = GenObject {_ptr :: !(ForeignPtr a), _meta :: !(Upcast a p)}
upcast :: Meta p -> Upcast p p -> GenObject a p -> IO (GenObject p p)
upcast m u (GenObject p (Upcast k _)) = withForeignPtr p (k >=> peekObject m u)
peekObject :: Meta a -> Upcast a p -> Ptr a -> IO (GenObject a p)
peekObject (Meta f) u p = newForeignPtr f p <&> (`GenObject` u)
withObject :: GenObject a p -> (Ptr a -> IO b) -> IO b
withObject (GenObject p _) = withForeignPtr p
withObjectArray :: [GenObject a p] -> ((CUInt, Ptr (Ptr a)) -> IO b) -> IO b
withObjectArray x f = withMany withObject x (`withArray` (\px -> f (fromIntegral $ length x, px)))
-- TODO: OPTIMIZE: call the finalizer without creating a temp foreign ptr
withDescendant :: GenObject a p -> (Ptr p -> IO b) -> IO b
withDescendant (GenObject p (Upcast k fi)) f =
    withForeignPtr p (k >=>
      if fi /= nullFunPtr
        then newForeignPtr fi >=> (`withForeignPtr` f)
        else f)
withMaybeDescendant :: Maybe (GenObject a p) -> (Ptr p -> IO b) -> IO b
withMaybeDescendant x f = maybe (f nullPtr) (`withDescendant` f) x
withDescendantArray :: [GenObject a p] -> ((CUInt, Ptr (Ptr p)) -> IO b) -> IO b
withDescendantArray x f = withMany withDescendant x (`withArray` (\px -> f (fromIntegral $ length x, px)))
withDescendantArrayRaw :: [GenObject a p] -> (Ptr (Ptr p) -> IO b) -> IO b
withDescendantArrayRaw x f = withMany withDescendant x (`withArray` f)

---- Attempt at type classes. So far it pollutes all usages with ~ etc
--class Upcastable a where
--  type Parent a :: Type
--  upc :: Ptr a -> IO (Ptr (Parent a))
--  root :: Ptr a -> Bool
--data GenObject2 a = GenObject2 {_ptr :: !(ForeignPtr a)}
--upcast2 :: (Upcastable a, Finalizable (Parent a)) =>  GenObject2 a -> IO (GenObject2 (Parent a))
--upcast2 (GenObject2 p) = withForeignPtr p (upc >=> peekObject2)
--peekObject2 :: Finalizable a => Ptr a -> IO (GenObject2 a)
--peekObject2 p = newForeignPtr finalize p <&> GenObject2
--withObject2 :: GenObject2 a -> (Ptr a -> IO b) -> IO b
--withObject2 (GenObject2 p) = withForeignPtr p
--withObject2Array :: [GenObject2 a] -> ((CUInt, Ptr (Ptr a)) -> IO b) -> IO b
--withObject2Array x f = withMany withObject2 x (`withArray` (\px -> f (fromIntegral $ length x, px)))
--withDescendant2 :: (Upcastable a, Finalizable (Parent a), Upcastable (Parent a)) => GenObject2 a -> (Ptr (Parent a) -> IO b) -> IO b
--withDescendant2 (GenObject2 p) f =
--    withForeignPtr p (\x -> do
--      u <- upc x
--      if not $ root u
--        then newForeignPtr finalize u >>= (`withForeignPtr` f)
--        else f u)
--withMaybeDescendant2 :: (Upcastable a, Upcastable (Parent a), Finalizable (Parent a)) => Maybe (GenObject2 a) -> (Ptr (Parent a) -> IO b) -> IO b
--withMaybeDescendant2 x f = maybe (f nullPtr) (`withDescendant2` f) x
--withDescendant2Array :: (Upcastable a, Upcastable (Parent a), Finalizable (Parent a)) => [GenObject2 a] -> ((CUInt, Ptr (Ptr (Parent a))) -> IO b) -> IO b
--withDescendant2Array x f = withMany withDescendant2 x (`withArray` (\px -> f (fromIntegral $ length x, px)))
--withDescendant2ArrayRaw :: (Upcastable a, Upcastable (Parent a), Finalizable (Parent a)) => [GenObject2 a] -> (Ptr (Ptr (Parent a)) -> IO b) -> IO b
--withDescendant2ArrayRaw x f = withMany withDescendant2 x (`withArray` f)

--data CQuote
--data CSimpleQuote
--instance Upcastable CSimpleQuote where
--  type Parent CSimpleQuote = CQuote
--  upc = qlSimpleQuoteAsQuote
--  root = const False
--instance Upcastable CQuote where
--  type Parent CQuote = CQuote
--  upc = return
--  root = const True
--instance Finalizable CSimpleQuote where
--  finalize = qlFreeSimpleQuote
--instance Finalizable CQuote where
--  finalize = qlFreeQuote
--newtype GenQuote a = GenQuote {getQuote :: GenObject2 a}
--type Quote = GenQuote CQuote
--type SimpleQuote = GenQuote CSimpleQuote
--foreign import ccall "ql.h &qlFreeQuote" qlFreeQuote :: FinalizerPtr CQuote
--foreign import ccall "ql.h &qlFreeSimpleQuote" qlFreeSimpleQuote :: FinalizerPtr CSimpleQuote
--foreign import ccall safe "ql.h qlSimpleQuoteAsQuote" qlSimpleQuoteAsQuote :: Ptr CSimpleQuote -> IO (Ptr CQuote)
---- Haskell does not allow function arguments like [forall a.GenQuote a]
---- let's at least provide a way to convert all quote classes to the most generic one
--asQuote :: (Parent a ~ CQuote, Upcastable a) => GenQuote a -> IO Quote
--asQuote (GenQuote q) = GenQuote <$> upcast2 q
--peekQuote :: Ptr CQuote -> IO (GenQuote CQuote)
--peekQuote p = GenQuote <$> peekObject2 p
--withQuote :: (Parent a ~ CQuote, Upcastable a) => GenQuote a -> (Ptr CQuote -> IO b) -> IO b
--withQuote = withDescendant2 . getQuote
--withMaybeQuote :: (Parent a ~ CQuote, Upcastable a) => Maybe (GenQuote a) -> (Ptr CQuote -> IO b) -> IO b
--withMaybeQuote x = withMaybeDescendant2 (getQuote <$> x)
--withQuoteArray :: (Parent a ~ CQuote, Upcastable a) => [GenQuote a] -> ((CUInt, Ptr (Ptr CQuote)) -> IO b) -> IO b
--withQuoteArray x = withDescendant2Array (map getQuote x)
--withQuoteArrayRaw :: (Parent a ~ CQuote, Upcastable a) => [GenQuote a] -> (Ptr (Ptr CQuote) -> IO b) -> IO b
--withQuoteArrayRaw x = withDescendant2ArrayRaw (map getQuote x)
--peekSimpleQuote :: Ptr CSimpleQuote -> IO (GenQuote CSimpleQuote)
--peekSimpleQuote = GenQuote <.> peekObject2
--withSimpleQuote :: GenQuote CSimpleQuote -> (Ptr CSimpleQuote-> IO b) -> IO b
--withSimpleQuote = withObject2 . getQuote

data CQuote
data CSimpleQuote
newtype GenQuote a = GenQuote {getQuote :: GenObject a CQuote}
type Quote = GenQuote CQuote
type SimpleQuote = GenQuote CSimpleQuote
foreign import ccall "ql.h &qlFreeQuote" qlFreeQuote :: FinalizerPtr CQuote
foreign import ccall "ql.h &qlFreeSimpleQuote" qlFreeSimpleQuote :: FinalizerPtr CSimpleQuote
metaQuote :: Meta CQuote
metaQuote = Meta qlFreeQuote
metaSimpleQuote :: Meta CSimpleQuote
metaSimpleQuote = Meta qlFreeSimpleQuote
upcastQuote :: Upcast CQuote CQuote
upcastQuote = Upcast return nullFunPtr
foreign import ccall safe "ql.h qlSimpleQuoteAsQuote" qlSimpleQuoteAsQuote :: Ptr CSimpleQuote -> IO (Ptr CQuote)
upcastSimpleQuote :: Upcast CSimpleQuote CQuote
upcastSimpleQuote = Upcast qlSimpleQuoteAsQuote qlFreeQuote
-- Haskell does not allow function arguments like [forall a.GenQuote a]
-- let's at least provide a way to convert all quote classes to the most generic one
asQuote :: GenQuote a -> IO Quote
asQuote (GenQuote q) = GenQuote <$> upcast metaQuote upcastQuote q
peekQuote :: Ptr CQuote -> IO (GenQuote CQuote)
peekQuote p = GenQuote <$> peekObject metaQuote upcastQuote p
withQuote :: GenQuote a -> (Ptr CQuote -> IO b) -> IO b
withQuote = withDescendant . getQuote
withMaybeQuote :: Maybe (GenQuote a) -> (Ptr CQuote -> IO b) -> IO b
withMaybeQuote x = withMaybeDescendant (getQuote <$> x)
withQuoteArray :: [GenQuote a] -> ((CUInt, Ptr (Ptr CQuote)) -> IO b) -> IO b
withQuoteArray x = withDescendantArray (map getQuote x)
withQuoteArrayRaw :: [GenQuote a] -> (Ptr (Ptr CQuote) -> IO b) -> IO b
withQuoteArrayRaw x = withDescendantArrayRaw (map getQuote x)
peekSimpleQuote :: Ptr CSimpleQuote -> IO (GenQuote CSimpleQuote)
peekSimpleQuote = GenQuote <.> peekObject metaSimpleQuote upcastSimpleQuote
withSimpleQuote :: GenQuote CSimpleQuote -> (Ptr CSimpleQuote-> IO b) -> IO b
withSimpleQuote = withObject . getQuote

data CLeg
data CCouponLeg
newtype GenLeg a = GenLeg {getLeg :: GenObject a CLeg}
type Leg = GenLeg CLeg
type CouponLeg = GenLeg CCouponLeg
foreign import ccall "ql.h &qlFreeLeg" qlFreeLeg :: FinalizerPtr CLeg
foreign import ccall "ql.h &qlFreeCouponLeg" qlFreeCouponLeg :: FinalizerPtr CCouponLeg
metaLeg :: Meta CLeg
metaLeg = Meta qlFreeLeg
metaCouponLeg :: Meta CCouponLeg
metaCouponLeg = Meta qlFreeCouponLeg
upcastLeg :: Upcast CLeg CLeg
upcastLeg = Upcast return nullFunPtr
foreign import ccall safe "ql.h qlCouponLegAsLeg" qlCouponLegAsLeg :: Ptr CCouponLeg -> IO (Ptr CLeg)
upcastCouponLeg :: Upcast CCouponLeg CLeg
upcastCouponLeg = Upcast qlCouponLegAsLeg qlFreeLeg
asLeg :: GenLeg a -> IO Leg
asLeg (GenLeg q) = GenLeg <$> upcast metaLeg upcastLeg q
peekLeg :: Ptr CLeg -> IO Leg
peekLeg = GenLeg <.> peekObject metaLeg upcastLeg
withLeg :: GenLeg a -> (Ptr CLeg -> IO b) -> IO b
withLeg = withDescendant . getLeg
withLegArray :: [GenLeg a] -> ((CUInt, Ptr (Ptr CLeg)) -> IO b) -> IO b
withLegArray x = withDescendantArray (map getLeg x)
peekCouponLeg :: Ptr CCouponLeg -> IO (GenLeg CCouponLeg)
peekCouponLeg = GenLeg <.> peekObject metaCouponLeg upcastCouponLeg
withCouponLeg :: GenLeg CCouponLeg -> (Ptr CCouponLeg-> IO b) -> IO b
withCouponLeg = withObject . getLeg

data CRateHelper
data CBondHelper
data CSwapRateHelper
data COISRateHelper
newtype GenRateHelper a = GenRateHelper {getRateHelper :: GenObject a CRateHelper}
type RateHelper = GenRateHelper CRateHelper
type BondHelper = GenRateHelper CBondHelper
type SwapRateHelper = GenRateHelper CSwapRateHelper
type OISRateHelper = GenRateHelper COISRateHelper
foreign import ccall "ql.h &qlFreeRateHelper" qlFreeRateHelper :: FinalizerPtr CRateHelper
foreign import ccall "ql.h &qlFreeBondHelper" qlFreeBondHelper :: FinalizerPtr CBondHelper
foreign import ccall "ql.h &qlFreeSwapRateHelper" qlFreeSwapRateHelper :: FinalizerPtr CSwapRateHelper
foreign import ccall "ql.h &qlFreeOISRateHelper" qlFreeOISRateHelper :: FinalizerPtr COISRateHelper
metaRateHelper :: Meta CRateHelper
metaRateHelper = Meta qlFreeRateHelper
metaBondHelper :: Meta CBondHelper
metaBondHelper = Meta qlFreeBondHelper
metaSwapRateHelper :: Meta CSwapRateHelper
metaSwapRateHelper = Meta qlFreeSwapRateHelper
metaOISRateHelper :: Meta COISRateHelper
metaOISRateHelper = Meta qlFreeOISRateHelper
upcastRateHelper :: Upcast CRateHelper CRateHelper
upcastRateHelper = Upcast return nullFunPtr
foreign import ccall safe "ql.h qlBondHelperAsRateHelper" qlBondHelperAsRateHelper :: Ptr CBondHelper -> IO (Ptr CRateHelper)
upcastBondHelper :: Upcast CBondHelper CRateHelper
upcastBondHelper = Upcast qlBondHelperAsRateHelper qlFreeRateHelper
foreign import ccall safe "ql.h qlSwapRateHelperAsRateHelper" qlSwapRateHelperAsRateHelper :: Ptr CSwapRateHelper -> IO (Ptr CRateHelper)
upcastSwapRateHelper :: Upcast CSwapRateHelper CRateHelper
upcastSwapRateHelper = Upcast qlSwapRateHelperAsRateHelper qlFreeRateHelper
foreign import ccall safe "ql.h qlOISRateHelperAsRateHelper" qlOISRateHelperAsRateHelper :: Ptr COISRateHelper -> IO (Ptr CRateHelper)
upcastOISRateHelper :: Upcast COISRateHelper CRateHelper
upcastOISRateHelper = Upcast qlOISRateHelperAsRateHelper qlFreeRateHelper
asRateHelper :: GenRateHelper a -> IO (GenRateHelper CRateHelper)
asRateHelper (GenRateHelper q) = GenRateHelper <$> upcast metaRateHelper upcastRateHelper q
peekRateHelper :: Ptr CRateHelper -> IO (GenRateHelper CRateHelper)
peekRateHelper = GenRateHelper <.> peekObject metaRateHelper upcastRateHelper
withRateHelper :: GenRateHelper a -> (Ptr CRateHelper -> IO b) -> IO b
withRateHelper = withDescendant . getRateHelper
withRateHelperArray :: [GenRateHelper a] -> ((CUInt, Ptr (Ptr CRateHelper)) -> IO b) -> IO b
withRateHelperArray x = withDescendantArray (map getRateHelper x)
peekBondHelper :: Ptr CBondHelper -> IO (GenRateHelper CBondHelper)
peekBondHelper = GenRateHelper <.> peekObject metaBondHelper upcastBondHelper
withBondHelper :: GenRateHelper CBondHelper -> (Ptr CBondHelper-> IO b) -> IO b
withBondHelper = withObject . getRateHelper
withBondHelperArray :: [BondHelper] -> ((CUInt, Ptr (Ptr CBondHelper)) -> IO b) -> IO b
withBondHelperArray x = withObjectArray (map getRateHelper x)
peekSwapRateHelper :: Ptr CSwapRateHelper -> IO (GenRateHelper CSwapRateHelper)
peekSwapRateHelper = GenRateHelper <.> peekObject metaSwapRateHelper upcastSwapRateHelper
withSwapRateHelper :: GenRateHelper CSwapRateHelper -> (Ptr CSwapRateHelper-> IO b) -> IO b
withSwapRateHelper = withObject . getRateHelper
peekOISRateHelper :: Ptr COISRateHelper -> IO (GenRateHelper COISRateHelper)
peekOISRateHelper = GenRateHelper <.> peekObject metaOISRateHelper upcastOISRateHelper
withOISRateHelper :: GenRateHelper COISRateHelper -> (Ptr COISRateHelper-> IO b) -> IO b
withOISRateHelper = withObject . getRateHelper

data CCalibrationHelper
data CBlackCalibrationHelper
newtype GenCalibrationHelper a = GenCalibrationHelper {getCalibrationHelper :: GenObject a CCalibrationHelper}
type CalibrationHelper = GenCalibrationHelper CCalibrationHelper
type BlackCalibrationHelper = GenCalibrationHelper CBlackCalibrationHelper
foreign import ccall "ql.h &qlFreeCalibrationHelper" qlFreeCalibrationHelper :: FinalizerPtr CCalibrationHelper
foreign import ccall "ql.h &qlFreeBlackCalibrationHelper" qlFreeBlackCalibrationHelper :: FinalizerPtr CBlackCalibrationHelper
metaCalibrationHelper :: Meta CCalibrationHelper
metaCalibrationHelper = Meta qlFreeCalibrationHelper
metaBlackCalibrationHelper :: Meta CBlackCalibrationHelper
metaBlackCalibrationHelper = Meta qlFreeBlackCalibrationHelper
foreign import ccall safe "ql.h qlBlackCalibrationHelperAsCalibrationHelper" qlBlackCalibrationHelperAsCalibrationHelper :: Ptr CBlackCalibrationHelper -> IO (Ptr CCalibrationHelper)
upcastCalibrationHelper :: Upcast CCalibrationHelper CCalibrationHelper
upcastCalibrationHelper = Upcast return nullFunPtr
upcastBlackCalibrationHelper :: Upcast CBlackCalibrationHelper CCalibrationHelper
upcastBlackCalibrationHelper = Upcast qlBlackCalibrationHelperAsCalibrationHelper qlFreeCalibrationHelper
asCalibrationHelper :: GenCalibrationHelper a -> IO (GenCalibrationHelper CCalibrationHelper)
asCalibrationHelper (GenCalibrationHelper q) = GenCalibrationHelper <$> upcast metaCalibrationHelper upcastCalibrationHelper q
peekCalibrationHelper :: Ptr CCalibrationHelper -> IO (GenCalibrationHelper CCalibrationHelper)
peekCalibrationHelper = GenCalibrationHelper <.> peekObject metaCalibrationHelper upcastCalibrationHelper
withCalibrationHelper :: GenCalibrationHelper a -> (Ptr CCalibrationHelper -> IO b) -> IO b
withCalibrationHelper = withDescendant . getCalibrationHelper
withCalibrationHelperArray :: [GenCalibrationHelper a] -> ((CUInt, Ptr (Ptr CCalibrationHelper)) -> IO b) -> IO b
withCalibrationHelperArray x = withDescendantArray (map getCalibrationHelper x)
peekBlackCalibrationHelper :: Ptr CBlackCalibrationHelper -> IO (GenCalibrationHelper CBlackCalibrationHelper)
peekBlackCalibrationHelper = GenCalibrationHelper <.> peekObject metaBlackCalibrationHelper upcastBlackCalibrationHelper
withBlackCalibrationHelper :: GenCalibrationHelper CBlackCalibrationHelper -> (Ptr CBlackCalibrationHelper-> IO b) -> IO b
withBlackCalibrationHelper = withObject . getCalibrationHelper

data CBlackCalculator
data CBlackScholesCalculator
newtype GenBlackCalculator a = GenBlackCalculator {getBlackCalculator :: GenObject a CBlackCalculator}
type BlackCalculator = GenBlackCalculator CBlackCalculator
type BlackScholesCalculator = GenBlackCalculator CBlackScholesCalculator
foreign import ccall "ql.h &qlFreeBlackCalculator" qlFreeBlackCalculator :: FinalizerPtr CBlackCalculator
foreign import ccall "ql.h &qlFreeBlackScholesCalculator" qlFreeBlackScholesCalculator :: FinalizerPtr CBlackScholesCalculator
metaBlackCalculator :: Meta CBlackCalculator
metaBlackCalculator = Meta qlFreeBlackCalculator
metaBlackScholesCalculator :: Meta CBlackScholesCalculator
metaBlackScholesCalculator = Meta qlFreeBlackScholesCalculator
upcastBlackCalculator :: Upcast CBlackCalculator CBlackCalculator
upcastBlackCalculator = Upcast return nullFunPtr
foreign import ccall safe "ql.h qlBlackScholesCalculatorAsBlackCalculator" qlBlackScholesCalculatorAsBlackCalculator :: Ptr CBlackScholesCalculator -> IO (Ptr CBlackCalculator)
upcastBlackScholesCalculator :: Upcast CBlackScholesCalculator CBlackCalculator
upcastBlackScholesCalculator = Upcast qlBlackScholesCalculatorAsBlackCalculator qlFreeBlackCalculator
asBlackCalculator :: GenBlackCalculator a -> IO (GenBlackCalculator CBlackCalculator)
asBlackCalculator (GenBlackCalculator q) = GenBlackCalculator <$> upcast metaBlackCalculator upcastBlackCalculator q
peekBlackCalculator :: Ptr CBlackCalculator -> IO (GenBlackCalculator CBlackCalculator)
peekBlackCalculator = GenBlackCalculator <.> peekObject metaBlackCalculator upcastBlackCalculator
withBlackCalculator :: GenBlackCalculator a -> (Ptr CBlackCalculator -> IO b) -> IO b
withBlackCalculator = withDescendant . getBlackCalculator
peekBlackScholesCalculator :: Ptr CBlackScholesCalculator -> IO (GenBlackCalculator CBlackScholesCalculator)
peekBlackScholesCalculator = GenBlackCalculator <.> peekObject metaBlackScholesCalculator upcastBlackScholesCalculator
withBlackScholesCalculator :: GenBlackCalculator CBlackScholesCalculator -> (Ptr CBlackScholesCalculator-> IO b) -> IO b
withBlackScholesCalculator = withObject . getBlackCalculator

-- MULTILEVEL HIERARCHIES
-- TODO get rid of implicit dictionary passing in favour of type classes
data GenForeignPtr a b = GenForeignPtr {_ptr :: !a, _marshal :: !(forall r. a -> (Ptr b -> IO r) -> IO r)}

withCastForeignPtr :: (t -> (Ptr a -> IO r) -> IO r) -> Upcast a b -> t -> (Ptr b -> IO r) -> IO r
withCastForeignPtr w (Upcast u _) p f = w p $ u >=> f
-- FIXME for some reason this definition, being more rigorous, leads to double free of the base object, Investigate!
--withCastForeignPtr w (Upcast u fi) p f = w p $ u >=> newForeignPtr fi >=> (`withForeignPtr` f)

withGenForeignPtr :: Upcast a b -> GenForeignPtr c a -> (Ptr b -> IO r) -> IO r
withGenForeignPtr u (GenForeignPtr p w) = withCastForeignPtr w u p

newGenForeignPtr :: Meta a -> Upcast a b -> Ptr a -> IO (GenForeignPtr (ForeignPtr a) b)
newGenForeignPtr (Meta f) u x = newForeignPtr f x <&> (`GenForeignPtr` withCastForeignPtr withForeignPtr u)

newCastForeignPtr :: Meta a -> Ptr a -> IO (GenForeignPtr (ForeignPtr a) a)
newCastForeignPtr (Meta f) x = newForeignPtr f x <&> (`GenForeignPtr` withForeignPtr)

data CIndex'
data CInterestRateIndex'
data CBMAIndex'
data CIborIndex'
data COvernightIndex'
data CSwapIndex'
data COvernightIndexedSwapIndex'
newtype GenIndex a = GenIndex (GenForeignPtr a CIndex')
-- extra encapsulation to hide ForeignPtr from users. I hope to find a cleaner solution, I feel like I'm using too many wrappers here
type CIndex = ForeignPtr CIndex'
type Index = GenIndex CIndex
newtype InterestRateIndexDescendant a = InterestRateIndexDescendant (GenForeignPtr a CInterestRateIndex')
type GenInterestRateIndex a = GenIndex (InterestRateIndexDescendant a)
type CInterestRateIndex = ForeignPtr CInterestRateIndex'
type InterestRateIndex = GenInterestRateIndex CInterestRateIndex
type CBMAIndex = ForeignPtr CBMAIndex'
type BMAIndex = GenInterestRateIndex CBMAIndex
newtype IborIndexDescendant a = IborIndexDescendant (GenForeignPtr a CIborIndex')
type GenIborIndex a = GenIndex (InterestRateIndexDescendant (IborIndexDescendant a))
type CIborIndex = ForeignPtr CIborIndex'
type IborIndex = GenIborIndex CIborIndex
type COvernightIndex = ForeignPtr COvernightIndex'
type OvernightIborIndex = GenIborIndex COvernightIndex
newtype SwapIndexDescendant a = SwapIndexDescendant (GenForeignPtr a CSwapIndex')
type GenSwapIndex a = GenIndex (InterestRateIndexDescendant (SwapIndexDescendant a))
type CSwapIndex = ForeignPtr CSwapIndex'
type SwapIndex = GenSwapIndex CSwapIndex
type COvernightIndexedSwapIndex = ForeignPtr COvernightIndexedSwapIndex'
type OvernightIndexedSwapIndex = GenSwapIndex COvernightIndexedSwapIndex
foreign import ccall "ql.h &qlFreeIndex" qlFreeIndex :: FinalizerPtr CIndex'
foreign import ccall "ql.h &qlFreeInterestRateIndex" qlFreeInterestRateIndex :: FinalizerPtr CInterestRateIndex'
foreign import ccall "ql.h &qlFreeBMAIndex" qlFreeBMAIndex :: FinalizerPtr CBMAIndex'
foreign import ccall "ql.h &qlFreeIborIndex" qlFreeIborIndex :: FinalizerPtr CIborIndex'
foreign import ccall "ql.h &qlFreeOvernightIndex" qlFreeOvernightIborIndex :: FinalizerPtr COvernightIndex'
foreign import ccall "ql.h &qlFreeSwapIndex" qlFreeSwapIndex :: FinalizerPtr CSwapIndex'
foreign import ccall "ql.h &qlFreeOvernightIndexedSwapIndex" qlFreeOvernightIndexedSwapIndex :: FinalizerPtr COvernightIndexedSwapIndex'
metaIndex :: Meta CIndex'
metaIndex = Meta qlFreeIndex
metaInterestRateIndex :: Meta CInterestRateIndex'
metaInterestRateIndex = Meta qlFreeInterestRateIndex
metaBMAIndex :: Meta CBMAIndex'
metaBMAIndex = Meta qlFreeBMAIndex
metaIborIndex :: Meta CIborIndex'
metaIborIndex = Meta qlFreeIborIndex
metaOvernightIborIndex :: Meta COvernightIndex'
metaOvernightIborIndex = Meta qlFreeOvernightIborIndex
metaSwapIndex :: Meta CSwapIndex'
metaSwapIndex = Meta qlFreeSwapIndex
metaOvernightIndexedSwapIndex :: Meta COvernightIndexedSwapIndex'
metaOvernightIndexedSwapIndex = Meta qlFreeOvernightIndexedSwapIndex
foreign import ccall "ql.h qlInterestRateIndexAsIndex" qlInterestRateIndexAsIndex :: Ptr CInterestRateIndex' -> IO (Ptr CIndex')
foreign import ccall "ql.h qlBMAIndexAsInterestRateIndex" qlBMAIndexAsInterestRateIndex :: Ptr CBMAIndex' -> IO (Ptr CInterestRateIndex')
foreign import ccall "ql.h qlIborIndexAsInterestRateIndex" qlIborIndexAsInterestRateIndex :: Ptr CIborIndex' -> IO (Ptr CInterestRateIndex')
foreign import ccall "ql.h qlOvernightIndexAsIborIndex" qlOvernightIndexAsIborIndex :: Ptr COvernightIndex' -> IO (Ptr CIborIndex')
foreign import ccall "ql.h qlSwapIndexAsInterestRateIndex" qlSwapIndexAsInterestRateIndex :: Ptr CSwapIndex' -> IO (Ptr CInterestRateIndex')
foreign import ccall "ql.h qlOvernightIndexedSwapIndexAsSwapIndex" qlOvernightIndexedSwapIndexAsSwapIndex :: Ptr COvernightIndexedSwapIndex' -> IO (Ptr CSwapIndex')
upcastInterestRateIndex :: Upcast CInterestRateIndex' CIndex'
upcastInterestRateIndex = Upcast qlInterestRateIndexAsIndex qlFreeIndex
upcastBMAIndex :: Upcast CBMAIndex' CInterestRateIndex'
upcastBMAIndex = Upcast qlBMAIndexAsInterestRateIndex qlFreeInterestRateIndex
upcastIborIndex :: Upcast CIborIndex' CInterestRateIndex'
upcastIborIndex = Upcast qlIborIndexAsInterestRateIndex qlFreeInterestRateIndex
upcastOvernightIndex :: Upcast COvernightIndex' CIborIndex'
upcastOvernightIndex = Upcast qlOvernightIndexAsIborIndex qlFreeIborIndex
upcastSwapIndex :: Upcast CSwapIndex' CInterestRateIndex'
upcastSwapIndex = Upcast qlSwapIndexAsInterestRateIndex qlFreeInterestRateIndex
upcastOvernightIndexedSwapIndex :: Upcast COvernightIndexedSwapIndex' CSwapIndex'
upcastOvernightIndexedSwapIndex = Upcast qlOvernightIndexedSwapIndexAsSwapIndex qlFreeSwapIndex

asIndex :: GenIndex a -> IO Index
asIndex (GenIndex (GenForeignPtr x w)) = w x (GenIndex <.> newCastForeignPtr metaIndex)
withIndex :: GenIndex a -> (Ptr CIndex' -> IO b) -> IO b
withIndex (GenIndex (GenForeignPtr x w)) = w x

asInterestRateIndex :: GenInterestRateIndex a -> IO InterestRateIndex
asInterestRateIndex (GenIndex (GenForeignPtr (InterestRateIndexDescendant (GenForeignPtr x w)) _)) = w x peekInterestRateIndex
  where peekInterestRateIndex = newCastForeignPtr metaInterestRateIndex >=> newInterestRateIndexDescendant
withInterestRateIndex :: GenInterestRateIndex a -> (Ptr CInterestRateIndex' -> IO b) -> IO b
withInterestRateIndex (GenIndex (GenForeignPtr (InterestRateIndexDescendant (GenForeignPtr x w)) _)) = w x
withGenForeignInterestRateIndex :: InterestRateIndexDescendant a -> (Ptr CIndex' -> IO b) -> IO b
withGenForeignInterestRateIndex (InterestRateIndexDescendant o) = withGenForeignPtr upcastInterestRateIndex o
newInterestRateIndexDescendant :: GenForeignPtr a CInterestRateIndex' -> IO (GenIndex (InterestRateIndexDescendant a))
newInterestRateIndexDescendant p = GenIndex <^> GenForeignPtr (InterestRateIndexDescendant p) withGenForeignInterestRateIndex

peekBMAIndex :: Ptr CBMAIndex' -> IO BMAIndex
peekBMAIndex = newGenForeignPtr metaBMAIndex upcastBMAIndex >=> newInterestRateIndexDescendant
withBMAIndex :: BMAIndex -> (Ptr CBMAIndex' -> IO b) -> IO b
withBMAIndex (GenIndex (GenForeignPtr (InterestRateIndexDescendant (GenForeignPtr x _)) _)) = withForeignPtr x

asIborIndex :: GenIborIndex a -> IO IborIndex
asIborIndex (GenIndex (GenForeignPtr (InterestRateIndexDescendant (GenForeignPtr (IborIndexDescendant (GenForeignPtr x w)) _)) _)) = w x peekIborIndex
peekIborIndex :: Ptr CIborIndex' -> IO IborIndex
peekIborIndex = newCastForeignPtr metaIborIndex >=> newIborIndexDescendant
withIborIndex :: GenIborIndex a -> (Ptr CIborIndex' -> IO b) -> IO b
withIborIndex (GenIndex (GenForeignPtr (InterestRateIndexDescendant (GenForeignPtr (IborIndexDescendant (GenForeignPtr x w)) _)) _)) = w x
withGenForeignIborIndex :: IborIndexDescendant a -> (Ptr CInterestRateIndex' -> IO b) -> IO b
withGenForeignIborIndex (IborIndexDescendant o) = withGenForeignPtr upcastIborIndex o
newIborIndexDescendant :: GenForeignPtr a CIborIndex' -> IO (GenIborIndex a)
newIborIndexDescendant p = GenIndex <^> GenForeignPtr (InterestRateIndexDescendant $ GenForeignPtr (IborIndexDescendant p) withGenForeignIborIndex) withGenForeignInterestRateIndex

peekOvernightIborIndex :: Ptr COvernightIndex' -> IO OvernightIborIndex
peekOvernightIborIndex = newGenForeignPtr metaOvernightIborIndex upcastOvernightIndex >=> newIborIndexDescendant
withOvernightIborIndex :: OvernightIborIndex -> (Ptr COvernightIndex' -> IO b) -> IO b
withOvernightIborIndex (GenIndex (GenForeignPtr (InterestRateIndexDescendant (GenForeignPtr (IborIndexDescendant (GenForeignPtr x _)) _)) _)) = withForeignPtr x

asSwapIndex :: GenSwapIndex a -> IO SwapIndex
asSwapIndex (GenIndex (GenForeignPtr (InterestRateIndexDescendant (GenForeignPtr (SwapIndexDescendant (GenForeignPtr x w)) _)) _)) = w x peekSwapIndex
peekSwapIndex :: Ptr CSwapIndex' -> IO SwapIndex
peekSwapIndex = newCastForeignPtr metaSwapIndex >=> newSwapIndexDescendant
withSwapIndex :: GenSwapIndex a -> (Ptr CSwapIndex' -> IO b) -> IO b
withSwapIndex (GenIndex (GenForeignPtr (InterestRateIndexDescendant (GenForeignPtr (SwapIndexDescendant (GenForeignPtr x w)) _)) _)) = w x
withGenForeignSwapIndex :: SwapIndexDescendant a -> (Ptr CInterestRateIndex' -> IO b) -> IO b
withGenForeignSwapIndex (SwapIndexDescendant o) = withGenForeignPtr upcastSwapIndex o
newSwapIndexDescendant :: GenForeignPtr a CSwapIndex' -> IO (GenSwapIndex a)
newSwapIndexDescendant p = GenIndex <^> GenForeignPtr (InterestRateIndexDescendant $ GenForeignPtr (SwapIndexDescendant p) withGenForeignSwapIndex) withGenForeignInterestRateIndex

peekOvernightIndexedSwapIndex :: Ptr COvernightIndexedSwapIndex' -> IO OvernightIndexedSwapIndex
peekOvernightIndexedSwapIndex = newGenForeignPtr metaOvernightIndexedSwapIndex upcastOvernightIndexedSwapIndex >=> newSwapIndexDescendant
withOvernightIndexedSwapIndex :: OvernightIndexedSwapIndex -> (Ptr COvernightIndexedSwapIndex' -> IO b) -> IO b
withOvernightIndexedSwapIndex (GenIndex (GenForeignPtr (InterestRateIndexDescendant (GenForeignPtr (SwapIndexDescendant (GenForeignPtr x _)) _)) _)) = withForeignPtr x

data CTermStructure'
data CVolatilityTermStructure'
data COptionletVolatilityStructure'
data CSwaptionVolatilityStructure'
data CCapFloorTermVolSurface'
data CLocalVolTermStructure'
data CBlackVolTermStructure'
data CBlackVarianceCurve'
data CYieldTermStructure'
data CFittedBondDiscountCurve'
data CCallableBondVolatilityStructure'
data CDefaultProbabilityTermStructure'
newtype GenTermStructure a = GenTermStructure (GenForeignPtr a CTermStructure')
type CTermStructure = ForeignPtr CTermStructure'
type TermStructure = GenTermStructure CTermStructure
newtype YieldTermStructureDescendant a = YieldTermStructureDescendant (GenForeignPtr a CYieldTermStructure')
type GenYieldTermStructure a = GenTermStructure (YieldTermStructureDescendant a)
type CYieldTermStructure = ForeignPtr CYieldTermStructure'
type YieldTermStructure = GenYieldTermStructure CYieldTermStructure
type CFittedBondDiscountCurve = ForeignPtr CFittedBondDiscountCurve'
type FittedBondDiscountCurve = GenYieldTermStructure CFittedBondDiscountCurve
newtype VolatilityTermStructureDescendant a = VolatilityTermStructureDescendant (GenForeignPtr a CVolatilityTermStructure')
type GenVolatilityTermStructure a = GenTermStructure (VolatilityTermStructureDescendant a)
type CVolatilityTermStructure = ForeignPtr CVolatilityTermStructure'
type VolatilityTermStructure = GenVolatilityTermStructure CVolatilityTermStructure
type COptionletVolatilityStructure = ForeignPtr COptionletVolatilityStructure'
type OptionletVolatilityStructure = GenVolatilityTermStructure COptionletVolatilityStructure
type CCapFloorTermVolSurface = ForeignPtr CCapFloorTermVolSurface'
type CapFloorTermVolSurface = GenVolatilityTermStructure CCapFloorTermVolSurface
type CSwaptionVolatilityStructure = ForeignPtr CSwaptionVolatilityStructure'
type SwaptionVolatilityStructure = GenVolatilityTermStructure CSwaptionVolatilityStructure
type CLocalVolTermStructure = ForeignPtr CLocalVolTermStructure'
type LocalVolTermStructure = GenVolatilityTermStructure CLocalVolTermStructure
newtype BlackVolTermStructureDescendant a = BlackVolTermStructureDescendant (GenForeignPtr a CBlackVolTermStructure')
type GenBlackVolTermStructure a = GenTermStructure (VolatilityTermStructureDescendant (BlackVolTermStructureDescendant a))
type CBlackVolTermStructure = ForeignPtr CBlackVolTermStructure'
type BlackVolTermStructure = GenBlackVolTermStructure CBlackVolTermStructure
type CBlackVarianceCurve = ForeignPtr CBlackVarianceCurve'
type BlackVarianceCurve = GenBlackVolTermStructure CBlackVarianceCurve
type CCallableBondVolatilityStructure = ForeignPtr CCallableBondVolatilityStructure'
type CallableBondVolatilityStructure = GenTermStructure CCallableBondVolatilityStructure
type CDefaultProbabilityTermStructure = ForeignPtr CDefaultProbabilityTermStructure'
type DefaultProbabilityTermStructure = GenTermStructure CDefaultProbabilityTermStructure
foreign import ccall "ql.h &qlFreeTermStructure" qlFreeTermStructure :: FinalizerPtr CTermStructure'
foreign import ccall "ql.h &qlFreeVolatilityTermStructure" qlFreeVolatilityTermStructure :: FinalizerPtr CVolatilityTermStructure'
foreign import ccall "ql.h &qlFreeOptionletVolatilityStructure" qlFreeOptionletVolatilityStructure :: FinalizerPtr COptionletVolatilityStructure'
foreign import ccall "ql.h &qlFreeSwaptionVolatilityStructure" qlFreeSwaptionVolatilityStructure :: FinalizerPtr CSwaptionVolatilityStructure'
foreign import ccall "ql.h &qlFreeCapFloorTermVolSurface" qlFreeCapFloorTermVolSurface :: FinalizerPtr CCapFloorTermVolSurface'
foreign import ccall "ql.h &qlFreeLocalVolTermStructure" qlFreeLocalVolTermStructure :: FinalizerPtr CLocalVolTermStructure'
foreign import ccall "ql.h &qlFreeBlackVolTermStructure" qlFreeBlackVolTermStructure :: FinalizerPtr CBlackVolTermStructure'
foreign import ccall "ql.h &qlFreeBlackVarianceCurve" qlFreeBlackVarianceCurve :: FinalizerPtr CBlackVarianceCurve'
foreign import ccall "ql.h &qlFreeYieldTermStructure" qlFreeYieldTermStructure :: FinalizerPtr CYieldTermStructure'
foreign import ccall "ql.h &qlFreeFittedBondDiscountCurve" qlFreeFittedBondDiscountCurve :: FinalizerPtr CFittedBondDiscountCurve'
foreign import ccall "ql.h &qlFreeCallableBondVolatilityStructure" qlFreeCallableBondVolatilityStructure :: FinalizerPtr CCallableBondVolatilityStructure'
foreign import ccall "ql.h &qlFreeDefaultProbabilityTermStructure" qlFreeDefaultProbabilityTermStructure :: FinalizerPtr CDefaultProbabilityTermStructure'
metaTermStructure :: Meta CTermStructure'
metaTermStructure = Meta qlFreeTermStructure
metaVolatilityTermStructure :: Meta CVolatilityTermStructure'
metaVolatilityTermStructure = Meta qlFreeVolatilityTermStructure
metaOptionletVolatilityStructure :: Meta COptionletVolatilityStructure'
metaOptionletVolatilityStructure = Meta qlFreeOptionletVolatilityStructure
metaSwaptionVolatilityStructure :: Meta CSwaptionVolatilityStructure'
metaSwaptionVolatilityStructure = Meta qlFreeSwaptionVolatilityStructure
metaCapFloorTermVolSurface :: Meta CCapFloorTermVolSurface'
metaCapFloorTermVolSurface = Meta qlFreeCapFloorTermVolSurface
metaLocalVolTermStructure :: Meta CLocalVolTermStructure'
metaLocalVolTermStructure = Meta qlFreeLocalVolTermStructure
metaBlackVolTermStructure :: Meta CBlackVolTermStructure'
metaBlackVolTermStructure = Meta qlFreeBlackVolTermStructure
metaBlackVarianceCurve :: Meta CBlackVarianceCurve'
metaBlackVarianceCurve = Meta qlFreeBlackVarianceCurve
metaYieldTermStructure :: Meta CYieldTermStructure'
metaYieldTermStructure = Meta qlFreeYieldTermStructure
metaFittedBondDiscountCurve :: Meta CFittedBondDiscountCurve'
metaFittedBondDiscountCurve = Meta qlFreeFittedBondDiscountCurve
metaCallableBondVolatilityStructure :: Meta CCallableBondVolatilityStructure'
metaCallableBondVolatilityStructure = Meta qlFreeCallableBondVolatilityStructure
metaDefaultProbabilityTermStructure :: Meta CDefaultProbabilityTermStructure'
metaDefaultProbabilityTermStructure = Meta qlFreeDefaultProbabilityTermStructure
foreign import ccall "ql.h qlYieldTermStructureAsTermStructure" qlYieldTermStructureAsTermStructure :: Ptr CYieldTermStructure' -> IO (Ptr CTermStructure')
foreign import ccall "ql.h qlFittedBondDiscountCurveAsYieldTermStructure" qlFittedBondDiscountCurveAsYieldTermStructure :: Ptr CFittedBondDiscountCurve' -> IO (Ptr CYieldTermStructure')
foreign import ccall "ql.h qlVolatilityTermStructureAsTermStructure" qlVolatilityTermStructureAsTermStructure :: Ptr CVolatilityTermStructure' -> IO (Ptr CTermStructure')
foreign import ccall "ql.h qlOptionletVolatilityStructureAsVolatilityTermStructure" qlOptionletVolatilityStructureAsVolatilityTermStructure :: Ptr COptionletVolatilityStructure' -> IO (Ptr CVolatilityTermStructure')
foreign import ccall "ql.h qlBlackVolTermStructureAsVolatilityTermStructure" qlBlackVolTermStructureAsVolatilityTermStructure :: Ptr CBlackVolTermStructure' -> IO (Ptr CVolatilityTermStructure')
foreign import ccall "ql.h qlBlackVarianceCurveAsBlackVolTermStructure" qlBlackVarianceCurveAsBlackVolTermStructure :: Ptr CBlackVarianceCurve' -> IO (Ptr CBlackVolTermStructure')
foreign import ccall "ql.h qlSwaptionVolatilityStructureAsVolatilityTermStructure" qlSwaptionVolatilityStructureAsVolatilityTermStructure :: Ptr CSwaptionVolatilityStructure' -> IO (Ptr CVolatilityTermStructure')
foreign import ccall "ql.h qlCapFloorTermVolSurfaceAsVolatilityTermStructure" qlCapFloorTermVolSurfaceAsVolatilityTermStructure :: Ptr CCapFloorTermVolSurface' -> IO (Ptr CVolatilityTermStructure')
foreign import ccall "ql.h qlLocalVolTermStructureAsVolatilityTermStructure" qlLocalVolTermStructureAsVolatilityTermStructure :: Ptr CLocalVolTermStructure' -> IO (Ptr CVolatilityTermStructure')
foreign import ccall "ql.h qlCallableBondVolatilityStructureAsTermStructure" qlCallableBondVolatilityStructureAsTermStructure :: Ptr CCallableBondVolatilityStructure' -> IO (Ptr CTermStructure')
foreign import ccall "ql.h qlDefaultProbabilityTermStructureAsTermStructure" qlDefaultProbabilityTermStructureAsTermStructure :: Ptr CDefaultProbabilityTermStructure' -> IO (Ptr CTermStructure')
upcastYieldTermStructure :: Upcast CYieldTermStructure' CTermStructure'
upcastYieldTermStructure = Upcast qlYieldTermStructureAsTermStructure qlFreeTermStructure
upcastFittedBondDiscountCurve :: Upcast CFittedBondDiscountCurve' CYieldTermStructure'
upcastFittedBondDiscountCurve = Upcast qlFittedBondDiscountCurveAsYieldTermStructure qlFreeYieldTermStructure
upcastVolatilityTermStructure :: Upcast CVolatilityTermStructure' CTermStructure'
upcastVolatilityTermStructure = Upcast qlVolatilityTermStructureAsTermStructure qlFreeTermStructure
upcastCallableBondVolatilityStructure :: Upcast CCallableBondVolatilityStructure' CTermStructure'
upcastCallableBondVolatilityStructure = Upcast qlCallableBondVolatilityStructureAsTermStructure qlFreeTermStructure
upcastDefaultProbabilityTermStructure :: Upcast CDefaultProbabilityTermStructure' CTermStructure'
upcastDefaultProbabilityTermStructure = Upcast qlDefaultProbabilityTermStructureAsTermStructure qlFreeTermStructure
upcastBlackVolTermStructure :: Upcast CBlackVolTermStructure' CVolatilityTermStructure'
upcastBlackVolTermStructure = Upcast qlBlackVolTermStructureAsVolatilityTermStructure qlFreeVolatilityTermStructure
upcastBlackVarianceCurve :: Upcast CBlackVarianceCurve' CBlackVolTermStructure'
upcastBlackVarianceCurve = Upcast qlBlackVarianceCurveAsBlackVolTermStructure qlFreeBlackVolTermStructure
upcastOptionletVolatilityStructure :: Upcast COptionletVolatilityStructure' CVolatilityTermStructure'
upcastOptionletVolatilityStructure = Upcast qlOptionletVolatilityStructureAsVolatilityTermStructure qlFreeVolatilityTermStructure
upcastSwaptionVolatilityStructure :: Upcast CSwaptionVolatilityStructure' CVolatilityTermStructure'
upcastSwaptionVolatilityStructure = Upcast qlSwaptionVolatilityStructureAsVolatilityTermStructure qlFreeVolatilityTermStructure
upcastCapFloorTermVolSurface :: Upcast CCapFloorTermVolSurface' CVolatilityTermStructure'
upcastCapFloorTermVolSurface = Upcast qlCapFloorTermVolSurfaceAsVolatilityTermStructure qlFreeVolatilityTermStructure
upcastLocalVolTermStructure :: Upcast CLocalVolTermStructure' CVolatilityTermStructure'
upcastLocalVolTermStructure = Upcast qlLocalVolTermStructureAsVolatilityTermStructure qlFreeVolatilityTermStructure

asTermStructure :: GenTermStructure a -> IO TermStructure
asTermStructure (GenTermStructure (GenForeignPtr x w)) = w x (GenTermStructure <.> newCastForeignPtr metaTermStructure)
withTermStructure :: GenTermStructure a  -> (Ptr CTermStructure' -> IO b) -> IO b
withTermStructure (GenTermStructure (GenForeignPtr x w)) = w x
withTermStructureDescendant :: GenTermStructure (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withTermStructureDescendant (GenTermStructure (GenForeignPtr x _)) = withForeignPtr x

asVolatilityTermStructure :: GenVolatilityTermStructure a -> IO VolatilityTermStructure
asVolatilityTermStructure (GenTermStructure (GenForeignPtr (VolatilityTermStructureDescendant (GenForeignPtr x w)) _)) = w x peekVolatilityTermStructure
peekVolatilityTermStructure :: Ptr CVolatilityTermStructure' -> IO VolatilityTermStructure
peekVolatilityTermStructure = newCastForeignPtr metaVolatilityTermStructure >=> newVolatilityTermStructureDescendant
peekVolatilityTermStructureDescendant :: Meta a -> Upcast a CVolatilityTermStructure' -> Ptr a -> IO (GenVolatilityTermStructure (ForeignPtr a))
peekVolatilityTermStructureDescendant m u = newGenForeignPtr m u >=> newVolatilityTermStructureDescendant
withVolatilityTermStructure :: GenVolatilityTermStructure a -> (Ptr CVolatilityTermStructure' -> IO b) -> IO b
withVolatilityTermStructure (GenTermStructure (GenForeignPtr (VolatilityTermStructureDescendant (GenForeignPtr x w)) _)) = w x
marshalVolatilityTermStructure :: VolatilityTermStructureDescendant a -> (Ptr CTermStructure' -> IO b) -> IO b
marshalVolatilityTermStructure (VolatilityTermStructureDescendant o) = withGenForeignPtr upcastVolatilityTermStructure o
withVolatilityTermStructureDescendant :: GenVolatilityTermStructure (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
withVolatilityTermStructureDescendant (GenTermStructure (GenForeignPtr (VolatilityTermStructureDescendant (GenForeignPtr x _)) _)) = withForeignPtr x
newVolatilityTermStructureDescendant :: GenForeignPtr a CVolatilityTermStructure' -> IO (GenVolatilityTermStructure a)
newVolatilityTermStructureDescendant p = GenTermStructure <^> GenForeignPtr (VolatilityTermStructureDescendant p) marshalVolatilityTermStructure

asBlackVolTermStructure :: GenBlackVolTermStructure a -> IO BlackVolTermStructure
asBlackVolTermStructure (GenTermStructure (GenForeignPtr (VolatilityTermStructureDescendant (GenForeignPtr (BlackVolTermStructureDescendant (GenForeignPtr x w)) _)) _)) = w x peekBlackVolTermStructure
peekBlackVolTermStructure :: Ptr CBlackVolTermStructure' -> IO BlackVolTermStructure
peekBlackVolTermStructure = newCastForeignPtr metaBlackVolTermStructure >=> newBlackVolTermStructureDescendant
withBlackVolTermStructure :: GenBlackVolTermStructure a -> (Ptr CBlackVolTermStructure' -> IO b) -> IO b
withBlackVolTermStructure (GenTermStructure (GenForeignPtr (VolatilityTermStructureDescendant (GenForeignPtr (BlackVolTermStructureDescendant (GenForeignPtr x w)) _)) _)) = w x
marshalBlackVolTermStructure :: BlackVolTermStructureDescendant a -> (Ptr CVolatilityTermStructure' -> IO b) -> IO b
marshalBlackVolTermStructure (BlackVolTermStructureDescendant o) = withGenForeignPtr upcastBlackVolTermStructure o
newBlackVolTermStructureDescendant :: GenForeignPtr a CBlackVolTermStructure' -> IO (GenBlackVolTermStructure a)
newBlackVolTermStructureDescendant p = GenTermStructure <^> GenForeignPtr (VolatilityTermStructureDescendant $ GenForeignPtr (BlackVolTermStructureDescendant p) marshalBlackVolTermStructure) marshalVolatilityTermStructure

peekBlackVarianceCurve :: Ptr CBlackVarianceCurve' -> IO BlackVarianceCurve
peekBlackVarianceCurve = newGenForeignPtr metaBlackVarianceCurve upcastBlackVarianceCurve >=> newBlackVolTermStructureDescendant
withBlackVarianceCurve :: BlackVarianceCurve -> (Ptr CBlackVarianceCurve' -> IO b) -> IO b
withBlackVarianceCurve (GenTermStructure (GenForeignPtr (VolatilityTermStructureDescendant (GenForeignPtr (BlackVolTermStructureDescendant (GenForeignPtr x _)) _)) _)) = withForeignPtr x

peekOptionletVolatilityStructure :: Ptr COptionletVolatilityStructure' -> IO OptionletVolatilityStructure
peekOptionletVolatilityStructure = peekVolatilityTermStructureDescendant metaOptionletVolatilityStructure upcastOptionletVolatilityStructure
peekSwaptionVolatilityStructure :: Ptr CSwaptionVolatilityStructure' -> IO SwaptionVolatilityStructure
peekSwaptionVolatilityStructure = peekVolatilityTermStructureDescendant metaSwaptionVolatilityStructure upcastSwaptionVolatilityStructure
peekCapFloorTermVolSurface :: Ptr CCapFloorTermVolSurface' -> IO CapFloorTermVolSurface
peekCapFloorTermVolSurface = peekVolatilityTermStructureDescendant metaCapFloorTermVolSurface upcastCapFloorTermVolSurface
peekLocalVolTermStructure :: Ptr CLocalVolTermStructure' -> IO LocalVolTermStructure
peekLocalVolTermStructure = peekVolatilityTermStructureDescendant metaLocalVolTermStructure upcastLocalVolTermStructure
peekCallableBondVolatilityStructure :: Ptr CCallableBondVolatilityStructure' -> IO CallableBondVolatilityStructure
peekCallableBondVolatilityStructure = GenTermStructure <.> newGenForeignPtr metaCallableBondVolatilityStructure upcastCallableBondVolatilityStructure
peekDefaultProbabilityTermStructure :: Ptr CDefaultProbabilityTermStructure' -> IO DefaultProbabilityTermStructure
peekDefaultProbabilityTermStructure = GenTermStructure <.> newGenForeignPtr metaDefaultProbabilityTermStructure upcastDefaultProbabilityTermStructure

asYieldTermStructure :: GenYieldTermStructure a -> IO YieldTermStructure
asYieldTermStructure (GenTermStructure (GenForeignPtr (YieldTermStructureDescendant (GenForeignPtr x w)) _)) = w x peekYieldTermStructure
peekYieldTermStructure :: Ptr CYieldTermStructure' -> IO YieldTermStructure
peekYieldTermStructure = newCastForeignPtr metaYieldTermStructure >=> newYieldTermStructureDescendant
withYieldTermStructure :: GenYieldTermStructure a -> (Ptr CYieldTermStructure' -> IO b) -> IO b
withYieldTermStructure (GenTermStructure (GenForeignPtr (YieldTermStructureDescendant (GenForeignPtr x w)) _)) = w x
withMaybeYieldTermStructure :: Maybe (GenYieldTermStructure a) -> (Ptr CYieldTermStructure' -> IO b) -> IO b
withMaybeYieldTermStructure x f = maybe (f nullPtr) (`withYieldTermStructure` f) x
marshalYieldTermStructure :: YieldTermStructureDescendant a -> (Ptr CTermStructure' -> IO b) -> IO b
marshalYieldTermStructure (YieldTermStructureDescendant o) = withGenForeignPtr upcastYieldTermStructure o
newYieldTermStructureDescendant :: GenForeignPtr a CYieldTermStructure' -> IO (GenYieldTermStructure a)
newYieldTermStructureDescendant p = GenTermStructure <^> GenForeignPtr (YieldTermStructureDescendant p) marshalYieldTermStructure

peekFittedBondDiscountCurve :: Ptr CFittedBondDiscountCurve' -> IO FittedBondDiscountCurve
peekFittedBondDiscountCurve = newGenForeignPtr metaFittedBondDiscountCurve upcastFittedBondDiscountCurve >=> newYieldTermStructureDescendant
withFittedBondDiscountCurve :: FittedBondDiscountCurve -> (Ptr CFittedBondDiscountCurve' -> IO b) -> IO b
withFittedBondDiscountCurve (GenTermStructure (GenForeignPtr (YieldTermStructureDescendant (GenForeignPtr x _)) _)) = withForeignPtr x

data CStochasticProcess'
data CExtOUWithJumpsProcess'
data CGJRGARCHProcess'
data CHybridHestonHullWhiteProcess'
data CKlugeExtOUProcess'
data CLiborForwardModelProcess'
data CStochasticProcessArray'
data CHestonProcess'
data CStochasticProcess1D'
data CBatesProcess'
data CExtendedOrnsteinUhlenbeckProcess'
data CHullWhiteForwardProcess'
data CHullWhiteProcess'
data CMerton76Process'
data CVarianceGammaProcess'
data CGeneralizedBlackScholesProcess'
data CBlackProcess'
newtype GenStochasticProcess a = GenStochasticProcess (GenForeignPtr a CStochasticProcess')
type CStochasticProcess = ForeignPtr CStochasticProcess'
type StochasticProcess = GenStochasticProcess CStochasticProcess
type CExtOUWithJumpsProcess = ForeignPtr CExtOUWithJumpsProcess'
type ExtOUWithJumpsProcess = GenStochasticProcess CExtOUWithJumpsProcess
type CGJRGARCHProcess = ForeignPtr CGJRGARCHProcess'
type GJRGARCHProcess = GenStochasticProcess CGJRGARCHProcess
type CHybridHestonHullWhiteProcess = ForeignPtr CHybridHestonHullWhiteProcess'
type HybridHestonHullWhiteProcess = GenStochasticProcess CHybridHestonHullWhiteProcess
type CKlugeExtOUProcess = ForeignPtr CKlugeExtOUProcess'
type KlugeExtOUProcess = GenStochasticProcess CKlugeExtOUProcess
type CLiborForwardModelProcess = ForeignPtr CLiborForwardModelProcess'
type LiborForwardModelProcess = GenStochasticProcess CLiborForwardModelProcess
type CStochasticProcessArray = ForeignPtr CStochasticProcessArray'
type StochasticProcessArray = GenStochasticProcess CStochasticProcessArray
newtype HestonProcessDescendant a = HestonProcessDescendant (GenForeignPtr a CHestonProcess')
type GenHestonProcess a = GenStochasticProcess (HestonProcessDescendant a)
type CHestonProcess = ForeignPtr CHestonProcess'
type HestonProcess = GenHestonProcess CHestonProcess
newtype StochasticProcess1DDescendant a = StochasticProcess1DDescendant (GenForeignPtr a CStochasticProcess1D')
type GenStochasticProcess1D a = GenStochasticProcess (StochasticProcess1DDescendant a)
type CStochasticProcess1D = ForeignPtr CStochasticProcess1D'
type StochasticProcess1D = GenStochasticProcess1D CStochasticProcess1D
type CMerton76Process = ForeignPtr CMerton76Process'
type Merton76Process = GenStochasticProcess1D CMerton76Process
type CVarianceGammaProcess = ForeignPtr CVarianceGammaProcess'
type VarianceGammaProcess = GenStochasticProcess1D CVarianceGammaProcess
newtype GeneralizedBlackScholesProcessDescendant a = GeneralizedBlackScholesProcessDescendant (GenForeignPtr a CGeneralizedBlackScholesProcess')
type GenGeneralizedBlackScholesProcess a = GenStochasticProcess (StochasticProcess1DDescendant (GeneralizedBlackScholesProcessDescendant a))
type CGeneralizedBlackScholesProcess = ForeignPtr CGeneralizedBlackScholesProcess'
type GeneralizedBlackScholesProcess = GenGeneralizedBlackScholesProcess CGeneralizedBlackScholesProcess
type CBlackProcess = ForeignPtr CBlackProcess'
type BlackProcess = GenGeneralizedBlackScholesProcess CBlackProcess
type CBatesProcess = ForeignPtr CBatesProcess'
type BatesProcess = GenHestonProcess CBatesProcess
type CHullWhiteProcess = ForeignPtr CHullWhiteProcess'
type HullWhiteProcess = GenStochasticProcess1D CHullWhiteProcess
type CHullWhiteForwardProcess = ForeignPtr CHullWhiteForwardProcess'
type HullWhiteForwardProcess = GenStochasticProcess1D CHullWhiteForwardProcess
type CExtendedOrnsteinUhlenbeckProcess = ForeignPtr CExtendedOrnsteinUhlenbeckProcess'
type ExtendedOrnsteinUhlenbeckProcess = GenStochasticProcess1D CExtendedOrnsteinUhlenbeckProcess
foreign import ccall "ql.h &qlFreeStochasticProcess" qlFreeStochasticProcess :: FinalizerPtr CStochasticProcess'
foreign import ccall "ql.h &qlFreeExtOUWithJumpsProcess" qlFreeExtOUWithJumpsProcess :: FinalizerPtr CExtOUWithJumpsProcess'
foreign import ccall "ql.h &qlFreeGJRGARCHProcess" qlFreeGJRGARCHProcess :: FinalizerPtr CGJRGARCHProcess'
foreign import ccall "ql.h &qlFreeHybridHestonHullWhiteProcess" qlFreeHybridHestonHullWhiteProcess :: FinalizerPtr CHybridHestonHullWhiteProcess'
foreign import ccall "ql.h &qlFreeKlugeExtOUProcess" qlFreeKlugeExtOUProcess :: FinalizerPtr CKlugeExtOUProcess'
foreign import ccall "ql.h &qlFreeLiborForwardModelProcess" qlFreeLiborForwardModelProcess :: FinalizerPtr CLiborForwardModelProcess'
foreign import ccall "ql.h &qlFreeStochasticProcessArray" qlFreeStochasticProcessArray :: FinalizerPtr CStochasticProcessArray'
foreign import ccall "ql.h &qlFreeHestonProcess" qlFreeHestonProcess :: FinalizerPtr CHestonProcess'
foreign import ccall "ql.h &qlFreeStochasticProcess1D" qlFreeStochasticProcess1D :: FinalizerPtr CStochasticProcess1D'
foreign import ccall "ql.h &qlFreeBatesProcess" qlFreeBatesProcess :: FinalizerPtr CBatesProcess'
foreign import ccall "ql.h &qlFreeExtendedOrnsteinUhlenbeckProcess" qlFreeExtendedOrnsteinUhlenbeckProcess :: FinalizerPtr CExtendedOrnsteinUhlenbeckProcess'
foreign import ccall "ql.h &qlFreeHullWhiteForwardProcess" qlFreeHullWhiteForwardProcess :: FinalizerPtr CHullWhiteForwardProcess'
foreign import ccall "ql.h &qlFreeHullWhiteProcess" qlFreeHullWhiteProcess :: FinalizerPtr CHullWhiteProcess'
foreign import ccall "ql.h &qlFreeMerton76Process" qlFreeMerton76Process :: FinalizerPtr CMerton76Process'
foreign import ccall "ql.h &qlFreeVarianceGammaProcess" qlFreeVarianceGammaProcess :: FinalizerPtr CVarianceGammaProcess'
foreign import ccall "ql.h &qlFreeGeneralizedBlackScholesProcess" qlFreeGeneralizedBlackScholesProcess :: FinalizerPtr CGeneralizedBlackScholesProcess'
foreign import ccall "ql.h &qlFreeBlackProcess" qlFreeBlackProcess :: FinalizerPtr CBlackProcess'
metaStochasticProcess :: Meta CStochasticProcess'
metaStochasticProcess = Meta qlFreeStochasticProcess
metaExtOUWithJumpsProcess :: Meta CExtOUWithJumpsProcess'
metaExtOUWithJumpsProcess = Meta qlFreeExtOUWithJumpsProcess
metaGJRGARCHProcess :: Meta CGJRGARCHProcess'
metaGJRGARCHProcess = Meta qlFreeGJRGARCHProcess
metaHybridHestonHullWhiteProcess :: Meta CHybridHestonHullWhiteProcess'
metaHybridHestonHullWhiteProcess = Meta qlFreeHybridHestonHullWhiteProcess
metaKlugeExtOUProcess :: Meta CKlugeExtOUProcess'
metaKlugeExtOUProcess = Meta qlFreeKlugeExtOUProcess
metaLiborForwardModelProcess :: Meta CLiborForwardModelProcess'
metaLiborForwardModelProcess = Meta qlFreeLiborForwardModelProcess
metaStochasticProcessArray :: Meta CStochasticProcessArray'
metaStochasticProcessArray = Meta qlFreeStochasticProcessArray
metaHestonProcess :: Meta CHestonProcess'
metaHestonProcess = Meta qlFreeHestonProcess
metaStochasticProcess1D :: Meta CStochasticProcess1D'
metaStochasticProcess1D = Meta qlFreeStochasticProcess1D
metaBatesProcess :: Meta CBatesProcess'
metaBatesProcess = Meta qlFreeBatesProcess
metaExtendedOrnsteinUhlenbeckProcess :: Meta CExtendedOrnsteinUhlenbeckProcess'
metaExtendedOrnsteinUhlenbeckProcess = Meta qlFreeExtendedOrnsteinUhlenbeckProcess
metaHullWhiteForwardProcess :: Meta CHullWhiteForwardProcess'
metaHullWhiteForwardProcess = Meta qlFreeHullWhiteForwardProcess
metaHullWhiteProcess :: Meta CHullWhiteProcess'
metaHullWhiteProcess = Meta qlFreeHullWhiteProcess
metaMerton76Process :: Meta CMerton76Process'
metaMerton76Process = Meta qlFreeMerton76Process
metaVarianceGammaProcess :: Meta CVarianceGammaProcess'
metaVarianceGammaProcess = Meta qlFreeVarianceGammaProcess
metaGeneralizedBlackScholesProcess :: Meta CGeneralizedBlackScholesProcess'
metaGeneralizedBlackScholesProcess = Meta qlFreeGeneralizedBlackScholesProcess
metaBlackProcess :: Meta CBlackProcess'
metaBlackProcess = Meta qlFreeBlackProcess
foreign import ccall "ql.h qlExtOUWithJumpsProcessAsStochasticProcess" qlExtOUWithJumpsProcessAsStochasticProcess :: Ptr CExtOUWithJumpsProcess' -> IO (Ptr CStochasticProcess')
foreign import ccall "ql.h qlGJRGARCHProcessAsStochasticProcess" qlGJRGARCHProcessAsStochasticProcess :: Ptr CGJRGARCHProcess' -> IO (Ptr CStochasticProcess')
foreign import ccall "ql.h qlHybridHestonHullWhiteProcessAsStochasticProcess" qlHybridHestonHullWhiteProcessAsStochasticProcess :: Ptr CHybridHestonHullWhiteProcess' -> IO (Ptr CStochasticProcess')
foreign import ccall "ql.h qlKlugeExtOUProcessAsStochasticProcess" qlKlugeExtOUProcessAsStochasticProcess :: Ptr CKlugeExtOUProcess' -> IO (Ptr CStochasticProcess')
foreign import ccall "ql.h qlLiborForwardModelProcessAsStochasticProcess" qlLiborForwardModelProcessAsStochasticProcess :: Ptr CLiborForwardModelProcess' -> IO (Ptr CStochasticProcess')
foreign import ccall "ql.h qlStochasticProcessArrayAsStochasticProcess" qlStochasticProcessArrayAsStochasticProcess :: Ptr CStochasticProcessArray' -> IO (Ptr CStochasticProcess')
foreign import ccall "ql.h qlHestonProcessAsStochasticProcess" qlHestonProcessAsStochasticProcess :: Ptr CHestonProcess' -> IO (Ptr CStochasticProcess')
foreign import ccall "ql.h qlStochasticProcess1DAsStochasticProcess" qlStochasticProcess1DAsStochasticProcess :: Ptr CStochasticProcess1D' -> IO (Ptr CStochasticProcess')
foreign import ccall "ql.h qlBatesProcessAsHestonProcess" qlBatesProcessAsHestonProcess :: Ptr CBatesProcess' -> IO (Ptr CHestonProcess')
foreign import ccall "ql.h qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D" qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D :: Ptr CExtendedOrnsteinUhlenbeckProcess' -> IO (Ptr CStochasticProcess1D')
foreign import ccall "ql.h qlHullWhiteForwardProcessAsStochasticProcess1D" qlHullWhiteForwardProcessAsStochasticProcess1D :: Ptr CHullWhiteForwardProcess' -> IO (Ptr CStochasticProcess1D')
foreign import ccall "ql.h qlHullWhiteProcessAsStochasticProcess1D" qlHullWhiteProcessAsStochasticProcess1D :: Ptr CHullWhiteProcess' -> IO (Ptr CStochasticProcess1D')
foreign import ccall "ql.h qlMerton76ProcessAsStochasticProcess1D" qlMerton76ProcessAsStochasticProcess1D :: Ptr CMerton76Process' -> IO (Ptr CStochasticProcess1D')
foreign import ccall "ql.h qlVarianceGammaProcessAsStochasticProcess1D" qlVarianceGammaProcessAsStochasticProcess1D :: Ptr CVarianceGammaProcess' -> IO (Ptr CStochasticProcess1D')
foreign import ccall "ql.h qlGeneralizedBlackScholesProcessAsStochasticProcess1D" qlGeneralizedBlackScholesProcessAsStochasticProcess1D :: Ptr CGeneralizedBlackScholesProcess' -> IO (Ptr CStochasticProcess1D')
foreign import ccall "ql.h qlBlackProcessAsGeneralizedBlackScholesProcess" qlBlackProcessAsGeneralizedBlackScholesProcess :: Ptr CBlackProcess' -> IO (Ptr CGeneralizedBlackScholesProcess')
upcastExtOUWithJumpsProcess :: Upcast CExtOUWithJumpsProcess' CStochasticProcess'
upcastExtOUWithJumpsProcess = Upcast qlExtOUWithJumpsProcessAsStochasticProcess qlFreeStochasticProcess
upcastGJRGARCHProcess :: Upcast CGJRGARCHProcess' CStochasticProcess'
upcastGJRGARCHProcess = Upcast qlGJRGARCHProcessAsStochasticProcess qlFreeStochasticProcess
upcastHybridHestonHullWhiteProcess :: Upcast CHybridHestonHullWhiteProcess' CStochasticProcess'
upcastHybridHestonHullWhiteProcess = Upcast qlHybridHestonHullWhiteProcessAsStochasticProcess qlFreeStochasticProcess
upcastKlugeExtOUProcess :: Upcast CKlugeExtOUProcess' CStochasticProcess'
upcastKlugeExtOUProcess = Upcast qlKlugeExtOUProcessAsStochasticProcess qlFreeStochasticProcess
upcastLiborForwardModelProcess :: Upcast CLiborForwardModelProcess' CStochasticProcess'
upcastLiborForwardModelProcess = Upcast qlLiborForwardModelProcessAsStochasticProcess qlFreeStochasticProcess
upcastStochasticProcessArray :: Upcast CStochasticProcessArray' CStochasticProcess'
upcastStochasticProcessArray = Upcast qlStochasticProcessArrayAsStochasticProcess qlFreeStochasticProcess
upcastHestonProcess :: Upcast CHestonProcess' CStochasticProcess'
upcastHestonProcess = Upcast qlHestonProcessAsStochasticProcess qlFreeStochasticProcess
upcastStochasticProcess1D :: Upcast CStochasticProcess1D' CStochasticProcess'
upcastStochasticProcess1D = Upcast qlStochasticProcess1DAsStochasticProcess qlFreeStochasticProcess
upcastBatesProcess :: Upcast CBatesProcess' CHestonProcess'
upcastBatesProcess = Upcast qlBatesProcessAsHestonProcess qlFreeHestonProcess
upcastExtendedOrnsteinUhlenbeckProcess :: Upcast CExtendedOrnsteinUhlenbeckProcess' CStochasticProcess1D'
upcastExtendedOrnsteinUhlenbeckProcess = Upcast qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D qlFreeStochasticProcess1D
upcastHullWhiteForwardProcess :: Upcast CHullWhiteForwardProcess' CStochasticProcess1D'
upcastHullWhiteForwardProcess = Upcast qlHullWhiteForwardProcessAsStochasticProcess1D qlFreeStochasticProcess1D
upcastHullWhiteProcess :: Upcast CHullWhiteProcess' CStochasticProcess1D'
upcastHullWhiteProcess = Upcast qlHullWhiteProcessAsStochasticProcess1D qlFreeStochasticProcess1D
upcastMerton76Process :: Upcast CMerton76Process' CStochasticProcess1D'
upcastMerton76Process = Upcast qlMerton76ProcessAsStochasticProcess1D qlFreeStochasticProcess1D
upcastVarianceGammaProcess :: Upcast CVarianceGammaProcess' CStochasticProcess1D'
upcastVarianceGammaProcess = Upcast qlVarianceGammaProcessAsStochasticProcess1D qlFreeStochasticProcess1D
upcastGeneralizedBlackScholesProcess :: Upcast CGeneralizedBlackScholesProcess' CStochasticProcess1D'
upcastGeneralizedBlackScholesProcess = Upcast qlGeneralizedBlackScholesProcessAsStochasticProcess1D qlFreeStochasticProcess1D
upcastBlackProcess :: Upcast CBlackProcess' CGeneralizedBlackScholesProcess'
upcastBlackProcess = Upcast qlBlackProcessAsGeneralizedBlackScholesProcess qlFreeGeneralizedBlackScholesProcess
asStochasticProcess :: GenStochasticProcess a -> IO StochasticProcess
asStochasticProcess (GenStochasticProcess (GenForeignPtr x w)) = w x peekStochasticProcess
peekStochasticProcess :: Ptr CStochasticProcess' -> IO StochasticProcess
peekStochasticProcess = GenStochasticProcess <.> newCastForeignPtr metaStochasticProcess
withStochasticProcess :: GenStochasticProcess a -> (Ptr CStochasticProcess' -> IO b) -> IO b
withStochasticProcess (GenStochasticProcess (GenForeignPtr x w)) = w x
withStochasticProcessDescendant :: GenStochasticProcess (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withStochasticProcessDescendant (GenStochasticProcess (GenForeignPtr x _)) = withForeignPtr x
peekExtOUWithJumpsProcess :: Ptr CExtOUWithJumpsProcess' -> IO ExtOUWithJumpsProcess
peekExtOUWithJumpsProcess = GenStochasticProcess <.> newGenForeignPtr metaExtOUWithJumpsProcess upcastExtOUWithJumpsProcess
peekGJRGARCHProcess :: Ptr CGJRGARCHProcess' -> IO GJRGARCHProcess
peekGJRGARCHProcess = GenStochasticProcess <.> newGenForeignPtr metaGJRGARCHProcess upcastGJRGARCHProcess
peekHybridHestonHullWhiteProcess :: Ptr CHybridHestonHullWhiteProcess' -> IO HybridHestonHullWhiteProcess
peekHybridHestonHullWhiteProcess = GenStochasticProcess <.> newGenForeignPtr metaHybridHestonHullWhiteProcess upcastHybridHestonHullWhiteProcess
peekKlugeExtOUProcess :: Ptr CKlugeExtOUProcess' -> IO KlugeExtOUProcess
peekKlugeExtOUProcess = GenStochasticProcess <.> newGenForeignPtr metaKlugeExtOUProcess upcastKlugeExtOUProcess
peekLiborForwardModelProcess :: Ptr CLiborForwardModelProcess' -> IO LiborForwardModelProcess
peekLiborForwardModelProcess = GenStochasticProcess <.> newGenForeignPtr metaLiborForwardModelProcess upcastLiborForwardModelProcess
peekStochasticProcessArray :: Ptr CStochasticProcessArray' -> IO StochasticProcessArray
peekStochasticProcessArray = GenStochasticProcess <.> newGenForeignPtr metaStochasticProcessArray upcastStochasticProcessArray
asHestonProcess :: GenHestonProcess a -> IO HestonProcess
asHestonProcess (GenStochasticProcess (GenForeignPtr (HestonProcessDescendant (GenForeignPtr x w)) _)) = w x peekHestonProcess
peekHestonProcess :: Ptr CHestonProcess' -> IO HestonProcess
peekHestonProcess = newCastForeignPtr metaHestonProcess >=> newHestonProcessDescendant
withHestonProcess :: GenHestonProcess a -> (Ptr CHestonProcess' -> IO b) -> IO b
withHestonProcess (GenStochasticProcess (GenForeignPtr (HestonProcessDescendant (GenForeignPtr x w)) _)) = w x
marshalHestonProcess :: HestonProcessDescendant a -> (Ptr CStochasticProcess' -> IO b) -> IO b
marshalHestonProcess (HestonProcessDescendant o) = withGenForeignPtr upcastHestonProcess o
newHestonProcessDescendant :: GenForeignPtr a CHestonProcess' -> IO (GenHestonProcess a)
newHestonProcessDescendant p = GenStochasticProcess <^> GenForeignPtr (HestonProcessDescendant p) marshalHestonProcess
peekHestonProcessDescendant :: Meta a -> Upcast a CHestonProcess' -> Ptr a -> IO (GenHestonProcess (ForeignPtr a))
peekHestonProcessDescendant m u = newGenForeignPtr m u >=> newHestonProcessDescendant
asStochasticProcess1D :: GenStochasticProcess1D a -> IO StochasticProcess1D
asStochasticProcess1D (GenStochasticProcess (GenForeignPtr (StochasticProcess1DDescendant (GenForeignPtr x w)) _)) = w x peekStochasticProcess1D
peekStochasticProcess1D :: Ptr CStochasticProcess1D' -> IO StochasticProcess1D
peekStochasticProcess1D = newCastForeignPtr metaStochasticProcess1D >=> newStochasticProcess1DDescendant
withStochasticProcess1D :: GenStochasticProcess1D a -> (Ptr CStochasticProcess1D' -> IO b) -> IO b
withStochasticProcess1D (GenStochasticProcess (GenForeignPtr (StochasticProcess1DDescendant (GenForeignPtr x w)) _)) = w x
withStochasticProcess1DArray :: [GenStochasticProcess1D a] -> ((CUInt, Ptr (Ptr CStochasticProcess1D')) -> IO b) -> IO b
withStochasticProcess1DArray x f = withMany withStochasticProcess1D x (`withArray` (\px -> f (fromIntegral $ length x, px)))
marshalStochasticProcess1D :: StochasticProcess1DDescendant a -> (Ptr CStochasticProcess' -> IO b) -> IO b
marshalStochasticProcess1D (StochasticProcess1DDescendant o) = withGenForeignPtr upcastStochasticProcess1D o
newStochasticProcess1DDescendant :: GenForeignPtr a CStochasticProcess1D' -> IO (GenStochasticProcess1D a)
newStochasticProcess1DDescendant p = GenStochasticProcess <^> GenForeignPtr (StochasticProcess1DDescendant p) marshalStochasticProcess1D
peekStochasticProcess1DDescendant :: Meta a -> Upcast a CStochasticProcess1D' -> Ptr a -> IO (GenStochasticProcess1D (ForeignPtr a))
peekStochasticProcess1DDescendant m u = newGenForeignPtr m u >=> newStochasticProcess1DDescendant
withStochasticProcess1DDescendant :: GenStochasticProcess1D (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
withStochasticProcess1DDescendant (GenStochasticProcess (GenForeignPtr (StochasticProcess1DDescendant (GenForeignPtr x _)) _)) = withForeignPtr x
peekBatesProcess :: Ptr CBatesProcess' -> IO BatesProcess
peekBatesProcess = peekHestonProcessDescendant metaBatesProcess upcastBatesProcess
withBatesProcess :: BatesProcess -> (Ptr CBatesProcess' -> IO b) -> IO b
withBatesProcess (GenStochasticProcess (GenForeignPtr (HestonProcessDescendant (GenForeignPtr x _)) _)) = withForeignPtr x
peekExtendedOrnsteinUhlenbeckProcess :: Ptr CExtendedOrnsteinUhlenbeckProcess' -> IO ExtendedOrnsteinUhlenbeckProcess
peekExtendedOrnsteinUhlenbeckProcess = peekStochasticProcess1DDescendant metaExtendedOrnsteinUhlenbeckProcess upcastExtendedOrnsteinUhlenbeckProcess
peekHullWhiteForwardProcess :: Ptr CHullWhiteForwardProcess' -> IO HullWhiteForwardProcess
peekHullWhiteForwardProcess = peekStochasticProcess1DDescendant metaHullWhiteForwardProcess upcastHullWhiteForwardProcess
peekHullWhiteProcess :: Ptr CHullWhiteProcess' -> IO HullWhiteProcess
peekHullWhiteProcess = peekStochasticProcess1DDescendant metaHullWhiteProcess upcastHullWhiteProcess
peekMerton76Process :: Ptr CMerton76Process' -> IO Merton76Process
peekMerton76Process = peekStochasticProcess1DDescendant metaMerton76Process upcastMerton76Process
peekVarianceGammaProcess :: Ptr CVarianceGammaProcess' -> IO VarianceGammaProcess
peekVarianceGammaProcess = peekStochasticProcess1DDescendant metaVarianceGammaProcess upcastVarianceGammaProcess
asGeneralizedBlackScholesProcess :: GenGeneralizedBlackScholesProcess a -> IO GeneralizedBlackScholesProcess
asGeneralizedBlackScholesProcess (GenStochasticProcess (GenForeignPtr (StochasticProcess1DDescendant (GenForeignPtr (GeneralizedBlackScholesProcessDescendant (GenForeignPtr x w)) _)) _)) = w x peekGeneralizedBlackScholesProcess
peekGeneralizedBlackScholesProcess :: Ptr CGeneralizedBlackScholesProcess' -> IO GeneralizedBlackScholesProcess
peekGeneralizedBlackScholesProcess = newCastForeignPtr metaGeneralizedBlackScholesProcess >=> newGeneralizedBlackScholesProcessDescendant
withGeneralizedBlackScholesProcess :: GenGeneralizedBlackScholesProcess a -> (Ptr CGeneralizedBlackScholesProcess' -> IO b) -> IO b
withGeneralizedBlackScholesProcess (GenStochasticProcess (GenForeignPtr (StochasticProcess1DDescendant (GenForeignPtr (GeneralizedBlackScholesProcessDescendant (GenForeignPtr x w)) _)) _)) = w x
marshalGeneralizedBlackScholesProcess :: GeneralizedBlackScholesProcessDescendant a -> (Ptr CStochasticProcess1D' -> IO b) -> IO b
marshalGeneralizedBlackScholesProcess (GeneralizedBlackScholesProcessDescendant o) = withGenForeignPtr upcastGeneralizedBlackScholesProcess o
newGeneralizedBlackScholesProcessDescendant :: GenForeignPtr a CGeneralizedBlackScholesProcess' -> IO (GenGeneralizedBlackScholesProcess a)
newGeneralizedBlackScholesProcessDescendant p = GenStochasticProcess <^> GenForeignPtr (StochasticProcess1DDescendant $ GenForeignPtr (GeneralizedBlackScholesProcessDescendant p) marshalGeneralizedBlackScholesProcess) marshalStochasticProcess1D
peekBlackProcess :: Ptr CBlackProcess' -> IO BlackProcess
peekBlackProcess = newGenForeignPtr metaBlackProcess upcastBlackProcess >=> newGeneralizedBlackScholesProcessDescendant
withBlackProcess :: BlackProcess -> (Ptr CBlackProcess' -> IO b) -> IO b
withBlackProcess (GenStochasticProcess (GenForeignPtr (StochasticProcess1DDescendant (GenForeignPtr (GeneralizedBlackScholesProcessDescendant (GenForeignPtr x _)) _)) _)) = withForeignPtr x

-- TEMPORARY STORAGE BEFORE HIERARCHIES ARE MIGRATED OFF TYPE CLASSES

data CAssetSwap
instance Finalizable CAssetSwap where finalize = qlFreeAssetSwap
newtype AssetSwap = AssetSwap {getCAssetSwap :: Standalone CAssetSwap}
peekAssetSwap :: Ptr CAssetSwap -> IO AssetSwap
peekAssetSwap = peekStandalone >=> return . AssetSwap
withAssetSwap :: AssetSwap -> (Ptr CAssetSwap -> IO b) -> IO b
withAssetSwap = withStandalone . getCAssetSwap
data CBarrierOption
newtype BarrierOption = BarrierOption {getCBarrierOption :: Standalone CBarrierOption}
instance Finalizable CBarrierOption where finalize = qlFreeBarrierOption
peekBarrierOption :: Ptr CBarrierOption -> IO BarrierOption
peekBarrierOption = peekStandalone >=> return . BarrierOption
withBarrierOption :: BarrierOption -> (Ptr CBarrierOption -> IO b) -> IO b
withBarrierOption = withStandalone . getCBarrierOption
data CBMASwap
newtype BMASwap = BMASwap {getCBMASwap :: Standalone CBMASwap}
instance Finalizable CBMASwap where finalize = qlFreeBMASwap
peekBMASwap :: Ptr CBMASwap -> IO BMASwap
peekBMASwap = peekStandalone >=> return . BMASwap
withBMASwap :: BMASwap -> (Ptr CBMASwap -> IO b) -> IO b
withBMASwap = withStandalone . getCBMASwap
data CBond
newtype Bond = Bond {getCBond :: Standalone CBond}
instance Finalizable CBond where finalize = qlFreeBond
peekBond :: Ptr CBond -> IO Bond
peekBond = peekStandalone >=> return . Bond
withBond :: Bond -> (Ptr CBond -> IO b) -> IO b
withBond = withStandalone . getCBond
data CCallableBond
newtype CallableBond = CallableBond {getCCallableBond :: Standalone CCallableBond}
instance Finalizable CCallableBond where finalize = qlFreeCallableBond
peekCallableBond :: Ptr CCallableBond -> IO CallableBond
peekCallableBond = peekStandalone >=> return . CallableBond
withCallableBond :: CallableBond -> (Ptr CCallableBond -> IO b) -> IO b
withCallableBond = withStandalone . getCCallableBond
data CCapFloor
newtype CapFloor = CapFloor {getCCapFloor :: Standalone CCapFloor}
instance Finalizable CCapFloor where finalize = qlFreeCapFloor
peekCapFloor :: Ptr CCapFloor -> IO CapFloor
peekCapFloor = peekStandalone >=> return . CapFloor
withCapFloor :: CapFloor -> (Ptr CCapFloor -> IO b) -> IO b
withCapFloor = withStandalone . getCCapFloor
data CCdsOption
newtype CdsOption = CdsOption {getCCdsOption :: Standalone CCdsOption}
instance Finalizable CCdsOption where finalize = qlFreeCdsOption
peekCdsOption :: Ptr CCdsOption -> IO CdsOption
peekCdsOption = peekStandalone >=> return . CdsOption
withCdsOption :: CdsOption -> (Ptr CCdsOption -> IO b) -> IO b
withCdsOption = withStandalone . getCCdsOption
data CConvertibleBond
newtype ConvertibleBond = ConvertibleBond {getCConvertibleBond :: Standalone CConvertibleBond}
instance Finalizable CConvertibleBond where finalize = qlFreeConvertibleBond
peekConvertibleBond :: Ptr CConvertibleBond -> IO ConvertibleBond
peekConvertibleBond = peekStandalone >=> return . ConvertibleBond
withConvertibleBond :: ConvertibleBond -> (Ptr CConvertibleBond -> IO b) -> IO b
withConvertibleBond = withStandalone . getCConvertibleBond
data CCreditDefaultSwap
newtype CreditDefaultSwap = CreditDefaultSwap {getCCreditDefaultSwap :: Standalone CCreditDefaultSwap}
instance Finalizable CCreditDefaultSwap where finalize = qlFreeCreditDefaultSwap
peekCreditDefaultSwap :: Ptr CCreditDefaultSwap -> IO CreditDefaultSwap
peekCreditDefaultSwap = peekStandalone >=> return . CreditDefaultSwap
withCreditDefaultSwap :: CreditDefaultSwap -> (Ptr CCreditDefaultSwap -> IO b) -> IO b
withCreditDefaultSwap = withStandalone . getCCreditDefaultSwap
data CDividendVanillaOption
newtype DividendVanillaOption = DividendVanillaOption {getCDividendVanillaOption :: Standalone CDividendVanillaOption}
instance Finalizable CDividendVanillaOption where finalize = qlFreeDividendVanillaOption
peekDividendVanillaOption :: Ptr CDividendVanillaOption -> IO DividendVanillaOption
peekDividendVanillaOption = peekStandalone >=> return . DividendVanillaOption
withDividendVanillaOption :: DividendVanillaOption -> (Ptr CDividendVanillaOption -> IO b) -> IO b
withDividendVanillaOption = withStandalone . getCDividendVanillaOption
data CFixedRateBond
newtype FixedRateBond = FixedRateBond {getCFixedRateBond :: Standalone CFixedRateBond}
instance Finalizable CFixedRateBond where finalize = qlFreeFixedRateBond
peekFixedRateBond :: Ptr CFixedRateBond -> IO FixedRateBond
peekFixedRateBond = peekStandalone >=> return . FixedRateBond
withFixedRateBond :: FixedRateBond -> (Ptr CFixedRateBond -> IO b) -> IO b
withFixedRateBond = withStandalone . getCFixedRateBond
data CBondForward
newtype BondForward = BondForward {getCBondForward :: Standalone CBondForward}
instance Finalizable CBondForward where finalize = qlFreeBondForward
peekBondForward :: Ptr CBondForward -> IO BondForward
peekBondForward = peekStandalone >=> return . BondForward
withBondForward :: BondForward -> (Ptr CBondForward -> IO b) -> IO b
withBondForward = withStandalone . getCBondForward
data CForward
newtype Forward = Forward {getCForward :: Standalone CForward}
instance Finalizable CForward where finalize = qlFreeForward
peekForward :: Ptr CForward -> IO Forward
peekForward = peekStandalone >=> return . Forward
withForward :: Forward -> (Ptr CForward -> IO b) -> IO b
withForward = withStandalone . getCForward
data CForwardRateAgreement
newtype ForwardRateAgreement = ForwardRateAgreement {getCForwardRateAgreement :: Standalone CForwardRateAgreement}
instance Finalizable CForwardRateAgreement where finalize = qlFreeForwardRateAgreement
peekForwardRateAgreement :: Ptr CForwardRateAgreement -> IO ForwardRateAgreement
peekForwardRateAgreement = peekStandalone >=> return . ForwardRateAgreement
withForwardRateAgreement :: ForwardRateAgreement -> (Ptr CForwardRateAgreement -> IO b) -> IO b
withForwardRateAgreement = withStandalone . getCForwardRateAgreement
data CForwardVanillaOption
newtype ForwardVanillaOption = ForwardVanillaOption {getCForwardVanillaOption :: Standalone CForwardVanillaOption}
instance Finalizable CForwardVanillaOption where finalize = qlFreeForwardVanillaOption
peekForwardVanillaOption :: Ptr CForwardVanillaOption -> IO ForwardVanillaOption
peekForwardVanillaOption = peekStandalone >=> return . ForwardVanillaOption
withForwardVanillaOption :: ForwardVanillaOption -> (Ptr CForwardVanillaOption -> IO b) -> IO b
withForwardVanillaOption = withStandalone . getCForwardVanillaOption
data CInstrument
newtype Instrument = Instrument {getCInstrument :: Standalone CInstrument}
instance Finalizable CInstrument where finalize = qlFreeInstrument
peekInstrument :: Ptr CInstrument -> IO Instrument
peekInstrument = peekStandalone >=> return . Instrument
withInstrument :: Instrument -> (Ptr CInstrument -> IO b) -> IO b
withInstrument = withStandalone . getCInstrument
data CMargrabeOption
newtype MargrabeOption = MargrabeOption {getCMargrabeOption :: Standalone CMargrabeOption}
instance Finalizable CMargrabeOption where finalize = qlFreeMargrabeOption
peekMargrabeOption :: Ptr CMargrabeOption -> IO MargrabeOption
peekMargrabeOption = peekStandalone >=> return . MargrabeOption
withMargrabeOption :: MargrabeOption -> (Ptr CMargrabeOption -> IO b) -> IO b
withMargrabeOption = withStandalone . getCMargrabeOption
data CMultiAssetOption
newtype MultiAssetOption = MultiAssetOption {getCMultiAssetOption :: Standalone CMultiAssetOption}
instance Finalizable CMultiAssetOption where finalize = qlFreeMultiAssetOption
peekMultiAssetOption :: Ptr CMultiAssetOption -> IO MultiAssetOption
peekMultiAssetOption = peekStandalone >=> return . MultiAssetOption
withMultiAssetOption :: MultiAssetOption -> (Ptr CMultiAssetOption -> IO b) -> IO b
withMultiAssetOption = withStandalone . getCMultiAssetOption
data COneAssetOption
newtype OneAssetOption = OneAssetOption {getCOneAssetOption :: Standalone COneAssetOption}
instance Finalizable COneAssetOption where finalize = qlFreeOneAssetOption
peekOneAssetOption :: Ptr COneAssetOption -> IO OneAssetOption
peekOneAssetOption = peekStandalone >=> return . OneAssetOption
withOneAssetOption :: OneAssetOption -> (Ptr COneAssetOption -> IO b) -> IO b
withOneAssetOption = withStandalone . getCOneAssetOption
data COption
newtype Option = Option {getCOption :: Standalone COption}
instance Finalizable COption where finalize = qlFreeOption
peekOption :: Ptr COption -> IO Option
peekOption = peekStandalone >=> return . Option
withOption :: Option -> (Ptr COption -> IO b) -> IO b
withOption = withStandalone . getCOption
data COvernightIndexedSwap
newtype OvernightIndexedSwap = OvernightIndexedSwap {getCOvernightIndexedSwap :: Standalone COvernightIndexedSwap}
instance Finalizable COvernightIndexedSwap where finalize = qlFreeOvernightIndexedSwap
peekOvernightIndexedSwap :: Ptr COvernightIndexedSwap -> IO OvernightIndexedSwap
peekOvernightIndexedSwap = peekStandalone >=> return . OvernightIndexedSwap
withOvernightIndexedSwap :: OvernightIndexedSwap -> (Ptr COvernightIndexedSwap -> IO b) -> IO b
withOvernightIndexedSwap = withStandalone . getCOvernightIndexedSwap
data CQuantoBarrierOption
newtype QuantoBarrierOption = QuantoBarrierOption {getCQuantoBarrierOption :: Standalone CQuantoBarrierOption}
instance Finalizable CQuantoBarrierOption where finalize = qlFreeQuantoBarrierOption
peekQuantoBarrierOption :: Ptr CQuantoBarrierOption -> IO QuantoBarrierOption
peekQuantoBarrierOption = peekStandalone >=> return . QuantoBarrierOption
withQuantoBarrierOption :: QuantoBarrierOption -> (Ptr CQuantoBarrierOption -> IO b) -> IO b
withQuantoBarrierOption = withStandalone . getCQuantoBarrierOption
data CQuantoForwardVanillaOption
newtype QuantoForwardVanillaOption = QuantoForwardVanillaOption {getCQuantoForwardVanillaOption :: Standalone CQuantoForwardVanillaOption}
instance Finalizable CQuantoForwardVanillaOption where finalize = qlFreeQuantoForwardVanillaOption
peekQuantoForwardVanillaOption :: Ptr CQuantoForwardVanillaOption -> IO QuantoForwardVanillaOption
peekQuantoForwardVanillaOption = peekStandalone >=> return . QuantoForwardVanillaOption
withQuantoForwardVanillaOption :: QuantoForwardVanillaOption -> (Ptr CQuantoForwardVanillaOption -> IO b) -> IO b
withQuantoForwardVanillaOption = withStandalone . getCQuantoForwardVanillaOption
data CQuantoVanillaOption
newtype QuantoVanillaOption = QuantoVanillaOption {getCQuantoVanillaOption :: Standalone CQuantoVanillaOption}
instance Finalizable CQuantoVanillaOption where finalize = qlFreeQuantoVanillaOption
peekQuantoVanillaOption :: Ptr CQuantoVanillaOption -> IO QuantoVanillaOption
peekQuantoVanillaOption = peekStandalone >=> return . QuantoVanillaOption
withQuantoVanillaOption :: QuantoVanillaOption -> (Ptr CQuantoVanillaOption -> IO b) -> IO b
withQuantoVanillaOption = withStandalone . getCQuantoVanillaOption
data CSwap
newtype Swap = Swap {getCSwap :: Standalone CSwap}
instance Finalizable CSwap where finalize = qlFreeSwap
peekSwap :: Ptr CSwap -> IO Swap
peekSwap = peekStandalone >=> return . Swap
withSwap :: Swap -> (Ptr CSwap -> IO b) -> IO b
withSwap = withStandalone . getCSwap
data CSwaption
newtype Swaption = Swaption {getCSwaption :: Standalone CSwaption}
instance Finalizable CSwaption where finalize = qlFreeSwaption
peekSwaption :: Ptr CSwaption -> IO Swaption
peekSwaption = peekStandalone >=> return . Swaption
withSwaption :: Swaption -> (Ptr CSwaption -> IO b) -> IO b
withSwaption = withStandalone . getCSwaption
data CVanillaOption
newtype VanillaOption = VanillaOption {getCVanillaOption :: Standalone CVanillaOption}
instance Finalizable CVanillaOption where finalize = qlFreeVanillaOption
peekVanillaOption :: Ptr CVanillaOption -> IO VanillaOption
peekVanillaOption = peekStandalone >=> return . VanillaOption
withVanillaOption :: VanillaOption -> (Ptr CVanillaOption -> IO b) -> IO b
withVanillaOption = withStandalone . getCVanillaOption
data CVanillaSwap
newtype VanillaSwap = VanillaSwap {getCVanillaSwap :: Standalone CVanillaSwap}
instance Finalizable CVanillaSwap where finalize = qlFreeVanillaSwap
peekVanillaSwap :: Ptr CVanillaSwap -> IO VanillaSwap
peekVanillaSwap = peekStandalone >=> return . VanillaSwap
withVanillaSwap :: VanillaSwap -> (Ptr CVanillaSwap -> IO b) -> IO b
withVanillaSwap = withStandalone . getCVanillaSwap
withInstrumentArray :: [Instrument] -> ((CUInt, Ptr (Ptr CInstrument)) -> IO b) -> IO b
withInstrumentArray = withStandaloneArray getCInstrument
foreign import ccall "ql.h &qlFreeAssetSwap" qlFreeAssetSwap :: FinalizerPtr CAssetSwap
foreign import ccall "ql.h &qlFreeBarrierOption" qlFreeBarrierOption :: FinalizerPtr CBarrierOption
foreign import ccall "ql.h &qlFreeBMASwap" qlFreeBMASwap :: FinalizerPtr CBMASwap
foreign import ccall "ql.h &qlFreeBond" qlFreeBond :: FinalizerPtr CBond
foreign import ccall "ql.h &qlFreeCallableBond" qlFreeCallableBond :: FinalizerPtr CCallableBond
foreign import ccall "ql.h &qlFreeCapFloor" qlFreeCapFloor :: FinalizerPtr CCapFloor
foreign import ccall "ql.h &qlFreeCdsOption" qlFreeCdsOption :: FinalizerPtr CCdsOption
foreign import ccall "ql.h &qlFreeConvertibleBond" qlFreeConvertibleBond :: FinalizerPtr CConvertibleBond
foreign import ccall "ql.h &qlFreeCreditDefaultSwap" qlFreeCreditDefaultSwap :: FinalizerPtr CCreditDefaultSwap
foreign import ccall "ql.h &qlFreeDividendVanillaOption" qlFreeDividendVanillaOption :: FinalizerPtr CDividendVanillaOption
foreign import ccall "ql.h &qlFreeFixedRateBond" qlFreeFixedRateBond :: FinalizerPtr CFixedRateBond
foreign import ccall "ql.h &qlFreeBondForward" qlFreeBondForward :: FinalizerPtr CBondForward
foreign import ccall "ql.h &qlFreeForward" qlFreeForward :: FinalizerPtr CForward
foreign import ccall "ql.h &qlFreeForwardRateAgreement" qlFreeForwardRateAgreement :: FinalizerPtr CForwardRateAgreement
foreign import ccall "ql.h &qlFreeForwardVanillaOption" qlFreeForwardVanillaOption :: FinalizerPtr CForwardVanillaOption
foreign import ccall "ql.h &qlFreeInstrument" qlFreeInstrument :: FinalizerPtr CInstrument
foreign import ccall "ql.h &qlFreeMargrabeOption" qlFreeMargrabeOption :: FinalizerPtr CMargrabeOption
foreign import ccall "ql.h &qlFreeMultiAssetOption" qlFreeMultiAssetOption :: FinalizerPtr CMultiAssetOption
foreign import ccall "ql.h &qlFreeOneAssetOption" qlFreeOneAssetOption :: FinalizerPtr COneAssetOption
foreign import ccall "ql.h &qlFreeOption" qlFreeOption :: FinalizerPtr COption
foreign import ccall "ql.h &qlFreeQuantoBarrierOption" qlFreeQuantoBarrierOption :: FinalizerPtr CQuantoBarrierOption
foreign import ccall "ql.h &qlFreeQuantoForwardVanillaOption" qlFreeQuantoForwardVanillaOption :: FinalizerPtr CQuantoForwardVanillaOption
foreign import ccall "ql.h &qlFreeOvernightIndexedSwap" qlFreeOvernightIndexedSwap :: FinalizerPtr COvernightIndexedSwap
foreign import ccall "ql.h &qlFreeQuantoVanillaOption" qlFreeQuantoVanillaOption :: FinalizerPtr CQuantoVanillaOption
foreign import ccall "ql.h &qlFreeSwap" qlFreeSwap :: FinalizerPtr CSwap
foreign import ccall "ql.h &qlFreeSwaption" qlFreeSwaption :: FinalizerPtr CSwaption
foreign import ccall "ql.h &qlFreeVanillaOption" qlFreeVanillaOption :: FinalizerPtr CVanillaOption
foreign import ccall "ql.h &qlFreeVanillaSwap" qlFreeVanillaSwap :: FinalizerPtr CVanillaSwap

data CAffineModel
newtype AffineModel = AffineModel {getCAffineModel :: Standalone CAffineModel}
instance Finalizable CAffineModel where finalize = qlFreeAffineModel
peekAffineModel :: Ptr CAffineModel -> IO AffineModel
peekAffineModel = peekStandalone >=> return . AffineModel
withAffineModel :: AffineModel -> (Ptr CAffineModel -> IO b) -> IO b
withAffineModel = withStandalone . getCAffineModel
data CBatesDetJumpModel
newtype BatesDetJumpModel = BatesDetJumpModel {getCBatesDetJumpModel :: Standalone CBatesDetJumpModel}
instance Finalizable CBatesDetJumpModel where finalize = qlFreeBatesDetJumpModel
peekBatesDetJumpModel :: Ptr CBatesDetJumpModel -> IO BatesDetJumpModel
peekBatesDetJumpModel = peekStandalone >=> return . BatesDetJumpModel
withBatesDetJumpModel :: BatesDetJumpModel -> (Ptr CBatesDetJumpModel -> IO b) -> IO b
withBatesDetJumpModel = withStandalone . getCBatesDetJumpModel
data CBatesDoubleExpDetJumpModel
newtype BatesDoubleExpDetJumpModel = BatesDoubleExpDetJumpModel {getCBatesDoubleExpDetJumpModel :: Standalone CBatesDoubleExpDetJumpModel}
instance Finalizable CBatesDoubleExpDetJumpModel where finalize = qlFreeBatesDoubleExpDetJumpModel
peekBatesDoubleExpDetJumpModel :: Ptr CBatesDoubleExpDetJumpModel -> IO BatesDoubleExpDetJumpModel
peekBatesDoubleExpDetJumpModel = peekStandalone >=> return . BatesDoubleExpDetJumpModel
withBatesDoubleExpDetJumpModel :: BatesDoubleExpDetJumpModel -> (Ptr CBatesDoubleExpDetJumpModel -> IO b) -> IO b
withBatesDoubleExpDetJumpModel = withStandalone . getCBatesDoubleExpDetJumpModel
data CBatesDoubleExpModel
newtype BatesDoubleExpModel = BatesDoubleExpModel {getCBatesDoubleExpModel :: Standalone CBatesDoubleExpModel}
instance Finalizable CBatesDoubleExpModel where finalize = qlFreeBatesDoubleExpModel
peekBatesDoubleExpModel :: Ptr CBatesDoubleExpModel -> IO BatesDoubleExpModel
peekBatesDoubleExpModel = peekStandalone >=> return . BatesDoubleExpModel
withBatesDoubleExpModel :: BatesDoubleExpModel -> (Ptr CBatesDoubleExpModel -> IO b) -> IO b
withBatesDoubleExpModel = withStandalone . getCBatesDoubleExpModel
data CBatesModel
newtype BatesModel = BatesModel {getCBatesModel :: Standalone CBatesModel}
instance Finalizable CBatesModel where finalize = qlFreeBatesModel
peekBatesModel :: Ptr CBatesModel -> IO BatesModel
peekBatesModel = peekStandalone >=> return . BatesModel
withBatesModel :: BatesModel -> (Ptr CBatesModel -> IO b) -> IO b
withBatesModel = withStandalone . getCBatesModel
data CCalibratedModel
newtype CalibratedModel = CalibratedModel {getCCalibratedModel :: Standalone CCalibratedModel}
instance Finalizable CCalibratedModel where finalize = qlFreeCalibratedModel
peekCalibratedModel :: Ptr CCalibratedModel -> IO CalibratedModel
peekCalibratedModel = peekStandalone >=> return . CalibratedModel
withCalibratedModel :: CalibratedModel -> (Ptr CCalibratedModel -> IO b) -> IO b
withCalibratedModel = withStandalone . getCCalibratedModel
data CG2
newtype G2 = G2 {getCG2 :: Standalone CG2}
instance Finalizable CG2 where finalize = qlFreeG2
peekG2 :: Ptr CG2 -> IO G2
peekG2 = peekStandalone >=> return . G2
withG2 :: G2 -> (Ptr CG2 -> IO b) -> IO b
withG2 = withStandalone . getCG2
data CGJRGARCHModel
newtype GJRGARCHModel = GJRGARCHModel {getCGJRGARCHModel :: Standalone CGJRGARCHModel}
instance Finalizable CGJRGARCHModel where finalize = qlFreeGJRGARCHModel
peekGJRGARCHModel :: Ptr CGJRGARCHModel -> IO GJRGARCHModel
peekGJRGARCHModel = peekStandalone >=> return . GJRGARCHModel
withGJRGARCHModel :: GJRGARCHModel -> (Ptr CGJRGARCHModel -> IO b) -> IO b
withGJRGARCHModel = withStandalone . getCGJRGARCHModel
data CHestonModel
newtype HestonModel = HestonModel {getCHestonModel :: Standalone CHestonModel}
instance Finalizable CHestonModel where finalize = qlFreeHestonModel
peekHestonModel :: Ptr CHestonModel -> IO HestonModel
peekHestonModel = peekStandalone >=> return . HestonModel
withHestonModel :: HestonModel -> (Ptr CHestonModel -> IO b) -> IO b
withHestonModel = withStandalone . getCHestonModel
data CHullWhite
newtype HullWhite = HullWhite {getCHullWhite :: Standalone CHullWhite}
instance Finalizable CHullWhite where finalize = qlFreeHullWhite
peekHullWhite :: Ptr CHullWhite -> IO HullWhite
peekHullWhite = peekStandalone >=> return . HullWhite
withHullWhite :: HullWhite -> (Ptr CHullWhite -> IO b) -> IO b
withHullWhite = withStandalone . getCHullWhite
data CLiborForwardModel
newtype LiborForwardModel = LiborForwardModel {getCLiborForwardModel :: Standalone CLiborForwardModel}
instance Finalizable CLiborForwardModel where finalize = qlFreeLiborForwardModel
peekLiborForwardModel :: Ptr CLiborForwardModel -> IO LiborForwardModel
peekLiborForwardModel = peekStandalone >=> return . LiborForwardModel
withLiborForwardModel :: LiborForwardModel -> (Ptr CLiborForwardModel -> IO b) -> IO b
withLiborForwardModel = withStandalone . getCLiborForwardModel
data COneFactorAffineModel
newtype OneFactorAffineModel = OneFactorAffineModel {getCOneFactorAffineModel :: Standalone COneFactorAffineModel}
instance Finalizable COneFactorAffineModel where finalize = qlFreeOneFactorAffineModel
peekOneFactorAffineModel :: Ptr COneFactorAffineModel -> IO OneFactorAffineModel
peekOneFactorAffineModel = peekStandalone >=> return . OneFactorAffineModel
withOneFactorAffineModel :: OneFactorAffineModel -> (Ptr COneFactorAffineModel -> IO b) -> IO b
withOneFactorAffineModel = withStandalone . getCOneFactorAffineModel
data CPiecewiseTimeDependentHestonModel
newtype PiecewiseTimeDependentHestonModel = PiecewiseTimeDependentHestonModel {getCPiecewiseTimeDependentHestonModel :: Standalone CPiecewiseTimeDependentHestonModel}
instance Finalizable CPiecewiseTimeDependentHestonModel where finalize = qlFreePiecewiseTimeDependentHestonModel
peekPiecewiseTimeDependentHestonModel :: Ptr CPiecewiseTimeDependentHestonModel -> IO PiecewiseTimeDependentHestonModel
peekPiecewiseTimeDependentHestonModel = peekStandalone >=> return . PiecewiseTimeDependentHestonModel
withPiecewiseTimeDependentHestonModel :: PiecewiseTimeDependentHestonModel -> (Ptr CPiecewiseTimeDependentHestonModel -> IO b) -> IO b
withPiecewiseTimeDependentHestonModel = withStandalone . getCPiecewiseTimeDependentHestonModel
data CShortRateModel
newtype ShortRateModel = ShortRateModel {getCShortRateModel :: Standalone CShortRateModel}
instance Finalizable CShortRateModel where finalize = qlFreeShortRateModel
peekShortRateModel :: Ptr CShortRateModel -> IO ShortRateModel
peekShortRateModel = peekStandalone >=> return . ShortRateModel
withShortRateModel :: ShortRateModel -> (Ptr CShortRateModel -> IO b) -> IO b
withShortRateModel = withStandalone . getCShortRateModel
foreign import ccall "ql.h &qlFreeAffineModel" qlFreeAffineModel :: FinalizerPtr CAffineModel
foreign import ccall "ql.h &qlFreeBatesDetJumpModel" qlFreeBatesDetJumpModel :: FinalizerPtr CBatesDetJumpModel
foreign import ccall "ql.h &qlFreeBatesDoubleExpDetJumpModel" qlFreeBatesDoubleExpDetJumpModel :: FinalizerPtr CBatesDoubleExpDetJumpModel
foreign import ccall "ql.h &qlFreeBatesDoubleExpModel" qlFreeBatesDoubleExpModel :: FinalizerPtr CBatesDoubleExpModel
foreign import ccall "ql.h &qlFreeBatesModel" qlFreeBatesModel :: FinalizerPtr CBatesModel
foreign import ccall "ql.h &qlFreeCalibratedModel" qlFreeCalibratedModel :: FinalizerPtr CCalibratedModel
foreign import ccall "ql.h &qlFreeG2" qlFreeG2 :: FinalizerPtr CG2
foreign import ccall "ql.h &qlFreeGJRGARCHModel" qlFreeGJRGARCHModel :: FinalizerPtr CGJRGARCHModel
foreign import ccall "ql.h &qlFreeHestonModel" qlFreeHestonModel :: FinalizerPtr CHestonModel
foreign import ccall "ql.h &qlFreeHullWhite" qlFreeHullWhite :: FinalizerPtr CHullWhite
foreign import ccall "ql.h &qlFreeLiborForwardModel" qlFreeLiborForwardModel :: FinalizerPtr CLiborForwardModel
foreign import ccall "ql.h &qlFreeOneFactorAffineModel" qlFreeOneFactorAffineModel :: FinalizerPtr COneFactorAffineModel
foreign import ccall "ql.h &qlFreeShortRateModel" qlFreeShortRateModel :: FinalizerPtr CShortRateModel
foreign import ccall "ql.h &qlFreePiecewiseTimeDependentHestonModel" qlFreePiecewiseTimeDependentHestonModel :: FinalizerPtr CPiecewiseTimeDependentHestonModel

--- TEMPLATE CODE

--data CNode0'
--data CLeaf1'
--data CNode1'
--data CLeaf2'
--data CNode2'
--data CLeaf3'
--newtype GenNode0 a = GenNode0 (GenForeignPtr a CNode0')
--type CNode0 = ForeignPtr CNode0'
--type Node0 = GenNode0 CNode0
--type CLeaf1 = ForeignPtr CLeaf1'
--type Leaf1 = GenNode0 CLeaf1
--newtype Node1Descendant a = Node1Descendant (GenForeignPtr a CNode1')
--type GenNode1 a = GenNode0 (Node1Descendant a)
--type CNode1 = ForeignPtr CNode1'
--type Node1 = GenNode1 CNode1
--type CLeaf2 = ForeignPtr CLeaf2'
--type Leaf2 = GenNode1 CLeaf2
--newtype Node2Descendant a = Node2Descendant (GenForeignPtr a CNode2')
--type GenNode2 a = GenNode0 (Node1Descendant (Node2Descendant a))
--type CNode2 = ForeignPtr CNode2'
--type Node2 = GenNode2 CNode2
--type CLeaf3 = ForeignPtr CLeaf3'
--type Leaf3 = GenNode2 CLeaf3
--foreign import ccall "ql.h &qlFreeNode0" qlFreeNode0 :: FinalizerPtr CNode0'
--foreign import ccall "ql.h &qlFreeLeaf1" qlFreeLeaf1 :: FinalizerPtr CLeaf1'
--foreign import ccall "ql.h &qlFreeNode1" qlFreeNode1 :: FinalizerPtr CNode1'
--foreign import ccall "ql.h &qlFreeLeaf2" qlFreeLeaf2 :: FinalizerPtr CLeaf2'
--foreign import ccall "ql.h &qlFreeNode2" qlFreeNode2 :: FinalizerPtr CNode2'
--foreign import ccall "ql.h &qlFreeLeaf3" qlFreeLeaf3 :: FinalizerPtr CLeaf3'
--metaNode0 :: Meta CNode0'
--metaNode0 = Meta qlFreeNode0
--metaLeaf1 :: Meta CLeaf1'
--metaLeaf1 = Meta qlFreeLeaf1
--metaNode1 :: Meta CNode1'
--metaNode1 = Meta qlFreeNode1
--metaLeaf2 :: Meta CLeaf2'
--metaLeaf2 = Meta qlFreeLeaf2
--metaNode2 :: Meta CNode2'
--metaNode2 = Meta qlFreeNode2
--metaLeaf3 :: Meta CLeaf3'
--metaLeaf3 = Meta qlFreeLeaf3
--foreign import ccall "ql.h qlLeaf1AsNode0" qlLeaf1AsNode0 :: Ptr CLeaf1' -> IO (Ptr CNode0')
--foreign import ccall "ql.h qlNode1AsNode0" qlNode1AsNode0 :: Ptr CNode1' -> IO (Ptr CNode0')
--foreign import ccall "ql.h qlLeaf2AsNode1" qlLeaf2AsNode1 :: Ptr CLeaf2' -> IO (Ptr CNode1')
--foreign import ccall "ql.h qlNode2AsNode1" qlNode2AsNode1 :: Ptr CNode2' -> IO (Ptr CNode1')
--foreign import ccall "ql.h qlLeaf3AsNode2" qlLeaf3AsNode2 :: Ptr CLeaf3' -> IO (Ptr CNode2')
--upcastLeaf1 :: Upcast CLeaf1' CNode0'
--upcastLeaf1 = Upcast qlLeaf1AsNode0 qlFreeNode0
--upcastNode1 :: Upcast CNode1' CNode0'
--upcastNode1 = Upcast qlNode1AsNode0 qlFreeNode0
--upcastLeaf2 :: Upcast CLeaf2' CNode1'
--upcastLeaf2 = Upcast qlLeaf2AsNode1 qlFreeNode1
--upcastNode2 :: Upcast CNode2' CNode1'
--upcastNode2 = Upcast qlNode2AsNode1 qlFreeNode1
--upcastLeaf3 :: Upcast CLeaf3' CNode2'
--upcastLeaf3 = Upcast qlLeaf3AsNode2 qlFreeNode2
--asNode0 :: GenNode0 a -> IO Node0
--asNode0 (GenNode0 (GenForeignPtr x w)) = w x peekNode0
--peekNode0 :: Ptr CNode0' -> IO Node0
--peekNode0 = GenNode0 <.> newCastForeignPtr metaNode0
--withNode0 :: GenNode0 a -> (Ptr CNode0' -> IO b) -> IO b
--withNode0 (GenNode0 (GenForeignPtr x w)) = w x
--withNode0Descendant :: GenNode0 (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
--withNode0Descendant (GenNode0 (GenForeignPtr x _)) = withForeignPtr x
--peekLeaf1 :: Ptr CLeaf1' -> IO Leaf1
--peekLeaf1 = GenNode0 <.> newGenForeignPtr metaLeaf1 upcastLeaf1
--asNode1 :: GenNode1 a -> IO Node1
--asNode1 (GenNode0 (GenForeignPtr (Node1Descendant (GenForeignPtr x w)) _)) = w x peekNode1
--peekNode1 :: Ptr CNode1' -> IO Node1
--peekNode1 = newCastForeignPtr metaNode1 >=> newNode1Descendant
--withNode1 :: GenNode1 a -> (Ptr CNode1' -> IO b) -> IO b
--withNode1 (GenNode0 (GenForeignPtr (Node1Descendant (GenForeignPtr x w)) _)) = w x
--withMaybeNode1 :: Maybe (GenNode1 a) -> (Ptr CNode1' -> IO b) -> IO b
--withMaybeNode1 x f = maybe (f nullPtr) (`withNode1` f) x
--marshalNode1 :: Node1Descendant a -> (Ptr CNode0' -> IO b) -> IO b
--marshalNode1 (Node1Descendant o) = withGenForeignPtr upcastNode1 o
--newNode1Descendant :: GenForeignPtr a CNode1' -> IO (GenNode1 a)
--newNode1Descendant p = GenNode0 <^> GenForeignPtr (Node1Descendant p) marshalNode1
--peekNode1Descendant :: Meta a -> Upcast a CNode1' -> Ptr a -> IO (GenNode1 (ForeignPtr a))
--peekNode1Descendant m u = newGenForeignPtr m u >=> newNode1Descendant
--withNode1Descendant :: GenNode1 (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
--withNode1Descendant (GenNode0 (GenForeignPtr (Node1Descendant (GenForeignPtr x _)) _)) = withForeignPtr x
--peekLeaf2 :: Ptr CLeaf2' -> IO Leaf2
--peekLeaf2 = peekNode1Descendant metaLeaf2 upcastLeaf2
----withLeaf2 :: Leaf2 -> (Ptr CLeaf2' -> IO b) -> IO b
----withLeaf2 (GenNode0 (GenForeignPtr (Node1Descendant (GenForeignPtr x _)) _)) = withForeignPtr x
--asNode2 :: GenNode2 a -> IO Node2
--asNode2 (GenNode0 (GenForeignPtr (Node1Descendant (GenForeignPtr (Node2Descendant (GenForeignPtr x w)) _)) _)) = w x peekNode2
--peekNode2 :: Ptr CNode2' -> IO Node2
--peekNode2 = newCastForeignPtr metaNode2 >=> newNode2Descendant
--withNode2 :: GenNode2 a -> (Ptr CNode2' -> IO b) -> IO b
--withNode2 (GenNode0 (GenForeignPtr (Node1Descendant (GenForeignPtr (Node2Descendant (GenForeignPtr x w)) _)) _)) = w x
--marshalNode2 :: Node2Descendant a -> (Ptr CNode1' -> IO b) -> IO b
--marshalNode2 (Node2Descendant o) = withGenForeignPtr upcastNode2 o
--newNode2Descendant :: GenForeignPtr a CNode2' -> IO (GenNode2 a)
--newNode2Descendant p = GenNode0 <^> GenForeignPtr (Node1Descendant $ GenForeignPtr (Node2Descendant p) marshalNode2) marshalNode1
--peekLeaf3 :: Ptr CLeaf3' -> IO Leaf3
--peekLeaf3 = newGenForeignPtr metaLeaf3 upcastLeaf3 >=> newNode2Descendant
----withLeaf3 :: Leaf3 -> (Ptr CLeaf3' -> IO b) -> IO b
----withLeaf3 (GenNode0 (GenForeignPtr (Node1Descendant (GenForeignPtr (Node2Descendant (GenForeignPtr x _)) _)) _)) = withForeignPtr x

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
