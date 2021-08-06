#ifdef __cplusplus
extern "C" {
#endif
//  QlOptionletVolatilityStructure *qlConstantOptionletVol1(unsigned days, Calendar *cal, int conv, QlQuote *q, DayCounter *dc, char **e);
//  void qlFreeOptionletVolatilityStructure(QlOptionletVolatilityStructure *p);
//  QlVolatilityTermStructure* qlOptionletVolatilityStructureAsVolatilityTermStructure(QlOptionletVolatilityStructure *o);
//  void qlFreeVolatilityTermStructure(QlVolatilityTermStructure *o);
//  QlTermStructure* qlVolatilityTermStructureAsTermStructure(QlVolatilityTermStructure *o);
//  void qlFreeBlackVolTermStructure(QlBlackVolTermStructure *o);
//  QlVolatilityTermStructure* qlBlackVolTermStructureAsVolatilityTermStructure(QlBlackVolTermStructure *o);
//  void qlFreeSwaptionVolatilityStructure(QlSwaptionVolatilityStructure *o);
//  QlVolatilityTermStructure* qlSwaptionVolatilityStructureAsVolatilityTermStructure(QlSwaptionVolatilityStructure *o);
//  void qlFreeSmileSection(QlSmileSection *o);
//  QlBlackVolTermStructure* qlBlackConstantVol1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e);
//  QlBlackVolTermStructure* qlBlackConstantVol(int referenceDate, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e);
//  QlOptionletVolatilityStructure* qlConstantOptionletVolatility(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e);
//  QlSwaptionVolatilityStructure* qlConstantSwaptionVolatility1(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e);
//  QlSwaptionVolatilityStructure* qlConstantSwaptionVolatility(unsigned settlementDays, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e);
//  double qlSwaptionVolatilityStructureBlackVariance1(QlSwaptionVolatilityStructure* o, int optionDate, int, int, double strike, int extrapolate, char **e);
//  double qlSwaptionVolatilityStructureBlackVariance2(QlSwaptionVolatilityStructure* o, double optionTime, int, int, double strike, int extrapolate, char **e);
//  double qlSwaptionVolatilityStructureBlackVariance3(QlSwaptionVolatilityStructure* o, int, int, double swapLength, double strike, int extrapolate, char **e);
//  double qlSwaptionVolatilityStructureBlackVariance4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, double strike, int extrapolate, char **e);
//  double qlSwaptionVolatilityStructureBlackVariance5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, double strike, int extrapolate, char **e);
//  double qlSwaptionVolatilityStructureBlackVariance(QlSwaptionVolatilityStructure* o, int, int, int, int, double strike, int extrapolate, char **e);
//  double qlSwaptionVolatilityStructureMaxSwapLength(QlSwaptionVolatilityStructure* o, char **e);
//  int qlSwaptionVolatilityStructureMaxSwapTenor(QlSwaptionVolatilityStructure* o, int *, char **e);
//  QlSmileSection* qlSwaptionVolatilityStructureSmileSection1(QlSwaptionVolatilityStructure* o, int optionDate, int, int, int extr, char **e);
//  QlSmileSection* qlSwaptionVolatilityStructureSmileSection2(QlSwaptionVolatilityStructure* o, double optionTime, int, int, int extr, char **e);
//  QlSmileSection* qlSwaptionVolatilityStructureSmileSection3(QlSwaptionVolatilityStructure* o, int, int, double swapLength, int extr, char **e);
//  QlSmileSection* qlSwaptionVolatilityStructureSmileSection4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, int extr, char **e);
//  QlSmileSection* qlSwaptionVolatilityStructureSmileSection5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, int extr, char **e);
//  QlSmileSection* qlSwaptionVolatilityStructureSmileSection(QlSwaptionVolatilityStructure* o, int, int, int, int, int extr, char **e);
//  double qlSwaptionVolatilityStructureSwapLength1(QlSwaptionVolatilityStructure* o, int start, int end, char **e);
//  double qlSwaptionVolatilityStructureSwapLength(QlSwaptionVolatilityStructure* o, int, int, char **e);
//  double qlSwaptionVolatilityStructureVolatility1(QlSwaptionVolatilityStructure* o, int optionDate, int, int, double strike, int extrapolate, char **e);
//  double qlSwaptionVolatilityStructureVolatility2(QlSwaptionVolatilityStructure* o, double optionTime, int, int, double strike, int extrapolate, char **e);
//  double qlSwaptionVolatilityStructureVolatility3(QlSwaptionVolatilityStructure* o, int, int, double swapLength, double strike, int extrapolate, char **e);
//  double qlSwaptionVolatilityStructureVolatility4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, double strike, int extrapolate, char **e);
//  double qlSwaptionVolatilityStructureVolatility5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, double strike, int extrapolate, char **e);
//  double qlSwaptionVolatilityStructureVolatility(QlSwaptionVolatilityStructure* o, int, int, int, int, double strike, int extrapolate, char **e);
//  QlVolatilityTermStructure* qlCapFloorTermVolCurve1(int settlementDate, Calendar* calendar, int bdc, unsigned, int*, int*, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e);
//  QlVolatilityTermStructure* qlCapFloorTermVolCurve(unsigned settlementDays, Calendar* calendar, int bdc, unsigned, int*, int*, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e);
//  QlVolatilityTermStructure* qlConstantCapFloorTermVolatility1(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e);
//  QlVolatilityTermStructure* qlConstantCapFloorTermVolatility(unsigned settlementDays, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e);
//  QlSwaptionVolatilityStructure* qlSpreadedSwaptionVolatility(QlSwaptionVolatilityStructure* x0, QlQuote* spread, char **e);
//
//  void qlFreeCapFloorTermVolSurface(QlCapFloorTermVolSurface *o);
//  QlVolatilityTermStructure* qlCapFloorTermVolSurfaceAsVolatilityTermStructure(QlCapFloorTermVolSurface *o);
//  void qlFreeLocalVolTermStructure(QlLocalVolTermStructure *o);
//  QlVolatilityTermStructure* qlLocalVolTermStructureAsVolatilityTermStructure(QlLocalVolTermStructure *o);
//  QlLocalVolTermStructure* qlLocalConstantVol1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e);
//  QlLocalVolTermStructure* qlLocalConstantVol(int referenceDate, QlQuote* volatility, DayCounter* dayCounter, char **e);
//  QlLocalVolTermStructure* qlLocalVolCurve(QlBlackVarianceCurve* curve, char **e);
//  QlLocalVolTermStructure* qlLocalVolSurface(QlBlackVolTermStructure* blackTS, QlYieldTermStructure* riskFreeTS, QlYieldTermStructure* dividendTS, QlQuote* underlying, char **e);
//  void qlFreeBlackVarianceCurve(QlBlackVarianceCurve *o);
//  QlBlackVolTermStructure* qlBlackVarianceCurveAsBlackVolTermStructure(QlBlackVarianceCurve *o);
//  QlBlackVolTermStructure* qlImpliedVolTermStructure(QlBlackVolTermStructure* origTS, int referenceDate, char **e);
//  QlBlackVarianceCurve* qlBlackVarianceCurve(int referenceDate, unsigned datesLen, int* dates, unsigned blackVolCurveLen, double* blackVolCurve, DayCounter* dayCounter, int forceMonotoneVariance, char *interpolation, char **e);
//  QlBlackVolTermStructure* qlBlackVarianceSurface(int referenceDate, Calendar* cal, unsigned datesLen, int* dates, unsigned strikesLen, double* strikes, unsigned blackVolMatrixRows, unsigned blackVolMatrixCols, double* blackVolMatrix, DayCounter* dayCounter, int lowerExtrapolation, int upperExtrapolation/*, char *interpolation*/, char **e);
//  QlCapFloorTermVolSurface* qlCapFloorTermVolSurface(unsigned settlementDays, Calendar* calendar, int bdc, unsigned, int*, int*, unsigned strikesLen, double* strikes, unsigned volatilitiesRows, unsigned volatilitiesCols, QlQuote** volatilities, DayCounter* dc, char **e);
//  QlCapFloorTermVolSurface* qlCapFloorTermVolSurface1(int settlementDate, Calendar* calendar, int bdc, unsigned, int*, int*, unsigned strikesLen, double* strikes, unsigned volatilitiesRows, unsigned volatilitiesCols, QlQuote** volatilities, DayCounter* dc, char **e);
//
//  void qlFreeCallableBondVolatilityStructure(QlCallableBondVolatilityStructure *o);
//  QlTermStructure* qlCallableBondVolatilityStructureAsTermStructure(QlCallableBondVolatilityStructure *o);
//  QlCallableBondVolatilityStructure* qlCallableBondConstantVolatility1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e);
//  QlCallableBondVolatilityStructure* qlCallableBondConstantVolatility(int referenceDate, QlQuote* volatility, DayCounter* dayCounter, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
