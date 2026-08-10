#include <ql/instrument.hpp>
#include <ql/exercise.hpp>
#include <ql/payoff.hpp>
#include <ql/instruments/basketoption.hpp>
#include <ql/instruments/compositeinstrument.hpp>
#include <ql/instruments/stickyratchet.hpp>
#include <ql/instruments/forward.hpp>
#include <ql/instruments/vanillaswingoption.hpp>
#include <ql/instruments/capfloor.hpp>
#include <ql/instruments/callabilityschedule.hpp>
#include <ql/instruments/forwardrateagreement.hpp>
#include <ql/instruments/fxforward.hpp>
#include <ql/instruments/bondforward.hpp>
#include <ql/instruments/creditdefaultswap.hpp>
#include <ql/experimental/credit/cdsoption.hpp>
#include <ql/instruments/claim.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/instruments/vanillaswap.hpp>
#include <ql/instruments/bmaswap.hpp>
#include <ql/instruments/overnightindexedswap.hpp>
#include <ql/instruments/assetswap.hpp>
#include <ql/instruments/zerocouponinflationswap.hpp>
#include <ql/instruments/yearonyearinflationswap.hpp>
#include <ql/instruments/cpiswap.hpp>
#include <ql/instruments/barrieroption.hpp>
#include <ql/instruments/vanillaoption.hpp>
#include <ql/instruments/swaption.hpp>
#include <ql/instruments/vanillaswingoption.hpp>
#include <ql/instruments/forwardvanillaoption.hpp>
#include <ql/instruments/quantoforwardvanillaoption.hpp>
#include <ql/instruments/quantobarrieroption.hpp>
#include <ql/instruments/europeanoption.hpp>
#include <ql/instruments/varianceswap.hpp>
#include <ql/instruments/asianoption.hpp>
#include <ql/instruments/vanillastorageoption.hpp>
#include <ql/instruments/lookbackoption.hpp>
#include <ql/instruments/cliquetoption.hpp>
#include <ql/instruments/basketoption.hpp>
#include <ql/instruments/margrabeoption.hpp>
#include <ql/experimental/exoticoptions/himalayaoption.hpp>
#include <ql/experimental/exoticoptions/pagodaoption.hpp>
#include <ql/experimental/credit/cdsoption.hpp>
#include <ql/instruments/bonds/all.hpp>
#include <ql/cashflows/couponpricer.hpp>
#include <ql/pricingengines/bond/bondfunctions.hpp>
#include <ql/experimental/callablebonds/callablebond.hpp>
#include <ql/instruments/bonds/convertiblebonds.hpp>
#include <ql/cashflows/cashflows.hpp>
#include <ql/cashflows/coupon.hpp>
#include <ql/cashflows/averagebmacoupon.hpp>
#include <ql/cashflows/fixedratecoupon.hpp>
#include <ql/cashflows/iborcoupon.hpp>
#include <ql/cashflows/overnightindexedcoupon.hpp>
#include <ql/cashflows/rangeaccrual.hpp>
#include <ql/cashflows/simplecashflow.hpp>
#include <ql/cashflows/cpicoupon.hpp>
#include <ql/cashflows/yoyinflationcoupon.hpp>
#include <ql/cashflows/couponpricer.hpp>
#include <ql/cashflows/dividend.hpp>
#include <ql/cashflows/couponpricer.hpp>
#include <ql/cashflows/conundrumpricer.hpp>

#include "qlaux.h"
using namespace QuantLib;
#include "qlInstrument.h"
#include "qlMisc.h"

#ifdef QLTRACK_ALLOCATIONS
template <> class ObjClassName<Leg*> {public: static void output(std::ostream& os) {os << "Leg";}};
#endif

extern "C" {
double qlInstrumentNPV(QlInstrument *instr, char **e) {try {return (*arg(instr))->NPV();} catch (std::exception& er) {return handleException<double>(e, er);}}
void qlInstrumentSetPricingEngine(QlInstrument *instr, QlPricingEngine *eng, char **e) {try {(*arg(instr))->setPricingEngine(*arg(eng));} catch (std::exception& er) {(void)handleException<int>(e, er);}}
void qlFreeInstrument(QlInstrument *instr) {del(instr);}

QlInstrument* qlCompositeInstrument(unsigned instrLen, QlInstrument **instrs, unsigned, double *coeff, char **e) {
  CompositeInstrument *ci = 0;
  try {ci = new CompositeInstrument();
    for (unsigned i = 0; i < instrLen; ++i)
        ci->add(*(instrs[i]), coeff[i]);
    return ret(new QlInstrument(alloc(ci)));
  } catch (std::exception& er) {delete ci; return handleException<QlInstrument*>(e, er);}}

double qlInstrumentErrorEstimate(QlInstrument* o, char **e) {try {return (*arg(o))->errorEstimate();} catch (std::exception& er) {return handleException<double>(e, er);}}
int qlInstrumentIsExpired(QlInstrument* o, char **e) {try {return (*arg(o))->isExpired();} catch (std::exception& er) {return handleException<int>(e, er);}}
int qlInstrumentValuationDate(QlInstrument* o, char **e) {try {return ((*arg(o))->valuationDate()).serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}
void qlFreePayoff(QlPayoff *o) {del(o);}
void qlFreeBasketPayoff(QlBasketPayoff *o) {del(o);}
QlPayoff* qlBasketPayoffAsPayoff(QlBasketPayoff *o) {return ret(new QlPayoff(*arg(o)));}
void qlFreeTypePayoff(QlTypePayoff *o) {del(o);}
QlPayoff* qlTypePayoffAsPayoff(QlTypePayoff *o) {return ret(new QlPayoff(*arg(o)));}
void qlFreeStrikedTypePayoff(QlStrikedTypePayoff *o) {del(o);}
QlTypePayoff* qlStrikedTypePayoffAsTypePayoff(QlStrikedTypePayoff *o) {return ret(new QlTypePayoff(*arg(o)));}
void qlFreePercentageStrikePayoff(QlPercentageStrikePayoff *o) {del(o);}
QlStrikedTypePayoff* qlPercentageStrikePayoffAsStrikedTypePayoff(QlPercentageStrikePayoff *o) {return ret(new QlStrikedTypePayoff(*arg(o)));}
void qlFreePlainVanillaPayoff(QlPlainVanillaPayoff *o) {del(o);}
QlStrikedTypePayoff* qlPlainVanillaPayoffAsStrikedTypePayoff(QlPlainVanillaPayoff *o) {return ret(new QlStrikedTypePayoff(*arg(o)));}

QlStrikedTypePayoff* qlAssetOrNothingPayoff(int type, double strike, char **e) {
  try {return ret(new QlStrikedTypePayoff(alloc(new AssetOrNothingPayoff((Option::Type)type, strike))));
  } catch (std::exception& er) {return handleException<QlStrikedTypePayoff*>(e, er);}}
QlBasketPayoff* qlAverageBasketPayoff(QlPayoff* p, unsigned n, char **e) {
  try {return ret(new QlBasketPayoff(alloc(new AverageBasketPayoff(*arg(p), n))));
  } catch (std::exception& er) {return handleException<QlBasketPayoff*>(e, er);}}
QlBasketPayoff* qlAverageBasketPayoff1(QlPayoff* p, unsigned aLen, double* a, char **e) {
  try {return ret(new QlBasketPayoff(alloc(new AverageBasketPayoff(*arg(p), Array(a, a+aLen)))));
  } catch (std::exception& er) {return handleException<QlBasketPayoff*>(e, er);}}
QlStrikedTypePayoff* qlCashOrNothingPayoff(int type, double strike, double cashPayoff, char **e) {
  try {return ret(new QlStrikedTypePayoff(alloc(new CashOrNothingPayoff((Option::Type)type, strike, cashPayoff))));
  } catch (std::exception& er) {return handleException<QlStrikedTypePayoff*>(e, er);}}
QlPayoff* qlDoubleStickyRatchetPayoff(double type1, double type2, double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e) {
  try {return ret(new QlPayoff(alloc(new DoubleStickyRatchetPayoff(type1, type2, gearing1, gearing2, gearing3, spread1, spread2, spread3, initialValue1, initialValue2, accrualFactor))));
  } catch (std::exception& er) {return handleException<QlPayoff*>(e, er);}}
QlTypePayoff* qlFloatingTypePayoff(int type, char **e) {try {return ret(new QlTypePayoff(alloc(new FloatingTypePayoff((Option::Type)type))));} catch (std::exception& er) {return handleException<QlTypePayoff*>(e, er);}}
QlPayoff* qlForwardTypePayoff(int type, double strike, char **e) {try {return ret(new QlPayoff(alloc(new ForwardTypePayoff((Position::Type)type, strike))));} catch (std::exception& er) {return handleException<QlPayoff*>(e, er);}}
QlStrikedTypePayoff* qlGapPayoff(int type, double strike, double secondStrike, char **e) {try {return ret(new QlStrikedTypePayoff(alloc(new GapPayoff((Option::Type)type, strike, secondStrike))));} catch (std::exception& er) {return handleException<QlStrikedTypePayoff*>(e, er);}}
QlBasketPayoff* qlMaxBasketPayoff(QlPayoff* p, char **e) {try {return ret(new QlBasketPayoff(alloc(new MaxBasketPayoff(*arg(p)))));} catch (std::exception& er) {return handleException<QlBasketPayoff*>(e, er);}}
QlBasketPayoff* qlMinBasketPayoff(QlPayoff* p, char **e) {try {return ret(new QlBasketPayoff(alloc(new MinBasketPayoff(*arg(p)))));} catch (std::exception& er) {return handleException<QlBasketPayoff*>(e, er);}}
QlPercentageStrikePayoff* qlPercentageStrikePayoff(int type, double moneyness, char **e) {
  try {return ret(new QlPercentageStrikePayoff(alloc(new PercentageStrikePayoff((Option::Type)type, moneyness))));
  } catch (std::exception& er) {return handleException<QlPercentageStrikePayoff*>(e, er);}}
QlPlainVanillaPayoff* qlPlainVanillaPayoff(int type, double strike, char **e) {
  try {return ret(new QlPlainVanillaPayoff(alloc(new PlainVanillaPayoff((Option::Type)type, strike))));
  } catch (std::exception& er) {return handleException<QlPlainVanillaPayoff*>(e, er);}}
QlPayoff* qlRatchetMaxPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e) {
  try {return ret(new QlPayoff(alloc(new RatchetMaxPayoff(gearing1, gearing2, gearing3, spread1, spread2, spread3, initialValue1, initialValue2, accrualFactor))));
  } catch (std::exception& er) {return handleException<QlPayoff*>(e, er);}}
QlPayoff* qlRatchetMinPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e) {
  try {return ret(new QlPayoff(alloc(new RatchetMinPayoff(gearing1, gearing2, gearing3, spread1, spread2, spread3, initialValue1, initialValue2, accrualFactor))));
  } catch (std::exception& er) {return handleException<QlPayoff*>(e, er);}}
QlPayoff* qlRatchetPayoff(double gearing1, double gearing2, double spread1, double spread2, double initialValue, double accrualFactor, char **e) {
  try {return ret(new QlPayoff(alloc(new RatchetPayoff(gearing1, gearing2, spread1, spread2, initialValue, accrualFactor))));
  } catch (std::exception& er) {return handleException<QlPayoff*>(e, er);}}
QlBasketPayoff* qlSpreadBasketPayoff(QlPayoff* p, char **e) {
  try {return ret(new QlBasketPayoff(alloc(new SpreadBasketPayoff(*arg(p)))));
  } catch (std::exception& er) {return handleException<QlBasketPayoff*>(e, er);}}
QlPayoff* qlStickyMaxPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e) {
  try {return ret(new QlPayoff(alloc(new StickyMaxPayoff(gearing1, gearing2, gearing3, spread1, spread2, spread3, initialValue1, initialValue2, accrualFactor))));
  } catch (std::exception& er) {return handleException<QlPayoff*>(e, er);}}
QlPayoff* qlStickyMinPayoff(double gearing1, double gearing2, double gearing3, double spread1, double spread2, double spread3, double initialValue1, double initialValue2, double accrualFactor, char **e) {
  try {return ret(new QlPayoff(alloc(new StickyMinPayoff(gearing1, gearing2, gearing3, spread1, spread2, spread3, initialValue1, initialValue2, accrualFactor))));
  } catch (std::exception& er) {return handleException<QlPayoff*>(e, er);}}
QlPayoff* qlStickyPayoff(double gearing1, double gearing2, double spread1, double spread2, double initialValue, double accrualFactor, char **e) {
  try {return ret(new QlPayoff(alloc(new StickyPayoff(gearing1, gearing2, spread1, spread2, initialValue, accrualFactor))));
  } catch (std::exception& er) {return handleException<QlPayoff*>(e, er);}}
QlStrikedTypePayoff* qlSuperFundPayoff(double strike, double secondStrike, char **e) {
  try {return ret(new QlStrikedTypePayoff(alloc(new SuperFundPayoff(strike, secondStrike))));
  } catch (std::exception& er) {return handleException<QlStrikedTypePayoff*>(e, er);}}
