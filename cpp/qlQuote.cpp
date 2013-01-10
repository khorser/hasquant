#include <ql/quotes/all.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlSimpleQuote(double value, char **e) {
  try {
    return upcast<SimpleQuote, Quote>("Allocated simple quote", new SimpleQuote(value));
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

double qlQuoteValue(void *quote, char **e) {
  try {
    return cast<Quote>("Pquote", quote)->value();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

void qlFreeQuote(void *quote) {
  delete cast<Quote>("Pfreeing quote", quote);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
