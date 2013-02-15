#include <ql/instrument.hpp>
#include <ql/instruments/vanillaswap.hpp>
#include <ql/instruments/bmaswap.hpp>
#include <ql/instruments/overnightindexedswap.hpp>
#include <ql/instruments/assetswap.hpp>

#include "qlaux.h"

using namespace QuantLib;

void qlFreeSwap(QlSwap *o) { del(o); }
QlInstrument* qlSwapAsInstrument(QlSwap *o) { return ret(new QlInstrument(*arg(o))); }

void qlFreeVanillaSwap(QlVanillaSwap *o) { del(o); }
QlSwap* qlVanillaSwapAsSwap(QlVanillaSwap *o) { return ret(new QlSwap(*arg(o))); }

void qlFreeBMASwap(QlBMASwap *o) { del(o); }
QlSwap* qlBMASwapAsSwap(QlBMASwap *o) { return ret(new QlSwap(*arg(o))); }

void qlFreeOvernightIndexedSwap(QlOvernightIndexedSwap *o) { del(o); }
QlSwap* qlOvernightIndexedSwapAsSwap(QlOvernightIndexedSwap *o) { return ret(new QlSwap(*arg(o))); }

QlSwap* qlSwap1(unsigned legsLen, Leg** legs, int *payer, char **e) {
  try {
    return ret(new QlSwap(alloc(new Swap(qlBuildVector(legs, legsLen), std::vector<bool>(payer, payer+legsLen)))));
  } catch (std::exception& er) {
    return handleException<QlSwap*>(e, er);
  }
}

void qlFreeAssetSwap(QlAssetSwap *o) { del(o); }
QlSwap* qlAssetSwapAsSwap(QlAssetSwap *o) { return ret(new QlSwap(*arg(o))); }

QlAssetSwap* qlAssetSwap1(int parAssetSwap, QlBond* bond, double bondCleanPrice, double nonParRepayment, double gearing, QlIborIndex* iborIndex, double spread, DayCounter* floatingDayCount, int dealMaturity, int payBondCoupon, char **e) {
  try {
    return ret(new QlAssetSwap(alloc(new AssetSwap(parAssetSwap, (*arg(bond)), bondCleanPrice, nonParRepayment, gearing, (*arg(iborIndex)), spread, (*arg(floatingDayCount)), qlNullableDate(dealMaturity), payBondCoupon))));
  } catch (std::exception& er) {
    return handleException<QlAssetSwap*>(e, er);
  }
}
QlAssetSwap* qlAssetSwap(int payBondCoupon, QlBond* bond, double bondCleanPrice, QlIborIndex* iborIndex, double spread, Schedule* floatSchedule, DayCounter* floatingDayCount, int parAssetSwap, char **e) {
  try {
    return ret(new QlAssetSwap(alloc(new AssetSwap(payBondCoupon, (*arg(bond)), bondCleanPrice, (*arg(iborIndex)), spread, (*arg(floatSchedule)), (*arg(floatingDayCount)), parAssetSwap))));
  } catch (std::exception& er) {
    return handleException<QlAssetSwap*>(e, er);
  }
}
QlBMASwap* qlBMASwap(int type, double nominal, Schedule* liborSchedule, double liborFraction, double liborSpread, QlIborIndex* liborIndex, DayCounter* liborDayCount, Schedule* bmaSchedule, QlBMAIndex* bmaIndex, DayCounter* bmaDayCount, char **e) {
  try {
    return ret(new QlBMASwap(alloc(new BMASwap((BMASwap::Type)type, nominal, (*arg(liborSchedule)), liborFraction, liborSpread, (*arg(liborIndex)), (*arg(liborDayCount)), (*arg(bmaSchedule)), (*arg(bmaIndex)), (*arg(bmaDayCount))))));
  } catch (std::exception& er) {
    return handleException<QlBMASwap*>(e, er);
  }
}
QlVanillaSwap* qlVanillaSwap(int type, double nominal, Schedule* fixedSchedule, double fixedRate, DayCounter* fixedDayCount, Schedule* floatSchedule, QlIborIndex* iborIndex, double spread, DayCounter* floatingDayCount, int paymentConvention, char **e) {
  try {
    return ret(new QlVanillaSwap(alloc(new VanillaSwap((VanillaSwap::Type)type, nominal, (*arg(fixedSchedule)), fixedRate, (*arg(fixedDayCount)), (*arg(floatSchedule)), (*arg(iborIndex)), spread, (*arg(floatingDayCount)), (BusinessDayConvention)paymentConvention))));
  } catch (std::exception& er) {
    return handleException<QlVanillaSwap*>(e, er);
  }
}

QlSwap* qlSwap(Leg* firstLeg, Leg* secondLeg, char **e) {
  try {
    return ret(new QlSwap(alloc(new Swap((*arg(firstLeg)), (*arg(secondLeg))))));
  } catch (std::exception& er) {
    return handleException<QlSwap*>(e, er);
  }
}
/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
