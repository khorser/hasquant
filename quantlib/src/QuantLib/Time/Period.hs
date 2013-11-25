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

import QuantLib.Error(QLError)
import QuantLib.Internal.Enum
import QuantLib.Internal.Syntax
import QuantLib.Internal.Utils
import qualified QuantLib.Time.Frequency as F(Frequency)
import QuantLib.Time.Unit(Unit)

unmarshalPeriod :: (Ptr CInt -> Ptr CString -> IO CInt) -> IO (Int, Unit)
unmarshalPeriod f = do
  (p1, p2) <- getIntPair f
  e <- fromQlEnum (show ''Unit) p2
  return (p1, e)

foreign import ccall safe "ql.h qlPeriodFromFrequency1"
  c_fromFrequency :: CInt -> Ptr CInt -> Ptr CString -> IO CInt

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual)
fromFrequency :: F.Frequency -> Either QLError (Int, Unit)
fromFrequency f = purifyExceptions $ do
  e <- toQlEnum (show ''F.Frequency) f
  unmarshalPeriod $ c_fromFrequency e

foreign import ccall safe "ql.h qlPeriodToFrequency1"
  c_toFrequency :: CInt -> CInt -> Ptr CString -> IO CInt

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M)
toFrequency :: (Int, Unit) -> Either QLError F.Frequency
toFrequency = $(ffiCallPureX 'toFrequency) c_toFrequency

parse :: String -> Either QLError (Int, Unit)
parse s = purifyExceptions $ withCString s (unmarshalPeriod . c_parse)

foreign import ccall safe "ql.h qlPeriodParserParse1"
  c_parse :: CString -> Ptr CInt -> Ptr CString -> IO CInt

addPeriods :: (Int, Unit) -> (Int, Unit) -> Either QLError (Int, Unit)
addPeriods (n1, u1) (n2, u2) = purifyExceptions $ do
  e1 <- toQlEnum (show ''Unit) u1
  e2 <- toQlEnum (show ''Unit) u2
  unmarshalPeriod $ c_addPeriods (fromIntegral n1) e1 (fromIntegral n2) e2

foreign import ccall safe "ql.h qlPeriodAdd1"
  c_addPeriods :: CInt -> CInt -> CInt -> CInt -> Ptr CInt -> Ptr CString -> IO CInt

dividePeriod :: (Int, Unit) -> Int -> Either QLError (Int, Unit)
dividePeriod (n1, u1) n = purifyExceptions $ do
  e1 <- toQlEnum (show ''Unit) u1
  unmarshalPeriod $ c_dividePeriod (fromIntegral n1) e1 (fromIntegral n)

foreign import ccall safe "ql.h qlPeriodDivide1"
  c_dividePeriod :: CInt -> CInt -> CInt -> Ptr CInt -> Ptr CString -> IO CInt

periodsLT :: (Int, Unit) -> (Int, Unit) -> Either QLError Bool
periodsLT = $(ffiCallPureX 'periodsLT) c_periodsLT

foreign import ccall safe "ql.h qlPeriodsLT1"
  c_periodsLT :: CInt -> CInt -> CInt -> CInt -> Ptr CString -> IO CInt

normalize :: (Int, Unit) -> Either QLError (Int, Unit)
normalize (n1, u1) = purifyExceptions $ do
  e1 <- toQlEnum (show ''Unit) u1
  unmarshalPeriod $ c_normalize (fromIntegral n1) e1

foreign import ccall safe "ql.h qlPeriodNormalize1"
  c_normalize :: CInt -> CInt -> Ptr CInt -> Ptr CString -> IO CInt

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
