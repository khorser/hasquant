{-# LANGUAGE RankNTypes, DuplicateRecordFields, TypeFamilies #-}
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
  , CQuote'
  , Quote
  , asQuote
  , peekQuote
  , withQuote
  , withGenQuote
  , withMaybeQuote
  , withQuoteArray
  , withQuoteArrayRaw
  , CSimpleQuote
  , CSimpleQuote'
  , SimpleQuote
  , peekSimpleQuote

  , GenLeg
  , CLeg
  , CLeg'
  , Leg
  , asLeg
  , peekLeg
  , withLeg
  , withGenLeg
  , withLegArray
  , CCouponLeg
  , CCouponLeg'
  , CouponLeg
  , peekCouponLeg

  , GenRateHelper
  , CRateHelper
  , CRateHelper'
  , RateHelper
  , asRateHelper
  , peekRateHelper
  , withRateHelper
  , withGenRateHelper
  , withRateHelperArray
  , CBondHelper
  , CBondHelper'
  , BondHelper
  , peekBondHelper
  , withBondHelperArray
  , CSwapRateHelper
  , CSwapRateHelper'
  , SwapRateHelper
  , peekSwapRateHelper
  , COISRateHelper
  , COISRateHelper'
  , OISRateHelper
  , peekOISRateHelper

  , GenCalibrationHelper
  , CCalibrationHelper
  , CCalibrationHelper'
  , CalibrationHelper
  , asCalibrationHelper
  , peekCalibrationHelper
  , withCalibrationHelper
  , withGenCalibrationHelper
  , withCalibrationHelperArray
  , CBlackCalibrationHelper
  , CBlackCalibrationHelper'
  , BlackCalibrationHelper
  , peekBlackCalibrationHelper

  , GenBlackCalculator
  , CBlackCalculator
  , CBlackCalculator'
  , BlackCalculator
  , asBlackCalculator
  , peekBlackCalculator
  , withBlackCalculator
  , CBlackScholesCalculator
  , CBlackScholesCalculator'
  , BlackScholesCalculator
  , peekBlackScholesCalculator
  , withGenBlackCalculator

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
  , withGenTermStructure
  , GenVolatilityTermStructure
  , VolatilityTermStructure
  , CVolatilityTermStructure
  , CVolatilityTermStructure'
  , peekVolatilityTermStructure
  , withVolatilityTermStructure
  , withGenVolatilityTermStructure
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
  , withGenStochasticProcess1D
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
  , withGenStochasticProcess
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
  , GenAffineModel
  , CAffineModel
  , CAffineModel'
  , asCalibratedModel
  , asBatesDoubleExpModel
  , asBatesModel
  , asOneFactorAffineModel
  , asShortRateModel
  , asHestonModel
  , peekAffineModel
  , withAffineModel
  , asAffineModel
  , BatesDetJumpModel
  , CBatesDetJumpModel
  , CBatesDetJumpModel'
  , peekBatesDetJumpModel
  , withBatesDetJumpModel
  , BatesDoubleExpDetJumpModel
  , CBatesDoubleExpDetJumpModel
  , CBatesDoubleExpDetJumpModel'
  , peekBatesDoubleExpDetJumpModel
  , withBatesDoubleExpDetJumpModel
  , BatesDoubleExpModel
  , GenBatesDoubleExpModel
  , CBatesDoubleExpModel
  , CBatesDoubleExpModel'
  , peekBatesDoubleExpModel
  , withBatesDoubleExpModel
  , BatesModel
  , GenBatesModel
  , CBatesModel
  , CBatesModel'
  , peekBatesModel
  , withBatesModel
  , CalibratedModel
  , GenCalibratedModel
  , CCalibratedModel
  , CCalibratedModel'
  , peekCalibratedModel
  , withCalibratedModel
  , withGenCalibratedModel
  , G2
  , CG2
  , CG2'
  , peekG2
  , withG2
  , GJRGARCHModel
  , CGJRGARCHModel
  , CGJRGARCHModel'
  , peekGJRGARCHModel
  , HestonModel
  , GenHestonModel
  , CHestonModel
  , CHestonModel'
  , peekHestonModel
  , withHestonModel
  , HullWhite
  , CHullWhite
  , CHullWhite'
  , peekHullWhite
  , withHullWhite
  , PiecewiseTimeDependentHestonModel
  , CPiecewiseTimeDependentHestonModel
  , CPiecewiseTimeDependentHestonModel'
  , peekPiecewiseTimeDependentHestonModel
  , ShortRateModel
  , GenShortRateModel
  , CShortRateModel
  , CShortRateModel'
  , peekShortRateModel
  , withShortRateModel
  , OneFactorAffineModel
  , GenOneFactorAffineModel
  , COneFactorAffineModel
  , COneFactorAffineModel'
  , peekOneFactorAffineModel
  , withOneFactorAffineModel
  , LiborForwardModel
  , CLiborForwardModel
  , CLiborForwardModel'
  , peekLiborForwardModel

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
  ) where
import Foreign.Ptr
import Foreign.ForeignPtr
import Foreign.C.Types
import Foreign.C.String
import Foreign.Marshal.Array(withArray)
import Foreign.Marshal.Utils(withMany)

import Data.Functor((<&>))
import Control.Monad((>=>))
import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Internal

(<.>) :: Functor f => (b -> r) -> (a -> f b) -> a -> f r
f1 <.> f2 = fmap f1 . f2

(<^>) :: Applicative f => (a -> b) -> a -> f b
f <^> x = pure $ f x

-- STANDALONE TYPES
newtype Standalone a = Standalone {_ptr :: ForeignPtr a}
class Finalizable a where
  finalize :: FinalizerPtr a
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
-- the original pointer to a with a way to marshal it to b
-- Actually we don't need the second field as we can infer the number of upcasts needed from the structure of the objects
data GenForeignPtr a b = GenForeignPtr {_ptr :: !a, _marshal :: !(forall r. a -> (Ptr b -> IO r) -> IO r)}
class Upcastable a where
  type Base a
  upcast :: Ptr a -> IO (Ptr (Base a))

withCastForeignPtr :: Upcastable c => (a -> (Ptr c -> IO r) -> IO r) -> a -> (Ptr (Base c) -> IO r) -> IO r
withCastForeignPtr w p f = w p $ upcast >=> f

withGenForeignPtr :: Upcastable b => GenForeignPtr a b -> (Ptr (Base b) -> IO r) -> IO r
withGenForeignPtr (GenForeignPtr p w) = withCastForeignPtr w p

newGenForeignPtr :: (Finalizable a, Upcastable a) => Ptr a -> IO (GenForeignPtr (ForeignPtr a) (Base a))
newGenForeignPtr x = newForeignPtr finalize x <&> (`GenForeignPtr` withCastForeignPtr withForeignPtr)

newCastForeignPtr :: Finalizable a => Ptr a -> IO (GenForeignPtr (ForeignPtr a) a)
newCastForeignPtr x = newForeignPtr finalize x <&> (`GenForeignPtr` withForeignPtr)

withGenArray :: (a -> (Ptr c -> IO r) -> IO r) -> [a] -> ((CUInt, Ptr (Ptr c)) -> IO r) -> IO r
withGenArray m x f = withMany m x (`withArray` (\p -> f (fromIntegral $ length x, p)))

