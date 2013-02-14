{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Index.Swap
  (
    chfLiborSwapIsdaFix
  , eurLiborSwapIfrFix
  , eurLiborSwapIsdaFixA
  , eurLiborSwapIsdaFixB
  , gbpLiborSwapIsdaFix
  , jpyLiborSwapIsdaFixAm
  , jpyLiborSwapIsdaFixPm
  , usdLiborSwapIsdaFixAm
  , usdLiborSwapIsdaFixPm
  , euriborSwapIfrFix
  , euriborSwapIsdaFixA
  , euriborSwapIsdaFixB
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

chfLiborSwapIsdaFix :: Period -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
chfLiborSwapIsdaFix = createLiborSwapIndex "ChfLiborSwapIsdaFix"

eurLiborSwapIfrFix :: Period -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
eurLiborSwapIfrFix = createLiborSwapIndex "EurLiborSwapIfrFix"

eurLiborSwapIsdaFixA :: Period -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
eurLiborSwapIsdaFixA = createLiborSwapIndex "EurLiborSwapIsdaFixA"

eurLiborSwapIsdaFixB :: Period -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
eurLiborSwapIsdaFixB = createLiborSwapIndex "EurLiborSwapIsdaFixB"

gbpLiborSwapIsdaFix :: Period -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
gbpLiborSwapIsdaFix = createLiborSwapIndex "GbpLiborSwapIsdaFix"

jpyLiborSwapIsdaFixAm :: Period -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
jpyLiborSwapIsdaFixAm = createLiborSwapIndex "JpyLiborSwapIsdaFixAm"

jpyLiborSwapIsdaFixPm :: Period -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
jpyLiborSwapIsdaFixPm = createLiborSwapIndex "JpyLiborSwapIsdaFixPm"

usdLiborSwapIsdaFixAm :: Period -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
usdLiborSwapIsdaFixAm = createLiborSwapIndex "UsdLiborSwapIsdaFixAm"

usdLiborSwapIsdaFixPm :: Period -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
usdLiborSwapIsdaFixPm = createLiborSwapIndex "UsdLiborSwapIsdaFixPm"


euriborSwapIfrFix :: Period -> Maybe YieldTermStructure -> Maybe YieldTermStructure -> IO SwapIndex
euriborSwapIfrFix = createLiborSwapIndex "EuriborSwapIfrFix"

euriborSwapIsdaFixA :: Period -> Maybe YieldTermStructure -> Maybe YieldTermStructure -> IO SwapIndex
euriborSwapIsdaFixA = createLiborSwapIndex "EuriborSwapIsdaFixA"

euriborSwapIsdaFixB :: Period -> Maybe YieldTermStructure -> Maybe YieldTermStructure -> IO SwapIndex
euriborSwapIsdaFixB = createLiborSwapIndex "EuriborSwapIsdaFixB"

createLiborSwapIndex :: String
  -> Period -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
createLiborSwapIndex = $(ffiConstruct 'createLiborSwapIndex) c_liborSwapIndex

foreign import ccall safe "ql.h qlCreateLiborSwapIndex"
  c_liborSwapIndex :: CString -> Ptr CPeriod -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CSwapIndex)
