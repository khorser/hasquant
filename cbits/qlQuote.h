#ifdef __cplusplus
extern "C" {
#endif
  QlSimpleQuote *qlSimpleQuote(double value, char **e);
  double qlQuoteValue(QlQuote *quote, char **e);

  void qlFreeQuote(QlQuote *quote);
  void qlFreeSimpleQuote(QlSimpleQuote *o);
  QlQuote* qlSimpleQuoteAsQuote(QlSimpleQuote *o);
  double qlSimpleQuoteSetValue(QlSimpleQuote* o, double value, char **e);
//  QlQuote* qlEurodollarFuturesImpliedStdDevQuote(QlQuote* forward, QlQuote* callPrice, QlQuote* putPrice, double strike, double guess, double accuracy, unsigned maxIter, char **e);
//  QlQuote* qlForwardSwapQuote(QlSwapIndex* swapIndex, QlQuote* spread, int, int, char **e);
//  QlQuote* qlForwardValueQuote(QlIndex* index, int fixingDate, char **e);
//  QlQuote* qlFuturesConvAdjustmentQuote1(QlIborIndex* index, char* immCode, QlQuote* futuresQuote, QlQuote* volatility, QlQuote* meanReversion, char **e);
//  QlQuote* qlFuturesConvAdjustmentQuote(QlIborIndex* index, int futuresDate, QlQuote* futuresQuote, QlQuote* volatility, QlQuote* meanReversion, char **e);
//  QlQuote* qlImpliedStdDevQuote(int optionType, QlQuote* forward, QlQuote* price, double strike, double guess, double accuracy, unsigned maxIter, char **e);
//  QlQuote* qlLastFixingQuote(QlIndex* index, char **e);
  int qlQuoteIsValid(QlQuote* o, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
