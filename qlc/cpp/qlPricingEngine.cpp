#include <ql/pricingengines/bond/discountingbondengine.hpp>

#include "ql.h"

using namespace QuantLib;

QlPricingEngine *qlDiscountingBondEngine(QlYieldTermStructure *ts, char **e) {
  try {
    return ret(new QlPricingEngine(alloc(
		    new DiscountingBondEngine(Handle<YieldTermStructure>(*(arg(ts)))))));
  } catch (std::exception& er) {
    return handleException<QlPricingEngine *>(e, er);
  }
}

void qlFreePricingEngine(QlPricingEngine *engine) {
  del(engine);
}
