#include <ql/quotes/all.hpp>

#include "qlaux.h"
#include "qlQuote.h"

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

QlQuote* qlEurodollarFuturesImpliedStdDevQuote(QlQuote* forward, QlQuote* callPrice, QlQuote* putPrice, double strike, double guess, double accuracy, unsigned maxIter, char **e) {
  try {
    return ret(new QlQuote(alloc(new EurodollarFuturesImpliedStdDevQuote(Handle<Quote>(*arg(forward)), Handle<Quote>(*arg(callPrice)), Handle<Quote>(*arg(putPrice)), strike, guess, accuracy, maxIter))));
  } catch (std::exception& er) {
    return handleException<QlQuote*>(e, er);
  }
}
QlQuote* qlForwardSwapQuote(QlSwapIndex* swapIndex, QlQuote* spread, int l, int u, char **e) {
  try {
    return ret(new QlQuote(alloc(new ForwardSwapQuote(*arg(swapIndex), Handle<Quote>(*arg(spread)), Period(l, (TimeUnit)u)))));
  } catch (std::exception& er) {
    return handleException<QlQuote*>(e, er);
  }
}
QlQuote* qlForwardValueQuote(QlIndex* index, int fixingDate, char **e) {
  try {
    return ret(new QlQuote(alloc(new ForwardValueQuote(*arg(index), Date(fixingDate)))));
  } catch (std::exception& er) {
    return handleException<QlQuote*>(e, er);
  }
}
QlQuote* qlFuturesConvAdjustmentQuote1(QlIborIndex* index, char* immCode, QlQuote* futuresQuote, QlQuote* volatility, QlQuote* meanReversion, char **e) {
  try {
    return ret(new QlQuote(alloc(new FuturesConvAdjustmentQuote(*arg(index), std::string(arg(immCode)), Handle<Quote>(*arg(futuresQuote)), Handle<Quote>(*arg(volatility)), Handle<Quote>(*arg(meanReversion))))));
  } catch (std::exception& er) {
    return handleException<QlQuote*>(e, er);
  }
}
QlQuote* qlFuturesConvAdjustmentQuote(QlIborIndex* index, int futuresDate, QlQuote* futuresQuote, QlQuote* volatility, QlQuote* meanReversion, char **e) {
  try {
    return ret(new QlQuote(alloc(new FuturesConvAdjustmentQuote(*arg(index), Date(futuresDate), Handle<Quote>(*arg(futuresQuote)), Handle<Quote>(*arg(volatility)), Handle<Quote>(*arg(meanReversion))))));
  } catch (std::exception& er) {
    return handleException<QlQuote*>(e, er);
  }
}
QlQuote* qlImpliedStdDevQuote(int optionType, QlQuote* forward, QlQuote* price, double strike, double guess, double accuracy, unsigned maxIter, char **e) {
  try {
    return ret(new QlQuote(alloc(new ImpliedStdDevQuote((Option::Type)optionType, Handle<Quote>(*arg(forward)), Handle<Quote>(*arg(price)), strike, guess, accuracy, maxIter))));
  } catch (std::exception& er) {
    return handleException<QlQuote*>(e, er);
  }
}
QlQuote* qlLastFixingQuote(QlIndex* index, char **e) {
  try {
    return ret(new QlQuote(alloc(new LastFixingQuote(*arg(index)))));
  } catch (std::exception& er) {
    return handleException<QlQuote*>(e, er);
  }
}
int qlQuoteIsValid(QlQuote* o, char **e) {
  try {
    return (*arg(o))->isValid();
  } catch (std::exception& er) {
    return handleException<int>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
