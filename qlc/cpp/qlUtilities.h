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
  const char *DLLEXPORT qlVersion();
  const char *DLLEXPORT qlBoostVersion();

  void DLLEXPORT qlFreeString(char *p);
  void DLLEXPORT qlFreeInts(int *p);
  void DLLEXPORT qlFreeDoubles(double *p);
  void DLLEXPORT qlFreePointerArray(void **p);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
