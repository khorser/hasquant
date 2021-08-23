// Enumerations to be mapped to specific QuantLib classes
// must match with the order of qlCurrency.cpp:ccys
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
};

// should match with the order of qlCalendar.cpp:calendars
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
};

// should match with the order of qlDayCounter.cpp:dayCounters
enum DayCounterType {
  Actual360 = 0
  , Actual364
  , Actual365Fixed
  , ActualActual
  , OneDayCounter
  , SimpleDayCounter
  , Thirty360
  , Thirty365
};

#define NO_ENUM -100;

// must match with the order of qlIborIndex.cpp:onIndices
enum OvernightIborIndexType {
  Aonia = 0
  , Eonia
  , Estr
  , FedFunds
  , Nzocr
  , Sofr
  , Sonia
};

// must match with the order of qlIndex.cpp:swapIndices
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

// must match with the order of qlIborIndex.cpp:iborIndices
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
  , EurDailyTenorLibor
  , ChfDailyTenorLibor
  , GbpDailyTenorLibor
  , JpyDailyTenorLibor
  , UsdDailyTenorLibor
  , CadLiborON
  , EurLiborON
  , GbpLiborON
  , UsdLiborON
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

/* vim: set ft=c ff=unix ts=8 sts=2 sw=2 et: */
