{-# LANGUAGE ForeignFunctionInterface, DeriveDataTypeable #-}

module Main(version, settingsEvaluationDate, settingsSetEvaluationDate, QLError, main)
where

import Prelude hiding(catch)

import Foreign.Ptr
import Foreign.C.Types
import Foreign.C.String
import System.IO.Unsafe

import Data.Time.Calendar
import Control.Monad
import Control.Exception
import Data.Typeable

foreign import ccall safe "qlsettings.h qlVersion"
    c_version :: CString
foreign import ccall safe "qlsettings.h boostVersion"
    c_boostVersion :: CString
foreign import ccall safe "qlsettings.h qlFreeString"
    c_freeString :: CString -> IO ()
foreign import ccall safe "qlsettings.h qlSettingsEvaluationDate"
    c_settingsEvaluationDate :: IO CInt
foreign import ccall safe "qlsettings.h qlSettingsSetEvaluationDate"
    c_settingsSetEvaluationDate :: CInt -> IO CString

foreign import ccall safe "qlsettings.h qlMinDate" c_minDate :: CInt
foreign import ccall safe "qlsettings.h qlMinYear" c_minYear :: CInt
foreign import ccall safe "qlsettings.h qlMinMonth" c_minMonth :: CInt
foreign import ccall safe "qlsettings.h qlMinDay" c_minDay :: CInt

version :: String
version = unsafePerformIO $ peekCString c_version

boostVersion :: String
boostVersion = unsafePerformIO $ peekCString c_boostVersion

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

settingsEvaluationDate :: IO Day
settingsEvaluationDate = liftM fromQlDate c_settingsEvaluationDate

data QLError = QLError{message::String} deriving (Typeable, Show)
instance Exception QLError

settingsSetEvaluationDate :: Day -> IO ()
settingsSetEvaluationDate x =
  do result <- c_settingsSetEvaluationDate (toQlDate x)
     unless (result == nullPtr) $
       do msg <- peekCString result
          c_freeString result
          throw (QLError msg)

main :: IO ()
main = do
        putStrLn version
        putStrLn boostVersion
        d <- settingsEvaluationDate
        print d
        settingsSetEvaluationDate $ fromGregorian 2012 12 29
        d1 <- settingsEvaluationDate
        print d1
        catch (settingsSetEvaluationDate $ fromGregorian 1861 1 1)
            (\e -> do putStrLn $ "Caught QuantLib exception: " ++ message e)
        putStrLn "OK"
