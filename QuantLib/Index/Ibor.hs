{-# LANGUAGE ForeignFunctionInterface,MultiParamTypeClasses #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
module QuantLib.Index.Ibor
  (
  -- makers
    iborIndex
  , overnightIndex
  , libor
  , dailyTenorLibor
  , euribor
  , euribor365
  , audLibor
  , cadLibor
  , cadLiborON
  , cdor
  , chfLibor
  , dailyTenorChfLibor
  , dkkLibor
  , eonia
  , eurLibor
  , dailyTenorEURLibor
  , gbpLibor
  , dailyTenorGBPLibor
  , gbpLiborON
  , jibar
  , jpyLibor
  , dailyTenorJPYLibor
  , nzdLibor
  , sekLibor
  , sonia
  , tibor
  , trLibor
  , usdLibor
  , dailyTenorUsdLibor
  , usdLiborON
  , zibor
  )
where

import QuantLib.Internal
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)

foreign import ccall safe "ql.h qlIborIndex"
  c_iborIndex :: CString -> Ptr CPeriod -> CUInt -> Ptr CCurrency
    -> Ptr CCalendar -> CInt -> CInt -> Ptr CDayCounter
    -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CIborIndex)
foreign import ccall safe "ql.h &qlFreeIborIndex"
  p_freeIborIndex :: FunPtr (Ptr CIborIndex -> IO ())

instance Finalizable CIborIndex where
  finalize = p_freeIborIndex

-- XXX any point in passing Nothing as the term structure?
-- | (qlIborIndex)
iborIndex :: String -> Period -> Word -> Currency -> Calendar
  -> BusinessDayConvention -> Bool -> DayCounter -> YieldTermStructure
  -> IO IborIndex
iborIndex famname tenor settlDays ccy cal conv eom dayCounter fwd =
  withCString famname
  (\n ->
    withObject5 tenor ccy cal dayCounter fwd
    (\t cur c dc ts ->
      (construct $ c_iborIndex n
                               t
                               (fromIntegral settlDays)
                               cur
                               c
                               (toQlEnum conv)
                               (fromBool eom)
                               dc
                               ts)))
foreign import ccall safe "ql.h qlLibor"
  c_libor :: CString -> Ptr CPeriod -> CUInt -> Ptr CCurrency
    -> Ptr CCalendar -> Ptr CDayCounter -> Ptr CYieldTermStructure
    -> Ptr CString -> IO (Ptr CIborIndex)

-- |(qlLibor)
libor :: String -> Period -> Word -> Currency -> Calendar -> DayCounter
  -> YieldTermStructure -> IO IborIndex
libor famname tenor settlDays ccy cal dayCount fwd =
  withCString famname
  (\n -> withObject5 tenor ccy cal dayCount fwd
          (\t cur c dc ts-> 
            (construct $ c_libor n
                                 t
                                 (fromIntegral settlDays)
                                 cur
                                 c
                                 dc
                                 ts)))

foreign import ccall safe "ql.h qlDailyTenorLibor"
  c_dailyTenorLibor :: CString -> CUInt -> Ptr CCurrency -> Ptr CCalendar
    -> Ptr CDayCounter -> Ptr CYieldTermStructure -> Ptr CString
    -> IO (Ptr CIborIndex)

dailyTenorLibor :: String -> Word -> Currency -> Calendar -> DayCounter
  -> YieldTermStructure -> IO IborIndex
dailyTenorLibor famname settlDays ccy cal dayCount fwd =
  withCString famname
  (\n -> withObject4 ccy cal dayCount fwd
          (\cur c dc ts ->
            (construct $ c_dailyTenorLibor n
                                           (fromIntegral settlDays)
                                           cur
                                           c
                                           dc
                                           ts)))

foreign import ccall safe "ql.h qlOvernightIndex"
  c_overnightIndex :: CString -> CUInt -> Ptr CCurrency -> Ptr CCalendar
    -> Ptr CDayCounter -> Ptr CYieldTermStructure -> Ptr CString
    -> IO (Ptr CIborIndex)

-- |(qlOvernightIndex)
overnightIndex :: String -> Word -> Currency -> Calendar -> DayCounter
  -> YieldTermStructure -> IO IborIndex
overnightIndex famname settlDays ccy cal dayCount fwd =
  withCString famname
  (\n -> withObject4 ccy cal dayCount fwd
          (\cur c dc ts -> (construct $ c_overnightIndex n
                                                         (fromIntegral settlDays)
                                                         cur
                                                         c
                                                         dc
                                                         ts)))


foreign import ccall safe "ql.h qlCreateIbor"
  c_createIbor :: CString -> Ptr CPeriod -> Ptr CYieldTermStructure
    -> Ptr CString -> IO (Ptr CIborIndex)
