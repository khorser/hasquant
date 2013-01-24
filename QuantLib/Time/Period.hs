module QuantLib.Time.Period
  (
  -- makers
    period
  , fromFrequency
  -- accessors
  , toFrequency
  )
where

import QuantLib.Internal.Enum
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
period n u = construct $ c_period (fromIntegral n) (toQlEnum u)

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual) (qlPeriodFromFrequency)
fromFrequency :: F.Frequency -> IO Period
fromFrequency f = construct $ c_periodFromFreq (toQlEnum f)

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M) (qlFrequencyFromPeriod)
toFrequency :: Period -> F.Frequency
toFrequency p = fromQlEnum $ unsafePerformIO (withObject p (handleExceptions . c_periodToFreq))
