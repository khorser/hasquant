#include <ql/quote.hpp>
#include <ql/termstructures/volatility/optionlet/constantoptionletvol.hpp>
#include <ql/termstructures/volatility/equityfx/blackvoltermstructure.hpp>
#include <ql/termstructures/volatility/swaption/swaptionconstantvol.hpp>

#include "qlaux.h"

using namespace QuantLib;

QlOptionletVolatilityStructure *qlConstantOptionletVol1(
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

QlVolatilityTermStructure* qlOptionletVolatilityStructureAsVolatilityTermStructure(QlOptionletVolatilityStructure *o) { return ret(new QlVolatilityTermStructure(*arg(o))); }

void qlFreeBlackVolTermStructure(QlBlackVolTermStructure *o) { del(o); }
QlVolatilityTermStructure* qlBlackVolTermStructureAsVolatilityTermStructure(QlBlackVolTermStructure *o) { return ret(new QlVolatilityTermStructure(*arg(o))); }

void qlFreeVolatilityTermStructure(QlVolatilityTermStructure *o) { del(o); }
QlTermStructure* qlVolatilityTermStructureAsTermStructure(QlVolatilityTermStructure *o) { return ret(new QlTermStructure(*arg(o))); }

void qlFreeSwaptionVolatilityStructure(QlSwaptionVolatilityStructure *o) { del(o); }
QlVolatilityTermStructure* qlSwaptionVolatilityStructureAsVolatilityTermStructure(QlSwaptionVolatilityStructure *o) { return ret(new QlVolatilityTermStructure(*arg(o))); }

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
