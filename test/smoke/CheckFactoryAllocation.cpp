// Build with cbits objects and QuantLib; inject failures after each successful allocation.
#include "qlaux.h"
#include <ql/termstructures/credit/defaultprobabilityhelpers.hpp>
#include <ql/termstructures/yield/ratehelpers.hpp>
#include <ql/termstructures/yield/fittedbonddiscountcurve.hpp>
using QlDefaultProbabilityHelper = shared_ptr<QuantLib::DefaultProbabilityHelper>;
using QlRateHelper = shared_ptr<QuantLib::RateHelper>;
using FittedBondDiscountCurveFittingMethod = QuantLib::FittedBondDiscountCurve::FittingMethod;
#include "qlTermStructure.h"
#include <ql/quotes/simplequote.hpp>
#include <ql/termstructures/yield/flatforward.hpp>
#include <ql/time/daycounters/actual365fixed.hpp>
#include <cstdio>
#include <cstdlib>
#include <new>

namespace {
long live = 0;
long attempts = 0;
long failAt = -1;
}
void* operator new(std::size_t size) {
  if (attempts++ == failAt) throw std::bad_alloc();
  void* p = std::malloc(size ? size : 1);
  if (!p) throw std::bad_alloc();
  ++live;
  return p;
}
void operator delete(void* p) noexcept {if (p) {--live; std::free(p);}}
void* operator new[](std::size_t size) {return ::operator new(size);}
void operator delete[](void* p) noexcept {::operator delete(p);}

// Warm caches first; the final allocations wrap an already-constructed payload.
template<class Make, class Free> void check(const char* name, long tailAllocations, Make make, Free free) {
  char* error = nullptr;
  auto warm = make(&error);
  if (error || !warm) std::abort();
  free(warm);
  attempts = 0;
  auto measured = make(&error);
  const long count = attempts;
  free(measured);
  const long baseline = live;
  for (long i = count - tailAllocations; i < count; ++i) {
    error = nullptr;
    attempts = 0;
    failAt = i;
    auto result = make(&error);
    failAt = -1;
    if (result) free(result);
    if (error) qlFreeString(error);
    if (live != baseline) {
      std::fprintf(stderr, "%s failure %ld/%ld: leaked %ld allocations\n", name, i, count, live-baseline);
      std::abort();
    }
  }
  std::printf("%s: %ld allocation failures cleaned up\n", name, tailAllocations);
}

int main() {
  using namespace QuantLib;
  QlYieldTermStructure base(ext::make_shared<FlatForward>(Date(1, January, 2026), 0.03, Actual365Fixed()));
  QlQuote spread(ext::make_shared<SimpleQuote>(0.001));
  QlQuote* spreads[] = {&spread, &spread};
  int dates[] = {Date(1, January, 2027).serialNumber(), Date(1, January, 2028).serialNumber()};
  check("Ibor factory", 2, [&](char** e) {return qlCreateIbor(0, 3, Months, &base, e);}, qlFreeIborIndex);
  check("Spread curve factory", 4, [&](char** e) {
    return qlPiecewiseZeroSpreadedTermStructure(&base, 2, spreads, 2, dates, Continuous, Annual, 2, 0, 0, e);
  }, qlFreeYieldTermStructure);
}
