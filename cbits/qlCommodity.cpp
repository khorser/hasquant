#include <ql/experimental/commodities/commoditytype.hpp>
#include <ql/experimental/commodities/unitofmeasure.hpp>
#include <ql/experimental/commodities/petroleumunitsofmeasure.hpp>
#include <ql/experimental/commodities/paymentterm.hpp>
#include <ql/time/calendar.hpp>
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
Calendar *qlPaymentTermCalendar(PaymentTerm *o) {return ret(new Calendar(arg(o)->calendar()));}
int qlPaymentTermEmpty(PaymentTerm *o) {return arg(o)->empty();}

int qlPaymentTermGetPaymentDate(PaymentTerm *o, int date, char **e) {
  try {return arg(o)->getPaymentDate(qlNullableDate(date)).serialNumber();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
