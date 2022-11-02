#include <ql/models/all.hpp>
#include <ql/legacy/libormarketmodels/all.hpp>
#include <ql/experimental/shortrate/generalizedhullwhite.hpp>
#include <ql/experimental/variancegamma/variancegammamodel.hpp>

#include "qlaux.h"
#include "qlModel.h"

using namespace QuantLib;

void qlFreeGJRGARCHModel(QlGJRGARCHModel *o) {del(o);}
void qlFreeHestonModel(QlHestonModel *o) {del(o);}
void qlFreeBatesModel(QlBatesModel *o) {del(o);}
void qlFreePiecewiseTimeDependentHestonModel(QlPiecewiseTimeDependentHestonModel *o) {del(o);}
void qlFreeShortRateModel(QlShortRateModel *o) {del(o);}
void qlFreeAffineModel(QlAffineModel *o) {del(o);}
void qlFreeOneFactorAffineModel(QlOneFactorAffineModel *o) {del(o);}
QlAffineModel* qlOneFactorAffineModelAsAffineModel(QlOneFactorAffineModel *o) {return ret(new QlAffineModel(*arg(o)));}
void qlFreeLiborForwardModel(QlLiborForwardModel *o) {del(o);}
QlAffineModel* qlLiborForwardModelAsAffineModel(QlLiborForwardModel *o) {return ret(new QlAffineModel(*arg(o)));}
void qlFreeHullWhite(QlHullWhite *o) {del(o);}
QlOneFactorAffineModel* qlHullWhiteAsOneFactorAffineModel(QlHullWhite *o) {return ret(new QlOneFactorAffineModel(*arg(o)));}

void qlFreeCalibratedModel(QlCalibratedModel *o) {del(o);}

QlBatesModel* qlBatesModel(QlBatesProcess* process, char **e) {
  try {
    return ret(new QlBatesModel(alloc(new BatesModel(*arg(process)))));
  } catch (std::exception& er) {
    return handleException<QlBatesModel*>(e, er);
  }
}
QlShortRateModel* qlBlackKarasinski(QlYieldTermStructure* termStructure, double a, double sigma, char **e) {
  try {
    return ret(new QlShortRateModel(alloc(new BlackKarasinski(Handle<YieldTermStructure>(*arg(termStructure)), a, sigma))));
  } catch (std::exception& er) {
    return handleException<QlShortRateModel*>(e, er);
  }
}
QlOneFactorAffineModel* qlCoxIngersollRoss(double r0, double theta, double k, double sigma, char **e) {
  try {
    return ret(new QlOneFactorAffineModel(alloc(new CoxIngersollRoss(r0, theta, k, sigma))));
  } catch (std::exception& er) {
    return handleException<QlOneFactorAffineModel*>(e, er);
  }
}
QlOneFactorAffineModel* qlExtendedCoxIngersollRoss(QlYieldTermStructure* termStructure, double theta, double k, double sigma, double x0, char **e) {
  try {
    return ret(new QlOneFactorAffineModel(alloc(new ExtendedCoxIngersollRoss(Handle<YieldTermStructure>(*arg(termStructure)), theta, k, sigma, x0))));
  } catch (std::exception& er) {
    return handleException<QlOneFactorAffineModel*>(e, er);
  }
}
QlG2* qlG2(QlYieldTermStructure* termStructure, double a, double sigma, double b, double eta, double rho, char **e) {
  try {
    return ret(new QlG2(alloc(new G2(Handle<YieldTermStructure>(*arg(termStructure)), a, sigma, b, eta, rho))));
  } catch (std::exception& er) {
    return handleException<QlG2*>(e, er);
  }
}
QlShortRateModel* qlGeneralizedHullWhite(QlYieldTermStructure* yieldtermStructure, unsigned speedstructureLen, int* speedstructure, unsigned volstructureLen, int* volstructure, unsigned speedLen, double* speed, unsigned volLen, double* vol, char **e) {
  try {
    return ret(new QlShortRateModel(alloc(new GeneralizedHullWhite(Handle<YieldTermStructure>(*arg(yieldtermStructure)), qlDateVector(speedstructureLen, speedstructure), qlDateVector(volstructureLen, volstructure), std::vector<double>(speed, speed+speedLen), std::vector<double>(vol, vol+volLen)))));
  } catch (std::exception& er) {
    return handleException<QlShortRateModel*>(e, er);
  }
}
QlGJRGARCHModel* qlGJRGARCHModel(QlGJRGARCHProcess* process, char **e) {
  try {
    return ret(new QlGJRGARCHModel(alloc(new GJRGARCHModel(*arg(process)))));
  } catch (std::exception& er) {
    return handleException<QlGJRGARCHModel*>(e, er);
  }
}
QlHestonModel* qlHestonModel(QlHestonProcess* process, char **e) {
  try {
    return ret(new QlHestonModel(alloc(new HestonModel(*arg(process)))));
  } catch (std::exception& er) {
    return handleException<QlHestonModel*>(e, er);
  }
}
QlHullWhite* qlHullWhite(QlYieldTermStructure* termStructure, double a, double sigma, char **e) {
  try {
    return ret(new QlHullWhite(alloc(new HullWhite(Handle<YieldTermStructure>(*arg(termStructure)), a, sigma))));
  } catch (std::exception& er) {
    return handleException<QlHullWhite*>(e, er);
  }
}
QlCalibratedModel* qlVarianceGammaModel(QlVarianceGammaProcess* process, char **e) {
  try {
    return ret(new QlCalibratedModel(alloc(new VarianceGammaModel(*arg(process)))));
  } catch (std::exception& er) {
    return handleException<QlCalibratedModel*>(e, er);
  }
}
QlOneFactorAffineModel* qlVasicek(double r0, double a, double b, double sigma, double lambda, char **e) {
  try {
    return ret(new QlOneFactorAffineModel(alloc(new Vasicek(r0, a, b, sigma, lambda))));
  } catch (std::exception& er) {
    return handleException<QlOneFactorAffineModel*>(e, er);
  }
}

