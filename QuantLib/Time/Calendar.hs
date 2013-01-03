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

import Foreign.C.String(withCString, CString, peekCString)
import Foreign.ForeignPtr(ForeignPtr, withForeignPtr)
import Foreign.Ptr(Ptr, FunPtr)

import QuantLib.Internal(c_freeString, Finalizable, finalize, construct)

import System.IO.Unsafe(unsafePerformIO)

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

calendar :: String -> IO Calendar
calendar cname = withCString cname $ construct . c_calendar
name :: Calendar -> String
name c = unsafePerformIO
          $ withForeignPtr
              c
              (\cc -> do n <- c_calendarName cc
                         str <- peekCString n
                         c_freeString n
                         return str)

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

noCalendar              = unsafePerformIO $ calendar "NoCalendar"
nullCalendar            = unsafePerformIO $ calendar "NullCalendar"
target                  = unsafePerformIO $ calendar "TARGET"
argentinaMerval         = unsafePerformIO $ calendar "Argentina::Merval"
australia               = unsafePerformIO $ calendar "Australia"
brazilSettlement        = unsafePerformIO $ calendar "Brazil::Settlement"
brazilExchange          = unsafePerformIO $ calendar "Brazil::Exchange"
canadaSettlement        = unsafePerformIO $ calendar "Canada::Settlement"
canadaTSX               = unsafePerformIO $ calendar "Canada::TSX"
china                   = unsafePerformIO $ calendar "China"
czechRepublicPSE        = unsafePerformIO $ calendar "CzechRepublic::PSE"
denmark                 = unsafePerformIO $ calendar "Denmark"
finland                 = unsafePerformIO $ calendar "Finland"
germanyEurex            = unsafePerformIO $ calendar "Germany::Eurex"
germanyFrankfurtStockExchange = unsafePerformIO $ calendar "Germany::FrankfurtStockExchange"
germanySettlement       = unsafePerformIO $ calendar "Germany::Settlement"
germanyXetra            = unsafePerformIO $ calendar "Germany::Xetra"
hongKongHKEx            = unsafePerformIO $ calendar "HongKong::HKEx"
hungary                 = unsafePerformIO $ calendar "Hungary"
icelandICEX             = unsafePerformIO $ calendar "Iceland::ICEX"
indiaNSE                = unsafePerformIO $ calendar "India::NSE"
indonesiaBEJ            = unsafePerformIO $ calendar "Indonesia::BEJ"
indonesiaJSX            = unsafePerformIO $ calendar "Indonesia::JSX"
italyExchange           = unsafePerformIO $ calendar "Italy::Exchange"
italySettlement         = unsafePerformIO $ calendar "Italy::Settlement"
japan                   = unsafePerformIO $ calendar "Japan"
mexicoBMV               = unsafePerformIO $ calendar "Mexico::BMV"
newZealand              = unsafePerformIO $ calendar "NewZealand"
norway                  = unsafePerformIO $ calendar "Norway"
poland                  = unsafePerformIO $ calendar "Poland"
russia                  = unsafePerformIO $ calendar "Russia"
saudiArabiaTadawul      = unsafePerformIO $ calendar "SaudiArabia::Tadawul"
singaporeSGX            = unsafePerformIO $ calendar "Singapore::SGX"
slovakiaBSSE            = unsafePerformIO $ calendar "Slovakia::BSSE"
southAfrica             = unsafePerformIO $ calendar "SouthAfrica"
southKoreaKRX           = unsafePerformIO $ calendar "SouthKorea::KRX"
sweden                  = unsafePerformIO $ calendar "Sweden"
switzerland             = unsafePerformIO $ calendar "Switzerland"
taiwanTSEC              = unsafePerformIO $ calendar "Taiwan::TSEC"
eur                     = unsafePerformIO $ calendar "EUR"
turkey                  = unsafePerformIO $ calendar "Turkey"
ukraineUSE              = unsafePerformIO $ calendar "Ukraine::USE"
unitedKingdomExchange   = unsafePerformIO $ calendar "UnitedKingdom::Exchange"
londonStockExchange     = unsafePerformIO $ calendar "London stock exchange"
london                  = unsafePerformIO $ calendar "LONDON"
gbp                     = unsafePerformIO $ calendar "GBP"
unitedKingdomMetals     = unsafePerformIO $ calendar "UnitedKingdom::Metals"
unitedKingdomSettlement = unsafePerformIO $ calendar "UnitedKingdom::Settlement"
unitedStatesGovernmentBond = unsafePerformIO $ calendar "UnitedStates::GovernmentBond"
unitedStatesNERC        = unsafePerformIO $ calendar "UnitedStates::NERC"
unitedStatesNYSE        = unsafePerformIO $ calendar "UnitedStates::NYSE"
unitedStatesSettlement  = unsafePerformIO $ calendar "UnitedStates::Settlement"
