extern "C"
{
  /* utilities */
  const char *qlVersion();
  const char *boostVersion();

  void	qlFreeString(char *p);
  void *qlAllocateDate(int x, char **e);
  int	qlDateSerialNumber(void *);
  void  qlFreeDate(void *p);

  int	qlMinDate();
  int	qlMinYear();
  int	qlMinMonth();
  int	qlMinDay();

  /* settings */
  int	qlSettingsEvaluationDate();
  void	qlSettingsSetEvaluationDate(void *x);
  void	qlSettingsSetEnforceTodaysHistoricFixings(int x);
  int	qlSettingsEnforceTodaysHistoricFixings();
}

/* vim: set ft=CPP ff=unix ts=8 sts=2 sw=2: */
