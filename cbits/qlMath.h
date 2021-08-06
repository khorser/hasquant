#ifdef __cplusplus
extern "C" {
#endif
  void qlFreeConstraint(Constraint *o);
  Constraint* qlBoundaryConstraint(double low, double high, char **e);
  Constraint* qlCompositeConstraint(Constraint* c1, Constraint* c2, char **e);
  Constraint* qlNoConstraint(char **e);
  Constraint* qlPositiveConstraint(char **e);

  void qlFreeOptimizationMethod(OptimizationMethod *o);
  OptimizationMethod* qlSimplex(double lambda, char **e);
  OptimizationMethod* qlLevenbergMarquardt(double epsfcn, double xtol, double gtol, char **e);
  void qlFreeEndCriteria(EndCriteria *o);
  EndCriteria* qlEndCriteria(unsigned maxIterations, unsigned maxStationaryStateIterations, double rootEpsilon, double functionEpsilon, double gradientNormEpsilon, char **e);
  void qlFreeTimeGrid(TimeGrid *o);
  TimeGrid* qlTimeGrid1(double end, unsigned steps, char **e);
  TimeGrid* qlTimeGrid2(unsigned x0Len, double* x0, char **e);
  TimeGrid* qlTimeGrid3(unsigned x0Len, double* x0, unsigned steps, char **e);

  void qlFreeRounding(Rounding *o);
  Rounding* qlRounding(char **e);
  Rounding* qlRounding1(int precision, int type, int digit, char **e);
  double qlRound(Rounding *r, double val);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
