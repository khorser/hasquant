#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  Currency *DLLEXPORT qlCurrency(const char *name, char **e);
  const char *DLLEXPORT qlCurrencyName(Currency *currency);

  void DLLEXPORT qlFreeCurrency(Currency *currency);
  char* DLLEXPORT qlCurrencyCode(Currency* o);
  char* DLLEXPORT qlCurrencyFormat(Currency* o);
  int DLLEXPORT qlCurrencyFractionsPerUnit(Currency* o);
  char* DLLEXPORT qlCurrencyFractionSymbol(Currency* o);
  int DLLEXPORT qlCurrencyNumericCode(Currency* o);
  char* DLLEXPORT qlCurrencySymbol(Currency* o);
  void DLLEXPORT qlFreeRounding(Rounding *o);
  Rounding* DLLEXPORT qlRounding(char **e);
  Rounding* DLLEXPORT qlRounding1(int precision, int type, int digit, char **e);
  Currency* DLLEXPORT qlCreateCurrency(char* name, char* code, int numericCode, char* symbol, char* fractionSymbol, int fractionsPerUnit, Rounding* rounding, char* formatString, Currency* triangulationCurrency, char **e);
}
