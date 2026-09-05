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
  , disableUpdates
  , enableUpdates
  , updatesEnabled
  , updatesDeferred

  , keepingSettings
  , keepingSettings'
  , collectGarbage
  , setExtendedPrecision
  , version
  , boostVersion
  , epsilon
  ) where
import Foreign.C.Types(CDouble)
import Foreign.C.String(CString, peekCString)
import System.IO.Unsafe(unsafePerformIO)
import System.Mem(performGC)
import Control.Exception(bracket)

import QuantLib.Time.Date
import QuantLib.Internal

#include "qlTypesC2HS.h"
#include "ql.h"

-- |Sets the x87 floating-point unit to 64-bit extended precision.
--
-- Call this once at program start on Windows, before any pricing. By the time Haskell
-- code runs there, the x87 unit sits at 53-bit precision, where a binary linked by
-- clang++ rather than ghc has 64-bit; every 80-bit @long double@ operation inside
-- QuantLib is then silently rounded to double. That matters because @boost::math@ promotes @double@
-- arguments to @long double@ by default, so its distributions lose the precision their
-- algorithms assume -- returning quietly less accurate answers, or failing to converge
-- outright (@hestonSLVFDMModel@ throws out of @quantile(non_central_chi_squared)@
-- without this).
--
-- A no-op on every other platform and on non-x86 Windows. The control word is
-- per-thread, so with a threaded runtime call it on each OS thread that prices. Only
-- the x87 unit is touched: Haskell's own 'Double' arithmetic is SSE\/MXCSR and is
-- unaffected either way.
{#fun qlSetExtendedPrecision as setExtendedPrecision{}->`()'#}

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

-- |if set, whether CashFlows occurring on today's date should enter the NPV; when the NPV date
-- equals today's date this overrides includeReferenceDateEvents and cannot be overridden locally
{#fun qlSettingsIncludeTodaysCashFlows as includeTodaysCashFlows{}->`Maybe Bool' toMaybeBool#}

-- |sets whether CashFlows occurring on today's date should enter the NPV
{#fun qlSettingsSetIncludeTodaysCashFlows as setIncludeTodaysCashFlows{fromMaybeBool`Maybe Bool'}->`()'#}

-- |This flag specifies whether or not Events occurring on the reference date should, by default, be taken into account as not happened yet. It can be overridden locally when calling the Event::hasOccurred method.
{#fun qlSettingsIncludeReferenceDateEvents as includeReferenceDateEvents{}->`Bool'#}

-- |sets whether Events occurring on the reference date should, by default, be taken into account as not happened yet
{#fun qlSettingsSetIncludeReferenceDateEvents as setIncludeReferenceDateEvents{`Bool'}->`()'#}

-- |Disables observer notifications. When @deferred@ is 'True', notifications are queued until
-- 'enableUpdates' is called; otherwise they are discarded.
{#fun qlObservableSettingsDisableUpdates as disableUpdates{`Bool' -- ^deferred
  }->`()'#}

-- |Enables observer notifications and runs any notifications queued while updates were deferred.
{#fun qlObservableSettingsEnableUpdates as enableUpdates{preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Whether observer notifications are currently enabled.
{#fun qlObservableSettingsUpdatesEnabled as updatesEnabled{}->`Bool'#}

-- |Whether observer notifications are currently disabled with deferred delivery enabled.
{#fun qlObservableSettingsUpdatesDeferred as updatesDeferred{}->`Bool'#}

-- |brackets to restore settings once action has completed or raised an exception
keepingSettings :: IO b -> IO b
keepingSettings = bracket qlSavedSettings qlFreeSavedSettings . const
-- SavedSettings destructor suppresses all exceptions

-- |brackets to restore settings once action has completed or raised an exception. Before restoring settings
-- 'collectGarbage' is run to avoid problems with market data objects watching evaluation date
keepingSettings' :: IO b -> IO b
keepingSettings' = bracket qlSavedSettings (\s -> collectGarbage >> qlFreeSavedSettings s) . const

-- |Best effort: give the finalizers of unreachable QuantLib objects a chance to run, so
-- their C++ destructors fire before, say, 'setEvaluationDate' notifies surviving observers.
--
-- 'performGC' only /schedules/ finalizers, it does not run them synchronously, so this is a
-- nudge rather than a guarantee. Where correctness depends on an object being gone, anchor
-- its dates so staleness cannot arise in the first place.
collectGarbage :: IO ()
collectGarbage = performGC >> performGC

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
