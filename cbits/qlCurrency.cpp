#include <ql/currencies/all.hpp>

#include "qlaux.h"
#include "qlCurrency.h"

using namespace QuantLib;

typedef Currency *(*makeCcy)();

// should match the order in qlEnumObjects.h
static const makeCcy ccys[] = {[](){
    return static_cast<Currency *>(new ARSCurrency()); }
  , [](){ return static_cast<Currency *>(new ATSCurrency()); }
  , [](){ return static_cast<Currency *>(new AUDCurrency()); }
  , [](){ return static_cast<Currency *>(new BCHCurrency()); }
  , [](){ return static_cast<Currency *>(new BDTCurrency()); }
  , [](){ return static_cast<Currency *>(new BEFCurrency()); }
  , [](){ return static_cast<Currency *>(new BGLCurrency()); }
  , [](){ return static_cast<Currency *>(new BRLCurrency()); }
  , [](){ return static_cast<Currency *>(new BTCCurrency()); }
  , [](){ return static_cast<Currency *>(new BYRCurrency()); }
  , [](){ return static_cast<Currency *>(new CADCurrency()); }
  , [](){ return static_cast<Currency *>(new CHFCurrency()); }
  , [](){ return static_cast<Currency *>(new CLPCurrency()); }
  , [](){ return static_cast<Currency *>(new CNYCurrency()); }
  , [](){ return static_cast<Currency *>(new COPCurrency()); }
  , [](){ return static_cast<Currency *>(new CYPCurrency()); }
  , [](){ return static_cast<Currency *>(new CZKCurrency()); }
  , [](){ return static_cast<Currency *>(new DASHCurrency()); }
  , [](){ return static_cast<Currency *>(new DEMCurrency()); }
  , [](){ return static_cast<Currency *>(new DKKCurrency()); }
  , [](){ return static_cast<Currency *>(new EEKCurrency()); }
  , [](){ return static_cast<Currency *>(new ESPCurrency()); }
  , [](){ return static_cast<Currency *>(new ETCCurrency()); }
  , [](){ return static_cast<Currency *>(new ETHCurrency()); }
  , [](){ return static_cast<Currency *>(new EURCurrency()); }
  , [](){ return static_cast<Currency *>(new FIMCurrency()); }
  , [](){ return static_cast<Currency *>(new FRFCurrency()); }
  , [](){ return static_cast<Currency *>(new GBPCurrency()); }
  , [](){ return static_cast<Currency *>(new GRDCurrency()); }
  , [](){ return static_cast<Currency *>(new HKDCurrency()); }
  , [](){ return static_cast<Currency *>(new HUFCurrency()); }
  , [](){ return static_cast<Currency *>(new IDRCurrency()); }
  , [](){ return static_cast<Currency *>(new IEPCurrency()); }
  , [](){ return static_cast<Currency *>(new ILSCurrency()); }
  , [](){ return static_cast<Currency *>(new INRCurrency()); }
  , [](){ return static_cast<Currency *>(new IQDCurrency()); }
  , [](){ return static_cast<Currency *>(new IRRCurrency()); }
  , [](){ return static_cast<Currency *>(new ISKCurrency()); }
  , [](){ return static_cast<Currency *>(new ITLCurrency()); }
  , [](){ return static_cast<Currency *>(new JPYCurrency()); }
  , [](){ return static_cast<Currency *>(new KRWCurrency()); }
  , [](){ return static_cast<Currency *>(new KWDCurrency()); }
  , [](){ return static_cast<Currency *>(new KZTCurrency()); }
  , [](){ return static_cast<Currency *>(new LTCCurrency()); }
  , [](){ return static_cast<Currency *>(new LTLCurrency()); }
  , [](){ return static_cast<Currency *>(new LUFCurrency()); }
  , [](){ return static_cast<Currency *>(new LVLCurrency()); }
  , [](){ return static_cast<Currency *>(new MTLCurrency()); }
  , [](){ return static_cast<Currency *>(new MXNCurrency()); }
  , [](){ return static_cast<Currency *>(new MYRCurrency()); }
  , [](){ return static_cast<Currency *>(new NGNCurrency()); }
  , [](){ return static_cast<Currency *>(new NLGCurrency()); }
  , [](){ return static_cast<Currency *>(new NOKCurrency()); }
  , [](){ return static_cast<Currency *>(new NPRCurrency()); }
  , [](){ return static_cast<Currency *>(new NZDCurrency()); }
  , [](){ return static_cast<Currency *>(new PEHCurrency()); }
  , [](){ return static_cast<Currency *>(new PEICurrency()); }
  , [](){ return static_cast<Currency *>(new PENCurrency()); }
  , [](){ return static_cast<Currency *>(new PKRCurrency()); }
  , [](){ return static_cast<Currency *>(new PLNCurrency()); }
  , [](){ return static_cast<Currency *>(new PTECurrency()); }
  , [](){ return static_cast<Currency *>(new ROLCurrency()); }
  , [](){ return static_cast<Currency *>(new RONCurrency()); }
  , [](){ return static_cast<Currency *>(new RUBCurrency()); }
  , [](){ return static_cast<Currency *>(new SARCurrency()); }
  , [](){ return static_cast<Currency *>(new SEKCurrency()); }
  , [](){ return static_cast<Currency *>(new SGDCurrency()); }
  , [](){ return static_cast<Currency *>(new SITCurrency()); }
  , [](){ return static_cast<Currency *>(new SKKCurrency()); }
  , [](){ return static_cast<Currency *>(new THBCurrency()); }
  , [](){ return static_cast<Currency *>(new TRLCurrency()); }
  , [](){ return static_cast<Currency *>(new TRYCurrency()); }
  , [](){ return static_cast<Currency *>(new TTDCurrency()); }
  , [](){ return static_cast<Currency *>(new TWDCurrency()); }
  , [](){ return static_cast<Currency *>(new UAHCurrency()); }
  , [](){ return static_cast<Currency *>(new USDCurrency()); }
  , [](){ return static_cast<Currency *>(new VEBCurrency()); }
  , [](){ return static_cast<Currency *>(new VNDCurrency()); }
  , [](){ return static_cast<Currency *>(new XRPCurrency()); }
  , [](){ return static_cast<Currency *>(new ZARCurrency()); }
  , [](){ return static_cast<Currency *>(new ZECCurrency()); }
};

Currency *qlCurrency(int ccy, char **e) {
  try {
    if (ccy < 0 || ccy >= (int)LENGTH(ccys))
      QL_FAIL("Invalid currency index " << ccy);
    return alloc(ccys[ccy]());
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

class CustomCurrency : public Currency {
public:
  CustomCurrency(const char* name, const char* code, int numericCode,
      const char* symbol, const char* fractionSymbol, int fractionsPerUnit,
      Rounding* rounding, const char* formatString,
      Currency* triangulationCurrency) {
    ext::shared_ptr<Data> data(new Data(name, code, numericCode,
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
