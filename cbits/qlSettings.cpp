#include <ql/settings.hpp>
#include <ql/version.hpp>
#include <ql/errors.hpp>
#include <ql/time/date.hpp>

#include "qlaux.h"
#include "qlSettings.h"

using namespace QuantLib;

int qlSettingsEvaluationDate() {
  Date d = Settings::instance().evaluationDate();
  return d.serialNumber();
}

int qlSettingsEnforceTodaysHistoricFixings() {
  return Settings::instance().enforcesTodaysHistoricFixings();
}

void qlSettingsSetEvaluationDate(int x, char **e) {
  try {
    Settings::instance().evaluationDate() = qlNullableDate(x);
  } catch (std::exception& er) {
    handleException<void *>(e, er);
  }
}

void qlSettingsSetEnforceTodaysHistoricFixings(int x) {
  Settings::instance().enforcesTodaysHistoricFixings() = x;
}

int qlSettingsIncludeTodaysCashFlows() {
  return qlOptBool(Settings::instance().includeTodaysCashFlows());
}

void qlSettingsSetIncludeTodaysCashFlows(int x) {
  Settings::instance().includeTodaysCashFlows() = qlOptBool(x);
}

int qlSettingsIncludeReferenceDateEvents() {
  return Settings::instance().includeReferenceDateEvents();
}
void qlSettingsSetIncludeReferenceDateEvents(int x0) {
  Settings::instance().includeReferenceDateEvents() = x0;
}

void *qlSavedSettings() {
  return new SavedSettings();
}

void qlFreeSavedSettings(void *settings) {
  delete (SavedSettings *)settings;
}

const char *qlVersion() {
  return QL_VERSION;
}

const char *qlBoostVersion() {
  return BOOST_LIB_VERSION;
}

void qlFreeString(char *p) {
  TP2("Freeing string", (void *)p);
  free(p);
  TP2("Freed string", (void *)p);
}

int *qlAllocateInts(size_t size) {
  return new int[size];
}

void qlFreeInts(int *p) {
  delete[] p;
}

void qlFreeUInts(unsigned *p) {
  delete[] p;
}

double *qlAllocateDoubles(size_t size) {
  return new double[size];
}

void qlFreeDoubles(double *p) {
  delete[] p;
}

const QuantLib::Date qlNullableDate(int serialNumber) {
  if (!serialNumber)
    return Date(); /* special null date value */
  else
    return Date(serialNumber);
}

int qlNullableDate(const QuantLib::Date &date) {
  if (date == Date())
    return 0;
  else
    return date.serialNumber();
}

boost::optional<bool> qlOptBool(int b) {
  if (b == -1)
    return boost::none;
  else
    return b;
}

int qlOptBool(boost::optional<bool> b) {
  if (b)
    return *b;
  else
    return -1;
}

char *tracedup(const char *p) {
  TP2("Duplicating string", (void *)p);
  char *dup = strdup(p);
  TP2("Duplicated string to", (void *)dup);
  return dup;
}

std::vector<Date> qlDateVector(unsigned len, int *dates) {
  std::vector<Date> d;
  for (unsigned i = 0; i < len; ++i)
    d.push_back(Date(dates[i]));
  return d;
}

Matrix qlBuildMatrix(double *a, unsigned r, unsigned c) {
  Matrix m (r, c);
  std::copy(a, a + r*c, m.begin());
  return m;
}

void **qlAllocatePointerArray(size_t size) {
  return new void*[size];
}

void qlFreePointerArray(void **p) {
  delete[] p;
}

int qlNullInteger() {
  return QL_NULL_INTEGER;
}

double qlNullReal() {
  return QL_NULL_REAL;
}

double qlEpsilon() {
  return QL_EPSILON;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
