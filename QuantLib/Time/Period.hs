{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Time.Period
  (
    Period
  , CPeriod
  , period
  , fromFrequency
  , toFrequency
  )
where

import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Internal
import qualified QuantLib.Time.Frequency as F(Frequency)
import QuantLib.Time.Unit(Unit)

data CPeriod
type Period = Object CPeriod

foreign import ccall safe "ql.h qlPeriod"
  c_period :: CInt -> CInt -> Ptr CString -> IO (Ptr CPeriod)
foreign import ccall safe "ql.h &qlFreePeriod"
  p_freePeriod :: FunPtr (Ptr CPeriod -> IO ())
foreign import ccall safe "ql.h qlPeriodFromFrequency"
  c_periodFromFreq :: CInt -> Ptr CString -> IO (Ptr CPeriod)
foreign import ccall safe "ql.h qlPeriodToFrequency"
  c_periodToFreq :: Ptr CPeriod -> Ptr CString -> IO CInt

instance Finalizable CPeriod where
  finalize = p_freePeriod

period :: Int -> Unit -> IO Period
period n u = construct $ c_period (fromIntegral n) (toQlEnum u)

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual) (qlPeriodFromFrequency)
fromFrequency :: F.Frequency -> IO Period
fromFrequency f = construct $ c_periodFromFreq (toQlEnum f)

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M) (qlFrequencyFromPeriod)
toFrequency :: Period -> F.Frequency
toFrequency p = fromQlEnum $ unsafePerformIO (withObject p (handleExceptions . c_periodToFreq))
