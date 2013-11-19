{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Time.Period
  (
    fromFrequency
  , toFrequency
  , parse
  , addPeriods
  , dividePeriod
  , periodsLT
  , normalize
  )
where

import QuantLib.Internal.Enum
import QuantLib.Internal.Period
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import qualified QuantLib.Time.Frequency as F(Frequency)
import QuantLib.Time.Unit(Unit)

foreign import ccall safe "ql.h qlPeriodFromFrequency1"
  c_fromFrequency :: CInt -> Ptr CInt -> Ptr CString -> IO CInt

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual)
fromFrequency :: F.Frequency -> Either String (Int, Unit)
fromFrequency f = unmarshalPeriod (c_fromFrequency $ toQlEnum (show ''F.Frequency) f)

foreign import ccall safe "ql.h qlPeriodToFrequency1"
  c_toFrequency :: CInt -> CInt -> Ptr CString -> IO CInt

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M)
toFrequency :: (Int, Unit) -> Either String F.Frequency
toFrequency = $(ffiCallPureX 'toFrequency) c_toFrequency

parse :: String -> Either String (Int, Unit)
parse s = purifyExceptions (withCString s (getIntPair . c_parse))
  >>= \(n, u) -> return (n, fromQlEnum (show ''Unit) u)

foreign import ccall safe "ql.h qlPeriodParserParse1"
  c_parse :: CString -> Ptr CInt -> Ptr CString -> IO CInt

addPeriods :: (Int, Unit) -> (Int, Unit) -> Either String (Int, Unit)
addPeriods p1 p2 = unmarshalPeriod (marshalPeriod (marshalPeriod c_addPeriods p1) p2)

foreign import ccall safe "ql.h qlPeriodAdd1"
  c_addPeriods :: CInt -> CInt -> CInt -> CInt -> Ptr CInt -> Ptr CString -> IO CInt

dividePeriod :: (Int, Unit) -> Int -> Either String (Int, Unit)
dividePeriod p n = unmarshalPeriod $ marshalPeriod c_dividePeriod p (fromIntegral n)

foreign import ccall safe "ql.h qlPeriodDivide1"
  c_dividePeriod :: CInt -> CInt -> CInt -> Ptr CInt -> Ptr CString -> IO CInt

periodsLT :: (Int, Unit) -> (Int, Unit) -> Either String Bool
periodsLT = $(ffiCallPureX 'periodsLT) c_periodsLT

foreign import ccall safe "ql.h qlPeriodsLT1"
  c_periodsLT :: CInt -> CInt -> CInt -> CInt -> Ptr CString -> IO CInt

normalize :: (Int, Unit) -> Either String (Int, Unit)
normalize p = unmarshalPeriod (marshalPeriod c_normalize p)

foreign import ccall safe "ql.h qlPeriodNormalize1"
  c_normalize :: CInt -> CInt -> Ptr CInt -> Ptr CString -> IO CInt

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
