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
  Period *DLLEXPORT qlPeriod(int n, int u, char **e);
  Period *DLLEXPORT qlPeriodFromFrequency(int freq, char **e);
  int DLLEXPORT qlPeriodFromFrequency1(int freq, int *, char **e);
  int DLLEXPORT qlPeriodToFrequency(Period *period, char **e);
  int DLLEXPORT qlPeriodToFrequency1(int l, int u, char **e);

  void DLLEXPORT qlFreePeriod(Period *period);
  Period* DLLEXPORT qlPeriodParserParse(char* str, char **e);

  int DLLEXPORT qlPeriodUnits(Period *p);
  int DLLEXPORT qlPeriodLength(Period *p);

  Period* DLLEXPORT qlPeriodAdd(Period *p1, Period *p2, char **e);
  Period* DLLEXPORT qlPeriodSubtract(Period *p1, Period *p2, char **e);
  Period* DLLEXPORT qlPeriodDivide(Period *p1, int n, char **e);
  int DLLEXPORT qlPeriodsEQ(Period *p1, Period *p2, char **e);
  int DLLEXPORT qlPeriodsLT(Period *p1, Period *p2, char **e);
  Period* DLLEXPORT qlPeriodNormalize(Period *p1, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
