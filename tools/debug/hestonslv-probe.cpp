// Diagnostic probe for the Windows-only HestonSLV failure marked pending in
// QuantLib.Spec.PricingEngine ("builds MC/FDM Heston-SLV models with a consistent
// density-grid layout"): boost's quantile(non_central_chi_squared) throws inside
// SquareRootProcessRNDCalculator::invcdf, called from hestonslvfdmmodel.cpp's
// varianceMesher. It reproduces on no other platform, so this reconstructs the
// fixture in plain C++ -- no Haskell, no hasquant -- and prints the exact
// (t, df, ncp, q) the mesher asks for, so the failing call can be identified from
// a CI log. Run via the "Windows HestonSLV probe" workflow_dispatch job.
//
// The Windows run of this probe passes -- every invcdf returns and the model builds --
// while the same libQuantLib call throws under GHC, so the sections below are also
// exported as extern "C" entry points (-DHESTONSLV_PROBE_NO_MAIN drops main()) for
// tools/debug/HestonSLVProbe.hs to call from inside a GHC-hosted process. fpState()
// dumps the x86 FP environment at each stage: if the RTS-hosted run differs there, that
// is the difference the C++-only run cannot show.
#include <ql/quantlib.hpp>
#include <ql/methods/finitedifferences/utilities/squarerootprocessrndcalculator.hpp>
#include <ql/methods/finitedifferences/utilities/localvolrndcalculator.hpp>

#include <boost/math/distributions/non_central_chi_squared.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/version.hpp>

#include <cfenv>
#include <cfloat>
#include <cstdio>
#include <iostream>
#include <vector>

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
#  define HESTONSLV_PROBE_X86 1
#  include <xmmintrin.h>
#endif

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

extern "C" void hsprobe_environment() {
    std::printf("== environment\n");
    std::printf("  QuantLib          %s\n", QL_VERSION);
    std::printf("  boost             %d.%d.%d\n",
                BOOST_VERSION / 100000, BOOST_VERSION / 100 % 1000, BOOST_VERSION % 100);
    std::printf("  sizeof(long double) %zu, LDBL_MANT_DIG %d, FLT_EVAL_METHOD %d\n",
                sizeof(long double), LDBL_MANT_DIG, FLT_EVAL_METHOD);
    std::printf("  sizeof(Real)        %zu\n", sizeof(Real));
}

