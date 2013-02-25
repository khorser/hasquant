#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  int DLLEXPORT qlSettingsEvaluationDate();
  int DLLEXPORT qlSettingsEnforceTodaysHistoricFixings();
  void DLLEXPORT qlSettingsSetEvaluationDate(int x, char **e);
  void DLLEXPORT qlSettingsSetEnforceTodaysHistoricFixings(int x);
  int DLLEXPORT qlSettingsIncludeTodaysCashFlows();
  void DLLEXPORT qlSettingsSetIncludeTodaysCashFlows(int x);
  void DLLEXPORT qlSettingsAnchorEvaluationDate();
  int DLLEXPORT qlSettingsIncludeReferenceDateEvents();
  void DLLEXPORT qlSettingsResetEvaluationDate(char **e);
  void DLLEXPORT qlSettingsSetIncludeReferenceDateEvents(int x0);
  void *DLLEXPORT qlSavedSettings();
  void DLLEXPORT qlFreeSavedSettings(void *settings);
}
