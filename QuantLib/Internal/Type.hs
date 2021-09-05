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

newtype SimpleType a = SimpleType {ptr :: ForeignPtr a}
newtype Meta a = Meta {_fin :: FinalizerPtr a}
newtype Calendar = Calendar {getCCalendar :: SimpleType CCalendar}
newtype Currency = Currency {getCCurrency :: SimpleType CCurrency}
newtype DayCounter = DayCounter {getCDayCounter :: SimpleType CDayCounter}
newtype Schedule = Schedule {getCSchedule :: SimpleType CSchedule}
newtype InterestRate = InterestRate {getCInterestRate :: SimpleType CInterestRate}
newtype TimeGrid = TimeGrid {getCTimeGrid :: SimpleType CTimeGrid}
newtype Dividend = Dividend {getCDividend :: SimpleType CDividend}
-- special cases: those types will be represented as enums so no need to wrap them
type QlClaim = SimpleType CQlClaim
type QlCallability = SimpleType CQlCallability

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

timeGridMeta :: Meta CTimeGrid
timeGridMeta = Meta qlFreeTimeGrid

interestRateMeta :: Meta CInterestRate
interestRateMeta = Meta qlFreeInterestRate

dividendMeta :: Meta CDividend
dividendMeta = Meta qlFreeDividend

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

peekInterestRate :: Ptr CInterestRate -> IO InterestRate
peekInterestRate = peekSimpleType interestRateMeta >=> return . InterestRate

peekDividend :: Ptr CDividend -> IO Dividend
peekDividend = peekSimpleType dividendMeta >=> return . Dividend

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
foreign import ccall "ql.h &qlFreeDividend" qlFreeDividend :: FinalizerPtr CDividend
foreign import ccall "ql.h &qlFreeCallability" qlFreeCallability :: FinalizerPtr CQlCallability
foreign import ccall "ql.h &qlFreeClaim" qlFreeClaim :: FinalizerPtr CQlClaim

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

withDividend :: Dividend -> (Ptr CDividend -> IO b) -> IO b
withDividend = withSimpleType . getCDividend

withTimeGrid :: TimeGrid -> (Ptr CTimeGrid -> IO b) -> IO b
withTimeGrid = withSimpleType . getCTimeGrid

withSimpleArray :: (t -> SimpleType a) -> [t] -> ((CUInt, Ptr (Ptr a)) -> IO b) -> IO b
withSimpleArray c x f = withMany withSimpleType (map c x) (`withArray` (\px -> f (fromIntegral $ length x, px)))

withInterestRateArray :: [InterestRate] -> ((CUInt, Ptr (Ptr CInterestRate)) -> IO b) -> IO b
withInterestRateArray = withSimpleArray getCInterestRate

withDividendArray :: [Dividend] -> ((CUInt, Ptr (Ptr CDividend)) -> IO b) -> IO b
withDividendArray = withSimpleArray getCDividend

---- class hierarchies
data Meta2 a b = Meta2 {_finalizer :: FinalizerPtr a, _upcast :: Ptr a -> IO (Ptr b)}
data GenObject c a = GenObject {getObject :: ForeignPtr a, _getMeta :: Meta2 a c}

asGenObject :: Meta2 c c -> GenObject c a -> IO (GenObject c c)
asGenObject m (GenObject p (Meta2 _ k)) = withForeignPtr p (\qq -> GenObject <$> (k qq >>= newForeignPtr (_finalizer m)) <*> return m)

withGenObject :: GenObject c a -> (Ptr c -> IO b) -> IO b
withGenObject (GenObject p (Meta2 _ k)) ff = withForeignPtr p (k >=> ff)

withSubObject :: GenObject c a -> (Ptr a -> IO b) -> IO b
withSubObject = withForeignPtr . getObject

peekGenObject :: Meta2 c c -> Ptr c -> IO (GenObject c c)
peekGenObject m p = GenObject <$> newForeignPtr (_finalizer m) p <*> return m

peekSubObject :: Meta2 a c -> Ptr a -> IO (GenObject c a)
peekSubObject m p = GenObject <$> newForeignPtr (_finalizer m) p <*> return m

withGenArray :: [GenObject c a] -> ((CUInt, Ptr (Ptr c)) -> IO b) -> IO b
withGenArray x f = withMany withGenObject x (`withArray` (\px -> f (fromIntegral $ length x, px)))

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

genQuoteMeta :: Meta2 CQuote CQuote
genQuoteMeta = Meta2 qlFreeQuote return

genSimpleQuoteMeta :: Meta2 CSimpleQuote CQuote
genSimpleQuoteMeta = Meta2 qlFreeSimpleQuote qlSimpleQuoteAsQuote

asQuote :: GenQuote a -> IO (GenQuote CQuote)
asQuote (GenQuote q) = GenQuote <$> asGenObject genQuoteMeta q

withQuote :: GenQuote a -> (Ptr CQuote -> IO b) -> IO b
withQuote = withGenObject . getQuote

withSimpleQuote :: GenQuote CSimpleQuote -> (Ptr CSimpleQuote-> IO b) -> IO b
withSimpleQuote = withSubObject . getQuote

peekQuote :: Ptr CQuote -> IO (GenQuote CQuote)
peekQuote p = GenQuote <$> peekGenObject genQuoteMeta p

peekSimpleQuote :: Ptr CSimpleQuote -> IO (GenQuote CSimpleQuote)
peekSimpleQuote p = GenQuote <$> peekSubObject genSimpleQuoteMeta p

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

genLegMeta :: Meta2 CLeg CLeg
genLegMeta = Meta2 qlFreeLeg return

genCouponLegMeta :: Meta2 CCouponLeg CLeg
genCouponLegMeta = Meta2 qlFreeCouponLeg qlCouponLegAsLeg

asLeg :: GenLeg a -> IO (GenLeg CLeg)
asLeg (GenLeg q) = GenLeg <$> asGenObject genLegMeta q

withLeg :: GenLeg a -> (Ptr CLeg -> IO b) -> IO b
withLeg = withGenObject . getLeg

withCouponLeg :: GenLeg CCouponLeg -> (Ptr CCouponLeg-> IO b) -> IO b
withCouponLeg = withSubObject . getLeg

peekLeg :: Ptr CLeg -> IO (GenLeg CLeg)
peekLeg p = GenLeg <$> peekGenObject genLegMeta p

peekCouponLeg :: Ptr CCouponLeg -> IO (GenLeg CCouponLeg)
peekCouponLeg p = GenLeg <$> peekSubObject genCouponLegMeta p

withLegArray :: [GenLeg a] -> ((CUInt, Ptr (Ptr CLeg)) -> IO b) -> IO b
withLegArray x = withGenArray (map getLeg x)

--bondMeta :: Meta2 CBond ()
--bondMeta = Meta2 qlFreeBond undefined
--
--fixedRateBondMeta :: Meta2 CFixedRateBond CBond
--fixedRateBondMeta = Meta2 qlFreeFixedRateBond qlFixedRateBondAsBond
--
--floatingRateBondMeta :: Meta2 CFloatingRateBond CBond
--floatingRateBondMeta = Meta2 qlFreeFloatingRateBond qlFloatingRateBondAsBond
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
