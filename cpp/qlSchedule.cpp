#include <ql/time/schedule.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlSchedule1(int len, int *dates, void *cal, int conv, char **e) {
  *e = 0;
  try {
    std::vector<Date> d;
    for (int i = 0; i < len; ++i)
      d.push_back(Date(TV("PAdate", dates[i])));
    return TP("Allocated schedule",
		new Schedule(d,
			      *log_and_cast<Calendar>("Pcalendar", cal),
			      (BusinessDayConvention)conv));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void *qlSchedule(int eff, int term, void *tenor, void *cal,
    int conv, int termConv, int rule, int eom, int first, int nextToLast,
    char **e) {
  *e = 0;
  try {
    return TP("Allocated schedule2",
	      new Schedule(qlNullableDate(eff),
			    Date(term),
			    *log_and_cast<Period>("Ptenor", tenor),
			    *log_and_cast<Calendar>("Pcalendar", cal),
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

void *qlScheduleUntil(void *sched, int date, char **e) {
  *e = 0;
  try {
    return TP("Allocated truncated schedule",
	new Schedule(log_and_cast<Schedule>("Pschedule", sched)
		      ->until(Date(date))));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

int *qlScheduleDates(void *sched, int *count) {
  const std::vector<Date> &dates = log_and_cast<Schedule>("Pschedule", sched)
    ->dates();
  *count = dates.size();
  int *days = qlAllocateInts(*count);
  // if we wanted more C++
  // we could use std::transform, mem_fun/lambda, and std::copy here
  for (size_t i = 0; i < dates.size(); ++i)
    days[i] = dates[i].serialNumber();
  return days;
}

void qlFreeSchedule(void *s) {
  delete log_and_cast<Schedule>("Pfreeing schedule", s);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
