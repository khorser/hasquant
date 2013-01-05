#include <ql/currencies/all.hpp>

#include "ql.h"

using namespace QuantLib;

void *qlCurrency(const char *name, char **e)
{
  *e = 0;
  // use enumerations instead?
  try {
    if (!strcmp("Currency", name))
      return new Currency();
    else if (!strcmp("NoCurrency", name))
      return new Currency();
    else if (!strcmp("EUR", name))
      return new EURCurrency();
    else if (!strcmp("ARS", name))
      return new ARSCurrency();
    else if (!strcmp("ATS", name))
      return new ATSCurrency();
    else if (!strcmp("AUD", name))
      return new AUDCurrency();
    else if (!strcmp("BDT", name))
      return new BDTCurrency();
    else if (!strcmp("BEF", name))
      return new BEFCurrency();
    else if (!strcmp("BGL", name))
      return new BGLCurrency();
    else if (!strcmp("BRL", name))
      return new BRLCurrency();
    else if (!strcmp("BYR", name))
      return new BYRCurrency();
    else if (!strcmp("CAD", name))
      return new CADCurrency();
    else if (!strcmp("CHF", name))
      return new CHFCurrency();
    else if (!strcmp("CLP", name))
      return new CLPCurrency();
    else if (!strcmp("CNY", name))
      return new CNYCurrency();
    else if (!strcmp("COP", name))
      return new COPCurrency();
    else if (!strcmp("CYP", name))
      return new CYPCurrency();
    else if (!strcmp("CZK", name))
      return new CZKCurrency();
    else if (!strcmp("DEM", name))
      return new DEMCurrency();
    else if (!strcmp("DKK", name))
      return new DKKCurrency();
    else if (!strcmp("EEK", name))
      return new EEKCurrency();
    else if (!strcmp("ESP", name))
      return new ESPCurrency();
    else if (!strcmp("FIM", name))
      return new FIMCurrency();
    else if (!strcmp("FRF", name))
      return new FRFCurrency();
    else if (!strcmp("GBP", name))
      return new GBPCurrency();
    else if (!strcmp("GRD", name))
      return new GRDCurrency();
    else if (!strcmp("HKD", name))
      return new HKDCurrency();
    else if (!strcmp("HUF", name))
      return new HUFCurrency();
    else if (!strcmp("IEP", name))
      return new IEPCurrency();
    else if (!strcmp("ILS", name))
      return new ILSCurrency();
    else if (!strcmp("INR", name))
      return new INRCurrency();
    else if (!strcmp("IQD", name))
      return new IQDCurrency();
    else if (!strcmp("IRR", name))
      return new IRRCurrency();
    else if (!strcmp("ISK", name))
      return new ISKCurrency();
    else if (!strcmp("ITL", name))
      return new ITLCurrency();
    else if (!strcmp("JPY", name))
      return new JPYCurrency();
    else if (!strcmp("KRW", name))
      return new KRWCurrency();
    else if (!strcmp("KWD", name))
      return new KWDCurrency();
    else if (!strcmp("LTL", name))
      return new LTLCurrency();
    else if (!strcmp("LUF", name))
      return new LUFCurrency();
    else if (!strcmp("LVL", name))
      return new LVLCurrency();
    else if (!strcmp("MTL", name))
      return new MTLCurrency();
    else if (!strcmp("MXN", name))
      return new MXNCurrency();
    else if (!strcmp("NLG", name))
      return new NLGCurrency();
    else if (!strcmp("NOK", name))
      return new NOKCurrency();
    else if (!strcmp("NPR", name))
      return new NPRCurrency();
    else if (!strcmp("NZD", name))
      return new NZDCurrency();
    else if (!strcmp("PKR", name))
      return new PKRCurrency();
    else if (!strcmp("PLN", name))
      return new PLNCurrency();
    else if (!strcmp("PTE", name))
      return new PTECurrency();
    else if (!strcmp("ROL", name))
      return new ROLCurrency();
    else if (!strcmp("SAR", name))
      return new SARCurrency();
    else if (!strcmp("SEK", name))
      return new SEKCurrency();
    else if (!strcmp("SGD", name))
      return new SGDCurrency();
    else if (!strcmp("SIT", name))
      return new SITCurrency();
    else if (!strcmp("SKK", name))
      return new SKKCurrency();
    else if (!strcmp("THB", name))
      return new THBCurrency();
    else if (!strcmp("TRL", name))
      return new TRLCurrency();
    else if (!strcmp("TRY", name))
      return new TRYCurrency();
    else if (!strcmp("TTD", name))
      return new TTDCurrency();
    else if (!strcmp("TWD", name))
      return new TWDCurrency();
    else if (!strcmp("USD", name))
      return new USDCurrency();
    else if (!strcmp("VEB", name))
      return new VEBCurrency();
    else if (!strcmp("ZAR", name))
      return new ZARCurrency();
    else
      QL_FAIL("Currency not found");
  } catch (std::exception& er) {
    return handleException<void *>(e, er);
  }
}

void  qlFreeCurrency(void *currency) {
  //printf("freeing currency %p", currency);
  delete static_cast<Currency *>(currency);
}

const char *qlCurrencyName(void *currency) {
  std::string name = static_cast<Currency *>(currency)->name();
  return strdup(name.c_str());
}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2: */
