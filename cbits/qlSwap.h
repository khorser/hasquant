#ifdef __cplusplus
extern "C" {
#endif
  void qlFreeSwap(QlSwap *o);
  QlInstrument* qlSwapAsInstrument(QlSwap *o);
  void qlFreeVanillaSwap(QlVanillaSwap *o);
  QlSwap* qlVanillaSwapAsSwap(QlVanillaSwap *o);
  void qlFreeBMASwap(QlBMASwap *o);
  QlSwap* qlBMASwapAsSwap(QlBMASwap *o);
  void qlFreeOvernightIndexedSwap(QlOvernightIndexedSwap *o);
  QlSwap* qlOvernightIndexedSwapAsSwap(QlOvernightIndexedSwap *o);
  void qlFreeAssetSwap(QlAssetSwap *o);
//  QlSwap* qlAssetSwapAsSwap(QlAssetSwap *o);
//  QlOvernightIndexedSwap* qlOvernightIndexedSwap(int type, double nominal, Schedule* schedule, double fixedRate, DayCounter* fixedDC, QlOvernightIndex* overnightIndex, double spread, char **e);
//  QlOvernightIndexedSwap* qlOvernightIndexedSwap1(int type, unsigned nominalsLen, double* nominals, Schedule* schedule, double fixedRate, DayCounter* fixedDC, QlOvernightIndex* overnightIndex, double spread, char **e);
//  QlSwap* qlSwap1(unsigned legsLen, Leg** legs, int *payer, char **e);
//  QlAssetSwap* qlAssetSwap1(int parAssetSwap, QlBond* bond, double bondCleanPrice, double nonParRepayment, double gearing, QlIborIndex* iborIndex, double spread, DayCounter* floatingDayCount, int dealMaturity, int payBondCoupon, char **e);
//  QlAssetSwap* qlAssetSwap(int payBondCoupon, QlBond* bond, double bondCleanPrice, QlIborIndex* iborIndex, double spread, Schedule* floatSchedule, DayCounter* floatingDayCount, int parAssetSwap, char **e);
//  QlBMASwap* qlBMASwap(int type, double nominal, Schedule* liborSchedule, double liborFraction, double liborSpread, QlIborIndex* liborIndex, DayCounter* liborDayCount, Schedule* bmaSchedule, QlBMAIndex* bmaIndex, DayCounter* bmaDayCount, char **e);
//  QlVanillaSwap* qlVanillaSwap(int type, double nominal, Schedule* fixedSchedule, double fixedRate, DayCounter* fixedDayCount, Schedule* floatSchedule, QlIborIndex* iborIndex, double spread, DayCounter* floatingDayCount, int paymentConvention, char **e);
//  QlSwap* qlSwap(Leg* firstLeg, Leg* secondLeg, char **e);
  Leg* qlSwapLeg(QlSwap* o, unsigned j, char **e);
  Leg* qlVanillaSwapFixedLeg(QlVanillaSwap* o, char **e);
  Leg* qlVanillaSwapFloatingLeg(QlVanillaSwap* o, char **e);
  Leg* qlAssetSwapBondLeg(QlAssetSwap* o, char **e);
  Leg* qlAssetSwapFloatingLeg(QlAssetSwap* o, char **e);
  Leg* qlBMASwapBmaLeg(QlBMASwap* o, char **e);
  Leg* qlBMASwapLiborLeg(QlBMASwap* o, char **e);
  Leg* qlOvernightIndexedSwapFixedLeg(QlOvernightIndexedSwap* o, char **e);
  Leg* qlOvernightIndexedSwapOvernightLeg(QlOvernightIndexedSwap* o, char **e);
  double qlAssetSwapCleanPrice(QlAssetSwap* o, char **e);
  double qlAssetSwapFairCleanPrice(QlAssetSwap* o, char **e);
  double qlAssetSwapFairNonParRepayment(QlAssetSwap* o, char **e);
  double qlAssetSwapFairSpread(QlAssetSwap* o, char **e);
  double qlAssetSwapFloatingLegBPS(QlAssetSwap* o, char **e);
  double qlAssetSwapFloatingLegNPV(QlAssetSwap* o, char **e);
  double qlAssetSwapNonParRepayment(QlAssetSwap* o, char **e);
  int qlAssetSwapParSwap(QlAssetSwap* o, char **e);
  int qlAssetSwapPayBondCoupon(QlAssetSwap* o, char **e);
  double qlBMASwapBmaLegBPS(QlBMASwap* o, char **e);
  double qlBMASwapBmaLegNPV(QlBMASwap* o, char **e);
  double qlBMASwapFairLiborFraction(QlBMASwap* o, char **e);
  double qlBMASwapFairLiborSpread(QlBMASwap* o, char **e);
  double qlBMASwapLiborFraction(QlBMASwap* o, char **e);
  double qlBMASwapLiborLegBPS(QlBMASwap* o, char **e);
  double qlBMASwapLiborLegNPV(QlBMASwap* o, char **e);
  double qlOvernightIndexedSwapFairRate(QlOvernightIndexedSwap* o, char **e);
  double qlOvernightIndexedSwapFairSpread(QlOvernightIndexedSwap* o, char **e);
  double qlOvernightIndexedSwapFixedLegBPS(QlOvernightIndexedSwap* o, char **e);
  double qlOvernightIndexedSwapFixedLegNPV(QlOvernightIndexedSwap* o, char **e);
  double qlOvernightIndexedSwapOvernightLegBPS(QlOvernightIndexedSwap* o, char **e);
  double qlOvernightIndexedSwapOvernightLegNPV(QlOvernightIndexedSwap* o, char **e);
  double qlSwapEndDiscounts(QlSwap* o, unsigned j, char **e);
  double qlSwapLegBPS(QlSwap* o, unsigned j, char **e);
  double qlSwapLegNPV(QlSwap* o, unsigned j, char **e);
  int qlSwapMaturityDate(QlSwap* o, char **e);
  double qlSwapNpvDateDiscount(QlSwap* o, char **e);
  int qlSwapStartDate(QlSwap* o, char **e);
  double qlSwapStartDiscounts(QlSwap* o, unsigned j, char **e);
  double qlVanillaSwapFairRate(QlVanillaSwap* o, char **e);
  double qlVanillaSwapFairSpread(QlVanillaSwap* o, char **e);
  double qlVanillaSwapFixedLegBPS(QlVanillaSwap* o, char **e);
  double qlVanillaSwapFixedLegNPV(QlVanillaSwap* o, char **e);
  double qlVanillaSwapFloatingLegBPS(QlVanillaSwap* o, char **e);
  double qlVanillaSwapFloatingLegNPV(QlVanillaSwap* o, char **e);
#ifdef __cplusplus
}
#endif

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