QlStrikedTypePayoff* qlSuperSharePayoff(double strike, double secondStrike, double cashPayoff, char **e) {
  try {return ret(new QlStrikedTypePayoff(alloc(new SuperSharePayoff(strike, secondStrike, cashPayoff))));
  } catch (std::exception& er) {return handleException<QlStrikedTypePayoff*>(e, er);}}
void qlFreeAmericanExercise(QlAmericanExercise *o) {del(o);}
QlExercise* qlAmericanExerciseAsExercise(QlAmericanExercise *o) {return ret(new QlExercise(*arg(o)));}
void qlFreeBermudanExercise(QlBermudanExercise *o) {del(o);}
QlExercise* qlBermudanExerciseAsExercise(QlBermudanExercise *o) {return ret(new QlExercise(*arg(o)));}
void qlFreeEuropeanExercise(QlEuropeanExercise *o) {del(o);}
QlExercise* qlEuropeanExerciseAsExercise(QlEuropeanExercise *o) {return ret(new QlExercise(*arg(o)));}
void qlFreeExercise(QlExercise *o) {del(o);}
QlAmericanExercise* qlAmericanExercise(int earliestDate, int latestDate, int payoffAtExpiry, char **e) {
  try {return ret(new QlAmericanExercise(alloc(new AmericanExercise(Date(earliestDate), Date(latestDate), payoffAtExpiry))));
  } catch (std::exception& er) {return handleException<QlAmericanExercise*>(e, er);}}
QlBermudanExercise* qlBermudanExercise(unsigned datesLen, int *dates, int payoffAtExpiry, char **e) {
  try {return ret(new QlBermudanExercise(alloc(new BermudanExercise(qlDateVector(dates, datesLen), payoffAtExpiry))));
  } catch (std::exception& er) {return handleException<QlBermudanExercise*>(e, er);}}
QlExercise* qlEarlyExercise(int type, int payoffAtExpiry, char **e) {
  try {return ret(new QlExercise(alloc(new EarlyExercise((Exercise::Type)type, payoffAtExpiry))));
  } catch (std::exception& er) {return handleException<QlExercise*>(e, er);}}
QlExercise* qlExercise(int type, char **e) {try {return ret(new QlExercise(alloc(new Exercise((Exercise::Type)type))));
  } catch (std::exception& er) {return handleException<QlExercise*>(e, er);}}
QlEuropeanExercise* qlEuropeanExercise(int date, char **e) {try {return ret(new QlEuropeanExercise(alloc(new EuropeanExercise(Date(date)))));} catch (std::exception& er) {return handleException<QlEuropeanExercise*>(e, er);}}
QlSwingExercise* qlSwingExercise(unsigned datesLen, int* dates, unsigned secLen, unsigned* seconds, char **e) {
  try {std::vector<Size> secs(seconds, seconds+secLen);
    return ret(new QlSwingExercise(alloc(new SwingExercise(qlDateVector(dates, datesLen), secs))));
  } catch (std::exception& er) {return handleException<QlSwingExercise*>(e, er);}}

QlSwingExercise* qlSwingExercise1(int from, int to, unsigned stepSizeSecs, char **e) {
  try {return ret(new QlSwingExercise(alloc(new SwingExercise(Date(from), Date(to), stepSizeSecs))));
  } catch (std::exception& er) {return handleException<QlSwingExercise*>(e, er);}}
QlExercise* qlSwingExerciseAsExercise(QlSwingExercise *o) {return ret(new QlExercise(*arg(o)));}
QlAmericanExercise* qlAmericanExercise1(int latestDate, int payoffAtExpiry, char **e) {
  try {return ret(new QlAmericanExercise(alloc(new AmericanExercise(Date(latestDate), payoffAtExpiry))));
  } catch (std::exception& er) {return handleException<QlAmericanExercise*>(e, er);}}

void qlFreeCapFloor(QlCapFloor *o) {del(o);}
QlInstrument* qlCapFloorAsInstrument(QlCapFloor *o) {return ret(new QlInstrument(*arg(o)));}

QlCapFloor* qlCap(Leg* floatingLeg, unsigned exerciseRatesLen, double* exerciseRates, char **e) {
  try {return ret(new QlCapFloor(alloc(new Cap(*arg(floatingLeg), std::vector<double>(exerciseRates, exerciseRates+exerciseRatesLen)))));
  } catch (std::exception& er) {return handleException<QlCapFloor*>(e, er);}}
QlCapFloor* qlCollar(Leg* floatingLeg, unsigned capRatesLen, double* capRates, unsigned floorRatesLen, double* floorRates, char **e) {
  try {return ret(new QlCapFloor(alloc(new Collar(*arg(floatingLeg), std::vector<double>(capRates, capRates+capRatesLen), std::vector<double>(floorRates, floorRates+floorRatesLen)))));
  } catch (std::exception& er) {return handleException<QlCapFloor*>(e, er);}}
QlCapFloor* qlFloor(Leg* floatingLeg, unsigned exerciseRatesLen, double* exerciseRates, char **e) {
  try {return ret(new QlCapFloor(alloc(new Floor(*arg(floatingLeg), std::vector<double>(exerciseRates, exerciseRates+exerciseRatesLen)))));
  } catch (std::exception& er) {return handleException<QlCapFloor*>(e, er);}}
