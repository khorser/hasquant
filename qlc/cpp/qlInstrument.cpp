#include <ql/instrument.hpp>

#include "qlaux.h"

using namespace QuantLib;

double qlInstrumentNPV(QlInstrument *instr, char **e) {
  try {
    return (*arg(instr))->NPV();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

void qlInstrumentSetPricingEngine(QlInstrument *instr, QlPricingEngine *eng,
  char **e) {
  try {
    (*arg(instr))->setPricingEngine(*arg(eng));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}

void DLLEXPORT qlFreeInstrument(QlInstrument *instr) {
  del(instr);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
