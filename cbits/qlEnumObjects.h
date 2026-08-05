// Enumerations to be mapped to specific QuantLib classes
// must match with the order of qlMisc.cpp:ccys
enum Ccy {ARS = 0
  , ATS
  , AUD
  , BCH
  , BDT
  , BEF
  , BGL
  , BRL
  , BTC
  , BYR
  , CAD
  , CHF
  , CLP
  , CNY
  , COP
  , CYP
  , CZK
  , DASH
  , DEM
  , DKK
  , EEK
  , ESP
  , ETC
  , ETH
  , EUR
  , FIM
  , FRF
  , GBP
  , GRD
  , HKD
  , HUF
  , IDR
  , IEP
  , ILS
  , INR
  , IQD
  , IRR
  , ISK
  , ITL
  , JPY
  , KRW
  , KWD
  , KZT
  , LTC
  , LTL
  , LUF
  , LVL
  , MTL
  , MXN
  , MYR
  , NGN
  , NLG
  , NOK
  , NPR
  , NZD
  , PEH
  , PEI
  , PEN
  , PKR
  , PLN
  , PTE
  , ROL
  , RON
  , RUB
  , SAR
  , SEK
  , SGD
  , SIT
  , SKK
  , THB
  , TRL
  , TRY
  , TTD
  , TWD
  , UAH
  , USD
  , VEB
  , VND
  , XRP
  , ZAR
  , ZEC
  , AED
  , AOA
  , BGN
  , BHD
  , BWP
  , CLF
  , CNH
  , COU
  , EGP
  , ETB
  , GEL
  , GHS
  , HRK
  , JOD
  , KES
  , LKR
  , MAD
  , MKD
  , MUR
  , MXV
  , OMR
  , PHP
  , QAR
  , RSD
  , TND
  , UGX
  , UYU
  , UZS
  , XOF
  , ZMW
};

// should match with the order of qlMisc.cpp:calendars
enum CalendarCountry {
  Argentina = 0
  , Australia
  , Austria
  , Botswana
  , Brazil
  , Canada
  , China
  , CzechRepublic
  , Denmark
  , Finland
  , France
  , Germany
  , HongKong
  , Hungary
  , Iceland
  , India
  , Indonesia
  , Israel
  , Italy
  , Japan
  , Mexico
  , NewZealand
  , Norway
  , Null
  , Poland
  , Romania
  , Russia
  , SaudiArabia
  , Singapore
  , Slovakia
  , SouthAfrica
  , SouthKorea
  , Sweden
  , Switzerland
  , Taiwan
  , TARGET
  , Thailand
  , Turkey
  , Ukraine
  , UnitedKingdom
  , UnitedStates
  , WeekendsOnly
  , Chile
  , Croatia
  , Malta
  , Montenegro
  , NorthMacedonia
  , Serbia
  , Slovenia
  , Uzbekistan
};

// should match with the order of qlMisc.cpp:dayCounters
enum DayCounterType {
  Actual360 = 0
  , Actual364
  , Actual365Fixed
  , ActualActual
  , One
  , Simple
  , Thirty360
  , Thirty365
  , Actual36525
  , Actual366
};

#define NO_ENUM -100;

// must match with the order of qlTermStructure.cpp.cpp:onIndices
enum OvernightIborIndexType {
  Aonia = 0
  , Eonia
  , Estr
  , FedFunds
  , Nzocr
  , Sofr
  , Sonia
  , Cdi
  , Corra
  , Kofr
  , Destr
  , Swestr
  , Shir
  , Tonar
  , Saron
  , Zaronia
};

// must match with the order of qlTermStructure.cpp:swapIndices
enum LiborSwapIndexType {
  ChfLiborSwapIsdaFix = 0
  , EurLiborSwapIfrFix
  , EurLiborSwapIsdaFixA
  , EurLiborSwapIsdaFixB
  , EuriborSwapIfrFix
  , EuriborSwapIsdaFixA
  , EuriborSwapIsdaFixB
  , GbpLiborSwapIsdaFix
  , JpyLiborSwapIsdaFixAm
  , JpyLiborSwapIsdaFixPm
  , UsdLiborSwapIsdaFixAm
  , UsdLiborSwapIsdaFixPm
};

