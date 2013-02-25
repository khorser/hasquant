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
  QlFloatingRateCouponPricer *DLLEXPORT qlBlackIborCouponPricer(
    QlOptionletVolatilityStructure *vol, char **e);
  void DLLEXPORT qlFreeFloatingCouponPricer(QlFloatingRateCouponPricer *p);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
