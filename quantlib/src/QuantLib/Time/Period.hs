{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Time.Period
  (
    period
  , fromFrequency

  , toFrequency
  , parse

  , units
  , periodLength
  , addPeriods
  , subtractPeriods
  , dividePeriod

  , periodsEQ
  , periodsLT
  , normalize
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import qualified QuantLib.Time.Frequency as F(Frequency)
import QuantLib.Time.Unit(Unit)

foreign import ccall safe "ql.h qlPeriod"
  c_period :: CInt -> CInt -> Ptr CString -> IO (Ptr CPeriod)
foreign import ccall safe "ql.h qlPeriodFromFrequency"
  c_fromFrequency :: CInt -> Ptr CString -> IO (Ptr CPeriod)
foreign import ccall safe "ql.h qlPeriodToFrequency"
  c_toFrequency :: Ptr CPeriod -> Ptr CString -> IO CInt

period :: Int -- ^n
  -> Unit -- ^units
  -> IO Period
period = $(ffiCall 'period) c_period

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual). QuantLib: qlPeriodFromFrequency
fromFrequency :: F.Frequency -> IO Period
fromFrequency = $(ffiCall 'fromFrequency) c_fromFrequency

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M). QuantLib: qlFrequencyFromPeriod
toFrequency :: Period -> Either String F.Frequency
toFrequency = $(ffiCallPureX 'toFrequency) c_toFrequency

parse :: String -> IO Period
parse = $(ffiCall 'parse) c_parse

foreign import ccall safe "ql.h qlPeriodParserParse"
  c_parse :: CString -> Ptr CString -> IO (Ptr CPeriod)

units :: Period -> Unit
units = $(ffiCallPure 'units) c_units

foreign import ccall safe "ql.h qlPeriodUnits"
  c_units :: Ptr CPeriod -> IO CInt

periodLength :: Period -> Int
periodLength = $(ffiCallPure 'periodLength) c_periodLength

foreign import ccall safe "ql.h qlPeriodLength"
  c_periodLength :: Ptr CPeriod -> IO CInt

addPeriods :: Period -> Period -> IO Period
addPeriods = $(ffiCall 'addPeriods) c_addPeriods

foreign import ccall safe "ql.h qlPeriodAdd"
  c_addPeriods :: Ptr CPeriod -> Ptr CPeriod -> Ptr CString -> IO (Ptr CPeriod)

subtractPeriods :: Period -> Period -> IO Period
subtractPeriods = $(ffiCall 'subtractPeriods) c_subtractPeriods

foreign import ccall safe "ql.h qlPeriodSubtract"
  c_subtractPeriods :: Ptr CPeriod -> Ptr CPeriod -> Ptr CString -> IO (Ptr CPeriod)

dividePeriod :: Period -> Int -> IO Period
dividePeriod = $(ffiCall 'dividePeriod) c_dividePeriod

foreign import ccall safe "ql.h qlPeriodDivide"
  c_dividePeriod :: Ptr CPeriod -> CInt -> Ptr CString -> IO (Ptr CPeriod)

periodsEQ :: Period -> Period -> Either String Bool
periodsEQ = $(ffiCallPureX 'periodsEQ) c_periodsEQ

foreign import ccall safe "ql.h qlPeriodsEQ"
  c_periodsEQ :: Ptr CPeriod -> Ptr CPeriod -> Ptr CString -> IO CInt

periodsLT :: Period -> Period -> Either String Bool
periodsLT = $(ffiCallPureX 'periodsLT) c_periodsLT

foreign import ccall safe "ql.h qlPeriodsLT"
  c_periodsLT :: Ptr CPeriod -> Ptr CPeriod -> Ptr CString -> IO CInt

normalize :: Period -> IO Period
normalize = $(ffiCall 'normalize) c_normalize

foreign import ccall safe "ql.h qlPeriodNormalize"
  c_normalize :: Ptr CPeriod -> Ptr CString -> IO (Ptr CPeriod)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
