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
  , includeReferenceDateEvents
  , setIncludeReferenceDateEvents

  , keepingSettings
  , keepingSettings'
  )
where

import Control.Exception(bracket)
import Foreign.Marshal.Utils(toBool)
import System.Mem(performGC)

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types hiding(evaluationDate
  , includeTodaysCashFlows
  , enforceTodaysHistoricFixings
  , includeReferenceDateEvents)

foreign import ccall safe "ql.h qlSettingsEvaluationDate"
  c_evaluationDate :: IO CDate
foreign import ccall safe "ql.h qlSettingsEnforceTodaysHistoricFixings"
  c_enforceTodaysHistoricFixings :: IO CInt
foreign import ccall safe "ql.h qlSettingsSetEvaluationDate"
  c_setEvaluationDate :: CDate -> Ptr CString -> IO ()
foreign import ccall safe "ql.h qlSettingsSetEnforceTodaysHistoricFixings"
  c_setEnforceTodaysHistoricFixings :: CInt -> IO ()

-- |returns the current value of the Evaluation Date:
-- the date at which pricing is to be performed
evaluationDate :: IO Day
evaluationDate = $(ffiCall 'evaluationDate) c_evaluationDate

-- |sets the value of the Evaluation Date
-- |Nothing sets the evaluation date to Date::todaysDate() and allow it to change at midnight. This comes at the price of losing some performance, since the evaluation date is re-evaluated each time it is read.
setEvaluationDate :: Maybe Day -> IO ()
setEvaluationDate = $(ffiCallX 'setEvaluationDate) c_setEvaluationDate

-- |returns the current value of the boolean which enforce the usage of historic
-- fixings for today's date
enforceTodaysHistoricFixings :: IO Bool
enforceTodaysHistoricFixings =
  $(ffiCall 'enforceTodaysHistoricFixings) c_enforceTodaysHistoricFixings

-- |sets the value of the boolean which enforce the usage of historic fixings
-- for today's date
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

-- |This flag specifies whether or not Events occurring on the reference date should, by default, be taken into account as not happened yet. It can be overridden locally when calling the Event::hasOccurred method.
includeReferenceDateEvents :: IO Bool
includeReferenceDateEvents = $(ffiCall 'includeReferenceDateEvents) c_includeReferenceDateEvents

foreign import ccall safe "ql.h qlSettingsIncludeReferenceDateEvents"
  c_includeReferenceDateEvents :: IO CInt

setIncludeReferenceDateEvents :: Bool -> IO ()
setIncludeReferenceDateEvents = $(ffiCall 'setIncludeReferenceDateEvents) c_setIncludeReferenceDateEvents

foreign import ccall safe "ql.h qlSettingsSetIncludeReferenceDateEvents"
  c_setIncludeReferenceDateEvents :: CInt -> IO ()

-- |brackets to restore settings once action has completed or raised an exception
keepingSettings :: IO b -> IO b
keepingSettings = bracket c_savedSettings c_freeSavedSettings . const
-- SavedSettings destructor suppresses all exceptions

-- |brackets to restore settings once action has completed or raised an exception. Before restoring settings
-- garbage collection is run to avoid problems with market data objects watching evaluation date
keepingSettings' :: IO b -> IO b
keepingSettings' = bracket c_savedSettings (\s -> performGC >> c_freeSavedSettings s) . const

data CSavedSettings

foreign import ccall safe "ql.h qlSavedSettings"
  c_savedSettings :: IO (Ptr CSavedSettings)

foreign import ccall safe "ql.h qlFreeSavedSettings"
  c_freeSavedSettings :: Ptr CSavedSettings -> IO ()

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
