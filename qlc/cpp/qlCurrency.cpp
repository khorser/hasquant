#include <ql/currencies/all.hpp>

#include "qlaux.h"
#include "qlCurrency.h"

using namespace QuantLib;

typedef EnumObjectInfo<Currency> CurrencyInfo;
static const CurrencyInfo currencyInfo[] = {
  {"EUR", &CurrencyInfo::makeObject<EURCurrency>},
  {"ARS", &CurrencyInfo::makeObject<ARSCurrency>},
  {"ATS", &CurrencyInfo::makeObject<ATSCurrency>},
  {"AUD", &CurrencyInfo::makeObject<AUDCurrency>},
  {"BDT", &CurrencyInfo::makeObject<BDTCurrency>},
  {"BEF", &CurrencyInfo::makeObject<BEFCurrency>},
  {"BGL", &CurrencyInfo::makeObject<BGLCurrency>},
  {"BRL", &CurrencyInfo::makeObject<BRLCurrency>},
  {"BYR", &CurrencyInfo::makeObject<BYRCurrency>},
  {"CAD", &CurrencyInfo::makeObject<CADCurrency>},
  {"CHF", &CurrencyInfo::makeObject<CHFCurrency>},
  {"CLP", &CurrencyInfo::makeObject<CLPCurrency>},
  {"CNY", &CurrencyInfo::makeObject<CNYCurrency>},
  {"COP", &CurrencyInfo::makeObject<COPCurrency>},
  {"CYP", &CurrencyInfo::makeObject<CYPCurrency>},
  {"CZK", &CurrencyInfo::makeObject<CZKCurrency>},
  {"DEM", &CurrencyInfo::makeObject<DEMCurrency>},
  {"DKK", &CurrencyInfo::makeObject<DKKCurrency>},
  {"EEK", &CurrencyInfo::makeObject<EEKCurrency>},
  {"ESP", &CurrencyInfo::makeObject<ESPCurrency>},
  {"FIM", &CurrencyInfo::makeObject<FIMCurrency>},
  {"FRF", &CurrencyInfo::makeObject<FRFCurrency>},
  {"GBP", &CurrencyInfo::makeObject<GBPCurrency>},
  {"GRD", &CurrencyInfo::makeObject<GRDCurrency>},
  {"HKD", &CurrencyInfo::makeObject<HKDCurrency>},
  {"HUF", &CurrencyInfo::makeObject<HUFCurrency>},
  {"IEP", &CurrencyInfo::makeObject<IEPCurrency>},
  {"ILS", &CurrencyInfo::makeObject<ILSCurrency>},
  {"INR", &CurrencyInfo::makeObject<INRCurrency>},
  {"IQD", &CurrencyInfo::makeObject<IQDCurrency>},
  {"IRR", &CurrencyInfo::makeObject<IRRCurrency>},
  {"ISK", &CurrencyInfo::makeObject<ISKCurrency>},
  {"ITL", &CurrencyInfo::makeObject<ITLCurrency>},
  {"JPY", &CurrencyInfo::makeObject<JPYCurrency>},
  {"KRW", &CurrencyInfo::makeObject<KRWCurrency>},
  {"KWD", &CurrencyInfo::makeObject<KWDCurrency>},
  {"LTL", &CurrencyInfo::makeObject<LTLCurrency>},
  {"LUF", &CurrencyInfo::makeObject<LUFCurrency>},
  {"LVL", &CurrencyInfo::makeObject<LVLCurrency>},
  {"MTL", &CurrencyInfo::makeObject<MTLCurrency>},
  {"MXN", &CurrencyInfo::makeObject<MXNCurrency>},
  {"NLG", &CurrencyInfo::makeObject<NLGCurrency>},
  {"NOK", &CurrencyInfo::makeObject<NOKCurrency>},
  {"NPR", &CurrencyInfo::makeObject<NPRCurrency>},
  {"NZD", &CurrencyInfo::makeObject<NZDCurrency>},
  {"PEH", &CurrencyInfo::makeObject<PEHCurrency>},
  {"PEI", &CurrencyInfo::makeObject<PEICurrency>},
  {"PEN", &CurrencyInfo::makeObject<PEICurrency>},
  {"PKR", &CurrencyInfo::makeObject<PKRCurrency>},
  {"PLN", &CurrencyInfo::makeObject<PLNCurrency>},
  {"PTE", &CurrencyInfo::makeObject<PTECurrency>},
  {"ROL", &CurrencyInfo::makeObject<ROLCurrency>},
  {"RON", &CurrencyInfo::makeObject<RONCurrency>},
  {"SAR", &CurrencyInfo::makeObject<SARCurrency>},
  {"SEK", &CurrencyInfo::makeObject<SEKCurrency>},
  {"SGD", &CurrencyInfo::makeObject<SGDCurrency>},
  {"SIT", &CurrencyInfo::makeObject<SITCurrency>},
  {"SKK", &CurrencyInfo::makeObject<SKKCurrency>},
  {"THB", &CurrencyInfo::makeObject<THBCurrency>},
  {"TRL", &CurrencyInfo::makeObject<TRLCurrency>},
  {"TRY", &CurrencyInfo::makeObject<TRYCurrency>},
  {"TTD", &CurrencyInfo::makeObject<TTDCurrency>},
  {"TWD", &CurrencyInfo::makeObject<TWDCurrency>},
  {"USD", &CurrencyInfo::makeObject<USDCurrency>},
  {"VEB", &CurrencyInfo::makeObject<VEBCurrency>},
  {"ZAR", &CurrencyInfo::makeObject<ZARCurrency>}
};

