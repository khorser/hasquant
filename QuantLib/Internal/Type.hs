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

--  , CBond
--  , Bond
--  , CFixedRateBond
--  , FixedRateBond
--  , CFloatingRateBond
--  , FloatingRateBond
--  , peekBond
--  , withBond
--
--  , withFixedRateBond
--  , peekFixedRateBond
--  , fixedRateBondAsBond
--
--  , withFloatingRateBond
--  , peekFloatingRateBond
--  , floatingRateBondAsBond
--
--  , asBond
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

timeGridMeta :: Meta CTimeGrid
timeGridMeta = Meta qlFreeTimeGrid

interestRateMeta :: Meta CInterestRate
interestRateMeta = Meta qlFreeInterestRate

dividendMeta :: Meta CDividend
dividendMeta = Meta qlFreeDividend

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

peekConstraint :: Ptr CConstraint -> IO (SimpleType CConstraint)
peekConstraint = peekSimpleType constraintMeta

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
data GenObject b a = GenObject {getObject :: ForeignPtr a, _getMeta :: MetaConv a b}

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

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
