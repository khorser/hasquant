{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Time.Calendar
  (
    Calendar
  , name

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
calendar cname = 
  withCString
    cname
    (\n -> construct $ c_calendar n)

name :: Calendar -> String
name c = unsafePerformIO
          $ withForeignPtr
              c
              (\cc -> do n <- c_calendarName cc
                         str <- peekCString n
                         c_freeString n
                         return str)

noCalendar::Calendar
noCalendar                    = unsafePerformIO $ calendar "NoCalendar"
nullCalendar::Calendar
nullCalendar                  = unsafePerformIO $ calendar "NullCalendar"
target::Calendar
target                        = unsafePerformIO $ calendar "TARGET"
argentinaMerval::Calendar
argentinaMerval              = unsafePerformIO $ calendar "Argentina::Merval"
australia::Calendar
australia                     = unsafePerformIO $ calendar "Australia"
brazilSettlement::Calendar
brazilSettlement             = unsafePerformIO $ calendar "Brazil::Settlement"
brazilExchange::Calendar
brazilExchange               = unsafePerformIO $ calendar "Brazil::Exchange"
canadaSettlement::Calendar
canadaSettlement             = unsafePerformIO $ calendar "Canada::Settlement"
canadaTSX::Calendar
canadaTSX                    = unsafePerformIO $ calendar "Canada::TSX"
china::Calendar
china                         = unsafePerformIO $ calendar "China"
czechRepublicPSE::Calendar
czechRepublicPSE             = unsafePerformIO $ calendar "CzechRepublic::PSE"
denmark::Calendar
denmark                       = unsafePerformIO $ calendar "Denmark"
finland::Calendar
finland                       = unsafePerformIO $ calendar "Finland"
germanyEurex::Calendar
germanyEurex                 = unsafePerformIO $ calendar "Germany::Eurex"
germanyFrankfurtStockExchange::Calendar
germanyFrankfurtStockExchange= unsafePerformIO $ calendar "Germany::FrankfurtStockExchange"
germanySettlement::Calendar
germanySettlement            = unsafePerformIO $ calendar "Germany::Settlement"
germanyXetra::Calendar
germanyXetra                 = unsafePerformIO $ calendar "Germany::Xetra"
hongKongHKEx::Calendar
hongKongHKEx                 = unsafePerformIO $ calendar "HongKong::HKEx"
hungary::Calendar
hungary                       = unsafePerformIO $ calendar "Hungary"
icelandICEX::Calendar
icelandICEX                  = unsafePerformIO $ calendar "Iceland::ICEX"
indiaNSE::Calendar
indiaNSE                     = unsafePerformIO $ calendar "India::NSE"
indonesiaBEJ::Calendar
indonesiaBEJ                 = unsafePerformIO $ calendar "Indonesia::BEJ"
indonesiaJSX::Calendar
indonesiaJSX                 = unsafePerformIO $ calendar "Indonesia::JSX"
italyExchange::Calendar
italyExchange                = unsafePerformIO $ calendar "Italy::Exchange"
italySettlement::Calendar
italySettlement              = unsafePerformIO $ calendar "Italy::Settlement"
japan::Calendar
japan                         = unsafePerformIO $ calendar "Japan"
mexicoBMV::Calendar
mexicoBMV                    = unsafePerformIO $ calendar "Mexico::BMV"
newZealand::Calendar
newZealand                    = unsafePerformIO $ calendar "NewZealand"
norway::Calendar
norway                        = unsafePerformIO $ calendar "Norway"
poland::Calendar
poland                        = unsafePerformIO $ calendar "Poland"
russia::Calendar
russia                        = unsafePerformIO $ calendar "Russia"
saudiArabiaTadawul::Calendar
saudiArabiaTadawul           = unsafePerformIO $ calendar "SaudiArabia::Tadawul"
singaporeSGX::Calendar
singaporeSGX                 = unsafePerformIO $ calendar "Singapore::SGX"
slovakiaBSSE::Calendar
slovakiaBSSE                 = unsafePerformIO $ calendar "Slovakia::BSSE"
southAfrica::Calendar
southAfrica                   = unsafePerformIO $ calendar "SouthAfrica"
southKoreaKRX::Calendar
southKoreaKRX                = unsafePerformIO $ calendar "SouthKorea::KRX"
sweden::Calendar
sweden                        = unsafePerformIO $ calendar "Sweden"
switzerland::Calendar
switzerland                   = unsafePerformIO $ calendar "Switzerland"
taiwanTSEC::Calendar
taiwanTSEC                   = unsafePerformIO $ calendar "Taiwan::TSEC"
eur::Calendar
eur                           = unsafePerformIO $ calendar "EUR"
turkey::Calendar
turkey                        = unsafePerformIO $ calendar "Turkey"
ukraineUSE::Calendar
ukraineUSE                   = unsafePerformIO $ calendar "Ukraine::USE"
unitedKingdomExchange::Calendar
unitedKingdomExchange        = unsafePerformIO $ calendar "UnitedKingdom::Exchange"
londonStockExchange::Calendar
londonStockExchange         = unsafePerformIO $ calendar "London stock exchange"
london::Calendar
london                        = unsafePerformIO $ calendar "LONDON"
gbp::Calendar
gbp                           = unsafePerformIO $ calendar "GBP"
unitedKingdomMetals::Calendar
unitedKingdomMetals          = unsafePerformIO $ calendar "UnitedKingdom::Metals"
unitedKingdomSettlement::Calendar
unitedKingdomSettlement      = unsafePerformIO $ calendar "UnitedKingdom::Settlement"
unitedStatesGovernmentBond::Calendar
unitedStatesGovernmentBond   = unsafePerformIO $ calendar "UnitedStates::GovernmentBond"
unitedStatesNERC::Calendar
unitedStatesNERC             = unsafePerformIO $ calendar "UnitedStates::NERC"
unitedStatesNYSE::Calendar
unitedStatesNYSE             = unsafePerformIO $ calendar "UnitedStates::NYSE"
unitedStatesSettlement::Calendar
unitedStatesSettlement       = unsafePerformIO $ calendar "UnitedStates::Settlement"