Currency *qlCurrency(const char *name, char **e) {
  // use enumerations instead?
  try {
    const CurrencyInfo *last = LAST(currencyInfo);
    const CurrencyInfo *found = std::find_if(currencyInfo, last, CurrencyInfo::Cmp(name));
    if (found != last)
      return alloc(found->make());
    else
      QL_FAIL("Currency not found " << name);
  } catch (std::exception& er) {
    return handleException<Currency *>(e, er);
  }
}

void qlFreeCurrency(Currency *currency) { del(currency); }

const char *qlCurrencyName(Currency *currency) {
  std::string name = arg(currency)->name();
  return DUP(name.c_str());
}

char* qlCurrencyCode(Currency* o) { return DUP(arg(o)->code().c_str()); }
char* qlCurrencyFormat(Currency* o) { return DUP(arg(o)->format().c_str()); }
int qlCurrencyFractionsPerUnit(Currency* o) { return arg(o)->fractionsPerUnit(); }
char* qlCurrencyFractionSymbol(Currency* o) { return DUP(arg(o)->fractionSymbol().c_str()); }
int qlCurrencyNumericCode(Currency* o) { return arg(o)->numericCode(); }
char* qlCurrencySymbol(Currency* o) { return DUP(arg(o)->symbol().c_str()); }

void qlFreeRounding(Rounding *o) { del(o); }

Rounding* qlRounding(char **e) {
  try {
    return alloc(new Rounding());
  } catch (std::exception& er) {
    return handleException<Rounding*>(e, er);
  }
}

Rounding* qlRounding1(int precision, int type, int digit, char **e) {
  try {
    return alloc(new Rounding(precision, (Rounding::Type)type, digit));
  } catch (std::exception& er) {
    return handleException<Rounding*>(e, er);
  }
}

class CustomCurrency : public Currency {
public:
  CustomCurrency(const char* name, const char* code, int numericCode,
      const char* symbol, const char* fractionSymbol, int fractionsPerUnit,
      Rounding* rounding, const char* formatString,
      Currency* triangulationCurrency) {
    boost::shared_ptr<Data> data(new Data(name, code, numericCode,
          symbol, fractionSymbol, fractionsPerUnit,
          rounding ? *rounding : Rounding(),
          formatString,
          triangulationCurrency ? *triangulationCurrency : Currency()));
    data_ = data;
  }
};

Currency* qlCreateCurrency(char* name, char* code, int numericCode, char* symbol, char* fractionSymbol, int fractionsPerUnit, Rounding* rounding, char* formatString, Currency* triangulationCurrency, char **e) {
  try {
    return alloc(new CustomCurrency(arg(name), arg(code), numericCode,
          arg(symbol), arg(fractionSymbol), fractionsPerUnit,
          rounding, arg(formatString), triangulationCurrency));
  } catch (std::exception& er) {
    return handleException<Currency*>(e, er);
  }
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
