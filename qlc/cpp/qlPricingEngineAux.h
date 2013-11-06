QuantLib::PricingEngine* qlBinomialVanillaEngineAux(const char *tree, const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, unsigned timeSteps);
QuantLib::PricingEngine* qlBinomialConvertibleEngineAux(const char *tree, const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, unsigned timeSteps);

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
