{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Time.Calendar
  (
    Calendar
  )
where

import Foreign.ForeignPtr(ForeignPtr)

data CCalendar

type Calendar = ForeignPtr CCalendar
