#include <ql/pricingengines/bond/discountingbondengine.hpp>

#include "qlaux.h"

using namespace QuantLib;

QlPricingEngine *qlDiscountingBondEngine(QlYieldTermStructure *ts, int f, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(
		    new DiscountingBondEngine(
			Handle<YieldTermStructure>(*(arg(ts))),
			f == -1 ? boost::none : boost::optional<bool>(f)))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine *>(e, er);
  }
}

void qlFreePricingEngine(QlPricingEngine *engine) {
  del(engine);
}
