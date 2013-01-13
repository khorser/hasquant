#include <ql/index.hpp>

#include "ql.h"

using namespace QuantLib;

void qlIndexAddFixing(QlIndex *i, int date, double fix, int overwrite, char **e) {
  try {
    (*arg(i))->addFixing(Date(date), fix, overwrite);
  } catch (std::exception& er) {
    (void)handleException<void *>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
