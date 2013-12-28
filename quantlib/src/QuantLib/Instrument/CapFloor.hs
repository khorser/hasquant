{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Instrument.CapFloor
  (
    cap
  , collar
  , floor
  , atmRate
  , impliedVolatility
  , optionlet
  )
where

import Prelude hiding(floor)

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Types

cap :: Leg -- ^floatingLeg
  -> [Double] -- ^exerciseRates
  -> QLE s (CapFloor s)
cap = $(ffiCall 'cap) c_cap

foreign import ccall safe "ql.h qlCap"
  c_cap :: Ptr CLeg -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CCapFloor)

collar :: Leg -- ^floatingLeg
  -> [Double] -- ^capRates
  -> [Double] -- ^floorRates
  -> QLE s (CapFloor s)
collar = $(ffiCall 'collar) c_collar

foreign import ccall safe "ql.h qlCollar"
  c_collar :: Ptr CLeg -> CUInt -> Ptr CDouble -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CCapFloor)

floor :: Leg -- ^floatingLeg
  -> [Double] -- ^exerciseRates
  -> QLE s (CapFloor s)
floor = $(ffiCall 'floor) c_floor

foreign import ccall safe "ql.h qlFloor"
  c_floor :: Ptr CLeg -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CCapFloor)

atmRate :: CapFloor
  -> YieldTermStructure -- ^discountCurve
  -> QLE s Double
atmRate = $(ffiCallX 'atmRate) c_atmRate

foreign import ccall safe "ql.h qlCapFloorAtmRate"
  c_atmRate :: Ptr CCapFloor -> Ptr CYieldTermStructure -> Ptr CString -> IO CDouble

-- |implied term volatility
impliedVolatility :: CapFloor
  -> Double -- ^price
  -> YieldTermStructure -- ^disc
  -> Double -- ^guess
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> Double -- ^minVol
  -> Double -- ^maxVol
  -> QLE s Double
impliedVolatility = $(ffiCallX 'impliedVolatility) c_impliedVolatility

foreign import ccall safe "ql.h qlCapFloorImpliedVolatility"
  c_impliedVolatility :: Ptr CCapFloor -> CDouble -> Ptr CYieldTermStructure -> CDouble -> CDouble -> CUInt -> CDouble -> CDouble -> Ptr CString -> IO CDouble

-- |Returns the n-th optionlet as a new CapFloor with only one cash flow.
optionlet :: CapFloor
  -> Word -- ^n
  -> QLE s (CapFloor s)
optionlet = $(ffiCall 'optionlet) c_optionlet

foreign import ccall safe "ql.h qlCapFloorOptionlet"
  c_optionlet :: Ptr CCapFloor -> CUInt -> Ptr CString -> IO (Ptr CCapFloor)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
