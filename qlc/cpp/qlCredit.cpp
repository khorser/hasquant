#include <ql/experimental/credit/cdsoption.hpp>

#include "qlaux.h"

using namespace QuantLib;

void qlFreeCdsOption(QlCdsOption *o) { del(o); }
QlOption* qlCdsOptionAsOption(QlCdsOption *o) { return ret(new QlOption(*arg(o))); }

void qlFreeCreditDefaultSwap(QlCreditDefaultSwap *o) { del(o); }
QlInstrument* qlCreditDefaultSwapAsInstrument(QlCreditDefaultSwap *o) { return ret(new QlInstrument(*arg(o))); }

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
