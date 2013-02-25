#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
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
