#include <ql/quotes/all.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlSimpleQuote(double value, char **e) {
  *e = 0;
  try {
    return (Quote *)(new SimpleQuote(value));
    //printf("Allocated simple quote %p\n", q);
    //QL_FAIL("Just for fun");
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

double qlQuoteValue(void *quote, char **e) {
  *e = 0;
  try {
    return ((Quote *)quote)->value();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

void qlFreeQuote(void *quote) {
  //printf("freeing quote %p\n", quote);
  delete (Quote *)quote;
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
