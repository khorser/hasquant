module QuantLib.Process
  (
    ProcessDiscretization(..)
  , ExtendedBlackScholesMertonProcessDiscretization(..)
  , HestonProcessDiscretization(..)
  , GJRGARCHProcessDiscretization(..)
  , HybridHestonHullWhiteProcessDiscretization(..)

  , GeneralizedBlackScholesProcess
  , StochasticProcess1D
  , GenStochasticProcess1D
  , StochasticProcess
  , GenStochasticProcess
  , BlackProcess
  , ExtOUWithJumpsProcess
  , ExtendedOrnsteinUhlenbeckProcess
  , GJRGARCHProcess
  , HestonProcess
  , GenHestonProcess
  , BatesProcess
  , HybridHestonHullWhiteProcess
  , KlugeExtOUProcess
  , LiborForwardModelProcess
  , StochasticProcessArray
  , VarianceGammaProcess
  , Merton76Process
  , HullWhiteProcess
  , HullWhiteForwardProcess

  , asStochasticProcess
  , asStochasticProcess1D
  , asGeneralizedBlackScholesProcess
  , asHestonProcess

  , blackProcess
  , blackScholesMertonProcess
  , blackScholesProcess
  , extendedBlackScholesMertonProcess
  , garmanKohlagenProcess
  , generalizedBlackScholesProcess
  , squareRootProcess
  , vegaStressedBlackScholesProcess

  , batesProcess
  , extOUWithJumpsProcess
  , g2ForwardProcess
  , g2Process
  , gemanRoncoroniProcess
  , geometricBrownianMotionProcess
  , gjrGARCHProcess
  , hestonProcess
  , hullWhiteForwardProcess
  , hullWhiteProcess
  , hybridHestonHullWhiteProcess
  , klugeExtOUProcess
  , liborForwardModelProcess
  , merton76Process
  , ornsteinUhlenbeckProcess
  , varianceGammaProcess
  , stochasticProcessArray

  , blackScholesTheta
  ) where
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

import QuantLib.Internal
import QuantLib.Internal.Type

