{-# LANGUAGE ForeignFunctionInterface,FlexibleInstances #-}
module QuantLib.Internal
  (
    fromQlDateSerialNumber
  , toQlDateSerialNumber
  , c_maxDateSerialNumber
  , c_minDateSerialNumber
  , c_freeString
  , handleExceptions
  , isValid
  )
where

import Control.Exception(throw)
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, fromGregorian)

import Foreign.C.String(CString, peekCString)
import Foreign.C.Types(CInt(CInt))
import Foreign.Marshal.Alloc(alloca)
import Foreign.Ptr(nullPtr, Ptr)
import Foreign.Storable(peek)

import QuantLib.Error(Error(Error))

foreign import ccall safe "ql.h qlFreeString"
    c_freeString :: CString -> IO ()

foreign import ccall safe "ql.h qlMinDateSerialNumber"
    c_minDateSerialNumber :: CInt
foreign import ccall safe "ql.h qlMaxDateSerialNumber"
    c_maxDateSerialNumber :: CInt
foreign import ccall safe "ql.h qlMinYear"
    c_minYear :: CInt
foreign import ccall safe "ql.h qlMinMonth"
    c_minMonth :: CInt
foreign import ccall safe "ql.h qlMinDay"
    c_minDay :: CInt

-- |Julian day of the QuantLib zero date
qlStart :: Integer
qlStart = minDateJulianDays - fromIntegral c_minDateSerialNumber
            where minDateJulianDays = toModifiedJulianDay
                    $ fromGregorian (fromIntegral c_minYear)
                                    (fromIntegral c_minMonth)
                                    (fromIntegral c_minDay)

fromQlDateSerialNumber :: CInt -> Day
fromQlDateSerialNumber p = ModifiedJulianDay $
                fromIntegral p + qlStart

toQlDateSerialNumberUnsafe :: Day -> CInt
toQlDateSerialNumberUnsafe x = fromInteger $ toModifiedJulianDay x - qlStart

handleExceptions :: (Ptr CString -> IO a) -> IO a
handleExceptions f =
   alloca $
     \errptr ->
     do r <- f errptr
        msg <- peek errptr
        if msg /= nullPtr 
          then do err <- peekCString msg
                  c_freeString msg
                  throw (Error err)
          else return r

class QLDate a where
  isValid :: a -> Bool
  toQlDateSerialNumber :: a -> CInt

instance QLDate Day where
  isValid x = num >= c_minDateSerialNumber && num <= c_maxDateSerialNumber
                where num = toQlDateSerialNumberUnsafe x
  -- return Either instead?
  toQlDateSerialNumber x | isValid x = fromInteger $ toModifiedJulianDay x - qlStart
                         | otherwise = throw $ Error ("Invalid QuantLib date: " ++ show x)
  

instance QLDate (Maybe Day) where
  isValid Nothing = True
  isValid (Just x) = isValid x

  toQlDateSerialNumber Nothing = 0 
  toQlDateSerialNumber (Just x) = toQlDateSerialNumber x
