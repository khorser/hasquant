// This file should only by used in C2HS, enums below are extracted from QuantLib headers
// time/weekday.hpp
enum Weekday {Sunday    = 1,
  Monday    = 2,
  Tuesday   = 3,
  Wednesday = 4,
  Thursday  = 5,
  Friday    = 6,
  Saturday  = 7,
  Sun = 1,
  Mon = 2,
  Tue = 3,
  Wed = 4,
  Thu = 5,
  Fri = 6,
  Sat = 7
};

// time/date.hpp
enum Month {January   = 1,
  February  = 2,
  March     = 3,
  April     = 4,
  May       = 5,
  June      = 6,
  July      = 7,
  August    = 8,
  September = 9,
  October   = 10,
  November  = 11,
  December  = 12,
  Jan = 1,
  Feb = 2,
  Mar = 3,
  Apr = 4,
  Jun = 6,
  Jul = 7,
  Aug = 8,
  Sep = 9,
  Oct = 10,
  Nov = 11,
  Dec = 12
};

// time/businessdayconvention.hpp
enum BusinessDayConvention {
  // ISDA
  Following,                   /*!< Choose the first business day after
                                 the given holiday. */
  ModifiedFollowing,           /*!< Choose the first business day after
                                 the given holiday unless it belongs
                                 to a different month, in which case
                                 choose the first business day before
                                 the holiday. */
  Preceding,                   /*!< Choose the first business
                                 day before the given holiday. */
  // NON ISDA
  ModifiedPreceding,           /*!< Choose the first business day before
                                 the given holiday unless it belongs
                                 to a different month, in which case
                                 choose the first business day after
                                 the holiday. */
  Unadjusted,                  /*!< Do not adjust. */
  HalfMonthModifiedFollowing,  /*!< Choose the first business day after
                                 the given holiday unless that day
                                 crosses the mid-month (15th) or the
                                 end of month, in which case choose
                                 the first business day before the
                                 holiday. */
  Nearest                      /*!< Choose the nearest business day
                                 to the given holiday. If both the
                                 preceding and following business
                                 days are equally far away, default
                                 to following business day. */
};

// time/dategenerationrule.hpp
enum DateGenerationRule {
  Backward,       /*!< Backward from termination date to
                    effective date. */
  Forward,        /*!< Forward from effective date to
                    termination date. */
  Zero,           /*!< No intermediate dates between effective date
                    and termination date. */
  ThirdWednesday, /*!< All dates but effective date and termination
                    date are taken to be on the third wednesday
                    of their month (with forward calculation.) */
  ThirdWednesdayInclusive, /*!< All dates including effective date and
                    termination date are taken to be on the third
                    wednesday of their month (with forward calculation.) */
  Twentieth,      /*!< All dates but the effective date are
                    taken to be the twentieth of their
                    month (used for CDS schedules in
                    emerging markets.)  The termination
                    date is also modified. */
  TwentiethIMM,   /*!< All dates but the effective date are
                    taken to be the twentieth of an IMM
                    month (used for CDS schedules.)  The
                    termination date is also modified. */
  OldCDS,         /*!< Same as TwentiethIMM with unrestricted date
                    ends and log/short stub coupon period (old
                    CDS convention). */
  CDS,             /*!< Credit derivatives standard rule since 'Big
                     Bang' changes in 2009.  */
  CDS2015,         /*!< Credit derivatives standard rule since
                     December 20th, 2015.  */
};

// time/timeunit.hpp
enum TimeUnit {Days,
  Weeks,
  Months,
  Years,
  Hours,
  Minutes,
  Seconds,
  Milliseconds,
  Microseconds
};

// time/frequency.hpp
enum Frequency {NoFrequency = -1,     //!< null frequency
  Once = 0,             //!< only once, e.g., a zero-coupon
  Annual = 1,           //!< once a year
  Semiannual = 2,       //!< twice a year
  EveryFourthMonth = 3, //!< every fourth month
  Quarterly = 4,        //!< every third month
  Bimonthly = 6,        //!< every second month
  Monthly = 12,         //!< once a month
  EveryFourthWeek = 13, //!< every fourth week
  Biweekly = 26,        //!< every second week
  Weekly = 52,          //!< once a week
  Daily = 365,          //!< once a day
  OtherFrequency = 999  //!< some other unknown frequency
};

