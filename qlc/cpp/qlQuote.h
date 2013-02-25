#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  QlSimpleQuote *DLLEXPORT qlSimpleQuote(double value, char **e);
  double DLLEXPORT qlQuoteValue(QlQuote *quote, char **e);

  void DLLEXPORT qlFreeQuote(QlQuote *quote);
  void DLLEXPORT qlFreeSimpleQuote(QlSimpleQuote *o);
  QlQuote* DLLEXPORT qlSimpleQuoteAsQuote(QlSimpleQuote *o);
  double DLLEXPORT qlSimpleQuoteSetValue(QlSimpleQuote* o, double value, char **e);
  QlQuote* DLLEXPORT qlEurodollarFuturesImpliedStdDevQuote(QlQuote* forward, QlQuote* callPrice, QlQuote* putPrice, double strike, double guess, double accuracy, unsigned maxIter, char **e);
  QlQuote* DLLEXPORT qlForwardSwapQuote(QlSwapIndex* swapIndex, QlQuote* spread, Period* fwdStart, char **e);
  QlQuote* DLLEXPORT qlForwardValueQuote(QlIndex* index, int fixingDate, char **e);
  QlQuote* DLLEXPORT qlFuturesConvAdjustmentQuote1(QlIborIndex* index, char* immCode, QlQuote* futuresQuote, QlQuote* volatility, QlQuote* meanReversion, char **e);
  QlQuote* DLLEXPORT qlFuturesConvAdjustmentQuote(QlIborIndex* index, int futuresDate, QlQuote* futuresQuote, QlQuote* volatility, QlQuote* meanReversion, char **e);
  QlQuote* DLLEXPORT qlImpliedStdDevQuote(int optionType, QlQuote* forward, QlQuote* price, double strike, double guess, double accuracy, unsigned maxIter, char **e);
  QlQuote* DLLEXPORT qlLastFixingQuote(QlIndex* index, char **e);
  int DLLEXPORT qlQuoteIsValid(QlQuote* o, char **e);
}
