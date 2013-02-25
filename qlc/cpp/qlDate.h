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
  int DLLEXPORT qlMinDateSerialNumber();
  int DLLEXPORT qlMaxDateSerialNumber();
  int DLLEXPORT qlMinYear();
  int DLLEXPORT qlMinMonth();
  int DLLEXPORT qlMinDay();
  int DLLEXPORT qlWeekday(int date);
  int DLLEXPORT qlDateDayOfYear(int o, char **e);
  int DLLEXPORT qlDateEndOfMonth(int d, char **e);
  int DLLEXPORT qlDateIsEndOfMonth(int d, char **e);
  int DLLEXPORT qlDateNextWeekday(int d, int w, char **e);
  int DLLEXPORT qlDateNthWeekday(unsigned n, int w, int m, int y, char **e);

  char* DLLEXPORT qlIMMCode(int immDate, char **e);
  int DLLEXPORT qlIMMDate(char* immCode, int referenceDate, char **e);
  int DLLEXPORT qlIMMIsIMMcode(char* in, int mainCycle, char **e);
  int DLLEXPORT qlIMMIsIMMdate(int d, int mainCycle, char **e);
  char* DLLEXPORT qlIMMNextCode1(char* immCode, int mainCycle, int referenceDate, char **e);
  char* DLLEXPORT qlIMMNextCode(int d, int mainCycle, char **e);
  int DLLEXPORT qlIMMNextDate1(char* immCode, int mainCycle, int referenceDate, char **e);
  int DLLEXPORT qlIMMNextDate(int d, int mainCycle, char **e);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
