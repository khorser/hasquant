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
  void DLLEXPORT qlFreeFixedRateBondForward(QlFixedRateBondForward *fwd);
  QlForward* DLLEXPORT qlFixedRateBondForwardAsForward(QlFixedRateBondForward *fwd);
  QlFixedRateBondForward* DLLEXPORT qlFixedRateBondForward(int valueDate, int maturityDate, int type, double strike, unsigned settlementDays, DayCounter* dayCounter, Calendar* calendar, int businessDayConvention, QlFixedRateBond* fixedCouponBond, QlYieldTermStructure* discountCurve, QlYieldTermStructure* incomeDiscountCurve, char **e);
  double DLLEXPORT qlFixedRateBondForwardCleanForwardPrice(QlFixedRateBondForward* o, char **e);
  double DLLEXPORT qlFixedRateBondForwardForwardPrice(QlFixedRateBondForward* o, char **e);
  void DLLEXPORT qlFreeForward(QlForward *fwd);
  QlInstrument* DLLEXPORT qlForwardAsInstrument(QlForward *fwd);
  double DLLEXPORT qlForwardForwardValue(QlForward* o, char **e);
  InterestRate* DLLEXPORT qlForwardImpliedYield(QlForward* o, double underlyingSpotValue, double forwardValue, int settlementDate, int compoundingConvention, DayCounter* dayCounter, char **e);
  int DLLEXPORT qlForwardSettlementDate(QlForward* o, char **e);
  double DLLEXPORT qlForwardSpotIncome(QlForward* o, QlYieldTermStructure* incomeDiscountCurve, char **e);
  double DLLEXPORT qlForwardSpotValue(QlForward* o, char **e);
  void DLLEXPORT qlFreeForwardRateAgreement(QlForwardRateAgreement *fwd);
  QlForward* DLLEXPORT qlForwardRateAgreementAsForward(QlForwardRateAgreement *fwd);
  QlForwardRateAgreement* DLLEXPORT qlForwardRateAgreement(int valueDate, int maturityDate, int type, double strikeForwardRate, double notionalAmount, QlIborIndex* index, QlYieldTermStructure* discountCurve, char **e);

  InterestRate* DLLEXPORT qlForwardRateAgreementForwardRate(QlForwardRateAgreement* o, char **e);
  int DLLEXPORT qlForwardRateAgreementIsExpired(QlForwardRateAgreement* o, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
