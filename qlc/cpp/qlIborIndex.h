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
  QlIborIndex *DLLEXPORT qlIborIndex(char *name, Period *period, unsigned settlDays,
    Currency *ccy, Calendar *cal, int conv, int eom, DayCounter *dayCount,
    QlYieldTermStructure *fwd, char **e);
  QlIborIndex *DLLEXPORT qlLibor(char *name, Period *tenor, unsigned settlDays,
    Currency *ccy, Calendar *cal, DayCounter *dc, QlYieldTermStructure *fwd,
    char **e);
  QlIborIndex *DLLEXPORT qlDailyTenorLibor(char *name, unsigned settlDays,
    Currency *ccy, Calendar *cal, DayCounter *dayCount,
    QlYieldTermStructure *fwd, char **e);
  QlOvernightIndex *DLLEXPORT qlOvernightIndex(char *name, unsigned settlDays, Currency *cur,
    Calendar *cal, DayCounter *dayCount, QlYieldTermStructure *fwd, char **e);
  QlIborIndex *DLLEXPORT qlCreateIbor(char *name, Period *tenor,
    QlYieldTermStructure *fwd, char **e);
  QlIborIndex *DLLEXPORT qlCreateIborON(char *name, QlYieldTermStructure *fwd, char **e);
  QlOvernightIndex *DLLEXPORT qlCreateONIndex(char *name, QlYieldTermStructure *fwd, char **e);
  QlIborIndex *DLLEXPORT qlCreateDailyTenorIbor(char *name, unsigned settlDays,
    QlYieldTermStructure *fwd, char **e);

  void DLLEXPORT qlFreeIborIndex(QlIborIndex *i);
  QlInterestRateIndex* DLLEXPORT qlIborIndexAsInterestRateIndex(QlIborIndex *o);
  void DLLEXPORT qlFreeOvernightIndex(QlOvernightIndex *o);
  QlIborIndex* DLLEXPORT qlOvernightIndexAsIborIndex(QlOvernightIndex *o);
  int DLLEXPORT qlIborIndexBusinessDayConvention(QlIborIndex* o, char **e);
  int DLLEXPORT qlIborIndexEndOfMonth(QlIborIndex* o, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
