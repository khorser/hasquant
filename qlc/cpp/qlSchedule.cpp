#include <ql/time/schedule.hpp>

#include "qlaux.h"
#include "qlSchedule.h"

using namespace QuantLib;

Schedule *qlSchedule1(unsigned len, int *dates, Calendar *cal, int conv,
  char **e) {
  try {
    std::vector<Date> d;
    for (unsigned i = 0; i < len; ++i)
      d.push_back(Date(dates[i]));
    return alloc(new Schedule(d, *arg(cal), (BusinessDayConvention) conv));
  } catch (std::exception& er) {
    return handleException<Schedule *>(e, er);
  }
}

Schedule *qlSchedule(int eff, int term, int l, int u, Calendar *cal,
    int conv, int termConv, int rule, int eom, int first, int nextToLast,
    char **e) {
  try {
    return alloc(new Schedule(qlNullableDate(eff),
			    Date(term),
			    Period(l, (TimeUnit)u),
			    *arg(cal),
			    (BusinessDayConvention) conv,
			    (BusinessDayConvention) termConv,
			    (DateGeneration::Rule) rule,
			    eom,
			    qlNullableDate(first),
			    qlNullableDate(nextToLast)));
  } catch (std::exception& er) {
    return handleException<Schedule *>(e, er);
  }
}

Schedule *qlScheduleUntil(Schedule *sched, int date, char **e) {
  try {
    return alloc(new Schedule(arg(sched)->until(Date(date))));
  } catch (std::exception& er) {
    return handleException<Schedule *>(e, er);
  }
}

int *qlScheduleDates(Schedule *sched, unsigned *count) {
  const std::vector<Date> &dates = arg(sched)->dates();
  *count = dates.size();
  int *days = qlAllocateInts(*count);
  std::transform(dates.begin(), dates.end(), days,
      std::mem_fun_ref(&Date::serialNumber));
  return days;
}

void qlFreeSchedule(Schedule *s) {
  del(s);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