void qlFreeG2(QlG2 *o) {del(o);}
QlAffineModel* qlG2AsAffineModel(QlG2 *o) {return ret(new QlAffineModel(*arg(o)));}
QlShortRateModel* qlG2AsShortRateModel(QlG2 *o) {return ret(new QlShortRateModel(*arg(o)));}

void qlFreeBatesDetJumpModel(QlBatesDetJumpModel *o) {del(o);}
QlBatesModel* qlBatesDetJumpModelAsBatesModel(QlBatesDetJumpModel *o) {return ret(new QlBatesModel(*arg(o)));}
void qlFreeBatesDoubleExpDetJumpModel(QlBatesDoubleExpDetJumpModel *o) {del(o);}
QlBatesDoubleExpModel* qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel(QlBatesDoubleExpDetJumpModel *o) {return ret(new QlBatesDoubleExpModel(*arg(o)));}
void qlFreeBatesDoubleExpModel(QlBatesDoubleExpModel *o) {del(o);}
QlHestonModel* qlBatesDoubleExpModelAsHestonModel(QlBatesDoubleExpModel *o) {return ret(new QlHestonModel(*arg(o)));}

void qlFreeLmCorrelationModel(QlLmCorrelationModel *o) {del(o);}
void qlFreeLmVolatilityModel(QlLmVolatilityModel *o) {del(o);}
QlLmCorrelationModel* qlLmConstWrapperCorrelationModel(QlLmCorrelationModel* corrModel, char **e) {
  try {
    return ret(new QlLmCorrelationModel(alloc(new LmConstWrapperCorrelationModel(*arg(corrModel)))));
  } catch (std::exception& er) {
    return handleException<QlLmCorrelationModel*>(e, er);
  }
}
QlLmVolatilityModel* qlLmConstWrapperVolatilityModel(QlLmVolatilityModel* volaModel, char **e) {
  try {
    return ret(new QlLmVolatilityModel(alloc(new LmConstWrapperVolatilityModel(*arg(volaModel)))));
  } catch (std::exception& er) {
    return handleException<QlLmVolatilityModel*>(e, er);
  }
}
QlLmCorrelationModel* qlLmExponentialCorrelationModel(unsigned size, double rho, char **e) {
  try {
    return ret(new QlLmCorrelationModel(alloc(new LmExponentialCorrelationModel(size, rho))));
  } catch (std::exception& er) {
    return handleException<QlLmCorrelationModel*>(e, er);
  }
}
QlLmVolatilityModel* qlLmFixedVolatilityModel(unsigned volatilitiesLen, double* volatilities, unsigned startTimesLen, double * startTimes, char **e) {
  try {
    return ret(new QlLmVolatilityModel(alloc(new LmFixedVolatilityModel(Array(volatilities, volatilities+volatilitiesLen), std::vector<double>(startTimes, startTimes+startTimesLen)))));
  } catch (std::exception& er) {
    return handleException<QlLmVolatilityModel*>(e, er);
  }
}
QlLmCorrelationModel* qlLmLinearExponentialCorrelationModel(unsigned size, double rho, double beta, unsigned factors, char **e) {
  try {
    return ret(new QlLmCorrelationModel(alloc(new LmLinearExponentialCorrelationModel(size, rho, beta, factors))));
  } catch (std::exception& er) {
    return handleException<QlLmCorrelationModel*>(e, er);
  }
}
QlLmVolatilityModel* qlLmLinearExponentialVolatilityModel(unsigned fixingTimesLen, double * fixingTimes, double a, double b, double c, double d, char **e) {
  try {
    return ret(new QlLmVolatilityModel(alloc(new LmLinearExponentialVolatilityModel(std::vector<double>(fixingTimes, fixingTimes+fixingTimesLen), a, b, c, d))));
  } catch (std::exception& er) {
    return handleException<QlLmVolatilityModel*>(e, er);
  }
}
QlLiborForwardModel* qlLiborForwardModel(QlLiborForwardModelProcess* process, QlLmVolatilityModel* volaModel, QlLmCorrelationModel* corrModel, char **e) {
  try {
    return ret(new QlLiborForwardModel(alloc(new LiborForwardModel(*arg(process), *arg(volaModel), *arg(corrModel)))));
  } catch (std::exception& er) {
    return handleException<QlLiborForwardModel*>(e, er);
  }
}
QlCalibratedModel* qlGJRGARCHModelAsCalibratedModel(QlGJRGARCHModel *o) {return ret(new QlCalibratedModel(*arg(o)));}
QlCalibratedModel* qlHestonModelAsCalibratedModel(QlHestonModel *o) {return ret(new QlCalibratedModel(*arg(o)));}
QlHestonModel* qlBatesModelAsHestonModel(QlBatesModel *o) {return ret(new QlHestonModel(*arg(o)));}
QlCalibratedModel* qlLiborForwardModelAsCalibratedModel(QlLiborForwardModel *o) {return ret(new QlCalibratedModel(*arg(o)));}
QlCalibratedModel* qlPiecewiseTimeDependentHestonModelAsCalibratedModel(QlPiecewiseTimeDependentHestonModel *o) {return ret(new QlCalibratedModel(*arg(o)));}
QlCalibratedModel* qlShortRateModelAsCalibratedModel(QlShortRateModel *o) {return ret(new QlCalibratedModel(*arg(o)));}
QlShortRateModel* qlOneFactorAffineModelAsShortRateModel(QlOneFactorAffineModel *o) {return ret(new QlShortRateModel(*arg(o)));}

