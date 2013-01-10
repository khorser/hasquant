#include <ql/currencies/all.hpp>

#include "ql.h"

using namespace QuantLib;

Currency *qlCurrency(const char *name, char **e)
{
  // use enumerations instead?
  try {
    Currency *c = 0;
    if (!strcmp("Currency", name))
      c = new Currency();
    else if (!strcmp("NoCurrency", name))
      c = new Currency();
    else if (!strcmp("EUR", name))
      c = new EURCurrency();
    else if (!strcmp("ARS", name))
      c = new ARSCurrency();
    else if (!strcmp("ATS", name))
      c = new ATSCurrency();
    else if (!strcmp("AUD", name))
      c = new AUDCurrency();
    else if (!strcmp("BDT", name))
      c = new BDTCurrency();
    else if (!strcmp("BEF", name))
      c = new BEFCurrency();
    else if (!strcmp("BGL", name))
      c = new BGLCurrency();
    else if (!strcmp("BRL", name))
      c = new BRLCurrency();
    else if (!strcmp("BYR", name))
      c = new BYRCurrency();
    else if (!strcmp("CAD", name))
      c = new CADCurrency();
    else if (!strcmp("CHF", name))
      c = new CHFCurrency();
    else if (!strcmp("CLP", name))
      c = new CLPCurrency();
    else if (!strcmp("CNY", name))
      c = new CNYCurrency();
    else if (!strcmp("COP", name))
      c = new COPCurrency();
    else if (!strcmp("CYP", name))
      c = new CYPCurrency();
    else if (!strcmp("CZK", name))
      c = new CZKCurrency();
    else if (!strcmp("DEM", name))
      c = new DEMCurrency();
    else if (!strcmp("DKK", name))
      c = new DKKCurrency();
    else if (!strcmp("EEK", name))
      c = new EEKCurrency();
    else if (!strcmp("ESP", name))
      c = new ESPCurrency();
    else if (!strcmp("FIM", name))
      c = new FIMCurrency();
    else if (!strcmp("FRF", name))
      c = new FRFCurrency();
    else if (!strcmp("GBP", name))
      c = new GBPCurrency();
    else if (!strcmp("GRD", name))
      c = new GRDCurrency();
    else if (!strcmp("HKD", name))
      c = new HKDCurrency();
    else if (!strcmp("HUF", name))
      c = new HUFCurrency();
    else if (!strcmp("IEP", name))
      c = new IEPCurrency();
    else if (!strcmp("ILS", name))
      c = new ILSCurrency();
    else if (!strcmp("INR", name))
      c = new INRCurrency();
    else if (!strcmp("IQD", name))
      c = new IQDCurrency();
    else if (!strcmp("IRR", name))
      c = new IRRCurrency();
    else if (!strcmp("ISK", name))
      c = new ISKCurrency();
    else if (!strcmp("ITL", name))
      c = new ITLCurrency();
    else if (!strcmp("JPY", name))
      c = new JPYCurrency();
    else if (!strcmp("KRW", name))
      c = new KRWCurrency();
    else if (!strcmp("KWD", name))
      c = new KWDCurrency();
    else if (!strcmp("LTL", name))
      c = new LTLCurrency();
    else if (!strcmp("LUF", name))
      c = new LUFCurrency();
    else if (!strcmp("LVL", name))
      c = new LVLCurrency();
    else if (!strcmp("MTL", name))
      c = new MTLCurrency();
    else if (!strcmp("MXN", name))
      c = new MXNCurrency();
    else if (!strcmp("NLG", name))
      c = new NLGCurrency();
    else if (!strcmp("NOK", name))
      c = new NOKCurrency();
    else if (!strcmp("NPR", name))
      c = new NPRCurrency();
    else if (!strcmp("NZD", name))
      c = new NZDCurrency();
    else if (!strcmp("PKR", name))
      c = new PKRCurrency();
    else if (!strcmp("PLN", name))
      c = new PLNCurrency();
    else if (!strcmp("PTE", name))
      c = new PTECurrency();
    else if (!strcmp("ROL", name))
      c = new ROLCurrency();
    else if (!strcmp("SAR", name))
      c = new SARCurrency();
    else if (!strcmp("SEK", name))
      c = new SEKCurrency();
    else if (!strcmp("SGD", name))
      c = new SGDCurrency();
    else if (!strcmp("SIT", name))
      c = new SITCurrency();
    else if (!strcmp("SKK", name))
      c = new SKKCurrency();
    else if (!strcmp("THB", name))
      c = new THBCurrency();
    else if (!strcmp("TRL", name))
      c = new TRLCurrency();
    else if (!strcmp("TRY", name))
      c = new TRYCurrency();
    else if (!strcmp("TTD", name))
      c = new TTDCurrency();
    else if (!strcmp("TWD", name))
      c = new TWDCurrency();
    else if (!strcmp("USD", name))
      c = new USDCurrency();
    else if (!strcmp("VEB", name))
      c = new VEBCurrency();
    else if (!strcmp("ZAR", name))
      c = new ZARCurrency();
    else
      QL_FAIL("Currency not found");
    return alloc(c);
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
