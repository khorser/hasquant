#include <ql/interestrate.hpp>

#include "qlaux.h"

using namespace QuantLib;

InterestRate *qlInterestRate(double r, DayCounter *dc, int comp, int freq, char **e) {
  try {
    return alloc(new InterestRate(
	  r,
	  *arg(dc),
	  (Compounding) comp,
	  (Frequency) freq));
  } catch (std::exception& er) {
    return handleException<InterestRate *>(e, er);
  }
}

void qlFreeInterestRate(InterestRate *rate) {
  del(rate);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
