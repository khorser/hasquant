#include "ql/version.hpp"
#include "ql/settings.hpp"
#include "ql/time/date.hpp"

#include "qlsettings.h"

const char *qlVersion() {
     return QL_VERSION;
}

int qlSettingsEvaluationDate() {
    QuantLib::Date d = QuantLib::Date(QuantLib::Settings::instance().evaluationDate());
    return d.serialNumber();
}

void qlSettingsSetEvaluationDate(int x) {
    QuantLib::Settings::instance().evaluationDate() = QuantLib::Date(x);
}

int qlMinDate() {
    return QuantLib::Date::minDate().serialNumber();
}

int qlMinYear() {
    return QuantLib::Date::minDate().year();
}

int qlMinMonth() {
    return QuantLib::Date::minDate().month();
}

int qlMinDay() {
    return QuantLib::Date::minDate().dayOfMonth();
}
