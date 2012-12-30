{-# LANGUAGE ForeignFunctionInterface #-}

module Main(qlVersion, qlSettingsEvaluationDate, qlSettingsSetEvaluationDate, main)
where

import Foreign.C.Types
import Foreign.C.String
import System.IO.Unsafe

import Data.Time.Calendar
import Control.Monad

foreign import ccall "qlsettings.h qlVersion" c_qlVersion :: CString
foreign import ccall "qlsettings.h qlSettingsEvaluationDate" c_qlSettingsEvaluationDate :: IO CInt
foreign import ccall "qlsettings.h qlSettingsSetEvaluationDate" c_qlSettingsSetEvaluationDate :: CInt -> IO ()

foreign import ccall "qlsettings.h qlMinDate" c_qlMinDate :: IO CInt
foreign import ccall "qlsettings.h qlMinYear" c_qlMinYear :: IO CInt
foreign import ccall "qlsettings.h qlMinMonth" c_qlMinMonth :: IO CInt
foreign import ccall "qlsettings.h qlMinDay" c_qlMinDay :: IO CInt

qlVersion :: String
qlVersion = unsafePerformIO $ peekCString c_qlVersion

-- Julian day of the QuantLib zero date
qlStart :: Integer
qlStart = unsafePerformIO $ do
                                d <- c_qlMinDay
                                m <- c_qlMinMonth
                                y <- c_qlMinYear
                                minDate <- c_qlMinDate
                                let julian = fromGregorian (fromIntegral y) (fromIntegral m) (fromIntegral d)
                                let julianDays = toModifiedJulianDay julian
                                return $ julianDays - fromIntegral minDate

fromQlDate :: CInt -> Day
fromQlDate x = ModifiedJulianDay $ fromIntegral x + qlStart

toQlDate :: Day -> CInt
toQlDate x = fromInteger $ toModifiedJulianDay x - qlStart

qlSettingsEvaluationDate :: IO Day
qlSettingsEvaluationDate = liftM fromQlDate c_qlSettingsEvaluationDate

qlSettingsSetEvaluationDate :: Day -> IO ()
qlSettingsSetEvaluationDate = c_qlSettingsSetEvaluationDate . toQlDate

main :: IO ()
main = do
        putStrLn qlVersion
        d <- qlSettingsEvaluationDate
        print d
        qlSettingsSetEvaluationDate $ fromGregorian 2012 12 29
        d1 <- qlSettingsEvaluationDate
        print d1
