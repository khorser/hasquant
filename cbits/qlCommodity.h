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

  /* Quantity -- marshalled as flat (CommodityType, UnitOfMeasure, double) triples throughout,
     since c2hs's `&` tuple-splitter caps at two C arguments (confirmed against its source: the
     `twoCVal` marshaller consumes exactly [ct1, ct2], with no three-way variant). */
  double qlQuantityRoundedAmount(UnitOfMeasure *uom, double amount);
  int qlQuantityClose(CommodityType *ct1, UnitOfMeasure *uom1, double amount1,
                      CommodityType *ct2, UnitOfMeasure *uom2, double amount2, int n, char **e);
  int qlQuantityCloseEnough(CommodityType *ct1, UnitOfMeasure *uom1, double amount1,
                            CommodityType *ct2, UnitOfMeasure *uom2, double amount2, int n, char **e);

  /* UnitOfMeasureConversion */
  UnitOfMeasureConversion *qlUnitOfMeasureConversion(CommodityType *commodityType, UnitOfMeasure *source,
                                                     UnitOfMeasure *target, double conversionFactor, char **e);
  void qlFreeUnitOfMeasureConversion(UnitOfMeasureConversion *o);
  UnitOfMeasure *qlUnitOfMeasureConversionSource(UnitOfMeasureConversion *o);
  UnitOfMeasure *qlUnitOfMeasureConversionTarget(UnitOfMeasureConversion *o);
  CommodityType *qlUnitOfMeasureConversionCommodityType(UnitOfMeasureConversion *o);
  int qlUnitOfMeasureConversionType_(UnitOfMeasureConversion *o);
  double qlUnitOfMeasureConversionFactor(UnitOfMeasureConversion *o);
  char *qlUnitOfMeasureConversionCode(UnitOfMeasureConversion *o);
  double qlUnitOfMeasureConversionConvert(UnitOfMeasureConversion *o, CommodityType *ct, UnitOfMeasure *uom,
                                          double amount, CommodityType **outCt, UnitOfMeasure **outUom, char **e);
  UnitOfMeasureConversion *qlUnitOfMeasureConversionChain(UnitOfMeasureConversion *r1, UnitOfMeasureConversion *r2, char **e);

  /* UnitOfMeasureConversionManager (singleton) */
  UnitOfMeasureConversion *qlUnitOfMeasureConversionManagerLookup(
      CommodityType *commodityType, UnitOfMeasure *source, UnitOfMeasure *target, int type, char **e);
  void qlUnitOfMeasureConversionManagerAdd(UnitOfMeasureConversion *c);
  void qlUnitOfMeasureConversionManagerClear(void);

  /* CommoditySettings (singleton) */
  Currency *qlCommoditySettingsCurrency(void);
  void qlCommoditySettingsSetCurrency(Currency *c);
  UnitOfMeasure *qlCommoditySettingsUnitOfMeasure(void);
  void qlCommoditySettingsSetUnitOfMeasure(UnitOfMeasure *u);
#ifdef __cplusplus
}
#endif