{#enum ProcessDiscretization{} deriving(Show,Eq)#}
{#enum ExtendedBlackScholesMertonProcessDiscretization{} deriving(Show, Eq)#}
{#enum HestonProcessDiscretization{} deriving(Show, Eq)#}
{#enum GJRGARCHProcessDiscretization{} deriving(Show, Eq)#}
{#enum HybridHestonHullWhiteProcessDiscretization{} deriving(Show, Eq)#}

{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlBlackVolTermStructure as BlackVolTermStructure foreign -> CBlackVolTermStructure' nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}

{#pointer *QlGeneralizedBlackScholesProcess as GeneralizedBlackScholesProcess foreign -> CGeneralizedBlackScholesProcess' nocode#}
{#pointer *QlStochasticProcess1D as StochasticProcess1D foreign -> CStochasticProcess1D' nocode#}
{#pointer *QlStochasticProcess as StochasticProcess foreign -> CStochasticProcess' nocode#}
{#pointer *QlBlackProcess as BlackProcess foreign -> CBlackProcess' nocode#}
{#pointer *QlExtOUWithJumpsProcess as ExtOUWithJumpsProcess foreign -> CExtOUWithJumpsProcess' nocode#}
{#pointer *QlExtendedOrnsteinUhlenbeckProcess as ExtendedOrnsteinUhlenbeckProcess foreign -> CExtendedOrnsteinUhlenbeckProcess' nocode#}
{#pointer *QlGJRGARCHProcess as GJRGARCHProcess foreign -> CGJRGARCHProcess' nocode#}
{#pointer *QlHestonProcess as HestonProcess foreign -> CHestonProcess' nocode#}
{#pointer *QlBatesProcess as BatesProcess foreign -> CBatesProcess' nocode#}
{#pointer *QlHybridHestonHullWhiteProcess as HybridHestonHullWhiteProcess foreign -> CHybridHestonHullWhiteProcess' nocode#}
{#pointer *QlKlugeExtOUProcess as KlugeExtOUProcess foreign -> CKlugeExtOUProcess' nocode#}
{#pointer *QlLiborForwardModelProcess as LiborForwardModelProcess foreign -> CLiborForwardModelProcess' nocode#}
{#pointer *QlStochasticProcessArray as StochasticProcessArray foreign -> CStochasticProcessArray' nocode#}
{#pointer *QlVarianceGammaProcess as VarianceGammaProcess foreign -> CVarianceGammaProcess' nocode#}
{#pointer *QlMerton76Process as Merton76Process foreign -> CMerton76Process' nocode#}
{#pointer *QlHullWhiteProcess as HullWhiteProcess foreign -> CHullWhiteProcess' nocode#}
{#pointer *QlHullWhiteForwardProcess as HullWhiteForwardProcess foreign -> CHullWhiteForwardProcess' nocode#}

{#fun qlBlackProcess as blackProcess{withQuote*`GenQuote a' -- ^x0
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^riskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure c' -- ^blackVolTS
  ,`ProcessDiscretization'
  ,`Bool' -- ^forceDiscretization
  ,preErrorCheck-`String'errorCheck*-}->`BlackProcess'peekBlackProcess*#}
{#fun qlBlackScholesMertonProcess as blackScholesMertonProcess{withQuote*`GenQuote a' -- ^x0
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^dividendTS
  ,withYieldTermStructure*`GenYieldTermStructure c' -- ^riskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure d' -- ^blackVolTS
  ,`ProcessDiscretization'
  ,`Bool' -- ^forceDiscretization
  ,preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}
{#fun qlBlackScholesProcess as blackScholesProcess{withQuote*`GenQuote a' -- ^x0
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^riskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure c' -- ^blackVolTS
  ,`ProcessDiscretization'
  ,`Bool' -- ^forceDiscretization
  ,preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}
{#fun qlExtendedBlackScholesMertonProcess as extendedBlackScholesMertonProcess{withQuote*`GenQuote a' -- ^x0
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^dividendTS
  ,withYieldTermStructure*`GenYieldTermStructure c' -- ^rsikFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure d' -- ^blackVolTS
  ,`ProcessDiscretization',`ExtendedBlackScholesMertonProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}
{#fun qlGarmanKohlagenProcess as garmanKohlagenProcess{withQuote*`GenQuote a' -- x0
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^foreignRiskFreeTS
  ,withYieldTermStructure*`GenYieldTermStructure c' -- ^domesticRiskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure d' -- ^blackVolTS
  ,`ProcessDiscretization'
  ,`Bool' -- ^forceDiscretization
  ,preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}
{#fun qlGeneralizedBlackScholesProcess as generalizedBlackScholesProcess{withQuote*`GenQuote a' -- ^x0
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^dividendTS
  ,withYieldTermStructure*`GenYieldTermStructure c' -- ^riskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure d' -- ^blackVolTS
  ,`ProcessDiscretization'
  ,`Bool' -- ^forceDiscretization
  ,preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}
{#fun qlSquareRootProcess as squareRootProcess{`Double' -- ^b
  ,`Double' -- ^a
  ,`Double' -- ^sigma
  ,`Double' -- ^x0
  ,`ProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`StochasticProcess1D'peekStochasticProcess1D*#}
{#fun qlVegaStressedBlackScholesProcess as vegaStressedBlackScholesProcess{withQuote*`GenQuote a' -- x0
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^dividendTS
  ,withYieldTermStructure*`GenYieldTermStructure c' -- ^riskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure d' -- ^blackVolTS
  ,`Double' -- ^lowerTimeBorderForStressTest
  ,`Double' -- ^upperTimeBorderForStressTest
  ,`Double' -- ^lowerAssetBorderForStressTest
  ,`Double' -- ^upperAssetBorderForStressTest
  ,`Double' -- ^stressLevel
  ,`ProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}
{#fun qlBatesProcess as batesProcess{withYieldTermStructure*`GenYieldTermStructure b' -- ^riskFreeTS
  ,withYieldTermStructure*`GenYieldTermStructure c' -- ^dividendYield
  ,withQuote*`GenQuote a' -- ^s0
  ,`Double' -- ^v0
  ,`Double' -- ^kappa
  ,`Double' -- ^theta
  ,`Double' -- ^sigma
  ,`Double' -- ^rho
  ,`Double' -- ^lambda
  ,`Double' -- ^nu
  ,`Double' -- ^delta
  ,`HestonProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`BatesProcess'peekBatesProcess*#}
{#fun qlExtOUWithJumpsProcess as extOUWithJumpsProcess{withGenStochasticProcess1D*`ExtendedOrnsteinUhlenbeckProcess',`Double' -- ^Y0
  ,`Double' -- ^beta
  ,`Double' -- ^jumpIntensity
  ,`Double' -- ^eta
  ,preErrorCheck-`String'errorCheck*-}->`ExtOUWithJumpsProcess'peekExtOUWithJumpsProcess*#}
{#fun qlG2ForwardProcess as g2ForwardProcess{`Double' -- ^a
  ,`Double' -- ^sigma
  ,`Double' -- ^b
  ,`Double' -- ^eta
  ,`Double' -- ^rho
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^termStructure
  ,preErrorCheck-`String'errorCheck*-}->`StochasticProcess'peekStochasticProcess*#}
{#fun qlG2Process as g2Process{`Double' -- ^a
  ,`Double' -- ^sigma
  ,`Double' -- ^b
  ,`Double' -- ^eta
  ,`Double' -- ^rho
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^termStructure
  ,preErrorCheck-`String'errorCheck*-}->`StochasticProcess'peekStochasticProcess*#}
{#fun qlGemanRoncoroniProcess as gemanRoncoroniProcess{`Double'-- ^x0
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^gamma
  ,`Double' -- ^delta
  ,`Double' -- ^eps
  ,`Double' -- ^zeta
  ,`Double' -- ^d
  ,`Double' -- ^d
  ,`Double' -- ^tau
  ,`Double' -- ^sig2
  ,`Double' -- ^a
  ,`Double' -- ^b
  ,`Double' -- ^theta1
  ,`Double' -- ^theta2
  ,`Double' -- ^theta3
  ,`Double' -- ^psi
  ,preErrorCheck-`String'errorCheck*-}->`StochasticProcess1D'peekStochasticProcess1D*#}
{#fun qlGeometricBrownianMotionProcess as geometricBrownianMotionProcess{`Double' -- ^initialValue
  ,`Double' -- ^mue
  ,`Double' -- ^sigma
  ,preErrorCheck-`String'errorCheck*-}->`StochasticProcess1D'peekStochasticProcess1D*#}
{#fun qlGJRGARCHProcess as gjrGARCHProcess{withYieldTermStructure*`GenYieldTermStructure b' -- ^riskFreeRate
  ,withYieldTermStructure*`GenYieldTermStructure c' -- ^dividendYield
  ,withQuote*`GenQuote a' -- ^s0
  ,`Double' -- ^v0
  ,`Double' -- &omega
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^gamma
  ,`Double' -- ^lambda
  ,`Double' -- ^daysPerYear
  ,`GJRGARCHProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`GJRGARCHProcess'peekGJRGARCHProcess*#}
{#fun qlHestonProcess as hestonProcess{withYieldTermStructure*`GenYieldTermStructure b' -- ^riskFreeRate
  ,withYieldTermStructure*`GenYieldTermStructure c' -- dividendYield
  ,withQuote*`GenQuote a' -- ^s0
  ,`Double' -- ^v0
  ,`Double' -- ^kappa
  ,`Double' -- ^theta
  ,`Double' -- ^sigma
  ,`Double' -- ^rho
  ,`HestonProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`HestonProcess'peekHestonProcess*#}
{#fun qlHullWhiteForwardProcess as hullWhiteForwardProcess{withYieldTermStructure*`GenYieldTermStructure a' -- ^h
  ,`Double' -- ^a
  ,`Double' -- ^sigma
  ,preErrorCheck-`String'errorCheck*-}->`HullWhiteForwardProcess'peekHullWhiteForwardProcess*#}
{#fun qlHullWhiteProcess as hullWhiteProcess{withYieldTermStructure*`GenYieldTermStructure a' -- ^h
  ,`Double' -- ^a
  ,`Double' -- ^sigma
  ,preErrorCheck-`String'errorCheck*-}->`HullWhiteProcess'peekHullWhiteProcess*#}
{#fun qlHybridHestonHullWhiteProcess as hybridHestonHullWhiteProcess{withHestonProcess*`GenHestonProcess a',withGenStochasticProcess1D*`HullWhiteForwardProcess'
  ,`Double' -- ^corrEquityShortRate
  ,`HybridHestonHullWhiteProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`HybridHestonHullWhiteProcess'peekHybridHestonHullWhiteProcess*#}
{#fun qlKlugeExtOUProcess as klugeExtOUProcess{`Double' -- ^rho
  ,withGenStochasticProcess*`ExtOUWithJumpsProcess',withGenStochasticProcess1D*`ExtendedOrnsteinUhlenbeckProcess',preErrorCheck-`String'errorCheck*-}->`KlugeExtOUProcess'peekKlugeExtOUProcess*#}
{#fun qlLiborForwardModelProcess as liborForwardModelProcess{fromIntegral`Word' -- ^size
  ,withIborIndex*`GenIborIndex a',preErrorCheck-`String'errorCheck*-}->`LiborForwardModelProcess'peekLiborForwardModelProcess*#}
{#fun qlMerton76Process as merton76Process{withQuote*`GenQuote a' -- ^stateVariable
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^dividendTS
  ,withYieldTermStructure*`GenYieldTermStructure c' -- ^riskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure d' -- ^blackVolTS
  ,withQuote*`GenQuote e' -- ^jumpInt
  ,withQuote*`GenQuote f' -- ^logJMean
  ,withQuote*`GenQuote g' -- ^logJVol
  ,`ProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`Merton76Process'peekMerton76Process*#}
{#fun qlOrnsteinUhlenbeckProcess as ornsteinUhlenbeckProcess{`Double' -- ^speed
  ,`Double' -- ^vol
  ,`Double' -- ^x0
  ,`Double' -- ^vol
  ,preErrorCheck-`String'errorCheck*-}->`StochasticProcess1D'peekStochasticProcess1D*#}
{#fun qlVarianceGammaProcess as varianceGammaProcess{withQuote*`GenQuote a' -- ^s0
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^dividendYield
  ,withYieldTermStructure*`GenYieldTermStructure c' -- ^riskFreeRate
  ,`Double' -- ^sigma
  ,`Double' -- ^nu
  ,`Double' -- ^theta
  ,preErrorCheck-`String'errorCheck*-}->`VarianceGammaProcess'peekVarianceGammaProcess*#}
stochasticProcessArray :: [GenStochasticProcess1D p] -> Matrix Double -- ^correlation
  -> IO StochasticProcessArray
stochasticProcessArray a (Matrix mr mc md) = qlStochasticProcessArray a mr mc md
{#fun qlStochasticProcessArray{withStochasticProcess1DArray*`[GenStochasticProcess1D p]'&,fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]',preErrorCheck-`String'errorCheck*-}->`StochasticProcessArray'peekStochasticProcessArray*#}

-- |default theta calculation for Black-Scholes options
{#fun qlQuantLibBlackScholesTheta as blackScholesTheta{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double' -- ^value
  ,`Double' -- ^delta
  ,`Double' -- ^gamma
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
