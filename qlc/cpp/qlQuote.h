#ifdef _WIN32
# if defined(DLLSOURCE)
#  define DLLEXPORT __declspec(dllexport)
# elif defined(DLLUSE)
#  define DLLEXPORT __declspec(dllimport)
# else
#  define DLLEXPORT
# endif
#else
# define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif
  QlSimpleQuote *DLLEXPORT qlSimpleQuote(double value, char **e);
  double DLLEXPORT qlQuoteValue(QlQuote *quote, char **e);

  void DLLEXPORT qlFreeQuote(QlQuote *quote);
  void DLLEXPORT qlFreeSimpleQuote(QlSimpleQuote *o);
  QlQuote* DLLEXPORT qlSimpleQuoteAsQuote(QlSimpleQuote *o);
  double DLLEXPORT qlSimpleQuoteSetValue(QlSimpleQuote* o, double value, char **e);
  QlQuote* DLLEXPORT qlEurodollarFuturesImpliedStdDevQuote(QlQuote* forward, QlQuote* callPrice, QlQuote* putPrice, double strike, double guess, double accuracy, unsigned maxIter, char **e);
  QlQuote* DLLEXPORT qlForwardSwapQuote(QlSwapIndex* swapIndex, QlQuote* spread, int, int, char **e);
  QlQuote* DLLEXPORT qlForwardValueQuote(QlIndex* index, int fixingDate, char **e);
  QlQuote* DLLEXPORT qlFuturesConvAdjustmentQuote1(QlIborIndex* index, char* immCode, QlQuote* futuresQuote, QlQuote* volatility, QlQuote* meanReversion, char **e);
  QlQuote* DLLEXPORT qlFuturesConvAdjustmentQuote(QlIborIndex* index, int futuresDate, QlQuote* futuresQuote, QlQuote* volatility, QlQuote* meanReversion, char **e);
  QlQuote* DLLEXPORT qlImpliedStdDevQuote(int optionType, QlQuote* forward, QlQuote* price, double strike, double guess, double accuracy, unsigned maxIter, char **e);
  QlQuote* DLLEXPORT qlLastFixingQuote(QlIndex* index, char **e);
  int DLLEXPORT qlQuoteIsValid(QlQuote* o, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
