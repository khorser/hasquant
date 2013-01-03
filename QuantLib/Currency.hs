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

import Foreign.C.String(CString)
import Foreign.ForeignPtr(ForeignPtr)
import Foreign.Ptr(Ptr, FunPtr)

import QuantLib.Internal(Finalizable, finalize, c_construct, NamedSingleton, c_name, name, constructNamed)

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

instance NamedSingleton CCurrency
  where c_construct = c_currency
        c_name = c_currencyName

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

currency  = constructNamed "Currency"
noCurrency= constructNamed "NoCurrency"
eur = constructNamed "EUR"
ars = constructNamed "ARS"
ats = constructNamed "ATS"
aud = constructNamed "AUD"
bdt = constructNamed "BDT"
bef = constructNamed "BEF"
bgl = constructNamed "BGL"
brl = constructNamed "BRL"
byr = constructNamed "BYR"
cad = constructNamed "CAD"
chf = constructNamed "CHF"
clp = constructNamed "CLP"
cny = constructNamed "CNY"
cop = constructNamed "COP"
cyp = constructNamed "CYP"
czk = constructNamed "CZK"
dem = constructNamed "DEM"
dkk = constructNamed "DKK"
eek = constructNamed "EEK"
esp = constructNamed "ESP"
fim = constructNamed "FIM"
frf = constructNamed "FRF"
gbp = constructNamed "GBP"
grd = constructNamed "GRD"
hkd = constructNamed "HKD"
huf = constructNamed "HUF"
iep = constructNamed "IEP"
ils = constructNamed "ILS"
inr = constructNamed "INR"
iqd = constructNamed "IQD"
irr = constructNamed "IRR"
isk = constructNamed "ISK"
itl = constructNamed "ITL"
jpy = constructNamed "JPY"
krw = constructNamed "KRW"
kwd = constructNamed "KWD"
ltl = constructNamed "LTL"
luf = constructNamed "LUF"
lvl = constructNamed "LVL"
mtl = constructNamed "MTL"
mxn = constructNamed "MXN"
nlg = constructNamed "NLG"
nok = constructNamed "NOK"
npr = constructNamed "NPR"
nzd = constructNamed "NZD"
pkr = constructNamed "PKR"
pln = constructNamed "PLN"
pte = constructNamed "PTE"
rol = constructNamed "ROL"
sar = constructNamed "SAR"
sek = constructNamed "SEK"
sgd = constructNamed "SGD"
sit = constructNamed "SIT"
skk = constructNamed "SKK"
thb = constructNamed "THB"
trl = constructNamed "TRL"
try = constructNamed "TRY"
ttd = constructNamed "TTD"
twd = constructNamed "TWD"
usd = constructNamed "USD"
veb = constructNamed "VEB"
zar = constructNamed "ZAR"
