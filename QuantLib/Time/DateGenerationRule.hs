{-# LANGUAGE ForeignFunctionInterface #-}
module QuantLib.Time.DateGenerationRule
  (
    DateGenerationRule(..)
  , fromDateGenerationRule
  , toDateGenerationRule
  )
where

import Foreign.C.Types(CInt)
import Foreign.Ptr(Ptr)

import QuantLib.Internal(fromQlEnum, toQlEnum)

-- the order should be identical to that in qlDateGenerationRule.cpp!
data DateGenerationRule = Backward | Forward | Zero | ThirdWednesday | Twentieth | TwentiethIMM | OldCDS | CDS
  deriving (Show, Eq, Enum)

foreign import ccall safe "ql.h qlDateGenerationRule"
  c_values :: Ptr CInt -> IO (Ptr CInt)

fromDateGenerationRule :: DateGenerationRule -> CInt
fromDateGenerationRule = toQlEnum c_values

toDateGenerationRule :: CInt -> DateGenerationRule
toDateGenerationRule = fromQlEnum c_values
