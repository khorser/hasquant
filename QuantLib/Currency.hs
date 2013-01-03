{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Currency
  (
    CCurrency
  , name
  , Currency

  , currency
  , noCurrency
  , eur
  , ars
  , ats
  , aud
  , bdt
  , bef
  , bgl
  , brl
  , byr
  , cad
  , chf
  , clp
  , cny
  , cop
  , cyp
  , czk
  , dem
  , dkk
  , eek
  , esp
  , fim
  , frf
  , gbp
  , grd
  , hkd
  , huf
  , iep
  , ils
  , inr
  , iqd
  , irr
  , isk
  , itl
  , jpy
  , krw
  , kwd
  , ltl
  , luf
  , lvl
  , mtl
  , mxn
  , nlg
  , nok
  , npr
  , nzd
  , pkr
  , pln
  , pte
  , rol
  , sar
  , sek
  , sgd
  , sit
  , skk
  , thb
  , trl
  , try
  , ttd
  , twd
  , usd
  , veb
  , zar
  )
where

import Foreign.C.String(withCString, CString, peekCString)
import Foreign.ForeignPtr(ForeignPtr, withForeignPtr)
import Foreign.Ptr(Ptr, FunPtr)

import QuantLib.Internal(c_freeString, Finalizable, finalize, construct)

import System.IO.Unsafe(unsafePerformIO)

data CCurrency

type Currency = ForeignPtr CCurrency

foreign import ccall safe "ql.h qlCurrency"
    c_currency :: CString -> Ptr CString -> IO (Ptr CCurrency)
foreign import ccall safe "ql.h &qlFreeCurrency"
    p_freeCurrency :: FunPtr (Ptr CCurrency -> IO ())
foreign import ccall safe "ql.h qlCurrencyName"
    c_currencyName :: Ptr CCurrency -> IO CString

instance Finalizable CCurrency
  where finalize = p_freeCurrency

constructCurrency :: String -> IO Currency
constructCurrency cname = withCString cname $ construct . c_currency

name :: Currency -> String
name c = unsafePerformIO
          $ withForeignPtr
              c
              (\cc -> do n <- c_currencyName cc
                         str <- peekCString n
                         c_freeString n
                         return str)

-- TODO add data Currency = ...

currency :: Currency
noCurrency :: Currency
eur :: Currency
ars :: Currency
ats :: Currency
aud :: Currency
bdt :: Currency
bef :: Currency
bgl :: Currency
brl :: Currency
byr :: Currency
cad :: Currency
chf :: Currency
clp :: Currency
cny :: Currency
cop :: Currency
cyp :: Currency
czk :: Currency
dem :: Currency
dkk :: Currency
eek :: Currency
esp :: Currency
fim :: Currency
frf :: Currency
gbp :: Currency
grd :: Currency
hkd :: Currency
huf :: Currency
iep :: Currency
ils :: Currency
inr :: Currency
iqd :: Currency
irr :: Currency
isk :: Currency
itl :: Currency
jpy :: Currency
krw :: Currency
kwd :: Currency
ltl :: Currency
luf :: Currency
lvl :: Currency
mtl :: Currency
mxn :: Currency
nlg :: Currency
nok :: Currency
npr :: Currency
nzd :: Currency
pkr :: Currency
pln :: Currency
pte :: Currency
rol :: Currency
sar :: Currency
sek :: Currency
sgd :: Currency
sit :: Currency
skk :: Currency
thb :: Currency
trl :: Currency
try :: Currency
ttd :: Currency
twd :: Currency
usd :: Currency
veb :: Currency
zar :: Currency

currency  = unsafePerformIO $ constructCurrency "Currency"
noCurrency= unsafePerformIO $ constructCurrency "NoCurrency"
eur = unsafePerformIO $ constructCurrency "EUR"
ars = unsafePerformIO $ constructCurrency "ARS"
ats = unsafePerformIO $ constructCurrency "ATS"
aud = unsafePerformIO $ constructCurrency "AUD"
bdt = unsafePerformIO $ constructCurrency "BDT"
bef = unsafePerformIO $ constructCurrency "BEF"
bgl = unsafePerformIO $ constructCurrency "BGL"
brl = unsafePerformIO $ constructCurrency "BRL"
byr = unsafePerformIO $ constructCurrency "BYR"
cad = unsafePerformIO $ constructCurrency "CAD"
chf = unsafePerformIO $ constructCurrency "CHF"
clp = unsafePerformIO $ constructCurrency "CLP"
cny = unsafePerformIO $ constructCurrency "CNY"
cop = unsafePerformIO $ constructCurrency "COP"
cyp = unsafePerformIO $ constructCurrency "CYP"
czk = unsafePerformIO $ constructCurrency "CZK"
dem = unsafePerformIO $ constructCurrency "DEM"
dkk = unsafePerformIO $ constructCurrency "DKK"
eek = unsafePerformIO $ constructCurrency "EEK"
esp = unsafePerformIO $ constructCurrency "ESP"
fim = unsafePerformIO $ constructCurrency "FIM"
frf = unsafePerformIO $ constructCurrency "FRF"
gbp = unsafePerformIO $ constructCurrency "GBP"
grd = unsafePerformIO $ constructCurrency "GRD"
hkd = unsafePerformIO $ constructCurrency "HKD"
huf = unsafePerformIO $ constructCurrency "HUF"
iep = unsafePerformIO $ constructCurrency "IEP"
ils = unsafePerformIO $ constructCurrency "ILS"
inr = unsafePerformIO $ constructCurrency "INR"
iqd = unsafePerformIO $ constructCurrency "IQD"
irr = unsafePerformIO $ constructCurrency "IRR"
isk = unsafePerformIO $ constructCurrency "ISK"
itl = unsafePerformIO $ constructCurrency "ITL"
jpy = unsafePerformIO $ constructCurrency "JPY"
krw = unsafePerformIO $ constructCurrency "KRW"
kwd = unsafePerformIO $ constructCurrency "KWD"
ltl = unsafePerformIO $ constructCurrency "LTL"
luf = unsafePerformIO $ constructCurrency "LUF"
lvl = unsafePerformIO $ constructCurrency "LVL"
mtl = unsafePerformIO $ constructCurrency "MTL"
mxn = unsafePerformIO $ constructCurrency "MXN"
nlg = unsafePerformIO $ constructCurrency "NLG"
nok = unsafePerformIO $ constructCurrency "NOK"
npr = unsafePerformIO $ constructCurrency "NPR"
nzd = unsafePerformIO $ constructCurrency "NZD"
pkr = unsafePerformIO $ constructCurrency "PKR"
pln = unsafePerformIO $ constructCurrency "PLN"
pte = unsafePerformIO $ constructCurrency "PTE"
rol = unsafePerformIO $ constructCurrency "ROL"
sar = unsafePerformIO $ constructCurrency "SAR"
sek = unsafePerformIO $ constructCurrency "SEK"
sgd = unsafePerformIO $ constructCurrency "SGD"
sit = unsafePerformIO $ constructCurrency "SIT"
skk = unsafePerformIO $ constructCurrency "SKK"
thb = unsafePerformIO $ constructCurrency "THB"
trl = unsafePerformIO $ constructCurrency "TRL"
try = unsafePerformIO $ constructCurrency "TRY"
ttd = unsafePerformIO $ constructCurrency "TTD"
twd = unsafePerformIO $ constructCurrency "TWD"
usd = unsafePerformIO $ constructCurrency "USD"
veb = unsafePerformIO $ constructCurrency "VEB"
zar = unsafePerformIO $ constructCurrency "ZAR"
