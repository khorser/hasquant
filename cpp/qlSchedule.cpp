#include <ql/time/schedule.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlSchedule2(int eff, int term, void *tenor, void *cal,
    int conv, int termConv, int rule, int eom, int first, int nextToLast,
    char **e) {
  *e = 0;
  try {
    return TP("Allocated schedule2",
	      new Schedule(qlNullableDate(eff),
			    Date(term),
			    *static_cast<Period *>(TP("Ptenor", tenor)),
			    *static_cast<Calendar *>(TP("Pcalendar", cal)),
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
      d.push_back(Date(TV("PAdate", dates[i])));
    return TP("Allocated schedule",
		new Schedule(d,
			      *static_cast<Calendar *>(TP("Pcalendar", cal)),
			      (BusinessDayConvention)conv));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlScheduleUntil(void *sched, int date, char **e) {
  *e = 0;
  try {
    return TP("Allocated truncated schedule",
	      new Schedule(static_cast<Schedule *>(TP("Pschedule", sched))
		->until(Date(TV("Pdate", date)))));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void qlFreeSchedule(void *s) {
  delete static_cast<Schedule *>(TP("Pfreeing schedule", s));
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
