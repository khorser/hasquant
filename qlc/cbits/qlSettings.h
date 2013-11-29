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
  int DLLEXPORT qlSettingsEvaluationDate();
  int DLLEXPORT qlSettingsEnforceTodaysHistoricFixings();
  void DLLEXPORT qlSettingsSetEvaluationDate(int x, char **e);
  void DLLEXPORT qlSettingsSetEnforceTodaysHistoricFixings(int x);
  int DLLEXPORT qlSettingsIncludeTodaysCashFlows();
  void DLLEXPORT qlSettingsSetIncludeTodaysCashFlows(int x);
  void DLLEXPORT qlSettingsAnchorEvaluationDate();
  int DLLEXPORT qlSettingsIncludeReferenceDateEvents();
  void DLLEXPORT qlSettingsSetIncludeReferenceDateEvents(int x0);
  void *DLLEXPORT qlSavedSettings();
  void DLLEXPORT qlFreeSavedSettings(void *settings);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