// time/imm.hpp
enum ImmMonth {F =  1, G =  2, H =  3,
  J =  4, K =  5, M =  6,
  N =  7, Q =  8, U =  9,
  V = 10, X = 11, Z = 12};

// cashflows/duration.hpp
enum DurationType {Simple, Macaulay, Modified};

// time/calendars/jointcalendar.hpp
enum JointCalendarRule {JoinHolidays,    /*!< A date is a holiday
                                            for the joint calendar
                                            if it is a holiday
                                            for any of the given
                                            calendars */
  JoinBusinessDays /*!< A date is a business day
                     for the joint calendar
                     if it is a business day
                     for any of the given
                     calendars */
};

// prices.hpp
enum PriceType {
  Bid,          /*!< Bid price. */
  Ask,          /*!< Ask price. */
  Last,         /*!< Last price. */
  Close,        /*!< Close price. */
  Mid,          /*!< Mid price, calculated as the arithmetic
                  average of bid and ask prices. */
  MidEquivalent, /*!< Mid equivalent price, calculated as
                   a) the arithmetic average of bid and ask prices
                   when both are available; b) either the bid or the
                   ask price if any of them is available;
                   c) the last price; or d) the close price. */
  MidSafe       /*!< Safe Mid price, returns the mid price only if
                  both bid and ask are available. */
};

// prices.hpp
enum IntervalPriceType {Open, Close, High, Low};

// experimental/fx/deltavolquote.hpp
enum DeltaType {
  Spot,        // Spot Delta, e.g. usual Black Scholes delta
  Fwd,         // Forward Delta
  PaSpot,      // Premium Adjusted Spot Delta
  PaFwd        // Premium Adjusted Forward Delta
};

// experimental/fx/deltavolquote.hpp
enum AtmType {
  AtmNull,         // Default, if not an atm quote
  AtmSpot,         // K=S_0
  AtmFwd,          // K=F
  AtmDeltaNeutral, // Call Delta = Put Delta
  AtmVegaMax,      // K such that Vega is Maximum
  AtmGammaMax,     // K such that Gamma is Maximum
  AtmPutCall50     // K such that Call Delta=0.50 (only for Fwd Delta)
};

// models/calibrationhelper.hpp
enum CalibrationErrorType {
  RelativePriceError, PriceError, ImpliedVolError};

// cashflows/duration.hpp
enum DurationType {Simple, Macaulay, Modified};

// money.hpp
enum MoneyConversionType {
  NoConversion,           /*!< do not perform conversions */
  BaseCurrencyConversion, /*!< convert both operands to
                            the base currency before
                            converting */
  AutomatedConversion     /*!< return the result in the
                            currency of the first
                            operand */
};

// exchangerate.hpp
enum ExchangeRateType {Direct, Derived};

// exercise.hpp
enum ExerciseType {American, Bermudan, European};

// position.hpp
enum PositionType {Long, Short};

// instruments/swaption.hpp
enum SettlementType {Physical, Cash};

// instruments/swaption.hpp
enum SwaptionPriceType {Spot, Forward};

// pricingengines/swaption/blackswaptionengine.hpp
enum CashAnnuityModel {SwapRate, DiscountCurve};

// pricingengines/swaption/gaussian1dswaptionengine.hpp
enum Probabilities {None, Naive, Digital};

// pricingengines/vanilla/cashdividendeuropeanengine.hpp
enum CashDividendModel {Spot, Escrowed};

// pricingengines/credit/isdacdsengine.hpp
// NumericalFix's enumerators are prefixed (NumericalFixNone/NumericalFixTaylor) because plain
// "None" already belongs to Probabilities above -- C enumerators share one namespace per TU.
enum NumericalFix {NumericalFixNone, NumericalFixTaylor};
enum AccrualBias {HalfDayBias, NoBias};
enum ForwardsInCouponPeriod {Flat, Piecewise};

// instruments/swaption.hpp
enum SettlementMethod {
  PhysicalOTC,
  PhysicalCleared,
  CollateralizedCashPrice,
  ParYieldCurve
};

// pricingengines/swaption/basketgeneratingengine.hpp
// CalibrationBasketNaive is prefixed because plain "Naive" already belongs to Probabilities
// above -- C enumerators share one namespace per TU.
enum CalibrationBasketType {CalibrationBasketNaive, MaturityStrikeByDeltaGamma};

