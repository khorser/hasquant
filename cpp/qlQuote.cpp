#include <ql/quotes/all.hpp>

#include "ql.h"

using namespace QuantLib;

Quote *qlSimpleQuote(double value, char **e) {
  try {
    return log(new SimpleQuote(value), "Allocated quote");
  } catch (std::exception& er) {
    return handleException<Quote *>(e, er);
  }
}

double qlQuoteValue(Quote *quote, char **e) {
  try {
    return quote->value();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

void qlFreeQuote(Quote *quote) {
  delete log(quote, "Deallocating quote");
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
