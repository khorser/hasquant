{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Time.Period
  (
    period
  , fromFrequency
  , fromFrequency'

  , toFrequency
  , toFrequency'
  , parse'

  , units
  , periodLength
  , addPeriods'
  , dividePeriod'

  , periodsLT'
  , normalize'
  )
where

import QuantLib.Internal.Enum
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

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual)
fromFrequency :: F.Frequency -> IO Period
fromFrequency = $(ffiCall 'fromFrequency) c_fromFrequency

unmarshalPeriod :: (Ptr CInt -> Ptr CString -> IO CInt)
  -> Either String (Int, Unit)
unmarshalPeriod f = purifyExceptions (getIntPair f)
  >>= \(p1, p2) -> return (p1, fromQlEnum (show ''Unit) p2)

foreign import ccall safe "ql.h qlPeriodFromFrequency1"
  c_fromFrequency' :: CInt -> Ptr CInt -> Ptr CString -> IO CInt

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual)
fromFrequency' :: F.Frequency -> Either String (Int, Unit)
fromFrequency' f = unmarshalPeriod (c_fromFrequency' $ toQlEnum (show ''F.Frequency) f)

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M)
toFrequency :: Period -> Either String F.Frequency
toFrequency = $(ffiCallPureX 'toFrequency) c_toFrequency

foreign import ccall safe "ql.h qlPeriodToFrequency1"
  c_toFrequency' :: CInt -> CInt -> Ptr CString -> IO CInt

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M)
toFrequency' :: (Int, Unit) -> Either String F.Frequency
toFrequency' = $(ffiCallPureX 'toFrequency') c_toFrequency'

parse' :: String -> Either String (Int, Unit)
parse' s = purifyExceptions (withCString s (getIntPair . c_parse'))
  >>= \(n, u) -> return (n, fromQlEnum (show ''Unit) u)

foreign import ccall safe "ql.h qlPeriodParserParse1"
  c_parse' :: CString -> Ptr CInt -> Ptr CString -> IO CInt

units :: Period -> Unit
units = $(ffiCallPure 'units) c_units

foreign import ccall safe "ql.h qlPeriodUnits"
  c_units :: Ptr CPeriod -> IO CInt

periodLength :: Period -> Int
periodLength = $(ffiCallPure 'periodLength) c_periodLength

foreign import ccall safe "ql.h qlPeriodLength"
  c_periodLength :: Ptr CPeriod -> IO CInt

marshalPeriod :: (CInt -> CInt -> a) -> (Int, Unit) -> a
marshalPeriod f (n, u) = f (fromIntegral n) (toQlEnum (show ''Unit) u)

addPeriods' :: (Int, Unit) -> (Int, Unit) -> Either String (Int, Unit)
addPeriods' p1 p2 = unmarshalPeriod (marshalPeriod (marshalPeriod c_addPeriods' p1) p2)

foreign import ccall safe "ql.h qlPeriodAdd1"
  c_addPeriods' :: CInt -> CInt -> CInt -> CInt -> Ptr CInt -> Ptr CString -> IO CInt

dividePeriod' :: (Int, Unit) -> Int -> Either String (Int, Unit)
dividePeriod' p n = unmarshalPeriod $ marshalPeriod c_dividePeriod' p (fromIntegral n)

foreign import ccall safe "ql.h qlPeriodDivide1"
  c_dividePeriod' :: CInt -> CInt -> CInt -> Ptr CInt -> Ptr CString -> IO CInt

periodsLT' :: (Int, Unit) -> (Int, Unit) -> Either String Bool
periodsLT' = $(ffiCallPureX 'periodsLT') c_periodsLT'

foreign import ccall safe "ql.h qlPeriodsLT1"
  c_periodsLT' :: CInt -> CInt -> CInt -> CInt -> Ptr CString -> IO CInt

normalize' :: (Int, Unit) -> Either String (Int, Unit)
normalize' p = unmarshalPeriod (marshalPeriod c_normalize' p)

foreign import ccall safe "ql.h qlPeriodNormalize1"
  c_normalize' :: CInt -> CInt -> Ptr CInt -> Ptr CString -> IO CInt

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
