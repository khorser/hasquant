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

import System.IO.Unsafe(unsafePerformIO)

data CCalendar
data CCurrency
data CDayCounter
data CSchedule

newtype SimpleType a = SimpleType {ptr :: ForeignPtr a}
data Meta a = Meta {_fin :: FinalizerPtr a, _show :: Ptr a -> IO CString}
type Calendar = SimpleType CCalendar
type Currency = SimpleType CCurrency
type DayCounter = SimpleType CDayCounter
type Schedule = SimpleType CSchedule

calendarMeta :: Meta CCalendar
calendarMeta = Meta qlFreeCalendar c_qlCalendarName

currencyMeta :: Meta CCurrency
currencyMeta = Meta qlFreeCurrency c_qlCurrencyName

dayCounterMeta :: Meta CDayCounter
dayCounterMeta = Meta qlFreeDayCounter c_qlDayCounterName

scheduleMeta :: Meta CSchedule
scheduleMeta = Meta qlFreeSchedule undefined

peekSimpleType :: Meta a -> Ptr a -> IO (SimpleType a)
peekSimpleType (Meta f _) = newForeignPtr f >=> return . SimpleType

peekCalendar :: Ptr CCalendar -> IO Calendar
peekCalendar = peekSimpleType calendarMeta

peekSchedule :: Ptr CSchedule -> IO Schedule
peekSchedule = peekSimpleType scheduleMeta

peekDayCounter :: Ptr CDayCounter -> IO DayCounter
peekDayCounter = peekSimpleType dayCounterMeta

peekCurrency :: Ptr CCurrency -> IO Currency
peekCurrency = peekSimpleType currencyMeta

withSimpleType :: SimpleType a -> (Ptr a -> IO b) -> IO b
withSimpleType = withForeignPtr . ptr

withMaybeSimpleType :: Maybe (SimpleType a) -> (Ptr a -> IO b) -> IO b
withMaybeSimpleType x f = maybe (f nullPtr) (`withSimpleType` f) x

foreign import ccall "ql.h &qlFreeCalendar" qlFreeCalendar :: FinalizerPtr CCalendar
foreign import ccall "ql.h &qlFreeCurrency" qlFreeCurrency :: FinalizerPtr CCurrency
foreign import ccall "ql.h &qlFreeSchedule" qlFreeSchedule :: FinalizerPtr CSchedule
foreign import ccall "ql.h &qlFreeDayCounter" qlFreeDayCounter :: FinalizerPtr CDayCounter

showSimpleType :: Meta a -> SimpleType a -> String
showSimpleType (Meta _ s) x = unsafePerformIO $ withSimpleType x (s >=> peekDynString)

foreign import ccall safe "ql.h qlCalendarName" c_qlCalendarName :: Ptr CCalendar -> IO (Ptr CChar)
instance Show Calendar where show = showSimpleType calendarMeta
instance Eq Calendar where x == y = show x == show y

foreign import ccall safe "ql.h qlCurrencyName" c_qlCurrencyName :: Ptr CCurrency -> IO (Ptr CChar)
instance Show Currency where show = showSimpleType currencyMeta
instance Eq Currency where x == y = show x == show y

foreign import ccall safe "ql.h qlDayCounterName" c_qlDayCounterName :: Ptr CDayCounter -> IO (Ptr CChar)
instance Show DayCounter where show = showSimpleType dayCounterMeta
instance Eq DayCounter where x == y = show x == show y


--data Meta2 a b = Meta2 {_finalizer :: FinalizerPtr a, _upcast :: Ptr a -> IO (Ptr b)}
--
--bondMeta :: Meta2 CBond ()
--bondMeta = Meta2 qlFreeBond undefined
--
--fixedRateBondMeta :: Meta2 CFixedRateBond CBond
--fixedRateBondMeta = Meta2 qlFreeFixedRateBond qlFixedRateBondAsBond
--
--floatingRateBondMeta :: Meta2 CFloatingRateBond CBond
--floatingRateBondMeta = Meta2 qlFreeFloatingRateBond qlFloatingRateBondAsBond
--
--data ComplexType a b = PlainPtr (ForeignPtr a) (Meta2 a b) | CastPtr (IO (ForeignPtr a)) (Meta2 a b)
--
--data CBond
--data CFixedRateBond
--data CFloatingRateBond
--
--type Bond = ComplexType CBond ()
--type FixedRateBond = ComplexType CFixedRateBond CBond
--type FloatingRateBond = ComplexType CFloatingRateBond CBond
--
--peekComplexType :: Meta2 a b -> Ptr a -> IO (ComplexType a b)
--peekComplexType m@(Meta2 f _) p = do { pp <- newForeignPtr f p; return $ PlainPtr pp m}
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
--createCast :: Meta2 b c -> ComplexType a b -> ComplexType b c
--createCast m@(Meta2 f _) o = CastPtr (case o of
--  (PlainPtr p (Meta2 _ k)) -> withPtr k p
--  (CastPtr p (Meta2 _ k)) -> p >>= withPtr k) m
--  where withPtr k p = withForeignPtr p (k >=> newForeignPtr f)
--
--fixedRateBondAsBond :: FixedRateBond -> Bond
--fixedRateBondAsBond = asBond
--
--floatingRateBondAsBond :: FloatingRateBond -> Bond
--floatingRateBondAsBond = asBond
--
--resolveCast :: ComplexType a b -> IO (ForeignPtr a)
--resolveCast (PlainPtr p _) = return p
--resolveCast (CastPtr p _) = p
--
--withComplexType :: ComplexType a b -> (Ptr a -> IO c) -> IO c
--withComplexType p f = resolveCast p >>= (`withForeignPtr` f)
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
