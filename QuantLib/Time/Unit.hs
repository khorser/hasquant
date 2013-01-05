{-# LANGUAGE ForeignFunctionInterface #-}
module QuantLib.Time.Unit
  (
    Unit(..)
  , fromUnit
  , toUnit
  )

where

import Foreign.C.Types(CInt)
import Foreign.Ptr(Ptr)

import QuantLib.Internal(fromQlEnum, toQlEnum)

data Unit = Months | Days | Weeks | Years
  deriving (Show, Eq, Enum)

data BusinessDayConvention = Following | ModifiedFollowing | Preceding | ModifiedPreceding | Unadjusted
  deriving (Show, Eq, Enum)

foreign import ccall safe "ql.h qlTimeUnit"
  c_values :: Ptr CInt -> IO (Ptr CInt)

fromUnit :: Unit -> CInt
fromUnit = toQlEnum c_values

toUnit :: CInt -> Unit
toUnit = fromQlEnum c_values
