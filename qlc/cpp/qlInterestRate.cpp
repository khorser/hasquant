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

// generated code
double qlInterestRateCompoundFactor1(InterestRate* o, int d1, int d2, int refStart, int refEnd, char **e) {
  try {
    return (arg(o))->compoundFactor(Date(d1), Date(d2), qlNullableDate(refStart), qlNullableDate(refEnd));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlInterestRateCompoundFactor(InterestRate* o, double t, char **e) {
  try {
    return (arg(o))->compoundFactor(t);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlInterestRateDiscountFactor1(InterestRate* o, int d1, int d2, int refStart, int refEnd, char **e) {
  try {
    return (arg(o))->discountFactor(Date(d1), Date(d2), qlNullableDate(refStart), qlNullableDate(refEnd));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

double qlInterestRateDiscountFactor(InterestRate* o, double t, char **e) {
  try {
    return (arg(o))->discountFactor(t);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

InterestRate* qlInterestRateEquivalentRate1(InterestRate* o, DayCounter* resultDC, int comp, int freq, int d1, int d2, int refStart, int refEnd, char **e) {
  try {
    return ret(new InterestRate((arg(o))->equivalentRate((*arg(resultDC)), (Compounding)comp, (Frequency)freq, Date(d1), Date(d2), qlNullableDate(refStart), qlNullableDate(refEnd))));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlInterestRateEquivalentRate(InterestRate* o, int comp, int freq, double t, char **e) {
  try {
    return ret(new InterestRate((arg(o))->equivalentRate((Compounding)comp, (Frequency)freq, t)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlInterestRateImpliedRate1(InterestRate* o, double compound, DayCounter* resultDC, int comp, int freq, int d1, int d2, int refStart, int refEnd, char **e) {
  try {
    return ret(new InterestRate((arg(o))->impliedRate(compound, (*arg(resultDC)), (Compounding)comp, (Frequency)freq, Date(d1), Date(d2), qlNullableDate(refStart), qlNullableDate(refEnd))));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

InterestRate* qlInterestRateImpliedRate(InterestRate* o, double compound, DayCounter* resultDC, int comp, int freq, double t, char **e) {
  try {
    return ret(new InterestRate((arg(o))->impliedRate(compound, (*arg(resultDC)), (Compounding)comp, (Frequency)freq, t)));
  } catch (std::exception& er) {
    return handleException<InterestRate*>(e, er);
  }
}

double qlInterestRateRate(InterestRate* o, char **e) {
  try {
    return (arg(o))->rate();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
