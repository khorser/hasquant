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

//  QlSwapIndex* qlCreateLiborSwapIndex(char *name, int, int, QlYieldTermStructure* h1, QlYieldTermStructure* h2, char **e);
//  QlOvernightIndexedSwapIndex* qlOvernightIndexedSwapIndex(char* familyName, int, int, unsigned settlementDays, Currency* currency, QlOvernightIndex* overnightIndex, char **e);
//  QlSwapIndex* qlSwapIndex1(char* familyName, int, int, unsigned settlementDays, Currency* currency, Calendar* calendar, int, int, int fixedLegConvention, DayCounter* fixedLegDayCounter, QlIborIndex* iborIndex, QlYieldTermStructure* discountingTermStructure, char **e);
//  QlSwapIndex* qlSwapIndex(char* familyName, int, int, unsigned settlementDays, Currency* currency, Calendar* calendar, int, int, int fixedLegConvention, DayCounter* fixedLegDayCounter, QlIborIndex* iborIndex, char **e);

//  Schedule* qlBMAIndexFixingSchedule(QlBMAIndex* o, int start, int end, char **e);
//  QlOvernightIndexedSwap* qlOvernightIndexedSwapIndexUnderlyingSwap(QlOvernightIndexedSwapIndex* o, int fixingDate, char **e);
//  QlVanillaSwap* qlSwapIndexUnderlyingSwap(QlSwapIndex* o, int fixingDate, char **e);
  double qlInterestRateIndexForecastFixing(QlInterestRateIndex* o, int fixingDate, char **e);
  Calendar* qlIndexFixingCalendar(QlIndex* o, char **e);
  Currency* qlInterestRateIndexCurrency(QlInterestRateIndex* o, char **e);
  DayCounter* qlInterestRateIndexDayCounter(QlInterestRateIndex* o, char **e);
  unsigned qlInterestRateIndexFixingDays(QlInterestRateIndex* o);
  int qlInterestRateIndexTenor(QlInterestRateIndex* o, int *, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
