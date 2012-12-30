#include <ql/version.hpp>
#include <ql/settings.hpp>
#include <ql/time/date.hpp>

#include "qlsettings.h"

#include <string.h>

using namespace QuantLib;

const char *qlVersion() {
     return QL_VERSION;
}

int qlSettingsEvaluationDate() {
    Date d = Date(QuantLib::Settings::instance().evaluationDate());
    return d.serialNumber();
}

void qlFreeString(char *p) {
    free(p);
}

char* qlSettingsSetEvaluationDate(int x) {
    try {
	Settings::instance().evaluationDate() = QuantLib::Date(x);
    } catch (Error& e) {
	return strdup(e.what());
    }
    return 0;
}

int qlMinDate() {
    return Date::minDate().serialNumber();
}

int qlMinYear() {
    return Date::minDate().year();
}

int qlMinMonth() {
    return Date::minDate().month();
}

int qlMinDay() {
    return Date::minDate().dayOfMonth();
}
