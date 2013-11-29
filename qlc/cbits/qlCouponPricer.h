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
  QlFloatingRateCouponPricer *DLLEXPORT qlBlackIborCouponPricer(
    QlOptionletVolatilityStructure *vol, char **e);
  void DLLEXPORT qlFreeFloatingCouponPricer(QlFloatingRateCouponPricer *p);
  QlFloatingRateCouponPricer* DLLEXPORT qlAnalyticHaganPricer(QlSwaptionVolatilityStructure* swaptionVol, int modelOfYieldCurve, QlQuote* meanReversion, char **e);
  QlFloatingRateCouponPricer* DLLEXPORT qlNumericHaganPricer(QlSwaptionVolatilityStructure* swaptionVol, int modelOfYieldCurve, QlQuote* meanReversion, double lowerLimit, double upperLimit, double precision, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
