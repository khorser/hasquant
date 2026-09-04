// Diagnostic probe for the Windows-only HestonSLV failure marked pending in
// QuantLib.Spec.PricingEngine ("builds MC/FDM Heston-SLV models with a consistent
// density-grid layout"): boost's quantile(non_central_chi_squared) throws inside
// SquareRootProcessRNDCalculator::invcdf, called from hestonslvfdmmodel.cpp's
// varianceMesher. It reproduces on no other platform, so this reconstructs the
// fixture in plain C++ -- no Haskell, no hasquant -- and prints the exact
// (t, df, ncp, q) the mesher asks for, so the failing call can be identified from
// a CI log. Run via the "Windows HestonSLV probe" workflow_dispatch job.
#include <ql/quantlib.hpp>
#include <ql/methods/finitedifferences/utilities/squarerootprocessrndcalculator.hpp>
#include <ql/methods/finitedifferences/utilities/localvolrndcalculator.hpp>

#include <boost/math/distributions/non_central_chi_squared.hpp>
#include <boost/version.hpp>

#include <cfloat>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace QuantLib;

// The hspec test's fixture, verbatim.
namespace fixture {
    const Date today(5, March, 2016);
    const Real s0 = 100.0, r = 0.01, q = 0.02, flatLocalVol = 0.3;
    const Real v0 = 0.09, kappa = 1.0, theta = 0.06, sigma = 0.4, rho = -0.75;
    const Size xGrid = 51, vGrid = 151;
    const Size tMaxStepsPerYear = 500, tMinStepsPerYear = 50;
    const Real tStepNumberDecay = 100.0;
    const Real x0Density = 0.1, localVolEpsProb = 1e-4;
    const Size maxIntegrationIterations = 10000;
    const Real vLowerEps = 1e-5, vUpperEps = 1e-5;
}

static void environment() {
    std::printf("== environment\n");
    std::printf("  QuantLib          %s\n", QL_VERSION);
    std::printf("  boost             %d.%d.%d\n",
                BOOST_VERSION / 100000, BOOST_VERSION / 100 % 1000, BOOST_VERSION % 100);
    std::printf("  sizeof(long double) %zu, LDBL_MANT_DIG %d, FLT_EVAL_METHOD %d\n",
                sizeof(long double), LDBL_MANT_DIG, FLT_EVAL_METHOD);
    std::printf("  sizeof(Real)        %zu\n", sizeof(Real));
}

// One invcdf call, spelled out the way SquareRootProcessRNDCalculator does it, so a
// throw can be attributed to a concrete (t, df, ncp, q).
static void probeQuantile(Time t, Real q, Real v0, Real kappa, Real theta, Real sigma) {
    const Real d = 4 * kappa / (sigma * sigma), df = d * theta;
    const Real e = std::exp(-kappa * t), k = d / (1 - e), ncp = k * v0 * e;
    std::printf("  t=%-12g q=%-10g df=%-10g k=%-14g ncp=%-14g ", t, q, df, k, ncp);
    try {
        const boost::math::non_central_chi_squared_distribution<Real> dist(df, ncp);
        std::printf("-> %.12g\n", boost::math::quantile(dist, q) / k);
    } catch (const std::exception& ex) {
        std::printf("-> THREW: %s\n", ex.what());
    }
}

// Part A: the quantile itself, over a wide sweep of t, independent of any QuantLib
// mesher -- shows whether the failure needs the fixture at all.
static void sweep() {
    using namespace fixture;
    std::printf("== A: raw quantile sweep\n");
    for (Time t = 1e-8; t <= 1.0001; t *= 3.0) {
        probeQuantile(t, vLowerEps, v0, kappa, theta, sigma);
        probeQuantile(t, 1.0 - vUpperEps, v0, kappa, theta, sigma);
    }
}

