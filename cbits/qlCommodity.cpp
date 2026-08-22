#include <ql/experimental/commodities/commoditytype.hpp>
#include <ql/experimental/commodities/unitofmeasure.hpp>
#include <ql/experimental/commodities/petroleumunitsofmeasure.hpp>
#include <ql/experimental/commodities/paymentterm.hpp>
#include <ql/experimental/commodities/quantity.hpp>
#include <ql/experimental/commodities/unitofmeasureconversion.hpp>
#include <ql/experimental/commodities/unitofmeasureconversionmanager.hpp>
#include <ql/experimental/commodities/commoditysettings.hpp>
#include <ql/time/calendar.hpp>
#include <ql/currency.hpp>
#include "qlaux.h"
#include "qlCommodity.h"

using namespace QuantLib;

/* CommodityType */

CommodityType *qlCommodityType(char *code, char *name, char **e) {
  // commoditytype.hpp's declaration names its params (code, name), but the out-of-line
  // definition in commoditytype.cpp takes (name, code) -- and that's what actually executes.
  try {return alloc(new CommodityType(arg(name), arg(code)));
  } catch (std::exception& er) {return handleException<CommodityType*>(e, er);}}

CommodityType *qlNullCommodityType(char **e) {
  try {return alloc(new CommodityType(NullCommodityType()));
  } catch (std::exception& er) {return handleException<CommodityType*>(e, er);}}

void qlFreeCommodityType(CommodityType *o) {del(o);}
char *qlCommodityTypeCode(CommodityType *o) {return DUP(arg(o)->code().c_str());}
char *qlCommodityTypeName(CommodityType *o) {return DUP(arg(o)->name().c_str());}
int qlCommodityTypeEmpty(CommodityType *o) {return arg(o)->empty();}

/* UnitOfMeasure */

