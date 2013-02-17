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
  , anchorEvaluationDate
  , includeReferenceDateEvents
  , resetEvaluationDate
  , setIncludeReferenceDateEvents

  , keepingSettings
  )
where

import Control.Exception(bracket)

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

-- |Call this to prevent the evaluation date to change at midnight (and, incidentally, to gain quite a bit of performance.) If no evaluation date was previously set, it is equivalent to setting the evaluation date to Date::todaysDate(); if an evaluation date other than Date() was already set, it has no effect.
anchorEvaluationDate :: IO ()
anchorEvaluationDate = $(ffiCall 'anchorEvaluationDate) c_anchorEvaluationDate

foreign import ccall safe "ql.h qlSettingsAnchorEvaluationDate"
  c_anchorEvaluationDate :: IO ()

-- |This flag specifies whether or not Events occurring on the reference date should, by default, be taken into account as not happened yet. It can be overridden locally when calling the Event::hasOccurred method.
includeReferenceDateEvents :: IO Bool
includeReferenceDateEvents = $(ffiCall 'includeReferenceDateEvents) c_includeReferenceDateEvents

foreign import ccall safe "ql.h qlSettingsIncludeReferenceDateEvents"
  c_includeReferenceDateEvents :: IO CInt

-- |Call this to reset the evaluation date to Date::todaysDate() and allow it to change at midnight. It is equivalent to setting the evaluation date to Date(). This comes at the price of losing some performance, since the evaluation date is re-evaluated each time it is read.
resetEvaluationDate :: IO ()
resetEvaluationDate = $(ffiCallX 'resetEvaluationDate) c_resetEvaluationDate

foreign import ccall safe "ql.h qlSettingsResetEvaluationDate"
  c_resetEvaluationDate :: Ptr CString -> IO ()

setIncludeReferenceDateEvents :: Bool -> IO ()
setIncludeReferenceDateEvents = $(ffiCall 'setIncludeReferenceDateEvents) c_setIncludeReferenceDateEvents

foreign import ccall safe "ql.h qlSettingsSetIncludeReferenceDateEvents"
  c_setIncludeReferenceDateEvents :: CInt -> IO ()

-- |brackets to restore settings once action has completed or raised an exception
keepingSettings :: IO b -> IO b
keepingSettings = bracket c_savedSettings c_freeSavedSettings . const
-- XXX add a variant doing GC?

data CSavedSettings

foreign import ccall safe "ql.h qlSavedSettings"
  c_savedSettings :: IO (Ptr CSavedSettings)

foreign import ccall safe "ql.h qlFreeSavedSettings"
  c_freeSavedSettings :: Ptr CSavedSettings -> IO ()
