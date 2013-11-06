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
  QlOptionletVolatilityStructure *DLLEXPORT qlConstantOptionletVol1(unsigned days, Calendar *cal, int conv, QlQuote *q, DayCounter *dc, char **e);
  void DLLEXPORT qlFreeOptionletVolatilityStructure(QlOptionletVolatilityStructure *p);
  QlVolatilityTermStructure* DLLEXPORT qlOptionletVolatilityStructureAsVolatilityTermStructure(QlOptionletVolatilityStructure *o);
  void DLLEXPORT qlFreeVolatilityTermStructure(QlVolatilityTermStructure *o);
  QlTermStructure* DLLEXPORT qlVolatilityTermStructureAsTermStructure(QlVolatilityTermStructure *o);
  void DLLEXPORT qlFreeBlackVolTermStructure(QlBlackVolTermStructure *o);
  QlVolatilityTermStructure* DLLEXPORT qlBlackVolTermStructureAsVolatilityTermStructure(QlBlackVolTermStructure *o);
  void DLLEXPORT qlFreeSwaptionVolatilityStructure(QlSwaptionVolatilityStructure *o);
  QlVolatilityTermStructure* DLLEXPORT qlSwaptionVolatilityStructureAsVolatilityTermStructure(QlSwaptionVolatilityStructure *o);
  void DLLEXPORT qlFreeSmileSection(QlSmileSection *o);
  QlBlackVolTermStructure* DLLEXPORT qlBlackConstantVol1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e);
  QlBlackVolTermStructure* DLLEXPORT qlBlackConstantVol(int referenceDate, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e);
  QlOptionletVolatilityStructure* DLLEXPORT qlConstantOptionletVolatility(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e);
  QlSwaptionVolatilityStructure* DLLEXPORT qlConstantSwaptionVolatility1(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e);
  QlSwaptionVolatilityStructure* DLLEXPORT qlConstantSwaptionVolatility(unsigned settlementDays, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureBlackVariance1(QlSwaptionVolatilityStructure* o, int optionDate, Period* swapTenor, double strike, int extrapolate, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureBlackVariance2(QlSwaptionVolatilityStructure* o, double optionTime, Period* swapTenor, double strike, int extrapolate, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureBlackVariance3(QlSwaptionVolatilityStructure* o, Period* optionTenor, double swapLength, double strike, int extrapolate, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureBlackVariance4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, double strike, int extrapolate, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureBlackVariance5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, double strike, int extrapolate, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureBlackVariance(QlSwaptionVolatilityStructure* o, Period* optionTenor, Period* swapTenor, double strike, int extrapolate, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureMaxSwapLength(QlSwaptionVolatilityStructure* o, char **e);
  Period* DLLEXPORT qlSwaptionVolatilityStructureMaxSwapTenor(QlSwaptionVolatilityStructure* o, char **e);
  QlSmileSection* DLLEXPORT qlSwaptionVolatilityStructureSmileSection1(QlSwaptionVolatilityStructure* o, int optionDate, Period* swapTenor, int extr, char **e);
  QlSmileSection* DLLEXPORT qlSwaptionVolatilityStructureSmileSection2(QlSwaptionVolatilityStructure* o, double optionTime, Period* swapTenor, int extr, char **e);
  QlSmileSection* DLLEXPORT qlSwaptionVolatilityStructureSmileSection3(QlSwaptionVolatilityStructure* o, Period* optionTenor, double swapLength, int extr, char **e);
  QlSmileSection* DLLEXPORT qlSwaptionVolatilityStructureSmileSection4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, int extr, char **e);
  QlSmileSection* DLLEXPORT qlSwaptionVolatilityStructureSmileSection5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, int extr, char **e);
  QlSmileSection* DLLEXPORT qlSwaptionVolatilityStructureSmileSection(QlSwaptionVolatilityStructure* o, Period* optionTenor, Period* swapTenor, int extr, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureSwapLength1(QlSwaptionVolatilityStructure* o, int start, int end, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureSwapLength(QlSwaptionVolatilityStructure* o, Period* swapTenor, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureVolatility1(QlSwaptionVolatilityStructure* o, int optionDate, Period* swapTenor, double strike, int extrapolate, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureVolatility2(QlSwaptionVolatilityStructure* o, double optionTime, Period* swapTenor, double strike, int extrapolate, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureVolatility3(QlSwaptionVolatilityStructure* o, Period* optionTenor, double swapLength, double strike, int extrapolate, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureVolatility4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, double strike, int extrapolate, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureVolatility5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, double strike, int extrapolate, char **e);
  double DLLEXPORT qlSwaptionVolatilityStructureVolatility(QlSwaptionVolatilityStructure* o, Period* optionTenor, Period* swapTenor, double strike, int extrapolate, char **e);
  QlVolatilityTermStructure* DLLEXPORT qlCapFloorTermVolCurve1(int settlementDate, Calendar* calendar, int bdc, unsigned optionTenorsLen, Period** optionTenors, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e);
  QlVolatilityTermStructure* DLLEXPORT qlCapFloorTermVolCurve(unsigned settlementDays, Calendar* calendar, int bdc, unsigned optionTenorsLen, Period** optionTenors, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e);
  QlVolatilityTermStructure* DLLEXPORT qlConstantCapFloorTermVolatility1(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e);
  QlVolatilityTermStructure* DLLEXPORT qlConstantCapFloorTermVolatility(unsigned settlementDays, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e);
  QlSwaptionVolatilityStructure* DLLEXPORT qlSpreadedSwaptionVolatility(QlSwaptionVolatilityStructure* x0, QlQuote* spread, char **e);

  void DLLEXPORT qlFreeCapFloorTermVolSurface(QlCapFloorTermVolSurface *o);
  QlVolatilityTermStructure* DLLEXPORT qlCapFloorTermVolSurfaceAsVolatilityTermStructure(QlCapFloorTermVolSurface *o);
  void DLLEXPORT qlFreeLocalVolTermStructure(QlLocalVolTermStructure *o);
  QlVolatilityTermStructure* DLLEXPORT qlLocalVolTermStructureAsVolatilityTermStructure(QlLocalVolTermStructure *o);
  QlLocalVolTermStructure* DLLEXPORT qlLocalConstantVol1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e);
  QlLocalVolTermStructure* DLLEXPORT qlLocalConstantVol(int referenceDate, QlQuote* volatility, DayCounter* dayCounter, char **e);
  QlLocalVolTermStructure* DLLEXPORT qlLocalVolCurve(QlBlackVarianceCurve* curve, char **e);
  QlLocalVolTermStructure* DLLEXPORT qlLocalVolSurface(QlBlackVolTermStructure* blackTS, QlYieldTermStructure* riskFreeTS, QlYieldTermStructure* dividendTS, QlQuote* underlying, char **e);
  void DLLEXPORT qlFreeBlackVarianceCurve(QlBlackVarianceCurve *o);
  QlBlackVolTermStructure* DLLEXPORT qlBlackVarianceCurveAsBlackVolTermStructure(QlBlackVarianceCurve *o);
  QlBlackVolTermStructure* DLLEXPORT qlImpliedVolTermStructure(QlBlackVolTermStructure* origTS, int referenceDate, char **e);
  QlBlackVarianceCurve* DLLEXPORT qlBlackVarianceCurve(int referenceDate, unsigned datesLen, int* dates, unsigned blackVolCurveLen, double* blackVolCurve, DayCounter* dayCounter, int forceMonotoneVariance, char *interpolation, char **e);
  QlBlackVolTermStructure* DLLEXPORT qlBlackVarianceSurface(int referenceDate, Calendar* cal, unsigned datesLen, int* dates, unsigned strikesLen, double* strikes, unsigned blackVolMatrixRows, unsigned blackVolMatrixCols, double* blackVolMatrix, DayCounter* dayCounter, int lowerExtrapolation, int upperExtrapolation/*, char *interpolation*/, char **e);
  QlCapFloorTermVolSurface* DLLEXPORT qlCapFloorTermVolSurface(unsigned settlementDays, Calendar* calendar, int bdc, unsigned optionTenorsLen, Period** optionTenors, unsigned strikesLen, double* strikes, unsigned volatilitiesRows, unsigned volatilitiesCols, QlQuote** volatilities, DayCounter* dc, char **e);
  QlCapFloorTermVolSurface* DLLEXPORT qlCapFloorTermVolSurface1(int settlementDate, Calendar* calendar, int bdc, unsigned optionTenorsLen, Period** optionTenors, unsigned strikesLen, double* strikes, unsigned volatilitiesRows, unsigned volatilitiesCols, QlQuote** volatilities, DayCounter* dc, char **e);

  void DLLEXPORT qlFreeCallableBondVolatilityStructure(QlCallableBondVolatilityStructure *o);
  QlTermStructure* DLLEXPORT qlCallableBondVolatilityStructureAsTermStructure(QlCallableBondVolatilityStructure *o);
  QlCallableBondVolatilityStructure* DLLEXPORT qlCallableBondConstantVolatility1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e);
  QlCallableBondVolatilityStructure* DLLEXPORT qlCallableBondConstantVolatility(int referenceDate, QlQuote* volatility, DayCounter* dayCounter, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
