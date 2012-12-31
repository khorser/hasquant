{-# LANGUAGE ForeignFunctionInterface #-}
module QuantLib.Settings
  (
    evaluationDate
  , setEvaluationDate
  , enforceTodaysHistoricFixings
  , setEnforceTodaysHistoricFixings
  )
where

import Control.Exception(throw)
import Control.Monad(liftM)
import Data.Time.Calendar(Day)
import Foreign.C.Types(CInt(CInt))
import Foreign.Marshal.Utils(fromBool, toBool)
import Foreign.Ptr(Ptr)

import QuantLib.Error(Error(Error))
import QuantLib.Internal(CDate, fromQlDateSerialNumber, allocateDate, freeDate)

foreign import ccall safe "ql.h qlSettingsEvaluationDate"
    c_evaluationDate :: IO CInt
foreign import ccall safe "ql.h qlSettingsSetEvaluationDate"
    c_setEvaluationDate :: Ptr CDate -> IO ()
foreign import ccall safe "ql.h qlSettingsEnforceTodaysHistoricFixings"
    c_enforceTodaysHistoricFixings :: IO CInt
foreign import ccall safe "ql.h qlSettingsSetEnforceTodaysHistoricFixings"
    c_setEnforceTodaysHistoricFixings :: CInt -> IO ()

-- |returns the current value of the Evaluation Date (qlSettingsEvaluationDate)
evaluationDate :: IO Day
evaluationDate = liftM fromQlDateSerialNumber c_evaluationDate

-- |sets the value of the Evaluation Date (qlSettingsSetEvaluationDate)
setEvaluationDate :: Day -> IO ()
setEvaluationDate x =
  do d <- allocateDate x
     case d of
       Left e   -> throw $ Error e -- shall we use exceptions here?
       Right p  -> c_setEvaluationDate p >> freeDate p

-- |returns the current value of the boolean which enforce the usage of historic
-- fixings for today's date (qlSettingsEnforceTodaysHistoricFixings)
enforceTodaysHistoricFixings :: IO Bool
enforceTodaysHistoricFixings = liftM toBool c_enforceTodaysHistoricFixings

-- |sets the value of the boolean which enforce the usage of historic fixings
-- for today's date (qlSettingsSetEnforceTodaysHistoricFixings)
setEnforceTodaysHistoricFixings :: Bool -> IO ()
setEnforceTodaysHistoricFixings = c_setEnforceTodaysHistoricFixings . fromBool
