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

import Foreign.Marshal.Utils(toBool)
import Foreign.Ptr(Ptr)

import System.Mem(performGC)

import Control.Exception(bracket)

import QuantLib.Date
import QuantLib.Utility

#include "ql.h"

-- |returns the current value of the Evaluation Date:
-- the date at which pricing is to be performed
{#fun qlSettingsEvaluationDate as evaluationDate {} -> `Day' toDay #}

-- |sets the value of the Evaluation Date
-- |Nothing sets the evaluation date to Date::todaysDate() and allow it to change at midnight. This comes at the price of losing some performance, since the evaluation date is re-evaluated each time it is read.
{#fun qlSettingsSetEvaluationDate as setEvaluationDate {fromDay'* `Maybe Day', preErrorCheck- `String' errorCheck*-} -> `()' #}

-- |returns the current value of the boolean which enforce the usage of historic
-- fixings for today's date
{#fun qlSettingsEnforceTodaysHistoricFixings as enforceTodaysHistoricFixings {} -> `Bool' #}

-- |sets the value of the boolean which enforce the usage of historic fixings
-- for today's date
{#fun qlSettingsSetEnforceTodaysHistoricFixings as setEnforceTodaysHistoricFixings {`Bool'} -> `()' #}

{#fun qlSettingsIncludeTodaysCashFlows as includeTodaysCashFlows {} -> `Maybe Bool' toBool' #}

{#fun qlSettingsSetIncludeTodaysCashFlows as setIncludeTodaysCashFlows {fromBool' `Maybe Bool'} -> `()' #}

-- |This flag specifies whether or not Events occurring on the reference date should, by default, be taken into account as not happened yet. It can be overridden locally when calling the Event::hasOccurred method.
{#fun qlSettingsIncludeReferenceDateEvents as includeReferenceDateEvents {} -> `Bool' #}

{#fun qlSettingsSetIncludeReferenceDateEvents as setIncludeReferenceDateEvents {`Bool'} -> `()' #}

{#fun qlSavedSettings as savedSettings {} -> `Ptr ()' #}

{#fun qlFreeSavedSettings as freeSavedSettings {`Ptr ()'} -> `()' #}

-- |brackets to restore settings once action has completed or raised an exception
keepingSettings :: IO b -> IO b
keepingSettings = bracket savedSettings freeSavedSettings . const
-- SavedSettings destructor suppresses all exceptions

-- |brackets to restore settings once action has completed or raised an exception. Before restoring settings
-- garbage collection is run to avoid problems with market data objects watching evaluation date
keepingSettings' :: IO b -> IO b
keepingSettings' = bracket savedSettings (\s -> performGC >> freeSavedSettings s) . const

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
