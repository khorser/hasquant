#ifdef __cplusplus
extern "C" {
#endif
  /* CommodityType */
  CommodityType *qlCommodityType(char *code, char *name, char **e);
  CommodityType *qlNullCommodityType(char **e);
  void qlFreeCommodityType(CommodityType *o);
  char *qlCommodityTypeCode(CommodityType *o);
  char *qlCommodityTypeName(CommodityType *o);
  int qlCommodityTypeEmpty(CommodityType *o);

  /* UnitOfMeasure */
  UnitOfMeasure *qlUnitOfMeasure(char *name, char *code, int unitType, char **e);
  void qlFreeUnitOfMeasure(UnitOfMeasure *o);
  char *qlUnitOfMeasureName(UnitOfMeasure *o);
  char *qlUnitOfMeasureCode(UnitOfMeasure *o);
  int qlUnitOfMeasureUnitType(UnitOfMeasure *o);
  int qlUnitOfMeasureEmpty(UnitOfMeasure *o);
  UnitOfMeasure *qlLotUnitOfMeasure(char **e);
  UnitOfMeasure *qlBarrelUnitOfMeasure(char **e);
  UnitOfMeasure *qlMTUnitOfMeasure(char **e);
  UnitOfMeasure *qlMBUnitOfMeasure(char **e);
  UnitOfMeasure *qlGallonUnitOfMeasure(char **e);
  UnitOfMeasure *qlLitreUnitOfMeasure(char **e);
  UnitOfMeasure *qlKilolitreUnitOfMeasure(char **e);
  UnitOfMeasure *qlTokyoKilolitreUnitOfMeasure(char **e);

  /* PaymentTerm */
  PaymentTerm *qlPaymentTerm(char *name, int eventType, int offsetDays, Calendar *calendar, char **e);
  void qlFreePaymentTerm(PaymentTerm *o);
  char *qlPaymentTermName(PaymentTerm *o);
  int qlPaymentTermEventType_(PaymentTerm *o);
  int qlPaymentTermOffsetDays(PaymentTerm *o);
  Calendar *qlPaymentTermCalendar(PaymentTerm *o);
  int qlPaymentTermEmpty(PaymentTerm *o);
  int qlPaymentTermGetPaymentDate(PaymentTerm *o, int date, char **e);
#ifdef __cplusplus
}
#endif
