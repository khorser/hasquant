#include <ql/instruments/barrieroption.hpp>
#include <ql/instruments/vanillaoption.hpp>
#include <ql/instruments/swaption.hpp>
#include <ql/instruments/vanillaswingoption.hpp>
#include <ql/instruments/forwardvanillaoption.hpp>
#include <ql/instruments/dividendvanillaoption.hpp>
#include <ql/instruments/quantoforwardvanillaoption.hpp>
#include <ql/experimental/exoticoptions/margrabeoption.hpp>
#include <ql/experimental/exoticoptions/himalayaoption.hpp>
#include <ql/experimental/exoticoptions/pagodaoption.hpp>

#include "qlaux.h"

using namespace QuantLib;

void qlFreeBarrierOption(QlBarrierOption *o) { del(o); }
QlOneAssetOption* qlBarrierOptionAsOneAssetOption(QlBarrierOption *o) { return ret(new QlOneAssetOption(*arg(o))); }

void qlFreeDividendVanillaOption(QlDividendVanillaOption *o) { del(o); }
QlOneAssetOption* qlDividendVanillaOptionAsOneAssetOption(QlDividendVanillaOption *o) { return ret(new QlOneAssetOption(*arg(o))); }

void qlFreeForwardVanillaOption(QlForwardVanillaOption *o) { del(o); }
QlOneAssetOption* qlForwardVanillaOptionAsOneAssetOption(QlForwardVanillaOption *o) { return ret(new QlOneAssetOption(*arg(o))); }

void qlFreeMargrabeOption(QlMargrabeOption *o) { del(o); }
QlMultiAssetOption* qlMargrabeOptionAsMultiAssetOption(QlMargrabeOption *o) { return ret(new QlMultiAssetOption(*arg(o))); }

void qlFreeMultiAssetOption(QlMultiAssetOption *o) { del(o); }
QlOption* qlMultiAssetOptionAsOption(QlMultiAssetOption *o) { return ret(new QlOption(*arg(o))); }

void qlFreeOneAssetOption(QlOneAssetOption *o) { del(o); }
QlOption* qlOneAssetOptionAsOption(QlOneAssetOption *o) { return ret(new QlOption(*arg(o))); }

void qlFreeOption(QlOption *o) { del(o); }
QlInstrument* qlOptionAsInstrument(QlOption *o) { return ret(new QlInstrument(*arg(o))); }

void qlFreeQuantoVanillaOption(QlQuantoVanillaOption *o) { del(o); }
QlOneAssetOption* qlQuantoVanillaOptionAsOneAssetOption(QlQuantoVanillaOption *o) { return ret(new QlOneAssetOption(*arg(o))); }

void qlFreeSwaption(QlSwaption *o) { del(o); }
QlOption* qlSwaptionAsOption(QlSwaption *o) { return ret(new QlOption(*arg(o))); }

void qlFreeVanillaOption(QlVanillaOption *o) { del(o); }
QlOneAssetOption* qlVanillaOptionAsOneAssetOption(QlVanillaOption *o) { return ret(new QlOneAssetOption(*arg(o))); }

void qlFreeSwingExercise(QlSwingExercise *o) { del(o); }
QlBermudanExercise* qlSwingExerciseAsBermudanExercise(QlSwingExercise *o) { return ret(new QlBermudanExercise(*arg(o))); }

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
