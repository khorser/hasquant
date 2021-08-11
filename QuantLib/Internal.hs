module QuantLib.Internal
  (
    minDate
  , maxDate
  -- marshalling helpers
  , preErrorCheck
  , errorCheck

  , fromMaybeBool
  , toMaybeBool
  , peekDynString
  , peekEnum
  , preEnum
  , preNum
  , preArray
  , peekIntArray
  , withMaybeObject
  , withEnumArray
  , fromEnumQuantity
  , toEnumQuantity

  , fromDay
  , toDay
  , fromMaybeDay
  , toMaybeDay
  , peekDayArray
  , withDayArray

  , isValid
  , toSerial
  , fromSerial
  , ForeignObject(..)
  )
where

import Foreign.C.Types
import Foreign.C.String(CString, peekCString)
import Foreign.Ptr(Ptr, nullPtr)
import Foreign.Marshal.Array(peekArray, withArray)
import Foreign.Marshal.Utils(with, toBool, fromBool)
import Foreign.Storable(peek, Storable)

import Control.Exception(throwIO)
import Control.Monad(when)
import Data.Functor
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, fromGregorian)

import QuantLib.Type

errorCheck :: Ptr CString -> IO ()
errorCheck p = do
  a <- peek p
  when
    (a /= nullPtr)
    ((peekCString a <* c_freeString a) >>= throwIO . CPlusPlusException)

-- like alloca but initializes the allocated pointer with zero
preErrorCheck :: (Ptr (Ptr a) -> IO b) -> IO b
preErrorCheck = with nullPtr

fromMaybeBool :: Maybe Bool -> CInt
fromMaybeBool = maybe (-1) fromBool

toMaybeBool :: CInt -> Maybe Bool
toMaybeBool x = if x == -1 then Nothing else Just $ toBool x

peekDynString :: CString -> IO String
peekDynString x = peekCString x <* c_freeString x

peekEnum :: (Enum a) => Ptr CInt -> IO a
peekEnum x = peek x <&> (toEnum . fromIntegral)

-- initialize pointer to a enum with a valid value before passing it to the function
preEnum :: (Storable a, Bounded a) => (Ptr a -> IO b) -> IO b
preEnum = with minBound

preNum :: (Storable a, Num a) => (Ptr a -> IO b) -> IO b
preNum = with 0

foreign import ccall safe "ql.h qlFreeString" c_freeString :: CString -> IO ()
foreign import ccall safe "ql.h qlFreeInts" c_freeInts :: Ptr CInt -> IO ()
--foreign import ccall safe "ql.h qlFreeDoubles" c_freeDoubles :: Ptr CDouble -> IO ()
--foreign import ccall safe "ql.h qlFreePointerArray" c_freePointerArray :: Ptr (Ptr ()) -> IO ()

withEnumArray :: (Enum a) => [a] -> ((CUInt, Ptr CInt) -> IO b) -> IO b
withEnumArray x f = withArray (map (fromIntegral . fromEnum) x) (\xs -> f (fromIntegral $ length x, xs))

preArray :: ((Ptr CUInt, Ptr (Ptr a)) -> IO b) -> IO b
preArray f = with 0 $
  \x -> with nullPtr $
    \y -> f (x, y)

peekIntArray :: (CInt -> b) -> Ptr CUInt -> Ptr (Ptr CInt) -> IO [b]
peekIntArray f pl pp = do
  l <- peek pl
  p <- peek pp
  map f <$> peekArray (fromIntegral l) p <* c_freeInts p

withMaybeObject :: (ForeignObject a) => Maybe a -> (Ptr a -> IO b) -> IO b
withMaybeObject x f = maybe (f nullPtr) (`withObject` f) x

fromEnumQuantity :: (Enum a) => (Int, a) -> (CInt, CInt)
fromEnumQuantity (x, u) = (fromIntegral x, fromIntegral $ fromEnum u)

toEnumQuantity :: (Enum a) => (CInt, CInt) -> (Int, a)
toEnumQuantity (x, u) = (fromIntegral x, toEnum $ fromIntegral u)

foreign import ccall safe "ql.h qlMinYear" qlMinYear :: CInt

foreign import ccall safe "ql.h qlMinMonth" qlMinMonth :: CInt

foreign import ccall safe "ql.h qlMinDay" qlMinDay :: CInt

foreign import ccall safe "ql.h qlMinDateSerialNumber" qlMinDateSerialNumber :: CInt

foreign import ccall safe "ql.h qlMaxDateSerialNumber" qlMaxDateSerialNumber :: CInt

-- |Julian day of the QuantLib zero date
qlStart :: CInt
qlStart = minDateJulianDays - qlMinDateSerialNumber
  where minDateJulianDays = toModifiedJulianDay' $ fromGregorian (fromIntegral qlMinYear) (fromIntegral qlMinMonth) (fromIntegral qlMinDay)

toModifiedJulianDay' :: Day -> CInt
toModifiedJulianDay' = fromIntegral . toModifiedJulianDay

fromSerial :: CInt -> Day
fromSerial x = ModifiedJulianDay $ fromIntegral (x + qlStart)

isValid :: Day -> Bool
isValid x = s >= qlMinDateSerialNumber && s <= qlMaxDateSerialNumber
  where s = toModifiedJulianDay' x - qlStart

toSerial :: Day -> IO CInt
toSerial x | isValid x = return $ toModifiedJulianDay' x - qlStart
           | otherwise = throwIO $ DateConversion x

fromDay :: Day -> (CInt -> IO a) -> IO a
fromDay x f = toSerial x >>= f

toDay :: CInt -> Day
toDay = fromSerial

fromMaybeDay :: Maybe Day -> (CInt -> IO a) -> IO a
fromMaybeDay x f = maybe (f 0) (`fromDay` f) x

toMaybeDay :: CInt -> Maybe Day
toMaybeDay 0 = Nothing
toMaybeDay x = Just $ fromSerial x

withDayArray :: [Day] -> ((CUInt, Ptr CInt) -> IO b) -> IO b
withDayArray x f = do
  xs <- mapM toSerial x
  withArray xs (\xx -> f (fromIntegral $ length x, xx))

peekDayArray :: Ptr CUInt -> Ptr (Ptr CInt) -> IO [Day]
peekDayArray = peekIntArray fromSerial

-- |earliest allowed date in QuantLib
minDate :: Day
minDate = fromSerial qlMinDateSerialNumber

-- |latest date allowed in QuantLib
maxDate :: Day
maxDate = fromSerial qlMaxDateSerialNumber

-- this leaks the abstraction to some degree...
class ForeignObject a where
  withObject :: a -> (Ptr a -> IO b) -> IO b

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
