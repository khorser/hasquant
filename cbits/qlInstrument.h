// Discriminants for QlAdditionalResult.type, read by both the C++ shim and c2hs. Declared here,
// before the `#ifdef __cplusplus` guard that wraps the function prototypes, so c2hs (whose
// preprocessor does NOT define __cplusplus) can see and bind them with `{#enum ... #}`; the C++
// shim references the same names below.
enum AdditionalResultType {
  AdditionalResultDouble       = 0,  // value holds a Real (double)
  AdditionalResultString       = 1,  // value holds a std::string
  AdditionalResultDoubleVector = 2,  // value holds a std::vector<Real>
  AdditionalResultUnknown      = 3   // value is an unrecognised type; sval holds its C++ RTTI name
};

#ifdef __cplusplus
extern "C" {
#endif
  // Flat, C-friendly projection of Instrument::additionalResults(), whose values are
  // QuantLib's ext::any (std::any or boost::any depending on the QuantLib build). We pick
  // four concrete shapes -- double, std::string, vector<Real>, and an "unknown" fallback that
  // records the value's RTTI type name -- so no key is ever silently dropped or mislabelled.
  // Every key, (when set) sval, and (when set) varr is strdup'd/heap-allocated and freed by
  // qlFreeAdditionalResults.
  struct QlAdditionalResult {
    char    *key;   // strdup'd, freed by qlFreeAdditionalResults
    int      type;  // AdditionalResultType discriminant
    double   dval;  // valid iff type == AdditionalResultDouble
    char    *sval;  // strdup'd (or NULL), freed by qlFreeAdditionalResults
    double  *varr;  // heap array (or NULL), freed by qlFreeAdditionalResults; valid iff type == AdditionalResultDoubleVector
    unsigned vlen;  // varr's length
  };
  void qlInstrumentAdditionalResults(QlInstrument *instr, unsigned *len,
    struct QlAdditionalResult **out, char **e);
  void qlFreeAdditionalResults(unsigned len, struct QlAdditionalResult *out);

  void qlInstrumentSetPricingEngine(QlInstrument *instr, QlPricingEngine *eng,
    char **e);
  double qlInstrumentNPV(QlInstrument *instr, char **e);
  void qlFreeInstrument(QlInstrument *instr);
  QlInstrument* qlCompositeInstrument(unsigned instrLen, QlInstrument **instrs, unsigned cLen, double *coeff, char **e);
  double qlInstrumentErrorEstimate(QlInstrument* o, char **e);
  int qlInstrumentIsExpired(QlInstrument* o, char **e);
  int qlInstrumentValuationDate(QlInstrument* o, char **e);
  void qlFreePayoff(QlPayoff *o);
  void qlFreeBasketPayoff(QlBasketPayoff *o);
  QlPayoff* qlBasketPayoffAsPayoff(QlBasketPayoff *o);
  void qlFreeStrikedTypePayoff(QlStrikedTypePayoff *o);
  QlTypePayoff* qlStrikedTypePayoffAsTypePayoff(QlStrikedTypePayoff *o);
  void qlFreeTypePayoff(QlTypePayoff *o);
  QlPayoff* qlTypePayoffAsPayoff(QlTypePayoff *o);
  void qlFreePercentageStrikePayoff(QlPercentageStrikePayoff *o);
  QlStrikedTypePayoff* qlPercentageStrikePayoffAsStrikedTypePayoff(QlPercentageStrikePayoff *o);
  void qlFreePlainVanillaPayoff(QlPlainVanillaPayoff *o);
  QlStrikedTypePayoff* qlPlainVanillaPayoffAsStrikedTypePayoff(QlPlainVanillaPayoff *o);

  QlStrikedTypePayoff* qlAssetOrNothingPayoff(int type, double strike, char **e);
  QlBasketPayoff* qlAverageBasketPayoff(QlPayoff* p, unsigned n, char **e);
  QlBasketPayoff* qlAverageBasketPayoff1(QlPayoff* p, unsigned aLen, double* a, char **e);
  QlStrikedTypePayoff* qlCashOrNothingPayoff(int type, double strike, double cashPayoff, char **e);
  QlPayoff* qlDoubleStickyRatchetPayoff(double type1, double type2, double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlTypePayoff* qlFloatingTypePayoff(int type, char **e);
  QlPayoff* qlForwardTypePayoff(int type, double strike, char **e);
  QlStrikedTypePayoff* qlGapPayoff(int type, double strike, double secondStrike, char **e);
  QlBasketPayoff* qlMaxBasketPayoff(QlPayoff* p, char **e);
  QlBasketPayoff* qlMinBasketPayoff(QlPayoff* p, char **e);
  QlPercentageStrikePayoff* qlPercentageStrikePayoff(int type, double moneyness, char **e);
  QlPlainVanillaPayoff* qlPlainVanillaPayoff(int type, double strike, char **e);
  QlPayoff* qlRatchetMaxPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlPayoff* qlRatchetMinPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlPayoff* qlRatchetPayoff(double gearing1, double gearing2, double spread1, double spread2, double initialValue, double accrualFactor, char **e);
  QlBasketPayoff* qlSpreadBasketPayoff(QlPayoff* p, char **e);
  QlPayoff* qlStickyMaxPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlPayoff* qlStickyMinPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e);
  QlPayoff* qlStickyPayoff(double gearing1, double gearing2, double spread1, double spread2, double initialValue, double accrualFactor, char **e);
  QlStrikedTypePayoff* qlSuperFundPayoff(double strike, double secondStrike, char **e);
  QlStrikedTypePayoff* qlSuperSharePayoff(double strike, double secondStrike, double cashPayoff, char **e);

  void qlFreeAmericanExercise(QlAmericanExercise *o);
  QlExercise* qlAmericanExerciseAsExercise(QlAmericanExercise *o);
  void qlFreeBermudanExercise(QlBermudanExercise *o);
  QlExercise* qlBermudanExerciseAsExercise(QlBermudanExercise *o);
  void qlFreeEuropeanExercise(QlEuropeanExercise *o);
  QlExercise* qlEuropeanExerciseAsExercise(QlEuropeanExercise *o);
  void qlFreeExercise(QlExercise *o);
  QlAmericanExercise* qlAmericanExercise(int earliestDate, int latestDate, int payoffAtExpiry, char **e);
  QlBermudanExercise* qlBermudanExercise(unsigned datesLen, int *dates, int payoffAtExpiry, char **e);
  QlExercise* qlEarlyExercise(int type, int payoffAtExpiry, char **e);
  QlExercise* qlExercise(int type, char **e);
  QlEuropeanExercise* qlEuropeanExercise(int date, char **e);

  QlAmericanExercise* qlAmericanExercise1(int latestDate, int payoffAtExpiry, char **e);
  QlSwingExercise* qlSwingExercise(unsigned datesLen, int* dates, unsigned secLen, unsigned* seconds, char **e);
  QlSwingExercise* qlSwingExercise1(int from, int to, unsigned stepSizeSecs, char **e);
  QlExercise* qlSwingExerciseAsExercise(QlSwingExercise *o);

  void qlFreeRebatedExercise(QlRebatedExercise *o);
  QlExercise* qlRebatedExerciseAsExercise(QlRebatedExercise *o);
  QlRebatedExercise* qlRebatedExercise(QlExercise* exercise, double rebate, unsigned rebateSettlementDays, Calendar* rebatePaymentCalendar, int rebatePaymentConvention, char **e);

  void qlFreeCapFloor(QlCapFloor *o);
  QlInstrument* qlCapFloorAsInstrument(QlCapFloor *o);
  QlCapFloor* qlCap(Leg* floatingLeg, unsigned exerciseRatesLen, double* exerciseRates, char **e);
  QlCapFloor* qlCollar(Leg* floatingLeg, unsigned capRatesLen, double* capRates, unsigned floorRatesLen, double* floorRates, char **e);
  QlCapFloor* qlFloor(Leg* floatingLeg, unsigned exerciseRatesLen, double* exerciseRates, char **e);
  double qlCapFloorAtmRate(QlCapFloor* o, QlYieldTermStructure* discountCurve, char **e);
  double qlCapFloorImpliedVolatility(QlCapFloor* o, double price, QlYieldTermStructure* disc, double guess, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, int type, double displacement, char **e);
  QlCapFloor* qlCapFloorOptionlet(QlCapFloor* o, unsigned n, char **e);

  void qlFreeCallability(QlCallability *o);
  QlCallability* qlCallability(double price, int priceType, int type, int date, char **e);
  void qlFreeBondForward(QlBondForward *fwd);
  QlForward* qlBondForwardAsForward(QlBondForward *fwd);
  QlBondForward* qlBondForward(int valueDate, int maturityDate, int type, double strike, unsigned settlementDays, DayCounter* dayCounter, Calendar* calendar, int businessDayConvention, QlBond* fixedCouponBond, QlYieldTermStructure* discountCurve, QlYieldTermStructure* incomeDiscountCurve, char **e);
  double qlBondForwardCleanForwardPrice(QlBondForward* o, char **e);
  double qlBondForwardForwardPrice(QlBondForward* o, char **e);
  void qlFreeForward(QlForward *fwd);
  QlInstrument* qlForwardAsInstrument(QlForward *fwd);
  double qlForwardForwardValue(QlForward* o, char **e);
  InterestRate* qlForwardImpliedYield(QlForward* o, double underlyingSpotValue, double forwardValue, int settlementDate, int compoundingConvention, DayCounter* dayCounter, char **e);
  int qlForwardSettlementDate(QlForward* o, char **e);
  double qlForwardSpotIncome(QlForward* o, QlYieldTermStructure* incomeDiscountCurve, char **e);
  double qlForwardSpotValue(QlForward* o, char **e);
  void qlFreeForwardRateAgreement(QlForwardRateAgreement *fwd);
  QlInstrument* qlForwardRateAgreementAsInstrument(QlForwardRateAgreement *fwd);
  QlForwardRateAgreement* qlForwardRateAgreement(QlIborIndex* index, int valueDate, int maturityDate, int type, double strikeForwardRate, double notionalAmount, QlYieldTermStructure* discountCurve, char **e);

  InterestRate* qlForwardRateAgreementForwardRate(QlForwardRateAgreement* o, char **e);

  void qlFreeFxForward(QlFxForward *fwd);
  QlInstrument* qlFxForwardAsInstrument(QlFxForward *fwd);
  QlFxForward* qlFxForward(double sourceNominal, Currency* sourceCurrency, double targetNominal, Currency* targetCurrency, int maturityDate, int paySourceCurrency, unsigned settlementDays, Calendar* paymentCalendar, char **e);
  QlFxForward* qlFxForward1(double sourceNominal, Currency* sourceCurrency, Currency* targetCurrency, double forwardRate, int maturityDate, int paySourceCurrency, unsigned settlementDays, Calendar* paymentCalendar, char **e);
  double qlFxForwardFairForwardRate(QlFxForward* o, char **e);
  double qlFxForwardNpvSourceCurrency(QlFxForward* o, char **e);
  double qlFxForwardNpvTargetCurrency(QlFxForward* o, char **e);

  void qlFreeSwap(QlSwap *o);
  QlInstrument* qlSwapAsInstrument(QlSwap *o);
  void qlFreeFixedVsFloatingSwap(QlFixedVsFloatingSwap *o);
  QlSwap* qlFixedVsFloatingSwapAsSwap(QlFixedVsFloatingSwap *o);
  void qlFreeVanillaSwap(QlVanillaSwap *o);
  QlFixedVsFloatingSwap* qlVanillaSwapAsFixedVsFloatingSwap(QlVanillaSwap *o);
  void qlFreeNonstandardSwap(QlNonstandardSwap *o);
  QlSwap* qlNonstandardSwapAsSwap(QlNonstandardSwap *o);
  void qlFreeBMASwap(QlBMASwap *o);
  QlSwap* qlBMASwapAsSwap(QlBMASwap *o);
  void qlFreeOvernightIndexedSwap(QlOvernightIndexedSwap *o);
  QlSwap* qlOvernightIndexedSwapAsSwap(QlOvernightIndexedSwap *o);
  void qlFreeAssetSwap(QlAssetSwap *o);
  QlSwap* qlAssetSwapAsSwap(QlAssetSwap *o);
  void qlFreeZeroCouponInflationSwap(QlZeroCouponInflationSwap *o);
  QlSwap* qlZeroCouponInflationSwapAsSwap(QlZeroCouponInflationSwap *o);
  QlZeroCouponInflationSwap* qlZeroCouponInflationSwap(int type, double nominal, int startDate, int maturity, Calendar* cal, int paymentConvention, DayCounter* dayCounter, double fixedRate, QlZeroInflationIndex* index, int obsLagLen, int obsLagUnit, int observationInterpolation, int adjustInfObsDates, Calendar* infCalendar, int infConvention, char **e);
  double qlZeroCouponInflationSwapFairRate(QlZeroCouponInflationSwap* o, char **e);
  void qlFreeYearOnYearInflationSwap(QlYearOnYearInflationSwap *o);
  QlSwap* qlYearOnYearInflationSwapAsSwap(QlYearOnYearInflationSwap *o);
  QlYearOnYearInflationSwap* qlYearOnYearInflationSwap(int type, double nominal, Schedule* fixedSchedule, double fixedRate, DayCounter* fixedDayCount, Schedule* yoySchedule, QlYoYInflationIndex* yoyIndex, int obsLagLen, int obsLagUnit, int interpolation, double spread, DayCounter* yoyDayCount, Calendar* paymentCalendar, int paymentConvention, char **e);
  double qlYearOnYearInflationSwapFairRate(QlYearOnYearInflationSwap* o, char **e);
  double qlYearOnYearInflationSwapFairSpread(QlYearOnYearInflationSwap* o, char **e);
  void qlFreeCPISwap(QlCPISwap *o);
  QlSwap* qlCPISwapAsSwap(QlCPISwap *o);
  QlCPISwap* qlCPISwap(int type, double nominal, int subtractInflationNominal, double spread, DayCounter* floatDayCount, Schedule* floatSchedule, int floatRoll, unsigned fixingDays, QlIborIndex* floatIndex, double fixedRate, double baseCPI, DayCounter* fixedDayCount, Schedule* fixedSchedule, int fixedRoll, int obsLagLen, int obsLagUnit, QlZeroInflationIndex* fixedIndex, int observationInterpolation, double inflationNominal, char **e);
  double qlCPISwapFairRate(QlCPISwap* o, char **e);
  double qlCPISwapFairSpread(QlCPISwap* o, char **e);
  void qlFreeZeroCouponSwap(QlZeroCouponSwap *o);
  QlSwap* qlZeroCouponSwapAsSwap(QlZeroCouponSwap *o);
  QlZeroCouponSwap* qlZeroCouponSwap(int type, double baseNominal, int startDate, int maturityDate, double fixedPayment, QlIborIndex* iborIndex, Calendar* paymentCalendar, int paymentConvention, unsigned paymentDelay, char **e);
  QlZeroCouponSwap* qlZeroCouponSwap1(int type, double baseNominal, int startDate, int maturityDate, double fixedRate, DayCounter* fixedDayCounter, QlIborIndex* iborIndex, Calendar* paymentCalendar, int paymentConvention, unsigned paymentDelay, char **e);
  double qlZeroCouponSwapFairFixedPayment(QlZeroCouponSwap* o, char **e);
  double qlZeroCouponSwapFairFixedRate(QlZeroCouponSwap* o, DayCounter* dayCounter, char **e);
  QlOvernightIndexedSwap* qlOvernightIndexedSwap(int type, double nominal, Schedule* schedule, double fixedRate, DayCounter* fixedDC, QlOvernightIndex* overnightIndex, double spread, int paymentLag, int paymentAdjustment, Calendar* paymentCalendar, int telescopicValueDates, int averagingMethod, unsigned lookbackDays, unsigned lockoutDays, int applyObservationShift, char **e);
  QlOvernightIndexedSwap* qlOvernightIndexedSwap1(int type, unsigned nominalsLen, double* nominals, Schedule* schedule, double fixedRate, DayCounter* fixedDC, QlOvernightIndex* overnightIndex, double spread, int paymentLag, int paymentAdjustment, Calendar* paymentCalendar, int telescopicValueDates, int averagingMethod, unsigned lookbackDays, unsigned lockoutDays, int applyObservationShift, char **e);
  QlSwap* qlSwap1(unsigned legsLen, Leg** legs, unsigned payerLen, int *payer, char **e);
  QlAssetSwap* qlAssetSwap(int payBondCoupon, QlBond* bond, double bondCleanPrice, QlIborIndex* iborIndex, double spread, Schedule* floatSchedule, DayCounter* floatingDayCount, int parAssetSwap, double gearing, double nonParRepayment, int dealMaturity, char **e);
  QlBMASwap* qlBMASwap(int type, double nominal, Schedule* liborSchedule, double liborFraction, double liborSpread, QlIborIndex* liborIndex, DayCounter* liborDayCount, Schedule* bmaSchedule, QlBMAIndex* bmaIndex, DayCounter* bmaDayCount, char **e);
  QlVanillaSwap* qlVanillaSwap(int type, double nominal, Schedule* fixedSchedule, double fixedRate, DayCounter* fixedDayCount, Schedule* floatSchedule, QlIborIndex* iborIndex, double spread, DayCounter* floatingDayCount, int paymentConvention, int useIndexedCoupons, char **e);
  QlNonstandardSwap* qlNonstandardSwap1(QlFixedVsFloatingSwap* v, char **e);
  QlNonstandardSwap* qlNonstandardSwap(int type, unsigned fixedNominalLen, double* fixedNominal, unsigned floatingNominalLen, double* floatingNominal, Schedule* fixedSchedule, unsigned fixedRateLen, double* fixedRate, DayCounter* fixedDayCount, Schedule* floatingSchedule, QlIborIndex* iborIndex, double gearing, double spread, DayCounter* floatingDayCount, int intermediateCapitalExchange, int finalCapitalExchange, int paymentConvention, char **e);
  QlNonstandardSwap* qlNonstandardSwap2(int type, unsigned fixedNominalLen, double* fixedNominal, unsigned floatingNominalLen, double* floatingNominal, Schedule* fixedSchedule, unsigned fixedRateLen, double* fixedRate, DayCounter* fixedDayCount, Schedule* floatingSchedule, QlIborIndex* iborIndex, unsigned gearingLen, double* gearing, unsigned spreadLen, double* spread, DayCounter* floatingDayCount, int intermediateCapitalExchange, int finalCapitalExchange, int paymentConvention, char **e);
  QlSwap* qlSwap(Leg* firstLeg, Leg* secondLeg, char **e);
  Leg* qlSwapLeg(QlSwap* o, unsigned j, char **e);
  Leg* qlFixedVsFloatingSwapFixedLeg(QlFixedVsFloatingSwap* o, char **e);
  Leg* qlFixedVsFloatingSwapFloatingLeg(QlFixedVsFloatingSwap* o, char **e);
  Leg* qlAssetSwapBondLeg(QlAssetSwap* o, char **e);
  Leg* qlAssetSwapFloatingLeg(QlAssetSwap* o, char **e);
  Leg* qlBMASwapBmaLeg(QlBMASwap* o, char **e);
  Leg* qlBMASwapLiborLeg(QlBMASwap* o, char **e);
  Leg* qlOvernightIndexedSwapFixedLeg(QlOvernightIndexedSwap* o, char **e);
  Leg* qlOvernightIndexedSwapOvernightLeg(QlOvernightIndexedSwap* o, char **e);
  double qlAssetSwapCleanPrice(QlAssetSwap* o, char **e);
  double qlAssetSwapFairCleanPrice(QlAssetSwap* o, char **e);
  double qlAssetSwapFairNonParRepayment(QlAssetSwap* o, char **e);
  double qlAssetSwapFairSpread(QlAssetSwap* o, char **e);
  double qlAssetSwapFloatingLegBPS(QlAssetSwap* o, char **e);
  double qlAssetSwapFloatingLegNPV(QlAssetSwap* o, char **e);
  double qlAssetSwapNonParRepayment(QlAssetSwap* o, char **e);
  int qlAssetSwapParSwap(QlAssetSwap* o, char **e);
  int qlAssetSwapPayBondCoupon(QlAssetSwap* o, char **e);
  double qlBMASwapBmaLegBPS(QlBMASwap* o, char **e);
  double qlBMASwapBmaLegNPV(QlBMASwap* o, char **e);
  double qlBMASwapFairLiborFraction(QlBMASwap* o, char **e);
  double qlBMASwapFairLiborSpread(QlBMASwap* o, char **e);
  double qlBMASwapLiborFraction(QlBMASwap* o, char **e);
  double qlBMASwapLiborLegBPS(QlBMASwap* o, char **e);
  double qlBMASwapLiborLegNPV(QlBMASwap* o, char **e);
  double qlOvernightIndexedSwapFairRate(QlOvernightIndexedSwap* o, char **e);
  double qlOvernightIndexedSwapFairSpread(QlOvernightIndexedSwap* o, char **e);
  double qlOvernightIndexedSwapFixedLegBPS(QlOvernightIndexedSwap* o, char **e);
  double qlOvernightIndexedSwapFixedLegNPV(QlOvernightIndexedSwap* o, char **e);
  double qlOvernightIndexedSwapOvernightLegBPS(QlOvernightIndexedSwap* o, char **e);
  double qlOvernightIndexedSwapOvernightLegNPV(QlOvernightIndexedSwap* o, char **e);
  double qlSwapEndDiscounts(QlSwap* o, unsigned j, char **e);
  double qlSwapLegBPS(QlSwap* o, unsigned j, char **e);
  double qlSwapLegNPV(QlSwap* o, unsigned j, char **e);
  int qlSwapMaturityDate(QlSwap* o, char **e);
  double qlSwapNpvDateDiscount(QlSwap* o, char **e);
  int qlSwapStartDate(QlSwap* o, char **e);
  double qlSwapStartDiscounts(QlSwap* o, unsigned j, char **e);
  double qlFixedVsFloatingSwapFairRate(QlFixedVsFloatingSwap* o, char **e);
  double qlFixedVsFloatingSwapFairSpread(QlFixedVsFloatingSwap* o, char **e);
  double qlFixedVsFloatingSwapFixedLegBPS(QlFixedVsFloatingSwap* o, char **e);
  double qlFixedVsFloatingSwapFixedLegNPV(QlFixedVsFloatingSwap* o, char **e);
  double qlFixedVsFloatingSwapFloatingLegBPS(QlFixedVsFloatingSwap* o, char **e);
  double qlFixedVsFloatingSwapFloatingLegNPV(QlFixedVsFloatingSwap* o, char **e);

  void qlFreeEquityTotalReturnSwap(QlEquityTotalReturnSwap *o);
  QlSwap* qlEquityTotalReturnSwapAsSwap(QlEquityTotalReturnSwap *o);
  QlEquityTotalReturnSwap* qlEquityTotalReturnSwapIbor(int type, double nominal, Schedule* schedule, QlEquityIndex* equityIndex, QlIborIndex* interestRateIndex, DayCounter* dayCounter, double margin, double gearing, Calendar* paymentCalendar, int paymentConvention, unsigned paymentDelay, char **e);
  QlEquityTotalReturnSwap* qlEquityTotalReturnSwapOvernight(int type, double nominal, Schedule* schedule, QlEquityIndex* equityIndex, QlOvernightIndex* interestRateIndex, DayCounter* dayCounter, double margin, double gearing, Calendar* paymentCalendar, int paymentConvention, unsigned paymentDelay, char **e);
  double qlEquityTotalReturnSwapEquityLegNPV(QlEquityTotalReturnSwap* o, char **e);
  double qlEquityTotalReturnSwapInterestRateLegNPV(QlEquityTotalReturnSwap* o, char **e);
  double qlEquityTotalReturnSwapFairMargin(QlEquityTotalReturnSwap* o, char **e);

  void qlFreeCreditDefaultSwap(QlCreditDefaultSwap *o);
  QlInstrument* qlCreditDefaultSwapAsInstrument(QlCreditDefaultSwap *o);
  void qlFreeClaim(QlClaim *o);
  QlClaim* qlFaceValueAccrualClaim(QlBond* referenceSecurity, char **e);
  QlClaim* qlFaceValueClaim(char **e);
  QlCreditDefaultSwap* qlCreditDefaultSwap(int side, double notional, double spread, Schedule* schedule, int paymentConvention, DayCounter* dayCounter, int settlesAccrual, int paysAtDefaultTime, int protectionStart, QlClaim* x9, DayCounter* lastPeriodDayCounter, int rebatesAccrual, int tradeDate, unsigned cashSettlementDays, char **e);
  QlCreditDefaultSwap* qlCreditDefaultSwap1(int side, double notional, double upfront, double spread, Schedule* schedule, int paymentConvention, DayCounter* dayCounter, int settlesAccrual, int paysAtDefaultTime, int protectionStart, int upfrontDate, QlClaim* x11, DayCounter* lastPeriodDayCounter, int rebatesAccrual, int tradeDate, unsigned cashSettlementDays, char **e);
  QlOption* qlCdsOptionAsOption(QlCdsOption *o);
  void qlFreeCdsOption(QlCdsOption *o);
  double qlCreditDefaultSwapFairSpread(QlCreditDefaultSwap* o, char **e);
  double qlCreditDefaultSwapConventionalSpread(QlCreditDefaultSwap* o, double conventionalRecovery, QlYieldTermStructure* discountCurve, DayCounter* dayCounter, int model, char **e);
  double qlCreditDefaultSwapCouponLegBPS(QlCreditDefaultSwap* o, char **e);
  double qlCreditDefaultSwapCouponLegNPV(QlCreditDefaultSwap* o, char **e);
  Leg* qlCreditDefaultSwapCoupons(QlCreditDefaultSwap* o, char **e);
  double qlCreditDefaultSwapDefaultLegNPV(QlCreditDefaultSwap* o, char **e);
  double qlCreditDefaultSwapFairUpfront(QlCreditDefaultSwap* o, char **e);
  double qlCreditDefaultSwapImpliedHazardRate(QlCreditDefaultSwap* o, double targetNPV, QlYieldTermStructure* discountCurve, DayCounter* dayCounter, double recoveryRate, double accuracy, int model, char **e);
  double qlCreditDefaultSwapUpfrontBPS(QlCreditDefaultSwap* o, char **e);
  double qlCreditDefaultSwapUpfrontNPV(QlCreditDefaultSwap* o, char **e);
  void qlFreeBarrierOption(QlBarrierOption *o);
  QlOneAssetOption* qlBarrierOptionAsOneAssetOption(QlBarrierOption *o);
  void qlFreeDoubleBarrierOption(QlDoubleBarrierOption *o);
  QlOneAssetOption* qlDoubleBarrierOptionAsOneAssetOption(QlDoubleBarrierOption *o);
  void qlFreeMargrabeOption(QlMargrabeOption *o);
  QlMultiAssetOption* qlMargrabeOptionAsMultiAssetOption(QlMargrabeOption *o);
  void qlFreeMultiAssetOption(QlMultiAssetOption *o);
  QlOption* qlMultiAssetOptionAsOption(QlMultiAssetOption *o);
  void qlFreeOneAssetOption(QlOneAssetOption *o);
  QlOption* qlOneAssetOptionAsOption(QlOneAssetOption *o);
  void qlFreeOption(QlOption *o);
  QlInstrument* qlOptionAsInstrument(QlOption *o);
  void qlFreeQuantoVanillaOption(QlQuantoVanillaOption *o);
  QlOneAssetOption* qlQuantoVanillaOptionAsOneAssetOption(QlQuantoVanillaOption *o);
  void qlFreeSwaption(QlSwaption *o);
  QlOption* qlSwaptionAsOption(QlSwaption *o);
  void qlFreeSwingExercise(QlSwingExercise *o);
  QlBermudanExercise* qlSwingExerciseAsBermudanExercise(QlSwingExercise *o);
  void qlFreeVanillaOption(QlVanillaOption *o);
  QlOneAssetOption* qlVanillaOptionAsOneAssetOption(QlVanillaOption *o);
  double qlCdsOptionAtmRate(QlCdsOption* o, char **e);
  QlCdsOption* qlCdsOption(QlCreditDefaultSwap* swap, QlExercise* exercise, int knocksOut, char **e);
  double qlCdsOptionImpliedVolatility(QlCdsOption* o, double price, QlYieldTermStructure* termStructure, QlDefaultProbabilityTermStructure* x3, double recoveryRate, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  double qlCdsOptionRiskyAnnuity(QlCdsOption* o, char **e);
  double qlSwaptionImpliedVolatility(QlSwaption* o, double price, QlYieldTermStructure* discountCurve, double guess, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, int type, double displacement, int priceType, char **e);
  QlSwaption* qlSwaption(QlFixedVsFloatingSwap* swap, QlExercise* exercise, int delivery, int settlementMethod, char **e);
  void qlFreeNonstandardSwaption(QlNonstandardSwaption *o);
  QlOption* qlNonstandardSwaptionAsOption(QlNonstandardSwaption *o);
  QlNonstandardSwaption* qlNonstandardSwaption1(QlSwaption* fromSwaption, char **e);
  QlNonstandardSwaption* qlNonstandardSwaption(QlNonstandardSwap* swap, QlExercise* exercise, int delivery, int settlementMethod, char **e);
  void qlNonstandardSwaptionCalibrationBasket(QlNonstandardSwaption* o, QlSwapIndex* swapBase, QlSwaptionVolatilityStructure* swaptionVol, int basketType, unsigned* len, QlBlackCalibrationHelper*** helpers, char **e);
  void qlFreeQuantoBarrierOption(QlQuantoBarrierOption *o);
  QlOneAssetOption* qlQuantoBarrierOptionAsOneAssetOption(QlQuantoBarrierOption *o);
  void qlFreeQuantoForwardVanillaOption(QlQuantoForwardVanillaOption *o);
  QlOption* qlQuantoForwardVanillaOptionAsOption(QlQuantoForwardVanillaOption *o);

  QlBarrierOption* qlBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  double qlBarrierOptionImpliedVolatility(QlBarrierOption* o, double price, QlGeneralizedBlackScholesProcess* process, unsigned dividendsLen, QlDividend** dividends, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  QlOneAssetOption* qlPartialTimeBarrierOption(int barrierType, int barrierRange, double barrier, double rebate, int coverEventDate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  QlDoubleBarrierOption* qlDoubleBarrierOption(int barrierType, double barrierLo, double barrierHi, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  double qlDoubleBarrierOptionImpliedVolatility(QlDoubleBarrierOption* o, double price, QlGeneralizedBlackScholesProcess* process, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  QlOneAssetOption* qlForwardVanillaOption(double moneyness, int resetDate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* qlCompoundOption(QlStrikedTypePayoff* motherPayoff, QlExercise* motherExercise, QlStrikedTypePayoff* daughterPayoff, QlExercise* daughterExercise, char **e);
  double qlMargrabeOptionDelta1(QlMargrabeOption* o, char **e);
  double qlMargrabeOptionDelta2(QlMargrabeOption* o, char **e);
  double qlMargrabeOptionGamma1(QlMargrabeOption* o, char **e);
  double qlMargrabeOptionGamma2(QlMargrabeOption* o, char **e);
  QlMargrabeOption* qlMargrabeOption(int Q1, int Q2, QlExercise* x2, char **e);
  double qlMultiAssetOptionDelta(QlMultiAssetOption* o, char **e);
  double qlMultiAssetOptionDividendRho(QlMultiAssetOption* o, char **e);
  double qlMultiAssetOptionGamma(QlMultiAssetOption* o, char **e);
  QlMultiAssetOption* qlMultiAssetOption(QlPayoff* x0, QlExercise* x1, char **e);
  double qlMultiAssetOptionRho(QlMultiAssetOption* o, char **e);
  double qlMultiAssetOptionTheta(QlMultiAssetOption* o, char **e);
  double qlMultiAssetOptionVega(QlMultiAssetOption* o, char **e);
  double qlOneAssetOptionDelta(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionDeltaForward(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionDividendRho(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionElasticity(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionGamma(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionItmCashProbability(QlOneAssetOption* o, char **e);
  QlOneAssetOption* qlOneAssetOption(QlPayoff* x0, QlExercise* x1, char **e);
  double qlOneAssetOptionRho(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionStrikeSensitivity(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionTheta(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionThetaPerDay(QlOneAssetOption* o, char **e);
  double qlOneAssetOptionVega(QlOneAssetOption* o, char **e);
  double qlQuantoBarrierOptionQlambda(QlQuantoBarrierOption* o, char **e);
  double qlQuantoBarrierOptionQrho(QlQuantoBarrierOption* o, char **e);
  QlQuantoBarrierOption* qlQuantoBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  double qlQuantoBarrierOptionQvega(QlQuantoBarrierOption* o, char **e);
  double qlQuantoForwardVanillaOptionQlambda(QlQuantoForwardVanillaOption* o, char **e);
  double qlQuantoForwardVanillaOptionQrho(QlQuantoForwardVanillaOption* o, char **e);
  QlQuantoForwardVanillaOption* qlQuantoForwardVanillaOption(double moneyness, int resetDate, QlStrikedTypePayoff* x2, QlExercise* x3, char **e);
  double qlQuantoForwardVanillaOptionQvega(QlQuantoForwardVanillaOption* o, char **e);
  double qlQuantoVanillaOptionQlambda(QlQuantoVanillaOption* o, char **e);
  double qlQuantoVanillaOptionQrho(QlQuantoVanillaOption* o, char **e);
  QlQuantoVanillaOption* qlQuantoVanillaOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e);
  double qlQuantoVanillaOptionQvega(QlQuantoVanillaOption* o, char **e);
  double qlVanillaOptionImpliedVolatility(QlVanillaOption* o, double price, QlGeneralizedBlackScholesProcess* process, unsigned dividendsLen, QlDividend** dividends, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e);
  QlVanillaOption* qlVanillaOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e);
  QlMultiAssetOption* qlBasketOption(QlBasketPayoff* x0, QlExercise* x1, char **e);
  QlMultiAssetOption* qlHimalayaOption(unsigned fixingDatesLen, int* fixingDates, double strike, char **e);
  QlMultiAssetOption* qlPagodaOption(unsigned fixingDatesLen, int* fixingDates, double roof, double fraction, char **e);
  QlOneAssetOption* qlCliquetOption(QlPercentageStrikePayoff* x0, QlEuropeanExercise* maturity, unsigned resetDatesLen, int* resetDates, char **e);
  QlOneAssetOption* qlContinuousAveragingAsianOption(int averageType, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* qlContinuousFixedLookbackOption(double currentMinmax, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* qlContinuousFloatingLookbackOption(double currentMinmax, QlTypePayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* qlDiscreteAveragingAsianOption(int averageType, double runningAccumulator, unsigned pastFixings, unsigned fixingDatesLen, int* fixingDates, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e);
  QlOneAssetOption* qlVanillaStorageOption(QlBermudanExercise* ex, double capacity, double load, double changeRate, char **e);
  QlOneAssetOption* qlVanillaSwingOption(QlStrikedTypePayoff* payoff, QlSwingExercise* ex, unsigned minExerciseRights, unsigned maxExerciseRights, char **e);
  QlVanillaOption* qlEuropeanOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e);

  QlBond *qlBond(unsigned settlDays, Calendar *calendar, int issueDate, Leg *coupons, char **e);
  QlBond *qlBond1(unsigned settlDays, Calendar *calendar, double faceAmount, int maturityDate, int issueDate, Leg *cashFlows, char **e);
  Leg* qlBondCashflows(QlBond* o, char **e);
  Leg* qlBondRedemptions(QlBond* o, char **e);
  int qlBondSettlementDate(QlBond* o, int d, char **e);
  int qlBondStartDate(QlBond* o, char **e);
  int qlBondMaturityDate(QlBond *bond);
  QlInstrument *qlBondAsInstrument(QlBond *bond);

  QlFixedRateBond *qlFixedRateBond(unsigned settlDays, double face, Schedule *schedule, unsigned cLen, double *coupons, DayCounter *counter, int payConv, double redemption, int issue, Calendar *payCal, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, DayCounter* firstPeriodDayCounter, char **e);
  QlBond *qlZeroCouponBond(int settlDays, Calendar *cal, double face, int maturity, int payConv, double redemption, int issue, char **e);
  QlBond *qlFloatingRateBond(unsigned settlDays, double face, Schedule *sched, QlIborIndex *index, DayCounter *dc, int payConv, unsigned fixDays,
    unsigned nGearings, double *gearings, unsigned nSpreads, double *spreads, unsigned nCaps, double *caps, unsigned nFloors, double *floors,
    int inArrears, double redemption, int issue, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, int fixingConvention, char **e);
  QlBond *qlCmsRateBond(unsigned settlDays, double faceAmount, Schedule *sched, QlSwapIndex *index, DayCounter *dc,
    int payConv, unsigned fixDays, unsigned nGearings, double *gearings, unsigned nSpreads, double *spreads,
    unsigned nCaps, double *caps, unsigned nFloors, double *floors, int inArrears, double redemption, int issue, char **e);
  QlBond *qlAmortizingCmsRateBond(unsigned settlementDays, unsigned notionalsLen, double *notionals, Schedule *sched,
    QlSwapIndex *index, DayCounter *dc, int payConv, unsigned fixDays, unsigned nGearings, double *gearings,
    unsigned nSpreads, double *spreads, unsigned nCaps, double *caps, unsigned nFloors, double *floors,
    int inArrears, int issue, unsigned redemptionsLen, double *redemptions, char **e);
  QlBond *qlFixedRateBondAsBond(QlFixedRateBond *bond);
  QlCPIBond *qlCPIBond(unsigned settlementDays, double faceAmount, double baseCPI, int obsLagLen, int obsLagUnit, QlZeroInflationIndex* index, int observationInterpolation, Schedule *schedule, unsigned couponsLen, double *coupons, DayCounter *accrualDayCounter, int paymentConvention, int issueDate, Calendar *paymentCalendar, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, char **e);
  QlBond *qlCPIBondAsBond(QlCPIBond *bond);

  QlBond *qlAmortizingFixedRateBond(unsigned settlementDays, unsigned notionalsLen, double *notionals, Schedule *schedule,
    unsigned couponsLen, double *coupons, DayCounter *accrualDayCounter, int paymentConvention, int issueDate,
    int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth,
    unsigned redemptionsLen, double *redemptions, int paymentLag, char **e);
  QlBond *qlAmortizingFloatingRateBond(unsigned settlementDays, unsigned notionalLen, double *notional, Schedule *schedule,
    QlIborIndex *index, DayCounter *accrualDayCounter, int paymentConvention, unsigned fixingDays,
    unsigned nGearings, double *gearings, unsigned nSpreads, double *spreads, unsigned nCaps, double *caps, unsigned nFloors, double *floors,
    int inArrears, int issueDate, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention,
    int exCouponEndOfMonth, unsigned redemptionsLen, double *redemptions, int paymentLag, char **e);
  Schedule *qlSinkingSchedule(int startDate, int lengthLen, int lengthUnit, int frequency, Calendar *paymentCalendar, char **e);
  void qlSinkingNotionals(int lengthLen, int lengthUnit, int frequency, double couponRate, double initialNotional,
    unsigned *len, double **out, char **e);

  double qlBondYield(QlBond* o, DayCounter* dc, int comp, int freq, double accuracy,
    unsigned maxEvaluations, double guess, int priceType, char **e);
  double qlBondAccruedAmount(QlBond* o, int d, char **e);
  double qlBondCleanPrice(QlBond* o, char **e);
  double qlBondCleanPrice1(QlBond* o, double yield, DayCounter* dc, int comp, int freq, int settlementDate, char **e);
  double qlBondDirtyPrice(QlBond* o, char **e);
  double qlBondDirtyPrice1(QlBond* o, double yield, DayCounter* dc, int comp, int freq, int settlementDate, char **e);
  int qlBondNextCashFlowDate(QlBond* o, int d, char **e);
  double qlBondNextCouponRate(QlBond* o, int d, char **e);
  double qlBondNotional(QlBond* o, int d, char **e);
  int qlBondPreviousCashFlowDate(QlBond* o, int d, char **e);
  double qlBondPreviousCouponRate(QlBond* o, int d, char **e);
  double qlBondSettlementValue1(QlBond* o, double cleanPrice, char **e);
  double qlBondSettlementValue(QlBond* o, char **e);
  double qlBondYield1(QlBond* o, double price, int, DayCounter* dc, int comp, int freq, int settlementDate, double accuracy, unsigned maxEvaluations, char **e);
  int qlBondIsTradable(QlBond* o, int d, char **e);
  void qlBondNotionals(QlBond* o, unsigned *len, double **ns, char **e);

  int qlBondFunctionsAccrualDays(QlBond* bond, int settlementDate, char **e);
  int qlBondFunctionsAccrualEndDate(QlBond* bond, int settlementDate, char **e);
  double qlBondFunctionsAccrualPeriod(QlBond* bond, int settlementDate, char **e);
  int qlBondFunctionsAccrualStartDate(QlBond* bond, int settlementDate, char **e);
  int qlBondFunctionsAccruedDays(QlBond* bond, int settlementDate, char **e);
  double qlBondFunctionsAccruedPeriod(QlBond* bond, int settlementDate, char **e);
  double qlBondFunctionsAtmRate(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, double price, int, char **e);
  double qlBondFunctionsBasisPointValue1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double qlBondFunctionsBasisPointValue(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double qlBondFunctionsBps1(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double qlBondFunctionsBps2(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double qlBondFunctionsBps(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, char **e);
  double qlBondFunctionsCleanPrice2(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, char **e);
  double qlBondFunctionsCleanPrice3(QlBond* bond, QlYieldTermStructure* discount, double zSpread, int compounding, int frequency, int settlementDate, char **e);
  double qlBondFunctionsCleanPrice4(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double qlBondFunctionsConvexity1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double qlBondFunctionsConvexity(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double qlBondFunctionsDuration1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int type, int settlementDate, char **e);
  double qlBondFunctionsDuration(QlBond* bond, InterestRate* yield, int type, int settlementDate, char **e);
  double qlBondFunctionsNextCashFlowAmount(QlBond* bond, int refDate, char **e);
  double qlBondFunctionsPreviousCashFlowAmount(QlBond* bond, int refDate, char **e);
  int qlBondFunctionsReferencePeriodEnd(QlBond* bond, int settlementDate, char **e);
  int qlBondFunctionsReferencePeriodStart(QlBond* bond, int settlementDate, char **e);
  double qlBondFunctionsYield2(QlBond* bond, double price, int, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, double accuracy, unsigned maxIterations, double guess, char **e);
  double qlBondFunctionsYieldValueBasisPoint1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e);
  double qlBondFunctionsYieldValueBasisPoint(QlBond* bond, InterestRate* yield, int settlementDate, char **e);
  double qlBondFunctionsZSpread(QlBond* bond, double price, int, QlYieldTermStructure* x2, int compounding, int frequency, int settlementDate, double accuracy, unsigned maxIterations, double guess, char **e);

  void qlFreeBond(QlBond *bond);
  void qlFreeFixedRateBond(QlFixedRateBond *bond);
  void qlFreeCPIBond(QlCPIBond *bond);
  void qlFreeCallableBond(QlCallableBond *o);
  QlBond* qlCallableBondAsBond(QlCallableBond *o);
  void qlFreeConvertibleBond(QlConvertibleBond *o);
  QlBond* qlConvertibleBondAsBond(QlConvertibleBond *o);

  QlCallableBond* qlCallableFixedRateBond(unsigned settlementDays, double faceAmount, Schedule* schedule, unsigned couponsLen, double* coupons, DayCounter* accrualDayCounter, int paymentConvention, double redemption, int issueDate, unsigned putCallScheduleLen, QlCallability** putCallSchedule, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, char **e);
  QlCallableBond* qlCallableZeroCouponBond(unsigned settlementDays, double faceAmount, Calendar* calendar, int maturityDate, DayCounter* dayCounter, int paymentConvention, double redemption, int issueDate, unsigned putCallScheduleLen, QlCallability** putCallSchedule, char **e);
  QlConvertibleBond* qlConvertibleFixedCouponBond(QlExercise* exercise, double conversionRatio, unsigned callabilityLen, QlCallability** callability, int issueDate, unsigned settlementDays, unsigned couponsLen, double* coupons, DayCounter* dayCounter, Schedule* schedule, double redemption, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, char **e);
  QlConvertibleBond* qlConvertibleFloatingRateBond(QlExercise* exercise, double conversionRatio, unsigned callabilityLen, QlCallability** callability, int issueDate, unsigned settlementDays, QlIborIndex* index, unsigned fixingDays, unsigned spreadsLen, double* spreads, DayCounter* dayCounter, Schedule* schedule, double redemption, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, char **e);
  QlConvertibleBond* qlConvertibleZeroCouponBond(QlExercise* exercise, double conversionRatio, unsigned callabilityLen, QlCallability** callability, int issueDate, unsigned settlementDays, DayCounter* dayCounter, Schedule* schedule, double redemption, char **e);
  QlCallability* qlSoftCallability(double price, int priceType, int date, double trigger, char **e);

  Leg *qlLeg(unsigned len, double *amounts, int *dates, char **e);
  int qlLegStartDate(Leg *leg, char **e);

  void qlFreeLeg(Leg *leg);
  Leg *qlNextCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate, char **e);
  Leg *qlPreviousCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate, char **e);
  void qlLegCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate, unsigned *al, double **amount, unsigned *dl, int **date, unsigned *hl, int **hasOccurred, char **e);

  double qlCashFlowsDuration(Leg* leg, InterestRate* yield, int type, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  int qlCashFlowsAccrualDays(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int qlCashFlowsAccrualEndDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double qlCashFlowsAccrualPeriod(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int qlCashFlowsAccrualStartDate(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  double qlCashFlowsAccruedAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int qlCashFlowsAccruedDays(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double qlCashFlowsAccruedPeriod(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double qlCashFlowsAtmRate(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, double npv, char **e);
  double qlCashFlowsBasisPointValue1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsBasisPointValue(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsBps1(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsBps2(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsBps(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsConvexity1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsConvexity(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsDuration1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int type, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  int qlCashFlowsIsExpired(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int qlCashFlowsMaturityDate(Leg* leg, char **e);
  double qlCashFlowsNextCashFlowAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int qlCashFlowsNextCashFlowDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double qlCashFlowsNextCouponRate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double qlCashFlowsNominal(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  double qlCashFlowsNpv1(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsNpv2(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsNpv3(Leg* leg, QlYieldTermStructure* discount, double zSpread, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsNpv(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  void qlCashFlowsNpvbps(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, double *npv, double *bps, char **e);
  double qlCashFlowsPreviousCashFlowAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int qlCashFlowsPreviousCashFlowDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  double qlCashFlowsPreviousCouponRate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e);
  int qlCashFlowsReferencePeriodEnd(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  int qlCashFlowsReferencePeriodStart(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e);
  double qlCashFlowsYield(Leg* leg, double npv, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, char **e);
  double qlCashFlowsYieldValueBasisPoint1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsYieldValueBasisPoint(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e);
  double qlCashFlowsZSpread(Leg* leg, double npv, QlYieldTermStructure* x2, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, char **e);

  void qlQuantLibSetCouponPricer(Leg* leg, QlFloatingRateCouponPricer* x1, char **e);
  void qlQuantLibSetCouponPricers(Leg* leg, unsigned x1Len, QlFloatingRateCouponPricer** x1, char **e);

  void qlCouponAccrualStartDates(CouponLeg* o, unsigned *len, int **days, char **e);

  void qlFreeDividend(QlDividend *o);
  QlDividend* qlFixedDividend(double amount, int date, char **e);
  QlDividend* qlFractionalDividend1(double rate, double nominal, int date, char **e);
  QlDividend* qlFractionalDividend(double rate, int date, char **e);

  Leg* qlAverageBMALeg(Schedule* schedule, QlBMAIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, char **e);
  Leg* qlFixedRateLeg(Schedule* schedule, unsigned NotionalsLen, double* Notionals, unsigned couponRatesLen, InterestRate** couponRates, int paymentAdjustment, DayCounter* firstPeriodDayCounter, Calendar* paymentCalendar, char **e);
  Leg* qlIborLeg(Schedule* schedule, QlIborIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned capsLen, double* caps, unsigned floorsLen, double* floors, int inArrears, int zeroPayments,
    int paymentLag, Calendar* paymentCalendar, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, int fixingConvention, int useIndexedCoupons, char **e);
  Leg* qlCmsLeg(Schedule* schedule, QlSwapIndex* swapIndex, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned capsLen, double* caps, unsigned floorsLen, double* floors, int inArrears, int zeroPayments,
    int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, int fixingConvention, char **e);
  Leg* qlOvernightLeg(Schedule* schedule, QlOvernightIndex* overnightIndex, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, char **e);
  Leg* qlRangeAccrualLeg(Schedule* schedule, QlIborIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned lowerTriggersLen, double* lowerTriggers, unsigned upperTriggersLen, double* upperTriggers, int, int, int observationConvention, char **e);
  void qlFreeCouponLeg(CouponLeg *o);
  Leg* qlCouponLegAsLeg(CouponLeg *o);

  CouponLeg* qlLegToCouponLeg(Leg *o, char **e);
  Leg* qlCPILeg(Schedule* schedule, QlZeroInflationIndex* index, double baseCPI, int obsLagLen, int obsLagUnit, unsigned notionalsLen, double* notionals, unsigned fixedRatesLen, double* fixedRates, DayCounter* paymentDayCounter, int paymentAdjustment, Calendar* paymentCalendar, int observationInterpolation, int subtractInflationNominal, char **e);
  Leg* qlYoYInflationLeg(Schedule* schedule, Calendar* cal, QlYoYInflationIndex* index, int obsLagLen, int obsLagUnit, int interpolation, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, char **e);

  void qlFreeZeroInflationCashFlow(QlZeroInflationCashFlow *o);
  QlZeroInflationCashFlow* qlZeroInflationCashFlow(double notional, QlZeroInflationIndex* index, int observationInterpolation, int startDate, int endDate, int obsLagLen, int obsLagUnit, int paymentDate, int growthOnly, char **e);
  double qlZeroInflationCashFlowAmount(QlZeroInflationCashFlow* o, char **e);
  double qlZeroInflationCashFlowBaseFixing(QlZeroInflationCashFlow* o, char **e);
  double qlZeroInflationCashFlowIndexFixing(QlZeroInflationCashFlow* o, char **e);

  void qlFreeCPICashFlow(QlCPICashFlow *o);
  QlCPICashFlow* qlCPICashFlow(double notional, QlZeroInflationIndex* index, int baseDate, double baseFixing, int observationDate, int obsLagLen, int obsLagUnit, int interpolation, int paymentDate, int growthOnly, char **e);
  double qlCPICashFlowAmount(QlCPICashFlow* o, char **e);
  double qlCPICashFlowBaseFixing(QlCPICashFlow* o, char **e);
  double qlCPICashFlowIndexFixing(QlCPICashFlow* o, char **e);

  void qlFreeEquityCashFlow(QlEquityCashFlow *o);
  QlEquityCashFlow* qlEquityCashFlow(double notional, QlEquityIndex* index, int baseDate, int fixingDate, int paymentDate, int growthOnly, char **e);
  double qlEquityCashFlowAmount(QlEquityCashFlow* o, char **e);
  double qlEquityCashFlowBaseFixing(QlEquityCashFlow* o, char **e);
  double qlEquityCashFlowIndexFixing(QlEquityCashFlow* o, char **e);
  void qlEquityCashFlowSetPricer(QlEquityCashFlow* o, QlEquityCashFlowPricer* pricer, char **e);

  void qlFreeEquityCashFlowPricer(QlEquityCashFlowPricer *o);
  QlEquityCashFlowPricer* qlEquityQuantoCashFlowPricer(QlYieldTermStructure* quantoCurrencyTermStructure, QlBlackVolTermStructure* equityVolatility, QlBlackVolTermStructure* fxVolatility, QlQuote* correlation, char **e);
  void qlQuantLibSetEquityCashFlowPricer(Leg* leg, QlEquityCashFlowPricer* pricer, char **e);

  QlFloatingRateCouponPricer *qlBlackIborCouponPricer(QlOptionletVolatilityStructure *vol, int timingAdjustment, QlQuote *correlation, int useIndexedCoupon, char **e);
  void qlFreeFloatingCouponPricer(QlFloatingRateCouponPricer *p);
  QlFloatingRateCouponPricer* qlAnalyticHaganPricer(QlSwaptionVolatilityStructure* swaptionVol, int modelOfYieldCurve, QlQuote* meanReversion, char **e);
  QlFloatingRateCouponPricer* qlNumericHaganPricer(QlSwaptionVolatilityStructure* swaptionVol, int modelOfYieldCurve, QlQuote* meanReversion, double lowerLimit, double upperLimit, double precision, double hardUpperLimit, char **e);
  QlFloatingRateCouponPricer* qlLinearTsrPricer(QlSwaptionVolatilityStructure* swaptionVol, QlQuote* meanReversion, QlYieldTermStructure* couponDiscountCurve, int strategy, double param, int haveBounds, double lowerBound, double upperBound, char **e);
  QlFloatingRateCouponPricer* qlRangeAccrualPricerByBgm(double correlation, QlSmileSection* smilesOnExpiry, QlSmileSection* smilesOnPayment, int withSmile, int byCallSpread, char **e);

  void qlFreeVarianceSwap(QlVarianceSwap *o);
  QlInstrument* qlVarianceSwapAsInstrument(QlVarianceSwap *o);
  QlVarianceSwap* qlVarianceSwap(int position, double strike, double notional, int startDate, int maturityDate, char **e);
  double qlVarianceSwapVariance(QlVarianceSwap* o, char **e);

  void qlFreeVarianceOption(QlVarianceOption *o);
  QlInstrument* qlVarianceOptionAsInstrument(QlVarianceOption *o);
  QlVarianceOption* qlVarianceOption(QlPayoff* payoff, double notional, int startDate, int maturityDate, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
