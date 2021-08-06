#ifdef __cplusplus
extern "C" {
#endif
  Schedule *qlSchedule(int eff, int term, int, int, Calendar *cal,
        int conv, int termConv, int rule, int eom, int first, int nextToLast,
	char **e);
  Schedule *qlSchedule1(unsigned len, int *dates, Calendar *cal, int conv,
    char **e);
  Schedule *qlScheduleUntil(Schedule *sched, int date, char **e);
  int *qlScheduleDates(Schedule *sched, unsigned *count);

  void qlFreeSchedule(Schedule *s);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
