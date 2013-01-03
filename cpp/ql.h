#include <ql/time/date.hpp>
#include <ql/errors.hpp>

#include <string.h>
#include <stdio.h>

/* dates are passed as int = serial number o the date.
 * the code assumes that Haskell bindings validate date */ 

extern "C"
{
  /* utilities */
  const char *qlVersion();
  const char *boostVersion();
      /* internal */
  void	qlFreeString(char *p);

  /* date */
      /* internal */
  int	qlMinDateSerialNumber();
  int	qlMaxDateSerialNumber();
  int	qlMinYear();
  int	qlMinMonth();
  int	qlMinDay();

  /* leg */
  void *qlLeg(int len, double *amounts, int *dates, char **e);
  int   qlLegStartDate(void *leg, char **e);
      /* internal */
  void  qlFreeLeg(void *leg);

  /* calendar */
  void *qlCalendar(const char *name, char **e);
  const char *qlCalendarName(void *calendar);
      /* internal */
  void  qlFreeCalendar(void *calendar);

  /* settings */
  int	qlSettingsEvaluationDate();
  void	qlSettingsSetEvaluationDate(int x);
  void	qlSettingsSetEnforceTodaysHistoricFixings(int x);
  int	qlSettingsEnforceTodaysHistoricFixings();

  /* bond */
  void *qlBond(unsigned settlDays, void *calendar, double faceAmount, int maturityDate, int issueDate, void *cashFlows, char **e);
  int   qlBondMaturityDate(void *bond);
  int   qlBondIssueDate(void *bond);
      /* internal */
  void qlFreeBond(void *bond);

  /* daycounter */
  void *qlDayCounter(const char *name, char **e);
  const char *qlDayCounterName(void *counter);
      /* internal */
  void  qlFreeDayCounter(void *counter);
}

static inline QuantLib::Date qlNullableDate(int serialNumber) {
  if (!serialNumber)
    return QuantLib::Date(); /* special null date value */
  else
    return QuantLib::Date(serialNumber);
}

/* some helpers ... well ... I hope they will help... */
template <class T>
T *handleException(char **msg, std::exception &e, T *t)
{
  *msg = strdup(e.what());
  //printf("Duplicated exception message to a string %p", *msg);
  if (t)
    delete t;
  return 0;
}

template <class T>
T handleException(char **msg, std::exception &e)
{
  *msg = strdup(e.what());
  //printf("Duplicated exception message to a string %p", *msg);
  return 0;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
