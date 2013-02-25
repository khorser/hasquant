#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  const char *DLLEXPORT qlVersion();
  const char *DLLEXPORT qlBoostVersion();

  void DLLEXPORT qlFreeString(char *p);
  void DLLEXPORT qlFreeInts(int *p);
  void DLLEXPORT qlFreeDoubles(double *p);
}
