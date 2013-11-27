{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Index.Ibor
  (
    iborIndex
  , overnightIndex
  , libor
  , dailyTenorLibor
  , euribor
  , euribor365
  , eurLiborON
  , audLibor
  , cadLibor
  , cadLiborON
  , cdor
  , chfLibor
  , dailyTenorCHFLibor
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
  , dailyTenorUSDLibor
  , usdLiborON
  , zibor

  , euriborSW
  , euribor2W
  , euribor3W
  , euribor1M
  , euribor2M
  , euribor3M
  , euribor4M
  , euribor5M
  , euribor6M
  , euribor7M
  , euribor8M
  , euribor9M
  , euribor10M
  , euribor11M
  , euribor1Y
  , euribor365SW
  , euribor3652W
  , euribor3653W
  , euribor3651M
  , euribor3652M
  , euribor3653M
  , euribor3654M
  , euribor3655M
  , euribor3656M
  , euribor3657M
  , euribor3658M
  , euribor3659M
  , euribor36510M
  , euribor36511M
  , euribor3651Y
  , eurLiborSW
  , eurLibor2W
  , eurLibor1M
  , eurLibor2M
  , eurLibor3M
  , eurLibor4M
  , eurLibor5M
  , eurLibor6M
  , eurLibor7M
  , eurLibor8M
  , eurLibor9M
  , eurLibor10M
  , eurLibor11M
  , eurLibor1Y

  , businessDayConvention
  , endOfMonth
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Unit(Unit(..))

foreign import ccall safe "ql.h qlIborIndex"
  c_iborIndex :: CString -> CInt -> CInt -> CUInt -> Ptr CCurrency
    -> Ptr CCalendar -> CInt -> CInt -> Ptr CDayCounter
    -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CIborIndex)

iborIndex :: String -- ^familyName
  -> (Int, Unit) -- ^tenor
  -> Word -- ^settlementDays
  -> Currency -- ^currency
  -> Calendar -- ^fixingCalendar
  -> BusinessDayConvention -- ^convention
  -> Bool -- ^endOfMonth
  -> DayCounter -- ^dayCounter
  -> Maybe YieldTermStructure
  -> IO IborIndex
iborIndex = $(ffiCall 'iborIndex) c_iborIndex

foreign import ccall safe "ql.h qlLibor"
  c_libor :: CString -> CInt -> CInt -> CUInt -> Ptr CCurrency
    -> Ptr CCalendar -> Ptr CDayCounter -> Ptr CYieldTermStructure
    -> Ptr CString -> IO (Ptr CIborIndex)

-- |all BBA LIBOR indexes but the EUR, O\/N, and S\/N ones
-- LIBOR fixed by BBA. See <http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414>.
libor :: String -- ^familyName
  -> (Int, Unit) -- ^tenor
  -> Word -- ^settlementDays
  -> Currency -- ^currency
  -> Calendar -- ^financialCenterCalendar
  -> DayCounter -- ^dayCounter
  -> Maybe YieldTermStructure -> IO IborIndex
libor = $(ffiCall 'libor) c_libor

foreign import ccall safe "ql.h qlDailyTenorLibor"
  c_dailyTenorLibor :: CString -> CUInt -> Ptr CCurrency -> Ptr CCalendar
    -> Ptr CDayCounter -> Ptr CYieldTermStructure -> Ptr CString
    -> IO (Ptr CIborIndex)

-- |O\/N-S\/N BBA LIBOR indexes but the EUR ones
-- One day deposit LIBOR fixed by BBA. See <http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414>.
dailyTenorLibor :: String -- ^ familyName
  -> Word -- ^settlementDays
  -> Currency -- ^currency
  -> Calendar -- ^financialCenterCalendar
  -> DayCounter -- ^dayCounter
  -> Maybe YieldTermStructure -> IO IborIndex
dailyTenorLibor = $(ffiCall 'dailyTenorLibor) c_dailyTenorLibor

foreign import ccall safe "ql.h qlOvernightIndex"
  c_overnightIndex :: CString -> CUInt -> Ptr CCurrency -> Ptr CCalendar
    -> Ptr CDayCounter -> Ptr CYieldTermStructure -> Ptr CString
    -> IO (Ptr COvernightIndex)

overnightIndex :: String -- ^familyName
  -> Word -- ^settlementDays
  -> Currency -- ^currency
  -> Calendar -- ^fixingCalendar
  -> DayCounter -- ^dayCounter
  -> Maybe YieldTermStructure
  -> IO OvernightIndex
overnightIndex = $(ffiCall 'overnightIndex) c_overnightIndex

foreign import ccall safe "ql.h qlCreateIbor"
  c_createIbor :: CString -> CInt -> CInt -> Ptr CYieldTermStructure
    -> Ptr CString -> IO (Ptr CIborIndex)
foreign import ccall safe "ql.h qlCreateIborON"
  c_createIborON :: CString -> Ptr CYieldTermStructure -> Ptr CString
  -> IO (Ptr CIborIndex)
foreign import ccall safe "ql.h qlCreateDailyTenorIbor"
  c_createDailyTenorLibor :: CString -> CUInt -> Ptr CYieldTermStructure
    -> Ptr CString -> IO (Ptr CIborIndex)

createIbor :: String -> (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
createIbor = $(ffiCall 'createIbor) c_createIbor

createIborON :: String -> Maybe YieldTermStructure -> IO IborIndex
createIborON = $(ffiCall 'createIborON) c_createIborON

createDailyTenorLibor :: String -> Word -> Maybe YieldTermStructure
  -> IO IborIndex
createDailyTenorLibor = $(ffiCall 'createDailyTenorLibor) c_createDailyTenorLibor

-- |Euribor index
-- Euribor rate fixed by the ECB./Warning/ This is the rate fixed by the ECB. Use EurLibor if you're interested in the London fixing by BBA
euribor :: (Int, Unit) -- ^tenor
  -> Maybe YieldTermStructure -> IO IborIndex
euribor = createIbor "Euribor"

-- |Actual/365 Euribor index.
-- Euribor rate adjusted for the mismatch between the actual/360 convention used for Euribor and the actual/365 convention previously used by a few pre-EUR currencies
euribor365 :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
euribor365 = createIbor "Euribor365"

-- |AUD LIBOR rate
-- Australian Dollar LIBOR fixed by BBA. See <http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414>.
audLibor :: (Int, Unit) -- ^tenor
  -> Maybe YieldTermStructure -> IO IborIndex
audLibor = createIbor "AUDLibor"

-- |CAD LIBOR rate
-- Canadian Dollar LIBOR fixed by BBA. See <http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414>. /Warning/ This is the rate fixed in London by BBA. Use CDOR if you're interested in the Canadian fixing by IDA.
cadLibor :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
cadLibor = createIbor "CADLibor"

-- |Overnight CAD Libor index
cadLiborON :: Maybe YieldTermStructure -> IO IborIndex
cadLiborON = createIborON "CADLiborON"

cdor :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
cdor = createIbor "Cdor"

-- |CHF LIBOR rate
-- Swiss Franc LIBOR fixed by BBA. See <http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414>. /Warning/ This is the rate fixed in London by BBA. Use ZIBOR if you're interested in the Zurich fixing.
chfLibor :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
chfLibor = createIbor "CHFLibor"

-- |one day deposit BBA CHF LIBOR indexes
dailyTenorCHFLibor :: Word -- ^settlementDays
  -> Maybe YieldTermStructure -> IO IborIndex
dailyTenorCHFLibor = createDailyTenorLibor "DailyTenorCHFLibor"

-- |DKK LIBOR rate
--  Danish Krona LIBOR fixed by BBA. See <http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414>.
dkkLibor :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
dkkLibor = createIbor "DKKLibor"

foreign import ccall safe "ql.h qlCreateONIndex"
  c_createONIndex :: CString -> Ptr CYieldTermStructure -> Ptr CString
    -> IO (Ptr COvernightIndex)

createONIndex :: String -> Maybe YieldTermStructure -> IO OvernightIndex
createONIndex = $(ffiCall 'createONIndex) c_createONIndex

-- |Eonia (Euro Overnight Index Average) rate fixed by the ECB
eonia :: Maybe YieldTermStructure -> IO OvernightIndex
eonia = createONIndex "Eonia"

-- |Sonia (Sterling Overnight Index Average) rate
sonia :: Maybe YieldTermStructure -> IO OvernightIndex
sonia = createONIndex "Sonia"

-- |all BBA EUR LIBOR indexes but the O\/N
-- Euro LIBOR fixed by BBA. See <http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414>. /Warning/ This is the rate fixed in London by BBA. Use Euribor if you're interested in the fixing by the ECB.
eurLibor :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
eurLibor = createIbor "EURLibor"

-- |one day deposit BBA EUR LIBOR indexes
-- |Euro O\/N LIBOR fixed by BBA. It can be also used for T/N and S/N indexes, even if such indexes do not have BBA fixing. See http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414. /Warning/ This is the rate fixed in London by BBA. Use Eonia if you're interested in the fixing by the ECB.
dailyTenorEURLibor :: Word -- ^settlementDays
  -> Maybe YieldTermStructure -> IO IborIndex
dailyTenorEURLibor = createDailyTenorLibor "DailyTenorEURLibor"

-- |GBP LIBOR rate
-- Pound Sterling LIBOR fixed by BBA. See <http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414>
gbpLibor :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
gbpLibor = createIbor "GBPLibor"

-- |base class for the one day deposit BBA GBP LIBOR indexes
dailyTenorGBPLibor :: Word -- ^settlementDays
  -> Maybe YieldTermStructure -> IO IborIndex
dailyTenorGBPLibor = createDailyTenorLibor "DailyTenorGBPLibor"

-- |Overnight GBP Libor index
gbpLiborON :: Maybe YieldTermStructure -> IO IborIndex
gbpLiborON = createIborON "GBPLiborON"

jibar :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
jibar = createIbor "Jibar"

-- |JPY LIBOR rate
-- Japanese Yen LIBOR fixed by BBA. See <http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414>. /Warning/ This is the rate fixed in London by BBA. Use TIBOR if you're interested in the Tokio fixing.
jpyLibor :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
jpyLibor = createIbor "JPYLibor"

-- |one day deposit BBA JPY LIBOR indexes
dailyTenorJPYLibor :: Word -- ^settlementDays
  -> Maybe YieldTermStructure -> IO IborIndex
dailyTenorJPYLibor = createDailyTenorLibor "DailyTenorJPYLibor"

-- |NZD LIBOR rate
-- New Zealand Dollar LIBOR fixed by BBA. See <http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414>.
nzdLibor :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
nzdLibor = createIbor "NZDLibor"

-- |SEK LIBOR rate
-- Sweden Krone LIBOR fixed by BBA. See <http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414>.
sekLibor :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
sekLibor = createIbor "SEKLibor"

-- |JPY TIBOR index
-- Tokyo Interbank Offered Rate.WarningThis is the rate fixed in Tokio by JBA. Use JPYLibor if you're interested in the London fixing by BBA.Possible enhancementscheck settlement days and end-of-month adjustment.
tibor :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
tibor = createIbor "Tibor"

-- |TRY LIBOR rate
-- TRY LIBOR fixed by TBA. See <http://www.trlibor.org/trlibor/english/default.asp> Possible enhancementscheck end-of-month adjustment.
trLibor  :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
trLibor = createIbor "TRLibor"

-- |USD LIBOR rate
-- US Dollar LIBOR fixed by BBA. See <http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414>.
usdLibor :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
usdLibor = createIbor "USDLibor"

dailyTenorUSDLibor :: Word -> Maybe YieldTermStructure -> IO IborIndex
dailyTenorUSDLibor = createDailyTenorLibor "DailyTenorUSDLibor"

-- |Overnight EUR Libor index
eurLiborON :: Maybe YieldTermStructure -> IO IborIndex
eurLiborON = createIborON "EURLiborON"

-- |Overnight USD Libor index
usdLiborON :: Maybe YieldTermStructure -> IO IborIndex
usdLiborON = createIborON "USDLiborON"

-- |CHF ZIBOR rate
-- Zurich Interbank Offered Rate.WarningThis is the rate fixed in Zurich by BBA. Use CHFLibor if you're interested in the London fixing by BBA.Possible enhancementscheck settlement days, end-of-month adjustment, and day-count convention.
zibor :: (Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex
zibor = createIbor "Zibor"

makeIbor :: ((Int, Unit) -> Maybe YieldTermStructure -> IO IborIndex) -> Int -> Unit -> Maybe YieldTermStructure -> IO IborIndex
makeIbor f i u = f (i, u)

-- |1-week Euribor index
euriborSW :: Maybe YieldTermStructure -> IO IborIndex
euriborSW = makeIbor euribor 1 Weeks

-- |2-weeks Euribor index
euribor2W :: Maybe YieldTermStructure -> IO IborIndex
euribor2W = makeIbor euribor 2 Weeks

-- |3-weeks Euribor index
euribor3W :: Maybe YieldTermStructure -> IO IborIndex
euribor3W = makeIbor euribor 3 Weeks

-- |1-month Euribor index
euribor1M :: Maybe YieldTermStructure -> IO IborIndex
euribor1M = makeIbor euribor 1 Months

-- |2-months Euribor index
euribor2M :: Maybe YieldTermStructure -> IO IborIndex
euribor2M = makeIbor euribor 2 Months

-- |3-months Euribor index
euribor3M :: Maybe YieldTermStructure -> IO IborIndex
euribor3M = makeIbor euribor 3 Months

-- |4-months Euribor index
euribor4M :: Maybe YieldTermStructure -> IO IborIndex
euribor4M = makeIbor euribor 4 Months

-- |5-months Euribor index
euribor5M :: Maybe YieldTermStructure -> IO IborIndex
euribor5M = makeIbor euribor 5 Months

-- |6-months Euribor index
euribor6M :: Maybe YieldTermStructure -> IO IborIndex
euribor6M = makeIbor euribor 6 Months

-- |7-months Euribor index
euribor7M :: Maybe YieldTermStructure -> IO IborIndex
euribor7M = makeIbor euribor 7 Months

-- |8-months Euribor index
euribor8M :: Maybe YieldTermStructure -> IO IborIndex
euribor8M = makeIbor euribor 8 Months

-- |9-months Euribor index
euribor9M :: Maybe YieldTermStructure -> IO IborIndex
euribor9M = makeIbor euribor 9 Months

-- |10-months Euribor index
euribor10M :: Maybe YieldTermStructure -> IO IborIndex
euribor10M = makeIbor euribor 10 Months

-- |11-months Euribor index
euribor11M :: Maybe YieldTermStructure -> IO IborIndex
euribor11M = makeIbor euribor 11 Months

-- |1-year Euribor index
euribor1Y :: Maybe YieldTermStructure -> IO IborIndex
euribor1Y = makeIbor euribor 1 Years

-- |1-week Euribor365 index
euribor365SW :: Maybe YieldTermStructure -> IO IborIndex
euribor365SW = makeIbor euribor365 1 Weeks

-- |2-weeks Euribor365 index
euribor3652W :: Maybe YieldTermStructure -> IO IborIndex
euribor3652W = makeIbor euribor365 2 Weeks

-- |3-weeks Euribor365 index
euribor3653W :: Maybe YieldTermStructure -> IO IborIndex
euribor3653W = makeIbor euribor365 3 Weeks

-- |1-month Euribor365 index
euribor3651M :: Maybe YieldTermStructure -> IO IborIndex
euribor3651M = makeIbor euribor365 1 Months

-- |2-months Euribor365 index
euribor3652M :: Maybe YieldTermStructure -> IO IborIndex
euribor3652M = makeIbor euribor365 2 Months

-- |3-months Euribor365 index
euribor3653M :: Maybe YieldTermStructure -> IO IborIndex
euribor3653M = makeIbor euribor365 3 Months

-- |4-months Euribor365 index
euribor3654M :: Maybe YieldTermStructure -> IO IborIndex
euribor3654M = makeIbor euribor365 4 Months

-- |5-months Euribor365 index
euribor3655M :: Maybe YieldTermStructure -> IO IborIndex
euribor3655M = makeIbor euribor365 5 Months

-- |6-months Euribor365 index
euribor3656M :: Maybe YieldTermStructure -> IO IborIndex
euribor3656M = makeIbor euribor365 6 Months

-- |7-months Euribor365 index
euribor3657M :: Maybe YieldTermStructure -> IO IborIndex
euribor3657M = makeIbor euribor365 7 Months

-- |8-months Euribor365 index
euribor3658M :: Maybe YieldTermStructure -> IO IborIndex
euribor3658M = makeIbor euribor365 8 Months

-- |9-months Euribor365 index
euribor3659M :: Maybe YieldTermStructure -> IO IborIndex
euribor3659M = makeIbor euribor365 9 Months

-- |10-months Euribor365 index
euribor36510M :: Maybe YieldTermStructure -> IO IborIndex
euribor36510M = makeIbor euribor365 10 Months

-- |11-months Euribor365 index
euribor36511M :: Maybe YieldTermStructure -> IO IborIndex
euribor36511M = makeIbor euribor365 11 Months

-- |1-year Euribor365 index
euribor3651Y :: Maybe YieldTermStructure -> IO IborIndex
euribor3651Y = makeIbor euribor365 1 Years

-- |1-week EUR Libor index
eurLiborSW :: Maybe YieldTermStructure -> IO IborIndex
eurLiborSW = makeIbor eurLibor 1 Weeks

-- |2-weeks EUR Libor index
eurLibor2W :: Maybe YieldTermStructure -> IO IborIndex
eurLibor2W = makeIbor eurLibor 2 Weeks

-- |1-month EUR Libor index
eurLibor1M :: Maybe YieldTermStructure -> IO IborIndex
eurLibor1M = makeIbor eurLibor 1 Months

-- |2-months EUR Libor index
eurLibor2M :: Maybe YieldTermStructure -> IO IborIndex
eurLibor2M = makeIbor eurLibor 2 Months

-- |3-months EUR Libor index
eurLibor3M :: Maybe YieldTermStructure -> IO IborIndex
eurLibor3M = makeIbor eurLibor 3 Months

-- |4-months EUR Libor index
eurLibor4M :: Maybe YieldTermStructure -> IO IborIndex
eurLibor4M = makeIbor eurLibor 4 Months

-- |5-months EUR Libor index
eurLibor5M :: Maybe YieldTermStructure -> IO IborIndex
eurLibor5M = makeIbor eurLibor 5 Months

-- |6-months EUR Libor index
eurLibor6M :: Maybe YieldTermStructure -> IO IborIndex
eurLibor6M = makeIbor eurLibor 6 Months

-- |7-months EUR Libor index
eurLibor7M :: Maybe YieldTermStructure -> IO IborIndex
eurLibor7M = makeIbor eurLibor 7 Months

-- |8-months EUR Libor index
eurLibor8M :: Maybe YieldTermStructure -> IO IborIndex
eurLibor8M = makeIbor eurLibor 8 Months

-- |9-months EUR Libor index
eurLibor9M :: Maybe YieldTermStructure -> IO IborIndex
eurLibor9M = makeIbor eurLibor 9 Months

-- |10-months EUR Libor index
eurLibor10M :: Maybe YieldTermStructure -> IO IborIndex
eurLibor10M = makeIbor eurLibor 10 Months

-- |11-months EUR Libor index
eurLibor11M :: Maybe YieldTermStructure -> IO IborIndex
eurLibor11M = makeIbor eurLibor 11 Months

-- |1-year EUR Libor index
eurLibor1Y :: Maybe YieldTermStructure -> IO IborIndex
eurLibor1Y = makeIbor eurLibor 1 Years

businessDayConvention :: IborIndex -> Either QLError BusinessDayConvention
businessDayConvention = $(ffiCallPureX2 'businessDayConvention) c_businessDayConvention

foreign import ccall safe "ql.h qlIborIndexBusinessDayConvention"
  c_businessDayConvention :: Ptr CIborIndex -> IO CInt

endOfMonth :: IborIndex
  -> Bool
endOfMonth = $(ffiCallPure 'endOfMonth) c_endOfMonth

foreign import ccall safe "ql.h qlIborIndexEndOfMonth"
  c_endOfMonth :: Ptr CIborIndex -> IO CInt

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
