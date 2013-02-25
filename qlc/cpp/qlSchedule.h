#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  Schedule *DLLEXPORT qlSchedule(int eff, int term, Period *tenor, Calendar *cal,
        int conv, int termConv, int rule, int eom, int first, int nextToLast,
	char **e);
  Schedule *DLLEXPORT qlSchedule1(unsigned len, int *dates, Calendar *cal, int conv,
    char **e);
  Schedule *DLLEXPORT qlScheduleUntil(Schedule *sched, int date, char **e);
  int *DLLEXPORT qlScheduleDates(Schedule *sched, unsigned *count);

  void DLLEXPORT qlFreeSchedule(Schedule *s);
}
