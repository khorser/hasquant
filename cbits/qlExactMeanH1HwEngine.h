#ifndef HASQUANT_EXACT_MEAN_H1HW_ENGINE_H
#define HASQUANT_EXACT_MEAN_H1HW_ENGINE_H

#include <ql/math/distributions/gammadistribution.hpp>
#include <ql/math/integrals/gaussianquadratures.hpp>
#include <ql/pricingengines/vanilla/analytichestonhullwhiteengine.hpp>
#include <cmath>
#include <complex>

namespace hasquant {
  // QuantLib's AnalyticH1HWEngine replaces E[sqrt(v_s)] by a + b exp(-c s), with c fitted at s = 1.
  // Where E[sqrt(v_s)] is not monotone (v0 near theta) that fit takes the log of a negative number
  // and the engine returns NaN. This engine integrates the exact E[sqrt(v_s)] instead: the same
  // H1-HW approximation, without the second one. It backports the Exact variance-root mean
  // proposed to QuantLib; drop it once QuantLib ships that.
  class ExactMeanH1HWEngine : public QuantLib::AnalyticHestonHullWhiteEngine {
  public:
    ExactMeanH1HWEngine(const QuantLib::ext::shared_ptr<QuantLib::HestonModel>& model,
                        const QuantLib::ext::shared_ptr<QuantLib::HullWhite>& hullWhiteModel,
                        QuantLib::Real rhoSr, QuantLib::Size integrationOrder, QuantLib::Size meanOrder)
    : AnalyticHestonHullWhiteEngine(model, hullWhiteModel, integrationOrder), rhoSr_(rhoSr), meanOrder_(meanOrder) {
      check();
    }
    ExactMeanH1HWEngine(const QuantLib::ext::shared_ptr<QuantLib::HestonModel>& model,
                        const QuantLib::ext::shared_ptr<QuantLib::HullWhite>& hullWhiteModel,
                        QuantLib::Real rhoSr, QuantLib::Real relTolerance, QuantLib::Size maxEvaluations,
                        QuantLib::Size meanOrder)
    : AnalyticHestonHullWhiteEngine(model, hullWhiteModel, relTolerance, maxEvaluations), rhoSr_(rhoSr), meanOrder_(meanOrder) {
      check();
    }

    void update() override {
      cached_ = false;
      AnalyticHestonHullWhiteEngine::update();
    }

    // E[sqrt(v_t)] under the Heston variance from v0: v_t / c(t) is noncentral chi-squared with d
    // degrees of freedom and noncentrality lambda(t), and E[sqrt] of that is a Poisson mixture of
    // central ones. Its weights are summed outwards from the mode, so no term overflows; past
    // lambda = 1e5 the mixture needs thousands of terms and loses digits, while QuantLib's
    // LambdaApprox is within 0.25/lambda^2 of it, so that is used instead.
    static QuantLib::Real meanRoot(QuantLib::Real v0, QuantLib::Real kappa, QuantLib::Real theta, QuantLib::Real sigma,
                                   QuantLib::Time t) {
      using std::exp; using std::log; using std::sqrt;
      if (t <= 0.0) return sqrt(v0);
      const QuantLib::Real e = exp(-kappa * t);
      if (sigma == 0.0) return sqrt(theta + (v0 - theta) * e);
      const QuantLib::Real c = sigma * sigma / (4.0 * kappa) * (1.0 - e);
      const QuantLib::Real lambda = 4.0 * kappa * v0 * e / (sigma * sigma * (1.0 - e));
      const QuantLib::Real d = 4.0 * kappa * theta / (sigma * sigma);
      if (lambda >= approximationThreshold)
        return sqrt(c * (lambda - 1.0) + c * d * (1.0 + 1.0 / (2.0 * (d + lambda))));
      const QuantLib::GammaFunction g;
      const QuantLib::Real h = 0.5 * lambda, a = 0.5 * (d + 1.0), b = 0.5 * d;
      const QuantLib::Size m = static_cast<QuantLib::Size>(std::floor(h));
      const QuantLib::Real mr = static_cast<QuantLib::Real>(m);
      const QuantLib::Real w0 = exp(-h + (m > 0 ? mr * log(h) : 0.0) - g.logValue(mr + 1.0));
      const QuantLib::Real g0 = exp(g.logValue(a + mr) - g.logValue(b + mr));
      QuantLib::Real sum = w0 * g0, w = w0, r = g0, k = mr;
      for (;;) {
        w *= h / (k + 1.0); r *= (a + k) / (b + k); k += 1.0;
        const QuantLib::Real term = w * r;
        sum += term;
        if (term <= tiny * sum) break;
      }
      w = w0; r = g0; k = mr;
      while (k > 0.0) {
        w *= k / h; r *= (b + k - 1.0) / (a + k - 1.0); k -= 1.0;
        const QuantLib::Real term = w * r;
        sum += term;
        if (term <= tiny * sum) break;
      }
      return sqrt(2.0 * c) * sum;
    }

  protected:
    std::complex<QuantLib::Real> addOnTerm(QuantLib::Real u, QuantLib::Time t, QuantLib::Size j) const override {
      const QuantLib::Real lambda = hullWhiteModel_->a(), eta = hullWhiteModel_->sigma();
      const std::complex<QuantLib::Real> i4 =
          -1.0 / lambda * std::complex<QuantLib::Real>(u * u, (j == 1U) ? -u : u) * meanIntegral(t, lambda);
      return AnalyticHestonHullWhiteEngine::addOnTerm(u, t, j) + eta * rhoSr_ * i4;
    }

  private:
    static constexpr QuantLib::Real approximationThreshold = 1.0e5;
    static constexpr QuantLib::Real tiny = 1.0e-17;

    void check() const {
      QL_REQUIRE(rhoSr_ >= 0.0, "Fourier integration is not stable if the equity interest rate correlation is negative");
      QL_REQUIRE(meanOrder_ > 0, "the exact-mean quadrature needs at least one node");
    }

    // J(t) = int_0^t E[sqrt(v_s)] (1 - exp(-lambda (t - s))) ds, which QuantLib's H1-HW evaluates in
    // closed form for its fitted mean. It does not depend on the Fourier node, so it is kept for
    // the last term and parameters.
    QuantLib::Real meanIntegral(QuantLib::Time t, QuantLib::Real lambda) const {
      const QuantLib::Real v0 = model_->v0(), kappa = model_->kappa(), theta = model_->theta(), sigma = model_->sigma();
      if (!(cached_ && t == keyT_ && v0 == keyV0_ && kappa == keyKappa_ && theta == keyTheta_ && sigma == keySigma_ && lambda == keyLambda_)) {
        const QuantLib::GaussLegendreIntegration quadrature(meanOrder_);
        j_ = 0.5 * t * quadrature([&](QuantLib::Real x) {
          const QuantLib::Time s = 0.5 * t * (x + 1.0);
          return meanRoot(v0, kappa, theta, sigma, s) * (1.0 - std::exp(-lambda * (t - s)));
        });
        keyT_ = t; keyV0_ = v0; keyKappa_ = kappa; keyTheta_ = theta; keySigma_ = sigma; keyLambda_ = lambda; cached_ = true;
      }
      return j_;
    }

    const QuantLib::Real rhoSr_;
    const QuantLib::Size meanOrder_;
    mutable bool cached_ = false;
    mutable QuantLib::Real keyT_ = 0.0, keyV0_ = 0.0, keyKappa_ = 0.0, keyTheta_ = 0.0, keySigma_ = 0.0, keyLambda_ = 0.0, j_ = 0.0;
  };
}
#endif