data CQuote'
data CSimpleQuote'
newtype GenQuote a = GenQuote (GenForeignPtr a CQuote')
type CQuote = ForeignPtr CQuote'
type Quote = GenQuote CQuote
type CSimpleQuote = ForeignPtr CSimpleQuote'
type SimpleQuote = GenQuote CSimpleQuote
foreign import ccall "ql.h &qlFreeQuote" qlFreeQuote :: FinalizerPtr CQuote'
foreign import ccall "ql.h &qlFreeSimpleQuote" qlFreeSimpleQuote :: FinalizerPtr CSimpleQuote'
instance Finalizable CQuote' where finalize = qlFreeQuote
instance Finalizable CSimpleQuote' where finalize = qlFreeSimpleQuote
instance Upcastable CSimpleQuote' where {type Base CSimpleQuote' = CQuote'; upcast = qlSimpleQuoteAsQuote}
foreign import ccall "ql.h qlSimpleQuoteAsQuote" qlSimpleQuoteAsQuote :: Ptr CSimpleQuote' -> IO (Ptr CQuote')
-- Haskell does not allow function arguments like [forall a.GenQuote a]
-- let's at least provide a way to convert all quote classes to the most generic one
asQuote :: GenQuote a -> IO Quote
asQuote (GenQuote (GenForeignPtr x w)) = w x peekQuote
peekQuote :: Ptr CQuote' -> IO Quote
peekQuote = GenQuote <.> newCastForeignPtr
withQuote :: GenQuote a -> (Ptr CQuote' -> IO b) -> IO b
withQuote (GenQuote (GenForeignPtr x w)) = w x
withGenQuote :: GenQuote (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenQuote (GenQuote (GenForeignPtr x _)) = withForeignPtr x
peekSimpleQuote :: Ptr CSimpleQuote' -> IO SimpleQuote
peekSimpleQuote = GenQuote <.> newGenForeignPtr
withMaybeQuote :: Maybe (GenQuote a) -> (Ptr CQuote' -> IO b) -> IO b
withMaybeQuote x f = maybe (f nullPtr) (`withQuote` f) x
withQuoteArray :: [GenQuote a] -> ((CUInt, Ptr (Ptr CQuote')) -> IO b) -> IO b
withQuoteArray = withGenArray withQuote
withQuoteArrayRaw :: [GenQuote a] -> (Ptr (Ptr CQuote') -> IO b) -> IO b
withQuoteArrayRaw x f= withMany withQuote x (`withArray` f)

data CLeg'
data CCouponLeg'
newtype GenLeg a = GenLeg (GenForeignPtr a CLeg')
type CLeg = ForeignPtr CLeg'
type Leg = GenLeg CLeg
type CCouponLeg = ForeignPtr CCouponLeg'
type CouponLeg = GenLeg CCouponLeg
foreign import ccall "ql.h &qlFreeLeg" qlFreeLeg :: FinalizerPtr CLeg'
foreign import ccall "ql.h &qlFreeCouponLeg" qlFreeCouponLeg :: FinalizerPtr CCouponLeg'
instance Finalizable CLeg' where finalize = qlFreeLeg
instance Finalizable CCouponLeg' where finalize = qlFreeCouponLeg
foreign import ccall "ql.h qlCouponLegAsLeg" qlCouponLegAsLeg :: Ptr CCouponLeg' -> IO (Ptr CLeg')
instance Upcastable CCouponLeg' where {type Base CCouponLeg' = CLeg'; upcast = qlCouponLegAsLeg}
asLeg :: GenLeg a -> IO Leg
asLeg (GenLeg (GenForeignPtr x w)) = w x peekLeg
peekLeg :: Ptr CLeg' -> IO Leg
peekLeg = GenLeg <.> newCastForeignPtr
withLeg :: GenLeg a -> (Ptr CLeg' -> IO b) -> IO b
withLeg (GenLeg (GenForeignPtr x w)) = w x
withLegArray :: [GenLeg a] -> ((CUInt, Ptr (Ptr CLeg')) -> IO b) -> IO b
withLegArray = withGenArray withLeg
withGenLeg :: GenLeg (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenLeg (GenLeg (GenForeignPtr x _)) = withForeignPtr x
peekCouponLeg :: Ptr CCouponLeg' -> IO CouponLeg
peekCouponLeg = GenLeg <.> newGenForeignPtr

data CRateHelper'
newtype GenRateHelper a = GenRateHelper (GenForeignPtr a CRateHelper')
type CRateHelper = ForeignPtr CRateHelper'
type RateHelper = GenRateHelper CRateHelper
foreign import ccall "ql.h &qlFreeRateHelper" qlFreeRateHelper :: FinalizerPtr CRateHelper'
instance Finalizable CRateHelper' where finalize = qlFreeRateHelper
asRateHelper :: GenRateHelper a -> IO RateHelper
asRateHelper (GenRateHelper (GenForeignPtr x w)) = w x peekRateHelper
peekRateHelper :: Ptr CRateHelper' -> IO RateHelper
peekRateHelper = GenRateHelper <.> newCastForeignPtr
withRateHelper :: GenRateHelper a -> (Ptr CRateHelper' -> IO b) -> IO b
withRateHelper (GenRateHelper (GenForeignPtr x w)) = w x
withGenRateHelper :: GenRateHelper (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenRateHelper (GenRateHelper (GenForeignPtr x _)) = withForeignPtr x
withRateHelperArray :: [GenRateHelper a] -> ((CUInt, Ptr (Ptr CRateHelper')) -> IO b) -> IO b
withRateHelperArray = withGenArray withRateHelper
data CBondHelper'
type CBondHelper = ForeignPtr CBondHelper'
type BondHelper = GenRateHelper CBondHelper
foreign import ccall "ql.h &qlFreeBondHelper" qlFreeBondHelper :: FinalizerPtr CBondHelper'
instance Finalizable CBondHelper' where finalize = qlFreeBondHelper
foreign import ccall "ql.h qlBondHelperAsRateHelper" qlBondHelperAsRateHelper :: Ptr CBondHelper' -> IO (Ptr CRateHelper')
instance Upcastable CBondHelper' where {type Base CBondHelper' = CRateHelper'; upcast = qlBondHelperAsRateHelper}
peekBondHelper :: Ptr CBondHelper' -> IO BondHelper
peekBondHelper = GenRateHelper <.> newGenForeignPtr
withBondHelperArray :: [BondHelper] -> ((CUInt, Ptr (Ptr CBondHelper')) -> IO b) -> IO b
withBondHelperArray = withGenArray withGenRateHelper
data CSwapRateHelper'
type CSwapRateHelper = ForeignPtr CSwapRateHelper'
type SwapRateHelper = GenRateHelper CSwapRateHelper
foreign import ccall "ql.h &qlFreeSwapRateHelper" qlFreeSwapRateHelper :: FinalizerPtr CSwapRateHelper'
instance Finalizable CSwapRateHelper' where finalize = qlFreeSwapRateHelper
foreign import ccall "ql.h qlSwapRateHelperAsRateHelper" qlSwapRateHelperAsRateHelper :: Ptr CSwapRateHelper' -> IO (Ptr CRateHelper')
instance Upcastable CSwapRateHelper' where {type Base CSwapRateHelper' = CRateHelper'; upcast = qlSwapRateHelperAsRateHelper}
peekSwapRateHelper :: Ptr CSwapRateHelper' -> IO SwapRateHelper
peekSwapRateHelper = GenRateHelper <.> newGenForeignPtr
data COISRateHelper'
type COISRateHelper = ForeignPtr COISRateHelper'
type OISRateHelper = GenRateHelper COISRateHelper
foreign import ccall "ql.h &qlFreeOISRateHelper" qlFreeOISRateHelper :: FinalizerPtr COISRateHelper'
instance Finalizable COISRateHelper' where finalize = qlFreeOISRateHelper
foreign import ccall "ql.h qlOISRateHelperAsRateHelper" qlOISRateHelperAsRateHelper :: Ptr COISRateHelper' -> IO (Ptr CRateHelper')
instance Upcastable COISRateHelper' where {type Base COISRateHelper' = CRateHelper'; upcast = qlOISRateHelperAsRateHelper}
peekOISRateHelper :: Ptr COISRateHelper' -> IO OISRateHelper
peekOISRateHelper = GenRateHelper <.> newGenForeignPtr

data CCalibrationHelper'
data CBlackCalibrationHelper'
newtype GenCalibrationHelper a = GenCalibrationHelper (GenForeignPtr a CCalibrationHelper')
type CCalibrationHelper = ForeignPtr CCalibrationHelper'
type CalibrationHelper = GenCalibrationHelper CCalibrationHelper
type CBlackCalibrationHelper = ForeignPtr CBlackCalibrationHelper'
type BlackCalibrationHelper = GenCalibrationHelper CBlackCalibrationHelper
foreign import ccall "ql.h &qlFreeCalibrationHelper" qlFreeCalibrationHelper :: FinalizerPtr CCalibrationHelper'
foreign import ccall "ql.h &qlFreeBlackCalibrationHelper" qlFreeBlackCalibrationHelper :: FinalizerPtr CBlackCalibrationHelper'
instance Finalizable CCalibrationHelper' where finalize = qlFreeCalibrationHelper
instance Finalizable CBlackCalibrationHelper' where finalize = qlFreeBlackCalibrationHelper
foreign import ccall "ql.h qlBlackCalibrationHelperAsCalibrationHelper" qlBlackCalibrationHelperAsCalibrationHelper :: Ptr CBlackCalibrationHelper' -> IO (Ptr CCalibrationHelper')
instance Upcastable CBlackCalibrationHelper' where {type Base CBlackCalibrationHelper' = CCalibrationHelper'; upcast = qlBlackCalibrationHelperAsCalibrationHelper}
asCalibrationHelper :: GenCalibrationHelper a -> IO CalibrationHelper
asCalibrationHelper (GenCalibrationHelper (GenForeignPtr x w)) = w x peekCalibrationHelper
peekCalibrationHelper :: Ptr CCalibrationHelper' -> IO CalibrationHelper
peekCalibrationHelper = GenCalibrationHelper <.> newCastForeignPtr
withCalibrationHelper :: GenCalibrationHelper a -> (Ptr CCalibrationHelper' -> IO b) -> IO b
withCalibrationHelper (GenCalibrationHelper (GenForeignPtr x w)) = w x
withGenCalibrationHelper :: GenCalibrationHelper (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenCalibrationHelper (GenCalibrationHelper (GenForeignPtr x _)) = withForeignPtr x
peekBlackCalibrationHelper :: Ptr CBlackCalibrationHelper' -> IO BlackCalibrationHelper
peekBlackCalibrationHelper = GenCalibrationHelper <.> newGenForeignPtr
withCalibrationHelperArray :: [GenCalibrationHelper a] -> ((CUInt, Ptr (Ptr CCalibrationHelper')) -> IO b) -> IO b
withCalibrationHelperArray = withGenArray withCalibrationHelper

data CBlackCalculator'
data CBlackScholesCalculator'
newtype GenBlackCalculator a = GenBlackCalculator (GenForeignPtr a CBlackCalculator')
type CBlackCalculator = ForeignPtr CBlackCalculator'
type BlackCalculator = GenBlackCalculator CBlackCalculator
type CBlackScholesCalculator = ForeignPtr CBlackScholesCalculator'
type BlackScholesCalculator = GenBlackCalculator CBlackScholesCalculator
foreign import ccall "ql.h &qlFreeBlackCalculator" qlFreeBlackCalculator :: FinalizerPtr CBlackCalculator'
foreign import ccall "ql.h &qlFreeBlackScholesCalculator" qlFreeBlackScholesCalculator :: FinalizerPtr CBlackScholesCalculator'
instance Finalizable CBlackCalculator' where finalize = qlFreeBlackCalculator
instance Finalizable CBlackScholesCalculator' where finalize = qlFreeBlackScholesCalculator
foreign import ccall "ql.h qlBlackScholesCalculatorAsBlackCalculator" qlBlackScholesCalculatorAsBlackCalculator :: Ptr CBlackScholesCalculator' -> IO (Ptr CBlackCalculator')
instance Upcastable CBlackScholesCalculator' where {type Base CBlackScholesCalculator' = CBlackCalculator'; upcast = qlBlackScholesCalculatorAsBlackCalculator}
asBlackCalculator :: GenBlackCalculator a -> IO BlackCalculator
asBlackCalculator (GenBlackCalculator (GenForeignPtr x w)) = w x peekBlackCalculator
peekBlackCalculator :: Ptr CBlackCalculator' -> IO BlackCalculator
peekBlackCalculator = GenBlackCalculator <.> newCastForeignPtr
withBlackCalculator :: GenBlackCalculator a -> (Ptr CBlackCalculator' -> IO b) -> IO b
withBlackCalculator (GenBlackCalculator (GenForeignPtr x w)) = w x
withGenBlackCalculator :: GenBlackCalculator (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenBlackCalculator (GenBlackCalculator (GenForeignPtr x _)) = withForeignPtr x
peekBlackScholesCalculator :: Ptr CBlackScholesCalculator' -> IO BlackScholesCalculator
peekBlackScholesCalculator = GenBlackCalculator <.> newGenForeignPtr

-- MULTILEVEL HIERARCHIES
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
-- to make types in error messages a bit pretty
newtype AnyInterestRateIndex a = AnyInterestRateIndex (GenForeignPtr a CInterestRateIndex')
type GenInterestRateIndex a = GenIndex (AnyInterestRateIndex a)
type CInterestRateIndex = ForeignPtr CInterestRateIndex'
type InterestRateIndex = GenInterestRateIndex CInterestRateIndex
type CBMAIndex = ForeignPtr CBMAIndex'
type BMAIndex = GenInterestRateIndex CBMAIndex
newtype AnyIborIndex a = AnyIborIndex (GenForeignPtr a CIborIndex')
type GenIborIndex a = GenInterestRateIndex (AnyIborIndex a)
type CIborIndex = ForeignPtr CIborIndex'
type IborIndex = GenIborIndex CIborIndex
type COvernightIndex = ForeignPtr COvernightIndex'
type OvernightIborIndex = GenIborIndex COvernightIndex
newtype AnySwapIndex a = AnySwapIndex (GenForeignPtr a CSwapIndex')
type GenSwapIndex a = GenInterestRateIndex (AnySwapIndex a)
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
instance Finalizable CIndex' where finalize = qlFreeIndex
instance Finalizable CInterestRateIndex' where finalize = qlFreeInterestRateIndex
instance Finalizable CBMAIndex' where finalize = qlFreeBMAIndex
instance Finalizable CIborIndex' where finalize = qlFreeIborIndex
instance Finalizable COvernightIndex' where finalize = qlFreeOvernightIborIndex
instance Finalizable CSwapIndex' where finalize = qlFreeSwapIndex
instance Finalizable COvernightIndexedSwapIndex' where finalize = qlFreeOvernightIndexedSwapIndex
foreign import ccall "ql.h qlInterestRateIndexAsIndex" qlInterestRateIndexAsIndex :: Ptr CInterestRateIndex' -> IO (Ptr CIndex')
foreign import ccall "ql.h qlBMAIndexAsInterestRateIndex" qlBMAIndexAsInterestRateIndex :: Ptr CBMAIndex' -> IO (Ptr CInterestRateIndex')
foreign import ccall "ql.h qlIborIndexAsInterestRateIndex" qlIborIndexAsInterestRateIndex :: Ptr CIborIndex' -> IO (Ptr CInterestRateIndex')
foreign import ccall "ql.h qlOvernightIndexAsIborIndex" qlOvernightIndexAsIborIndex :: Ptr COvernightIndex' -> IO (Ptr CIborIndex')
foreign import ccall "ql.h qlSwapIndexAsInterestRateIndex" qlSwapIndexAsInterestRateIndex :: Ptr CSwapIndex' -> IO (Ptr CInterestRateIndex')
foreign import ccall "ql.h qlOvernightIndexedSwapIndexAsSwapIndex" qlOvernightIndexedSwapIndexAsSwapIndex :: Ptr COvernightIndexedSwapIndex' -> IO (Ptr CSwapIndex')
instance Upcastable CInterestRateIndex' where {type Base CInterestRateIndex' = CIndex'; upcast = qlInterestRateIndexAsIndex}
instance Upcastable CBMAIndex' where {type Base CBMAIndex' = CInterestRateIndex'; upcast = qlBMAIndexAsInterestRateIndex}
instance Upcastable CIborIndex' where {type Base CIborIndex' = CInterestRateIndex'; upcast = qlIborIndexAsInterestRateIndex}
instance Upcastable COvernightIndex' where {type Base COvernightIndex' = CIborIndex'; upcast = qlOvernightIndexAsIborIndex}
instance Upcastable CSwapIndex' where {type Base CSwapIndex' = CInterestRateIndex'; upcast = qlSwapIndexAsInterestRateIndex}
instance Upcastable COvernightIndexedSwapIndex' where {type Base COvernightIndexedSwapIndex' = CSwapIndex'; upcast = qlOvernightIndexedSwapIndexAsSwapIndex}
asIndex :: GenIndex a -> IO Index
asIndex (GenIndex (GenForeignPtr x w)) = w x (GenIndex <.> newCastForeignPtr)
withIndex :: GenIndex a -> (Ptr CIndex' -> IO b) -> IO b
withIndex (GenIndex (GenForeignPtr x w)) = w x

asInterestRateIndex :: GenInterestRateIndex a -> IO InterestRateIndex
asInterestRateIndex (GenIndex (GenForeignPtr (AnyInterestRateIndex (GenForeignPtr x w)) _)) = w x peekInterestRateIndex
  where peekInterestRateIndex = newCastForeignPtr >=> newGenInterestRateIndex
withInterestRateIndex :: GenInterestRateIndex a -> (Ptr CInterestRateIndex' -> IO b) -> IO b
withInterestRateIndex (GenIndex (GenForeignPtr (AnyInterestRateIndex (GenForeignPtr x w)) _)) = w x
withGenForeignInterestRateIndex :: AnyInterestRateIndex a -> (Ptr CIndex' -> IO b) -> IO b
withGenForeignInterestRateIndex (AnyInterestRateIndex o) = withGenForeignPtr o
newGenInterestRateIndex :: GenForeignPtr a CInterestRateIndex' -> IO (GenInterestRateIndex a)
newGenInterestRateIndex p = GenIndex <^> GenForeignPtr (AnyInterestRateIndex p) withGenForeignInterestRateIndex

peekBMAIndex :: Ptr CBMAIndex' -> IO BMAIndex
peekBMAIndex = newGenForeignPtr >=> newGenInterestRateIndex
withBMAIndex :: BMAIndex -> (Ptr CBMAIndex' -> IO b) -> IO b
withBMAIndex (GenIndex (GenForeignPtr (AnyInterestRateIndex (GenForeignPtr x _)) _)) = withForeignPtr x

asIborIndex :: GenIborIndex a -> IO IborIndex
asIborIndex (GenIndex (GenForeignPtr (AnyInterestRateIndex (GenForeignPtr (AnyIborIndex (GenForeignPtr x w)) _)) _)) = w x peekIborIndex
peekIborIndex :: Ptr CIborIndex' -> IO IborIndex
peekIborIndex = newCastForeignPtr >=> newGenIborIndex
withIborIndex :: GenIborIndex a -> (Ptr CIborIndex' -> IO b) -> IO b
withIborIndex (GenIndex (GenForeignPtr (AnyInterestRateIndex (GenForeignPtr (AnyIborIndex (GenForeignPtr x w)) _)) _)) = w x
withGenForeignIborIndex :: AnyIborIndex a -> (Ptr CInterestRateIndex' -> IO b) -> IO b
withGenForeignIborIndex (AnyIborIndex o) = withGenForeignPtr o
newGenIborIndex :: GenForeignPtr a CIborIndex' -> IO (GenIborIndex a)
newGenIborIndex p = GenIndex <^> GenForeignPtr (AnyInterestRateIndex $ GenForeignPtr (AnyIborIndex p) withGenForeignIborIndex) withGenForeignInterestRateIndex

peekOvernightIborIndex :: Ptr COvernightIndex' -> IO OvernightIborIndex
peekOvernightIborIndex = newGenForeignPtr >=> newGenIborIndex
withOvernightIborIndex :: OvernightIborIndex -> (Ptr COvernightIndex' -> IO b) -> IO b
withOvernightIborIndex (GenIndex (GenForeignPtr (AnyInterestRateIndex (GenForeignPtr (AnyIborIndex (GenForeignPtr x _)) _)) _)) = withForeignPtr x

asSwapIndex :: GenSwapIndex a -> IO SwapIndex
asSwapIndex (GenIndex (GenForeignPtr (AnyInterestRateIndex (GenForeignPtr (AnySwapIndex (GenForeignPtr x w)) _)) _)) = w x peekSwapIndex
peekSwapIndex :: Ptr CSwapIndex' -> IO SwapIndex
peekSwapIndex = newCastForeignPtr >=> newGenSwapIndex
withSwapIndex :: GenSwapIndex a -> (Ptr CSwapIndex' -> IO b) -> IO b
withSwapIndex (GenIndex (GenForeignPtr (AnyInterestRateIndex (GenForeignPtr (AnySwapIndex (GenForeignPtr x w)) _)) _)) = w x
withGenForeignSwapIndex :: AnySwapIndex a -> (Ptr CInterestRateIndex' -> IO b) -> IO b
withGenForeignSwapIndex (AnySwapIndex o) = withGenForeignPtr o
newGenSwapIndex :: GenForeignPtr a CSwapIndex' -> IO (GenSwapIndex a)
newGenSwapIndex p = GenIndex <^> GenForeignPtr (AnyInterestRateIndex $ GenForeignPtr (AnySwapIndex p) withGenForeignSwapIndex) withGenForeignInterestRateIndex

peekOvernightIndexedSwapIndex :: Ptr COvernightIndexedSwapIndex' -> IO OvernightIndexedSwapIndex
peekOvernightIndexedSwapIndex = newGenForeignPtr >=> newGenSwapIndex
withOvernightIndexedSwapIndex :: OvernightIndexedSwapIndex -> (Ptr COvernightIndexedSwapIndex' -> IO b) -> IO b
withOvernightIndexedSwapIndex (GenIndex (GenForeignPtr (AnyInterestRateIndex (GenForeignPtr (AnySwapIndex (GenForeignPtr x _)) _)) _)) = withForeignPtr x

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
newtype AnyYieldTermStructure a = AnyYieldTermStructure {getYieldTermStructure :: GenForeignPtr a CYieldTermStructure'}
type GenYieldTermStructure a = GenTermStructure (AnyYieldTermStructure a)
type CYieldTermStructure = ForeignPtr CYieldTermStructure'
type YieldTermStructure = GenYieldTermStructure CYieldTermStructure
type CFittedBondDiscountCurve = ForeignPtr CFittedBondDiscountCurve'
type FittedBondDiscountCurve = GenYieldTermStructure CFittedBondDiscountCurve
newtype AnyVolatilityTermStructure a = AnyVolatilityTermStructure {getVolatilityTermStructure :: GenForeignPtr a CVolatilityTermStructure'}
type GenVolatilityTermStructure a = GenTermStructure (AnyVolatilityTermStructure a)
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
newtype AnyBlackVolTermStructure a = AnyBlackVolTermStructure {getBlackVolTermStructure :: GenForeignPtr a CBlackVolTermStructure'}
type GenBlackVolTermStructure a = GenVolatilityTermStructure (AnyBlackVolTermStructure a)
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
instance Finalizable CTermStructure' where finalize = qlFreeTermStructure
instance Finalizable CVolatilityTermStructure' where finalize = qlFreeVolatilityTermStructure
instance Finalizable COptionletVolatilityStructure' where finalize = qlFreeOptionletVolatilityStructure
instance Finalizable CSwaptionVolatilityStructure' where finalize = qlFreeSwaptionVolatilityStructure
instance Finalizable CCapFloorTermVolSurface' where finalize = qlFreeCapFloorTermVolSurface
instance Finalizable CLocalVolTermStructure' where finalize = qlFreeLocalVolTermStructure
instance Finalizable CBlackVolTermStructure' where finalize = qlFreeBlackVolTermStructure
instance Finalizable CBlackVarianceCurve' where finalize = qlFreeBlackVarianceCurve
instance Finalizable CYieldTermStructure' where finalize = qlFreeYieldTermStructure
instance Finalizable CFittedBondDiscountCurve' where finalize = qlFreeFittedBondDiscountCurve
instance Finalizable CCallableBondVolatilityStructure' where finalize = qlFreeCallableBondVolatilityStructure
instance Finalizable CDefaultProbabilityTermStructure' where finalize = qlFreeDefaultProbabilityTermStructure
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
instance Upcastable CYieldTermStructure' where {type Base CYieldTermStructure' = CTermStructure'; upcast = qlYieldTermStructureAsTermStructure}
instance Upcastable CFittedBondDiscountCurve' where {type Base CFittedBondDiscountCurve' = CYieldTermStructure'; upcast = qlFittedBondDiscountCurveAsYieldTermStructure}
instance Upcastable CVolatilityTermStructure' where {type Base CVolatilityTermStructure' = CTermStructure'; upcast = qlVolatilityTermStructureAsTermStructure}
instance Upcastable CCallableBondVolatilityStructure' where {type Base CCallableBondVolatilityStructure' = CTermStructure'; upcast = qlCallableBondVolatilityStructureAsTermStructure}
instance Upcastable CDefaultProbabilityTermStructure' where {type Base CDefaultProbabilityTermStructure' = CTermStructure'; upcast = qlDefaultProbabilityTermStructureAsTermStructure}
instance Upcastable CBlackVolTermStructure' where {type Base CBlackVolTermStructure' = CVolatilityTermStructure'; upcast = qlBlackVolTermStructureAsVolatilityTermStructure}
instance Upcastable CBlackVarianceCurve' where {type Base CBlackVarianceCurve' = CBlackVolTermStructure'; upcast = qlBlackVarianceCurveAsBlackVolTermStructure}
instance Upcastable COptionletVolatilityStructure' where {type Base COptionletVolatilityStructure' = CVolatilityTermStructure'; upcast = qlOptionletVolatilityStructureAsVolatilityTermStructure}
instance Upcastable CSwaptionVolatilityStructure' where {type Base CSwaptionVolatilityStructure' = CVolatilityTermStructure'; upcast = qlSwaptionVolatilityStructureAsVolatilityTermStructure}
instance Upcastable CCapFloorTermVolSurface' where {type Base CCapFloorTermVolSurface' = CVolatilityTermStructure'; upcast = qlCapFloorTermVolSurfaceAsVolatilityTermStructure}
instance Upcastable CLocalVolTermStructure' where {type Base CLocalVolTermStructure' = CVolatilityTermStructure'; upcast = qlLocalVolTermStructureAsVolatilityTermStructure}
asTermStructure :: GenTermStructure a -> IO TermStructure
asTermStructure (GenTermStructure (GenForeignPtr x w)) = w x (GenTermStructure <.> newCastForeignPtr)
withTermStructure :: GenTermStructure a  -> (Ptr CTermStructure' -> IO b) -> IO b
withTermStructure (GenTermStructure (GenForeignPtr x w)) = w x
withGenTermStructure :: GenTermStructure (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenTermStructure (GenTermStructure (GenForeignPtr x _)) = withForeignPtr x

asVolatilityTermStructure :: GenVolatilityTermStructure a -> IO VolatilityTermStructure
asVolatilityTermStructure (GenTermStructure (GenForeignPtr (AnyVolatilityTermStructure (GenForeignPtr x w)) _)) = w x peekVolatilityTermStructure
peekVolatilityTermStructure :: Ptr CVolatilityTermStructure' -> IO VolatilityTermStructure
peekVolatilityTermStructure = newCastForeignPtr >=> newGenVolatilityTermStructure
peekGenVolatilityTermStructure :: (Finalizable a, Upcastable a, Base a ~ CVolatilityTermStructure') => Ptr a -> IO (GenVolatilityTermStructure (ForeignPtr a))
peekGenVolatilityTermStructure = newGenForeignPtr >=> newGenVolatilityTermStructure
withVolatilityTermStructure :: GenVolatilityTermStructure a -> (Ptr CVolatilityTermStructure' -> IO b) -> IO b
withVolatilityTermStructure (GenTermStructure (GenForeignPtr (AnyVolatilityTermStructure (GenForeignPtr x w)) _)) = w x
withGenVolatilityTermStructure :: GenVolatilityTermStructure (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
withGenVolatilityTermStructure (GenTermStructure (GenForeignPtr (AnyVolatilityTermStructure (GenForeignPtr x _)) _)) = withForeignPtr x
newGenVolatilityTermStructure :: GenForeignPtr a CVolatilityTermStructure' -> IO (GenVolatilityTermStructure a)
newGenVolatilityTermStructure p = GenTermStructure <^> GenForeignPtr (AnyVolatilityTermStructure p) (withGenForeignPtr . getVolatilityTermStructure)

asBlackVolTermStructure :: GenBlackVolTermStructure a -> IO BlackVolTermStructure
asBlackVolTermStructure (GenTermStructure (GenForeignPtr (AnyVolatilityTermStructure (GenForeignPtr (AnyBlackVolTermStructure (GenForeignPtr x w)) _)) _)) = w x peekBlackVolTermStructure
peekBlackVolTermStructure :: Ptr CBlackVolTermStructure' -> IO BlackVolTermStructure
peekBlackVolTermStructure = newCastForeignPtr >=> newGenBlackVolTermStructure
withBlackVolTermStructure :: GenBlackVolTermStructure a -> (Ptr CBlackVolTermStructure' -> IO b) -> IO b
withBlackVolTermStructure (GenTermStructure (GenForeignPtr (AnyVolatilityTermStructure (GenForeignPtr (AnyBlackVolTermStructure (GenForeignPtr x w)) _)) _)) = w x
newGenBlackVolTermStructure :: GenForeignPtr a CBlackVolTermStructure' -> IO (GenBlackVolTermStructure a)
newGenBlackVolTermStructure p = GenTermStructure <^> GenForeignPtr (AnyVolatilityTermStructure $ GenForeignPtr (AnyBlackVolTermStructure p) (withGenForeignPtr . getBlackVolTermStructure)) (withGenForeignPtr . getVolatilityTermStructure)

peekBlackVarianceCurve :: Ptr CBlackVarianceCurve' -> IO BlackVarianceCurve
peekBlackVarianceCurve = newGenForeignPtr >=> newGenBlackVolTermStructure
withBlackVarianceCurve :: BlackVarianceCurve -> (Ptr CBlackVarianceCurve' -> IO b) -> IO b
withBlackVarianceCurve (GenTermStructure (GenForeignPtr (AnyVolatilityTermStructure (GenForeignPtr (AnyBlackVolTermStructure (GenForeignPtr x _)) _)) _)) = withForeignPtr x

peekOptionletVolatilityStructure :: Ptr COptionletVolatilityStructure' -> IO OptionletVolatilityStructure
peekOptionletVolatilityStructure = peekGenVolatilityTermStructure
peekSwaptionVolatilityStructure :: Ptr CSwaptionVolatilityStructure' -> IO SwaptionVolatilityStructure
peekSwaptionVolatilityStructure = peekGenVolatilityTermStructure
peekCapFloorTermVolSurface :: Ptr CCapFloorTermVolSurface' -> IO CapFloorTermVolSurface
peekCapFloorTermVolSurface = peekGenVolatilityTermStructure
peekLocalVolTermStructure :: Ptr CLocalVolTermStructure' -> IO LocalVolTermStructure
peekLocalVolTermStructure = peekGenVolatilityTermStructure
peekCallableBondVolatilityStructure :: Ptr CCallableBondVolatilityStructure' -> IO CallableBondVolatilityStructure
peekCallableBondVolatilityStructure = GenTermStructure <.> newGenForeignPtr
peekDefaultProbabilityTermStructure :: Ptr CDefaultProbabilityTermStructure' -> IO DefaultProbabilityTermStructure
peekDefaultProbabilityTermStructure = GenTermStructure <.> newGenForeignPtr

asYieldTermStructure :: GenYieldTermStructure a -> IO YieldTermStructure
asYieldTermStructure (GenTermStructure (GenForeignPtr (AnyYieldTermStructure (GenForeignPtr x w)) _)) = w x peekYieldTermStructure
peekYieldTermStructure :: Ptr CYieldTermStructure' -> IO YieldTermStructure
peekYieldTermStructure = newCastForeignPtr >=> newGenYieldTermStructure
withYieldTermStructure :: GenYieldTermStructure a -> (Ptr CYieldTermStructure' -> IO b) -> IO b
withYieldTermStructure (GenTermStructure (GenForeignPtr (AnyYieldTermStructure (GenForeignPtr x w)) _)) = w x
withMaybeYieldTermStructure :: Maybe (GenYieldTermStructure a) -> (Ptr CYieldTermStructure' -> IO b) -> IO b
withMaybeYieldTermStructure x f = maybe (f nullPtr) (`withYieldTermStructure` f) x
newGenYieldTermStructure :: GenForeignPtr a CYieldTermStructure' -> IO (GenYieldTermStructure a)
newGenYieldTermStructure p = GenTermStructure <^> GenForeignPtr (AnyYieldTermStructure p) (withGenForeignPtr . getYieldTermStructure)

peekFittedBondDiscountCurve :: Ptr CFittedBondDiscountCurve' -> IO FittedBondDiscountCurve
peekFittedBondDiscountCurve = newGenForeignPtr >=> newGenYieldTermStructure
withFittedBondDiscountCurve :: FittedBondDiscountCurve -> (Ptr CFittedBondDiscountCurve' -> IO b) -> IO b
withFittedBondDiscountCurve (GenTermStructure (GenForeignPtr (AnyYieldTermStructure (GenForeignPtr x _)) _)) = withForeignPtr x

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
newtype AnyHestonProcess a = AnyHestonProcess {getHestonProcess :: GenForeignPtr a CHestonProcess'}
type GenHestonProcess a = GenStochasticProcess (AnyHestonProcess a)
type CHestonProcess = ForeignPtr CHestonProcess'
type HestonProcess = GenHestonProcess CHestonProcess
newtype AnyStochasticProcess1D a = AnyStochasticProcess1D {getStochasticProcess1D :: GenForeignPtr a CStochasticProcess1D'}
type GenStochasticProcess1D a = GenStochasticProcess (AnyStochasticProcess1D a)
type CStochasticProcess1D = ForeignPtr CStochasticProcess1D'
type StochasticProcess1D = GenStochasticProcess1D CStochasticProcess1D
type CMerton76Process = ForeignPtr CMerton76Process'
type Merton76Process = GenStochasticProcess1D CMerton76Process
type CVarianceGammaProcess = ForeignPtr CVarianceGammaProcess'
type VarianceGammaProcess = GenStochasticProcess1D CVarianceGammaProcess
newtype AnyGeneralizedBlackScholesProcess a = AnyGeneralizedBlackScholesProcess {getGeneralizedBlackScholesProcess :: GenForeignPtr a CGeneralizedBlackScholesProcess'}
type GenGeneralizedBlackScholesProcess a = GenStochasticProcess1D (AnyGeneralizedBlackScholesProcess a)
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
instance Finalizable CStochasticProcess' where finalize = qlFreeStochasticProcess
instance Finalizable CExtOUWithJumpsProcess' where finalize = qlFreeExtOUWithJumpsProcess
instance Finalizable CGJRGARCHProcess' where finalize = qlFreeGJRGARCHProcess
instance Finalizable CHybridHestonHullWhiteProcess' where finalize = qlFreeHybridHestonHullWhiteProcess
instance Finalizable CKlugeExtOUProcess' where finalize = qlFreeKlugeExtOUProcess
instance Finalizable CLiborForwardModelProcess' where finalize = qlFreeLiborForwardModelProcess
instance Finalizable CStochasticProcessArray' where finalize = qlFreeStochasticProcessArray
instance Finalizable CHestonProcess' where finalize = qlFreeHestonProcess
instance Finalizable CStochasticProcess1D' where finalize = qlFreeStochasticProcess1D
instance Finalizable CBatesProcess' where finalize = qlFreeBatesProcess
instance Finalizable CExtendedOrnsteinUhlenbeckProcess' where finalize = qlFreeExtendedOrnsteinUhlenbeckProcess
instance Finalizable CHullWhiteForwardProcess' where finalize = qlFreeHullWhiteForwardProcess
instance Finalizable CHullWhiteProcess' where finalize = qlFreeHullWhiteProcess
instance Finalizable CMerton76Process' where finalize = qlFreeMerton76Process
instance Finalizable CVarianceGammaProcess' where finalize = qlFreeVarianceGammaProcess
instance Finalizable CGeneralizedBlackScholesProcess' where finalize = qlFreeGeneralizedBlackScholesProcess
instance Finalizable CBlackProcess' where finalize = qlFreeBlackProcess
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
instance Upcastable CExtOUWithJumpsProcess' where {type Base CExtOUWithJumpsProcess' = CStochasticProcess'; upcast = qlExtOUWithJumpsProcessAsStochasticProcess}
instance Upcastable CGJRGARCHProcess' where {type Base CGJRGARCHProcess' = CStochasticProcess'; upcast = qlGJRGARCHProcessAsStochasticProcess}
instance Upcastable CHybridHestonHullWhiteProcess' where {type Base CHybridHestonHullWhiteProcess' = CStochasticProcess'; upcast = qlHybridHestonHullWhiteProcessAsStochasticProcess}
instance Upcastable CKlugeExtOUProcess' where {type Base CKlugeExtOUProcess' = CStochasticProcess'; upcast = qlKlugeExtOUProcessAsStochasticProcess}
instance Upcastable CLiborForwardModelProcess' where {type Base CLiborForwardModelProcess' = CStochasticProcess'; upcast = qlLiborForwardModelProcessAsStochasticProcess}
instance Upcastable CStochasticProcessArray' where {type Base CStochasticProcessArray' = CStochasticProcess'; upcast = qlStochasticProcessArrayAsStochasticProcess}
instance Upcastable CHestonProcess' where {type Base CHestonProcess' = CStochasticProcess'; upcast = qlHestonProcessAsStochasticProcess}
instance Upcastable CStochasticProcess1D' where {type Base CStochasticProcess1D' = CStochasticProcess'; upcast = qlStochasticProcess1DAsStochasticProcess}
instance Upcastable CBatesProcess' where {type Base CBatesProcess' = CHestonProcess'; upcast = qlBatesProcessAsHestonProcess}
instance Upcastable CExtendedOrnsteinUhlenbeckProcess' where {type Base CExtendedOrnsteinUhlenbeckProcess' = CStochasticProcess1D'; upcast = qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D}
instance Upcastable CHullWhiteForwardProcess' where {type Base CHullWhiteForwardProcess' = CStochasticProcess1D'; upcast = qlHullWhiteForwardProcessAsStochasticProcess1D}
instance Upcastable CHullWhiteProcess' where {type Base CHullWhiteProcess' = CStochasticProcess1D'; upcast = qlHullWhiteProcessAsStochasticProcess1D}
instance Upcastable CMerton76Process' where {type Base CMerton76Process' = CStochasticProcess1D'; upcast = qlMerton76ProcessAsStochasticProcess1D}
instance Upcastable CVarianceGammaProcess' where {type Base CVarianceGammaProcess' = CStochasticProcess1D'; upcast = qlVarianceGammaProcessAsStochasticProcess1D}
instance Upcastable CGeneralizedBlackScholesProcess' where {type Base CGeneralizedBlackScholesProcess' = CStochasticProcess1D'; upcast = qlGeneralizedBlackScholesProcessAsStochasticProcess1D}
instance Upcastable CBlackProcess' where {type Base CBlackProcess' = CGeneralizedBlackScholesProcess'; upcast = qlBlackProcessAsGeneralizedBlackScholesProcess}
asStochasticProcess :: GenStochasticProcess a -> IO StochasticProcess
asStochasticProcess (GenStochasticProcess (GenForeignPtr x w)) = w x peekStochasticProcess
peekStochasticProcess :: Ptr CStochasticProcess' -> IO StochasticProcess
peekStochasticProcess = GenStochasticProcess <.> newCastForeignPtr
withStochasticProcess :: GenStochasticProcess a -> (Ptr CStochasticProcess' -> IO b) -> IO b
withStochasticProcess (GenStochasticProcess (GenForeignPtr x w)) = w x
withGenStochasticProcess :: GenStochasticProcess (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenStochasticProcess (GenStochasticProcess (GenForeignPtr x _)) = withForeignPtr x
peekExtOUWithJumpsProcess :: Ptr CExtOUWithJumpsProcess' -> IO ExtOUWithJumpsProcess
peekExtOUWithJumpsProcess = GenStochasticProcess <.> newGenForeignPtr
peekGJRGARCHProcess :: Ptr CGJRGARCHProcess' -> IO GJRGARCHProcess
peekGJRGARCHProcess = GenStochasticProcess <.> newGenForeignPtr
peekHybridHestonHullWhiteProcess :: Ptr CHybridHestonHullWhiteProcess' -> IO HybridHestonHullWhiteProcess
peekHybridHestonHullWhiteProcess = GenStochasticProcess <.> newGenForeignPtr
peekKlugeExtOUProcess :: Ptr CKlugeExtOUProcess' -> IO KlugeExtOUProcess
peekKlugeExtOUProcess = GenStochasticProcess <.> newGenForeignPtr
peekLiborForwardModelProcess :: Ptr CLiborForwardModelProcess' -> IO LiborForwardModelProcess
peekLiborForwardModelProcess = GenStochasticProcess <.> newGenForeignPtr
peekStochasticProcessArray :: Ptr CStochasticProcessArray' -> IO StochasticProcessArray
peekStochasticProcessArray = GenStochasticProcess <.> newGenForeignPtr
asHestonProcess :: GenHestonProcess a -> IO HestonProcess
asHestonProcess (GenStochasticProcess (GenForeignPtr (AnyHestonProcess (GenForeignPtr x w)) _)) = w x peekHestonProcess
peekHestonProcess :: Ptr CHestonProcess' -> IO HestonProcess
peekHestonProcess = newCastForeignPtr >=> newGenHestonProcess
withHestonProcess :: GenHestonProcess a -> (Ptr CHestonProcess' -> IO b) -> IO b
withHestonProcess (GenStochasticProcess (GenForeignPtr (AnyHestonProcess (GenForeignPtr x w)) _)) = w x
newGenHestonProcess :: GenForeignPtr a CHestonProcess' -> IO (GenHestonProcess a)
newGenHestonProcess p = GenStochasticProcess <^> GenForeignPtr (AnyHestonProcess p) (withGenForeignPtr . getHestonProcess)
peekGenHestonProcess :: (Finalizable a, Upcastable a, Base a ~ CHestonProcess') => Ptr a -> IO (GenHestonProcess (ForeignPtr a))
peekGenHestonProcess = newGenForeignPtr >=> newGenHestonProcess
asStochasticProcess1D :: GenStochasticProcess1D a -> IO StochasticProcess1D
asStochasticProcess1D (GenStochasticProcess (GenForeignPtr (AnyStochasticProcess1D (GenForeignPtr x w)) _)) = w x peekStochasticProcess1D
peekStochasticProcess1D :: Ptr CStochasticProcess1D' -> IO StochasticProcess1D
peekStochasticProcess1D = newCastForeignPtr >=> newGenStochasticProcess1D
withStochasticProcess1D :: GenStochasticProcess1D a -> (Ptr CStochasticProcess1D' -> IO b) -> IO b
withStochasticProcess1D (GenStochasticProcess (GenForeignPtr (AnyStochasticProcess1D (GenForeignPtr x w)) _)) = w x
withStochasticProcess1DArray :: [GenStochasticProcess1D a] -> ((CUInt, Ptr (Ptr CStochasticProcess1D')) -> IO b) -> IO b
withStochasticProcess1DArray = withGenArray withStochasticProcess1D
newGenStochasticProcess1D :: GenForeignPtr a CStochasticProcess1D' -> IO (GenStochasticProcess1D a)
newGenStochasticProcess1D p = GenStochasticProcess <^> GenForeignPtr (AnyStochasticProcess1D p) (withGenForeignPtr . getStochasticProcess1D)
peekGenStochasticProcess1D :: (Finalizable a, Upcastable a, Base a ~ CStochasticProcess1D') => Ptr a -> IO (GenStochasticProcess1D (ForeignPtr a))
peekGenStochasticProcess1D = newGenForeignPtr >=> newGenStochasticProcess1D
withGenStochasticProcess1D :: GenStochasticProcess1D (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
withGenStochasticProcess1D (GenStochasticProcess (GenForeignPtr (AnyStochasticProcess1D (GenForeignPtr x _)) _)) = withForeignPtr x
peekBatesProcess :: Ptr CBatesProcess' -> IO BatesProcess
peekBatesProcess = peekGenHestonProcess
withBatesProcess :: BatesProcess -> (Ptr CBatesProcess' -> IO b) -> IO b
withBatesProcess (GenStochasticProcess (GenForeignPtr (AnyHestonProcess (GenForeignPtr x _)) _)) = withForeignPtr x
peekExtendedOrnsteinUhlenbeckProcess :: Ptr CExtendedOrnsteinUhlenbeckProcess' -> IO ExtendedOrnsteinUhlenbeckProcess
peekExtendedOrnsteinUhlenbeckProcess = peekGenStochasticProcess1D
peekHullWhiteForwardProcess :: Ptr CHullWhiteForwardProcess' -> IO HullWhiteForwardProcess
peekHullWhiteForwardProcess = peekGenStochasticProcess1D
peekHullWhiteProcess :: Ptr CHullWhiteProcess' -> IO HullWhiteProcess
peekHullWhiteProcess = peekGenStochasticProcess1D
peekMerton76Process :: Ptr CMerton76Process' -> IO Merton76Process
peekMerton76Process = peekGenStochasticProcess1D
peekVarianceGammaProcess :: Ptr CVarianceGammaProcess' -> IO VarianceGammaProcess
peekVarianceGammaProcess = peekGenStochasticProcess1D
asGeneralizedBlackScholesProcess :: GenGeneralizedBlackScholesProcess a -> IO GeneralizedBlackScholesProcess
asGeneralizedBlackScholesProcess (GenStochasticProcess (GenForeignPtr (AnyStochasticProcess1D (GenForeignPtr (AnyGeneralizedBlackScholesProcess (GenForeignPtr x w)) _)) _)) = w x peekGeneralizedBlackScholesProcess
peekGeneralizedBlackScholesProcess :: Ptr CGeneralizedBlackScholesProcess' -> IO GeneralizedBlackScholesProcess
peekGeneralizedBlackScholesProcess = newCastForeignPtr >=> newGenGeneralizedBlackScholesProcess
withGeneralizedBlackScholesProcess :: GenGeneralizedBlackScholesProcess a -> (Ptr CGeneralizedBlackScholesProcess' -> IO b) -> IO b
withGeneralizedBlackScholesProcess (GenStochasticProcess (GenForeignPtr (AnyStochasticProcess1D (GenForeignPtr (AnyGeneralizedBlackScholesProcess (GenForeignPtr x w)) _)) _)) = w x
newGenGeneralizedBlackScholesProcess :: GenForeignPtr a CGeneralizedBlackScholesProcess' -> IO (GenGeneralizedBlackScholesProcess a)
newGenGeneralizedBlackScholesProcess p = GenStochasticProcess <^> GenForeignPtr (AnyStochasticProcess1D $ GenForeignPtr (AnyGeneralizedBlackScholesProcess p) (withGenForeignPtr . getGeneralizedBlackScholesProcess)) (withGenForeignPtr . getStochasticProcess1D)
peekBlackProcess :: Ptr CBlackProcess' -> IO BlackProcess
peekBlackProcess = newGenForeignPtr >=> newGenGeneralizedBlackScholesProcess
withBlackProcess :: BlackProcess -> (Ptr CBlackProcess' -> IO b) -> IO b
withBlackProcess (GenStochasticProcess (GenForeignPtr (AnyStochasticProcess1D (GenForeignPtr (AnyGeneralizedBlackScholesProcess (GenForeignPtr x _)) _)) _)) = withForeignPtr x

data CCalibratedModel'
data CGJRGARCHModel'
data CLiborForwardModel'
data CPiecewiseTimeDependentHestonModel'
data CHestonModel'
data CShortRateModel'
data CBatesModel'
data CBatesDetJumpModel'
data CBatesDoubleExpModel'
data CBatesDoubleExpDetJumpModel'
data COneFactorAffineModel'
data CHullWhite'
data CG2'
data CAffineModel'
newtype GenCalibratedModel a f = GenCalibratedModel (GenForeignPtr a CCalibratedModel')
type CCalibratedModel = ForeignPtr CCalibratedModel'
type CalibratedModel = GenCalibratedModel CCalibratedModel NonAffineModel
type CLiborForwardModel = ForeignPtr CLiborForwardModel'
type LiborForwardModel = GenCalibratedModel CLiborForwardModel (AffineModel CLiborForwardModel)
type CGJRGARCHModel = ForeignPtr CGJRGARCHModel'
type GJRGARCHModel = GenCalibratedModel CGJRGARCHModel NonAffineModel
type CPiecewiseTimeDependentHestonModel = ForeignPtr CPiecewiseTimeDependentHestonModel'
type PiecewiseTimeDependentHestonModel = GenCalibratedModel CPiecewiseTimeDependentHestonModel NonAffineModel
newtype AnyHestonModel a = AnyHestonModel {getHestonModel :: GenForeignPtr a CHestonModel'}
type GenHestonModel a = GenCalibratedModel (AnyHestonModel a) NonAffineModel
type CHestonModel = ForeignPtr CHestonModel'
type HestonModel = GenHestonModel CHestonModel
newtype AnyShortRateModel a = AnyShortRateModel {getShortRateModel :: GenForeignPtr a CShortRateModel'}
type GenShortRateModel a f = GenCalibratedModel (AnyShortRateModel a) f
type CShortRateModel = ForeignPtr CShortRateModel'
type ShortRateModel = GenShortRateModel CShortRateModel NonAffineModel
newtype AnyBatesModel a = AnyBatesModel {getBatesModel :: GenForeignPtr a CBatesModel'}
type GenBatesModel a = GenHestonModel (AnyBatesModel a)
type CBatesModel = ForeignPtr CBatesModel'
type BatesModel = GenBatesModel CBatesModel
type CBatesDetJumpModel = ForeignPtr CBatesDetJumpModel'
type BatesDetJumpModel = GenBatesModel CBatesDetJumpModel
newtype AnyBatesDoubleExpModel a = AnyBatesDoubleExpModel {getBatesDoubleExpModel :: GenForeignPtr a CBatesDoubleExpModel'}
type GenBatesDoubleExpModel a = GenHestonModel (AnyBatesDoubleExpModel a)
type CBatesDoubleExpModel = ForeignPtr CBatesDoubleExpModel'
type BatesDoubleExpModel = GenBatesDoubleExpModel CBatesDoubleExpModel
type CBatesDoubleExpDetJumpModel = ForeignPtr CBatesDoubleExpDetJumpModel'
type BatesDoubleExpDetJumpModel = GenBatesDoubleExpModel CBatesDoubleExpDetJumpModel
newtype AnyOneFactorAffineModel a = AnyOneFactorAffineModel {getOneFactorAffineModel :: GenForeignPtr a COneFactorAffineModel'}
type GenOneFactorAffineModel a = GenShortRateModel (AnyOneFactorAffineModel a) (AffineModel COneFactorAffineModel)
type COneFactorAffineModel = ForeignPtr COneFactorAffineModel'
type OneFactorAffineModel = GenOneFactorAffineModel COneFactorAffineModel
type CHullWhite = ForeignPtr CHullWhite'
type HullWhite = GenOneFactorAffineModel CHullWhite
type CG2 = ForeignPtr CG2'
type G2 = GenShortRateModel CG2 (AffineModel CG2)
foreign import ccall "ql.h &qlFreeCalibratedModel" qlFreeCalibratedModel :: FinalizerPtr CCalibratedModel'
foreign import ccall "ql.h &qlFreeLiborForwardModel" qlFreeLiborForwardModel :: FinalizerPtr CLiborForwardModel'
foreign import ccall "ql.h &qlFreeGJRGARCHModel" qlFreeGJRGARCHModel :: FinalizerPtr CGJRGARCHModel'
foreign import ccall "ql.h &qlFreePiecewiseTimeDependentHestonModel" qlFreePiecewiseTimeDependentHestonModel :: FinalizerPtr CPiecewiseTimeDependentHestonModel'
foreign import ccall "ql.h &qlFreeHestonModel" qlFreeHestonModel :: FinalizerPtr CHestonModel'
foreign import ccall "ql.h &qlFreeShortRateModel" qlFreeShortRateModel :: FinalizerPtr CShortRateModel'
foreign import ccall "ql.h &qlFreeBatesModel" qlFreeBatesModel :: FinalizerPtr CBatesModel'
foreign import ccall "ql.h &qlFreeBatesDetJumpModel" qlFreeBatesDetJumpModel :: FinalizerPtr CBatesDetJumpModel'
foreign import ccall "ql.h &qlFreeBatesDoubleExpModel" qlFreeBatesDoubleExpModel :: FinalizerPtr CBatesDoubleExpModel'
foreign import ccall "ql.h &qlFreeBatesDoubleExpDetJumpModel" qlFreeBatesDoubleExpDetJumpModel :: FinalizerPtr CBatesDoubleExpDetJumpModel'
foreign import ccall "ql.h &qlFreeG2" qlFreeG2 :: FinalizerPtr CG2'
foreign import ccall "ql.h &qlFreeAffineModel" qlFreeAffineModel :: FinalizerPtr CAffineModel'
foreign import ccall "ql.h &qlFreeOneFactorAffineModel" qlFreeOneFactorAffineModel :: FinalizerPtr COneFactorAffineModel'
foreign import ccall "ql.h &qlFreeHullWhite" qlFreeHullWhite :: FinalizerPtr CHullWhite'
foreign import ccall "ql.h qlPiecewiseTimeDependentHestonModelAsCalibratedModel" qlPiecewiseTimeDependentHestonModelAsCalibratedModel :: Ptr CPiecewiseTimeDependentHestonModel' -> IO (Ptr CCalibratedModel')
foreign import ccall "ql.h qlLiborForwardModelAsCalibratedModel" qlLiborForwardModelAsCalibratedModel :: Ptr CLiborForwardModel' -> IO (Ptr CCalibratedModel')
foreign import ccall "ql.h qlGJRGARCHModelAsCalibratedModel" qlGJRGARCHModelAsCalibratedModel :: Ptr CGJRGARCHModel' -> IO (Ptr CCalibratedModel')
foreign import ccall "ql.h qlHestonModelAsCalibratedModel" qlHestonModelAsCalibratedModel :: Ptr CHestonModel' -> IO (Ptr CCalibratedModel')
foreign import ccall "ql.h qlShortRateModelAsCalibratedModel" qlShortRateModelAsCalibratedModel :: Ptr CShortRateModel' -> IO (Ptr CCalibratedModel')
foreign import ccall "ql.h qlBatesModelAsHestonModel" qlBatesModelAsHestonModel :: Ptr CBatesModel' -> IO (Ptr CHestonModel')
foreign import ccall "ql.h qlBatesDetJumpModelAsBatesModel" qlBatesDetJumpModelAsBatesModel :: Ptr CBatesDetJumpModel' -> IO (Ptr CBatesModel')
foreign import ccall "ql.h qlBatesDoubleExpModelAsHestonModel" qlBatesDoubleExpModelAsHestonModel :: Ptr CBatesDoubleExpModel' -> IO (Ptr CHestonModel')
foreign import ccall "ql.h qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel" qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel :: Ptr CBatesDoubleExpDetJumpModel' -> IO (Ptr CBatesDoubleExpModel')
foreign import ccall "ql.h qlOneFactorAffineModelAsShortRateModel" qlOneFactorAffineModelAsShortRateModel :: Ptr COneFactorAffineModel' -> IO (Ptr CShortRateModel')
foreign import ccall "ql.h qlHullWhiteAsOneFactorAffineModel" qlHullWhiteAsOneFactorAffineModel :: Ptr CHullWhite' -> IO (Ptr COneFactorAffineModel')
foreign import ccall "ql.h qlG2AsShortRateModel" qlG2AsShortRateModel :: Ptr CG2' -> IO (Ptr CShortRateModel')
instance Finalizable CCalibratedModel' where finalize = qlFreeCalibratedModel
instance Finalizable CLiborForwardModel' where finalize = qlFreeLiborForwardModel
instance Finalizable CGJRGARCHModel' where finalize = qlFreeGJRGARCHModel
instance Finalizable CPiecewiseTimeDependentHestonModel' where finalize = qlFreePiecewiseTimeDependentHestonModel
instance Finalizable CHestonModel' where finalize = qlFreeHestonModel
instance Finalizable CShortRateModel' where finalize = qlFreeShortRateModel
instance Finalizable CBatesModel' where finalize = qlFreeBatesModel
instance Finalizable CBatesDetJumpModel' where finalize = qlFreeBatesDetJumpModel
instance Finalizable CBatesDoubleExpModel' where finalize = qlFreeBatesDoubleExpModel
instance Finalizable CBatesDoubleExpDetJumpModel' where finalize = qlFreeBatesDoubleExpDetJumpModel
instance Finalizable COneFactorAffineModel' where finalize = qlFreeOneFactorAffineModel
instance Finalizable CHullWhite' where finalize = qlFreeHullWhite
instance Finalizable CG2' where finalize = qlFreeG2
instance Finalizable CAffineModel' where finalize = qlFreeAffineModel
instance Upcastable CLiborForwardModel' where {type Base CLiborForwardModel' = CCalibratedModel'; upcast = qlLiborForwardModelAsCalibratedModel}
instance Upcastable CPiecewiseTimeDependentHestonModel' where {type Base CPiecewiseTimeDependentHestonModel' = CCalibratedModel'; upcast = qlPiecewiseTimeDependentHestonModelAsCalibratedModel}
instance Upcastable CGJRGARCHModel' where {type Base CGJRGARCHModel' = CCalibratedModel'; upcast = qlGJRGARCHModelAsCalibratedModel}
instance Upcastable CHestonModel' where {type Base CHestonModel' = CCalibratedModel'; upcast = qlHestonModelAsCalibratedModel}
instance Upcastable CShortRateModel' where {type Base CShortRateModel' = CCalibratedModel'; upcast = qlShortRateModelAsCalibratedModel}
instance Upcastable CBatesModel' where {type Base CBatesModel' = CHestonModel'; upcast = qlBatesModelAsHestonModel}
instance Upcastable CBatesDetJumpModel' where {type Base CBatesDetJumpModel' = CBatesModel'; upcast = qlBatesDetJumpModelAsBatesModel}
instance Upcastable CBatesDoubleExpModel' where {type Base CBatesDoubleExpModel' = CHestonModel'; upcast = qlBatesDoubleExpModelAsHestonModel}
instance Upcastable CBatesDoubleExpDetJumpModel' where {type Base CBatesDoubleExpDetJumpModel' = CBatesDoubleExpModel'; upcast = qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel}
instance Upcastable COneFactorAffineModel' where {type Base COneFactorAffineModel' = CShortRateModel'; upcast = qlOneFactorAffineModelAsShortRateModel}
instance Upcastable CHullWhite' where {type Base CHullWhite' = COneFactorAffineModel'; upcast = qlHullWhiteAsOneFactorAffineModel}
instance Upcastable CG2' where {type Base CG2' = CShortRateModel'; upcast = qlG2AsShortRateModel}
asCalibratedModel :: GenCalibratedModel a f -> IO CalibratedModel
asCalibratedModel (GenCalibratedModel (GenForeignPtr x w)) = w x peekCalibratedModel
peekCalibratedModel :: Ptr CCalibratedModel' -> IO CalibratedModel
peekCalibratedModel = GenCalibratedModel <.> newCastForeignPtr
withCalibratedModel :: GenCalibratedModel a f -> (Ptr CCalibratedModel' -> IO b) -> IO b
withCalibratedModel (GenCalibratedModel (GenForeignPtr x w)) = w x
withGenCalibratedModel :: GenCalibratedModel (ForeignPtr a) f -> (Ptr a -> IO b) -> IO b
withGenCalibratedModel (GenCalibratedModel (GenForeignPtr x _)) = withForeignPtr x
peekLiborForwardModel :: Ptr CLiborForwardModel' -> IO LiborForwardModel
peekLiborForwardModel = GenCalibratedModel <.> newGenForeignPtr
peekGJRGARCHModel :: Ptr CGJRGARCHModel' -> IO GJRGARCHModel
peekGJRGARCHModel = GenCalibratedModel <.> newGenForeignPtr
peekPiecewiseTimeDependentHestonModel :: Ptr CPiecewiseTimeDependentHestonModel' -> IO PiecewiseTimeDependentHestonModel
peekPiecewiseTimeDependentHestonModel = GenCalibratedModel <.> newGenForeignPtr

asHestonModel :: GenHestonModel a -> IO HestonModel
asHestonModel (GenCalibratedModel (GenForeignPtr (AnyHestonModel (GenForeignPtr x w)) _)) = w x peekHestonModel
peekHestonModel :: Ptr CHestonModel' -> IO HestonModel
peekHestonModel = newCastForeignPtr >=> newGenHestonModel
withHestonModel :: GenHestonModel a -> (Ptr CHestonModel' -> IO b) -> IO b
withHestonModel (GenCalibratedModel (GenForeignPtr (AnyHestonModel (GenForeignPtr x w)) _)) = w x
newGenHestonModel :: GenForeignPtr a CHestonModel' -> IO (GenHestonModel a)
newGenHestonModel p = GenCalibratedModel <^> GenForeignPtr (AnyHestonModel p) (withGenForeignPtr . getHestonModel)

asShortRateModel :: GenShortRateModel a f -> IO ShortRateModel
asShortRateModel (GenCalibratedModel (GenForeignPtr (AnyShortRateModel (GenForeignPtr x w)) _)) = w x peekShortRateModel
peekShortRateModel :: Ptr CShortRateModel' -> IO ShortRateModel
peekShortRateModel = newCastForeignPtr >=> newGenShortRateModel
withShortRateModel :: GenShortRateModel a f -> (Ptr CShortRateModel' -> IO b) -> IO b
withShortRateModel (GenCalibratedModel (GenForeignPtr (AnyShortRateModel (GenForeignPtr x w)) _)) = w x
newGenShortRateModel :: GenForeignPtr a CShortRateModel' -> IO (GenShortRateModel a f)
newGenShortRateModel p = GenCalibratedModel <^> GenForeignPtr (AnyShortRateModel p) (withGenForeignPtr . getShortRateModel)
peekGenShortRateModel :: (Finalizable a, Upcastable a, Base a ~ CShortRateModel') => Ptr a -> IO (GenShortRateModel (ForeignPtr a) f)
peekGenShortRateModel = newGenForeignPtr >=> newGenShortRateModel

asBatesModel :: GenBatesModel a -> IO BatesModel
asBatesModel (GenCalibratedModel (GenForeignPtr (AnyHestonModel (GenForeignPtr (AnyBatesModel (GenForeignPtr x w)) _)) _)) = w x peekBatesModel
peekBatesModel :: Ptr CBatesModel' -> IO BatesModel
peekBatesModel = newCastForeignPtr >=> newGenBatesModel
withBatesModel :: GenBatesModel a -> (Ptr CBatesModel' -> IO b) -> IO b
withBatesModel (GenCalibratedModel (GenForeignPtr (AnyHestonModel (GenForeignPtr (AnyBatesModel (GenForeignPtr x w)) _)) _)) = w x
newGenBatesModel :: GenForeignPtr a CBatesModel' -> IO (GenBatesModel a)
newGenBatesModel p = GenCalibratedModel <^> GenForeignPtr (AnyHestonModel $ GenForeignPtr (AnyBatesModel p) (withGenForeignPtr . getBatesModel)) (withGenForeignPtr . getHestonModel)
peekBatesDetJumpModel :: Ptr CBatesDetJumpModel' -> IO BatesDetJumpModel
peekBatesDetJumpModel = newGenForeignPtr >=> newGenBatesModel
withBatesDetJumpModel :: BatesDetJumpModel -> (Ptr CBatesDetJumpModel' -> IO b) -> IO b
withBatesDetJumpModel (GenCalibratedModel (GenForeignPtr (AnyHestonModel (GenForeignPtr (AnyBatesModel (GenForeignPtr x _)) _)) _)) = withForeignPtr x

asBatesDoubleExpModel :: GenBatesDoubleExpModel a -> IO BatesDoubleExpModel
asBatesDoubleExpModel (GenCalibratedModel (GenForeignPtr (AnyHestonModel (GenForeignPtr (AnyBatesDoubleExpModel (GenForeignPtr x w)) _)) _)) = w x peekBatesDoubleExpModel
peekBatesDoubleExpModel :: Ptr CBatesDoubleExpModel' -> IO BatesDoubleExpModel
peekBatesDoubleExpModel = newCastForeignPtr >=> newGenBatesDoubleExpModel
withBatesDoubleExpModel :: GenBatesDoubleExpModel a -> (Ptr CBatesDoubleExpModel' -> IO b) -> IO b
withBatesDoubleExpModel (GenCalibratedModel (GenForeignPtr (AnyHestonModel (GenForeignPtr (AnyBatesDoubleExpModel (GenForeignPtr x w)) _)) _)) = w x
newGenBatesDoubleExpModel :: GenForeignPtr a CBatesDoubleExpModel' -> IO (GenBatesDoubleExpModel a)
newGenBatesDoubleExpModel p = GenCalibratedModel <^> GenForeignPtr (AnyHestonModel $ GenForeignPtr (AnyBatesDoubleExpModel p) (withGenForeignPtr . getBatesDoubleExpModel)) (withGenForeignPtr . getHestonModel)
peekBatesDoubleExpDetJumpModel :: Ptr CBatesDoubleExpDetJumpModel' -> IO BatesDoubleExpDetJumpModel
peekBatesDoubleExpDetJumpModel = newGenForeignPtr >=> newGenBatesDoubleExpModel
withBatesDoubleExpDetJumpModel :: BatesDoubleExpDetJumpModel -> (Ptr CBatesDoubleExpDetJumpModel' -> IO b) -> IO b
withBatesDoubleExpDetJumpModel (GenCalibratedModel (GenForeignPtr (AnyHestonModel (GenForeignPtr (AnyBatesDoubleExpModel (GenForeignPtr x _)) _)) _)) = withForeignPtr x

asOneFactorAffineModel :: GenOneFactorAffineModel a -> IO OneFactorAffineModel
asOneFactorAffineModel (GenCalibratedModel (GenForeignPtr (AnyShortRateModel (GenForeignPtr (AnyOneFactorAffineModel (GenForeignPtr x w)) _)) _)) = w x peekOneFactorAffineModel
peekOneFactorAffineModel :: Ptr COneFactorAffineModel' -> IO OneFactorAffineModel
peekOneFactorAffineModel = newCastForeignPtr >=> newGenOneFactorAffineModel
withOneFactorAffineModel :: GenOneFactorAffineModel a -> (Ptr COneFactorAffineModel' -> IO b) -> IO b
withOneFactorAffineModel (GenCalibratedModel (GenForeignPtr (AnyShortRateModel (GenForeignPtr (AnyOneFactorAffineModel (GenForeignPtr x w)) _)) _)) = w x
newGenOneFactorAffineModel :: GenForeignPtr a COneFactorAffineModel' -> IO (GenOneFactorAffineModel a)
newGenOneFactorAffineModel p = GenCalibratedModel <^> GenForeignPtr (AnyShortRateModel $ GenForeignPtr (AnyOneFactorAffineModel p) (withGenForeignPtr . getOneFactorAffineModel)) (withGenForeignPtr . getShortRateModel)
peekHullWhite :: Ptr CHullWhite' -> IO HullWhite
peekHullWhite = newGenForeignPtr >=> newGenOneFactorAffineModel
withHullWhite :: HullWhite -> (Ptr CHullWhite' -> IO b) -> IO b
withHullWhite (GenCalibratedModel (GenForeignPtr (AnyShortRateModel (GenForeignPtr (AnyOneFactorAffineModel (GenForeignPtr x _)) _)) _)) = withForeignPtr x

peekG2 :: Ptr CG2' -> IO G2
peekG2 = peekGenShortRateModel
withG2 :: G2 -> (Ptr CG2' -> IO b) -> IO b
withG2 (GenCalibratedModel (GenForeignPtr (AnyShortRateModel (GenForeignPtr x _)) _)) = withForeignPtr x

data NonAffineModel
newtype AffineModel a = AffineModel (forall r. a -> (Ptr CAffineModel' -> IO r) -> IO r)
newtype GenAffineModel a = GenAffineModel (GenForeignPtr a CAffineModel')
type CAffineModel = ForeignPtr CAffineModel'
foreign import ccall "ql.h qlOneFactorAffineModelAsAffineModel" qlOneFactorAffineModelAsAffineModel :: Ptr COneFactorAffineModel' -> IO (Ptr CAffineModel')
foreign import ccall "ql.h qlLiborForwardModelAsAffineModel" qlLiborForwardModelAsAffineModel :: Ptr CLiborForwardModel' -> IO (Ptr CAffineModel')
foreign import ccall "ql.h qlG2AsAffineModel" qlG2AsAffineModel :: Ptr CG2' -> IO (Ptr CAffineModel')
foreign import ccall "ql.h qlHullWhiteAsAffineModel" qlHullWhiteAsAffineModel :: Ptr CHullWhite' -> IO (Ptr CAffineModel')
withAffineModel = undefined
peekAffineModel = undefined
asAffineModel :: GenCalibratedModel a (AffineModel a) -> IO (GenAffineModel a)
asAffineModel = undefined

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
--newtype AnyNode1 a = AnyNode1 {getNode1 :: GenForeignPtr a CNode1'}
--type GenNode1 a = GenNode0 (AnyNode1 a)
--type CNode1 = ForeignPtr CNode1'
--type Node1 = GenNode1 CNode1
--type CLeaf2 = ForeignPtr CLeaf2'
--type Leaf2 = GenNode1 CLeaf2
--newtype AnyNode2 a = AnyNode2 {getNode2 :: GenForeignPtr a CNode2'}
--type GenNode2 a = GenNode1 (AnyNode2 a)
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
--instance Finalizable CNode0' where finalize = qlFreeNode0
--instance Finalizable CLeaf1' where finalize = qlFreeLeaf1
--instance Finalizable CNode1' where finalize = qlFreeNode1
--instance Finalizable CLeaf2' where finalize = qlFreeLeaf2
--instance Finalizable CNode2' where finalize = qlFreeNode2
--instance Finalizable CLeaf3' where finalize = qlFreeLeaf3
--foreign import ccall "ql.h qlLeaf1AsNode0" qlLeaf1AsNode0 :: Ptr CLeaf1' -> IO (Ptr CNode0')
--foreign import ccall "ql.h qlNode1AsNode0" qlNode1AsNode0 :: Ptr CNode1' -> IO (Ptr CNode0')
--foreign import ccall "ql.h qlLeaf2AsNode1" qlLeaf2AsNode1 :: Ptr CLeaf2' -> IO (Ptr CNode1')
--foreign import ccall "ql.h qlNode2AsNode1" qlNode2AsNode1 :: Ptr CNode2' -> IO (Ptr CNode1')
--foreign import ccall "ql.h qlLeaf3AsNode2" qlLeaf3AsNode2 :: Ptr CLeaf3' -> IO (Ptr CNode2')
--instance Upcastable CLeaf1' where {type Base CLeaf1' = CNode0'; upcast = qlLeaf1AsNode0}
--instance Upcastable CNode1' where {type Base CNode1' = CNode0'; upcast = qlNode1AsNode0}
--instance Upcastable CLeaf2' where {type Base CLeaf2' = CNode1'; upcast = qlLeaf2AsNode1}
--instance Upcastable CNode2' where {type Base CNode2' = CNode1'; upcast = qlNode2AsNode1}
--instance Upcastable CLeaf3' where {type Base CLeaf3' = CNode2'; upcast = qlLeaf3AsNode2}
--asNode0 :: GenNode0 a -> IO Node0
--asNode0 (GenNode0 (GenForeignPtr x w)) = w x peekNode0
--peekNode0 :: Ptr CNode0' -> IO Node0
--peekNode0 = GenNode0 <.> newCastForeignPtr
--withNode0 :: GenNode0 a -> (Ptr CNode0' -> IO b) -> IO b
--withNode0 (GenNode0 (GenForeignPtr x w)) = w x
--withGenNode0 :: GenNode0 (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
--withGenNode0 (GenNode0 (GenForeignPtr x _)) = withForeignPtr x
--peekLeaf1 :: Ptr CLeaf1' -> IO Leaf1
--peekLeaf1 = GenNode0 <.> newGenForeignPtr
--asNode1 :: GenNode1 a -> IO Node1
--asNode1 (GenNode0 (GenForeignPtr (AnyNode1 (GenForeignPtr x w)) _)) = w x peekNode1
--peekNode1 :: Ptr CNode1' -> IO Node1
--peekNode1 = newCastForeignPtr >=> newGenNode1
--withNode1 :: GenNode1 a -> (Ptr CNode1' -> IO b) -> IO b
--withNode1 (GenNode0 (GenForeignPtr (AnyNode1 (GenForeignPtr x w)) _)) = w x
--withMaybeNode1 :: Maybe (GenNode1 a) -> (Ptr CNode1' -> IO b) -> IO b
--withMaybeNode1 x f = maybe (f nullPtr) (`withNode1` f) x
--newGenNode1 :: GenForeignPtr a CNode1' -> IO (GenNode1 a)
--newGenNode1 p = GenNode0 <^> GenForeignPtr (AnyNode1 p) (withGenForeignPtr . getNode1)
--peekGenNode1 :: (Finalizable a, Upcastable a, Base a ~ CNode1') => Ptr a -> IO (GenNode1 (ForeignPtr a))
--peekGenNode1 = newGenForeignPtr >=> newGenNode1
--withGenNode1 :: GenNode1 (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
--withGenNode1 (GenNode0 (GenForeignPtr (AnyNode1 (GenForeignPtr x _)) _)) = withForeignPtr x
--peekLeaf2 :: Ptr CLeaf2' -> IO Leaf2
--peekLeaf2 = peekGenNode1
----withLeaf2 :: Leaf2 -> (Ptr CLeaf2' -> IO b) -> IO b
----withLeaf2 (GenNode0 (GenForeignPtr (AnyNode1 (GenForeignPtr x _)) _)) = withForeignPtr x
--asNode2 :: GenNode2 a -> IO Node2
--asNode2 (GenNode0 (GenForeignPtr (AnyNode1 (GenForeignPtr (AnyNode2 (GenForeignPtr x w)) _)) _)) = w x peekNode2
--peekNode2 :: Ptr CNode2' -> IO Node2
--peekNode2 = newCastForeignPtr >=> newGenNode2
--withNode2 :: GenNode2 a -> (Ptr CNode2' -> IO b) -> IO b
--withNode2 (GenNode0 (GenForeignPtr (AnyNode1 (GenForeignPtr (AnyNode2 (GenForeignPtr x w)) _)) _)) = w x
--newGenNode2 :: GenForeignPtr a CNode2' -> IO (GenNode2 a)
--newGenNode2 p = GenNode0 <^> GenForeignPtr (AnyNode1 $ GenForeignPtr (AnyNode2 p) (withGenForeignPtr . getNode2)) (withGenForeignPtr . getNode1)
--peekLeaf3 :: Ptr CLeaf3' -> IO Leaf3
--peekLeaf3 = newGenForeignPtr >=> newGenNode2
----withLeaf3 :: Leaf3 -> (Ptr CLeaf3' -> IO b) -> IO b
----withLeaf3 (GenNode0 (GenForeignPtr (AnyNode1 (GenForeignPtr (AnyNode2 (GenForeignPtr x _)) _)) _)) = withForeignPtr x

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
