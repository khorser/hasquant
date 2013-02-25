#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  DayCounter *DLLEXPORT qlDayCounter(const char *name, char **e);
  DayCounter *DLLEXPORT qlDayCounterBusiness252(Calendar *cal, char **e);
  const char *DLLEXPORT qlDayCounterName(DayCounter *counter);
  int DLLEXPORT qlDayCounterDayCount(DayCounter* o, int x0, int x1, char **e);
  double DLLEXPORT qlDayCounterYearFraction(DayCounter* o, int x0, int x1, int refPeriodStart, int refPeriodEnd, char **e);

  void DLLEXPORT qlFreeDayCounter(DayCounter *counter);
}
