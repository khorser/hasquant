module QuantLib.Currency
  (
  -- makers
    currency
  , noCurrency
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
  )
where

import QuantLib.Internal.Utils
import QuantLib.Types

-- TODO add data Currency = ...

currency :: IO Currency
noCurrency :: IO Currency
ars :: IO Currency -- ^Argentinian peso
ats :: IO Currency -- ^Austrian shilling
aud :: IO Currency -- ^Australian dollar
bdt :: IO Currency -- ^Bangladesh taka
bef :: IO Currency -- ^Belgian franc
bgl :: IO Currency -- ^Bulgarian lev
brl :: IO Currency -- ^Brazilian real
byr :: IO Currency -- ^Belarussian ruble
cad :: IO Currency -- ^Canadian dollar
chf :: IO Currency -- ^Swiss franc
clp :: IO Currency -- ^Chilean peso
cny :: IO Currency -- ^Chinese yuan
cop :: IO Currency -- ^Colombian peso
cyp :: IO Currency -- ^Cyprus pound
czk :: IO Currency -- ^Czech koruna
dem :: IO Currency -- ^Deutsche mark
dkk :: IO Currency -- ^Danish krone
eek :: IO Currency -- ^Estonian kroon
esp :: IO Currency -- ^Spanish peseta
eur :: IO Currency -- ^European Euro
fim :: IO Currency -- ^Finnish markka
frf :: IO Currency -- ^French franc
gbp :: IO Currency -- ^British pound sterling
grd :: IO Currency -- ^Greek drachma
hkd :: IO Currency -- ^Honk Kong dollar
huf :: IO Currency -- ^Hungarian forint
iep :: IO Currency -- ^Irish punt
ils :: IO Currency -- ^Israeli shekel
inr :: IO Currency -- ^Indian rupee
iqd :: IO Currency -- ^Iraqi dinar
irr :: IO Currency -- ^Iranian rial
isk :: IO Currency -- ^Icelandic krona
itl :: IO Currency -- ^Italian lira
jpy :: IO Currency -- ^Japanese yen
krw :: IO Currency -- ^South-Korean won
kwd :: IO Currency -- ^Kuwaiti dinar
ltl :: IO Currency -- ^Lithuanian litas
luf :: IO Currency -- ^Luxembourg franc
lvl :: IO Currency -- ^Latvian lat
mtl :: IO Currency -- ^Maltese lira
mxn :: IO Currency -- ^Mexican peso
nlg :: IO Currency -- ^Dutch guilder
nok :: IO Currency -- ^Norwegian krone
npr :: IO Currency -- ^Nepal rupee
nzd :: IO Currency -- ^New Zealand dollar
peh :: IO Currency -- ^Peruvian sol
pei :: IO Currency -- ^Peruvian inti
pen :: IO Currency -- ^Peruvian nuevo sol
pkr :: IO Currency -- ^Pakistani rupee
pln :: IO Currency -- ^Polish zloty
pte :: IO Currency -- ^Portuguese escudo
rol :: IO Currency -- ^Romanian leu
ron :: IO Currency -- ^Romanian new leu
sar :: IO Currency -- ^Saudi riyal
sek :: IO Currency -- ^Swedish krona
sgd :: IO Currency -- ^Singapore dollar
sit :: IO Currency -- ^Slovenian tolar
skk :: IO Currency -- ^Slovak koruna
thb :: IO Currency -- ^Thai baht
trl :: IO Currency -- ^Turkish lira
try :: IO Currency -- ^New Turkish lira
ttd :: IO Currency -- ^Trinidad & Tobago dollar
twd :: IO Currency -- ^Taiwan dollar
usd :: IO Currency -- ^U.S. dollar
veb :: IO Currency -- ^Venezuelan bolivar
zar :: IO Currency -- ^South-African rand

currency  = constructNamed "Currency"
noCurrency= constructNamed "NoCurrency"
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