// instruments/callabilityschedule.hpp
enum CallabilityType {Call, Put};

// instruments/bond.hpp
enum BondPriceType {Dirty, Clean};

// option.hpp
enum OptionType {Put = -1, Call = 1};

// instruments/barriertype.hpp
enum BarrierType {DownIn, UpIn, DownOut, UpOut};

// instruments/doublebarriertype.hpp
enum DoubleBarrierType {KnockIn, KnockOut, KIKO, KOKI};

// instruments/partialtimebarrieroption.hpp -- values are non-consecutive
// upstream (no 1), must mirror PartialBarrier::Range exactly or EndB1/EndB2
// silently alias to the wrong case (unchecked cast, see CLAUDE.md).
enum PartialBarrierRange {Start = 0, EndB1 = 2, EndB2 = 3};

// instruments/swap.hpp
enum SwapType {Receiver = -1, Payer = 1};

// compounding.hpp
enum Compounding {Simple = 0,          //!< \f$ 1+rt \f$
  Compounded = 1,      //!< \f$ (1+r)^t \f$
  Continuous = 2,      //!< \f$ e^{rt} \f$
  SimpleThenCompounded, //!< Simple up to the first period then Compounded
  CompoundedThenSimple //!< Compounded up to the first period then Simple
};

// instruments/averagetype.hpp
enum AverageType {Arithmetic, Geometric};

// termstructures/volatility/volatilitytype.hpp
enum VolatilityType {ShiftedLognormal, Normal};

// cashflows/rateaveraging.hpp
enum RateAveragingType {
  Simple,  /*!< Under the simple convention the amount of
             interest is calculated by applying the
             sub-rate to the principal, and the payment
             due at the end of the period is the sum of
             those amounts. */
  Compound /*!< Under the compound convention, the
             additional amount of interest owed each
             period is calculated by applying the rate
             both to the principal and the accumulated
             unpaid interest. */
};

// termstructures/bootstraphelper.hpp
enum PillarChoice {MaturityDate, LastRelevantDate, CustomDate};

// instruments/futures.hpp
enum FuturesType {IMM, ASX, Custom};

// instruments/creditdefaultswap.hpp
enum PricingModel {
  Midpoint,
  ISDA
};

// default.hpp
enum ProtectionSide {Buyer, Seller};

// experimental/credit/defaulttype.hpp
enum Seniority {
  SecDom = 0,
  SnrFor,
  SubLT2,
  JrSubT2,
  PrefT1,
  // Unassigned value, allows for default RR quote
  NoSeniority,
  // markit parlance
  SeniorSec     = SecDom,
  SeniorUnSec   = SnrFor,
  SubTier1      = PrefT1,
  SubUpperTier2 = JrSubT2,
  SubLoweTier2  = SubLT2
};

// experimental/credit/defaulttype.hpp
enum AtomicDefaultType {
  // Includes one of the restructuring cases
  Restructuring = 0,
  Bankruptcy,
  FailureToPay,
  RepudiationMoratorium,
  Acceleration,
  Default,
  // synonyms
  ObligationAcceleration = Acceleration,
  ObligationDefault = Default,
  CrossDefault = Default,
  // Other non-isda
  Downgrade,   // Non-ISDA, not in FpML
  MergerEvent  // Non-ISDA, not in FpML
};


// experimental/credit/defaulttype.hpp
enum RestructuringType {
  NoRestructuring = 0,
  ModifiedRestructuring,
  ModifiedModifiedRestructuring,
  FullRestructuring,
  AnyRestructuring,
  // Markit notation:
  XR = NoRestructuring,
  MR = ModifiedRestructuring,
  MM = ModifiedModifiedRestructuring,
  CR = FullRestructuring
};

// math/rounding.hpp
enum RoundingType {
  None,    /*!< do not round: return the number unmodified */
  Up,      /*!< the first decimal place past the precision will be
             rounded up. This differs from the OMG rule which
             rounds up only if the decimal to be rounded is
             greater than or equal to the rounding digit */
  Down,    /*!< all decimal places past the precision will be
             truncated */
  Closest, /*!< the first decimal place past the precision
             will be rounded up if greater than or equal
             to the rounding digit; this corresponds to
             the OMG round-up rule.  When the rounding
             digit is 5, the result will be the one
             closest to the original number, hence the
             name. */
  Floor,   /*!< positive numbers will be rounded up and negative
             numbers will be rounded down using the OMG round up
             and round down rules */
  Ceiling  /*!< positive numbers will be rounded down and negative
             numbers will be rounded up using the OMG round up
             and round down rules */
};

