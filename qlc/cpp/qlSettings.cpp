#include <ql/settings.hpp>

#include "qlaux.h"

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

void qlSettingsAnchorEvaluationDate() {
  Settings::instance().anchorEvaluationDate();
}
int qlSettingsIncludeReferenceDateCashFlows() {
  return Settings::instance().includeReferenceDateCashFlows();
}
int qlSettingsIncludeReferenceDateEvents() {
  return Settings::instance().includeReferenceDateEvents();
}
void qlSettingsResetEvaluationDate(char **e) {
  try {
    return Settings::instance().resetEvaluationDate();
  } catch (std::exception& er) {
    (void)handleException<void*>(e, er);
  }
}
void qlSettingsSetIncludeReferenceDateCashFlows(int x0) {
  Settings::instance().includeReferenceDateCashFlows() = x0;
}
void qlSettingsSetIncludeReferenceDateEvents(int x0) {
  Settings::instance().includeReferenceDateEvents() = x0;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
