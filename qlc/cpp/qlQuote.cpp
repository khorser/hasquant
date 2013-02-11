#include <ql/quotes/all.hpp>

#include "qlaux.h"

using namespace QuantLib;

QlSimpleQuote *qlSimpleQuote(double value, char **e) {
  try {
    return ret(new QlSimpleQuote(new SimpleQuote(value)));
  } catch (std::exception& er) {
    return handleException<QlSimpleQuote *>(e, er);
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

void qlFreeSimpleQuote(QlSimpleQuote *o) { del(o); }
QlQuote* qlSimpleQuoteAsQuote(QlSimpleQuote *o) { return ret(new QlQuote(*arg(o))); }

double qlSimpleQuoteSetValue(QlSimpleQuote* o, double value, char **e) {
  try {
    return (*arg(o))->setValue(value);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
