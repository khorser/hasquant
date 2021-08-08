#ifdef __cplusplus
extern "C" {
#endif
  void qlFreeFixedRateBondForward(QlFixedRateBondForward *fwd);
  QlForward* qlFixedRateBondForwardAsForward(QlFixedRateBondForward *fwd);
  QlFixedRateBondForward* qlFixedRateBondForward(int valueDate, int maturityDate, int type, double strike, unsigned settlementDays, DayCounter* dayCounter, Calendar* calendar, int businessDayConvention, QlFixedRateBond* fixedCouponBond, QlYieldTermStructure* discountCurve, QlYieldTermStructure* incomeDiscountCurve, char **e);
  double qlFixedRateBondForwardCleanForwardPrice(QlFixedRateBondForward* o, char **e);
  double qlFixedRateBondForwardForwardPrice(QlFixedRateBondForward* o, char **e);
  void qlFreeForward(QlForward *fwd);
  QlInstrument* qlForwardAsInstrument(QlForward *fwd);
  double qlForwardForwardValue(QlForward* o, char **e);
  InterestRate* qlForwardImpliedYield(QlForward* o, double underlyingSpotValue, double forwardValue, int settlementDate, int compoundingConvention, DayCounter* dayCounter, char **e);
  int qlForwardSettlementDate(QlForward* o, char **e);
  double qlForwardSpotIncome(QlForward* o, QlYieldTermStructure* incomeDiscountCurve, char **e);
  double qlForwardSpotValue(QlForward* o, char **e);
  void qlFreeForwardRateAgreement(QlForwardRateAgreement *fwd);
  QlForward* qlForwardRateAgreementAsForward(QlForwardRateAgreement *fwd);
  QlForwardRateAgreement* qlForwardRateAgreement(int valueDate, int maturityDate, int type, double strikeForwardRate, double notionalAmount, QlIborIndex* index, QlYieldTermStructure* discountCurve, char **e);

  InterestRate* qlForwardRateAgreementForwardRate(QlForwardRateAgreement* o, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
