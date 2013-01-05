{-# LANGUAGE ForeignFunctionInterface #-}
module QuantLib.Time.Frequency
  (
    Frequency(..)
  , fromFrequency
  , toFrequency
  )

where

import Foreign.C.Types(CInt)
import Foreign.Ptr(Ptr)

import QuantLib.Internal(fromQlEnum, toQlEnum)

-- the order should be identical to that in qlFrequency.cpp!
data Frequency = NoFrequency | Annual | Semiannual | EveryFourthMonth | Quarterly
 | Bimonthly | Monthly | Biweekly | EveryFourthWeek | Weekly | Daily | Once | Other
 deriving (Show, Eq, Enum)

foreign import ccall safe "ql.h qlFrequency"
  c_values :: Ptr CInt -> IO (Ptr CInt)

fromFrequency :: Frequency -> CInt
fromFrequency = toQlEnum c_values

toFrequency :: CInt -> Frequency
toFrequency = fromQlEnum c_values
