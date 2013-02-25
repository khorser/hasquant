#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  QlFloatingRateCouponPricer *DLLEXPORT qlBlackIborCouponPricer(
    QlOptionletVolatilityStructure *vol, char **e);
  void DLLEXPORT qlFreeFloatingCouponPricer(QlFloatingRateCouponPricer *p);
}
