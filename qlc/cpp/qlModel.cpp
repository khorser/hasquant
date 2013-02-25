#include <ql/models/all.hpp>
#include <ql/legacy/libormarketmodels/liborforwardmodel.hpp>

#include "qlaux.h"

using namespace QuantLib;

void qlFreeGJRGARCHModel(QlGJRGARCHModel *o) { del(o); }
void qlFreeHestonModel(QlHestonModel *o) { del(o); }
void qlFreeBatesModel(QlBatesModel *o) { del(o); }
void qlFreePiecewiseTimeDependentHestonModel(QlPiecewiseTimeDependentHestonModel *o) { del(o); }
void qlFreeShortRateModel(QlShortRateModel *o) { del(o); }
void qlFreeAffineModel(QlAffineModel *o) { del(o); }
void qlFreeOneFactorAffineModel(QlOneFactorAffineModel *o) { del(o); }
QlAffineModel* qlOneFactorAffineModelAsAffineModel(QlOneFactorAffineModel *o) { return ret(new QlAffineModel(*arg(o))); }
void qlFreeLiborForwardModel(QlLiborForwardModel *o) { del(o); }
QlAffineModel* qlLiborForwardModelAsAffineModel(QlLiborForwardModel *o) { return ret(new QlAffineModel(*arg(o))); }
void qlFreeHullWhite(QlHullWhite *o) { del(o); }
QlOneFactorAffineModel* qlHullWhiteAsOneFactorAffineModel(QlHullWhite *o) { return ret(new QlOneFactorAffineModel(*arg(o))); }

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