foreign import ccall safe "ql.h qlCreateIborON"
  c_createIborON :: CString -> Ptr CYieldTermStructure -> Ptr CString
  -> IO (Ptr CIborIndex)
foreign import ccall safe "ql.h qlCreateDailyTenorIbor"
  c_createDailyTenorLibor :: CString -> CUInt -> Ptr CYieldTermStructure
    -> Ptr CString -> IO (Ptr CIborIndex)

createIbor :: String -> Period -> YieldTermStructure -> IO IborIndex
createIbor famname tenor ts =
  withCString famname
  (\n -> withObject2 tenor ts
          (\p t -> (construct $ c_createIbor n p t)))

createIborON :: String -> YieldTermStructure -> IO IborIndex
createIborON famname ts =
  withCString famname
  (\n -> withObject ts
          (construct . c_createIborON n))

createDailyTenorLibor :: String -> Word -> YieldTermStructure
  -> IO IborIndex
createDailyTenorLibor famname settlDays ts =
  withCString famname
  (\n -> withObject ts
          (construct . c_createDailyTenorLibor n (fromIntegral settlDays)))

-- |(qlEuribor)
euribor :: Period -> YieldTermStructure -> IO IborIndex
euribor = createIbor "Euribor"

-- |(qlEuribor365)
euribor365 :: Period -> YieldTermStructure -> IO IborIndex
euribor365 = createIbor "Euribor365"

audLibor :: Period -> YieldTermStructure -> IO IborIndex
audLibor = createIbor "AUDLibor"

cadLibor :: Period -> YieldTermStructure -> IO IborIndex
cadLibor = createIbor "CADLibor"

cadLiborON :: YieldTermStructure -> IO IborIndex
cadLiborON = createIborON "CADLiborON"

cdor :: Period -> YieldTermStructure -> IO IborIndex
cdor = createIbor "Cdor"

chfLibor :: Period -> YieldTermStructure -> IO IborIndex
chfLibor = createIbor "CHFLibor"

dailyTenorChfLibor :: Word -> YieldTermStructure -> IO IborIndex
dailyTenorChfLibor = createDailyTenorLibor "DailyTenorCHFLibor"

dkkLibor :: Period -> YieldTermStructure -> IO IborIndex
dkkLibor = createIbor "DKKLibor"

-- |(qlEonia)
eonia :: YieldTermStructure -> IO IborIndex
eonia = createIborON "Eonia"

eurLibor :: Period -> YieldTermStructure -> IO IborIndex
eurLibor = createIbor "EURLibor"

dailyTenorEURLibor :: Word -> YieldTermStructure -> IO IborIndex
dailyTenorEURLibor = createDailyTenorLibor "DailyTenorEURLibor"

gbpLibor :: Period -> YieldTermStructure -> IO IborIndex
gbpLibor = createIbor "GBPLibor"

dailyTenorGBPLibor :: Word -> YieldTermStructure -> IO IborIndex
dailyTenorGBPLibor = createDailyTenorLibor "DailyTenorGBPLibor"

gbpLiborON :: YieldTermStructure -> IO IborIndex
gbpLiborON = createIborON "GBPLiborON"

jibar :: Period -> YieldTermStructure -> IO IborIndex
jibar = createIbor "Jibar"

jpyLibor :: Period -> YieldTermStructure -> IO IborIndex
jpyLibor = createIbor "JPYLibor"

dailyTenorJPYLibor :: Word -> YieldTermStructure -> IO IborIndex
dailyTenorJPYLibor = createDailyTenorLibor "DailyTenorJPYLibor"

nzdLibor :: Period -> YieldTermStructure -> IO IborIndex
nzdLibor = createIbor "NZDLibor"

sekLibor :: Period -> YieldTermStructure -> IO IborIndex
sekLibor = createIbor "SEKLibor"

-- |(qlSonia)
sonia :: YieldTermStructure -> IO IborIndex
sonia = createIborON "Sonia"

tibor :: Period -> YieldTermStructure -> IO IborIndex
tibor = createIbor "Tibor"

trLibor  :: Period -> YieldTermStructure -> IO IborIndex
trLibor = createIbor "TRLibor"

usdLibor :: Period -> YieldTermStructure -> IO IborIndex
usdLibor = createIbor "USDLibor"

dailyTenorUsdLibor :: Word -> YieldTermStructure -> IO IborIndex
dailyTenorUsdLibor = createDailyTenorLibor "DailyTenorUSDLibor"

usdLiborON :: YieldTermStructure -> IO IborIndex
usdLiborON = createIborON "USDLiborON"

zibor :: Period -> YieldTermStructure -> IO IborIndex
zibor = createIbor "Zibor"

foreign import ccall safe "ql.h qlIborAsIndex"
  c_iborAsIndex :: Ptr CIborIndex -> Ptr CIndex

instance IsA CIndex CIborIndex where
  cast = c_iborAsIndex
