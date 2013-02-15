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

double qlSwapEndDiscounts(QlSwap* o, unsigned j, char **e) {
  try {
    return (*arg(o))->endDiscounts(j);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
Leg* qlSwapLeg(QlSwap* o, unsigned j, char **e) {
  try {
    return ret(new Leg((*arg(o))->leg(j)));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
double qlSwapLegBPS(QlSwap* o, unsigned j, char **e) {
  try {
    return (*arg(o))->legBPS(j);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlSwapLegNPV(QlSwap* o, unsigned j, char **e) {
  try {
    return (*arg(o))->legNPV(j);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
int qlSwapMaturityDate(QlSwap* o, char **e) {
  try {
    return ((*arg(o))->maturityDate()).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlSwapNpvDateDiscount(QlSwap* o, char **e) {
  try {
    return (*arg(o))->npvDateDiscount();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
int qlSwapStartDate(QlSwap* o, char **e) {
  try {
    return ((*arg(o))->startDate()).serialNumber();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
double qlSwapStartDiscounts(QlSwap* o, unsigned j, char **e) {
  try {
    return (*arg(o))->startDiscounts(j);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlVanillaSwapFairRate(QlVanillaSwap* o, char **e) {
  try {
    return (*arg(o))->fairRate();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlVanillaSwapFairSpread(QlVanillaSwap* o, char **e) {
  try {
    return (*arg(o))->fairSpread();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
Leg* qlVanillaSwapFixedLeg(QlVanillaSwap* o, char **e) {
  try {
    return ret(new Leg((*arg(o))->fixedLeg()));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
double qlVanillaSwapFixedLegBPS(QlVanillaSwap* o, char **e) {
  try {
    return (*arg(o))->fixedLegBPS();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlVanillaSwapFixedLegNPV(QlVanillaSwap* o, char **e) {
  try {
    return (*arg(o))->fixedLegNPV();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
Leg* qlVanillaSwapFloatingLeg(QlVanillaSwap* o, char **e) {
  try {
    return ret(new Leg((*arg(o))->floatingLeg()));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
double qlVanillaSwapFloatingLegBPS(QlVanillaSwap* o, char **e) {
  try {
    return (*arg(o))->floatingLegBPS();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlVanillaSwapFloatingLegNPV(QlVanillaSwap* o, char **e) {
  try {
    return (*arg(o))->floatingLegNPV();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

QlOvernightIndexedSwap* qlOvernightIndexedSwap(int type, double nominal, Schedule* schedule, double fixedRate, DayCounter* fixedDC, QlOvernightIndex* overnightIndex, double spread, char **e) {
  try {
    return ret(new QlOvernightIndexedSwap(alloc(new OvernightIndexedSwap((OvernightIndexedSwap::Type)type, nominal, (*arg(schedule)), fixedRate, (*arg(fixedDC)), (*arg(overnightIndex)), spread))));
  } catch (std::exception& er) {
    return handleException<QlOvernightIndexedSwap*>(e, er);
  }
}

QlOvernightIndexedSwap* qlOvernightIndexedSwap1(int type, unsigned nominalsLen, double* nominals, Schedule* schedule, double fixedRate, DayCounter* fixedDC, QlOvernightIndex* overnightIndex, double spread, char **e) {
  try {
    return ret(new QlOvernightIndexedSwap(alloc(new OvernightIndexedSwap((OvernightIndexedSwap::Type)type, std::vector<double>(nominals, nominals+nominalsLen), (*arg(schedule)), fixedRate, (*arg(fixedDC)), (*arg(overnightIndex)), spread))));
  } catch (std::exception& er) {
    return handleException<QlOvernightIndexedSwap*>(e, er);
  }
}
Leg* qlAssetSwapBondLeg(QlAssetSwap* o, char **e) {
  try {
    return ret(new Leg((*arg(o))->bondLeg()));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
double qlAssetSwapCleanPrice(QlAssetSwap* o, char **e) {
  try {
    return (*arg(o))->cleanPrice();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlAssetSwapFairCleanPrice(QlAssetSwap* o, char **e) {
  try {
    return (*arg(o))->fairCleanPrice();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlAssetSwapFairNonParRepayment(QlAssetSwap* o, char **e) {
  try {
    return (*arg(o))->fairNonParRepayment();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlAssetSwapFairSpread(QlAssetSwap* o, char **e) {
  try {
    return (*arg(o))->fairSpread();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
Leg* qlAssetSwapFloatingLeg(QlAssetSwap* o, char **e) {
  try {
    return ret(new Leg((*arg(o))->floatingLeg()));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
double qlAssetSwapFloatingLegBPS(QlAssetSwap* o, char **e) {
  try {
    return (*arg(o))->floatingLegBPS();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlAssetSwapFloatingLegNPV(QlAssetSwap* o, char **e) {
  try {
    return (*arg(o))->floatingLegNPV();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlAssetSwapNonParRepayment(QlAssetSwap* o, char **e) {
  try {
    return (*arg(o))->nonParRepayment();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
int qlAssetSwapParSwap(QlAssetSwap* o, char **e) {
  try {
    return (*arg(o))->parSwap();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
int qlAssetSwapPayBondCoupon(QlAssetSwap* o, char **e) {
  try {
    return (*arg(o))->payBondCoupon();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}
Leg* qlBMASwapBmaLeg(QlBMASwap* o, char **e) {
  try {
    return ret(new Leg((*arg(o))->bmaLeg()));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
double qlBMASwapBmaLegBPS(QlBMASwap* o, char **e) {
  try {
    return (*arg(o))->bmaLegBPS();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBMASwapBmaLegNPV(QlBMASwap* o, char **e) {
  try {
    return (*arg(o))->bmaLegNPV();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBMASwapFairLiborFraction(QlBMASwap* o, char **e) {
  try {
    return (*arg(o))->fairLiborFraction();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBMASwapFairLiborSpread(QlBMASwap* o, char **e) {
  try {
    return (*arg(o))->fairLiborSpread();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBMASwapLiborFraction(QlBMASwap* o, char **e) {
  try {
    return (*arg(o))->liborFraction();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
Leg* qlBMASwapLiborLeg(QlBMASwap* o, char **e) {
  try {
    return ret(new Leg((*arg(o))->liborLeg()));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
double qlBMASwapLiborLegBPS(QlBMASwap* o, char **e) {
  try {
    return (*arg(o))->liborLegBPS();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBMASwapLiborLegNPV(QlBMASwap* o, char **e) {
  try {
    return (*arg(o))->liborLegNPV();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlOvernightIndexedSwapFairRate(QlOvernightIndexedSwap* o, char **e) {
  try {
    return (*arg(o))->fairRate();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlOvernightIndexedSwapFairSpread(QlOvernightIndexedSwap* o, char **e) {
  try {
    return (*arg(o))->fairSpread();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
Leg* qlOvernightIndexedSwapFixedLeg(QlOvernightIndexedSwap* o, char **e) {
  try {
    return ret(new Leg((*arg(o))->fixedLeg()));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
double qlOvernightIndexedSwapFixedLegBPS(QlOvernightIndexedSwap* o, char **e) {
  try {
    return (*arg(o))->fixedLegBPS();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlOvernightIndexedSwapFixedLegNPV(QlOvernightIndexedSwap* o, char **e) {
  try {
    return (*arg(o))->fixedLegNPV();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
Leg* qlOvernightIndexedSwapOvernightLeg(QlOvernightIndexedSwap* o, char **e) {
  try {
    return ret(new Leg((*arg(o))->overnightLeg()));
  } catch (std::exception& er) {
    return handleException<Leg*>(e, er);
  }
}
double qlOvernightIndexedSwapOvernightLegBPS(QlOvernightIndexedSwap* o, char **e) {
  try {
    return (*arg(o))->overnightLegBPS();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlOvernightIndexedSwapOvernightLegNPV(QlOvernightIndexedSwap* o, char **e) {
  try {
    return (*arg(o))->overnightLegNPV();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
