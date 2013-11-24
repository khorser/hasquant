{-# LANGUAGE FlexibleInstances #-}
module QuantLib.Internal.Date
  (
    Day
  , CDate
  , CYearFraction
  , c_maxDateSerialNumber
  , c_minDateSerialNumber
  , isValid
  , withDay
  , withDays
  , fromQlDate
  , toQlDate
  )
where

import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, fromGregorian)

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

-- |Julian day of the QuantLib zero date
qlStart :: Integer
qlStart = minDateJulianDays - fromIntegral c_minDateSerialNumber
            where minDateJulianDays = toModifiedJulianDay
                    $ fromGregorian (fromIntegral c_minYear)
                                    (fromIntegral c_minMonth)
                                    (fromIntegral c_minDay)

toQlDateNoCheck :: Day -> CDate
toQlDateNoCheck x = fromIntegral $ toModifiedJulianDay x - qlStart

withDay :: (QLDate a) => a -> (CDate -> IO b) -> IO b
withDay x f = toQlDate x >>= f

withDays :: [Day] -> (CUInt -> Ptr CDate -> IO b) -> IO b
withDays = withArrayULenTIO toQlDate

class QLDate a where
  isValid :: a -> Bool
  toQlDate :: a -> IO CDate
  fromQlDate :: CDate -> a

instance QLDate Day where
  isValid x = num >= c_minDateSerialNumber && num <= c_maxDateSerialNumber
                where num = toQlDateNoCheck x
  toQlDate x | isValid x = return $ fromIntegral (toModifiedJulianDay x - qlStart)
             | otherwise = signalErrorIO ("Invalid QuantLib date: " ++ show x)
  fromQlDate p = ModifiedJulianDay $ fromIntegral p + qlStart

instance QLDate (Maybe Day) where
  isValid = maybe True isValid
  toQlDate = maybe (return 0) toQlDate
  fromQlDate 0 = Nothing
  fromQlDate x = Just $ fromQlDate x

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
