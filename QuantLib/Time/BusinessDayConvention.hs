{-# LANGUAGE ForeignFunctionInterface #-}
module QuantLib.Time.BusinessDayConvention
  (
    BusinessDayConvention(..)
  , fromBusinessDayConvention
  , toBusinessDayConvention
  )

where

import Foreign.C.Types(CInt)
import Foreign.Ptr(Ptr)

import QuantLib.Internal(fromQlEnum, toQlEnum)

data BusinessDayConvention = Following | ModifiedFollowing | Preceding | ModifiedPreceding | Unadjusted
  deriving (Show, Eq, Enum)

foreign import ccall safe "ql.h qlBusinessDayConvention"
  c_values :: Ptr CInt -> IO (Ptr CInt)

fromBusinessDayConvention :: BusinessDayConvention -> CInt
fromBusinessDayConvention = toQlEnum c_values

toBusinessDayConvention :: CInt -> BusinessDayConvention
toBusinessDayConvention = fromQlEnum c_values
