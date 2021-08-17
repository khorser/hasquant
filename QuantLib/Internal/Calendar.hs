module QuantLib.Internal.Calendar(withCalendar) where

import Foreign.Ptr(Ptr)
import QuantLib.Time.Calendar(Calendar)
import QuantLib.Internal(ForeignObject(withObject))

-- i didn't want to expose withT functions so here we go with more boilerplate
withCalendar :: Calendar -> (Ptr Calendar -> IO b) -> IO b
withCalendar = withObject
