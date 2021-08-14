module QuantLib.Internal
  (
    Day -- reexport for simplicity
  , minDate
  , maxDate

  -- marshalling helpers
  , prePtr
  , preErrorCheck
  , errorCheck

  , fromMaybeBool
  , toMaybeBool
  , peekDynString
  , peekEnum
  , peekDouble
  , preEnum
  , preNum
  , preArray
  , withMaybeObject
  , withEnumArray
  , withIntArray
  , withDoubleArray
  , withObjectArray
  , withDayPtr
  , fromEnumQuantity
  , toEnumQuantity

  , fromDay
  , toDay
  , fromMaybeDay
  , fromMaybeInt
  , toMaybeDay
  , peekDayArray
  , peekBoolArray
  , withDayArray
  , peekDoubleArray

  , toSerial
  , fromSerial
  , ForeignObject(..)
  , qlSavedSettings
  , qlFreeSavedSettings
  , fromMaybeDouble
  , peekIntArray
  , peekUIntArray

  -- reexport some useful stuff
  , newForeignPtr
  , (>=>)
  )
where

import Foreign.C.Types
import Foreign.C.String(CString, peekCString)
import Foreign.Ptr(Ptr, nullPtr)
import Foreign.Marshal.Array(peekArray, withArray)
import Foreign.Marshal.Utils(with, toBool, fromBool, withMany)
import Foreign.Storable(peek, Storable)
import Foreign.Marshal.Alloc(alloca)

import Foreign.ForeignPtr(newForeignPtr)
import Control.Exception(throwIO)
import Control.Monad(when, (>=>))
import Data.Functor((<&>))
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, fromGregorian)

import QuantLib.Type

-- ch2s will not attach finalizers to foreign ptrs declared in other modules
-- so let's add more boilerplate and declare the unmarshaller outselves
class ForeignObject a where
  withObject :: a -> (Ptr a -> IO b) -> IO b
  peekObject :: Ptr a -> IO a

errorCheck :: Ptr CString -> IO ()
errorCheck p = do
  a <- peek p
  when
    (a /= nullPtr)
    ((peekCString a <* qlFreeString a) >>= throwIO . CPlusPlusException)

-- like alloca but initializes the allocated pointer with zero
preErrorCheck :: (Ptr (Ptr a) -> IO b) -> IO b
preErrorCheck = with nullPtr

fromMaybeBool :: Maybe Bool -> CInt
fromMaybeBool = maybe (-1) fromBool

foreign import ccall safe "ql.h qlNullInteger" qlNullInteger :: CInt
foreign import ccall safe "ql.h qlNullReal" qlNullReal :: CDouble

fromMaybeInt :: (Integral a, Integral b, Storable b) => Maybe a -> b
fromMaybeInt = maybe (fromIntegral qlNullInteger) fromIntegral

fromMaybeDouble :: Maybe Double -> CDouble
fromMaybeDouble = maybe (realToFrac qlNullReal) realToFrac

toMaybeBool :: CInt -> Maybe Bool
toMaybeBool x = if x == -1 then Nothing else Just $ toBool x

peekDynString :: CString -> IO String
peekDynString x = peekCString x <* qlFreeString x

peekEnum :: (Enum a) => Ptr CInt -> IO a
peekEnum x = peek x <&> (toEnum . fromIntegral)

peekDouble :: Ptr CDouble -> IO Double
peekDouble x = realToFrac <$> peek x

-- initialize pointer to a enum with a valid value before passing it to the function
preEnum :: (Storable a, Bounded a) => (Ptr a -> IO b) -> IO b
preEnum = with minBound

preNum :: (Storable a, Num a) => (Ptr a -> IO b) -> IO b
preNum = with 0

foreign import ccall safe "ql.h qlFreeString" qlFreeString :: CString -> IO ()
foreign import ccall safe "ql.h qlFreeInts" qlFreeInts :: Ptr CInt -> IO ()
foreign import ccall safe "ql.h qlFreeUInts" qlFreeUInts :: Ptr CUInt -> IO ()
foreign import ccall safe "ql.h qlFreeDoubles" qlFreeDoubles :: Ptr CDouble -> IO ()
--foreign import ccall safe "ql.h qlFreePointerArray" qlFreePointerArray :: Ptr (Ptr ()) -> IO ()
foreign import ccall safe "ql.h qlSavedSettings" qlSavedSettings :: IO (Ptr ())
foreign import ccall safe "ql.h qlFreeSavedSettings" qlFreeSavedSettings :: Ptr () -> IO ()

