#include <ql/instrument.hpp>
#include <ql/exercise.hpp>
#include <ql/payoff.hpp>
#include <ql/instruments/basketoption.hpp>
#include <ql/instruments/compositeinstrument.hpp>
#include <ql/instruments/stickyratchet.hpp>
#include <ql/instruments/forward.hpp>
#include <ql/instruments/vanillaswingoption.hpp>
#include <ql/instruments/capfloor.hpp>

#include "qlaux.h"
#include "qlInstrument.h"

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

void qlFreeInstrument(QlInstrument *instr) {
  del(instr);
}

QlInstrument* DLLEXPORT qlCompositeInstrument(unsigned instrLen, QlInstrument **instrs, double *coeff, char **e) {
  CompositeInstrument *ci = 0;
  try {
    ci = new CompositeInstrument();
    for (unsigned i = 0; i < instrLen; ++i)
        ci->add(*(instrs[i]), coeff[i]);
    return ret(new QlInstrument(alloc(ci)));
  } catch (std::exception& er) {
    delete ci;
    return handleException<QlInstrument*>(e, er);
  }
}

double qlInstrumentErrorEstimate(QlInstrument* o, char **e) {
  try {
    return (*arg(o))->errorEstimate();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
int qlInstrumentIsExpired(QlInstrument* o, char **e) {
  try {
    return (*arg(o))->isExpired();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlInstrumentValuationDate(QlInstrument* o, char **e) {
  try {
    return ((*arg(o))->valuationDate()).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

void qlFreePayoff(QlPayoff *o) { del(o); }

void qlFreeBasketPayoff(QlBasketPayoff *o) { del(o); }
QlPayoff* qlBasketPayoffAsPayoff(QlBasketPayoff *o) { return ret(new QlPayoff(*arg(o))); }

void qlFreeTypePayoff(QlTypePayoff *o) { del(o); }
QlPayoff* qlTypePayoffAsPayoff(QlTypePayoff *o) { return ret(new QlPayoff(*arg(o))); }

void qlFreeStrikedTypePayoff(QlStrikedTypePayoff *o) { del(o); }
QlTypePayoff* qlStrikedTypePayoffAsTypePayoff(QlStrikedTypePayoff *o) { return ret(new QlTypePayoff(*arg(o))); }

void qlFreePercentageStrikePayoff(QlPercentageStrikePayoff *o) { del(o); }
QlStrikedTypePayoff* qlPercentageStrikePayoffAsStrikedTypePayoff(QlPercentageStrikePayoff *o) { return ret(new QlStrikedTypePayoff(*arg(o))); }

void qlFreePlainVanillaPayoff(QlPlainVanillaPayoff *o) { del(o); }
QlStrikedTypePayoff* qlPlainVanillaPayoffAsStrikedTypePayoff(QlPlainVanillaPayoff *o) { return ret(new QlStrikedTypePayoff(*arg(o))); }

QlStrikedTypePayoff* qlAssetOrNothingPayoff(int type, double strike, char **e) {
  try {
    return ret(new QlStrikedTypePayoff(alloc(new AssetOrNothingPayoff((Option::Type)type, strike))));
  } catch (std::exception& er) {
    return handleException<QlStrikedTypePayoff*>(e, er);
  }
}
QlBasketPayoff* qlAverageBasketPayoff(QlPayoff* p, unsigned n, char **e) {
  try {
    return ret(new QlBasketPayoff(alloc(new AverageBasketPayoff(*arg(p), n))));
  } catch (std::exception& er) {
    return handleException<QlBasketPayoff*>(e, er);
  }
}
QlBasketPayoff* qlAverageBasketPayoff1(QlPayoff* p, unsigned aLen, double* a, char **e) {
  try {
    return ret(new QlBasketPayoff(alloc(new AverageBasketPayoff((*arg(p)), Array(a, a+aLen)))));
  } catch (std::exception& er) {
    return handleException<QlBasketPayoff*>(e, er);
  }
}
QlStrikedTypePayoff* qlCashOrNothingPayoff(int type, double strike, double cashPayoff, char **e) {
  try {
    return ret(new QlStrikedTypePayoff(alloc(new CashOrNothingPayoff((Option::Type)type, strike, cashPayoff))));
  } catch (std::exception& er) {
    return handleException<QlStrikedTypePayoff*>(e, er);
  }
}
QlPayoff* qlDoubleStickyRatchetPayoff(double type1, double type2, double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e) {
  try {
    return ret(new QlPayoff(alloc(new DoubleStickyRatchetPayoff(type1, type2, gearing1, gearing2, gearing3, spread1, spread2, spread3, initialValue1, initialValue2, accrualFactor))));
  } catch (std::exception& er) {
    return handleException<QlPayoff*>(e, er);
  }
}
QlTypePayoff* qlFloatingTypePayoff(int type, char **e) {
  try {
    return ret(new QlTypePayoff(alloc(new FloatingTypePayoff((Option::Type)type))));
  } catch (std::exception& er) {
    return handleException<QlTypePayoff*>(e, er);
  }
}
QlPayoff* qlForwardTypePayoff(int type, double strike, char **e) {
  try {
    return ret(new QlPayoff(alloc(new ForwardTypePayoff((Position::Type)type, strike))));
  } catch (std::exception& er) {
    return handleException<QlPayoff*>(e, er);
  }
}
QlStrikedTypePayoff* qlGapPayoff(int type, double strike, double secondStrike, char **e) {
  try {
    return ret(new QlStrikedTypePayoff(alloc(new GapPayoff((Option::Type)type, strike, secondStrike))));
  } catch (std::exception& er) {
    return handleException<QlStrikedTypePayoff*>(e, er);
  }
}
QlBasketPayoff* qlMaxBasketPayoff(QlPayoff* p, char **e) {
  try {
    return ret(new QlBasketPayoff(alloc(new MaxBasketPayoff(*arg(p)))));
  } catch (std::exception& er) {
    return handleException<QlBasketPayoff*>(e, er);
  }
}
QlBasketPayoff* qlMinBasketPayoff(QlPayoff* p, char **e) {
  try {
    return ret(new QlBasketPayoff(alloc(new MinBasketPayoff(*arg(p)))));
  } catch (std::exception& er) {
    return handleException<QlBasketPayoff*>(e, er);
  }
}
QlPercentageStrikePayoff* qlPercentageStrikePayoff(int type, double moneyness, char **e) {
  try {
    return ret(new QlPercentageStrikePayoff(alloc(new PercentageStrikePayoff((Option::Type)type, moneyness))));
  } catch (std::exception& er) {
    return handleException<QlPercentageStrikePayoff*>(e, er);
  }
}
QlPlainVanillaPayoff* qlPlainVanillaPayoff(int type, double strike, char **e) {
  try {
    return ret(new QlPlainVanillaPayoff(alloc(new PlainVanillaPayoff((Option::Type)type, strike))));
  } catch (std::exception& er) {
    return handleException<QlPlainVanillaPayoff*>(e, er);
  }
}
QlPayoff* qlRatchetMaxPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e) {
  try {
    return ret(new QlPayoff(alloc(new RatchetMaxPayoff(gearing1, gearing2, gearing3, spread1, spread2, spread3, initialValue1, initialValue2, accrualFactor))));
  } catch (std::exception& er) {
    return handleException<QlPayoff*>(e, er);
  }
}
QlPayoff* qlRatchetMinPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e) {
  try {
    return ret(new QlPayoff(alloc(new RatchetMinPayoff(gearing1, gearing2, gearing3, spread1, spread2, spread3, initialValue1, initialValue2, accrualFactor))));
  } catch (std::exception& er) {
    return handleException<QlPayoff*>(e, er);
  }
}
QlPayoff* qlRatchetPayoff(double gearing1, double gearing2, double spread1, double spread2, double initialValue, double accrualFactor, char **e) {
  try {
    return ret(new QlPayoff(alloc(new RatchetPayoff(gearing1, gearing2, spread1, spread2, initialValue, accrualFactor))));
  } catch (std::exception& er) {
    return handleException<QlPayoff*>(e, er);
  }
}
QlBasketPayoff* qlSpreadBasketPayoff(QlPayoff* p, char **e) {
  try {
    return ret(new QlBasketPayoff(alloc(new SpreadBasketPayoff((*arg(p))))));
  } catch (std::exception& er) {
    return handleException<QlBasketPayoff*>(e, er);
  }
}
QlPayoff* qlStickyMaxPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e) {
  try {
    return ret(new QlPayoff(alloc(new StickyMaxPayoff(gearing1, gearing2, gearing3, spread1, spread2, spread3, initialValue1, initialValue2, accrualFactor))));
  } catch (std::exception& er) {
    return handleException<QlPayoff*>(e, er);
  }
}
QlPayoff* qlStickyMinPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e) {
  try {
    return ret(new QlPayoff(alloc(new StickyMinPayoff(gearing1, gearing2, gearing3, spread1, spread2, spread3, initialValue1, initialValue2, accrualFactor))));
  } catch (std::exception& er) {
    return handleException<QlPayoff*>(e, er);
  }
}
QlPayoff* qlStickyPayoff(double gearing1, double gearing2, double spread1, double spread2, double initialValue, double accrualFactor, char **e) {
  try {
    return ret(new QlPayoff(alloc(new StickyPayoff(gearing1, gearing2, spread1, spread2, initialValue, accrualFactor))));
  } catch (std::exception& er) {
    return handleException<QlPayoff*>(e, er);
  }
}
QlStrikedTypePayoff* qlSuperFundPayoff(double strike, double secondStrike, char **e) {
  try {
    return ret(new QlStrikedTypePayoff(alloc(new SuperFundPayoff(strike, secondStrike))));
  } catch (std::exception& er) {
    return handleException<QlStrikedTypePayoff*>(e, er);
  }
}
QlStrikedTypePayoff* qlSuperSharePayoff(double strike, double secondStrike, double cashPayoff, char **e) {
  try {
    return ret(new QlStrikedTypePayoff(alloc(new SuperSharePayoff(strike, secondStrike, cashPayoff))));
  } catch (std::exception& er) {
    return handleException<QlStrikedTypePayoff*>(e, er);
  }
}
void qlFreeAmericanExercise(QlAmericanExercise *o) { del(o); }
QlExercise* qlAmericanExerciseAsExercise(QlAmericanExercise *o) { return ret(new QlExercise(*arg(o))); }
void qlFreeBermudanExercise(QlBermudanExercise *o) { del(o); }
QlExercise* qlBermudanExerciseAsExercise(QlBermudanExercise *o) { return ret(new QlExercise(*arg(o))); }
void qlFreeEuropeanExercise(QlEuropeanExercise *o) { del(o); }
QlExercise* qlEuropeanExerciseAsExercise(QlEuropeanExercise *o) { return ret(new QlExercise(*arg(o))); }
void qlFreeExercise(QlExercise *o) { del(o); }

QlAmericanExercise* qlAmericanExercise(int earliestDate, int latestDate, int payoffAtExpiry, char **e) {
  try {
    return ret(new QlAmericanExercise(alloc(new AmericanExercise(Date(earliestDate), Date(latestDate), payoffAtExpiry))));
  } catch (std::exception& er) {
    return handleException<QlAmericanExercise*>(e, er);
  }
}
QlBermudanExercise* qlBermudanExercise(unsigned datesLen, int *dates, int payoffAtExpiry, char **e) {
  try {
    return ret(new QlBermudanExercise(alloc(new BermudanExercise(qlDateVector(datesLen, dates), payoffAtExpiry))));
  } catch (std::exception& er) {
    return handleException<QlBermudanExercise*>(e, er);
  }
}
QlExercise* qlEarlyExercise(int type, int payoffAtExpiry, char **e) {
  try {
    return ret(new QlExercise(alloc(new EarlyExercise((Exercise::Type)type, payoffAtExpiry))));
  } catch (std::exception& er) {
    return handleException<QlExercise*>(e, er);
  }
}
QlExercise* qlExercise(int type, char **e) {
  try {
    return ret(new QlExercise(alloc(new Exercise((Exercise::Type)type))));
  } catch (std::exception& er) {
    return handleException<QlExercise*>(e, er);
  }
}

QlEuropeanExercise* qlEuropeanExercise(int date, char **e) {
  try {
    return ret(new QlEuropeanExercise(alloc(new EuropeanExercise(Date(date)))));
  } catch (std::exception& er) {
    return handleException<QlEuropeanExercise*>(e, er);
  }
}

QlSwingExercise* qlSwingExercise(unsigned datesLen, int* dates, unsigned* seconds, char **e) {
  try {
    std::vector<Size> secs; // on x86-64 sizeof(size_t) might be greater than sizeof(unsigned)
    std::copy(seconds, seconds+datesLen, secs.begin());
    return ret(new QlSwingExercise(alloc(new SwingExercise(qlDateVector(datesLen, dates), secs))));
  } catch (std::exception& er) {
    return handleException<QlSwingExercise*>(e, er);
  }
}

QlSwingExercise* qlSwingExercise1(int from, int to, unsigned stepSizeSecs, char **e) {
  try {
    return ret(new QlSwingExercise(alloc(new SwingExercise(Date(from), Date(to), stepSizeSecs))));
  } catch (std::exception& er) {
    return handleException<QlSwingExercise*>(e, er);
  }
}

QlAmericanExercise* qlAmericanExercise1(int latestDate, int payoffAtExpiry, char **e) {
  try {
    return ret(new QlAmericanExercise(alloc(new AmericanExercise(Date(latestDate), payoffAtExpiry))));
  } catch (std::exception& er) {
    return handleException<QlAmericanExercise*>(e, er);
  }
}

void qlFreeCapFloor(QlCapFloor *o) { del(o); }
QlInstrument* qlCapFloorAsInstrument(QlCapFloor *o) { return ret(new QlInstrument(*arg(o))); }

QlCapFloor* qlCap(Leg* floatingLeg, unsigned exerciseRatesLen, double* exerciseRates, char **e) {
  try {
    return ret(new QlCapFloor(alloc(new Cap(*arg(floatingLeg), std::vector<double>(exerciseRates, exerciseRates+exerciseRatesLen)))));
  } catch (std::exception& er) {
    return handleException<QlCapFloor*>(e, er);
  }
}
QlCapFloor* qlCollar(Leg* floatingLeg, unsigned capRatesLen, double* capRates, unsigned floorRatesLen, double* floorRates, char **e) {
  try {
    return ret(new QlCapFloor(alloc(new Collar(*arg(floatingLeg), std::vector<double>(capRates, capRates+capRatesLen), std::vector<double>(floorRates, floorRates+floorRatesLen)))));
  } catch (std::exception& er) {
    return handleException<QlCapFloor*>(e, er);
  }
}
QlCapFloor* qlFloor(Leg* floatingLeg, unsigned exerciseRatesLen, double* exerciseRates, char **e) {
  try {
    return ret(new QlCapFloor(alloc(new Floor(*arg(floatingLeg), std::vector<double>(exerciseRates, exerciseRates+exerciseRatesLen)))));
  } catch (std::exception& er) {
    return handleException<QlCapFloor*>(e, er);
  }
}
double qlCapFloorAtmRate(QlCapFloor* o, QlYieldTermStructure* discountCurve, char **e) {
  try {
    return (*arg(o))->atmRate(**arg(discountCurve));
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlCapFloorImpliedVolatility(QlCapFloor* o, double price, QlYieldTermStructure* disc, double guess, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e) {
  try {
    return (*arg(o))->impliedVolatility(price, Handle<YieldTermStructure>(*arg(disc)), guess, accuracy, maxEvaluations, minVol, maxVol);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
QlCapFloor* qlCapFloorOptionlet(QlCapFloor* o, unsigned n, char **e) {
  try {
    return ret(new QlCapFloor(alloc((*arg(o))->optionlet(n))));
  } catch (std::exception& er) {
    return handleException<QlCapFloor*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
