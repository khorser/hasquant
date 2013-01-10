#include <ql/interestrate.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlInterestRate(double r, void *dc, int comp, int freq, char **e) {
  try {
    return uncast("Allocated InterestRate",
	new InterestRate(
	  r,
	  *cast<DayCounter>("Pday counter", dc),
	  (Compounding) comp,
	  (Frequency) freq));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void qlFreeInterestRate(void *rate) {
  delete cast<InterestRate>("Pfreeing interest rate", rate);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
