#include <ql/models/all.hpp>
#include <ql/legacy/libormarketmodels/liborforwardmodel.hpp>
#include <ql/experimental/shortrate/generalizedhullwhite.hpp>
#include <ql/experimental/variancegamma/variancegammamodel.hpp>

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

void qlFreeCalibratedModel(QlCalibratedModel *o) { del(o); }

QlBatesModel* qlBatesModel(QlBatesProcess* process, char **e) {
  try {
    return ret(new QlBatesModel(alloc(new BatesModel((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlBatesModel*>(e, er);
  }
}
QlShortRateModel* qlBlackKarasinski(QlYieldTermStructure* termStructure, double a, double sigma, char **e) {
  try {
    return ret(new QlShortRateModel(alloc(new BlackKarasinski(Handle<YieldTermStructure>(*arg(termStructure)), a, sigma))));
  } catch (std::exception& er) {
    return handleException<QlShortRateModel*>(e, er);
  }
}
QlOneFactorAffineModel* qlCoxIngersollRoss(double r0, double theta, double k, double sigma, char **e) {
  try {
    return ret(new QlOneFactorAffineModel(alloc(new CoxIngersollRoss(r0, theta, k, sigma))));
  } catch (std::exception& er) {
    return handleException<QlOneFactorAffineModel*>(e, er);
  }
}
QlOneFactorAffineModel* qlExtendedCoxIngersollRoss(QlYieldTermStructure* termStructure, double theta, double k, double sigma, double x0, char **e) {
  try {
    return ret(new QlOneFactorAffineModel(alloc(new ExtendedCoxIngersollRoss(Handle<YieldTermStructure>(*arg(termStructure)), theta, k, sigma, x0))));
  } catch (std::exception& er) {
    return handleException<QlOneFactorAffineModel*>(e, er);
  }
}
QlG2* qlG2(QlYieldTermStructure* termStructure, double a, double sigma, double b, double eta, double rho, char **e) {
  try {
    return ret(new QlG2(alloc(new G2(Handle<YieldTermStructure>(*arg(termStructure)), a, sigma, b, eta, rho))));
  } catch (std::exception& er) {
    return handleException<QlG2*>(e, er);
  }
}
QlShortRateModel* qlGeneralizedHullWhite1(QlYieldTermStructure* yieldtermStructure, unsigned speedstructureLen, int* speedstructure, unsigned volstructureLen, int* volstructure, unsigned speedLen, double* speed, unsigned volLen, double* vol, char **e) {
  try {
    return ret(new QlShortRateModel(alloc(new GeneralizedHullWhite(Handle<YieldTermStructure>(*arg(yieldtermStructure)), qlDateVector(speedstructureLen, speedstructure), qlDateVector(volstructureLen, volstructure), std::vector<double>(speed, speed+speedLen), std::vector<double>(vol, vol+volLen)))));
  } catch (std::exception& er) {
    return handleException<QlShortRateModel*>(e, er);
  }
}
QlShortRateModel* qlGeneralizedHullWhite(QlYieldTermStructure* yieldtermStructure, unsigned speedstructureLen, int* speedstructure, unsigned volstructureLen, int* volstructure, char **e) {
  try {
    return ret(new QlShortRateModel(alloc(new GeneralizedHullWhite(Handle<YieldTermStructure>(*arg(yieldtermStructure)), qlDateVector(speedstructureLen, speedstructure), qlDateVector(volstructureLen, volstructure)))));
  } catch (std::exception& er) {
    return handleException<QlShortRateModel*>(e, er);
  }
}
QlGJRGARCHModel* qlGJRGARCHModel(QlGJRGARCHProcess* process, char **e) {
  try {
    return ret(new QlGJRGARCHModel(alloc(new GJRGARCHModel((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlGJRGARCHModel*>(e, er);
  }
}
QlHestonModel* qlHestonModel(QlHestonProcess* process, char **e) {
  try {
    return ret(new QlHestonModel(alloc(new HestonModel((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlHestonModel*>(e, er);
  }
}
QlHullWhite* qlHullWhite(QlYieldTermStructure* termStructure, double a, double sigma, char **e) {
  try {
    return ret(new QlHullWhite(alloc(new HullWhite(Handle<YieldTermStructure>(*arg(termStructure)), a, sigma))));
  } catch (std::exception& er) {
    return handleException<QlHullWhite*>(e, er);
  }
}
QlCalibratedModel* qlVarianceGammaModel(QlVarianceGammaProcess* process, char **e) {
  try {
    return ret(new QlCalibratedModel(alloc(new VarianceGammaModel((*arg(process))))));
  } catch (std::exception& er) {
    return handleException<QlCalibratedModel*>(e, er);
  }
}
QlOneFactorAffineModel* qlVasicek(double r0, double a, double b, double sigma, double lambda, char **e) {
  try {
    return ret(new QlOneFactorAffineModel(alloc(new Vasicek(r0, a, b, sigma, lambda))));
  } catch (std::exception& er) {
    return handleException<QlOneFactorAffineModel*>(e, er);
  }
}

void qlFreeG2(QlG2 *o) { del(o); }
QlAffineModel* qlG2AsAffineModel(QlG2 *o) { return ret(new QlAffineModel(*arg(o))); }

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
