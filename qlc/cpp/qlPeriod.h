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
  Period *DLLEXPORT qlPeriod(int n, int u, char **e);
  Period *DLLEXPORT qlPeriodFromFrequency(int freq, char **e);
  int DLLEXPORT qlPeriodToFrequency(Period *period, char **e);

  void DLLEXPORT qlFreePeriod(Period *period);
  Period* DLLEXPORT qlPeriodParserParse(char* str, char **e);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
