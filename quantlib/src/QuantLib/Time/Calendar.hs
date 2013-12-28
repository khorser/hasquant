{-# LANGUAGE TemplateHaskell #-}
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
import QuantLib.Time.JointCalendarRule(JointCalendarRule)
import QuantLib.Time.Unit(Unit)
import QuantLib.Time.Weekday(Weekday)

foreign import ccall safe "ql.h qlCalendarAdjust"
  c_adjust :: Ptr CCalendar -> CDate -> CInt -> IO CDate
foreign import ccall safe "ql.h qlCalendarAdvance"
  c_advance :: Ptr CCalendar -> CDate -> CInt -> CInt -> CInt -> CInt -> IO CDate

-- |Adjusts a non-business day to the appropriate near business day with respect to the given convention
adjust :: Calendar s
  -> Day
  -> BusinessDayConvention
  -> QLE s Day
adjust = $(ffiCall 'adjust) c_adjust

-- |Advances the given date of the given number of business days and returns the result
advance :: Calendar s
  -> Day
  -> Int
  -> Unit
  -> BusinessDayConvention
  -> Bool -- ^endOfMonth
  -> QLE s Day
advance = $(ffiCall 'advance) c_advance

-- |Calendar for reproducing theoretical calculations.
-- This calendar has no holidays. It ensures that dates at whole-month distances have the same day of month.
nullCalendar            :: QLE s (Calendar s)
target                  :: QLE s (Calendar s) -- ^TARGET calendar
argentinaMerval         :: QLE s (Calendar s) -- ^Argentinian calendar: Buenos Aires stock exchange
australia               :: QLE s (Calendar s) -- ^Australian calendar
brazilSettlement        :: QLE s (Calendar s) -- ^Brazilian calendar: generic settlement
brazilExchange          :: QLE s (Calendar s) -- ^Brazilian calendar: BOVESPA
canadaSettlement        :: QLE s (Calendar s) -- ^Canadian calendar: generic settlement
canadaTSX               :: QLE s (Calendar s) -- ^Canadian calendar: Toronto stock exchange
china                   :: QLE s (Calendar s) -- ^Chinese calendar
czechRepublicPSE        :: QLE s (Calendar s) -- ^Czech calendar: Prague stock exchange
denmark                 :: QLE s (Calendar s) -- ^Danish calendar
finland                 :: QLE s (Calendar s) -- ^Finnish calendar
germanyEurex            :: QLE s (Calendar s) -- ^German calendar: Eurex
germanyFrankfurtStockExchange :: QLE s (Calendar s) -- ^German calendar: Frankfurt stock-exchange
germanySettlement       :: QLE s (Calendar s) -- ^German calendar: generic settlement
germanyXetra            :: QLE s (Calendar s) -- ^German calendar: Xetra
hongKongHKEx            :: QLE s (Calendar s) -- ^Hong Kong calendar: Hong Kong stock exchange
hungary                 :: QLE s (Calendar s) -- ^Hungarian calendar
icelandICEX             :: QLE s (Calendar s) -- ^Icelandic calendar: Iceland stock exchange.
indiaNSE                :: QLE s (Calendar s) -- ^Indian calendar: National Stock Exchange.
indonesiaBEJ            :: QLE s (Calendar s) -- ^Indonesian calendar: Jakarta stock exchange (merged into IDX)
indonesiaJSX            :: QLE s (Calendar s) -- ^Indonesian calendar: Jakarta stock exchange (merged into IDX)
indonesiaIDX            :: QLE s (Calendar s) -- ^Indonesian calendar: Indonesia stock exchange
italyExchange           :: QLE s (Calendar s) -- ^Italian calendar: Milan stock-exchange
italySettlement         :: QLE s (Calendar s) -- ^Italian calendar: generic settlement
japan                   :: QLE s (Calendar s) -- ^Japanese calendar
mexicoBMV               :: QLE s (Calendar s) -- ^Mexican calendar: Mexican stock exchange
newZealand              :: QLE s (Calendar s) -- ^New Zealand calendar
norway                  :: QLE s (Calendar s) -- ^Norwegian calendar
poland                  :: QLE s (Calendar s) -- ^Polish calendar
russia                  :: QLE s (Calendar s) -- ^Russian calendar
saudiArabiaTadawul      :: QLE s (Calendar s) -- ^Saudi Arabian calendar: Tadawul financial market
singaporeSGX            :: QLE s (Calendar s) -- ^Singapore calendar: Singapore exchange.
slovakiaBSSE            :: QLE s (Calendar s) -- ^Slovak calendars: Bratislava stock exchange
southAfrica             :: QLE s (Calendar s) -- ^South-African calendar
southKoreaKRX           :: QLE s (Calendar s) -- ^South Korean calendar: KRX
southKoreaSettlement    :: QLE s (Calendar s) -- ^South Korean calendar: public holidays
sweden                  :: QLE s (Calendar s) -- ^Swedish calendar
switzerland             :: QLE s (Calendar s) -- ^Swiss calendar
taiwanTSEC              :: QLE s (Calendar s) -- ^Taiwanese calendar: Taiwan stock exchange
turkey                  :: QLE s (Calendar s) -- ^Turkish calendar
ukraineUSE              :: QLE s (Calendar s) -- ^Ukrainian calendar: Ukrainian stock exchange
unitedKingdomExchange   :: QLE s (Calendar s) -- ^United Kingdom calendar: London stock-exchange
unitedKingdomMetals     :: QLE s (Calendar s) -- ^United Kingdom calendar: London metal exchange
unitedKingdomSettlement :: QLE s (Calendar s) -- ^United Kingdom calendar: generic settlement
unitedStatesGovernmentBond:: QLE s (Calendar s) -- ^United States calendar: government-bond
unitedStatesNERC        :: QLE s (Calendar s) -- ^United States calendar: off-peak days for NERC
unitedStatesNYSE        :: QLE s (Calendar s) -- ^United States calendar: New York stock exchange
unitedStatesSettlement  :: QLE s (Calendar s) -- ^United States calendar: generic settlement
-- |Weekends-only calendar.
-- This calendar has no bank holidays except for weekends (Saturdays and Sundays) as required by ISDA for calculating conventional CDS spreads.
weekendsOnly            :: QLE s (Calendar s)

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
unitedKingdomMetals     = constructNamed "UnitedKingdom::Metals"
unitedKingdomSettlement = constructNamed "UnitedKingdom::Settlement"
unitedStatesGovernmentBond = constructNamed "UnitedStates::GovernmentBond"
unitedStatesNERC        = constructNamed "UnitedStates::NERC"
unitedStatesNYSE        = constructNamed "UnitedStates::NYSE"
unitedStatesSettlement  = constructNamed "UnitedStates::Settlement"
weekendsOnly            = constructNamed "WeekendsOnly"

-- |Adds a date to the set of holidays for the given calendar.
addHoliday :: Calendar s -> Day -> QLE s ()
addHoliday = $(ffiCallX 'addHoliday) c_addHoliday

foreign import ccall safe "ql.h qlCalendarAddHoliday"
  c_addHoliday :: Ptr CCalendar -> CDate -> Ptr CString -> IO ()

-- |Advances the given date as specified by the given period and returns the result. The input date is not modified.
advance' :: Calendar s
  -> Day -- ^date
  -> (Int, Unit) -- ^period
  -> BusinessDayConvention -- ^convention
  -> Bool -- ^endOfMonth
  -> QLE s Day
advance' = $(ffiCallX 'advance') c_advance'

foreign import ccall safe "ql.h qlCalendarAdvance1"
  c_advance' :: Ptr CCalendar -> CDate -> CInt -> CInt -> CInt -> CInt -> Ptr CString -> IO CDate

-- |Calculates the number of business days between two given dates and returns the result.
businessDaysBetween :: Calendar s
  -> Day -- ^from
  -> Day -- ^to
  -> Bool -- ^includeFirst
  -> Bool -- ^includeLast
  -> QLE s Int
businessDaysBetween = $(ffiCallX 'businessDaysBetween) c_businessDaysBetween

foreign import ccall safe "ql.h qlCalendarBusinessDaysBetween"
  c_businessDaysBetween :: Ptr CCalendar -> CDate -> CDate -> CInt -> CInt -> Ptr CString -> IO CInt

-- |last business day of the month to which the given date belongs
endOfMonth :: Calendar s
  -> Day -- ^d
  -> QLE s Day
endOfMonth = $(ffiCallX 'endOfMonth) c_endOfMonth

foreign import ccall safe "ql.h qlCalendarEndOfMonth"
  c_endOfMonth :: Ptr CCalendar -> CDate -> Ptr CString -> IO CDate

-- |Returns true iff the date is a business day for the given market.
isBusinessDay :: Calendar s
  -> Day -- ^d
  -> QLE s Bool
isBusinessDay = $(ffiCallX 'isBusinessDay) c_isBusinessDay

foreign import ccall safe "ql.h qlCalendarIsBusinessDay"
  c_isBusinessDay :: Ptr CCalendar -> CDate -> Ptr CString -> IO CInt

-- |Returns true iff the date is last business day for the month in given market.
isEndOfMonth :: Calendar s
  -> Day -- ^d
  -> QLE s Bool
isEndOfMonth = $(ffiCallX 'isEndOfMonth) c_isEndOfMonth

foreign import ccall safe "ql.h qlCalendarIsEndOfMonth"
  c_isEndOfMonth :: Ptr CCalendar -> CDate -> Ptr CString -> IO CInt

-- |Returns true iff the date is a holiday for the given market.
isHoliday :: Calendar s
  -> Day -- ^d
  -> QLE s Bool
isHoliday = $(ffiCallX 'isHoliday) c_isHoliday

foreign import ccall safe "ql.h qlCalendarIsHoliday"
  c_isHoliday :: Ptr CCalendar -> CDate -> Ptr CString -> IO CInt

-- |Returns true iff the weekday is part of the weekend for the given market.
isWeekend :: Calendar s
  -> Weekday -- ^w
  -> QLE s Bool
isWeekend = $(ffiCallX 'isWeekend) c_isWeekend

foreign import ccall safe "ql.h qlCalendarIsWeekend"
  c_isWeekend :: Ptr CCalendar -> CInt -> Ptr CString -> IO CInt

-- |Removes a date from the set of holidays for the given calendar.
removeHoliday :: Calendar s -> Day -> QLE s ()
removeHoliday = $(ffiCallX 'removeHoliday) c_removeHoliday

foreign import ccall safe "ql.h qlCalendarRemoveHoliday"
  c_removeHoliday :: Ptr CCalendar -> CDate -> Ptr CString -> IO ()

-- |/Warning/ different bespoke calendars created with the same name (or different bespoke calendars created with no name) will compare as equal.
bespokeCalendar :: String -- ^name
  -> [Weekday] -- ^weekends
  -> QLE s (Calendar s)
bespokeCalendar = $(ffiCall 'bespokeCalendar) c_bespokeCalendar

foreign import ccall safe "ql.h qlBespokeCalendar"
  c_bespokeCalendar :: CString -> CUInt -> Ptr CInt -> Ptr CString -> IO (Ptr CCalendar)

jointCalendar3 :: Calendar s -> Calendar s -> Calendar s -> JointCalendarRule
  -> QLE s (Calendar s)
jointCalendar3 = $(ffiCall 'jointCalendar3) c_jointCalendar3

foreign import ccall safe "ql.h qlJointCalendar3"
  c_jointCalendar3 :: Ptr CCalendar -> Ptr CCalendar -> Ptr CCalendar -> CInt -> Ptr CString -> IO (Ptr CCalendar)

jointCalendar4 :: Calendar s -> Calendar s -> Calendar s
  -> Calendar s -> JointCalendarRule -> QLE s (Calendar s)
jointCalendar4 = $(ffiCall 'jointCalendar4) c_jointCalendar4

foreign import ccall safe "ql.h qlJointCalendar4"
  c_jointCalendar4 :: Ptr CCalendar -> Ptr CCalendar -> Ptr CCalendar -> Ptr CCalendar -> CInt -> Ptr CString -> IO (Ptr CCalendar)

jointCalendar2 :: Calendar s -> Calendar s -> JointCalendarRule -> QLE s (Calendar s)
jointCalendar2 = $(ffiCall 'jointCalendar2) c_jointCalendar2

foreign import ccall safe "ql.h qlJointCalendar2"
  c_jointCalendar2 :: Ptr CCalendar -> Ptr CCalendar -> CInt -> Ptr CString -> IO (Ptr CCalendar)

-- |Returns the holidays between two dates.
holidays :: Calendar s -- ^calendar
  -> Day -- ^from
  -> Day -- ^to
  -> Bool -- ^includeWeekEnds
  -> QLE s [Day]
holidays c from to w = mkQLE $
  map fromQlDate <$>
    withObject c
      (\cc -> do
        f <- toQlDate from
        t <- toQlDate to
        getArrayX $ c_holidayList cc f t (fromBool w))

foreign import ccall safe "ql.h qlCalendarHolidayList"
  c_holidayList :: Ptr CCalendar -> CDate -> CDate -> CInt -> Ptr CUInt -> Ptr CString -> IO (Ptr CDate)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
