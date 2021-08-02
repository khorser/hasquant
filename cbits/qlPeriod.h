#ifdef __cplusplus
extern "C" {
#endif
  int qlPeriodFromFrequency1(int freq, int *, char **e);
  int qlPeriodToFrequency1(int l, int u, char **e);

  int qlPeriodParserParse1(char* str, int *, char **e);

  int qlPeriodAdd1(int, int, int, int, int *, char **e);
  int qlPeriodDivide1(int, int, int n, int *, char **e);
  int qlPeriodNormalize1(int, int, int *, char **e);
  int qlPeriodsLT1(int, int, int, int, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
