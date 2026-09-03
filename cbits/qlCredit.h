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
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
