#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#else
# define DLLEXPORT
#endif

extern "C" {
  void DLLEXPORT qlFreeSwap(QlSwap *o);
  QlInstrument* DLLEXPORT qlSwapAsInstrument(QlSwap *o);
  void DLLEXPORT qlFreeVanillaSwap(QlVanillaSwap *o);
  QlSwap* DLLEXPORT qlVanillaSwapAsSwap(QlVanillaSwap *o);
  void DLLEXPORT qlFreeBMASwap(QlBMASwap *o);
  QlSwap* DLLEXPORT qlBMASwapAsSwap(QlBMASwap *o);
  void DLLEXPORT qlFreeOvernightIndexedSwap(QlOvernightIndexedSwap *o);
  QlSwap* DLLEXPORT qlOvernightIndexedSwapAsSwap(QlOvernightIndexedSwap *o);
  void DLLEXPORT qlFreeAssetSwap(QlAssetSwap *o);
  QlSwap* DLLEXPORT qlAssetSwapAsSwap(QlAssetSwap *o);
  QlOvernightIndexedSwap* DLLEXPORT qlOvernightIndexedSwap(int type, double nominal, Schedule* schedule, double fixedRate, DayCounter* fixedDC, QlOvernightIndex* overnightIndex, double spread, char **e);
  QlOvernightIndexedSwap* DLLEXPORT qlOvernightIndexedSwap1(int type, unsigned nominalsLen, double* nominals, Schedule* schedule, double fixedRate, DayCounter* fixedDC, QlOvernightIndex* overnightIndex, double spread, char **e);
  QlSwap* DLLEXPORT qlSwap1(unsigned legsLen, Leg** legs, int *payer, char **e);
  QlAssetSwap* DLLEXPORT qlAssetSwap1(int parAssetSwap, QlBond* bond, double bondCleanPrice, double nonParRepayment, double gearing, QlIborIndex* iborIndex, double spread, DayCounter* floatingDayCount, int dealMaturity, int payBondCoupon, char **e);
  QlAssetSwap* DLLEXPORT qlAssetSwap(int payBondCoupon, QlBond* bond, double bondCleanPrice, QlIborIndex* iborIndex, double spread, Schedule* floatSchedule, DayCounter* floatingDayCount, int parAssetSwap, char **e);
  QlBMASwap* DLLEXPORT qlBMASwap(int type, double nominal, Schedule* liborSchedule, double liborFraction, double liborSpread, QlIborIndex* liborIndex, DayCounter* liborDayCount, Schedule* bmaSchedule, QlBMAIndex* bmaIndex, DayCounter* bmaDayCount, char **e);
  QlVanillaSwap* DLLEXPORT qlVanillaSwap(int type, double nominal, Schedule* fixedSchedule, double fixedRate, DayCounter* fixedDayCount, Schedule* floatSchedule, QlIborIndex* iborIndex, double spread, DayCounter* floatingDayCount, int paymentConvention, char **e);
  QlSwap* DLLEXPORT qlSwap(Leg* firstLeg, Leg* secondLeg, char **e);
  Leg* DLLEXPORT qlSwapLeg(QlSwap* o, unsigned j, char **e);
  Leg* DLLEXPORT qlVanillaSwapFixedLeg(QlVanillaSwap* o, char **e);
  Leg* DLLEXPORT qlVanillaSwapFloatingLeg(QlVanillaSwap* o, char **e);
  Leg* DLLEXPORT qlAssetSwapBondLeg(QlAssetSwap* o, char **e);
  Leg* DLLEXPORT qlAssetSwapFloatingLeg(QlAssetSwap* o, char **e);
  Leg* DLLEXPORT qlBMASwapBmaLeg(QlBMASwap* o, char **e);
  Leg* DLLEXPORT qlBMASwapLiborLeg(QlBMASwap* o, char **e);
  Leg* DLLEXPORT qlOvernightIndexedSwapFixedLeg(QlOvernightIndexedSwap* o, char **e);
  Leg* DLLEXPORT qlOvernightIndexedSwapOvernightLeg(QlOvernightIndexedSwap* o, char **e);
  double DLLEXPORT qlAssetSwapCleanPrice(QlAssetSwap* o, char **e);
  double DLLEXPORT qlAssetSwapFairCleanPrice(QlAssetSwap* o, char **e);
  double DLLEXPORT qlAssetSwapFairNonParRepayment(QlAssetSwap* o, char **e);
  double DLLEXPORT qlAssetSwapFairSpread(QlAssetSwap* o, char **e);
  double DLLEXPORT qlAssetSwapFloatingLegBPS(QlAssetSwap* o, char **e);
  double DLLEXPORT qlAssetSwapFloatingLegNPV(QlAssetSwap* o, char **e);
  double DLLEXPORT qlAssetSwapNonParRepayment(QlAssetSwap* o, char **e);
  int DLLEXPORT qlAssetSwapParSwap(QlAssetSwap* o, char **e);
  int DLLEXPORT qlAssetSwapPayBondCoupon(QlAssetSwap* o, char **e);
  double DLLEXPORT qlBMASwapBmaLegBPS(QlBMASwap* o, char **e);
  double DLLEXPORT qlBMASwapBmaLegNPV(QlBMASwap* o, char **e);
  double DLLEXPORT qlBMASwapFairLiborFraction(QlBMASwap* o, char **e);
  double DLLEXPORT qlBMASwapFairLiborSpread(QlBMASwap* o, char **e);
  double DLLEXPORT qlBMASwapLiborFraction(QlBMASwap* o, char **e);
  double DLLEXPORT qlBMASwapLiborLegBPS(QlBMASwap* o, char **e);
  double DLLEXPORT qlBMASwapLiborLegNPV(QlBMASwap* o, char **e);
  double DLLEXPORT qlOvernightIndexedSwapFairRate(QlOvernightIndexedSwap* o, char **e);
  double DLLEXPORT qlOvernightIndexedSwapFairSpread(QlOvernightIndexedSwap* o, char **e);
  double DLLEXPORT qlOvernightIndexedSwapFixedLegBPS(QlOvernightIndexedSwap* o, char **e);
  double DLLEXPORT qlOvernightIndexedSwapFixedLegNPV(QlOvernightIndexedSwap* o, char **e);
  double DLLEXPORT qlOvernightIndexedSwapOvernightLegBPS(QlOvernightIndexedSwap* o, char **e);
  double DLLEXPORT qlOvernightIndexedSwapOvernightLegNPV(QlOvernightIndexedSwap* o, char **e);
  double DLLEXPORT qlSwapEndDiscounts(QlSwap* o, unsigned j, char **e);
  double DLLEXPORT qlSwapLegBPS(QlSwap* o, unsigned j, char **e);
  double DLLEXPORT qlSwapLegNPV(QlSwap* o, unsigned j, char **e);
  int DLLEXPORT qlSwapMaturityDate(QlSwap* o, char **e);
  double DLLEXPORT qlSwapNpvDateDiscount(QlSwap* o, char **e);
  int DLLEXPORT qlSwapStartDate(QlSwap* o, char **e);
  double DLLEXPORT qlSwapStartDiscounts(QlSwap* o, unsigned j, char **e);
  double DLLEXPORT qlVanillaSwapFairRate(QlVanillaSwap* o, char **e);
  double DLLEXPORT qlVanillaSwapFairSpread(QlVanillaSwap* o, char **e);
  double DLLEXPORT qlVanillaSwapFixedLegBPS(QlVanillaSwap* o, char **e);
  double DLLEXPORT qlVanillaSwapFixedLegNPV(QlVanillaSwap* o, char **e);
  double DLLEXPORT qlVanillaSwapFloatingLegBPS(QlVanillaSwap* o, char **e);
  double DLLEXPORT qlVanillaSwapFloatingLegNPV(QlVanillaSwap* o, char **e);
}
