#include <ql/math/optimization/all.hpp>

#include "qlaux.h"
#include "qlMath.h"

using namespace QuantLib;

void qlFreeConstraint(Constraint *o) { del(o); }

Constraint* qlBoundaryConstraint(double low, double high, char **e) {
  try {
    return alloc(new BoundaryConstraint(low, high));
  } catch (std::exception& er) {
    return handleException<Constraint*>(e, er);
  }
}
Constraint* qlCompositeConstraint(Constraint* c1, Constraint* c2, char **e) {
  try {
    return alloc(new CompositeConstraint(*arg(c1), *arg(c2)));
  } catch (std::exception& er) {
    return handleException<Constraint*>(e, er);
  }
}
Constraint* qlNoConstraint(char **e) {
  try {
    return alloc(new NoConstraint());
  } catch (std::exception& er) {
    return handleException<Constraint*>(e, er);
  }
}
Constraint* qlPositiveConstraint(char **e) {
  try {
    return alloc(new PositiveConstraint());
  } catch (std::exception& er) {
    return handleException<Constraint*>(e, er);
  }
}
void qlFreeOptimizationMethod(OptimizationMethod *o) { del(o); }

OptimizationMethod* qlLevenbergMarquardt(double epsfcn, double xtol, double gtol, char **e) {
  try {
    return alloc(new LevenbergMarquardt(epsfcn, xtol, gtol));
  } catch (std::exception& er) {
    return handleException<OptimizationMethod*>(e, er);
  }
}
OptimizationMethod* qlSimplex(double lambda, char **e) {
  try {
    return alloc(new Simplex(lambda));
  } catch (std::exception& er) {
    return handleException<OptimizationMethod*>(e, er);
  }
}

void qlFreeEndCriteria(EndCriteria *o) { del(o); }
EndCriteria* qlEndCriteria(unsigned maxIterations, unsigned maxStationaryStateIterations, double rootEpsilon, double functionEpsilon, double gradientNormEpsilon, char **e) {
  try {
    return alloc(new EndCriteria(maxIterations, maxStationaryStateIterations, rootEpsilon, functionEpsilon, gradientNormEpsilon));
  } catch (std::exception& er) {
    return handleException<EndCriteria*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
