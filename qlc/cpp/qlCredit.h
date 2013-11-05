#ifdef _WIN32
# if defined(DLLSOURCE)
#  define DLLEXPORT __declspec(dllexport)
# elif defined(DLLUSE)
#  define DLLEXPORT __declspec(dllimport)
# else
#  define DLLEXPORT
# endif
#else
# define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void DLLEXPORT qlFreeCreditDefaultSwap(QlCreditDefaultSwap *o);
  QlInstrument* DLLEXPORT qlCreditDefaultSwapAsInstrument(QlCreditDefaultSwap *o);
  void DLLEXPORT qlFreeClaim(QlClaim *o);
  QlClaim* DLLEXPORT qlFaceValueAccrualClaim(QlBond* referenceSecurity, char **e);
  QlClaim* DLLEXPORT qlFaceValueClaim(char **e);
  QlCreditDefaultSwap* DLLEXPORT qlCreditDefaultSwap(int side, double notional, double spread, Schedule* schedule, int paymentConvention, DayCounter* dayCounter, int settlesAccrual, int paysAtDefaultTime, int protectionStart, QlClaim* x9, char **e);
  QlCreditDefaultSwap* DLLEXPORT qlCreditDefaultSwap1(int side, double notional, double upfront, double spread, Schedule* schedule, int paymentConvention, DayCounter* dayCounter, int settlesAccrual, int paysAtDefaultTime, int protectionStart, int upfrontDate, QlClaim* x11, char **e);
  QlOption* DLLEXPORT qlCdsOptionAsOption(QlCdsOption *o);
  void DLLEXPORT qlFreeCdsOption(QlCdsOption *o);
  double DLLEXPORT qlCreditDefaultSwapFairSpread(QlCreditDefaultSwap* o, char **e);
  double DLLEXPORT qlCreditDefaultSwapConventionalSpread(QlCreditDefaultSwap* o, double conventionalRecovery, QlYieldTermStructure* discountCurve, DayCounter* dayCounter, char **e);
  double DLLEXPORT qlCreditDefaultSwapCouponLegBPS(QlCreditDefaultSwap* o, char **e);
  double DLLEXPORT qlCreditDefaultSwapCouponLegNPV(QlCreditDefaultSwap* o, char **e);
  Leg* DLLEXPORT qlCreditDefaultSwapCoupons(QlCreditDefaultSwap* o, char **e);
  double DLLEXPORT qlCreditDefaultSwapDefaultLegNPV(QlCreditDefaultSwap* o, char **e);
  double DLLEXPORT qlCreditDefaultSwapFairUpfront(QlCreditDefaultSwap* o, char **e);
  double DLLEXPORT qlCreditDefaultSwapImpliedHazardRate(QlCreditDefaultSwap* o, double targetNPV, QlYieldTermStructure* discountCurve, DayCounter* dayCounter, double recoveryRate, double accuracy, char **e);
  double DLLEXPORT qlCreditDefaultSwapUpfrontBPS(QlCreditDefaultSwap* o, char **e);
  double DLLEXPORT qlCreditDefaultSwapUpfrontNPV(QlCreditDefaultSwap* o, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