// The process-wide FP environment. A GHC-hosted run that masks/unmasks differently, or
// that has flush-to-zero or denormals-are-zero set, would make boost's root finder
// behave differently on the same inputs -- the failure's "best guess" of 2.2e-312 is a
// subnormal, so DAZ/FTZ are the bits to watch.
extern "C" void hsprobe_fpState(const char* label) {
    std::printf("== fp state (%s)\n", label);
    std::printf("  fegetround        %d\n", std::fegetround());
#ifdef HESTONSLV_PROBE_X86
    const unsigned mxcsr = _mm_getcsr();
    std::printf("  MXCSR             0x%04x  FTZ=%u DAZ=%u RC=%u maskedExc=0x%02x\n",
                mxcsr, (mxcsr >> 15) & 1u, (mxcsr >> 6) & 1u,
                (mxcsr >> 13) & 3u, (mxcsr >> 7) & 0x3fu);
    unsigned short cw = 0;
    __asm__ __volatile__("fnstcw %0" : "=m"(cw));
    std::printf("  x87 control word  0x%04x  PC=%u RC=%u maskedExc=0x%02x\n",
                cw, (cw >> 8) & 3u, (cw >> 10) & 3u, cw & 0x3fu);
#endif
    std::fflush(stdout);
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
extern "C" void hsprobe_sweep() {
    using namespace fixture;
    std::printf("== A: raw quantile sweep\n");
    for (Time t = 1e-8; t <= 1.0001; t *= 3.0) {
        probeQuantile(t, vLowerEps, v0, kappa, theta, sigma);
        probeQuantile(t, 1.0 - vUpperEps, v0, kappa, theta, sigma);
    }
}

// Part B: the time grid and rescale steps hestonslvfdmmodel.cpp actually builds for
// this fixture, then the invcdf calls its varianceMesher makes at those very t values.
extern "C" void hsprobe_meshGrid() {
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
extern "C" void hsprobe_buildModel() {
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

// Part E: is 80-bit long double actually working? Every quantile call fails under the
// GHC RTS with the same nonsense "best guess" regardless of input, while the FP
// environment is byte-identical to the standalone run's -- which points at the long
// double math functions boost's promote_double policy routes through (mingw supplies
// them from libmingwex; a GHC link that misses those gets MSVCRT's double-precision
// stubs, silently wrong). Compare this section between the two binaries.
extern "C" void hsprobe_longDouble() {
    std::printf("== E: long double sanity\n");
    // mingw's printf has no %Lg, so every value here is cast to double for display --
    // the standalone (passing) binary prints garbage for %Lg too, which is a formatting
    // limitation and not evidence about the arithmetic.
    volatile long double x = 1.5L;
    std::printf("  sizeof=%zu MANT_DIG=%d EPSILON=%.17g\n",
                sizeof(long double), LDBL_MANT_DIG, (double)LDBL_EPSILON);
    // Not constant-folded: ldexpl is a real call, and this is the check that caught the
    // difference between the two links. "NO" means long double arithmetic is collapsing.
    const long double half = std::ldexp(1.0L, -63);
    std::printf("  ldexpl(1, -63)  = %.17g (expect 1.0842021724855044e-19)\n", (double)half);
    std::printf("  1 + 2^-63 != 1 : %s\n",
                ((1.0L + half) != 1.0L) ? "yes (80-bit)" : "NO (collapsed)");
    std::printf("  logl(1.5)   = %.17g (expect 0.40546510810816438)\n", (double)std::log(x));
    std::printf("  expl(1.5)   = %.17g (expect 4.4816890703380645)\n", (double)std::exp(x));
    std::printf("  powl(1.5,3) = %.17g (expect 3.375)\n", (double)std::pow(x, 3.0L));
    std::printf("  sqrtl(1.5)  = %.17g (expect 1.2247448713915889)\n", (double)std::sqrt(x));
    std::printf("  lgammal(1.5)= %.17g (expect -0.12078223763524526)\n", (double)std::lgamma(x));
    std::fflush(stdout);
}

// Sets the x87 precision control to 64-bit (extended), which is what a mingw-linked
// binary starts with and what boost's promote_double policy assumes. GHC's Windows
// startup leaves MSVC's 53-bit default, silently rounding every long double operation
// to double. Done with fldcw rather than _controlfp_s because MSVC's CRT documents
// _MCW_PC as unsupported on x64.
// Records the x87 control word at namespace-scope-initializer time, so the RTS-hosted
// run can say whether such an initializer runs at all (absent line = never ran) and, if
// it does, whether the word is later reset (0x037f here, 0x027f at the first Haskell
// call = something reset it).
#ifdef HESTONSLV_PROBE_X86
static unsigned short staticInitCw = 0xffff;
namespace {
  struct RecordStaticInitCw {
    RecordStaticInitCw() { __asm__ __volatile__("fnstcw %0" : "=m"(staticInitCw)); }
  };
  const RecordStaticInitCw recordStaticInitCw;
}
#endif

extern "C" void hsprobe_staticInitReport() {
#ifdef HESTONSLV_PROBE_X86
    std::printf("== x87 control word at static-init time: 0x%04x (PC=%u)\n",
                staticInitCw, (unsigned)((staticInitCw >> 8) & 3u));
#else
    std::printf("== x87 control word at static-init time: not x86\n");
#endif
    std::fflush(stdout);
}

extern "C" void hsprobe_setPC64() {
#ifdef HESTONSLV_PROBE_X86
    unsigned short cw = 0;
    __asm__ __volatile__("fnstcw %0" : "=m"(cw));
    cw = (unsigned short)((cw & ~0x0300u) | 0x0300u);
    __asm__ __volatile__("fldcw %0" : : "m"(cw));
    std::printf("== set x87 PC to 64-bit (extended)\n");
#else
    std::printf("== set x87 PC: not x86, nothing to do\n");
#endif
    std::fflush(stdout);
}

// Part F: the same quantiles with boost's double->long double promotion switched off,
// so every intermediate stays in the double precision QuantLib's Real already uses. If
// this passes under the RTS while the promoted form fails, long double is the culprit
// and rebuilding QuantLib with BOOST_MATH_PROMOTE_DOUBLE_POLICY=false is the fix.
extern "C" void hsprobe_noPromote() {
    using namespace fixture;
    using NoPromote = boost::math::policies::policy<
        boost::math::policies::promote_double<false> >;
    std::printf("== F: quantiles with promote_double<false>\n");
    for (Time t = 1e-8; t <= 1.0001; t *= 30.0) {
        const Real d = 4 * kappa / (sigma * sigma), df = d * theta;
        const Real e = std::exp(-kappa * t), k = d / (1 - e), ncp = k * v0 * e;
        std::printf("  t=%-12g df=%-10g ncp=%-14g ", t, df, ncp);
        try {
            const boost::math::non_central_chi_squared_distribution<Real, NoPromote> dist(df, ncp);
            std::printf("-> %.12g / %.12g\n",
                        boost::math::quantile(dist, vLowerEps) / k,
                        boost::math::quantile(dist, 1.0 - vUpperEps) / k);
        } catch (const std::exception& ex) {
            std::printf("-> THREW: %s\n", ex.what());
        }
    }
    std::fflush(stdout);
}

// Part D: the hspec test's full sequence -- the MC model and SLV process it builds
// before the FDM one, in the same process. Part C alone builds the FDM model cold, so
// anything the MC calibration leaves behind (allocator state, a cached term structure,
// the FP environment) is invisible to it.
extern "C" void hsprobe_mcThenFdm() {
    using namespace fixture;
    std::printf("== D: MC model, SLV process, then FDM model (the test's own order)\n");
    Settings::instance().evaluationDate() = today;

    const DayCounter dc = Actual365Fixed();
    const Handle<Quote> spot(ext::make_shared<SimpleQuote>(s0));
    const Handle<YieldTermStructure> rTS(ext::make_shared<FlatForward>(today, r, dc));
    const Handle<YieldTermStructure> qTS(ext::make_shared<FlatForward>(today, q, dc));
    const Handle<LocalVolTermStructure> localVol(
        ext::make_shared<LocalConstantVol>(today, flatLocalVol, dc));

    const auto process = ext::make_shared<HestonProcess>(
        rTS, qTS, spot, v0, kappa, theta, sigma, rho,
        HestonProcess::FullTruncation);
    const Handle<HestonModel> hestonModel(ext::make_shared<HestonModel>(process));
    const Date endDate = today + Period(1, Years);

    try {
        const HestonSLVMCModel mc(
            localVol, hestonModel,
            ext::make_shared<SobolBrownianGeneratorFactory>(
                SobolBrownianGenerator::Diagonal, 1234, SobolRsg::JoeKuoD7),
            endDate, 91, 201, 32768);
        const auto mcLeverage = mc.leverageFunction();
        std::printf("  MC model built, leverage(t=1, x=100) = %.12g\n",
                    mcLeverage->localVol(1.0, 100.0, true));
        const HestonSLVProcess slv(process, mcLeverage, 1.0);
        std::printf("  SLV process factors = %zu\n", slv.factors());
    } catch (const std::exception& ex) {
        std::printf("  MC stage THREW: %s\n", ex.what());
    }
    hsprobe_fpState("after MC calibration");
    hsprobe_buildModel();
}

#ifndef HESTONSLV_PROBE_NO_MAIN
int main() {
    hsprobe_environment();
    hsprobe_fpState("startup, no RTS");
    hsprobe_longDouble();
    hsprobe_noPromote();
    hsprobe_sweep();
    hsprobe_meshGrid();
    hsprobe_buildModel();
    hsprobe_fpState("after model construction");
    hsprobe_mcThenFdm();
    std::fflush(stdout);
    return 0;
}
#endif
