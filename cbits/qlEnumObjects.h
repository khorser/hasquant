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
  CountryArgentina = 0
  , CountryAustralia
  , CountryAustria
  , CountryBotswana
  , CountryBrazil
  , CountryCanada
  , CountryChina
  , CountryCzechRepublic
  , CountryDenmark
  , CountryFinland
  , CountryFrance
  , CountryGermany
  , CountryHongKong
  , CountryHungary
  , CountryIceland
  , CountryIndia
  , CountryIndonesia
  , CountryIsrael
  , CountryItaly
  , CountryJapan
  , CountryMexico
  , CountryNewZealand
  , CountryNorway
  , CountryNull
  , CountryPoland
  , CountryRomania
  , CountryRussia
  , CountrySaudiArabia
  , CountrySingapore
  , CountrySlovakia
  , CountrySouthAfrica
  , CountrySouthKorea
  , CountrySweden
  , CountrySwitzerland
  , CountryTaiwan
  , CountryTARGET
  , CountryThailand
  , CountryTurkey
  , CountryUkraine
  , CountryUnitedKingdom
  , CountryUnitedStates
  , CountryWeekendsOnly
};

// should match with the order of qlDayCounter.cpp:dayCounters
enum DayCounterType {
  DayCounterActual360 = 0
  , DayCounterActual364
  , DayCounterActual365Fixed
  , DayCounterActualActual
  , DayCounterOneDayCounter
  , DayCounterSimpleDayCounter
  , DayCounterThirty360
  , DayCounterThirty365
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
  IborBbsw = 0
  , IborBibor
  , IborBkbm
  , IborCdor
  , IborEurLibor
  , IborAudLibor
  , IborCadLibor
  , IborChfLibor
  , IborDkkLibor
  , IborGbpLibor
  , IborJpyLibor
  , IborNzdLibor
  , IborSekLibor
  , IborUsdLibor
  , IborEurDailyTenorLibor
  , IborChfDailyTenorLibor
  , IborGbpDailyTenorLibor
  , IborJpyDailyTenorLibor
  , IborUsdDailyTenorLibor
  , IborCadLiborON
  , IborEurLiborON
  , IborGbpLiborON
  , IborUsdLiborON
  , IborEuribor
  , IborEuribor365
  , IborJibar
  , IborMosprime
  , IborPribor
  , IborRobor
  , IborShibor
  , IborTHBFIX
  , IborTRLibor
  , IborTibor
  , IborWibor
  , IborZibor
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

enum FdmScheme {
  CrankNicolson = 0
  , ExplicitEuler
  , ImplicitEuler
};

enum ProcessDiscretization {
  EulerDiscretization = 0
  , EndEulerDiscretization
};

enum CurveTrait {
  Discount
  , ZeroYield
  , ForwardRate
};

enum ProbabilityTrait {
  SurvivalProbability = 0
  , HazardRate
  , DefaultDensity
};

/* vim: set ft=c ff=unix ts=8 sts=2 sw=2 et: */
