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
import QuantLib.Internal.Syntax
import QuantLib.Internal.Utils
import qualified QuantLib.Time.Frequency as F(Frequency)
import QuantLib.Time.Unit(Unit)

foreign import ccall safe "ql.h qlPeriodFromFrequency1"
  c_fromFrequency :: CInt -> Ptr CInt -> Ptr CString -> IO CInt

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual)
fromFrequency :: F.Frequency -> Either String (Int, Unit)
fromFrequency f = purifyExceptions $ do
  e <- toQlEnum (show ''F.Frequency) f
  (p1, p2) <- getIntPair $ c_fromFrequency e
  ee <- fromQlEnum (show ''Unit) p2
  return (p1, ee)

foreign import ccall safe "ql.h qlPeriodToFrequency1"
  c_toFrequency :: CInt -> CInt -> Ptr CString -> IO CInt

-- |returns a Frequency from a given Period (e.g. SemiAnnual from 6M)
toFrequency :: (Int, Unit) -> Either String F.Frequency
toFrequency = $(ffiCallPureX 'toFrequency) c_toFrequency

parse :: String -> Either String (Int, Unit)
parse s = purifyExceptions $ do
  (p1, p2) <- withCString s (getIntPair . c_parse)
  ee <- fromQlEnum (show ''Unit) p2
  return (p1, ee)

foreign import ccall safe "ql.h qlPeriodParserParse1"
  c_parse :: CString -> Ptr CInt -> Ptr CString -> IO CInt

addPeriods :: (Int, Unit) -> (Int, Unit) -> Either String (Int, Unit)
addPeriods (n1, u1) (n2, u2) = purifyExceptions $ do
  e1 <- toQlEnum (show ''Unit) u1
  e2 <- toQlEnum (show ''Unit) u2
  (n, u) <- getIntPair $ c_addPeriods (fromIntegral n1) e1 (fromIntegral n2) e2
  e <- fromQlEnum (show ''Unit) u
  return (n, e)

foreign import ccall safe "ql.h qlPeriodAdd1"
  c_addPeriods :: CInt -> CInt -> CInt -> CInt -> Ptr CInt -> Ptr CString -> IO CInt

dividePeriod :: (Int, Unit) -> Int -> Either String (Int, Unit)
dividePeriod (n1, u1) n = purifyExceptions $ do
  e1 <- toQlEnum (show ''Unit) u1
  (p1, p2) <- getIntPair $ c_dividePeriod (fromIntegral n1) e1 (fromIntegral n)
  e <- fromQlEnum (show ''Unit) p2
  return (p1, e)

foreign import ccall safe "ql.h qlPeriodDivide1"
  c_dividePeriod :: CInt -> CInt -> CInt -> Ptr CInt -> Ptr CString -> IO CInt

periodsLT :: (Int, Unit) -> (Int, Unit) -> Either String Bool
periodsLT = $(ffiCallPureX 'periodsLT) c_periodsLT

foreign import ccall safe "ql.h qlPeriodsLT1"
  c_periodsLT :: CInt -> CInt -> CInt -> CInt -> Ptr CString -> IO CInt

normalize :: (Int, Unit) -> Either String (Int, Unit)
normalize (n1, u1) = purifyExceptions $ do
  e1 <- toQlEnum (show ''Unit) u1
  (p1, p2) <- getIntPair $ c_normalize (fromIntegral n1) e1
  e <- fromQlEnum (show ''Unit) p2
  return (p1, e)

foreign import ccall safe "ql.h qlPeriodNormalize1"
  c_normalize :: CInt -> CInt -> Ptr CInt -> Ptr CString -> IO CInt

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
