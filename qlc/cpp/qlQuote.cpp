#include <ql/quotes/all.hpp>

#include "qlaux.h"

using namespace QuantLib;

QlQuote *qlSimpleQuote(double value, char **e) {
  try {
    return ret(new QlQuote(new SimpleQuote(value)));
  } catch (std::exception& er) {
    return handleException<QlQuote *>(e, er);
  }
}

double qlQuoteValue(QlQuote *quote, char **e) {
  try {
    return (*arg(quote))->value();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

void qlFreeQuote(QlQuote *quote) {
  del(quote);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
