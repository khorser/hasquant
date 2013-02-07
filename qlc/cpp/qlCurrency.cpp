#include <ql/currencies/all.hpp>

#include "qlaux.h"

using namespace QuantLib;

EnumObjectInfo<Currency> currencyInfo[] = {
  {"Currency", &makeObject<Currency, Currency>},
  {"NoCurrency", &makeObject<Currency, Currency>},
  {"EUR", &makeObject<Currency, EURCurrency>},
  {"ARS", &makeObject<Currency, ARSCurrency>},
  {"ATS", &makeObject<Currency, ATSCurrency>},
  {"AUD", &makeObject<Currency, AUDCurrency>},
  {"BDT", &makeObject<Currency, BDTCurrency>},
  {"BEF", &makeObject<Currency, BEFCurrency>},
  {"BGL", &makeObject<Currency, BGLCurrency>},
  {"BRL", &makeObject<Currency, BRLCurrency>},
  {"BYR", &makeObject<Currency, BYRCurrency>},
  {"CAD", &makeObject<Currency, CADCurrency>},
  {"CHF", &makeObject<Currency, CHFCurrency>},
  {"CLP", &makeObject<Currency, CLPCurrency>},
  {"CNY", &makeObject<Currency, CNYCurrency>},
  {"COP", &makeObject<Currency, COPCurrency>},
  {"CYP", &makeObject<Currency, CYPCurrency>},
  {"CZK", &makeObject<Currency, CZKCurrency>},
  {"DEM", &makeObject<Currency, DEMCurrency>},
  {"DKK", &makeObject<Currency, DKKCurrency>},
  {"EEK", &makeObject<Currency, EEKCurrency>},
  {"ESP", &makeObject<Currency, ESPCurrency>},
  {"FIM", &makeObject<Currency, FIMCurrency>},
  {"FRF", &makeObject<Currency, FRFCurrency>},
  {"GBP", &makeObject<Currency, GBPCurrency>},
  {"GRD", &makeObject<Currency, GRDCurrency>},
  {"HKD", &makeObject<Currency, HKDCurrency>},
  {"HUF", &makeObject<Currency, HUFCurrency>},
  {"IEP", &makeObject<Currency, IEPCurrency>},
  {"ILS", &makeObject<Currency, ILSCurrency>},
  {"INR", &makeObject<Currency, INRCurrency>},
  {"IQD", &makeObject<Currency, IQDCurrency>},
  {"IRR", &makeObject<Currency, IRRCurrency>},
  {"ISK", &makeObject<Currency, ISKCurrency>},
  {"ITL", &makeObject<Currency, ITLCurrency>},
  {"JPY", &makeObject<Currency, JPYCurrency>},
  {"KRW", &makeObject<Currency, KRWCurrency>},
  {"KWD", &makeObject<Currency, KWDCurrency>},
  {"LTL", &makeObject<Currency, LTLCurrency>},
  {"LUF", &makeObject<Currency, LUFCurrency>},
  {"LVL", &makeObject<Currency, LVLCurrency>},
  {"MTL", &makeObject<Currency, MTLCurrency>},
  {"MXN", &makeObject<Currency, MXNCurrency>},
  {"NLG", &makeObject<Currency, NLGCurrency>},
  {"NOK", &makeObject<Currency, NOKCurrency>},
  {"NPR", &makeObject<Currency, NPRCurrency>},
  {"NZD", &makeObject<Currency, NZDCurrency>},
  {"PEH", &makeObject<Currency, PEHCurrency>},
  {"PEI", &makeObject<Currency, PEICurrency>},
  {"PEN", &makeObject<Currency, PEICurrency>},
  {"PKR", &makeObject<Currency, PKRCurrency>},
  {"PLN", &makeObject<Currency, PLNCurrency>},
  {"PTE", &makeObject<Currency, PTECurrency>},
  {"ROL", &makeObject<Currency, ROLCurrency>},
  {"RON", &makeObject<Currency, RONCurrency>},
  {"SAR", &makeObject<Currency, SARCurrency>},
  {"SEK", &makeObject<Currency, SEKCurrency>},
  {"SGD", &makeObject<Currency, SGDCurrency>},
  {"SIT", &makeObject<Currency, SITCurrency>},
  {"SKK", &makeObject<Currency, SKKCurrency>},
  {"THB", &makeObject<Currency, THBCurrency>},
  {"TRL", &makeObject<Currency, TRLCurrency>},
  {"TRY", &makeObject<Currency, TRYCurrency>},
  {"TTD", &makeObject<Currency, TTDCurrency>},
  {"TWD", &makeObject<Currency, TWDCurrency>},
  {"USD", &makeObject<Currency, USDCurrency>},
  {"VEB", &makeObject<Currency, VEBCurrency>},
  {"ZAR", &makeObject<Currency, ZARCurrency>}
};

Currency *qlCurrency(const char *name, char **e) {
  // use enumerations instead?
  try {
    EnumObjectInfo<Currency> *last = currencyInfo + LENGTH(currencyInfo);
    EnumObjectInfo<Currency> *found = std::find_if(currencyInfo, last, EnumObjectInfoComp<Currency>(name));
    if (found != last)
      return alloc(found->make());
    else
      QL_FAIL("Currency not found " << name);
  } catch (std::exception& er) {
    return handleException<Currency *>(e, er);
  }
}

void  qlFreeCurrency(Currency *currency) {
  del(currency);
}

const char *qlCurrencyName(Currency *currency) {
  std::string name = arg(currency)->name();
  return DUP(name.c_str());
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
