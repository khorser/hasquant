#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
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
