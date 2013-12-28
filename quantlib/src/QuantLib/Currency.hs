{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Currency
  (
    ars
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
  , eur
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
  , peh
  , pei
  , pen
  , pkr
  , pln
  , pte
  , rol
  , ron
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

  , currency
  , code
  , format
  , fractionsPerUnit
  , fractionSymbol
  , numericCode
  , symbol
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

ars :: QLE s (Currency s) -- ^Argentinian peso
ats :: QLE s (Currency s) -- ^Austrian shilling
aud :: QLE s (Currency s) -- ^Australian dollar
bdt :: QLE s (Currency s) -- ^Bangladesh taka
bef :: QLE s (Currency s) -- ^Belgian franc
bgl :: QLE s (Currency s) -- ^Bulgarian lev
brl :: QLE s (Currency s) -- ^Brazilian real
byr :: QLE s (Currency s) -- ^Belarussian ruble
cad :: QLE s (Currency s) -- ^Canadian dollar
chf :: QLE s (Currency s) -- ^Swiss franc
clp :: QLE s (Currency s) -- ^Chilean peso
cny :: QLE s (Currency s) -- ^Chinese yuan
cop :: QLE s (Currency s) -- ^Colombian peso
cyp :: QLE s (Currency s) -- ^Cyprus pound
czk :: QLE s (Currency s) -- ^Czech koruna
dem :: QLE s (Currency s) -- ^Deutsche mark
dkk :: QLE s (Currency s) -- ^Danish krone
eek :: QLE s (Currency s) -- ^Estonian kroon
esp :: QLE s (Currency s) -- ^Spanish peseta
eur :: QLE s (Currency s) -- ^European Euro
fim :: QLE s (Currency s) -- ^Finnish markka
frf :: QLE s (Currency s) -- ^French franc
gbp :: QLE s (Currency s) -- ^British pound sterling
grd :: QLE s (Currency s) -- ^Greek drachma
hkd :: QLE s (Currency s) -- ^Honk Kong dollar
huf :: QLE s (Currency s) -- ^Hungarian forint
iep :: QLE s (Currency s) -- ^Irish punt
ils :: QLE s (Currency s) -- ^Israeli shekel
inr :: QLE s (Currency s) -- ^Indian rupee
iqd :: QLE s (Currency s) -- ^Iraqi dinar
irr :: QLE s (Currency s) -- ^Iranian rial
isk :: QLE s (Currency s) -- ^Icelandic krona
itl :: QLE s (Currency s) -- ^Italian lira
jpy :: QLE s (Currency s) -- ^Japanese yen
krw :: QLE s (Currency s) -- ^South-Korean won
kwd :: QLE s (Currency s) -- ^Kuwaiti dinar
ltl :: QLE s (Currency s) -- ^Lithuanian litas
luf :: QLE s (Currency s) -- ^Luxembourg franc
lvl :: QLE s (Currency s) -- ^Latvian lat
mtl :: QLE s (Currency s) -- ^Maltese lira
mxn :: QLE s (Currency s) -- ^Mexican peso
nlg :: QLE s (Currency s) -- ^Dutch guilder
nok :: QLE s (Currency s) -- ^Norwegian krone
npr :: QLE s (Currency s) -- ^Nepal rupee
nzd :: QLE s (Currency s) -- ^New Zealand dollar
peh :: QLE s (Currency s) -- ^Peruvian sol
pei :: QLE s (Currency s) -- ^Peruvian inti
pen :: QLE s (Currency s) -- ^Peruvian nuevo sol
pkr :: QLE s (Currency s) -- ^Pakistani rupee
pln :: QLE s (Currency s) -- ^Polish zloty
pte :: QLE s (Currency s) -- ^Portuguese escudo
rol :: QLE s (Currency s) -- ^Romanian leu
ron :: QLE s (Currency s) -- ^Romanian new leu
sar :: QLE s (Currency s) -- ^Saudi riyal
sek :: QLE s (Currency s) -- ^Swedish krona
sgd :: QLE s (Currency s) -- ^Singapore dollar
sit :: QLE s (Currency s) -- ^Slovenian tolar
skk :: QLE s (Currency s) -- ^Slovak koruna
thb :: QLE s (Currency s) -- ^Thai baht
trl :: QLE s (Currency s) -- ^Turkish lira
try :: QLE s (Currency s) -- ^New Turkish lira
ttd :: QLE s (Currency s) -- ^Trinidad & Tobago dollar
twd :: QLE s (Currency s) -- ^Taiwan dollar
usd :: QLE s (Currency s) -- ^U.S. dollar
veb :: QLE s (Currency s) -- ^Venezuelan bolivar
zar :: QLE s (Currency s) -- ^South-African rand

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
eur = constructNamed "EUR"
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
peh = constructNamed "PEH"
pei = constructNamed "PEI"
pen = constructNamed "PEN"
pkr = constructNamed "PKR"
pln = constructNamed "PLN"
pte = constructNamed "PTE"
rol = constructNamed "ROL"
ron = constructNamed "RON"
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

-- |ISO 4217 three-letter code, e.g, "USD".
code :: Currency s -> String
code = $(ffiCallPure 'code) c_code

foreign import ccall safe "ql.h qlCurrencyCode"
  c_code :: Ptr CCurrency -> IO CString

-- |output format
-- The format will be fed three positional parameters, namely, value, code, and symbol, in this order.
format :: Currency s -> String
format = $(ffiCallPure 'format) c_format

foreign import ccall safe "ql.h qlCurrencyFormat"
  c_format :: Ptr CCurrency -> IO CString

-- |number of fractionary parts in a unit, e.g, 100
fractionsPerUnit :: Currency s -> Int
fractionsPerUnit = $(ffiCallPure 'fractionsPerUnit) c_fractionsPerUnit

foreign import ccall safe "ql.h qlCurrencyFractionsPerUnit"
  c_fractionsPerUnit :: Ptr CCurrency -> IO CInt

-- |fraction symbol, e.g, "¢"
fractionSymbol :: Currency s -> String
fractionSymbol = $(ffiCallPure 'fractionSymbol) c_fractionSymbol

foreign import ccall safe "ql.h qlCurrencyFractionSymbol"
  c_fractionSymbol :: Ptr CCurrency -> IO CString

-- |ISO 4217 numeric code, e.g, "840".
numericCode :: Currency s -> Int
numericCode = $(ffiCallPure 'numericCode) c_numericCode

foreign import ccall safe "ql.h qlCurrencyNumericCode"
  c_numericCode :: Ptr CCurrency -> IO CInt

-- |symbol, e.g, "$"
symbol :: Currency s -> String
symbol = $(ffiCallPure 'symbol) c_symbol

foreign import ccall safe "ql.h qlCurrencySymbol"
  c_symbol :: Ptr CCurrency -> IO CString

-- |create custom currency
currency :: String -- ^name
  -> String -- ^code
  -> Int -- ^numericCode
  -> String -- ^symbol
  -> String -- ^fractionSymbol
  -> Int -- ^fractionsPerUnit
  -> Maybe (Rounding s) -- ^rounding
  -> String -- ^formatString
  -> Maybe (Currency s) -- ^triangulationCurrency
  -> QLE s (Currency s)
currency = $(ffiCall 'currency) c_currency

foreign import ccall safe "ql.h qlCreateCurrency"
  c_currency :: CString -> CString -> CInt -> CString -> CString -> CInt -> Ptr CRounding -> CString -> Ptr CCurrency -> Ptr CString -> IO (Ptr CCurrency)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
