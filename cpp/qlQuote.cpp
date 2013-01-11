#include <ql/quotes/all.hpp>

#include "ql.h"

using namespace QuantLib;

#ifdef QLTRACK_ALLOCATIONS
// very minimal implementation to check that all objects are actually freed
class QuoteWrapper: public Quote {
  public:
    QuoteWrapper(Quote *quote): quote_(quote) {TP2("wrapped", quote); TP2("wrapper", this);}
    virtual ~QuoteWrapper() { TP2("destroying underlying", quote_); delete quote_; }
    Real value() const {return quote_->value();}
    bool isValid() const {return quote_->isValid();}
  private:
    Quote *quote_;
};
template <class T>
Quote *wrap(T *q) {
  return new QuoteWrapper(alloc(q));
}
#else
template <class T>
Quote *wrap(T *q) { return alloc(q); }
#endif

qlQuote *qlSimpleQuote(double value, char **e) {
  try {
    return ret(new qlQuote(wrap(new SimpleQuote(value))));
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
