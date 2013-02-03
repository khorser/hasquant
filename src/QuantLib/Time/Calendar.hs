{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Time.Calendar
  (
  -- accessors
    adjust
  , advance
  -- makers
  , noCalendar
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
  , eur
  , turkey
  , ukraineUSE
  , londonStockExchange
  , london
  , gbp
  , unitedKingdomMetals
  , unitedKingdomSettlement
  , unitedStatesGovernmentBond
  , unitedStatesNERC
  , unitedStatesNYSE
  , unitedStatesSettlement
  , weekendsOnly
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Unit(Unit)

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

-- TODO add data Calendar = ...

-- NB Calendars in QuantLib are sort of singletons: if you add
-- a holiday to QuantLib::Russia, it will be added to all instances
-- of the calendar
-- Luckily this doesn't apply to joint calendars
-- but there is another drawback: the name of a joint calendar is
-- the concatenation of its components so == will return TRUE
-- even while holidays might be different
-- Later it might be worthwhile to create a calendar that will call back Haskell
-- for actual implementation
-- Or we could use BespokeCalendar

noCalendar              :: IO Calendar
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
eur                     :: IO Calendar -- ^TARGET
turkey                  :: IO Calendar -- ^Turkish calendar
ukraineUSE              :: IO Calendar -- ^Ukrainian calendar: Ukrainian stock exchange
unitedKingdomExchange   :: IO Calendar -- ^United Kingdom calendar: London stock-exchange
londonStockExchange     :: IO Calendar -- ^United Kingdom calendar: London stock exchange
london                  :: IO Calendar -- ^United Kingdom calendar: London stock exchange
unitedKingdomMetals     :: IO Calendar -- ^United Kingdom calendar: London metal exchange
unitedKingdomSettlement :: IO Calendar -- ^United Kingdom calendar: generic settlement
gbp                     :: IO Calendar -- ^London Stock Exchange
unitedStatesGovernmentBond:: IO Calendar -- ^United States calendar: government-bond
unitedStatesNERC        :: IO Calendar -- ^United States calendar: off-peak days for NERC
unitedStatesNYSE        :: IO Calendar -- ^United States calendar: New York stock exchange
unitedStatesSettlement  :: IO Calendar -- ^United States calendar: generic settlement
-- |Weekends-only calendar.
-- This calendar has no bank holidays except for weekends (Saturdays and Sundays) as required by ISDA for calculating conventional CDS spreads.
weekendsOnly            :: IO Calendar

noCalendar              = constructNamed "NoCalendar"
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
eur                     = constructNamed "EUR"
turkey                  = constructNamed "Turkey"
ukraineUSE              = constructNamed "Ukraine::USE"
unitedKingdomExchange   = constructNamed "UnitedKingdom::Exchange"
londonStockExchange     = constructNamed "London stock exchange"
london                  = constructNamed "LONDON"
gbp                     = constructNamed "GBP"
unitedKingdomMetals     = constructNamed "UnitedKingdom::Metals"
unitedKingdomSettlement = constructNamed "UnitedKingdom::Settlement"
unitedStatesGovernmentBond = constructNamed "UnitedStates::GovernmentBond"
unitedStatesNERC        = constructNamed "UnitedStates::NERC"
unitedStatesNYSE        = constructNamed "UnitedStates::NYSE"
unitedStatesSettlement  = constructNamed "UnitedStates::Settlement"
weekendsOnly            = constructNamed "WeekendsOnly"
