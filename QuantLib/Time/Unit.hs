{-# LANGUAGE ForeignFunctionInterface #-}
module QuantLib.Time.Unit
  (
    Unit(..)
  , fromUnit
  )

where

import Foreign.C.Types(CInt(CInt))

data Unit = Months | Days | Weeks | Years deriving Show

-- use some preprocessor instead?
foreign import ccall safe "ql.h qlTimeUnitMonths"
    c_months :: CInt
foreign import ccall safe "ql.h qlTimeUnitDays"
    c_days :: CInt
foreign import ccall safe "ql.h qlTimeUnitWeeks"
    c_weeks :: CInt
foreign import ccall safe "ql.h qlTimeUnitYears"
    c_years :: CInt

fromUnit :: Unit -> CInt
fromUnit Months = c_months
fromUnit Days   = c_days
fromUnit Weeks  = c_weeks
fromUnit Years  = c_years
