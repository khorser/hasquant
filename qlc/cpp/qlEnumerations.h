#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  const int *DLLEXPORT qlEnumerationValue(const char *name, unsigned *c);
}
