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
  void DLLEXPORT qlFreeFdmSchemeDesc(FdmSchemeDesc *o);
  FdmSchemeDesc* DLLEXPORT qlFdmSchemeDesc(int type, double theta, double mu, char **e);
  FdmSchemeDesc* DLLEXPORT qlFdmSchemeDescCraigSneyd(char **e);
  FdmSchemeDesc* DLLEXPORT qlFdmSchemeDescDouglas(char **e);
  FdmSchemeDesc* DLLEXPORT qlFdmSchemeDescExplicitEuler(char **e);
  FdmSchemeDesc* DLLEXPORT qlFdmSchemeDescHundsdorfer(char **e);
  FdmSchemeDesc* DLLEXPORT qlFdmSchemeDescImplicitEuler(char **e);
  FdmSchemeDesc* DLLEXPORT qlFdmSchemeDescModifiedCraigSneyd(char **e);
  FdmSchemeDesc* DLLEXPORT qlFdmSchemeDescModifiedHundsdorfer(char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
