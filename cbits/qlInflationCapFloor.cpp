#include <ql/instruments/inflationcapfloor.hpp>
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

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
