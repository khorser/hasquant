{-# LANGUAGE TemplateHaskell #-}
-- |global repository for run-time library settings
module QuantLib.Settings
  (
    evaluationDate
  , setEvaluationDate
  , enforceTodaysHistoricFixings
  , setEnforceTodaysHistoricFixings
  , includeTodaysCashFlows
  , setIncludeTodaysCashFlows
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Utils

import Foreign.Marshal.Utils(toBool)

foreign import ccall safe "ql.h qlSettingsEvaluationDate"
  c_evaluationDate :: IO CDate
foreign import ccall safe "ql.h qlSettingsEnforceTodaysHistoricFixings"
  c_enforceTodaysHistoricFixings :: IO CInt
foreign import ccall safe "ql.h qlSettingsSetEvaluationDate"
  c_setEvaluationDate :: CDate -> Ptr CString -> IO ()
foreign import ccall safe "ql.h qlSettingsSetEnforceTodaysHistoricFixings"
  c_setEnforceTodaysHistoricFixings :: CInt -> IO ()

-- |returns the current value of the Evaluation Date:
-- the date at which pricing is to be performed. QuantLibXL: qlSettingsEvaluationDate
evaluationDate :: IO Day
evaluationDate = $(ffiCall 'evaluationDate) c_evaluationDate

-- |sets the value of the Evaluation Date. QuantLibXL: qlSettingsSetEvaluationDate
setEvaluationDate :: Maybe Day -> IO ()
setEvaluationDate = $(ffiCallX 'setEvaluationDate) c_setEvaluationDate

-- |returns the current value of the boolean which enforce the usage of historic
-- fixings for today's date. QuantLibXL: qlSettingsEnforceTodaysHistoricFixings
enforceTodaysHistoricFixings :: IO Bool
enforceTodaysHistoricFixings =
  $(ffiCall 'enforceTodaysHistoricFixings) c_enforceTodaysHistoricFixings

-- |sets the value of the boolean which enforce the usage of historic fixings
-- for today's date. QuantLibXL: qlSettingsSetEnforceTodaysHistoricFixings
setEnforceTodaysHistoricFixings :: Bool -> IO ()
setEnforceTodaysHistoricFixings =
  $(ffiCall 'setEnforceTodaysHistoricFixings) c_setEnforceTodaysHistoricFixings

-- easier to code it by hand than update Internal.Syntax
includeTodaysCashFlows :: IO (Maybe Bool)
includeTodaysCashFlows = do
  v <- c_includeTodaysCashFlows
  return $ if v == -1
            then Nothing
            else Just $ toBool v

foreign import ccall safe "ql.h qlSettingsIncludeTodaysCashFlows"
  c_includeTodaysCashFlows ::  IO CInt

setIncludeTodaysCashFlows :: Maybe Bool -> IO ()
setIncludeTodaysCashFlows = $(ffiCall 'setIncludeTodaysCashFlows) c_setIncludeTodaysCashFlows

foreign import ccall safe "ql.h qlSettingsSetIncludeTodaysCashFlows"
  c_setIncludeTodaysCashFlows :: CInt -> IO ()
