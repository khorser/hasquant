#include <ql/methods/finitedifferences/solvers/fdmbackwardsolver.hpp>

#include "qlaux.h"
#include "qlMethod.h"

using namespace QuantLib;

void qlFreeFdmSchemeDesc(FdmSchemeDesc *o) { del(o); }

FdmSchemeDesc* qlFdmSchemeDesc(int type, double theta, double mu, char **e) {
  try {
    return alloc(new FdmSchemeDesc((FdmSchemeDesc::FdmSchemeType)type, theta, mu));
  } catch (std::exception& er) {
    return handleException<FdmSchemeDesc*>(e, er);
  }
}

FdmSchemeDesc* qlFdmSchemeDescCraigSneyd(char **e) {
  try {
    return alloc(new FdmSchemeDesc(FdmSchemeDesc::CraigSneyd()));
  } catch (std::exception& er) {
    return handleException<FdmSchemeDesc*>(e, er);
  }
}
FdmSchemeDesc* qlFdmSchemeDescDouglas(char **e) {
  try {
    return alloc(new FdmSchemeDesc(FdmSchemeDesc::Douglas()));
  } catch (std::exception& er) {
    return handleException<FdmSchemeDesc*>(e, er);
  }
}
FdmSchemeDesc* qlFdmSchemeDescExplicitEuler(char **e) {
  try {
    return alloc(new FdmSchemeDesc(FdmSchemeDesc::ExplicitEuler()));
  } catch (std::exception& er) {
    return handleException<FdmSchemeDesc*>(e, er);
  }
}
FdmSchemeDesc* qlFdmSchemeDescHundsdorfer(char **e) {
  try {
    return alloc(new FdmSchemeDesc(FdmSchemeDesc::Hundsdorfer()));
  } catch (std::exception& er) {
    return handleException<FdmSchemeDesc*>(e, er);
  }
}
FdmSchemeDesc* qlFdmSchemeDescImplicitEuler(char **e) {
  try {
    return alloc(new FdmSchemeDesc(FdmSchemeDesc::ImplicitEuler()));
  } catch (std::exception& er) {
    return handleException<FdmSchemeDesc*>(e, er);
  }
}
FdmSchemeDesc* qlFdmSchemeDescModifiedCraigSneyd(char **e) {
  try {
    return alloc(new FdmSchemeDesc(FdmSchemeDesc::ModifiedCraigSneyd()));
  } catch (std::exception& er) {
    return handleException<FdmSchemeDesc*>(e, er);
  }
}
FdmSchemeDesc* qlFdmSchemeDescModifiedHundsdorfer(char **e) {
  try {
    return alloc(new FdmSchemeDesc(FdmSchemeDesc::ModifiedHundsdorfer()));
  } catch (std::exception& er) {
    return handleException<FdmSchemeDesc*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
