#include <ql/pricingengines/vanilla/binomialengine.hpp>
#include <ql/experimental/lattices/extendedbinomialtree.hpp>
#include <ql/experimental/convertiblebonds/binomialconvertibleengine.hpp>

#include "qlPricingEngineAux.h"

using namespace QuantLib;

PricingEngine* qlBinomialVanillaEngineAux(const char *tree, const boost::shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps) {
  if (!strcmp(tree, "JarrowRudd"))
    return new BinomialVanillaEngine<JarrowRudd>(process, timeSteps);
  else if (!strcmp(tree, "CoxRossRubinstein"))
    return new BinomialVanillaEngine<CoxRossRubinstein>(process, timeSteps);
  else if (!strcmp(tree, "AdditiveEQPBinomialTree"))
    return new BinomialVanillaEngine<AdditiveEQPBinomialTree>(process, timeSteps);
  else if (!strcmp(tree, "Trigeorgis"))
    return new BinomialVanillaEngine<Trigeorgis>(process, timeSteps);
  else if (!strcmp(tree, "Tian"))
    return new BinomialVanillaEngine<Tian>(process, timeSteps);
  else if (!strcmp(tree, "LeisenReimer"))
    return new BinomialVanillaEngine<LeisenReimer>(process, timeSteps);
  else if (!strcmp(tree, "Joshi4"))
    return new BinomialVanillaEngine<Joshi4>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedJarrowRudd"))
    return new BinomialVanillaEngine<ExtendedJarrowRudd>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedCoxRossRubinstein"))
    return new BinomialVanillaEngine<ExtendedCoxRossRubinstein>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedAdditiveEQPBinomialTree"))
    return new BinomialVanillaEngine<ExtendedAdditiveEQPBinomialTree>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedTrigeorgis"))
    return new BinomialVanillaEngine<ExtendedTrigeorgis>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedTian"))
    return new BinomialVanillaEngine<ExtendedTian>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedLeisenReimer"))
    return new BinomialVanillaEngine<ExtendedLeisenReimer>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedJoshi4"))
    return new BinomialVanillaEngine<ExtendedJoshi4>(process, timeSteps);
  else
    QL_FAIL("Unknown Binomial Tree "<< tree);
}

PricingEngine* qlBinomialConvertibleEngineAux(const char *tree, const boost::shared_ptr<GeneralizedBlackScholesProcess> process, unsigned timeSteps) {
  if (!strcmp(tree, "JarrowRudd"))
    return new BinomialConvertibleEngine<JarrowRudd>(process, timeSteps);
  else if (!strcmp(tree, "CoxRossRubinstein"))
    return new BinomialConvertibleEngine<CoxRossRubinstein>(process, timeSteps);
  else if (!strcmp(tree, "AdditiveEQPBinomialTree"))
    return new BinomialConvertibleEngine<AdditiveEQPBinomialTree>(process, timeSteps);
  else if (!strcmp(tree, "Trigeorgis"))
    return new BinomialConvertibleEngine<Trigeorgis>(process, timeSteps);
  else if (!strcmp(tree, "Tian"))
    return new BinomialConvertibleEngine<Tian>(process, timeSteps);
  else if (!strcmp(tree, "LeisenReimer"))
    return new BinomialConvertibleEngine<LeisenReimer>(process, timeSteps);
  else if (!strcmp(tree, "Joshi4"))
    return new BinomialConvertibleEngine<Joshi4>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedJarrowRudd"))
    return new BinomialConvertibleEngine<ExtendedJarrowRudd>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedCoxRossRubinstein"))
    return new BinomialConvertibleEngine<ExtendedCoxRossRubinstein>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedAdditiveEQPBinomialTree"))
    return new BinomialConvertibleEngine<ExtendedAdditiveEQPBinomialTree>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedTrigeorgis"))
    return new BinomialConvertibleEngine<ExtendedTrigeorgis>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedTian"))
    return new BinomialConvertibleEngine<ExtendedTian>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedLeisenReimer"))
    return new BinomialConvertibleEngine<ExtendedLeisenReimer>(process, timeSteps);
  else if (!strcmp(tree, "ExtendedJoshi4"))
    return new BinomialConvertibleEngine<ExtendedJoshi4>(process, timeSteps);
  else
    QL_FAIL("Unknown Binomial Tree "<< tree);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
