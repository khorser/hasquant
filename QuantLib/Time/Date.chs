module QuantLib.Time.Date
  (
    Day
  , fromSerial
  , toSerial
  )
where

import Control.Exception(throwIO)
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, fromGregorian)
import QuantLib.Internal.Types(Error(DateConversion))

#include "ql.h"

{#fun pure qlMinYear as minYear {} -> `Int' #}

{#fun pure qlMinMonth as minMonth {} -> `Int' #}

{#fun pure qlMinDay as minDay {} -> `Int' #}

{#fun pure qlMinDateSerialNumber as minDateSerialNumber {} -> `Int' #}

{#fun pure qlMaxDateSerialNumber as maxDateSerialNumber {} -> `Int' #}

-- |Julian day of the QuantLib zero date
qlStart :: Int
qlStart = fromIntegral minDateJulianDays - minDateSerialNumber
  where minDateJulianDays = toModifiedJulianDay $ fromGregorian (fromIntegral minYear) (fromIntegral minMonth) (fromIntegral minDay)

fromSerial :: Int -> Day
fromSerial x = ModifiedJulianDay $ fromIntegral (x + qlStart)

isValid :: Day -> Bool
isValid x = s >= minDateSerialNumber && s <= maxDateSerialNumber
  where s = (fromIntegral $ toModifiedJulianDay x) - qlStart

toSerial :: Day -> IO Int
toSerial x | isValid x = return $ (fromIntegral $ toModifiedJulianDay x) - qlStart
           | otherwise = throwIO $ DateConversion x

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
