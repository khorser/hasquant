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

  , GenQuote(..)
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

withSimpleArray :: (t -> SimpleType a) -> [t] -> ((CUInt, Ptr (Ptr a)) -> IO b) -> IO b
withSimpleArray c x f = withMany withSimpleType (map c x) (`withArray` (\px -> f (fromIntegral $ length x, px)))

withInterestRateArray :: [InterestRate] -> ((CUInt, Ptr (Ptr CInterestRate)) -> IO b) -> IO b
withInterestRateArray = withSimpleArray getCInterestRate

withDividendArray :: [Dividend] -> ((CUInt, Ptr (Ptr CDividend)) -> IO b) -> IO b
withDividendArray = withSimpleArray getCDividend

-- class hierarchies

data Meta2 a b = Meta2 {_finalizer :: FinalizerPtr a, _upcast :: Ptr a -> IO (Ptr b)}
--data ComplexType a b = PlainPtr (ForeignPtr a) (Meta2 a b) | CastPtr (IO (ForeignPtr a)) (Meta2 a b)
--
--peekComplexType :: Meta2 a b -> Ptr a -> IO (ComplexType a b)
--peekComplexType m@(Meta2 f _) p = do { pp <- newForeignPtr f p; return $ PlainPtr pp m}
--
--createCast :: Meta2 b c -> ComplexType a b -> ComplexType b c
--createCast m@(Meta2 f _) o = CastPtr (case o of
--  (PlainPtr p (Meta2 _ k)) -> withPtr k p
--  (CastPtr p (Meta2 _ k)) -> p >>= withPtr k) m
--  where withPtr k p = withForeignPtr p (k >=> newForeignPtr f)
--
--resolveCast :: ComplexType a b -> IO (ForeignPtr a)
--resolveCast (PlainPtr p _) = return p
--resolveCast (CastPtr p _) = p
--
--withComplexType :: ComplexType a b -> (Ptr a -> IO c) -> IO c
--withComplexType p f = resolveCast p >>= (`withForeignPtr` f)
--
---- put the first argument in meta
--withComplexArray :: (t -> ComplexType a c) -> [t] -> ((CUInt, Ptr (Ptr a)) -> IO b) -> IO b
--withComplexArray c x f = withMany withComplexType (map c x) (`withArray` (\px -> f (fromIntegral $ length x, px)))
--
--withComplexArrayRaw :: (t -> ComplexType a c) -> [t] -> (Ptr (Ptr a) -> IO b) -> IO b
--withComplexArrayRaw c x f = withMany withComplexType (map c x) (`withArray` f)
--
--withMaybeComplexType :: (t -> ComplexType a c) -> Maybe t -> (Ptr a -> IO b) -> IO b
--withMaybeComplexType c x f = maybe (f nullPtr) (`withComplexType` f) (c <$> x)

data CQuote
data CSimpleQuote

--newtype Quote = Quote {getQuote :: ComplexType CQuote CQuote}
--newtype SimpleQuote = SimpleQuote {getSimpleQuote :: ComplexType CSimpleQuote CQuote}
--
--quoteMeta :: Meta2 CQuote CQuote
--quoteMeta = Meta2 qlFreeQuote return
--
--simpleQuoteMeta :: Meta2 CSimpleQuote CQuote
--simpleQuoteMeta = Meta2 qlFreeSimpleQuote qlSimpleQuoteAsQuote
--
--peekQuote :: Ptr CQuote -> IO Quote
--peekQuote x = Quote <$> peekComplexType quoteMeta x
--
--peekSimpleQuote :: Ptr CSimpleQuote -> IO SimpleQuote
--peekSimpleQuote x = SimpleQuote <$> peekComplexType simpleQuoteMeta x

foreign import ccall "ql.h &qlFreeQuote" qlFreeQuote :: FinalizerPtr CQuote
foreign import ccall "ql.h &qlFreeSimpleQuote" qlFreeSimpleQuote :: FinalizerPtr CSimpleQuote

