{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Time.Period
  (
  -- makers
    period
  , fromFrequency
  -- accessors
  , toFrequency
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Utils
import QuantLib.Types
import qualified QuantLib.Time.Frequency as F(Frequency)
import QuantLib.Time.Unit(Unit)

foreign import ccall safe "ql.h qlPeriod"
  c_period :: CInt -> CInt -> Ptr CString -> IO (Ptr CPeriod)
foreign import ccall safe "ql.h qlPeriodFromFrequency"
  c_periodFromFreq :: CInt -> Ptr CString -> IO (Ptr CPeriod)
foreign import ccall safe "ql.h qlPeriodToFrequency"
  c_periodToFreq :: Ptr CPeriod -> Ptr CString -> IO CInt

period :: Int -> Unit -> IO Period
period = $(ffiConstruct 'period 'c_period)

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual) (qlPeriodFromFrequency)
fromFrequency :: F.Frequency -> IO Period
fromFrequency = $(ffiConstruct 'fromFrequency 'c_periodFromFreq)

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M) (qlFrequencyFromPeriod)
toFrequency :: Period -> F.Frequency
toFrequency = $(ffiCallXIO 'toFrequency 'c_periodToFreq)
