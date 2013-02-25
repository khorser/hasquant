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
  const int *DLLEXPORT qlEnumerationValue(const char *name, unsigned *c);
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
