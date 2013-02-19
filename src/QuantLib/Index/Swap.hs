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
  , overnightIndexedSwapIndex
  , swapIndex
  , swapIndex'
  , overnightIndexedSwap
  , vanillaSwap
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention

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
createLiborSwapIndex = $(ffiCall 'createLiborSwapIndex) c_liborSwapIndex

foreign import ccall safe "ql.h qlCreateLiborSwapIndex"
  c_liborSwapIndex :: CString -> Ptr CPeriod -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CSwapIndex)

overnightIndexedSwapIndex :: String -- ^familyName
  -> Period -- ^tenor
  -> Word -- ^settlementDays
  -> Currency -- ^currency
  -> OvernightIndex -- ^overnightIndex
  -> IO OvernightIndexedSwapIndex
overnightIndexedSwapIndex = $(ffiCall 'overnightIndexedSwapIndex) c_overnightIndexedSwapIndex

foreign import ccall safe "ql.h qlOvernightIndexedSwapIndex"
  c_overnightIndexedSwapIndex :: CString -> Ptr CPeriod -> CUInt -> Ptr CCurrency -> Ptr COvernightIndex -> Ptr CString -> IO (Ptr COvernightIndexedSwapIndex)

swapIndex :: String -- ^familyName
  -> Period -- ^tenor
  -> Word -- ^settlementDays
  -> Currency -- ^currency
  -> Calendar -- ^calendar
  -> Period -- ^fixedLegTenor
  -> BusinessDayConvention -- ^fixedLegConvention
  -> DayCounter -- ^fixedLegDayCounter
  -> IborIndex -- ^iborIndex
  -> IO SwapIndex
swapIndex = $(ffiCall 'swapIndex) c_swapIndex

foreign import ccall safe "ql.h qlSwapIndex"
  c_swapIndex :: CString -> Ptr CPeriod -> CUInt -> Ptr CCurrency -> Ptr CCalendar -> Ptr CPeriod -> CInt -> Ptr CDayCounter -> Ptr CIborIndex -> Ptr CString -> IO (Ptr CSwapIndex)

swapIndex' :: String -- ^familyName
  -> Period -- ^tenor
  -> Word -- ^settlementDays
  -> Currency -- ^currency
  -> Calendar -- ^calendar
  -> Period -- ^fixedLegTenor
  -> BusinessDayConvention -- ^fixedLegConvention
  -> DayCounter -- ^fixedLegDayCounter
  -> IborIndex -- ^iborIndex
  -> YieldTermStructure -- ^discountingTermStructure
  -> IO SwapIndex
swapIndex' = $(ffiCall 'swapIndex') c_swapIndex'

foreign import ccall safe "ql.h qlSwapIndex1"
  c_swapIndex' :: CString -> Ptr CPeriod -> CUInt -> Ptr CCurrency -> Ptr CCalendar -> Ptr CPeriod -> CInt -> Ptr CDayCounter -> Ptr CIborIndex -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CSwapIndex)

-- |/Warning/ Relinking the term structure underlying the index will not have effect on the returned swap.
overnightIndexedSwap :: OvernightIndexedSwapIndex
  -> Day -- ^fixingDate
  -> IO OvernightIndexedSwap
overnightIndexedSwap = $(ffiCall 'overnightIndexedSwap) c_underlyingOISwap

foreign import ccall safe "ql.h qlOvernightIndexedSwapIndexUnderlyingSwap"
  c_underlyingOISwap :: Ptr COvernightIndexedSwapIndex -> CDate -> Ptr CString -> IO (Ptr COvernightIndexedSwap)

-- |/Warning/ Relinking the term structure underlying the index will not have effect on the returned swap.
vanillaSwap :: SwapIndex
  -> Day -- ^fixingDate
  -> IO VanillaSwap
vanillaSwap = $(ffiCall 'vanillaSwap) c_underlyingVanillaSwap

foreign import ccall safe "ql.h qlSwapIndexUnderlyingSwap"
  c_underlyingVanillaSwap :: Ptr CSwapIndex -> CDate -> Ptr CString -> IO (Ptr CVanillaSwap)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
