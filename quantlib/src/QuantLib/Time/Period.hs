{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Time.Period
  (
    period
  , fromFrequency

  , toFrequency
  , parse
  )
where

import Prelude hiding(length)

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
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

period :: Int -- ^n
  -> Unit -- ^units
  -> IO Period
period = $(ffiCall 'period) c_period

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual). QuantLib: qlPeriodFromFrequency
fromFrequency :: F.Frequency -> IO Period
fromFrequency = $(ffiCall 'fromFrequency) c_periodFromFreq

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M). QuantLib: qlFrequencyFromPeriod
toFrequency :: Period -> Either String F.Frequency
toFrequency = $(ffiCallPureX 'toFrequency) c_periodToFreq

parse :: String -> IO Period
parse = $(ffiCall 'parse) c_parse

foreign import ccall safe "ql.h qlPeriodParserParse"
  c_parse :: CString -> Ptr CString -> IO (Ptr CPeriod)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
