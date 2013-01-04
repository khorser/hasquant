{-# LANGUAGE ForeignFunctionInterface #-}
module QuantLib.Time.BusinessDayConvention
  (
    BusinessDayConvention(..)
  , fromBusinessDayConvention
  )

where

import Foreign.C.Types(CInt(CInt))

data BusinessDayConvention = Following | ModifiedFollowing | Preceding | ModifiedPreceding | Unadjusted
  deriving (Show, Eq)

-- use some preprocessor instead?
foreign import ccall safe "ql.h qlBusinessDayConventionFollowing"
  c_following :: CInt
foreign import ccall safe "ql.h qlBusinessDayConventionModifiedFollowing"
  c_modifiedFollowing :: CInt
foreign import ccall safe "ql.h qlBusinessDayConventionPreceding"
  c_preceding :: CInt
foreign import ccall safe "ql.h qlBusinessDayConventionModifiedPreceding"
  c_modifiedPreceding :: CInt
foreign import ccall safe "ql.h qlBusinessDayConventionUnadjusted"
  c_unadjusted :: CInt

fromBusinessDayConvention :: BusinessDayConvention -> CInt
fromBusinessDayConvention Following = fromIntegral c_following
fromBusinessDayConvention ModifiedFollowing = fromIntegral c_modifiedFollowing
fromBusinessDayConvention Preceding = fromIntegral c_preceding
fromBusinessDayConvention ModifiedPreceding = fromIntegral c_modifiedPreceding
fromBusinessDayConvention Unadjusted = fromIntegral c_unadjusted
