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
  void DLLEXPORT qlIndexAddFixing(QlIndex *i, int date, double fix, int overwrite, char **e);
  void DLLEXPORT qlFreeIndex(QlIndex *i);
  void DLLEXPORT qlFreeInterestRateIndex(QlInterestRateIndex *o);
  QlIndex* DLLEXPORT qlInterestRateIndexAsIndex(QlInterestRateIndex *o);
  void DLLEXPORT qlFreeSwapIndex(QlSwapIndex *o);
  QlInterestRateIndex* DLLEXPORT qlSwapIndexAsInterestRateIndex(QlSwapIndex *o);

  void DLLEXPORT qlFreeBMAIndex(QlBMAIndex *o);
  QlInterestRateIndex* DLLEXPORT qlBMAIndexAsInterestRateIndex(QlBMAIndex *o);
  void DLLEXPORT qlFreeOvernightIndexedSwapIndex(QlOvernightIndexedSwapIndex *o);
  QlSwapIndex* DLLEXPORT qlOvernightIndexedSwapIndexAsSwapIndex(QlOvernightIndexedSwapIndex *o);
  QlBMAIndex* DLLEXPORT qlBMAIndex(QlYieldTermStructure* h, char **e);

  QlSwapIndex* DLLEXPORT qlCreateLiborSwapIndex(char *name, Period* tenor, QlYieldTermStructure* h1, QlYieldTermStructure* h2, char **e);
  QlOvernightIndexedSwapIndex* DLLEXPORT qlOvernightIndexedSwapIndex(char* familyName, Period* tenor, unsigned settlementDays, Currency* currency, QlOvernightIndex* overnightIndex, char **e);
  QlSwapIndex* DLLEXPORT qlSwapIndex1(char* familyName, Period* tenor, unsigned settlementDays, Currency* currency, Calendar* calendar, Period* fixedLegTenor, int fixedLegConvention, DayCounter* fixedLegDayCounter, QlIborIndex* iborIndex, QlYieldTermStructure* discountingTermStructure, char **e);
  QlSwapIndex* DLLEXPORT qlSwapIndex(char* familyName, Period* tenor, unsigned settlementDays, Currency* currency, Calendar* calendar, Period* fixedLegTenor, int fixedLegConvention, DayCounter* fixedLegDayCounter, QlIborIndex* iborIndex, char **e);

  Schedule* DLLEXPORT qlBMAIndexFixingSchedule(QlBMAIndex* o, int start, int end, char **e);
  QlOvernightIndexedSwap* DLLEXPORT qlOvernightIndexedSwapIndexUnderlyingSwap(QlOvernightIndexedSwapIndex* o, int fixingDate, char **e);
  QlVanillaSwap* DLLEXPORT qlSwapIndexUnderlyingSwap(QlSwapIndex* o, int fixingDate, char **e);
  double DLLEXPORT qlInterestRateIndexForecastFixing(QlInterestRateIndex* o, int fixingDate, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
