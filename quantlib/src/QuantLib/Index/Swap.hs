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
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Unit(Unit)

chfLiborSwapIsdaFix :: (Int, Unit) -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
chfLiborSwapIsdaFix = createLiborSwapIndex "ChfLiborSwapIsdaFix"

eurLiborSwapIfrFix :: (Int, Unit) -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
eurLiborSwapIfrFix = createLiborSwapIndex "EurLiborSwapIfrFix"

eurLiborSwapIsdaFixA :: (Int, Unit) -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
eurLiborSwapIsdaFixA = createLiborSwapIndex "EurLiborSwapIsdaFixA"

eurLiborSwapIsdaFixB :: (Int, Unit) -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
eurLiborSwapIsdaFixB = createLiborSwapIndex "EurLiborSwapIsdaFixB"

gbpLiborSwapIsdaFix :: (Int, Unit) -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
gbpLiborSwapIsdaFix = createLiborSwapIndex "GbpLiborSwapIsdaFix"

jpyLiborSwapIsdaFixAm :: (Int, Unit) -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
jpyLiborSwapIsdaFixAm = createLiborSwapIndex "JpyLiborSwapIsdaFixAm"

jpyLiborSwapIsdaFixPm :: (Int, Unit) -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
jpyLiborSwapIsdaFixPm = createLiborSwapIndex "JpyLiborSwapIsdaFixPm"

usdLiborSwapIsdaFixAm :: (Int, Unit) -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
usdLiborSwapIsdaFixAm = createLiborSwapIndex "UsdLiborSwapIsdaFixAm"

usdLiborSwapIsdaFixPm :: (Int, Unit) -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
usdLiborSwapIsdaFixPm = createLiborSwapIndex "UsdLiborSwapIsdaFixPm"

euriborSwapIfrFix :: (Int, Unit) -> Maybe YieldTermStructure -> Maybe YieldTermStructure -> IO SwapIndex
euriborSwapIfrFix = createLiborSwapIndex "EuriborSwapIfrFix"

euriborSwapIsdaFixA :: (Int, Unit) -> Maybe YieldTermStructure -> Maybe YieldTermStructure -> IO SwapIndex
euriborSwapIsdaFixA = createLiborSwapIndex "EuriborSwapIsdaFixA"

euriborSwapIsdaFixB :: (Int, Unit) -> Maybe YieldTermStructure -> Maybe YieldTermStructure -> IO SwapIndex
euriborSwapIsdaFixB = createLiborSwapIndex "EuriborSwapIsdaFixB"

createLiborSwapIndex :: String
  -> (Int, Unit) -- ^tenor
  -> Maybe YieldTermStructure -- ^forwarding
  -> Maybe YieldTermStructure -- ^discounting
  -> IO SwapIndex
createLiborSwapIndex = $(ffiCall 'createLiborSwapIndex) c_createLiborSwapIndex

foreign import ccall safe "ql.h qlCreateLiborSwapIndex"
  c_createLiborSwapIndex :: CString -> CInt -> CInt -> Ptr CYieldTermStructure -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CSwapIndex)

overnightIndexedSwapIndex :: String -- ^familyName
  -> (Int, Unit) -- ^tenor
  -> Word -- ^settlementDays
  -> Currency -- ^currency
  -> OvernightIndex -- ^overnightIndex
  -> IO OvernightIndexedSwapIndex
overnightIndexedSwapIndex = $(ffiCall 'overnightIndexedSwapIndex) c_overnightIndexedSwapIndex

foreign import ccall safe "ql.h qlOvernightIndexedSwapIndex"
  c_overnightIndexedSwapIndex :: CString -> CInt -> CInt -> CUInt -> Ptr CCurrency -> Ptr COvernightIndex -> Ptr CString -> IO (Ptr COvernightIndexedSwapIndex)

swapIndex :: String -- ^familyName
  -> (Int, Unit) -- ^tenor
  -> Word -- ^settlementDays
  -> Currency -- ^currency
  -> Calendar -- ^calendar
  -> (Int, Unit) -- ^fixedLegTenor
  -> BusinessDayConvention -- ^fixedLegConvention
  -> DayCounter -- ^fixedLegDayCounter
  -> IborIndex -- ^iborIndex
  -> IO SwapIndex
swapIndex = $(ffiCall 'swapIndex) c_swapIndex

foreign import ccall safe "ql.h qlSwapIndex"
  c_swapIndex :: CString -> CInt -> CInt -> CUInt -> Ptr CCurrency -> Ptr CCalendar -> CInt -> CInt -> CInt -> Ptr CDayCounter -> Ptr CIborIndex -> Ptr CString -> IO (Ptr CSwapIndex)

swapIndex' :: String -- ^familyName
  -> (Int, Unit) -- ^tenor
  -> Word -- ^settlementDays
  -> Currency -- ^currency
  -> Calendar -- ^calendar
  -> (Int, Unit) -- ^fixedLegTenor
  -> BusinessDayConvention -- ^fixedLegConvention
  -> DayCounter -- ^fixedLegDayCounter
  -> IborIndex -- ^iborIndex
  -> YieldTermStructure -- ^discountingTermStructure
  -> IO SwapIndex
swapIndex' = $(ffiCall 'swapIndex') c_swapIndex'

foreign import ccall safe "ql.h qlSwapIndex1"
  c_swapIndex' :: CString -> CInt -> CInt -> CUInt -> Ptr CCurrency -> Ptr CCalendar -> CInt -> CInt -> CInt -> Ptr CDayCounter -> Ptr CIborIndex -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CSwapIndex)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
