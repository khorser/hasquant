#include <ql/settings.hpp>

#include "ql.h"

using namespace QuantLib;

int qlSettingsEvaluationDate() {
  Date d = Settings::instance().evaluationDate();
  return d.serialNumber();
}

void qlSettingsSetEvaluationDate(void *x) {
  Settings::instance().evaluationDate() = *(Date *)x;
}

void qlSettingsSetEnforceTodaysHistoricFixings(int x) {
  Settings::instance().enforcesTodaysHistoricFixings() = x;
}

int qlSettingsEnforceTodaysHistoricFixings() {
  return Settings::instance().enforcesTodaysHistoricFixings();
}

/* vim: set ft=CPP ff=unix ts=8 sts=2 sw=2: */
