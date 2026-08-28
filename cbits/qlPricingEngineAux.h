QuantLib::PricingEngine* qlBinomialVanillaEngineAux(int tree, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, unsigned timeSteps);
QuantLib::PricingEngine* qlBinomialConvertibleEngineAux(int tree, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, unsigned timeSteps, const QuantLib::Handle<QuantLib::Quote>& cs, QuantLib::DividendSchedule d);
QuantLib::PricingEngine* qlBinomialBarrierEngineAux(int tree, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned maxTimeSteps);
QuantLib::PricingEngine* qlBinomialDoubleBarrierEngineAux(int tree, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, unsigned timeSteps);
QuantLib::PricingEngine* qlMCDoubleBarrierEngineAux(int rngtrait, int stattrait, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);

QuantLib::PricingEngine* qlMCVarianceSwapEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);
QuantLib::PricingEngine* qlMCHestonHullWhiteEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::HybridHestonHullWhiteProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);
QuantLib::PricingEngine* qlMCAmericanEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned polynomOrder, QuantLib::LsmBasisSystem::PolynomialType polynomType, unsigned nCalibrationSamples, QuantLib::ext::optional<bool> antitheticVariateCalibration, unsigned seedCalibration);
QuantLib::PricingEngine* qlMCBarrierEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, int isBiased, unsigned seed);
QuantLib::PricingEngine* qlMCDigitalEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);
QuantLib::PricingEngine* qlMCForwardEuropeanBSEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);
QuantLib::PricingEngine* qlMCDiscreteArithmeticAPEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, int controlVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);
QuantLib::PricingEngine* qlMCDiscreteArithmeticASEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);
QuantLib::PricingEngine* qlMCDiscreteGeometricAPEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);
QuantLib::PricingEngine* qlMCEuropeanEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);
QuantLib::PricingEngine* qlMCEuropeanGJRGARCHEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::GJRGARCHProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);
QuantLib::PricingEngine* qlMCEuropeanHestonEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::HestonProcess> x0, unsigned timeSteps, unsigned timeStepsPerYear, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);
QuantLib::PricingEngine* qlMCHullWhiteCapFloorEngine1Aux(int rngtrait, int stattrait, shared_ptr<QuantLib::HullWhite> model, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);
QuantLib::PricingEngine* qlMCHimalayaEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::StochasticProcessArray> processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);
QuantLib::PricingEngine* qlMCPagodaEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::StochasticProcessArray> processes, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);
QuantLib::PricingEngine* qlMCEuropeanBasketEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::StochasticProcessArray> processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);
QuantLib::PricingEngine* qlMCAmericanBasketEngine1Aux(int rngtrait, const shared_ptr<QuantLib::StochasticProcessArray> processes, unsigned timeSteps, unsigned timeStepsPerYear, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed, unsigned nCalibrationSamples, unsigned polynomialOrder, QuantLib::LsmBasisSystem::PolynomialType polynomialType);
QuantLib::PricingEngine* qlMCPerformanceEngine1Aux(int rngtrait, int stattrait, const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, int brownianBridge, int antitheticVariate, unsigned requiredSamples, double requiredTolerance, unsigned maxSamples, unsigned seed);

QuantLib::PricingEngine* qlFdBlackScholesVanillaEngineAux(const shared_ptr<QuantLib::GeneralizedBlackScholesProcess> process, unsigned tGrid, unsigned xGrid, unsigned dampingSteps, const QuantLib::FdmSchemeDesc &fdScheme, bool localVol, double illegalLocalVolOverwrite, int cashDividendModel);

class PolymorphicPathGenerator;
typedef QuantLib::Sample<QuantLib::MultiPath> SamplePath;
PolymorphicPathGenerator* qlPathGeneratorAux(int rngtrait, const shared_ptr<QuantLib::StochasticProcess> p, const QuantLib::TimeGrid &grid, unsigned seed, unsigned dim, bool brownianBrdige);
PolymorphicPathGenerator* qlSobolPathGeneratorAux(QuantLib::SobolRsg::DirectionIntegers dir, const shared_ptr<QuantLib::StochasticProcess> p, const QuantLib::TimeGrid &grid, unsigned seed, unsigned dim, bool brownianBridge);
void qlFreePolymorphicPathGeneratorAux(PolymorphicPathGenerator *p);
const SamplePath& qlPathGeneratorNextAux(PolymorphicPathGenerator* gen);
const SamplePath& qlPathGeneratorAntitheticAux(PolymorphicPathGenerator* gen);

// The gaussian sequence generator MultiPathGenerator merely consumes, exposed standalone so a
// Haskell-defined SDE can be evolved entirely in Haskell -- see QuantLib.Method.gaussianRsg.
class PolymorphicGaussianRsg;
PolymorphicGaussianRsg* qlGaussianRsgAux(int rngtrait, unsigned dimension, unsigned seed);
PolymorphicGaussianRsg* qlSobolGaussianRsgAux(QuantLib::SobolRsg::DirectionIntegers dir, unsigned dimension, unsigned seed);
void qlFreePolymorphicGaussianRsgAux(PolymorphicGaussianRsg* g);
const QuantLib::Sample<std::vector<QuantLib::Real> >& qlGaussianRsgNextSequenceAux(PolymorphicGaussianRsg* g);
const QuantLib::Sample<std::vector<QuantLib::Real> >& qlGaussianRsgLastSequenceAux(PolymorphicGaussianRsg* g);
unsigned qlGaussianRsgDimensionAux(PolymorphicGaussianRsg* g);

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
