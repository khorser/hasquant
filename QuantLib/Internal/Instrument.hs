module QuantLib.Internal.Instrument(withExercise) where

import Foreign.Ptr(Ptr)
import QuantLib.Instrument(Exercise)
import QuantLib.Internal(ForeignObject(withObject))

-- i didn't want to expose withT functions so here we go with more boilerplate
withExercise :: Exercise -> (Ptr Exercise -> IO b) -> IO b
withExercise = withObject

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
