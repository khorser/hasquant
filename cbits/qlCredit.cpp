#include <ql/experimental/credit/defaultprobabilitykey.hpp>
#include <ql/experimental/credit/issuer.hpp>
#include <ql/experimental/credit/pool.hpp>
#include <ql/experimental/credit/basket.hpp>
#include <ql/experimental/credit/gaussianlhplossmodel.hpp>
#include <ql/experimental/credit/syntheticcdo.hpp>
#include <ql/experimental/credit/nthtodefault.hpp>

#include "qlaux.h"
#include "qlCredit.h"
#include "qlTermStructureAux.h"

using namespace QuantLib;

extern "C" {

DefaultProbKey* qlNorthAmericaCorpDefaultKey(Currency* currency, int seniority, int graceFailureToPayLen, int graceFailureToPayUnit, double amountFailure, int restructuringType, char **e) {
  try {return new DefaultProbKey(NorthAmericaCorpDefaultKey(*arg(currency), (Seniority)seniority,
      Period(graceFailureToPayLen, (TimeUnit)graceFailureToPayUnit), amountFailure, (Restructuring::Type)restructuringType));
  } catch (std::exception& er) {return handleException<DefaultProbKey*>(e, er);}}
void qlFreeDefaultProbKey(DefaultProbKey *o) {del(o);}

Issuer* qlIssuer(unsigned probabilitiesLen, DefaultProbKey** keys, QlDefaultProbabilityTermStructure** curves, char **e) {
  try {
    std::vector<Issuer::key_curve_pair> probs;
    probs.reserve(probabilitiesLen);
    for (unsigned i = 0; i < probabilitiesLen; ++i)
      probs.emplace_back(*keys[i], Handle<DefaultProbabilityTermStructure>(*curves[i]));
    return new Issuer(probs);
  } catch (std::exception& er) {return handleException<Issuer*>(e, er);}}
void qlFreeIssuer(Issuer *o) {del(o);}

QlPool* qlPool(unsigned namesLen, char** names, Issuer** issuers, DefaultProbKey** keys, char **e) {
  try {
    auto p = allocShared(new Pool());
    for (unsigned i = 0; i < namesLen; ++i) p->add(names[i], *issuers[i], *keys[i]);
    return ret(new QlPool(p));
  } catch (std::exception& er) {return handleException<QlPool*>(e, er);}}
void qlFreePool(QlPool *o) {del(o);}

QlBasket* qlBasket(int refDate, unsigned namesLen, char** names, double* notionals, QlPool* pool, double attachmentRatio, double detachmentRatio, QlClaim* claim, QlDefaultLossModel* lossModel, char **e) {
  try {
    std::vector<std::string> nm(names, names + namesLen);
    auto b = allocShared(new Basket(Date(refDate), nm, std::vector<double>(notionals, notionals + namesLen),
        *arg(pool), attachmentRatio, detachmentRatio, *arg(claim)));
    b->setLossModel(*arg(lossModel));
    return ret(new QlBasket(b));
  } catch (std::exception& er) {return handleException<QlBasket*>(e, er);}}
void qlFreeBasket(QlBasket *o) {del(o);}
double qlBasketNotional(QlBasket* o, char **e) {
  try {return (*arg(o))->notional();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBasketExpectedTrancheLoss(QlBasket* o, int d, char **e) {
  try {return (*arg(o))->expectedTrancheLoss(Date(d));
  } catch (std::exception& er) {return handleException<double>(e, er);}}

QlBasket* qlDigitalBasket(int refDate, unsigned namesLen, char** names, double* notionals, QlPool* pool, double attachmentRatio, double detachmentRatio, QlClaim* claim, QlDefaultLossModel* lossModel, char **e) {
  return qlBasket(refDate, namesLen, names, notionals, pool, attachmentRatio, detachmentRatio, claim, lossModel, e);
}

QlDefaultLossModel* qlGaussianLHPLossModel(QlQuote* correlQuote, unsigned recoveriesLen, double* recoveries, char **e) {
  try {return ret(new QlDefaultLossModel(alloc(new GaussianLHPLossModel(*arg(correlQuote), std::vector<double>(recoveries, recoveries + recoveriesLen)))));
  } catch (std::exception& er) {return handleException<QlDefaultLossModel*>(e, er);}}
void qlFreeDefaultLossModel(QlDefaultLossModel *o) {del(o);}

QlSyntheticCDO* qlSyntheticCDO(QlBasket* basket, int side, Schedule* schedule, double upfrontRate, double runningRate, DayCounter* dayCounter, int paymentConvention, int haveNotional, double notional, char **e) {
  try {return ret(new QlSyntheticCDO(alloc(new SyntheticCDO(*arg(basket), (Protection::Side)side, *arg(schedule), upfrontRate, runningRate,
      *arg(dayCounter), (BusinessDayConvention)paymentConvention, haveNotional ? ext::optional<Real>(notional) : ext::nullopt))));
  } catch (std::exception& er) {return handleException<QlSyntheticCDO*>(e, er);}}
void qlFreeSyntheticCDO(QlSyntheticCDO *o) {del(o);}
QlInstrument* qlSyntheticCDOAsInstrument(QlSyntheticCDO *o) {return ret(new QlInstrument(*arg(o)));}
double qlSyntheticCDOFairPremium(QlSyntheticCDO* o, char **e) {
  try {return (*arg(o))->fairPremium();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSyntheticCDOFairUpfrontPremium(QlSyntheticCDO* o, char **e) {
  try {return (*arg(o))->fairUpfrontPremium();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSyntheticCDOPremiumValue(QlSyntheticCDO* o, char **e) {
  try {return (*arg(o))->premiumValue();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSyntheticCDOProtectionValue(QlSyntheticCDO* o, char **e) {
  try {return (*arg(o))->protectionValue();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSyntheticCDOPremiumLegNPV(QlSyntheticCDO* o, char **e) {
  try {return (*arg(o))->premiumLegNPV();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSyntheticCDOProtectionLegNPV(QlSyntheticCDO* o, char **e) {
  try {return (*arg(o))->protectionLegNPV();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSyntheticCDORemainingNotional(QlSyntheticCDO* o, char **e) {
  try {return (*arg(o))->remainingNotional();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSyntheticCDOImplicitCorrelation(QlSyntheticCDO* o, unsigned recoveriesLen, double* recoveries, QlYieldTermStructure* discountCurve, double targetNPV, double accuracy, char **e) {
  try {return (*arg(o))->implicitCorrelation(std::vector<double>(recoveries, recoveries + recoveriesLen), *arg(discountCurve), targetNPV, accuracy);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

QlDefaultLossModel* qlConstantLossModel(QlQuote* correlQuote, unsigned recoveriesLen, double* recoveries, int integralType, unsigned tOrdersLen, int* tOrders, char **e) {
  try {return ret(new QlDefaultLossModel(alloc(qlConstantLossModelAux(*arg(correlQuote),
      std::vector<double>(recoveries, recoveries + recoveriesLen),
      (LatentModelIntegrationType::LatentModelIntegrationType)integralType, recoveriesLen,
      std::vector<Integer>(tOrders, tOrders + tOrdersLen)))));
  } catch (std::exception& er) {return handleException<QlDefaultLossModel*>(e, er);}}

QlNthToDefault* qlNthToDefault(QlBasket* basket, unsigned n, int side, Schedule* premiumSchedule, double upfrontRate, double premiumRate, DayCounter* dayCounter, double nominal, int settlePremiumAccrual, char **e) {
  try {return ret(new QlNthToDefault(alloc(new NthToDefault(*arg(basket), n, (Protection::Side)side,
      *arg(premiumSchedule), upfrontRate, premiumRate, *arg(dayCounter), nominal, settlePremiumAccrual != 0))));
  } catch (std::exception& er) {return handleException<QlNthToDefault*>(e, er);}}
void qlFreeNthToDefault(QlNthToDefault *o) {del(o);}
QlInstrument* qlNthToDefaultAsInstrument(QlNthToDefault *o) {return ret(new QlInstrument(*arg(o)));}
double qlNthToDefaultFairPremium(QlNthToDefault* o, char **e) {
  try {return (*arg(o))->fairPremium();
  } catch (std::exception& er) {return handleException<double>(e, er);}}

}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
