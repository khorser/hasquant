#include <ql/time/schedule.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlSchedule(int eff, int term, double *amounts, int *dates, char **e) {
  *e = 0;
  try {
    //leg = new Leg();
    //printf("Allocated leg %p\n", leg);
    //QL_FAIL("Just for fun");
    return 0;
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void qlFreeSchedule(void *s) {
  delete (Schedule *)s;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