withLArray :: (Storable b) => (a -> b) -> [a] -> ((CUInt, Ptr b) -> IO c) -> IO c
withLArray c x f = withArray (map c x) (\px -> f (fromIntegral $ length x, px))

withEnumArray :: (Enum a) => [a] -> ((CUInt, Ptr CInt) -> IO b) -> IO b
withEnumArray = withLArray (fromIntegral . fromEnum)

withObjectArray :: (ForeignObject a) => [a] -> ((CUInt, Ptr (Ptr a)) -> IO b) -> IO b
withObjectArray x f = withMany withObject x (`withArray` (\px -> f (fromIntegral $ length x, px)))

withIntArray :: (Integral a, Num n, Storable n) => [a] -> ((CUInt, Ptr n) -> IO b) -> IO b
withIntArray = withLArray fromIntegral

withDoubleArray :: [Double] -> ((CUInt, Ptr CDouble) -> IO b) -> IO b
withDoubleArray = withLArray realToFrac

withDayArray :: [Day] -> ((CUInt, Ptr CInt) -> IO b) -> IO b
withDayArray x f = mapM toSerial x >>= (`withArray` (\px -> f (fromIntegral $ length x, px)))

withDayPtr :: [Day] -> (Ptr CInt -> IO a) -> IO a
withDayPtr x f = mapM toSerial x >>= (`withArray` f)

prePtr :: (Storable a) => (Ptr a -> IO b) -> IO b
prePtr = alloca

preArray :: ((Ptr CUInt, Ptr (Ptr a)) -> IO b) -> IO b
preArray f = with 0 $
  \x -> with nullPtr $
    \y -> f (x, y)

peekIntArray' :: (CInt -> b) -> Ptr CUInt -> Ptr (Ptr CInt) -> IO [b]
peekIntArray' f pl pp = do
  l <- peek pl
  p <- peek pp
  map f <$> peekArray (fromIntegral l) p <* qlFreeInts p

peekUIntArray :: Ptr CUInt -> Ptr (Ptr CUInt) -> IO [Word]
peekUIntArray pl pp = do
  l <- peek pl
  p <- peek pp
  map fromIntegral <$> peekArray (fromIntegral l) p <* qlFreeUInts p

peekIntArray :: Ptr CUInt -> Ptr (Ptr CInt) -> IO [Int]
peekIntArray = peekIntArray' fromIntegral

peekBoolArray :: Ptr CUInt -> Ptr (Ptr CInt) -> IO [Bool]
peekBoolArray = peekIntArray' toBool

peekDayArray :: Ptr CUInt -> Ptr (Ptr CInt) -> IO [Day]
peekDayArray = peekIntArray' fromSerial

peekDoubleArray :: Ptr CUInt -> Ptr (Ptr CDouble) -> IO [Double]
peekDoubleArray pl pp = do
  l <- peek pl
  p <- peek pp
  map realToFrac <$> peekArray (fromIntegral l) p <* qlFreeDoubles p

withMaybeObject :: (ForeignObject a) => Maybe a -> (Ptr a -> IO b) -> IO b
withMaybeObject x f = maybe (f nullPtr) (`withObject` f) x

fromEnumQuantity :: (Enum a, Integral b, Integral c, Storable c) => (b, a) -> (CInt, c)
fromEnumQuantity (x, u) = (fromIntegral x, fromIntegral $ fromEnum u)

toEnumQuantity :: (Enum a, Integral c, Storable c, Integral b) => (CInt, c) -> (b, a)
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

dayIsValid :: Day -> Bool
dayIsValid x = s >= qlMinDateSerialNumber && s <= qlMaxDateSerialNumber
  where s = toModifiedJulianDay' x - qlStart

toSerial :: Day -> IO CInt
toSerial x | dayIsValid x = return $ toModifiedJulianDay' x - qlStart
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

-- |earliest allowed date in QuantLib
minDate :: Day
minDate = fromSerial qlMinDateSerialNumber

-- |latest date allowed in QuantLib
maxDate :: Day
maxDate = fromSerial qlMaxDateSerialNumber

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
