{-# LANGUAGE ForeignFunctionInterface #-}

module QuantLib.Settings(
  evaluationDate,
  setEvaluationDate,
  enforceTodaysHistoricFixings,
  setEnforceTodaysHistoricFixings)
where

import Foreign.C.Types
import Foreign.C.String
import Foreign.Marshal.Utils

import Data.Time.Calendar
import Control.Monad

import QuantLib.Internal

foreign import ccall safe "ql.h qlSettingsEvaluationDate"
    c_evaluationDate :: IO CInt
foreign import ccall safe "ql.h qlSettingsSetEvaluationDate"
    c_setEvaluationDate :: CInt -> IO CString
foreign import ccall safe "ql.h qlSettingsEnforceTodaysHistoricFixings"
    c_enforceTodaysHistoricFixings :: IO CInt
foreign import ccall safe "ql.h qlSettingsSetEnforceTodaysHistoricFixings"
    c_setEnforceTodaysHistoricFixings :: CInt -> IO ()

-- | returns the current value of the Evaluation Date (qlSettingsEvaluationDate)
evaluationDate :: IO Day
evaluationDate = liftM fromQlDate c_evaluationDate

-- | sets the value of the Evaluation Date (qlSettingsSetEvaluationDate)
setEvaluationDate :: Day -> IO ()
setEvaluationDate x = c_setEvaluationDate (toQlDate x) >>= checkError

-- | returns the current value of the boolean which enforce the usage of historic
-- fixings for today's date (qlSettingsEnforceTodaysHistoricFixings)
enforceTodaysHistoricFixings :: IO Bool
enforceTodaysHistoricFixings = liftM toBool c_enforceTodaysHistoricFixings

-- | sets the value of the boolean which enforce the usage of historic fixings
-- for today's date (qlSettingsSetEnforceTodaysHistoricFixings)
setEnforceTodaysHistoricFixings :: Bool -> IO ()
setEnforceTodaysHistoricFixings = c_setEnforceTodaysHistoricFixings . fromBool
