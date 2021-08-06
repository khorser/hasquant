#ifdef __cplusplus
extern "C" {
#endif
  InterestRate *qlInterestRate(double r, DayCounter *dc, int comp, int freq,
    char **e);
  double qlInterestRateCompoundFactor1(InterestRate* o, int d1, int d2, int refStart, int refEnd, char **e);
  double qlInterestRateCompoundFactor(InterestRate* o, double t, char **e);
  double qlInterestRateDiscountFactor1(InterestRate* o, int d1, int d2, int refStart, int refEnd, char **e);
  double qlInterestRateDiscountFactor(InterestRate* o, double t, char **e);
  InterestRate* qlInterestRateEquivalentRate1(InterestRate* o, DayCounter* resultDC, int comp, int freq, int d1, int d2, int refStart, int refEnd, char **e);
  InterestRate* qlInterestRateEquivalentRate(InterestRate* o, int comp, int freq, double t, char **e);
  InterestRate* qlInterestRateImpliedRate1(InterestRate* o, double compound, DayCounter* resultDC, int comp, int freq, int d1, int d2, int refStart, int refEnd, char **e);
  InterestRate* qlInterestRateImpliedRate(InterestRate* o, double compound, DayCounter* resultDC, int comp, int freq, double t, char **e);
  double qlInterestRateRate(InterestRate* o);

  void qlFreeInterestRate(InterestRate *rate);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
