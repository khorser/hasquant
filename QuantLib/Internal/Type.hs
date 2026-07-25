{-# LANGUAGE RankNTypes, TypeFamilies, TypeOperators, FlexibleContexts, FlexibleInstances #-}
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
  , withGenBond
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
  , HasAffineModel(..)
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
  , CAssetSwap'
  , peekAssetSwap
  , withAssetSwap
  , BarrierOption
  , CBarrierOption
  , CBarrierOption'
  , peekBarrierOption
  , withBarrierOption
  , BMASwap
  , CBMASwap
  , CBMASwap'
  , peekBMASwap
  , withBMASwap
  , Bond
  , GenBond
  , CBond
  , CBond'
  , asBond
  , peekBond
  , withBond
  , CallableBond
  , CCallableBond
  , CCallableBond'
  , peekCallableBond
  , withCallableBond
  , CapFloor
  , CCapFloor
  , CCapFloor'
  , peekCapFloor
  , CdsOption
  , CCdsOption
  , CCdsOption'
  , peekCdsOption
  , withCdsOption
  , ConvertibleBond
  , CConvertibleBond
  , CConvertibleBond'
  , peekConvertibleBond
  , withConvertibleBond
  , CreditDefaultSwap
  , CCreditDefaultSwap
  , CCreditDefaultSwap'
  , peekCreditDefaultSwap
  , FixedRateBond
  , CFixedRateBond
  , CFixedRateBond'
  , peekFixedRateBond
  , withFixedRateBond
  , BondForward
  , CBondForward
  , CBondForward'
  , peekBondForward
  , withBondForward
  , Forward
  , CForward
  , GenForward
  , CForward'
  , asForward
  , peekForward
  , withForward
  , withGenForward
  , ForwardRateAgreement
  , CForwardRateAgreement
  , CForwardRateAgreement'
  , peekForwardRateAgreement
  , ForwardVanillaOption
  , CForwardVanillaOption
  , CForwardVanillaOption'
  , peekForwardVanillaOption
  , withForwardVanillaOption
  , Instrument
  , GenInstrument
  , CInstrument
  , CInstrument'
  , asInstrument
  , peekInstrument
  , withInstrument
  , withInstrumentArray
  , withGenInstrument
  , Option
  , GenOption
  , COption
  , COption'
  , asOption
  , withGenOption
  , peekOption
  , withOption
  , OvernightIndexedSwap
  , COvernightIndexedSwap
  , COvernightIndexedSwap'
  , peekOvernightIndexedSwap
  , withOvernightIndexedSwap
  , QuantoBarrierOption
  , CQuantoBarrierOption
  , CQuantoBarrierOption'
  , peekQuantoBarrierOption
  , withQuantoBarrierOption
  , QuantoForwardVanillaOption
  , CQuantoForwardVanillaOption
  , CQuantoForwardVanillaOption'
  , peekQuantoForwardVanillaOption
  , withQuantoForwardVanillaOption
  , QuantoVanillaOption
  , CQuantoVanillaOption'
  , peekQuantoVanillaOption
  , withQuantoVanillaOption
  , Swap
  , CSwap
  , GenSwap
  , CSwap'
  , asSwap
  , withGenSwap
  , peekSwap
  , withSwap
  , Swaption
  , CSwaption
  , CSwaption'
  , peekSwaption
  , withSwaption
  , VanillaOption
  , CVanillaOption
  , CVanillaOption'
  , peekVanillaOption
  , withVanillaOption
  , VanillaSwap
  , CVanillaSwap
  , CVanillaSwap'
  , peekVanillaSwap
  , withVanillaSwap
  , MargrabeOption
  , CMargrabeOption
  , CMargrabeOption'
  , peekMargrabeOption
  , withMargrabeOption
  , MultiAssetOption
  , GenMultiAssetOption
  , CMultiAssetOption
  , CMultiAssetOption'
  , asMultiAssetOption
  , peekMultiAssetOption
  , withMultiAssetOption
  , OneAssetOption
  , GenOneAssetOption
  , COneAssetOption
  , COneAssetOption'
  , asOneAssetOption
  , peekOneAssetOption
  , withOneAssetOption
  ) where
import Foreign.Ptr(Ptr, nullPtr)
import Foreign.ForeignPtr(ForeignPtr, FinalizerPtr, newForeignPtr, withForeignPtr)
import Foreign.C.Types(CUInt)
import Foreign.C.String(CString)
import Foreign.Marshal.Array(withArray)
import Foreign.Marshal.Utils(withMany)

import Control.Monad((>=>))
import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Internal(peekDynString)
import Control.Exception (finally)

(<.>) :: Functor f => (b -> r) -> (a -> f b) -> a -> f r
f1 <.> f2 = fmap f1 . f2

-- STANDALONE TYPES
newtype Standalone a = Standalone (ForeignPtr a)
foreign import ccall "dynamic" callFinalizer :: FinalizerPtr a -> Ptr a -> IO ()
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

