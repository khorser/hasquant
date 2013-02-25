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

extern "C" {
  DayCounter *DLLEXPORT qlDayCounter(const char *name, char **e);
  DayCounter *DLLEXPORT qlDayCounterBusiness252(Calendar *cal, char **e);
  const char *DLLEXPORT qlDayCounterName(DayCounter *counter);
  int DLLEXPORT qlDayCounterDayCount(DayCounter* o, int x0, int x1, char **e);
  double DLLEXPORT qlDayCounterYearFraction(DayCounter* o, int x0, int x1, int refPeriodStart, int refPeriodEnd, char **e);

  void DLLEXPORT qlFreeDayCounter(DayCounter *counter);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
