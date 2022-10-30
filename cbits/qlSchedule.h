#ifdef __cplusplus
extern "C" {
#endif
  Schedule *qlSchedule(int eff, int term, int, int, Calendar *cal,
        int conv, int termConv, int rule, int eom, int first, int nextToLast,
	char **e);
  Schedule *qlSchedule1(unsigned len, int *dates, Calendar *cal, int conv,
    char **e);
  Schedule *qlScheduleUntil(Schedule *sched, int date, char **e);
  void qlScheduleDates(Schedule *sched, unsigned *count, int **days);
  void qlFreeSchedule(Schedule *s);

  int qlPeriodFromFrequency1(int freq, int *, char **e);
  int qlPeriodToFrequency1(int l, int u, char **e);
  int qlPeriodParserParse1(char* str, int *u, char **e);
  int qlPeriodAdd1(int, int u1, int, int u2, int *u, char **e);
  int qlPeriodDivide1(int, int u1, int n2, int *u, char **e);
  int qlPeriodNormalize1(int, int u, int *, char **e);
  int qlPeriodsLT1(int, int u1, int, int u2, char **e);

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
