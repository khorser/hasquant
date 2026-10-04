#ifndef HASQUANT_EXACT_MEAN_H1HW_ENGINE_H
#define HASQUANT_EXACT_MEAN_H1HW_ENGINE_H

#include <ql/math/distributions/gammadistribution.hpp>
#include <ql/math/integrals/gaussianquadratures.hpp>
#include <ql/pricingengines/vanilla/analytichestonhullwhiteengine.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <cmath>
#include <complex>

namespace hasquant {
  // Backport of QuantLib's proposed exact variance-root mean for H1-HW.
  // Quadrature avoids the exponential fit, which can fail for a nonmonotone mean.
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
    // central ones. Sum weights outwards from the mode to avoid overflow; past lambda = 1e5,
    // use the asymptotic approximation instead of summing thousands of terms.
    static QuantLib::Real meanRoot(QuantLib::Real v0, QuantLib::Real kappa, QuantLib::Real theta, QuantLib::Real sigma,
                                   QuantLib::Time t) {
      using std::exp; using std::log; using std::sqrt;
      if (t <= 0.0) return sqrt(v0);
      const QuantLib::Real e = exp(-kappa * t);
      if (sigma == 0.0) return sqrt(theta + (v0 - theta) * e);
      const QuantLib::Real oneMinusE = -std::expm1(-kappa * t);
      const QuantLib::Real c = sigma * sigma / (4.0 * kappa) * oneMinusE;
      const QuantLib::Real lambda = 4.0 * kappa * v0 * e / (sigma * sigma * oneMinusE);
      const QuantLib::Real d = 4.0 * kappa * theta / (sigma * sigma);
      if (lambda >= approximationThreshold)
        return sqrt(c * (lambda - 1.0) + c * d * (1.0 + 1.0 / (2.0 * (d + lambda))));
      const QuantLib::GammaFunction g;
      const QuantLib::Real h = 0.5 * lambda, a = 0.5 * (d + 1.0), b = 0.5 * d;
      const QuantLib::Size m = static_cast<QuantLib::Size>(std::floor(h));
      const QuantLib::Real mr = static_cast<QuantLib::Real>(m);
      const QuantLib::Real w0 = exp(-h + (m > 0 ? mr * log(h) : 0.0) - g.logValue(mr + 1.0));
      const QuantLib::Real shape = b + mr;
      const QuantLib::Real inverseShape = 1.0 / shape;
      // Gamma(x + 1/2) / Gamma(x) = sqrt(x) * (1 - 1/(8x) + 1/(128x^2) + 5/(1024x^3) + O(x^-4)).
      const QuantLib::Real g0 = shape >= gammaRatioThreshold
          ? sqrt(shape) * (1.0 + inverseShape * (-0.125 + inverseShape *
              (1.0 / 128.0 + inverseShape * 5.0 / 1024.0)))
          : 1.0 / boost::math::tgamma_delta_ratio(shape, 0.5);
      QuantLib::Real sum = w0 * g0, w = w0, r = g0, k = mr;
      for (;;) {
        w *= h / (k + 1.0);
        r *= (a + k) / (b + k);
        k += 1.0;
        const QuantLib::Real term = w * r;
        sum += term;
        if (term <= tiny * sum) break;
      }
      w = w0;
      r = g0;
      k = mr;
      while (k > 0.0) {
        w *= k / h;
        r *= (b + k - 1.0) / (a + k - 1.0);
        k -= 1.0;
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
          -std::complex<QuantLib::Real>(u * u, (j == 1U) ? -u : u) * meanIntegral(t, lambda);
      return AnalyticHestonHullWhiteEngine::addOnTerm(u, t, j) + eta * rhoSr_ * i4;
    }

  private:
    static constexpr QuantLib::Real approximationThreshold = 1.0e5;
    static constexpr QuantLib::Real gammaRatioThreshold = 1.0e5;
    static constexpr QuantLib::Real tiny = 1.0e-17;

    void check() const {
      QL_REQUIRE(rhoSr_ >= 0.0, "Fourier integration is not stable if the equity interest rate correlation is negative");
      QL_REQUIRE(meanOrder_ > 0, "the exact-mean quadrature needs at least one node");
    }

    // Cache int_0^t E[sqrt(v_s)] (1 - exp(-lambda (t - s))) / lambda ds.
    // The scaled kernel tends to t - s as lambda tends to zero.
    QuantLib::Real meanIntegral(QuantLib::Time t, QuantLib::Real lambda) const {
      const QuantLib::Real v0 = model_->v0(), kappa = model_->kappa(), theta = model_->theta(), sigma = model_->sigma();
      if (!(cached_ && t == keyT_ && v0 == keyV0_ && kappa == keyKappa_ && theta == keyTheta_ && sigma == keySigma_ && lambda == keyLambda_)) {
        const QuantLib::GaussLegendreIntegration quadrature(meanOrder_);
        j_ = 0.5 * t * quadrature([&](QuantLib::Real x) {
          const QuantLib::Time s = 0.5 * t * (x + 1.0);
          const QuantLib::Time tau = t - s;
          const QuantLib::Real z = lambda * tau;
          const QuantLib::Real kernel = tau * (z == 0.0 ? 1.0 : -std::expm1(-z) / z);
          return meanRoot(v0, kappa, theta, sigma, s) * kernel;
        });
        keyT_ = t;
        keyV0_ = v0;
        keyKappa_ = kappa;
        keyTheta_ = theta;
        keySigma_ = sigma;
        keyLambda_ = lambda;
        cached_ = true;
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
