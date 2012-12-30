{-# LANGUAGE ForeignFunctionInterface #-}

module QuantLib.Internal(c_freeString, toQlDate, fromQlDate, checkError)
where

import Foreign.Ptr
import Foreign.C.Types
import Foreign.C.String
import Control.Exception
import Data.Time.Calendar

import QuantLib.Error

foreign import ccall safe "ql.h qlFreeString"
    c_freeString :: CString -> IO ()
foreign import ccall safe "ql.h qlMinDate" c_minDate :: CInt
foreign import ccall safe "ql.h qlMinYear" c_minYear :: CInt
foreign import ccall safe "ql.h qlMinMonth" c_minMonth :: CInt
foreign import ccall safe "ql.h qlMinDay" c_minDay :: CInt

-- Julian day of the QuantLib zero date
qlStart :: Integer
qlStart = let minDateQlDays = fromIntegral c_minDate
              minDateJulianDates = toModifiedJulianDay
                $ fromGregorian (fromIntegral c_minYear)
                                (fromIntegral c_minMonth)
                                (fromIntegral c_minDay)
              in minDateJulianDates - minDateQlDays

fromQlDate :: CInt -> Day
fromQlDate x = ModifiedJulianDay $ fromIntegral x + qlStart

toQlDate :: Day -> CInt
toQlDate x = fromInteger $ toModifiedJulianDay x - qlStart

checkError :: CString -> IO ()
checkError result = 
      unless (result == nullPtr) $
        do msg <- peekCString result
           c_freeString result
           throw (Error msg)
