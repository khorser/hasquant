#include <ql/interestrate.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlInterestRate(double r, void *dc, int comp, int freq, char **e) {
  *e = 0;
  try {
    return TP("Allocated InterestRate",
	new InterestRate(
	  r,
	  *log_and_cast<DayCounter>("Pday counter", dc),
	  (Compounding) comp,
	  (Frequency) freq));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void qlFreeInterestRate(void *rate) {
  delete log_and_cast<InterestRate>("Pfreeing interest rate", rate);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
