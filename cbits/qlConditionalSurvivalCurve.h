#ifndef HASQUANT_CONDITIONAL_SURVIVAL_CURVE_H
#define HASQUANT_CONDITIONAL_SURVIVAL_CURVE_H

#include <ql/termstructures/defaulttermstructure.hpp>
#include <cmath>
#include <utility>

namespace hasquant {

// Keep the original curve and its native numerics, conditioning on a fixed later reference.
class ConditionalSurvivalCurve final : public QuantLib::DefaultProbabilityTermStructure {
 public:
  ConditionalSurvivalCurve(QuantLib::Handle<QuantLib::DefaultProbabilityTermStructure> base,
                           QuantLib::Date reference)
  : QuantLib::DefaultProbabilityTermStructure(reference), base_(std::move(base)) {
    QL_REQUIRE(!base_.empty(), "a conditional survival curve needs an underlying curve");
    QL_REQUIRE(base_->jumpDates().empty(),
               "conditional survival views cannot transfer scheduled-jump metadata");
    checkReference();
    normalization();
    registerWith(base_);
    enableExtrapolation(base_->allowsExtrapolation());
  }
  QuantLib::DayCounter dayCounter() const override { return base_->dayCounter(); }
  QuantLib::Calendar calendar() const override { return base_->calendar(); }
  QuantLib::Date maxDate() const override { return base_->maxDate(); }
  QuantLib::Time maxTime() const override { return base_->maxTime() - offset(); }

 protected:
  QuantLib::Probability survivalProbabilityImpl(QuantLib::Time t) const override {
    const auto result = base_->survivalProbability(offset() + t, true) / normalization();
    QL_REQUIRE(std::isfinite(result), "conditional survival probability must be finite");
    return result;
  }
  QuantLib::Real defaultDensityImpl(QuantLib::Time t) const override {
    const auto result = base_->defaultDensity(offset() + t, true) / normalization();
    QL_REQUIRE(std::isfinite(result), "conditional default density must be finite");
    return result;
  }
  QuantLib::Real hazardRateImpl(QuantLib::Time t) const override {
    normalization();
    const auto result = base_->hazardRate(offset() + t, true);
    QL_REQUIRE(std::isfinite(result), "conditional hazard rate must be finite");
    return result;
  }

 private:
  void checkReference() const {
    QL_REQUIRE(referenceDate() >= base_->referenceDate(),
               "a conditional reference must not precede the original reference");
    QL_REQUIRE(referenceDate() <= base_->maxDate(),
               "a conditional reference must lie within the original curve support");
  }
  QuantLib::Time offset() const {
    checkReference();
    return base_->timeFromReference(referenceDate());
  }
  QuantLib::Probability normalization() const {
    checkReference();
    const auto result = base_->survivalProbability(referenceDate(), false);
    QL_REQUIRE(std::isfinite(result) && result > 0.0,
               "conditional survival normalization must be positive and finite");
    return result;
  }
  QuantLib::Handle<QuantLib::DefaultProbabilityTermStructure> base_;
};

}
#endif
