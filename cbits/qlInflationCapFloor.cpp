#include <ql/instruments/inflationcapfloor.hpp>
#include <ql/instruments/cpicapfloor.hpp>
#include "qlaux.h"
using namespace QuantLib;
#include "qlInflationCapFloor.h"

void qlFreeYoYInflationCapFloor(QlYoYInflationCapFloor *o) {del(o);}
QlInstrument *qlYoYInflationCapFloorAsInstrument(QlYoYInflationCapFloor *o) {return ret(new QlInstrument(*arg(o)));}

QlYoYInflationCapFloor *qlYoYInflationCap(Leg *yoyLeg, unsigned exerciseRatesLen, double *exerciseRates, char **e) {
  try {return ret(new QlYoYInflationCapFloor(alloc(new YoYInflationCapFloor(YoYInflationCapFloor::Cap, *arg(yoyLeg),
      std::vector<double>(exerciseRates, exerciseRates+exerciseRatesLen), std::vector<double>()))));
  } catch (std::exception& er) {return handleException<QlYoYInflationCapFloor*>(e, er);}}

QlYoYInflationCapFloor *qlYoYInflationFloor(Leg *yoyLeg, unsigned exerciseRatesLen, double *exerciseRates, char **e) {
  try {return ret(new QlYoYInflationCapFloor(alloc(new YoYInflationCapFloor(YoYInflationCapFloor::Floor, *arg(yoyLeg),
      std::vector<double>(), std::vector<double>(exerciseRates, exerciseRates+exerciseRatesLen)))));
  } catch (std::exception& er) {return handleException<QlYoYInflationCapFloor*>(e, er);}}

QlYoYInflationCapFloor *qlYoYInflationCollar(Leg *yoyLeg, unsigned capRatesLen, double *capRates,
    unsigned floorRatesLen, double *floorRates, char **e) {
  try {return ret(new QlYoYInflationCapFloor(alloc(new YoYInflationCapFloor(YoYInflationCapFloor::Collar, *arg(yoyLeg),
      std::vector<double>(capRates, capRates+capRatesLen), std::vector<double>(floorRates, floorRates+floorRatesLen)))));
  } catch (std::exception& er) {return handleException<QlYoYInflationCapFloor*>(e, er);}}

// atmRate takes a plain YieldTermStructure& (not a Handle), same reasoning as qlCapFloorAtmRate.
double qlYoYInflationCapFloorAtmRate(QlYoYInflationCapFloor *o, QlYieldTermStructure *discountCurve, char **e) {
  try {return (*arg(o))->atmRate(handleRef(arg(discountCurve)));
  } catch (std::exception& er) {return handleException<double>(e, er);}}

QlYoYInflationCapFloor *qlYoYInflationCapFloorOptionlet(QlYoYInflationCapFloor *o, unsigned n, char **e) {
  try {return ret(new QlYoYInflationCapFloor(alloc((*arg(o))->optionlet(n))));
  } catch (std::exception& er) {return handleException<QlYoYInflationCapFloor*>(e, er);}}

void qlFreeCPICapFloor(QlCPICapFloor *o) {del(o);}
QlInstrument *qlCPICapFloorAsInstrument(QlCPICapFloor *o) {return ret(new QlInstrument(*arg(o)));}

QlCPICapFloor *qlCPICapFloor(int type, double nominal, int startDate, double baseCPI, int maturity,
    Calendar *fixCalendar, int fixConvention, Calendar *payCalendar, int payConvention, double strike,
    QlZeroInflationIndex *index, int observationLagLen, int observationLagUnit, int observationInterpolation,
    char **e) {
  try {return ret(new QlCPICapFloor(alloc(new CPICapFloor((Option::Type)type, nominal, Date(startDate), baseCPI,
      Date(maturity), *arg(fixCalendar), (BusinessDayConvention)fixConvention, *arg(payCalendar),
      (BusinessDayConvention)payConvention, strike, *arg(index),
      Period(observationLagLen, (TimeUnit)observationLagUnit), (CPI::InterpolationType)observationInterpolation))));
  } catch (std::exception& er) {return handleException<QlCPICapFloor*>(e, er);}}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
