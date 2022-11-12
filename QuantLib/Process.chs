{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts, TypeOperators #-}
module QuantLib.Process
  (
    ProcessDiscretization(..)
  , ExtendedBlackScholesMertonProcessDiscretization(..)
  , HestonProcessDiscretization(..)
  , GJRGARCHProcessDiscretization(..)
  , HybridHestonHullWhiteProcessDiscretization(..)

  , GeneralizedBlackScholesProcess
  , StochasticProcess1D
  , StochasticProcess
  , BlackProcess
  , ExtOUWithJumpsProcess
  , ExtendedOrnsteinUhlenbeckProcess
  , GJRGARCHProcess
  , HestonProcess
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
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

import QuantLib.Type
import QuantLib.Internal
import QuantLib.Internal.Type

{#pointer *QlQuote as Quote foreign -> CQuote nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure nocode#}
{#pointer *QlBlackVolTermStructure as BlackVolTermStructure foreign -> CBlackVolTermStructure nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}

{#enum ProcessDiscretization{} deriving(Show,Eq)#}

{#enum ExtendedBlackScholesMertonProcessDiscretization{} deriving(Show, Eq)#}

{#enum HestonProcessDiscretization{} deriving(Show, Eq)#}

{#enum GJRGARCHProcessDiscretization{} deriving(Show, Eq)#}

{#enum HybridHestonHullWhiteProcessDiscretization{} deriving(Show, Eq)#}

{#pointer *QlGeneralizedBlackScholesProcess as GeneralizedBlackScholesProcess foreign -> CGeneralizedBlackScholesProcess nocode#}

{#pointer *QlStochasticProcess1D as StochasticProcess1D foreign -> CStochasticProcess1D nocode#}

{#pointer *QlStochasticProcess as StochasticProcess foreign -> CStochasticProcess nocode#}

{#pointer *QlBlackProcess as BlackProcess foreign -> CBlackProcess nocode#}

{#pointer *QlExtOUWithJumpsProcess as ExtOUWithJumpsProcess foreign -> CExtOUWithJumpsProcess nocode#}

{#pointer *QlExtendedOrnsteinUhlenbeckProcess as ExtendedOrnsteinUhlenbeckProcess foreign -> CExtendedOrnsteinUhlenbeckProcess nocode#}

{#pointer *QlGJRGARCHProcess as GJRGARCHProcess foreign -> CGJRGARCHProcess nocode#}

{#pointer *QlHestonProcess as HestonProcess foreign -> CHestonProcess nocode#}

{#pointer *QlBatesProcess as BatesProcess foreign -> CBatesProcess nocode#}

{#pointer *QlHybridHestonHullWhiteProcess as HybridHestonHullWhiteProcess foreign -> CHybridHestonHullWhiteProcess nocode#}

{#pointer *QlKlugeExtOUProcess as KlugeExtOUProcess foreign -> CKlugeExtOUProcess nocode#}

{#pointer *QlLiborForwardModelProcess as LiborForwardModelProcess foreign -> CLiborForwardModelProcess nocode#}

{#pointer *QlStochasticProcessArray as StochasticProcessArray foreign -> CStochasticProcessArray nocode#}

{#pointer *QlVarianceGammaProcess as VarianceGammaProcess foreign -> CVarianceGammaProcess nocode#}

{#pointer *QlMerton76Process as Merton76Process foreign -> CMerton76Process nocode#}

{#pointer *QlHullWhiteProcess as HullWhiteProcess foreign -> CHullWhiteProcess nocode#}

{#pointer *QlHullWhiteForwardProcess as HullWhiteForwardProcess foreign -> CHullWhiteForwardProcess nocode#}

asStochasticProcess :: (a`Derives` StochasticProcess) => a -> IO StochasticProcess
asStochasticProcess = cast

asStochasticProcess1D :: (a`Derives` StochasticProcess1D) => a -> IO StochasticProcess1D
asStochasticProcess1D = cast

instance BlackProcess`Derives` GeneralizedBlackScholesProcess where cast = qlBlackProcessAsGeneralizedBlackScholesProcess

asGeneralizedBlackScholesProcess :: (a`Derives` GeneralizedBlackScholesProcess) => a -> IO GeneralizedBlackScholesProcess
asGeneralizedBlackScholesProcess = cast

{#fun qlBlackProcessAsGeneralizedBlackScholesProcess{withBlackProcess*`BlackProcess'}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}
{#fun qlStochasticProcess1DAsStochasticProcess{withStochasticProcess1D*`StochasticProcess1D'}->`StochasticProcess'peekStochasticProcess*#}
instance StochasticProcess1D`Derives` StochasticProcess where cast = qlStochasticProcess1DAsStochasticProcess
{#fun qlExtOUWithJumpsProcessAsStochasticProcess{withExtOUWithJumpsProcess*`ExtOUWithJumpsProcess'}->`StochasticProcess'peekStochasticProcess*#}
instance ExtOUWithJumpsProcess`Derives` StochasticProcess where cast = qlExtOUWithJumpsProcessAsStochasticProcess
{#fun qlGJRGARCHProcessAsStochasticProcess{withGJRGARCHProcess*`GJRGARCHProcess'}->`StochasticProcess'peekStochasticProcess*#}
instance GJRGARCHProcess`Derives` StochasticProcess where cast = qlGJRGARCHProcessAsStochasticProcess
{#fun qlHestonProcessAsStochasticProcess{withHestonProcess*`HestonProcess'}->`StochasticProcess'peekStochasticProcess*#}
instance HestonProcess`Derives` StochasticProcess where cast = qlHestonProcessAsStochasticProcess

instance BatesProcess`Derives` HestonProcess where cast = qlBatesProcessAsHestonProcess
asHestonProcess :: (a`Derives` HestonProcess) => a -> IO HestonProcess
asHestonProcess = cast

{#fun qlBatesProcessAsHestonProcess{withBatesProcess*`BatesProcess'}->`HestonProcess'peekHestonProcess*#}
{#fun qlHybridHestonHullWhiteProcessAsStochasticProcess{withHybridHestonHullWhiteProcess*`HybridHestonHullWhiteProcess'}->`StochasticProcess'peekStochasticProcess*#}
instance HybridHestonHullWhiteProcess`Derives` StochasticProcess where cast = qlHybridHestonHullWhiteProcessAsStochasticProcess
{#fun qlKlugeExtOUProcessAsStochasticProcess{withKlugeExtOUProcess*`KlugeExtOUProcess'}->`StochasticProcess'peekStochasticProcess*#}
instance KlugeExtOUProcess`Derives` StochasticProcess where cast = qlKlugeExtOUProcessAsStochasticProcess
{#fun qlLiborForwardModelProcessAsStochasticProcess{withLiborForwardModelProcess*`LiborForwardModelProcess'}->`StochasticProcess'peekStochasticProcess*#}
instance LiborForwardModelProcess`Derives` StochasticProcess where cast = qlLiborForwardModelProcessAsStochasticProcess
{#fun qlStochasticProcessArrayAsStochasticProcess{withStochasticProcessArray*`StochasticProcessArray'}->`StochasticProcess'peekStochasticProcess*#}
instance StochasticProcessArray`Derives` StochasticProcess where cast = qlStochasticProcessArrayAsStochasticProcess

{#fun qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D{withExtendedOrnsteinUhlenbeckProcess*`ExtendedOrnsteinUhlenbeckProcess'}->`StochasticProcess1D'peekStochasticProcess1D*#}
instance ExtendedOrnsteinUhlenbeckProcess`Derives` StochasticProcess1D where cast = qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D
{#fun qlGeneralizedBlackScholesProcessAsStochasticProcess1D{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess'}->`StochasticProcess1D'peekStochasticProcess1D*#}
instance GeneralizedBlackScholesProcess`Derives` StochasticProcess1D where cast = qlGeneralizedBlackScholesProcessAsStochasticProcess1D
{#fun qlHullWhiteForwardProcessAsStochasticProcess1D{withHullWhiteForwardProcess*`HullWhiteForwardProcess'}->`StochasticProcess1D'peekStochasticProcess1D*#}
instance HullWhiteForwardProcess`Derives` StochasticProcess1D where cast = qlHullWhiteForwardProcessAsStochasticProcess1D
{#fun qlHullWhiteProcessAsStochasticProcess1D{withHullWhiteProcess*`HullWhiteProcess'}->`StochasticProcess1D'peekStochasticProcess1D*#}
instance HullWhiteProcess`Derives` StochasticProcess1D where cast = qlHullWhiteProcessAsStochasticProcess1D
{#fun qlMerton76ProcessAsStochasticProcess1D{withMerton76Process*`Merton76Process'}->`StochasticProcess1D'peekStochasticProcess1D*#}
instance Merton76Process`Derives` StochasticProcess1D where cast = qlMerton76ProcessAsStochasticProcess1D
{#fun qlVarianceGammaProcessAsStochasticProcess1D{withVarianceGammaProcess*`VarianceGammaProcess'}->`StochasticProcess1D'peekStochasticProcess1D*#}
instance VarianceGammaProcess`Derives` StochasticProcess1D where cast = qlVarianceGammaProcessAsStochasticProcess1D

{#fun qlBlackProcess as blackProcess{withQuote*`GenQuote a',withYieldTermStructure*`YieldTermStructure',withBlackVolTermStructure*`BlackVolTermStructure',`ProcessDiscretization', preErrorCheck-`String'errorCheck*-}->`BlackProcess'peekBlackProcess*#}

{#fun qlBlackScholesMertonProcess as blackScholesMertonProcess{withQuote*`GenQuote a',withYieldTermStructure*`YieldTermStructure',withYieldTermStructure*`YieldTermStructure',withBlackVolTermStructure*`BlackVolTermStructure',`ProcessDiscretization', preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}

{#fun qlBlackScholesProcess as blackScholesProcess{withQuote*`GenQuote a',withYieldTermStructure*`YieldTermStructure',withBlackVolTermStructure*`BlackVolTermStructure',`ProcessDiscretization', preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}

{#fun qlExtendedBlackScholesMertonProcess as extendedBlackScholesMertonProcess{withQuote*`GenQuote a',withYieldTermStructure*`YieldTermStructure',withYieldTermStructure*`YieldTermStructure',withBlackVolTermStructure*`BlackVolTermStructure',`ProcessDiscretization',`ExtendedBlackScholesMertonProcessDiscretization', preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}

{#fun qlGarmanKohlagenProcess as garmanKohlagenProcess{withQuote*`GenQuote a',withYieldTermStructure*`YieldTermStructure',withYieldTermStructure*`YieldTermStructure',withBlackVolTermStructure*`BlackVolTermStructure',`ProcessDiscretization', preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}

{#fun qlGeneralizedBlackScholesProcess as generalizedBlackScholesProcess{withQuote*`GenQuote a',withYieldTermStructure*`YieldTermStructure',withYieldTermStructure*`YieldTermStructure',withBlackVolTermStructure*`BlackVolTermStructure',`ProcessDiscretization', preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}

{#fun qlSquareRootProcess as squareRootProcess{`Double',`Double',`Double',`Double',`ProcessDiscretization', preErrorCheck-`String'errorCheck*-}->`StochasticProcess1D'peekStochasticProcess1D*#}

{#fun qlVegaStressedBlackScholesProcess as vegaStressedBlackScholesProcess{withQuote*`GenQuote a',withYieldTermStructure*`YieldTermStructure',withYieldTermStructure*`YieldTermStructure',withBlackVolTermStructure*`BlackVolTermStructure',`Double',`Double',`Double',`Double',`Double',`ProcessDiscretization', preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}

{#fun qlBatesProcess as batesProcess{withYieldTermStructure*`YieldTermStructure',withYieldTermStructure*`YieldTermStructure', withQuote*`GenQuote a',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`HestonProcessDiscretization', preErrorCheck-`String'errorCheck*-}->`BatesProcess'peekBatesProcess*#}

{#fun qlExtOUWithJumpsProcess as extOUWithJumpsProcess{withExtendedOrnsteinUhlenbeckProcess*`ExtendedOrnsteinUhlenbeckProcess',`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`ExtOUWithJumpsProcess'peekExtOUWithJumpsProcess*#}

{#fun qlG2ForwardProcess as g2ForwardProcess{`Double',`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`StochasticProcess'peekStochasticProcess*#}

{#fun qlG2Process as g2Process{`Double',`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`StochasticProcess'peekStochasticProcess*#}

{#fun qlGemanRoncoroniProcess as gemanRoncoroniProcess{`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`StochasticProcess1D'peekStochasticProcess1D*#}

{#fun qlGeometricBrownianMotionProcess as geometricBrownianMotionProcess{`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`StochasticProcess1D'peekStochasticProcess1D*#}

{#fun qlGJRGARCHProcess as gjrGARCHProcess{withYieldTermStructure*`YieldTermStructure',withYieldTermStructure*`YieldTermStructure', withQuote*`GenQuote a',`Double',`Double',`Double',`Double',`Double',`Double',`Double',`GJRGARCHProcessDiscretization', preErrorCheck-`String'errorCheck*-}->`GJRGARCHProcess'peekGJRGARCHProcess*#}

{#fun qlHestonProcess as hestonProcess{withYieldTermStructure*`YieldTermStructure',withYieldTermStructure*`YieldTermStructure', withQuote*`GenQuote a',`Double',`Double',`Double',`Double',`Double',`HestonProcessDiscretization', preErrorCheck-`String'errorCheck*-}->`HestonProcess'peekHestonProcess*#}

{#fun qlHullWhiteForwardProcess as hullWhiteForwardProcess{withYieldTermStructure*`YieldTermStructure',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`HullWhiteForwardProcess'peekHullWhiteForwardProcess*#}

{#fun qlHullWhiteProcess as hullWhiteProcess{withYieldTermStructure*`YieldTermStructure',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`HullWhiteProcess'peekHullWhiteProcess*#}

{#fun qlHybridHestonHullWhiteProcess as hybridHestonHullWhiteProcess{withHestonProcess*`HestonProcess',withHullWhiteForwardProcess*`HullWhiteForwardProcess',`Double',`HybridHestonHullWhiteProcessDiscretization', preErrorCheck-`String'errorCheck*-}->`HybridHestonHullWhiteProcess'peekHybridHestonHullWhiteProcess*#}

{#fun qlKlugeExtOUProcess as klugeExtOUProcess{`Double',withExtOUWithJumpsProcess*`ExtOUWithJumpsProcess',withExtendedOrnsteinUhlenbeckProcess*`ExtendedOrnsteinUhlenbeckProcess', preErrorCheck-`String'errorCheck*-}->`KlugeExtOUProcess'peekKlugeExtOUProcess*#}

{#fun qlLiborForwardModelProcess as liborForwardModelProcess{fromIntegral`Word',withIborIndex*`GenIborIndex a', preErrorCheck-`String'errorCheck*-}->`LiborForwardModelProcess'peekLiborForwardModelProcess*#}

{#fun qlMerton76Process as merton76Process{withQuote*`GenQuote a',withYieldTermStructure*`YieldTermStructure',withYieldTermStructure*`YieldTermStructure',withBlackVolTermStructure*`BlackVolTermStructure', withQuote*`GenQuote b', withQuote*`GenQuote c', withQuote*`GenQuote d',`ProcessDiscretization', preErrorCheck-`String'errorCheck*-}->`Merton76Process'peekMerton76Process*#}

{#fun qlOrnsteinUhlenbeckProcess as ornsteinUhlenbeckProcess{`Double',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`StochasticProcess1D'peekStochasticProcess1D*#}

{#fun qlVarianceGammaProcess as varianceGammaProcess{withQuote*`GenQuote a',withYieldTermStructure*`YieldTermStructure',withYieldTermStructure*`YieldTermStructure',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`VarianceGammaProcess'peekVarianceGammaProcess*#}

stochasticProcessArray :: [StochasticProcess1D] -> Matrix Double -> IO StochasticProcessArray
stochasticProcessArray a (Matrix mr mc md) = qlStochasticProcessArray a mr mc md
{#fun qlStochasticProcessArray{withStochasticProcess1DArray*`[StochasticProcess1D]'&, fromIntegral`Word', fromIntegral`Word', withDoubleArrayRaw*`[Double]', preErrorCheck-`String'errorCheck*-}->`StochasticProcessArray'peekStochasticProcessArray*#}

-- |default theta calculation for Black-Scholes options
{#fun qlQuantLibBlackScholesTheta as blackScholesTheta{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double',`Double',`Double', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
