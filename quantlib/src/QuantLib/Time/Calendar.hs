{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
-- |/NB/ Calendars in QuantLib are sort of singletons: if you add a holiday to
-- QuantLib::Russia, it will be added to all instances of the calendar.
-- QuantLib considers calendars equal if their names match.
-- The name of a joint calendar is the concatenation of its
-- components so they will be considered equal even if their holidays are
-- different.
-- BespokeCalendar provide the most generic solution.
module QuantLib.Time.Calendar
  (
    adjust
  , advance

  , nullCalendar
  , target
  , argentinaMerval
  , australia
  , brazilSettlement
  , brazilExchange
  , canadaSettlement
  , canadaTSX
  , china
  , czechRepublicPSE
  , denmark
  , finland
  , germanyEurex
  , germanyFrankfurtStockExchange
  , germanySettlement
  , germanyXetra
  , hongKongHKEx
  , hungary
  , icelandICEX
  , indiaNSE
  , indonesiaBEJ
  , indonesiaJSX
  , indonesiaIDX
  , italyExchange
  , italySettlement
  , japan
  , mexicoBMV
  , newZealand
  , norway
  , poland
  , russia
  , saudiArabiaTadawul
  , singaporeSGX
  , slovakiaBSSE
  , southAfrica
  , southKoreaKRX
  , southKoreaSettlement
  , sweden
  , switzerland
  , taiwanTSEC
  , turkey
  , ukraineUSE
  , londonStockExchange
  , london
  , unitedKingdomMetals
  , unitedKingdomSettlement
  , unitedStatesGovernmentBond
  , unitedStatesNERC
  , unitedStatesNYSE
  , unitedStatesSettlement
  , weekendsOnly
  , unitedKingdomExchange

  , addHoliday
  , advance'
  , businessDaysBetween
  , endOfMonth
  , isBusinessDay
  , isEndOfMonth
  , isHoliday
  , isWeekend
  , removeHoliday

  , bespokeCalendar
  , jointCalendar2
  , jointCalendar3
  , jointCalendar4
  , holidays
  )
where

import Data.Functor((<$>))
import Foreign.Marshal.Utils(fromBool)

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.JointCalendarRule
import QuantLib.Time.Unit(Unit)
import QuantLib.Time.Weekday

foreign import ccall safe "ql.h qlCalendarAdjust"
  c_calendarAdjust :: Ptr CCalendar -> CDate -> CInt -> IO CDate
foreign import ccall safe "ql.h qlCalendarAdvance"
  c_calendarAdvance :: Ptr CCalendar -> CDate -> CInt -> CInt -> CInt -> CInt -> IO CDate

-- |Adjusts a non-business day to the appropriate near business day with respect to the given convention. QuantLibXL: qlCalendarAdjust
adjust :: Calendar -> Day -> BusinessDayConvention -> IO Day
adjust = $(ffiCall 'adjust) c_calendarAdjust

-- |Advances the given date of the given number of business days and returns the result. QuantLibXL: qlCalendarAdvance
advance :: Calendar -> Day -> Int -> Unit -> BusinessDayConvention
  -> Bool -- ^endOfMonth
  -> IO Day
advance = $(ffiCall 'advance) c_calendarAdvance

-- |Calendar for reproducing theoretical calculations.
-- This calendar has no holidays. It ensures that dates at whole-month distances have the same day of month.
nullCalendar            :: IO Calendar
target                  :: IO Calendar -- ^TARGET calendar
argentinaMerval         :: IO Calendar -- ^Argentinian calendar: Buenos Aires stock exchange
australia               :: IO Calendar -- ^Australian calendar
brazilSettlement        :: IO Calendar -- ^Brazilian calendar: generic settlement
brazilExchange          :: IO Calendar -- ^Brazilian calendar: BOVESPA
canadaSettlement        :: IO Calendar -- ^Canadian calendar: generic settlement
canadaTSX               :: IO Calendar -- ^Canadian calendar: Toronto stock exchange
china                   :: IO Calendar -- ^Chinese calendar
czechRepublicPSE        :: IO Calendar -- ^Czech calendar: Prague stock exchange
denmark                 :: IO Calendar -- ^Danish calendar
finland                 :: IO Calendar -- ^Finnish calendar
germanyEurex            :: IO Calendar -- ^German calendar: Eurex
germanyFrankfurtStockExchange :: IO Calendar -- ^German calendar: Frankfurt stock-exchange
germanySettlement       :: IO Calendar -- ^German calendar: generic settlement
germanyXetra            :: IO Calendar -- ^German calendar: Xetra
hongKongHKEx            :: IO Calendar -- ^Hong Kong calendar: Hong Kong stock exchange
hungary                 :: IO Calendar -- ^Hungarian calendar
icelandICEX             :: IO Calendar -- ^Icelandic calendar: Iceland stock exchange.
indiaNSE                :: IO Calendar -- ^Indian calendar: National Stock Exchange.
indonesiaBEJ            :: IO Calendar -- ^Indonesian calendar: Jakarta stock exchange (merged into IDX)
indonesiaJSX            :: IO Calendar -- ^Indonesian calendar: Jakarta stock exchange (merged into IDX)
indonesiaIDX            :: IO Calendar -- ^Indonesian calendar: Indonesia stock exchange
italyExchange           :: IO Calendar -- ^Italian calendar: Milan stock-exchange
italySettlement         :: IO Calendar -- ^Italian calendar: generic settlement
japan                   :: IO Calendar -- ^Japanese calendar
mexicoBMV               :: IO Calendar -- ^Mexican calendar: Mexican stock exchange
newZealand              :: IO Calendar -- ^New Zealand calendar
norway                  :: IO Calendar -- ^Norwegian calendar
poland                  :: IO Calendar -- ^Polish calendar
russia                  :: IO Calendar -- ^Russian calendar
saudiArabiaTadawul      :: IO Calendar -- ^Saudi Arabian calendar: Tadawul financial market
singaporeSGX            :: IO Calendar -- ^Singapore calendar: Singapore exchange.
slovakiaBSSE            :: IO Calendar -- ^Slovak calendars: Bratislava stock exchange
southAfrica             :: IO Calendar -- ^South-African calendar
southKoreaKRX           :: IO Calendar -- ^South Korean calendar: KRX
southKoreaSettlement    :: IO Calendar -- ^South Korean calendar: public holidays
sweden                  :: IO Calendar -- ^Swedish calendar
switzerland             :: IO Calendar -- ^Swiss calendar
taiwanTSEC              :: IO Calendar -- ^Taiwanese calendar: Taiwan stock exchange
turkey                  :: IO Calendar -- ^Turkish calendar
ukraineUSE              :: IO Calendar -- ^Ukrainian calendar: Ukrainian stock exchange
unitedKingdomExchange   :: IO Calendar -- ^United Kingdom calendar: London stock-exchange
londonStockExchange     :: IO Calendar -- ^United Kingdom calendar: London stock exchange
london                  :: IO Calendar -- ^United Kingdom calendar: London stock exchange
unitedKingdomMetals     :: IO Calendar -- ^United Kingdom calendar: London metal exchange
unitedKingdomSettlement :: IO Calendar -- ^United Kingdom calendar: generic settlement
unitedStatesGovernmentBond:: IO Calendar -- ^United States calendar: government-bond
unitedStatesNERC        :: IO Calendar -- ^United States calendar: off-peak days for NERC
unitedStatesNYSE        :: IO Calendar -- ^United States calendar: New York stock exchange
unitedStatesSettlement  :: IO Calendar -- ^United States calendar: generic settlement
-- |Weekends-only calendar.
-- This calendar has no bank holidays except for weekends (Saturdays and Sundays) as required by ISDA for calculating conventional CDS spreads.
weekendsOnly            :: IO Calendar

nullCalendar            = constructNamed "NullCalendar"
target                  = constructNamed "TARGET"
argentinaMerval         = constructNamed "Argentina::Merval"
australia               = constructNamed "Australia"
brazilSettlement        = constructNamed "Brazil::Settlement"
brazilExchange          = constructNamed "Brazil::Exchange"
canadaSettlement        = constructNamed "Canada::Settlement"
canadaTSX               = constructNamed "Canada::TSX"
china                   = constructNamed "China"
czechRepublicPSE        = constructNamed "CzechRepublic::PSE"
denmark                 = constructNamed "Denmark"
finland                 = constructNamed "Finland"
germanyEurex            = constructNamed "Germany::Eurex"
germanyFrankfurtStockExchange = constructNamed "Germany::FrankfurtStockExchange"
germanySettlement       = constructNamed "Germany::Settlement"
germanyXetra            = constructNamed "Germany::Xetra"
hongKongHKEx            = constructNamed "HongKong::HKEx"
hungary                 = constructNamed "Hungary"
icelandICEX             = constructNamed "Iceland::ICEX"
indiaNSE                = constructNamed "India::NSE"
indonesiaBEJ            = constructNamed "Indonesia::BEJ"
indonesiaJSX            = constructNamed "Indonesia::JSX"
indonesiaIDX            = constructNamed "Indonesia::IDX"
italyExchange           = constructNamed "Italy::Exchange"
italySettlement         = constructNamed "Italy::Settlement"
japan                   = constructNamed "Japan"
mexicoBMV               = constructNamed "Mexico::BMV"
newZealand              = constructNamed "NewZealand"
norway                  = constructNamed "Norway"
poland                  = constructNamed "Poland"
russia                  = constructNamed "Russia"
saudiArabiaTadawul      = constructNamed "SaudiArabia::Tadawul"
singaporeSGX            = constructNamed "Singapore::SGX"
slovakiaBSSE            = constructNamed "Slovakia::BSSE"
southAfrica             = constructNamed "SouthAfrica"
southKoreaKRX           = constructNamed "SouthKorea::KRX"
southKoreaSettlement    = constructNamed "SouthKorea::Settlement"
sweden                  = constructNamed "Sweden"
switzerland             = constructNamed "Switzerland"
taiwanTSEC              = constructNamed "Taiwan::TSEC"
turkey                  = constructNamed "Turkey"
ukraineUSE              = constructNamed "Ukraine::USE"
unitedKingdomExchange   = constructNamed "UnitedKingdom::Exchange"
londonStockExchange     = constructNamed "London stock exchange"
london                  = constructNamed "LONDON"
unitedKingdomMetals     = constructNamed "UnitedKingdom::Metals"
unitedKingdomSettlement = constructNamed "UnitedKingdom::Settlement"
unitedStatesGovernmentBond = constructNamed "UnitedStates::GovernmentBond"
unitedStatesNERC        = constructNamed "UnitedStates::NERC"
unitedStatesNYSE        = constructNamed "UnitedStates::NYSE"
unitedStatesSettlement  = constructNamed "UnitedStates::Settlement"
weekendsOnly            = constructNamed "WeekendsOnly"

-- |Adds a date to the set of holidays for the given calendar.
addHoliday :: Calendar -> Day -> IO ()
addHoliday = $(ffiCallX 'addHoliday) c_addHoliday

foreign import ccall safe "ql.h qlCalendarAddHoliday"
  c_addHoliday :: Ptr CCalendar -> CDate -> Ptr CString -> IO ()

-- |Advances the given date as specified by the given period and returns the result. The input date is not modified.
advance' :: Calendar
  -> Day -- ^date
  -> Period -- ^period
  -> BusinessDayConvention -- ^convention
  -> Bool -- ^endOfMonth
  -> IO Day
advance' = $(ffiCallX 'advance') c_advance'

foreign import ccall safe "ql.h qlCalendarAdvance1"
  c_advance' :: Ptr CCalendar -> CDate -> Ptr CPeriod -> CInt -> CInt -> Ptr CString -> IO CDate

-- |Calculates the number of business days between two given dates and returns the result.
businessDaysBetween :: Calendar
  -> Day -- ^from
  -> Day -- ^to
  -> Bool -- ^includeFirst
  -> Bool -- ^includeLast
  -> IO Int
businessDaysBetween = $(ffiCallX 'businessDaysBetween) c_businessDaysBetween

foreign import ccall safe "ql.h qlCalendarBusinessDaysBetween"
  c_businessDaysBetween :: Ptr CCalendar -> CDate -> CDate -> CInt -> CInt -> Ptr CString -> IO CInt

-- |last business day of the month to which the given date belongs
endOfMonth :: Calendar
  -> Day -- ^d
  -> IO Day
endOfMonth = $(ffiCallX 'endOfMonth) c_endOfMonth

foreign import ccall safe "ql.h qlCalendarEndOfMonth"
  c_endOfMonth :: Ptr CCalendar -> CDate -> Ptr CString -> IO CDate

-- |Returns true iff the date is a business day for the given market.
isBusinessDay :: Calendar
  -> Day -- ^d
  -> IO Bool
isBusinessDay = $(ffiCallX 'isBusinessDay) c_isBusinessDay

foreign import ccall safe "ql.h qlCalendarIsBusinessDay"
  c_isBusinessDay :: Ptr CCalendar -> CDate -> Ptr CString -> IO CInt

-- |Returns true iff the date is last business day for the month in given market.
isEndOfMonth :: Calendar
  -> Day -- ^d
  -> IO Bool
isEndOfMonth = $(ffiCallX 'isEndOfMonth) c_isEndOfMonth

foreign import ccall safe "ql.h qlCalendarIsEndOfMonth"
  c_isEndOfMonth :: Ptr CCalendar -> CDate -> Ptr CString -> IO CInt

-- |Returns true iff the date is a holiday for the given market.
isHoliday :: Calendar
  -> Day -- ^d
  -> IO Bool
isHoliday = $(ffiCallX 'isHoliday) c_isHoliday

foreign import ccall safe "ql.h qlCalendarIsHoliday"
  c_isHoliday :: Ptr CCalendar -> CDate -> Ptr CString -> IO CInt

-- |Returns true iff the weekday is part of the weekend for the given market.
isWeekend :: Calendar
  -> Weekday -- ^w
  -> IO Bool
isWeekend = $(ffiCallX 'isWeekend) c_isWeekend

foreign import ccall safe "ql.h qlCalendarIsWeekend"
  c_isWeekend :: Ptr CCalendar -> CInt -> Ptr CString -> IO CInt

-- |Removes a date from the set of holidays for the given calendar.
removeHoliday :: Calendar
  -> Day
  -> IO ()
removeHoliday = $(ffiCallX 'removeHoliday) c_removeHoliday

foreign import ccall safe "ql.h qlCalendarRemoveHoliday"
  c_removeHoliday :: Ptr CCalendar -> CDate -> Ptr CString -> IO ()

-- |/Warning/ different bespoke calendars created with the same name (or different bespoke calendars created with no name) will compare as equal.
bespokeCalendar :: String -- ^name
  -> [Weekday] -- ^weekends
  -> IO Calendar
bespokeCalendar = $(ffiCall 'bespokeCalendar) c_bespokeCalendar

foreign import ccall safe "ql.h qlBespokeCalendar"
  c_bespokeCalendar :: CString -> CUInt -> Ptr CInt -> Ptr CString -> IO (Ptr CCalendar)

jointCalendar3 :: Calendar -> Calendar -> Calendar -> JointCalendarRule
  -> IO Calendar
jointCalendar3 = $(ffiCall 'jointCalendar3) c_jointCalendar3

foreign import ccall safe "ql.h qlJointCalendar3"
  c_jointCalendar3 :: Ptr CCalendar -> Ptr CCalendar -> Ptr CCalendar -> CInt -> Ptr CString -> IO (Ptr CCalendar)

jointCalendar4 :: Calendar -> Calendar -> Calendar
  -> Calendar -> JointCalendarRule -> IO Calendar
jointCalendar4 = $(ffiCall 'jointCalendar4) c_jointCalendar4

foreign import ccall safe "ql.h qlJointCalendar4"
  c_jointCalendar4 :: Ptr CCalendar -> Ptr CCalendar -> Ptr CCalendar -> Ptr CCalendar -> CInt -> Ptr CString -> IO (Ptr CCalendar)

jointCalendar2 :: Calendar -> Calendar -> JointCalendarRule -> IO Calendar
jointCalendar2 = $(ffiCall 'jointCalendar2) c_jointCalendar2

foreign import ccall safe "ql.h qlJointCalendar2"
  c_jointCalendar2 :: Ptr CCalendar -> Ptr CCalendar -> CInt -> Ptr CString -> IO (Ptr CCalendar)

-- |Returns the holidays between two dates.
holidays :: Calendar -- ^calendar
  -> Day -- ^from
  -> Day -- ^to
  -> Bool -- ^includeWeekEnds
  -> IO [Day]
holidays c from to w =
  map fromQlDate <$>
    withObject c
      (\cc -> getArrayX $ c_holidayList cc (toQlDate from) (toQlDate to) (fromBool w))

foreign import ccall safe "ql.h qlCalendarHolidayList"
  c_holidayList :: Ptr CCalendar -> CDate -> CDate -> CInt -> Ptr CUInt -> Ptr CString -> IO (Ptr CDate)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
