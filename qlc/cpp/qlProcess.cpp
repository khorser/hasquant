#include <ql/processes/blackscholesprocess.hpp>

#include "qlaux.h"

using namespace QuantLib;

void qlFreeStochasticProcess1D(QlStochasticProcess1D *o) { del(o); }
QlStochasticProcess* qlStochasticProcess1DAsStochasticProcess(QlStochasticProcess1D *o) { return ret(new QlStochasticProcess(*arg(o))); }
void qlFreeBlackProcess(QlBlackProcess *o) { del(o); }
QlGeneralizedBlackScholesProcess* qlBlackProcessAsGeneralizedBlackScholesProcess(QlBlackProcess *o) { return ret(new QlGeneralizedBlackScholesProcess(*arg(o))); }
void qlFreeGeneralizedBlackScholesProcess(QlGeneralizedBlackScholesProcess *o) { del(o); }
QlStochasticProcess1D* qlGeneralizedBlackScholesProcessAsStochasticProcess1D(QlGeneralizedBlackScholesProcess *o) { return ret(new QlStochasticProcess1D(*arg(o))); }
void qlFreeStochasticProcess(QlStochasticProcess *o) { del(o); }

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
