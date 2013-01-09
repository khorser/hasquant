#include <ql/termstructures/yield/all.hpp>

#include "ql.h"

using namespace QuantLib;

//void *qlBond(unsigned settlDays, void *calendar, int issueDate, void *coupons,
//    char **e)
//{
//  *e = 0;
//  try {
//    return TP("Allocated bond",
//	      new Bond(settlDays,
//			*log_and_cast<Calendar>("Pcalendar", calendar),
//			qlNullableDate(issueDate),
//			*log_and_cast<Leg>("Pcoupons", coupons)));
//  } catch (std::exception& er) {
//    return handleException<void *>(e, er);
//  }
//}

void qlFreeRateHelper(void *helper) {
  delete log_and_cast<RateHelper>("Pfreeing rate helper", helper);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
