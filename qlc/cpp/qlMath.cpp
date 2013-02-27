#include <ql/models/all.hpp>
#include <ql/legacy/libormarketmodels/all.hpp>
#include <ql/experimental/shortrate/generalizedhullwhite.hpp>
#include <ql/experimental/variancegamma/variancegammamodel.hpp>

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

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
