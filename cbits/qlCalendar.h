#ifdef __cplusplus
extern "C" {
#endif
  Calendar *qlCalendar(int country, int market, char **e);
  const char *qlCalendarName(Calendar *calendar);
  int qlCalendarAdjust(Calendar *c, int date, int conv);
  int qlCalendarAdvance(Calendar *c, int date, int n, int unit, int conv, int eom);
  void qlCalendarAddHoliday(Calendar* o, int x0, char **e);
  int qlCalendarAdvance1(Calendar* o, int date, int, int, int convention, int endOfMonth, char **e);
  int qlCalendarBusinessDaysBetween(Calendar* o, int from, int to, int includeFirst, int includeLast, char **e);
  int qlCalendarEndOfMonth(Calendar* o, int d, char **e);
  int qlCalendarIsBusinessDay(Calendar* o, int d, char **e);
  int qlCalendarIsEndOfMonth(Calendar* o, int d, char **e);
  int qlCalendarIsHoliday(Calendar* o, int d, char **e);
  int qlCalendarIsWeekend(Calendar* o, int w, char **e);
  void qlCalendarRemoveHoliday(Calendar* o, int x0, char **e);
  Calendar* qlBespokeCalendar(char* name, unsigned len, int *weekends, char **e);
  Calendar* qlJointCalendar2(Calendar* x_1, Calendar* x0, int x1, char **e);
  Calendar* qlJointCalendar3(Calendar* x_1, Calendar* x0, Calendar* x1, int x2, char **e);
  Calendar* qlJointCalendar4(Calendar* x_1, Calendar* x0, Calendar* x1, Calendar* x2, int x3, char **e);

  int* qlCalendarHolidayList(Calendar* calendar, int from, int to, int includeWeekEnds, unsigned *len, char **e);
  void qlFreeCalendar(Calendar *calendar);
#ifdef __cplusplus
}
#endif

/* vim: set ft=c ff=unix ts=8 sts=2 sw=2 et: */
