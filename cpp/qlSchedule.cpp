#include <ql/time/schedule.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlSchedule2(int eff, int term, void *tenor, void *cal,
    int conv, int termConv, int rule, int eom, int first, int nextToLast,
    char **e) {
  *e = 0;
  try {
    return TM("Allocated schedule2",
	      new Schedule(qlNullableDate(eff),
			    Date(term),
			    *static_cast<Period *>(TM("Tenor", tenor)),
			    *static_cast<Calendar *>(TM("Calendar", cal)),
			    (BusinessDayConvention) conv,
			    (BusinessDayConvention) termConv,
			    (DateGeneration::Rule) rule,
			    eom,
			    qlNullableDate(first),
			    qlNullableDate(nextToLast)));
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
    return TM("Allocated schedule",
		new Schedule(d,
			      *static_cast<Calendar *>(TM("Calendar", cal)),
			      (BusinessDayConvention)conv));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlScheduleUntil(void *sched, int date, char **e) {
  *e = 0;
  try {
    return TM("Allocated truncated schedule",
	      new Schedule(static_cast<Schedule *>(TM("Schedule", sched))->until(Date(date))));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void qlFreeSchedule(void *s) {
  delete static_cast<Schedule *>(TM("Freeing schedule", s));
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
