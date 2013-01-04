{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Time.Period
  (
    period
  , fromFrequency
  , toFrequency
  )
where

import Control.Monad(liftM)

import Foreign.C.Types(CInt(CInt))
import Foreign.C.String(CString)
import Foreign.Ptr(Ptr, FunPtr)

import QuantLib.Internal(handleExceptions, constructO, Finalizable, finalize, Object, withObject)
import qualified QuantLib.Time.Frequency as F(Frequency, fromFrequency, toFrequency)
import QuantLib.Time.Unit(Unit, fromUnit)

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
period n u = constructO $ c_period (fromIntegral n) (fromUnit u)

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual) (qlPeriodFromFrequency)
fromFrequency :: F.Frequency -> IO Period
fromFrequency f = constructO $ c_periodFromFreq (F.fromFrequency f)

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M) (qlFrequencyFromPeriod)
toFrequency :: Period -> IO F.Frequency
toFrequency p = liftM F.toFrequency $ withObject p (handleExceptions . c_periodToFreq )