UnitOfMeasure *qlUnitOfMeasure(char *name, char *code, int unitType, char **e) {
  try {return alloc(new UnitOfMeasure(arg(name), arg(code), (UnitOfMeasure::Type)unitType));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}

void qlFreeUnitOfMeasure(UnitOfMeasure *o) {del(o);}
char *qlUnitOfMeasureName(UnitOfMeasure *o) {return DUP(arg(o)->name().c_str());}
char *qlUnitOfMeasureCode(UnitOfMeasure *o) {return DUP(arg(o)->code().c_str());}
int qlUnitOfMeasureUnitType(UnitOfMeasure *o) {return arg(o)->unitType();}
int qlUnitOfMeasureEmpty(UnitOfMeasure *o) {return arg(o)->empty();}

UnitOfMeasure *qlLotUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(LotUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlBarrelUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(BarrelUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlMTUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(MTUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlMBUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(MBUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlGallonUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(GallonUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlLitreUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(LitreUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlKilolitreUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(KilolitreUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlTokyoKilolitreUnitOfMeasure(char **e) {
  try {return alloc(new UnitOfMeasure(TokyoKilolitreUnitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}

/* PaymentTerm */

PaymentTerm *qlPaymentTerm(char *name, int eventType, int offsetDays, Calendar *calendar, char **e) {
  try {return alloc(new PaymentTerm(arg(name), (PaymentTerm::EventType)eventType, offsetDays, *arg(calendar)));
  } catch (std::exception& er) {return handleException<PaymentTerm*>(e, er);}}

void qlFreePaymentTerm(PaymentTerm *o) {del(o);}
char *qlPaymentTermName(PaymentTerm *o) {return DUP(arg(o)->name().c_str());}
int qlPaymentTermEventType_(PaymentTerm *o) {return arg(o)->eventType();}
int qlPaymentTermOffsetDays(PaymentTerm *o) {return arg(o)->offsetDays();}
Calendar *qlPaymentTermCalendar(PaymentTerm *o, char **e) {
  try {return ret(new Calendar(arg(o)->calendar()));
  } catch (std::exception& er) {return handleException<Calendar*>(e, er);}}
int qlPaymentTermEmpty(PaymentTerm *o) {return arg(o)->empty();}

int qlPaymentTermGetPaymentDate(PaymentTerm *o, int date, char **e) {
  try {return arg(o)->getPaymentDate(qlNullableDate(date)).serialNumber();
  } catch (std::exception& er) {return handleException<int>(e, er);}}

/* Quantity -- see qlCommodity.h on why this is three flat arguments, not one tuple. */

double qlQuantityRoundedAmount(UnitOfMeasure *uom, double amount) {
  return arg(uom)->rounding()(amount);}

int qlQuantityClose(CommodityType *ct1, UnitOfMeasure *uom1, double amount1,
                    CommodityType *ct2, UnitOfMeasure *uom2, double amount2, int n, char **e) {
  try {return close(Quantity(*arg(ct1), *arg(uom1), amount1),
                    Quantity(*arg(ct2), *arg(uom2), amount2), n);
  } catch (std::exception& er) {return handleException<int>(e, er);}}

int qlQuantityCloseEnough(CommodityType *ct1, UnitOfMeasure *uom1, double amount1,
                          CommodityType *ct2, UnitOfMeasure *uom2, double amount2, int n, char **e) {
  try {return close_enough(Quantity(*arg(ct1), *arg(uom1), amount1),
                           Quantity(*arg(ct2), *arg(uom2), amount2), n);
  } catch (std::exception& er) {return handleException<int>(e, er);}}

/* UnitOfMeasureConversion */

UnitOfMeasureConversion *qlUnitOfMeasureConversion(CommodityType *commodityType, UnitOfMeasure *source,
                                                   UnitOfMeasure *target, double conversionFactor, char **e) {
  try {return alloc(new UnitOfMeasureConversion(*arg(commodityType), *arg(source), *arg(target), conversionFactor));
  } catch (std::exception& er) {return handleException<UnitOfMeasureConversion*>(e, er);}}

void qlFreeUnitOfMeasureConversion(UnitOfMeasureConversion *o) {del(o);}
UnitOfMeasure *qlUnitOfMeasureConversionSource(UnitOfMeasureConversion *o, char **e) {
  try {return ret(new UnitOfMeasure(arg(o)->source()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
UnitOfMeasure *qlUnitOfMeasureConversionTarget(UnitOfMeasureConversion *o, char **e) {
  try {return ret(new UnitOfMeasure(arg(o)->target()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
CommodityType *qlUnitOfMeasureConversionCommodityType(UnitOfMeasureConversion *o, char **e) {
  try {return ret(new CommodityType(arg(o)->commodityType()));
  } catch (std::exception& er) {return handleException<CommodityType*>(e, er);}}
int qlUnitOfMeasureConversionType_(UnitOfMeasureConversion *o) {return arg(o)->type();}
double qlUnitOfMeasureConversionFactor(UnitOfMeasureConversion *o) {return arg(o)->conversionFactor();}
char *qlUnitOfMeasureConversionCode(UnitOfMeasureConversion *o) {return DUP(arg(o)->code().c_str());}

double qlUnitOfMeasureConversionConvert(UnitOfMeasureConversion *o, CommodityType *ct, UnitOfMeasure *uom,
                                        double amount, CommodityType **outCt, UnitOfMeasure **outUom, char **e) {
  *outCt = 0; *outUom = 0;
  CommodityType *ct2 = 0;
  try {
    Quantity r = arg(o)->convert(Quantity(*arg(ct), *arg(uom), amount));
    ct2 = ret(new CommodityType(r.commodityType()));
    UnitOfMeasure *uom2 = ret(new UnitOfMeasure(r.unitOfMeasure()));
    *outCt = ct2; *outUom = uom2;
    return r.amount();
  } catch (std::exception& er) {
    delete ct2;
    return handleException<double>(e, er);
  }}

UnitOfMeasureConversion *qlUnitOfMeasureConversionChain(UnitOfMeasureConversion *r1, UnitOfMeasureConversion *r2, char **e) {
  try {return alloc(new UnitOfMeasureConversion(UnitOfMeasureConversion::chain(*arg(r1), *arg(r2))));
  } catch (std::exception& er) {return handleException<UnitOfMeasureConversion*>(e, er);}}

/* UnitOfMeasureConversionManager */

UnitOfMeasureConversion *qlUnitOfMeasureConversionManagerLookup(
    CommodityType *commodityType, UnitOfMeasure *source, UnitOfMeasure *target, int type, char **e) {
  try {return alloc(new UnitOfMeasureConversion(UnitOfMeasureConversionManager::instance().lookup(
      *arg(commodityType), *arg(source), *arg(target), (UnitOfMeasureConversion::Type)type)));
  } catch (std::exception& er) {return handleException<UnitOfMeasureConversion*>(e, er);}}

void qlUnitOfMeasureConversionManagerAdd(UnitOfMeasureConversion *c) {
  UnitOfMeasureConversionManager::instance().add(*arg(c));}

void qlUnitOfMeasureConversionManagerClear() {UnitOfMeasureConversionManager::instance().clear();}

/* CommoditySettings */

Currency *qlCommoditySettingsCurrency(char **e) {
  try {return ret(new Currency(CommoditySettings::instance().currency()));
  } catch (std::exception& er) {return handleException<Currency*>(e, er);}}
void qlCommoditySettingsSetCurrency(Currency *c) {CommoditySettings::instance().currency() = *arg(c);}
UnitOfMeasure *qlCommoditySettingsUnitOfMeasure(char **e) {
  try {return ret(new UnitOfMeasure(CommoditySettings::instance().unitOfMeasure()));
  } catch (std::exception& er) {return handleException<UnitOfMeasure*>(e, er);}}
void qlCommoditySettingsSetUnitOfMeasure(UnitOfMeasure *u) {CommoditySettings::instance().unitOfMeasure() = *arg(u);}
