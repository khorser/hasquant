#include <ql/quotes/all.hpp>

#include "ql.h"

using namespace QuantLib;

qlQuote *qlSimpleQuote(double value, char **e) {
  try {
    return ret(new qlQuote(alloc(new SimpleQuote(value))));
  } catch (std::exception& er) {
    return handleException<qlQuote *>(e, er);
  }
}

double qlQuoteValue(qlQuote *quote, char **e) {
  try {
    return (*arg(quote))->value();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

void qlFreeQuote(qlQuote *quote) {
  del(quote);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
