#include <ql/currencies/all.hpp>

#include "qlaux.h"
#include "qlCurrency.h"

using namespace QuantLib;

typedef Currency *(*makeCcy)();

// should match the order in qlEnumObjects.h
static const makeCcy ccys[] = {[](){ return (Currency *)new ARSCurrency(); }
  , [](){ return (Currency *)new ATSCurrency(); }
  , [](){ return (Currency *)new AUDCurrency(); }
  , [](){ return (Currency *)new BCHCurrency(); }
  , [](){ return (Currency *)new BDTCurrency(); }
  , [](){ return (Currency *)new BEFCurrency(); }
  , [](){ return (Currency *)new BGLCurrency(); }
  , [](){ return (Currency *)new BRLCurrency(); }
  , [](){ return (Currency *)new BTCCurrency(); }
  , [](){ return (Currency *)new BYRCurrency(); }
  , [](){ return (Currency *)new CADCurrency(); }
  , [](){ return (Currency *)new CHFCurrency(); }
  , [](){ return (Currency *)new CLPCurrency(); }
  , [](){ return (Currency *)new CNYCurrency(); }
  , [](){ return (Currency *)new COPCurrency(); }
  , [](){ return (Currency *)new CYPCurrency(); }
  , [](){ return (Currency *)new CZKCurrency(); }
  , [](){ return (Currency *)new DASHCurrency(); }
  , [](){ return (Currency *)new DEMCurrency(); }
  , [](){ return (Currency *)new DKKCurrency(); }
  , [](){ return (Currency *)new EEKCurrency(); }
  , [](){ return (Currency *)new ESPCurrency(); }
  , [](){ return (Currency *)new ETCCurrency(); }
  , [](){ return (Currency *)new ETHCurrency(); }
  , [](){ return (Currency *)new EURCurrency(); }
  , [](){ return (Currency *)new FIMCurrency(); }
  , [](){ return (Currency *)new FRFCurrency(); }
  , [](){ return (Currency *)new GBPCurrency(); }
  , [](){ return (Currency *)new GRDCurrency(); }
  , [](){ return (Currency *)new HKDCurrency(); }
  , [](){ return (Currency *)new HUFCurrency(); }
  , [](){ return (Currency *)new IDRCurrency(); }
  , [](){ return (Currency *)new IEPCurrency(); }
  , [](){ return (Currency *)new ILSCurrency(); }
  , [](){ return (Currency *)new INRCurrency(); }
  , [](){ return (Currency *)new IQDCurrency(); }
  , [](){ return (Currency *)new IRRCurrency(); }
  , [](){ return (Currency *)new ISKCurrency(); }
  , [](){ return (Currency *)new ITLCurrency(); }
  , [](){ return (Currency *)new JPYCurrency(); }
  , [](){ return (Currency *)new KRWCurrency(); }
  , [](){ return (Currency *)new KWDCurrency(); }
  , [](){ return (Currency *)new KZTCurrency(); }
  , [](){ return (Currency *)new LTCCurrency(); }
  , [](){ return (Currency *)new LTLCurrency(); }
  , [](){ return (Currency *)new LUFCurrency(); }
  , [](){ return (Currency *)new LVLCurrency(); }
  , [](){ return (Currency *)new MTLCurrency(); }
  , [](){ return (Currency *)new MXNCurrency(); }
  , [](){ return (Currency *)new MYRCurrency(); }
  , [](){ return (Currency *)new NGNCurrency(); }
  , [](){ return (Currency *)new NLGCurrency(); }
  , [](){ return (Currency *)new NOKCurrency(); }
  , [](){ return (Currency *)new NPRCurrency(); }
  , [](){ return (Currency *)new NZDCurrency(); }
  , [](){ return (Currency *)new PEHCurrency(); }
  , [](){ return (Currency *)new PEICurrency(); }
  , [](){ return (Currency *)new PENCurrency(); }
  , [](){ return (Currency *)new PKRCurrency(); }
  , [](){ return (Currency *)new PLNCurrency(); }
  , [](){ return (Currency *)new PTECurrency(); }
  , [](){ return (Currency *)new ROLCurrency(); }
  , [](){ return (Currency *)new RONCurrency(); }
  , [](){ return (Currency *)new RUBCurrency(); }
  , [](){ return (Currency *)new SARCurrency(); }
  , [](){ return (Currency *)new SEKCurrency(); }
  , [](){ return (Currency *)new SGDCurrency(); }
  , [](){ return (Currency *)new SITCurrency(); }
  , [](){ return (Currency *)new SKKCurrency(); }
  , [](){ return (Currency *)new THBCurrency(); }
  , [](){ return (Currency *)new TRLCurrency(); }
  , [](){ return (Currency *)new TRYCurrency(); }
  , [](){ return (Currency *)new TTDCurrency(); }
  , [](){ return (Currency *)new TWDCurrency(); }
  , [](){ return (Currency *)new UAHCurrency(); }
  , [](){ return (Currency *)new USDCurrency(); }
  , [](){ return (Currency *)new VEBCurrency(); }
  , [](){ return (Currency *)new VNDCurrency(); }
  , [](){ return (Currency *)new XRPCurrency(); }
  , [](){ return (Currency *)new ZARCurrency(); }
  , [](){ return (Currency *)new ZECCurrency(); }
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
