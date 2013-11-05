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
  int DLLEXPORT qlMinDateSerialNumber();
  int DLLEXPORT qlMaxDateSerialNumber();
  int DLLEXPORT qlMinYear();
  int DLLEXPORT qlMinMonth();
  int DLLEXPORT qlMinDay();
  int DLLEXPORT qlWeekday(int date);
  int DLLEXPORT qlDateDayOfYear(int o);
  int DLLEXPORT qlDateEndOfMonth(int d);
  int DLLEXPORT qlDateIsEndOfMonth(int d);
  int DLLEXPORT qlDateNextWeekday(int d, int w);
  int DLLEXPORT qlDateNthWeekday(unsigned n, int w, int m, int y);

  char* DLLEXPORT qlIMMCode(int immDate, char **e);
  int DLLEXPORT qlIMMDate(char* immCode, int referenceDate, char **e);
  int DLLEXPORT qlIMMIsIMMcode(char* in, int mainCycle);
  int DLLEXPORT qlIMMIsIMMdate(int d, int mainCycle);
  char* DLLEXPORT qlIMMNextCode1(char* immCode, int mainCycle, int referenceDate, char **e);
  char* DLLEXPORT qlIMMNextCode(int d, int mainCycle);
  int DLLEXPORT qlIMMNextDate1(char* immCode, int mainCycle, int referenceDate, char **e);
  int DLLEXPORT qlIMMNextDate(int d, int mainCycle);

  int DLLEXPORT qlAddPeriod(int d, Period *p, char **e);
  int DLLEXPORT qlSubtractPeriod(int d, Period *p, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
