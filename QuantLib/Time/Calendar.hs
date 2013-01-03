{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Time.Calendar
  (
    Calendar
  , name
  , CCalendar

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

import Foreign.C.String(CString)
import Foreign.ForeignPtr(ForeignPtr)
import Foreign.Ptr(Ptr, FunPtr)

import QuantLib.Internal(Finalizable, finalize, c_construct, NamedSingleton, c_name, name, constructNamed)

data CCalendar

type Calendar = ForeignPtr CCalendar

foreign import ccall safe "ql.h qlCalendar"
    c_calendar :: CString -> Ptr CString -> IO (Ptr CCalendar)
foreign import ccall safe "ql.h &qlFreeCalendar"
    p_freeCalendar :: FunPtr (Ptr CCalendar -> IO ())
foreign import ccall safe "ql.h qlCalendarName"
    c_calendarName :: Ptr CCalendar -> IO CString

instance Finalizable CCalendar
  where finalize = p_freeCalendar

instance NamedSingleton CCalendar
  where c_construct = c_calendar
        c_name = c_calendarName

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

noCalendar              ::Calendar
nullCalendar            ::Calendar
target                  ::Calendar
argentinaMerval         ::Calendar
australia               ::Calendar
brazilSettlement        ::Calendar
brazilExchange          ::Calendar
canadaSettlement        ::Calendar
canadaTSX               ::Calendar
china                   ::Calendar
czechRepublicPSE        ::Calendar
denmark                 ::Calendar
finland                 ::Calendar
germanyEurex            ::Calendar
germanyFrankfurtStockExchange ::Calendar
germanySettlement       ::Calendar
germanyXetra            ::Calendar
hongKongHKEx            ::Calendar
hungary                 ::Calendar
icelandICEX             ::Calendar
indiaNSE                ::Calendar
indonesiaBEJ            ::Calendar
indonesiaJSX            ::Calendar
italyExchange           ::Calendar
italySettlement         ::Calendar
japan                   ::Calendar
mexicoBMV               ::Calendar
newZealand              ::Calendar
norway                  ::Calendar
poland                  ::Calendar
russia                  ::Calendar
saudiArabiaTadawul      ::Calendar
singaporeSGX            ::Calendar
slovakiaBSSE            ::Calendar
southAfrica             ::Calendar
southKoreaKRX           ::Calendar
sweden                  ::Calendar
switzerland             ::Calendar
taiwanTSEC              ::Calendar
eur                     ::Calendar
turkey                  ::Calendar
ukraineUSE              ::Calendar
unitedKingdomExchange   ::Calendar
londonStockExchange     ::Calendar
london                  ::Calendar
gbp                     ::Calendar
unitedKingdomMetals     ::Calendar
unitedKingdomSettlement ::Calendar
unitedStatesGovernmentBond::Calendar
unitedStatesNERC        ::Calendar
unitedStatesNYSE        ::Calendar
unitedStatesSettlement  ::Calendar

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
