module QuantLib.Settings
  (
  -- accessors and mutators
    evaluationDate
  , setEvaluationDate
  , enforceTodaysHistoricFixings
  , setEnforceTodaysHistoricFixings
  )
where

import Control.Monad(liftM)

import QuantLib.Internal.Date
import QuantLib.Internal.Utils

foreign import ccall safe "ql.h qlSettingsEvaluationDate"
  c_evaluationDate :: IO CDate
foreign import ccall safe "ql.h qlSettingsEnforceTodaysHistoricFixings"
  c_enforceTodaysHistoricFixings :: IO CInt
foreign import ccall safe "ql.h qlSettingsSetEvaluationDate"
  c_setEvaluationDate :: CDate -> Ptr CString -> IO ()
foreign import ccall safe "ql.h qlSettingsSetEnforceTodaysHistoricFixings"
  c_setEnforceTodaysHistoricFixings :: CInt -> Ptr CString -> IO ()

-- |returns the current value of the Evaluation Date (qlSettingsEvaluationDate)
evaluationDate :: IO Day
evaluationDate = liftM fromQlDate c_evaluationDate

-- |sets the value of the Evaluation Date (qlSettingsSetEvaluationDate)
setEvaluationDate :: Maybe Day -> IO ()
setEvaluationDate x = handleExceptions $ c_setEvaluationDate (toQlDate x)

-- |returns the current value of the boolean which enforce the usage of historic
-- fixings for today's date (qlSettingsEnforceTodaysHistoricFixings)
enforceTodaysHistoricFixings :: IO Bool
enforceTodaysHistoricFixings = liftM toBool c_enforceTodaysHistoricFixings

-- |sets the value of the boolean which enforce the usage of historic fixings
-- for today's date (qlSettingsSetEnforceTodaysHistoricFixings)
setEnforceTodaysHistoricFixings :: Bool -> IO ()
setEnforceTodaysHistoricFixings x = handleExceptions $
      c_setEnforceTodaysHistoricFixings (fromBool x)
