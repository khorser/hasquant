#ifdef __cplusplus
extern "C" {
#endif
  int qlSettingsEvaluationDate();
  int qlSettingsEnforceTodaysHistoricFixings();
  void qlSettingsSetEvaluationDate(int x, char **e);
  void qlSettingsSetEnforceTodaysHistoricFixings(int x);
  int qlSettingsIncludeTodaysCashFlows();
  void qlSettingsSetIncludeTodaysCashFlows(int x);
  int qlSettingsIncludeReferenceDateEvents();
  void qlSettingsSetIncludeReferenceDateEvents(int x0);
  void *qlSavedSettings();
  void qlFreeSavedSettings(void *settings);

  const char *qlVersion();
  const char *qlBoostVersion();
  void qlFreeString(char *p);
  void qlFreeInts(int *p);
  void qlFreeUInts(unsigned *p);
  void qlFreeDoubles(double *p);
  void qlFreePointerArray(void **p);
  int qlNullInteger();
  double qlNullReal();
  double qlEpsilon();
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
