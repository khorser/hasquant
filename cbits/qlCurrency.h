#ifdef __cplusplus
extern "C" {
#endif
  Currency *qlCurrency(const char *name, char **e);
  const char *qlCurrencyName(Currency *currency);

  void qlFreeCurrency(Currency *currency);
  char* qlCurrencyCode(Currency* o);
  char* qlCurrencyFormat(Currency* o);
  int qlCurrencyFractionsPerUnit(Currency* o);
  char* qlCurrencyFractionSymbol(Currency* o);
  int qlCurrencyNumericCode(Currency* o);
  char* qlCurrencySymbol(Currency* o);
  Currency* qlCreateCurrency(char* name, char* code, int numericCode, char* symbol, char* fractionSymbol, int fractionsPerUnit, Rounding* rounding, char* formatString, Currency* triangulationCurrency, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
