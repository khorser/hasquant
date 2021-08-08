#ifdef __cplusplus
extern "C" {
#endif
  QlFloatingRateCouponPricer *qlBlackIborCouponPricer(
    QlOptionletVolatilityStructure *vol, char **e);
  void qlFreeFloatingCouponPricer(QlFloatingRateCouponPricer *p);
  QlFloatingRateCouponPricer* qlAnalyticHaganPricer(QlSwaptionVolatilityStructure* swaptionVol, int modelOfYieldCurve, QlQuote* meanReversion, char **e);
  QlFloatingRateCouponPricer* qlNumericHaganPricer(QlSwaptionVolatilityStructure* swaptionVol, int modelOfYieldCurve, QlQuote* meanReversion, double lowerLimit, double upperLimit, double precision, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
