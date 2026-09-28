#ifndef HASQUANT_CHECKED_FD_ENGINE_H
#define HASQUANT_CHECKED_FD_ENGINE_H

#include <ql/instruments/payoffs.hpp>
#include <ql/errors.hpp>

namespace hasquant {
  template<class Engine> class CheckedFdEngine : public Engine {
  public:
    using Engine::Engine;
    void calculate() const override {
      // These upstream engines dereference an unchecked payoff cast in QuantLib 1.43.
      QL_REQUIRE(dynamic_cast<QuantLib::StrikedTypePayoff*>(this->arguments_.payoff.get()),
                 "finite-difference vanilla engine requires a striked payoff");
      Engine::calculate();
    }
  };
}
#endif
