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
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
