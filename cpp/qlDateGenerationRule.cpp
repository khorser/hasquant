#include <ql/time/dategenerationrule.hpp>

#include "ql.h"

using namespace QuantLib;

int qlDateGenerationRuleBackward() {
  return DateGeneration::Backward;
}

int qlDateGenerationRuleForward() {
  return DateGeneration::Forward;
}

int qlDateGenerationRuleZero() {
  return DateGeneration::Zero;
}

int qlDateGenerationRuleThirdWednesday() {
  return DateGeneration::ThirdWednesday;
}

int qlDateGenerationRuleTwentieth() {
  return DateGeneration::Twentieth;
}

int qlDateGenerationRuleTwentiethIMM() {
  return DateGeneration::TwentiethIMM;
}

int qlDateGenerationRuleOldCDS() {
  return DateGeneration::OldCDS;
}

int qlDateGenerationRuleCDS() {
  return DateGeneration::CDS;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
