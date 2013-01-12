#include <ql/instrument.hpp>

#include "ql.h"

using namespace QuantLib;

double qlInstrumentNPV(Instrument *instr, char **e) {
  try {
    return arg(instr)->NPV();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

void qlInstrumentSetPricingEngine(Instrument *instr, QlPricingEngine eng,
  char **e) {
  try {
    arg(instr)->setPricingEngine(arg(eng));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
