{-# LANGUAGE ForeignFunctionInterface,MultiParamTypeClasses #-}
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

-- | (qlIborIndex)
iborIndex :: String -> Period -> Word -> Currency -> Calendar
  -> BusinessDayConvention -> Bool -> DayCounter -> Maybe YieldTermStructure
  -> IO IborIndex
iborIndex famname tenor settlDays ccy cal conv eom dayCounter fwd =
  withCString famname
  (\n ->
    withObject4 tenor ccy cal dayCounter
    (\t cur c dc ->
      maybeWithObject fwd
      (construct . c_iborIndex n
                               t
                               (fromIntegral settlDays)
                               cur
                               c
                               (toQlEnum conv)
                               (fromBool eom)
                               dc)))

foreign import ccall safe "ql.h qlLibor"
  c_libor :: CString -> Ptr CPeriod -> CUInt -> Ptr CCurrency
    -> Ptr CCalendar -> Ptr CDayCounter -> Ptr CYieldTermStructure
    -> Ptr CString -> IO (Ptr CIborIndex)

-- |(qlLibor)
libor :: String -> Period -> Word -> Currency -> Calendar -> DayCounter
  -> Maybe YieldTermStructure -> IO IborIndex
libor famname tenor settlDays ccy cal dayCount fwd =
  withCString famname
  (\n ->
    withObject4 tenor ccy cal dayCount
    (\t cur c dc -> 
    maybeWithObject fwd
    (construct . c_libor n
                         t
                         (fromIntegral settlDays)
                         cur
                         c
                         dc)))

foreign import ccall safe "ql.h qlDailyTenorLibor"
  c_dailyTenorLibor :: CString -> CUInt -> Ptr CCurrency -> Ptr CCalendar
    -> Ptr CDayCounter -> Ptr CYieldTermStructure -> Ptr CString
    -> IO (Ptr CIborIndex)

dailyTenorLibor :: String -> Word -> Currency -> Calendar -> DayCounter
  -> Maybe YieldTermStructure -> IO IborIndex
dailyTenorLibor famname settlDays ccy cal dayCount fwd =
  withCString famname
  (\n ->
    withObject3 ccy cal dayCount
    (\cur c dc ->
    maybeWithObject fwd
    (construct . c_dailyTenorLibor n
                                   (fromIntegral settlDays)
                                   cur
                                   c
                                   dc)))

foreign import ccall safe "ql.h qlOvernightIndex"
  c_overnightIndex :: CString -> CUInt -> Ptr CCurrency -> Ptr CCalendar
    -> Ptr CDayCounter -> Ptr CYieldTermStructure -> Ptr CString
    -> IO (Ptr CIborIndex)

-- |(qlOvernightIndex)
overnightIndex :: String -> Word -> Currency -> Calendar -> DayCounter
  -> Maybe YieldTermStructure -> IO IborIndex
overnightIndex famname settlDays ccy cal dayCount fwd =
  withCString famname
  (\n ->
    withObject3 ccy cal dayCount
    (\cur c dc ->
      maybeWithObject fwd
      (construct . c_overnightIndex n
                                    (fromIntegral settlDays)
                                    cur
                                    c
                                    dc)))


foreign import ccall safe "ql.h qlCreateIbor"
  c_createIbor :: CString -> Ptr CPeriod -> Ptr CYieldTermStructure
    -> Ptr CString -> IO (Ptr CIborIndex)
foreign import ccall safe "ql.h qlCreateIborON"
  c_createIborON :: CString -> Ptr CYieldTermStructure -> Ptr CString
  -> IO (Ptr CIborIndex)
foreign import ccall safe "ql.h qlCreateDailyTenorIbor"
  c_createDailyTenorLibor :: CString -> CUInt -> Ptr CYieldTermStructure
    -> Ptr CString -> IO (Ptr CIborIndex)

createIbor :: String -> Period -> Maybe YieldTermStructure -> IO IborIndex
createIbor famname tenor ts =
  withCString famname
  (\n ->
    withObject tenor
    (\p ->
      maybeWithObject ts
      (construct . c_createIbor n p)))

createIborON :: String -> Maybe YieldTermStructure -> IO IborIndex
createIborON famname ts =
  withCString famname
  (\n -> maybeWithObject ts
          (construct . c_createIborON n))

createDailyTenorLibor :: String -> Word -> Maybe YieldTermStructure
  -> IO IborIndex
createDailyTenorLibor famname settlDays ts =
  withCString famname
  (\n -> maybeWithObject ts
          (construct . c_createDailyTenorLibor n (fromIntegral settlDays)))

-- |(qlEuribor)
euribor :: Period -> Maybe YieldTermStructure -> IO IborIndex
euribor = createIbor "Euribor"

-- |(qlEuribor365)
euribor365 :: Period -> Maybe YieldTermStructure -> IO IborIndex
euribor365 = createIbor "Euribor365"

audLibor :: Period -> Maybe YieldTermStructure -> IO IborIndex
audLibor = createIbor "AUDLibor"

cadLibor :: Period -> Maybe YieldTermStructure -> IO IborIndex
cadLibor = createIbor "CADLibor"

cadLiborON :: Maybe YieldTermStructure -> IO IborIndex
cadLiborON = createIborON "CADLiborON"

cdor :: Period -> Maybe YieldTermStructure -> IO IborIndex
cdor = createIbor "Cdor"

chfLibor :: Period -> Maybe YieldTermStructure -> IO IborIndex
chfLibor = createIbor "CHFLibor"

dailyTenorChfLibor :: Word -> Maybe YieldTermStructure -> IO IborIndex
dailyTenorChfLibor = createDailyTenorLibor "DailyTenorCHFLibor"

dkkLibor :: Period -> Maybe YieldTermStructure -> IO IborIndex
dkkLibor = createIbor "DKKLibor"

-- |(qlEonia)
eonia :: Maybe YieldTermStructure -> IO IborIndex
eonia = createIborON "Eonia"

eurLibor :: Period -> Maybe YieldTermStructure -> IO IborIndex
eurLibor = createIbor "EURLibor"

dailyTenorEURLibor :: Word -> Maybe YieldTermStructure -> IO IborIndex
dailyTenorEURLibor = createDailyTenorLibor "DailyTenorEURLibor"

gbpLibor :: Period -> Maybe YieldTermStructure -> IO IborIndex
gbpLibor = createIbor "GBPLibor"

dailyTenorGBPLibor :: Word -> Maybe YieldTermStructure -> IO IborIndex
dailyTenorGBPLibor = createDailyTenorLibor "DailyTenorGBPLibor"

gbpLiborON :: Maybe YieldTermStructure -> IO IborIndex
gbpLiborON = createIborON "GBPLiborON"

jibar :: Period -> Maybe YieldTermStructure -> IO IborIndex
jibar = createIbor "Jibar"

jpyLibor :: Period -> Maybe YieldTermStructure -> IO IborIndex
jpyLibor = createIbor "JPYLibor"

dailyTenorJPYLibor :: Word -> Maybe YieldTermStructure -> IO IborIndex
dailyTenorJPYLibor = createDailyTenorLibor "DailyTenorJPYLibor"

nzdLibor :: Period -> Maybe YieldTermStructure -> IO IborIndex
nzdLibor = createIbor "NZDLibor"

sekLibor :: Period -> Maybe YieldTermStructure -> IO IborIndex
sekLibor = createIbor "SEKLibor"

-- |(qlSonia)
sonia :: Maybe YieldTermStructure -> IO IborIndex
sonia = createIborON "Sonia"

tibor :: Period -> Maybe YieldTermStructure -> IO IborIndex
tibor = createIbor "Tibor"

trLibor  :: Period -> Maybe YieldTermStructure -> IO IborIndex
trLibor = createIbor "TRLibor"

usdLibor :: Period -> Maybe YieldTermStructure -> IO IborIndex
usdLibor = createIbor "USDLibor"

dailyTenorUsdLibor :: Word -> Maybe YieldTermStructure -> IO IborIndex
dailyTenorUsdLibor = createDailyTenorLibor "DailyTenorUSDLibor"

usdLiborON :: Maybe YieldTermStructure -> IO IborIndex
usdLiborON = createIborON "USDLiborON"

zibor :: Period -> Maybe YieldTermStructure -> IO IborIndex
zibor = createIbor "Zibor"

foreign import ccall safe "ql.h qlIborIndex"
  c_iborIndex :: CString -> Ptr CPeriod -> CUInt -> Ptr CCurrency
    -> Ptr CCalendar -> CInt -> CInt -> Ptr CDayCounter
    -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CIborIndex)