// Part B: the time grid and rescale steps hestonslvfdmmodel.cpp actually builds for
// this fixture, then the invcdf calls its varianceMesher makes at those very t values.
static void meshGrid() {
    using namespace fixture;
    std::printf("== B: fixture time grid and the invcdf calls varianceMesher makes\n");
    Settings::instance().evaluationDate() = today;

    const DayCounter dc = Actual365Fixed();
    const auto spot = ext::make_shared<SimpleQuote>(s0);
    const auto rTS = ext::make_shared<FlatForward>(today, r, dc);
    const auto qTS = ext::make_shared<FlatForward>(today, q, dc);
    const auto localVol = ext::make_shared<LocalConstantVol>(today, flatLocalVol, dc);

    const Date endDate = today + Period(1, Years);
    const Time T = dc.yearFraction(today, endDate);
    const Time maxDt = 1.0 / tMaxStepsPerYear, minDt = 1.0 / tMinStepsPerYear;

    Time tIdx = 0.0;
    std::vector<Time> times(1, tIdx);
    while (tIdx < T) {
        const Real decay = std::exp(-tStepNumberDecay * tIdx);
        times.push_back(std::min(T, tIdx += maxDt * decay + minDt * (1.0 - decay)));
    }
    const auto timeGrid = ext::make_shared<TimeGrid>(times.begin(), times.end());
    std::printf("  T=%g, timeGrid size=%zu, t[1]=%g, t[2]=%g\n",
                T, timeGrid->size(), timeGrid->at(1), timeGrid->at(2));

    const LocalVolRNDCalculator localVolRND(
        spot, rTS, qTS, localVol, timeGrid, xGrid, x0Density,
        localVolEpsProb, maxIntegrationIterations);

    std::vector<Size> rescaleSteps;
    try {
        rescaleSteps = localVolRND.rescaleTimeSteps();
    } catch (const std::exception& ex) {
        std::printf("  rescaleTimeSteps THREW: %s\n", ex.what());
        return;
    }
    std::printf("  rescaleSteps (%zu):", rescaleSteps.size());
    for (Size s : rescaleSteps) std::printf(" %zu", s);
    std::printf("\n");

    // varianceMesher samples 11 points across each [t0, t1] window.
    for (Size i = 0; i < rescaleSteps.size(); ++i) {
        const Time t0 = timeGrid->at(rescaleSteps[i]);
        const Time t1 = (i + 1 < rescaleSteps.size())
            ? timeGrid->at(rescaleSteps[i + 1]) : timeGrid->back();
        std::printf("  window %zu: [%g, %g]\n", i, t0, t1);
        for (Size j = 0; j <= 10; ++j) {
            const Time t = t0 + j / 10.0 * (t1 - t0);
            probeQuantile(t, vLowerEps, v0, kappa, theta, sigma);
            probeQuantile(t, 1.0 - vUpperEps, v0, kappa, theta, sigma);
        }
    }
}

// Part C: the model construction the test actually performs.
static void buildModel() {
    using namespace fixture;
    std::printf("== C: HestonSLVFDMModel construction\n");
    Settings::instance().evaluationDate() = today;

    const DayCounter dc = Actual365Fixed();
    const Handle<Quote> spot(ext::make_shared<SimpleQuote>(s0));
    const Handle<YieldTermStructure> rTS(ext::make_shared<FlatForward>(today, r, dc));
    const Handle<YieldTermStructure> qTS(ext::make_shared<FlatForward>(today, q, dc));
    const Handle<LocalVolTermStructure> localVol(
        ext::make_shared<LocalConstantVol>(today, flatLocalVol, dc));

    const Handle<HestonModel> hestonModel(ext::make_shared<HestonModel>(
        ext::make_shared<HestonProcess>(rTS, qTS, spot, v0, kappa, theta, sigma, rho)));

    const HestonSLVFokkerPlanckFdmParams params = {
        xGrid, vGrid, tMaxStepsPerYear, tMinStepsPerYear, tStepNumberDecay, 5, 2,
        x0Density, localVolEpsProb, maxIntegrationIterations,
        vLowerEps, vUpperEps, 0.0000025,
        1.0, 0.1, 0.9, 1e-5,
        FdmHestonGreensFct::ZeroCorrelation,
        FdmSquareRootFwdOp::Log,
        FdmSchemeDesc::ModifiedCraigSneyd()
    };

    try {
        const HestonSLVFDMModel model(
            localVol, hestonModel, today + Period(1, Years), params, true);
        const std::list<HestonSLVFDMModel::LogEntry>& entries = model.logEntries();
        std::printf("  built, %zu log entries\n", entries.size());
        if (!entries.empty()) {
            const HestonSLVFDMModel::LogEntry& e = entries.front();
            std::printf("  first entry: t=%g, prob size %zu, v %zu, x %zu\n",
                        e.t, e.prob->size(),
                        e.mesher->getFdm1dMeshers().at(1)->locations().size(),
                        e.mesher->getFdm1dMeshers().at(0)->locations().size());
        }
    } catch (const std::exception& ex) {
        std::printf("  THREW: %s\n", ex.what());
    }
}

int main() {
    environment();
    sweep();
    meshGrid();
    buildModel();
    std::fflush(stdout);
    return 0;
}
