// Discriminants shared by the C++ shim and c2hs. They must remain outside the __cplusplus guard
// because the c2hs preprocessor does not define it.
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
    struct QlAdditionalResult **out, QlError **e);
  void qlFreeAdditionalResults(unsigned len, struct QlAdditionalResult *out);

  void qlInstrumentSetPricingEngine(QlInstrument *instr, QlPricingEngine *eng,
    QlError **e);
  QlInstrument* qlPerpetualFutures(int payoffType, int fundingType,
    int fundingFrequencyLength, int fundingFrequencyUnit, Calendar* cal,
    DayCounter* dc, QlError **e);
  double qlInstrumentNPV(QlInstrument *instr, QlError **e);
  void qlFreeInstrument(QlInstrument *instr);
  QlInstrument* qlCompositeInstrument(unsigned instrLen, QlInstrument **instrs, unsigned cLen, double *coeff, QlError **e);
  double qlInstrumentErrorEstimate(QlInstrument* o, QlError **e);
  int qlInstrumentIsExpired(QlInstrument* o, QlError **e);
  int qlInstrumentValuationDate(QlInstrument* o, QlError **e);
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

  // Native payoffs retain shared callback ownership for their complete lifetime.
  QlPayoff* qlPayoffFromFunction(const char* name, const char* description,
    QlCallback* fn, QlError **e);
  // accumulate() takes the whole underlying-state vector at once, so this one crosses the
  // language boundary once per evaluation, not once per component.
  QlBasketPayoff* qlBasketPayoffFromFunction(QlPayoff* base,
    QlCallback* fn, QlError **e);
  // As qlPayoffFromFunction, but a real StrikedTypePayoff: the (type, strike) pair is advisory --
  // it does not define the payoff, it is what QuantLib's FD vanilla engines downcast to reach for
  // when sizing their mesher. description() comes from StrikedTypePayoff itself, so unlike
  // qlPayoffFromFunction there is no description argument.
  QlStrikedTypePayoff* qlStrikedPayoffFromFunction(int type, double strike, const char* name,
    QlCallback* fn, QlError **e);

  QlStrikedTypePayoff* qlAssetOrNothingPayoff(int type, double strike, QlError **e);
  QlBasketPayoff* qlAverageBasketPayoff(QlPayoff* p, unsigned n, QlError **e);
  QlBasketPayoff* qlAverageBasketPayoff1(QlPayoff* p, unsigned aLen, double* a, QlError **e);
  QlStrikedTypePayoff* qlCashOrNothingPayoff(int type, double strike, double cashPayoff, QlError **e);
  QlPayoff* qlDoubleStickyRatchetPayoff(double type1, double type2, double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, QlError **e);
  QlTypePayoff* qlFloatingTypePayoff(int type, QlError **e);
  QlPayoff* qlForwardTypePayoff(int type, double strike, QlError **e);
  QlStrikedTypePayoff* qlGapPayoff(int type, double strike, double secondStrike, QlError **e);
  QlBasketPayoff* qlMaxBasketPayoff(QlPayoff* p, QlError **e);
  QlBasketPayoff* qlMinBasketPayoff(QlPayoff* p, QlError **e);
  QlPercentageStrikePayoff* qlPercentageStrikePayoff(int type, double moneyness, QlError **e);
  QlPlainVanillaPayoff* qlPlainVanillaPayoff(int type, double strike, QlError **e);
  QlPayoff* qlRatchetMaxPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, QlError **e);
  QlPayoff* qlRatchetMinPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, QlError **e);
  QlPayoff* qlRatchetPayoff(double gearing1, double gearing2, double spread1, double spread2, double initialValue, double accrualFactor, QlError **e);
  QlBasketPayoff* qlSpreadBasketPayoff(QlPayoff* p, QlError **e);
  QlPayoff* qlStickyMaxPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, QlError **e);
  QlPayoff* qlStickyMinPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, QlError **e);
  QlPayoff* qlStickyPayoff(double gearing1, double gearing2, double spread1, double spread2, double initialValue, double accrualFactor, QlError **e);
  QlStrikedTypePayoff* qlSuperFundPayoff(double strike, double secondStrike, QlError **e);
  QlStrikedTypePayoff* qlSuperSharePayoff(double strike, double secondStrike, double cashPayoff, QlError **e);

  void qlFreeAmericanExercise(QlAmericanExercise *o);
  QlExercise* qlAmericanExerciseAsExercise(QlAmericanExercise *o);
  void qlFreeBermudanExercise(QlBermudanExercise *o);
  QlExercise* qlBermudanExerciseAsExercise(QlBermudanExercise *o);
  void qlFreeEuropeanExercise(QlEuropeanExercise *o);
  QlExercise* qlEuropeanExerciseAsExercise(QlEuropeanExercise *o);
  void qlFreeExercise(QlExercise *o);
  QlAmericanExercise* qlAmericanExercise(int earliestDate, int latestDate, int payoffAtExpiry, QlError **e);
  QlBermudanExercise* qlBermudanExercise(unsigned datesLen, int *dates, int payoffAtExpiry, QlError **e);
  QlExercise* qlEarlyExercise(int type, int payoffAtExpiry, QlError **e);
  QlExercise* qlExercise(int type, QlError **e);
  QlEuropeanExercise* qlEuropeanExercise(int date, QlError **e);

  QlAmericanExercise* qlAmericanExercise1(int latestDate, int payoffAtExpiry, QlError **e);
  QlSwingExercise* qlSwingExercise(unsigned datesLen, int* dates, unsigned secLen, unsigned* seconds, QlError **e);
  QlSwingExercise* qlSwingExercise1(int from, int to, unsigned stepSizeSecs, QlError **e);
  QlExercise* qlSwingExerciseAsExercise(QlSwingExercise *o);

  void qlFreeRebatedExercise(QlRebatedExercise *o);
  QlExercise* qlRebatedExerciseAsExercise(QlRebatedExercise *o);
  QlRebatedExercise* qlRebatedExercise(QlExercise* exercise, double rebate, unsigned rebateSettlementDays, Calendar* rebatePaymentCalendar, int rebatePaymentConvention, QlError **e);

  void qlFreeCapFloor(QlCapFloor *o);
  QlInstrument* qlCapFloorAsInstrument(QlCapFloor *o);
  QlCapFloor* qlCap(Leg* floatingLeg, unsigned exerciseRatesLen, double* exerciseRates, QlError **e);
  QlCapFloor* qlCollar(Leg* floatingLeg, unsigned capRatesLen, double* capRates, unsigned floorRatesLen, double* floorRates, QlError **e);
  QlCapFloor* qlFloor(Leg* floatingLeg, unsigned exerciseRatesLen, double* exerciseRates, QlError **e);
  double qlCapFloorAtmRate(QlCapFloor* o, QlYieldTermStructure* discountCurve, QlError **e);
  double qlCapFloorImpliedVolatility(QlCapFloor* o, double price, QlYieldTermStructure* disc, double guess, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, int type, double displacement, QlError **e);
  QlCapFloor* qlCapFloorOptionlet(QlCapFloor* o, unsigned n, QlError **e);

  void qlFreeCallability(QlCallability *o);
  QlCallability* qlCallability(double price, int priceType, int type, int date, QlError **e);
  void qlFreeBondForward(QlBondForward *fwd);
  QlForward* qlBondForwardAsForward(QlBondForward *fwd);
  QlBondForward* qlBondForward(int valueDate, int maturityDate, int type, double strike, unsigned settlementDays, DayCounter* dayCounter, Calendar* calendar, int businessDayConvention, QlBond* fixedCouponBond, QlYieldTermStructure* discountCurve, QlYieldTermStructure* incomeDiscountCurve, QlError **e);
  double qlBondForwardCleanForwardPrice(QlBondForward* o, QlError **e);
  double qlBondForwardForwardPrice(QlBondForward* o, QlError **e);
  void qlFreeForward(QlForward *fwd);
  QlInstrument* qlForwardAsInstrument(QlForward *fwd);
  double qlForwardForwardValue(QlForward* o, QlError **e);
  InterestRate* qlForwardImpliedYield(QlForward* o, double underlyingSpotValue, double forwardValue, int settlementDate, int compoundingConvention, DayCounter* dayCounter, QlError **e);
  int qlForwardSettlementDate(QlForward* o, QlError **e);
  double qlForwardSpotIncome(QlForward* o, QlYieldTermStructure* incomeDiscountCurve, QlError **e);
  double qlForwardSpotValue(QlForward* o, QlError **e);
  void qlFreeForwardRateAgreement(QlForwardRateAgreement *fwd);
  QlInstrument* qlForwardRateAgreementAsInstrument(QlForwardRateAgreement *fwd);
  QlForwardRateAgreement* qlForwardRateAgreement(QlIborIndex* index, int valueDate, int maturityDate, int type, double strikeForwardRate, double notionalAmount, QlYieldTermStructure* discountCurve, QlError **e);

  InterestRate* qlForwardRateAgreementForwardRate(QlForwardRateAgreement* o, QlError **e);

  void qlFreeFxForward(QlFxForward *fwd);
  QlInstrument* qlFxForwardAsInstrument(QlFxForward *fwd);
  QlFxForward* qlFxForward(double sourceNominal, Currency* sourceCurrency, double targetNominal, Currency* targetCurrency, int maturityDate, int paySourceCurrency, unsigned settlementDays, Calendar* paymentCalendar, QlError **e);
  QlFxForward* qlFxForward1(double sourceNominal, Currency* sourceCurrency, Currency* targetCurrency, double forwardRate, int maturityDate, int paySourceCurrency, unsigned settlementDays, Calendar* paymentCalendar, QlError **e);
  double qlForwardRateAgreementAmount(QlForwardRateAgreement* o, QlError **e);
  double qlFxForwardForwardRate(QlFxForward* o);
  double qlFxForwardFairForwardRate(QlFxForward* o, QlError **e);
  double qlFxForwardNpvSourceCurrency(QlFxForward* o, QlError **e);
  double qlFxForwardNpvTargetCurrency(QlFxForward* o, QlError **e);

  void qlFreeSwap(QlSwap *o);
  QlInstrument* qlSwapAsInstrument(QlSwap *o);
  void qlFreeFixedVsFloatingSwap(QlFixedVsFloatingSwap *o);
  QlSwap* qlFixedVsFloatingSwapAsSwap(QlFixedVsFloatingSwap *o);
  void qlFreeVanillaSwap(QlVanillaSwap *o);
  QlFixedVsFloatingSwap* qlVanillaSwapAsFixedVsFloatingSwap(QlVanillaSwap *o);
  void qlFreeNonstandardSwap(QlNonstandardSwap *o);
  QlSwap* qlNonstandardSwapAsSwap(QlNonstandardSwap *o);
  void qlFreeFloatFloatSwap(QlFloatFloatSwap *o);
  QlSwap* qlFloatFloatSwapAsSwap(QlFloatFloatSwap *o);
  void qlFreeBMASwap(QlBMASwap *o);
  QlSwap* qlBMASwapAsSwap(QlBMASwap *o);
  void qlFreeOvernightIndexedSwap(QlOvernightIndexedSwap *o);
  QlSwap* qlOvernightIndexedSwapAsSwap(QlOvernightIndexedSwap *o);
  void qlFreeAssetSwap(QlAssetSwap *o);
  QlSwap* qlAssetSwapAsSwap(QlAssetSwap *o);
  void qlFreeZeroCouponInflationSwap(QlZeroCouponInflationSwap *o);
  QlSwap* qlZeroCouponInflationSwapAsSwap(QlZeroCouponInflationSwap *o);
  QlZeroCouponInflationSwap* qlZeroCouponInflationSwap(int type, double nominal, int startDate, int maturity, Calendar* cal, int paymentConvention, DayCounter* dayCounter, double fixedRate, QlZeroInflationIndex* index, int obsLagLen, int obsLagUnit, int observationInterpolation, int adjustInfObsDates, Calendar* infCalendar, int infConvention, QlError **e);
  double qlZeroCouponInflationSwapFairRate(QlZeroCouponInflationSwap* o, QlError **e);
  void qlFreeYearOnYearInflationSwap(QlYearOnYearInflationSwap *o);
  QlSwap* qlYearOnYearInflationSwapAsSwap(QlYearOnYearInflationSwap *o);
  QlYearOnYearInflationSwap* qlYearOnYearInflationSwap(int type, double nominal, Schedule* fixedSchedule, double fixedRate, DayCounter* fixedDayCount, Schedule* yoySchedule, QlYoYInflationIndex* yoyIndex, int obsLagLen, int obsLagUnit, int interpolation, double spread, DayCounter* yoyDayCount, Calendar* paymentCalendar, int paymentConvention, QlError **e);
  double qlYearOnYearInflationSwapFairRate(QlYearOnYearInflationSwap* o, QlError **e);
  double qlYearOnYearInflationSwapFairSpread(QlYearOnYearInflationSwap* o, QlError **e);
  void qlFreeCPISwap(QlCPISwap *o);
  QlSwap* qlCPISwapAsSwap(QlCPISwap *o);
  QlCPISwap* qlCPISwap(int type, double nominal, int subtractInflationNominal, double spread, DayCounter* floatDayCount, Schedule* floatSchedule, int floatRoll, unsigned fixingDays, QlIborIndex* floatIndex, double fixedRate, double baseCPI, DayCounter* fixedDayCount, Schedule* fixedSchedule, int fixedRoll, int obsLagLen, int obsLagUnit, QlZeroInflationIndex* fixedIndex, int observationInterpolation, double inflationNominal, QlError **e);
  double qlCPISwapFairRate(QlCPISwap* o, QlError **e);
  double qlCPISwapFairSpread(QlCPISwap* o, QlError **e);
  void qlFreeZeroCouponSwap(QlZeroCouponSwap *o);
  QlSwap* qlZeroCouponSwapAsSwap(QlZeroCouponSwap *o);
  QlZeroCouponSwap* qlZeroCouponSwap(int type, double baseNominal, int startDate, int maturityDate, double fixedPayment, QlIborIndex* iborIndex, Calendar* paymentCalendar, int paymentConvention, unsigned paymentDelay, QlError **e);
  QlZeroCouponSwap* qlZeroCouponSwap1(int type, double baseNominal, int startDate, int maturityDate, double fixedRate, DayCounter* fixedDayCounter, QlIborIndex* iborIndex, Calendar* paymentCalendar, int paymentConvention, unsigned paymentDelay, QlError **e);
  double qlZeroCouponSwapFairFixedPayment(QlZeroCouponSwap* o, QlError **e);
  double qlZeroCouponSwapFairFixedRate(QlZeroCouponSwap* o, DayCounter* dayCounter, QlError **e);
  QlOvernightIndexedSwap* qlOvernightIndexedSwap(int type, double nominal, Schedule* schedule, double fixedRate, DayCounter* fixedDC, QlOvernightIndex* overnightIndex, double spread, int paymentLag, int paymentAdjustment, Calendar* paymentCalendar, int telescopicValueDates, int averagingMethod, unsigned lookbackDays, unsigned lockoutDays, int applyObservationShift, int roundingPrecision, QlError **e);
  QlOvernightIndexedSwap* qlOvernightIndexedSwap1(int type, unsigned nominalsLen, double* nominals, Schedule* schedule, double fixedRate, DayCounter* fixedDC, QlOvernightIndex* overnightIndex, double spread, int paymentLag, int paymentAdjustment, Calendar* paymentCalendar, int telescopicValueDates, int averagingMethod, unsigned lookbackDays, unsigned lockoutDays, int applyObservationShift, int roundingPrecision, QlError **e);
  QlSwap* qlSwap1(unsigned legsLen, Leg** legs, unsigned payerLen, int *payer, QlError **e);
  QlAssetSwap* qlAssetSwap(int payBondCoupon, QlBond* bond, double bondCleanPrice, QlIborIndex* iborIndex, double spread, Schedule* floatSchedule, DayCounter* floatingDayCount, int parAssetSwap, double gearing, double nonParRepayment, int dealMaturity, QlError **e);
  QlBMASwap* qlBMASwap(int type, double nominal, Schedule* liborSchedule, double liborFraction, double liborSpread, QlIborIndex* liborIndex, DayCounter* liborDayCount, Schedule* bmaSchedule, QlBMAIndex* bmaIndex, DayCounter* bmaDayCount, QlError **e);
  QlVanillaSwap* qlVanillaSwap(int type, double nominal, Schedule* fixedSchedule, double fixedRate, DayCounter* fixedDayCount, Schedule* floatSchedule, QlIborIndex* iborIndex, double spread, DayCounter* floatingDayCount, int paymentConvention, int useIndexedCoupons, QlError **e);
  QlNonstandardSwap* qlNonstandardSwap1(QlFixedVsFloatingSwap* v, QlError **e);
  QlNonstandardSwap* qlNonstandardSwap(int type, unsigned fixedNominalLen, double* fixedNominal, unsigned floatingNominalLen, double* floatingNominal, Schedule* fixedSchedule, unsigned fixedRateLen, double* fixedRate, DayCounter* fixedDayCount, Schedule* floatingSchedule, QlIborIndex* iborIndex, double gearing, double spread, DayCounter* floatingDayCount, int intermediateCapitalExchange, int finalCapitalExchange, int paymentConvention, int paymentLag, Calendar* paymentCalendar, QlError **e);
  QlNonstandardSwap* qlNonstandardSwap2(int type, unsigned fixedNominalLen, double* fixedNominal, unsigned floatingNominalLen, double* floatingNominal, Schedule* fixedSchedule, unsigned fixedRateLen, double* fixedRate, DayCounter* fixedDayCount, Schedule* floatingSchedule, QlIborIndex* iborIndex, unsigned gearingLen, double* gearing, unsigned spreadLen, double* spread, DayCounter* floatingDayCount, int intermediateCapitalExchange, int finalCapitalExchange, int paymentConvention, int paymentLag, Calendar* paymentCalendar, QlError **e);
  void qlNonstandardSwapFixedRate(QlNonstandardSwap* o, unsigned *len, double **out, QlError **e);
  QlFloatFloatSwap* qlFloatFloatSwap(int type, double nominal1, double nominal2, Schedule* schedule1, QlInterestRateIndex* index1, DayCounter* dayCount1, Schedule* schedule2, QlInterestRateIndex* index2, DayCounter* dayCount2, int intermediateCapitalExchange, int finalCapitalExchange, double gearing1, double spread1, double cappedRate1, double flooredRate1, double gearing2, double spread2, double cappedRate2, double flooredRate2, int paymentConvention1, int paymentConvention2, QlError **e);
  QlFloatFloatSwap* qlFloatFloatSwap2(int type, unsigned nominal1Len, double* nominal1, unsigned nominal2Len, double* nominal2, Schedule* schedule1, QlInterestRateIndex* index1, DayCounter* dayCount1, Schedule* schedule2, QlInterestRateIndex* index2, DayCounter* dayCount2, int intermediateCapitalExchange, int finalCapitalExchange, unsigned gearing1Len, double* gearing1, unsigned spread1Len, double* spread1, unsigned cappedRate1Len, double* cappedRate1, unsigned flooredRate1Len, double* flooredRate1, unsigned gearing2Len, double* gearing2, unsigned spread2Len, double* spread2, unsigned cappedRate2Len, double* cappedRate2, unsigned flooredRate2Len, double* flooredRate2, int paymentConvention1, int paymentConvention2, QlError **e);
  double qlFloatFloatSwapFairSpread1(QlFloatFloatSwap* o, QlError **e);
  double qlFloatFloatSwapFairSpread2(QlFloatFloatSwap* o, QlError **e);
  QlSwap* qlSwap(Leg* firstLeg, Leg* secondLeg, QlError **e);
  unsigned qlSwapNumberOfLegs(QlSwap* o, QlError **e);
  Leg* qlSwapLeg(QlSwap* o, unsigned j, QlError **e);
  Leg* qlFixedVsFloatingSwapFixedLeg(QlFixedVsFloatingSwap* o, QlError **e);
  Leg* qlFixedVsFloatingSwapFloatingLeg(QlFixedVsFloatingSwap* o, QlError **e);
  void qlFreeConstNotionalCrossCurrencySwap(QlConstNotionalCrossCurrencySwap *o);
  QlSwap* qlConstNotionalCrossCurrencySwapAsSwap(QlConstNotionalCrossCurrencySwap *o);
  QlConstNotionalCrossCurrencySwap* qlConstNotionalCrossCurrencySwap(Leg* firstLeg, Currency* firstLegCcy, Leg* secondLeg, Currency* secondLegCcy, QlError **e);
  QlConstNotionalCrossCurrencySwap* qlConstNotionalCrossCurrencySwap1(unsigned legsLen, Leg** legs, unsigned payerLen, int* payer, unsigned currenciesLen, Currency** currencies, QlError **e);
  Currency* qlConstNotionalCrossCurrencySwapLegCurrency(QlConstNotionalCrossCurrencySwap* o, unsigned j, QlError **e);
  double qlConstNotionalCrossCurrencySwapInCcyLegBPS(QlConstNotionalCrossCurrencySwap* o, unsigned j, QlError **e);
  double qlConstNotionalCrossCurrencySwapInCcyLegNPV(QlConstNotionalCrossCurrencySwap* o, unsigned j, QlError **e);
  double qlConstNotionalCrossCurrencySwapNpvDateDiscounts(QlConstNotionalCrossCurrencySwap* o, unsigned j, QlError **e);

  void qlFreeConstNotionalCrossCurrencyBasisSwap(QlConstNotionalCrossCurrencyBasisSwap *o);
  QlConstNotionalCrossCurrencySwap* qlConstNotionalCrossCurrencyBasisSwapAsConstNotionalCrossCurrencySwap(QlConstNotionalCrossCurrencyBasisSwap *o);
  QlConstNotionalCrossCurrencyBasisSwap* qlConstNotionalCrossCurrencyBasisSwap(
    double payNominal, Currency* payCurrency, Schedule* paySchedule, QlIborIndex* payIndex, double paySpread, double payGearing,
    double recNominal, Currency* recCurrency, Schedule* recSchedule, QlIborIndex* recIndex, double recSpread, double recGearing,
    int payPaymentLag, int recPaymentLag,
    int payCompoundSpread, unsigned payLookbackDays, int payObservationShift, unsigned payLockoutDays, int payAveragingMethod,
    int recCompoundSpread, unsigned recLookbackDays, int recObservationShift, unsigned recLockoutDays, int recAveragingMethod,
    int telescopicValueDates, int useIndexedCoupons, int paymentLagOnNotionalExchanges, QlStubIndexSelection* payStub, QlStubIndexSelection* recStub, QlError **e);
  double qlConstNotionalCrossCurrencyBasisSwapFairPaySpread(QlConstNotionalCrossCurrencyBasisSwap* o, QlError **e);
  double qlConstNotionalCrossCurrencyBasisSwapFairRecSpread(QlConstNotionalCrossCurrencyBasisSwap* o, QlError **e);

  void qlFreeConstNotionalCrossCurrencyFixedVsFloatingSwap(QlConstNotionalCrossCurrencyFixedVsFloatingSwap *o);
  QlConstNotionalCrossCurrencySwap* qlConstNotionalCrossCurrencyFixedVsFloatingSwapAsConstNotionalCrossCurrencySwap(QlConstNotionalCrossCurrencyFixedVsFloatingSwap *o);
  QlConstNotionalCrossCurrencyFixedVsFloatingSwap* qlConstNotionalCrossCurrencyFixedVsFloatingSwap(
    int type, double fixedNominal, Currency* fixedCurrency, Schedule* fixedSchedule, double fixedRate,
    DayCounter* fixedDayCount, int fixedPaymentBdc, unsigned fixedPaymentLag, Calendar* fixedPaymentCalendar,
    double floatNominal, Currency* floatCurrency, Schedule* floatSchedule, QlIborIndex* floatIndex, double floatSpread,
    int floatPaymentBdc, unsigned floatPaymentLag, Calendar* floatPaymentCalendar,
    int telescopicValueDates, int floatCompoundSpread, unsigned floatLookbackDays, int floatObservationShift,
    unsigned floatLockoutDays, int floatAveragingMethod, int useIndexedCoupons, QlStubIndexSelection* floatStub, QlError **e);
  double qlConstNotionalCrossCurrencyFixedVsFloatingSwapFairRate(QlConstNotionalCrossCurrencyFixedVsFloatingSwap* o, QlError **e);
  double qlConstNotionalCrossCurrencyFixedVsFloatingSwapFairSpread(QlConstNotionalCrossCurrencyFixedVsFloatingSwap* o, QlError **e);

  Leg* qlAssetSwapBondLeg(QlAssetSwap* o, QlError **e);
  Leg* qlAssetSwapFloatingLeg(QlAssetSwap* o, QlError **e);
  Leg* qlBMASwapBmaLeg(QlBMASwap* o, QlError **e);
  Leg* qlBMASwapLiborLeg(QlBMASwap* o, QlError **e);
  Leg* qlOvernightIndexedSwapFixedLeg(QlOvernightIndexedSwap* o, QlError **e);
  Leg* qlOvernightIndexedSwapOvernightLeg(QlOvernightIndexedSwap* o, QlError **e);
  double qlAssetSwapCleanPrice(QlAssetSwap* o, QlError **e);
  double qlAssetSwapFairCleanPrice(QlAssetSwap* o, QlError **e);
  double qlAssetSwapFairNonParRepayment(QlAssetSwap* o, QlError **e);
  double qlAssetSwapFairSpread(QlAssetSwap* o, QlError **e);
  double qlAssetSwapFloatingLegBPS(QlAssetSwap* o, QlError **e);
  double qlAssetSwapFloatingLegNPV(QlAssetSwap* o, QlError **e);
  double qlAssetSwapNonParRepayment(QlAssetSwap* o, QlError **e);
  int qlAssetSwapParSwap(QlAssetSwap* o, QlError **e);
  int qlAssetSwapPayBondCoupon(QlAssetSwap* o, QlError **e);
  double qlBMASwapBmaLegBPS(QlBMASwap* o, QlError **e);
  double qlBMASwapBmaLegNPV(QlBMASwap* o, QlError **e);
  double qlBMASwapFairLiborFraction(QlBMASwap* o, QlError **e);
  double qlBMASwapFairLiborSpread(QlBMASwap* o, QlError **e);
  double qlBMASwapLiborFraction(QlBMASwap* o, QlError **e);
  double qlBMASwapLiborLegBPS(QlBMASwap* o, QlError **e);
  double qlBMASwapLiborLegNPV(QlBMASwap* o, QlError **e);
  double qlOvernightIndexedSwapFairRate(QlOvernightIndexedSwap* o, QlError **e);
  double qlOvernightIndexedSwapFairSpread(QlOvernightIndexedSwap* o, QlError **e);
  double qlOvernightIndexedSwapFixedLegBPS(QlOvernightIndexedSwap* o, QlError **e);
  double qlOvernightIndexedSwapFixedLegNPV(QlOvernightIndexedSwap* o, QlError **e);
  double qlOvernightIndexedSwapOvernightLegBPS(QlOvernightIndexedSwap* o, QlError **e);
  double qlOvernightIndexedSwapOvernightLegNPV(QlOvernightIndexedSwap* o, QlError **e);
  double qlSwapEndDiscounts(QlSwap* o, unsigned j, QlError **e);
  double qlSwapLegBPS(QlSwap* o, unsigned j, QlError **e);
  double qlSwapLegNPV(QlSwap* o, unsigned j, QlError **e);
  int qlSwapMaturityDate(QlSwap* o, QlError **e);
  double qlSwapNpvDateDiscount(QlSwap* o, QlError **e);
  int qlSwapStartDate(QlSwap* o, QlError **e);
  double qlSwapStartDiscounts(QlSwap* o, unsigned j, QlError **e);
  double qlFixedVsFloatingSwapFairRate(QlFixedVsFloatingSwap* o, QlError **e);
  double qlFixedVsFloatingSwapFairSpread(QlFixedVsFloatingSwap* o, QlError **e);
  double qlFixedVsFloatingSwapFixedLegBPS(QlFixedVsFloatingSwap* o, QlError **e);
  double qlFixedVsFloatingSwapFixedLegNPV(QlFixedVsFloatingSwap* o, QlError **e);
  double qlFixedVsFloatingSwapFloatingLegBPS(QlFixedVsFloatingSwap* o, QlError **e);
  double qlFixedVsFloatingSwapFloatingLegNPV(QlFixedVsFloatingSwap* o, QlError **e);

  void qlFreeEquityTotalReturnSwap(QlEquityTotalReturnSwap *o);
  QlSwap* qlEquityTotalReturnSwapAsSwap(QlEquityTotalReturnSwap *o);
  QlEquityTotalReturnSwap* qlEquityTotalReturnSwapIbor(int type, double nominal, Schedule* schedule, QlEquityIndex* equityIndex, QlIborIndex* interestRateIndex, DayCounter* dayCounter, double margin, double gearing, Calendar* paymentCalendar, int paymentConvention, unsigned paymentDelay, QlError **e);
  QlEquityTotalReturnSwap* qlEquityTotalReturnSwapOvernight(int type, double nominal, Schedule* schedule, QlEquityIndex* equityIndex, QlOvernightIndex* interestRateIndex, DayCounter* dayCounter, double margin, double gearing, Calendar* paymentCalendar, int paymentConvention, unsigned paymentDelay, QlError **e);
  double qlEquityTotalReturnSwapEquityLegNPV(QlEquityTotalReturnSwap* o, QlError **e);
  double qlEquityTotalReturnSwapInterestRateLegNPV(QlEquityTotalReturnSwap* o, QlError **e);
  double qlEquityTotalReturnSwapFairMargin(QlEquityTotalReturnSwap* o, QlError **e);

  void qlFreeCreditDefaultSwap(QlCreditDefaultSwap *o);
  QlInstrument* qlCreditDefaultSwapAsInstrument(QlCreditDefaultSwap *o);
  void qlFreeClaim(QlClaim *o);
  QlClaim* qlFaceValueAccrualClaim(QlBond* referenceSecurity, QlError **e);
  QlClaim* qlFaceValueClaim(QlError **e);
  QlCreditDefaultSwap* qlCreditDefaultSwap(int side, double notional, double spread, Schedule* schedule, int paymentConvention, DayCounter* dayCounter, int settlesAccrual, int paysAtDefaultTime, int protectionStart, QlClaim* x9, DayCounter* lastPeriodDayCounter, int rebatesAccrual, int tradeDate, unsigned cashSettlementDays, QlError **e);
  QlCreditDefaultSwap* qlCreditDefaultSwap1(int side, double notional, double upfront, double spread, Schedule* schedule, int paymentConvention, DayCounter* dayCounter, int settlesAccrual, int paysAtDefaultTime, int protectionStart, int upfrontDate, QlClaim* x11, DayCounter* lastPeriodDayCounter, int rebatesAccrual, int tradeDate, unsigned cashSettlementDays, QlError **e);
  QlOption* qlCdsOptionAsOption(QlCdsOption *o);
  void qlFreeCdsOption(QlCdsOption *o);
  double qlCreditDefaultSwapFairSpread(QlCreditDefaultSwap* o, QlError **e);
  double qlCreditDefaultSwapConventionalSpread(QlCreditDefaultSwap* o, double conventionalRecovery, QlYieldTermStructure* discountCurve, DayCounter* dayCounter, int model, QlError **e);
  double qlCreditDefaultSwapCouponLegBPS(QlCreditDefaultSwap* o, QlError **e);
  double qlCreditDefaultSwapCouponLegNPV(QlCreditDefaultSwap* o, QlError **e);
  Leg* qlCreditDefaultSwapCoupons(QlCreditDefaultSwap* o, QlError **e);
  double qlCreditDefaultSwapDefaultLegNPV(QlCreditDefaultSwap* o, QlError **e);
  double qlCreditDefaultSwapFairUpfront(QlCreditDefaultSwap* o, QlError **e);
  double qlCreditDefaultSwapImpliedHazardRate(QlCreditDefaultSwap* o, double targetNPV, QlYieldTermStructure* discountCurve, DayCounter* dayCounter, double recoveryRate, double accuracy, int model, QlError **e);
  double qlCreditDefaultSwapUpfrontBPS(QlCreditDefaultSwap* o, QlError **e);
  double qlCreditDefaultSwapUpfrontNPV(QlCreditDefaultSwap* o, QlError **e);
  double qlCreditDefaultSwapAccrualRebateNPV(QlCreditDefaultSwap* o, QlError **e);
  void qlFreeBarrierOption(QlBarrierOption *o);
  QlOneAssetOption* qlBarrierOptionAsOneAssetOption(QlBarrierOption *o);
  void qlFreeDoubleBarrierOption(QlDoubleBarrierOption *o);
  QlOneAssetOption* qlDoubleBarrierOptionAsOneAssetOption(QlDoubleBarrierOption *o);
  void qlFreeSoftBarrierOption(QlSoftBarrierOption *o);
  QlOneAssetOption* qlSoftBarrierOptionAsOneAssetOption(QlSoftBarrierOption *o);
  void qlFreeMargrabeOption(QlMargrabeOption *o);
  QlMultiAssetOption* qlMargrabeOptionAsMultiAssetOption(QlMargrabeOption *o);
  void qlFreeEverestOption(QlEverestOption *o);
  QlMultiAssetOption* qlEverestOptionAsMultiAssetOption(QlEverestOption *o);
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
  double qlCdsOptionAtmRate(QlCdsOption* o, QlError **e);
  QlCdsOption* qlCdsOption(QlCreditDefaultSwap* swap, QlExercise* exercise, int knocksOut, QlError **e);
  QlCreditDefaultSwap* qlCdsOptionUnderlyingSwap(QlCdsOption* o, QlError **e);
  double qlCdsOptionImpliedVolatility(QlCdsOption* o, double price, QlYieldTermStructure* termStructure, QlDefaultProbabilityTermStructure* x3, double recoveryRate, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, QlError **e);
  double qlCdsOptionRiskyAnnuity(QlCdsOption* o, QlError **e);
  double qlSwaptionImpliedVolatility(QlSwaption* o, double price, QlYieldTermStructure* discountCurve, double guess, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, int type, double displacement, int priceType, QlError **e);
  QlSwaption* qlSwaption(QlFixedVsFloatingSwap* swap, QlExercise* exercise, int delivery, int settlementMethod, QlError **e);
  QlFixedVsFloatingSwap* qlSwaptionUnderlying(QlSwaption* o, QlError **e);
  void qlFreeIrregularSwaption(QlIrregularSwaption*);
  QlOption* qlIrregularSwaptionAsOption(QlIrregularSwaption*);
  QlIrregularSwaption* qlIrregularSwaption(QlIrregularSwap*, QlExercise*, int settlement, QlError **e);
  QlIrregularSwap* qlIrregularSwaptionUnderlyingSwap(QlIrregularSwaption* o, QlError **e);
  void qlFreeIrregularSwap(QlIrregularSwap*);
  QlSwap* qlIrregularSwapAsSwap(QlIrregularSwap*);
  QlIrregularSwap* qlIrregularSwap(int type, Leg*, Leg*, QlError **e);
  double qlIrregularSwapFairRate(QlIrregularSwap*, QlError **e);
  double qlIrregularSwapFairSpread(QlIrregularSwap*, QlError **e);
  void qlFreeNonstandardSwaption(QlNonstandardSwaption *o);
  QlOption* qlNonstandardSwaptionAsOption(QlNonstandardSwaption *o);
  QlNonstandardSwaption* qlNonstandardSwaption1(QlSwaption* fromSwaption, QlError **e);
  QlNonstandardSwaption* qlNonstandardSwaption(QlNonstandardSwap* swap, QlExercise* exercise, int delivery, int settlementMethod, QlError **e);
  QlNonstandardSwap* qlNonstandardSwaptionUnderlyingSwap(QlNonstandardSwaption* o, QlError **e);
  void qlNonstandardSwaptionCalibrationBasket(QlNonstandardSwaption* o, QlSwapIndex* swapBase, QlSwaptionVolatilityStructure* swaptionVol, int basketType, unsigned* len, QlBlackCalibrationHelper*** helpers, QlError **e);
  void qlFreeFloatFloatSwaption(QlFloatFloatSwaption *o);
  QlOption* qlFloatFloatSwaptionAsOption(QlFloatFloatSwaption *o);
  QlFloatFloatSwaption* qlFloatFloatSwaption(QlFloatFloatSwap* swap, QlExercise* exercise, int delivery, int settlementMethod, QlError **e);
  QlFloatFloatSwap* qlFloatFloatSwaptionUnderlyingSwap(QlFloatFloatSwaption* o, QlError **e);
  void qlFloatFloatSwaptionCalibrationBasket(QlFloatFloatSwaption* o, QlSwapIndex* swapBase, QlSwaptionVolatilityStructure* swaptionVol, int basketType, unsigned* len, QlBlackCalibrationHelper*** helpers, QlError **e);
  void qlFreeQuantoBarrierOption(QlQuantoBarrierOption *o);
  QlOneAssetOption* qlQuantoBarrierOptionAsOneAssetOption(QlQuantoBarrierOption *o);
  void qlFreeQuantoDoubleBarrierOption(QlQuantoDoubleBarrierOption *o);
  QlOneAssetOption* qlQuantoDoubleBarrierOptionAsOneAssetOption(QlQuantoDoubleBarrierOption *o);
  void qlFreeQuantoForwardVanillaOption(QlQuantoForwardVanillaOption *o);
  QlOption* qlQuantoForwardVanillaOptionAsOption(QlQuantoForwardVanillaOption *o);

  QlBarrierOption* qlBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, QlError **e);
  QlInstrument* qlTwoAssetBarrierOption(int barrierType, double barrier, QlStrikedTypePayoff* payoff, QlExercise* exercise, QlError **e);
  double qlBarrierOptionImpliedVolatility(QlBarrierOption* o, double price, QlGeneralizedBlackScholesProcess* process, unsigned dividendsLen, QlDividend** dividends, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, QlError **e);
  QlOneAssetOption* qlPartialTimeBarrierOption(int barrierType, int barrierRange, double barrier, double rebate, int coverEventDate, QlStrikedTypePayoff* payoff, QlExercise* exercise, QlError **e);
  QlDoubleBarrierOption* qlDoubleBarrierOption(int barrierType, double barrierLo, double barrierHi, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, QlError **e);
  double qlDoubleBarrierOptionImpliedVolatility(QlDoubleBarrierOption* o, double price, QlGeneralizedBlackScholesProcess* process, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, QlError **e);
  QlSoftBarrierOption* qlSoftBarrierOption(int barrierType, double barrierLo, double barrierHi, QlStrikedTypePayoff* payoff, QlExercise* exercise, QlError **e);
  double qlSoftBarrierOptionImpliedVolatility(QlSoftBarrierOption* o, double price, QlGeneralizedBlackScholesProcess* process, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, QlError **e);
  QlOneAssetOption* qlSimpleChooserOption(int choosingDate, double strike, QlExercise* exercise, QlError **e);
  QlOneAssetOption* qlComplexChooserOption(int choosingDate, double strikeCall, double strikePut, QlExercise* exerciseCall, QlExercise* exercisePut, QlError **e);
  QlMultiAssetOption* qlTwoAssetCorrelationOption(int type, double strike1, double strike2, QlExercise* exercise, QlError **e);
  QlOneAssetOption* qlWriterExtensibleOption(QlPlainVanillaPayoff* payoff1, QlExercise* exercise1, QlPlainVanillaPayoff* payoff2, QlExercise* exercise2, QlError **e);
  QlOneAssetOption* qlHolderExtensibleOption(int type, double premium, int secondExpiryDate, double secondStrike, QlStrikedTypePayoff* payoff, QlExercise* exercise, QlError **e);
  QlOneAssetOption* qlForwardVanillaOption(double moneyness, int resetDate, QlStrikedTypePayoff* payoff, QlExercise* exercise, QlError **e);
  QlOneAssetOption* qlCompoundOption(QlStrikedTypePayoff* motherPayoff, QlExercise* motherExercise, QlStrikedTypePayoff* daughterPayoff, QlExercise* daughterExercise, QlError **e);
  double qlMargrabeOptionDelta1(QlMargrabeOption* o, QlError **e);
  double qlMargrabeOptionDelta2(QlMargrabeOption* o, QlError **e);
  double qlMargrabeOptionGamma1(QlMargrabeOption* o, QlError **e);
  double qlMargrabeOptionGamma2(QlMargrabeOption* o, QlError **e);
  QlMargrabeOption* qlMargrabeOption(int Q1, int Q2, QlExercise* x2, QlError **e);
  double qlEverestOptionYield(QlEverestOption* o, QlError **e);
  QlEverestOption* qlEverestOption(double notional, double guarantee, QlExercise* exercise, QlError **e);
  double qlMultiAssetOptionDelta(QlMultiAssetOption* o, QlError **e);
  double qlMultiAssetOptionDividendRho(QlMultiAssetOption* o, QlError **e);
  double qlMultiAssetOptionGamma(QlMultiAssetOption* o, QlError **e);
  QlMultiAssetOption* qlMultiAssetOption(QlPayoff* x0, QlExercise* x1, QlError **e);
  double qlMultiAssetOptionRho(QlMultiAssetOption* o, QlError **e);
  double qlMultiAssetOptionTheta(QlMultiAssetOption* o, QlError **e);
  double qlMultiAssetOptionVega(QlMultiAssetOption* o, QlError **e);
  double qlOneAssetOptionDelta(QlOneAssetOption* o, QlError **e);
  double qlOneAssetOptionDeltaForward(QlOneAssetOption* o, QlError **e);
  double qlOneAssetOptionDividendRho(QlOneAssetOption* o, QlError **e);
  double qlOneAssetOptionElasticity(QlOneAssetOption* o, QlError **e);
  double qlOneAssetOptionGamma(QlOneAssetOption* o, QlError **e);
  double qlOneAssetOptionItmCashProbability(QlOneAssetOption* o, QlError **e);
  QlOneAssetOption* qlOneAssetOption(QlPayoff* x0, QlExercise* x1, QlError **e);
  double qlOneAssetOptionRho(QlOneAssetOption* o, QlError **e);
  double qlOneAssetOptionStrikeSensitivity(QlOneAssetOption* o, QlError **e);
  double qlOneAssetOptionTheta(QlOneAssetOption* o, QlError **e);
  double qlOneAssetOptionThetaPerDay(QlOneAssetOption* o, QlError **e);
  double qlOneAssetOptionVega(QlOneAssetOption* o, QlError **e);
  double qlQuantoBarrierOptionQlambda(QlQuantoBarrierOption* o, QlError **e);
  double qlQuantoBarrierOptionQrho(QlQuantoBarrierOption* o, QlError **e);
  QlQuantoBarrierOption* qlQuantoBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, QlError **e);
  double qlQuantoBarrierOptionQvega(QlQuantoBarrierOption* o, QlError **e);
  double qlQuantoDoubleBarrierOptionQlambda(QlQuantoDoubleBarrierOption* o, QlError **e);
  double qlQuantoDoubleBarrierOptionQrho(QlQuantoDoubleBarrierOption* o, QlError **e);
  QlQuantoDoubleBarrierOption* qlQuantoDoubleBarrierOption(int barrierType, double barrierLo, double barrierHi, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, QlError **e);
  double qlQuantoDoubleBarrierOptionQvega(QlQuantoDoubleBarrierOption* o, QlError **e);
  double qlQuantoForwardVanillaOptionQlambda(QlQuantoForwardVanillaOption* o, QlError **e);
  double qlQuantoForwardVanillaOptionQrho(QlQuantoForwardVanillaOption* o, QlError **e);
  QlQuantoForwardVanillaOption* qlQuantoForwardVanillaOption(double moneyness, int resetDate, QlStrikedTypePayoff* x2, QlExercise* x3, QlError **e);
  double qlQuantoForwardVanillaOptionQvega(QlQuantoForwardVanillaOption* o, QlError **e);
  double qlQuantoVanillaOptionQlambda(QlQuantoVanillaOption* o, QlError **e);
  double qlQuantoVanillaOptionQrho(QlQuantoVanillaOption* o, QlError **e);
  QlQuantoVanillaOption* qlQuantoVanillaOption(QlStrikedTypePayoff* x0, QlExercise* x1, QlError **e);
  double qlQuantoVanillaOptionQvega(QlQuantoVanillaOption* o, QlError **e);
  double qlVanillaOptionImpliedVolatility(QlVanillaOption* o, double price, QlGeneralizedBlackScholesProcess* process, unsigned dividendsLen, QlDividend** dividends, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, QlError **e);
  QlVanillaOption* qlVanillaOption(QlStrikedTypePayoff* x0, QlExercise* x1, QlError **e);
  QlMultiAssetOption* qlBasketOption(QlBasketPayoff* x0, QlExercise* x1, QlError **e);
  QlMultiAssetOption* qlHimalayaOption(unsigned fixingDatesLen, int* fixingDates, double strike, QlError **e);
  QlMultiAssetOption* qlPagodaOption(unsigned fixingDatesLen, int* fixingDates, double roof, double fraction, QlError **e);
  QlOneAssetOption* qlCliquetOption(QlPercentageStrikePayoff* x0, QlEuropeanExercise* maturity, unsigned resetDatesLen, int* resetDates, QlError **e);
  QlOneAssetOption* qlContinuousAveragingAsianOption(int averageType, QlStrikedTypePayoff* payoff, QlExercise* exercise, QlError **e);
  QlOneAssetOption* qlContinuousFixedLookbackOption(double currentMinmax, QlStrikedTypePayoff* payoff, QlExercise* exercise, QlError **e);
  QlOneAssetOption* qlContinuousFloatingLookbackOption(double currentMinmax, QlTypePayoff* payoff, QlExercise* exercise, QlError **e);
  QlOneAssetOption* qlContinuousPartialFloatingLookbackOption(double currentMinmax, double lambda, int lookbackPeriodEnd, QlTypePayoff* payoff, QlExercise* exercise, QlError **e);
  QlOneAssetOption* qlContinuousPartialFixedLookbackOption(int lookbackPeriodStart, QlStrikedTypePayoff* payoff, QlExercise* exercise, QlError **e);
  QlOneAssetOption* qlDiscreteAveragingAsianOption(int averageType, double runningAccumulator, unsigned pastFixings, unsigned fixingDatesLen, int* fixingDates, QlStrikedTypePayoff* payoff, QlExercise* exercise, QlError **e);
  QlOneAssetOption* qlVanillaStorageOption(QlBermudanExercise* ex, double capacity, double load, double changeRate, QlError **e);
  QlOneAssetOption* qlVanillaSwingOption(QlStrikedTypePayoff* payoff, QlSwingExercise* ex, unsigned minExerciseRights, unsigned maxExerciseRights, QlError **e);
  QlVanillaOption* qlEuropeanOption(QlStrikedTypePayoff* x0, QlExercise* x1, QlError **e);

  QlBond *qlBond(unsigned settlDays, Calendar *calendar, int issueDate, Leg *coupons, QlError **e);
  Leg* qlBondCashflows(QlBond* o, QlError **e);
  Leg* qlBondRedemptions(QlBond* o, QlError **e);
  int qlBondSettlementDate(QlBond* o, int d, QlError **e);
  int qlBondStartDate(QlBond* o, QlError **e);
  int qlBondMaturityDate(QlBond *bond, QlError **e);
  QlInstrument *qlBondAsInstrument(QlBond *bond);

  QlFixedRateBond *qlFixedRateBond(unsigned settlDays, double face, Schedule *schedule, unsigned cLen, double *coupons, DayCounter *counter, int payConv, double redemption, int issue, Calendar *payCal, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, DayCounter* firstPeriodDayCounter, QlError **e);
  QlBond *qlZeroCouponBond(int settlDays, Calendar *cal, double face, int maturity, int payConv, double redemption, int issue, QlError **e);
  QlBond *qlFloatingRateBond(unsigned settlDays, double face, Schedule *sched, QlIborIndex *index, DayCounter *dc, int payConv, unsigned fixDays,
    unsigned nGearings, double *gearings, unsigned nSpreads, double *spreads, unsigned nCaps, double *caps, unsigned nFloors, double *floors,
    int inArrears, double redemption, int issue, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, int fixingConvention, QlError **e);
  QlBond *qlCmsRateBond(unsigned settlDays, double faceAmount, Schedule *sched, QlSwapIndex *index, DayCounter *dc,
    int payConv, unsigned fixDays, unsigned nGearings, double *gearings, unsigned nSpreads, double *spreads,
    unsigned nCaps, double *caps, unsigned nFloors, double *floors, int inArrears, double redemption, int issue, QlError **e);
  QlBond *qlAmortizingCmsRateBond(unsigned settlementDays, unsigned notionalsLen, double *notionals, Schedule *sched,
    QlSwapIndex *index, DayCounter *dc, int payConv, unsigned fixDays, unsigned nGearings, double *gearings,
    unsigned nSpreads, double *spreads, unsigned nCaps, double *caps, unsigned nFloors, double *floors,
    int inArrears, int issue, unsigned redemptionsLen, double *redemptions, QlError **e);
  QlBond *qlFixedRateBondAsBond(QlFixedRateBond *bond);

  // RendistatoBasket requires BTP values, so this Italian Treasury bond has its own type.
  QlBTP *qlBtp(int maturityDate, double fixedRate, int startDate, int issueDate, QlError **e);
  // Non-par redemption constructor.
  QlBTP *qlBtpWithRedemption(int maturityDate, double fixedRate, double redemption, int startDate, int issueDate, QlError **e);
  void qlFreeBtp(QlBTP *o);
  QlFixedRateBond *qlBtpAsFixedRateBond(QlBTP *o);

  QlCPIBond *qlCPIBond(unsigned settlementDays, double faceAmount, double baseCPI, int obsLagLen, int obsLagUnit, QlZeroInflationIndex* index, int observationInterpolation, Schedule *schedule, unsigned couponsLen, double *coupons, DayCounter *accrualDayCounter, int paymentConvention, int issueDate, Calendar *paymentCalendar, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, QlError **e);
  QlBond *qlCPIBondAsBond(QlCPIBond *bond);

  QlBond *qlAmortizingFixedRateBond(unsigned settlementDays, unsigned notionalsLen, double *notionals, Schedule *schedule,
    unsigned couponsLen, double *coupons, DayCounter *accrualDayCounter, int paymentConvention, int issueDate,
    int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth,
    unsigned redemptionsLen, double *redemptions, int paymentLag, QlError **e);
  QlBond *qlAmortizingFloatingRateBond(unsigned settlementDays, unsigned notionalLen, double *notional, Schedule *schedule,
    QlIborIndex *index, DayCounter *accrualDayCounter, int paymentConvention, unsigned fixingDays,
    unsigned nGearings, double *gearings, unsigned nSpreads, double *spreads, unsigned nCaps, double *caps, unsigned nFloors, double *floors,
    int inArrears, int issueDate, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention,
    int exCouponEndOfMonth, unsigned redemptionsLen, double *redemptions, int paymentLag, QlError **e);
  Schedule *qlSinkingSchedule(int startDate, int lengthLen, int lengthUnit, int frequency, Calendar *paymentCalendar, QlError **e);
  void qlSinkingNotionals(int lengthLen, int lengthUnit, int frequency, double couponRate, double initialNotional,
    unsigned *len, double **out, QlError **e);

  double qlBondYield(QlBond* o, DayCounter* dc, int comp, int freq, double accuracy,
    unsigned maxEvaluations, double guess, int priceType, QlError **e);
  double qlBondAccruedAmount(QlBond* o, int d, QlError **e);
  double qlBondCleanPrice(QlBond* o, QlError **e);
  double qlBondDirtyPrice(QlBond* o, QlError **e);
  double qlBondDirtyPrice1(QlBond* o, double yield, DayCounter* dc, int comp, int freq, int settlementDate, QlError **e);
  int qlBondNextCashFlowDate(QlBond* o, int d, QlError **e);
  double qlBondNextCouponRate(QlBond* o, int d, QlError **e);
  double qlBondNotional(QlBond* o, int d, QlError **e);
  int qlBondPreviousCashFlowDate(QlBond* o, int d, QlError **e);
  double qlBondPreviousCouponRate(QlBond* o, int d, QlError **e);
  double qlBondSettlementValue1(QlBond* o, double cleanPrice, QlError **e);
  double qlBondSettlementValue(QlBond* o, QlError **e);
  double qlBondYield1(QlBond* o, double price, int, DayCounter* dc, int comp, int freq, int settlementDate, double accuracy, unsigned maxEvaluations, QlError **e);
  int qlBondIsTradable(QlBond* o, int d, QlError **e);
  void qlBondNotionals(QlBond* o, unsigned *len, double **ns, QlError **e);

  int qlBondFunctionsAccrualDays(QlBond* bond, int settlementDate, QlError **e);
  int qlBondFunctionsAccrualEndDate(QlBond* bond, int settlementDate, QlError **e);
  double qlBondFunctionsAccrualPeriod(QlBond* bond, int settlementDate, QlError **e);
  int qlBondFunctionsAccrualStartDate(QlBond* bond, int settlementDate, QlError **e);
  int qlBondFunctionsAccruedDays(QlBond* bond, int settlementDate, QlError **e);
  double qlBondFunctionsAccruedPeriod(QlBond* bond, int settlementDate, QlError **e);
  double qlBondFunctionsAtmRate(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, double price, int, QlError **e);
  double qlBondFunctionsBasisPointValue(QlBond* bond, InterestRate* yield, int settlementDate, QlError **e);
  double qlBondFunctionsBps1(QlBond* bond, InterestRate* yield, int settlementDate, QlError **e);
  double qlBondFunctionsBps(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, QlError **e);
  double qlBondFunctionsCleanPrice2(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, QlError **e);
  double qlBondFunctionsCleanPrice3(QlBond* bond, QlYieldTermStructure* discount, double zSpread, int compounding, int frequency, int settlementDate, QlError **e);
  double qlBondFunctionsCleanPrice4(QlBond* bond, InterestRate* yield, int settlementDate, QlError **e);
  double qlBondFunctionsConvexity(QlBond* bond, InterestRate* yield, int settlementDate, QlError **e);
  double qlBondFunctionsDuration(QlBond* bond, InterestRate* yield, int type, int settlementDate, QlError **e);
  double qlBondFunctionsNextCashFlowAmount(QlBond* bond, int refDate, QlError **e);
  double qlBondFunctionsPreviousCashFlowAmount(QlBond* bond, int refDate, QlError **e);
  int qlBondFunctionsReferencePeriodEnd(QlBond* bond, int settlementDate, QlError **e);
  int qlBondFunctionsReferencePeriodStart(QlBond* bond, int settlementDate, QlError **e);
  double qlBondFunctionsYield2(QlBond* bond, double price, int, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, double accuracy, unsigned maxIterations, double guess, QlError **e);
  double qlBondFunctionsYieldValueBasisPoint(QlBond* bond, InterestRate* yield, int settlementDate, QlError **e);
  double qlBondFunctionsZSpread(QlBond* bond, double price, int, QlYieldTermStructure* x2, int compounding, int frequency, int settlementDate, double accuracy, unsigned maxIterations, double guess, QlError **e);

  void qlFreeBond(QlBond *bond);
  void qlFreeFixedRateBond(QlFixedRateBond *bond);
  void qlFreeCPIBond(QlCPIBond *bond);
  void qlFreeCallableBond(QlCallableBond *o);
  QlBond* qlCallableBondAsBond(QlCallableBond *o);
  void qlFreeConvertibleBond(QlConvertibleBond *o);
  QlBond* qlConvertibleBondAsBond(QlConvertibleBond *o);

  QlCallableBond* qlCallableFixedRateBond(unsigned settlementDays, double faceAmount, Schedule* schedule, unsigned couponsLen, double* coupons, DayCounter* accrualDayCounter, int paymentConvention, double redemption, int issueDate, unsigned putCallScheduleLen, QlCallability** putCallSchedule, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, QlError **e);
  QlCallableBond* qlCallableZeroCouponBond(unsigned settlementDays, double faceAmount, Calendar* calendar, int maturityDate, DayCounter* dayCounter, int paymentConvention, double redemption, int issueDate, unsigned putCallScheduleLen, QlCallability** putCallSchedule, QlError **e);
  QlConvertibleBond* qlConvertibleFixedCouponBond(QlExercise* exercise, double conversionRatio, unsigned callabilityLen, QlCallability** callability, int issueDate, unsigned settlementDays, unsigned couponsLen, double* coupons, DayCounter* dayCounter, Schedule* schedule, double redemption, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, QlError **e);
  QlConvertibleBond* qlConvertibleFloatingRateBond(QlExercise* exercise, double conversionRatio, unsigned callabilityLen, QlCallability** callability, int issueDate, unsigned settlementDays, QlIborIndex* index, unsigned fixingDays, unsigned spreadsLen, double* spreads, DayCounter* dayCounter, Schedule* schedule, double redemption, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, QlError **e);
  QlConvertibleBond* qlConvertibleZeroCouponBond(QlExercise* exercise, double conversionRatio, unsigned callabilityLen, QlCallability** callability, int issueDate, unsigned settlementDays, DayCounter* dayCounter, Schedule* schedule, double redemption, QlError **e);
  QlCallability* qlSoftCallability(double price, int priceType, int date, double trigger, QlError **e);

  Leg *qlLeg(unsigned len, double *amounts, int *dates, QlError **e);
  void qlFreeCashFlow(QlCashFlow *o);
  double qlCashFlowAmount(QlCashFlow *o, QlError **e);
  int qlCashFlowDate(QlCashFlow *o);
  QlCashFlow *qlSimpleCashFlow(double amount, int date, QlError **e);
  void qlFreeIndexedCashFlow(QlIndexedCashFlow *o);
  QlCashFlow *qlIndexedCashFlowAsCashFlow(QlIndexedCashFlow *o);
  QlIndexedCashFlow *qlIndexedCashFlow(double notional, QlIndex *index, int baseDate, int fixingDate, int paymentDate, int growthOnly, QlError **e);
  double qlIndexedCashFlowBaseFixing(QlIndexedCashFlow *o, QlError **e);
  double qlIndexedCashFlowIndexFixing(QlIndexedCashFlow *o, QlError **e);
  QlFixedRateCoupon *qlFixedRateCoupon(int paymentDate, double nominal, double rate, DayCounter *dayCounter, int accrualStartDate, int accrualEndDate, int refPeriodStart, int refPeriodEnd, int exCouponDate, QlError **e);
  void qlFreeCoupon(QlCoupon *o);
  QlCashFlow* qlCouponAsCashFlow(QlCoupon *o);
  double qlCouponRate(QlCoupon *o, QlError **e);
  double qlCouponAccruedAmount(QlCoupon *o, int d, QlError **e);
  void qlFreeFixedRateCoupon(QlFixedRateCoupon *o);
  QlCoupon* qlFixedRateCouponAsCoupon(QlFixedRateCoupon *o);
  InterestRate* qlFixedRateCouponInterestRate(QlFixedRateCoupon *o);
  QlFloatingRateCoupon *qlFloatingRateCoupon(int paymentDate, double nominal, int startDate, int endDate, unsigned fixingDays, QlInterestRateIndex *index, double gearing, double spread, int refPeriodStart, int refPeriodEnd, DayCounter *dayCounter, int inArrears, int exCouponDate, int fixingConvention, QlError **e);
  Leg *qlCashFlowLeg(unsigned len, QlCashFlow **cashFlows, QlError **e);
  int qlLegStartDate(Leg *leg, QlError **e);

  void qlFreeLeg(Leg *leg);
  Leg *qlNextCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  Leg *qlPreviousCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  void qlLegCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate, unsigned *al, double **amount, unsigned *dl, int **date, unsigned *hl, int **hasOccurred, QlError **e);
  void qlLegFixingDependencies(Leg *leg, unsigned *nameLen, char ***names, unsigned *dateLen, int **dates, QlError **e);

  double qlCashFlowsDuration(Leg* leg, InterestRate* yield, int type, int includeSettlementDateFlows, int settlementDate, int npvDate, QlError **e);
  int qlCashFlowsAccrualDays(Leg* leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  int qlCashFlowsAccrualEndDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  double qlCashFlowsAccrualPeriod(Leg* leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  int qlCashFlowsAccrualStartDate(Leg* leg, int includeSettlementDateFlows, int settlDate, QlError **e);
  double qlCashFlowsAccruedAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  int qlCashFlowsAccruedDays(Leg* leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  double qlCashFlowsAccruedPeriod(Leg* leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  double qlCashFlowsAtmRate(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, double npv, QlError **e);
  double qlCashFlowsBasisPointValue(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, QlError **e);
  double qlCashFlowsBps1(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, QlError **e);
  double qlCashFlowsBps(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, QlError **e);
  double qlCashFlowsConvexity(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, QlError **e);
  int qlCashFlowsIsExpired(Leg* leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  int qlCashFlowsMaturityDate(Leg* leg, QlError **e);
  double qlCashFlowsNextCashFlowAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  int qlCashFlowsNextCashFlowDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  double qlCashFlowsNextCouponRate(Leg* leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  double qlCashFlowsNominal(Leg* leg, int includeSettlementDateFlows, int settlDate, QlError **e);
  double qlCashFlowsNpv1(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, QlError **e);
  double qlCashFlowsNpv3(Leg* leg, QlYieldTermStructure* discount, double zSpread, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, QlError **e);
  double qlCashFlowsNpv(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, QlError **e);
  void qlCashFlowsNpvbps(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, double *npv, double *bps, QlError **e);
  double qlCashFlowsPreviousCashFlowAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  int qlCashFlowsPreviousCashFlowDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  double qlCashFlowsPreviousCouponRate(Leg* leg, int includeSettlementDateFlows, int settlementDate, QlError **e);
  int qlCashFlowsReferencePeriodEnd(Leg* leg, int includeSettlementDateFlows, int settlDate, QlError **e);
  int qlCashFlowsReferencePeriodStart(Leg* leg, int includeSettlementDateFlows, int settlDate, QlError **e);
  double qlCashFlowsYield(Leg* leg, double npv, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, QlError **e);
  double qlCashFlowsYieldValueBasisPoint(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, QlError **e);
  double qlCashFlowsZSpread(Leg* leg, double npv, QlYieldTermStructure* x2, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, QlError **e);

  void qlQuantLibSetCouponPricer(Leg* leg, QlFloatingRateCouponPricer* x1, QlError **e);
  void qlQuantLibSetCouponPricers(Leg* leg, unsigned x1Len, QlFloatingRateCouponPricer** x1, QlError **e);

  void qlCouponAccrualStartDates(CouponLeg* o, unsigned *len, int **days, QlError **e);
  void qlCouponLegCoupons(CouponLeg* o, unsigned *len, QlCoupon ***out, QlError **e);

  void qlFreeDividend(QlDividend *o);
  QlDividend* qlFixedDividend(double amount, int date, QlError **e);
  QlDividend* qlFractionalDividend1(double rate, double nominal, int date, QlError **e);
  QlDividend* qlFractionalDividend(double rate, int date, QlError **e);

  Leg* qlAverageBMALeg(Schedule* schedule, QlBMAIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, QlError **e);
  Leg* qlFixedRateLeg(Schedule* schedule, unsigned NotionalsLen, double* Notionals, unsigned couponRatesLen, InterestRate** couponRates, int paymentAdjustment, DayCounter* firstPeriodDayCounter, Calendar* paymentCalendar, QlError **e);
  Leg* qlIborLeg(Schedule* schedule, QlIborIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned capsLen, double* caps, unsigned floorsLen, double* floors, int inArrears, int zeroPayments,
    int paymentLag, Calendar* paymentCalendar, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, int fixingConvention, int useIndexedCoupons, QlStubIndexSelection* stub, QlError **e);
  Leg* qlCmsLeg(Schedule* schedule, QlSwapIndex* swapIndex, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned capsLen, double* caps, unsigned floorsLen, double* floors, int inArrears, int zeroPayments,
    int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, int fixingConvention, QlError **e);
  Leg* qlOvernightLeg(Schedule* schedule, QlOvernightIndex* overnightIndex, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, QlError **e);
  Leg* qlRangeAccrualLeg(Schedule* schedule, QlIborIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned lowerTriggersLen, double* lowerTriggers, unsigned upperTriggersLen, double* upperTriggers, int, int, int observationConvention, QlError **e);
  void qlFreeCouponLeg(CouponLeg *o);
  Leg* qlCouponLegAsLeg(CouponLeg *o);

  CouponLeg* qlLegToCouponLeg(Leg *o, QlError **e);
  Leg* qlCPILeg(Schedule* schedule, QlZeroInflationIndex* index, double baseCPI, int obsLagLen, int obsLagUnit, unsigned notionalsLen, double* notionals, unsigned fixedRatesLen, double* fixedRates, DayCounter* paymentDayCounter, int paymentAdjustment, Calendar* paymentCalendar, int observationInterpolation, int subtractInflationNominal, QlError **e);
  Leg* qlYoYInflationLeg(Schedule* schedule, Calendar* cal, QlYoYInflationIndex* index, int obsLagLen, int obsLagUnit, int interpolation, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned capsLen, double* caps, unsigned floorsLen, double* floors, QlError **e);

  /* YoYInflationCouponPricer -- all 3 concrete pricers share this ctor shape */
  QlYoYInflationCouponPricer *qlBlackYoYInflationCouponPricer(QlYoYOptionletVolatilitySurface *vol, QlYieldTermStructure *nominalTs, QlError **e);
  QlYoYInflationCouponPricer *qlUnitDisplacedBlackYoYInflationCouponPricer(QlYoYOptionletVolatilitySurface *vol, QlYieldTermStructure *nominalTs, QlError **e);
  QlYoYInflationCouponPricer *qlBachelierYoYInflationCouponPricer(QlYoYOptionletVolatilitySurface *vol, QlYieldTermStructure *nominalTs, QlError **e);
  void qlFreeYoYInflationCouponPricer(QlYoYInflationCouponPricer *p);
  void qlSetYoYInflationCouponPricer(Leg* leg, QlYoYInflationCouponPricer* pricer, QlError **e);

  void qlFreeZeroInflationCashFlow(QlZeroInflationCashFlow *o);
  QlIndexedCashFlow *qlZeroInflationCashFlowAsIndexedCashFlow(QlZeroInflationCashFlow *o);
  QlZeroInflationCashFlow* qlZeroInflationCashFlow(double notional, QlZeroInflationIndex* index, int observationInterpolation, int startDate, int endDate, int obsLagLen, int obsLagUnit, int paymentDate, int growthOnly, QlError **e);

  void qlFreeCPICashFlow(QlCPICashFlow *o);
  QlIndexedCashFlow *qlCPICashFlowAsIndexedCashFlow(QlCPICashFlow *o);
  QlCPICashFlow* qlCPICashFlow(double notional, QlZeroInflationIndex* index, int baseDate, double baseFixing, int observationDate, int obsLagLen, int obsLagUnit, int interpolation, int paymentDate, int growthOnly, QlError **e);

  void qlFreeEquityCashFlow(QlEquityCashFlow *o);
  QlIndexedCashFlow *qlEquityCashFlowAsIndexedCashFlow(QlEquityCashFlow *o);
  QlEquityCashFlow* qlEquityCashFlow(double notional, QlEquityIndex* index, int baseDate, int fixingDate, int paymentDate, int growthOnly, QlError **e);
  void qlEquityCashFlowSetPricer(QlEquityCashFlow* o, QlEquityCashFlowPricer* pricer, QlError **e);

  void qlFreeEquityCashFlowPricer(QlEquityCashFlowPricer *o);
  QlEquityCashFlowPricer* qlEquityQuantoCashFlowPricer(QlYieldTermStructure* quantoCurrencyTermStructure, QlBlackVolTermStructure* equityVolatility, QlBlackVolTermStructure* fxVolatility, QlQuote* correlation, QlError **e);
  void qlQuantLibSetEquityCashFlowPricer(Leg* leg, QlEquityCashFlowPricer* pricer, QlError **e);

  QlFloatingRateCouponPricer *qlBlackIborCouponPricer(QlOptionletVolatilityStructure *vol, int timingAdjustment, QlQuote *correlation, int useIndexedCoupon, QlError **e);
  QlFloatingRateCouponPricer *qlBlackIborQuantoCouponPricer(QlBlackVolTermStructure *fxRateBlackVolatility, QlQuote *underlyingFxCorrelation, QlOptionletVolatilityStructure *capletVolatility, QlError **e);
  void qlFreeFloatingCouponPricer(QlFloatingRateCouponPricer *p);
  void qlFreeCmsCouponPricer(QlCmsCouponPricer *p);
  QlFloatingRateCouponPricer* qlCmsCouponPricerAsFloatingRateCouponPricer(QlCmsCouponPricer *p);
  QlCmsCouponPricer* qlAnalyticHaganPricer(QlSwaptionVolatilityStructure* swaptionVol, int modelOfYieldCurve, QlQuote* meanReversion, QlError **e);
  QlCmsCouponPricer* qlNumericHaganPricer(QlSwaptionVolatilityStructure* swaptionVol, int modelOfYieldCurve, QlQuote* meanReversion, double lowerLimit, double upperLimit, double precision, double hardUpperLimit, QlError **e);
  QlCmsCouponPricer* qlLinearTsrPricer(QlSwaptionVolatilityStructure* swaptionVol, QlQuote* meanReversion, QlYieldTermStructure* couponDiscountCurve, int strategy, double param, int haveBounds, double lowerBound, double upperBound, QlError **e);
  QlFloatingRateCouponPricer* qlRangeAccrualPricerByBgm(double correlation, QlSmileSection* smilesOnExpiry, QlSmileSection* smilesOnPayment, int withSmile, int byCallSpread, QlError **e);

  void qlFreeFloatingRateCoupon(QlFloatingRateCoupon *o);
  void qlFreeIborCoupon(QlIborCoupon *o);
  QlFloatingRateCoupon* qlIborCouponAsFloatingRateCoupon(QlIborCoupon *o);
  QlIborCoupon* qlIborCouponExact(int paymentDate, double nominal, int startDate, int endDate, unsigned fixingDays, QlIborIndex *index, double gearing, double spread, int refPeriodStart, int refPeriodEnd, DayCounter *dayCounter, int inArrears, int exCouponDate, int fixingConvention, QlError **e);
  void qlFreeAverageBMACoupon(QlAverageBMACoupon *o);
  QlFloatingRateCoupon* qlAverageBMACouponAsFloatingRateCoupon(QlAverageBMACoupon* o);
  QlAverageBMACoupon* qlAverageBMACoupon(int paymentDate, double nominal, int startDate, int endDate, QlBMAIndex *index, double gearing, double spread, int refPeriodStart, int refPeriodEnd, DayCounter *dayCounter, QlError **e);
  void qlAverageBMACouponFixingDates(QlAverageBMACoupon *o, unsigned *len, int **ds, QlError **e);
  void qlAverageBMACouponIndexFixings(QlAverageBMACoupon *o, unsigned *len, double **fs, QlError **e);
  QlFloatingRateCoupon* qlCappedFlooredCoupon(QlFloatingRateCoupon *underlying, double cap, double floor, QlError **e);
  void qlFreeStrippedCappedFlooredCoupon(QlStrippedCappedFlooredCoupon *o);
  QlFloatingRateCoupon* qlStrippedCappedFlooredCouponAsFloatingRateCoupon(QlStrippedCappedFlooredCoupon *o);
  QlStrippedCappedFlooredCoupon* qlStrippedCappedFlooredCoupon(QlFloatingRateCoupon *underlying, double cap, double floor, QlError **e);
  double qlStrippedCappedFlooredCouponCap(QlStrippedCappedFlooredCoupon *o);
  double qlStrippedCappedFlooredCouponFloor(QlStrippedCappedFlooredCoupon *o);
  double qlStrippedCappedFlooredCouponEffectiveCap(QlStrippedCappedFlooredCoupon *o);
  double qlStrippedCappedFlooredCouponEffectiveFloor(QlStrippedCappedFlooredCoupon *o);
  int qlStrippedCappedFlooredCouponIsCap(QlStrippedCappedFlooredCoupon *o);
  int qlStrippedCappedFlooredCouponIsFloor(QlStrippedCappedFlooredCoupon *o);
  int qlStrippedCappedFlooredCouponIsCollar(QlStrippedCappedFlooredCoupon *o);
  QlFloatingRateCoupon* qlCappedFlooredIborCoupon(int paymentDate, double nominal, int startDate, int endDate, unsigned fixingDays, QlIborIndex *index, double gearing, double spread, double cap, double floor, int refPeriodStart, int refPeriodEnd, DayCounter *dayCounter, int inArrears, int exCouponDate, int fixingConvention, QlError **e);
  QlDigitalCoupon* qlDigitalIborCoupon(QlIborCoupon *underlying, double callStrike, int callPosition, int callATM, double callPayoff, double putStrike, int putPosition, int putATM, double putPayoff, QlDigitalReplication *replication, int nakedOption, QlError **e);
  void qlFreeDigitalCoupon(QlDigitalCoupon*);
  QlFloatingRateCoupon* qlDigitalCouponAsFloatingRateCoupon(QlDigitalCoupon*);
  QlDigitalCoupon* qlDigitalCoupon(QlFloatingRateCoupon *underlying, double callStrike, int callPosition, int callATM, double callPayoff, double putStrike, int putPosition, int putATM, double putPayoff, QlDigitalReplication *replication, int nakedOption, QlError **e);
  double qlDigitalCouponCallOptionRate(QlDigitalCoupon *o, QlError **e);
  double qlDigitalCouponPutOptionRate(QlDigitalCoupon *o, QlError **e);
  void qlFreeMultipleResetsCoupon(QlMultipleResetsCoupon *o);
  QlFloatingRateCoupon* qlMultipleResetsCouponAsFloatingRateCoupon(QlMultipleResetsCoupon* o);
  QlMultipleResetsCoupon* qlMultipleResetsCoupon(int paymentDate, double nominal, Schedule *schedule, unsigned fixingDays, QlIborIndex *index, double gearing, double couponSpread, double rateSpread, int refPeriodStart, int refPeriodEnd, DayCounter *dayCounter, int exCouponDate, QlError **e);
  void qlMultipleResetsCouponFixingDates(QlMultipleResetsCoupon *o, unsigned *len, int **dates, QlError **e);
  void qlFreeRangeAccrualFloatersCoupon(QlRangeAccrualFloatersCoupon*);
  QlFloatingRateCoupon* qlRangeAccrualFloatersCouponAsFloatingRateCoupon(QlRangeAccrualFloatersCoupon*);
  QlRangeAccrualFloatersCoupon* qlRangeAccrualFloatersCoupon(int paymentDate, double nominal, QlIborIndex*, int startDate, int endDate, unsigned fixingDays, DayCounter*, double gearing, double spread, int refStart, int refEnd, Schedule*, double lower, double upper, QlError **e);
  double qlRangeAccrualFloatersCouponPriceWithoutOptionality(QlRangeAccrualFloatersCoupon*, QlYieldTermStructure*, QlError **e);
  void qlFreeYoYInflationCoupon(QlYoYInflationCoupon*);
  QlCoupon* qlYoYInflationCouponAsCoupon(QlYoYInflationCoupon*);
  QlYoYInflationCoupon* qlYoYInflationCoupon(int paymentDate, double nominal, int startDate, int endDate, unsigned fixingDays, QlYoYInflationIndex*, int lagLen, int lagUnit, int interpolation, DayCounter*, double gearing, double spread, int refStart, int refEnd, QlError **e);
  double qlYoYInflationCouponAdjustedFixing(QlYoYInflationCoupon*, QlError **e);
  QlFloatingRateCouponPricer* qlAveragingMultipleResetsPricer(QlError **e);
  QlFloatingRateCouponPricer* qlCompoundingMultipleResetsPricer(QlError **e);
  void qlFreeOvernightIndexedCoupon(QlOvernightIndexedCoupon *o);
  QlFloatingRateCoupon* qlOvernightIndexedCouponAsFloatingRateCoupon(QlOvernightIndexedCoupon *o);
  QlOvernightIndexedCoupon* qlOvernightIndexedCoupon(int paymentDate, double nominal, int startDate, int endDate, QlOvernightIndex *index, double gearing, double spread, int refPeriodStart, int refPeriodEnd, DayCounter *dayCounter, int telescopic, int averaging, unsigned lookback, unsigned lockout, int observationShift, int compoundSpread, int rateStart, int rateEnd, int exCouponDate, int rounding, QlError **e);
  QlFloatingRateCoupon* qlCappedFlooredOvernightIndexedCoupon(QlOvernightIndexedCoupon *underlying, double cap, double floor, int naked, int daily, QlError **e);
  void qlOvernightIndexedCouponFixingDates(QlOvernightIndexedCoupon *o, unsigned *len, int **dates, QlError **e);
  void qlOvernightIndexedCouponIndexFixings(QlOvernightIndexedCoupon *o, unsigned *len, double **fixings, QlError **e);
  QlFloatingRateCouponPricer* qlCompoundingOvernightIndexedCouponPricer(QlOptionletVolatilityStructure *vol, int effective, QlError **e);
  QlFloatingRateCouponPricer* qlArithmeticAveragedOvernightIndexedCouponPricer(double mr, double volatility, int byApprox, QlOptionletVolatilityStructure *vol, int effective, QlError **e);
  QlFloatingRateCouponPricer* qlBlackCompoundingOvernightIndexedCouponPricer(QlOptionletVolatilityStructure *vol, int effective, QlError **e);
  QlFloatingRateCouponPricer* qlBlackAveragingOvernightIndexedCouponPricer(QlOptionletVolatilityStructure *vol, int effective, QlError **e);
  void qlFreeCPICoupon(QlCPICoupon *o);
  QlCPICoupon* qlCPICoupon(double baseCPI, int paymentDate, double nominal, int startDate, int endDate, QlZeroInflationIndex *index, int lagLen, int lagUnit, int interpolation, DayCounter *dc, double fixedRate, int refStart, int refEnd, int exCoupon, QlError **e);
  QlCPICoupon* qlCPICouponFromBaseDate(int baseDate, int paymentDate, double nominal, int startDate, int endDate, QlZeroInflationIndex *index, int lagLen, int lagUnit, int interpolation, DayCounter *dc, double fixedRate, int refStart, int refEnd, int exCoupon, QlError **e);
  QlCPICoupon* qlCPICouponWithBaseDate(double baseCPI, int baseDate, int paymentDate, double nominal, int startDate, int endDate, QlZeroInflationIndex *index, int lagLen, int lagUnit, int interpolation, DayCounter *dc, double fixedRate, int refStart, int refEnd, int exCoupon, QlError **e);
  void qlFreeCPICouponPricer(QlCPICouponPricer *o);
  QlCPICouponPricer* qlCPICouponPricer(QlYieldTermStructure *nominal, QlError **e);
  QlCPICouponPricer* qlCPICouponPricerWithVol(QlCPIVolatilitySurface *vol, QlYieldTermStructure *nominal, QlError **e);
  QlCoupon* qlCPICouponAsCoupon(QlCPICoupon *o);
  void qlCPICouponSetPricer(QlCPICoupon *coupon, QlCPICouponPricer *pricer, QlError **e);
  QlCashFlow* qlRedemption(double amount, int date, QlError **e);
  QlCashFlow* qlAmortizingPayment(double amount, int date, QlError **e);
  QlCoupon* qlFloatingRateCouponAsCoupon(QlFloatingRateCoupon* o);
  void qlFloatingRateCouponSetPricer(QlFloatingRateCoupon* o, QlFloatingRateCouponPricer* pricer, QlError **e);
  double qlFloatingRateCouponPrice(QlFloatingRateCoupon* o, QlYieldTermStructure* discountingCurve, QlError **e);
  double qlFloatingRateCouponConvexityAdjustment(QlFloatingRateCoupon* o, QlError **e);
  double qlCPICouponIndexRatio(QlCPICoupon *o, int d, QlError **e);
  double qlFloatingRateCouponPricerSwapletRate(QlFloatingRateCouponPricer* o, QlError **e);
  double qlFloatingRateCouponPricerSwapletPrice(QlFloatingRateCouponPricer* o, QlError **e);
  double qlFloatingRateCouponPricerCapletPrice(QlFloatingRateCouponPricer* o, double effectiveCap, QlError **e);
  double qlFloatingRateCouponPricerCapletRate(QlFloatingRateCouponPricer* o, double effectiveCap, QlError **e);
  double qlFloatingRateCouponPricerFloorletPrice(QlFloatingRateCouponPricer* o, double effectiveFloor, QlError **e);
  double qlFloatingRateCouponPricerFloorletRate(QlFloatingRateCouponPricer* o, double effectiveFloor, QlError **e);

  void qlFreeCmsCoupon(QlCmsCoupon *o);
  QlFloatingRateCoupon* qlCmsCouponAsFloatingRateCoupon(QlCmsCoupon *o);
  QlCmsCoupon* qlCmsCoupon(int paymentDate, double nominal, int startDate, int endDate, unsigned fixingDays, QlSwapIndex* index, double gearing, double spread, int refPeriodStart, int refPeriodEnd, DayCounter* dayCounter, int inArrears, int exCouponDate, int fixingConvention, QlError **e);

  QlFloatingRateCoupon* qlCmsSpreadCoupon(int paymentDate, double nominal, int startDate, int endDate, unsigned fixingDays, QlSwapSpreadIndex* index, double gearing, double spread, int refPeriodStart, int refPeriodEnd, DayCounter* dayCounter, int inArrears, int exCouponDate, int fixingConvention, QlError **e);
  QlFloatingRateCoupon* qlCappedFlooredCmsSpreadCoupon(int paymentDate, double nominal, int startDate, int endDate, unsigned fixingDays, QlSwapSpreadIndex* index, double gearing, double spread, double cap, double floor, int refPeriodStart, int refPeriodEnd, DayCounter* dayCounter, int inArrears, int exCouponDate, int fixingConvention, QlError **e);
  QlFloatingRateCouponPricer* qlLognormalCmsSpreadPricer(QlCmsCouponPricer* cmsPricer, QlQuote* correlation, QlYieldTermStructure* couponDiscountCurve, unsigned integrationPoints, int haveVolatilityType, int volatilityType, double shift1, double shift2, QlError **e);
  Leg* qlCmsSpreadLeg(Schedule* schedule, QlSwapSpreadIndex* swapSpreadIndex, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned capsLen, double* caps, unsigned floorsLen, double* floors, int inArrears, int zeroPayments, QlError **e);

  void qlFreeDigitalCmsSpreadCoupon(QlDigitalCmsSpreadCoupon *o);
  QlDigitalCoupon* qlDigitalCmsSpreadCouponAsDigitalCoupon(QlDigitalCmsSpreadCoupon *o);
  QlDigitalCmsSpreadCoupon* qlDigitalCmsSpreadCoupon(int paymentDate, double nominal, int startDate, int endDate, unsigned fixingDays, QlSwapSpreadIndex* index, double gearing, double spread, int refPeriodStart, int refPeriodEnd, DayCounter* dayCounter, int inArrears, int exCouponDate, int fixingConvention, double callStrike, int callPosition, int callATM, double callPayoff, double putStrike, int putPosition, int putATM, double putPayoff, QlDigitalReplication* replication, int nakedOption, QlError **e);
  Leg* qlDigitalCmsSpreadLeg(Schedule* schedule, QlSwapSpreadIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, int inArrears, unsigned callStrikesLen, double* callStrikes, int callPosition, int callATM, unsigned callPayoffsLen, double* callPayoffs, unsigned putStrikesLen, double* putStrikes, int putPosition, int putATM, unsigned putPayoffsLen, double* putPayoffs, QlDigitalReplication* replication, int nakedOption, QlError **e);

  void qlFreeSwapSpreadIndex(QlSwapSpreadIndex *o);
  QlInterestRateIndex* qlSwapSpreadIndexAsInterestRateIndex(QlSwapSpreadIndex *o);
  QlSwapSpreadIndex* qlSwapSpreadIndex(const char* familyName, QlSwapIndex* swapIndex1, QlSwapIndex* swapIndex2, double gearing1, double gearing2, QlError **e);

  QlFloatingRateCoupon* qlCappedFlooredCmsCoupon(int paymentDate, double nominal, int startDate, int endDate, unsigned fixingDays, QlSwapIndex* index, double gearing, double spread, double cap, double floor, int refPeriodStart, int refPeriodEnd, DayCounter* dayCounter, int inArrears, int exCouponDate, int fixingConvention, QlError **e);

  void qlFreeDigitalReplication(QlDigitalReplication *o);
  QlDigitalReplication* qlDigitalReplication(int type, double gap, QlError **e);
  int qlDigitalReplicationType(QlDigitalReplication* o);
  double qlDigitalReplicationGap(QlDigitalReplication* o);

  void qlFreeDigitalCmsCoupon(QlDigitalCmsCoupon *o);
  QlDigitalCoupon* qlDigitalCmsCouponAsDigitalCoupon(QlDigitalCmsCoupon *o);
  QlDigitalCmsCoupon* qlDigitalCmsCoupon(QlCmsCoupon* underlying, double callStrike, int callPosition, int callATM, double callPayoff, double putStrike, int putPosition, int putATM, double putPayoff, QlDigitalReplication* replication, int nakedOption, QlError **e);

  Leg* qlDigitalCmsLeg(Schedule* schedule, QlSwapIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, int inArrears, unsigned callStrikesLen, double* callStrikes, int callPosition, int callATM, unsigned callPayoffsLen, double* callPayoffs, unsigned putStrikesLen, double* putStrikes, int putPosition, int putATM, unsigned putPayoffsLen, double* putPayoffs, QlDigitalReplication* replication, int nakedOption, QlError **e);
  Leg* qlDigitalIborLeg(Schedule*, QlIborIndex*, unsigned, double*, DayCounter*, int, unsigned, unsigned*, unsigned, double*, unsigned, double*, int, unsigned, double*, int, int, unsigned, double*, unsigned, double*, int, int, unsigned, double*, QlDigitalReplication*, int, QlError **e);
  Leg* qlMultipleResetsLeg(Schedule*, QlIborIndex*, unsigned, unsigned, double*, DayCounter*, int, Calendar*, int, unsigned, unsigned*, unsigned, double*, unsigned, double*, unsigned, double*, int, int, Calendar*, int, int, int, QlError **e);

  void qlFreeVarianceSwap(QlVarianceSwap *o);
  QlInstrument* qlVarianceSwapAsInstrument(QlVarianceSwap *o);
  QlVarianceSwap* qlVarianceSwap(int position, double strike, double notional, int startDate, int maturityDate, QlError **e);
  double qlVarianceSwapVariance(QlVarianceSwap* o, QlError **e);

  void qlFreeVarianceOption(QlVarianceOption *o);
  QlInstrument* qlVarianceOptionAsInstrument(QlVarianceOption *o);
  QlVarianceOption* qlVarianceOption(QlPayoff* payoff, double notional, int startDate, int maturityDate, QlError **e);

  void qlFreeCommodity(QlCommodity *o);
  QlInstrument* qlCommodityAsInstrument(QlCommodity *o);
  void qlFreeEnergyCommodity(QlEnergyCommodity *o);
  QlCommodity* qlEnergyCommodityAsCommodity(QlEnergyCommodity *o);

  /* Commodity base-level getters. Each output array needs its own c2hs `preArray-` length cell,
     even though arrays returned by one call have equal lengths. */
  void qlCommodityAddPricingError(QlCommodity *o, int level, char *error, char *detail);
  void qlCommoditySecondaryCostAmounts(QlCommodity *o, unsigned *len, char ***keys,
      unsigned *len2, double **amounts, unsigned *len3, Currency ***currencies, QlError **e);
  void qlCommodityPricingErrors(QlCommodity *o, unsigned *len, int **levels,
      unsigned *len2, char ***errors, unsigned *len3, char ***details, QlError **e);

  /* EnergyCommodity -- quantity() is pure virtual upstream; one shim covers every leaf. */
  double qlEnergyCommodityQuantity(QlEnergyCommodity *o, CommodityType **outCt, UnitOfMeasure **outUom, QlError **e);

  /* EnergyFuture. secondaryCosts is 5 c2hs-marshalled arrays (keys/isUnitCost/amounts/currencies/
     uoms), each an independent `withXArray*&` clause -- c2hs emits one length parameter per array
     clause even though all 5 always carry the same Haskell-side length, so 4 of the 5 `unsigned`s
     below are deliberately unnamed (same convention as qlCompositeInstrument's `unsigned, double
     *coeff` above) and only the first (scLen) is read. */
  QlEnergyFuture* qlEnergyFuture(int buySell,
      CommodityType *qCt, UnitOfMeasure *qUom, double qAmount,
      double tpAmount, Currency *tpCcy, UnitOfMeasure *tpUom,
      QlCommodityIndex *index, CommodityType *commodityType,
      unsigned scLen, char **scKeys, unsigned, int *scIsUnitCost, unsigned, double *scAmounts,
      unsigned, Currency **scCurrencies, unsigned, UnitOfMeasure **scUoms,
      QlError **e);
  void qlFreeEnergyFuture(QlEnergyFuture *o);

  /* EnergySwap -- binds no constructor (see qlaux.h); base-level getters generalized over both
     leaves below. */
  void qlFreeEnergySwap(QlEnergySwap *o);
  QlEnergyCommodity* qlEnergySwapAsEnergyCommodity(QlEnergySwap *o);
  void qlEnergySwapDailyPositions(QlEnergySwap *o, unsigned *len, int **dates,
      unsigned *len2, double **quantityAmounts, unsigned *len3, double **payLegPrices,
      unsigned *len4, double **receiveLegPrices, unsigned *len5, double **riskDeltas,
      unsigned *len6, int **unrealized, QlError **e);
  void qlEnergySwapPaymentCashFlows(QlEnergySwap *o, unsigned *len, QlCommodityCashFlow ***out, QlError **e);

  /* EnergyVanillaSwap. pricingPeriods is 6 parallel arrays (start/end/payment dates, quantity
     type/uom/amount); like secondaryCosts above, only the first length parameter of each group
     (ppLen, scLen) is read. */
  void qlFreeEnergyVanillaSwap(QlEnergyVanillaSwap *o);
  QlEnergySwap* qlEnergyVanillaSwapAsEnergySwap(QlEnergyVanillaSwap *o);
  QlEnergyVanillaSwap* qlEnergyVanillaSwap(int payer, Calendar *calendar,
      double fixedPriceAmount, Currency *fixedPriceCurrency, UnitOfMeasure *fixedPriceUnitOfMeasure,
      QlCommodityIndex *index, Currency *payCurrency, Currency *receiveCurrency,
      unsigned ppLen, int *ppStartDates, unsigned, int *ppEndDates, unsigned, int *ppPaymentDates,
      unsigned, CommodityType **ppTypes, unsigned, UnitOfMeasure **ppUoms, unsigned, double *ppAmounts,
      CommodityType *commodityType,
      unsigned scLen, char **scKeys, unsigned, int *scIsUnitCost, unsigned, double *scAmounts,
      unsigned, Currency **scCurrencies, unsigned, UnitOfMeasure **scUoms,
      QlYieldTermStructure *payLegTS, QlYieldTermStructure *receiveLegTS, QlYieldTermStructure *discountTS,
      QlError **e);

  /* EnergyBasisSwap -- same pricingPeriods/secondaryCosts array-group shape as EnergyVanillaSwap. */
  void qlFreeEnergyBasisSwap(QlEnergyBasisSwap *o);
  QlEnergySwap* qlEnergyBasisSwapAsEnergySwap(QlEnergyBasisSwap *o);
  QlEnergyBasisSwap* qlEnergyBasisSwap(Calendar *calendar,
      QlCommodityIndex *spreadIndex, QlCommodityIndex *payIndex, QlCommodityIndex *receiveIndex,
      int spreadToPayLeg, Currency *payCurrency, Currency *receiveCurrency,
      unsigned ppLen, int *ppStartDates, unsigned, int *ppEndDates, unsigned, int *ppPaymentDates,
      unsigned, CommodityType **ppTypes, unsigned, UnitOfMeasure **ppUoms, unsigned, double *ppAmounts,
      double basisAmount, Currency *basisCurrency, UnitOfMeasure *basisUnitOfMeasure,
      CommodityType *commodityType,
      unsigned scLen, char **scKeys, unsigned, int *scIsUnitCost, unsigned, double *scAmounts,
      unsigned, Currency **scCurrencies, unsigned, UnitOfMeasure **scUoms,
      QlYieldTermStructure *payLegTS, QlYieldTermStructure *receiveLegTS, QlYieldTermStructure *discountTS,
      QlError **e);

  /* CommodityCashFlow -- a standalone CashFlow leaf, never Haskell-constructed (only ever produced
     by EnergySwap::paymentCashFlows()). */
  void qlFreeCommodityCashFlow(QlCommodityCashFlow *o);
  QlCashFlow *qlCommodityCashFlowAsCashFlow(QlCommodityCashFlow *o);
  double qlCommodityCashFlowDiscountedAmount(QlCommodityCashFlow *o, Currency **outCcy, QlError **e);
  double qlCommodityCashFlowUndiscountedAmount(QlCommodityCashFlow *o, Currency **outCcy, QlError **e);
  double qlCommodityCashFlowDiscountedPaymentAmount(QlCommodityCashFlow *o, Currency **outCcy, QlError **e);
  double qlCommodityCashFlowUndiscountedPaymentAmount(QlCommodityCashFlow *o, Currency **outCcy, QlError **e);
  double qlCommodityCashFlowDiscountFactor(QlCommodityCashFlow *o);
  double qlCommodityCashFlowPaymentDiscountFactor(QlCommodityCashFlow *o);
  int qlCommodityCashFlowFinalized(QlCommodityCashFlow *o);

  /* CommodityPricingHelper::createPricingPeriods */
  void qlCreatePricingPeriods(int startDate, int endDate, CommodityType *qCt, UnitOfMeasure *qUom, double qAmount,
      int deliverySchedule, int qtyPeriodicity, PaymentTerm *paymentTerm,
      unsigned *len, int **ppStartDates, unsigned *len2, int **ppEndDates, unsigned *len3, int **ppPaymentDates,
      unsigned *len4, CommodityType ***ppTypes, unsigned *len5, UnitOfMeasure ***ppUoms, unsigned *len6, double **ppAmounts,
      QlError **e);
  /* YoYInflationCapFloor -- constructed directly at the given Type (Cap/Floor/Collar are thin
     ctor-only subclasses upstream with no logic of their own, so there's no need to touch them). */
  QlYoYInflationCapFloor *qlYoYInflationCap(Leg *yoyLeg, unsigned exerciseRatesLen, double *exerciseRates, QlError **e);
  QlYoYInflationCapFloor *qlYoYInflationFloor(Leg *yoyLeg, unsigned exerciseRatesLen, double *exerciseRates, QlError **e);
  QlYoYInflationCapFloor *qlYoYInflationCollar(Leg *yoyLeg, unsigned capRatesLen, double *capRates,
      unsigned floorRatesLen, double *floorRates, QlError **e);
  void qlFreeYoYInflationCapFloor(QlYoYInflationCapFloor *o);
  QlInstrument *qlYoYInflationCapFloorAsInstrument(QlYoYInflationCapFloor *o);
  double qlYoYInflationCapFloorAtmRate(QlYoYInflationCapFloor *o, QlYieldTermStructure *discountCurve, QlError **e);
  QlYoYInflationCapFloor *qlYoYInflationCapFloorOptionlet(QlYoYInflationCapFloor *o, unsigned n, QlError **e);

  /* CPICapFloor -- a single cumulative option, unlike YoYInflationCapFloor; no impliedVolatility
     (no vol-driven engine exists for it in QL 1.43, see qlInterpolatingCPICapFloorEngine below). */
  QlCPICapFloor *qlCPICapFloor(int type, double nominal, int startDate, double baseCPI, int maturity,
      Calendar *fixCalendar, int fixConvention, Calendar *payCalendar, int payConvention, double strike,
      QlZeroInflationIndex *index, int observationLagLen, int observationLagUnit, int observationInterpolation,
      QlError **e);
  void qlFreeCPICapFloor(QlCPICapFloor *o);
  QlInstrument *qlCPICapFloorAsInstrument(QlCPICapFloor *o);

  // ql/experimental/credit -- portfolio credit scaffolding (Pool/Issuer/Basket/loss models) plus
  // the SyntheticCDO/NthToDefault instruments built on it. Folded in here rather than kept in a
  // dedicated qlCredit.{h,cpp} pair -- too small to justify its own source files.

  // ql/experimental/credit/defaultprobabilitykey.hpp -- only the NorthAmericaCorpDefaultKey
  // constructor is bound; DefaultProbKey itself has no public constructor of its own upstream.
  DefaultProbKey* qlNorthAmericaCorpDefaultKey(Currency* currency, int seniority, int graceFailureToPayLen, int graceFailureToPayUnit, double amountFailure, int restructuringType, QlError **e);
  void qlFreeDefaultProbKey(DefaultProbKey *o);

  // ql/experimental/credit/issuer.hpp -- only the key_curve_pair-vector constructor (empty
  // DefaultEventSet) is bound.
  Issuer* qlIssuer(unsigned probabilitiesLen, DefaultProbKey** keys, QlDefaultProbabilityTermStructure** curves, QlError **e);
  void qlFreeIssuer(Issuer *o);

  // ql/experimental/credit/pool.hpp -- Pool::add is looped over internally; no add mutator is
  // exposed to Haskell.
  QlPool* qlPool(unsigned namesLen, char** names, Issuer** issuers, DefaultProbKey** keys, QlError **e);
  void qlFreePool(QlPool *o);

  // ql/experimental/credit/basket.hpp -- the loss model is a constructor argument here; the
  // shim calls Basket::setLossModel internally, so no setter is exposed to Haskell.
  QlBasket* qlBasket(int refDate, unsigned namesLen, char** names, double* notionals, QlPool* pool, double attachmentRatio, double detachmentRatio, QlClaim* claim, QlDefaultLossModel* lossModel, QlError **e);
  void qlFreeBasket(QlBasket *o);
  double qlBasketNotional(QlBasket* o, QlError **e);
  // Bound early (ahead of the rest of Basket's risk-output surface) to give this step's own
  // test a discriminating check that the loss model actually wired up; the remaining outputs
  // (percentile, expectedShortfall, lossDistribution, ...) are a separate step.
  double qlBasketExpectedTrancheLoss(QlBasket* o, int d, QlError **e);
  // Identical to qlBasket -- QuantLib's own Basket doesn't distinguish which DefaultLossModel
  // subclass it holds. This entry point exists only so the Haskell side can bind its result as
  // the distinct DigitalBasket type (see QuantLib/Internal/Type.hs's CREDIT comment), which is
  // the only basket type qlNthToDefault accepts: GaussianLHPLossModel-backed baskets (built via
  // qlBasket) don't implement the probAtLeastNEvents/probsBeingNthEvent virtuals
  // IntegralNtdEngine needs, and ConstantLossModel-backed baskets don't implement
  // expectedTrancheLoss -- QL_FAILs at runtime either way, caught here at compile time instead.
  QlBasket* qlDigitalBasket(int refDate, unsigned namesLen, char** names, double* notionals, QlPool* pool, double attachmentRatio, double detachmentRatio, QlClaim* claim, QlDefaultLossModel* lossModel, QlError **e);

  // Loss-model-agnostic: basket state, not delegated to the loss model.
  double qlBasketRemainingNotional(QlBasket* o, int d, QlError **e);
  double qlBasketRecoveryRate(QlBasket* o, int d, unsigned iName, QlError **e);

  // Tranche-loss outputs -- implemented by GaussianLHPLossModel.
  double qlBasketProbOverLoss(QlBasket* o, int d, double lossFraction, QlError **e);
  double qlBasketPercentile(QlBasket* o, int d, double prob, QlError **e);
  double qlBasketExpectedShortfall(QlBasket* o, int d, double prob, QlError **e);

  // Digital-loss outputs -- implemented by ConstantLossModel.
  double qlBasketDefaultCorrelation(QlBasket* o, int d, unsigned iName, unsigned jName, QlError **e);
  double qlBasketProbAtLeastNEvents(QlBasket* o, unsigned n, int d, QlError **e);

  // ql/experimental/credit/gaussianlhplossmodel.hpp -- only the Handle<Quote> correlation
  // overload is bound, per the std::variant/Handle<Quote> convention (a caller with a bare
  // number gets a simpleQuote for free).
  QlDefaultLossModel* qlGaussianLHPLossModel(QlQuote* correlQuote, unsigned recoveriesLen, double* recoveries, QlError **e);
  void qlFreeDefaultLossModel(QlDefaultLossModel *o);

  // ql/experimental/credit/syntheticcdo.hpp -- notional is ext::optional<Real>; haveNotional
  // selects between the "leveraged off basket tranche notional" default (0) and an explicit
  // override notional.
  QlSyntheticCDO* qlSyntheticCDO(QlBasket* basket, int side, Schedule* schedule, double upfrontRate, double runningRate, DayCounter* dayCounter, int paymentConvention, int haveNotional, double notional, QlError **e);
  void qlFreeSyntheticCDO(QlSyntheticCDO *o);
  QlInstrument* qlSyntheticCDOAsInstrument(QlSyntheticCDO *o);
  double qlSyntheticCDOFairPremium(QlSyntheticCDO* o, QlError **e);
  double qlSyntheticCDOFairUpfrontPremium(QlSyntheticCDO* o, QlError **e);
  double qlSyntheticCDOPremiumValue(QlSyntheticCDO* o, QlError **e);
  double qlSyntheticCDOProtectionValue(QlSyntheticCDO* o, QlError **e);
  double qlSyntheticCDOPremiumLegNPV(QlSyntheticCDO* o, QlError **e);
  double qlSyntheticCDOProtectionLegNPV(QlSyntheticCDO* o, QlError **e);
  double qlSyntheticCDORemainingNotional(QlSyntheticCDO* o, QlError **e);
  // leverageFactor() is skipped -- a constructor echo (notional / basket tranche notional).
  double qlSyntheticCDOImplicitCorrelation(QlSyntheticCDO* o, unsigned recoveriesLen, double* recoveries, QlYieldTermStructure* discountCurve, double targetNPV, double accuracy, QlError **e);

  // ql/experimental/credit/constantlosslatentmodel.hpp -- ConstantLossModel<CopulaPolicy>, only
  // the Handle<Quote>/nVariables (one-factor) constructor. tOrdersLen == 0 selects
  // GaussianCopulaPolicy; tOrdersLen > 0 selects TCopulaPolicy with these degrees of freedom
  // (see qlTermStructureAux.h for the exact-length requirement). The dispatch itself lives in
  // qlTermStructureAux.cpp, alongside the other DefaultProbabilityTermStructure/credit dispatch
  // already there, per AGENTS.md's rule that a runtime-enum-selects-a-template-argument switch
  // belongs in its domain's Aux TU.
  QlDefaultLossModel* qlConstantLossModel(QlQuote* correlQuote, unsigned recoveriesLen, double* recoveries, int integralType, unsigned tOrdersLen, int* tOrders, QlError **e);

  // ql/experimental/credit/nthtodefault.hpp -- only fairPremium() is bound; premium/nominal/
  // dayCounter/side/rank/basketSize are all constructor echoes.
  QlNthToDefault* qlNthToDefault(QlBasket* basket, unsigned n, int side, Schedule* premiumSchedule, double upfrontRate, double premiumRate, DayCounter* dayCounter, double nominal, int settlePremiumAccrual, QlError **e);
  void qlFreeNthToDefault(QlNthToDefault *o);
  QlInstrument* qlNthToDefaultAsInstrument(QlNthToDefault *o);
  double qlNthToDefaultFairPremium(QlNthToDefault* o, QlError **e);

  // ql/instruments/bonds/btp.hpp -- RendistatoBasket/RendistatoCalculator, QuantLib's own
  // BTP-vs-swap-curve relative-value tool for the Italian bond market. size/btps/
  // cleanPriceQuotes/outstandings/weights/outstanding on RendistatoBasket are all constructor
  // echoes and are not bound; only the basket constructor itself is needed to build a
  // RendistatoCalculator.
  QlRendistatoBasket *qlRendistatoBasket(unsigned btpsLen, QlBTP **btps, unsigned outstandingsLen, double *outstandings, unsigned quotesLen, QlQuote **cleanPriceQuotes, QlError **e);
  void qlFreeRendistatoBasket(QlRendistatoBasket *o);

  // euriborTenor/euriborForwardCurve build the Euribor index RendistatoCalculator needs
  // internally (for its ladder of comparison swaps); Euribor itself is never exposed back to
  // Haskell, since nothing calls it back -- constructed transiently here exactly like
  // GarmanKlass's IntervalPrice.
  QlRendistatoCalculator *qlRendistatoCalculator(QlRendistatoBasket *basket, int euriborTenorLen, int euriborTenorUnit, QlYieldTermStructure *euriborForwardCurve, QlYieldTermStructure *discountCurve, QlError **e);
  void qlFreeRendistatoCalculator(QlRendistatoCalculator *o);
  double qlRendistatoCalculatorYield(QlRendistatoCalculator *o, QlError **e);
  double qlRendistatoCalculatorDuration(QlRendistatoCalculator *o, QlError **e);
  void qlRendistatoCalculatorYields(QlRendistatoCalculator *o, unsigned *len, double **out, QlError **e);
  void qlRendistatoCalculatorDurations(QlRendistatoCalculator *o, unsigned *len, double **out, QlError **e);
  void qlRendistatoCalculatorSwapLengths(QlRendistatoCalculator *o, unsigned *len, double **out, QlError **e);
  void qlRendistatoCalculatorSwapRates(QlRendistatoCalculator *o, unsigned *len, double **out, QlError **e);
  void qlRendistatoCalculatorSwapYields(QlRendistatoCalculator *o, unsigned *len, double **out, QlError **e);
  void qlRendistatoCalculatorSwapDurations(QlRendistatoCalculator *o, unsigned *len, double **out, QlError **e);
  QlVanillaSwap *qlRendistatoCalculatorEquivalentSwap(QlRendistatoCalculator *o, QlError **e);
  double qlRendistatoCalculatorEquivalentSwapRate(QlRendistatoCalculator *o, QlError **e);
  double qlRendistatoCalculatorEquivalentSwapYield(QlRendistatoCalculator *o, QlError **e);
  double qlRendistatoCalculatorEquivalentSwapDuration(QlRendistatoCalculator *o, QlError **e);
  double qlRendistatoCalculatorEquivalentSwapLength(QlRendistatoCalculator *o, QlError **e);
  double qlRendistatoCalculatorEquivalentSwapSpread(QlRendistatoCalculator *o, QlError **e);
  QlQuote *qlRendistatoEquivalentSwapLengthQuote(QlRendistatoCalculator *o, QlError **e);
  QlQuote *qlRendistatoEquivalentSwapSpreadQuote(QlRendistatoCalculator *o, QlError **e);
void qlFreeMtMCrossCurrencyBasisSwap(QlMtMCrossCurrencyBasisSwap* o);
QlSwap* qlMtMCrossCurrencyBasisSwapAsSwap(QlMtMCrossCurrencyBasisSwap* o);
QlMtMCrossCurrencyBasisSwap* qlMtMCrossCurrencyBasisSwap(int type, double fxBaseNominal, Currency* fxBaseCurrency, Schedule* fxBaseSchedule, QlIborIndex* fxBaseIndex, double fxBaseSpread, double fxBaseGearing, double fxQuoteNominal, Currency* fxQuoteCurrency, Schedule* fxQuoteSchedule, QlIborIndex* fxQuoteIndex, double fxQuoteSpread, double fxQuoteGearing, int resetBase, unsigned fxResetFixingDays, Calendar* fxResetFixingCalendar, int fxBasePaymentLag, int fxQuotePaymentLag, int fxBasePaymentConvention, int fxQuotePaymentConvention, int fxBaseCompoundSpread, unsigned fxBaseLookbackDays, int fxBaseObservationShift, unsigned fxBaseLockoutDays, int fxBaseAveragingMethod, int fxQuoteCompoundSpread, unsigned fxQuoteLookbackDays, int fxQuoteObservationShift, unsigned fxQuoteLockoutDays, int fxQuoteAveragingMethod, int telescopicValueDates, int useIndexedCoupons, QlStubIndexSelection* fxBaseStubIndexSelection, QlStubIndexSelection* fxQuoteStubIndexSelection, QlError **e);
Currency* qlMtMLegCurrency(QlMtMCrossCurrencyBasisSwap* o, unsigned j, QlError **e);
double qlMtMInCcyLegBPS(QlMtMCrossCurrencyBasisSwap* o, unsigned j, QlError **e);
double qlMtMInCcyLegNPV(QlMtMCrossCurrencyBasisSwap* o, unsigned j, QlError **e);
double qlMtMNpvDateDiscounts(QlMtMCrossCurrencyBasisSwap* o, unsigned j, QlError **e);
double qlMtMFairFxBaseSpread(QlMtMCrossCurrencyBasisSwap* o, QlError **e);
double qlMtMFairFxQuoteSpread(QlMtMCrossCurrencyBasisSwap* o, QlError **e);
double qlMtMFairPaySpread(QlMtMCrossCurrencyBasisSwap* o, QlError **e);
double qlMtMFairRecSpread(QlMtMCrossCurrencyBasisSwap* o, QlError **e);
void qlMtMFxResetRates(QlMtMCrossCurrencyBasisSwap* o, unsigned* len, double** out, QlError **e);
void qlMtMFxResetNotionals(QlMtMCrossCurrencyBasisSwap* o, unsigned* len, double** out, QlError **e);
void qlFxResetConventionReset(unsigned fixingDays, Calendar* calendar, int date, int* fixing, int* value, QlError **e);
int qlFxResetConventionValueDate(unsigned fixingDays, Calendar* calendar, int date, QlError **e);
void qlFreeFxResetPricer(QlFxResetPricer* o);
QlFxResetPricer* qlDiscountingFxResetPricer(Currency* constantCcy, Currency* resetCcy, QlYieldTermStructure* constantCurve, QlYieldTermStructure* resetCurve, QlQuote* spotFx, int spotIsResettablePerConstant, int spotFxSettleDate, QlError **e);
double qlFxResetRate(QlFxResetPricer* o, int fixing, int value, QlError **e);
void qlFreeFxResetCoupon(QlFxResetCoupon* o);
QlFloatingRateCoupon* qlFxResetCouponAsFloatingRateCoupon(QlFxResetCoupon* o);
void qlFreeFxResetNotionalExchange(QlFxResetNotionalExchange* o);
QlCashFlow* qlFxResetNotionalExchangeAsCashFlow(QlFxResetNotionalExchange* o);
QlFxResetCoupon* qlFxResetCoupon(QlFloatingRateCoupon* underlying, double notional, int fixing, int value, QlError **e);
QlFxResetNotionalExchange* qlFxResetNotionalExchange(int payment, double notional, int previousFixing, int previousValue, int currentFixing, int currentValue, QlError **e);
void qlFxResetCouponSetFxResetPricer(QlFxResetCoupon* o, QlFxResetPricer* pricer, QlError **e);
void qlFxResetNotionalExchangeSetFxResetPricer(QlFxResetNotionalExchange* o, QlFxResetPricer* pricer, QlError **e);
void qlSetFxResetLegPricer(Leg* leg, QlFxResetPricer* pricer, QlError **e);
QlIborCoupon* qlStubIborCoupon(int paymentDate, double nominal, int startDate, int endDate, unsigned fixingDays, QlStubIndexSelection* selection, double gearing, double spread, int refPeriodStart, int refPeriodEnd, DayCounter* dayCounter, int inArrears, int exCouponDate, int fixingConvention, QlError **e);
double qlCouponNominal(QlCoupon* o, QlError **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
