#include <ql/instrument.hpp>
#include <ql/instruments/vanillaswap.hpp>

#include "qlaux.h"

using namespace QuantLib;

void qlFreeSwap(QlSwap *o) { del(o); }
QlInstrument* qlSwapAsInstrument(QlSwap *o) { return ret(new QlInstrument(*arg(o))); }

void qlFreeVanillaSwap(QlVanillaSwap *o) { del(o); }
QlSwap* qlVanillaSwapAsSwap(QlVanillaSwap *o) { return ret(new QlSwap(*arg(o))); }

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
