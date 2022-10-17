#ifdef __cplusplus
extern "C" {
#endif
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
  QlForwardRateAgreement* qlForwardRateAgreement(int valueDate, int maturityDate, int type, double strikeForwardRate, double notionalAmount, QlIborIndex* index, QlYieldTermStructure* discountCurve, char **e);

  InterestRate* qlForwardRateAgreementForwardRate(QlForwardRateAgreement* o, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
