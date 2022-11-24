{-# LANGUAGE FlexibleInstances, RankNTypes, DuplicateRecordFields #-}
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

  , BatesProcess
  , CBatesProcess
  , peekBatesProcess
  , withBatesProcess
  , BlackProcess
  , CBlackProcess
  , peekBlackProcess
  , withBlackProcess
  , ExtendedOrnsteinUhlenbeckProcess
  , CExtendedOrnsteinUhlenbeckProcess
  , peekExtendedOrnsteinUhlenbeckProcess
  , withExtendedOrnsteinUhlenbeckProcess
  , ExtOUWithJumpsProcess
  , CExtOUWithJumpsProcess
  , peekExtOUWithJumpsProcess
  , withExtOUWithJumpsProcess
  , GeneralizedBlackScholesProcess
  , CGeneralizedBlackScholesProcess
  , peekGeneralizedBlackScholesProcess
  , withGeneralizedBlackScholesProcess
  , GJRGARCHProcess
  , CGJRGARCHProcess
  , peekGJRGARCHProcess
  , withGJRGARCHProcess
  , HestonProcess
  , CHestonProcess
  , peekHestonProcess
  , withHestonProcess
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
  , KlugeExtOUProcess
  , CKlugeExtOUProcess
  , peekKlugeExtOUProcess
  , withKlugeExtOUProcess
  , LiborForwardModelProcess
  , CLiborForwardModelProcess
  , peekLiborForwardModelProcess
  , withLiborForwardModelProcess
  , withStochasticProcess1DArray
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
  , VarianceGammaProcess
  , CVarianceGammaProcess
  , peekVarianceGammaProcess
  , withVarianceGammaProcess
  , Merton76Process
  , CMerton76Process
  , peekMerton76Process
  , withMerton76Process
)
  where
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

(<.>) :: Functor f => (a1 -> b) -> (a2 -> f a1) -> a2 -> f b
f1 <.> f2 = fmap f1 . f2

(<^>) :: Applicative f => (t -> a) -> t -> f a
f <^> x = pure $ f x

-- STANDALONE TYPES
newtype Standalone a = Standalone {_ptr :: ForeignPtr a}
newtype Meta a = Meta (FinalizerPtr a)
peekStandalone :: Meta a -> Ptr a -> IO (Standalone a)
peekStandalone (Meta f) = Standalone <.> newForeignPtr f
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
foreign import ccall "ql.h &qlFreeCalendar" qlFreeCalendar :: FinalizerPtr CCalendar
metaCalendar :: Meta CCalendar
metaCalendar = Meta qlFreeCalendar
peekCalendar :: Ptr CCalendar -> IO Calendar
peekCalendar = Calendar <.> peekStandalone metaCalendar
withCalendar :: Calendar -> (Ptr CCalendar -> IO b) -> IO b
withCalendar = withStandalone . getCCalendar
foreign import ccall safe "ql.h qlCalendarName" qlCalendarName :: Ptr CCalendar -> IO CString
instance Show Calendar where show x = showStandalone qlCalendarName (getCCalendar x)
instance Eq Calendar where x == y = show x == show y

data CCurrency
newtype Currency = Currency {getCCurrency :: Standalone CCurrency}
foreign import ccall "ql.h &qlFreeCurrency" qlFreeCurrency :: FinalizerPtr CCurrency
metaCurrency :: Meta CCurrency
metaCurrency = Meta qlFreeCurrency
peekCurrency :: Ptr CCurrency -> IO Currency
peekCurrency = Currency <.> peekStandalone metaCurrency
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
metaDayCounter :: Meta CDayCounter
metaDayCounter = Meta qlFreeDayCounter
peekDayCounter :: Ptr CDayCounter -> IO DayCounter
peekDayCounter = DayCounter <.> peekStandalone metaDayCounter
withDayCounter :: DayCounter -> (Ptr CDayCounter -> IO b) -> IO b
withDayCounter = withStandalone . getCDayCounter
foreign import ccall safe "ql.h qlDayCounterName" qlDayCounterName :: Ptr CDayCounter -> IO CString
instance Show DayCounter where show x = showStandalone qlDayCounterName (getCDayCounter x)
instance Eq DayCounter where x == y = show x == show y

data CSchedule
newtype Schedule = Schedule {getCSchedule :: Standalone CSchedule}
foreign import ccall "ql.h &qlFreeSchedule" qlFreeSchedule :: FinalizerPtr CSchedule
metaSchedule :: Meta CSchedule
metaSchedule = Meta qlFreeSchedule
peekSchedule :: Ptr CSchedule -> IO Schedule
peekSchedule = Schedule <.> peekStandalone metaSchedule
withSchedule :: Schedule -> (Ptr CSchedule -> IO b) -> IO b
withSchedule = withStandalone . getCSchedule

data CInterestRate
newtype InterestRate = InterestRate {getCInterestRate :: Standalone CInterestRate}
foreign import ccall "ql.h &qlFreeInterestRate" qlFreeInterestRate :: FinalizerPtr CInterestRate
metaInterestRate :: Meta CInterestRate
metaInterestRate = Meta qlFreeInterestRate
peekInterestRate :: Ptr CInterestRate -> IO InterestRate
peekInterestRate = InterestRate <.> peekStandalone metaInterestRate
withInterestRate :: InterestRate -> (Ptr CInterestRate -> IO b) -> IO b
withInterestRate = withStandalone . getCInterestRate
withInterestRateArray :: [InterestRate] -> ((CUInt, Ptr (Ptr CInterestRate)) -> IO b) -> IO b
withInterestRateArray = withStandaloneArray getCInterestRate

data CTimeGrid
newtype TimeGrid = TimeGrid {getCTimeGrid :: Standalone CTimeGrid}
foreign import ccall "ql.h &qlFreeTimeGrid" qlFreeTimeGrid :: FinalizerPtr CTimeGrid
metaTimeGrid :: Meta CTimeGrid
metaTimeGrid = Meta qlFreeTimeGrid
peekTimeGrid :: Ptr CTimeGrid -> IO TimeGrid
peekTimeGrid = TimeGrid <.> peekStandalone metaTimeGrid
withTimeGrid :: TimeGrid -> (Ptr CTimeGrid -> IO b) -> IO b
withTimeGrid = withStandalone . getCTimeGrid

data CDividend
newtype Dividend = Dividend {getCDividend :: Standalone CDividend}
foreign import ccall "ql.h &qlFreeDividend" qlFreeDividend :: FinalizerPtr CDividend
metaDividend :: Meta CDividend
metaDividend = Meta qlFreeDividend
peekDividend :: Ptr CDividend -> IO Dividend
peekDividend = Dividend <.> peekStandalone metaDividend
withDividend :: Dividend -> (Ptr CDividend -> IO b) -> IO b
withDividend = withStandalone . getCDividend
withDividendArray :: [Dividend] -> ((CUInt, Ptr (Ptr CDividend)) -> IO b) -> IO b
withDividendArray = withStandaloneArray getCDividend

data CSmileSection
newtype SmileSection = SmileSection {getCSmileSection :: Standalone CSmileSection}
foreign import ccall "ql.h &qlFreeSmileSection" qlFreeSmileSection :: FinalizerPtr CSmileSection
metaSmileSection :: Meta CSmileSection
metaSmileSection = Meta qlFreeSmileSection
peekSmileSection :: Ptr CSmileSection -> IO SmileSection
peekSmileSection = SmileSection <.> peekStandalone metaSmileSection
withSmileSection :: SmileSection -> (Ptr CSmileSection -> IO b) -> IO b
withSmileSection = withStandalone . getCSmileSection

data CPricingEngine
newtype PricingEngine = PricingEngine {getCPricingEngine :: Standalone CPricingEngine}
foreign import ccall "ql.h &qlFreePricingEngine" qlFreePricingEngine :: FinalizerPtr CPricingEngine
metaPricingEngine :: Meta CPricingEngine
metaPricingEngine = Meta qlFreePricingEngine
peekPricingEngine :: Ptr CPricingEngine -> IO PricingEngine
peekPricingEngine = PricingEngine <.> peekStandalone metaPricingEngine
withPricingEngine :: PricingEngine -> (Ptr CPricingEngine -> IO b) -> IO b
withPricingEngine = withStandalone . getCPricingEngine

data CFloatingRateCouponPricer
newtype FloatingRateCouponPricer = FloatingRateCouponPricer {getCFloatingRateCouponPricer :: Standalone CFloatingRateCouponPricer}
foreign import ccall "ql.h &qlFreeFloatingCouponPricer" qlFreeFloatingRateCouponPricer :: FinalizerPtr CFloatingRateCouponPricer
metaFloatingRateCouponPricer :: Meta CFloatingRateCouponPricer
metaFloatingRateCouponPricer = Meta qlFreeFloatingRateCouponPricer
peekFloatingRateCouponPricer :: Ptr CFloatingRateCouponPricer -> IO FloatingRateCouponPricer
peekFloatingRateCouponPricer = FloatingRateCouponPricer <.> peekStandalone metaFloatingRateCouponPricer
withFloatingRateCouponPricer :: FloatingRateCouponPricer -> (Ptr CFloatingRateCouponPricer -> IO b) -> IO b
withFloatingRateCouponPricer = withStandalone . getCFloatingRateCouponPricer
withFloatingRateCouponPricerArray :: [FloatingRateCouponPricer] -> ((CUInt, Ptr (Ptr CFloatingRateCouponPricer)) -> IO b) -> IO b
withFloatingRateCouponPricerArray = withStandaloneArray getCFloatingRateCouponPricer

