#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  Calendar *DLLEXPORT qlCalendar(const char *name, char **e);
  const char *DLLEXPORT qlCalendarName(Calendar *calendar);
  int DLLEXPORT qlCalendarAdjust(Calendar *c, int date, int conv);
  int DLLEXPORT qlCalendarAdvance(Calendar *c, int date, int n, int unit, int conv, int eom);
  void DLLEXPORT qlCalendarAddHoliday(Calendar* o, int x0, char **e);
  int DLLEXPORT qlCalendarAdvance1(Calendar* o, int date, Period* period, int convention, int endOfMonth, char **e);
  int DLLEXPORT qlCalendarBusinessDaysBetween(Calendar* o, int from, int to, int includeFirst, int includeLast, char **e);
  int DLLEXPORT qlCalendarEndOfMonth(Calendar* o, int d, char **e);
  int DLLEXPORT qlCalendarIsBusinessDay(Calendar* o, int d, char **e);
  int DLLEXPORT qlCalendarIsEndOfMonth(Calendar* o, int d, char **e);
  int DLLEXPORT qlCalendarIsHoliday(Calendar* o, int d, char **e);
  int DLLEXPORT qlCalendarIsWeekend(Calendar* o, int w, char **e);
  void DLLEXPORT qlCalendarRemoveHoliday(Calendar* o, int x0, char **e);
  Calendar* DLLEXPORT qlBespokeCalendar(char* name, unsigned len, int *weekends, char **e);
  Calendar* DLLEXPORT qlJointCalendar2(Calendar* x_1, Calendar* x0, int x1, char **e);
  Calendar* DLLEXPORT qlJointCalendar3(Calendar* x_1, Calendar* x0, Calendar* x1, int x2, char **e);
  Calendar* DLLEXPORT qlJointCalendar4(Calendar* x_1, Calendar* x0, Calendar* x1, Calendar* x2, int x3, char **e);

  int* DLLEXPORT qlCalendarHolidayList(Calendar* calendar, int from, int to, int includeWeekEnds, unsigned *len, char **e);
  void DLLEXPORT qlFreeCalendar(Calendar *calendar);
}
