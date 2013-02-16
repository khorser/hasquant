{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Time.Period
  (
    period
  , fromFrequency

  , toFrequency
  , days
  , length
  , months
  , normalize
  , units
  , weeks
  , years
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
period = $(ffiConstruct 'period) c_period

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual). QuantLib: qlPeriodFromFrequency
fromFrequency :: F.Frequency -> IO Period
fromFrequency = $(ffiConstruct 'fromFrequency) c_periodFromFreq

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M). QuantLib: qlFrequencyFromPeriod
toFrequency :: Period -> IO F.Frequency
toFrequency = $(ffiCallX 'toFrequency) c_periodToFreq

days :: Period -> IO Double
days = $(ffiCallX 'days) c_days

foreign import ccall safe "ql.h qlPeriodDays"
  c_days :: Ptr CPeriod -> Ptr CString -> IO CDouble

length :: Period -> IO Int
length = $(ffiCallX 'length) c_length

foreign import ccall safe "ql.h qlPeriodLength"
  c_length :: Ptr CPeriod -> Ptr CString -> IO CInt

months :: Period -> IO Double
months = $(ffiCallX 'months) c_months

foreign import ccall safe "ql.h qlPeriodMonths"
  c_months :: Ptr CPeriod -> Ptr CString -> IO CDouble

normalize :: Period -> IO Period
normalize = $(ffiConstruct 'normalize) c_normalize

foreign import ccall safe "ql.h qlPeriodNormalize"
  c_normalize :: Ptr CPeriod -> Ptr CString -> IO (Ptr CPeriod)

units :: Period -> IO Unit
units = $(ffiCallX 'units) c_units

foreign import ccall safe "ql.h qlPeriodUnits"
  c_units :: Ptr CPeriod -> Ptr CString -> IO CInt

weeks :: Period -> IO Double
weeks = $(ffiCallX 'weeks) c_weeks

foreign import ccall safe "ql.h qlPeriodWeeks"
  c_weeks :: Ptr CPeriod -> Ptr CString -> IO CDouble

years :: Period -> IO Double
years = $(ffiCallX 'years) c_years

foreign import ccall safe "ql.h qlPeriodYears"
  c_years :: Ptr CPeriod -> Ptr CString -> IO CDouble

parse :: String -> IO Period
parse = $(ffiConstruct 'parse) c_parse

foreign import ccall safe "ql.h qlPeriodParserParse"
  c_parse :: CString -> Ptr CString -> IO (Ptr CPeriod)
