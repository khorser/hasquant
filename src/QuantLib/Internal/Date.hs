{-# LANGUAGE FlexibleInstances #-}
module QuantLib.Internal.Date
  (
    Day
  , CDate
  , CYearFraction
  , c_maxDateSerialNumber
  , c_minDateSerialNumber
  , isValid
  , withDays
  , c_weekday
  , fromQlDate
  , toQlDate
  )
where

import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, fromGregorian)
import Foreign.Marshal.Array(withArrayLen)

import QuantLib.Internal.Utils

type CDate = CInt
type CYearFraction = CDouble

foreign import ccall safe "ql.h qlMinDateSerialNumber"
  c_minDateSerialNumber :: CDate
foreign import ccall safe "ql.h qlMaxDateSerialNumber"
  c_maxDateSerialNumber :: CDate
foreign import ccall safe "ql.h qlMinYear"
  c_minYear :: CInt
foreign import ccall safe "ql.h qlMinMonth"
  c_minMonth :: CInt
foreign import ccall safe "ql.h qlMinDay"
  c_minDay :: CInt

foreign import ccall safe "ql.h qlWeekday"
  c_weekday :: CInt -> CInt

-- |Julian day of the QuantLib zero date
qlStart :: Integer
qlStart = minDateJulianDays - fromIntegral c_minDateSerialNumber
            where minDateJulianDays = toModifiedJulianDay
                    $ fromGregorian (fromIntegral c_minYear)
                                    (fromIntegral c_minMonth)
                                    (fromIntegral c_minDay)

toQlDateUnsafe :: Day -> CDate
toQlDateUnsafe x = fromIntegral $ toModifiedJulianDay x - qlStart

withDays :: [Day] -> (CUInt -> Ptr CDate -> IO b) -> IO b
withDays days f = withArrayLen
                      (map toQlDate days)
                      (\n d -> f (fromIntegral n) d)

class QLDate a where
  isValid :: a -> Bool
  toQlDate :: a -> CDate
  fromQlDate :: CDate -> a

instance QLDate Day where
  isValid x = num >= c_minDateSerialNumber && num <= c_maxDateSerialNumber
                where num = toQlDateUnsafe x
  -- return Either instead?
  toQlDate x | isValid x = fromIntegral $ toModifiedJulianDay x - qlStart
                         | otherwise = signalError ("Invalid QuantLib date: " ++ show x)
  fromQlDate p = ModifiedJulianDay $ fromIntegral p + qlStart

instance QLDate (Maybe Day) where
  isValid = maybe True isValid
  toQlDate = maybe 0 toQlDate
  fromQlDate 0 = Nothing
  fromQlDate x = Just $ fromQlDate x

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