// must match the order of the "standard" block of qlTermStructure.cpp:iborIndices (comes
// first). IborIndexTypeLast is a sentinel, not a real index -- insert new values above it.
// This (and the other *Last sentinels below) is stripped out and turned into a flat-array
// offset entirely on the Haskell side by deriveIborConstructor in QuantLib/Internal/Syntax.hs
// -- nothing here needs to encode a count, a length, or an offset by hand.
enum IborIndexType {
  Bbsw = 0
  , Bibor
  , Bkbm
  , Cdor
  , EurLibor
  , AudLibor
  , CadLibor
  , ChfLibor
  , DkkLibor
  , GbpLibor
  , JpyLibor
  , NzdLibor
  , SekLibor
  , UsdLibor
  , Euribor
  , Euribor365
  , Jibar
  , Mosprime
  , Pribor
  , Robor
  , Shibor
  , THBFIX
  , TRLibor
  , Tibor
  , Wibor
  , Zibor
  , Nibor
  , IborIndexTypeLast
};

// must match the order of the "daily tenor" block of qlTermStructure.cpp:iborIndices (comes
// right after the standard block).
enum IborDailyTenorIndexType {
  EurDailyTenorLibor = 0
  , ChfDailyTenorLibor
  , GbpDailyTenorLibor
  , JpyDailyTenorLibor
  , UsdDailyTenorLibor
  , IborDailyTenorIndexTypeLast
};

// must match the order of the "overnight" block of qlTermStructure.cpp:iborIndices (comes
// last -- no sentinel needed, nothing chains off this group).
enum IborONIndexType {
  CadLiborON = 0
  , EurLiborON
  , GbpLiborON
  , UsdLiborON
};

enum RngTrait {
  PseudoRandom = 0
  , PoissonPseudoRandom
  , LowDiscrepancy
  , Ziggurat
};

enum BinomialTree {
  JarrowRudd = 0
  , CoxRossRubinstein
  , AdditiveEQPBinomialTree
  , Trigeorgis
  , Tian
  , LeisenReimer
  , Joshi4
  , ExtendedJarrowRudd
  , ExtendedCoxRossRubinstein
  , ExtendedAdditiveEQPBinomialTree
  , ExtendedTrigeorgis
  , ExtendedTian
  , ExtendedLeisenReimer
  , ExtendedJoshi4
};

enum ProcessDiscretization {
  EulerDiscretization = 0
  , EndEulerDiscretization
};

enum BootstrapTrait {
  Discount
  , ZeroYield
  , ForwardRate
};

enum InterpolationType {
  BackwardFlat
  , ForwardFlat
  , Linear
  , LogLinear
  , Cubic
  , LogCubic
  , Abcd
};

enum ApproximationType {
  NaturalSpline
  , Parabolic
  , Kruger
  , FritschButland
};

enum ProbabilityTrait {
  SurvivalProbability = 0
  , HazardRate
  , DefaultDensity
};

// must match the order of qlTermStructure.cpp:zeroInflationIndices
enum ZeroInflationIndexType {
  AUCPI = 0
  , EUHICP
  , EUHICPXT
  , FRHICP
  , UKHICP
  , UKRPI
  , USCPI
  , ZACPI
};

// must match the order of qlTermStructure.cpp:yoyInflationIndices
enum YoYInflationIndexType {
  YYAUCPI = 0
  , YYEUHICP
  , YYEUHICPXT
  , YYFRHICP
  , YYUKRPI
  , YYUSCPI
  , YYZACPI
};

enum CPIInterpolationType {
  CPIFlat = 0
  , CPILinear
};

// must match the order of qlTermStructure.cpp:regions
enum RegionType {
  AustraliaRegion = 0
  , EURegion
  , FranceRegion
  , UKRegion
  , USRegion
  , ZARegion
};

/* vim: set ft=c ff=unix ts=8 sts=2 sw=2 et: */
