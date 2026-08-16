{-# LANGUAGE RankNTypes, TypeFamilies, TypeOperators, FlexibleContexts, FlexibleInstances #-}
module QuantLib.Internal.Type where
import Foreign.Ptr(Ptr, nullPtr)
import Foreign.ForeignPtr(ForeignPtr, FinalizerPtr, newForeignPtr, withForeignPtr)
import Foreign.C.Types(CUInt, CInt, CDouble)
import Foreign.C.String(CString)
import Foreign.Marshal.Array(withArray)
import Foreign.Marshal.Utils(withMany)
import Foreign.Storable(peek)

import Control.Monad((>=>))
import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Internal(peekDynString, preArray, peekDayArray)
import Control.Exception (finally, bracket, mask)

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
-- The name of a QuantLib object is fixed for its lifetime, so reading it through
-- unsafePerformIO is safe; NOINLINE keeps GHC from duplicating or floating the C++
-- call, matching how QuantLib.Settings guards its own unsafePerformIO sites.
showStandalone :: (Ptr a -> IO CString) -> Standalone a -> String
showStandalone f x = unsafePerformIO $ withStandalone x (f >=> peekDynString)
{-# NOINLINE showStandalone #-}

-- On `safe' vs `unsafe' imports, file-wide (this was an open TODO; it is settled):
--   * The `&qlFreeX' finalizer imports below take a symbol *address*, not a call, so their
--     `unsafe' annotation is inert. The call that matters is `callFinalizer' above, plus
--     whatever the GC runs; both are safe.
--   * Everything that runs QuantLib logic stays `safe'. Under the non-threaded RTS an
--     `unsafe' call blocks GC and the scheduler for its whole duration, and pricing or
--     bootstrapping is unbounded.
--   * The qlXAsY upcast shims are the one legitimate `unsafe' candidate -- bare
--     `ret(new QlY(*arg(o)))', no callback into Haskell, bounded work -- but they are
--     already dominated by the QuantLib call they precede, so leave them `safe' absent a
--     measurement; a per-shim rule would break the first time one grows logic.
-- If a Haskell callback is ever passed into C++, every import on that path must be `safe'.
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
-- Equality by name, here and for the Currency/Region/DayCounter/Schedule instances
-- below. This is deliberate: it is how QuantLib itself compares these types.
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
peekMaybeCurrency :: Ptr CCurrency -> IO (Maybe Currency)
peekMaybeCurrency p
  | p == nullPtr = pure Nothing
  | otherwise = Just <$> peekCurrency p
-- |Peek a 'Currency' out of a @Currency**@ out-parameter (as opposed to 'peekCurrency', which
-- peeks it directly out of a @Currency*@ primary return).
peekCurrencyPtr :: Ptr (Ptr CCurrency) -> IO Currency
peekCurrencyPtr = peek >=> peekCurrency
-- |Split a @(Double, Currency)@ cash amount (QuantLib's 'Money', per the @Period@-as-tuple
-- convention) into the @(double, Currency*)@ pair of C arguments it marshals to, for use with
-- the c2hs @&@ splitter -- the input-direction counterpart of 'peekCurrencyPtr'.
withMoney :: (Double, Currency) -> ((CDouble, Ptr CCurrency) -> IO b) -> IO b
withMoney (amount, ccy) f = withCurrency ccy (\p -> f (realToFrac amount, p))
foreign import ccall safe "ql.h qlCurrencyName" qlCurrencyName :: Ptr CCurrency -> IO CString
instance Show Currency where show x = showStandalone qlCurrencyName (getCCurrency x)
instance Eq Currency where x == y = show x == show y

data CExchangeRate
newtype ExchangeRate = ExchangeRate {getCExchangeRate :: Standalone CExchangeRate}
foreign import ccall unsafe "ql.h &qlFreeExchangeRate" qlFreeExchangeRate :: FinalizerPtr CExchangeRate
instance Finalizable CExchangeRate where finalize = qlFreeExchangeRate
peekExchangeRate :: Ptr CExchangeRate -> IO ExchangeRate
peekExchangeRate = ExchangeRate <.> peekStandalone
withExchangeRate :: ExchangeRate -> (Ptr CExchangeRate -> IO b) -> IO b
withExchangeRate = withStandalone . getCExchangeRate

data CRegion
newtype Region = Region {getCRegion :: Standalone CRegion}
foreign import ccall unsafe "ql.h &qlFreeRegion" qlFreeRegion :: FinalizerPtr CRegion
instance Finalizable CRegion where finalize = qlFreeRegion
peekRegion :: Ptr CRegion -> IO Region
peekRegion = Region <.> peekStandalone
withRegion :: Region -> (Ptr CRegion -> IO b) -> IO b
withRegion = withStandalone . getCRegion
foreign import ccall safe "ql.h qlRegionName" qlRegionName :: Ptr CRegion -> IO CString
instance Show Region where show x = showStandalone qlRegionName (getCRegion x)
instance Eq Region where x == y = show x == show y

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
foreign import ccall safe "ql.h qlScheduleDates" qlScheduleDates :: Ptr CSchedule -> Ptr CUInt -> Ptr (Ptr CInt) -> IO ()
showSchedule :: Schedule -> String
showSchedule x = unsafePerformIO $ withSchedule x $ \p ->
  show <$> preArray (\(cp, ap) -> qlScheduleDates p cp ap >> peekDayArray cp ap)
{-# NOINLINE showSchedule #-}

instance Show Schedule where
  show = showSchedule
instance Eq Schedule where
  x == y = show x == show y

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

data CFdmQuantoHelper
newtype FdmQuantoHelper = FdmQuantoHelper {getCFdmQuantoHelper :: Standalone CFdmQuantoHelper}
foreign import ccall unsafe "ql.h &qlFreeFdmQuantoHelper" qlFreeFdmQuantoHelper :: FinalizerPtr CFdmQuantoHelper
instance Finalizable CFdmQuantoHelper where finalize = qlFreeFdmQuantoHelper
peekFdmQuantoHelper :: Ptr CFdmQuantoHelper -> IO FdmQuantoHelper
peekFdmQuantoHelper = FdmQuantoHelper <.> peekStandalone
withFdmQuantoHelper :: FdmQuantoHelper -> (Ptr CFdmQuantoHelper -> IO b) -> IO b
withFdmQuantoHelper = withStandalone . getCFdmQuantoHelper
withMaybeFdmQuantoHelper :: Maybe FdmQuantoHelper -> (Ptr CFdmQuantoHelper -> IO b) -> IO b
withMaybeFdmQuantoHelper = withMaybeStandalone . (getCFdmQuantoHelper <$>)

data CZeroInflationCashFlow
newtype ZeroInflationCashFlow = ZeroInflationCashFlow {getCZeroInflationCashFlow :: Standalone CZeroInflationCashFlow}
foreign import ccall unsafe "ql.h &qlFreeZeroInflationCashFlow" qlFreeZeroInflationCashFlow :: FinalizerPtr CZeroInflationCashFlow
instance Finalizable CZeroInflationCashFlow where finalize = qlFreeZeroInflationCashFlow
peekZeroInflationCashFlow :: Ptr CZeroInflationCashFlow -> IO ZeroInflationCashFlow
peekZeroInflationCashFlow = ZeroInflationCashFlow <.> peekStandalone
withZeroInflationCashFlow :: ZeroInflationCashFlow -> (Ptr CZeroInflationCashFlow -> IO b) -> IO b
withZeroInflationCashFlow = withStandalone . getCZeroInflationCashFlow

data CCPICashFlow
newtype CPICashFlow = CPICashFlow {getCCPICashFlow :: Standalone CCPICashFlow}
foreign import ccall unsafe "ql.h &qlFreeCPICashFlow" qlFreeCPICashFlow :: FinalizerPtr CCPICashFlow
instance Finalizable CCPICashFlow where finalize = qlFreeCPICashFlow
peekCPICashFlow :: Ptr CCPICashFlow -> IO CPICashFlow
peekCPICashFlow = CPICashFlow <.> peekStandalone
withCPICashFlow :: CPICashFlow -> (Ptr CCPICashFlow -> IO b) -> IO b
withCPICashFlow = withStandalone . getCCPICashFlow

data CEquityCashFlow
newtype EquityCashFlow = EquityCashFlow {getCEquityCashFlow :: Standalone CEquityCashFlow}
foreign import ccall unsafe "ql.h &qlFreeEquityCashFlow" qlFreeEquityCashFlow :: FinalizerPtr CEquityCashFlow
instance Finalizable CEquityCashFlow where finalize = qlFreeEquityCashFlow
peekEquityCashFlow :: Ptr CEquityCashFlow -> IO EquityCashFlow
peekEquityCashFlow = EquityCashFlow <.> peekStandalone
withEquityCashFlow :: EquityCashFlow -> (Ptr CEquityCashFlow -> IO b) -> IO b
withEquityCashFlow = withStandalone . getCEquityCashFlow

data CSmileSection
newtype SmileSection = SmileSection {getCSmileSection :: Standalone CSmileSection}
foreign import ccall unsafe "ql.h &qlFreeSmileSection" qlFreeSmileSection :: FinalizerPtr CSmileSection
instance Finalizable CSmileSection where finalize = qlFreeSmileSection
peekSmileSection :: Ptr CSmileSection -> IO SmileSection
peekSmileSection = SmileSection <.> peekStandalone
withSmileSection :: SmileSection -> (Ptr CSmileSection -> IO b) -> IO b
withSmileSection = withStandalone . getCSmileSection

-- |a dedicated leaf, not a downcast target: 'QuantLib.TermStructure.Volatility.sabrInterpolatedSmileSection'
-- returns this concrete type directly so its alpha\/beta\/nu\/rho\/etc getters need no
-- runtime cast to reach them (see CLAUDE.md's "avoid dynamic_cast unless upstream forces it"
-- rule). Use 'QuantLib.TermStructure.Volatility.sabrInterpolatedSmileSectionAsSmileSection' to
-- pass one into anything that wants the generic 'SmileSection' interface.
data CSabrInterpolatedSmileSection
newtype SabrInterpolatedSmileSection = SabrInterpolatedSmileSection {getCSabrInterpolatedSmileSection :: Standalone CSabrInterpolatedSmileSection}
foreign import ccall unsafe "ql.h &qlFreeSabrInterpolatedSmileSection" qlFreeSabrInterpolatedSmileSection :: FinalizerPtr CSabrInterpolatedSmileSection
instance Finalizable CSabrInterpolatedSmileSection where finalize = qlFreeSabrInterpolatedSmileSection
peekSabrInterpolatedSmileSection :: Ptr CSabrInterpolatedSmileSection -> IO SabrInterpolatedSmileSection
peekSabrInterpolatedSmileSection = SabrInterpolatedSmileSection <.> peekStandalone
withSabrInterpolatedSmileSection :: SabrInterpolatedSmileSection -> (Ptr CSabrInterpolatedSmileSection -> IO b) -> IO b
withSabrInterpolatedSmileSection = withStandalone . getCSabrInterpolatedSmileSection

data CPricingEngine
newtype PricingEngine = PricingEngine {getCPricingEngine :: Standalone CPricingEngine}
foreign import ccall unsafe "ql.h &qlFreePricingEngine" qlFreePricingEngine :: FinalizerPtr CPricingEngine
instance Finalizable CPricingEngine where finalize = qlFreePricingEngine
peekPricingEngine :: Ptr CPricingEngine -> IO PricingEngine
peekPricingEngine = PricingEngine <.> peekStandalone
withPricingEngine :: PricingEngine -> (Ptr CPricingEngine -> IO b) -> IO b
withPricingEngine = withStandalone . getCPricingEngine

data CBlackDeltaCalculator
newtype BlackDeltaCalculator = BlackDeltaCalculator {getCBlackDeltaCalculator :: Standalone CBlackDeltaCalculator}
foreign import ccall unsafe "ql.h &qlFreeBlackDeltaCalculator" qlFreeBlackDeltaCalculator :: FinalizerPtr CBlackDeltaCalculator
instance Finalizable CBlackDeltaCalculator where finalize = qlFreeBlackDeltaCalculator
peekBlackDeltaCalculator :: Ptr CBlackDeltaCalculator -> IO BlackDeltaCalculator
peekBlackDeltaCalculator = BlackDeltaCalculator <.> peekStandalone
withBlackDeltaCalculator :: BlackDeltaCalculator -> (Ptr CBlackDeltaCalculator -> IO b) -> IO b
withBlackDeltaCalculator = withStandalone . getCBlackDeltaCalculator

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
withMaybeFloatingRateCouponPricer :: Maybe FloatingRateCouponPricer -> (Ptr CFloatingRateCouponPricer -> IO b) -> IO b
withMaybeFloatingRateCouponPricer = maybe ($ nullPtr) withFloatingRateCouponPricer

data CEquityCashFlowPricer
newtype EquityCashFlowPricer = EquityCashFlowPricer {getCEquityCashFlowPricer :: Standalone CEquityCashFlowPricer}
foreign import ccall unsafe "ql.h &qlFreeEquityCashFlowPricer" qlFreeEquityCashFlowPricer :: FinalizerPtr CEquityCashFlowPricer
instance Finalizable CEquityCashFlowPricer where finalize = qlFreeEquityCashFlowPricer
peekEquityCashFlowPricer :: Ptr CEquityCashFlowPricer -> IO EquityCashFlowPricer
peekEquityCashFlowPricer = EquityCashFlowPricer <.> peekStandalone
withEquityCashFlowPricer :: EquityCashFlowPricer -> (Ptr CEquityCashFlowPricer -> IO b) -> IO b
withEquityCashFlowPricer = withStandalone . getCEquityCashFlowPricer

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

data CZeroCouponInflationSwapHelper
newtype ZeroCouponInflationSwapHelper = ZeroCouponInflationSwapHelper {getCZeroCouponInflationSwapHelper :: Standalone CZeroCouponInflationSwapHelper}
foreign import ccall unsafe "ql.h &qlFreeZeroCouponInflationSwapHelper" qlFreeZeroCouponInflationSwapHelper :: FinalizerPtr CZeroCouponInflationSwapHelper
instance Finalizable CZeroCouponInflationSwapHelper where finalize = qlFreeZeroCouponInflationSwapHelper
peekZeroCouponInflationSwapHelper :: Ptr CZeroCouponInflationSwapHelper -> IO ZeroCouponInflationSwapHelper
peekZeroCouponInflationSwapHelper = ZeroCouponInflationSwapHelper <.> peekStandalone
withZeroCouponInflationSwapHelper :: ZeroCouponInflationSwapHelper -> (Ptr CZeroCouponInflationSwapHelper -> IO b) -> IO b
withZeroCouponInflationSwapHelper = withStandalone . getCZeroCouponInflationSwapHelper
withZeroCouponInflationSwapHelperArray :: [ZeroCouponInflationSwapHelper] -> ((CUInt, Ptr (Ptr CZeroCouponInflationSwapHelper)) -> IO b) -> IO b
withZeroCouponInflationSwapHelperArray = withStandaloneArray getCZeroCouponInflationSwapHelper

data CYearOnYearInflationSwapHelper
newtype YearOnYearInflationSwapHelper = YearOnYearInflationSwapHelper {getCYearOnYearInflationSwapHelper :: Standalone CYearOnYearInflationSwapHelper}
foreign import ccall unsafe "ql.h &qlFreeYearOnYearInflationSwapHelper" qlFreeYearOnYearInflationSwapHelper :: FinalizerPtr CYearOnYearInflationSwapHelper
instance Finalizable CYearOnYearInflationSwapHelper where finalize = qlFreeYearOnYearInflationSwapHelper
peekYearOnYearInflationSwapHelper :: Ptr CYearOnYearInflationSwapHelper -> IO YearOnYearInflationSwapHelper
peekYearOnYearInflationSwapHelper = YearOnYearInflationSwapHelper <.> peekStandalone
withYearOnYearInflationSwapHelper :: YearOnYearInflationSwapHelper -> (Ptr CYearOnYearInflationSwapHelper -> IO b) -> IO b
withYearOnYearInflationSwapHelper = withStandalone . getCYearOnYearInflationSwapHelper
withYearOnYearInflationSwapHelperArray :: [YearOnYearInflationSwapHelper] -> ((CUInt, Ptr (Ptr CYearOnYearInflationSwapHelper)) -> IO b) -> IO b
withYearOnYearInflationSwapHelperArray = withStandaloneArray getCYearOnYearInflationSwapHelper

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

-- MultiCurve is enable_shared_from_this upstream ("This must be a shared pointer") and builds a
-- set of curves that form a genuine dependency cycle; bound as a standalone leaf, not part of
-- the TermStructure hierarchy (it isn't a TermStructure itself), mirroring PricingEngine above.
data CMultiCurve
newtype MultiCurve = MultiCurve {getCMultiCurve :: Standalone CMultiCurve}
foreign import ccall unsafe "ql.h &qlFreeMultiCurve" qlFreeMultiCurve :: FinalizerPtr CMultiCurve
instance Finalizable CMultiCurve where finalize = qlFreeMultiCurve
peekMultiCurve :: Ptr CMultiCurve -> IO MultiCurve
peekMultiCurve = MultiCurve <.> peekStandalone
withMultiCurve :: MultiCurve -> (Ptr CMultiCurve -> IO b) -> IO b
withMultiCurve = withStandalone . getCMultiCurve

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
--
-- Each hierarchy root below carries a haddock tree listing every member. Notation:
--   indentation  parent/child
--   `X*'         abstract *here*: hasquant binds no constructor returning an X, you only
--                obtain one by upcasting. This is not the same as C++ abstractness and
--                cannot be derived from it -- Option and Swap are concrete classes
--                upstream but unconstructible here, while Quote/Index/TermStructure are
--                pure-virtual upstream yet routinely returned by bindings. Marks are
--                added where established; an unmarked node is not a claim of the opposite.
--   `X + Y'      X also reaches secondary interface Y, via the standalone qlXAsY shim and
--                the hand-written Y ADT (see CAffineModel' below), not via Upcastable.
--   X (CFoo')    X's C type, given only where it is not the expected C<X>'.
-- Payoff and Exercise are documented in the files that define them, not here.
-- the original pointer to `a' with a way to marshal it to `b'
-- The access/free pair IS derivable from the structure of `a' (each nested AnyOf layer is
-- one upcast; the innermost ForeignPtr is identity or one upcast). It stays a stored
-- dictionary because the alternative -- an `Access a b' class -- becomes a constraint at
-- every polymorphic use site, and c2hs emits an explicit signature for every {#fun#}: 363
-- of 880 hooks take a polymorphic `GenX a' and would each need a hand-written context,
-- which would also leak into public API signatures. It buys no correctness -- the smart
-- constructors below are already pinned by their result types.
data GenForeignPtr a b = GenForeignPtr {
  ptr :: !a
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

-- `access' performs the upcast, which allocates a fresh handle that `mfree' must release, so
-- acquiring it and installing the handler have to be atomic -- `mask' covers the upcast
-- happening inside `access', and `restore' hands `f' back the caller's masking state. This
-- is `bracket' semantics (cf. `withUpcast' below) expressed around a continuation that
-- allocates internally. Nesting is fine: an inner level's `restore' only wraps the
-- continuation that contains the outer `restore', so `f' still runs unmasked.
withGenForeignPtr :: GenForeignPtr a b -> (Ptr b -> IO r) -> IO r
withGenForeignPtr (GenForeignPtr p access Nothing) f = access p f
withGenForeignPtr (GenForeignPtr p access (Just free)) f =
  mask $ \restore -> access p $ \bp -> restore (f bp) `finally` free bp

transferGenForeignPtr :: (Ptr b -> IO r) -> GenForeignPtr a b -> IO r
transferGenForeignPtr f (GenForeignPtr p access _) = access p f

withGenArray :: (a -> (Ptr c -> IO r) -> IO r) -> [a] -> ((CUInt, Ptr (Ptr c)) -> IO r) -> IO r
withGenArray m x f = withMany m x (`withArray` (\p -> f (fromIntegral $ length x, p)))

peel :: GenForeignPtr (AnyOf b a) c -> GenForeignPtr a b
peel = getAnyOf . ptr

-- | > Quote
-- >   SimpleQuote
-- >   DeltaVolQuote
-- >   RelinkableQuote
type Quote = GenQuote CQuote
data CQuote'
data CSimpleQuote'
data CDeltaVolQuote'
data CRelinkableQuote'
newtype GenQuote q = GenQuote {getQuote :: GenForeignPtr q CQuote'}
type CQuote = ForeignPtr CQuote'
type CSimpleQuote = ForeignPtr CSimpleQuote'
type SimpleQuote = GenQuote CSimpleQuote
type CDeltaVolQuote = ForeignPtr CDeltaVolQuote'
type DeltaVolQuote = GenQuote CDeltaVolQuote
type CRelinkableQuote = ForeignPtr CRelinkableQuote'
type RelinkableQuote = GenQuote CRelinkableQuote
foreign import ccall unsafe "ql.h &qlFreeQuote" qlFreeQuote :: FinalizerPtr CQuote'
foreign import ccall unsafe "ql.h &qlFreeSimpleQuote" qlFreeSimpleQuote :: FinalizerPtr CSimpleQuote'
foreign import ccall unsafe "ql.h &qlFreeDeltaVolQuote" qlFreeDeltaVolQuote :: FinalizerPtr CDeltaVolQuote'
foreign import ccall unsafe "ql.h &qlFreeRelinkableQuote" qlFreeRelinkableQuote :: FinalizerPtr CRelinkableQuote'
instance Finalizable CQuote' where finalize = qlFreeQuote
instance Finalizable CSimpleQuote' where finalize = qlFreeSimpleQuote
instance Finalizable CDeltaVolQuote' where finalize = qlFreeDeltaVolQuote
instance Finalizable CRelinkableQuote' where finalize = qlFreeRelinkableQuote
instance Upcastable CSimpleQuote' where {type Base CSimpleQuote' = CQuote'; upcast = qlSimpleQuoteAsQuote}
instance Upcastable CDeltaVolQuote' where {type Base CDeltaVolQuote' = CQuote'; upcast = qlDeltaVolQuoteAsQuote}
instance Upcastable CRelinkableQuote' where {type Base CRelinkableQuote' = CQuote'; upcast = qlRelinkableQuoteAsQuote}
foreign import ccall "ql.h qlSimpleQuoteAsQuote" qlSimpleQuoteAsQuote :: Ptr CSimpleQuote' -> IO (Ptr CQuote')
foreign import ccall "ql.h qlDeltaVolQuoteAsQuote" qlDeltaVolQuoteAsQuote :: Ptr CDeltaVolQuote' -> IO (Ptr CQuote')
foreign import ccall "ql.h qlRelinkableQuoteAsQuote" qlRelinkableQuoteAsQuote :: Ptr CRelinkableQuote' -> IO (Ptr CQuote')
-- Haskell does not allow function arguments like [forall q.GenQuote q]
-- let's at least provide a way to convert all quote classes to the most generic one
asQuote :: GenQuote q -> IO Quote
asQuote = transferGenForeignPtr peekQuote . getQuote
peekQuote :: Ptr CQuote' -> IO Quote
peekQuote = GenQuote <.> newCastForeignPtr
withQuote :: GenQuote q -> (Ptr CQuote' -> IO b) -> IO b
withQuote = withGenForeignPtr . getQuote
withGenQuote :: GenQuote (ForeignPtr q) -> (Ptr q -> IO b) -> IO b
withGenQuote = withForeignPtr . ptr . getQuote
peekSimpleQuote :: Ptr CSimpleQuote' -> IO SimpleQuote
peekSimpleQuote = GenQuote <.> newGenForeignPtr
peekDeltaVolQuote :: Ptr CDeltaVolQuote' -> IO DeltaVolQuote
peekDeltaVolQuote = GenQuote <.> newGenForeignPtr
peekRelinkableQuote :: Ptr CRelinkableQuote' -> IO RelinkableQuote
peekRelinkableQuote = GenQuote <.> newGenForeignPtr
withRelinkableQuote :: RelinkableQuote -> (Ptr CRelinkableQuote' -> IO b) -> IO b
withRelinkableQuote = withGenQuote
withMaybeQuote :: Maybe (GenQuote q) -> (Ptr CQuote' -> IO b) -> IO b
withMaybeQuote x f = maybe (f nullPtr) (`withQuote` f) x
withQuoteArray :: [GenQuote q] -> ((CUInt, Ptr (Ptr CQuote')) -> IO b) -> IO b
withQuoteArray = withGenArray withQuote
withQuoteArrayRaw :: [GenQuote q] -> (Ptr (Ptr CQuote') -> IO b) -> IO b
withQuoteArrayRaw x f = withMany withQuote x (`withArray` f)

-- PAYOFF/EXERCISE upcast targets used by QuantLib.Internal.Enum's Payoff/Exercise ADT dispatch
-- (the ADTs themselves stay in Enum.chs; only the pointer hierarchy plumbing lives here,
-- matching every other hierarchy in this module)
data CPayoff'
foreign import ccall unsafe "ql.h &qlFreePayoff" qlFreePayoff :: FinalizerPtr CPayoff'
instance Finalizable CPayoff' where finalize = qlFreePayoff

data CBasketPayoff'
foreign import ccall unsafe "ql.h &qlFreeBasketPayoff" qlFreeBasketPayoff :: FinalizerPtr CBasketPayoff'
instance Finalizable CBasketPayoff' where finalize = qlFreeBasketPayoff
instance Upcastable CBasketPayoff' where {type Base CBasketPayoff' = CPayoff'; upcast = qlBasketPayoffAsPayoff}
foreign import ccall "ql.h qlBasketPayoffAsPayoff" qlBasketPayoffAsPayoff :: Ptr CBasketPayoff' -> IO (Ptr CPayoff')

data CTypePayoff'
foreign import ccall unsafe "ql.h &qlFreeTypePayoff" qlFreeTypePayoff :: FinalizerPtr CTypePayoff'
instance Finalizable CTypePayoff' where finalize = qlFreeTypePayoff
instance Upcastable CTypePayoff' where {type Base CTypePayoff' = CPayoff'; upcast = qlTypePayoffAsPayoff}
foreign import ccall "ql.h qlTypePayoffAsPayoff" qlTypePayoffAsPayoff :: Ptr CTypePayoff' -> IO (Ptr CPayoff')

data CStrikedTypePayoff'
foreign import ccall unsafe "ql.h &qlFreeStrikedTypePayoff" qlFreeStrikedTypePayoff :: FinalizerPtr CStrikedTypePayoff'
instance Finalizable CStrikedTypePayoff' where finalize = qlFreeStrikedTypePayoff
instance Upcastable CStrikedTypePayoff' where {type Base CStrikedTypePayoff' = CTypePayoff'; upcast = qlStrikedTypePayoffAsTypePayoff}
foreign import ccall "ql.h qlStrikedTypePayoffAsTypePayoff" qlStrikedTypePayoffAsTypePayoff :: Ptr CStrikedTypePayoff' -> IO (Ptr CTypePayoff')

data CPercentageStrikePayoff'
foreign import ccall unsafe "ql.h &qlFreePercentageStrikePayoff" qlFreePercentageStrikePayoff :: FinalizerPtr CPercentageStrikePayoff'
instance Finalizable CPercentageStrikePayoff' where finalize = qlFreePercentageStrikePayoff
instance Upcastable CPercentageStrikePayoff' where {type Base CPercentageStrikePayoff' = CStrikedTypePayoff'; upcast = qlPercentageStrikePayoffAsStrikedTypePayoff}
foreign import ccall "ql.h qlPercentageStrikePayoffAsStrikedTypePayoff" qlPercentageStrikePayoffAsStrikedTypePayoff :: Ptr CPercentageStrikePayoff' -> IO (Ptr CStrikedTypePayoff')

data CPlainVanillaPayoff'
foreign import ccall unsafe "ql.h &qlFreePlainVanillaPayoff" qlFreePlainVanillaPayoff :: FinalizerPtr CPlainVanillaPayoff'
instance Finalizable CPlainVanillaPayoff' where finalize = qlFreePlainVanillaPayoff
instance Upcastable CPlainVanillaPayoff' where {type Base CPlainVanillaPayoff' = CStrikedTypePayoff'; upcast = qlPlainVanillaPayoffAsStrikedTypePayoff}
foreign import ccall "ql.h qlPlainVanillaPayoffAsStrikedTypePayoff" qlPlainVanillaPayoffAsStrikedTypePayoff :: Ptr CPlainVanillaPayoff' -> IO (Ptr CStrikedTypePayoff')

data CExercise'
foreign import ccall unsafe "ql.h &qlFreeExercise" qlFreeExercise :: FinalizerPtr CExercise'
instance Finalizable CExercise' where finalize = qlFreeExercise

data CAmericanExercise'
foreign import ccall unsafe "ql.h &qlFreeAmericanExercise" qlFreeAmericanExercise :: FinalizerPtr CAmericanExercise'
instance Finalizable CAmericanExercise' where finalize = qlFreeAmericanExercise
instance Upcastable CAmericanExercise' where {type Base CAmericanExercise' = CExercise'; upcast = qlAmericanExerciseAsExercise}
foreign import ccall "ql.h qlAmericanExerciseAsExercise" qlAmericanExerciseAsExercise :: Ptr CAmericanExercise' -> IO (Ptr CExercise')

data CEuropeanExercise'
foreign import ccall unsafe "ql.h &qlFreeEuropeanExercise" qlFreeEuropeanExercise :: FinalizerPtr CEuropeanExercise'
instance Finalizable CEuropeanExercise' where finalize = qlFreeEuropeanExercise
instance Upcastable CEuropeanExercise' where {type Base CEuropeanExercise' = CExercise'; upcast = qlEuropeanExerciseAsExercise}
foreign import ccall "ql.h qlEuropeanExerciseAsExercise" qlEuropeanExerciseAsExercise :: Ptr CEuropeanExercise' -> IO (Ptr CExercise')

data CBermudanExercise'
foreign import ccall unsafe "ql.h &qlFreeBermudanExercise" qlFreeBermudanExercise :: FinalizerPtr CBermudanExercise'
instance Finalizable CBermudanExercise' where finalize = qlFreeBermudanExercise
instance Upcastable CBermudanExercise' where {type Base CBermudanExercise' = CExercise'; upcast = qlBermudanExerciseAsExercise}
foreign import ccall "ql.h qlBermudanExerciseAsExercise" qlBermudanExerciseAsExercise :: Ptr CBermudanExercise' -> IO (Ptr CExercise')

data CSwingExercise'
foreign import ccall unsafe "ql.h &qlFreeSwingExercise" qlFreeSwingExercise :: FinalizerPtr CSwingExercise'
instance Finalizable CSwingExercise' where finalize = qlFreeSwingExercise
instance Upcastable CSwingExercise' where {type Base CSwingExercise' = CBermudanExercise'; upcast = qlSwingExerciseAsBermudanExercise}
foreign import ccall "ql.h qlSwingExerciseAsBermudanExercise" qlSwingExerciseAsBermudanExercise :: Ptr CSwingExercise' -> IO (Ptr CBermudanExercise')

data CLeg'
data CCouponLeg'
newtype GenLeg l = GenLeg {getLeg :: GenForeignPtr l CLeg'}
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
asLeg :: GenLeg l -> IO Leg
asLeg = transferGenForeignPtr peekLeg . getLeg
peekLeg :: Ptr CLeg' -> IO Leg
peekLeg = GenLeg <.> newCastForeignPtr
withLeg :: GenLeg l -> (Ptr CLeg' -> IO b) -> IO b
withLeg = withGenForeignPtr . getLeg
withLegArray :: [GenLeg l] -> ((CUInt, Ptr (Ptr CLeg')) -> IO b) -> IO b
withLegArray = withGenArray withLeg
withGenLeg :: GenLeg (ForeignPtr l) -> (Ptr l -> IO b) -> IO b
withGenLeg = withForeignPtr . ptr . getLeg
peekCouponLeg :: Ptr CCouponLeg' -> IO CouponLeg
peekCouponLeg = GenLeg <.> newGenForeignPtr

-- | > RateHelper
-- >   BondHelper
-- >   SwapRateHelper
-- >   OISRateHelper
type RateHelper = GenRateHelper CRateHelper
data CRateHelper'
newtype GenRateHelper rh = GenRateHelper {getRateHelper :: GenForeignPtr rh CRateHelper'}
type CRateHelper = ForeignPtr CRateHelper'
foreign import ccall unsafe "ql.h &qlFreeRateHelper" qlFreeRateHelper :: FinalizerPtr CRateHelper'
instance Finalizable CRateHelper' where finalize = qlFreeRateHelper
asRateHelper :: GenRateHelper rh -> IO RateHelper
asRateHelper = transferGenForeignPtr peekRateHelper . getRateHelper
peekRateHelper :: Ptr CRateHelper' -> IO RateHelper
peekRateHelper = GenRateHelper <.> newCastForeignPtr
withRateHelper :: GenRateHelper rh -> (Ptr CRateHelper' -> IO b) -> IO b
withRateHelper = withGenForeignPtr . getRateHelper
withGenRateHelper :: GenRateHelper (ForeignPtr rh) -> (Ptr rh -> IO b) -> IO b
withGenRateHelper = withForeignPtr . ptr . getRateHelper
withRateHelperArray :: [GenRateHelper rh] -> ((CUInt, Ptr (Ptr CRateHelper')) -> IO b) -> IO b
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

-- | > CalibrationHelper
-- >   BlackCalibrationHelper
type CalibrationHelper = GenCalibrationHelper CCalibrationHelper
data CCalibrationHelper'
data CBlackCalibrationHelper'
newtype GenCalibrationHelper ch = GenCalibrationHelper {getCalibrationHelper :: GenForeignPtr ch CCalibrationHelper'}
type CCalibrationHelper = ForeignPtr CCalibrationHelper'
type CBlackCalibrationHelper = ForeignPtr CBlackCalibrationHelper'
type BlackCalibrationHelper = GenCalibrationHelper CBlackCalibrationHelper
foreign import ccall unsafe "ql.h &qlFreeCalibrationHelper" qlFreeCalibrationHelper :: FinalizerPtr CCalibrationHelper'
foreign import ccall unsafe "ql.h &qlFreeBlackCalibrationHelper" qlFreeBlackCalibrationHelper :: FinalizerPtr CBlackCalibrationHelper'
instance Finalizable CCalibrationHelper' where finalize = qlFreeCalibrationHelper
instance Finalizable CBlackCalibrationHelper' where finalize = qlFreeBlackCalibrationHelper
foreign import ccall "ql.h qlBlackCalibrationHelperAsCalibrationHelper" qlBlackCalibrationHelperAsCalibrationHelper :: Ptr CBlackCalibrationHelper' -> IO (Ptr CCalibrationHelper')
instance Upcastable CBlackCalibrationHelper' where {type Base CBlackCalibrationHelper' = CCalibrationHelper'; upcast = qlBlackCalibrationHelperAsCalibrationHelper}
asCalibrationHelper :: GenCalibrationHelper ch -> IO CalibrationHelper
asCalibrationHelper = transferGenForeignPtr peekCalibrationHelper . getCalibrationHelper
peekCalibrationHelper :: Ptr CCalibrationHelper' -> IO CalibrationHelper
peekCalibrationHelper = GenCalibrationHelper <.> newCastForeignPtr
withCalibrationHelper :: GenCalibrationHelper ch -> (Ptr CCalibrationHelper' -> IO b) -> IO b
withCalibrationHelper = withGenForeignPtr . getCalibrationHelper
withGenCalibrationHelper :: GenCalibrationHelper (ForeignPtr ch) -> (Ptr ch -> IO b) -> IO b
withGenCalibrationHelper = withForeignPtr . ptr . getCalibrationHelper
peekBlackCalibrationHelper :: Ptr CBlackCalibrationHelper' -> IO BlackCalibrationHelper
peekBlackCalibrationHelper = GenCalibrationHelper <.> newGenForeignPtr
withCalibrationHelperArray :: [GenCalibrationHelper ch] -> ((CUInt, Ptr (Ptr CCalibrationHelper')) -> IO b) -> IO b
withCalibrationHelperArray = withGenArray withCalibrationHelper
withBlackCalibrationHelperArray :: [BlackCalibrationHelper] -> ((CUInt, Ptr (Ptr CBlackCalibrationHelper')) -> IO b) -> IO b
withBlackCalibrationHelperArray = withGenArray withGenCalibrationHelper

-- | > BlackCalculator
-- >   BlackScholesCalculator
type BlackCalculator = GenBlackCalculator CBlackCalculator
data CBlackCalculator'
data CBlackScholesCalculator'
newtype GenBlackCalculator bc = GenBlackCalculator {getBlackCalculator :: GenForeignPtr bc CBlackCalculator'}
type CBlackCalculator = ForeignPtr CBlackCalculator'
type CBlackScholesCalculator = ForeignPtr CBlackScholesCalculator'
type BlackScholesCalculator = GenBlackCalculator CBlackScholesCalculator
foreign import ccall unsafe "ql.h &qlFreeBlackCalculator" qlFreeBlackCalculator :: FinalizerPtr CBlackCalculator'
foreign import ccall unsafe "ql.h &qlFreeBlackScholesCalculator" qlFreeBlackScholesCalculator :: FinalizerPtr CBlackScholesCalculator'
instance Finalizable CBlackCalculator' where finalize = qlFreeBlackCalculator
instance Finalizable CBlackScholesCalculator' where finalize = qlFreeBlackScholesCalculator
foreign import ccall "ql.h qlBlackScholesCalculatorAsBlackCalculator" qlBlackScholesCalculatorAsBlackCalculator :: Ptr CBlackScholesCalculator' -> IO (Ptr CBlackCalculator')
instance Upcastable CBlackScholesCalculator' where {type Base CBlackScholesCalculator' = CBlackCalculator'; upcast = qlBlackScholesCalculatorAsBlackCalculator}
asBlackCalculator :: GenBlackCalculator bc -> IO BlackCalculator
asBlackCalculator = transferGenForeignPtr peekBlackCalculator . getBlackCalculator
peekBlackCalculator :: Ptr CBlackCalculator' -> IO BlackCalculator
peekBlackCalculator = GenBlackCalculator <.> newCastForeignPtr
withBlackCalculator :: GenBlackCalculator bc -> (Ptr CBlackCalculator' -> IO b) -> IO b
withBlackCalculator = withGenForeignPtr . getBlackCalculator
withGenBlackCalculator :: GenBlackCalculator (ForeignPtr bc) -> (Ptr bc -> IO b) -> IO b
withGenBlackCalculator = withForeignPtr . ptr . getBlackCalculator
peekBlackScholesCalculator :: Ptr CBlackScholesCalculator' -> IO BlackScholesCalculator
peekBlackScholesCalculator = GenBlackCalculator <.> newGenForeignPtr

-- | > BachelierCalculator
-- no subclasses upstream, unlike BlackCalculator/BlackScholesCalculator above, so this is a
-- plain leaf (Standalone), not a GenX/Upcastable hierarchy
data CBachelierCalculator
newtype BachelierCalculator = BachelierCalculator {getCBachelierCalculator :: Standalone CBachelierCalculator}
foreign import ccall unsafe "ql.h &qlFreeBachelierCalculator" qlFreeBachelierCalculator :: FinalizerPtr CBachelierCalculator
instance Finalizable CBachelierCalculator where finalize = qlFreeBachelierCalculator
peekBachelierCalculator :: Ptr CBachelierCalculator -> IO BachelierCalculator
peekBachelierCalculator = BachelierCalculator <.> peekStandalone
withBachelierCalculator :: BachelierCalculator -> (Ptr CBachelierCalculator -> IO b) -> IO b
withBachelierCalculator = withStandalone . getCBachelierCalculator

-- MULTILEVEL HIERARCHIES
-- | > Index
-- >  InterestRateIndex
-- >    BMAIndex
-- >    IborIndex
-- >      OvernightIborIndex (COvernightIndex')
-- >    SwapIndex
-- >      OvernightIndexedSwapIndex
-- >  InflationIndex
-- >    YoYInflationIndex
-- >    ZeroInflationIndex
-- >  EquityIndex
type Index = GenIndex CIndex
data CIndex'
data CInterestRateIndex'
data CInflationIndex'
data CZeroInflationIndex'
data CYoYInflationIndex'
data CBMAIndex'
data CIborIndex'
data COvernightIndex'
data CSwapIndex'
data COvernightIndexedSwapIndex'
newtype GenIndex idx = GenIndex {getIndex :: GenForeignPtr idx CIndex'}
type CIndex = ForeignPtr CIndex'

foreign import ccall safe "ql.h qlIndexName" qlIndexName :: Ptr CIndex' -> IO CString
showIndex :: GenIndex idx -> String
showIndex = unsafePerformIO . (`withIndex` (qlIndexName >=> peekDynString))
{-# NOINLINE showIndex #-}

instance Show (GenIndex idx) where show = showIndex

type GenInterestRateIndex ridx = GenIndex (AnyOf CInterestRateIndex' ridx)
type CInterestRateIndex = ForeignPtr CInterestRateIndex'
type InterestRateIndex = GenInterestRateIndex CInterestRateIndex
type GenInflationIndex iidx = GenIndex (AnyOf CInflationIndex' iidx)
type CInflationIndex = ForeignPtr CInflationIndex'
type InflationIndex = GenInflationIndex CInflationIndex
type GenZeroInflationIndex zidx = GenInflationIndex (AnyOf CZeroInflationIndex' zidx)
type CZeroInflationIndex = ForeignPtr CZeroInflationIndex'
type ZeroInflationIndex = GenZeroInflationIndex CZeroInflationIndex
type GenYoYInflationIndex yidx = GenInflationIndex (AnyOf CYoYInflationIndex' yidx)
type CYoYInflationIndex = ForeignPtr CYoYInflationIndex'
type YoYInflationIndex = GenYoYInflationIndex CYoYInflationIndex
type CBMAIndex = ForeignPtr CBMAIndex'
type BMAIndex = GenInterestRateIndex CBMAIndex
type CIborIndex = ForeignPtr CIborIndex'
type IborIndex = GenIborIndex CIborIndex
type COvernightIndex = ForeignPtr COvernightIndex'
type OvernightIborIndex = GenIborIndex COvernightIndex
type CSwapIndex = ForeignPtr CSwapIndex'
type SwapIndex = GenSwapIndex CSwapIndex
type GenIborIndex ibor = GenInterestRateIndex (AnyOf CIborIndex' ibor)
type GenSwapIndex sidx = GenInterestRateIndex (AnyOf CSwapIndex' sidx)
type COvernightIndexedSwapIndex = ForeignPtr COvernightIndexedSwapIndex'
type OvernightIndexedSwapIndex = GenSwapIndex COvernightIndexedSwapIndex
foreign import ccall unsafe "ql.h &qlFreeIndex" qlFreeIndex :: FinalizerPtr CIndex'
foreign import ccall unsafe "ql.h &qlFreeInterestRateIndex" qlFreeInterestRateIndex :: FinalizerPtr CInterestRateIndex'
foreign import ccall unsafe "ql.h &qlFreeInflationIndex" qlFreeInflationIndex :: FinalizerPtr CInflationIndex'
foreign import ccall unsafe "ql.h &qlFreeZeroInflationIndex" qlFreeZeroInflationIndex :: FinalizerPtr CZeroInflationIndex'
foreign import ccall unsafe "ql.h &qlFreeYoYInflationIndex" qlFreeYoYInflationIndex :: FinalizerPtr CYoYInflationIndex'
foreign import ccall unsafe "ql.h &qlFreeBMAIndex" qlFreeBMAIndex :: FinalizerPtr CBMAIndex'
foreign import ccall unsafe "ql.h &qlFreeIborIndex" qlFreeIborIndex :: FinalizerPtr CIborIndex'
foreign import ccall unsafe "ql.h &qlFreeOvernightIndex" qlFreeOvernightIborIndex :: FinalizerPtr COvernightIndex'
foreign import ccall unsafe "ql.h &qlFreeSwapIndex" qlFreeSwapIndex :: FinalizerPtr CSwapIndex'
foreign import ccall unsafe "ql.h &qlFreeOvernightIndexedSwapIndex" qlFreeOvernightIndexedSwapIndex :: FinalizerPtr COvernightIndexedSwapIndex'
instance Finalizable CIndex' where finalize = qlFreeIndex
instance Finalizable CInterestRateIndex' where finalize = qlFreeInterestRateIndex
instance Finalizable CInflationIndex' where finalize = qlFreeInflationIndex
instance Finalizable CZeroInflationIndex' where finalize = qlFreeZeroInflationIndex
instance Finalizable CYoYInflationIndex' where finalize = qlFreeYoYInflationIndex
instance Finalizable CBMAIndex' where finalize = qlFreeBMAIndex
instance Finalizable CIborIndex' where finalize = qlFreeIborIndex
instance Finalizable COvernightIndex' where finalize = qlFreeOvernightIborIndex
instance Finalizable CSwapIndex' where finalize = qlFreeSwapIndex
instance Finalizable COvernightIndexedSwapIndex' where finalize = qlFreeOvernightIndexedSwapIndex
foreign import ccall "ql.h qlInterestRateIndexAsIndex" qlInterestRateIndexAsIndex :: Ptr CInterestRateIndex' -> IO (Ptr CIndex')
foreign import ccall "ql.h qlInflationIndexAsIndex" qlInflationIndexAsIndex :: Ptr CInflationIndex' -> IO (Ptr CIndex')
foreign import ccall "ql.h qlZeroInflationIndexAsInflationIndex" qlZeroInflationIndexAsInflationIndex :: Ptr CZeroInflationIndex' -> IO (Ptr CInflationIndex')
foreign import ccall "ql.h qlYoYInflationIndexAsInflationIndex" qlYoYInflationIndexAsInflationIndex :: Ptr CYoYInflationIndex' -> IO (Ptr CInflationIndex')
foreign import ccall "ql.h qlBMAIndexAsInterestRateIndex" qlBMAIndexAsInterestRateIndex :: Ptr CBMAIndex' -> IO (Ptr CInterestRateIndex')
foreign import ccall "ql.h qlIborIndexAsInterestRateIndex" qlIborIndexAsInterestRateIndex :: Ptr CIborIndex' -> IO (Ptr CInterestRateIndex')
foreign import ccall "ql.h qlOvernightIndexAsIborIndex" qlOvernightIndexAsIborIndex :: Ptr COvernightIndex' -> IO (Ptr CIborIndex')
foreign import ccall "ql.h qlSwapIndexAsInterestRateIndex" qlSwapIndexAsInterestRateIndex :: Ptr CSwapIndex' -> IO (Ptr CInterestRateIndex')
foreign import ccall "ql.h qlOvernightIndexedSwapIndexAsSwapIndex" qlOvernightIndexedSwapIndexAsSwapIndex :: Ptr COvernightIndexedSwapIndex' -> IO (Ptr CSwapIndex')
instance Upcastable CInterestRateIndex' where {type Base CInterestRateIndex' = CIndex'; upcast = qlInterestRateIndexAsIndex}
instance Upcastable CInflationIndex' where {type Base CInflationIndex' = CIndex'; upcast = qlInflationIndexAsIndex}
instance Upcastable CZeroInflationIndex' where {type Base CZeroInflationIndex' = CInflationIndex'; upcast = qlZeroInflationIndexAsInflationIndex}
instance Upcastable CYoYInflationIndex' where {type Base CYoYInflationIndex' = CInflationIndex'; upcast = qlYoYInflationIndexAsInflationIndex}
instance Upcastable CBMAIndex' where {type Base CBMAIndex' = CInterestRateIndex'; upcast = qlBMAIndexAsInterestRateIndex}
instance Upcastable CIborIndex' where {type Base CIborIndex' = CInterestRateIndex'; upcast = qlIborIndexAsInterestRateIndex}
instance Upcastable COvernightIndex' where {type Base COvernightIndex' = CIborIndex'; upcast = qlOvernightIndexAsIborIndex}
instance Upcastable CSwapIndex' where {type Base CSwapIndex' = CInterestRateIndex'; upcast = qlSwapIndexAsInterestRateIndex}
instance Upcastable COvernightIndexedSwapIndex' where {type Base COvernightIndexedSwapIndex' = CSwapIndex'; upcast = qlOvernightIndexedSwapIndexAsSwapIndex}

asIndex :: GenIndex idx -> IO Index
asIndex = transferGenForeignPtr peekIndex . getIndex
withIndex :: GenIndex idx -> (Ptr CIndex' -> IO b) -> IO b
withIndex = withGenForeignPtr . getIndex
peekIndex :: Ptr CIndex' -> IO Index
peekIndex = GenIndex <.> newCastForeignPtr

asInterestRateIndex :: GenInterestRateIndex ridx -> IO InterestRateIndex
asInterestRateIndex = transferGenForeignPtr peekInterestRateIndex . peel . getIndex
peekInterestRateIndex :: Ptr CInterestRateIndex' -> IO InterestRateIndex
peekInterestRateIndex = newCastForeignPtr >=> newGenInterestRateIndex
newGenInterestRateIndex :: GenForeignPtr ridx CInterestRateIndex' -> IO (GenInterestRateIndex ridx)
newGenInterestRateIndex = pure . GenIndex . newAnyOf
withInterestRateIndex :: GenInterestRateIndex ridx -> (Ptr CInterestRateIndex' -> IO b) -> IO b
withInterestRateIndex = withGenForeignPtr . peel . getIndex

asInflationIndex :: GenInflationIndex iidx -> IO InflationIndex
asInflationIndex = transferGenForeignPtr peekInflationIndex . peel . getIndex
peekInflationIndex :: Ptr CInflationIndex' -> IO InflationIndex
peekInflationIndex = newCastForeignPtr >=> newGenInflationIndex
newGenInflationIndex :: GenForeignPtr iidx CInflationIndex' -> IO (GenInflationIndex iidx)
newGenInflationIndex = pure . GenIndex . newAnyOf
withInflationIndex :: GenInflationIndex iidx -> (Ptr CInflationIndex' -> IO b) -> IO b
withInflationIndex = withGenForeignPtr . peel . getIndex

peekZeroInflationIndex :: Ptr CZeroInflationIndex' -> IO ZeroInflationIndex
peekZeroInflationIndex = newCastForeignPtr >=> newGenZeroInflationIndex
withZeroInflationIndex :: GenZeroInflationIndex zidx -> (Ptr CZeroInflationIndex' -> IO b) -> IO b
withZeroInflationIndex = withGenForeignPtr . peel . peel . getIndex
newGenZeroInflationIndex :: GenForeignPtr zidx CZeroInflationIndex' -> IO (GenZeroInflationIndex zidx)
newGenZeroInflationIndex = pure . GenIndex . newAnyOf . newAnyOf

peekYoYInflationIndex :: Ptr CYoYInflationIndex' -> IO YoYInflationIndex
peekYoYInflationIndex = newCastForeignPtr >=> newGenYoYInflationIndex
withYoYInflationIndex :: GenYoYInflationIndex yidx -> (Ptr CYoYInflationIndex' -> IO b) -> IO b
withYoYInflationIndex = withGenForeignPtr . peel . peel . getIndex
newGenYoYInflationIndex :: GenForeignPtr yidx CYoYInflationIndex' -> IO (GenYoYInflationIndex yidx)
newGenYoYInflationIndex = pure . GenIndex . newAnyOf . newAnyOf

peekBMAIndex :: Ptr CBMAIndex' -> IO BMAIndex
peekBMAIndex = newGenForeignPtr >=> newGenInterestRateIndex
withBMAIndex :: BMAIndex -> (Ptr CBMAIndex' -> IO b) -> IO b
withBMAIndex = withForeignPtr . ptr . peel . getIndex

asIborIndex :: GenIborIndex ibor -> IO IborIndex
asIborIndex = transferGenForeignPtr peekIborIndex . peel . peel . getIndex
peekIborIndex :: Ptr CIborIndex' -> IO IborIndex
peekIborIndex = newCastForeignPtr >=> newGenIborIndex
withIborIndex :: GenIborIndex ibor -> (Ptr CIborIndex' -> IO b) -> IO b
withIborIndex = withGenForeignPtr . peel . peel . getIndex
newGenIborIndex :: GenForeignPtr ibor CIborIndex' -> IO (GenIborIndex ibor)
newGenIborIndex = pure . GenIndex . newAnyOf . newAnyOf

peekOvernightIborIndex :: Ptr COvernightIndex' -> IO OvernightIborIndex
peekOvernightIborIndex = newGenForeignPtr >=> newGenIborIndex
withOvernightIborIndex :: OvernightIborIndex -> (Ptr COvernightIndex' -> IO b) -> IO b
withOvernightIborIndex = withForeignPtr . ptr . peel . peel . getIndex

asSwapIndex :: GenSwapIndex sidx -> IO SwapIndex
asSwapIndex = transferGenForeignPtr peekSwapIndex . peel . peel . getIndex
peekSwapIndex :: Ptr CSwapIndex' -> IO SwapIndex
peekSwapIndex = newCastForeignPtr >=> newGenSwapIndex
withSwapIndex :: GenSwapIndex sidx -> (Ptr CSwapIndex' -> IO b) -> IO b
withSwapIndex  = withGenForeignPtr . peel . peel . getIndex
newGenSwapIndex :: GenForeignPtr sidx CSwapIndex' -> IO (GenSwapIndex sidx)
newGenSwapIndex = pure . GenIndex . newAnyOf . newAnyOf

peekOvernightIndexedSwapIndex :: Ptr COvernightIndexedSwapIndex' -> IO OvernightIndexedSwapIndex
peekOvernightIndexedSwapIndex = newGenForeignPtr >=> newGenSwapIndex
withOvernightIndexedSwapIndex :: OvernightIndexedSwapIndex -> (Ptr COvernightIndexedSwapIndex' -> IO b) -> IO b
withOvernightIndexedSwapIndex = withForeignPtr  .ptr . peel . peel . getIndex

data CEquityIndex'
type CEquityIndex = ForeignPtr CEquityIndex'
type EquityIndex = GenIndex CEquityIndex
foreign import ccall unsafe "ql.h &qlFreeEquityIndex" qlFreeEquityIndex :: FinalizerPtr CEquityIndex'
instance Finalizable CEquityIndex' where finalize = qlFreeEquityIndex
foreign import ccall "ql.h qlEquityIndexAsIndex" qlEquityIndexAsIndex :: Ptr CEquityIndex' -> IO (Ptr CIndex')
instance Upcastable CEquityIndex' where {type Base CEquityIndex' = CIndex'; upcast = qlEquityIndexAsIndex}
peekEquityIndex :: Ptr CEquityIndex' -> IO EquityIndex
peekEquityIndex = GenIndex <.> newGenForeignPtr
withEquityIndex :: EquityIndex -> (Ptr CEquityIndex' -> IO b) -> IO b
withEquityIndex = withForeignPtr . ptr . getIndex

-- | > TermStructure = GenTermStructure t
-- >  YieldTermStructure = GenYieldTermStructure y = GenTermStructure t
-- >    FittedBondDiscountCurve = GenYieldTermStructure ...
-- >    RelinkableYieldTermStructure = GenYieldTermStructure ...
-- (MultiCurve, below with the other standalone leaves, is not a YieldTermStructure member --
-- it manages a cycle of them, handing out 'YieldTermStructure' handles via addBootstrappedCurve
-- \/ addNonBootstrappedCurve. See its own definition's comment.)
-- >  VolatilityTermStructure
-- >    OptionletVolatilityStructure
-- >      RelinkableOptionletVolatilityStructure
-- >    BlackVolTermStructure
-- >      BlackVarianceCurve
-- >      BlackVolatilitySurfaceDelta
-- >      RelinkableBlackVolTermStructure
-- >    SwaptionVolatilityStructure
-- >      RelinkableSwaptionVolatilityStructure
-- >      SabrSwaptionVolatilityCube
-- >      InterpolatedSwaptionVolatilityCube
-- >    CapFloorTermVolSurface
-- >    LocalVolTermStructure
-- >  CallableBondVolatilityStructure
-- >  DefaultProbabilityTermStructure
-- >  ZeroInflationTermStructure
-- >  YoYInflationTermStructure
type TermStructure = GenTermStructure CTermStructure
data CTermStructure'
data CVolatilityTermStructure'
data COptionletVolatilityStructure'
data CRelinkableOptionletVolatilityStructure'
data CSwaptionVolatilityStructure'
data CRelinkableSwaptionVolatilityStructure'
data CSabrSwaptionVolatilityCube'
data CInterpolatedSwaptionVolatilityCube'
data CCapFloorTermVolSurface'
data CLocalVolTermStructure'
data CBlackVolTermStructure'
data CRelinkableBlackVolTermStructure'
data CBlackVarianceCurve'
data CBlackVolatilitySurfaceDelta'
data CYieldTermStructure'
data CFittedBondDiscountCurve'
data CRelinkableYieldTermStructure'
data CCallableBondVolatilityStructure'
data CDefaultProbabilityTermStructure'
data CZeroInflationTermStructure'
data CYoYInflationTermStructure'
newtype GenTermStructure t = GenTermStructure {getTermStructure :: GenForeignPtr t CTermStructure'}
type CTermStructure = ForeignPtr CTermStructure'
type GenYieldTermStructure y = GenTermStructure (AnyOf CYieldTermStructure' y)
type CYieldTermStructure = ForeignPtr CYieldTermStructure'
type YieldTermStructure = GenYieldTermStructure CYieldTermStructure
type CFittedBondDiscountCurve = ForeignPtr CFittedBondDiscountCurve'
type FittedBondDiscountCurve = GenYieldTermStructure CFittedBondDiscountCurve
type CRelinkableYieldTermStructure = ForeignPtr CRelinkableYieldTermStructure'
-- | A curve held behind a relinkable handle. It /is/ a 'YieldTermStructure' -- pass it
-- anywhere a curve is expected and it upcasts like any other hierarchy member, sharing its
-- @Link@ so that a later 'QuantLib.TermStructure.Yield.linkTo' reaches everything already
-- built on it.
type RelinkableYieldTermStructure = GenYieldTermStructure CRelinkableYieldTermStructure
type GenVolatilityTermStructure v = GenTermStructure (AnyOf CVolatilityTermStructure' v)
type CVolatilityTermStructure = ForeignPtr CVolatilityTermStructure'
type VolatilityTermStructure = GenVolatilityTermStructure CVolatilityTermStructure
type GenOptionletVolatilityStructure ov = GenVolatilityTermStructure (AnyOf COptionletVolatilityStructure' ov)
type COptionletVolatilityStructure = ForeignPtr COptionletVolatilityStructure'
type OptionletVolatilityStructure = GenOptionletVolatilityStructure COptionletVolatilityStructure
type CRelinkableOptionletVolatilityStructure = ForeignPtr CRelinkableOptionletVolatilityStructure'
-- | An optionlet vol surface held behind a relinkable handle. It /is/ an
-- 'OptionletVolatilityStructure' -- pass it anywhere one is expected and it upcasts like any
-- other hierarchy member, sharing its @Link@ so that a later
-- 'QuantLib.TermStructure.Volatility.linkOptionletVolTo' reaches everything already built on
-- it. Mirrors 'RelinkableSwaptionVolatilityStructure'.
type RelinkableOptionletVolatilityStructure = GenOptionletVolatilityStructure CRelinkableOptionletVolatilityStructure
type CCapFloorTermVolSurface = ForeignPtr CCapFloorTermVolSurface'
type CapFloorTermVolSurface = GenVolatilityTermStructure CCapFloorTermVolSurface
type GenSwaptionVolatilityStructure sv = GenVolatilityTermStructure (AnyOf CSwaptionVolatilityStructure' sv)
type CSwaptionVolatilityStructure = ForeignPtr CSwaptionVolatilityStructure'
type SwaptionVolatilityStructure = GenSwaptionVolatilityStructure CSwaptionVolatilityStructure
type CRelinkableSwaptionVolatilityStructure = ForeignPtr CRelinkableSwaptionVolatilityStructure'
-- | A swaption vol surface held behind a relinkable handle. It /is/ a
-- 'SwaptionVolatilityStructure' -- pass it anywhere one is expected and it upcasts like any
-- other hierarchy member, sharing its @Link@ so that a later
-- 'QuantLib.TermStructure.Volatility.linkSwaptionVolTo' reaches everything already built on
-- it. Mirrors 'RelinkableBlackVolTermStructure'.
type RelinkableSwaptionVolatilityStructure = GenSwaptionVolatilityStructure CRelinkableSwaptionVolatilityStructure
type CSabrSwaptionVolatilityCube = ForeignPtr CSabrSwaptionVolatilityCube'
-- | A SABR-calibrated swaption vol cube. It /is/ a 'SwaptionVolatilityStructure' -- pass it
-- anywhere one is expected. Its own extra getters (sparse\/dense SABR parameters, market\/ATM-
-- calibrated vol cubes, ATM strike) are bound directly against this concrete type rather than
-- via a downcast: it has real calculations of its own beyond the generic interface, so per the
-- API-design rule in CLAUDE.md it earns a dedicated leaf instead of being collapsed into
-- 'SwaptionVolatilityStructure' the way 'swaptionVolatilityMatrix'' is.
type SabrSwaptionVolatilityCube = GenSwaptionVolatilityStructure CSabrSwaptionVolatilityCube
type CInterpolatedSwaptionVolatilityCube = ForeignPtr CInterpolatedSwaptionVolatilityCube'
-- | The non-SABR, linear-interpolation swaption vol cube. It /is/ a
-- 'SwaptionVolatilityStructure' -- pass it anywhere one is expected. Gets the same dedicated-leaf
-- treatment as 'SabrSwaptionVolatilityCube' for its 'atmStrike' getter (inherited, in upstream,
-- from the same abstract @SwaptionVolatilityCube@ base both concrete cubes share).
type InterpolatedSwaptionVolatilityCube = GenSwaptionVolatilityStructure CInterpolatedSwaptionVolatilityCube
type CLocalVolTermStructure = ForeignPtr CLocalVolTermStructure'
type LocalVolTermStructure = GenVolatilityTermStructure CLocalVolTermStructure
type GenBlackVolTermStructure bv = GenVolatilityTermStructure (AnyOf CBlackVolTermStructure' bv)
type CBlackVolTermStructure = ForeignPtr CBlackVolTermStructure'
type BlackVolTermStructure = GenBlackVolTermStructure CBlackVolTermStructure
type CRelinkableBlackVolTermStructure = ForeignPtr CRelinkableBlackVolTermStructure'
-- | A Black vol surface held behind a relinkable handle. It /is/ a 'BlackVolTermStructure' --
-- pass it anywhere one is expected and it upcasts like any other hierarchy member, sharing its
-- @Link@ so that a later 'QuantLib.TermStructure.Volatility.linkBlackVolTo' reaches everything
-- already built on it. Mirrors 'RelinkableYieldTermStructure'.
type RelinkableBlackVolTermStructure = GenBlackVolTermStructure CRelinkableBlackVolTermStructure
type CBlackVarianceCurve = ForeignPtr CBlackVarianceCurve'
type BlackVarianceCurve = GenBlackVolTermStructure CBlackVarianceCurve
type CBlackVolatilitySurfaceDelta = ForeignPtr CBlackVolatilitySurfaceDelta'
type BlackVolatilitySurfaceDelta = GenBlackVolTermStructure CBlackVolatilitySurfaceDelta
type CCallableBondVolatilityStructure = ForeignPtr CCallableBondVolatilityStructure'
type CallableBondVolatilityStructure = GenTermStructure CCallableBondVolatilityStructure
type CDefaultProbabilityTermStructure = ForeignPtr CDefaultProbabilityTermStructure'
type DefaultProbabilityTermStructure = GenTermStructure CDefaultProbabilityTermStructure
type CZeroInflationTermStructure = ForeignPtr CZeroInflationTermStructure'
type ZeroInflationTermStructure = GenTermStructure CZeroInflationTermStructure
type CYoYInflationTermStructure = ForeignPtr CYoYInflationTermStructure'
type YoYInflationTermStructure = GenTermStructure CYoYInflationTermStructure
foreign import ccall unsafe "ql.h &qlFreeTermStructure" qlFreeTermStructure :: FinalizerPtr CTermStructure'
foreign import ccall unsafe "ql.h &qlFreeVolatilityTermStructure" qlFreeVolatilityTermStructure :: FinalizerPtr CVolatilityTermStructure'
foreign import ccall unsafe "ql.h &qlFreeOptionletVolatilityStructure" qlFreeOptionletVolatilityStructure :: FinalizerPtr COptionletVolatilityStructure'
foreign import ccall unsafe "ql.h &qlFreeRelinkableOptionletVolatilityStructure" qlFreeRelinkableOptionletVolatilityStructure :: FinalizerPtr CRelinkableOptionletVolatilityStructure'
foreign import ccall unsafe "ql.h &qlFreeSwaptionVolatilityStructure" qlFreeSwaptionVolatilityStructure :: FinalizerPtr CSwaptionVolatilityStructure'
foreign import ccall unsafe "ql.h &qlFreeRelinkableSwaptionVolatilityStructure" qlFreeRelinkableSwaptionVolatilityStructure :: FinalizerPtr CRelinkableSwaptionVolatilityStructure'
foreign import ccall unsafe "ql.h &qlFreeSabrSwaptionVolatilityCube" qlFreeSabrSwaptionVolatilityCube :: FinalizerPtr CSabrSwaptionVolatilityCube'
foreign import ccall unsafe "ql.h &qlFreeInterpolatedSwaptionVolatilityCube" qlFreeInterpolatedSwaptionVolatilityCube :: FinalizerPtr CInterpolatedSwaptionVolatilityCube'
foreign import ccall unsafe "ql.h &qlFreeCapFloorTermVolSurface" qlFreeCapFloorTermVolSurface :: FinalizerPtr CCapFloorTermVolSurface'
foreign import ccall unsafe "ql.h &qlFreeLocalVolTermStructure" qlFreeLocalVolTermStructure :: FinalizerPtr CLocalVolTermStructure'
foreign import ccall unsafe "ql.h &qlFreeBlackVolTermStructure" qlFreeBlackVolTermStructure :: FinalizerPtr CBlackVolTermStructure'
foreign import ccall unsafe "ql.h &qlFreeRelinkableBlackVolTermStructure" qlFreeRelinkableBlackVolTermStructure :: FinalizerPtr CRelinkableBlackVolTermStructure'
foreign import ccall unsafe "ql.h &qlFreeBlackVarianceCurve" qlFreeBlackVarianceCurve :: FinalizerPtr CBlackVarianceCurve'
foreign import ccall unsafe "ql.h &qlFreeBlackVolatilitySurfaceDelta" qlFreeBlackVolatilitySurfaceDelta :: FinalizerPtr CBlackVolatilitySurfaceDelta'
foreign import ccall unsafe "ql.h &qlFreeYieldTermStructure" qlFreeYieldTermStructure :: FinalizerPtr CYieldTermStructure'
foreign import ccall unsafe "ql.h &qlFreeFittedBondDiscountCurve" qlFreeFittedBondDiscountCurve :: FinalizerPtr CFittedBondDiscountCurve'
foreign import ccall unsafe "ql.h &qlFreeRelinkableYieldTermStructure" qlFreeRelinkableYieldTermStructure :: FinalizerPtr CRelinkableYieldTermStructure'
foreign import ccall unsafe "ql.h &qlFreeCallableBondVolatilityStructure" qlFreeCallableBondVolatilityStructure :: FinalizerPtr CCallableBondVolatilityStructure'
foreign import ccall unsafe "ql.h &qlFreeDefaultProbabilityTermStructure" qlFreeDefaultProbabilityTermStructure :: FinalizerPtr CDefaultProbabilityTermStructure'
foreign import ccall unsafe "ql.h &qlFreeZeroInflationTermStructure" qlFreeZeroInflationTermStructure :: FinalizerPtr CZeroInflationTermStructure'
foreign import ccall unsafe "ql.h &qlFreeYoYInflationTermStructure" qlFreeYoYInflationTermStructure :: FinalizerPtr CYoYInflationTermStructure'
instance Finalizable CTermStructure' where finalize = qlFreeTermStructure
instance Finalizable CVolatilityTermStructure' where finalize = qlFreeVolatilityTermStructure
instance Finalizable COptionletVolatilityStructure' where finalize = qlFreeOptionletVolatilityStructure
instance Finalizable CRelinkableOptionletVolatilityStructure' where finalize = qlFreeRelinkableOptionletVolatilityStructure
instance Finalizable CSwaptionVolatilityStructure' where finalize = qlFreeSwaptionVolatilityStructure
instance Finalizable CRelinkableSwaptionVolatilityStructure' where finalize = qlFreeRelinkableSwaptionVolatilityStructure
instance Finalizable CSabrSwaptionVolatilityCube' where finalize = qlFreeSabrSwaptionVolatilityCube
instance Finalizable CInterpolatedSwaptionVolatilityCube' where finalize = qlFreeInterpolatedSwaptionVolatilityCube
instance Finalizable CCapFloorTermVolSurface' where finalize = qlFreeCapFloorTermVolSurface
instance Finalizable CLocalVolTermStructure' where finalize = qlFreeLocalVolTermStructure
instance Finalizable CBlackVolTermStructure' where finalize = qlFreeBlackVolTermStructure
instance Finalizable CRelinkableBlackVolTermStructure' where finalize = qlFreeRelinkableBlackVolTermStructure
instance Finalizable CBlackVarianceCurve' where finalize = qlFreeBlackVarianceCurve
instance Finalizable CBlackVolatilitySurfaceDelta' where finalize = qlFreeBlackVolatilitySurfaceDelta
instance Finalizable CYieldTermStructure' where finalize = qlFreeYieldTermStructure
instance Finalizable CFittedBondDiscountCurve' where finalize = qlFreeFittedBondDiscountCurve
instance Finalizable CRelinkableYieldTermStructure' where finalize = qlFreeRelinkableYieldTermStructure
instance Finalizable CCallableBondVolatilityStructure' where finalize = qlFreeCallableBondVolatilityStructure
instance Finalizable CDefaultProbabilityTermStructure' where finalize = qlFreeDefaultProbabilityTermStructure
instance Finalizable CZeroInflationTermStructure' where finalize = qlFreeZeroInflationTermStructure
instance Finalizable CYoYInflationTermStructure' where finalize = qlFreeYoYInflationTermStructure
foreign import ccall "ql.h qlYieldTermStructureAsTermStructure" qlYieldTermStructureAsTermStructure :: Ptr CYieldTermStructure' -> IO (Ptr CTermStructure')
foreign import ccall "ql.h qlFittedBondDiscountCurveAsYieldTermStructure" qlFittedBondDiscountCurveAsYieldTermStructure :: Ptr CFittedBondDiscountCurve' -> IO (Ptr CYieldTermStructure')
foreign import ccall "ql.h qlRelinkableYieldTermStructureAsYieldTermStructure" qlRelinkableYieldTermStructureAsYieldTermStructure :: Ptr CRelinkableYieldTermStructure' -> IO (Ptr CYieldTermStructure')
foreign import ccall "ql.h qlVolatilityTermStructureAsTermStructure" qlVolatilityTermStructureAsTermStructure :: Ptr CVolatilityTermStructure' -> IO (Ptr CTermStructure')
foreign import ccall "ql.h qlOptionletVolatilityStructureAsVolatilityTermStructure" qlOptionletVolatilityStructureAsVolatilityTermStructure :: Ptr COptionletVolatilityStructure' -> IO (Ptr CVolatilityTermStructure')
foreign import ccall "ql.h qlRelinkableOptionletVolatilityStructureAsOptionletVolatilityStructure" qlRelinkableOptionletVolatilityStructureAsOptionletVolatilityStructure :: Ptr CRelinkableOptionletVolatilityStructure' -> IO (Ptr COptionletVolatilityStructure')
foreign import ccall "ql.h qlBlackVolTermStructureAsVolatilityTermStructure" qlBlackVolTermStructureAsVolatilityTermStructure :: Ptr CBlackVolTermStructure' -> IO (Ptr CVolatilityTermStructure')
foreign import ccall "ql.h qlRelinkableBlackVolTermStructureAsBlackVolTermStructure" qlRelinkableBlackVolTermStructureAsBlackVolTermStructure :: Ptr CRelinkableBlackVolTermStructure' -> IO (Ptr CBlackVolTermStructure')
foreign import ccall "ql.h qlBlackVarianceCurveAsBlackVolTermStructure" qlBlackVarianceCurveAsBlackVolTermStructure :: Ptr CBlackVarianceCurve' -> IO (Ptr CBlackVolTermStructure')
foreign import ccall "ql.h qlBlackVolatilitySurfaceDeltaAsBlackVolTermStructure" qlBlackVolatilitySurfaceDeltaAsBlackVolTermStructure :: Ptr CBlackVolatilitySurfaceDelta' -> IO (Ptr CBlackVolTermStructure')
foreign import ccall "ql.h qlSwaptionVolatilityStructureAsVolatilityTermStructure" qlSwaptionVolatilityStructureAsVolatilityTermStructure :: Ptr CSwaptionVolatilityStructure' -> IO (Ptr CVolatilityTermStructure')
foreign import ccall "ql.h qlRelinkableSwaptionVolatilityStructureAsSwaptionVolatilityStructure" qlRelinkableSwaptionVolatilityStructureAsSwaptionVolatilityStructure :: Ptr CRelinkableSwaptionVolatilityStructure' -> IO (Ptr CSwaptionVolatilityStructure')
foreign import ccall "ql.h qlSabrSwaptionVolatilityCubeAsSwaptionVolatilityStructure" qlSabrSwaptionVolatilityCubeAsSwaptionVolatilityStructure :: Ptr CSabrSwaptionVolatilityCube' -> IO (Ptr CSwaptionVolatilityStructure')
foreign import ccall "ql.h qlInterpolatedSwaptionVolatilityCubeAsSwaptionVolatilityStructure" qlInterpolatedSwaptionVolatilityCubeAsSwaptionVolatilityStructure :: Ptr CInterpolatedSwaptionVolatilityCube' -> IO (Ptr CSwaptionVolatilityStructure')
foreign import ccall "ql.h qlCapFloorTermVolSurfaceAsVolatilityTermStructure" qlCapFloorTermVolSurfaceAsVolatilityTermStructure :: Ptr CCapFloorTermVolSurface' -> IO (Ptr CVolatilityTermStructure')
foreign import ccall "ql.h qlLocalVolTermStructureAsVolatilityTermStructure" qlLocalVolTermStructureAsVolatilityTermStructure :: Ptr CLocalVolTermStructure' -> IO (Ptr CVolatilityTermStructure')
foreign import ccall "ql.h qlCallableBondVolatilityStructureAsTermStructure" qlCallableBondVolatilityStructureAsTermStructure :: Ptr CCallableBondVolatilityStructure' -> IO (Ptr CTermStructure')
foreign import ccall "ql.h qlDefaultProbabilityTermStructureAsTermStructure" qlDefaultProbabilityTermStructureAsTermStructure :: Ptr CDefaultProbabilityTermStructure' -> IO (Ptr CTermStructure')
foreign import ccall "ql.h qlZeroInflationTermStructureAsTermStructure" qlZeroInflationTermStructureAsTermStructure :: Ptr CZeroInflationTermStructure' -> IO (Ptr CTermStructure')
foreign import ccall "ql.h qlYoYInflationTermStructureAsTermStructure" qlYoYInflationTermStructureAsTermStructure :: Ptr CYoYInflationTermStructure' -> IO (Ptr CTermStructure')
instance Upcastable CYieldTermStructure' where {type Base CYieldTermStructure' = CTermStructure'; upcast = qlYieldTermStructureAsTermStructure}
instance Upcastable CFittedBondDiscountCurve' where {type Base CFittedBondDiscountCurve' = CYieldTermStructure'; upcast = qlFittedBondDiscountCurveAsYieldTermStructure}
instance Upcastable CRelinkableYieldTermStructure' where {type Base CRelinkableYieldTermStructure' = CYieldTermStructure'; upcast = qlRelinkableYieldTermStructureAsYieldTermStructure}
instance Upcastable CVolatilityTermStructure' where {type Base CVolatilityTermStructure' = CTermStructure'; upcast = qlVolatilityTermStructureAsTermStructure}
instance Upcastable CCallableBondVolatilityStructure' where {type Base CCallableBondVolatilityStructure' = CTermStructure'; upcast = qlCallableBondVolatilityStructureAsTermStructure}
instance Upcastable CDefaultProbabilityTermStructure' where {type Base CDefaultProbabilityTermStructure' = CTermStructure'; upcast = qlDefaultProbabilityTermStructureAsTermStructure}
instance Upcastable CZeroInflationTermStructure' where {type Base CZeroInflationTermStructure' = CTermStructure'; upcast = qlZeroInflationTermStructureAsTermStructure}
instance Upcastable CYoYInflationTermStructure' where {type Base CYoYInflationTermStructure' = CTermStructure'; upcast = qlYoYInflationTermStructureAsTermStructure}
instance Upcastable CBlackVolTermStructure' where {type Base CBlackVolTermStructure' = CVolatilityTermStructure'; upcast = qlBlackVolTermStructureAsVolatilityTermStructure}
instance Upcastable CRelinkableBlackVolTermStructure' where {type Base CRelinkableBlackVolTermStructure' = CBlackVolTermStructure'; upcast = qlRelinkableBlackVolTermStructureAsBlackVolTermStructure}
instance Upcastable CBlackVarianceCurve' where {type Base CBlackVarianceCurve' = CBlackVolTermStructure'; upcast = qlBlackVarianceCurveAsBlackVolTermStructure}
instance Upcastable CBlackVolatilitySurfaceDelta' where {type Base CBlackVolatilitySurfaceDelta' = CBlackVolTermStructure'; upcast = qlBlackVolatilitySurfaceDeltaAsBlackVolTermStructure}
instance Upcastable COptionletVolatilityStructure' where {type Base COptionletVolatilityStructure' = CVolatilityTermStructure'; upcast = qlOptionletVolatilityStructureAsVolatilityTermStructure}
instance Upcastable CRelinkableOptionletVolatilityStructure' where {type Base CRelinkableOptionletVolatilityStructure' = COptionletVolatilityStructure'; upcast = qlRelinkableOptionletVolatilityStructureAsOptionletVolatilityStructure}
instance Upcastable CSwaptionVolatilityStructure' where {type Base CSwaptionVolatilityStructure' = CVolatilityTermStructure'; upcast = qlSwaptionVolatilityStructureAsVolatilityTermStructure}
instance Upcastable CRelinkableSwaptionVolatilityStructure' where {type Base CRelinkableSwaptionVolatilityStructure' = CSwaptionVolatilityStructure'; upcast = qlRelinkableSwaptionVolatilityStructureAsSwaptionVolatilityStructure}
instance Upcastable CSabrSwaptionVolatilityCube' where {type Base CSabrSwaptionVolatilityCube' = CSwaptionVolatilityStructure'; upcast = qlSabrSwaptionVolatilityCubeAsSwaptionVolatilityStructure}
instance Upcastable CInterpolatedSwaptionVolatilityCube' where {type Base CInterpolatedSwaptionVolatilityCube' = CSwaptionVolatilityStructure'; upcast = qlInterpolatedSwaptionVolatilityCubeAsSwaptionVolatilityStructure}
instance Upcastable CCapFloorTermVolSurface' where {type Base CCapFloorTermVolSurface' = CVolatilityTermStructure'; upcast = qlCapFloorTermVolSurfaceAsVolatilityTermStructure}
instance Upcastable CLocalVolTermStructure' where {type Base CLocalVolTermStructure' = CVolatilityTermStructure'; upcast = qlLocalVolTermStructureAsVolatilityTermStructure}
asTermStructure :: GenTermStructure t -> IO TermStructure
asTermStructure = transferGenForeignPtr peekTermStructure . getTermStructure
withTermStructure :: GenTermStructure t  -> (Ptr CTermStructure' -> IO b) -> IO b
withTermStructure = withGenForeignPtr . getTermStructure
withGenTermStructure :: GenTermStructure (ForeignPtr t) -> (Ptr t -> IO b) -> IO b
withGenTermStructure = withForeignPtr . ptr . getTermStructure
peekTermStructure :: Ptr CTermStructure' -> IO TermStructure
peekTermStructure = GenTermStructure <.> newCastForeignPtr

asVolatilityTermStructure :: GenVolatilityTermStructure v -> IO VolatilityTermStructure
asVolatilityTermStructure = transferGenForeignPtr peekVolatilityTermStructure . peel . getTermStructure
peekVolatilityTermStructure :: Ptr CVolatilityTermStructure' -> IO VolatilityTermStructure
peekVolatilityTermStructure = newCastForeignPtr >=> newGenVolatilityTermStructure
peekGenVolatilityTermStructure :: (Finalizable v, Upcastable v, Base v ~ CVolatilityTermStructure') => Ptr v -> IO (GenVolatilityTermStructure (ForeignPtr v))
peekGenVolatilityTermStructure = newGenForeignPtr >=> newGenVolatilityTermStructure
withVolatilityTermStructure :: GenVolatilityTermStructure v -> (Ptr CVolatilityTermStructure' -> IO b) -> IO b
withVolatilityTermStructure = withGenForeignPtr . peel . getTermStructure
withGenVolatilityTermStructure :: GenVolatilityTermStructure (ForeignPtr v) -> (Ptr v -> IO b) -> IO b
withGenVolatilityTermStructure = withForeignPtr . ptr . peel . getTermStructure
newGenVolatilityTermStructure :: GenForeignPtr v CVolatilityTermStructure' -> IO (GenVolatilityTermStructure v)
newGenVolatilityTermStructure = pure . GenTermStructure . newAnyOf

asBlackVolTermStructure :: GenBlackVolTermStructure bv -> IO BlackVolTermStructure
asBlackVolTermStructure = transferGenForeignPtr peekBlackVolTermStructure . peel . peel . getTermStructure
peekBlackVolTermStructure :: Ptr CBlackVolTermStructure' -> IO BlackVolTermStructure
peekBlackVolTermStructure = newCastForeignPtr >=> newGenBlackVolTermStructure
withBlackVolTermStructure :: GenBlackVolTermStructure bv -> (Ptr CBlackVolTermStructure' -> IO b) -> IO b
withBlackVolTermStructure = withGenForeignPtr . peel . peel . getTermStructure
withMaybeBlackVolTermStructure :: Maybe (GenBlackVolTermStructure bv) -> (Ptr CBlackVolTermStructure' -> IO b) -> IO b
withMaybeBlackVolTermStructure x f = maybe (f nullPtr) (`withBlackVolTermStructure` f) x
newGenBlackVolTermStructure :: GenForeignPtr bv CBlackVolTermStructure' -> IO (GenBlackVolTermStructure bv)
newGenBlackVolTermStructure = pure . GenTermStructure . newAnyOf . newAnyOf

peekBlackVarianceCurve :: Ptr CBlackVarianceCurve' -> IO BlackVarianceCurve
peekBlackVarianceCurve = newGenForeignPtr >=> newGenBlackVolTermStructure
peekRelinkableBlackVolTermStructure :: Ptr CRelinkableBlackVolTermStructure' -> IO RelinkableBlackVolTermStructure
peekRelinkableBlackVolTermStructure = newGenForeignPtr >=> newGenBlackVolTermStructure
withRelinkableBlackVolTermStructure :: RelinkableBlackVolTermStructure -> (Ptr CRelinkableBlackVolTermStructure' -> IO b) -> IO b
withRelinkableBlackVolTermStructure = withForeignPtr . ptr . peel . peel . getTermStructure
withBlackVarianceCurve :: BlackVarianceCurve -> (Ptr CBlackVarianceCurve' -> IO b) -> IO b
withBlackVarianceCurve = withForeignPtr . ptr . peel . peel . getTermStructure
peekBlackVolatilitySurfaceDelta :: Ptr CBlackVolatilitySurfaceDelta' -> IO BlackVolatilitySurfaceDelta
peekBlackVolatilitySurfaceDelta = newGenForeignPtr >=> newGenBlackVolTermStructure
withBlackVolatilitySurfaceDelta :: BlackVolatilitySurfaceDelta -> (Ptr CBlackVolatilitySurfaceDelta' -> IO b) -> IO b
withBlackVolatilitySurfaceDelta = withForeignPtr . ptr . peel . peel . getTermStructure

peekOptionletVolatilityStructure :: Ptr COptionletVolatilityStructure' -> IO OptionletVolatilityStructure
peekOptionletVolatilityStructure = newCastForeignPtr >=> newGenOptionletVolatilityStructure
withOptionletVolatilityStructure :: GenOptionletVolatilityStructure ov -> (Ptr COptionletVolatilityStructure' -> IO b) -> IO b
withOptionletVolatilityStructure = withGenForeignPtr . peel . peel . getTermStructure
withMaybeOptionletVolatilityStructure :: Maybe (GenOptionletVolatilityStructure ov) -> (Ptr COptionletVolatilityStructure' -> IO b) -> IO b
withMaybeOptionletVolatilityStructure x f = maybe (f nullPtr) (`withOptionletVolatilityStructure` f) x
newGenOptionletVolatilityStructure :: GenForeignPtr ov COptionletVolatilityStructure' -> IO (GenOptionletVolatilityStructure ov)
newGenOptionletVolatilityStructure = pure . GenTermStructure . newAnyOf . newAnyOf
peekRelinkableOptionletVolatilityStructure :: Ptr CRelinkableOptionletVolatilityStructure' -> IO RelinkableOptionletVolatilityStructure
peekRelinkableOptionletVolatilityStructure = newGenForeignPtr >=> newGenOptionletVolatilityStructure
withRelinkableOptionletVolatilityStructure :: RelinkableOptionletVolatilityStructure -> (Ptr CRelinkableOptionletVolatilityStructure' -> IO b) -> IO b
withRelinkableOptionletVolatilityStructure = withForeignPtr . ptr . peel . peel . getTermStructure
peekSwaptionVolatilityStructure :: Ptr CSwaptionVolatilityStructure' -> IO SwaptionVolatilityStructure
peekSwaptionVolatilityStructure = newCastForeignPtr >=> newGenSwaptionVolatilityStructure
withSwaptionVolatilityStructure :: GenSwaptionVolatilityStructure sv -> (Ptr CSwaptionVolatilityStructure' -> IO b) -> IO b
withSwaptionVolatilityStructure = withGenForeignPtr . peel . peel . getTermStructure
withMaybeSwaptionVolatilityStructure :: Maybe (GenSwaptionVolatilityStructure sv) -> (Ptr CSwaptionVolatilityStructure' -> IO b) -> IO b
withMaybeSwaptionVolatilityStructure x f = maybe (f nullPtr) (`withSwaptionVolatilityStructure` f) x
newGenSwaptionVolatilityStructure :: GenForeignPtr sv CSwaptionVolatilityStructure' -> IO (GenSwaptionVolatilityStructure sv)
newGenSwaptionVolatilityStructure = pure . GenTermStructure . newAnyOf . newAnyOf
peekRelinkableSwaptionVolatilityStructure :: Ptr CRelinkableSwaptionVolatilityStructure' -> IO RelinkableSwaptionVolatilityStructure
peekRelinkableSwaptionVolatilityStructure = newGenForeignPtr >=> newGenSwaptionVolatilityStructure
withRelinkableSwaptionVolatilityStructure :: RelinkableSwaptionVolatilityStructure -> (Ptr CRelinkableSwaptionVolatilityStructure' -> IO b) -> IO b
withRelinkableSwaptionVolatilityStructure = withForeignPtr . ptr . peel . peel . getTermStructure
peekSabrSwaptionVolatilityCube :: Ptr CSabrSwaptionVolatilityCube' -> IO SabrSwaptionVolatilityCube
peekSabrSwaptionVolatilityCube = newGenForeignPtr >=> newGenSwaptionVolatilityStructure
withSabrSwaptionVolatilityCube :: SabrSwaptionVolatilityCube -> (Ptr CSabrSwaptionVolatilityCube' -> IO b) -> IO b
withSabrSwaptionVolatilityCube = withForeignPtr . ptr . peel . peel . getTermStructure
peekInterpolatedSwaptionVolatilityCube :: Ptr CInterpolatedSwaptionVolatilityCube' -> IO InterpolatedSwaptionVolatilityCube
peekInterpolatedSwaptionVolatilityCube = newGenForeignPtr >=> newGenSwaptionVolatilityStructure
withInterpolatedSwaptionVolatilityCube :: InterpolatedSwaptionVolatilityCube -> (Ptr CInterpolatedSwaptionVolatilityCube' -> IO b) -> IO b
withInterpolatedSwaptionVolatilityCube = withForeignPtr . ptr . peel . peel . getTermStructure
peekCapFloorTermVolSurface :: Ptr CCapFloorTermVolSurface' -> IO CapFloorTermVolSurface
peekCapFloorTermVolSurface = peekGenVolatilityTermStructure
peekLocalVolTermStructure :: Ptr CLocalVolTermStructure' -> IO LocalVolTermStructure
peekLocalVolTermStructure = peekGenVolatilityTermStructure
withLocalVolTermStructure :: LocalVolTermStructure -> (Ptr CLocalVolTermStructure' -> IO b) -> IO b
withLocalVolTermStructure = withGenVolatilityTermStructure
withMaybeLocalVolTermStructure :: Maybe LocalVolTermStructure -> (Ptr CLocalVolTermStructure' -> IO b) -> IO b
withMaybeLocalVolTermStructure x f = maybe (f nullPtr) (`withGenVolatilityTermStructure` f) x
peekCallableBondVolatilityStructure :: Ptr CCallableBondVolatilityStructure' -> IO CallableBondVolatilityStructure
peekCallableBondVolatilityStructure = GenTermStructure <.> newGenForeignPtr
peekDefaultProbabilityTermStructure :: Ptr CDefaultProbabilityTermStructure' -> IO DefaultProbabilityTermStructure
peekDefaultProbabilityTermStructure = GenTermStructure <.> newGenForeignPtr
withMaybeDefaultProbabilityTermStructure :: Maybe DefaultProbabilityTermStructure -> (Ptr CDefaultProbabilityTermStructure' -> IO b) -> IO b
withMaybeDefaultProbabilityTermStructure x f = maybe (f nullPtr) (`withGenTermStructure` f) x
peekZeroInflationTermStructure :: Ptr CZeroInflationTermStructure' -> IO ZeroInflationTermStructure
peekZeroInflationTermStructure = GenTermStructure <.> newGenForeignPtr
withMaybeZeroInflationTermStructure :: Maybe ZeroInflationTermStructure -> (Ptr CZeroInflationTermStructure' -> IO b) -> IO b
withMaybeZeroInflationTermStructure x f = maybe (f nullPtr) (`withGenTermStructure` f) x
peekYoYInflationTermStructure :: Ptr CYoYInflationTermStructure' -> IO YoYInflationTermStructure
peekYoYInflationTermStructure = GenTermStructure <.> newGenForeignPtr
withMaybeYoYInflationTermStructure :: Maybe YoYInflationTermStructure -> (Ptr CYoYInflationTermStructure' -> IO b) -> IO b
withMaybeYoYInflationTermStructure x f = maybe (f nullPtr) (`withGenTermStructure` f) x

asYieldTermStructure :: GenYieldTermStructure y -> IO YieldTermStructure
asYieldTermStructure = transferGenForeignPtr peekYieldTermStructure . peel . getTermStructure
peekYieldTermStructure :: Ptr CYieldTermStructure' -> IO YieldTermStructure
peekYieldTermStructure = newCastForeignPtr >=> newGenYieldTermStructure
withYieldTermStructure :: GenYieldTermStructure y -> (Ptr CYieldTermStructure' -> IO b) -> IO b
withYieldTermStructure = withGenForeignPtr . peel . getTermStructure
withMaybeYieldTermStructure :: Maybe (GenYieldTermStructure y) -> (Ptr CYieldTermStructure' -> IO b) -> IO b
withMaybeYieldTermStructure x f = maybe (f nullPtr) (`withYieldTermStructure` f) x
newGenYieldTermStructure :: GenForeignPtr y CYieldTermStructure' -> IO (GenYieldTermStructure y)
newGenYieldTermStructure = pure . GenTermStructure . newAnyOf

peekFittedBondDiscountCurve :: Ptr CFittedBondDiscountCurve' -> IO FittedBondDiscountCurve
peekFittedBondDiscountCurve = newGenForeignPtr >=> newGenYieldTermStructure
peekRelinkableYieldTermStructure :: Ptr CRelinkableYieldTermStructure' -> IO RelinkableYieldTermStructure
peekRelinkableYieldTermStructure = newGenForeignPtr >=> newGenYieldTermStructure
-- | Reach the relinkable handle itself, for the operations that only it has ('linkTo',
-- 'currentLink'). Ordinary curve arguments go through 'withYieldTermStructure' instead,
-- which upcasts.
withRelinkableYieldTermStructure :: RelinkableYieldTermStructure -> (Ptr CRelinkableYieldTermStructure' -> IO b) -> IO b
withRelinkableYieldTermStructure = withForeignPtr . ptr . peel . getTermStructure
withFittedBondDiscountCurve :: FittedBondDiscountCurve -> (Ptr CFittedBondDiscountCurve' -> IO b) -> IO b
withFittedBondDiscountCurve = withForeignPtr . ptr . peel . getTermStructure

-- | > StochasticProcess
-- >   ExtOUWithJumpsProcess
-- >   GJRGARCHProcess
-- >   HybridHestonHullWhiteProcess
-- >   KlugeExtOUProcess
-- >   LiborForwardModelProcess
-- >   StochasticProcessArray
-- >   HestonProcess
-- >     BatesProcess
-- >   StochasticProcess1D
-- >     ExtendedOrnsteinUhlenbeckProcess
-- >     HullWhiteForwardProcess
-- >     HullWhiteProcess
-- >     Merton76Process
-- >     VarianceGammaProcess
-- >     GeneralizedBlackScholesProcess
-- >       BlackProcess
type StochasticProcess = GenStochasticProcess CStochasticProcess
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
newtype GenStochasticProcess p = GenStochasticProcess {getStochasticProcess :: GenForeignPtr p CStochasticProcess'}
type CStochasticProcess = ForeignPtr CStochasticProcess'
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
type GenHestonProcess hp = GenStochasticProcess (AnyOf CHestonProcess' hp)
type CHestonProcess = ForeignPtr CHestonProcess'
type HestonProcess = GenHestonProcess CHestonProcess
type GenStochasticProcess1D p1d = GenStochasticProcess (AnyOf CStochasticProcess1D' p1d)
type CStochasticProcess1D = ForeignPtr CStochasticProcess1D'
type StochasticProcess1D = GenStochasticProcess1D CStochasticProcess1D
type CMerton76Process = ForeignPtr CMerton76Process'
type Merton76Process = GenStochasticProcess1D CMerton76Process
type CVarianceGammaProcess = ForeignPtr CVarianceGammaProcess'
type VarianceGammaProcess = GenStochasticProcess1D CVarianceGammaProcess
type GenGeneralizedBlackScholesProcess gbs = GenStochasticProcess1D (AnyOf CGeneralizedBlackScholesProcess' gbs)
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
asStochasticProcess :: GenStochasticProcess p -> IO StochasticProcess
asStochasticProcess = transferGenForeignPtr peekStochasticProcess . getStochasticProcess
peekStochasticProcess :: Ptr CStochasticProcess' -> IO StochasticProcess
peekStochasticProcess = GenStochasticProcess <.> newCastForeignPtr
withStochasticProcess :: GenStochasticProcess p -> (Ptr CStochasticProcess' -> IO b) -> IO b
withStochasticProcess = withGenForeignPtr . getStochasticProcess
withGenStochasticProcess :: GenStochasticProcess (ForeignPtr p) -> (Ptr p -> IO b) -> IO b
withGenStochasticProcess = withForeignPtr . ptr . getStochasticProcess
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
asHestonProcess :: GenHestonProcess hp -> IO HestonProcess
asHestonProcess = transferGenForeignPtr peekHestonProcess . peel . getStochasticProcess
peekHestonProcess :: Ptr CHestonProcess' -> IO HestonProcess
peekHestonProcess = newCastForeignPtr >=> newGenHestonProcess
withHestonProcess :: GenHestonProcess hp -> (Ptr CHestonProcess' -> IO b) -> IO b
withHestonProcess = withGenForeignPtr . peel . getStochasticProcess
newGenHestonProcess :: GenForeignPtr hp CHestonProcess' -> IO (GenHestonProcess hp)
newGenHestonProcess = pure . GenStochasticProcess . newAnyOf
peekGenHestonProcess :: (Finalizable hp, Upcastable hp, Base hp ~ CHestonProcess') => Ptr hp -> IO (GenHestonProcess (ForeignPtr hp))
peekGenHestonProcess = newGenForeignPtr >=> newGenHestonProcess
asStochasticProcess1D :: GenStochasticProcess1D p1d -> IO StochasticProcess1D
asStochasticProcess1D = transferGenForeignPtr peekStochasticProcess1D . peel . getStochasticProcess
peekStochasticProcess1D :: Ptr CStochasticProcess1D' -> IO StochasticProcess1D
peekStochasticProcess1D = newCastForeignPtr >=> newGenStochasticProcess1D
withStochasticProcess1D :: GenStochasticProcess1D p1d -> (Ptr CStochasticProcess1D' -> IO b) -> IO b
withStochasticProcess1D = withGenForeignPtr . peel . getStochasticProcess
withStochasticProcess1DArray :: [GenStochasticProcess1D p1d] -> ((CUInt, Ptr (Ptr CStochasticProcess1D')) -> IO b) -> IO b
withStochasticProcess1DArray = withGenArray withStochasticProcess1D
newGenStochasticProcess1D :: GenForeignPtr p1d CStochasticProcess1D' -> IO (GenStochasticProcess1D p1d)
newGenStochasticProcess1D = pure . GenStochasticProcess . newAnyOf
peekGenStochasticProcess1D :: (Finalizable p1d, Upcastable p1d, Base p1d ~ CStochasticProcess1D') => Ptr p1d -> IO (GenStochasticProcess1D (ForeignPtr p1d))
peekGenStochasticProcess1D = newGenForeignPtr >=> newGenStochasticProcess1D
withGenStochasticProcess1D :: GenStochasticProcess1D (ForeignPtr p1d) -> (Ptr p1d -> IO b) -> IO b
withGenStochasticProcess1D = withForeignPtr . ptr . peel . getStochasticProcess
peekBatesProcess :: Ptr CBatesProcess' -> IO BatesProcess
peekBatesProcess = peekGenHestonProcess
withBatesProcess :: BatesProcess -> (Ptr CBatesProcess' -> IO b) -> IO b
withBatesProcess = withForeignPtr . ptr . peel . getStochasticProcess
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
asGeneralizedBlackScholesProcess :: GenGeneralizedBlackScholesProcess gbs -> IO GeneralizedBlackScholesProcess
asGeneralizedBlackScholesProcess = transferGenForeignPtr peekGeneralizedBlackScholesProcess . peel . peel . getStochasticProcess
peekGeneralizedBlackScholesProcess :: Ptr CGeneralizedBlackScholesProcess' -> IO GeneralizedBlackScholesProcess
peekGeneralizedBlackScholesProcess = newCastForeignPtr >=> newGenGeneralizedBlackScholesProcess
withGeneralizedBlackScholesProcess :: GenGeneralizedBlackScholesProcess gbs -> (Ptr CGeneralizedBlackScholesProcess' -> IO b) -> IO b
withGeneralizedBlackScholesProcess = withGenForeignPtr . peel . peel . getStochasticProcess
newGenGeneralizedBlackScholesProcess :: GenForeignPtr gbs CGeneralizedBlackScholesProcess' -> IO (GenGeneralizedBlackScholesProcess gbs)
newGenGeneralizedBlackScholesProcess = pure . GenStochasticProcess . newAnyOf . newAnyOf
peekBlackProcess :: Ptr CBlackProcess' -> IO BlackProcess
peekBlackProcess = newGenForeignPtr >=> newGenGeneralizedBlackScholesProcess
withBlackProcess :: BlackProcess -> (Ptr CBlackProcess' -> IO b) -> IO b
withBlackProcess = withForeignPtr . ptr . peel . peel . getStochasticProcess

-- | > CalibratedModel
-- >  LiborForwardModel + AffineModel
-- >  GJRGARCHModel
-- >  PiecewiseTimeDependentHestonModel
-- >  HestonModel
-- >    BatesModel
-- >      BatesDetJumpModel
-- >    BatesDoubleExpModel
-- >      BatesDoubleExpDetJumpModel
-- >  ShortRateModel
-- >    G2 + AffineModel
-- >    OneFactorAffineModel + AffineModel
-- >      HullWhite + AffineModel
-- >  Gsr + Gaussian1dModel
-- >  MarkovFunctional + Gaussian1dModel
type CalibratedModel = GenCalibratedModel CCalibratedModel
data CCalibratedModel'
data CGJRGARCHModel'
data CLiborForwardModel'
data CGsr'
data CMarkovFunctional'
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
newtype GenCalibratedModel m = GenCalibratedModel {getCalibratedModel :: GenForeignPtr m CCalibratedModel'}
type CCalibratedModel = ForeignPtr CCalibratedModel'
type CLiborForwardModel = ForeignPtr CLiborForwardModel'
type LiborForwardModel = GenCalibratedModel CLiborForwardModel
type CGJRGARCHModel = ForeignPtr CGJRGARCHModel'
type GJRGARCHModel = GenCalibratedModel CGJRGARCHModel
type CGsr = ForeignPtr CGsr'
type Gsr = GenCalibratedModel CGsr
type CMarkovFunctional = ForeignPtr CMarkovFunctional'
type MarkovFunctional = GenCalibratedModel CMarkovFunctional
type CPiecewiseTimeDependentHestonModel = ForeignPtr CPiecewiseTimeDependentHestonModel'
type PiecewiseTimeDependentHestonModel = GenCalibratedModel CPiecewiseTimeDependentHestonModel
type GenHestonModel hm = GenCalibratedModel (AnyOf CHestonModel' hm)
type CHestonModel = ForeignPtr CHestonModel'
type HestonModel = GenHestonModel CHestonModel
type GenShortRateModel sm = GenCalibratedModel (AnyOf CShortRateModel' sm)
type CShortRateModel = ForeignPtr CShortRateModel'
type ShortRateModel = GenShortRateModel CShortRateModel
type GenBatesModel bm = GenHestonModel (AnyOf CBatesModel' bm)
type CBatesModel = ForeignPtr CBatesModel'
type BatesModel = GenBatesModel CBatesModel
type CBatesDetJumpModel = ForeignPtr CBatesDetJumpModel'
type BatesDetJumpModel = GenBatesModel CBatesDetJumpModel
type GenBatesDoubleExpModel bdem = GenHestonModel (AnyOf CBatesDoubleExpModel' bdem)
type CBatesDoubleExpModel = ForeignPtr CBatesDoubleExpModel'
type BatesDoubleExpModel = GenBatesDoubleExpModel CBatesDoubleExpModel
type CBatesDoubleExpDetJumpModel = ForeignPtr CBatesDoubleExpDetJumpModel'
type BatesDoubleExpDetJumpModel = GenBatesDoubleExpModel CBatesDoubleExpDetJumpModel
type GenOneFactorAffineModel om = GenShortRateModel (AnyOf COneFactorAffineModel' om)
type COneFactorAffineModel = ForeignPtr COneFactorAffineModel'
type OneFactorAffineModel = GenOneFactorAffineModel COneFactorAffineModel
type CHullWhite = ForeignPtr CHullWhite'
type HullWhite = GenOneFactorAffineModel CHullWhite
type CG2 = ForeignPtr CG2'
type G2 = GenShortRateModel CG2
foreign import ccall unsafe "ql.h &qlFreeCalibratedModel" qlFreeCalibratedModel :: FinalizerPtr CCalibratedModel'
foreign import ccall unsafe "ql.h &qlFreeLiborForwardModel" qlFreeLiborForwardModel :: FinalizerPtr CLiborForwardModel'
foreign import ccall unsafe "ql.h &qlFreeGJRGARCHModel" qlFreeGJRGARCHModel :: FinalizerPtr CGJRGARCHModel'
foreign import ccall unsafe "ql.h &qlFreeGsr" qlFreeGsr :: FinalizerPtr CGsr'
foreign import ccall unsafe "ql.h &qlFreeMarkovFunctional" qlFreeMarkovFunctional :: FinalizerPtr CMarkovFunctional'
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
foreign import ccall "ql.h qlGsrAsCalibratedModel" qlGsrAsCalibratedModel :: Ptr CGsr' -> IO (Ptr CCalibratedModel')
foreign import ccall "ql.h qlMarkovFunctionalAsCalibratedModel" qlMarkovFunctionalAsCalibratedModel :: Ptr CMarkovFunctional' -> IO (Ptr CCalibratedModel')
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
instance Finalizable CGsr' where finalize = qlFreeGsr
instance Finalizable CMarkovFunctional' where finalize = qlFreeMarkovFunctional
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
instance Upcastable CGsr' where {type Base CGsr' = CCalibratedModel'; upcast = qlGsrAsCalibratedModel}
instance Upcastable CMarkovFunctional' where {type Base CMarkovFunctional' = CCalibratedModel'; upcast = qlMarkovFunctionalAsCalibratedModel}
instance Upcastable CHestonModel' where {type Base CHestonModel' = CCalibratedModel'; upcast = qlHestonModelAsCalibratedModel}
instance Upcastable CShortRateModel' where {type Base CShortRateModel' = CCalibratedModel'; upcast = qlShortRateModelAsCalibratedModel}
instance Upcastable CBatesModel' where {type Base CBatesModel' = CHestonModel'; upcast = qlBatesModelAsHestonModel}
instance Upcastable CBatesDetJumpModel' where {type Base CBatesDetJumpModel' = CBatesModel'; upcast = qlBatesDetJumpModelAsBatesModel}
instance Upcastable CBatesDoubleExpModel' where {type Base CBatesDoubleExpModel' = CHestonModel'; upcast = qlBatesDoubleExpModelAsHestonModel}
instance Upcastable CBatesDoubleExpDetJumpModel' where {type Base CBatesDoubleExpDetJumpModel' = CBatesDoubleExpModel'; upcast = qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel}
instance Upcastable COneFactorAffineModel' where {type Base COneFactorAffineModel' = CShortRateModel'; upcast = qlOneFactorAffineModelAsShortRateModel}
instance Upcastable CHullWhite' where {type Base CHullWhite' = COneFactorAffineModel'; upcast = qlHullWhiteAsOneFactorAffineModel}
instance Upcastable CG2' where {type Base CG2' = CShortRateModel'; upcast = qlG2AsShortRateModel}
asCalibratedModel :: GenCalibratedModel m -> IO CalibratedModel
asCalibratedModel = transferGenForeignPtr peekCalibratedModel . getCalibratedModel
peekCalibratedModel :: Ptr CCalibratedModel' -> IO CalibratedModel
peekCalibratedModel = GenCalibratedModel <.> newCastForeignPtr
withCalibratedModel :: GenCalibratedModel m -> (Ptr CCalibratedModel' -> IO b) -> IO b
withCalibratedModel = withGenForeignPtr . getCalibratedModel
withGenCalibratedModel :: GenCalibratedModel (ForeignPtr m) -> (Ptr m -> IO b) -> IO b
withGenCalibratedModel = withForeignPtr . ptr . getCalibratedModel
peekLiborForwardModel :: Ptr CLiborForwardModel' -> IO LiborForwardModel
peekLiborForwardModel = GenCalibratedModel <.> newGenForeignPtr
peekGJRGARCHModel :: Ptr CGJRGARCHModel' -> IO GJRGARCHModel
peekGJRGARCHModel = GenCalibratedModel <.> newGenForeignPtr
peekGsr :: Ptr CGsr' -> IO Gsr
peekGsr = GenCalibratedModel <.> newGenForeignPtr
peekMarkovFunctional :: Ptr CMarkovFunctional' -> IO MarkovFunctional
peekMarkovFunctional = GenCalibratedModel <.> newGenForeignPtr
peekPiecewiseTimeDependentHestonModel :: Ptr CPiecewiseTimeDependentHestonModel' -> IO PiecewiseTimeDependentHestonModel
peekPiecewiseTimeDependentHestonModel = GenCalibratedModel <.> newGenForeignPtr

asHestonModel :: GenHestonModel hm -> IO HestonModel
asHestonModel = transferGenForeignPtr peekHestonModel . peel . getCalibratedModel
peekHestonModel :: Ptr CHestonModel' -> IO HestonModel
peekHestonModel = newCastForeignPtr >=> newGenHestonModel
withHestonModel :: GenHestonModel hm -> (Ptr CHestonModel' -> IO b) -> IO b
withHestonModel = withGenForeignPtr . peel . getCalibratedModel
newGenHestonModel :: GenForeignPtr hm CHestonModel' -> IO (GenHestonModel hm)
newGenHestonModel = pure . GenCalibratedModel . newAnyOf

asShortRateModel :: GenShortRateModel sm -> IO ShortRateModel
asShortRateModel  = transferGenForeignPtr peekShortRateModel . peel . getCalibratedModel
peekShortRateModel :: Ptr CShortRateModel' -> IO ShortRateModel
peekShortRateModel = newCastForeignPtr >=> newGenShortRateModel
withShortRateModel :: GenShortRateModel sm -> (Ptr CShortRateModel' -> IO b) -> IO b
withShortRateModel = withGenForeignPtr . peel . getCalibratedModel
newGenShortRateModel :: GenForeignPtr sm CShortRateModel' -> IO (GenShortRateModel sm)
newGenShortRateModel = pure . GenCalibratedModel . newAnyOf
peekGenShortRateModel :: (Finalizable sm, Upcastable sm, Base sm ~ CShortRateModel') => Ptr sm -> IO (GenShortRateModel (ForeignPtr sm))
peekGenShortRateModel = newGenForeignPtr >=> newGenShortRateModel

asBatesModel :: GenBatesModel bm -> IO BatesModel
asBatesModel = transferGenForeignPtr peekBatesModel . peel . peel . getCalibratedModel
peekBatesModel :: Ptr CBatesModel' -> IO BatesModel
peekBatesModel = newCastForeignPtr >=> newGenBatesModel
withBatesModel :: GenBatesModel bm -> (Ptr CBatesModel' -> IO b) -> IO b
withBatesModel = withGenForeignPtr . peel . peel . getCalibratedModel
newGenBatesModel :: GenForeignPtr bm CBatesModel' -> IO (GenBatesModel bm)
newGenBatesModel = pure . GenCalibratedModel . newAnyOf . newAnyOf
peekBatesDetJumpModel :: Ptr CBatesDetJumpModel' -> IO BatesDetJumpModel
peekBatesDetJumpModel = newGenForeignPtr >=> newGenBatesModel
withBatesDetJumpModel :: BatesDetJumpModel -> (Ptr CBatesDetJumpModel' -> IO b) -> IO b
withBatesDetJumpModel = withForeignPtr . ptr . peel . peel . getCalibratedModel

asBatesDoubleExpModel :: GenBatesDoubleExpModel bdem -> IO BatesDoubleExpModel
asBatesDoubleExpModel = transferGenForeignPtr peekBatesDoubleExpModel . peel . peel . getCalibratedModel
peekBatesDoubleExpModel :: Ptr CBatesDoubleExpModel' -> IO BatesDoubleExpModel
peekBatesDoubleExpModel = newCastForeignPtr >=> newGenBatesDoubleExpModel
withBatesDoubleExpModel :: GenBatesDoubleExpModel bdem -> (Ptr CBatesDoubleExpModel' -> IO b) -> IO b
withBatesDoubleExpModel = withGenForeignPtr . peel . peel . getCalibratedModel
newGenBatesDoubleExpModel :: GenForeignPtr bdem CBatesDoubleExpModel' -> IO (GenBatesDoubleExpModel bdem)
newGenBatesDoubleExpModel = pure . GenCalibratedModel . newAnyOf . newAnyOf
peekBatesDoubleExpDetJumpModel :: Ptr CBatesDoubleExpDetJumpModel' -> IO BatesDoubleExpDetJumpModel
peekBatesDoubleExpDetJumpModel = newGenForeignPtr >=> newGenBatesDoubleExpModel
withBatesDoubleExpDetJumpModel :: BatesDoubleExpDetJumpModel -> (Ptr CBatesDoubleExpDetJumpModel' -> IO b) -> IO b
withBatesDoubleExpDetJumpModel = withForeignPtr . ptr . peel . peel . getCalibratedModel

asOneFactorAffineModel :: GenOneFactorAffineModel om -> IO OneFactorAffineModel
asOneFactorAffineModel = transferGenForeignPtr peekOneFactorAffineModel . peel . peel . getCalibratedModel
peekOneFactorAffineModel :: Ptr COneFactorAffineModel' -> IO OneFactorAffineModel
peekOneFactorAffineModel = newCastForeignPtr >=> newGenOneFactorAffineModel
withOneFactorAffineModel :: GenOneFactorAffineModel om -> (Ptr COneFactorAffineModel' -> IO b) -> IO b
withOneFactorAffineModel = withGenForeignPtr . peel . peel . getCalibratedModel
newGenOneFactorAffineModel :: GenForeignPtr om COneFactorAffineModel' -> IO (GenOneFactorAffineModel om)
newGenOneFactorAffineModel = pure . GenCalibratedModel . newAnyOf . newAnyOf

peekHullWhite :: Ptr CHullWhite' -> IO HullWhite
peekHullWhite = newGenForeignPtr >=> newGenOneFactorAffineModel
withHullWhite :: HullWhite -> (Ptr CHullWhite' -> IO b) -> IO b
withHullWhite = withForeignPtr . ptr . peel . peel . getCalibratedModel

peekG2 :: Ptr CG2' -> IO G2
peekG2 = peekGenShortRateModel
withG2 :: G2 -> (Ptr CG2' -> IO b) -> IO b
withG2 = withForeignPtr . ptr . peel . getCalibratedModel

foreign import ccall "ql.h qlOneFactorAffineModelAsAffineModel" qlOneFactorAffineModelAsAffineModel :: Ptr COneFactorAffineModel' -> IO (Ptr CAffineModel')
foreign import ccall "ql.h qlLiborForwardModelAsAffineModel" qlLiborForwardModelAsAffineModel :: Ptr CLiborForwardModel' -> IO (Ptr CAffineModel')
foreign import ccall "ql.h qlG2AsAffineModel" qlG2AsAffineModel :: Ptr CG2' -> IO (Ptr CAffineModel')
foreign import ccall "ql.h qlHullWhiteAsAffineModel" qlHullWhiteAsAffineModel :: Ptr CHullWhite' -> IO (Ptr CAffineModel')

data AffineModel = HullWhite HullWhite | G2 G2 | OneFactorAffineModel OneFactorAffineModel | LiborForwardModel LiborForwardModel
withUpcast :: Finalizable b => (Ptr a -> IO (Ptr b)) -> (Ptr b -> IO r) -> Ptr a -> IO r
withUpcast up f p = bracket (up p) freeUpcast f
withAffineModel :: AffineModel -> (Ptr CAffineModel' -> IO b) -> IO b
withAffineModel (HullWhite m) f = withHullWhite m (withUpcast qlHullWhiteAsAffineModel f)
withAffineModel (G2 m) f = withG2 m (withUpcast qlG2AsAffineModel f)
withAffineModel (OneFactorAffineModel m) f = withOneFactorAffineModel m (withUpcast qlOneFactorAffineModelAsAffineModel f)
withAffineModel (LiborForwardModel m) f = withGenCalibratedModel m (withUpcast qlLiborForwardModelAsAffineModel f)

data CGaussian1dModel'
foreign import ccall unsafe "ql.h &qlFreeGaussian1dModel" qlFreeGaussian1dModel :: FinalizerPtr CGaussian1dModel'
instance Finalizable CGaussian1dModel' where finalize = qlFreeGaussian1dModel
foreign import ccall "ql.h qlGsrAsGaussian1dModel" qlGsrAsGaussian1dModel :: Ptr CGsr' -> IO (Ptr CGaussian1dModel')
foreign import ccall "ql.h qlMarkovFunctionalAsGaussian1dModel" qlMarkovFunctionalAsGaussian1dModel :: Ptr CMarkovFunctional' -> IO (Ptr CGaussian1dModel')
data Gaussian1dModel = Gsr Gsr | MarkovFunctional MarkovFunctional
withGaussian1dModel :: Gaussian1dModel -> (Ptr CGaussian1dModel' -> IO b) -> IO b
withGaussian1dModel (Gsr m) f = withGenCalibratedModel m (withUpcast qlGsrAsGaussian1dModel f)
withGaussian1dModel (MarkovFunctional m) f = withGenCalibratedModel m (withUpcast qlMarkovFunctionalAsGaussian1dModel f)

-- | > Instrument*
-- >  Forward*
-- >    BondForward
-- >  ForwardRateAgreement
-- >  FxForward
-- >  VarianceSwap
-- >  VarianceOption
-- >  Option*
-- >    CdsOption
-- >    MultiAssetOption
-- >      MargrabeOption
-- >    OneAssetOption
-- >      BarrierOption
-- >      DoubleBarrierOption
-- >      VanillaOption
-- >      QuantoVanillaOption
-- >      QuantoForwardVanillaOption
-- >      QuantoBarrierOption
-- >    Swaption
-- >  Swap*
-- >    VanillaSwap
-- >    AssetSwap
-- >    BMASwap
-- >    OvernightIndexedSwap
-- >    ZeroCouponInflationSwap
-- >    YearOnYearInflationSwap
-- >    CPISwap
-- >    ZeroCouponSwap
-- >    EquityTotalReturnSwap
-- >  CreditDefaultSwap
-- >  CapFloor
-- >  Bond
-- >    ConvertibleBond
-- >    FixedRateBond
-- >    CallableBond
-- >    CPIBond
type Instrument = GenInstrument CInstrument
data CInstrument'
newtype GenInstrument i = GenInstrument {getInstrument :: GenForeignPtr i CInstrument'}
type CInstrument = ForeignPtr CInstrument'
foreign import ccall unsafe "ql.h &qlFreeInstrument" qlFreeInstrument :: FinalizerPtr CInstrument'
instance Finalizable CInstrument' where finalize = qlFreeInstrument
asInstrument :: GenInstrument i -> IO Instrument
asInstrument = transferGenForeignPtr peekInstrument . getInstrument
peekInstrument :: Ptr CInstrument' -> IO Instrument
peekInstrument = GenInstrument <.> newCastForeignPtr
withInstrument :: GenInstrument i -> (Ptr CInstrument' -> IO b) -> IO b
withInstrument = withGenForeignPtr . getInstrument
withGenInstrument :: GenInstrument (ForeignPtr i) -> (Ptr i -> IO b) -> IO b
withGenInstrument = withForeignPtr . ptr . getInstrument

data CForwardRateAgreement'
type CForwardRateAgreement = ForeignPtr CForwardRateAgreement'
type ForwardRateAgreement = GenInstrument CForwardRateAgreement
foreign import ccall unsafe "ql.h &qlFreeForwardRateAgreement" qlFreeForwardRateAgreement :: FinalizerPtr CForwardRateAgreement'
instance Finalizable CForwardRateAgreement' where finalize = qlFreeForwardRateAgreement
foreign import ccall "ql.h qlForwardRateAgreementAsInstrument" qlForwardRateAgreementAsInstrument :: Ptr CForwardRateAgreement' -> IO (Ptr CInstrument')
instance Upcastable CForwardRateAgreement' where {type Base CForwardRateAgreement' = CInstrument'; upcast = qlForwardRateAgreementAsInstrument}
peekForwardRateAgreement :: Ptr CForwardRateAgreement' -> IO ForwardRateAgreement
peekForwardRateAgreement = GenInstrument <.> newGenForeignPtr

data CFxForward'
type CFxForward = ForeignPtr CFxForward'
type FxForward = GenInstrument CFxForward
foreign import ccall unsafe "ql.h &qlFreeFxForward" qlFreeFxForward :: FinalizerPtr CFxForward'
instance Finalizable CFxForward' where finalize = qlFreeFxForward
foreign import ccall "ql.h qlFxForwardAsInstrument" qlFxForwardAsInstrument :: Ptr CFxForward' -> IO (Ptr CInstrument')
instance Upcastable CFxForward' where {type Base CFxForward' = CInstrument'; upcast = qlFxForwardAsInstrument}
peekFxForward :: Ptr CFxForward' -> IO FxForward
peekFxForward = GenInstrument <.> newGenForeignPtr

data CCreditDefaultSwap'
type CCreditDefaultSwap = ForeignPtr CCreditDefaultSwap'
type CreditDefaultSwap = GenInstrument CCreditDefaultSwap
foreign import ccall unsafe "ql.h &qlFreeCreditDefaultSwap" qlFreeCreditDefaultSwap :: FinalizerPtr CCreditDefaultSwap'
instance Finalizable CCreditDefaultSwap' where finalize = qlFreeCreditDefaultSwap
foreign import ccall "ql.h qlCreditDefaultSwapAsInstrument" qlCreditDefaultSwapAsInstrument :: Ptr CCreditDefaultSwap' -> IO (Ptr CInstrument')
instance Upcastable CCreditDefaultSwap' where {type Base CCreditDefaultSwap' = CInstrument'; upcast = qlCreditDefaultSwapAsInstrument}
peekCreditDefaultSwap :: Ptr CCreditDefaultSwap' -> IO CreditDefaultSwap
peekCreditDefaultSwap = GenInstrument <.> newGenForeignPtr

data CVarianceSwap'
type CVarianceSwap = ForeignPtr CVarianceSwap'
type VarianceSwap = GenInstrument CVarianceSwap
foreign import ccall unsafe "ql.h &qlFreeVarianceSwap" qlFreeVarianceSwap :: FinalizerPtr CVarianceSwap'
instance Finalizable CVarianceSwap' where finalize = qlFreeVarianceSwap
foreign import ccall "ql.h qlVarianceSwapAsInstrument" qlVarianceSwapAsInstrument :: Ptr CVarianceSwap' -> IO (Ptr CInstrument')
instance Upcastable CVarianceSwap' where {type Base CVarianceSwap' = CInstrument'; upcast = qlVarianceSwapAsInstrument}
peekVarianceSwap :: Ptr CVarianceSwap' -> IO VarianceSwap
peekVarianceSwap = GenInstrument <.> newGenForeignPtr

data CVarianceOption'
type CVarianceOption = ForeignPtr CVarianceOption'
type VarianceOption = GenInstrument CVarianceOption
foreign import ccall unsafe "ql.h &qlFreeVarianceOption" qlFreeVarianceOption :: FinalizerPtr CVarianceOption'
instance Finalizable CVarianceOption' where finalize = qlFreeVarianceOption
foreign import ccall "ql.h qlVarianceOptionAsInstrument" qlVarianceOptionAsInstrument :: Ptr CVarianceOption' -> IO (Ptr CInstrument')
instance Upcastable CVarianceOption' where {type Base CVarianceOption' = CInstrument'; upcast = qlVarianceOptionAsInstrument}
peekVarianceOption :: Ptr CVarianceOption' -> IO VarianceOption
peekVarianceOption = GenInstrument <.> newGenForeignPtr

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
type GenForward f = GenInstrument (AnyOf CForward' f)
type CForward = ForeignPtr CForward'
type Forward = GenForward CForward
foreign import ccall unsafe "ql.h &qlFreeForward" qlFreeForward :: FinalizerPtr CForward'
instance Finalizable CForward' where finalize = qlFreeForward
foreign import ccall "ql.h qlForwardAsInstrument" qlForwardAsInstrument :: Ptr CForward' -> IO (Ptr CInstrument')
instance Upcastable CForward' where {type Base CForward' = CInstrument'; upcast = qlForwardAsInstrument}
asForward :: GenForward f -> IO Forward
asForward = transferGenForeignPtr peekForward . peel . getInstrument
peekForward :: Ptr CForward' -> IO Forward
peekForward = newCastForeignPtr >=> newGenForward
withForward :: GenForward f -> (Ptr CForward' -> IO b) -> IO b
withForward = withGenForeignPtr . peel . getInstrument
newGenForward :: GenForeignPtr f CForward' -> IO (GenForward f)
newGenForward = pure . GenInstrument . newAnyOf
peekGenForward :: (Finalizable f, Upcastable f, Base f ~ CForward') => Ptr f -> IO (GenForward (ForeignPtr f))
peekGenForward = newGenForeignPtr >=> newGenForward
withGenForward :: GenForward (ForeignPtr f) -> (Ptr f -> IO b) -> IO b
withGenForward = withForeignPtr . ptr . peel . getInstrument

data COption'
type GenOption o = GenInstrument (AnyOf COption' o)
type COption = ForeignPtr COption'
type Option = GenOption COption
foreign import ccall unsafe "ql.h &qlFreeOption" qlFreeOption :: FinalizerPtr COption'
instance Finalizable COption' where finalize = qlFreeOption
foreign import ccall "ql.h qlOptionAsInstrument" qlOptionAsInstrument :: Ptr COption' -> IO (Ptr CInstrument')
instance Upcastable COption' where {type Base COption' = CInstrument'; upcast = qlOptionAsInstrument}
asOption :: GenOption o -> IO Option
asOption = transferGenForeignPtr peekOption . peel . getInstrument
peekOption :: Ptr COption' -> IO Option
peekOption = newCastForeignPtr >=> newGenOption
withOption :: GenOption o -> (Ptr COption' -> IO b) -> IO b
withOption = withGenForeignPtr . peel . getInstrument
newGenOption :: GenForeignPtr o COption' -> IO (GenOption o)
newGenOption = pure . GenInstrument . newAnyOf
peekGenOption :: (Finalizable o, Upcastable o, Base o ~ COption') => Ptr o -> IO (GenOption (ForeignPtr o))
peekGenOption = newGenForeignPtr >=> newGenOption
withGenOption :: GenOption (ForeignPtr o) -> (Ptr o -> IO b) -> IO b
withGenOption = withForeignPtr . ptr . peel . getInstrument

data CSwap'
type GenSwap s = GenInstrument (AnyOf CSwap' s)
type CSwap = ForeignPtr CSwap'
type Swap = GenSwap CSwap
foreign import ccall unsafe "ql.h &qlFreeSwap" qlFreeSwap :: FinalizerPtr CSwap'
instance Finalizable CSwap' where finalize = qlFreeSwap
foreign import ccall "ql.h qlSwapAsInstrument" qlSwapAsInstrument :: Ptr CSwap' -> IO (Ptr CInstrument')
instance Upcastable CSwap' where {type Base CSwap' = CInstrument'; upcast = qlSwapAsInstrument}
asSwap :: GenSwap s -> IO Swap
asSwap = transferGenForeignPtr peekSwap . peel . getInstrument
peekSwap :: Ptr CSwap' -> IO Swap
peekSwap = newCastForeignPtr >=> newGenSwap
withSwap :: GenSwap s -> (Ptr CSwap' -> IO b) -> IO b
withSwap = withGenForeignPtr . peel . getInstrument
newGenSwap :: GenForeignPtr s CSwap' -> IO (GenSwap s)
newGenSwap = pure . GenInstrument . newAnyOf
peekGenSwap :: (Finalizable s, Upcastable s, Base s ~ CSwap') => Ptr s -> IO (GenSwap (ForeignPtr s))
peekGenSwap = newGenForeignPtr >=> newGenSwap
withGenSwap :: GenSwap (ForeignPtr s) -> (Ptr s -> IO b) -> IO b
withGenSwap = withForeignPtr . ptr . peel . getInstrument

data CBond'
type GenBond b = GenInstrument (AnyOf CBond' b)
type CBond = ForeignPtr CBond'
type Bond = GenBond CBond
foreign import ccall unsafe "ql.h &qlFreeBond" qlFreeBond :: FinalizerPtr CBond'
instance Finalizable CBond' where finalize = qlFreeBond
foreign import ccall "ql.h qlBondAsInstrument" qlBondAsInstrument :: Ptr CBond' -> IO (Ptr CInstrument')
instance Upcastable CBond' where {type Base CBond' = CInstrument'; upcast = qlBondAsInstrument}
asBond :: GenBond b -> IO Bond
asBond = transferGenForeignPtr peekBond . peel . getInstrument
peekBond :: Ptr CBond' -> IO Bond
peekBond = newCastForeignPtr >=> newGenBond
withBond :: GenBond b -> (Ptr CBond' -> IO r) -> IO r
withBond = withGenForeignPtr . peel . getInstrument
newGenBond :: GenForeignPtr b CBond' -> IO (GenBond b)
newGenBond = pure . GenInstrument . newAnyOf
peekGenBond :: (Finalizable b, Upcastable b, Base b ~ CBond') => Ptr b -> IO (GenBond (ForeignPtr b))
peekGenBond = newGenForeignPtr >=> newGenBond
withGenBond :: GenBond (ForeignPtr b) -> (Ptr b -> IO r) -> IO r
withGenBond = withForeignPtr . ptr . peel . getInstrument

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
withBondForward = withForeignPtr . ptr . peel . getInstrument

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
withConvertibleBond = withForeignPtr . ptr . peel . getInstrument

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
withFixedRateBond = withForeignPtr . ptr . peel . getInstrument

data CCPIBond'
type CCPIBond = ForeignPtr CCPIBond'
type CPIBond = GenBond CCPIBond
foreign import ccall unsafe "ql.h &qlFreeCPIBond" qlFreeCPIBond :: FinalizerPtr CCPIBond'
instance Finalizable CCPIBond' where finalize = qlFreeCPIBond
foreign import ccall "ql.h qlCPIBondAsBond" qlCPIBondAsBond :: Ptr CCPIBond' -> IO (Ptr CBond')
instance Upcastable CCPIBond' where {type Base CCPIBond' = CBond'; upcast = qlCPIBondAsBond}
peekCPIBond :: Ptr CCPIBond' -> IO CPIBond
peekCPIBond = peekGenBond
withCPIBond :: CPIBond -> (Ptr CCPIBond' -> IO b) -> IO b
withCPIBond = withForeignPtr . ptr . peel . getInstrument

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
withCallableBond = withForeignPtr . ptr . peel . getInstrument

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
withVanillaSwap = withForeignPtr . ptr . peel . getInstrument

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
withAssetSwap = withForeignPtr . ptr . peel . getInstrument

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
withBMASwap = withForeignPtr . ptr . peel . getInstrument

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
withOvernightIndexedSwap = withForeignPtr . ptr . peel . getInstrument

data CZeroCouponInflationSwap'
type CZeroCouponInflationSwap = ForeignPtr CZeroCouponInflationSwap'
type ZeroCouponInflationSwap = GenSwap CZeroCouponInflationSwap
foreign import ccall unsafe "ql.h &qlFreeZeroCouponInflationSwap" qlFreeZeroCouponInflationSwap :: FinalizerPtr CZeroCouponInflationSwap'
instance Finalizable CZeroCouponInflationSwap' where finalize = qlFreeZeroCouponInflationSwap
foreign import ccall "ql.h qlZeroCouponInflationSwapAsSwap" qlZeroCouponInflationSwapAsSwap :: Ptr CZeroCouponInflationSwap' -> IO (Ptr CSwap')
instance Upcastable CZeroCouponInflationSwap' where {type Base CZeroCouponInflationSwap' = CSwap'; upcast = qlZeroCouponInflationSwapAsSwap}
peekZeroCouponInflationSwap :: Ptr CZeroCouponInflationSwap' -> IO ZeroCouponInflationSwap
peekZeroCouponInflationSwap = peekGenSwap
withZeroCouponInflationSwap :: ZeroCouponInflationSwap -> (Ptr CZeroCouponInflationSwap' -> IO b) -> IO b
withZeroCouponInflationSwap = withForeignPtr . ptr . peel . getInstrument

data CYearOnYearInflationSwap'
type CYearOnYearInflationSwap = ForeignPtr CYearOnYearInflationSwap'
type YearOnYearInflationSwap = GenSwap CYearOnYearInflationSwap
foreign import ccall unsafe "ql.h &qlFreeYearOnYearInflationSwap" qlFreeYearOnYearInflationSwap :: FinalizerPtr CYearOnYearInflationSwap'
instance Finalizable CYearOnYearInflationSwap' where finalize = qlFreeYearOnYearInflationSwap
foreign import ccall "ql.h qlYearOnYearInflationSwapAsSwap" qlYearOnYearInflationSwapAsSwap :: Ptr CYearOnYearInflationSwap' -> IO (Ptr CSwap')
instance Upcastable CYearOnYearInflationSwap' where {type Base CYearOnYearInflationSwap' = CSwap'; upcast = qlYearOnYearInflationSwapAsSwap}
peekYearOnYearInflationSwap :: Ptr CYearOnYearInflationSwap' -> IO YearOnYearInflationSwap
peekYearOnYearInflationSwap = peekGenSwap
withYearOnYearInflationSwap :: YearOnYearInflationSwap -> (Ptr CYearOnYearInflationSwap' -> IO b) -> IO b
withYearOnYearInflationSwap = withForeignPtr . ptr . peel . getInstrument

data CCPISwap'
type CCPISwap = ForeignPtr CCPISwap'
type CPISwap = GenSwap CCPISwap
foreign import ccall unsafe "ql.h &qlFreeCPISwap" qlFreeCPISwap :: FinalizerPtr CCPISwap'
instance Finalizable CCPISwap' where finalize = qlFreeCPISwap
foreign import ccall "ql.h qlCPISwapAsSwap" qlCPISwapAsSwap :: Ptr CCPISwap' -> IO (Ptr CSwap')
instance Upcastable CCPISwap' where {type Base CCPISwap' = CSwap'; upcast = qlCPISwapAsSwap}
peekCPISwap :: Ptr CCPISwap' -> IO CPISwap
peekCPISwap = peekGenSwap
withCPISwap :: CPISwap -> (Ptr CCPISwap' -> IO b) -> IO b
withCPISwap = withForeignPtr . ptr . peel . getInstrument

data CZeroCouponSwap'
type CZeroCouponSwap = ForeignPtr CZeroCouponSwap'
type ZeroCouponSwap = GenSwap CZeroCouponSwap
foreign import ccall unsafe "ql.h &qlFreeZeroCouponSwap" qlFreeZeroCouponSwap :: FinalizerPtr CZeroCouponSwap'
instance Finalizable CZeroCouponSwap' where finalize = qlFreeZeroCouponSwap
foreign import ccall "ql.h qlZeroCouponSwapAsSwap" qlZeroCouponSwapAsSwap :: Ptr CZeroCouponSwap' -> IO (Ptr CSwap')
instance Upcastable CZeroCouponSwap' where {type Base CZeroCouponSwap' = CSwap'; upcast = qlZeroCouponSwapAsSwap}
peekZeroCouponSwap :: Ptr CZeroCouponSwap' -> IO ZeroCouponSwap
peekZeroCouponSwap = peekGenSwap
withZeroCouponSwap :: ZeroCouponSwap -> (Ptr CZeroCouponSwap' -> IO b) -> IO b
withZeroCouponSwap = withForeignPtr . ptr . peel . getInstrument

data CEquityTotalReturnSwap'
type CEquityTotalReturnSwap = ForeignPtr CEquityTotalReturnSwap'
type EquityTotalReturnSwap = GenSwap CEquityTotalReturnSwap
foreign import ccall unsafe "ql.h &qlFreeEquityTotalReturnSwap" qlFreeEquityTotalReturnSwap :: FinalizerPtr CEquityTotalReturnSwap'
instance Finalizable CEquityTotalReturnSwap' where finalize = qlFreeEquityTotalReturnSwap
foreign import ccall "ql.h qlEquityTotalReturnSwapAsSwap" qlEquityTotalReturnSwapAsSwap :: Ptr CEquityTotalReturnSwap' -> IO (Ptr CSwap')
instance Upcastable CEquityTotalReturnSwap' where {type Base CEquityTotalReturnSwap' = CSwap'; upcast = qlEquityTotalReturnSwapAsSwap}
peekEquityTotalReturnSwap :: Ptr CEquityTotalReturnSwap' -> IO EquityTotalReturnSwap
peekEquityTotalReturnSwap = peekGenSwap
withEquityTotalReturnSwap :: EquityTotalReturnSwap -> (Ptr CEquityTotalReturnSwap' -> IO b) -> IO b
withEquityTotalReturnSwap = withForeignPtr . ptr . peel . getInstrument

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
withCdsOption = withForeignPtr . ptr . peel . getInstrument

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
withSwaption = withForeignPtr . ptr . peel . getInstrument

data CMultiAssetOption'
data CMargrabeOption'
type GenMultiAssetOption mo = GenOption (AnyOf CMultiAssetOption' mo)
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
asMultiAssetOption :: GenMultiAssetOption mo -> IO MultiAssetOption
asMultiAssetOption = transferGenForeignPtr peekMultiAssetOption . peel . peel . getInstrument
peekMultiAssetOption :: Ptr CMultiAssetOption' -> IO MultiAssetOption
peekMultiAssetOption = newCastForeignPtr >=> newGenMultiAssetOption
withMultiAssetOption :: GenMultiAssetOption mo -> (Ptr CMultiAssetOption' -> IO b) -> IO b
withMultiAssetOption = withGenForeignPtr . peel . peel . getInstrument
newGenMultiAssetOption :: GenForeignPtr mo CMultiAssetOption' -> IO (GenMultiAssetOption mo)
newGenMultiAssetOption = pure . GenInstrument . newAnyOf . newAnyOf

peekMargrabeOption :: Ptr CMargrabeOption' -> IO MargrabeOption
peekMargrabeOption = newGenForeignPtr >=> newGenMultiAssetOption
withMargrabeOption :: MargrabeOption -> (Ptr CMargrabeOption' -> IO b) -> IO b
withMargrabeOption = withForeignPtr . ptr . peel . peel . getInstrument

data COneAssetOption'
type GenOneAssetOption oo = GenOption (AnyOf COneAssetOption' oo)
type COneAssetOption = ForeignPtr COneAssetOption'
type OneAssetOption = GenOneAssetOption COneAssetOption
foreign import ccall unsafe "ql.h &qlFreeOneAssetOption" qlFreeOneAssetOption :: FinalizerPtr COneAssetOption'
instance Finalizable COneAssetOption' where finalize = qlFreeOneAssetOption
foreign import ccall "ql.h qlOneAssetOptionAsOption" qlOneAssetOptionAsOption :: Ptr COneAssetOption' -> IO (Ptr COption')
instance Upcastable COneAssetOption' where {type Base COneAssetOption' = COption'; upcast = qlOneAssetOptionAsOption}
asOneAssetOption :: GenOneAssetOption oo -> IO OneAssetOption
asOneAssetOption = transferGenForeignPtr peekOneAssetOption . peel . peel . getInstrument
peekOneAssetOption :: Ptr COneAssetOption' -> IO OneAssetOption
peekOneAssetOption = newCastForeignPtr >=> newGenOneAssetOption
withOneAssetOption :: GenOneAssetOption oo -> (Ptr COneAssetOption' -> IO b) -> IO b
withOneAssetOption = withGenForeignPtr . peel . peel . getInstrument
newGenOneAssetOption :: GenForeignPtr oo COneAssetOption' -> IO (GenOneAssetOption oo)
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
withBarrierOption = withForeignPtr . ptr . peel . peel . getInstrument

data CDoubleBarrierOption'
type CDoubleBarrierOption = ForeignPtr CDoubleBarrierOption'
type DoubleBarrierOption = GenOneAssetOption CDoubleBarrierOption
foreign import ccall unsafe "ql.h &qlFreeDoubleBarrierOption" qlFreeDoubleBarrierOption :: FinalizerPtr CDoubleBarrierOption'
instance Finalizable CDoubleBarrierOption' where finalize = qlFreeDoubleBarrierOption
foreign import ccall "ql.h qlDoubleBarrierOptionAsOneAssetOption" qlDoubleBarrierOptionAsOneAssetOption :: Ptr CDoubleBarrierOption' -> IO (Ptr COneAssetOption')
instance Upcastable CDoubleBarrierOption' where {type Base CDoubleBarrierOption' = COneAssetOption'; upcast = qlDoubleBarrierOptionAsOneAssetOption}
peekDoubleBarrierOption :: Ptr CDoubleBarrierOption' -> IO DoubleBarrierOption
peekDoubleBarrierOption = newGenForeignPtr >=> newGenOneAssetOption
withDoubleBarrierOption :: DoubleBarrierOption -> (Ptr CDoubleBarrierOption' -> IO b) -> IO b
withDoubleBarrierOption = withForeignPtr . ptr . peel . peel . getInstrument

data CQuantoForwardVanillaOption'
type CQuantoForwardVanillaOption = ForeignPtr CQuantoForwardVanillaOption'
type QuantoForwardVanillaOption = GenOneAssetOption CQuantoForwardVanillaOption
foreign import ccall unsafe "ql.h &qlFreeQuantoForwardVanillaOption" qlFreeQuantoForwardVanillaOption :: FinalizerPtr CQuantoForwardVanillaOption'
instance Finalizable CQuantoForwardVanillaOption' where finalize = qlFreeQuantoForwardVanillaOption
foreign import ccall "ql.h qlQuantoForwardVanillaOptionAsOneAssetOption" qlQuantoForwardVanillaOptionAsOneAssetOption :: Ptr CQuantoForwardVanillaOption' -> IO (Ptr COneAssetOption')
instance Upcastable CQuantoForwardVanillaOption' where {type Base CQuantoForwardVanillaOption' = COneAssetOption'; upcast = qlQuantoForwardVanillaOptionAsOneAssetOption}
peekQuantoForwardVanillaOption :: Ptr CQuantoForwardVanillaOption' -> IO QuantoForwardVanillaOption
peekQuantoForwardVanillaOption = newGenForeignPtr >=> newGenOneAssetOption
withQuantoForwardVanillaOption :: QuantoForwardVanillaOption -> (Ptr CQuantoForwardVanillaOption' -> IO b) -> IO b
withQuantoForwardVanillaOption = withForeignPtr . ptr . peel . peel . getInstrument

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
withQuantoVanillaOption = withForeignPtr . ptr . peel . peel . getInstrument

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
withVanillaOption = withForeignPtr . ptr . peel . peel . getInstrument

data CQuantoBarrierOption'
type CQuantoBarrierOption = ForeignPtr CQuantoBarrierOption'
type QuantoBarrierOption = GenOneAssetOption CQuantoBarrierOption
foreign import ccall unsafe "ql.h &qlFreeQuantoBarrierOption" qlFreeQuantoBarrierOption :: FinalizerPtr CQuantoBarrierOption'
instance Finalizable CQuantoBarrierOption' where finalize = qlFreeQuantoBarrierOption
foreign import ccall "ql.h qlQuantoBarrierOptionAsOneAssetOption" qlQuantoBarrierOptionAsOneAssetOption :: Ptr CQuantoBarrierOption' -> IO (Ptr COneAssetOption')
instance Upcastable CQuantoBarrierOption' where {type Base CQuantoBarrierOption' = COneAssetOption'; upcast = qlQuantoBarrierOptionAsOneAssetOption}
peekQuantoBarrierOption :: Ptr CQuantoBarrierOption' -> IO QuantoBarrierOption
peekQuantoBarrierOption = newGenForeignPtr >=> newGenOneAssetOption
withQuantoBarrierOption :: QuantoBarrierOption -> (Ptr CQuantoBarrierOption' -> IO b) -> IO b
withQuantoBarrierOption = withForeignPtr . ptr . peel . peel . getInstrument

withInstrumentArray :: [GenInstrument i] -> ((CUInt, Ptr (Ptr CInstrument')) -> IO b) -> IO b
withInstrumentArray = withGenArray withInstrument

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
