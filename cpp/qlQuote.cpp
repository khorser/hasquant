#include <ql/quotes/all.hpp>

#include "ql.h"

using namespace QuantLib;

Quote *qlSimpleQuote(double value, char **e) {
  try {
    return alloc(new SimpleQuote(value));
  } catch (std::exception& er) {
    return handleException<Quote *>(e, er);
  }
}

double qlQuoteValue(Quote *quote, char **e) {
  try {
    return arg(quote)->value();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

void qlFreeQuote(Quote *quote) {
  del(quote);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
