#ifdef __cplusplus
extern "C" {
#endif
  DayCounter *qlDayCounter(int type, int convention, char **e);
  DayCounter *qlDayCounterBusiness252(Calendar *cal, char **e);
  const char *qlDayCounterName(DayCounter *counter);
  int qlDayCounterDayCount(DayCounter* o, int x0, int x1);
  double qlDayCounterYearFraction(DayCounter* o, int x0, int x1, int refPeriodStart, int refPeriodEnd, char **e);

  void qlFreeDayCounter(DayCounter *counter);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
