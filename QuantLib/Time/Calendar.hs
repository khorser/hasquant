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
  , sweden
  , switzerland
  , taiwanTSEC
  , eur
  , turkey
  , ukraineUSE
  , unitedKingdomExchange
  , londonStockExchange
  , london
  , gbp
  , unitedKingdomMetals
  , unitedKingdomSettlement
  , unitedStatesGovernmentBond
  , unitedStatesNERC
  , unitedStatesNYSE
  , unitedStatesSettlement
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.Time.BusinessDayConvention(BusinessDayConvention)
import QuantLib.Time.Unit(Unit)

foreign import ccall safe "ql.h qlCalendarAdjust"
  c_calendarAdjust :: Ptr CCalendar -> CDate -> CInt -> IO CDate
foreign import ccall safe "ql.h qlCalendarAdvance"
  c_calendarAdvance :: Ptr CCalendar -> CDate -> CInt -> CInt -> CInt -> CInt -> IO CDate

-- |Adjusts a non-business day to the appropriate near business day according to a given calendar with respect to the given convention (qlCalendarAdjust)
adjust :: Calendar -> Day -> BusinessDayConvention -> IO Day
adjust = $(ffiCall 'adjust 'c_calendarAdjust)

-- |advances a date according to a given calendar (qlCalendarAdvance)
advance :: Calendar -> Day -> Int -> Unit -> BusinessDayConvention -> Bool -> IO Day
advance = $(ffiCall 'advance 'c_calendarAdvance)

-- TODO add data Calendar = ...

-- NB Calendars in QuantLib are sort of singletons: if you add
-- a holiday to QuantLib::Russia, it will be added to all instances
-- of the calendar
-- Luckily this doesn't apply to joint calendars
-- but there is another drawback: the name of a joint calendar is
-- the concatenation of its components so == will return TRUE
-- even while holidays might be different
-- Also we can create a calendar that will call back Haskell
-- for actual implementation

noCalendar              :: IO Calendar
nullCalendar            :: IO Calendar
target                  :: IO Calendar
argentinaMerval         :: IO Calendar
australia               :: IO Calendar
brazilSettlement        :: IO Calendar
brazilExchange          :: IO Calendar
canadaSettlement        :: IO Calendar
canadaTSX               :: IO Calendar
china                   :: IO Calendar
czechRepublicPSE        :: IO Calendar
denmark                 :: IO Calendar
finland                 :: IO Calendar
germanyEurex            :: IO Calendar
germanyFrankfurtStockExchange :: IO Calendar
germanySettlement       :: IO Calendar
germanyXetra            :: IO Calendar
hongKongHKEx            :: IO Calendar
hungary                 :: IO Calendar
icelandICEX             :: IO Calendar
indiaNSE                :: IO Calendar
indonesiaBEJ            :: IO Calendar
indonesiaJSX            :: IO Calendar
italyExchange           :: IO Calendar
italySettlement         :: IO Calendar
japan                   :: IO Calendar
mexicoBMV               :: IO Calendar
newZealand              :: IO Calendar
norway                  :: IO Calendar
poland                  :: IO Calendar
russia                  :: IO Calendar
saudiArabiaTadawul      :: IO Calendar
singaporeSGX            :: IO Calendar
slovakiaBSSE            :: IO Calendar
southAfrica             :: IO Calendar
southKoreaKRX           :: IO Calendar
sweden                  :: IO Calendar
switzerland             :: IO Calendar
taiwanTSEC              :: IO Calendar
eur                     :: IO Calendar
turkey                  :: IO Calendar
ukraineUSE              :: IO Calendar
unitedKingdomExchange   :: IO Calendar
londonStockExchange     :: IO Calendar
london                  :: IO Calendar
gbp                     :: IO Calendar
unitedKingdomMetals     :: IO Calendar
unitedKingdomSettlement :: IO Calendar
unitedStatesGovernmentBond:: IO Calendar
unitedStatesNERC        :: IO Calendar
unitedStatesNYSE        :: IO Calendar
unitedStatesSettlement  :: IO Calendar

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
