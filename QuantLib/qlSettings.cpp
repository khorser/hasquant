#include <ql/settings.hpp>

#include "ql.h"

#include <string.h>

using namespace QuantLib;

int qlSettingsEvaluationDate() {
    Date d = Date(QuantLib::Settings::instance().evaluationDate());
    return d.serialNumber();
}

char* qlSettingsSetEvaluationDate(int x) {
    try {
	Settings::instance().evaluationDate() = QuantLib::Date(x);
    } catch (Error& e) {
	return strdup(e.what());
    }
    return 0;
}
