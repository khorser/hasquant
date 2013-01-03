#include <ql/time/businessdayconvention.hpp>

#include "ql.h"

using namespace QuantLib;

int qlBusinessDayConventionFollowing() {
    return Following;
}

int qlBusinessDayConventionModifiedFollowing() {
    return ModifiedFollowing;
}

int qlBusinessDayConventionPreceding() {
    return Preceding;
}

int qlBusinessDayConventionModifiedPreceding() {
    return ModifiedPreceding;
}

int qlBusinessDayConventionUnadjusted() {
    return Unadjusted;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
