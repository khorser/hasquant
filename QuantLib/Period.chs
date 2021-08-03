module QuantLib.Period
  (
    fromFrequency
{-
  , toFrequency
  , parse
  , addPeriods
  , dividePeriod
  , periodsLT
  , normalize
-}
  , TimeUnit(..)
  , Frequency(..)
  , marshalPeriod
  , unmarshalPeriod
  )
where

import Foreign.C.Types(CInt)
import Foreign.Ptr(Ptr)
import Foreign.Storable(peek)
import Foreign.Marshal.Alloc(alloca)

import Control.Monad(liftM)

import QuantLib.Utility

#include "ql.h"

#include "qlEnum.h"

{#enum TimeUnit {} deriving(Show, Eq) #}

{#enum Frequency {} deriving(Show, Eq) #}

unitOut :: Ptr CInt -> IO TimeUnit
unitOut x = peek x >>= return . toEnum . fromIntegral

-- |returns a Period from a given Frequency (e.g. 6M from SemiAnnual)
{#fun qlPeriodFromFrequency1 as fromFrequency {`Frequency', alloca- `TimeUnit' unitOut*, preErrorCheck- `String' errorCheck*-} -> `Int' #}

{-
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
-}

marshalPeriod :: (Int, TimeUnit) -> (CInt, CInt)
marshalPeriod (x, u) = (fromIntegral x, fromIntegral $ fromEnum u)

unmarshalPeriod :: (CInt, CInt) -> (Int, TimeUnit)
unmarshalPeriod (x, u) = (fromIntegral x, toEnum $ fromIntegral u)

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
