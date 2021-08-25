module QuantLib.Time.Calendar
  (
    Calendar
  )

where

import Foreign.ForeignPtr(ForeignPtr)

newtype Calendar = Calendar (ForeignPtr Calendar)
instance Show Calendar
instance Eq Calendar
