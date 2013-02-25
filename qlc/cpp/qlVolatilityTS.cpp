#include <ql/quote.hpp>
#include <ql/termstructures/volatility/optionlet/constantoptionletvol.hpp>
#include <ql/termstructures/volatility/equityfx/blackvoltermstructure.hpp>
#include <ql/termstructures/volatility/swaption/swaptionconstantvol.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/termstructures/volatility/swaption/swaptionconstantvol.hpp>

#include "qlaux.h"
#include "qlVolatilityTS.h"

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

void qlFreeSmileSection(QlSmileSection *o) { del(o); }

QlBlackVolTermStructure* qlBlackConstantVol1(unsigned settlementDays, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {
    return ret(new QlBlackVolTermStructure(alloc(new BlackConstantVol(settlementDays, (*arg(x1)), Handle<Quote>(*arg(volatility)), (*arg(dayCounter))))));
  } catch (std::exception& er) {
    return handleException<QlBlackVolTermStructure*>(e, er);
  }
}
QlBlackVolTermStructure* qlBlackConstantVol(int referenceDate, Calendar* x1, QlQuote* volatility, DayCounter* dayCounter, char **e) {
  try {
    return ret(new QlBlackVolTermStructure(alloc(new BlackConstantVol(Date(referenceDate), (*arg(x1)), Handle<Quote>(*arg(volatility)), (*arg(dayCounter))))));
  } catch (std::exception& er) {
    return handleException<QlBlackVolTermStructure*>(e, er);
  }
}
QlOptionletVolatilityStructure* qlConstantOptionletVolatility(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {
    return ret(new QlOptionletVolatilityStructure(alloc(new ConstantOptionletVolatility(Date(referenceDate), (*arg(cal)), (BusinessDayConvention)bdc, Handle<Quote>(*arg(volatility)), (*arg(dc))))));
  } catch (std::exception& er) {
    return handleException<QlOptionletVolatilityStructure*>(e, er);
  }
}
QlSwaptionVolatilityStructure* qlConstantSwaptionVolatility1(int referenceDate, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {
    return ret(new QlSwaptionVolatilityStructure(alloc(new ConstantSwaptionVolatility(Date(referenceDate), (*arg(cal)), (BusinessDayConvention)bdc, Handle<Quote>(*arg(volatility)), (*arg(dc))))));
  } catch (std::exception& er) {
    return handleException<QlSwaptionVolatilityStructure*>(e, er);
  }
}
QlSwaptionVolatilityStructure* qlConstantSwaptionVolatility(unsigned settlementDays, Calendar* cal, int bdc, QlQuote* volatility, DayCounter* dc, char **e) {
  try {
    return ret(new QlSwaptionVolatilityStructure(alloc(new ConstantSwaptionVolatility(settlementDays, (*arg(cal)), (BusinessDayConvention)bdc, Handle<Quote>(*arg(volatility)), (*arg(dc))))));
  } catch (std::exception& er) {
    return handleException<QlSwaptionVolatilityStructure*>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance1(QlSwaptionVolatilityStructure* o, int optionDate, Period* swapTenor, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance(Date(optionDate), (*arg(swapTenor)), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance2(QlSwaptionVolatilityStructure* o, double optionTime, Period* swapTenor, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance(optionTime, (*arg(swapTenor)), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance3(QlSwaptionVolatilityStructure* o, Period* optionTenor, double swapLength, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance((*arg(optionTenor)), swapLength, strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance(Date(optionDate), swapLength, strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance(optionTime, swapLength, strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureBlackVariance(QlSwaptionVolatilityStructure* o, Period* optionTenor, Period* swapTenor, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->blackVariance((*arg(optionTenor)), (*arg(swapTenor)), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureMaxSwapLength(QlSwaptionVolatilityStructure* o, char **e) {
  try {
    return (*arg(o))->maxSwapLength();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
Period* qlSwaptionVolatilityStructureMaxSwapTenor(QlSwaptionVolatilityStructure* o, char **e) {
  try {
    return ret(new Period((*arg(o))->maxSwapTenor()));
  } catch (std::exception& er) {
    return handleException<Period*>(e, er);
  }
}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection1(QlSwaptionVolatilityStructure* o, int optionDate, Period* swapTenor, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection(Date(optionDate), (*arg(swapTenor)), extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
/* The following methods are not implemented in Swaption TS
QlSmileSection* qlSwaptionVolatilityStructureSmileSection2(QlSwaptionVolatilityStructure* o, double optionTime, Period* swapTenor, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection(optionTime, (*arg(swapTenor)), extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection3(QlSwaptionVolatilityStructure* o, Period* optionTenor, double swapLength, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection((*arg(optionTenor)), swapLength, extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection(Date(optionDate), swapLength, extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
*/
QlSmileSection* qlSwaptionVolatilityStructureSmileSection5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection(optionTime, swapLength, extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
QlSmileSection* qlSwaptionVolatilityStructureSmileSection(QlSwaptionVolatilityStructure* o, Period* optionTenor, Period* swapTenor, int extr, char **e) {
  try {
    return ret(new QlSmileSection(alloc((*arg(o))->smileSection((*arg(optionTenor)), (*arg(swapTenor)), extr))));
  } catch (std::exception& er) {
    return handleException<QlSmileSection*>(e, er);
  }
}
double qlSwaptionVolatilityStructureSwapLength1(QlSwaptionVolatilityStructure* o, int start, int end, char **e) {
  try {
    return (*arg(o))->swapLength(Date(start), Date(end));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureSwapLength(QlSwaptionVolatilityStructure* o, Period* swapTenor, char **e) {
  try {
    return (*arg(o))->swapLength((*arg(swapTenor)));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility1(QlSwaptionVolatilityStructure* o, int optionDate, Period* swapTenor, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility(Date(optionDate), (*arg(swapTenor)), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility2(QlSwaptionVolatilityStructure* o, double optionTime, Period* swapTenor, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility(optionTime, (*arg(swapTenor)), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility3(QlSwaptionVolatilityStructure* o, Period* optionTenor, double swapLength, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility((*arg(optionTenor)), swapLength, strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility4(QlSwaptionVolatilityStructure* o, int optionDate, double swapLength, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility(Date(optionDate), swapLength, strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility5(QlSwaptionVolatilityStructure* o, double optionTime, double swapLength, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility(optionTime, swapLength, strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwaptionVolatilityStructureVolatility(QlSwaptionVolatilityStructure* o, Period* optionTenor, Period* swapTenor, double strike, int extrapolate, char **e) {
  try {
    return (*arg(o))->volatility((*arg(optionTenor)), (*arg(swapTenor)), strike, extrapolate);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
