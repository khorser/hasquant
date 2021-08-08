#ifdef __cplusplus
extern "C" {
#endif
  void qlFreeCreditDefaultSwap(QlCreditDefaultSwap *o);
  QlInstrument* qlCreditDefaultSwapAsInstrument(QlCreditDefaultSwap *o);
  void qlFreeClaim(QlClaim *o);
  QlClaim* qlFaceValueAccrualClaim(QlBond* referenceSecurity, char **e);
  QlClaim* qlFaceValueClaim(char **e);
  QlCreditDefaultSwap* qlCreditDefaultSwap(int side, double notional, double spread, Schedule* schedule, int paymentConvention, DayCounter* dayCounter, int settlesAccrual, int paysAtDefaultTime, int protectionStart, QlClaim* x9, char **e);
  QlCreditDefaultSwap* qlCreditDefaultSwap1(int side, double notional, double upfront, double spread, Schedule* schedule, int paymentConvention, DayCounter* dayCounter, int settlesAccrual, int paysAtDefaultTime, int protectionStart, int upfrontDate, QlClaim* x11, char **e);
  QlOption* qlCdsOptionAsOption(QlCdsOption *o);
  void qlFreeCdsOption(QlCdsOption *o);
  double qlCreditDefaultSwapFairSpread(QlCreditDefaultSwap* o, char **e);
  double qlCreditDefaultSwapConventionalSpread(QlCreditDefaultSwap* o, double conventionalRecovery, QlYieldTermStructure* discountCurve, DayCounter* dayCounter, char **e);
  double qlCreditDefaultSwapCouponLegBPS(QlCreditDefaultSwap* o, char **e);
  double qlCreditDefaultSwapCouponLegNPV(QlCreditDefaultSwap* o, char **e);
  Leg* qlCreditDefaultSwapCoupons(QlCreditDefaultSwap* o, char **e);
  double qlCreditDefaultSwapDefaultLegNPV(QlCreditDefaultSwap* o, char **e);
  double qlCreditDefaultSwapFairUpfront(QlCreditDefaultSwap* o, char **e);
  double qlCreditDefaultSwapImpliedHazardRate(QlCreditDefaultSwap* o, double targetNPV, QlYieldTermStructure* discountCurve, DayCounter* dayCounter, double recoveryRate, double accuracy, char **e);
  double qlCreditDefaultSwapUpfrontBPS(QlCreditDefaultSwap* o, char **e);
  double qlCreditDefaultSwapUpfrontNPV(QlCreditDefaultSwap* o, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
