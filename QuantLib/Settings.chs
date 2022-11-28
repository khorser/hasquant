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
  , version
  , boostVersion
  , epsilon
  ) where
import Foreign.C.Types
import Foreign.C.String(CString, peekCString)
import System.IO.Unsafe(unsafePerformIO)
import System.Mem(performGC)

import Control.Exception(bracket)

import QuantLib.Time.Date
import QuantLib.Internal

#include "qlTypesC2HS.h"
#include "ql.h"

-- |returns the current value of the Evaluation Date:
-- the date at which pricing is to be performed
{#fun qlSettingsEvaluationDate as evaluationDate{}->`Day'toDay#}
-- |sets the value of the Evaluation Date
-- |Nothing sets the evaluation date to Date::todaysDate() and allow it to change at midnight. This comes at the price of losing some performance, since the evaluation date is re-evaluated each time it is read.
{#fun qlSettingsSetEvaluationDate as setEvaluationDate{withMaybeDay*`Maybe Day',preErrorCheck-`String'errorCheck*-}->`()'#}
-- |returns the current value of the boolean which enforce the usage of historic
-- fixings for today's date
{#fun qlSettingsEnforceTodaysHistoricFixings as enforceTodaysHistoricFixings{}->`Bool'#}
-- |sets the value of the boolean which enforce the usage of historic fixings
-- for today's date
{#fun qlSettingsSetEnforceTodaysHistoricFixings as setEnforceTodaysHistoricFixings{`Bool'}->`()'#}
{#fun qlSettingsIncludeTodaysCashFlows as includeTodaysCashFlows{}->`Maybe Bool' toMaybeBool#}
{#fun qlSettingsSetIncludeTodaysCashFlows as setIncludeTodaysCashFlows{fromMaybeBool`Maybe Bool'}->`()'#}

-- |This flag specifies whether or not Events occurring on the reference date should, by default, be taken into account as not happened yet. It can be overridden locally when calling the Event::hasOccurred method.
{#fun qlSettingsIncludeReferenceDateEvents as includeReferenceDateEvents{}->`Bool'#}
{#fun qlSettingsSetIncludeReferenceDateEvents as setIncludeReferenceDateEvents{`Bool'}->`()'#}

-- |brackets to restore settings once action has completed or raised an exception
keepingSettings :: IO b -> IO b
keepingSettings = bracket qlSavedSettings qlFreeSavedSettings . const
-- SavedSettings destructor suppresses all exceptions

-- |brackets to restore settings once action has completed or raised an exception. Before restoring settings
-- garbage collection is run to avoid problems with market data objects watching evaluation date
keepingSettings' :: IO b -> IO b
keepingSettings' = bracket qlSavedSettings (\s -> performGC >> qlFreeSavedSettings s) . const

foreign import ccall safe "ql.h qlVersion" qlVersion :: IO CString
foreign import ccall safe "ql.h qlBoostVersion" qlBoostVersion :: IO CString
foreign import ccall safe "ql.h qlEpsilon" qlEpsilon :: CDouble

{-# NOINLINE version #-}
version :: String
version = unsafePerformIO $ qlVersion >>= peekCString

{-# NOINLINE boostVersion #-}
boostVersion :: String
boostVersion = unsafePerformIO $ qlBoostVersion >>= peekCString

epsilon :: Double
epsilon = realToFrac qlEpsilon

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
