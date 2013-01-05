#include <ql/time/schedule.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlSchedule2(int eff, int term, void *tenor, void *cal,
    int conv, int termConv, int rule, int eom, int first, int nextToLast,
    char **e) {
  *e = 0;
  try {
    return new Schedule(qlNullableDate(eff), Date(term),
	*static_cast<Period *>(tenor), *static_cast<Calendar *>(cal),
	(BusinessDayConvention) conv, (BusinessDayConvention) termConv,
	(DateGeneration::Rule) rule,
	eom, qlNullableDate(first), qlNullableDate(nextToLast));
    //printf("Allocated schedule %p\n", s);
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlSchedule(int len, int *dates, void *cal, int conv, char **e) {
  *e = 0;
  try {
    std::vector<Date> d;
    for (int i = 0; i < len; ++i)
      d.push_back(Date(dates[i]));
    return new Schedule(d, *static_cast<Calendar *>(cal), (BusinessDayConvention)conv);
    //printf("Allocated schedule %p\n", s);
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlScheduleUntil(void *sched, int date, char **e) {
  *e = 0;
  try {
    Schedule *s = new Schedule(static_cast<Schedule *>(sched)->until(Date(date)));
    printf("Allocated schedule %p\n", s);
    return s;
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void qlFreeSchedule(void *s) {
  fprintf(stderr, "freeing schedule %p\n", s);
  delete static_cast<Schedule *>(s);
  fprintf(stderr, "freed schedule %p\n", s);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
