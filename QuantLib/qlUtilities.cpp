#include <ql/version.hpp>
#include <ql/time/date.hpp>
#include <stdlib.h>

#include "ql.h"

using namespace QuantLib;

const char *qlVersion() {
     return QL_VERSION;
}

const char *boostVersion() {
     return BOOST_LIB_VERSION;
}

void qlFreeString(char *p) {
    free(p);
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
