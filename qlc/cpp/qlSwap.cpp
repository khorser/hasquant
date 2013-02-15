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

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
