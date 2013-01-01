{-# LANGUAGE ForeignFunctionInterface #-}
module QuantLib.Internal
  (
    fromQlDateSerialNumber
  , toQlDateSerialNumber
  , c_maxDateSerialNumber
  , c_minDateSerialNumber
  , c_freeString
  , isDateValid
  )
where

import Control.Exception(throw)
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, fromGregorian)

import Foreign.C.String(CString)
import Foreign.C.Types(CInt(CInt))

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

-- return Either instead?
toQlDateSerialNumber :: Day -> CInt
toQlDateSerialNumber x | isDateValid x = fromInteger $ toModifiedJulianDay x - qlStart
                       | otherwise = throw $ Error ("Invalid QuantLib date: " ++ show x)

isDateValid :: Day -> Bool
isDateValid x = toQlDateSerialNumberUnsafe x >= c_minDateSerialNumber
                  && toQlDateSerialNumberUnsafe x <= c_maxDateSerialNumber
