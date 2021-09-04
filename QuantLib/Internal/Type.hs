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
  , withMaybeSimpleType

  , CQuote
  , Quote
  , asQuote
  , peekQuote
  , CSimpleQuote
  , SimpleQuote
  , peekSimpleQuote

  , withComplexType
  , withComplexArray
  , withComplexArrayRaw
  , withSimpleArray
  , withMaybeComplexType

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
data Meta a = Meta {_fin :: FinalizerPtr a, _show :: Ptr a -> IO CString}
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
calendarMeta = Meta qlFreeCalendar c_qlCalendarName

currencyMeta :: Meta CCurrency
currencyMeta = Meta qlFreeCurrency c_qlCurrencyName

dayCounterMeta :: Meta CDayCounter
dayCounterMeta = Meta qlFreeDayCounter c_qlDayCounterName

scheduleMeta :: Meta CSchedule
scheduleMeta = Meta qlFreeSchedule undefined

callabilityMeta :: Meta CQlCallability
callabilityMeta = Meta qlFreeCallability undefined

claimMeta :: Meta CQlClaim
claimMeta = Meta qlFreeClaim undefined

timeGridMeta :: Meta CTimeGrid
timeGridMeta = Meta qlFreeTimeGrid undefined

interestRateMeta :: Meta CInterestRate
interestRateMeta = Meta qlFreeInterestRate undefined

dividendMeta :: Meta CDividend
dividendMeta = Meta qlFreeDividend undefined

peekSimpleType :: Meta a -> Ptr a -> IO (SimpleType a)
peekSimpleType (Meta f _) = newForeignPtr f >=> return . SimpleType

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
withMaybeCurrency x = withMaybeSimpleType (fmap getCCurrency x)

foreign import ccall "ql.h &qlFreeCalendar" qlFreeCalendar :: FinalizerPtr CCalendar
foreign import ccall "ql.h &qlFreeCurrency" qlFreeCurrency :: FinalizerPtr CCurrency
foreign import ccall "ql.h &qlFreeSchedule" qlFreeSchedule :: FinalizerPtr CSchedule
foreign import ccall "ql.h &qlFreeDayCounter" qlFreeDayCounter :: FinalizerPtr CDayCounter
foreign import ccall "ql.h &qlFreeTimeGrid" qlFreeTimeGrid :: FinalizerPtr CTimeGrid
foreign import ccall "ql.h &qlFreeInterestRate" qlFreeInterestRate :: FinalizerPtr CInterestRate
foreign import ccall "ql.h &qlFreeDividend" qlFreeDividend :: FinalizerPtr CDividend
foreign import ccall "ql.h &qlFreeCallability" qlFreeCallability :: FinalizerPtr CQlCallability
foreign import ccall "ql.h &qlFreeClaim" qlFreeClaim :: FinalizerPtr CQlClaim

showSimpleType :: Meta a -> SimpleType a -> String
showSimpleType (Meta _ s) x = unsafePerformIO $ withSimpleType x (s >=> peekDynString)

foreign import ccall safe "ql.h qlCalendarName" c_qlCalendarName :: Ptr CCalendar -> IO (Ptr CChar)
instance Show Calendar where show x = showSimpleType calendarMeta (getCCalendar x)
instance Eq Calendar where x == y = show x == show y

foreign import ccall safe "ql.h qlCurrencyName" c_qlCurrencyName :: Ptr CCurrency -> IO (Ptr CChar)
instance Show Currency where show x = showSimpleType currencyMeta (getCCurrency x)
instance Eq Currency where x == y = show x == show y

foreign import ccall safe "ql.h qlDayCounterName" c_qlDayCounterName :: Ptr CDayCounter -> IO (Ptr CChar)
instance Show DayCounter where show x = showSimpleType dayCounterMeta (getCDayCounter x)
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

-- class hierarchies

data Meta2 a b = Meta2 {_finalizer :: FinalizerPtr a, _upcast :: Ptr a -> IO (Ptr b)}
data ComplexType a b = PlainPtr (ForeignPtr a) (Meta2 a b) | CastPtr (IO (ForeignPtr a)) (Meta2 a b)

peekComplexType :: Meta2 a b -> Ptr a -> IO (ComplexType a b)
peekComplexType m@(Meta2 f _) p = do { pp <- newForeignPtr f p; return $ PlainPtr pp m}

createCast :: Meta2 b c -> ComplexType a b -> ComplexType b c
createCast m@(Meta2 f _) o = CastPtr (case o of
  (PlainPtr p (Meta2 _ k)) -> withPtr k p
  (CastPtr p (Meta2 _ k)) -> p >>= withPtr k) m
  where withPtr k p = withForeignPtr p (k >=> newForeignPtr f)

resolveCast :: ComplexType a b -> IO (ForeignPtr a)
resolveCast (PlainPtr p _) = return p
resolveCast (CastPtr p _) = p

withComplexType :: ComplexType a b -> (Ptr a -> IO c) -> IO c
withComplexType p f = resolveCast p >>= (`withForeignPtr` f)

data CQuote
data CSimpleQuote

type Quote = ComplexType CQuote ()
type SimpleQuote = ComplexType CSimpleQuote CQuote

quoteMeta :: Meta2 CQuote ()
quoteMeta = Meta2 qlFreeQuote undefined

simpleQuoteMeta :: Meta2 CSimpleQuote CQuote
simpleQuoteMeta = Meta2 qlFreeSimpleQuote qlSimpleQuoteAsQuote

peekQuote :: Ptr CQuote -> IO Quote
peekQuote = peekComplexType quoteMeta

peekSimpleQuote :: Ptr CSimpleQuote -> IO SimpleQuote
peekSimpleQuote = peekComplexType simpleQuoteMeta

foreign import ccall "ql.h &qlFreeQuote" qlFreeQuote :: FinalizerPtr CQuote
foreign import ccall "ql.h &qlFreeSimpleQuote" qlFreeSimpleQuote :: FinalizerPtr CSimpleQuote

foreign import ccall safe "ql.h qlSimpleQuoteAsQuote" qlSimpleQuoteAsQuote :: Ptr CSimpleQuote -> IO (Ptr CQuote)

asQuote :: ComplexType a CQuote -> Quote
asQuote = createCast quoteMeta

withSimpleArray :: [SimpleType a] -> ((CUInt, Ptr (Ptr a)) -> IO b) -> IO b
withSimpleArray x f = withMany withSimpleType x (`withArray` (\px -> f (fromIntegral $ length x, px)))

withInterestRateArray :: [InterestRate] -> ((CUInt, Ptr (Ptr CInterestRate)) -> IO b) -> IO b
withInterestRateArray x f = withMany withInterestRate x (`withArray` (\px -> f (fromIntegral $ length x, px)))

withDividendArray :: [Dividend] -> ((CUInt, Ptr (Ptr CDividend)) -> IO b) -> IO b
withDividendArray x f = withMany withDividend x (`withArray` (\px -> f (fromIntegral $ length x, px)))

withComplexArray :: [ComplexType a c] -> ((CUInt, Ptr (Ptr a)) -> IO b) -> IO b
withComplexArray x f = withMany withComplexType x (`withArray` (\px -> f (fromIntegral $ length x, px)))

-- pass length somewhere else
withComplexArrayRaw :: [ComplexType a c] -> (Ptr (Ptr a) -> IO b) -> IO b
withComplexArrayRaw x f = withMany withComplexType x (`withArray` f)

withMaybeComplexType :: Maybe (ComplexType a c) -> (Ptr a -> IO b) -> IO b
withMaybeComplexType x f = maybe (f nullPtr) (`withComplexType` f) x

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