-- TODO double check feasibility of `unsafe' if Haskell callbacks are added later
data CCalendar
newtype Calendar = Calendar {getCCalendar :: Standalone CCalendar}
instance Finalizable CCalendar where finalize = qlFreeCalendar
foreign import ccall unsafe "ql.h &qlFreeCalendar" qlFreeCalendar :: FinalizerPtr CCalendar
peekCalendar :: Ptr CCalendar -> IO Calendar
peekCalendar = Calendar <.> peekStandalone
withCalendar :: Calendar -> (Ptr CCalendar -> IO b) -> IO b
withCalendar = withStandalone . getCCalendar
foreign import ccall safe "ql.h qlCalendarName" qlCalendarName :: Ptr CCalendar -> IO CString
instance Show Calendar where show x = showStandalone qlCalendarName (getCCalendar x)
instance Eq Calendar where x == y = show x == show y

data CCurrency
newtype Currency = Currency {getCCurrency :: Standalone CCurrency}
foreign import ccall unsafe "ql.h &qlFreeCurrency" qlFreeCurrency :: FinalizerPtr CCurrency
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
foreign import ccall unsafe "ql.h &qlFreeDayCounter" qlFreeDayCounter :: FinalizerPtr CDayCounter
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
foreign import ccall unsafe "ql.h &qlFreeSchedule" qlFreeSchedule :: FinalizerPtr CSchedule
instance Finalizable CSchedule where finalize = qlFreeSchedule
peekSchedule :: Ptr CSchedule -> IO Schedule
peekSchedule = Schedule <.> peekStandalone
withSchedule :: Schedule -> (Ptr CSchedule -> IO b) -> IO b
withSchedule = withStandalone . getCSchedule

data CInterestRate
newtype InterestRate = InterestRate {getCInterestRate :: Standalone CInterestRate}
foreign import ccall unsafe "ql.h &qlFreeInterestRate" qlFreeInterestRate :: FinalizerPtr CInterestRate
instance Finalizable CInterestRate where finalize = qlFreeInterestRate
peekInterestRate :: Ptr CInterestRate -> IO InterestRate
peekInterestRate = InterestRate <.> peekStandalone
withInterestRate :: InterestRate -> (Ptr CInterestRate -> IO b) -> IO b
withInterestRate = withStandalone . getCInterestRate
withInterestRateArray :: [InterestRate] -> ((CUInt, Ptr (Ptr CInterestRate)) -> IO b) -> IO b
withInterestRateArray = withStandaloneArray getCInterestRate

data CTimeGrid
newtype TimeGrid = TimeGrid {getCTimeGrid :: Standalone CTimeGrid}
foreign import ccall unsafe "ql.h &qlFreeTimeGrid" qlFreeTimeGrid :: FinalizerPtr CTimeGrid
instance Finalizable CTimeGrid where finalize = qlFreeTimeGrid
peekTimeGrid :: Ptr CTimeGrid -> IO TimeGrid
peekTimeGrid = TimeGrid <.> peekStandalone
withTimeGrid :: TimeGrid -> (Ptr CTimeGrid -> IO b) -> IO b
withTimeGrid = withStandalone . getCTimeGrid

data CDividend
newtype Dividend = Dividend {getCDividend :: Standalone CDividend}
foreign import ccall unsafe "ql.h &qlFreeDividend" qlFreeDividend :: FinalizerPtr CDividend
instance Finalizable CDividend where finalize = qlFreeDividend
peekDividend :: Ptr CDividend -> IO Dividend
peekDividend = Dividend <.> peekStandalone
withDividend :: Dividend -> (Ptr CDividend -> IO b) -> IO b
withDividend = withStandalone . getCDividend
withDividendArray :: [Dividend] -> ((CUInt, Ptr (Ptr CDividend)) -> IO b) -> IO b
withDividendArray = withStandaloneArray getCDividend

data CSmileSection
newtype SmileSection = SmileSection {getCSmileSection :: Standalone CSmileSection}
foreign import ccall unsafe "ql.h &qlFreeSmileSection" qlFreeSmileSection :: FinalizerPtr CSmileSection
instance Finalizable CSmileSection where finalize = qlFreeSmileSection
peekSmileSection :: Ptr CSmileSection -> IO SmileSection
peekSmileSection = SmileSection <.> peekStandalone
withSmileSection :: SmileSection -> (Ptr CSmileSection -> IO b) -> IO b
withSmileSection = withStandalone . getCSmileSection

data CPricingEngine
newtype PricingEngine = PricingEngine {getCPricingEngine :: Standalone CPricingEngine}
foreign import ccall unsafe "ql.h &qlFreePricingEngine" qlFreePricingEngine :: FinalizerPtr CPricingEngine
instance Finalizable CPricingEngine where finalize = qlFreePricingEngine
peekPricingEngine :: Ptr CPricingEngine -> IO PricingEngine
peekPricingEngine = PricingEngine <.> peekStandalone
withPricingEngine :: PricingEngine -> (Ptr CPricingEngine -> IO b) -> IO b
withPricingEngine = withStandalone . getCPricingEngine

data CFloatingRateCouponPricer
newtype FloatingRateCouponPricer = FloatingRateCouponPricer {getCFloatingRateCouponPricer :: Standalone CFloatingRateCouponPricer}
foreign import ccall unsafe "ql.h &qlFreeFloatingCouponPricer" qlFreeFloatingRateCouponPricer :: FinalizerPtr CFloatingRateCouponPricer
instance Finalizable CFloatingRateCouponPricer where finalize = qlFreeFloatingRateCouponPricer
peekFloatingRateCouponPricer :: Ptr CFloatingRateCouponPricer -> IO FloatingRateCouponPricer
peekFloatingRateCouponPricer = FloatingRateCouponPricer <.> peekStandalone
withFloatingRateCouponPricer :: FloatingRateCouponPricer -> (Ptr CFloatingRateCouponPricer -> IO b) -> IO b
withFloatingRateCouponPricer = withStandalone . getCFloatingRateCouponPricer
withFloatingRateCouponPricerArray :: [FloatingRateCouponPricer] -> ((CUInt, Ptr (Ptr CFloatingRateCouponPricer)) -> IO b) -> IO b
withFloatingRateCouponPricerArray = withStandaloneArray getCFloatingRateCouponPricer

data CDefaultProbabilityHelper
newtype DefaultProbabilityHelper = DefaultProbabilityHelper {getCDefaultProbabilityHelper :: Standalone CDefaultProbabilityHelper}
foreign import ccall unsafe "ql.h &qlFreeDefaultProbabilityHelper" qlFreeDefaultProbabilityHelper :: FinalizerPtr CDefaultProbabilityHelper
instance Finalizable CDefaultProbabilityHelper where finalize = qlFreeDefaultProbabilityHelper
peekDefaultProbabilityHelper :: Ptr CDefaultProbabilityHelper -> IO DefaultProbabilityHelper
peekDefaultProbabilityHelper = DefaultProbabilityHelper <.> peekStandalone
withDefaultProbabilityHelper :: DefaultProbabilityHelper -> (Ptr CDefaultProbabilityHelper -> IO b) -> IO b
withDefaultProbabilityHelper = withStandalone . getCDefaultProbabilityHelper
withDefaultProbabilityHelperArray :: [DefaultProbabilityHelper] -> ((CUInt, Ptr (Ptr CDefaultProbabilityHelper)) -> IO b) -> IO b
withDefaultProbabilityHelperArray = withStandaloneArray getCDefaultProbabilityHelper

data CPathGenerator
newtype PathGenerator = PathGenerator {getCPathGenerator :: Standalone CPathGenerator}
foreign import ccall unsafe "ql.h &qlFreePathGenerator" qlFreePathGenerator :: FinalizerPtr CPathGenerator
instance Finalizable CPathGenerator where finalize = qlFreePathGenerator
peekPathGenerator :: Ptr CPathGenerator -> IO PathGenerator
peekPathGenerator = PathGenerator <.> peekStandalone
withPathGenerator :: PathGenerator -> (Ptr CPathGenerator -> IO b) -> IO b
withPathGenerator = withStandalone . getCPathGenerator

data CSamplePath
newtype SamplePath = SamplePath {getCSamplePath :: Standalone CSamplePath}
foreign import ccall unsafe "ql.h &qlFreeSamplePath" qlFreeSamplePath :: FinalizerPtr CSamplePath
instance Finalizable CSamplePath where finalize = qlFreeSamplePath
peekSamplePath :: Ptr CSamplePath -> IO SamplePath
peekSamplePath = SamplePath <.> peekStandalone
withSamplePath :: SamplePath -> (Ptr CSamplePath -> IO b) -> IO b
withSamplePath = withStandalone . getCSamplePath

-- special cases: those types will be represented as enums so no need to wrap them
data CQlClaim
type QlClaim = Standalone CQlClaim
foreign import ccall unsafe "ql.h &qlFreeClaim" qlFreeClaim :: FinalizerPtr CQlClaim
instance Finalizable CQlClaim where finalize = qlFreeClaim
peekClaim :: Ptr CQlClaim -> IO (Standalone CQlClaim)
peekClaim = peekStandalone

data CQlCallability
type QlCallability = Standalone CQlCallability
foreign import ccall unsafe "ql.h &qlFreeCallability" qlFreeCallability :: FinalizerPtr CQlCallability
instance Finalizable CQlCallability where finalize = qlFreeCallability
peekCallability :: Ptr CQlCallability -> IO (Standalone CQlCallability)
peekCallability = peekStandalone

data CConstraint
type QlConstraint = Standalone CConstraint
foreign import ccall unsafe "ql.h &qlFreeConstraint" qlFreeConstraint :: FinalizerPtr CConstraint
instance Finalizable CConstraint where finalize = qlFreeConstraint
peekConstraint :: Ptr CConstraint -> IO (Standalone CConstraint)
peekConstraint = peekStandalone

data CEndCriteria
type QlEndCriteria = Standalone CEndCriteria
foreign import ccall unsafe "ql.h &qlFreeEndCriteria" qlFreeEndCriteria :: FinalizerPtr CEndCriteria
instance Finalizable CEndCriteria where finalize = qlFreeEndCriteria
peekEndCriteria :: Ptr CEndCriteria -> IO (Standalone CEndCriteria)
peekEndCriteria = peekStandalone

data CFdmSchemeDesc
type QlFdmSchemeDesc = Standalone CFdmSchemeDesc
foreign import ccall unsafe "ql.h &qlFreeFdmSchemeDesc" qlFreeFdmSchemeDesc :: FinalizerPtr CFdmSchemeDesc
instance Finalizable CFdmSchemeDesc where finalize = qlFreeFdmSchemeDesc
peekFdmSchemeDesc :: Ptr CFdmSchemeDesc -> IO (Standalone CFdmSchemeDesc)
peekFdmSchemeDesc = peekStandalone

data CFittedBondDiscountCurveFittingMethod
type QlFittedBondDiscountCurveFittingMethod = Standalone CFittedBondDiscountCurveFittingMethod
foreign import ccall unsafe "ql.h &qlFreeFittedBondDiscountCurveFittingMethod" qlFreeFittedBondDiscountCurveFittingMethod :: FinalizerPtr CFittedBondDiscountCurveFittingMethod
instance Finalizable CFittedBondDiscountCurveFittingMethod where finalize = qlFreeFittedBondDiscountCurveFittingMethod
peekFittedBondDiscountCurveFittingMethod :: Ptr CFittedBondDiscountCurveFittingMethod -> IO (Standalone CFittedBondDiscountCurveFittingMethod)
peekFittedBondDiscountCurveFittingMethod = peekStandalone

data COptimizationMethod
type QlOptimizationMethod = Standalone COptimizationMethod
foreign import ccall unsafe "ql.h &qlFreeOptimizationMethod" qlFreeOptimizationMethod :: FinalizerPtr COptimizationMethod
instance Finalizable COptimizationMethod where finalize = qlFreeOptimizationMethod
peekOptimizationMethod :: Ptr COptimizationMethod -> IO (Standalone COptimizationMethod)
peekOptimizationMethod = peekStandalone

data CRounding
type QlRounding = Standalone CRounding
foreign import ccall unsafe "ql.h &qlFreeRounding" qlFreeRounding :: FinalizerPtr CRounding
instance Finalizable CRounding where finalize = qlFreeRounding
peekRounding :: Ptr CRounding -> IO (Standalone CRounding)
peekRounding = peekStandalone

data CLmCorrelationModel
type QlLmCorrelationModel = Standalone CLmCorrelationModel
foreign import ccall unsafe "ql.h &qlFreeLmCorrelationModel" qlFreeLmCorrelationModel :: FinalizerPtr CLmCorrelationModel
instance Finalizable CLmCorrelationModel where finalize = qlFreeLmCorrelationModel
peekLmCorrelationModel :: Ptr CLmCorrelationModel -> IO (Standalone CLmCorrelationModel)
peekLmCorrelationModel = peekStandalone

data CLmVolatilityModel
type QlLmVolatilityModel = Standalone CLmVolatilityModel
foreign import ccall unsafe "ql.h &qlFreeLmVolatilityModel" qlFreeLmVolatilityModel :: FinalizerPtr CLmVolatilityModel
instance Finalizable CLmVolatilityModel where finalize = qlFreeLmVolatilityModel
peekLmVolatilityModel :: Ptr CLmVolatilityModel -> IO (Standalone CLmVolatilityModel)
peekLmVolatilityModel = peekStandalone

-- TYPE HIERARCHIES
-- the original pointer to `a' with a way to marshal it to `b'
-- Actually we don't need the second field as we can infer the number of upcasts needed from the structure of the objects
data GenForeignPtr a b = GenForeignPtr {
  _ptr :: !a
  , _access :: !(forall r. a -> (Ptr b -> IO r) -> IO r)
  , _mayFree :: !(Maybe (Ptr b -> IO ())) -- `free' after upcast is needed
}

freeUpcast :: Finalizable b => Ptr b -> IO ()
freeUpcast = callFinalizer finalize

newtype AnyOf b a = AnyOf { getAnyOf :: GenForeignPtr a b }
newAnyOf :: (Upcastable b, Finalizable (Base b)) => GenForeignPtr a b -> GenForeignPtr (AnyOf b a) (Base b)
newAnyOf x = GenForeignPtr (AnyOf x)
  (\(AnyOf i) f -> withGenForeignPtr i (upcast >=> f))
  (Just freeUpcast)

class Upcastable a where
  type Base a
  upcast :: Ptr a -> IO (Ptr (Base a))

newGenForeignPtr :: (Finalizable a, Upcastable a, Finalizable (Base a)) => Ptr a -> IO (GenForeignPtr (ForeignPtr a) (Base a))
newGenForeignPtr x = do
  fp <- newForeignPtr finalize x
  pure $ GenForeignPtr fp (\a f -> withForeignPtr a (upcast >=> f)) (Just freeUpcast)

newCastForeignPtr :: Finalizable a => Ptr a -> IO (GenForeignPtr (ForeignPtr a) a)
newCastForeignPtr x = do
  fp <- newForeignPtr finalize x
  pure $ GenForeignPtr fp withForeignPtr Nothing

withGenForeignPtr :: GenForeignPtr a b -> (Ptr b -> IO r) -> IO r
withGenForeignPtr (GenForeignPtr p access mfree) f =
  access p $ \bp -> f bp `finally` maybe (pure ()) ($ bp) mfree

transferGenForeignPtr :: (Ptr b -> IO r) -> GenForeignPtr a b -> IO r
transferGenForeignPtr f (GenForeignPtr p access _) = access p f

withGenArray :: (a -> (Ptr c -> IO r) -> IO r) -> [a] -> ((CUInt, Ptr (Ptr c)) -> IO r) -> IO r
withGenArray m x f = withMany m x (`withArray` (\p -> f (fromIntegral $ length x, p)))

peel :: GenForeignPtr (AnyOf b a) c -> GenForeignPtr a b
peel = getAnyOf . _ptr

data CQuote'
data CSimpleQuote'
newtype GenQuote a = GenQuote {getQuote :: GenForeignPtr a CQuote'}
type CQuote = ForeignPtr CQuote'
type Quote = GenQuote CQuote
type CSimpleQuote = ForeignPtr CSimpleQuote'
type SimpleQuote = GenQuote CSimpleQuote
foreign import ccall unsafe "ql.h &qlFreeQuote" qlFreeQuote :: FinalizerPtr CQuote'
foreign import ccall unsafe "ql.h &qlFreeSimpleQuote" qlFreeSimpleQuote :: FinalizerPtr CSimpleQuote'
instance Finalizable CQuote' where finalize = qlFreeQuote
instance Finalizable CSimpleQuote' where finalize = qlFreeSimpleQuote
instance Upcastable CSimpleQuote' where {type Base CSimpleQuote' = CQuote'; upcast = qlSimpleQuoteAsQuote}
foreign import ccall "ql.h qlSimpleQuoteAsQuote" qlSimpleQuoteAsQuote :: Ptr CSimpleQuote' -> IO (Ptr CQuote')
-- Haskell does not allow function arguments like [forall a.GenQuote a]
-- let's at least provide a way to convert all quote classes to the most generic one
asQuote :: GenQuote a -> IO Quote
asQuote = transferGenForeignPtr peekQuote . getQuote
peekQuote :: Ptr CQuote' -> IO Quote
peekQuote = GenQuote <.> newCastForeignPtr
withQuote :: GenQuote a -> (Ptr CQuote' -> IO b) -> IO b
withQuote = withGenForeignPtr . getQuote
withGenQuote :: GenQuote (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenQuote = withForeignPtr . _ptr . getQuote
peekSimpleQuote :: Ptr CSimpleQuote' -> IO SimpleQuote
peekSimpleQuote = GenQuote <.> newGenForeignPtr
withMaybeQuote :: Maybe (GenQuote a) -> (Ptr CQuote' -> IO b) -> IO b
withMaybeQuote x f = maybe (f nullPtr) (`withQuote` f) x
withQuoteArray :: [GenQuote a] -> ((CUInt, Ptr (Ptr CQuote')) -> IO b) -> IO b
withQuoteArray = withGenArray withQuote
withQuoteArrayRaw :: [GenQuote a] -> (Ptr (Ptr CQuote') -> IO b) -> IO b
withQuoteArrayRaw x f = withMany withQuote x (`withArray` f)

data CLeg'
data CCouponLeg'
newtype GenLeg a = GenLeg {getLeg :: GenForeignPtr a CLeg'}
type CLeg = ForeignPtr CLeg'
type Leg = GenLeg CLeg
type CCouponLeg = ForeignPtr CCouponLeg'
type CouponLeg = GenLeg CCouponLeg
foreign import ccall unsafe "ql.h &qlFreeLeg" qlFreeLeg :: FinalizerPtr CLeg'
foreign import ccall unsafe "ql.h &qlFreeCouponLeg" qlFreeCouponLeg :: FinalizerPtr CCouponLeg'
instance Finalizable CLeg' where finalize = qlFreeLeg
instance Finalizable CCouponLeg' where finalize = qlFreeCouponLeg
foreign import ccall "ql.h qlCouponLegAsLeg" qlCouponLegAsLeg :: Ptr CCouponLeg' -> IO (Ptr CLeg')
instance Upcastable CCouponLeg' where {type Base CCouponLeg' = CLeg'; upcast = qlCouponLegAsLeg}
asLeg :: GenLeg a -> IO Leg
asLeg = transferGenForeignPtr peekLeg . getLeg
peekLeg :: Ptr CLeg' -> IO Leg
peekLeg = GenLeg <.> newCastForeignPtr
withLeg :: GenLeg a -> (Ptr CLeg' -> IO b) -> IO b
withLeg = withGenForeignPtr . getLeg
withLegArray :: [GenLeg a] -> ((CUInt, Ptr (Ptr CLeg')) -> IO b) -> IO b
withLegArray = withGenArray withLeg
withGenLeg :: GenLeg (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenLeg = withForeignPtr . _ptr . getLeg
peekCouponLeg :: Ptr CCouponLeg' -> IO CouponLeg
peekCouponLeg = GenLeg <.> newGenForeignPtr

data CRateHelper'
newtype GenRateHelper a = GenRateHelper {getRateHelper :: GenForeignPtr a CRateHelper'}
type CRateHelper = ForeignPtr CRateHelper'
type RateHelper = GenRateHelper CRateHelper
foreign import ccall unsafe "ql.h &qlFreeRateHelper" qlFreeRateHelper :: FinalizerPtr CRateHelper'
instance Finalizable CRateHelper' where finalize = qlFreeRateHelper
asRateHelper :: GenRateHelper a -> IO RateHelper
asRateHelper = transferGenForeignPtr peekRateHelper . getRateHelper
peekRateHelper :: Ptr CRateHelper' -> IO RateHelper
peekRateHelper = GenRateHelper <.> newCastForeignPtr
withRateHelper :: GenRateHelper a -> (Ptr CRateHelper' -> IO b) -> IO b
withRateHelper = withGenForeignPtr . getRateHelper
withGenRateHelper :: GenRateHelper (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenRateHelper = withForeignPtr . _ptr . getRateHelper
withRateHelperArray :: [GenRateHelper a] -> ((CUInt, Ptr (Ptr CRateHelper')) -> IO b) -> IO b
withRateHelperArray = withGenArray withRateHelper
data CBondHelper'
type CBondHelper = ForeignPtr CBondHelper'
type BondHelper = GenRateHelper CBondHelper
foreign import ccall unsafe "ql.h &qlFreeBondHelper" qlFreeBondHelper :: FinalizerPtr CBondHelper'
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
foreign import ccall unsafe "ql.h &qlFreeSwapRateHelper" qlFreeSwapRateHelper :: FinalizerPtr CSwapRateHelper'
instance Finalizable CSwapRateHelper' where finalize = qlFreeSwapRateHelper
foreign import ccall "ql.h qlSwapRateHelperAsRateHelper" qlSwapRateHelperAsRateHelper :: Ptr CSwapRateHelper' -> IO (Ptr CRateHelper')
instance Upcastable CSwapRateHelper' where {type Base CSwapRateHelper' = CRateHelper'; upcast = qlSwapRateHelperAsRateHelper}
peekSwapRateHelper :: Ptr CSwapRateHelper' -> IO SwapRateHelper
peekSwapRateHelper = GenRateHelper <.> newGenForeignPtr
data COISRateHelper'
type COISRateHelper = ForeignPtr COISRateHelper'
type OISRateHelper = GenRateHelper COISRateHelper
foreign import ccall unsafe "ql.h &qlFreeOISRateHelper" qlFreeOISRateHelper :: FinalizerPtr COISRateHelper'
instance Finalizable COISRateHelper' where finalize = qlFreeOISRateHelper
foreign import ccall "ql.h qlOISRateHelperAsRateHelper" qlOISRateHelperAsRateHelper :: Ptr COISRateHelper' -> IO (Ptr CRateHelper')
instance Upcastable COISRateHelper' where {type Base COISRateHelper' = CRateHelper'; upcast = qlOISRateHelperAsRateHelper}
peekOISRateHelper :: Ptr COISRateHelper' -> IO OISRateHelper
peekOISRateHelper = GenRateHelper <.> newGenForeignPtr

data CCalibrationHelper'
data CBlackCalibrationHelper'
newtype GenCalibrationHelper a = GenCalibrationHelper {getCalibrationHelper :: GenForeignPtr a CCalibrationHelper'}
type CCalibrationHelper = ForeignPtr CCalibrationHelper'
type CalibrationHelper = GenCalibrationHelper CCalibrationHelper
type CBlackCalibrationHelper = ForeignPtr CBlackCalibrationHelper'
type BlackCalibrationHelper = GenCalibrationHelper CBlackCalibrationHelper
foreign import ccall unsafe "ql.h &qlFreeCalibrationHelper" qlFreeCalibrationHelper :: FinalizerPtr CCalibrationHelper'
foreign import ccall unsafe "ql.h &qlFreeBlackCalibrationHelper" qlFreeBlackCalibrationHelper :: FinalizerPtr CBlackCalibrationHelper'
instance Finalizable CCalibrationHelper' where finalize = qlFreeCalibrationHelper
instance Finalizable CBlackCalibrationHelper' where finalize = qlFreeBlackCalibrationHelper
foreign import ccall "ql.h qlBlackCalibrationHelperAsCalibrationHelper" qlBlackCalibrationHelperAsCalibrationHelper :: Ptr CBlackCalibrationHelper' -> IO (Ptr CCalibrationHelper')
instance Upcastable CBlackCalibrationHelper' where {type Base CBlackCalibrationHelper' = CCalibrationHelper'; upcast = qlBlackCalibrationHelperAsCalibrationHelper}
asCalibrationHelper :: GenCalibrationHelper a -> IO CalibrationHelper
asCalibrationHelper = transferGenForeignPtr peekCalibrationHelper . getCalibrationHelper
peekCalibrationHelper :: Ptr CCalibrationHelper' -> IO CalibrationHelper
peekCalibrationHelper = GenCalibrationHelper <.> newCastForeignPtr
withCalibrationHelper :: GenCalibrationHelper a -> (Ptr CCalibrationHelper' -> IO b) -> IO b
withCalibrationHelper = withGenForeignPtr . getCalibrationHelper
withGenCalibrationHelper :: GenCalibrationHelper (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenCalibrationHelper = withForeignPtr . _ptr . getCalibrationHelper
peekBlackCalibrationHelper :: Ptr CBlackCalibrationHelper' -> IO BlackCalibrationHelper
peekBlackCalibrationHelper = GenCalibrationHelper <.> newGenForeignPtr
withCalibrationHelperArray :: [GenCalibrationHelper a] -> ((CUInt, Ptr (Ptr CCalibrationHelper')) -> IO b) -> IO b
withCalibrationHelperArray = withGenArray withCalibrationHelper

data CBlackCalculator'
data CBlackScholesCalculator'
newtype GenBlackCalculator a = GenBlackCalculator {getBlackCalculator :: GenForeignPtr a CBlackCalculator'}
type CBlackCalculator = ForeignPtr CBlackCalculator'
type BlackCalculator = GenBlackCalculator CBlackCalculator
type CBlackScholesCalculator = ForeignPtr CBlackScholesCalculator'
type BlackScholesCalculator = GenBlackCalculator CBlackScholesCalculator
foreign import ccall unsafe "ql.h &qlFreeBlackCalculator" qlFreeBlackCalculator :: FinalizerPtr CBlackCalculator'
foreign import ccall unsafe "ql.h &qlFreeBlackScholesCalculator" qlFreeBlackScholesCalculator :: FinalizerPtr CBlackScholesCalculator'
instance Finalizable CBlackCalculator' where finalize = qlFreeBlackCalculator
instance Finalizable CBlackScholesCalculator' where finalize = qlFreeBlackScholesCalculator
foreign import ccall "ql.h qlBlackScholesCalculatorAsBlackCalculator" qlBlackScholesCalculatorAsBlackCalculator :: Ptr CBlackScholesCalculator' -> IO (Ptr CBlackCalculator')
instance Upcastable CBlackScholesCalculator' where {type Base CBlackScholesCalculator' = CBlackCalculator'; upcast = qlBlackScholesCalculatorAsBlackCalculator}
asBlackCalculator :: GenBlackCalculator a -> IO BlackCalculator
asBlackCalculator = transferGenForeignPtr peekBlackCalculator . getBlackCalculator
peekBlackCalculator :: Ptr CBlackCalculator' -> IO BlackCalculator
peekBlackCalculator = GenBlackCalculator <.> newCastForeignPtr
withBlackCalculator :: GenBlackCalculator a -> (Ptr CBlackCalculator' -> IO b) -> IO b
withBlackCalculator = withGenForeignPtr . getBlackCalculator
withGenBlackCalculator :: GenBlackCalculator (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenBlackCalculator = withForeignPtr . _ptr . getBlackCalculator
peekBlackScholesCalculator :: Ptr CBlackScholesCalculator' -> IO BlackScholesCalculator
peekBlackScholesCalculator = GenBlackCalculator <.> newGenForeignPtr

-- MULTILEVEL HIERARCHIES
-- Index
--   InterestRateIndex
--     BMAIndex
--     IborIndex
--       OvernightIborIndex
--     SwapIndex
--       OvernightIndexedSwapIndex
data CIndex'
data CInterestRateIndex'
data CBMAIndex'
data CIborIndex'
data COvernightIndex'
data CSwapIndex'
data COvernightIndexedSwapIndex'
newtype GenIndex a = GenIndex {getIndex :: GenForeignPtr a CIndex'}
type CIndex = ForeignPtr CIndex'
type Index = GenIndex CIndex
type GenInterestRateIndex a = GenIndex (AnyOf CInterestRateIndex' a)
type CInterestRateIndex = ForeignPtr CInterestRateIndex'
type InterestRateIndex = GenInterestRateIndex CInterestRateIndex
type CBMAIndex = ForeignPtr CBMAIndex'
type BMAIndex = GenInterestRateIndex CBMAIndex
type CIborIndex = ForeignPtr CIborIndex'
type IborIndex = GenIborIndex CIborIndex
type COvernightIndex = ForeignPtr COvernightIndex'
type OvernightIborIndex = GenIborIndex COvernightIndex
type CSwapIndex = ForeignPtr CSwapIndex'
type SwapIndex = GenSwapIndex CSwapIndex
type GenIborIndex a = GenInterestRateIndex (AnyOf CIborIndex' a)
type GenSwapIndex a = GenInterestRateIndex (AnyOf CSwapIndex' a)
type COvernightIndexedSwapIndex = ForeignPtr COvernightIndexedSwapIndex'
type OvernightIndexedSwapIndex = GenSwapIndex COvernightIndexedSwapIndex
foreign import ccall unsafe "ql.h &qlFreeIndex" qlFreeIndex :: FinalizerPtr CIndex'
foreign import ccall unsafe "ql.h &qlFreeInterestRateIndex" qlFreeInterestRateIndex :: FinalizerPtr CInterestRateIndex'
foreign import ccall unsafe "ql.h &qlFreeBMAIndex" qlFreeBMAIndex :: FinalizerPtr CBMAIndex'
foreign import ccall unsafe "ql.h &qlFreeIborIndex" qlFreeIborIndex :: FinalizerPtr CIborIndex'
foreign import ccall unsafe "ql.h &qlFreeOvernightIndex" qlFreeOvernightIborIndex :: FinalizerPtr COvernightIndex'
foreign import ccall unsafe "ql.h &qlFreeSwapIndex" qlFreeSwapIndex :: FinalizerPtr CSwapIndex'
foreign import ccall unsafe "ql.h &qlFreeOvernightIndexedSwapIndex" qlFreeOvernightIndexedSwapIndex :: FinalizerPtr COvernightIndexedSwapIndex'
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
asIndex = transferGenForeignPtr peekIndex . getIndex
withIndex :: GenIndex a -> (Ptr CIndex' -> IO b) -> IO b
withIndex = withGenForeignPtr . getIndex
peekIndex :: Ptr CIndex' -> IO Index
peekIndex = GenIndex <.> newCastForeignPtr

asInterestRateIndex :: GenInterestRateIndex a -> IO InterestRateIndex
asInterestRateIndex = transferGenForeignPtr peekInterestRateIndex . peel . getIndex
peekInterestRateIndex :: Ptr CInterestRateIndex' -> IO InterestRateIndex
peekInterestRateIndex = newCastForeignPtr >=> newGenInterestRateIndex
newGenInterestRateIndex :: GenForeignPtr a CInterestRateIndex' -> IO (GenInterestRateIndex a)
newGenInterestRateIndex = pure . GenIndex . newAnyOf
withInterestRateIndex :: GenInterestRateIndex a -> (Ptr CInterestRateIndex' -> IO b) -> IO b
withInterestRateIndex = withGenForeignPtr . peel . getIndex

peekBMAIndex :: Ptr CBMAIndex' -> IO BMAIndex
peekBMAIndex = newGenForeignPtr >=> newGenInterestRateIndex
withBMAIndex :: BMAIndex -> (Ptr CBMAIndex' -> IO b) -> IO b
withBMAIndex = withForeignPtr . _ptr . peel . getIndex

asIborIndex :: GenIborIndex a -> IO IborIndex
asIborIndex = transferGenForeignPtr peekIborIndex . peel . peel . getIndex
peekIborIndex :: Ptr CIborIndex' -> IO IborIndex
peekIborIndex = newCastForeignPtr >=> newGenIborIndex
withIborIndex :: GenIborIndex a -> (Ptr CIborIndex' -> IO b) -> IO b
withIborIndex = withGenForeignPtr . peel . peel . getIndex
newGenIborIndex :: GenForeignPtr a CIborIndex' -> IO (GenIborIndex a)
newGenIborIndex = pure . GenIndex . newAnyOf . newAnyOf

peekOvernightIborIndex :: Ptr COvernightIndex' -> IO OvernightIborIndex
peekOvernightIborIndex = newGenForeignPtr >=> newGenIborIndex
withOvernightIborIndex :: OvernightIborIndex -> (Ptr COvernightIndex' -> IO b) -> IO b
withOvernightIborIndex = withForeignPtr . _ptr . peel . peel . getIndex

asSwapIndex :: GenSwapIndex a -> IO SwapIndex
asSwapIndex = transferGenForeignPtr peekSwapIndex . peel . peel . getIndex
peekSwapIndex :: Ptr CSwapIndex' -> IO SwapIndex
peekSwapIndex = newCastForeignPtr >=> newGenSwapIndex
withSwapIndex :: GenSwapIndex a -> (Ptr CSwapIndex' -> IO b) -> IO b
withSwapIndex  = withGenForeignPtr . peel . peel . getIndex
newGenSwapIndex :: GenForeignPtr a CSwapIndex' -> IO (GenSwapIndex a)
newGenSwapIndex = pure . GenIndex . newAnyOf . newAnyOf

peekOvernightIndexedSwapIndex :: Ptr COvernightIndexedSwapIndex' -> IO OvernightIndexedSwapIndex
peekOvernightIndexedSwapIndex = newGenForeignPtr >=> newGenSwapIndex
withOvernightIndexedSwapIndex :: OvernightIndexedSwapIndex -> (Ptr COvernightIndexedSwapIndex' -> IO b) -> IO b
withOvernightIndexedSwapIndex = withForeignPtr  ._ptr . peel . peel . getIndex

-- TermStructure = GenTermStructure a
--   YieldTermStructure = GenYieldTermStructure b = GenTermStructure c
--     FittedBondDiscountCurve = GenYieldTermStructure ...
--   VolatilityTermStructure
--     OptionletVolatilityStructure
--     BlackVolTermStructure
--       BlackVarianceCurve
--     SwaptionVolatilityStructure
--     CapFloorTermVolSurface
--     LocalVolTermStructure
--   CallableBondVolatilityStructure
--   DefaultProbabilityTermStructure
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
newtype GenTermStructure a = GenTermStructure {getTermStructure :: GenForeignPtr a CTermStructure'}
type CTermStructure = ForeignPtr CTermStructure'
type TermStructure = GenTermStructure CTermStructure
type GenYieldTermStructure a = GenTermStructure (AnyOf CYieldTermStructure' a)
type CYieldTermStructure = ForeignPtr CYieldTermStructure'
type YieldTermStructure = GenYieldTermStructure CYieldTermStructure
type CFittedBondDiscountCurve = ForeignPtr CFittedBondDiscountCurve'
type FittedBondDiscountCurve = GenYieldTermStructure CFittedBondDiscountCurve
type GenVolatilityTermStructure a = GenTermStructure (AnyOf CVolatilityTermStructure' a)
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
type GenBlackVolTermStructure a = GenVolatilityTermStructure (AnyOf CBlackVolTermStructure' a)
type CBlackVolTermStructure = ForeignPtr CBlackVolTermStructure'
type BlackVolTermStructure = GenBlackVolTermStructure CBlackVolTermStructure
type CBlackVarianceCurve = ForeignPtr CBlackVarianceCurve'
type BlackVarianceCurve = GenBlackVolTermStructure CBlackVarianceCurve
type CCallableBondVolatilityStructure = ForeignPtr CCallableBondVolatilityStructure'
type CallableBondVolatilityStructure = GenTermStructure CCallableBondVolatilityStructure
type CDefaultProbabilityTermStructure = ForeignPtr CDefaultProbabilityTermStructure'
type DefaultProbabilityTermStructure = GenTermStructure CDefaultProbabilityTermStructure
foreign import ccall unsafe "ql.h &qlFreeTermStructure" qlFreeTermStructure :: FinalizerPtr CTermStructure'
foreign import ccall unsafe "ql.h &qlFreeVolatilityTermStructure" qlFreeVolatilityTermStructure :: FinalizerPtr CVolatilityTermStructure'
foreign import ccall unsafe "ql.h &qlFreeOptionletVolatilityStructure" qlFreeOptionletVolatilityStructure :: FinalizerPtr COptionletVolatilityStructure'
foreign import ccall unsafe "ql.h &qlFreeSwaptionVolatilityStructure" qlFreeSwaptionVolatilityStructure :: FinalizerPtr CSwaptionVolatilityStructure'
foreign import ccall unsafe "ql.h &qlFreeCapFloorTermVolSurface" qlFreeCapFloorTermVolSurface :: FinalizerPtr CCapFloorTermVolSurface'
foreign import ccall unsafe "ql.h &qlFreeLocalVolTermStructure" qlFreeLocalVolTermStructure :: FinalizerPtr CLocalVolTermStructure'
foreign import ccall unsafe "ql.h &qlFreeBlackVolTermStructure" qlFreeBlackVolTermStructure :: FinalizerPtr CBlackVolTermStructure'
foreign import ccall unsafe "ql.h &qlFreeBlackVarianceCurve" qlFreeBlackVarianceCurve :: FinalizerPtr CBlackVarianceCurve'
foreign import ccall unsafe "ql.h &qlFreeYieldTermStructure" qlFreeYieldTermStructure :: FinalizerPtr CYieldTermStructure'
foreign import ccall unsafe "ql.h &qlFreeFittedBondDiscountCurve" qlFreeFittedBondDiscountCurve :: FinalizerPtr CFittedBondDiscountCurve'
foreign import ccall unsafe "ql.h &qlFreeCallableBondVolatilityStructure" qlFreeCallableBondVolatilityStructure :: FinalizerPtr CCallableBondVolatilityStructure'
foreign import ccall unsafe "ql.h &qlFreeDefaultProbabilityTermStructure" qlFreeDefaultProbabilityTermStructure :: FinalizerPtr CDefaultProbabilityTermStructure'
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
asTermStructure = transferGenForeignPtr peekTermStructure . getTermStructure
withTermStructure :: GenTermStructure a  -> (Ptr CTermStructure' -> IO b) -> IO b
withTermStructure = withGenForeignPtr . getTermStructure
withGenTermStructure :: GenTermStructure (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenTermStructure = withForeignPtr . _ptr . getTermStructure
peekTermStructure :: Ptr CTermStructure' -> IO TermStructure
peekTermStructure = GenTermStructure <.> newCastForeignPtr

asVolatilityTermStructure :: GenVolatilityTermStructure a -> IO VolatilityTermStructure
asVolatilityTermStructure = transferGenForeignPtr peekVolatilityTermStructure . peel . getTermStructure
peekVolatilityTermStructure :: Ptr CVolatilityTermStructure' -> IO VolatilityTermStructure
peekVolatilityTermStructure = newCastForeignPtr >=> newGenVolatilityTermStructure
peekGenVolatilityTermStructure :: (Finalizable a, Upcastable a, Base a ~ CVolatilityTermStructure') => Ptr a -> IO (GenVolatilityTermStructure (ForeignPtr a))
peekGenVolatilityTermStructure = newGenForeignPtr >=> newGenVolatilityTermStructure
withVolatilityTermStructure :: GenVolatilityTermStructure a -> (Ptr CVolatilityTermStructure' -> IO b) -> IO b
withVolatilityTermStructure = withGenForeignPtr . peel . getTermStructure
withGenVolatilityTermStructure :: GenVolatilityTermStructure (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
withGenVolatilityTermStructure = withForeignPtr . _ptr . peel . getTermStructure
newGenVolatilityTermStructure :: GenForeignPtr a CVolatilityTermStructure' -> IO (GenVolatilityTermStructure a)
newGenVolatilityTermStructure = pure . GenTermStructure . newAnyOf

asBlackVolTermStructure :: GenBlackVolTermStructure a -> IO BlackVolTermStructure
asBlackVolTermStructure = transferGenForeignPtr peekBlackVolTermStructure . peel . peel . getTermStructure
peekBlackVolTermStructure :: Ptr CBlackVolTermStructure' -> IO BlackVolTermStructure
peekBlackVolTermStructure = newCastForeignPtr >=> newGenBlackVolTermStructure
withBlackVolTermStructure :: GenBlackVolTermStructure a -> (Ptr CBlackVolTermStructure' -> IO b) -> IO b
withBlackVolTermStructure = withGenForeignPtr . peel . peel . getTermStructure
newGenBlackVolTermStructure :: GenForeignPtr a CBlackVolTermStructure' -> IO (GenBlackVolTermStructure a)
newGenBlackVolTermStructure = pure . GenTermStructure . newAnyOf . newAnyOf

peekBlackVarianceCurve :: Ptr CBlackVarianceCurve' -> IO BlackVarianceCurve
peekBlackVarianceCurve = newGenForeignPtr >=> newGenBlackVolTermStructure
withBlackVarianceCurve :: BlackVarianceCurve -> (Ptr CBlackVarianceCurve' -> IO b) -> IO b
withBlackVarianceCurve = withForeignPtr . _ptr . peel . peel . getTermStructure

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
asYieldTermStructure = transferGenForeignPtr peekYieldTermStructure . peel . getTermStructure
peekYieldTermStructure :: Ptr CYieldTermStructure' -> IO YieldTermStructure
peekYieldTermStructure = newCastForeignPtr >=> newGenYieldTermStructure
withYieldTermStructure :: GenYieldTermStructure a -> (Ptr CYieldTermStructure' -> IO b) -> IO b
withYieldTermStructure = withGenForeignPtr . peel . getTermStructure
withMaybeYieldTermStructure :: Maybe (GenYieldTermStructure a) -> (Ptr CYieldTermStructure' -> IO b) -> IO b
withMaybeYieldTermStructure x f = maybe (f nullPtr) (`withYieldTermStructure` f) x
newGenYieldTermStructure :: GenForeignPtr a CYieldTermStructure' -> IO (GenYieldTermStructure a)
newGenYieldTermStructure = pure . GenTermStructure . newAnyOf

peekFittedBondDiscountCurve :: Ptr CFittedBondDiscountCurve' -> IO FittedBondDiscountCurve
peekFittedBondDiscountCurve = newGenForeignPtr >=> newGenYieldTermStructure
withFittedBondDiscountCurve :: FittedBondDiscountCurve -> (Ptr CFittedBondDiscountCurve' -> IO b) -> IO b
withFittedBondDiscountCurve = withForeignPtr . _ptr . peel . getTermStructure

-- StochasticProcess
--   ExtOUWithJumpsProcess
--   GJRGARCHProcess
--   HybridHestonHullWhiteProcess
--   KlugeExtOUProcess
--   LiborForwardModelProcess
--   StochasticProcessArray
--   HestonProcess
--     BatesProcess
--   StochasticProcess1D
--     ExtendedOrnsteinUhlenbeckProcess
--     HullWhiteForwardProcess
--     HullWhiteProcess
--     Merton76Process
--     VarianceGammaProcess
--     GeneralizedBlackScholesProcess
--       BlackProcess
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
newtype GenStochasticProcess a = GenStochasticProcess {getStochasticProcess :: GenForeignPtr a CStochasticProcess'}
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
type GenHestonProcess a = GenStochasticProcess (AnyOf CHestonProcess' a)
type CHestonProcess = ForeignPtr CHestonProcess'
type HestonProcess = GenHestonProcess CHestonProcess
type GenStochasticProcess1D a = GenStochasticProcess (AnyOf CStochasticProcess1D' a)
type CStochasticProcess1D = ForeignPtr CStochasticProcess1D'
type StochasticProcess1D = GenStochasticProcess1D CStochasticProcess1D
type CMerton76Process = ForeignPtr CMerton76Process'
type Merton76Process = GenStochasticProcess1D CMerton76Process
type CVarianceGammaProcess = ForeignPtr CVarianceGammaProcess'
type VarianceGammaProcess = GenStochasticProcess1D CVarianceGammaProcess
type GenGeneralizedBlackScholesProcess a = GenStochasticProcess1D (AnyOf CGeneralizedBlackScholesProcess' a)
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
foreign import ccall unsafe "ql.h &qlFreeStochasticProcess" qlFreeStochasticProcess :: FinalizerPtr CStochasticProcess'
foreign import ccall unsafe "ql.h &qlFreeExtOUWithJumpsProcess" qlFreeExtOUWithJumpsProcess :: FinalizerPtr CExtOUWithJumpsProcess'
foreign import ccall unsafe "ql.h &qlFreeGJRGARCHProcess" qlFreeGJRGARCHProcess :: FinalizerPtr CGJRGARCHProcess'
foreign import ccall unsafe "ql.h &qlFreeHybridHestonHullWhiteProcess" qlFreeHybridHestonHullWhiteProcess :: FinalizerPtr CHybridHestonHullWhiteProcess'
foreign import ccall unsafe "ql.h &qlFreeKlugeExtOUProcess" qlFreeKlugeExtOUProcess :: FinalizerPtr CKlugeExtOUProcess'
foreign import ccall unsafe "ql.h &qlFreeLiborForwardModelProcess" qlFreeLiborForwardModelProcess :: FinalizerPtr CLiborForwardModelProcess'
foreign import ccall unsafe "ql.h &qlFreeStochasticProcessArray" qlFreeStochasticProcessArray :: FinalizerPtr CStochasticProcessArray'
foreign import ccall unsafe "ql.h &qlFreeHestonProcess" qlFreeHestonProcess :: FinalizerPtr CHestonProcess'
foreign import ccall unsafe "ql.h &qlFreeStochasticProcess1D" qlFreeStochasticProcess1D :: FinalizerPtr CStochasticProcess1D'
foreign import ccall unsafe "ql.h &qlFreeBatesProcess" qlFreeBatesProcess :: FinalizerPtr CBatesProcess'
foreign import ccall unsafe "ql.h &qlFreeExtendedOrnsteinUhlenbeckProcess" qlFreeExtendedOrnsteinUhlenbeckProcess :: FinalizerPtr CExtendedOrnsteinUhlenbeckProcess'
foreign import ccall unsafe "ql.h &qlFreeHullWhiteForwardProcess" qlFreeHullWhiteForwardProcess :: FinalizerPtr CHullWhiteForwardProcess'
foreign import ccall unsafe "ql.h &qlFreeHullWhiteProcess" qlFreeHullWhiteProcess :: FinalizerPtr CHullWhiteProcess'
foreign import ccall unsafe "ql.h &qlFreeMerton76Process" qlFreeMerton76Process :: FinalizerPtr CMerton76Process'
foreign import ccall unsafe "ql.h &qlFreeVarianceGammaProcess" qlFreeVarianceGammaProcess :: FinalizerPtr CVarianceGammaProcess'
foreign import ccall unsafe "ql.h &qlFreeGeneralizedBlackScholesProcess" qlFreeGeneralizedBlackScholesProcess :: FinalizerPtr CGeneralizedBlackScholesProcess'
foreign import ccall unsafe "ql.h &qlFreeBlackProcess" qlFreeBlackProcess :: FinalizerPtr CBlackProcess'
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
asStochasticProcess = transferGenForeignPtr peekStochasticProcess . getStochasticProcess
peekStochasticProcess :: Ptr CStochasticProcess' -> IO StochasticProcess
peekStochasticProcess = GenStochasticProcess <.> newCastForeignPtr
withStochasticProcess :: GenStochasticProcess a -> (Ptr CStochasticProcess' -> IO b) -> IO b
withStochasticProcess = withGenForeignPtr . getStochasticProcess
withGenStochasticProcess :: GenStochasticProcess (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenStochasticProcess = withForeignPtr . _ptr . getStochasticProcess
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
asHestonProcess = transferGenForeignPtr peekHestonProcess . peel . getStochasticProcess
peekHestonProcess :: Ptr CHestonProcess' -> IO HestonProcess
peekHestonProcess = newCastForeignPtr >=> newGenHestonProcess
withHestonProcess :: GenHestonProcess a -> (Ptr CHestonProcess' -> IO b) -> IO b
withHestonProcess = withGenForeignPtr . peel . getStochasticProcess
newGenHestonProcess :: GenForeignPtr a CHestonProcess' -> IO (GenHestonProcess a)
newGenHestonProcess = pure . GenStochasticProcess . newAnyOf
peekGenHestonProcess :: (Finalizable a, Upcastable a, Base a ~ CHestonProcess') => Ptr a -> IO (GenHestonProcess (ForeignPtr a))
peekGenHestonProcess = newGenForeignPtr >=> newGenHestonProcess
asStochasticProcess1D :: GenStochasticProcess1D a -> IO StochasticProcess1D
asStochasticProcess1D = transferGenForeignPtr peekStochasticProcess1D . peel . getStochasticProcess
peekStochasticProcess1D :: Ptr CStochasticProcess1D' -> IO StochasticProcess1D
peekStochasticProcess1D = newCastForeignPtr >=> newGenStochasticProcess1D
withStochasticProcess1D :: GenStochasticProcess1D a -> (Ptr CStochasticProcess1D' -> IO b) -> IO b
withStochasticProcess1D = withGenForeignPtr . peel . getStochasticProcess
withStochasticProcess1DArray :: [GenStochasticProcess1D a] -> ((CUInt, Ptr (Ptr CStochasticProcess1D')) -> IO b) -> IO b
withStochasticProcess1DArray = withGenArray withStochasticProcess1D
newGenStochasticProcess1D :: GenForeignPtr a CStochasticProcess1D' -> IO (GenStochasticProcess1D a)
newGenStochasticProcess1D = pure . GenStochasticProcess . newAnyOf
peekGenStochasticProcess1D :: (Finalizable a, Upcastable a, Base a ~ CStochasticProcess1D') => Ptr a -> IO (GenStochasticProcess1D (ForeignPtr a))
peekGenStochasticProcess1D = newGenForeignPtr >=> newGenStochasticProcess1D
withGenStochasticProcess1D :: GenStochasticProcess1D (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
withGenStochasticProcess1D = withForeignPtr . _ptr . peel . getStochasticProcess
peekBatesProcess :: Ptr CBatesProcess' -> IO BatesProcess
peekBatesProcess = peekGenHestonProcess
withBatesProcess :: BatesProcess -> (Ptr CBatesProcess' -> IO b) -> IO b
withBatesProcess = withForeignPtr . _ptr . peel . getStochasticProcess
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
asGeneralizedBlackScholesProcess = transferGenForeignPtr peekGeneralizedBlackScholesProcess . peel . peel . getStochasticProcess
peekGeneralizedBlackScholesProcess :: Ptr CGeneralizedBlackScholesProcess' -> IO GeneralizedBlackScholesProcess
peekGeneralizedBlackScholesProcess = newCastForeignPtr >=> newGenGeneralizedBlackScholesProcess
withGeneralizedBlackScholesProcess :: GenGeneralizedBlackScholesProcess a -> (Ptr CGeneralizedBlackScholesProcess' -> IO b) -> IO b
withGeneralizedBlackScholesProcess = withGenForeignPtr . peel . peel . getStochasticProcess
newGenGeneralizedBlackScholesProcess :: GenForeignPtr a CGeneralizedBlackScholesProcess' -> IO (GenGeneralizedBlackScholesProcess a)
newGenGeneralizedBlackScholesProcess = pure . GenStochasticProcess . newAnyOf . newAnyOf
peekBlackProcess :: Ptr CBlackProcess' -> IO BlackProcess
peekBlackProcess = newGenForeignPtr >=> newGenGeneralizedBlackScholesProcess
withBlackProcess :: BlackProcess -> (Ptr CBlackProcess' -> IO b) -> IO b
withBlackProcess = withForeignPtr . _ptr . peel . peel . getStochasticProcess

-- CalibratedModel
--   LiborForwardModel: AffineModel
--   GJRGARCHModel
--   PiecewiseTimeDependentHestonModel
--   HestonModel
--     BatesModel
--       BatesDetJumpModel
--     BatesDoubleExpModel
--       BatesDoubleExpDetJumpModel
--   ShortRateModel
--     G2: AffineModel
--     OneFactorAffineModel: AffineModel
--       HullWhite: AffineMode
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
newtype GenCalibratedModel a = GenCalibratedModel {getCalibratedModel :: GenForeignPtr a CCalibratedModel'}
type CCalibratedModel = ForeignPtr CCalibratedModel'
type CalibratedModel = GenCalibratedModel CCalibratedModel
type CLiborForwardModel = ForeignPtr CLiborForwardModel'
type LiborForwardModel = GenCalibratedModel CLiborForwardModel
type CGJRGARCHModel = ForeignPtr CGJRGARCHModel'
type GJRGARCHModel = GenCalibratedModel CGJRGARCHModel
type CPiecewiseTimeDependentHestonModel = ForeignPtr CPiecewiseTimeDependentHestonModel'
type PiecewiseTimeDependentHestonModel = GenCalibratedModel CPiecewiseTimeDependentHestonModel
type GenHestonModel a = GenCalibratedModel (AnyOf CHestonModel' a)
type CHestonModel = ForeignPtr CHestonModel'
type HestonModel = GenHestonModel CHestonModel
type GenShortRateModel a = GenCalibratedModel (AnyOf CShortRateModel' a)
type CShortRateModel = ForeignPtr CShortRateModel'
type ShortRateModel = GenShortRateModel CShortRateModel
type GenBatesModel a = GenHestonModel (AnyOf CBatesModel' a)
type CBatesModel = ForeignPtr CBatesModel'
type BatesModel = GenBatesModel CBatesModel
type CBatesDetJumpModel = ForeignPtr CBatesDetJumpModel'
type BatesDetJumpModel = GenBatesModel CBatesDetJumpModel
type GenBatesDoubleExpModel a = GenHestonModel (AnyOf CBatesDoubleExpModel' a)
type CBatesDoubleExpModel = ForeignPtr CBatesDoubleExpModel'
type BatesDoubleExpModel = GenBatesDoubleExpModel CBatesDoubleExpModel
type CBatesDoubleExpDetJumpModel = ForeignPtr CBatesDoubleExpDetJumpModel'
type BatesDoubleExpDetJumpModel = GenBatesDoubleExpModel CBatesDoubleExpDetJumpModel
type GenOneFactorAffineModel a = GenShortRateModel (AnyOf COneFactorAffineModel' a)
type COneFactorAffineModel = ForeignPtr COneFactorAffineModel'
type OneFactorAffineModel = GenOneFactorAffineModel COneFactorAffineModel
type CHullWhite = ForeignPtr CHullWhite'
type HullWhite = GenOneFactorAffineModel CHullWhite
type CG2 = ForeignPtr CG2'
type G2 = GenShortRateModel CG2
foreign import ccall unsafe "ql.h &qlFreeCalibratedModel" qlFreeCalibratedModel :: FinalizerPtr CCalibratedModel'
foreign import ccall unsafe "ql.h &qlFreeLiborForwardModel" qlFreeLiborForwardModel :: FinalizerPtr CLiborForwardModel'
foreign import ccall unsafe "ql.h &qlFreeGJRGARCHModel" qlFreeGJRGARCHModel :: FinalizerPtr CGJRGARCHModel'
foreign import ccall unsafe "ql.h &qlFreePiecewiseTimeDependentHestonModel" qlFreePiecewiseTimeDependentHestonModel :: FinalizerPtr CPiecewiseTimeDependentHestonModel'
foreign import ccall unsafe "ql.h &qlFreeHestonModel" qlFreeHestonModel :: FinalizerPtr CHestonModel'
foreign import ccall unsafe "ql.h &qlFreeShortRateModel" qlFreeShortRateModel :: FinalizerPtr CShortRateModel'
foreign import ccall unsafe "ql.h &qlFreeBatesModel" qlFreeBatesModel :: FinalizerPtr CBatesModel'
foreign import ccall unsafe "ql.h &qlFreeBatesDetJumpModel" qlFreeBatesDetJumpModel :: FinalizerPtr CBatesDetJumpModel'
foreign import ccall unsafe "ql.h &qlFreeBatesDoubleExpModel" qlFreeBatesDoubleExpModel :: FinalizerPtr CBatesDoubleExpModel'
foreign import ccall unsafe "ql.h &qlFreeBatesDoubleExpDetJumpModel" qlFreeBatesDoubleExpDetJumpModel :: FinalizerPtr CBatesDoubleExpDetJumpModel'
foreign import ccall unsafe "ql.h &qlFreeG2" qlFreeG2 :: FinalizerPtr CG2'
foreign import ccall unsafe "ql.h &qlFreeAffineModel" qlFreeAffineModel :: FinalizerPtr CAffineModel'
foreign import ccall unsafe "ql.h &qlFreeOneFactorAffineModel" qlFreeOneFactorAffineModel :: FinalizerPtr COneFactorAffineModel'
foreign import ccall unsafe "ql.h &qlFreeHullWhite" qlFreeHullWhite :: FinalizerPtr CHullWhite'
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
asCalibratedModel :: GenCalibratedModel a -> IO CalibratedModel
asCalibratedModel = transferGenForeignPtr peekCalibratedModel . getCalibratedModel
peekCalibratedModel :: Ptr CCalibratedModel' -> IO CalibratedModel
peekCalibratedModel = GenCalibratedModel <.> newCastForeignPtr
withCalibratedModel :: GenCalibratedModel a -> (Ptr CCalibratedModel' -> IO b) -> IO b
withCalibratedModel = withGenForeignPtr . getCalibratedModel
withGenCalibratedModel :: GenCalibratedModel (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenCalibratedModel = withForeignPtr . _ptr . getCalibratedModel
peekLiborForwardModel :: Ptr CLiborForwardModel' -> IO LiborForwardModel
peekLiborForwardModel = GenCalibratedModel <.> newGenForeignPtr
peekGJRGARCHModel :: Ptr CGJRGARCHModel' -> IO GJRGARCHModel
peekGJRGARCHModel = GenCalibratedModel <.> newGenForeignPtr
peekPiecewiseTimeDependentHestonModel :: Ptr CPiecewiseTimeDependentHestonModel' -> IO PiecewiseTimeDependentHestonModel
peekPiecewiseTimeDependentHestonModel = GenCalibratedModel <.> newGenForeignPtr

asHestonModel :: GenHestonModel a -> IO HestonModel
asHestonModel = transferGenForeignPtr peekHestonModel . peel . getCalibratedModel
peekHestonModel :: Ptr CHestonModel' -> IO HestonModel
peekHestonModel = newCastForeignPtr >=> newGenHestonModel
withHestonModel :: GenHestonModel a -> (Ptr CHestonModel' -> IO b) -> IO b
withHestonModel = withGenForeignPtr . peel . getCalibratedModel
newGenHestonModel :: GenForeignPtr a CHestonModel' -> IO (GenHestonModel a)
newGenHestonModel = pure . GenCalibratedModel . newAnyOf

asShortRateModel :: GenShortRateModel a -> IO ShortRateModel
asShortRateModel  = transferGenForeignPtr peekShortRateModel . peel . getCalibratedModel
peekShortRateModel :: Ptr CShortRateModel' -> IO ShortRateModel
peekShortRateModel = newCastForeignPtr >=> newGenShortRateModel
withShortRateModel :: GenShortRateModel a -> (Ptr CShortRateModel' -> IO b) -> IO b
withShortRateModel = withGenForeignPtr . peel . getCalibratedModel
newGenShortRateModel :: GenForeignPtr a CShortRateModel' -> IO (GenShortRateModel a)
newGenShortRateModel = pure . GenCalibratedModel . newAnyOf
peekGenShortRateModel :: (Finalizable a, Upcastable a, Base a ~ CShortRateModel') => Ptr a -> IO (GenShortRateModel (ForeignPtr a))
peekGenShortRateModel = newGenForeignPtr >=> newGenShortRateModel

asBatesModel :: GenBatesModel a -> IO BatesModel
asBatesModel = transferGenForeignPtr peekBatesModel . peel . peel . getCalibratedModel
peekBatesModel :: Ptr CBatesModel' -> IO BatesModel
peekBatesModel = newCastForeignPtr >=> newGenBatesModel
withBatesModel :: GenBatesModel a -> (Ptr CBatesModel' -> IO b) -> IO b
withBatesModel = withGenForeignPtr . peel . peel . getCalibratedModel
newGenBatesModel :: GenForeignPtr a CBatesModel' -> IO (GenBatesModel a)
newGenBatesModel = pure . GenCalibratedModel . newAnyOf . newAnyOf
peekBatesDetJumpModel :: Ptr CBatesDetJumpModel' -> IO BatesDetJumpModel
peekBatesDetJumpModel = newGenForeignPtr >=> newGenBatesModel
withBatesDetJumpModel :: BatesDetJumpModel -> (Ptr CBatesDetJumpModel' -> IO b) -> IO b
withBatesDetJumpModel = withForeignPtr . _ptr . peel . peel . getCalibratedModel

asBatesDoubleExpModel :: GenBatesDoubleExpModel a -> IO BatesDoubleExpModel
asBatesDoubleExpModel = transferGenForeignPtr peekBatesDoubleExpModel . peel . peel . getCalibratedModel
peekBatesDoubleExpModel :: Ptr CBatesDoubleExpModel' -> IO BatesDoubleExpModel
peekBatesDoubleExpModel = newCastForeignPtr >=> newGenBatesDoubleExpModel
withBatesDoubleExpModel :: GenBatesDoubleExpModel a -> (Ptr CBatesDoubleExpModel' -> IO b) -> IO b
withBatesDoubleExpModel = withGenForeignPtr . peel . peel . getCalibratedModel
newGenBatesDoubleExpModel :: GenForeignPtr a CBatesDoubleExpModel' -> IO (GenBatesDoubleExpModel a)
newGenBatesDoubleExpModel = pure . GenCalibratedModel . newAnyOf . newAnyOf
peekBatesDoubleExpDetJumpModel :: Ptr CBatesDoubleExpDetJumpModel' -> IO BatesDoubleExpDetJumpModel
peekBatesDoubleExpDetJumpModel = newGenForeignPtr >=> newGenBatesDoubleExpModel
withBatesDoubleExpDetJumpModel :: BatesDoubleExpDetJumpModel -> (Ptr CBatesDoubleExpDetJumpModel' -> IO b) -> IO b
withBatesDoubleExpDetJumpModel = withForeignPtr . _ptr . peel . peel . getCalibratedModel

asOneFactorAffineModel :: GenOneFactorAffineModel a -> IO OneFactorAffineModel
asOneFactorAffineModel = transferGenForeignPtr peekOneFactorAffineModel . peel . peel . getCalibratedModel
peekOneFactorAffineModel :: Ptr COneFactorAffineModel' -> IO OneFactorAffineModel
peekOneFactorAffineModel = newCastForeignPtr >=> newGenOneFactorAffineModel
withOneFactorAffineModel :: GenOneFactorAffineModel a -> (Ptr COneFactorAffineModel' -> IO b) -> IO b
withOneFactorAffineModel = withGenForeignPtr . peel . peel . getCalibratedModel
newGenOneFactorAffineModel :: GenForeignPtr a COneFactorAffineModel' -> IO (GenOneFactorAffineModel a)
newGenOneFactorAffineModel = pure . GenCalibratedModel . newAnyOf . newAnyOf

peekHullWhite :: Ptr CHullWhite' -> IO HullWhite
peekHullWhite = newGenForeignPtr >=> newGenOneFactorAffineModel
withHullWhite :: HullWhite -> (Ptr CHullWhite' -> IO b) -> IO b
withHullWhite = withForeignPtr . _ptr . peel . peel . getCalibratedModel

peekG2 :: Ptr CG2' -> IO G2
peekG2 = peekGenShortRateModel
withG2 :: G2 -> (Ptr CG2' -> IO b) -> IO b
withG2 = withForeignPtr . _ptr . peel . getCalibratedModel

newtype GenAffineModel a = GenAffineModel {getAffineModel :: GenForeignPtr a CAffineModel'}
type CAffineModel = ForeignPtr CAffineModel'
type AffineModel = GenAffineModel CAffineModel
foreign import ccall "ql.h qlOneFactorAffineModelAsAffineModel" qlOneFactorAffineModelAsAffineModel :: Ptr COneFactorAffineModel' -> IO (Ptr CAffineModel')
foreign import ccall "ql.h qlLiborForwardModelAsAffineModel" qlLiborForwardModelAsAffineModel :: Ptr CLiborForwardModel' -> IO (Ptr CAffineModel')
foreign import ccall "ql.h qlG2AsAffineModel" qlG2AsAffineModel :: Ptr CG2' -> IO (Ptr CAffineModel')
foreign import ccall "ql.h qlHullWhiteAsAffineModel" qlHullWhiteAsAffineModel :: Ptr CHullWhite' -> IO (Ptr CAffineModel')

peekAffineModel :: Ptr CAffineModel' -> IO AffineModel
peekAffineModel = GenAffineModel <.> newCastForeignPtr

withAffineModel :: GenAffineModel a -> (Ptr CAffineModel' -> IO b) -> IO b
withAffineModel = withGenForeignPtr . getAffineModel

class HasAffineModel a where
  asAffineModel :: a -> IO AffineModel

instance HasAffineModel HullWhite where
  asAffineModel = flip withForeignPtr (qlHullWhiteAsAffineModel >=> peekAffineModel) . _ptr . peel . peel . getCalibratedModel
instance HasAffineModel G2 where
  asAffineModel = flip withForeignPtr (qlG2AsAffineModel >=> peekAffineModel) . _ptr . peel . getCalibratedModel
instance HasAffineModel OneFactorAffineModel where
  asAffineModel = flip withForeignPtr (qlOneFactorAffineModelAsAffineModel >=> peekAffineModel) . _ptr . peel . peel . getCalibratedModel
instance HasAffineModel LiborForwardModel where
  asAffineModel = flip withForeignPtr (qlLiborForwardModelAsAffineModel >=> peekAffineModel) . _ptr . getCalibratedModel

-- a:Instrument ("a" == an abstract class)
--   a:Forward : Instrument
--     BondForward : Forward
--   a:Option : Instrument
--     CdsOption : Option
--     MultiAssetOption : Option
--       MargrabeOption : MultiAssetOption
--     OneAssetOption : Option
--       BarrierOption : OneAssetOption
--       ForwardVanillaOption : OneAssetOption
--       QuantoVanillaOption : OneAssetOption
--       VanillaOption : OneAssetOption
--     QuantoBarrierOption : Option (TODO consider deriving from BarrierOption)
--     QuantoForwardVanillaOption : Option (TODO consider deriving from ForwardVanillaOption)
--     Swaption : Option
--   a:Swap : Instrument
--     VanillaSwap : Swap
--     AssetSwap : Swap
--     BMASwap : Swap
--     OvernightIndexedSwap : Swap
--   ForwardRateAgreement : Instrument
--   CreditDefaultSwap : Instrument
--     CapFloor : Instrument
--     Bond : Instrument
--       ConvertibleBond : Bond
--       FixedRateBond : Bond
--       CallableBond : Bond
data CInstrument'
newtype GenInstrument a = GenInstrument {getInstrument :: GenForeignPtr a CInstrument'}
type CInstrument = ForeignPtr CInstrument'
type Instrument = GenInstrument CInstrument
foreign import ccall unsafe "ql.h &qlFreeInstrument" qlFreeInstrument :: FinalizerPtr CInstrument'
instance Finalizable CInstrument' where finalize = qlFreeInstrument
asInstrument :: GenInstrument a -> IO Instrument
asInstrument = transferGenForeignPtr peekInstrument . getInstrument
peekInstrument :: Ptr CInstrument' -> IO Instrument
peekInstrument = GenInstrument <.> newCastForeignPtr
withInstrument :: GenInstrument a -> (Ptr CInstrument' -> IO b) -> IO b
withInstrument = withGenForeignPtr . getInstrument
withGenInstrument :: GenInstrument (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
withGenInstrument = withForeignPtr . _ptr . getInstrument

data CForwardRateAgreement'
type CForwardRateAgreement = ForeignPtr CForwardRateAgreement'
type ForwardRateAgreement = GenInstrument CForwardRateAgreement
foreign import ccall unsafe "ql.h &qlFreeForwardRateAgreement" qlFreeForwardRateAgreement :: FinalizerPtr CForwardRateAgreement'
instance Finalizable CForwardRateAgreement' where finalize = qlFreeForwardRateAgreement
foreign import ccall "ql.h qlForwardRateAgreementAsInstrument" qlForwardRateAgreementAsInstrument :: Ptr CForwardRateAgreement' -> IO (Ptr CInstrument')
instance Upcastable CForwardRateAgreement' where {type Base CForwardRateAgreement' = CInstrument'; upcast = qlForwardRateAgreementAsInstrument}
peekForwardRateAgreement :: Ptr CForwardRateAgreement' -> IO ForwardRateAgreement
peekForwardRateAgreement = GenInstrument <.> newGenForeignPtr

data CCreditDefaultSwap'
type CCreditDefaultSwap = ForeignPtr CCreditDefaultSwap'
type CreditDefaultSwap = GenInstrument CCreditDefaultSwap
foreign import ccall unsafe "ql.h &qlFreeCreditDefaultSwap" qlFreeCreditDefaultSwap :: FinalizerPtr CCreditDefaultSwap'
instance Finalizable CCreditDefaultSwap' where finalize = qlFreeCreditDefaultSwap
foreign import ccall "ql.h qlCreditDefaultSwapAsInstrument" qlCreditDefaultSwapAsInstrument :: Ptr CCreditDefaultSwap' -> IO (Ptr CInstrument')
instance Upcastable CCreditDefaultSwap' where {type Base CCreditDefaultSwap' = CInstrument'; upcast = qlCreditDefaultSwapAsInstrument}
peekCreditDefaultSwap :: Ptr CCreditDefaultSwap' -> IO CreditDefaultSwap
peekCreditDefaultSwap = GenInstrument <.> newGenForeignPtr

data CCapFloor'
type CCapFloor = ForeignPtr CCapFloor'
type CapFloor = GenInstrument CCapFloor
foreign import ccall unsafe "ql.h &qlFreeCapFloor" qlFreeCapFloor :: FinalizerPtr CCapFloor'
instance Finalizable CCapFloor' where finalize = qlFreeCapFloor
foreign import ccall "ql.h qlCapFloorAsInstrument" qlCapFloorAsInstrument :: Ptr CCapFloor' -> IO (Ptr CInstrument')
instance Upcastable CCapFloor' where {type Base CCapFloor' = CInstrument'; upcast = qlCapFloorAsInstrument}
peekCapFloor :: Ptr CCapFloor' -> IO CapFloor
peekCapFloor = GenInstrument <.> newGenForeignPtr

data CForward'
type GenForward a = GenInstrument (AnyOf CForward' a)
type CForward = ForeignPtr CForward'
type Forward = GenForward CForward
foreign import ccall unsafe "ql.h &qlFreeForward" qlFreeForward :: FinalizerPtr CForward'
instance Finalizable CForward' where finalize = qlFreeForward
foreign import ccall "ql.h qlForwardAsInstrument" qlForwardAsInstrument :: Ptr CForward' -> IO (Ptr CInstrument')
instance Upcastable CForward' where {type Base CForward' = CInstrument'; upcast = qlForwardAsInstrument}
asForward :: GenForward a -> IO Forward
asForward = transferGenForeignPtr peekForward . peel . getInstrument
peekForward :: Ptr CForward' -> IO Forward
peekForward = newCastForeignPtr >=> newGenForward
withForward :: GenForward a -> (Ptr CForward' -> IO b) -> IO b
withForward = withGenForeignPtr . peel . getInstrument
newGenForward :: GenForeignPtr a CForward' -> IO (GenForward a)
newGenForward = pure . GenInstrument . newAnyOf
peekGenForward :: (Finalizable a, Upcastable a, Base a ~ CForward') => Ptr a -> IO (GenForward (ForeignPtr a))
peekGenForward = newGenForeignPtr >=> newGenForward
withGenForward :: GenForward (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
withGenForward = withForeignPtr . _ptr . peel . getInstrument

data COption'
type GenOption a = GenInstrument (AnyOf COption' a)
type COption = ForeignPtr COption'
type Option = GenOption COption
foreign import ccall unsafe "ql.h &qlFreeOption" qlFreeOption :: FinalizerPtr COption'
instance Finalizable COption' where finalize = qlFreeOption
foreign import ccall "ql.h qlOptionAsInstrument" qlOptionAsInstrument :: Ptr COption' -> IO (Ptr CInstrument')
instance Upcastable COption' where {type Base COption' = CInstrument'; upcast = qlOptionAsInstrument}
asOption :: GenOption a -> IO Option
asOption = transferGenForeignPtr peekOption . peel . getInstrument
peekOption :: Ptr COption' -> IO Option
peekOption = newCastForeignPtr >=> newGenOption
withOption :: GenOption a -> (Ptr COption' -> IO b) -> IO b
withOption = withGenForeignPtr . peel . getInstrument
newGenOption :: GenForeignPtr a COption' -> IO (GenOption a)
newGenOption = pure . GenInstrument . newAnyOf
peekGenOption :: (Finalizable a, Upcastable a, Base a ~ COption') => Ptr a -> IO (GenOption (ForeignPtr a))
peekGenOption = newGenForeignPtr >=> newGenOption
withGenOption :: GenOption (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
withGenOption = withForeignPtr . _ptr . peel . getInstrument

data CSwap'
type GenSwap a = GenInstrument (AnyOf CSwap' a)
type CSwap = ForeignPtr CSwap'
type Swap = GenSwap CSwap
foreign import ccall unsafe "ql.h &qlFreeSwap" qlFreeSwap :: FinalizerPtr CSwap'
instance Finalizable CSwap' where finalize = qlFreeSwap
foreign import ccall "ql.h qlSwapAsInstrument" qlSwapAsInstrument :: Ptr CSwap' -> IO (Ptr CInstrument')
instance Upcastable CSwap' where {type Base CSwap' = CInstrument'; upcast = qlSwapAsInstrument}
asSwap :: GenSwap a -> IO Swap
asSwap = transferGenForeignPtr peekSwap . peel . getInstrument
peekSwap :: Ptr CSwap' -> IO Swap
peekSwap = newCastForeignPtr >=> newGenSwap
withSwap :: GenSwap a -> (Ptr CSwap' -> IO b) -> IO b
withSwap = withGenForeignPtr . peel . getInstrument
newGenSwap :: GenForeignPtr a CSwap' -> IO (GenSwap a)
newGenSwap = pure . GenInstrument . newAnyOf
peekGenSwap :: (Finalizable a, Upcastable a, Base a ~ CSwap') => Ptr a -> IO (GenSwap (ForeignPtr a))
peekGenSwap = newGenForeignPtr >=> newGenSwap
withGenSwap :: GenSwap (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
withGenSwap = withForeignPtr . _ptr . peel . getInstrument

data CBond'
type GenBond a = GenInstrument (AnyOf CBond' a)
type CBond = ForeignPtr CBond'
type Bond = GenBond CBond
foreign import ccall unsafe "ql.h &qlFreeBond" qlFreeBond :: FinalizerPtr CBond'
instance Finalizable CBond' where finalize = qlFreeBond
foreign import ccall "ql.h qlBondAsInstrument" qlBondAsInstrument :: Ptr CBond' -> IO (Ptr CInstrument')
instance Upcastable CBond' where {type Base CBond' = CInstrument'; upcast = qlBondAsInstrument}
asBond :: GenBond a -> IO Bond
asBond = transferGenForeignPtr peekBond . peel . getInstrument
peekBond :: Ptr CBond' -> IO Bond
peekBond = newCastForeignPtr >=> newGenBond
withBond :: GenBond a -> (Ptr CBond' -> IO b) -> IO b
withBond = withGenForeignPtr . peel . getInstrument
newGenBond :: GenForeignPtr a CBond' -> IO (GenBond a)
newGenBond = pure . GenInstrument . newAnyOf
peekGenBond :: (Finalizable a, Upcastable a, Base a ~ CBond') => Ptr a -> IO (GenBond (ForeignPtr a))
peekGenBond = newGenForeignPtr >=> newGenBond
withGenBond :: GenBond (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
withGenBond = withForeignPtr . _ptr . peel . getInstrument

data CBondForward'
type CBondForward = ForeignPtr CBondForward'
type BondForward = GenForward CBondForward
foreign import ccall unsafe "ql.h &qlFreeBondForward" qlFreeBondForward :: FinalizerPtr CBondForward'
instance Finalizable CBondForward' where finalize = qlFreeBondForward
foreign import ccall "ql.h qlBondForwardAsForward" qlBondForwardAsForward :: Ptr CBondForward' -> IO (Ptr CForward')
instance Upcastable CBondForward' where {type Base CBondForward' = CForward'; upcast = qlBondForwardAsForward}
peekBondForward :: Ptr CBondForward' -> IO BondForward
peekBondForward = peekGenForward
withBondForward :: BondForward -> (Ptr CBondForward' -> IO b) -> IO b
withBondForward = withForeignPtr . _ptr . peel . getInstrument

data CConvertibleBond'
type CConvertibleBond = ForeignPtr CConvertibleBond'
type ConvertibleBond = GenBond CConvertibleBond
foreign import ccall unsafe "ql.h &qlFreeConvertibleBond" qlFreeConvertibleBond :: FinalizerPtr CConvertibleBond'
instance Finalizable CConvertibleBond' where finalize = qlFreeConvertibleBond
foreign import ccall "ql.h qlConvertibleBondAsBond" qlConvertibleBondAsBond :: Ptr CConvertibleBond' -> IO (Ptr CBond')
instance Upcastable CConvertibleBond' where {type Base CConvertibleBond' = CBond'; upcast = qlConvertibleBondAsBond}
peekConvertibleBond :: Ptr CConvertibleBond' -> IO ConvertibleBond
peekConvertibleBond = peekGenBond
withConvertibleBond :: ConvertibleBond -> (Ptr CConvertibleBond' -> IO b) -> IO b
withConvertibleBond = withForeignPtr . _ptr . peel . getInstrument

data CFixedRateBond'
type CFixedRateBond = ForeignPtr CFixedRateBond'
type FixedRateBond = GenBond CFixedRateBond
foreign import ccall unsafe "ql.h &qlFreeFixedRateBond" qlFreeFixedRateBond :: FinalizerPtr CFixedRateBond'
instance Finalizable CFixedRateBond' where finalize = qlFreeFixedRateBond
foreign import ccall "ql.h qlFixedRateBondAsBond" qlFixedRateBondAsBond :: Ptr CFixedRateBond' -> IO (Ptr CBond')
instance Upcastable CFixedRateBond' where {type Base CFixedRateBond' = CBond'; upcast = qlFixedRateBondAsBond}
peekFixedRateBond :: Ptr CFixedRateBond' -> IO FixedRateBond
peekFixedRateBond = peekGenBond
withFixedRateBond :: FixedRateBond -> (Ptr CFixedRateBond' -> IO b) -> IO b
withFixedRateBond = withForeignPtr . _ptr . peel . getInstrument

data CCallableBond'
type CCallableBond = ForeignPtr CCallableBond'
type CallableBond = GenBond CCallableBond
foreign import ccall unsafe "ql.h &qlFreeCallableBond" qlFreeCallableBond :: FinalizerPtr CCallableBond'
instance Finalizable CCallableBond' where finalize = qlFreeCallableBond
foreign import ccall "ql.h qlCallableBondAsBond" qlCallableBondAsBond :: Ptr CCallableBond' -> IO (Ptr CBond')
instance Upcastable CCallableBond' where {type Base CCallableBond' = CBond'; upcast = qlCallableBondAsBond}
peekCallableBond :: Ptr CCallableBond' -> IO CallableBond
peekCallableBond = peekGenBond
withCallableBond :: CallableBond -> (Ptr CCallableBond' -> IO b) -> IO b
withCallableBond = withForeignPtr . _ptr . peel . getInstrument

data CVanillaSwap'
type CVanillaSwap = ForeignPtr CVanillaSwap'
type VanillaSwap = GenSwap CVanillaSwap
foreign import ccall unsafe "ql.h &qlFreeVanillaSwap" qlFreeVanillaSwap :: FinalizerPtr CVanillaSwap'
instance Finalizable CVanillaSwap' where finalize = qlFreeVanillaSwap
foreign import ccall "ql.h qlVanillaSwapAsSwap" qlVanillaSwapAsSwap :: Ptr CVanillaSwap' -> IO (Ptr CSwap')
instance Upcastable CVanillaSwap' where {type Base CVanillaSwap' = CSwap'; upcast = qlVanillaSwapAsSwap}
peekVanillaSwap :: Ptr CVanillaSwap' -> IO VanillaSwap
peekVanillaSwap = peekGenSwap
withVanillaSwap :: VanillaSwap -> (Ptr CVanillaSwap' -> IO b) -> IO b
withVanillaSwap = withForeignPtr . _ptr . peel . getInstrument

data CAssetSwap'
type CAssetSwap = ForeignPtr CAssetSwap'
type AssetSwap = GenSwap CAssetSwap
foreign import ccall unsafe "ql.h &qlFreeAssetSwap" qlFreeAssetSwap :: FinalizerPtr CAssetSwap'
instance Finalizable CAssetSwap' where finalize = qlFreeAssetSwap
foreign import ccall "ql.h qlAssetSwapAsSwap" qlAssetSwapAsSwap :: Ptr CAssetSwap' -> IO (Ptr CSwap')
instance Upcastable CAssetSwap' where {type Base CAssetSwap' = CSwap'; upcast = qlAssetSwapAsSwap}
peekAssetSwap :: Ptr CAssetSwap' -> IO AssetSwap
peekAssetSwap = peekGenSwap
withAssetSwap :: AssetSwap -> (Ptr CAssetSwap' -> IO b) -> IO b
withAssetSwap = withForeignPtr . _ptr . peel . getInstrument

data CBMASwap'
type CBMASwap = ForeignPtr CBMASwap'
type BMASwap = GenSwap CBMASwap
foreign import ccall unsafe "ql.h &qlFreeBMASwap" qlFreeBMASwap :: FinalizerPtr CBMASwap'
instance Finalizable CBMASwap' where finalize = qlFreeBMASwap
foreign import ccall "ql.h qlBMASwapAsSwap" qlBMASwapAsSwap :: Ptr CBMASwap' -> IO (Ptr CSwap')
instance Upcastable CBMASwap' where {type Base CBMASwap' = CSwap'; upcast = qlBMASwapAsSwap}
peekBMASwap :: Ptr CBMASwap' -> IO BMASwap
peekBMASwap = peekGenSwap
withBMASwap :: BMASwap -> (Ptr CBMASwap' -> IO b) -> IO b
withBMASwap = withForeignPtr . _ptr . peel . getInstrument

data COvernightIndexedSwap'
type COvernightIndexedSwap = ForeignPtr COvernightIndexedSwap'
type OvernightIndexedSwap = GenSwap COvernightIndexedSwap
foreign import ccall unsafe "ql.h &qlFreeOvernightIndexedSwap" qlFreeOvernightIndexedSwap :: FinalizerPtr COvernightIndexedSwap'
instance Finalizable COvernightIndexedSwap' where finalize = qlFreeOvernightIndexedSwap
foreign import ccall "ql.h qlOvernightIndexedSwapAsSwap" qlOvernightIndexedSwapAsSwap :: Ptr COvernightIndexedSwap' -> IO (Ptr CSwap')
instance Upcastable COvernightIndexedSwap' where {type Base COvernightIndexedSwap' = CSwap'; upcast = qlOvernightIndexedSwapAsSwap}
peekOvernightIndexedSwap :: Ptr COvernightIndexedSwap' -> IO OvernightIndexedSwap
peekOvernightIndexedSwap = peekGenSwap
withOvernightIndexedSwap :: OvernightIndexedSwap -> (Ptr COvernightIndexedSwap' -> IO b) -> IO b
withOvernightIndexedSwap = withForeignPtr . _ptr . peel . getInstrument

data CCdsOption'
type CCdsOption = ForeignPtr CCdsOption'
type CdsOption = GenOption CCdsOption
foreign import ccall unsafe "ql.h &qlFreeCdsOption" qlFreeCdsOption :: FinalizerPtr CCdsOption'
instance Finalizable CCdsOption' where finalize = qlFreeCdsOption
foreign import ccall "ql.h qlCdsOptionAsOption" qlCdsOptionAsOption :: Ptr CCdsOption' -> IO (Ptr COption')
instance Upcastable CCdsOption' where {type Base CCdsOption' = COption'; upcast = qlCdsOptionAsOption}
peekCdsOption :: Ptr CCdsOption' -> IO CdsOption
peekCdsOption = peekGenOption
withCdsOption :: CdsOption -> (Ptr CCdsOption' -> IO b) -> IO b
withCdsOption = withForeignPtr . _ptr . peel . getInstrument

data CQuantoBarrierOption'
type CQuantoBarrierOption = ForeignPtr CQuantoBarrierOption'
type QuantoBarrierOption = GenOption CQuantoBarrierOption
foreign import ccall unsafe "ql.h &qlFreeQuantoBarrierOption" qlFreeQuantoBarrierOption :: FinalizerPtr CQuantoBarrierOption'
instance Finalizable CQuantoBarrierOption' where finalize = qlFreeQuantoBarrierOption
foreign import ccall "ql.h qlQuantoBarrierOptionAsOption" qlQuantoBarrierOptionAsOption :: Ptr CQuantoBarrierOption' -> IO (Ptr COption')
instance Upcastable CQuantoBarrierOption' where {type Base CQuantoBarrierOption' = COption'; upcast = qlQuantoBarrierOptionAsOption}
peekQuantoBarrierOption :: Ptr CQuantoBarrierOption' -> IO QuantoBarrierOption
peekQuantoBarrierOption = peekGenOption
withQuantoBarrierOption :: QuantoBarrierOption -> (Ptr CQuantoBarrierOption' -> IO b) -> IO b
withQuantoBarrierOption = withForeignPtr . _ptr . peel . getInstrument

data CQuantoForwardVanillaOption'
type CQuantoForwardVanillaOption = ForeignPtr CQuantoForwardVanillaOption'
type QuantoForwardVanillaOption = GenOption CQuantoForwardVanillaOption
foreign import ccall unsafe "ql.h &qlFreeQuantoForwardVanillaOption" qlFreeQuantoForwardVanillaOption :: FinalizerPtr CQuantoForwardVanillaOption'
instance Finalizable CQuantoForwardVanillaOption' where finalize = qlFreeQuantoForwardVanillaOption
foreign import ccall "ql.h qlQuantoForwardVanillaOptionAsOption" qlQuantoForwardVanillaOptionAsOption :: Ptr CQuantoForwardVanillaOption' -> IO (Ptr COption')
instance Upcastable CQuantoForwardVanillaOption' where {type Base CQuantoForwardVanillaOption' = COption'; upcast = qlQuantoForwardVanillaOptionAsOption}
peekQuantoForwardVanillaOption :: Ptr CQuantoForwardVanillaOption' -> IO QuantoForwardVanillaOption
peekQuantoForwardVanillaOption = peekGenOption
withQuantoForwardVanillaOption :: QuantoForwardVanillaOption -> (Ptr CQuantoForwardVanillaOption' -> IO b) -> IO b
withQuantoForwardVanillaOption = withForeignPtr . _ptr . peel . getInstrument

data CSwaption'
type CSwaption = ForeignPtr CSwaption'
type Swaption = GenOption CSwaption
foreign import ccall unsafe "ql.h &qlFreeSwaption" qlFreeSwaption :: FinalizerPtr CSwaption'
instance Finalizable CSwaption' where finalize = qlFreeSwaption
foreign import ccall "ql.h qlSwaptionAsOption" qlSwaptionAsOption :: Ptr CSwaption' -> IO (Ptr COption')
instance Upcastable CSwaption' where {type Base CSwaption' = COption'; upcast = qlSwaptionAsOption}
peekSwaption :: Ptr CSwaption' -> IO Swaption
peekSwaption = peekGenOption
withSwaption :: Swaption -> (Ptr CSwaption' -> IO b) -> IO b
withSwaption = withForeignPtr . _ptr . peel . getInstrument

data CMultiAssetOption'
data CMargrabeOption'
type GenMultiAssetOption a = GenOption (AnyOf CMultiAssetOption' a)
type CMultiAssetOption = ForeignPtr CMultiAssetOption'
type MultiAssetOption = GenMultiAssetOption CMultiAssetOption
type CMargrabeOption = ForeignPtr CMargrabeOption'
type MargrabeOption = GenMultiAssetOption CMargrabeOption
foreign import ccall unsafe "ql.h &qlFreeMultiAssetOption" qlFreeMultiAssetOption :: FinalizerPtr CMultiAssetOption'
foreign import ccall unsafe "ql.h &qlFreeMargrabeOption" qlFreeMargrabeOption :: FinalizerPtr CMargrabeOption'
instance Finalizable CMultiAssetOption' where finalize = qlFreeMultiAssetOption
instance Finalizable CMargrabeOption' where finalize = qlFreeMargrabeOption
foreign import ccall "ql.h qlMultiAssetOptionAsOption" qlMultiAssetOptionAsOption :: Ptr CMultiAssetOption' -> IO (Ptr COption')
foreign import ccall "ql.h qlMargrabeOptionAsMultiAssetOption" qlMargrabeOptionAsMultiAssetOption :: Ptr CMargrabeOption' -> IO (Ptr CMultiAssetOption')
instance Upcastable CMultiAssetOption' where {type Base CMultiAssetOption' = COption'; upcast = qlMultiAssetOptionAsOption}
instance Upcastable CMargrabeOption' where {type Base CMargrabeOption' = CMultiAssetOption'; upcast = qlMargrabeOptionAsMultiAssetOption}
asMultiAssetOption :: GenMultiAssetOption a -> IO MultiAssetOption
asMultiAssetOption = transferGenForeignPtr peekMultiAssetOption . peel . peel . getInstrument
peekMultiAssetOption :: Ptr CMultiAssetOption' -> IO MultiAssetOption
peekMultiAssetOption = newCastForeignPtr >=> newGenMultiAssetOption
withMultiAssetOption :: GenMultiAssetOption a -> (Ptr CMultiAssetOption' -> IO b) -> IO b
withMultiAssetOption = withGenForeignPtr . peel . peel . getInstrument
newGenMultiAssetOption :: GenForeignPtr a CMultiAssetOption' -> IO (GenMultiAssetOption a)
newGenMultiAssetOption = pure . GenInstrument . newAnyOf . newAnyOf

peekMargrabeOption :: Ptr CMargrabeOption' -> IO MargrabeOption
peekMargrabeOption = newGenForeignPtr >=> newGenMultiAssetOption
withMargrabeOption :: MargrabeOption -> (Ptr CMargrabeOption' -> IO b) -> IO b
withMargrabeOption = withForeignPtr . _ptr . peel . peel . getInstrument

data COneAssetOption'
type GenOneAssetOption a = GenOption (AnyOf COneAssetOption' a)
type COneAssetOption = ForeignPtr COneAssetOption'
type OneAssetOption = GenOneAssetOption COneAssetOption
foreign import ccall unsafe "ql.h &qlFreeOneAssetOption" qlFreeOneAssetOption :: FinalizerPtr COneAssetOption'
instance Finalizable COneAssetOption' where finalize = qlFreeOneAssetOption
foreign import ccall "ql.h qlOneAssetOptionAsOption" qlOneAssetOptionAsOption :: Ptr COneAssetOption' -> IO (Ptr COption')
instance Upcastable COneAssetOption' where {type Base COneAssetOption' = COption'; upcast = qlOneAssetOptionAsOption}
asOneAssetOption :: GenOneAssetOption a -> IO OneAssetOption
asOneAssetOption = transferGenForeignPtr peekOneAssetOption . peel . peel . getInstrument
peekOneAssetOption :: Ptr COneAssetOption' -> IO OneAssetOption
peekOneAssetOption = newCastForeignPtr >=> newGenOneAssetOption
withOneAssetOption :: GenOneAssetOption a -> (Ptr COneAssetOption' -> IO b) -> IO b
withOneAssetOption = withGenForeignPtr . peel . peel . getInstrument
newGenOneAssetOption :: GenForeignPtr a COneAssetOption' -> IO (GenOneAssetOption a)
newGenOneAssetOption = pure . GenInstrument . newAnyOf . newAnyOf

data CBarrierOption'
type CBarrierOption = ForeignPtr CBarrierOption'
type BarrierOption = GenOneAssetOption CBarrierOption
foreign import ccall unsafe "ql.h &qlFreeBarrierOption" qlFreeBarrierOption :: FinalizerPtr CBarrierOption'
instance Finalizable CBarrierOption' where finalize = qlFreeBarrierOption
foreign import ccall "ql.h qlBarrierOptionAsOneAssetOption" qlBarrierOptionAsOneAssetOption :: Ptr CBarrierOption' -> IO (Ptr COneAssetOption')
instance Upcastable CBarrierOption' where {type Base CBarrierOption' = COneAssetOption'; upcast = qlBarrierOptionAsOneAssetOption}
peekBarrierOption :: Ptr CBarrierOption' -> IO BarrierOption
peekBarrierOption = newGenForeignPtr >=> newGenOneAssetOption
withBarrierOption :: BarrierOption -> (Ptr CBarrierOption' -> IO b) -> IO b
withBarrierOption = withForeignPtr . _ptr . peel . peel . getInstrument

data CForwardVanillaOption'
type CForwardVanillaOption = ForeignPtr CForwardVanillaOption'
type ForwardVanillaOption = GenOneAssetOption CForwardVanillaOption
foreign import ccall unsafe "ql.h &qlFreeForwardVanillaOption" qlFreeForwardVanillaOption :: FinalizerPtr CForwardVanillaOption'
instance Finalizable CForwardVanillaOption' where finalize = qlFreeForwardVanillaOption
foreign import ccall "ql.h qlForwardVanillaOptionAsOneAssetOption" qlForwardVanillaOptionAsOneAssetOption :: Ptr CForwardVanillaOption' -> IO (Ptr COneAssetOption')
instance Upcastable CForwardVanillaOption' where {type Base CForwardVanillaOption' = COneAssetOption'; upcast = qlForwardVanillaOptionAsOneAssetOption}
peekForwardVanillaOption :: Ptr CForwardVanillaOption' -> IO ForwardVanillaOption
peekForwardVanillaOption = newGenForeignPtr >=> newGenOneAssetOption
withForwardVanillaOption :: ForwardVanillaOption -> (Ptr CForwardVanillaOption' -> IO b) -> IO b
withForwardVanillaOption = withForeignPtr . _ptr . peel . peel . getInstrument

data CQuantoVanillaOption'
type CQuantoVanillaOption = ForeignPtr CQuantoVanillaOption'
type QuantoVanillaOption = GenOneAssetOption CQuantoVanillaOption
foreign import ccall unsafe "ql.h &qlFreeQuantoVanillaOption" qlFreeQuantoVanillaOption :: FinalizerPtr CQuantoVanillaOption'
instance Finalizable CQuantoVanillaOption' where finalize = qlFreeQuantoVanillaOption
foreign import ccall "ql.h qlQuantoVanillaOptionAsOneAssetOption" qlQuantoVanillaOptionAsOneAssetOption :: Ptr CQuantoVanillaOption' -> IO (Ptr COneAssetOption')
instance Upcastable CQuantoVanillaOption' where {type Base CQuantoVanillaOption' = COneAssetOption'; upcast = qlQuantoVanillaOptionAsOneAssetOption}
peekQuantoVanillaOption :: Ptr CQuantoVanillaOption' -> IO QuantoVanillaOption
peekQuantoVanillaOption = newGenForeignPtr >=> newGenOneAssetOption
withQuantoVanillaOption :: QuantoVanillaOption -> (Ptr CQuantoVanillaOption' -> IO b) -> IO b
withQuantoVanillaOption = withForeignPtr . _ptr . peel . peel . getInstrument

data CVanillaOption'
type CVanillaOption = ForeignPtr CVanillaOption'
type VanillaOption = GenOneAssetOption CVanillaOption
foreign import ccall unsafe "ql.h &qlFreeVanillaOption" qlFreeVanillaOption :: FinalizerPtr CVanillaOption'
instance Finalizable CVanillaOption' where finalize = qlFreeVanillaOption
foreign import ccall "ql.h qlVanillaOptionAsOneAssetOption" qlVanillaOptionAsOneAssetOption :: Ptr CVanillaOption' -> IO (Ptr COneAssetOption')
instance Upcastable CVanillaOption' where {type Base CVanillaOption' = COneAssetOption'; upcast = qlVanillaOptionAsOneAssetOption}
peekVanillaOption :: Ptr CVanillaOption' -> IO VanillaOption
peekVanillaOption = newGenForeignPtr >=> newGenOneAssetOption
withVanillaOption :: VanillaOption -> (Ptr CVanillaOption' -> IO b) -> IO b
withVanillaOption = withForeignPtr . _ptr . peel . peel . getInstrument

withInstrumentArray :: [GenInstrument a] -> ((CUInt, Ptr (Ptr CInstrument')) -> IO b) -> IO b
withInstrumentArray = withGenArray withInstrument

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