void qlFreeCalibrationHelper(QlCalibrationHelper *o) {del(o);}
void qlFreeBlackCalibrationHelper(QlBlackCalibrationHelper *o) {del(o);}

void qlCalibratedModelCalibrate(QlCalibratedModel* o, unsigned x1Len, QlCalibrationHelper** x1, unsigned wLen, double *weights, OptimizationMethod* method, EndCriteria* endCriteria, Constraint* constraint, char **e) {
  try {
    Constraint c(constraint ? *arg(constraint) : Constraint());
    (*arg(o))->calibrate(qlBuildVector(x1, x1Len), *arg(method), *arg(endCriteria), c, std::vector<double>(weights, weights+wLen));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}
void qlBlackCalibrationHelperSetPricingEngine(QlBlackCalibrationHelper* o, QlPricingEngine* engine, char **e) {
  try {
    (*arg(o))->setPricingEngine(*arg(engine));
  } catch (std::exception& er) {
    (void)handleException<int>(e, er);
  }
}
QlBlackCalibrationHelper* qlCapHelper(int l, int u, QlQuote* volatility, QlIborIndex* index, int fixedLegFrequency, DayCounter* fixedLegDayCounter, int includeFirstSwaplet, QlYieldTermStructure* termStructure, int errorType, char **e) {
  try {
    return ret(new QlBlackCalibrationHelper(alloc(new CapHelper(Period(l, (TimeUnit)u), Handle<Quote>(*arg(volatility)), *arg(index), (Frequency)fixedLegFrequency, *arg(fixedLegDayCounter), includeFirstSwaplet, Handle<YieldTermStructure>(*arg(termStructure)), (BlackCalibrationHelper::CalibrationErrorType)errorType))));
  } catch (std::exception& er) {
    return handleException<QlBlackCalibrationHelper*>(e, er);
  }
}
QlBlackCalibrationHelper* qlHestonModelHelper(int l, int u, Calendar* calendar, double s0, double strikePrice, QlQuote* volatility, QlYieldTermStructure* riskFreeRate, QlYieldTermStructure* dividendYield, int errorType, char **e) {
  try {
    return ret(new QlBlackCalibrationHelper(alloc(new HestonModelHelper(Period(l, (TimeUnit)u), *arg(calendar), s0, strikePrice, Handle<Quote>(*arg(volatility)), Handle<YieldTermStructure>(*arg(riskFreeRate)), Handle<YieldTermStructure>(*arg(dividendYield)), (BlackCalibrationHelper::CalibrationErrorType)errorType))));
  } catch (std::exception& er) {
    return handleException<QlBlackCalibrationHelper*>(e, er);
  }
}
QlBlackCalibrationHelper* qlSwaptionHelper(int l, int u, int ll, int lu, QlQuote* volatility, QlIborIndex* index, int fl, int fu, DayCounter* fixedLegDayCounter, DayCounter* floatingLegDayCounter, QlYieldTermStructure* termStructure, int errorType, char **e) {
  try {
    return ret(new QlBlackCalibrationHelper(alloc(new SwaptionHelper(Period(l, (TimeUnit)u), Period(ll, (TimeUnit)lu), Handle<Quote>(*arg(volatility)), *arg(index), Period(fl, (TimeUnit)fu), *arg(fixedLegDayCounter), *arg(floatingLegDayCounter), Handle<YieldTermStructure>(*arg(termStructure)), (BlackCalibrationHelper::CalibrationErrorType)errorType))));
  } catch (std::exception& er) {
    return handleException<QlBlackCalibrationHelper*>(e, er);
  }
}

void qlBlackCalibrationHelperTimes(QlBlackCalibrationHelper* o, unsigned *len, double **ts, char **e) {
  try {
    std::list<double> times;
    (*arg(o))->addTimesTo(times);
    *len = times.size();
    *ts = qlAllocateDoubles(*len);
    std::copy(times.begin(), times.end(), *ts);
  } catch (std::exception& er) {
    handleException<double*>(e, er);
  }
}

void qlCalibratedModelParams(QlCalibratedModel* o, unsigned *len, double** ps, char **e) {
  try {
    Array params = (*arg(o))->params();
    *len = params.size();
    *ps = qlAllocateDoubles(*len);
    std::copy(params.begin(), params.end(), *ps);
  } catch (std::exception& er) {
    handleException<double*>(e, er);
  }
}
double qlBlackCalibrationHelperBlackPrice(QlBlackCalibrationHelper* o, double volatility, char **e) {
  try {
    return (*arg(o))->blackPrice(volatility);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalibrationHelperCalibrationError(QlBlackCalibrationHelper* o, char **e) {
  try {
    return (*arg(o))->calibrationError();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalibrationHelperImpliedVolatility(QlBlackCalibrationHelper* o, double targetValue, double accuracy, unsigned maxEvaluations, double minVol, double maxVol, char **e) {
  try {
    return (*arg(o))->impliedVolatility(targetValue, accuracy, maxEvaluations, minVol, maxVol);
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalibrationHelperMarketValue(QlBlackCalibrationHelper* o, char **e) {
  try {
    return (*arg(o))->marketValue();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}
double qlBlackCalibrationHelperModelValue(QlBlackCalibrationHelper* o, char **e) {
  try {
    return (*arg(o))->modelValue();
  } catch (std::exception& er) {
    return handleException<double>(e, er);
  }
}

QlCalibrationHelper* qlBlackCalibrationHelperAsCalibrationHelper(QlBlackCalibrationHelper *o) {return ret(new QlCalibrationHelper(*arg(o)));}

/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
