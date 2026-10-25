#ifndef HASQUANT_SHAPED_HAZARD_CURVE_H
#define HASQUANT_SHAPED_HAZARD_CURVE_H

#include <ql/termstructures/credit/hazardratestructure.hpp>
#include <ql/math/interpolations/linearinterpolation.hpp>
#include <ql/math/interpolations/forwardflatinterpolation.hpp>
#include <ql/quote.hpp>
#include <ql/experimental/credit/spreadedhazardratecurve.hpp>
#include <algorithm>
#include <cmath>
#include <limits>

namespace hasquant {

// Preserve the native quadrature and arithmetic while refusing invalid queried hazards.
class CheckedParallelHazardCurve final : public QuantLib::SpreadedHazardRateCurve {
 public:
  using QuantLib::SpreadedHazardRateCurve::SpreadedHazardRateCurve;
 protected:
  QuantLib::Real hazardRateImpl(QuantLib::Time t) const override {
    const auto result = QuantLib::SpreadedHazardRateCurve::hazardRateImpl(t);
    QL_REQUIRE(std::isfinite(result) && result >= 0.0, "a shifted hazard rate must be finite and nonnegative");
    return result;
  }
};

// QuantLib supplies interpolation primitives; keep the underlying survival curve intact.
class ShapedHazardCurve final : public QuantLib::HazardRateStructure {
 public:
  ShapedHazardCurve(QuantLib::Handle<QuantLib::DefaultProbabilityTermStructure> base,
                   std::vector<QuantLib::Date> dates,
                   std::vector<QuantLib::Handle<QuantLib::Quote>> spreads, bool buckets)
  : base_(std::move(base)), dates_(std::move(dates)), spreads_(std::move(spreads)), buckets_(buckets) {
    QL_REQUIRE(!base_.empty(), "a shaped hazard curve needs an underlying curve");
    QL_REQUIRE(!dates_.empty() && dates_.size() == spreads_.size(), "hazard dates and spreads must match and be nonempty");
    registerWith(base_);
    for (const auto& spread : spreads_) registerWith(spread);
    ensureData();
  }
  QuantLib::DayCounter dayCounter() const override { return base_->dayCounter(); }
  QuantLib::Calendar calendar() const override { return base_->calendar(); }
  const QuantLib::Date& referenceDate() const override { return base_->referenceDate(); }
  QuantLib::Date maxDate() const override { return base_->maxDate(); }
  QuantLib::Time maxTime() const override { return base_->maxTime(); }
  void update() override { dirty_ = true; QuantLib::HazardRateStructure::update(); }

 protected:
  QuantLib::Real hazardRateImpl(QuantLib::Time t) const override {
    ensureData();
    const auto spread = buckets_ ? interpolation_(std::min(t, times_.back()), true)
                                : values_.size() == 1 ? values_.front()
                                : interpolation_(std::clamp(t, times_.front(), times_.back()), true);
    const auto result = base_->hazardRate(t, true) + spread;
    QL_REQUIRE(std::isfinite(result) && result >= 0.0, "a shifted hazard rate must be finite and nonnegative");
    return result;
  }
  QuantLib::Probability survivalProbabilityImpl(QuantLib::Time t) const override {
    ensureData();
    // A far-end survival query must also inspect both sides of earlier spread boundaries.
    hazardRateImpl(0.0);
    hazardRateImpl(t);
    for (auto knot : times_) if (knot > 0.0 && knot <= t) {
      hazardRateImpl(knot);
      hazardRateImpl(std::nextafter(knot, 0.0));
    }
    QuantLib::Real integral;
    if (buckets_) {
      integral = interpolation_.primitive(std::min(t, times_.back()), true);
    } else if (values_.size() == 1 || t <= times_.front()) {
      integral = values_.front() * t;
    } else {
      integral = values_.front() * times_.front()
               + interpolation_.primitive(std::min(t, times_.back()), true)
               + values_.back() * std::max(0.0, t - times_.back());
    }
    const auto result = base_->survivalProbability(t, true) * std::exp(-integral);
    const auto roundoff = 4 * std::numeric_limits<QuantLib::Probability>::epsilon();
    QL_REQUIRE(std::isfinite(result) && result >= 0.0 && result <= 1.0 + roundoff,
               "shifted survival probability must be finite and in [0,1]");
    return std::min(result, 1.0);
  }

 private:
  void ensureData() const {
    if (!dirty_) return;
    times_.clear(); values_.clear();
    if (buckets_) times_.push_back(0.0);
    QuantLib::Date previous = referenceDate();
    for (QuantLib::Size i = 0; i < dates_.size(); ++i) {
      QL_REQUIRE(dates_[i] > previous, "hazard dates must increase strictly after the reference date");
      const auto t = base_->timeFromReference(dates_[i]);
      QL_REQUIRE(std::isfinite(t) && t > (times_.empty() ? 0.0 : times_.back()),
                 "hazard times must be finite and strictly increasing");
      QL_REQUIRE(!spreads_[i].empty(), "a hazard spread quote must not be empty");
      const auto value = spreads_[i]->value();
      QL_REQUIRE(std::isfinite(value), "hazard spreads must be finite");
      times_.push_back(t); values_.push_back(value);
      previous = dates_[i];
    }
    if (buckets_) {
      values_.push_back(0.0);
      interpolation_ = QuantLib::ForwardFlat().interpolate(times_.begin(), times_.end(), values_.begin());
    } else if (values_.size() > 1) {
      interpolation_ = QuantLib::Linear().interpolate(times_.begin(), times_.end(), values_.begin());
    }
    dirty_ = false;
  }
  QuantLib::Handle<QuantLib::DefaultProbabilityTermStructure> base_;
  std::vector<QuantLib::Date> dates_;
  std::vector<QuantLib::Handle<QuantLib::Quote>> spreads_;
  bool buckets_;
  mutable bool dirty_ = true;
  mutable std::vector<QuantLib::Time> times_;
  mutable std::vector<QuantLib::Real> values_;
  mutable QuantLib::Interpolation interpolation_;
};

}
#endif
