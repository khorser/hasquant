#ifdef __cplusplus
extern "C" {
#endif
  void qlFreeFdmSchemeDesc(FdmSchemeDesc *o);
  FdmSchemeDesc* qlFdmSchemeDesc(int type, double theta, double mu, char **e);
  FdmSchemeDesc* qlFdmSchemeDescCraigSneyd(char **e);
  FdmSchemeDesc* qlFdmSchemeDescDouglas(char **e);
  FdmSchemeDesc* qlFdmSchemeDescExplicitEuler(char **e);
  FdmSchemeDesc* qlFdmSchemeDescHundsdorfer(char **e);
  FdmSchemeDesc* qlFdmSchemeDescImplicitEuler(char **e);
  FdmSchemeDesc* qlFdmSchemeDescModifiedCraigSneyd(char **e);
  FdmSchemeDesc* qlFdmSchemeDescModifiedHundsdorfer(char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
