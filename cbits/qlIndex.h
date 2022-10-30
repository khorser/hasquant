#ifdef __cplusplus
extern "C" {
#endif
  void qlIndexAddFixing(QlIndex *i, int date, double fix, int overwrite, char **e);
  void qlFreeIndex(QlIndex *i);
  void qlFreeInterestRateIndex(QlInterestRateIndex *o);
  QlIndex* qlInterestRateIndexAsIndex(QlInterestRateIndex *o);
  void qlFreeSwapIndex(QlSwapIndex *o);
  QlInterestRateIndex* qlSwapIndexAsInterestRateIndex(QlSwapIndex *o);

  void qlFreeBMAIndex(QlBMAIndex *o);
  QlInterestRateIndex* qlBMAIndexAsInterestRateIndex(QlBMAIndex *o);
  void qlFreeOvernightIndexedSwapIndex(QlOvernightIndexedSwapIndex *o);
  QlSwapIndex* qlOvernightIndexedSwapIndexAsSwapIndex(QlOvernightIndexedSwapIndex *o);
  QlBMAIndex* qlBMAIndex(QlYieldTermStructure* h, char **e);

  QlSwapIndex* qlCreateLiborSwapIndex(int, int, int, QlYieldTermStructure* h1, QlYieldTermStructure* h2, char **e);
  QlOvernightIndexedSwapIndex* qlOvernightIndexedSwapIndex(char* familyName, int, int, unsigned settlementDays, Currency* currency, QlOvernightIndex* overnightIndex, char **e);
  QlSwapIndex* qlSwapIndex1(char* familyName, int, int, unsigned settlementDays, Currency* currency, Calendar* calendar, int, int, int fixedLegConvention, DayCounter* fixedLegDayCounter, QlIborIndex* iborIndex, QlYieldTermStructure* discountingTermStructure, char **e);
  QlSwapIndex* qlSwapIndex(char* familyName, int, int, unsigned settlementDays, Currency* currency, Calendar* calendar, int, int, int fixedLegConvention, DayCounter* fixedLegDayCounter, QlIborIndex* iborIndex, char **e);

  Schedule* qlBMAIndexFixingSchedule(QlBMAIndex* o, int start, int end, char **e);
  QlOvernightIndexedSwap* qlOvernightIndexedSwapIndexUnderlyingSwap(QlOvernightIndexedSwapIndex* o, int fixingDate, char **e);
  QlVanillaSwap* qlSwapIndexUnderlyingSwap(QlSwapIndex* o, int fixingDate, char **e);
  double qlInterestRateIndexForecastFixing(QlInterestRateIndex* o, int fixingDate, char **e);
  Calendar* qlIndexFixingCalendar(QlIndex* o, char **e);
  Currency* qlInterestRateIndexCurrency(QlInterestRateIndex* o, char **e);
  DayCounter* qlInterestRateIndexDayCounter(QlInterestRateIndex* o, char **e);
  unsigned qlInterestRateIndexFixingDays(QlInterestRateIndex* o);
  int qlInterestRateIndexTenor(QlInterestRateIndex* o, int *, char **e);
  const char* qlIndexName(QlIndex *index);
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

  QlIborIndex *qlCreateIbor(int, int, int, QlYieldTermStructure *fwd, char **e);
  QlOvernightIndex *qlCreateONIndex(int index, QlYieldTermStructure *fwd, char **e);

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
