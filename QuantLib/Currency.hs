{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Currency
  (
    CCurrency
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
import Foreign.Ptr(Ptr, FunPtr)

import QuantLib.Internal(Object, Finalizable, finalize, c_construct, NamedSingleton, c_name, name, constructNamed)

data CCurrency

type Currency = Object CCurrency

foreign import ccall safe "ql.h qlCurrency"
  c_currency :: CString -> Ptr CString -> IO (Ptr CCurrency)
foreign import ccall safe "ql.h &qlFreeCurrency"
  p_freeCurrency :: FunPtr (Ptr CCurrency -> IO ())
foreign import ccall safe "ql.h qlCurrencyName"
  c_currencyName :: Ptr CCurrency -> IO CString

instance Finalizable CCurrency where
  finalize = p_freeCurrency

instance NamedSingleton CCurrency where
  c_construct = c_currency
  c_name = c_currencyName

-- TODO add data Currency = ...

currency :: IO Currency
noCurrency :: IO Currency
eur :: IO Currency
ars :: IO Currency
ats :: IO Currency
aud :: IO Currency
bdt :: IO Currency
bef :: IO Currency
bgl :: IO Currency
brl :: IO Currency
byr :: IO Currency
cad :: IO Currency
chf :: IO Currency
clp :: IO Currency
cny :: IO Currency
cop :: IO Currency
cyp :: IO Currency
czk :: IO Currency
dem :: IO Currency
dkk :: IO Currency
eek :: IO Currency
esp :: IO Currency
fim :: IO Currency
frf :: IO Currency
gbp :: IO Currency
grd :: IO Currency
hkd :: IO Currency
huf :: IO Currency
iep :: IO Currency
ils :: IO Currency
inr :: IO Currency
iqd :: IO Currency
irr :: IO Currency
isk :: IO Currency
itl :: IO Currency
jpy :: IO Currency
krw :: IO Currency
kwd :: IO Currency
ltl :: IO Currency
luf :: IO Currency
lvl :: IO Currency
mtl :: IO Currency
mxn :: IO Currency
nlg :: IO Currency
nok :: IO Currency
npr :: IO Currency
nzd :: IO Currency
pkr :: IO Currency
pln :: IO Currency
pte :: IO Currency
rol :: IO Currency
sar :: IO Currency
sek :: IO Currency
sgd :: IO Currency
sit :: IO Currency
skk :: IO Currency
thb :: IO Currency
trl :: IO Currency
try :: IO Currency
ttd :: IO Currency
twd :: IO Currency
usd :: IO Currency
veb :: IO Currency
zar :: IO Currency

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