data CDefaultProbabilityHelper
newtype DefaultProbabilityHelper = DefaultProbabilityHelper {getCDefaultProbabilityHelper :: Standalone CDefaultProbabilityHelper}
foreign import ccall "ql.h &qlFreeDefaultProbabilityHelper" qlFreeDefaultProbabilityHelper :: FinalizerPtr CDefaultProbabilityHelper
metaDefaultProbabilityHelper :: Meta CDefaultProbabilityHelper
metaDefaultProbabilityHelper = Meta qlFreeDefaultProbabilityHelper
peekDefaultProbabilityHelper :: Ptr CDefaultProbabilityHelper -> IO DefaultProbabilityHelper
peekDefaultProbabilityHelper = DefaultProbabilityHelper <.> peekStandalone metaDefaultProbabilityHelper
withDefaultProbabilityHelper :: DefaultProbabilityHelper -> (Ptr CDefaultProbabilityHelper -> IO b) -> IO b
withDefaultProbabilityHelper = withStandalone . getCDefaultProbabilityHelper
withDefaultProbabilityHelperArray :: [DefaultProbabilityHelper] -> ((CUInt, Ptr (Ptr CDefaultProbabilityHelper)) -> IO b) -> IO b
withDefaultProbabilityHelperArray = withStandaloneArray getCDefaultProbabilityHelper

data CPathGenerator
newtype PathGenerator = PathGenerator {getCPathGenerator :: Standalone CPathGenerator}
foreign import ccall "ql.h &qlFreePathGenerator" qlFreePathGenerator :: FinalizerPtr CPathGenerator
metaPathGenerator :: Meta CPathGenerator
metaPathGenerator = Meta qlFreePathGenerator
peekPathGenerator :: Ptr CPathGenerator -> IO PathGenerator
peekPathGenerator = PathGenerator <.> peekStandalone metaPathGenerator
withPathGenerator :: PathGenerator -> (Ptr CPathGenerator -> IO b) -> IO b
withPathGenerator = withStandalone . getCPathGenerator

data CSamplePath
newtype SamplePath = SamplePath {getCSamplePath :: Standalone CSamplePath}
foreign import ccall "ql.h &qlFreeSamplePath" qlFreeSamplePath :: FinalizerPtr CSamplePath
metaSamplePath :: Meta CSamplePath
metaSamplePath = Meta qlFreeSamplePath
peekSamplePath :: Ptr CSamplePath -> IO SamplePath
peekSamplePath = SamplePath <.> peekStandalone metaSamplePath
withSamplePath :: SamplePath -> (Ptr CSamplePath -> IO b) -> IO b
withSamplePath = withStandalone . getCSamplePath

-- special cases: those types will be represented as enums so no need to wrap them
data CQlClaim
type QlClaim = Standalone CQlClaim
foreign import ccall "ql.h &qlFreeClaim" qlFreeClaim :: FinalizerPtr CQlClaim
metaClaim :: Meta CQlClaim
metaClaim = Meta qlFreeClaim
peekClaim :: Ptr CQlClaim -> IO (Standalone CQlClaim)
peekClaim = peekStandalone metaClaim

data CQlCallability
type QlCallability = Standalone CQlCallability
foreign import ccall "ql.h &qlFreeCallability" qlFreeCallability :: FinalizerPtr CQlCallability
metaCallability :: Meta CQlCallability
metaCallability = Meta qlFreeCallability
peekCallability :: Ptr CQlCallability -> IO (Standalone CQlCallability)
peekCallability = peekStandalone metaCallability

data CConstraint
type QlConstraint = Standalone CConstraint
foreign import ccall "ql.h &qlFreeConstraint" qlFreeConstraint :: FinalizerPtr CConstraint
metaConstraint :: Meta CConstraint
metaConstraint = Meta qlFreeConstraint
peekConstraint :: Ptr CConstraint -> IO (Standalone CConstraint)
peekConstraint = peekStandalone metaConstraint

data CEndCriteria
type QlEndCriteria = Standalone CEndCriteria
foreign import ccall "ql.h &qlFreeEndCriteria" qlFreeEndCriteria :: FinalizerPtr CEndCriteria
metaEndCritetia :: Meta CEndCriteria
metaEndCritetia = Meta qlFreeEndCriteria
peekEndCriteria :: Ptr CEndCriteria -> IO (Standalone CEndCriteria)
peekEndCriteria = peekStandalone metaEndCritetia

data CFdmSchemeDesc
type QlFdmSchemeDesc = Standalone CFdmSchemeDesc
foreign import ccall "ql.h &qlFreeFdmSchemeDesc" qlFreeFdmSchemeDesc :: FinalizerPtr CFdmSchemeDesc
metaFdmSchemeDesc :: Meta CFdmSchemeDesc
metaFdmSchemeDesc = Meta qlFreeFdmSchemeDesc
peekFdmSchemeDesc :: Ptr CFdmSchemeDesc -> IO (Standalone CFdmSchemeDesc)
peekFdmSchemeDesc = peekStandalone metaFdmSchemeDesc

data CFittedBondDiscountCurveFittingMethod
type QlFittedBondDiscountCurveFittingMethod = Standalone CFittedBondDiscountCurveFittingMethod
foreign import ccall "ql.h &qlFreeFittedBondDiscountCurveFittingMethod" qlFreeFittedBondDiscountCurveFittingMethod :: FinalizerPtr CFittedBondDiscountCurveFittingMethod
metaFittedBondDiscountCurveFittingMethod :: Meta CFittedBondDiscountCurveFittingMethod
metaFittedBondDiscountCurveFittingMethod = Meta qlFreeFittedBondDiscountCurveFittingMethod
peekFittedBondDiscountCurveFittingMethod :: Ptr CFittedBondDiscountCurveFittingMethod -> IO (Standalone CFittedBondDiscountCurveFittingMethod)
peekFittedBondDiscountCurveFittingMethod = peekStandalone metaFittedBondDiscountCurveFittingMethod

data COptimizationMethod
type QlOptimizationMethod = Standalone COptimizationMethod
foreign import ccall "ql.h &qlFreeOptimizationMethod" qlFreeOptimizationMethod :: FinalizerPtr COptimizationMethod
metaOptimizationMethod :: Meta COptimizationMethod
metaOptimizationMethod = Meta qlFreeOptimizationMethod
peekOptimizationMethod :: Ptr COptimizationMethod -> IO (Standalone COptimizationMethod)
peekOptimizationMethod = peekStandalone metaOptimizationMethod

data CRounding
type QlRounding = Standalone CRounding
foreign import ccall "ql.h &qlFreeRounding" qlFreeRounding :: FinalizerPtr CRounding
metaRounding :: Meta CRounding
metaRounding = Meta qlFreeRounding
peekRounding :: Ptr CRounding -> IO (Standalone CRounding)
peekRounding = peekStandalone metaRounding

data CLmCorrelationModel
type QlLmCorrelationModel = Standalone CLmCorrelationModel
foreign import ccall "ql.h &qlFreeLmCorrelationModel" qlFreeLmCorrelationModel :: FinalizerPtr CLmCorrelationModel
metaLmCorrelationModel :: Meta CLmCorrelationModel
metaLmCorrelationModel = Meta qlFreeLmCorrelationModel
peekLmCorrelationModel :: Ptr CLmCorrelationModel -> IO (Standalone CLmCorrelationModel)
peekLmCorrelationModel = peekStandalone metaLmCorrelationModel

data CLmVolatilityModel
type QlLmVolatilityModel = Standalone CLmVolatilityModel
foreign import ccall "ql.h &qlFreeLmVolatilityModel" qlFreeLmVolatilityModel :: FinalizerPtr CLmVolatilityModel
metaLmVolatilityModel :: Meta CLmVolatilityModel
metaLmVolatilityModel = Meta qlFreeLmVolatilityModel
peekLmVolatilityModel :: Ptr CLmVolatilityModel -> IO (Standalone CLmVolatilityModel)
peekLmVolatilityModel = peekStandalone metaLmVolatilityModel

-- TYPE HIERARCHIES
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
withDescendant (GenObject p (Upcast k fi)) ff =
    withForeignPtr p (k >=> \pp ->
      (if fi /= nullFunPtr
        then newForeignPtr fi pp >>= (`withForeignPtr` ff)
        else ff pp))
withMaybeDescendant :: Maybe (GenObject a p) -> (Ptr p -> IO b) -> IO b
withMaybeDescendant x f = maybe (f nullPtr) (`withDescendant` f) x
withDescendantArray :: [GenObject a p] -> ((CUInt, Ptr (Ptr p)) -> IO b) -> IO b
withDescendantArray x f = withMany withDescendant x (`withArray` (\px -> f (fromIntegral $ length x, px)))
withDescendantArrayRaw :: [GenObject a p] -> (Ptr (Ptr p) -> IO b) -> IO b
withDescendantArrayRaw x f = withMany withDescendant x (`withArray` f)