double qlCapFloorAtmRate(QlCapFloor* o, QlYieldTermStructure* discountCurve, char **e) {
  try {return (*arg(o))->atmRate(**arg(discountCurve));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCapFloorImpliedVolatility(QlCapFloor* o, double price, QlYieldTermStructure* disc, double guess, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, int type, double displacement, char **e) {
  try {return (*arg(o))->impliedVolatility(price, Handle<YieldTermStructure>(*arg(disc)), guess, accuracy, maxEvaluations, minVol, maxVol, (VolatilityType)type, displacement);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
QlCapFloor* qlCapFloorOptionlet(QlCapFloor* o, unsigned n, char **e) {
  try {return ret(new QlCapFloor(alloc((*arg(o))->optionlet(n))));
  } catch (std::exception& er) {return handleException<QlCapFloor*>(e, er);}}

void qlFreeCallability(QlCallability *o) {del(o);}

QlCallability* qlCallability(double price, int priceType, int type, int date, char **e) {
  try {Bond::Price p(price, (Bond::Price::Type)priceType);
    return ret(new QlCallability(alloc(new Callability(p, (Callability::Type)type, Date(date)))));
  } catch (std::exception& er) {return handleException<QlCallability*>(e, er);}}

void qlFreeForward(QlForward *fwd) {del(fwd);}
void qlFreeForwardRateAgreement(QlForwardRateAgreement *fwd) {del(fwd);}
QlInstrument* qlForwardRateAgreementAsInstrument(QlForwardRateAgreement *fwd) {return ret(new QlInstrument(*arg(fwd)));}
QlInstrument* qlForwardAsInstrument(QlForward *fwd) {return ret(new QlInstrument(*arg(fwd)));}
double qlForwardForwardValue(QlForward* o, char **e) {try {return (*arg(o))->forwardValue();} catch (std::exception& er) {return handleException<double>(e, er);}}

InterestRate* qlForwardImpliedYield(QlForward* o, double underlyingSpotValue, double forwardValue, int settlementDate, int compoundingConvention, DayCounter* dayCounter, char **e) {
  try {return ret(new InterestRate((*arg(o))->impliedYield(underlyingSpotValue, forwardValue, Date(settlementDate), (Compounding)compoundingConvention, *arg(dayCounter))));
  } catch (std::exception& er) {return handleException<InterestRate*>(e, er);}}
int qlForwardSettlementDate(QlForward* o, char **e) {try {return ((*arg(o))->settlementDate()).serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}
double qlForwardSpotIncome(QlForward* o, QlYieldTermStructure* incomeDiscountCurve, char **e) {
  try {return (*arg(o))->spotIncome(Handle<YieldTermStructure>(*arg(incomeDiscountCurve)));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlForwardSpotValue(QlForward* o, char **e) {try {return (*arg(o))->spotValue();} catch (std::exception& er) {return handleException<double>(e, er);}}

QlForwardRateAgreement* qlForwardRateAgreement(QlIborIndex* index, int valueDate, int maturityDate, int type, double strikeForwardRate, double notionalAmount, QlYieldTermStructure* discountCurve, char **e) {
  try {return ret(new QlForwardRateAgreement(alloc(new ForwardRateAgreement(*arg(index), Date(valueDate), Date(maturityDate), (Position::Type)type, strikeForwardRate, notionalAmount, qlNullableHandle(arg(discountCurve))))));
  } catch (std::exception& er) {return handleException<QlForwardRateAgreement*>(e, er);}}

void qlFreeBondForward(QlBondForward *fwd) {del(fwd);}
QlForward* qlBondForwardAsForward(QlBondForward *fwd) {return ret(new QlForward(*arg(fwd)));}

QlBondForward* qlBondForward(int valueDate, int maturityDate, int type, double strike, unsigned settlementDays, DayCounter* dayCounter, Calendar* calendar, int businessDayConvention, QlBond* bond, QlYieldTermStructure* discountCurve, QlYieldTermStructure* incomeDiscountCurve, char **e) {
  try {return ret(new QlBondForward(alloc(new BondForward(Date(valueDate), Date(maturityDate), (Position::Type)type, strike, settlementDays, *arg(dayCounter), *arg(calendar), (BusinessDayConvention)businessDayConvention, *arg(bond), qlNullableHandle(arg(discountCurve)), qlNullableHandle(arg(incomeDiscountCurve))))));
  } catch (std::exception& er) {return handleException<QlBondForward*>(e, er);}}

double qlBondForwardCleanForwardPrice(QlBondForward* o, char **e) {try {return (*arg(o))->cleanForwardPrice();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondForwardForwardPrice(QlBondForward* o, char **e) {try {return (*arg(o))->forwardPrice();} catch (std::exception& er) {return handleException<double>(e, er);}}
InterestRate* qlForwardRateAgreementForwardRate(QlForwardRateAgreement* o, char **e) {try {return ret(new InterestRate((*arg(o))->forwardRate()));} catch (std::exception& er) {return handleException<InterestRate*>(e, er);}}

void qlFreeFxForward(QlFxForward *fwd) {del(fwd);}
QlInstrument* qlFxForwardAsInstrument(QlFxForward *fwd) {return ret(new QlInstrument(*arg(fwd)));}
QlFxForward* qlFxForward(double sourceNominal, Currency* sourceCurrency, double targetNominal, Currency* targetCurrency, int maturityDate, int paySourceCurrency, unsigned settlementDays, Calendar* paymentCalendar, char **e) {
  try {return ret(new QlFxForward(alloc(new FxForward(sourceNominal, *arg(sourceCurrency), targetNominal, *arg(targetCurrency), Date(maturityDate), paySourceCurrency, settlementDays, *arg(paymentCalendar)))));
  } catch (std::exception& er) {return handleException<QlFxForward*>(e, er);}}
QlFxForward* qlFxForward1(double sourceNominal, Currency* sourceCurrency, Currency* targetCurrency, double forwardRate, int maturityDate, int paySourceCurrency, unsigned settlementDays, Calendar* paymentCalendar, char **e) {
  try {return ret(new QlFxForward(alloc(new FxForward(sourceNominal, *arg(sourceCurrency), *arg(targetCurrency), forwardRate, Date(maturityDate), paySourceCurrency, settlementDays, *arg(paymentCalendar)))));
  } catch (std::exception& er) {return handleException<QlFxForward*>(e, er);}}
double qlFxForwardFairForwardRate(QlFxForward* o, char **e) {try {return (*arg(o))->fairForwardRate();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlFxForwardNpvSourceCurrency(QlFxForward* o, char **e) {try {return (*arg(o))->npvSourceCurrency();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlFxForwardNpvTargetCurrency(QlFxForward* o, char **e) {try {return (*arg(o))->npvTargetCurrency();} catch (std::exception& er) {return handleException<double>(e, er);}}

void qlFreeSwap(QlSwap *o) {del(o);}
QlInstrument* qlSwapAsInstrument(QlSwap *o) {return ret(new QlInstrument(*arg(o)));}
void qlFreeVanillaSwap(QlVanillaSwap *o) {del(o);}
QlSwap* qlVanillaSwapAsSwap(QlVanillaSwap *o) {return ret(new QlSwap(*arg(o)));}
void qlFreeBMASwap(QlBMASwap *o) {del(o);}
QlSwap* qlBMASwapAsSwap(QlBMASwap *o) {return ret(new QlSwap(*arg(o)));}
void qlFreeOvernightIndexedSwap(QlOvernightIndexedSwap *o) {del(o);}
QlSwap* qlOvernightIndexedSwapAsSwap(QlOvernightIndexedSwap *o) {return ret(new QlSwap(*arg(o)));}
QlSwap* qlSwap1(unsigned legsLen, Leg** legs, unsigned payerLen, int *payer, char **e) {
  try {return ret(new QlSwap(alloc(new Swap(qlVector(legs, legsLen), std::vector<bool>(payer, payer+payerLen)))));
  } catch (std::exception& er) {return handleException<QlSwap*>(e, er);}}

void qlFreeAssetSwap(QlAssetSwap *o) {del(o);}
QlSwap* qlAssetSwapAsSwap(QlAssetSwap *o) {return ret(new QlSwap(*arg(o)));}

QlAssetSwap* qlAssetSwap(int payBondCoupon, QlBond* bond, double bondCleanPrice, QlIborIndex* iborIndex, double spread, Schedule* floatSchedule, DayCounter* floatingDayCount, int parAssetSwap, double gearing, double nonParRepayment, int dealMaturity, char **e) {
  try {return ret(new QlAssetSwap(alloc(new AssetSwap(payBondCoupon, *arg(bond), bondCleanPrice, *arg(iborIndex), spread, *arg(floatSchedule), *arg(floatingDayCount), parAssetSwap, gearing, nonParRepayment, qlNullableDate(dealMaturity)))));
  } catch (std::exception& er) {return handleException<QlAssetSwap*>(e, er);}}
QlBMASwap* qlBMASwap(int type, double nominal, Schedule* liborSchedule, double liborFraction, double liborSpread, QlIborIndex* liborIndex, DayCounter* liborDayCount, Schedule* bmaSchedule, QlBMAIndex* bmaIndex, DayCounter* bmaDayCount, char **e) {
  try {return ret(new QlBMASwap(alloc(new BMASwap((BMASwap::Type)type, nominal, *arg(liborSchedule), liborFraction, liborSpread, *arg(liborIndex), *arg(liborDayCount), *arg(bmaSchedule), *arg(bmaIndex), *arg(bmaDayCount)))));
  } catch (std::exception& er) {return handleException<QlBMASwap*>(e, er);}}
QlVanillaSwap* qlVanillaSwap(int type, double nominal, Schedule* fixedSchedule, double fixedRate, DayCounter* fixedDayCount, Schedule* floatSchedule, QlIborIndex* iborIndex, double spread, DayCounter* floatingDayCount, int paymentConvention, int useIndexedCoupons, char **e) {
  try {return ret(new QlVanillaSwap(alloc(new VanillaSwap((VanillaSwap::Type)type, nominal, *arg(fixedSchedule), fixedRate, *arg(fixedDayCount), *arg(floatSchedule), *arg(iborIndex), spread, *arg(floatingDayCount), qlOptBusinessDayConvention(paymentConvention), qlOptBool(useIndexedCoupons)))));
  } catch (std::exception& er) {return handleException<QlVanillaSwap*>(e, er);}}

QlSwap* qlSwap(Leg* firstLeg, Leg* secondLeg, char **e) {try {return ret(new QlSwap(alloc(new Swap(*arg(firstLeg), *arg(secondLeg)))));} catch (std::exception& er) {return handleException<QlSwap*>(e, er);} }
double qlSwapEndDiscounts(QlSwap* o, unsigned j, char **e) {try {return (*arg(o))->endDiscounts(j);} catch (std::exception& er) {return handleException<double>(e, er);}}
Leg* qlSwapLeg(QlSwap* o, unsigned j, char **e) {try {return ret(new Leg((*arg(o))->leg(j)));} catch (std::exception& er) {return handleException<Leg*>(e, er);}}
double qlSwapLegBPS(QlSwap* o, unsigned j, char **e) {try {return (*arg(o))->legBPS(j);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwapLegNPV(QlSwap* o, unsigned j, char **e) {try {return (*arg(o))->legNPV(j);} catch (std::exception& er) {return handleException<double>(e, er);}}
int qlSwapMaturityDate(QlSwap* o, char **e) {try {return qlNullableDate((*arg(o))->maturityDate());} catch (std::exception& er) {return handleException<int>(e, er);}}
double qlSwapNpvDateDiscount(QlSwap* o, char **e) {try {return (*arg(o))->npvDateDiscount();} catch (std::exception& er) {return handleException<double>(e, er);}}
int qlSwapStartDate(QlSwap* o, char **e) {try {return qlNullableDate((*arg(o))->startDate());} catch (std::exception& er) {return handleException<int>(e, er);}}
double qlSwapStartDiscounts(QlSwap* o, unsigned j, char **e) {try {return (*arg(o))->startDiscounts(j);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlVanillaSwapFairRate(QlVanillaSwap* o, char **e) {try {return (*arg(o))->fairRate();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlVanillaSwapFairSpread(QlVanillaSwap* o, char **e) {try {return (*arg(o))->fairSpread();} catch (std::exception& er) {return handleException<double>(e, er);}}
Leg* qlVanillaSwapFixedLeg(QlVanillaSwap* o, char **e) {try {return ret(new Leg((*arg(o))->fixedLeg()));} catch (std::exception& er) {return handleException<Leg*>(e, er);}}
double qlVanillaSwapFixedLegBPS(QlVanillaSwap* o, char **e) {try {return (*arg(o))->fixedLegBPS();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlVanillaSwapFixedLegNPV(QlVanillaSwap* o, char **e) {try {return (*arg(o))->fixedLegNPV();} catch (std::exception& er) {return handleException<double>(e, er);}}
Leg* qlVanillaSwapFloatingLeg(QlVanillaSwap* o, char **e) {try {return ret(new Leg((*arg(o))->floatingLeg()));} catch (std::exception& er) {return handleException<Leg*>(e, er);}}
double qlVanillaSwapFloatingLegBPS(QlVanillaSwap* o, char **e) {try {return (*arg(o))->floatingLegBPS();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlVanillaSwapFloatingLegNPV(QlVanillaSwap* o, char **e) {try {return (*arg(o))->floatingLegNPV();} catch (std::exception& er) {return handleException<double>(e, er);} }

QlOvernightIndexedSwap* qlOvernightIndexedSwap(int type, double nominal, Schedule* schedule, double fixedRate, DayCounter* fixedDC, QlOvernightIndex* overnightIndex, double spread, int paymentLag, int paymentAdjustment, Calendar* paymentCalendar, int telescopicValueDates, int averagingMethod, unsigned lookbackDays, unsigned lockoutDays, int applyObservationShift, char **e) {
  try {return ret(new QlOvernightIndexedSwap(alloc(new OvernightIndexedSwap((OvernightIndexedSwap::Type)type, nominal, *arg(schedule), fixedRate, *arg(fixedDC), *arg(overnightIndex), spread, paymentLag, (BusinessDayConvention)paymentAdjustment, *arg(paymentCalendar), telescopicValueDates, (RateAveraging::Type)averagingMethod, lookbackDays, lockoutDays, applyObservationShift))));
  } catch (std::exception& er) {return handleException<QlOvernightIndexedSwap*>(e, er);}}

QlOvernightIndexedSwap* qlOvernightIndexedSwap1(int type, unsigned nominalsLen, double* nominals, Schedule* schedule, double fixedRate, DayCounter* fixedDC, QlOvernightIndex* overnightIndex, double spread, int paymentLag, int paymentAdjustment, Calendar* paymentCalendar, int telescopicValueDates, int averagingMethod, unsigned lookbackDays, unsigned lockoutDays, int applyObservationShift, char **e) {
  try {return ret(new QlOvernightIndexedSwap(alloc(new OvernightIndexedSwap((OvernightIndexedSwap::Type)type, std::vector<double>(nominals, nominals+nominalsLen), *arg(schedule), fixedRate, *arg(fixedDC), *arg(overnightIndex), spread, paymentLag, (BusinessDayConvention)paymentAdjustment, *arg(paymentCalendar), telescopicValueDates, (RateAveraging::Type)averagingMethod, lookbackDays, lockoutDays, applyObservationShift))));
  } catch (std::exception& er) {return handleException<QlOvernightIndexedSwap*>(e, er);}}
Leg* qlAssetSwapBondLeg(QlAssetSwap* o, char **e) {try {return ret(new Leg((*arg(o))->bondLeg()));} catch (std::exception& er) {return handleException<Leg*>(e, er);}}
double qlAssetSwapCleanPrice(QlAssetSwap* o, char **e) {try {return (*arg(o))->cleanPrice();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlAssetSwapFairCleanPrice(QlAssetSwap* o, char **e) {try {return (*arg(o))->fairCleanPrice();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlAssetSwapFairNonParRepayment(QlAssetSwap* o, char **e) {try {return (*arg(o))->fairNonParRepayment();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlAssetSwapFairSpread(QlAssetSwap* o, char **e) {try {return (*arg(o))->fairSpread();} catch (std::exception& er) {return handleException<double>(e, er);}}
Leg* qlAssetSwapFloatingLeg(QlAssetSwap* o, char **e) {try {return ret(new Leg((*arg(o))->floatingLeg()));} catch (std::exception& er) {return handleException<Leg*>(e, er);}}
double qlAssetSwapFloatingLegBPS(QlAssetSwap* o, char **e) {try {return (*arg(o))->floatingLegBPS();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlAssetSwapFloatingLegNPV(QlAssetSwap* o, char **e) {try {return (*arg(o))->floatingLegNPV();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlAssetSwapNonParRepayment(QlAssetSwap* o, char **e) {try {return (*arg(o))->nonParRepayment();} catch (std::exception& er) {return handleException<double>(e, er);}}
int qlAssetSwapParSwap(QlAssetSwap* o, char **e) {try {return (*arg(o))->parSwap();} catch (std::exception& er) {return handleException<int>(e, er);}}

void qlFreeZeroCouponInflationSwap(QlZeroCouponInflationSwap *o) {del(o);}
QlSwap* qlZeroCouponInflationSwapAsSwap(QlZeroCouponInflationSwap *o) {return ret(new QlSwap(*arg(o)));}
QlZeroCouponInflationSwap* qlZeroCouponInflationSwap(int type, double nominal, int startDate, int maturity, Calendar* cal, int paymentConvention, DayCounter* dayCounter, double fixedRate, QlZeroInflationIndex* index, int obsLagLen, int obsLagUnit, int observationInterpolation, int adjustInfObsDates, Calendar* infCalendar, int infConvention, char **e) {
  try {return ret(new QlZeroCouponInflationSwap(alloc(new ZeroCouponInflationSwap((ZeroCouponInflationSwap::Type)type, nominal, Date(startDate), Date(maturity), *arg(cal), (BusinessDayConvention)paymentConvention, *arg(dayCounter), fixedRate, *arg(index), Period(obsLagLen, (TimeUnit)obsLagUnit), (CPI::InterpolationType)observationInterpolation, adjustInfObsDates, infCalendar ? *arg(infCalendar) : Calendar(), (BusinessDayConvention)infConvention))));
  } catch (std::exception& er) {return handleException<QlZeroCouponInflationSwap*>(e, er);}}
double qlZeroCouponInflationSwapFairRate(QlZeroCouponInflationSwap* o, char **e) {try {return (*arg(o))->fairRate();} catch (std::exception& er) {return handleException<double>(e, er);}}

void qlFreeYearOnYearInflationSwap(QlYearOnYearInflationSwap *o) {del(o);}
QlSwap* qlYearOnYearInflationSwapAsSwap(QlYearOnYearInflationSwap *o) {return ret(new QlSwap(*arg(o)));}
QlYearOnYearInflationSwap* qlYearOnYearInflationSwap(int type, double nominal, Schedule* fixedSchedule, double fixedRate, DayCounter* fixedDayCount, Schedule* yoySchedule, QlYoYInflationIndex* yoyIndex, int obsLagLen, int obsLagUnit, int interpolation, double spread, DayCounter* yoyDayCount, Calendar* paymentCalendar, int paymentConvention, char **e) {
  try {return ret(new QlYearOnYearInflationSwap(alloc(new YearOnYearInflationSwap((YearOnYearInflationSwap::Type)type, nominal, *arg(fixedSchedule), fixedRate, *arg(fixedDayCount), *arg(yoySchedule), *arg(yoyIndex), Period(obsLagLen, (TimeUnit)obsLagUnit), (CPI::InterpolationType)interpolation, spread, *arg(yoyDayCount), *arg(paymentCalendar), (BusinessDayConvention)paymentConvention))));
  } catch (std::exception& er) {return handleException<QlYearOnYearInflationSwap*>(e, er);}}
double qlYearOnYearInflationSwapFairRate(QlYearOnYearInflationSwap* o, char **e) {try {return (*arg(o))->fairRate();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlYearOnYearInflationSwapFairSpread(QlYearOnYearInflationSwap* o, char **e) {try {return (*arg(o))->fairSpread();} catch (std::exception& er) {return handleException<double>(e, er);}}

void qlFreeCPISwap(QlCPISwap *o) {del(o);}
QlSwap* qlCPISwapAsSwap(QlCPISwap *o) {return ret(new QlSwap(*arg(o)));}
QlCPISwap* qlCPISwap(int type, double nominal, int subtractInflationNominal, double spread, DayCounter* floatDayCount, Schedule* floatSchedule, int floatRoll, unsigned fixingDays, QlIborIndex* floatIndex, double fixedRate, double baseCPI, DayCounter* fixedDayCount, Schedule* fixedSchedule, int fixedRoll, int obsLagLen, int obsLagUnit, QlZeroInflationIndex* fixedIndex, int observationInterpolation, double inflationNominal, char **e) {
  try {return ret(new QlCPISwap(alloc(new CPISwap((CPISwap::Type)type, nominal, subtractInflationNominal, spread, *arg(floatDayCount), *arg(floatSchedule), (BusinessDayConvention)floatRoll, fixingDays, *arg(floatIndex), fixedRate, baseCPI, *arg(fixedDayCount), *arg(fixedSchedule), (BusinessDayConvention)fixedRoll, Period(obsLagLen, (TimeUnit)obsLagUnit), *arg(fixedIndex), (CPI::InterpolationType)observationInterpolation, inflationNominal))));
  } catch (std::exception& er) {return handleException<QlCPISwap*>(e, er);}}
double qlCPISwapFairRate(QlCPISwap* o, char **e) {try {return (*arg(o))->fairRate();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCPISwapFairSpread(QlCPISwap* o, char **e) {try {return (*arg(o))->fairSpread();} catch (std::exception& er) {return handleException<double>(e, er);}}
int qlAssetSwapPayBondCoupon(QlAssetSwap* o, char **e) {try {return (*arg(o))->payBondCoupon();} catch (std::exception& er) {return handleException<int>(e, er);}}
Leg* qlBMASwapBmaLeg(QlBMASwap* o, char **e) {try {return ret(new Leg((*arg(o))->bmaLeg()));} catch (std::exception& er) {return handleException<Leg*>(e, er);}}
double qlBMASwapBmaLegBPS(QlBMASwap* o, char **e) {try {return (*arg(o))->bmaLegBPS();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBMASwapBmaLegNPV(QlBMASwap* o, char **e) {try {return (*arg(o))->bmaLegNPV();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBMASwapFairLiborFraction(QlBMASwap* o, char **e) {try {return (*arg(o))->fairLiborFraction();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBMASwapFairLiborSpread(QlBMASwap* o, char **e) {try {return (*arg(o))->fairLiborSpread();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBMASwapLiborFraction(QlBMASwap* o, char **e) {try {return (*arg(o))->liborFraction();} catch (std::exception& er) {return handleException<double>(e, er);}}
Leg* qlBMASwapLiborLeg(QlBMASwap* o, char **e) {try {return ret(new Leg((*arg(o))->liborLeg()));} catch (std::exception& er) {return handleException<Leg*>(e, er);}}
double qlBMASwapLiborLegBPS(QlBMASwap* o, char **e) {try {return (*arg(o))->liborLegBPS();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBMASwapLiborLegNPV(QlBMASwap* o, char **e) {try {return (*arg(o))->liborLegNPV();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlOvernightIndexedSwapFairRate(QlOvernightIndexedSwap* o, char **e) {try {return (*arg(o))->fairRate();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlOvernightIndexedSwapFairSpread(QlOvernightIndexedSwap* o, char **e) {try {return (*arg(o))->fairSpread();} catch (std::exception& er) {return handleException<double>(e, er);}}
Leg* qlOvernightIndexedSwapFixedLeg(QlOvernightIndexedSwap* o, char **e) {try {return ret(new Leg((*arg(o))->fixedLeg()));} catch (std::exception& er) {return handleException<Leg*>(e, er);}}
double qlOvernightIndexedSwapFixedLegBPS(QlOvernightIndexedSwap* o, char **e) {try {return (*arg(o))->fixedLegBPS();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlOvernightIndexedSwapFixedLegNPV(QlOvernightIndexedSwap* o, char **e) {try {return (*arg(o))->fixedLegNPV();} catch (std::exception& er) {return handleException<double>(e, er);}}
Leg* qlOvernightIndexedSwapOvernightLeg(QlOvernightIndexedSwap* o, char **e) {try {return ret(new Leg((*arg(o))->overnightLeg()));} catch (std::exception& er) {return handleException<Leg*>(e, er);}}
double qlOvernightIndexedSwapOvernightLegBPS(QlOvernightIndexedSwap* o, char **e) {try {return (*arg(o))->overnightLegBPS();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlOvernightIndexedSwapOvernightLegNPV(QlOvernightIndexedSwap* o, char **e) {try {return (*arg(o))->overnightLegNPV();} catch (std::exception& er) {return handleException<double>(e, er);}}
void qlFreeCdsOption(QlCdsOption *o) {del(o);}
QlOption* qlCdsOptionAsOption(QlCdsOption *o) {return ret(new QlOption(*arg(o)));}
void qlFreeCreditDefaultSwap(QlCreditDefaultSwap *o) {del(o);}
QlInstrument* qlCreditDefaultSwapAsInstrument(QlCreditDefaultSwap *o) {return ret(new QlInstrument(*arg(o)));}
void qlFreeClaim(QlClaim *o) {del(o);}
QlClaim* qlFaceValueAccrualClaim(QlBond* referenceSecurity, char **e) {try {return ret(new QlClaim(alloc(new FaceValueAccrualClaim(*arg(referenceSecurity)))));} catch (std::exception& er) {return handleException<QlClaim*>(e, er);}}

QlClaim* qlFaceValueClaim(char **e) {try {return ret(new QlClaim(alloc(new FaceValueClaim())));} catch (std::exception& er) {return handleException<QlClaim*>(e, er);}}
QlCreditDefaultSwap* qlCreditDefaultSwap1(int side, double notional, double upfront, double spread, Schedule* schedule, int paymentConvention, DayCounter* dayCounter, int settlesAccrual, int paysAtDefaultTime, int protectionStart, int upfrontDate, QlClaim* x11, DayCounter* lastPeriodDayCounter, int rebatesAccrual, int tradeDate, unsigned cashSettlementDays, char **e) {
  try {return ret(new QlCreditDefaultSwap(alloc(new CreditDefaultSwap((Protection::Side)side, notional, upfront, spread, *arg(schedule), (BusinessDayConvention)paymentConvention, *arg(dayCounter), settlesAccrual, paysAtDefaultTime, qlNullableDate(protectionStart), qlNullableDate(upfrontDate), (*arg(x11)),
            *arg(lastPeriodDayCounter), rebatesAccrual, qlNullableDate(tradeDate), cashSettlementDays))));
  } catch (std::exception& er) {return handleException<QlCreditDefaultSwap*>(e, er);}}

QlCreditDefaultSwap* qlCreditDefaultSwap(int side, double notional, double spread, Schedule* schedule, int paymentConvention, DayCounter* dayCounter, int settlesAccrual, int paysAtDefaultTime, int protectionStart, QlClaim* x9, DayCounter* lastPeriodDayCounter, int rebatesAccrual, int tradeDate, unsigned cashSettlementDays, char **e) {
  try {return ret(new QlCreditDefaultSwap(alloc(new CreditDefaultSwap((Protection::Side)side, notional, spread, *arg(schedule), (BusinessDayConvention)paymentConvention, *arg(dayCounter), settlesAccrual, paysAtDefaultTime, qlNullableDate(protectionStart), (*arg(x9)),
            *arg(lastPeriodDayCounter), rebatesAccrual, qlNullableDate(tradeDate), cashSettlementDays))));
  } catch (std::exception& er) {return handleException<QlCreditDefaultSwap*>(e, er);}}

double qlCreditDefaultSwapFairSpread(QlCreditDefaultSwap* o, char **e) {try {return (*arg(o))->fairSpread();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCreditDefaultSwapConventionalSpread(QlCreditDefaultSwap* o, double conventionalRecovery, QlYieldTermStructure* discountCurve, DayCounter* dayCounter, int model, char **e) {
  try {return (*arg(o))->conventionalSpread(conventionalRecovery, Handle<YieldTermStructure>(*arg(discountCurve)), *arg(dayCounter), (CreditDefaultSwap::PricingModel)model);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCreditDefaultSwapCouponLegBPS(QlCreditDefaultSwap* o, char **e) {try {return (*arg(o))->couponLegBPS();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCreditDefaultSwapCouponLegNPV(QlCreditDefaultSwap* o, char **e) {try {return (*arg(o))->couponLegNPV();} catch (std::exception& er) {return handleException<double>(e, er);}}
Leg* qlCreditDefaultSwapCoupons(QlCreditDefaultSwap* o, char **e) {try {return alloc(new Leg((*arg(o))->coupons()));} catch (std::exception& er) {return handleException<Leg*>(e, er);}}
double qlCreditDefaultSwapDefaultLegNPV(QlCreditDefaultSwap* o, char **e) {try {return (*arg(o))->defaultLegNPV();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCreditDefaultSwapFairUpfront(QlCreditDefaultSwap* o, char **e) {try {return (*arg(o))->fairUpfront();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCreditDefaultSwapImpliedHazardRate(QlCreditDefaultSwap* o, double targetNPV, QlYieldTermStructure* discountCurve, DayCounter* dayCounter, double recoveryRate, double accuracy, int model, char **e) {
  try {return (*arg(o))->impliedHazardRate(targetNPV, Handle<YieldTermStructure>(*arg(discountCurve)), *arg(dayCounter), recoveryRate, accuracy, (CreditDefaultSwap::PricingModel)model);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCreditDefaultSwapUpfrontBPS(QlCreditDefaultSwap* o, char **e) {try {return (*arg(o))->upfrontBPS();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCreditDefaultSwapUpfrontNPV(QlCreditDefaultSwap* o, char **e) {try {return (*arg(o))->upfrontNPV();} catch (std::exception& er) {return handleException<double>(e, er);}}
void qlFreeBarrierOption(QlBarrierOption *o) {del(o);}
QlOneAssetOption* qlBarrierOptionAsOneAssetOption(QlBarrierOption *o) {return ret(new QlOneAssetOption(*arg(o)));}
void qlFreeMargrabeOption(QlMargrabeOption *o) {del(o);}
QlMultiAssetOption* qlMargrabeOptionAsMultiAssetOption(QlMargrabeOption *o) {return ret(new QlMultiAssetOption(*arg(o)));}
void qlFreeMultiAssetOption(QlMultiAssetOption *o) {del(o);}
QlOption* qlMultiAssetOptionAsOption(QlMultiAssetOption *o) {return ret(new QlOption(*arg(o)));}
void qlFreeOneAssetOption(QlOneAssetOption *o) {del(o);}
QlOption* qlOneAssetOptionAsOption(QlOneAssetOption *o) {return ret(new QlOption(*arg(o)));}
void qlFreeOption(QlOption *o) {del(o);}
QlInstrument* qlOptionAsInstrument(QlOption *o) {return ret(new QlInstrument(*arg(o)));}
void qlFreeQuantoVanillaOption(QlQuantoVanillaOption *o) {del(o);}
QlOneAssetOption* qlQuantoVanillaOptionAsOneAssetOption(QlQuantoVanillaOption *o) {return ret(new QlOneAssetOption(*arg(o)));}
void qlFreeSwaption(QlSwaption *o) {del(o);}
QlOption* qlSwaptionAsOption(QlSwaption *o) {return ret(new QlOption(*arg(o)));}
void qlFreeVanillaOption(QlVanillaOption *o) {del(o);}
QlOneAssetOption* qlVanillaOptionAsOneAssetOption(QlVanillaOption *o) {return ret(new QlOneAssetOption(*arg(o)));}
void qlFreeSwingExercise(QlSwingExercise *o) {del(o);}
QlBermudanExercise* qlSwingExerciseAsBermudanExercise(QlSwingExercise *o) {return ret(new QlBermudanExercise(*arg(o)));}
double qlCdsOptionAtmRate(QlCdsOption* o, char **e) {try {return (*arg(o))->atmRate();} catch (std::exception& er) {return handleException<double>(e, er);}}
QlCdsOption* qlCdsOption(QlCreditDefaultSwap* swap, QlExercise* exercise, int knocksOut, char **e) {
  try {return ret(new QlCdsOption(alloc(new CdsOption(*arg(swap), *arg(exercise), knocksOut))));
  } catch (std::exception& er) {return handleException<QlCdsOption*>(e, er);}}
double qlCdsOptionImpliedVolatility(QlCdsOption* o, double price, QlYieldTermStructure* termStructure, QlDefaultProbabilityTermStructure* x3, double recoveryRate, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e) {
  try {return (*arg(o))->impliedVolatility(price, Handle<YieldTermStructure>(*arg(termStructure)), Handle<DefaultProbabilityTermStructure>(*arg(x3)), recoveryRate, accuracy, maxEvaluations, minVol, maxVol);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCdsOptionRiskyAnnuity(QlCdsOption* o, char **e) {
  try {return (*arg(o))->riskyAnnuity();
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlSwaptionImpliedVolatility(QlSwaption* o, double price, QlYieldTermStructure* discountCurve, double guess, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, int type, double displacement, int priceType, char **e) {
  try {return (*arg(o))->impliedVolatility(price, Handle<YieldTermStructure>(*arg(discountCurve)), guess, accuracy, maxEvaluations, minVol, maxVol, (VolatilityType)type, displacement, (Swaption::PriceType)priceType);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
QlSwaption* qlSwaption(QlVanillaSwap* swap, QlExercise* exercise, int delivery, int settlementMethod, char **e) {
  try {return ret(new QlSwaption(alloc(new Swaption(*arg(swap), *arg(exercise), (Settlement::Type) delivery, (Settlement::Method) settlementMethod))));
  } catch (std::exception& er) {return handleException<QlSwaption*>(e, er);}}

void qlFreeQuantoBarrierOption(QlQuantoBarrierOption *o) {del(o);}
QlOneAssetOption* qlQuantoBarrierOptionAsOneAssetOption(QlQuantoBarrierOption *o) {return ret(new QlOneAssetOption(*arg(o)));}
void qlFreeQuantoForwardVanillaOption(QlQuantoForwardVanillaOption *o) {del(o);}
QlOneAssetOption* qlQuantoForwardVanillaOptionAsOneAssetOption(QlQuantoForwardVanillaOption *o) {return ret(new QlOneAssetOption(*arg(o)));}

QlBarrierOption* qlBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e) {
  try {return ret(new QlBarrierOption(alloc(new BarrierOption((Barrier::Type)barrierType, barrier, rebate, *arg(payoff), (*arg(exercise))))));
  } catch (std::exception& er) {return handleException<QlBarrierOption*>(e, er);}}
double qlBarrierOptionImpliedVolatility(QlBarrierOption* o, double price, QlGeneralizedBlackScholesProcess* process, unsigned dividendsLen, QlDividend** dividends, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e) {
  try {DividendSchedule d = qlVector(dividends, dividendsLen);
    return (*arg(o))->impliedVolatility(price, *arg(process), d, accuracy, maxEvaluations, minVol, maxVol);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
QlOneAssetOption* qlForwardVanillaOption(double moneyness, int resetDate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e) {
  try {return ret(new QlOneAssetOption(alloc(new ForwardVanillaOption(moneyness, Date(resetDate), *arg(payoff), *arg(exercise)))));
  } catch (std::exception& er) {return handleException<QlOneAssetOption*>(e, er);}}
double qlMargrabeOptionDelta1(QlMargrabeOption* o, char **e) {try {return (*arg(o))->delta1();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlMargrabeOptionDelta2(QlMargrabeOption* o, char **e) {try {return (*arg(o))->delta2();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlMargrabeOptionGamma1(QlMargrabeOption* o, char **e) {try {return (*arg(o))->gamma1();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlMargrabeOptionGamma2(QlMargrabeOption* o, char **e) {try {return (*arg(o))->gamma2();} catch (std::exception& er) {return handleException<double>(e, er);}}
QlMargrabeOption* qlMargrabeOption(int Q1, int Q2, QlExercise* x2, char **e) {try {return ret(new QlMargrabeOption(alloc(new MargrabeOption(Q1, Q2, (*arg(x2))))));} catch (std::exception& er) {return handleException<QlMargrabeOption*>(e, er);}}
double qlMultiAssetOptionDelta(QlMultiAssetOption* o, char **e) {try {return (*arg(o))->delta();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlMultiAssetOptionDividendRho(QlMultiAssetOption* o, char **e) {try {return (*arg(o))->dividendRho();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlMultiAssetOptionGamma(QlMultiAssetOption* o, char **e) {try {return (*arg(o))->gamma();} catch (std::exception& er) {return handleException<double>(e, er);}}
QlMultiAssetOption* qlMultiAssetOption(QlPayoff* x0, QlExercise* x1, char **e) {try {return ret(new QlMultiAssetOption(alloc(new MultiAssetOption(*arg(x0), (*arg(x1))))));} catch (std::exception& er) {return handleException<QlMultiAssetOption*>(e, er);}}
double qlMultiAssetOptionRho(QlMultiAssetOption* o, char **e) {try {return (*arg(o))->rho();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlMultiAssetOptionTheta(QlMultiAssetOption* o, char **e) {try {return (*arg(o))->theta();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlMultiAssetOptionVega(QlMultiAssetOption* o, char **e) {try {return (*arg(o))->vega();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlOneAssetOptionDelta(QlOneAssetOption* o, char **e) {try {return (*arg(o))->delta();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlOneAssetOptionDeltaForward(QlOneAssetOption* o, char **e) {try {return (*arg(o))->deltaForward(); } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlOneAssetOptionDividendRho(QlOneAssetOption* o, char **e) {try {return (*arg(o))->dividendRho();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlOneAssetOptionElasticity(QlOneAssetOption* o, char **e) {try {return (*arg(o))->elasticity();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlOneAssetOptionGamma(QlOneAssetOption* o, char **e) {try {return (*arg(o))->gamma();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlOneAssetOptionItmCashProbability(QlOneAssetOption* o, char **e) {try {return (*arg(o))->itmCashProbability();} catch (std::exception& er) {return handleException<double>(e, er);}}
QlOneAssetOption* qlOneAssetOption(QlPayoff* x0, QlExercise* x1, char **e) {try {return ret(new QlOneAssetOption(alloc(new OneAssetOption(*arg(x0), (*arg(x1))))));} catch (std::exception& er) {return handleException<QlOneAssetOption*>(e, er);}}
double qlOneAssetOptionRho(QlOneAssetOption* o, char **e) {try {return (*arg(o))->rho();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlOneAssetOptionStrikeSensitivity(QlOneAssetOption* o, char **e) {try {return (*arg(o))->strikeSensitivity();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlOneAssetOptionTheta(QlOneAssetOption* o, char **e) {try {return (*arg(o))->theta();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlOneAssetOptionThetaPerDay(QlOneAssetOption* o, char **e) {try {return (*arg(o))->thetaPerDay();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlOneAssetOptionVega(QlOneAssetOption* o, char **e) {try {return (*arg(o))->vega();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantoBarrierOptionQlambda(QlQuantoBarrierOption* o, char **e) {try {return (*arg(o))->qlambda();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantoBarrierOptionQrho(QlQuantoBarrierOption* o, char **e) {try {return (*arg(o))->qrho();} catch (std::exception& er) {return handleException<double>(e, er);}}
QlQuantoBarrierOption* qlQuantoBarrierOption(int barrierType, double barrier, double rebate, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e) {
  try {return ret(new QlQuantoBarrierOption(alloc(new QuantoBarrierOption((Barrier::Type)barrierType, barrier, rebate, *arg(payoff), (*arg(exercise))))));
  } catch (std::exception& er) {return handleException<QlQuantoBarrierOption*>(e, er);}}
double qlQuantoBarrierOptionQvega(QlQuantoBarrierOption* o, char **e) {try {return (*arg(o))->qvega();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantoForwardVanillaOptionQlambda(QlQuantoForwardVanillaOption* o, char **e) {try {return (*arg(o))->qlambda();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantoForwardVanillaOptionQrho(QlQuantoForwardVanillaOption* o, char **e) {try {return (*arg(o))->qrho();} catch (std::exception& er) {return handleException<double>(e, er);}}
QlQuantoForwardVanillaOption* qlQuantoForwardVanillaOption(double moneyness, int resetDate, QlStrikedTypePayoff* x2, QlExercise* x3, char **e) {
  try {return ret(new QlQuantoForwardVanillaOption(alloc(new QuantoForwardVanillaOption(moneyness, Date(resetDate), *arg(x2), *arg(x3)))));
  } catch (std::exception& er) {return handleException<QlQuantoForwardVanillaOption*>(e, er);}}
double qlQuantoForwardVanillaOptionQvega(QlQuantoForwardVanillaOption* o, char **e) {try {return (*arg(o))->qvega();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantoVanillaOptionQlambda(QlQuantoVanillaOption* o, char **e) {try {return (*arg(o))->qlambda();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlQuantoVanillaOptionQrho(QlQuantoVanillaOption* o, char **e) {try {return (*arg(o))->qrho();} catch (std::exception& er) {return handleException<double>(e, er);}}
QlQuantoVanillaOption* qlQuantoVanillaOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e) {
  try {return ret(new QlQuantoVanillaOption(alloc(new QuantoVanillaOption(*arg(x0), (*arg(x1))))));
  } catch (std::exception& er) {return handleException<QlQuantoVanillaOption*>(e, er);}}
double qlQuantoVanillaOptionQvega(QlQuantoVanillaOption* o, char **e) {try {return (*arg(o))->qvega();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlVanillaOptionImpliedVolatility(QlVanillaOption* o, double price, QlGeneralizedBlackScholesProcess* process, unsigned dividendsLen, QlDividend** dividends, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e) {
  try {DividendSchedule d = qlVector(dividends, dividendsLen);
    return (*arg(o))->impliedVolatility(price, *arg(process), d, accuracy, maxEvaluations, minVol, maxVol);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
QlVanillaOption* qlVanillaOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e) {
  try {return ret(new QlVanillaOption(alloc(new VanillaOption(*arg(x0), (*arg(x1))))));
  } catch (std::exception& er) {return handleException<QlVanillaOption*>(e, er);}}
QlMultiAssetOption* qlBasketOption(QlBasketPayoff* x0, QlExercise* x1, char **e) {
  try {return ret(new QlMultiAssetOption(alloc(new BasketOption(*arg(x0), (*arg(x1))))));
  } catch (std::exception& er) {return handleException<QlMultiAssetOption*>(e, er);}}
QlMultiAssetOption* qlHimalayaOption(unsigned fixingDatesLen, int* fixingDates, double strike, char **e) {
  try {return ret(new QlMultiAssetOption(alloc(new HimalayaOption(qlDateVector(fixingDates, fixingDatesLen), strike))));
  } catch (std::exception& er) {return handleException<QlMultiAssetOption*>(e, er);}}
QlMultiAssetOption* qlPagodaOption(unsigned fixingDatesLen, int* fixingDates, double roof, double fraction, char **e) {
  try {return ret(new QlMultiAssetOption(alloc(new PagodaOption(qlDateVector(fixingDates, fixingDatesLen), roof, fraction))));
  } catch (std::exception& er) {return handleException<QlMultiAssetOption*>(e, er);}}
QlOneAssetOption* qlCliquetOption(QlPercentageStrikePayoff* x0, QlEuropeanExercise* maturity, unsigned resetDatesLen, int* resetDates, char **e) {
  try {return ret(new QlOneAssetOption(alloc(new CliquetOption(*arg(x0), *arg(maturity), qlDateVector(resetDates, resetDatesLen)))));
  } catch (std::exception& er) {return handleException<QlOneAssetOption*>(e, er);}}
QlOneAssetOption* qlContinuousAveragingAsianOption(int averageType, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e) {
  try {return ret(new QlOneAssetOption(alloc(new ContinuousAveragingAsianOption((Average::Type)averageType, *arg(payoff), *arg(exercise)))));
  } catch (std::exception& er) {return handleException<QlOneAssetOption*>(e, er);}}
QlOneAssetOption* qlContinuousFixedLookbackOption(double currentMinmax, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e) {
  try {return ret(new QlOneAssetOption(alloc(new ContinuousFixedLookbackOption(currentMinmax, *arg(payoff), *arg(exercise)))));
  } catch (std::exception& er) {return handleException<QlOneAssetOption*>(e, er);}}
QlOneAssetOption* qlContinuousFloatingLookbackOption(double currentMinmax, QlTypePayoff* payoff, QlExercise* exercise, char **e) {
  try {return ret(new QlOneAssetOption(alloc(new ContinuousFloatingLookbackOption(currentMinmax, *arg(payoff), *arg(exercise)))));
  } catch (std::exception& er) {return handleException<QlOneAssetOption*>(e, er);}}
QlOneAssetOption* qlDiscreteAveragingAsianOption(int averageType, double runningAccumulator, unsigned pastFixings, unsigned fixingDatesLen, int* fixingDates, QlStrikedTypePayoff* payoff, QlExercise* exercise, char **e) {
  try {return ret(new QlOneAssetOption(alloc(new DiscreteAveragingAsianOption((Average::Type)averageType, runningAccumulator, pastFixings, qlDateVector(fixingDates, fixingDatesLen), *arg(payoff), *arg(exercise)))));
  } catch (std::exception& er) {return handleException<QlOneAssetOption*>(e, er);}}
QlOneAssetOption* qlVanillaStorageOption(QlBermudanExercise* ex, double capacity, double load, double changeRate, char **e) {
  try {return ret(new QlOneAssetOption(alloc(new VanillaStorageOption(*arg(ex), capacity, load, changeRate))));
  } catch (std::exception& er) {return handleException<QlOneAssetOption*>(e, er);}}
QlOneAssetOption* qlVanillaSwingOption(QlStrikedTypePayoff* payoff, QlSwingExercise* ex, unsigned minExerciseRights, unsigned maxExerciseRights, char **e) {
  try {return ret(new QlOneAssetOption(alloc(new VanillaSwingOption(*arg(payoff), *arg(ex), minExerciseRights, maxExerciseRights))));
  } catch (std::exception& er) {return handleException<QlOneAssetOption*>(e, er);}}
QlVanillaOption* qlEuropeanOption(QlStrikedTypePayoff* x0, QlExercise* x1, char **e) {try {return ret(new QlVanillaOption(alloc(new EuropeanOption(*arg(x0), (*arg(x1))))));} catch (std::exception& er) {return handleException<QlVanillaOption*>(e, er);}}
QlBond *qlBond(unsigned settlDays, Calendar *calendar, int issueDate, Leg *coupons, char **e) {
  try {return ret(new QlBond(alloc(new Bond(settlDays, *arg(calendar), qlNullableDate(issueDate), *arg(coupons)))));
  } catch (std::exception& er) {return handleException<QlBond *>(e, er);}}
QlBond *qlBond1(unsigned settlDays, Calendar *calendar, double faceAmount, int maturityDate, int issueDate, Leg *cashFlows, char **e) {
  try {return ret(new QlBond(alloc(new Bond(settlDays, *arg(calendar), faceAmount, qlNullableDate(maturityDate), qlNullableDate(issueDate), *arg(cashFlows)))));
  } catch (std::exception& er) {return handleException<QlBond *>(e, er);}}

int qlBondMaturityDate(QlBond *bond) {return qlNullableDate((*arg(bond))->maturityDate());}
void qlFreeBond(QlBond *bond) {del(bond);}
void qlFreeFixedRateBond(QlFixedRateBond *bond) {del(bond);}
QlBond *qlFixedRateBondAsBond(QlFixedRateBond *bond) {return ret(new QlBond(*arg(bond)));}

void qlFreeCPIBond(QlCPIBond *bond) {del(bond);}
QlBond *qlCPIBondAsBond(QlCPIBond *bond) {return ret(new QlBond(*arg(bond)));}
QlCPIBond *qlCPIBond(unsigned settlementDays, double faceAmount, double baseCPI, int obsLagLen, int obsLagUnit, QlZeroInflationIndex* index, int observationInterpolation, Schedule *schedule, unsigned couponsLen, double *coupons, DayCounter *accrualDayCounter, int paymentConvention, int issueDate, Calendar *paymentCalendar, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, char **e) {
  try {std::vector<Rate> cpns(coupons, coupons+couponsLen);
    return ret(new QlCPIBond(alloc(new CPIBond(settlementDays, faceAmount, baseCPI, Period(obsLagLen, (TimeUnit)obsLagUnit), *arg(index),
              (CPI::InterpolationType)observationInterpolation, *arg(schedule), cpns, *arg(accrualDayCounter), (BusinessDayConvention)paymentConvention,
              qlNullableDate(issueDate), *arg(paymentCalendar), Period(exCouponPeriodLen, (TimeUnit)exCouponPeriodUnit), *arg(exCouponCalendar),
              (BusinessDayConvention)exCouponConvention, exCouponEndOfMonth))));
  } catch (std::exception& er) {return handleException<QlCPIBond *>(e, er);}}

QlFixedRateBond *qlFixedRateBond(unsigned settlDays, double face, Schedule *schedule, unsigned cLen, double *coupons, DayCounter *counter,
    int payConv, double redemption, int issue, Calendar *payCal, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, DayCounter* firstPeriodDayCounter, char **e) {
  try {std::vector<Rate> cpns(coupons, coupons+cLen);
    return ret(new QlFixedRateBond(alloc(new FixedRateBond(settlDays, face, *arg(schedule),
              cpns, *arg(counter), (BusinessDayConvention) payConv, redemption, qlNullableDate(issue), *arg(payCal),
              Period(exCouponPeriodLen, (TimeUnit)exCouponPeriodUnit), *arg(exCouponCalendar), (BusinessDayConvention)exCouponConvention, exCouponEndOfMonth,
              *arg(firstPeriodDayCounter)))));
  } catch (std::exception& er) {return handleException<QlFixedRateBond *>(e, er);}}

QlInstrument *qlBondAsInstrument(QlBond *b) {return ret(new QlInstrument(*arg(b)));}

QlBond *qlZeroCouponBond(int settlDays, Calendar *cal, double face, int maturity, int payConv, double redemption, int issue, char **e) {
  try {return ret(new QlBond(alloc(new ZeroCouponBond(settlDays, *arg(cal), face, Date(maturity), (BusinessDayConvention) payConv, redemption, qlNullableDate(issue)))));
  } catch (std::exception& er) {return handleException<QlBond *>(e, er);}}

QlBond *qlFloatingRateBond(unsigned settlDays, double face, Schedule *sched, QlIborIndex *index, DayCounter *dc, int payConv, unsigned fixDays,
  unsigned nGearings, double *gearings, unsigned nSpreads, double *spreads, unsigned nCaps, double *caps, unsigned nFloors, double *floors,
  int inArrears, double redemption, int issue, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, int fixingConvention, char **e) {
  try {std::vector<Real> gs(gearings, gearings+nGearings); std::vector<Spread> sps(spreads, spreads+nSpreads);
    std::vector<Rate> cs(caps, caps+nCaps); std::vector<Rate> fs(floors, floors+nFloors);
    return ret(new QlBond(alloc(new FloatingRateBond(settlDays, face, *arg(sched), *arg(index), *arg(dc), (BusinessDayConvention) payConv, fixDays, gs,
	  sps, cs, fs, inArrears, redemption, qlNullableDate(issue),
	  Period(exCouponPeriodLen, (TimeUnit)exCouponPeriodUnit), *arg(exCouponCalendar), (BusinessDayConvention)exCouponConvention, exCouponEndOfMonth,
	  (BusinessDayConvention)fixingConvention))));
  } catch (std::exception& er) {return handleException<QlBond *>(e, er);}}

void qlBondNotionals(QlBond* o, unsigned *len, double **ns, char **e) {
  try {const std::vector<double>& notionals = (*arg(o))->notionals(); *len = notionals.size(); *ns = qlAllocateDoubles(*len); std::copy(notionals.begin(), notionals.end(), *ns);
  } catch (std::exception& er) {(void)handleException<double*>(e, er);}}
double qlBondYield(QlBond* o, DayCounter* dc, int comp, int freq, double accuracy, unsigned maxEvaluations, double guess, int priceType, char **e) {
  try {return (*arg(o))->yield(*arg(dc), (Compounding)comp, (Frequency)freq, accuracy, maxEvaluations, guess, (Bond::Price::Type)priceType);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

double qlBondAccruedAmount(QlBond* o, int d, char **e) {try {return (*arg(o))->accruedAmount(Date(d));} catch (std::exception& er) {return handleException<double>(e, er);}}

double qlBondCleanPrice1(QlBond* o, double yield, DayCounter* dc, int comp, int freq, int settlementDate, char **e) {
  try {return (*arg(o))->cleanPrice(yield, *arg(dc), (Compounding)comp, (Frequency)freq, Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondDirtyPrice1(QlBond* o, double yield, DayCounter* dc, int comp, int freq, int settlementDate, char **e) {
  try {return (*arg(o))->dirtyPrice(yield, *arg(dc), (Compounding)comp, (Frequency)freq, Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}

int qlBondNextCashFlowDate(QlBond* o, int d, char **e) {try {return qlNullableDate((*arg(o))->nextCashFlowDate(Date(d)));} catch (std::exception& er) {return handleException<int>(e, er);}}
double qlBondNextCouponRate(QlBond* o, int d, char **e) {try {return (*arg(o))->nextCouponRate(Date(d));} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondNotional(QlBond* o, int d, char **e) {try {return (*arg(o))->notional(Date(d));} catch (std::exception& er) {return handleException<double>(e, er);}}
int qlBondPreviousCashFlowDate(QlBond* o, int d, char **e) {try {return qlNullableDate((*arg(o))->previousCashFlowDate(Date(d)));} catch (std::exception& er) {return handleException<int>(e, er);}}
double qlBondPreviousCouponRate(QlBond* o, int d, char **e) {try {return (*arg(o))->previousCouponRate(Date(d));} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondSettlementValue1(QlBond* o, double cleanPrice, char **e) {try {return (*arg(o))->settlementValue(cleanPrice);} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondSettlementValue(QlBond* o, char **e) {try {return (*arg(o))->settlementValue();} catch (std::exception& er) {return handleException<double>(e, er);}}

double qlBondYield1(QlBond* o, double price, int priceType, DayCounter* dc, int comp, int freq, int settlementDate, double accuracy, unsigned maxEvaluations, char **e) {
  try {return (*arg(o))->yield(Bond::Price(price, (Bond::Price::Type)priceType), *arg(dc), (Compounding)comp, (Frequency)freq, Date(settlementDate), accuracy, maxEvaluations);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

int qlBondIsTradable(QlBond* o, int d, char **e) {try {return (*arg(o))->isTradable(Date(d));} catch (std::exception& er) {return handleException<int>(e, er);}}
Leg* qlBondCashflows(QlBond* o, char **e) {try {return ret(new Leg((*arg(o))->cashflows()));} catch (std::exception& er) {return handleException<Leg*>(e, er);}}
Leg* qlBondRedemptions(QlBond* o, char **e) {try {return ret(new Leg((*arg(o))->redemptions()));} catch (std::exception& er) {return handleException<Leg*>(e, er);}}
int qlBondSettlementDate(QlBond* o, int d, char **e) {try {return ((*arg(o))->settlementDate(Date(d))).serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}
int qlBondStartDate(QlBond* o, char **e) {try {return ((*arg(o))->startDate()).serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}

int qlBondFunctionsAccrualDays(QlBond* bond, int settlementDate, char **e) {
  try {return BondFunctions::accrualDays(**arg(bond), Date(settlementDate));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlBondFunctionsAccrualEndDate(QlBond* bond, int settlementDate, char **e) {
  try {return qlNullableDate(BondFunctions::accrualEndDate(**arg(bond), Date(settlementDate)));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
double qlBondFunctionsAccrualPeriod(QlBond* bond, int settlementDate, char **e) {
  try {return BondFunctions::accrualPeriod(**arg(bond), Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
int qlBondFunctionsAccrualStartDate(QlBond* bond, int settlementDate, char **e) {
  try {return qlNullableDate(BondFunctions::accrualStartDate(**arg(bond), Date(settlementDate)));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlBondFunctionsAccruedDays(QlBond* bond, int settlementDate, char **e) {
  try {return BondFunctions::accruedDays(**arg(bond), Date(settlementDate));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
double qlBondFunctionsAccruedPeriod(QlBond* bond, int settlementDate, char **e) {
  try {return BondFunctions::accruedPeriod(**arg(bond), Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsAtmRate(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, double price, int priceType, char **e) {
  try {return BondFunctions::atmRate(**arg(bond), **arg(discountCurve), Date(settlementDate), Bond::Price(price, (Bond::Price::Type)priceType));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsBasisPointValue1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e) {
  try {return BondFunctions::basisPointValue(**arg(bond), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsBasisPointValue(QlBond* bond, InterestRate* yield, int settlementDate, char **e) {
  try {return BondFunctions::basisPointValue(**arg(bond), *arg(yield), Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsBps1(QlBond* bond, InterestRate* yield, int settlementDate, char **e) {
  try {return BondFunctions::bps(**arg(bond), *arg(yield), Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsBps2(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e) {
  try {return BondFunctions::bps(**arg(bond), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsBps(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, char **e) {
  try {return BondFunctions::bps(**arg(bond), **arg(discountCurve), Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsCleanPrice2(QlBond* bond, QlYieldTermStructure* discountCurve, int settlementDate, char **e) {
  try {return BondFunctions::cleanPrice(**arg(bond), **arg(discountCurve), Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsCleanPrice3(QlBond* bond, QlYieldTermStructure* discount, double zSpread, int compounding, int frequency, int settlementDate, char **e) {
  try {return BondFunctions::cleanPrice(**arg(bond), *arg(discount), zSpread, (Compounding)compounding, (Frequency)frequency, Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsCleanPrice4(QlBond* bond, InterestRate* yield, int settlementDate, char **e) {
  try {return BondFunctions::cleanPrice(**arg(bond), *arg(yield), Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsConvexity1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e) {
  try {return BondFunctions::convexity(**arg(bond), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsConvexity(QlBond* bond, InterestRate* yield, int settlementDate, char **e) {
  try {return BondFunctions::convexity(**arg(bond), *arg(yield), Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsDuration1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int type, int settlementDate, char **e) {
  try {return BondFunctions::duration(**arg(bond), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, (Duration::Type)type, Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsDuration(QlBond* bond, InterestRate* yield, int type, int settlementDate, char **e) {
  try {return BondFunctions::duration(**arg(bond), *arg(yield), (Duration::Type)type, Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsNextCashFlowAmount(QlBond* bond, int refDate, char **e) {
  try {return BondFunctions::nextCashFlowAmount(**arg(bond), Date(refDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsPreviousCashFlowAmount(QlBond* bond, int refDate, char **e) {
  try {return BondFunctions::previousCashFlowAmount(**arg(bond), Date(refDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
int qlBondFunctionsReferencePeriodEnd(QlBond* bond, int settlementDate, char **e) {
  try {return qlNullableDate(BondFunctions::referencePeriodEnd(**arg(bond), Date(settlementDate)));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlBondFunctionsReferencePeriodStart(QlBond* bond, int settlementDate, char **e) {
  try {return qlNullableDate(BondFunctions::referencePeriodStart(**arg(bond), Date(settlementDate)));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
double qlBondFunctionsYield2(QlBond* bond, double price, int priceType, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, double accuracy, unsigned maxIterations, double guess, char **e) {
  try {return BondFunctions::yield(**arg(bond), Bond::Price(price, (Bond::Price::Type)priceType), *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, Date(settlementDate), accuracy, maxIterations, guess);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsYieldValueBasisPoint1(QlBond* bond, double yield, DayCounter* dayCounter, int compounding, int frequency, int settlementDate, char **e) {
  try {return BondFunctions::yieldValueBasisPoint(**arg(bond), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsYieldValueBasisPoint(QlBond* bond, InterestRate* yield, int settlementDate, char **e) {
  try {return BondFunctions::yieldValueBasisPoint(**arg(bond), *arg(yield), Date(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondFunctionsZSpread(QlBond* bond, double price, int priceType, QlYieldTermStructure* x2, int compounding, int frequency, int settlementDate, double accuracy, unsigned maxIterations, double guess, char **e) {
  try {return BondFunctions::zSpread(**arg(bond), Bond::Price(price, (Bond::Price::Type)priceType), *arg(x2), (Compounding)compounding, (Frequency)frequency, Date(settlementDate), accuracy, maxIterations, guess);
  } catch (std::exception& er) {return handleException<double>(e, er);}}

double qlBondCleanPrice(QlBond* o, char **e) {try {return (*arg(o))->cleanPrice();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlBondDirtyPrice(QlBond* o, char **e) {try {return (*arg(o))->dirtyPrice();} catch (std::exception& er) {return handleException<double>(e, er);}}
void qlFreeCallableBond(QlCallableBond *o) {del(o);}
QlBond* qlCallableBondAsBond(QlCallableBond *o) {return ret(new QlBond(*arg(o)));}
void qlFreeConvertibleBond(QlConvertibleBond *o) {del(o);}
QlBond* qlConvertibleBondAsBond(QlConvertibleBond *o) {return ret(new QlBond(*arg(o)));}

QlCallableBond* qlCallableFixedRateBond(unsigned settlementDays, double faceAmount, Schedule* schedule, unsigned couponsLen, double* coupons, DayCounter* accrualDayCounter, int paymentConvention, double redemption, int issueDate, unsigned putCallScheduleLen, QlCallability** putCallSchedule, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, char **e) {
  try {return ret(new QlCallableBond(alloc(new CallableFixedRateBond(settlementDays, faceAmount, *arg(schedule), std::vector<double>(coupons, coupons+couponsLen), *arg(accrualDayCounter), (BusinessDayConvention)paymentConvention, redemption, qlNullableDate(issueDate), qlVector(putCallSchedule, putCallScheduleLen),
            Period(exCouponPeriodLen, (TimeUnit)exCouponPeriodUnit), *arg(exCouponCalendar), (BusinessDayConvention)exCouponConvention, exCouponEndOfMonth))));
  } catch (std::exception& er) {return handleException<QlCallableBond*>(e, er);}}
QlCallableBond* qlCallableZeroCouponBond(unsigned settlementDays, double faceAmount, Calendar* calendar, int maturityDate, DayCounter* dayCounter, int paymentConvention, double redemption, int issueDate, unsigned putCallScheduleLen, QlCallability** putCallSchedule, char **e) {
  try {return ret(new QlCallableBond(alloc(new CallableZeroCouponBond(settlementDays, faceAmount, *arg(calendar), Date(maturityDate), *arg(dayCounter), (BusinessDayConvention)paymentConvention, redemption, qlNullableDate(issueDate), qlVector(putCallSchedule, putCallScheduleLen)))));
  } catch (std::exception& er) {return handleException<QlCallableBond*>(e, er);}}
QlConvertibleBond* qlConvertibleFixedCouponBond(QlExercise* exercise, double conversionRatio, unsigned callabilityLen, QlCallability** callability, int issueDate, unsigned settlementDays, unsigned couponsLen, double* coupons, DayCounter* dayCounter, Schedule* schedule, double redemption, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, char **e) {
  try {return ret(new QlConvertibleBond(alloc(new ConvertibleFixedCouponBond(*arg(exercise), conversionRatio, qlVector(callability, callabilityLen), Date(issueDate), settlementDays, std::vector<double>(coupons, coupons+couponsLen), *arg(dayCounter), *arg(schedule), redemption,
            Period(exCouponPeriodLen, (TimeUnit)exCouponPeriodUnit), *arg(exCouponCalendar), (BusinessDayConvention)exCouponConvention, exCouponEndOfMonth))));
  } catch (std::exception& er) {return handleException<QlConvertibleBond*>(e, er);}}
QlConvertibleBond* qlConvertibleFloatingRateBond(QlExercise* exercise, double conversionRatio, unsigned callabilityLen, QlCallability** callability, int issueDate, unsigned settlementDays, QlIborIndex* index, unsigned fixingDays, unsigned spreadsLen, double* spreads, DayCounter* dayCounter, Schedule* schedule, double redemption, int exCouponPeriodLen, int exCouponPeriodUnit, Calendar* exCouponCalendar, int exCouponConvention, int exCouponEndOfMonth, char **e) {
  try {return ret(new QlConvertibleBond(alloc(new ConvertibleFloatingRateBond(*arg(exercise), conversionRatio, qlVector(callability, callabilityLen), Date(issueDate), settlementDays, (*arg(index)), fixingDays, std::vector<double>(spreads, spreads+spreadsLen), *arg(dayCounter), *arg(schedule), redemption,
            Period(exCouponPeriodLen, (TimeUnit)exCouponPeriodUnit), *arg(exCouponCalendar), (BusinessDayConvention)exCouponConvention, exCouponEndOfMonth))));
  } catch (std::exception& er) {return handleException<QlConvertibleBond*>(e, er);}}
QlConvertibleBond* qlConvertibleZeroCouponBond(QlExercise* exercise, double conversionRatio, unsigned callabilityLen, QlCallability** callability, int issueDate, unsigned settlementDays, DayCounter* dayCounter, Schedule* schedule, double redemption, char **e) {
  try {return ret(new QlConvertibleBond(alloc(new ConvertibleZeroCouponBond(*arg(exercise), conversionRatio, qlVector(callability, callabilityLen), Date(issueDate), settlementDays, *arg(dayCounter), *arg(schedule), redemption))));
  } catch (std::exception& er) {return handleException<QlConvertibleBond*>(e, er);}}

QlCallability* qlSoftCallability(double price, int priceType, int date, double trigger, char **e) {
  try {Bond::Price p(price, (Bond::Price::Type)priceType); return ret(new QlCallability(alloc(new SoftCallability(p, Date(date), trigger))));
  } catch (std::exception& er) {return handleException<QlCallability*>(e, er);}}
Leg *qlLeg(unsigned len, double *amounts, int *dates, char **e) {
  Leg *leg = 0;
  try {leg = new Leg(); leg->reserve(len);
    for (unsigned i = 0; i < len; ++i)
      leg->push_back(shared_ptr<CashFlow>(new SimpleCashFlow(amounts[i], Date(dates[i]))));
    return alloc(leg);
  } catch (std::exception& er) {return handleException(e, er, leg);}}

int qlLegStartDate(Leg *leg, char **e) {try {Date d = CashFlows::startDate(*arg(leg)); return d.serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}
void qlFreeLeg(Leg *leg) {del(leg);}

Leg *qlNextCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {const Leg &l = *arg(leg);
    Leg::const_iterator i = CashFlows::nextCashFlow(l,
        includeSettlementDateFlows, qlNullableDate(settlementDate));
    return new Leg(i, l.end());
  } catch (std::exception& er) {return handleException<Leg *>(e, er);}}
Leg *qlPreviousCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {const Leg &l = *arg(leg);
    Leg::const_reverse_iterator i = CashFlows::previousCashFlow(l,
        includeSettlementDateFlows, qlNullableDate(settlementDate));
    return new Leg(l.begin(), i.base());
  } catch (std::exception& er) {return handleException<Leg *>(e, er);}}
void qlLegCashFlows(Leg *leg, int includeSettlementDateFlows, int settlementDate,
   unsigned *al, double **amount, unsigned *dl, int **date, unsigned *hl, int **hasOccurred, char **e) {
  *amount = 0; *date = 0; *hasOccurred = 0;
  try {const Leg& l = *arg(leg); *amount = qlAllocateDoubles(l.size()); *date = qlAllocateInts(l.size()); *hasOccurred = qlAllocateInts(l.size());
    for (unsigned i = 0; i < l.size(); ++i) {
      (*amount)[i] = l[i]->amount();
      (*date)[i] = l[i]->date().serialNumber();
      (*hasOccurred)[i] = l[i]->hasOccurred(qlNullableDate(settlementDate), qlOptBool(includeSettlementDateFlows));
    }
    *al = l.size(); *dl = l.size(); *hl = l.size();
  } catch (std::exception& er) {qlFreeDoubles(*amount); qlFreeInts(*date); qlFreeInts(*hasOccurred); *e = DUP(er.what());}}

double qlCashFlowsDuration(Leg* leg, InterestRate* yield, int type, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::duration(*arg(leg), *arg(yield), (Duration::Type)type, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
int qlCashFlowsAccrualDays(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {return CashFlows::accrualDays(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlCashFlowsAccrualEndDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {return qlNullableDate(CashFlows::accrualEndDate(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate)));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
double qlCashFlowsAccrualPeriod(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {return CashFlows::accrualPeriod(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
int qlCashFlowsAccrualStartDate(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e) {
  try {return qlNullableDate(CashFlows::accrualStartDate(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlDate)));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
double qlCashFlowsAccruedAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {return CashFlows::accruedAmount(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
int qlCashFlowsAccruedDays(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {return CashFlows::accruedDays(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
double qlCashFlowsAccruedPeriod(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {return CashFlows::accruedPeriod(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsAtmRate(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, double npv, char **e) {
  try {return CashFlows::atmRate(*arg(leg), **arg(discountCurve), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate), npv);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsBasisPointValue1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::basisPointValue(*arg(leg), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsBasisPointValue(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::basisPointValue(*arg(leg), *arg(yield), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsBps1(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::bps(*arg(leg), *arg(yield), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsBps2(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::bps(*arg(leg), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsBps(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::bps(*arg(leg), *(*arg(discountCurve)), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsConvexity1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::convexity(*arg(leg), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsConvexity(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::convexity(*arg(leg), *arg(yield), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsDuration1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int type, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::duration(*arg(leg), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, (Duration::Type)type, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
int qlCashFlowsIsExpired(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {return CashFlows::isExpired(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlCashFlowsMaturityDate(Leg* leg, char **e) {
  try {return (CashFlows::maturityDate(*arg(leg))).serialNumber();
  } catch (std::exception& er) {return handleException<int>(e, er);}}
double qlCashFlowsNextCashFlowAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {return CashFlows::nextCashFlowAmount(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
int qlCashFlowsNextCashFlowDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {return qlNullableDate(CashFlows::nextCashFlowDate(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate)));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
double qlCashFlowsNextCouponRate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {return CashFlows::nextCouponRate(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsNominal(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e) {
  try {return CashFlows::nominal(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsNpv1(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::npv(*arg(leg), *arg(yield), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsNpv2(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::npv(*arg(leg), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsNpv3(Leg* leg, QlYieldTermStructure* discount, double zSpread, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::npv(*arg(leg), *arg(discount), zSpread, (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsNpv(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::npv(*arg(leg), **arg(discountCurve), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
void qlCashFlowsNpvbps(Leg* leg, QlYieldTermStructure* discountCurve, int includeSettlementDateFlows, int settlementDate, int npvDate, double *npv, double *bps, char **e) {
  try {
    auto r = CashFlows::npvbps(*arg(leg), **arg(discountCurve), includeSettlementDateFlows, Date(settlementDate), Date(npvDate));
    *npv = r.first; *bps = r.second;
  } catch (std::exception& er) {(void)handleException<int>(e, er);}}
double qlCashFlowsPreviousCashFlowAmount(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {return CashFlows::previousCashFlowAmount(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
int qlCashFlowsPreviousCashFlowDate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {return qlNullableDate(CashFlows::previousCashFlowDate(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate)));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
double qlCashFlowsPreviousCouponRate(Leg* leg, int includeSettlementDateFlows, int settlementDate, char **e) {
  try {return CashFlows::previousCouponRate(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlementDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
int qlCashFlowsReferencePeriodEnd(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e) {
  try {return qlNullableDate(CashFlows::referencePeriodEnd(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlDate)));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
int qlCashFlowsReferencePeriodStart(Leg* leg, int includeSettlementDateFlows, int settlDate, char **e) {
  try {return qlNullableDate(CashFlows::referencePeriodStart(*arg(leg), includeSettlementDateFlows, qlNullableDate(settlDate)));
  } catch (std::exception& er) {return handleException<int>(e, er);}}
double qlCashFlowsYield(Leg* leg, double npv, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, char **e) {
  try {return CashFlows::yield(*arg(leg), npv, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate), accuracy, maxIterations, guess);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsYieldValueBasisPoint1(Leg* leg, double yield, DayCounter* dayCounter, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::yieldValueBasisPoint(*arg(leg), yield, *arg(dayCounter), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsYieldValueBasisPoint(Leg* leg, InterestRate* yield, int includeSettlementDateFlows, int settlementDate, int npvDate, char **e) {
  try {return CashFlows::yieldValueBasisPoint(*arg(leg), *arg(yield), includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate));
  } catch (std::exception& er) {return handleException<double>(e, er);}}
double qlCashFlowsZSpread(Leg* leg, double npv, QlYieldTermStructure* x2, int compounding, int frequency, int includeSettlementDateFlows, int settlementDate, int npvDate, double accuracy, unsigned maxIterations, double guess, char **e) {
  try {return CashFlows::zSpread(*arg(leg), npv, *arg(x2), (Compounding)compounding, (Frequency)frequency, includeSettlementDateFlows, qlNullableDate(settlementDate), qlNullableDate(npvDate), accuracy, maxIterations, guess);
  } catch (std::exception& er) {return handleException<double>(e, er);}}
void qlQuantLibSetCouponPricer(Leg* leg, QlFloatingRateCouponPricer* x1, char **e) {try {return setCouponPricer(*arg(leg), *arg(x1));} catch (std::exception& er) {(void)handleException<int>(e, er);} }
void qlQuantLibSetCouponPricers(Leg* leg, unsigned x1Len, QlFloatingRateCouponPricer** x1, char **e) {try {return setCouponPricers(*arg(leg), qlVector(x1, x1Len));} catch (std::exception& er) {(void)handleException<int>(e, er);}}

void qlCouponAccrualStartDates(CouponLeg* o, unsigned *len, int **days, char **e) {
  int* dates = 0;
  try {*days = qlAllocateInts(o->size()); *len = o->size();
    for (unsigned i = 0; i < o->size(); ++i)
      (*days)[i] = ((*o)[i]->accrualStartDate()).serialNumber();
  } catch (std::exception& er) {qlFreeInts(dates);handleException<int*>(e, er);}}

void qlFreeDividend(QlDividend *o) {del(o);}
void qlFreeCouponLeg(CouponLeg *o) {del(o);}
Leg* qlCouponLegAsLeg(CouponLeg *o) {Leg *l = new Leg(); std::copy(o->begin(), o->end(), l->begin()); return alloc(l);}
void qlFreeFloatingCouponPricer(QlFloatingRateCouponPricer *p) {del(p);}

QlDividend* qlFixedDividend(double amount, int date, char **e) {try {return ret(new QlDividend(alloc(new FixedDividend(amount, Date(date)))));} catch (std::exception& er) {return handleException<QlDividend*>(e, er);} }
QlDividend* qlFractionalDividend1(double rate, double nominal, int date, char **e) {
  try {return ret(new QlDividend(alloc(new FractionalDividend(rate, nominal, Date(date)))));
  } catch (std::exception& er) {return handleException<QlDividend*>(e, er);}}
QlDividend* qlFractionalDividend(double rate, int date, char **e) {
  try {return ret(new QlDividend(alloc(new FractionalDividend(rate, Date(date)))));
  } catch (std::exception& er) {return handleException<QlDividend*>(e, er);}}
Leg* qlAverageBMALeg(Schedule* schedule, QlBMAIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, char **e) {
  try {return alloc(new Leg(AverageBMALeg(*arg(schedule), *arg(index)).withNotionals(std::vector<double>(notionals, notionals+notionalsLen)).withPaymentDayCounter(*arg(paymentDayCounter))
        .withPaymentAdjustment((BusinessDayConvention)paymentAdjustment).withGearings(std::vector<double>(gearings, gearings+gearingsLen)).withSpreads(std::vector<double>(spreads, spreads+spreadsLen))));
  } catch (std::exception& er) {return handleException<Leg*>(e, er);}}
Leg* qlFixedRateLeg(Schedule* schedule, unsigned NotionalsLen, double* Notionals, unsigned couponRatesLen, InterestRate** couponRates, int paymentAdjustment, DayCounter* firstPeriodDayCounter, Calendar* paymentCalendar, char **e) {
  try {return alloc(new Leg(FixedRateLeg(*arg(schedule)).withNotionals(std::vector<double>(Notionals, Notionals+NotionalsLen)).withCouponRates(qlVector(couponRates, couponRatesLen))
        .withPaymentAdjustment((BusinessDayConvention)paymentAdjustment).withFirstPeriodDayCounter(*arg(firstPeriodDayCounter)).withPaymentCalendar(*arg(paymentCalendar))));
  } catch (std::exception& er) {return handleException<Leg*>(e, er);}}
Leg* qlIborLeg(Schedule* schedule, QlIborIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned capsLen, double* caps, unsigned floorsLen, double* floors, int inArrears, int zeroPayments, char **e) {
  try {return alloc(new Leg(IborLeg(*arg(schedule), *arg(index)).withNotionals(std::vector<double>(notionals, notionals+notionalsLen)).withPaymentDayCounter(*arg(paymentDayCounter))
        .withPaymentAdjustment((BusinessDayConvention)paymentAdjustment).withFixingDays(std::vector<unsigned>(fixingDays, fixingDays+fixingDaysLen))
        .withGearings(std::vector<double>(gearings, gearings+gearingsLen)).withSpreads(std::vector<double>(spreads, spreads+spreadsLen))
        .withCaps(std::vector<double>(caps, caps+capsLen)).withFloors(std::vector<double>(floors, floors+floorsLen)).inArrears(inArrears).withZeroPayments(zeroPayments)));
  } catch (std::exception& er) {return handleException<Leg*>(e, er);}}
Leg* qlOvernightLeg(Schedule* schedule, QlOvernightIndex* overnightIndex, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, char **e) {
  try {return alloc(new Leg(OvernightLeg(*arg(schedule), *arg(overnightIndex)).withNotionals(std::vector<double>(notionals, notionals+notionalsLen)).withPaymentDayCounter(*arg(paymentDayCounter))
        .withPaymentAdjustment((BusinessDayConvention)paymentAdjustment).withGearings(std::vector<double>(gearings, gearings+gearingsLen)).withSpreads(std::vector<double>(spreads, spreads+spreadsLen))));
  } catch (std::exception& er) {return handleException<Leg*>(e, er);}}
Leg* qlRangeAccrualLeg(Schedule* schedule, QlIborIndex* index, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, unsigned lowerTriggersLen, double* lowerTriggers, unsigned upperTriggersLen, double* upperTriggers, int l, int u, int observationConvention, char **e) {
  try {return alloc(new Leg(RangeAccrualLeg(*arg(schedule), *arg(index)).withNotionals(std::vector<double>(notionals, notionals+notionalsLen)).withPaymentDayCounter(*arg(paymentDayCounter))
        .withPaymentAdjustment((BusinessDayConvention)paymentAdjustment).withFixingDays(std::vector<unsigned>(fixingDays, fixingDays+fixingDaysLen))
        .withGearings(std::vector<double>(gearings, gearings+gearingsLen)).withSpreads(std::vector<double>(spreads, spreads+spreadsLen)).
        withLowerTriggers(std::vector<double>(lowerTriggers, lowerTriggers+lowerTriggersLen)).withUpperTriggers(std::vector<double>(upperTriggers, upperTriggers+upperTriggersLen))
        .withObservationTenor(Period(l, (TimeUnit)u)).withObservationConvention((BusinessDayConvention)observationConvention)));
  } catch (std::exception& er) {return handleException<Leg*>(e, er);}}
Leg* qlCPILeg(Schedule* schedule, QlZeroInflationIndex* index, double baseCPI, int obsLagLen, int obsLagUnit, unsigned notionalsLen, double* notionals, unsigned fixedRatesLen, double* fixedRates, DayCounter* paymentDayCounter, int paymentAdjustment, Calendar* paymentCalendar, int observationInterpolation, int subtractInflationNominal, char **e) {
  try {return alloc(new Leg(CPILeg(*arg(schedule), *arg(index), baseCPI, Period(obsLagLen, (TimeUnit)obsLagUnit))
        .withNotionals(std::vector<double>(notionals, notionals+notionalsLen)).withFixedRates(std::vector<double>(fixedRates, fixedRates+fixedRatesLen))
        .withPaymentDayCounter(*arg(paymentDayCounter)).withPaymentAdjustment((BusinessDayConvention)paymentAdjustment).withPaymentCalendar(*arg(paymentCalendar))
        .withObservationInterpolation((CPI::InterpolationType)observationInterpolation).withSubtractInflationNominal(subtractInflationNominal)));
  } catch (std::exception& er) {return handleException<Leg*>(e, er);}}
Leg* qlYoYInflationLeg(Schedule* schedule, Calendar* cal, QlYoYInflationIndex* index, int obsLagLen, int obsLagUnit, int interpolation, unsigned notionalsLen, double* notionals, DayCounter* paymentDayCounter, int paymentAdjustment, unsigned fixingDaysLen, unsigned* fixingDays, unsigned gearingsLen, double* gearings, unsigned spreadsLen, double* spreads, char **e) {
  try {return alloc(new Leg(yoyInflationLeg(*arg(schedule), *arg(cal), *arg(index), Period(obsLagLen, (TimeUnit)obsLagUnit), (CPI::InterpolationType)interpolation)
        .withNotionals(std::vector<double>(notionals, notionals+notionalsLen)).withPaymentDayCounter(*arg(paymentDayCounter))
        .withPaymentAdjustment((BusinessDayConvention)paymentAdjustment).withFixingDays(std::vector<Natural>(fixingDays, fixingDays+fixingDaysLen))
        .withGearings(std::vector<double>(gearings, gearings+gearingsLen)).withSpreads(std::vector<double>(spreads, spreads+spreadsLen))));
  } catch (std::exception& er) {return handleException<Leg*>(e, er);}}
CouponLeg* qlLegToCouponLeg(Leg *o, char **e) {
  CouponLeg *cl = 0;
  try {cl = new CouponLeg(); cl->reserve(o->size());
    for (unsigned i = 0; i < o->size(); ++i) {
      shared_ptr<Coupon> c = coupon_cast((*o)[i]);
      if (c != nullptr) cl->push_back(c);
      else QL_FAIL("Cash flow #" << i << " is not a coupon");
    }
    return alloc(cl);
  } catch (std::exception& er) {return handleException(e, er, cl);}}

QlFloatingRateCouponPricer *qlBlackIborCouponPricer(QlOptionletVolatilityStructure *vol, int timingAdjustment, QlQuote *correlation, int useIndexedCoupon, char **e) {
  try {Handle<Quote> corr = correlation ? Handle<Quote>(*arg(correlation)) : Handle<Quote>(shared_ptr<Quote>(new SimpleQuote(1.0)));
    return ret(new QlFloatingRateCouponPricer(new BlackIborCouponPricer(Handle<OptionletVolatilityStructure>(*arg(vol)), (BlackIborCouponPricer::TimingAdjustment)timingAdjustment, corr, qlOptBool(useIndexedCoupon))));
  } catch (std::exception& er) {return handleException<QlFloatingRateCouponPricer *>(e, er);}}
QlFloatingRateCouponPricer* qlAnalyticHaganPricer(QlSwaptionVolatilityStructure* swaptionVol, int modelOfYieldCurve, QlQuote* meanReversion, char **e) {
  try {return ret(new QlFloatingRateCouponPricer(alloc(new AnalyticHaganPricer(Handle<SwaptionVolatilityStructure>(*arg(swaptionVol)), (GFunctionFactory::YieldCurveModel)modelOfYieldCurve, Handle<Quote>(*arg(meanReversion))))));
  } catch (std::exception& er) {return handleException<QlFloatingRateCouponPricer*>(e, er);}}
QlFloatingRateCouponPricer* qlNumericHaganPricer(QlSwaptionVolatilityStructure* swaptionVol, int modelOfYieldCurve, QlQuote* meanReversion, double lowerLimit, double upperLimit, double precision, double hardUpperLimit, char **e) {
  try {return ret(new QlFloatingRateCouponPricer(alloc(new NumericHaganPricer(Handle<SwaptionVolatilityStructure>(*arg(swaptionVol)), (GFunctionFactory::YieldCurveModel)modelOfYieldCurve, Handle<Quote>(*arg(meanReversion)), lowerLimit, upperLimit, precision, hardUpperLimit))));
  } catch (std::exception& er) {return handleException<QlFloatingRateCouponPricer*>(e, er);}}
QlFloatingRateCouponPricer* qlRangeAccrualPricerByBgm(double correlation, QlSmileSection* smilesOnExpiry, QlSmileSection* smilesOnPayment, int withSmile, int byCallSpread, char **e) {
  try {return ret(new QlFloatingRateCouponPricer(alloc(new RangeAccrualPricerByBgm(correlation, *arg(smilesOnExpiry), *arg(smilesOnPayment), withSmile, byCallSpread))));
  } catch (std::exception& er) {return handleException<QlFloatingRateCouponPricer*>(e, er);}}

void qlFreeVarianceSwap(QlVarianceSwap *o) {del(o);}
QlInstrument* qlVarianceSwapAsInstrument(QlVarianceSwap *o) {return ret(new QlInstrument(*arg(o)));}
QlVarianceSwap* qlVarianceSwap(int position, double strike, double notional, int startDate, int maturityDate, char **e) {
  try {return ret(new QlVarianceSwap(alloc(new VarianceSwap((Position::Type)position, strike, notional, Date(startDate), Date(maturityDate)))));
  } catch (std::exception& er) {return handleException<QlVarianceSwap*>(e, er);}}
double qlVarianceSwapStrike(QlVarianceSwap* o, char **e) {try {return (*arg(o))->strike();} catch (std::exception& er) {return handleException<double>(e, er);}}
int qlVarianceSwapPosition(QlVarianceSwap* o, char **e) {try {return (*arg(o))->position();} catch (std::exception& er) {return handleException<int>(e, er);}}
int qlVarianceSwapStartDate(QlVarianceSwap* o, char **e) {try {return (*arg(o))->startDate().serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}
int qlVarianceSwapMaturityDate(QlVarianceSwap* o, char **e) {try {return (*arg(o))->maturityDate().serialNumber();} catch (std::exception& er) {return handleException<int>(e, er);}}
double qlVarianceSwapNotional(QlVarianceSwap* o, char **e) {try {return (*arg(o))->notional();} catch (std::exception& er) {return handleException<double>(e, er);}}
double qlVarianceSwapVariance(QlVarianceSwap* o, char **e) {try {return (*arg(o))->variance();} catch (std::exception& er) {return handleException<double>(e, er);}}
}
/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
