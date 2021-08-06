#include <ql/math/optimization/all.hpp>
#include <ql/timegrid.hpp>
#include <ql/math/rounding.hpp>

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

void qlFreeTimeGrid(TimeGrid *o) { del(o); }

TimeGrid* qlTimeGrid1(double end, unsigned steps, char **e) {
  try {
    return alloc(new TimeGrid(end, steps));
  } catch (std::exception& er) {
    return handleException<TimeGrid*>(e, er);
  }
}
TimeGrid* qlTimeGrid2(unsigned x0Len, double* x0, char **e) {
  try {
    return alloc(new TimeGrid(x0, x0+x0Len));
  } catch (std::exception& er) {
    return handleException<TimeGrid*>(e, er);
  }
}
TimeGrid* qlTimeGrid3(unsigned x0Len, double* x0, unsigned steps, char **e) {
  try {
    return alloc(new TimeGrid(x0, x0+x0Len, steps));
  } catch (std::exception& er) {
    return handleException<TimeGrid*>(e, er);
  }
}

void qlFreeRounding(Rounding *o) { del(o); }

Rounding* qlRounding(char **e) {
  try {
    return alloc(new Rounding());
  } catch (std::exception& er) {
    return handleException<Rounding*>(e, er);
  }
}

Rounding* qlRounding1(int precision, int type, int digit, char **e) {
  try {
    return alloc(new Rounding(precision, (Rounding::Type)type, digit));
  } catch (std::exception& er) {
    return handleException<Rounding*>(e, er);
  }
}

double qlRound(Rounding *r, double val) {
  return (*r)(val);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
