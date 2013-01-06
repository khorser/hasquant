#include <ql/quotes/all.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlSimpleQuote(double value, char **e) {
  *e = 0;
  try {
    return TM("Allocated simple quote", static_cast<Quote *>(new SimpleQuote(value)));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

double qlQuoteValue(void *quote, char **e) {
  *e = 0;
  try {
    return static_cast<Quote *>(TM("Pquote", quote))->value();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

void qlFreeQuote(void *quote) {
  delete static_cast<Quote *>(TM("Pfreeing quote", quote));
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