---- instantiations
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
withGenForeignUpcastInterestRateIndex :: InterestRateIndexDescendant a -> (Ptr CIndex' -> IO b) -> IO b
withGenForeignUpcastInterestRateIndex (InterestRateIndexDescendant o) = withGenForeignPtr upcastInterestRateIndex o
newInterestRateIndexDescendant :: GenForeignPtr a CInterestRateIndex' -> IO (GenIndex (InterestRateIndexDescendant a))
newInterestRateIndexDescendant p = GenIndex <^> GenForeignPtr (InterestRateIndexDescendant p) withGenForeignUpcastInterestRateIndex

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
withGenForeignUpcastIborIndex :: IborIndexDescendant a -> (Ptr CInterestRateIndex' -> IO b) -> IO b
withGenForeignUpcastIborIndex (IborIndexDescendant o) = withGenForeignPtr upcastIborIndex o
newIborIndexDescendant :: GenForeignPtr a CIborIndex' -> IO (GenIborIndex a)
newIborIndexDescendant p = GenIndex <^> GenForeignPtr (InterestRateIndexDescendant $ GenForeignPtr (IborIndexDescendant p) withGenForeignUpcastIborIndex) withGenForeignUpcastInterestRateIndex

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
withGenForeignUpcastSwapIndex :: SwapIndexDescendant a -> (Ptr CInterestRateIndex' -> IO b) -> IO b
withGenForeignUpcastSwapIndex (SwapIndexDescendant o) = withGenForeignPtr upcastSwapIndex o
newSwapIndexDescendant :: GenForeignPtr a CSwapIndex' -> IO (GenSwapIndex a)
newSwapIndexDescendant p = GenIndex <^> GenForeignPtr (InterestRateIndexDescendant $ GenForeignPtr (SwapIndexDescendant p) withGenForeignUpcastSwapIndex) withGenForeignUpcastInterestRateIndex

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
withGenForeignUpcastVolatilityTermStructure :: VolatilityTermStructureDescendant a -> (Ptr CTermStructure' -> IO b) -> IO b
withGenForeignUpcastVolatilityTermStructure (VolatilityTermStructureDescendant o) = withGenForeignPtr upcastVolatilityTermStructure o
withVolatilityTermStructureDescendant :: GenVolatilityTermStructure (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
withVolatilityTermStructureDescendant (GenTermStructure (GenForeignPtr (VolatilityTermStructureDescendant (GenForeignPtr x _)) _)) = withForeignPtr x
newVolatilityTermStructureDescendant :: GenForeignPtr a CVolatilityTermStructure' -> IO (GenVolatilityTermStructure a)
newVolatilityTermStructureDescendant p = GenTermStructure <^> GenForeignPtr (VolatilityTermStructureDescendant p) withGenForeignUpcastVolatilityTermStructure

asBlackVolTermStructure :: GenBlackVolTermStructure a -> IO BlackVolTermStructure
asBlackVolTermStructure (GenTermStructure (GenForeignPtr (VolatilityTermStructureDescendant (GenForeignPtr (BlackVolTermStructureDescendant (GenForeignPtr x w)) _)) _)) = w x peekBlackVolTermStructure
peekBlackVolTermStructure :: Ptr CBlackVolTermStructure' -> IO BlackVolTermStructure
peekBlackVolTermStructure = newCastForeignPtr metaBlackVolTermStructure >=> newBlackVolTermStructureDescendant
withBlackVolTermStructure :: GenBlackVolTermStructure a -> (Ptr CBlackVolTermStructure' -> IO b) -> IO b
withBlackVolTermStructure (GenTermStructure (GenForeignPtr (VolatilityTermStructureDescendant (GenForeignPtr (BlackVolTermStructureDescendant (GenForeignPtr x w)) _)) _)) = w x
withGenForeignUpcastBlackVolTermStructure :: BlackVolTermStructureDescendant a -> (Ptr CVolatilityTermStructure' -> IO b) -> IO b
withGenForeignUpcastBlackVolTermStructure (BlackVolTermStructureDescendant o) = withGenForeignPtr upcastBlackVolTermStructure o
newBlackVolTermStructureDescendant :: GenForeignPtr a CBlackVolTermStructure' -> IO (GenBlackVolTermStructure a)
newBlackVolTermStructureDescendant p = GenTermStructure <^> GenForeignPtr (VolatilityTermStructureDescendant $ GenForeignPtr (BlackVolTermStructureDescendant p) withGenForeignUpcastBlackVolTermStructure) withGenForeignUpcastVolatilityTermStructure

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
withGenForeignUpcastYieldTermStructure :: YieldTermStructureDescendant a -> (Ptr CTermStructure' -> IO b) -> IO b
withGenForeignUpcastYieldTermStructure (YieldTermStructureDescendant o) = withGenForeignPtr upcastYieldTermStructure o
newYieldTermStructureDescendant :: GenForeignPtr a CYieldTermStructure' -> IO (GenYieldTermStructure a)
newYieldTermStructureDescendant p = GenTermStructure <^> GenForeignPtr (YieldTermStructureDescendant p) withGenForeignUpcastYieldTermStructure

peekFittedBondDiscountCurve :: Ptr CFittedBondDiscountCurve' -> IO FittedBondDiscountCurve
peekFittedBondDiscountCurve = newGenForeignPtr metaFittedBondDiscountCurve upcastFittedBondDiscountCurve >=> newYieldTermStructureDescendant
withFittedBondDiscountCurve :: FittedBondDiscountCurve -> (Ptr CFittedBondDiscountCurve' -> IO b) -> IO b
withFittedBondDiscountCurve (GenTermStructure (GenForeignPtr (YieldTermStructureDescendant (GenForeignPtr x _)) _)) = withForeignPtr x

-- TEMPORARY STORAGE BEFORE HIERARCHIES ARE MIGRATED OFF TYPE CLASSES

data CAssetSwap
newtype AssetSwap = AssetSwap {getCAssetSwap :: Standalone CAssetSwap}
metaAssetSwap :: Meta CAssetSwap
metaAssetSwap = Meta qlFreeAssetSwap
peekAssetSwap :: Ptr CAssetSwap -> IO AssetSwap
peekAssetSwap = peekStandalone metaAssetSwap >=> return . AssetSwap
withAssetSwap :: AssetSwap -> (Ptr CAssetSwap -> IO b) -> IO b
withAssetSwap = withStandalone . getCAssetSwap
data CBarrierOption
newtype BarrierOption = BarrierOption {getCBarrierOption :: Standalone CBarrierOption}
metaBarrierOption :: Meta CBarrierOption
metaBarrierOption = Meta qlFreeBarrierOption
peekBarrierOption :: Ptr CBarrierOption -> IO BarrierOption
peekBarrierOption = peekStandalone metaBarrierOption >=> return . BarrierOption
withBarrierOption :: BarrierOption -> (Ptr CBarrierOption -> IO b) -> IO b
withBarrierOption = withStandalone . getCBarrierOption
data CBMASwap
newtype BMASwap = BMASwap {getCBMASwap :: Standalone CBMASwap}
metaBMASwap :: Meta CBMASwap
metaBMASwap = Meta qlFreeBMASwap
peekBMASwap :: Ptr CBMASwap -> IO BMASwap
peekBMASwap = peekStandalone metaBMASwap >=> return . BMASwap
withBMASwap :: BMASwap -> (Ptr CBMASwap -> IO b) -> IO b
withBMASwap = withStandalone . getCBMASwap
data CBond
newtype Bond = Bond {getCBond :: Standalone CBond}
metaBond :: Meta CBond
metaBond = Meta qlFreeBond
peekBond :: Ptr CBond -> IO Bond
peekBond = peekStandalone metaBond >=> return . Bond
withBond :: Bond -> (Ptr CBond -> IO b) -> IO b
withBond = withStandalone . getCBond
data CCallableBond
newtype CallableBond = CallableBond {getCCallableBond :: Standalone CCallableBond}
metaCallableBond :: Meta CCallableBond
metaCallableBond = Meta qlFreeCallableBond
peekCallableBond :: Ptr CCallableBond -> IO CallableBond
peekCallableBond = peekStandalone metaCallableBond >=> return . CallableBond
withCallableBond :: CallableBond -> (Ptr CCallableBond -> IO b) -> IO b
withCallableBond = withStandalone . getCCallableBond
data CCapFloor
newtype CapFloor = CapFloor {getCCapFloor :: Standalone CCapFloor}
metaCapFloor :: Meta CCapFloor
metaCapFloor = Meta qlFreeCapFloor
peekCapFloor :: Ptr CCapFloor -> IO CapFloor
peekCapFloor = peekStandalone metaCapFloor >=> return . CapFloor
withCapFloor :: CapFloor -> (Ptr CCapFloor -> IO b) -> IO b
withCapFloor = withStandalone . getCCapFloor
data CCdsOption
newtype CdsOption = CdsOption {getCCdsOption :: Standalone CCdsOption}
metaCdsOption :: Meta CCdsOption
metaCdsOption = Meta qlFreeCdsOption
peekCdsOption :: Ptr CCdsOption -> IO CdsOption
peekCdsOption = peekStandalone metaCdsOption >=> return . CdsOption
withCdsOption :: CdsOption -> (Ptr CCdsOption -> IO b) -> IO b
withCdsOption = withStandalone . getCCdsOption
data CConvertibleBond
newtype ConvertibleBond = ConvertibleBond {getCConvertibleBond :: Standalone CConvertibleBond}
metaConvertibleBond :: Meta CConvertibleBond
metaConvertibleBond = Meta qlFreeConvertibleBond
peekConvertibleBond :: Ptr CConvertibleBond -> IO ConvertibleBond
peekConvertibleBond = peekStandalone metaConvertibleBond >=> return . ConvertibleBond
withConvertibleBond :: ConvertibleBond -> (Ptr CConvertibleBond -> IO b) -> IO b
withConvertibleBond = withStandalone . getCConvertibleBond
data CCreditDefaultSwap
newtype CreditDefaultSwap = CreditDefaultSwap {getCCreditDefaultSwap :: Standalone CCreditDefaultSwap}
metaCreditDefaultSwap :: Meta CCreditDefaultSwap
metaCreditDefaultSwap = Meta qlFreeCreditDefaultSwap
peekCreditDefaultSwap :: Ptr CCreditDefaultSwap -> IO CreditDefaultSwap
peekCreditDefaultSwap = peekStandalone metaCreditDefaultSwap >=> return . CreditDefaultSwap
withCreditDefaultSwap :: CreditDefaultSwap -> (Ptr CCreditDefaultSwap -> IO b) -> IO b
withCreditDefaultSwap = withStandalone . getCCreditDefaultSwap
data CDividendVanillaOption
newtype DividendVanillaOption = DividendVanillaOption {getCDividendVanillaOption :: Standalone CDividendVanillaOption}
metaDividendVanillaOption :: Meta CDividendVanillaOption
metaDividendVanillaOption = Meta qlFreeDividendVanillaOption
peekDividendVanillaOption :: Ptr CDividendVanillaOption -> IO DividendVanillaOption
peekDividendVanillaOption = peekStandalone metaDividendVanillaOption >=> return . DividendVanillaOption
withDividendVanillaOption :: DividendVanillaOption -> (Ptr CDividendVanillaOption -> IO b) -> IO b
withDividendVanillaOption = withStandalone . getCDividendVanillaOption
data CFixedRateBond
newtype FixedRateBond = FixedRateBond {getCFixedRateBond :: Standalone CFixedRateBond}
metaFixedRateBond :: Meta CFixedRateBond
metaFixedRateBond = Meta qlFreeFixedRateBond
peekFixedRateBond :: Ptr CFixedRateBond -> IO FixedRateBond
peekFixedRateBond = peekStandalone metaFixedRateBond >=> return . FixedRateBond
withFixedRateBond :: FixedRateBond -> (Ptr CFixedRateBond -> IO b) -> IO b
withFixedRateBond = withStandalone . getCFixedRateBond
data CBondForward
newtype BondForward = BondForward {getCBondForward :: Standalone CBondForward}
metaBondForward :: Meta CBondForward
metaBondForward = Meta qlFreeBondForward
peekBondForward :: Ptr CBondForward -> IO BondForward
peekBondForward = peekStandalone metaBondForward >=> return . BondForward
withBondForward :: BondForward -> (Ptr CBondForward -> IO b) -> IO b
withBondForward = withStandalone . getCBondForward
data CForward
newtype Forward = Forward {getCForward :: Standalone CForward}
metaForward :: Meta CForward
metaForward = Meta qlFreeForward
peekForward :: Ptr CForward -> IO Forward
peekForward = peekStandalone metaForward >=> return . Forward
withForward :: Forward -> (Ptr CForward -> IO b) -> IO b
withForward = withStandalone . getCForward
data CForwardRateAgreement
newtype ForwardRateAgreement = ForwardRateAgreement {getCForwardRateAgreement :: Standalone CForwardRateAgreement}
metaForwardRateAgreement :: Meta CForwardRateAgreement
metaForwardRateAgreement = Meta qlFreeForwardRateAgreement
peekForwardRateAgreement :: Ptr CForwardRateAgreement -> IO ForwardRateAgreement
peekForwardRateAgreement = peekStandalone metaForwardRateAgreement >=> return . ForwardRateAgreement
withForwardRateAgreement :: ForwardRateAgreement -> (Ptr CForwardRateAgreement -> IO b) -> IO b
withForwardRateAgreement = withStandalone . getCForwardRateAgreement
data CForwardVanillaOption
newtype ForwardVanillaOption = ForwardVanillaOption {getCForwardVanillaOption :: Standalone CForwardVanillaOption}
metaForwardVanillaOption :: Meta CForwardVanillaOption
metaForwardVanillaOption = Meta qlFreeForwardVanillaOption
peekForwardVanillaOption :: Ptr CForwardVanillaOption -> IO ForwardVanillaOption
peekForwardVanillaOption = peekStandalone metaForwardVanillaOption >=> return . ForwardVanillaOption
withForwardVanillaOption :: ForwardVanillaOption -> (Ptr CForwardVanillaOption -> IO b) -> IO b
withForwardVanillaOption = withStandalone . getCForwardVanillaOption
data CInstrument
newtype Instrument = Instrument {getCInstrument :: Standalone CInstrument}
metaInstrument :: Meta CInstrument
metaInstrument = Meta qlFreeInstrument
peekInstrument :: Ptr CInstrument -> IO Instrument
peekInstrument = peekStandalone metaInstrument >=> return . Instrument
withInstrument :: Instrument -> (Ptr CInstrument -> IO b) -> IO b
withInstrument = withStandalone . getCInstrument
data CMargrabeOption
newtype MargrabeOption = MargrabeOption {getCMargrabeOption :: Standalone CMargrabeOption}
metaMargrabeOption :: Meta CMargrabeOption
metaMargrabeOption = Meta qlFreeMargrabeOption
peekMargrabeOption :: Ptr CMargrabeOption -> IO MargrabeOption
peekMargrabeOption = peekStandalone metaMargrabeOption >=> return . MargrabeOption
withMargrabeOption :: MargrabeOption -> (Ptr CMargrabeOption -> IO b) -> IO b
withMargrabeOption = withStandalone . getCMargrabeOption
data CMultiAssetOption
newtype MultiAssetOption = MultiAssetOption {getCMultiAssetOption :: Standalone CMultiAssetOption}
metaMultiAssetOption :: Meta CMultiAssetOption
metaMultiAssetOption = Meta qlFreeMultiAssetOption
peekMultiAssetOption :: Ptr CMultiAssetOption -> IO MultiAssetOption
peekMultiAssetOption = peekStandalone metaMultiAssetOption >=> return . MultiAssetOption
withMultiAssetOption :: MultiAssetOption -> (Ptr CMultiAssetOption -> IO b) -> IO b
withMultiAssetOption = withStandalone . getCMultiAssetOption
data COneAssetOption
newtype OneAssetOption = OneAssetOption {getCOneAssetOption :: Standalone COneAssetOption}
metaOneAssetOption :: Meta COneAssetOption
metaOneAssetOption = Meta qlFreeOneAssetOption
peekOneAssetOption :: Ptr COneAssetOption -> IO OneAssetOption
peekOneAssetOption = peekStandalone metaOneAssetOption >=> return . OneAssetOption
withOneAssetOption :: OneAssetOption -> (Ptr COneAssetOption -> IO b) -> IO b
withOneAssetOption = withStandalone . getCOneAssetOption
data COption
newtype Option = Option {getCOption :: Standalone COption}
metaOption :: Meta COption
metaOption = Meta qlFreeOption
peekOption :: Ptr COption -> IO Option
peekOption = peekStandalone metaOption >=> return . Option
withOption :: Option -> (Ptr COption -> IO b) -> IO b
withOption = withStandalone . getCOption
data COvernightIndexedSwap
newtype OvernightIndexedSwap = OvernightIndexedSwap {getCOvernightIndexedSwap :: Standalone COvernightIndexedSwap}
metaOvernightIndexedSwap :: Meta COvernightIndexedSwap
metaOvernightIndexedSwap = Meta qlFreeOvernightIndexedSwap
peekOvernightIndexedSwap :: Ptr COvernightIndexedSwap -> IO OvernightIndexedSwap
peekOvernightIndexedSwap = peekStandalone metaOvernightIndexedSwap >=> return . OvernightIndexedSwap
withOvernightIndexedSwap :: OvernightIndexedSwap -> (Ptr COvernightIndexedSwap -> IO b) -> IO b
withOvernightIndexedSwap = withStandalone . getCOvernightIndexedSwap
data CQuantoBarrierOption
newtype QuantoBarrierOption = QuantoBarrierOption {getCQuantoBarrierOption :: Standalone CQuantoBarrierOption}
metaQuantoBarrierOption :: Meta CQuantoBarrierOption
metaQuantoBarrierOption = Meta qlFreeQuantoBarrierOption
peekQuantoBarrierOption :: Ptr CQuantoBarrierOption -> IO QuantoBarrierOption
peekQuantoBarrierOption = peekStandalone metaQuantoBarrierOption >=> return . QuantoBarrierOption
withQuantoBarrierOption :: QuantoBarrierOption -> (Ptr CQuantoBarrierOption -> IO b) -> IO b
withQuantoBarrierOption = withStandalone . getCQuantoBarrierOption
data CQuantoForwardVanillaOption
newtype QuantoForwardVanillaOption = QuantoForwardVanillaOption {getCQuantoForwardVanillaOption :: Standalone CQuantoForwardVanillaOption}
metaQuantoForwardVanillaOption :: Meta CQuantoForwardVanillaOption
metaQuantoForwardVanillaOption = Meta qlFreeQuantoForwardVanillaOption
peekQuantoForwardVanillaOption :: Ptr CQuantoForwardVanillaOption -> IO QuantoForwardVanillaOption
peekQuantoForwardVanillaOption = peekStandalone metaQuantoForwardVanillaOption >=> return . QuantoForwardVanillaOption
withQuantoForwardVanillaOption :: QuantoForwardVanillaOption -> (Ptr CQuantoForwardVanillaOption -> IO b) -> IO b
withQuantoForwardVanillaOption = withStandalone . getCQuantoForwardVanillaOption
data CQuantoVanillaOption
newtype QuantoVanillaOption = QuantoVanillaOption {getCQuantoVanillaOption :: Standalone CQuantoVanillaOption}
metaQuantoVanillaOption :: Meta CQuantoVanillaOption
metaQuantoVanillaOption = Meta qlFreeQuantoVanillaOption
peekQuantoVanillaOption :: Ptr CQuantoVanillaOption -> IO QuantoVanillaOption
peekQuantoVanillaOption = peekStandalone metaQuantoVanillaOption >=> return . QuantoVanillaOption
withQuantoVanillaOption :: QuantoVanillaOption -> (Ptr CQuantoVanillaOption -> IO b) -> IO b
withQuantoVanillaOption = withStandalone . getCQuantoVanillaOption
data CSwap
newtype Swap = Swap {getCSwap :: Standalone CSwap}
metaSwap :: Meta CSwap
metaSwap = Meta qlFreeSwap
peekSwap :: Ptr CSwap -> IO Swap
peekSwap = peekStandalone metaSwap >=> return . Swap
withSwap :: Swap -> (Ptr CSwap -> IO b) -> IO b
withSwap = withStandalone . getCSwap
data CSwaption
newtype Swaption = Swaption {getCSwaption :: Standalone CSwaption}
metaSwaption :: Meta CSwaption
metaSwaption = Meta qlFreeSwaption
peekSwaption :: Ptr CSwaption -> IO Swaption
peekSwaption = peekStandalone metaSwaption >=> return . Swaption
withSwaption :: Swaption -> (Ptr CSwaption -> IO b) -> IO b
withSwaption = withStandalone . getCSwaption
data CVanillaOption
newtype VanillaOption = VanillaOption {getCVanillaOption :: Standalone CVanillaOption}
metaVanillaOption :: Meta CVanillaOption
metaVanillaOption = Meta qlFreeVanillaOption
peekVanillaOption :: Ptr CVanillaOption -> IO VanillaOption
peekVanillaOption = peekStandalone metaVanillaOption >=> return . VanillaOption
withVanillaOption :: VanillaOption -> (Ptr CVanillaOption -> IO b) -> IO b
withVanillaOption = withStandalone . getCVanillaOption
data CVanillaSwap
newtype VanillaSwap = VanillaSwap {getCVanillaSwap :: Standalone CVanillaSwap}
metaVanillaSwap :: Meta CVanillaSwap
metaVanillaSwap = Meta qlFreeVanillaSwap
peekVanillaSwap :: Ptr CVanillaSwap -> IO VanillaSwap
peekVanillaSwap = peekStandalone metaVanillaSwap >=> return . VanillaSwap
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
metaAffineModel :: Meta CAffineModel
metaAffineModel = Meta qlFreeAffineModel
peekAffineModel :: Ptr CAffineModel -> IO AffineModel
peekAffineModel = peekStandalone metaAffineModel >=> return . AffineModel
withAffineModel :: AffineModel -> (Ptr CAffineModel -> IO b) -> IO b
withAffineModel = withStandalone . getCAffineModel
data CBatesDetJumpModel
newtype BatesDetJumpModel = BatesDetJumpModel {getCBatesDetJumpModel :: Standalone CBatesDetJumpModel}
metaBatesDetJumpModel :: Meta CBatesDetJumpModel
metaBatesDetJumpModel = Meta qlFreeBatesDetJumpModel
peekBatesDetJumpModel :: Ptr CBatesDetJumpModel -> IO BatesDetJumpModel
peekBatesDetJumpModel = peekStandalone metaBatesDetJumpModel >=> return . BatesDetJumpModel
withBatesDetJumpModel :: BatesDetJumpModel -> (Ptr CBatesDetJumpModel -> IO b) -> IO b
withBatesDetJumpModel = withStandalone . getCBatesDetJumpModel
data CBatesDoubleExpDetJumpModel
newtype BatesDoubleExpDetJumpModel = BatesDoubleExpDetJumpModel {getCBatesDoubleExpDetJumpModel :: Standalone CBatesDoubleExpDetJumpModel}
metaBatesDoubleExpDetJumpModel :: Meta CBatesDoubleExpDetJumpModel
metaBatesDoubleExpDetJumpModel = Meta qlFreeBatesDoubleExpDetJumpModel
peekBatesDoubleExpDetJumpModel :: Ptr CBatesDoubleExpDetJumpModel -> IO BatesDoubleExpDetJumpModel
peekBatesDoubleExpDetJumpModel = peekStandalone metaBatesDoubleExpDetJumpModel >=> return . BatesDoubleExpDetJumpModel
withBatesDoubleExpDetJumpModel :: BatesDoubleExpDetJumpModel -> (Ptr CBatesDoubleExpDetJumpModel -> IO b) -> IO b
withBatesDoubleExpDetJumpModel = withStandalone . getCBatesDoubleExpDetJumpModel
data CBatesDoubleExpModel
newtype BatesDoubleExpModel = BatesDoubleExpModel {getCBatesDoubleExpModel :: Standalone CBatesDoubleExpModel}
metaBatesDoubleExpModel :: Meta CBatesDoubleExpModel
metaBatesDoubleExpModel = Meta qlFreeBatesDoubleExpModel
peekBatesDoubleExpModel :: Ptr CBatesDoubleExpModel -> IO BatesDoubleExpModel
peekBatesDoubleExpModel = peekStandalone metaBatesDoubleExpModel >=> return . BatesDoubleExpModel
withBatesDoubleExpModel :: BatesDoubleExpModel -> (Ptr CBatesDoubleExpModel -> IO b) -> IO b
withBatesDoubleExpModel = withStandalone . getCBatesDoubleExpModel
data CBatesModel
newtype BatesModel = BatesModel {getCBatesModel :: Standalone CBatesModel}
metaBatesModel :: Meta CBatesModel
metaBatesModel = Meta qlFreeBatesModel
peekBatesModel :: Ptr CBatesModel -> IO BatesModel
peekBatesModel = peekStandalone metaBatesModel >=> return . BatesModel
withBatesModel :: BatesModel -> (Ptr CBatesModel -> IO b) -> IO b
withBatesModel = withStandalone . getCBatesModel
data CCalibratedModel
newtype CalibratedModel = CalibratedModel {getCCalibratedModel :: Standalone CCalibratedModel}
metaCalibratedModel :: Meta CCalibratedModel
metaCalibratedModel = Meta qlFreeCalibratedModel
peekCalibratedModel :: Ptr CCalibratedModel -> IO CalibratedModel
peekCalibratedModel = peekStandalone metaCalibratedModel >=> return . CalibratedModel
withCalibratedModel :: CalibratedModel -> (Ptr CCalibratedModel -> IO b) -> IO b
withCalibratedModel = withStandalone . getCCalibratedModel
data CG2
newtype G2 = G2 {getCG2 :: Standalone CG2}
metaG2 :: Meta CG2
metaG2 = Meta qlFreeG2
peekG2 :: Ptr CG2 -> IO G2
peekG2 = peekStandalone metaG2 >=> return . G2
withG2 :: G2 -> (Ptr CG2 -> IO b) -> IO b
withG2 = withStandalone . getCG2
data CGJRGARCHModel
newtype GJRGARCHModel = GJRGARCHModel {getCGJRGARCHModel :: Standalone CGJRGARCHModel}
metaGJRGARCHModel :: Meta CGJRGARCHModel
metaGJRGARCHModel = Meta qlFreeGJRGARCHModel
peekGJRGARCHModel :: Ptr CGJRGARCHModel -> IO GJRGARCHModel
peekGJRGARCHModel = peekStandalone metaGJRGARCHModel >=> return . GJRGARCHModel
withGJRGARCHModel :: GJRGARCHModel -> (Ptr CGJRGARCHModel -> IO b) -> IO b
withGJRGARCHModel = withStandalone . getCGJRGARCHModel
data CHestonModel
newtype HestonModel = HestonModel {getCHestonModel :: Standalone CHestonModel}
metaHestonModel :: Meta CHestonModel
metaHestonModel = Meta qlFreeHestonModel
peekHestonModel :: Ptr CHestonModel -> IO HestonModel
peekHestonModel = peekStandalone metaHestonModel >=> return . HestonModel
withHestonModel :: HestonModel -> (Ptr CHestonModel -> IO b) -> IO b
withHestonModel = withStandalone . getCHestonModel
data CHullWhite
newtype HullWhite = HullWhite {getCHullWhite :: Standalone CHullWhite}
metaHullWhite :: Meta CHullWhite
metaHullWhite = Meta qlFreeHullWhite
peekHullWhite :: Ptr CHullWhite -> IO HullWhite
peekHullWhite = peekStandalone metaHullWhite >=> return . HullWhite
withHullWhite :: HullWhite -> (Ptr CHullWhite -> IO b) -> IO b
withHullWhite = withStandalone . getCHullWhite
data CLiborForwardModel
newtype LiborForwardModel = LiborForwardModel {getCLiborForwardModel :: Standalone CLiborForwardModel}
metaLiborForwardModel :: Meta CLiborForwardModel
metaLiborForwardModel = Meta qlFreeLiborForwardModel
peekLiborForwardModel :: Ptr CLiborForwardModel -> IO LiborForwardModel
peekLiborForwardModel = peekStandalone metaLiborForwardModel >=> return . LiborForwardModel
withLiborForwardModel :: LiborForwardModel -> (Ptr CLiborForwardModel -> IO b) -> IO b
withLiborForwardModel = withStandalone . getCLiborForwardModel
data COneFactorAffineModel
newtype OneFactorAffineModel = OneFactorAffineModel {getCOneFactorAffineModel :: Standalone COneFactorAffineModel}
metaOneFactorAffineModel :: Meta COneFactorAffineModel
metaOneFactorAffineModel = Meta qlFreeOneFactorAffineModel
peekOneFactorAffineModel :: Ptr COneFactorAffineModel -> IO OneFactorAffineModel
peekOneFactorAffineModel = peekStandalone metaOneFactorAffineModel >=> return . OneFactorAffineModel
withOneFactorAffineModel :: OneFactorAffineModel -> (Ptr COneFactorAffineModel -> IO b) -> IO b
withOneFactorAffineModel = withStandalone . getCOneFactorAffineModel
data CPiecewiseTimeDependentHestonModel
newtype PiecewiseTimeDependentHestonModel = PiecewiseTimeDependentHestonModel {getCPiecewiseTimeDependentHestonModel :: Standalone CPiecewiseTimeDependentHestonModel}
metaPiecewiseTimeDependentHestonModel :: Meta CPiecewiseTimeDependentHestonModel
metaPiecewiseTimeDependentHestonModel = Meta qlFreePiecewiseTimeDependentHestonModel
peekPiecewiseTimeDependentHestonModel :: Ptr CPiecewiseTimeDependentHestonModel -> IO PiecewiseTimeDependentHestonModel
peekPiecewiseTimeDependentHestonModel = peekStandalone metaPiecewiseTimeDependentHestonModel >=> return . PiecewiseTimeDependentHestonModel
withPiecewiseTimeDependentHestonModel :: PiecewiseTimeDependentHestonModel -> (Ptr CPiecewiseTimeDependentHestonModel -> IO b) -> IO b
withPiecewiseTimeDependentHestonModel = withStandalone . getCPiecewiseTimeDependentHestonModel
data CShortRateModel
newtype ShortRateModel = ShortRateModel {getCShortRateModel :: Standalone CShortRateModel}
metaShortRateModel :: Meta CShortRateModel
metaShortRateModel = Meta qlFreeShortRateModel
peekShortRateModel :: Ptr CShortRateModel -> IO ShortRateModel
peekShortRateModel = peekStandalone metaShortRateModel >=> return . ShortRateModel
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

data CBatesProcess
newtype BatesProcess = BatesProcess {getCBatesProcess :: Standalone CBatesProcess}
metaBatesProcess :: Meta CBatesProcess
metaBatesProcess = Meta qlFreeBatesProcess
peekBatesProcess :: Ptr CBatesProcess -> IO BatesProcess
peekBatesProcess = peekStandalone metaBatesProcess >=> return . BatesProcess
withBatesProcess :: BatesProcess -> (Ptr CBatesProcess -> IO b) -> IO b
withBatesProcess = withStandalone . getCBatesProcess
data CBlackProcess
newtype BlackProcess = BlackProcess {getCBlackProcess :: Standalone CBlackProcess}
metaBlackProcess :: Meta CBlackProcess
metaBlackProcess = Meta qlFreeBlackProcess
peekBlackProcess :: Ptr CBlackProcess -> IO BlackProcess
peekBlackProcess = peekStandalone metaBlackProcess >=> return . BlackProcess
withBlackProcess :: BlackProcess -> (Ptr CBlackProcess -> IO b) -> IO b
withBlackProcess = withStandalone . getCBlackProcess
data CExtendedOrnsteinUhlenbeckProcess
newtype ExtendedOrnsteinUhlenbeckProcess = ExtendedOrnsteinUhlenbeckProcess {getCExtendedOrnsteinUhlenbeckProcess :: Standalone CExtendedOrnsteinUhlenbeckProcess}
metaExtendedOrnsteinUhlenbeckProcess :: Meta CExtendedOrnsteinUhlenbeckProcess
metaExtendedOrnsteinUhlenbeckProcess = Meta qlFreeExtendedOrnsteinUhlenbeckProcess
peekExtendedOrnsteinUhlenbeckProcess :: Ptr CExtendedOrnsteinUhlenbeckProcess -> IO ExtendedOrnsteinUhlenbeckProcess
peekExtendedOrnsteinUhlenbeckProcess = peekStandalone metaExtendedOrnsteinUhlenbeckProcess >=> return . ExtendedOrnsteinUhlenbeckProcess
withExtendedOrnsteinUhlenbeckProcess :: ExtendedOrnsteinUhlenbeckProcess -> (Ptr CExtendedOrnsteinUhlenbeckProcess -> IO b) -> IO b
withExtendedOrnsteinUhlenbeckProcess = withStandalone . getCExtendedOrnsteinUhlenbeckProcess
data CExtOUWithJumpsProcess
newtype ExtOUWithJumpsProcess = ExtOUWithJumpsProcess {getCExtOUWithJumpsProcess :: Standalone CExtOUWithJumpsProcess}
metaExtOUWithJumpsProcess :: Meta CExtOUWithJumpsProcess
metaExtOUWithJumpsProcess = Meta qlFreeExtOUWithJumpsProcess
peekExtOUWithJumpsProcess :: Ptr CExtOUWithJumpsProcess -> IO ExtOUWithJumpsProcess
peekExtOUWithJumpsProcess = peekStandalone metaExtOUWithJumpsProcess >=> return . ExtOUWithJumpsProcess
withExtOUWithJumpsProcess :: ExtOUWithJumpsProcess -> (Ptr CExtOUWithJumpsProcess -> IO b) -> IO b
withExtOUWithJumpsProcess = withStandalone . getCExtOUWithJumpsProcess
data CGeneralizedBlackScholesProcess
newtype GeneralizedBlackScholesProcess = GeneralizedBlackScholesProcess {getCGeneralizedBlackScholesProcess :: Standalone CGeneralizedBlackScholesProcess}
metaGeneralizedBlackScholesProcess :: Meta CGeneralizedBlackScholesProcess
metaGeneralizedBlackScholesProcess = Meta qlFreeGeneralizedBlackScholesProcess
peekGeneralizedBlackScholesProcess :: Ptr CGeneralizedBlackScholesProcess -> IO GeneralizedBlackScholesProcess
peekGeneralizedBlackScholesProcess = peekStandalone metaGeneralizedBlackScholesProcess >=> return . GeneralizedBlackScholesProcess
withGeneralizedBlackScholesProcess :: GeneralizedBlackScholesProcess -> (Ptr CGeneralizedBlackScholesProcess -> IO b) -> IO b
withGeneralizedBlackScholesProcess = withStandalone . getCGeneralizedBlackScholesProcess
data CGJRGARCHProcess
newtype GJRGARCHProcess = GJRGARCHProcess {getCGJRGARCHProcess :: Standalone CGJRGARCHProcess}
metaGJRGARCHProcess :: Meta CGJRGARCHProcess
metaGJRGARCHProcess = Meta qlFreeGJRGARCHProcess
peekGJRGARCHProcess :: Ptr CGJRGARCHProcess -> IO GJRGARCHProcess
peekGJRGARCHProcess = peekStandalone metaGJRGARCHProcess >=> return . GJRGARCHProcess
withGJRGARCHProcess :: GJRGARCHProcess -> (Ptr CGJRGARCHProcess -> IO b) -> IO b
withGJRGARCHProcess = withStandalone . getCGJRGARCHProcess
data CHestonProcess
newtype HestonProcess = HestonProcess {getCHestonProcess :: Standalone CHestonProcess}
metaHestonProcess :: Meta CHestonProcess
metaHestonProcess = Meta qlFreeHestonProcess
peekHestonProcess :: Ptr CHestonProcess -> IO HestonProcess
peekHestonProcess = peekStandalone metaHestonProcess >=> return . HestonProcess
withHestonProcess :: HestonProcess -> (Ptr CHestonProcess -> IO b) -> IO b
withHestonProcess = withStandalone . getCHestonProcess
data CHullWhiteForwardProcess
newtype HullWhiteForwardProcess = HullWhiteForwardProcess {getCHullWhiteForwardProcess :: Standalone CHullWhiteForwardProcess}
metaHullWhiteForwardProcess :: Meta CHullWhiteForwardProcess
metaHullWhiteForwardProcess = Meta qlFreeHullWhiteForwardProcess
peekHullWhiteForwardProcess :: Ptr CHullWhiteForwardProcess -> IO HullWhiteForwardProcess
peekHullWhiteForwardProcess = peekStandalone metaHullWhiteForwardProcess >=> return . HullWhiteForwardProcess
withHullWhiteForwardProcess :: HullWhiteForwardProcess -> (Ptr CHullWhiteForwardProcess -> IO b) -> IO b
withHullWhiteForwardProcess = withStandalone . getCHullWhiteForwardProcess
data CHullWhiteProcess
newtype HullWhiteProcess = HullWhiteProcess {getCHullWhiteProcess :: Standalone CHullWhiteProcess}
metaHullWhiteProcess :: Meta CHullWhiteProcess
metaHullWhiteProcess = Meta qlFreeHullWhiteProcess
peekHullWhiteProcess :: Ptr CHullWhiteProcess -> IO HullWhiteProcess
peekHullWhiteProcess = peekStandalone metaHullWhiteProcess >=> return . HullWhiteProcess
withHullWhiteProcess :: HullWhiteProcess -> (Ptr CHullWhiteProcess -> IO b) -> IO b
withHullWhiteProcess = withStandalone . getCHullWhiteProcess
data CHybridHestonHullWhiteProcess
newtype HybridHestonHullWhiteProcess = HybridHestonHullWhiteProcess {getCHybridHestonHullWhiteProcess :: Standalone CHybridHestonHullWhiteProcess}
metaHybridHestonHullWhiteProcess :: Meta CHybridHestonHullWhiteProcess
metaHybridHestonHullWhiteProcess = Meta qlFreeHybridHestonHullWhiteProcess
peekHybridHestonHullWhiteProcess :: Ptr CHybridHestonHullWhiteProcess -> IO HybridHestonHullWhiteProcess
peekHybridHestonHullWhiteProcess = peekStandalone metaHybridHestonHullWhiteProcess >=> return . HybridHestonHullWhiteProcess
withHybridHestonHullWhiteProcess :: HybridHestonHullWhiteProcess -> (Ptr CHybridHestonHullWhiteProcess -> IO b) -> IO b
withHybridHestonHullWhiteProcess = withStandalone . getCHybridHestonHullWhiteProcess
data CKlugeExtOUProcess
newtype KlugeExtOUProcess = KlugeExtOUProcess {getCKlugeExtOUProcess :: Standalone CKlugeExtOUProcess}
metaKlugeExtOUProcess :: Meta CKlugeExtOUProcess
metaKlugeExtOUProcess = Meta qlFreeKlugeExtOUProcess
peekKlugeExtOUProcess :: Ptr CKlugeExtOUProcess -> IO KlugeExtOUProcess
peekKlugeExtOUProcess = peekStandalone metaKlugeExtOUProcess >=> return . KlugeExtOUProcess
withKlugeExtOUProcess :: KlugeExtOUProcess -> (Ptr CKlugeExtOUProcess -> IO b) -> IO b
withKlugeExtOUProcess = withStandalone . getCKlugeExtOUProcess
data CLiborForwardModelProcess
newtype LiborForwardModelProcess = LiborForwardModelProcess {getCLiborForwardModelProcess :: Standalone CLiborForwardModelProcess}
metaLiborForwardModelProcess :: Meta CLiborForwardModelProcess
metaLiborForwardModelProcess = Meta qlFreeLiborForwardModelProcess
peekLiborForwardModelProcess :: Ptr CLiborForwardModelProcess -> IO LiborForwardModelProcess
peekLiborForwardModelProcess = peekStandalone metaLiborForwardModelProcess >=> return . LiborForwardModelProcess
withLiborForwardModelProcess :: LiborForwardModelProcess -> (Ptr CLiborForwardModelProcess -> IO b) -> IO b
withLiborForwardModelProcess = withStandalone . getCLiborForwardModelProcess
data CMerton76Process
newtype Merton76Process = Merton76Process {getCMerton76Process :: Standalone CMerton76Process}
metaMerton76Process :: Meta CMerton76Process
metaMerton76Process = Meta qlFreeMerton76Process
peekMerton76Process :: Ptr CMerton76Process -> IO Merton76Process
peekMerton76Process = peekStandalone metaMerton76Process >=> return . Merton76Process
withMerton76Process :: Merton76Process -> (Ptr CMerton76Process -> IO b) -> IO b
withMerton76Process = withStandalone . getCMerton76Process
data CStochasticProcess1D
newtype StochasticProcess1D = StochasticProcess1D {getCStochasticProcess1D :: Standalone CStochasticProcess1D}
metaStochasticProcess1D :: Meta CStochasticProcess1D
metaStochasticProcess1D = Meta qlFreeStochasticProcess1D
peekStochasticProcess1D :: Ptr CStochasticProcess1D -> IO StochasticProcess1D
peekStochasticProcess1D = peekStandalone metaStochasticProcess1D >=> return . StochasticProcess1D
withStochasticProcess1D :: StochasticProcess1D -> (Ptr CStochasticProcess1D -> IO b) -> IO b
withStochasticProcess1D = withStandalone . getCStochasticProcess1D
data CStochasticProcessArray
newtype StochasticProcessArray = StochasticProcessArray {getCStochasticProcessArray :: Standalone CStochasticProcessArray}
metaStochasticProcessArray :: Meta CStochasticProcessArray
metaStochasticProcessArray = Meta qlFreeStochasticProcessArray
peekStochasticProcessArray :: Ptr CStochasticProcessArray -> IO StochasticProcessArray
peekStochasticProcessArray = peekStandalone metaStochasticProcessArray >=> return . StochasticProcessArray
withStochasticProcessArray :: StochasticProcessArray -> (Ptr CStochasticProcessArray -> IO b) -> IO b
withStochasticProcessArray = withStandalone . getCStochasticProcessArray
data CStochasticProcess
newtype StochasticProcess = StochasticProcess {getCStochasticProcess :: Standalone CStochasticProcess}
metaStochasticProcess :: Meta CStochasticProcess
metaStochasticProcess = Meta qlFreeStochasticProcess
peekStochasticProcess :: Ptr CStochasticProcess -> IO StochasticProcess
peekStochasticProcess = peekStandalone metaStochasticProcess >=> return . StochasticProcess
withStochasticProcess :: StochasticProcess -> (Ptr CStochasticProcess -> IO b) -> IO b
withStochasticProcess = withStandalone . getCStochasticProcess
data CVarianceGammaProcess
newtype VarianceGammaProcess = VarianceGammaProcess {getCVarianceGammaProcess :: Standalone CVarianceGammaProcess}
metaVarianceGammaProcess :: Meta CVarianceGammaProcess
metaVarianceGammaProcess = Meta qlFreeVarianceGammaProcess
peekVarianceGammaProcess :: Ptr CVarianceGammaProcess -> IO VarianceGammaProcess
peekVarianceGammaProcess = peekStandalone metaVarianceGammaProcess >=> return . VarianceGammaProcess
withVarianceGammaProcess :: VarianceGammaProcess -> (Ptr CVarianceGammaProcess -> IO b) -> IO b
withVarianceGammaProcess = withStandalone . getCVarianceGammaProcess
withStochasticProcess1DArray :: [StochasticProcess1D] -> ((CUInt, Ptr (Ptr CStochasticProcess1D)) -> IO b) -> IO b
withStochasticProcess1DArray = withStandaloneArray getCStochasticProcess1D
foreign import ccall "ql.h &qlFreeBatesProcess" qlFreeBatesProcess :: FinalizerPtr CBatesProcess
foreign import ccall "ql.h &qlFreeBlackProcess" qlFreeBlackProcess :: FinalizerPtr CBlackProcess
foreign import ccall "ql.h &qlFreeExtendedOrnsteinUhlenbeckProcess" qlFreeExtendedOrnsteinUhlenbeckProcess :: FinalizerPtr CExtendedOrnsteinUhlenbeckProcess
foreign import ccall "ql.h &qlFreeExtOUWithJumpsProcess" qlFreeExtOUWithJumpsProcess :: FinalizerPtr CExtOUWithJumpsProcess
foreign import ccall "ql.h &qlFreeGeneralizedBlackScholesProcess" qlFreeGeneralizedBlackScholesProcess :: FinalizerPtr CGeneralizedBlackScholesProcess
foreign import ccall "ql.h &qlFreeGJRGARCHProcess" qlFreeGJRGARCHProcess :: FinalizerPtr CGJRGARCHProcess
foreign import ccall "ql.h &qlFreeHestonProcess" qlFreeHestonProcess :: FinalizerPtr CHestonProcess
foreign import ccall "ql.h &qlFreeHullWhiteForwardProcess" qlFreeHullWhiteForwardProcess :: FinalizerPtr CHullWhiteForwardProcess
foreign import ccall "ql.h &qlFreeHullWhiteProcess" qlFreeHullWhiteProcess :: FinalizerPtr CHullWhiteProcess
foreign import ccall "ql.h &qlFreeHybridHestonHullWhiteProcess" qlFreeHybridHestonHullWhiteProcess :: FinalizerPtr CHybridHestonHullWhiteProcess
foreign import ccall "ql.h &qlFreeKlugeExtOUProcess" qlFreeKlugeExtOUProcess :: FinalizerPtr CKlugeExtOUProcess
foreign import ccall "ql.h &qlFreeMerton76Process" qlFreeMerton76Process :: FinalizerPtr CMerton76Process
foreign import ccall "ql.h &qlFreeLiborForwardModelProcess" qlFreeLiborForwardModelProcess :: FinalizerPtr CLiborForwardModelProcess
foreign import ccall "ql.h &qlFreePiecewiseTimeDependentHestonModel" qlFreePiecewiseTimeDependentHestonModel :: FinalizerPtr CPiecewiseTimeDependentHestonModel
foreign import ccall "ql.h &qlFreeStochasticProcess1D" qlFreeStochasticProcess1D :: FinalizerPtr CStochasticProcess1D
foreign import ccall "ql.h &qlFreeStochasticProcessArray" qlFreeStochasticProcessArray :: FinalizerPtr CStochasticProcessArray
foreign import ccall "ql.h &qlFreeStochasticProcess" qlFreeStochasticProcess :: FinalizerPtr CStochasticProcess
foreign import ccall "ql.h &qlFreeVarianceGammaProcess" qlFreeVarianceGammaProcess :: FinalizerPtr CVarianceGammaProcess

--- TEMPLATE CODE

-- data CNode0'
-- data CLeaf1'
-- data CNode1'
-- data CLeaf2'
-- data CNode2'
-- data CLeaf3'
-- newtype GenNode0 a = GenNode0 (GenForeignPtr a CNode0')
-- type CNode0 = ForeignPtr CNode0'
-- type Node0 = GenNode0 CNode0
-- newtype Node1Descendant a = Node1Descendant (GenForeignPtr a CNode1')
-- type GenNode1 a = GenNode0 (Node1Descendant a)
-- type CNode1 = ForeignPtr CNode1'
-- type Node1 = GenNode1 CNode1
-- type CLeaf2 = ForeignPtr CLeaf2'
-- type Leaf2 = GenNode1 CLeaf2
-- newtype Node2Descendant a = Node2Descendant (GenForeignPtr a CNode2')
-- type GenNode2 a = GenNode0 (Node1Descendant (Node2Descendant a))
-- type CNode2 = ForeignPtr CNode2'
-- type Node2 = GenNode2 CNode2
-- type CLeaf3 = ForeignPtr CLeaf3'
-- type Leaf3 = GenNode2 CLeaf3
-- type CLeaf1 = ForeignPtr CLeaf1'
-- type Leaf1 = GenNode0 CLeaf1
-- foreign import ccall "ql.h &qlFreeNode0" qlFreeNode0 :: FinalizerPtr CNode0'
-- foreign import ccall "ql.h &qlFreeNode1" qlFreeNode1 :: FinalizerPtr CNode1'
-- foreign import ccall "ql.h &qlFreeLeaf2" qlFreeLeaf2 :: FinalizerPtr CLeaf2'
-- foreign import ccall "ql.h &qlFreeNode2" qlFreeNode2 :: FinalizerPtr CNode2'
-- foreign import ccall "ql.h &qlFreeLeaf3" qlFreeLeaf3 :: FinalizerPtr CLeaf3'
-- foreign import ccall "ql.h &qlFreeLeaf1" qlFreeLeaf1 :: FinalizerPtr CLeaf1'
-- metaNode0 :: Meta CNode0'
-- metaNode0 = Meta qlFreeNode0
-- metaNode1 :: Meta CNode1'
-- metaNode1 = Meta qlFreeNode1
-- metaLeaf2 :: Meta CLeaf2'
-- metaLeaf2 = Meta qlFreeLeaf2
-- metaNode2 :: Meta CNode2'
-- metaNode2 = Meta qlFreeNode2
-- metaLeaf3 :: Meta CLeaf3'
-- metaLeaf3 = Meta qlFreeLeaf3
-- metaLeaf1 :: Meta CLeaf1'
-- metaLeaf1 = Meta qlFreeLeaf1
-- foreign import ccall "ql.h qlNode1AsNode0" qlNode1AsNode0 :: Ptr CNode1' -> IO (Ptr CNode0')
-- foreign import ccall "ql.h qlLeaf2AsNode1" qlLeaf2AsNode1 :: Ptr CLeaf2' -> IO (Ptr CNode1')
-- foreign import ccall "ql.h qlNode2AsNode1" qlNode2AsNode1 :: Ptr CNode2' -> IO (Ptr CNode1')
-- foreign import ccall "ql.h qlLeaf3AsNode2" qlLeaf3AsNode2 :: Ptr CLeaf3' -> IO (Ptr CNode2')
-- foreign import ccall "ql.h qlLeaf1AsNode0" qlLeaf1AsNode0 :: Ptr CLeaf1' -> IO (Ptr CNode0')
-- upcastNode1 :: Upcast CNode1' CNode0'
-- upcastNode1 = Upcast qlNode1AsNode0 qlFreeNode0
-- upcastLeaf2 :: Upcast CLeaf2' CNode1'
-- upcastLeaf2 = Upcast qlLeaf2AsNode1 qlFreeNode1
-- upcastNode2 :: Upcast CNode2' CNode1'
-- upcastNode2 = Upcast qlNode2AsNode1 qlFreeNode1
-- upcastLeaf3 :: Upcast CLeaf3' CNode2'
-- upcastLeaf3 = Upcast qlLeaf3AsNode2 qlFreeNode2
-- upcastLeaf1 :: Upcast CLeaf1' CNode0'
-- upcastLeaf1 = Upcast qlLeaf1AsNode0 qlFreeNode0
-- 
-- asNode0 :: GenNode0 a -> IO Node0
-- asNode0 (GenNode0 (GenForeignPtr x w)) = w x peekNode0
-- peekNode0 :: Ptr CNode0' -> IO Node0
-- peekNode0 = GenNode0 <.> newCastForeignPtr metaNode0
-- withNode0 :: GenNode0 a -> (Ptr CNode0' -> IO b) -> IO b
-- withNode0 (GenNode0 (GenForeignPtr x w)) = w x
-- withNode0Descendant :: GenNode0 (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
-- withNode0Descendant (GenNode0 (GenForeignPtr x _)) = withForeignPtr x
-- 
-- asNode1 :: GenNode1 a -> IO Node1
-- asNode1 (GenNode0 (GenForeignPtr (Node1Descendant (GenForeignPtr x w)) _)) = w x peekNode1
-- peekNode1 :: Ptr CNode1' -> IO Node1
-- peekNode1 = newCastForeignPtr metaNode1 >=> newNode1Descendant
-- withNode1 :: GenNode1 a -> (Ptr CNode1' -> IO b) -> IO b
-- withNode1 (GenNode0 (GenForeignPtr (Node1Descendant (GenForeignPtr x w)) _)) = w x
-- withMaybeNode1 :: Maybe (GenNode1 a) -> (Ptr CNode1' -> IO b) -> IO b
-- withMaybeNode1 x f = maybe (f nullPtr) (`withNode1` f) x
-- withGenForeignUpcastNode1 :: Node1Descendant a -> (Ptr CNode0' -> IO b) -> IO b
-- withGenForeignUpcastNode1 (Node1Descendant o) = withGenForeignPtr upcastNode1 o
-- newNode1Descendant :: GenForeignPtr a CNode1' -> IO (GenNode1 a)
-- newNode1Descendant p = GenNode0 <^> GenForeignPtr (Node1Descendant p) withGenForeignUpcastNode1
-- peekNode1Descendant :: Meta a -> Upcast a CNode1' -> Ptr a -> IO (GenNode1 (ForeignPtr a))
-- peekNode1Descendant m u = newGenForeignPtr m u >=> newNode1Descendant
-- withNode1Descendant :: GenNode1 (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
-- withNode1Descendant (GenNode0 (GenForeignPtr (Node1Descendant (GenForeignPtr x _)) _)) = withForeignPtr x
-- 
-- asNode2 :: GenNode2 a -> IO Node2
-- asNode2 (GenNode0 (GenForeignPtr (Node1Descendant (GenForeignPtr (Node2Descendant (GenForeignPtr x w)) _)) _)) = w x peekNode2
-- peekNode2 :: Ptr CNode2' -> IO Node2
-- peekNode2 = newCastForeignPtr metaNode2 >=> newNode2Descendant
-- withNode2 :: GenNode2 a -> (Ptr CNode2' -> IO b) -> IO b
-- withNode2 (GenNode0 (GenForeignPtr (Node1Descendant (GenForeignPtr (Node2Descendant (GenForeignPtr x w)) _)) _)) = w x
-- withGenForeignUpcastNode2 :: Node2Descendant a -> (Ptr CNode1' -> IO b) -> IO b
-- withGenForeignUpcastNode2 (Node2Descendant o) = withGenForeignPtr upcastNode2 o
-- newNode2Descendant :: GenForeignPtr a CNode2' -> IO (GenNode2 a)
-- newNode2Descendant p = GenNode0 <^> GenForeignPtr (Node1Descendant $ GenForeignPtr (Node2Descendant p) withGenForeignUpcastNode2) withGenForeignUpcastNode1
-- 
-- peekLeaf1 :: Ptr CLeaf1' -> IO Leaf1
-- peekLeaf1 = GenNode0 <.> newGenForeignPtr metaLeaf1 upcastLeaf1
-- 
-- peekLeaf2 :: Ptr CLeaf2' -> IO Leaf2
-- peekLeaf2 = peekNode1Descendant metaLeaf2 upcastLeaf2
-- withLeaf2 :: Leaf2 -> (Ptr CLeaf2' -> IO b) -> IO b
-- withLeaf2 (GenNode0 (GenForeignPtr (Node1Descendant (GenForeignPtr x _)) _)) = withForeignPtr x
-- 
-- peekLeaf3 :: Ptr CLeaf3' -> IO Leaf3
-- peekLeaf3 = newGenForeignPtr metaLeaf3 upcastLeaf3 >=> newNode2Descendant
-- withLeaf3 :: Leaf3 -> (Ptr CLeaf3' -> IO b) -> IO b
-- withLeaf3 (GenNode0 (GenForeignPtr (Node1Descendant (GenForeignPtr (Node2Descendant (GenForeignPtr x _)) _)) _)) = withForeignPtr x

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
