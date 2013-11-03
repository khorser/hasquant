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
  void DLLEXPORT qlFreeConstraint(Constraint *o);
  Constraint* DLLEXPORT qlBoundaryConstraint(double low, double high, char **e);
  Constraint* DLLEXPORT qlCompositeConstraint(Constraint* c1, Constraint* c2, char **e);
  Constraint* DLLEXPORT qlNoConstraint(char **e);
  Constraint* DLLEXPORT qlPositiveConstraint(char **e);

  void DLLEXPORT qlFreeOptimizationMethod(OptimizationMethod *o);
  OptimizationMethod* DLLEXPORT qlSimplex(double lambda, char **e);
  OptimizationMethod* DLLEXPORT qlLevenbergMarquardt(double epsfcn, double xtol, double gtol, char **e);
  void DLLEXPORT qlFreeEndCriteria(EndCriteria *o);
  EndCriteria* DLLEXPORT qlEndCriteria(unsigned maxIterations, unsigned maxStationaryStateIterations, double rootEpsilon, double functionEpsilon, double gradientNormEpsilon, char **e);
  void DLLEXPORT qlFreeTimeGrid(TimeGrid *o);
  TimeGrid* DLLEXPORT qlTimeGrid1(double end, unsigned steps, char **e);
  TimeGrid* DLLEXPORT qlTimeGrid2(unsigned x0Len, double* x0, char **e);
  TimeGrid* DLLEXPORT qlTimeGrid3(unsigned x0Len, double* x0, unsigned steps, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
