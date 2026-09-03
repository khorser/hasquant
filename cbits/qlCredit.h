#ifdef __cplusplus
extern "C" {
#endif
  // ql/experimental/credit/defaultprobabilitykey.hpp -- only the NorthAmericaCorpDefaultKey
  // constructor is bound; DefaultProbKey itself has no public constructor of its own upstream.
  DefaultProbKey* qlNorthAmericaCorpDefaultKey(Currency* currency, int seniority, int graceFailureToPayLen, int graceFailureToPayUnit, double amountFailure, int restructuringType, char **e);
  void qlFreeDefaultProbKey(DefaultProbKey *o);

  // ql/experimental/credit/issuer.hpp -- only the key_curve_pair-vector constructor (empty
  // DefaultEventSet) is bound.
  Issuer* qlIssuer(unsigned probabilitiesLen, DefaultProbKey** keys, QlDefaultProbabilityTermStructure** curves, char **e);
  void qlFreeIssuer(Issuer *o);

  // ql/experimental/credit/pool.hpp -- Pool::add is looped over internally; no add mutator is
  // exposed to Haskell.
  QlPool* qlPool(unsigned namesLen, char** names, Issuer** issuers, DefaultProbKey** keys, char **e);
  void qlFreePool(QlPool *o);

  // ql/experimental/credit/basket.hpp -- the loss model is a constructor argument here; the
  // shim calls Basket::setLossModel internally, so no setter is exposed to Haskell.
  QlBasket* qlBasket(int refDate, unsigned namesLen, char** names, double* notionals, QlPool* pool, double attachmentRatio, double detachmentRatio, QlClaim* claim, QlDefaultLossModel* lossModel, char **e);
  void qlFreeBasket(QlBasket *o);
  double qlBasketNotional(QlBasket* o, char **e);
  // Bound early (ahead of the rest of Basket's risk-output surface) to give this step's own
  // test a discriminating check that the loss model actually wired up; the remaining outputs
  // (percentile, expectedShortfall, lossDistribution, ...) are a separate step.
  double qlBasketExpectedTrancheLoss(QlBasket* o, int d, char **e);

  // ql/experimental/credit/gaussianlhplossmodel.hpp -- only the Handle<Quote> correlation
  // overload is bound, per the std::variant/Handle<Quote> convention (a caller with a bare
  // number gets a simpleQuote for free).
  QlDefaultLossModel* qlGaussianLHPLossModel(QlQuote* correlQuote, unsigned recoveriesLen, double* recoveries, char **e);
  void qlFreeDefaultLossModel(QlDefaultLossModel *o);

  // ql/experimental/credit/syntheticcdo.hpp -- notional is ext::optional<Real>; haveNotional
  // selects between the "leveraged off basket tranche notional" default (0) and an explicit
  // override notional.
  QlSyntheticCDO* qlSyntheticCDO(QlBasket* basket, int side, Schedule* schedule, double upfrontRate, double runningRate, DayCounter* dayCounter, int paymentConvention, int haveNotional, double notional, char **e);
  void qlFreeSyntheticCDO(QlSyntheticCDO *o);
  QlInstrument* qlSyntheticCDOAsInstrument(QlSyntheticCDO *o);
  double qlSyntheticCDOFairPremium(QlSyntheticCDO* o, char **e);
  double qlSyntheticCDOFairUpfrontPremium(QlSyntheticCDO* o, char **e);
  double qlSyntheticCDOPremiumValue(QlSyntheticCDO* o, char **e);
  double qlSyntheticCDOProtectionValue(QlSyntheticCDO* o, char **e);
  double qlSyntheticCDOPremiumLegNPV(QlSyntheticCDO* o, char **e);
  double qlSyntheticCDOProtectionLegNPV(QlSyntheticCDO* o, char **e);
  double qlSyntheticCDORemainingNotional(QlSyntheticCDO* o, char **e);
  // leverageFactor() is skipped -- a constructor echo (notional / basket tranche notional).
  double qlSyntheticCDOImplicitCorrelation(QlSyntheticCDO* o, unsigned recoveriesLen, double* recoveries, QlYieldTermStructure* discountCurve, double targetNPV, double accuracy, char **e);

  // ql/experimental/credit/constantlosslatentmodel.hpp -- ConstantLossModel<CopulaPolicy>, only
  // the Handle<Quote>/nVariables (one-factor) constructor. tOrdersLen == 0 selects
  // GaussianCopulaPolicy; tOrdersLen > 0 selects TCopulaPolicy with these degrees of freedom
  // (see qlTermStructureAux.h for the exact-length requirement). The dispatch itself lives in
  // qlTermStructureAux.cpp, alongside the other DefaultProbabilityTermStructure/credit dispatch
  // already there, per AGENTS.md's rule that a runtime-enum-selects-a-template-argument switch
  // belongs in its domain's Aux TU.
  QlDefaultLossModel* qlConstantLossModel(QlQuote* correlQuote, unsigned recoveriesLen, double* recoveries, int integralType, unsigned tOrdersLen, int* tOrders, char **e);

  // ql/experimental/credit/nthtodefault.hpp -- only fairPremium() is bound; premium/nominal/
  // dayCounter/side/rank/basketSize are all constructor echoes.
  QlNthToDefault* qlNthToDefault(QlBasket* basket, unsigned n, int side, Schedule* premiumSchedule, double upfrontRate, double premiumRate, DayCounter* dayCounter, double nominal, int settlePremiumAccrual, char **e);
  void qlFreeNthToDefault(QlNthToDefault *o);
  QlInstrument* qlNthToDefaultAsInstrument(QlNthToDefault *o);
  double qlNthToDefaultFairPremium(QlNthToDefault* o, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
