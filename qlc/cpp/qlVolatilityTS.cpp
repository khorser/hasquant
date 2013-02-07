#include <ql/quote.hpp>
#include <ql/termstructures/volatility/optionlet/constantoptionletvol.hpp>

#include "qlaux.h"

using namespace QuantLib;

QlOptionletVolatilityStructure *qlConstantOptionletVol(
    unsigned days, Calendar *cal, int conv, QlQuote *q, DayCounter *dc, char **e) {
  try {
    return ret(new QlOptionletVolatilityStructure(new ConstantOptionletVolatility(
		    days, *arg(cal), (BusinessDayConvention) conv, Handle<Quote>(*q),
		    *arg(dc))));
  } catch (std::exception& er) {
    return handleException<QlOptionletVolatilityStructure *>(e, er);
  }
}

void qlFreeOptionletVolatilityStructure(QlOptionletVolatilityStructure *p) {
  del(p);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
