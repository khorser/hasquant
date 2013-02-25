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

extern "C" {
  InterestRate *DLLEXPORT qlInterestRate(double r, DayCounter *dc, int comp, int freq,
    char **e);
  double DLLEXPORT qlInterestRateCompoundFactor1(InterestRate* o, int d1, int d2, int refStart, int refEnd, char **e);
  double DLLEXPORT qlInterestRateCompoundFactor(InterestRate* o, double t, char **e);
  double DLLEXPORT qlInterestRateDiscountFactor1(InterestRate* o, int d1, int d2, int refStart, int refEnd, char **e);
  double DLLEXPORT qlInterestRateDiscountFactor(InterestRate* o, double t, char **e);
  InterestRate* DLLEXPORT qlInterestRateEquivalentRate1(InterestRate* o, DayCounter* resultDC, int comp, int freq, int d1, int d2, int refStart, int refEnd, char **e);
  InterestRate* DLLEXPORT qlInterestRateEquivalentRate(InterestRate* o, int comp, int freq, double t, char **e);
  InterestRate* DLLEXPORT qlInterestRateImpliedRate1(InterestRate* o, double compound, DayCounter* resultDC, int comp, int freq, int d1, int d2, int refStart, int refEnd, char **e);
  InterestRate* DLLEXPORT qlInterestRateImpliedRate(InterestRate* o, double compound, DayCounter* resultDC, int comp, int freq, double t, char **e);
  double DLLEXPORT qlInterestRateRate(InterestRate* o);

  void DLLEXPORT qlFreeInterestRate(InterestRate *rate);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
