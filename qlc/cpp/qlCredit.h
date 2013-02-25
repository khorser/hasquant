#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  void DLLEXPORT qlFreeCreditDefaultSwap(QlCreditDefaultSwap *o);
  QlInstrument* DLLEXPORT qlCreditDefaultSwapAsInstrument(QlCreditDefaultSwap *o);
  void DLLEXPORT qlFreeClaim(QlClaim *o);
  QlClaim* DLLEXPORT qlFaceValueAccrualClaim(QlBond* referenceSecurity, char **e);
  QlClaim* DLLEXPORT qlFaceValueClaim(char **e);
  QlCreditDefaultSwap* DLLEXPORT qlCreditDefaultSwap(int side, double notional, double spread, Schedule* schedule, int paymentConvention, DayCounter* dayCounter, int settlesAccrual, int paysAtDefaultTime, int protectionStart, QlClaim* x9, char **e);
  QlCreditDefaultSwap* DLLEXPORT qlCreditDefaultSwap1(int side, double notional, double upfront, double spread, Schedule* schedule, int paymentConvention, DayCounter* dayCounter, int settlesAccrual, int paysAtDefaultTime, int protectionStart, int upfrontDate, QlClaim* x11, char **e);
  QlOption* DLLEXPORT qlCdsOptionAsOption(QlCdsOption *o);
  void DLLEXPORT qlFreeCdsOption(QlCdsOption *o);
}
