#ifdef __cplusplus
extern "C" {
#endif
  QlOptionletVolatilityStructure *qlConstantOptionletVol1(unsigned days, Calendar *cal, int conv, QlQuote *q, DayCounter *dc, int type, double displacement, char **e);
  QlOptionletVolatilityStructure *qlCapletVarianceCurve(int referenceDate, unsigned datesLen, int* dates, unsigned volsLen, double* vols, DayCounter* dc, int type, double displacement, char **e);
  void qlFreeOptionletVolatilityStructure(QlOptionletVolatilityStructure *p);
  QlVolatilityTermStructure* qlOptionletVolatilityStructureAsVolatilityTermStructure(QlOptionletVolatilityStructure *o);
  QlRelinkableOptionletVolatilityStructure* qlRelinkableOptionletVolatilityStructure(QlOptionletVolatilityStructure *initial, char **e);
  void qlFreeRelinkableOptionletVolatilityStructure(QlRelinkableOptionletVolatilityStructure *o);
  void qlRelinkableOptionletVolatilityStructureLinkTo(QlRelinkableOptionletVolatilityStructure *o, QlOptionletVolatilityStructure *c, char **e);
  QlOptionletVolatilityStructure* qlRelinkableOptionletVolatilityStructureAsOptionletVolatilityStructure(QlRelinkableOptionletVolatilityStructure *o);
  QlOptionletVolatilityStructure* qlOptionletStripper1(QlCapFloorTermVolSurface* surface, QlIborIndex* index, double switchStrikes, double accuracy, unsigned maxIter, QlYieldTermStructure* discount, int type, double displacement, int dontThrow, int optionletFrequencyLen, int optionletFrequencyUnit, char **e);
  void qlFreeVolatilityTermStructure(QlVolatilityTermStructure *o);
  QlTermStructure* qlVolatilityTermStructureAsTermStructure(QlVolatilityTermStructure *o);
  void qlFreeBlackAtmVolCurve(QlBlackAtmVolCurve *o);
  QlVolatilityTermStructure* qlBlackAtmVolCurveAsVolatilityTermStructure(QlBlackAtmVolCurve *o);
  void qlFreeBlackVolSurface(QlBlackVolSurface *o);
  QlBlackAtmVolCurve* qlBlackVolSurfaceAsBlackAtmVolCurve(QlBlackVolSurface *o);
  void qlFreeAbcdAtmVolCurve(QlAbcdAtmVolCurve *o);
  QlBlackAtmVolCurve* qlAbcdAtmVolCurveAsBlackAtmVolCurve(QlAbcdAtmVolCurve *o);
  void qlFreeSabrVolSurface(QlSabrVolSurface *o);
  QlBlackVolSurface* qlSabrVolSurfaceAsBlackVolSurface(QlSabrVolSurface *o);
  double qlBlackAtmVolCurveAtmVolForPeriod(QlBlackAtmVolCurve* o, int n, int u, int extrapolate, char **e);
  double qlBlackAtmVolCurveAtmVolForDate(QlBlackAtmVolCurve* o, int date, int extrapolate, char **e);
  double qlBlackAtmVolCurveAtmVolForTime(QlBlackAtmVolCurve* o, double t, int extrapolate, char **e);
  double qlBlackAtmVolCurveAtmVarianceForPeriod(QlBlackAtmVolCurve* o, int n, int u, int extrapolate, char **e);
  double qlBlackAtmVolCurveAtmVarianceForDate(QlBlackAtmVolCurve* o, int date, int extrapolate, char **e);
  double qlBlackAtmVolCurveAtmVarianceForTime(QlBlackAtmVolCurve* o, double t, int extrapolate, char **e);
  QlSmileSection* qlBlackVolSurfaceSmileSectionForPeriod(QlBlackVolSurface* o, int n, int u, int extrapolate, char **e);
  QlSmileSection* qlBlackVolSurfaceSmileSectionForDate(QlBlackVolSurface* o, int date, int extrapolate, char **e);
  QlSmileSection* qlBlackVolSurfaceSmileSectionForTime(QlBlackVolSurface* o, double t, int extrapolate, char **e);
  QlAbcdAtmVolCurve* qlAbcdAtmVolCurve(unsigned settlementDays, Calendar* calendar, unsigned, int *n, unsigned, int *u, unsigned volsLen, QlQuote** vols, unsigned flagsLen, int *flags, int bdc, DayCounter* dc, char **e);
  double qlAbcdAtmVolCurveA(QlAbcdAtmVolCurve* o, char **e);
  double qlAbcdAtmVolCurveB(QlAbcdAtmVolCurve* o, char **e);
  double qlAbcdAtmVolCurveC(QlAbcdAtmVolCurve* o, char **e);
  double qlAbcdAtmVolCurveD(QlAbcdAtmVolCurve* o, char **e);
  double qlAbcdAtmVolCurveRmsError(QlAbcdAtmVolCurve* o, char **e);
  double qlAbcdAtmVolCurveMaxError(QlAbcdAtmVolCurve* o, char **e);
  int qlAbcdAtmVolCurveEndCriteria(QlAbcdAtmVolCurve* o, char **e);
  double qlAbcdAtmVolCurveKAtTime(QlAbcdAtmVolCurve* o, double t, char **e);
  void qlAbcdAtmVolCurveK(QlAbcdAtmVolCurve* o, unsigned *count, double **ks, char **e);
  void qlAbcdAtmVolCurveOptionTenors(QlAbcdAtmVolCurve* o, unsigned *count, int **n, unsigned *count2, int **u, char **e);
  void qlAbcdAtmVolCurveOptionTenorsInInterpolation(QlAbcdAtmVolCurve* o, unsigned *count, int **n, unsigned *count2, int **u, char **e);
  void qlAbcdAtmVolCurveOptionDates(QlAbcdAtmVolCurve* o, unsigned *count, int **days, char **e);
  void qlAbcdAtmVolCurveOptionTimes(QlAbcdAtmVolCurve* o, unsigned *count, double **times, char **e);
  QlSabrVolSurface* qlSabrVolSurface(QlInterestRateIndex* index, QlBlackAtmVolCurve* atmCurve, unsigned tenorsLen, int *n, unsigned, int *u, unsigned spreadsLen, double *atmRateSpreads, unsigned volRows, unsigned volCols, QlQuote** volSpreads, char **e);
  QlBlackAtmVolCurve* qlSabrVolSurfaceAtmCurve(QlSabrVolSurface* o, char **e);
  void qlSabrVolSurfaceVolatilitySpreadsForPeriod(QlSabrVolSurface* o, int n, int u, unsigned *count, double **vols, char **e);
  void qlSabrVolSurfaceVolatilitySpreadsForDate(QlSabrVolSurface* o, int date, unsigned *count, double **vols, char **e);
  QlInterestRateIndex* qlSabrVolSurfaceIndex(QlSabrVolSurface* o, char **e);
  int qlSabrVolSurfaceOptionDateFromTenor(QlSabrVolSurface* o, int n, int u, char **e);
  QlOptionletStripper2* qlOptionletStripper2(QlCapFloorTermVolSurface* surface, QlIborIndex* index, double switchStrikes, double accuracy, unsigned maxIter, QlYieldTermStructure* discount, int type, double displacement, int dontThrow, int optionletFrequencyLen, int optionletFrequencyUnit, QlCapFloorTermVolCurve* atmCurve, char **e);
  void qlFreeOptionletStripper2(QlOptionletStripper2 *o);
  QlOptionletVolatilityStructure* qlOptionletStripper2AsOptionletVolatilityStructure(QlOptionletStripper2 *o, char **e);
  void qlOptionletStripper2AtmCapFloorStrikes(QlOptionletStripper2* o, unsigned *count, double **vs, char **e);
  void qlOptionletStripper2AtmCapFloorPrices(QlOptionletStripper2* o, unsigned *count, double **vs, char **e);
  void qlOptionletStripper2SpreadsVol(QlOptionletStripper2* o, unsigned *count, double **vs, char **e);
  void qlFreeBlackVolTermStructure(QlBlackVolTermStructure *o);
  QlVolatilityTermStructure* qlBlackVolTermStructureAsVolatilityTermStructure(QlBlackVolTermStructure *o);
  QlRelinkableBlackVolTermStructure* qlRelinkableBlackVolTermStructure(QlBlackVolTermStructure *initial, char **e);
  void qlFreeRelinkableBlackVolTermStructure(QlRelinkableBlackVolTermStructure *o);
  void qlRelinkableBlackVolTermStructureLinkTo(QlRelinkableBlackVolTermStructure *o, QlBlackVolTermStructure *c, char **e);
  QlBlackVolTermStructure* qlRelinkableBlackVolTermStructureAsBlackVolTermStructure(QlRelinkableBlackVolTermStructure *o);
  void qlFreeSwaptionVolatilityStructure(QlSwaptionVolatilityStructure *o);
  QlVolatilityTermStructure* qlSwaptionVolatilityStructureAsVolatilityTermStructure(QlSwaptionVolatilityStructure *o);
  QlRelinkableSwaptionVolatilityStructure* qlRelinkableSwaptionVolatilityStructure(QlSwaptionVolatilityStructure *initial, char **e);
  void qlFreeRelinkableSwaptionVolatilityStructure(QlRelinkableSwaptionVolatilityStructure *o);
  void qlRelinkableSwaptionVolatilityStructureLinkTo(QlRelinkableSwaptionVolatilityStructure *o, QlSwaptionVolatilityStructure *c, char **e);
  QlSwaptionVolatilityStructure* qlRelinkableSwaptionVolatilityStructureAsSwaptionVolatilityStructure(QlRelinkableSwaptionVolatilityStructure *o);
  void qlFreeSmileSection(QlSmileSection *o);
  QlBlackVolTermStructure* qlBlackConstantVol1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e);
  QlBlackVolTermStructure* qlBlackConstantVol(int referenceDate, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e);
  QlOptionletVolatilityStructure* qlConstantOptionletVolatility(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, int type, double displacement, char **e);
  QlSwaptionVolatilityStructure* qlConstantSwaptionVolatility1(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, int type, double shift, char **e);
  QlSwaptionVolatilityStructure* qlConstantSwaptionVolatility(unsigned settlementDays, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, int type, double shift, char **e);
  double qlSwaptionVolatilityStructureBlackVariance1(QlSwaptionVolatilityStructure* o, int optionDate, int, int, double strike, int extrapolate, char **e);
  double qlSwaptionVolatilityStructureBlackVariance2(QlSwaptionVolatilityStructure* o, double optionTime, int, int, double strike, int extrapolate, char **e);
  double qlSwaptionVolatilityStructureBlackVariance3(QlSwaptionVolatilityStructure* o, int, int, double swapLength, double strike, int extrapolate, char **e);
  double qlSwaptionVolatilityStructureBlackVariance4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, double strike, int extrapolate, char **e);
  double qlSwaptionVolatilityStructureBlackVariance5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, double strike, int extrapolate, char **e);
  double qlSwaptionVolatilityStructureBlackVariance(QlSwaptionVolatilityStructure* o, int, int, int, int, double strike, int extrapolate, char **e);
  double qlSwaptionVolatilityStructureMaxSwapLength(QlSwaptionVolatilityStructure* o, char **e);
  int qlSwaptionVolatilityStructureMaxSwapTenor(QlSwaptionVolatilityStructure* o, int *, char **e);
  QlSmileSection* qlSwaptionVolatilityStructureSmileSection1(QlSwaptionVolatilityStructure* o, int optionDate, int, int, int extr, char **e);
  QlSmileSection* qlSwaptionVolatilityStructureSmileSection2(QlSwaptionVolatilityStructure* o, double optionTime, int, int, int extr, char **e);
  QlSmileSection* qlSwaptionVolatilityStructureSmileSection3(QlSwaptionVolatilityStructure* o, int, int, double swapLength, int extr, char **e);
  QlSmileSection* qlSwaptionVolatilityStructureSmileSection4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, int extr, char **e);
  QlSmileSection* qlSwaptionVolatilityStructureSmileSection5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, int extr, char **e);
  QlSmileSection* qlSwaptionVolatilityStructureSmileSection(QlSwaptionVolatilityStructure* o, int, int, int, int, int extr, char **e);
  QlSmileSection* qlSabrSmileSection(double timeToExpiry, double forward, double alpha, double beta, double nu, double rho, double shift, int volatilityType, char **e);
  QlSmileSection* qlSabrSmileSection1(int optionDate, double forward, double alpha, double beta, double nu, double rho, int referenceDate, DayCounter* dc, double shift, int volatilityType, char **e);
  QlSmileSection* qlNoArbSabrSmileSection(double timeToExpiry, double forward, double alpha, double beta, double nu, double rho, double shift, int volatilityType, char **e);
  QlSmileSection* qlNoArbSabrSmileSection1(int optionDate, double forward, double alpha, double beta, double nu, double rho, DayCounter* dc, double shift, int volatilityType, char **e);
  double qlSmileSectionVolatility(QlSmileSection* o, double strike, char **e);
  double qlSmileSectionVariance(QlSmileSection* o, double strike, char **e);
  double qlSmileSectionAtmLevel(QlSmileSection* o, char **e);
  double qlSmileSectionOptionPrice(QlSmileSection* o, double strike, int type, double discount, char **e);
  double qlSmileSectionDigitalOptionPrice(QlSmileSection* o, double strike, int type, double discount, double gap, char **e);
  double qlSmileSectionDensity(QlSmileSection* o, double strike, double discount, double gap, char **e);
  QlSmileSection* qlFlatSmileSection(int d, double vol, DayCounter* dc, int referenceDate, double atmLevel, int type, double shift, char **e);
  QlSmileSection* qlSviSmileSection(int d, double forward, double a, double b, double sigma, double rho, double m, DayCounter* dc, char **e);
  QlSmileSection* qlZabrSmileSection(int evaluation, double timeToExpiry, double forward, double alpha, double beta, double nu, double rho, double gamma, unsigned moneynessLen, double* moneyness, unsigned fdRefinement, char **e);
  QlSmileSection* qlZabrSmileSection1(int evaluation, int d, double forward, double alpha, double beta, double nu, double rho, double gamma, DayCounter* dc, unsigned moneynessLen, double* moneyness, unsigned fdRefinement, char **e);
  QlSmileSection* qlSpreadedSmileSection(QlSmileSection* source, QlQuote* spread, char **e);
  QlSmileSection* qlAtmSmileSection(QlSmileSection* source, double atm, char **e);
  QlSabrInterpolatedSmileSection* qlSabrInterpolatedSmileSection(int optionDate, QlQuote* forward, unsigned strikesLen, double* strikes, int hasFloatingStrikes, QlQuote* atmVolatility, unsigned volsLen, QlQuote** vols, double alpha, double beta, double nu, double rho, int isAlphaFixed, int isBetaFixed, int isNuFixed, int isRhoFixed, int vegaWeighted, QlEndCriteria* endCriteria, QlOptimizationMethod* method, DayCounter* dc, double shift, char **e);
  void qlFreeSabrInterpolatedSmileSection(QlSabrInterpolatedSmileSection* p);
  QlSmileSection* qlSabrInterpolatedSmileSectionAsSmileSection(QlSabrInterpolatedSmileSection* o, char **e);
  double qlSabrInterpolatedSmileSectionAlpha(QlSabrInterpolatedSmileSection* o, char **e);
  double qlSabrInterpolatedSmileSectionBeta(QlSabrInterpolatedSmileSection* o, char **e);
  double qlSabrInterpolatedSmileSectionNu(QlSabrInterpolatedSmileSection* o, char **e);
  double qlSabrInterpolatedSmileSectionRho(QlSabrInterpolatedSmileSection* o, char **e);
  double qlSabrInterpolatedSmileSectionRmsError(QlSabrInterpolatedSmileSection* o, char **e);
  double qlSabrInterpolatedSmileSectionMaxError(QlSabrInterpolatedSmileSection* o, char **e);
  int qlSabrInterpolatedSmileSectionEndCriteria(QlSabrInterpolatedSmileSection* o, char **e);
  QlSviInterpolatedSmileSection* qlSviInterpolatedSmileSection(int optionDate, QlQuote* forward, unsigned strikesLen, double* strikes, int hasFloatingStrikes, QlQuote* atmVolatility, unsigned volsLen, QlQuote** vols, double a, double b, double sigma, double rho, double m, int aIsFixed, int bIsFixed, int sigmaIsFixed, int rhoIsFixed, int mIsFixed, int vegaWeighted, QlEndCriteria* endCriteria, QlOptimizationMethod* method, DayCounter* dc, char **e);
  void qlFreeSviInterpolatedSmileSection(QlSviInterpolatedSmileSection* p);
  QlSmileSection* qlSviInterpolatedSmileSectionAsSmileSection(QlSviInterpolatedSmileSection* o, char **e);
  double qlSviInterpolatedSmileSectionA(QlSviInterpolatedSmileSection* o, char **e);
  double qlSviInterpolatedSmileSectionB(QlSviInterpolatedSmileSection* o, char **e);
  double qlSviInterpolatedSmileSectionSigma(QlSviInterpolatedSmileSection* o, char **e);
  double qlSviInterpolatedSmileSectionRho(QlSviInterpolatedSmileSection* o, char **e);
  double qlSviInterpolatedSmileSectionM(QlSviInterpolatedSmileSection* o, char **e);
  double qlSviInterpolatedSmileSectionRmsError(QlSviInterpolatedSmileSection* o, char **e);
  double qlSviInterpolatedSmileSectionMaxError(QlSviInterpolatedSmileSection* o, char **e);
  int qlSviInterpolatedSmileSectionEndCriteria(QlSviInterpolatedSmileSection* o, char **e);
  QlNoArbSabrInterpolatedSmileSection* qlNoArbSabrInterpolatedSmileSection(int optionDate, QlQuote* forward, unsigned strikesLen, double* strikes, int hasFloatingStrikes, QlQuote* atmVolatility, unsigned volsLen, QlQuote** vols, double alpha, double beta, double nu, double rho, int isAlphaFixed, int isBetaFixed, int isNuFixed, int isRhoFixed, int vegaWeighted, QlEndCriteria* endCriteria, QlOptimizationMethod* method, DayCounter* dc, char **e);
  void qlFreeNoArbSabrInterpolatedSmileSection(QlNoArbSabrInterpolatedSmileSection* p);
  QlSmileSection* qlNoArbSabrInterpolatedSmileSectionAsSmileSection(QlNoArbSabrInterpolatedSmileSection* o, char **e);
  double qlNoArbSabrInterpolatedSmileSectionAlpha(QlNoArbSabrInterpolatedSmileSection* o, char **e);
  double qlNoArbSabrInterpolatedSmileSectionBeta(QlNoArbSabrInterpolatedSmileSection* o, char **e);
  double qlNoArbSabrInterpolatedSmileSectionNu(QlNoArbSabrInterpolatedSmileSection* o, char **e);
  double qlNoArbSabrInterpolatedSmileSectionRho(QlNoArbSabrInterpolatedSmileSection* o, char **e);
  double qlNoArbSabrInterpolatedSmileSectionRmsError(QlNoArbSabrInterpolatedSmileSection* o, char **e);
  double qlNoArbSabrInterpolatedSmileSectionMaxError(QlNoArbSabrInterpolatedSmileSection* o, char **e);
  int qlNoArbSabrInterpolatedSmileSectionEndCriteria(QlNoArbSabrInterpolatedSmileSection* o, char **e);
  double qlSwaptionVolatilityStructureSwapLength1(QlSwaptionVolatilityStructure* o, int start, int end, char **e);
  double qlSwaptionVolatilityStructureSwapLength(QlSwaptionVolatilityStructure* o, int, int, char **e);
  double qlSwaptionVolatilityStructureVolatility1(QlSwaptionVolatilityStructure* o, int optionDate, int, int, double strike, int extrapolate, char **e);
  double qlSwaptionVolatilityStructureVolatility2(QlSwaptionVolatilityStructure* o, double optionTime, int, int, double strike, int extrapolate, char **e);
  double qlSwaptionVolatilityStructureVolatility3(QlSwaptionVolatilityStructure* o, int, int, double swapLength, double strike, int extrapolate, char **e);
  double qlSwaptionVolatilityStructureVolatility4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, double strike, int extrapolate, char **e);
  double qlSwaptionVolatilityStructureVolatility5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, double strike, int extrapolate, char **e);
  double qlSwaptionVolatilityStructureVolatility(QlSwaptionVolatilityStructure* o, int, int, int, int, double strike, int extrapolate, char **e);
  QlCapFloorTermVolCurve* qlCapFloorTermVolCurve1(int settlementDate, Calendar* calendar, int bdc, unsigned, int*, unsigned, int*, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e);
  QlCapFloorTermVolCurve* qlCapFloorTermVolCurve(unsigned settlementDays, Calendar* calendar, int bdc, unsigned, int*, unsigned, int*, unsigned volsLen, QlQuote** vols, DayCounter* dc, char **e);
  QlCapFloorTermVolatilityStructure* qlConstantCapFloorTermVolatility1(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e);
  QlCapFloorTermVolatilityStructure* qlConstantCapFloorTermVolatility(unsigned settlementDays, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e);
  QlSwaptionVolatilityStructure* qlSpreadedSwaptionVolatility(QlSwaptionVolatilityStructure* x0, QlQuote* spread, char **e);
  QlOptionletVolatilityStructure* qlSpreadedOptionletVolatility(QlOptionletVolatilityStructure* x0, QlQuote* spread, char **e);

  void qlFreeCapFloorTermVolatilityStructure(QlCapFloorTermVolatilityStructure *o);
  QlVolatilityTermStructure* qlCapFloorTermVolatilityStructureAsVolatilityTermStructure(QlCapFloorTermVolatilityStructure *o);
  double qlCapFloorTermVolatilityStructureVolatilityForPeriod(QlCapFloorTermVolatilityStructure* o, int n, int u, double strike, int extrapolate, char **e);
  double qlCapFloorTermVolatilityStructureVolatilityForDate(QlCapFloorTermVolatilityStructure* o, int date, double strike, int extrapolate, char **e);
  double qlCapFloorTermVolatilityStructureVolatilityForTime(QlCapFloorTermVolatilityStructure* o, double t, double strike, int extrapolate, char **e);
  void qlFreeCapFloorTermVolCurve(QlCapFloorTermVolCurve *o);
  QlCapFloorTermVolatilityStructure* qlCapFloorTermVolCurveAsCapFloorTermVolatilityStructure(QlCapFloorTermVolCurve *o);
  void qlCapFloorTermVolCurveOptionDates(QlCapFloorTermVolCurve *o, unsigned *count, int **days, char **e);
  void qlCapFloorTermVolCurveOptionTimes(QlCapFloorTermVolCurve *o, unsigned *count, double **times, char **e);

  void qlFreeCapFloorTermVolSurface(QlCapFloorTermVolSurface *o);
  QlCapFloorTermVolatilityStructure* qlCapFloorTermVolSurfaceAsCapFloorTermVolatilityStructure(QlCapFloorTermVolSurface *o);
  void qlCapFloorTermVolSurfaceOptionDates(QlCapFloorTermVolSurface *o, unsigned *count, int **days, char **e);
  void qlCapFloorTermVolSurfaceOptionTimes(QlCapFloorTermVolSurface *o, unsigned *count, double **times, char **e);
  void qlFreeLocalVolTermStructure(QlLocalVolTermStructure *o);
  QlVolatilityTermStructure* qlLocalVolTermStructureAsVolatilityTermStructure(QlLocalVolTermStructure *o);
  void qlFreeGridModelLocalVolSurface(QlGridModelLocalVolSurface *o);
  QlLocalVolTermStructure* qlGridModelLocalVolSurfaceAsLocalVolTermStructure(QlGridModelLocalVolSurface *o);
  QlCalibratedModel* qlGridModelLocalVolSurfaceAsCalibratedModel(QlGridModelLocalVolSurface *o, char **e);
  QlGridModelLocalVolSurface* qlGridModelLocalVolSurface(int referenceDate, unsigned datesLen, int* dates, unsigned rows, unsigned* strikeLengths, double* strikes, DayCounter* dayCounter, int lowerExtrapolation, int upperExtrapolation, char **e);
  QlBlackVolTermStructure* qlHestonBlackVolSurface(QlHestonModel* model, int cpxLogFormula, unsigned integrationOrder, char **e);
  void qlFreeAndreasenHugeVolatilityInterpl(QlAndreasenHugeVolatilityInterpl *o);
  QlAndreasenHugeVolatilityInterpl* qlAndreasenHugeVolatilityInterpl(unsigned calibrationLen, QlVanillaOption** options, QlQuote** quotes, QlQuote* spot, QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, int interpolationType, int calibrationType, unsigned nGridPoints, double minStrike, double maxStrike, QlOptimizationMethod* optimizationMethod, QlEndCriteria* endCriteria, char **e);
  void qlAndreasenHugeVolatilityInterplCalibrationError(QlAndreasenHugeVolatilityInterpl* o, unsigned* count, double** values, char **e);
  double qlAndreasenHugeVolatilityInterplFwd(QlAndreasenHugeVolatilityInterpl* o, double t, char **e);
  double qlAndreasenHugeVolatilityInterplOptionPrice(QlAndreasenHugeVolatilityInterpl* o, double t, double strike, int optionType, char **e);
  double qlAndreasenHugeVolatilityInterplLocalVol(QlAndreasenHugeVolatilityInterpl* o, double t, double strike, char **e);
  QlBlackVolTermStructure* qlAndreasenHugeVolatilityAdapter(QlAndreasenHugeVolatilityInterpl* o, double eps, char **e);
  QlLocalVolTermStructure* qlAndreasenHugeLocalVolAdapter(QlAndreasenHugeVolatilityInterpl* o, char **e);
  double qlLocalVolTermStructureLocalVol(QlLocalVolTermStructure* o, int d, double underlyingLevel, int extrapolate, char **e);
  QlLocalVolTermStructure* qlLocalConstantVol1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e);
  QlLocalVolTermStructure* qlLocalConstantVol(int referenceDate, QlQuote* volatility, DayCounter* dayCounter, char **e);
  QlLocalVolTermStructure* qlLocalVolCurve(QlBlackVarianceCurve* curve, char **e);
  QlLocalVolTermStructure* qlLocalVolSurface(QlBlackVolTermStructure* blackTS, QlYieldTermStructure* riskFreeTS, QlYieldTermStructure* dividendTS, QlQuote* underlying, char **e);
  QlLocalVolTermStructure* qlNoExceptLocalVolSurface(QlBlackVolTermStructure* blackTS, QlYieldTermStructure* riskFreeTS, QlYieldTermStructure* dividendTS, QlQuote* underlying, double illegalLocalVolOverwrite, char **e);
  QlLocalVolTermStructure* qlFixedLocalVolSurface(int referenceDate, unsigned datesLen, int* dates, unsigned strikesLen, double* strikes, unsigned matrixRows, unsigned matrixCols, double* matrixData, DayCounter* dayCounter, int lowerExtrapolation, int upperExtrapolation, char **e);
  void qlFreeBlackVarianceCurve(QlBlackVarianceCurve *o);
  QlBlackVolTermStructure* qlBlackVarianceCurveAsBlackVolTermStructure(QlBlackVarianceCurve *o);
  QlBlackVolTermStructure* qlImpliedVolTermStructure(QlBlackVolTermStructure* origTS, int referenceDate, char **e);
  QlBlackVarianceCurve* qlBlackVarianceCurve(int referenceDate, unsigned datesLen, int* dates, unsigned blackVolCurveLen, double* blackVolCurve, DayCounter* dayCounter, int forceMonotoneVariance, int interpolator, int approximator, int approximatorArg, char **e);
  QlBlackVolTermStructure* qlBlackVarianceSurface(int referenceDate, Calendar* cal, unsigned datesLen, int* dates, unsigned strikesLen, double* strikes, unsigned blackVolMatrixRows, unsigned blackVolMatrixCols, double* blackVolMatrix, DayCounter* dayCounter, int lowerExtrapolation, int upperExtrapolation, int interpolator, char **e);
  QlBlackVolTermStructure* qlPiecewiseBlackVarianceSurface(int referenceDate, unsigned datesLen, int* dates, unsigned strikesLen, double* strikes, unsigned blackVolsRows, unsigned blackVolsCols, double* blackVols, DayCounter* dayCounter, char **e);
  void qlFreeBlackVolatilitySurfaceDelta(QlBlackVolatilitySurfaceDelta *o);
  QlBlackVolTermStructure* qlBlackVolatilitySurfaceDeltaAsBlackVolTermStructure(QlBlackVolatilitySurfaceDelta *o);
  QlBlackVolatilitySurfaceDelta* qlBlackVolatilitySurfaceDelta(int referenceDate, unsigned datesLen, int* dates,
    unsigned putDeltasLen, double* putDeltas, unsigned callDeltasLen, double* callDeltas,
    int hasAtm, unsigned blackVolMatrixRows, unsigned blackVolMatrixCols, double* blackVolMatrix,
    DayCounter* dayCounter, Calendar* cal, QlQuote* spot,
    QlYieldTermStructure* domesticTS, QlYieldTermStructure* foreignTS,
    int deltaType, int atmType, int atmDeltaType,
    int interpolationMethod, int flatStrikeExtrapolation, int timeExtrapolationType,
    int switchTenorLen, int switchTenorUnit,
    int longTermDeltaType, int longTermAtmType, int longTermAtmDeltaType,
    char **e);
  QlSmileSection* qlBlackVolatilitySurfaceDeltaSmile1(QlBlackVolatilitySurfaceDelta* o, double t, char **e);
  QlSmileSection* qlBlackVolatilitySurfaceDeltaSmile(QlBlackVolatilitySurfaceDelta* o, int d, char **e);
  QlCapFloorTermVolSurface* qlCapFloorTermVolSurface(unsigned settlementDays, Calendar* calendar, int bdc, unsigned, int*, unsigned, int*, unsigned strikesLen, double* strikes, unsigned volatilitiesRows, unsigned volatilitiesCols, QlQuote** volatilities, DayCounter* dc, char **e);
  QlCapFloorTermVolSurface* qlCapFloorTermVolSurface1(int settlementDate, Calendar* calendar, int bdc, unsigned, int*, unsigned, int*, unsigned strikesLen, double* strikes, unsigned volatilitiesRows, unsigned volatilitiesCols, QlQuote** volatilities, DayCounter* dc, char **e);
  QlSwaptionVolatilityStructure* qlSwaptionVolatilityMatrix(int referenceDate, Calendar* calendar, int bdc, unsigned, int*, unsigned, int*, unsigned, int*, unsigned, int*, unsigned volRows, unsigned volCols, QlQuote** vols, DayCounter* dc, int flatExtrapolation, int type, unsigned shiftRows, unsigned shiftCols, double* shifts, char **e);
  QlSwaptionVolatilityStructure* qlSwaptionVolatilityMatrix1(Calendar* calendar, int bdc, unsigned, int*, unsigned, int*, unsigned, int*, unsigned, int*, unsigned volRows, unsigned volCols, QlQuote** vols, DayCounter* dc, int flatExtrapolation, int type, unsigned shiftRows, unsigned shiftCols, double* shifts, char **e);

  QlSabrSwaptionVolatilityCube* qlSabrSwaptionVolatilityCube(QlSwaptionVolatilityStructure* atmVolStructure,
      unsigned, int*, unsigned, int*, unsigned, int*, unsigned, int*,
      unsigned strikeSpreadsLen, double* strikeSpreads,
      unsigned volSpreadsRows, unsigned volSpreadsCols, QlQuote** volSpreads,
      QlSwapIndex* swapIndexBase, QlSwapIndex* shortSwapIndexBase,
      int vegaWeightedSmileFit,
      unsigned parametersGuessRows, unsigned parametersGuessCols, QlQuote** parametersGuess,
      int isAlphaFixed, int isBetaFixed, int isNuFixed, int isRhoFixed,
      int isAtmCalibrated,
      QlEndCriteria* endCriteria, QlOptimizationMethod* method,
      double maxErrorTolerance, double errorAccept, int useMaxError, unsigned maxGuesses,
      int backwardFlat, double cutoffStrike, char **e);
  void qlFreeSabrSwaptionVolatilityCube(QlSabrSwaptionVolatilityCube *o);
  QlSwaptionVolatilityStructure* qlSabrSwaptionVolatilityCubeAsSwaptionVolatilityStructure(QlSabrSwaptionVolatilityCube *o);
  QlNoArbSabrSwaptionVolatilityCube* qlNoArbSabrSwaptionVolatilityCube(QlSwaptionVolatilityStructure* atmVolStructure,
      unsigned, int*, unsigned, int*, unsigned, int*, unsigned, int*,
      unsigned strikeSpreadsLen, double* strikeSpreads,
      unsigned volSpreadsRows, unsigned volSpreadsCols, QlQuote** volSpreads,
      QlSwapIndex* swapIndexBase, QlSwapIndex* shortSwapIndexBase,
      int vegaWeightedSmileFit,
      unsigned parametersGuessRows, unsigned parametersGuessCols, QlQuote** parametersGuess,
      int isAlphaFixed, int isBetaFixed, int isNuFixed, int isRhoFixed,
      int isAtmCalibrated,
      QlEndCriteria* endCriteria, QlOptimizationMethod* method,
      double maxErrorTolerance, double errorAccept, int useMaxError, unsigned maxGuesses,
      int backwardFlat, double cutoffStrike, char **e);
  void qlFreeNoArbSabrSwaptionVolatilityCube(QlNoArbSabrSwaptionVolatilityCube *o);
  QlSwaptionVolatilityStructure* qlNoArbSabrSwaptionVolatilityCubeAsSwaptionVolatilityStructure(QlNoArbSabrSwaptionVolatilityCube *o);
  void qlNoArbSabrSwaptionVolatilityCubeSparseSabrParameters(QlNoArbSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e);
  void qlNoArbSabrSwaptionVolatilityCubeDenseSabrParameters(QlNoArbSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e);
  void qlNoArbSabrSwaptionVolatilityCubeMarketVolCube(QlNoArbSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e);
  void qlNoArbSabrSwaptionVolatilityCubeVolCubeAtmCalibrated(QlNoArbSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e);
  double qlNoArbSabrSwaptionVolatilityCubeAtmStrike1(QlNoArbSabrSwaptionVolatilityCube* o, int optionDate, int n, int u, char **e);
  double qlNoArbSabrSwaptionVolatilityCubeAtmStrike(QlNoArbSabrSwaptionVolatilityCube* o, int optionN, int optionU, int n, int u, char **e);
  QlInterpolatedSwaptionVolatilityCube* qlInterpolatedSwaptionVolatilityCube(QlSwaptionVolatilityStructure* atmVolStructure,
      unsigned, int*, unsigned, int*, unsigned, int*, unsigned, int*,
      unsigned strikeSpreadsLen, double* strikeSpreads,
      unsigned volSpreadsRows, unsigned volSpreadsCols, QlQuote** volSpreads,
      QlSwapIndex* swapIndexBase, QlSwapIndex* shortSwapIndexBase,
      int vegaWeightedSmileFit, char **e);
  void qlFreeInterpolatedSwaptionVolatilityCube(QlInterpolatedSwaptionVolatilityCube *o);
  QlSwaptionVolatilityStructure* qlInterpolatedSwaptionVolatilityCubeAsSwaptionVolatilityStructure(QlInterpolatedSwaptionVolatilityCube *o);
  void qlSabrSwaptionVolatilityCubeSparseSabrParameters(QlSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e);
  void qlSabrSwaptionVolatilityCubeDenseSabrParameters(QlSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e);
  void qlSabrSwaptionVolatilityCubeMarketVolCube(QlSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e);
  void qlSabrSwaptionVolatilityCubeVolCubeAtmCalibrated(QlSabrSwaptionVolatilityCube* o, unsigned* rows, unsigned* cols, unsigned* len, double** vs, char** e);
  double qlSabrSwaptionVolatilityCubeAtmStrike1(QlSabrSwaptionVolatilityCube* o, int optionDate, int n, int u, char **e);
  double qlSabrSwaptionVolatilityCubeAtmStrike(QlSabrSwaptionVolatilityCube* o, int optionN, int optionU, int n, int u, char **e);
  double qlInterpolatedSwaptionVolatilityCubeAtmStrike1(QlInterpolatedSwaptionVolatilityCube* o, int optionDate, int n, int u, char **e);
  double qlInterpolatedSwaptionVolatilityCubeAtmStrike(QlInterpolatedSwaptionVolatilityCube* o, int optionN, int optionU, int n, int u, char **e);

  void qlFreeCallableBondVolatilityStructure(QlCallableBondVolatilityStructure *o);
  QlTermStructure* qlCallableBondVolatilityStructureAsTermStructure(QlCallableBondVolatilityStructure *o);
  QlCallableBondVolatilityStructure* qlCallableBondConstantVolatility1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e);
  QlCallableBondVolatilityStructure* qlCallableBondConstantVolatility(int referenceDate, QlQuote* volatility, DayCounter* dayCounter, char **e);

  void qlFreeDefaultProbabilityTermStructure(QlDefaultProbabilityTermStructure *o);
  QlTermStructure* qlDefaultProbabilityTermStructureAsTermStructure(QlDefaultProbabilityTermStructure *o);
  QlDefaultProbabilityTermStructure* qlFactorSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e);
  QlDefaultProbabilityTermStructure* qlFlatHazardRate1(unsigned settlementDays, Calendar* calendar, QlQuote* hazardRate, DayCounter* x3, char **e);
  QlDefaultProbabilityTermStructure* qlFlatHazardRate(int referenceDate, QlQuote* hazardRate, DayCounter* x2, char **e);
  QlDefaultProbabilityTermStructure* qlSpreadedHazardRateCurve(QlDefaultProbabilityTermStructure* originalCurve, QlQuote* spread, char **e);
  QlDefaultProbabilityTermStructure* qlInterpolatedDefaultDensityCurve(unsigned datesLen, int* dates, unsigned densitiesLen, double* densities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int interpolator, int approximator, int approximatorArg, char **e);
  QlDefaultProbabilityTermStructure* qlInterpolatedHazardRateCurve(unsigned datesLen, int* dates, unsigned hazardRatesLen, double* hazardRates, DayCounter* dayCounter, Calendar* cal, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int interpolator, int approximator, int approximatorArg, int extrapolate, char **e);
  QlDefaultProbabilityTermStructure* qlInterpolatedSurvivalProbabilityCurve(unsigned datesLen, int* dates, unsigned probabilitiesLen, double* probabilities, DayCounter* dayCounter, Calendar* calendar, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int interpolator, int approximator, int approximatorArg, char **e);
  void qlFreeDefaultProbabilityHelper(QlDefaultProbabilityHelper *o);
  QlDefaultProbabilityHelper* qlSpreadCdsHelper(QlQuote* runningSpread, int, int, int settlementDays, Calendar* calendar, int frequency, int paymentConvention, int rule, DayCounter* dayCounter, double recoveryRate, QlYieldTermStructure* discountCurve, int settlesAccrual, int paysAtDefaultTime, int startDate, DayCounter* lastPeriodDayCounter, int rebatesAccrual, int model, char **e);
  QlDefaultProbabilityHelper* qlUpfrontCdsHelper(QlQuote* upfront, double runningSpread, int, int, int settlementDays, Calendar* calendar, int frequency, int paymentConvention, int rule, DayCounter* dayCounter, double recoveryRate, QlYieldTermStructure* discountCurve, unsigned upfrontSettlementDays, int settlesAccrual, int paysAtDefaultTime, int startDate, DayCounter* lastPeriodDayCounter, int rebatesAccrual, int model, char **e);
  QlDefaultProbabilityTermStructure* qlPiecewiseDefaultCurve(int referenceDate, unsigned instrumentsLen, QlDefaultProbabilityHelper** instruments, DayCounter* dayCounter, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int trait, int interpolator, int approximator, int approximatorArg, char **e);
  QlDefaultProbabilityTermStructure* qlPiecewiseDefaultCurve1(unsigned settlementDays, Calendar *calendar, unsigned instrumentsLen, QlDefaultProbabilityHelper** instruments, DayCounter* dayCounter, unsigned jumpsLen, QlQuote** jumps, unsigned jDatesLen, int* jumpDates, int trait, int interpolator, int approximator, int approximatorArg, char **e);

  double qlDefaultProbabilityTermStructureDefaultDensity1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureDefaultDensity(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureDefaultProbability1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureDefaultProbability2(QlDefaultProbabilityTermStructure* o, int x1, int x2, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureDefaultProbability3(QlDefaultProbabilityTermStructure* o, double x1, double x2, int extrapo, char **e);
  double qlDefaultProbabilityTermStructureDefaultProbability(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureHazardRate1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureHazardRate(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureSurvivalProbability1(QlDefaultProbabilityTermStructure* o, double t, int extrapolate, char **e);
  double qlDefaultProbabilityTermStructureSurvivalProbability(QlDefaultProbabilityTermStructure* o, int d, int extrapolate, char **e);

  void qlFreeZeroInflationTermStructure(QlZeroInflationTermStructure *o);
  QlTermStructure* qlZeroInflationTermStructureAsTermStructure(QlZeroInflationTermStructure *o);
  double qlZeroInflationTermStructureZeroRate(QlZeroInflationTermStructure* o, int d, int extrapolate, char **e);
  void qlFreeYoYInflationTermStructure(QlYoYInflationTermStructure *o);
  QlTermStructure* qlYoYInflationTermStructureAsTermStructure(QlYoYInflationTermStructure *o);
  double qlYoYInflationTermStructureYoYRate(QlYoYInflationTermStructure* o, int d, int extrapolate, char **e);

  /* CommodityCurve -- a plain TermStructure leaf, per qlaux.h's QlCommodityCurve comment. */
  QlCommodityCurve* qlCommodityCurve(char *name, CommodityType *commodityType, Currency *currency,
                                     UnitOfMeasure *unitOfMeasure, Calendar *calendar,
                                     unsigned datesLen, int *dates, unsigned pricesLen, double *prices,
                                     DayCounter *dayCounter, char **e);
  void qlFreeCommodityCurve(QlCommodityCurve *o);
  QlTermStructure* qlCommodityCurveAsTermStructure(QlCommodityCurve *o);
  char *qlCommodityCurveName(QlCommodityCurve *o);
  CommodityType *qlCommodityCurveCommodityType(QlCommodityCurve *o, char **e);
  UnitOfMeasure *qlCommodityCurveUnitOfMeasure(QlCommodityCurve *o, char **e);
  Currency *qlCommodityCurveCurrency(QlCommodityCurve *o, char **e);
  void qlCommodityCurveDates(QlCommodityCurve *o, unsigned *count, int **days, char **e);
  void qlCommodityCurvePrices(QlCommodityCurve *o, unsigned *count, double **prices, char **e);
  int qlCommodityCurveEmpty(QlCommodityCurve *o);
  QlCommodityCurve *qlCommodityCurveBasisOfCurve(QlCommodityCurve *o);
  void qlCommodityCurveSetBasisOfCurve(QlCommodityCurve *o, QlCommodityCurve *basisOfCurve, char **e);
  /* Full price()/underlyingPriceDate() signature, threading a real ExchangeContracts map (as 5
     parallel arrays -- map key, code, expirationDate, underlyingStartDate, underlyingEndDate --
     per the "c2hs's & caps at 2" precedent already used for Quantity's 3 flat args) and a
     nearbyOffset through to upstream. nearbyOffset<=0 with an empty map reproduces the old
     flat-price call exactly, since exchangeContracts is never touched on that branch. */
  double qlCommodityCurvePrice(QlCommodityCurve *o, int date,
      unsigned ecLen1, int *ecKeys, unsigned ecLen2, char **ecCodes,
      unsigned ecLen3, int *ecExpirations, unsigned ecLen4, int *ecStarts,
      unsigned ecLen5, int *ecEnds, int nearbyOffset, char **e);
  double qlCommodityCurveBasisOfPrice(QlCommodityCurve *o, int date, char **e);
  int qlCommodityCurveUnderlyingPriceDate(QlCommodityCurve *o, int date,
      unsigned ecLen1, int *ecKeys, unsigned ecLen2, char **ecCodes,
      unsigned ecLen3, int *ecExpirations, unsigned ecLen4, int *ecStarts,
      unsigned ecLen5, int *ecEnds, int nearbyOffset, char **e);

  /* CommodityIndex -- an Index leaf, per qlaux.h's QlCommodityIndex comment. The
     ExchangeContracts/nearbyOffset constructor args are not exposed (see Stage 3's
     CommodityCurve::price binding note): a null exchangeContracts + nearbyOffset 0 are passed
     to upstream, which is exactly the branch forwardPrice's own price() call never varies on
     exchangeContracts for. */
  QlCommodityIndex* qlCommodityIndex(char *name, CommodityType *commodityType, Currency *currency,
                                     UnitOfMeasure *unitOfMeasure, Calendar *calendar,
                                     double lotQuantity, QlCommodityCurve *forwardCurve, char **e);
  void qlFreeCommodityIndex(QlCommodityIndex *o);
  QlIndex* qlCommodityIndexAsIndex(QlCommodityIndex *o);
  double qlCommodityIndexForwardPrice(QlCommodityIndex *o, int date, char **e);
  int qlCommodityIndexLastQuoteDate(QlCommodityIndex *o, char **e);
  int qlCommodityIndexEmpty(QlCommodityIndex *o);

  void qlFreeZeroCouponInflationSwapHelper(QlZeroCouponInflationSwapHelper *o);
  QlZeroCouponInflationSwapHelper* qlZeroCouponInflationSwapHelper(QlQuote* quote, int, int, int maturity, Calendar* calendar, int paymentConvention, DayCounter* dayCounter, QlZeroInflationIndex* zii, int observationInterpolation, int pillar, int customPillarDate, char **e);
  void qlFreeYearOnYearInflationSwapHelper(QlYearOnYearInflationSwapHelper *o);
  QlYearOnYearInflationSwapHelper* qlYearOnYearInflationSwapHelper(QlQuote* quote, int, int, int maturity, Calendar* calendar, int paymentConvention, DayCounter* dayCounter, QlYoYInflationIndex* yii, int observationInterpolation, QlYieldTermStructure* nominalTermStructure, int pillar, int customPillarDate, char **e);
  QlZeroCouponInflationSwap* qlZeroCouponInflationSwapHelperSwap(QlZeroCouponInflationSwapHelper* o, char **e);
  QlYearOnYearInflationSwap* qlYearOnYearInflationSwapHelperSwap(QlYearOnYearInflationSwapHelper* o, char **e);

  QlZeroInflationTermStructure* qlPiecewiseZeroInflationCurve(int referenceDate, int baseDate, int frequency, DayCounter* dayCounter, unsigned instrumentsLen, QlZeroCouponInflationSwapHelper** instruments, int interpolator, int approximator, int approximatorArg, char **e);
  QlYoYInflationTermStructure* qlPiecewiseYoYInflationCurve(int referenceDate, int baseDate, double baseYoYRate, int frequency, DayCounter* dayCounter, unsigned instrumentsLen, QlYearOnYearInflationSwapHelper** instruments, int interpolator, int approximator, int approximatorArg, char **e);
  QlYoYInflationTermStructure* qlInterpolatedYoYInflationCurve(int referenceDate, unsigned datesLen, int *dates, double *rates, int frequency, DayCounter* dayCounter,
      int interpolator, int approximator, int approximatorArg, char **e);

  QlRateHelper *qlDepositRateHelper(QlQuote *quote, int, int, unsigned fixDays, Calendar *calendar, int conv, int eom, DayCounter *dayCount, char **e);
  QlBondHelper *qlFixedRateBondHelper(QlQuote *quote, unsigned settlDays, double face, Schedule *sched, unsigned cLen, double *coupons, DayCounter *dayCount, int conv, double redemption, int issue, char **e);
  QlBondHelper *qlCPIBondHelper(QlQuote *quote, unsigned settlementDays, double faceAmount, double baseCPI, int obsLagLen, int obsLagUnit, QlZeroInflationIndex* index, int observationInterpolation, Schedule *schedule, unsigned couponsLen, double *coupons, DayCounter *accrualDayCounter, int paymentConvention, int issueDate, Calendar *paymentCalendar, char **e);
  QlYieldTermStructure *qlPiecewiseYieldCurve(int date, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int trait, int interpolator, int approximator, int approximatorArg, char **e);
  QlYieldTermStructure *qlPiecewiseYieldCurve1(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int trait, int interpolator, int approximator, int approximatorArg, int extrapolate, char **e);
  // Full-arity counterparts of the two above, additionally taking every IterativeBootstrap
  // constructor parameter (ql/termstructures/iterativebootstrap.hpp). Separate entry points
  // rather than nine more params on the narrow ones, so the narrow Haskell bindings keep
  // their signatures -- see QuantLib/TermStructure/Yield.chs's IterativeBootstrapOpts.
  // accuracy/minValue/maxValue take qlNullReal() for "upstream's default".
  QlYieldTermStructure *qlPiecewiseYieldCurveFull(int date, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int trait, int interpolator, int approximator, int approximatorArg, double accuracy, double minValue, double maxValue, unsigned maxAttempts, double maxFactor, double minFactor, int dontThrow, unsigned dontThrowSteps, unsigned maxEvaluations, char **e);
  QlYieldTermStructure *qlPiecewiseYieldCurveFull1(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int trait, int interpolator, int approximator, int approximatorArg, double accuracy, double minValue, double maxValue, unsigned maxAttempts, double maxFactor, double minFactor, int dontThrow, unsigned dontThrowSteps, unsigned maxEvaluations, int extrapolate, char **e);
  // Dedicated GlobalBootstrap entry point, hardcoding trait=Discount/interpolator=LogLinear in
  // the shim itself (see qlTermStructureAux.cpp) rather than taking those as Haskell-visible
  // params -- CLAUDE.md's "dedicated constructor hardcodes the enum value" pattern.
  QlYieldTermStructure *qlPiecewiseYieldCurveGlobalBootstrap1(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, double accuracy, unsigned weightsLen, double *weights, int extrapolate, char **e);
  // Same shape as qlPiecewiseYieldCurveGlobalBootstrap1, hardcoding trait=SimpleZeroYield/
  // interpolator=Linear instead -- QuantLib-SWIG's only bound GlobalBootstrap combination
  // (GlobalLinearSimpleZeroCurve).
  QlYieldTermStructure *qlPiecewiseYieldCurveGlobalBootstrap2(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, double accuracy, unsigned weightsLen, double *weights, int extrapolate, char **e);
  // Same shape as qlPiecewiseYieldCurveGlobalBootstrap1/2, hardcoding trait=ForwardRate/
  // interpolator=Linear and trait=ZeroYield/interpolator=Linear respectively -- issue #15's two
  // next-cheapest, most generically useful GlobalBootstrap combinations.
  QlYieldTermStructure *qlPiecewiseYieldCurveGlobalBootstrap4(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, double accuracy, unsigned weightsLen, double *weights, int extrapolate, char **e);
  QlYieldTermStructure *qlPiecewiseYieldCurveGlobalBootstrap5(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, double accuracy, unsigned weightsLen, double *weights, int extrapolate, char **e);
  // trait=SimpleZeroYield/interpolator=Linear via GlobalBootstrap's functor-callback
  // constructor (canned AdditionalErrors/AdditionalDates -- see qlTermStructureAux.cpp).
  // additionalDatesLen must equal additionalRateLen - 2.
  QlYieldTermStructure *qlPiecewiseYieldCurveGlobalBootstrap3(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, unsigned additionalRateLen, QlRateHelper **additionalRatehelpers, unsigned additionalDatesLen, int *additionalDates, double accuracy, int extrapolate, char **e);
  // Dedicated LocalBootstrap entry point: interpolator is always ConvexMonotone (the only
  // upstream interpolator LocalBootstrap works with -- see qlTermStructureAux.cpp), so trait is
  // the only Haskell-visible dispatch axis here; localisation/forcePositive/accuracy are
  // LocalBootstrap's own constructor params, quadraticity/monotonicity/convexForcePositive are
  // ConvexMonotone's.
  QlYieldTermStructure *qlPiecewiseYieldCurveLocalBootstrap1(unsigned settl, Calendar *cal, unsigned rateLen, QlRateHelper **ratehelpers, DayCounter *dayCount, unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int trait, unsigned localisation, int forcePositive, double accuracy, double quadraticity, double monotonicity, int convexForcePositive, int extrapolate, char **e);

  QlMultiCurve *qlMultiCurve(double accuracy, char **e);
  void qlFreeMultiCurve(QlMultiCurve *o);
  QlYieldTermStructure *qlMultiCurveAddBootstrappedCurve(QlMultiCurve *mc, QlRelinkableYieldTermStructure *internalHandle, QlYieldTermStructure *curve, char **e);
  QlYieldTermStructure *qlMultiCurveAddNonBootstrappedCurve(QlMultiCurve *mc, QlRelinkableYieldTermStructure *internalHandle, QlYieldTermStructure *curve, char **e);

  QlRateHelper *qlIborIborBasisSwapRateHelper(QlQuote *basis, int tenorLen, int tenorUnit, unsigned settlementDays, Calendar *calendar, int convention, int endOfMonth, QlIborIndex *baseIndex, QlIborIndex *otherIndex, QlYieldTermStructure *discountHandle, int bootstrapBaseCurve, char **e);
  QlRateHelper *qlOvernightIborBasisSwapRateHelper(QlQuote *basis, int tenorLen, int tenorUnit, unsigned settlementDays, Calendar *calendar, int convention, int endOfMonth, QlOvernightIndex *baseIndex, QlIborIndex *otherIndex, QlYieldTermStructure *discountHandle, char **e);
  QlRateHelper *qlConstNotionalCrossCurrencyBasisSwapRateHelper(QlQuote *basis, int tenorLen, int tenorUnit, unsigned fixingDays, Calendar *calendar, int convention, int endOfMonth, QlIborIndex *baseCurrencyIndex, QlIborIndex *quoteCurrencyIndex, QlYieldTermStructure *collateralCurve, int isFxBaseCurrencyCollateralCurrency, int isBasisOnFxBaseCurrencyLeg, int paymentFrequency, int paymentLag, int quoteCurrencyPaymentFrequency, char **e);
  QlRateHelper *qlMtMCrossCurrencyBasisSwapRateHelper(QlQuote *basis, int tenorLen, int tenorUnit, unsigned fixingDays, Calendar *calendar, int convention, int endOfMonth, QlIborIndex *baseCurrencyIndex, QlIborIndex *quoteCurrencyIndex, QlYieldTermStructure *collateralCurve, int isFxBaseCurrencyCollateralCurrency, int isBasisOnFxBaseCurrencyLeg, int isFxBaseCurrencyLegResettable, int paymentFrequency, int paymentLag, int quoteCurrencyPaymentFrequency, char **e);
  QlRateHelper *qlConstNotionalCrossCurrencySwapRateHelper(QlQuote *fixedRate, int tenorLen, int tenorUnit, unsigned fixingDays, Calendar *calendar, int convention, int endOfMonth, int fixedFrequency, DayCounter *fixedDayCount, QlIborIndex *floatIndex, QlYieldTermStructure *collateralCurve, int collateralOnFixedLeg, int paymentLag, char **e);
  QlRateHelper *qlFxSwapRateHelper(QlQuote *fwdPoint, QlQuote *spotFx, int tenorLen, int tenorUnit, unsigned fixingDays, Calendar *calendar, int convention, int endOfMonth, int isFxBaseCurrencyCollateralCurrency, QlYieldTermStructure *collateralCurve, Calendar *tradingCalendar, char **e);
  QlRateHelper *qlFxSwapRateHelper2(QlQuote *fwdPoint, QlQuote *spotFx, int startDate, int endDate, int isFxBaseCurrencyCollateralCurrency, QlYieldTermStructure *collateralCurve, char **e);
  QlSwapRateHelper *qlSwapRateHelper1(QlQuote *q, int, int, Calendar *cal, int freq, int conv, DayCounter *dc, QlIborIndex *i, QlQuote *s, int, int, QlYieldTermStructure *ts, unsigned settlementDays, int pillar, int customPillarDate, int endOfMonth, int useIndexedCoupons, int floatConvention, QlFloatingRateCouponPricer *couponPricer, char **e);
  void qlFreeSwapRateHelper(QlSwapRateHelper *o);
  QlRateHelper* qlSwapRateHelperAsRateHelper(QlSwapRateHelper *o);

  void qlFreeBondHelper(QlBondHelper *o);
  QlRateHelper* qlBondHelperAsRateHelper(QlBondHelper *o);

  void qlFreeRateHelper(QlRateHelper *helper);
  QlRateHelper* qlFraRateHelper(QlQuote* rate, unsigned monthsToStart, unsigned monthsToEnd, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, int pillar, int customPillarDate, int useIndexedCoupon, char **e);

  void qlFreeOISRateHelper(QlOISRateHelper *o);
  QlRateHelper* qlOISRateHelperAsRateHelper(QlOISRateHelper *o);
  QlBondHelper* qlBondHelper(QlQuote* cleanPrice, QlBond* bond, int priceType, char **e);
  QlOISRateHelper* qlOISRateHelper(unsigned settlementDays, int, int, QlQuote* fixedRate, QlOvernightIndex* overnightIndex, QlYieldTermStructure* discountingCurve,
    int telescopicValueDates, int paymentLag, int paymentConvention, int paymentFrequency, Calendar* paymentCalendar,
    int, int, QlQuote* overnightSpread, int pillar, int customPillarDate, int averagingMethod, int endOfMonth, int fixedPaymentFrequency,
    Calendar* fixedCalendar, unsigned lookbackDays, unsigned lockoutDays, int applyObservationShift,
    QlFloatingRateCouponPricer* pricer, int rule, Calendar* overnightCalendar, int convention, char **e);
  QlOISRateHelper* qlOISRateHelper2(int, int, QlQuote* fixedRate, QlOvernightIndex* overnightIndex, QlYieldTermStructure* discountingCurve,
    int telescopicValueDates, int paymentLag, int paymentConvention, int paymentFrequency, Calendar* paymentCalendar,
    QlQuote* overnightSpread, int pillar, int customPillarDate, int averagingMethod, int endOfMonth, int fixedPaymentFrequency,
    Calendar* fixedCalendar, unsigned lookbackDays, unsigned lockoutDays, int applyObservationShift,
    QlFloatingRateCouponPricer* pricer, int rule, Calendar* overnightCalendar, int convention, char **e);
  QlSwapRateHelper* qlSwapRateHelper(QlQuote* rate, QlSwapIndex* swapIndex, QlQuote* spread, int, int, QlYieldTermStructure* discountingCurve, int pillar, int customPillarDate, int endOfMonth, int useIndexedCoupons, QlFloatingRateCouponPricer *couponPricer, char **e);
  QlRateHelper* qlBMASwapRateHelper(QlQuote* liborFraction, int, int, unsigned settlementDays, Calendar* calendar, int, int, int bmaConvention, DayCounter* bmaDayCount, QlBMAIndex* bmaIndex, QlIborIndex* index, char **e);
  QlRateHelper* qlDepositRateHelper1(QlQuote* rate, QlIborIndex* iborIndex, char **e);
  QlRateHelper* qlFraRateHelper1(QlQuote* rate, unsigned monthsToStart, QlIborIndex* iborIndex, int pillar, int customPillarDate, int useIndexedCoupon, char **e);
  QlRateHelper* qlFraRateHelper2(QlQuote* rate, int, int, unsigned lengthInMonths, unsigned fixingDays, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, int pillar, int customPillarDate, int useIndexedCoupon, char **e);
  QlRateHelper* qlFraRateHelper3(QlQuote* rate, int, int, QlIborIndex* iborIndex, int pillar, int customPillarDate, int useIndexedCoupon, char **e);
  QlRateHelper* qlFuturesRateHelper1(QlQuote* price, int immStartDate, int endDate, DayCounter* dayCounter, QlQuote* convexityAdjustment, int type, char **e);
  QlRateHelper* qlFuturesRateHelper2(QlQuote* price, int immDate, QlIborIndex* iborIndex, QlQuote* convexityAdjustment, char **e);
  QlRateHelper* qlFuturesRateHelper(QlQuote* price, int immDate, unsigned lengthInMonths, Calendar* calendar, int convention, int endOfMonth, DayCounter* dayCounter, QlQuote* convexityAdjustment, int type, char **e);
  QlRateHelper* qlOvernightIndexFutureRateHelper(QlQuote* price, int valueDate, int maturityDate, QlOvernightIndex* overnightIndex, QlQuote* convexityAdjustment, int averagingMethod, int pillar, int customPillarDate, char **e);
  QlRateHelper* qlSofrFutureRateHelper(QlQuote* price, int month, int year, int freq, QlQuote* convexityAdjustment, int pillar, int customPillarDate, char **e);
  double qlRateHelperImpliedQuote(QlRateHelper* o, char **e);
  QlBond* qlBondHelperBond(QlBondHelper* o, char **e);
  QlOvernightIndexedSwap* qlOISRateHelperSwap(QlOISRateHelper* o, char **e);
  QlVanillaSwap* qlSwapRateHelperSwap(QlSwapRateHelper* o, char **e);
  void qlFreeYieldTermStructure(QlYieldTermStructure *ts);
  QlRelinkableYieldTermStructure* qlRelinkableYieldTermStructure(QlYieldTermStructure *initial, char **e);
  void qlFreeRelinkableYieldTermStructure(QlRelinkableYieldTermStructure *o);
  void qlRelinkableYieldTermStructureLinkTo(QlRelinkableYieldTermStructure *o, QlYieldTermStructure *c, char **e);
  QlYieldTermStructure* qlRelinkableYieldTermStructureAsYieldTermStructure(QlRelinkableYieldTermStructure *o);
  double qlYieldTSDiscount(QlYieldTermStructure *ts, int date,
    int extrapolate, char **e);
  QlYieldTermStructure* qlFlatForward(int referenceDate, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e);
  QlYieldTermStructure* qlFlatForward1(unsigned settlementDays, Calendar* calendar, QlQuote* forward, DayCounter* dayCounter, int compounding, int frequency, char **e);
  QlYieldTermStructure* qlCompositeZeroYieldStructure(QlYieldTermStructure* curve1, QlYieldTermStructure* curve2, double (*fn)(double, double), int compounding, int frequency, char **e);
  InterestRate* qlYieldTermStructureZeroRate(QlYieldTermStructure* o, int d, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e);
  InterestRate* qlYieldTermStructureForwardRate(QlYieldTermStructure* o, int d1, int d2, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e);
  InterestRate* qlYieldTermStructureForwardRate1(QlYieldTermStructure* o, int d, int, int, DayCounter* resultDayCounter, int comp, int freq, int extrapolate, char **e);
  InterestRate* qlYieldTermStructureForwardRate2(QlYieldTermStructure* o, double t1, double t2, int comp, int freq, int extrapolate, char **e);
  InterestRate* qlYieldTermStructureZeroRate1(QlYieldTermStructure* o, double t, int comp, int freq, int extrapolate, char **e);
  double qlYieldTermStructureDiscount1(QlYieldTermStructure* o, double t, int extrapolate, char **e);

  QlYieldTermStructure *qlInterpolatedDiscountCurve(unsigned dfsLen,
    double *dfs, unsigned dfdatesLen, int *dfsDates, DayCounter *dayCount, Calendar *cal,
    unsigned quoteLen, QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, int extrapolate, char **e);
  QlYieldTermStructure *qlInterpolatedForwardCurve(unsigned fwdLen,
    double *fwds, unsigned fwddatesLen, int *fwdDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
    QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, char **e);
  QlYieldTermStructure *qlInterpolatedZeroCurve(unsigned yieldLen,
    double *yields, unsigned ydatesLen, int *yieldDates, DayCounter *dayCount, Calendar *cal, unsigned quoteLen,
    QlQuote **quotes, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, char **e);
  void qlFreeFittedBondDiscountCurveFittingMethod(FittedBondDiscountCurveFittingMethod *o);
  FittedBondDiscountCurveFittingMethod* qlCubicBSplinesFitting(unsigned knotVectorLen, double * knotVector, int constrainAtZero, unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, QlOptimizationMethod* method, Constraint* constraint, char **e);
  FittedBondDiscountCurveFittingMethod* qlExponentialSplinesFitting(int constrainAtZero, unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, unsigned numCoeffs, double fixedKappa, QlOptimizationMethod* method, Constraint* constraint, char **e);
  FittedBondDiscountCurveFittingMethod* qlNelsonSiegelFitting(unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, QlOptimizationMethod* method, Constraint* constraint, char **e);
  FittedBondDiscountCurveFittingMethod* qlSimplePolynomialFitting(unsigned degree, int constrainAtZero, unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, QlOptimizationMethod* method, Constraint* constraint, char **e);
  FittedBondDiscountCurveFittingMethod* qlSvenssonFitting(unsigned weightsLen, double *weights, unsigned l2Len, double *l2, double minCutoffTime, double maxCutoffTime, QlOptimizationMethod* method, Constraint* constraint, char **e);
  QlFittedBondDiscountCurve* qlFittedBondDiscountCurve(unsigned settlementDays, Calendar* calendar, unsigned bondsLen, QlBondHelper** bonds, DayCounter* dayCounter, FittedBondDiscountCurveFittingMethod* fittingMethod, double accuracy, unsigned maxEvaluations, unsigned guessLen, double *guess, double simplexLambda, char **e);
  QlFittedBondDiscountCurve* qlFittedBondDiscountCurve1(int referenceDate, unsigned bondsLen, QlBondHelper** bonds, DayCounter* dayCounter, FittedBondDiscountCurveFittingMethod* fittingMethod, double accuracy, unsigned maxEvaluations, unsigned guessLen, double *guess, double simplexLambda, char **e);

  void qlFreeFittedBondDiscountCurve(QlFittedBondDiscountCurve *o);
  QlYieldTermStructure* qlFittedBondDiscountCurveAsYieldTermStructure(QlFittedBondDiscountCurve *o);

  double qlFittedBondDiscountCurveFittingMethodMinimumCostValue(QlFittedBondDiscountCurve* o, char **e);
  int qlFittedBondDiscountCurveFittingMethodNumberOfIterations(QlFittedBondDiscountCurve* o, char **e);
  QlYieldTermStructure* qlForwardSpreadedTermStructure(QlYieldTermStructure* x0, QlQuote* spread, char **e);
  QlYieldTermStructure* qlZeroSpreadedTermStructure(QlYieldTermStructure* x0, QlQuote* spread, int comp, int freq, char **e);
  int qlTermStructureReferenceDate(QlTermStructure* o, char **e);
  int qlTermStructureMaxDate(QlTermStructure* o, char **e);
  void qlFreeTermStructure(QlTermStructure *o);
  QlTermStructure* qlYieldTermStructureAsTermStructure(QlYieldTermStructure *o);
  QlYieldTermStructure* qlImpliedTermStructure(QlYieldTermStructure* x0, int referenceDate, char **e);
  QlYieldTermStructure* qlPiecewiseZeroSpreadedTermStructure(QlYieldTermStructure* x0, unsigned spreadsLen, QlQuote** spreads, unsigned datesLen, int* dates, int comp, int freq, int interpolator, int approximator, int approximatorArg, char **e);
  QlYieldTermStructure* qlQuantoTermStructure(QlYieldTermStructure* underlyingDividendTS, QlYieldTermStructure* riskFreeTS, QlYieldTermStructure* foreignRiskFreeTS, QlBlackVolTermStructure* underlyingBlackVolTS, double strike, QlBlackVolTermStructure* exchRateBlackVolTS, double exchRateATMlevel, double underlyingExchRateCorrelation, char **e);
  QlYieldTermStructure* qlUltimateForwardTermStructure(QlYieldTermStructure* x0, QlQuote* lastLiquidForwardRate, QlQuote* ultimateForwardRate, int fspLen, int fspUnit, double alpha, int roundingDigits, int compounding, int frequency, char **e);
  QlYieldTermStructure* qlInterpolatedSpreadDiscountCurve(QlYieldTermStructure* baseCurve, unsigned dfsLen, double *dfs, unsigned datesLen, int *dates, int interpolator, int approximator, int approximatorArg, char **e);
  QlRateHelper* qlMultipleResetsSwapRateHelper(unsigned settlementDays, int tenorLen, int tenorUnit, QlQuote* fixedRate, QlIborIndex* iborIndex, unsigned resetsPerCoupon, QlYieldTermStructure* discountingCurve, int averagingMethod, double spread, int fixedFrequency, DayCounter* fixedDayCount, int fixedConvention, char **e);

  void qlIndexAddFixing(QlIndex *i, int date, double fix, int overwrite, char **e);
  double qlIndexFixing(QlIndex *i, int date, int forecastTodaysFixing, char **e);
  int qlIndexHasHistoricalFixing(QlIndex *i, int date, char **e);
  int qlIndexIsValidFixingDate(QlIndex *i, int date, char **e);
  void qlIndexAddFixings(QlIndex *i, unsigned datesLen, int *dates, double *values, int overwrite, char **e);
  void qlIndexClearFixings(QlIndex *i, char **e);
  void qlIndexFixingHistory(QlIndex *i, unsigned *datesLen, int **dates, unsigned *valuesLen, double **values, char **e);
  void qlIndexManagerHistories(unsigned *count, char ***names, char **e);
  void qlIndexManagerClearHistories(char **e);
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
  QlOvernightIndexedSwapIndex* qlOvernightIndexedSwapIndex(char* familyName, int, int, unsigned settlementDays, Currency* currency, QlOvernightIndex* overnightIndex, int telescopicValueDates, int averagingMethod, char **e);
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
  QlIborIndex *qlIborIndex(char *name, int, int, unsigned settlDays, Currency *ccy, Calendar *cal, int conv, int eom, DayCounter *dayCount, QlYieldTermStructure *fwd, char **e);
  QlIborIndex *qlLibor(char *name, int, int, unsigned settlDays, Currency *ccy, Calendar *cal, DayCounter *dc, QlYieldTermStructure *fwd, char **e);
  QlIborIndex *qlDailyTenorLibor(char *name, unsigned settlDays, Currency *ccy, Calendar *cal, DayCounter *dayCount, QlYieldTermStructure *fwd, char **e);
  QlIborIndex *qlCustomIborIndex(char *name, int, int, unsigned settlDays, Currency *ccy, Calendar *fixingCal, Calendar *valueCal, Calendar *maturityCal, int conv, int eom, DayCounter *dayCount, QlYieldTermStructure *fwd, char **e);

  QlOvernightIndex *qlOvernightIndex(char *name, unsigned settlDays, Currency *cur, Calendar *cal, DayCounter *dayCount, QlYieldTermStructure *fwd, char **e);

  QlIborIndex *qlCreateIbor(int, int, int, QlYieldTermStructure *fwd, char **e);
  QlOvernightIndex *qlCreateONIndex(int index, QlYieldTermStructure *fwd, char **e);

  void qlFreeIborIndex(QlIborIndex *i);
  QlInterestRateIndex* qlIborIndexAsInterestRateIndex(QlIborIndex *o);
  void qlFreeOvernightIndex(QlOvernightIndex *o);
  QlIborIndex* qlOvernightIndexAsIborIndex(QlOvernightIndex *o);
  int qlIborIndexBusinessDayConvention(QlIborIndex* o);
  int qlIborIndexEndOfMonth(QlIborIndex* o);

  QlEquityIndex *qlEquityIndex(char *name, Calendar *fixingCalendar, Currency *ccy, QlYieldTermStructure *interest, QlYieldTermStructure *dividend, QlQuote *spot, char **e);
  void qlFreeEquityIndex(QlEquityIndex *o);
  QlIndex* qlEquityIndexAsIndex(QlEquityIndex *o);

  QlZeroInflationIndex *qlCreateZeroInflationIndex(int index, char **e);
  QlYoYInflationIndex *qlCreateYoYInflationIndex(int index, char **e);

  Region *qlRegion(int r, char **e);
  Region *qlCreateRegion(char *name, char *code, char **e);
  void qlFreeRegion(Region *o);
  const char *qlRegionName(Region *o);

  QlZeroInflationIndex *qlZeroInflationIndex(char *familyName, Region *region, int revised, int frequency,
    int availLagN, int availLagU, Currency *currency, QlZeroInflationTermStructure *ts, char **e);
  QlYoYInflationIndex *qlYoYInflationIndex(char *familyName, Region *region, int revised, int frequency,
    int availLagN, int availLagU, Currency *currency, QlYoYInflationTermStructure *ts, char **e);
  QlYoYInflationIndex *qlYoYInflationIndexFromZero(QlZeroInflationIndex *underlying, QlYoYInflationTermStructure *ts, char **e);

  void qlFreeInflationIndex(QlInflationIndex *o);
  QlIndex* qlInflationIndexAsIndex(QlInflationIndex *o);
  void qlFreeZeroInflationIndex(QlZeroInflationIndex *o);
  QlInflationIndex* qlZeroInflationIndexAsInflationIndex(QlZeroInflationIndex *o);
  void qlFreeYoYInflationIndex(QlYoYInflationIndex *o);
  QlInflationIndex* qlYoYInflationIndexAsInflationIndex(QlYoYInflationIndex *o);

  double qlZeroInflationIndexFixing(QlZeroInflationIndex* o, int fixingDate, char **e);
  double qlYoYInflationIndexFixing(QlYoYInflationIndex* o, int fixingDate, char **e);

  /* YoYOptionletVolatilitySurface */
  QlYoYOptionletVolatilitySurface *qlConstantYoYOptionletVolatility(QlQuote *v, unsigned settlementDays,
      Calendar *cal, int bdc, DayCounter *dc, int observationLagLen, int observationLagUnit, int frequency,
      int indexIsInterpolated, double minStrike, double maxStrike, int volType, double displacement, char **e);
  void qlFreeYoYOptionletVolatilitySurface(QlYoYOptionletVolatilitySurface *p);
  QlVolatilityTermStructure *qlYoYOptionletVolatilitySurfaceAsVolatilityTermStructure(QlYoYOptionletVolatilitySurface *o);
  double qlYoYOptionletVolatilitySurfaceVolatility(QlYoYOptionletVolatilitySurface *o, int maturityDate,
      double strike, int obsLagLen, int obsLagUnit, int extrapolate, char **e);
  double qlYoYOptionletVolatilitySurfaceTotalVariance(QlYoYOptionletVolatilitySurface *o, int exerciseDate,
      double strike, int obsLagLen, int obsLagUnit, int extrapolate, char **e);

  /* YoY inflation cap/floor pricing engines -- all three share the same ctor shape
     (index, vol surface handle, nominal discount curve handle). */
  QlPricingEngine *qlYoYInflationBlackCapFloorEngine(QlYoYInflationIndex *index, QlYoYOptionletVolatilitySurface *vol,
      QlYieldTermStructure *nominalTs, char **e);
  QlPricingEngine *qlYoYInflationUnitDisplacedBlackCapFloorEngine(QlYoYInflationIndex *index,
      QlYoYOptionletVolatilitySurface *vol, QlYieldTermStructure *nominalTs, char **e);
  QlPricingEngine *qlYoYInflationBachelierCapFloorEngine(QlYoYInflationIndex *index, QlYoYOptionletVolatilitySurface *vol,
      QlYieldTermStructure *nominalTs, char **e);

  /* CPICapFloorTermPriceSurface */
  QlCPICapFloorTermPriceSurface *qlCPICapFloorTermPriceSurface(double nominal, double baseRate,
      int observationLagLen, int observationLagUnit, Calendar *cal, int bdc, DayCounter *dc,
      QlZeroInflationIndex *zii, int interpolationType, QlYieldTermStructure *yts,
      unsigned cStrikesLen, double *cStrikes, unsigned fStrikesLen, double *fStrikes,
      unsigned cfMaturitiesLen, int *cfMaturitiesNum, unsigned, int *cfMaturitiesUnit,
      unsigned cPriceRows, unsigned cPriceCols, double *cPriceData,
      unsigned fPriceRows, unsigned fPriceCols, double *fPriceData,
      int interpolator2D, char **e);
  void qlFreeCPICapFloorTermPriceSurface(QlCPICapFloorTermPriceSurface *o);
  QlTermStructure *qlCPICapFloorTermPriceSurfaceAsTermStructure(QlCPICapFloorTermPriceSurface *o);

  /* The only CPICapFloor pricing engine in QL 1.43: prices purely by interpolating a price
     surface, no stochastic-vol model (see plan Item 3's note on the CPI/YoY asymmetry). */
  QlPricingEngine *qlInterpolatingCPICapFloorEngine(QlCPICapFloorTermPriceSurface *surface, char **e);

  /* CPIVolatilitySurface -- no consumer (engine/pricer) in QL 1.43, see this type's own haddock
     in QuantLib.Internal.Type; stands alone as a queryable surface. */
  QlCPIVolatilitySurface *qlConstantCPIVolatility(QlQuote *v, unsigned settlementDays, Calendar *cal,
      int bdc, DayCounter *dc, int observationLagLen, int observationLagUnit, int frequency,
      int indexIsInterpolated, char **e);
  void qlFreeCPIVolatilitySurface(QlCPIVolatilitySurface *p);
  QlVolatilityTermStructure *qlCPIVolatilitySurfaceAsVolatilityTermStructure(QlCPIVolatilitySurface *o);
  double qlCPIVolatilitySurfaceVolatility(QlCPIVolatilitySurface *o, int maturityDate,
      double strike, int obsLagLen, int obsLagUnit, int extrapolate, char **e);
  double qlCPIVolatilitySurfaceTotalVariance(QlCPIVolatilitySurface *o, int exerciseDate,
      double strike, int obsLagLen, int obsLagUnit, int extrapolate, char **e);

  /* YoYCapFloorTermPriceSurface */
  QlYoYCapFloorTermPriceSurface *qlYoYCapFloorTermPriceSurface(unsigned fixingDays,
      int yyLagLen, int yyLagUnit, QlYoYInflationIndex *yii, int interpolationType,
      QlYieldTermStructure *nominal, DayCounter *dc, Calendar *cal, int bdc,
      unsigned cStrikesLen, double *cStrikes, unsigned fStrikesLen, double *fStrikes,
      unsigned cfMaturitiesLen, int *cfMaturitiesNum, unsigned, int *cfMaturitiesUnit,
      unsigned cPriceRows, unsigned cPriceCols, double *cPriceData,
      unsigned fPriceRows, unsigned fPriceCols, double *fPriceData,
      int interpolator2D, int interpolator1D, int approximator, int approximatorArg, char **e);
  void qlFreeYoYCapFloorTermPriceSurface(QlYoYCapFloorTermPriceSurface *o);
  QlTermStructure *qlYoYCapFloorTermPriceSurfaceAsTermStructure(QlYoYCapFloorTermPriceSurface *o);
  int qlYoYCapFloorTermPriceSurfaceBaseDate(QlYoYCapFloorTermPriceSurface *o, char **e);
  void qlYoYCapFloorTermPriceSurfaceAtmYoYSwapDateRates(QlYoYCapFloorTermPriceSurface *o,
      unsigned *dl, int **date, unsigned *rl, double **rate, char **e);
  double qlYoYCapFloorTermPriceSurfaceAtmYoYSwapRate(QlYoYCapFloorTermPriceSurface *o, int d,
      int extrapolate, char **e);
  double qlYoYCapFloorTermPriceSurfaceAtmYoYRate(QlYoYCapFloorTermPriceSurface *o, int d,
      int obsLagLen, int obsLagUnit, int extrapolate, char **e);
  void qlYoYCapFloorTermPriceSurfaceStrikes(QlYoYCapFloorTermPriceSurface *o, unsigned *sl, double **strike, char **e);

  /* KInterpolatedYoYOptionletVolatilitySurface<Linear> -- another concrete leaf constructor for
     YoYOptionletVolatilitySurface (Item 1), built by internally wiring up an
     InterpolatedYoYOptionletStripper<Linear> and one of the 3 YoYInflationCapFloorEngine
     descendants (constructed here with a null vol handle -- the stripper sets the real vol as
     it bootstraps each strike's curve, see interpolatedyoyoptionletstripper.hpp). Neither the
     stripper nor the per-strike PiecewiseYoYOptionletVolatilityCurve/YoYOptionletHelper it
     builds internally are ever exposed: nothing in upstream reaches them from outside
     YoYOptionletStripper::initialize, so there is nothing for a Haskell binding to return. */
  QlYoYOptionletVolatilitySurface *qlKInterpolatedYoYOptionletVolatilitySurfaceBlack(
      unsigned settlementDays, Calendar *cal, int bdc, DayCounter *dc,
      QlYoYCapFloorTermPriceSurface *capFloorPrices, QlYoYInflationIndex *index,
      QlYieldTermStructure *nominalTs, double slope,
      int interpolator, int approximator, int approximatorArg, char **e);
  QlYoYOptionletVolatilitySurface *qlKInterpolatedYoYOptionletVolatilitySurfaceUnitDisplacedBlack(
      unsigned settlementDays, Calendar *cal, int bdc, DayCounter *dc,
      QlYoYCapFloorTermPriceSurface *capFloorPrices, QlYoYInflationIndex *index,
      QlYieldTermStructure *nominalTs, double slope,
      int interpolator, int approximator, int approximatorArg, char **e);
  QlYoYOptionletVolatilitySurface *qlKInterpolatedYoYOptionletVolatilitySurfaceBachelier(
      unsigned settlementDays, Calendar *cal, int bdc, DayCounter *dc,
      QlYoYCapFloorTermPriceSurface *capFloorPrices, QlYoYInflationIndex *index,
      QlYieldTermStructure *nominalTs, double slope,
      int interpolator, int approximator, int approximatorArg, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
