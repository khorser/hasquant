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

void qlSettingsSetEnforceTodaysHistoricFixings(int x, char **e) {
  try {
    Settings::instance().enforcesTodaysHistoricFixings() = x;
  } catch (std::exception& er) {
    handleException<void *>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