foreign import ccall safe "ql.h qlSimpleQuoteAsQuote" qlSimpleQuoteAsQuote :: Ptr CSimpleQuote -> IO (Ptr CQuote)

---- won't scale if Quote has multiple subclasses
--asQuote :: SimpleQuote -> Quote
--asQuote x = Quote (createCast quoteMeta (getSimpleQuote x))
--
--withQuote :: Quote -> (Ptr CQuote -> IO c) -> IO c
--withQuote p = withComplexType (getQuote p)
--
--withSimpleQuote :: SimpleQuote -> (Ptr CSimpleQuote -> IO c) -> IO c
--withSimpleQuote p = withComplexType (getSimpleQuote p)
--
--withQuoteArray :: [Quote] -> ((CUInt, Ptr (Ptr CQuote)) -> IO b) -> IO b
--withQuoteArray = withComplexArray getQuote
--
--withQuoteArrayRaw :: [Quote] -> (Ptr (Ptr CQuote) -> IO b) -> IO b
--withQuoteArrayRaw = withComplexArrayRaw getQuote
--
--withMaybeQuote :: Maybe Quote -> (Ptr CQuote -> IO b) -> IO b
--withMaybeQuote = withMaybeComplexType getQuote

--data GenQuote a = GenQuote (ForeignPtr a) (Meta2 a CQuote)

data GenObject c a = GenObject (ForeignPtr a) (Meta2 a c)

newtype GenQuote a = GenQuote (GenObject CQuote a)

type Quote = GenQuote CQuote
type SimpleQuote = GenQuote CSimpleQuote

genQuoteMeta :: Meta2 CQuote CQuote
genQuoteMeta = Meta2 qlFreeQuote return

genSimpleQuoteMeta :: Meta2 CSimpleQuote CQuote
genSimpleQuoteMeta = Meta2 qlFreeSimpleQuote qlSimpleQuoteAsQuote

asQuote :: GenQuote a -> IO (GenQuote CQuote)
asQuote (GenQuote (GenObject p (Meta2 _ k))) = withForeignPtr p (\qq -> GenQuote <$> (GenObject <$> (k qq >>= newForeignPtr (_finalizer genQuoteMeta)) <*> return genQuoteMeta))

withQuote :: GenQuote a -> (Ptr CQuote -> IO b) -> IO b
withQuote (GenQuote (GenObject p (Meta2 _ k))) ff = withForeignPtr p (k >=> ff)

withSimpleQuote :: GenQuote CSimpleQuote -> (Ptr CSimpleQuote-> IO b) -> IO b
withSimpleQuote (GenQuote (GenObject p _ )) = withForeignPtr p

peekQuote :: Ptr CQuote -> IO (GenQuote CQuote)
peekQuote p = GenQuote <$> (GenObject <$> newForeignPtr (_finalizer genQuoteMeta) p <*> return genQuoteMeta)

peekSimpleQuote :: Ptr CSimpleQuote -> IO (GenQuote CSimpleQuote)
peekSimpleQuote p = GenQuote <$> (GenObject <$> newForeignPtr (_finalizer genSimpleQuoteMeta) p <*> return genSimpleQuoteMeta)

withQuoteArray :: [GenQuote a] -> ((CUInt, Ptr (Ptr CQuote)) -> IO b) -> IO b
withQuoteArray x f = withMany withQuote x (`withArray` (\px -> f (fromIntegral $ length x, px)))

withQuoteArrayRaw :: [GenQuote a] -> (Ptr (Ptr CQuote) -> IO b) -> IO b
withQuoteArrayRaw x f = withMany withQuote x (`withArray` f )

withMaybeQuote :: Maybe (GenQuote a) -> (Ptr CQuote -> IO b) -> IO b
withMaybeQuote x f = maybe (f nullPtr) (`withQuote` f) x

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