// enums values should match with those in ql/time/calendars/*.hpp
enum AustriaMarket {Settlement, Exchange};
enum BrazilMarket {Settlement, Exchange};
enum CanadaMarket {Settlement, TSX};
enum ChinaMarket {SSE, IB};
enum FranceMarket {Settlement, Exchange};
enum GermanyMarket {Settlement, FrankfurtStockExchange, Xetra, Eurex, Euwax};
enum IndonesiaMarket {BEJ, JSX, IDX};
enum IsraelMarket {Settlement, TASE, SHIR, Telbor};
enum ItalyMarket {Settlement, Exchange};
enum RomaniaMarket {Public, BVB};
enum RussiaMarket {Settlement, MOEX};
enum SouthKoreaMarket {Settlement, KRX};
enum UnitedKingdomMarket {Settlement, Exchange, Metals};
enum UnitedStatesMarket {Settlement, NYSE, GovernmentBond, NERC, LiborImpact, FederalReserve, SOFR};
enum AustraliaMarket {Settlement, ASX};
enum NewZealandMarket {Wellington, Auckland};
enum PolandMarket {Settlement, WSE};

// enums values should match with those in ql/time/daycounters/*.hpp
enum ActualActualConvention {ISMA, Bond, ISDA, Historical, Actual365, AFB, Euro};
enum Thirty360Convention {USA, BondBasis, European, EurobondBasis, Italian, German, ISMA, ISDA, NASD};
enum Actual365FixedConvention {Standard, Canadian, NoLeap};

// math/optimization/endcriteria.hpp
enum EndCriteriaType {EndNone,
  MaxIterations,
  StationaryPoint,
  StationaryFunctionValue,
  StationaryFunctionAccuracy,
  ZeroGradientNorm,
  Unknown
};

// math/statistics/histogram.hpp
enum HistogramAlgorithm {HistogramNone, Sturges, FD, Scott};

// methods/finitedifferences/boundarycondition.hpp
enum BoundaryConditionSide {BoundaryNone, Upper, Lower};

// methods/finitedifferences/solvers/fdmbackwardsolver.hpp
enum FdmSchemeType {HundsdorferType, DouglasType,
 CraigSneydType, ModifiedCraigSneydType,
 ImplicitEulerType, ExplicitEulerType,
 MethodOfLinesType, TrBDF2Type,
 CrankNicolsonType};

// methods/montecarlo/lsmbasissystem.hpp
enum PolynomialType {Monomial, Laguerre, Hermite, Hyperbolic,
  Legendre, Chebyshev, Chebyshev2nd};

// pricingengines/vanilla/analytichestonengine.hpp
enum ComplexLogFormula {
  // Gatheral form of characteristic function w/o control variate
  Gatheral,
  // old branch correction form of the characteristic function w/o control variate
  BranchCorrection,
  // Gatheral form with Andersen-Piterbarg control variate
  AndersenPiterbarg,
  // same as AndersenPiterbarg, but a slightly better control variate
  AndersenPiterbargOptCV,
  // Gatheral form with asymptotic expansion of the characteristic function as control variate
  // https://hpcquantlib.wordpress.com/2020/08/30/a-novel-control-variate-for-the-heston-model
  AsymptoticChF,
  // auto selection of best control variate algorithm from above
  OptimalCV
};

// experimental/processes/extendedblackscholesprocess.hpp
enum ExtendedBlackScholesMertonProcessDiscretization {ExtendedBSMEuler, Milstein, PredictorCorrector};

// processes/hestonprocess.hpp
enum HestonProcessDiscretization {HestonPartialTruncation,
  HestonFullTruncation,
  HestonReflection,
  NonCentralChiSquareVariance,
  QuadraticExponential,
  QuadraticExponentialMartingale,
  BroadieKayaExactSchemeLobatto,
  BroadieKayaExactSchemeLaguerre,
  BroadieKayaExactSchemeTrapezoidal
};

// processes/gjrgarchprocess.hpp
enum GJRGARCHProcessDiscretization {GJRGARCHPartialTruncation, GJRGARCHFullTruncation,
  GJRGARCHReflection};

