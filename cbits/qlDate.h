#ifdef __cplusplus
extern "C" {
#endif
  int qlMinDateSerialNumber();
  int qlMaxDateSerialNumber();
  int qlMinYear();
  int qlMinMonth();
  int qlMinDay();
  int qlWeekday(int date);
  int qlDateDayOfYear(int o);
  int qlDateEndOfMonth(int d);
  int qlDateIsEndOfMonth(int d);
  int qlDateNextWeekday(int d, int w);
  int qlDateNthWeekday(unsigned n, int w, int m, int y);

  char* qlIMMCode(int immDate, char **e);
  int qlIMMDate(char* immCode, int referenceDate, char **e);
  int qlIMMIsIMMcode(char* in, int mainCycle);
  int qlIMMIsIMMdate(int d, int mainCycle);
  char* qlIMMNextCode1(char* immCode, int mainCycle, int referenceDate, char **e);
  char* qlIMMNextCode(int d, int mainCycle);
  int qlIMMNextDate1(char* immCode, int mainCycle, int referenceDate, char **e);
  int qlIMMNextDate(int d, int mainCycle);

  int qlAddPeriod(int d, int, int, char **e);

  void qlECBAddDate(int d, char **e);
  char* qlECBCode(int ecbDate, char **e);
  int qlECBDate1(char* ecbCode, int referenceDate, char **e);
  int qlECBDate(int m, int y, char **e);
  int qlECBIsECBcode(char* in, char **e);
  int qlECBIsECBdate(int d, char **e);
  int* qlECBKnownDates(unsigned *count, char **e);
  char* qlECBNextCode1(char* ecbCode, char **e);
  char* qlECBNextCode(int d, char **e);
  int qlECBNextDate1(char* ecbCode, int referenceDate, char **e);
  int qlECBNextDate(int d, char **e);
  int* qlECBNextDates(int d, unsigned *count, char **e);
  int* qlECBNextDates1(char* ecbCode, int referenceDate, unsigned *count, char **e);
  void qlECBRemoveDate(int d, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
