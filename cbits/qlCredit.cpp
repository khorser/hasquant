#include <ql/experimental/credit/defaultprobabilitykey.hpp>
#include <ql/experimental/credit/issuer.hpp>
#include <ql/experimental/credit/pool.hpp>
#include <ql/experimental/credit/basket.hpp>
#include <ql/experimental/credit/gaussianlhplossmodel.hpp>

#include "qlaux.h"
#include "qlCredit.h"

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

QlDefaultLossModel* qlGaussianLHPLossModel(QlQuote* correlQuote, unsigned recoveriesLen, double* recoveries, char **e) {
  try {return ret(new QlDefaultLossModel(alloc(new GaussianLHPLossModel(*arg(correlQuote), std::vector<double>(recoveries, recoveries + recoveriesLen)))));
  } catch (std::exception& er) {return handleException<QlDefaultLossModel*>(e, er);}}
void qlFreeDefaultLossModel(QlDefaultLossModel *o) {del(o);}

}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