// processes/hybridhestonhullwhiteprocess.hpp
enum HybridHestonHullWhiteProcessDiscretization {HybridHestonHullWhiteEuler, BSMHullWhite};

// cashflows/conundrumpricer.hpp
enum YieldCurveModel {Standard,
  ExactYield,
  ParallelShifts,
  NonParallelShifts
};

// termstructures/volatility/swaption/cmsmarketcalibration.hpp
enum CmsMarketCalibrationType {OnSpread, OnPrice, OnForwardCmsPrice};

// termstructures/volatility/equityfx/blackvariancesurface.hp
enum BlackVarianceSurfaceExtrapolation {
  BlackVarianceSurfaceConstantExtrapolation,
  BlackVarianceSurfaceInterpolatorDefaultExtrapolation
};

// experimental/volatility/extendedblackvariancesurface.hpp
enum ExtendedBlackVarianceSurfaceExtrapolation {
  ExtendedBlackVarianceSurfaceConstantExtrapolation,
  ExtendedBlackVarianceSurfaceInterpolatorDefaultExtrapolation};

// termstructures/volatility/equityfx/fixedlocalvolsurface.hpp
enum FixedLocalVolSurfaceExtrapolation {
  FixedLocalVolSurfaceConstantExtrapolation,
  FixedLocalVolSurfaceInterpolatorDefaultExtrapolation
};

// cashflows/couponpricer.hpp (BlackIborCouponPricer::TimingAdjustment)
enum TimingAdjustment {Black76, BivariateLognormal};

// math/randomnumbers/sobolrsg.hpp
enum SobolDirectionIntegers {
  Unit, Jaeckel, SobolLevitan, SobolLevitanLemieux,
  JoeKuoD5, JoeKuoD6, JoeKuoD7, Kuo, Kuo2, Kuo3};

// termstructures/volatility/equityfx/blackvolsurfacedelta.hpp
// (BlackVolatilitySurfaceDelta::SmileInterpolationMethod). SmileLinear (not bare Linear, which
// would collide with Interpolation's own Linear constructor, imported unqualified all over) --
// same disambiguation-by-prefix convention DeltaVolQuote::AtmType's AtmSpot/AtmFwd/etc. already
// use against DeltaType's Spot/Fwd.
enum SmileInterpolationMethod {SmileLinear, NaturalCubic, FinancialCubic, CubicSpline};

// termstructures/volatility/equityfx/blackvoltimeextrapolation.hpp (BlackVolTimeExtrapolation::Type)
enum BlackVolTimeExtrapolationType {FlatVolatility, UseInterpolator, LinearVariance};

// experimental/commodities/unitofmeasure.hpp (UnitOfMeasure::Type). Quantity renamed to
// QuantityUnit -- it would otherwise collide with the Quantity class itself.
enum UnitOfMeasureType {Mass, Volume, Energy, QuantityUnit};

// experimental/commodities/paymentterm.hpp (PaymentTerm::EventType)
enum PaymentTermEventType {TradeDate, PricingDate};

// experimental/commodities/unitofmeasureconversion.hpp (UnitOfMeasureConversion::Type). Tags
// prefixed Uom -- confirmed clash with the already-bound ExchangeRateType{Direct,Derived}.
enum UnitOfMeasureConversionType {UomDirect, UomDerived};

// experimental/commodities/commodity.hpp (PricingError::Level). Grepped clean of any clash --
// 'Error' the data constructor doesn't collide with QuantLib.Type's 'Error' type (separate
// namespaces), and 'Info'/'Warning'/'Fatal' are otherwise unused as constructors here.
enum PricingErrorLevel {Info, Warning, Error, Fatal};

// experimental/commodities/energycommodity.hpp (EnergyCommodity::DeliverySchedule,
// EnergyCommodity::QuantityPeriodicity). Cross-cutting the same way UnitOfMeasureType is: both
// are used by EnergyCommodity's own constructors' callers and by
// CommodityPricingHelper::createPricingPeriods, so they're homed here rather than hand-rolled in
// QuantLib.Instrument.Energy.
enum DeliverySchedule {Constant, Window, Hourly, Daily, Weekly, Monthly, Quarterly, Yearly};
enum QuantityPeriodicity {Absolute, PerHour, PerDay, PerWeek, PerMonth, PerQuarter, PerYear};

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
