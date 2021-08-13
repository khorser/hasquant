#ifdef __cplusplus
extern "C" {
#endif
  QlIborIndex *qlIborIndex(char *name, int, int, unsigned settlDays,
    Currency *ccy, Calendar *cal, int conv, int eom, DayCounter *dayCount,
    QlYieldTermStructure *fwd, char **e);
  QlIborIndex *qlLibor(char *name, int, int, unsigned settlDays,
    Currency *ccy, Calendar *cal, DayCounter *dc, QlYieldTermStructure *fwd,
    char **e);
  QlIborIndex *qlDailyTenorLibor(char *name, unsigned settlDays,
    Currency *ccy, Calendar *cal, DayCounter *dayCount,
    QlYieldTermStructure *fwd, char **e);
  QlOvernightIndex *qlOvernightIndex(char *name, unsigned settlDays, Currency *cur,
    Calendar *cal, DayCounter *dayCount, QlYieldTermStructure *fwd, char **e);
  QlIborIndex *qlCreateIbor(char *name, int, int,
    QlYieldTermStructure *fwd, char **e);
  QlIborIndex *qlCreateIborON(char *name, QlYieldTermStructure *fwd, char **e);
  QlOvernightIndex *qlCreateONIndex(int index, QlYieldTermStructure *fwd, char **e);
  QlIborIndex *qlCreateDailyTenorIbor(char *name, unsigned settlDays,
    QlYieldTermStructure *fwd, char **e);

  void qlFreeIborIndex(QlIborIndex *i);
  QlInterestRateIndex* qlIborIndexAsInterestRateIndex(QlIborIndex *o);
  void qlFreeOvernightIndex(QlOvernightIndex *o);
  QlIborIndex* qlOvernightIndexAsIborIndex(QlOvernightIndex *o);
  int qlIborIndexBusinessDayConvention(QlIborIndex* o);
  int qlIborIndexEndOfMonth(QlIborIndex* o);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
