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
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
{#import QuantLib.TermStructure.Volatility#}(BlackVolTermStructure)
import QuantLib.Internal.TermStructure
{#import QuantLib.Index.InterestRate#}
import QuantLib.Internal.Index

{#pointer *QlQuote as Quote foreign -> CQuote nocode#}

{#enum ProcessDiscretization {} deriving(Show,Eq)#}

{#enum ExtendedBlackScholesMertonProcessDiscretization {} deriving(Show, Eq)#}

{#enum HestonProcessDiscretization {} deriving(Show, Eq)#}

{#enum GJRGARCHProcessDiscretization {} deriving(Show, Eq)#}

{#enum HybridHestonHullWhiteProcessDiscretization {} deriving(Show, Eq)#}

{#pointer *QlGeneralizedBlackScholesProcess as GeneralizedBlackScholesProcess foreign finalizer qlFreeGeneralizedBlackScholesProcess newtype#}
instance ForeignObject GeneralizedBlackScholesProcess where
  withObject = withGeneralizedBlackScholesProcess
  constructor = GeneralizedBlackScholesProcess
  finalizer = qlFreeGeneralizedBlackScholesProcess

{#pointer *QlStochasticProcess1D as StochasticProcess1D foreign finalizer qlFreeStochasticProcess1D newtype#}
instance ForeignObject StochasticProcess1D where
  withObject = withStochasticProcess1D
  constructor = StochasticProcess1D
  finalizer = qlFreeStochasticProcess1D

{#pointer *QlStochasticProcess as StochasticProcess foreign finalizer qlFreeStochasticProcess newtype#}
instance ForeignObject StochasticProcess where
  withObject = withStochasticProcess
  constructor = StochasticProcess
  finalizer = qlFreeStochasticProcess

{#pointer *QlBlackProcess as BlackProcess foreign finalizer qlFreeBlackProcess newtype#}
instance ForeignObject BlackProcess where
  withObject = withBlackProcess
  constructor = BlackProcess
  finalizer = qlFreeBlackProcess

{#pointer *QlExtOUWithJumpsProcess as ExtOUWithJumpsProcess foreign finalizer qlFreeExtOUWithJumpsProcess newtype#}
instance ForeignObject ExtOUWithJumpsProcess where
  withObject = withExtOUWithJumpsProcess
  constructor = ExtOUWithJumpsProcess
  finalizer = qlFreeExtOUWithJumpsProcess

{#pointer *QlExtendedOrnsteinUhlenbeckProcess as ExtendedOrnsteinUhlenbeckProcess foreign finalizer qlFreeExtendedOrnsteinUhlenbeckProcess newtype#}
instance ForeignObject ExtendedOrnsteinUhlenbeckProcess where
  withObject = withExtendedOrnsteinUhlenbeckProcess
  constructor = ExtendedOrnsteinUhlenbeckProcess
  finalizer = qlFreeExtendedOrnsteinUhlenbeckProcess

{#pointer *QlGJRGARCHProcess as GJRGARCHProcess foreign finalizer qlFreeGJRGARCHProcess newtype#}
instance ForeignObject GJRGARCHProcess where
  withObject = withGJRGARCHProcess
  constructor = GJRGARCHProcess
  finalizer = qlFreeGJRGARCHProcess

{#pointer *QlHestonProcess as HestonProcess foreign finalizer qlFreeHestonProcess newtype#}
instance ForeignObject HestonProcess where
  withObject = withHestonProcess
  constructor = HestonProcess
  finalizer = qlFreeHestonProcess

{#pointer *QlBatesProcess as BatesProcess foreign finalizer qlFreeBatesProcess newtype#}
instance ForeignObject BatesProcess where
  withObject = withBatesProcess
  constructor = BatesProcess
  finalizer = qlFreeBatesProcess

{#pointer *QlHybridHestonHullWhiteProcess as HybridHestonHullWhiteProcess foreign finalizer qlFreeHybridHestonHullWhiteProcess newtype#}
instance ForeignObject HybridHestonHullWhiteProcess where
  withObject = withHybridHestonHullWhiteProcess
  constructor = HybridHestonHullWhiteProcess
  finalizer = qlFreeHybridHestonHullWhiteProcess

{#pointer *QlKlugeExtOUProcess as KlugeExtOUProcess foreign finalizer qlFreeKlugeExtOUProcess newtype#}
instance ForeignObject KlugeExtOUProcess where
  withObject = withKlugeExtOUProcess
  constructor = KlugeExtOUProcess
  finalizer = qlFreeKlugeExtOUProcess

{#pointer *QlLiborForwardModelProcess as LiborForwardModelProcess foreign finalizer qlFreeLiborForwardModelProcess newtype#}
instance ForeignObject LiborForwardModelProcess where
  withObject = withLiborForwardModelProcess
  constructor = LiborForwardModelProcess
  finalizer = qlFreeLiborForwardModelProcess

{#pointer *QlStochasticProcessArray as StochasticProcessArray foreign finalizer qlFreeStochasticProcessArray newtype#}
instance ForeignObject StochasticProcessArray where
  withObject = withStochasticProcessArray
  constructor = StochasticProcessArray
  finalizer = qlFreeStochasticProcessArray

{#pointer *QlVarianceGammaProcess as VarianceGammaProcess foreign finalizer qlFreeVarianceGammaProcess newtype#}
instance ForeignObject VarianceGammaProcess where
  withObject = withVarianceGammaProcess
  constructor = VarianceGammaProcess
  finalizer = qlFreeVarianceGammaProcess

{#pointer *QlMerton76Process as Merton76Process foreign finalizer qlFreeMerton76Process newtype#}
instance ForeignObject Merton76Process where
  withObject = withMerton76Process
  constructor = Merton76Process
  finalizer = qlFreeMerton76Process

{#pointer *QlHullWhiteProcess as HullWhiteProcess foreign finalizer qlFreeHullWhiteProcess newtype#}
instance ForeignObject HullWhiteProcess where
  withObject = withHullWhiteProcess
  constructor = HullWhiteProcess
  finalizer = qlFreeHullWhiteProcess

{#pointer *QlHullWhiteForwardProcess as HullWhiteForwardProcess foreign finalizer qlFreeHullWhiteForwardProcess newtype#}
instance ForeignObject HullWhiteForwardProcess where
  withObject = withHullWhiteForwardProcess
  constructor = HullWhiteForwardProcess
  finalizer = qlFreeHullWhiteForwardProcess

asStochasticProcess :: (a `Derives` StochasticProcess) => a -> IO StochasticProcess
asStochasticProcess = cast

asStochasticProcess1D :: (a `Derives` StochasticProcess) => a -> IO StochasticProcess
asStochasticProcess1D = cast

instance BlackProcess `Derives` GeneralizedBlackScholesProcess where cast = qlBlackProcessAsGeneralizedBlackScholesProcess

asGeneralizedBlackScholesProcess :: (a `Derives` GeneralizedBlackScholesProcess) => a -> IO GeneralizedBlackScholesProcess
asGeneralizedBlackScholesProcess = cast

{#fun qlBlackProcessAsGeneralizedBlackScholesProcess {`BlackProcess'} -> `GeneralizedBlackScholesProcess'#}
{#fun qlStochasticProcess1DAsStochasticProcess {`StochasticProcess1D'} -> `StochasticProcess'#}
instance StochasticProcess1D `Derives` StochasticProcess where cast = qlStochasticProcess1DAsStochasticProcess
{#fun qlExtOUWithJumpsProcessAsStochasticProcess {`ExtOUWithJumpsProcess'} -> `StochasticProcess'#}
instance ExtOUWithJumpsProcess `Derives` StochasticProcess where cast = qlExtOUWithJumpsProcessAsStochasticProcess
{#fun qlGJRGARCHProcessAsStochasticProcess {`GJRGARCHProcess'} -> `StochasticProcess'#}
instance GJRGARCHProcess `Derives` StochasticProcess where cast = qlGJRGARCHProcessAsStochasticProcess
{#fun qlHestonProcessAsStochasticProcess {`HestonProcess'} -> `StochasticProcess'#}
instance HestonProcess `Derives` StochasticProcess where cast = qlHestonProcessAsStochasticProcess

instance BatesProcess `Derives` HestonProcess where cast = qlBatesProcessAsHestonProcess
asHestonProcess :: (a `Derives` HestonProcess) => a -> IO HestonProcess
asHestonProcess = cast

{#fun qlBatesProcessAsHestonProcess {`BatesProcess'} -> `HestonProcess'#}
{#fun qlHybridHestonHullWhiteProcessAsStochasticProcess {`HybridHestonHullWhiteProcess'} -> `StochasticProcess'#}
instance HybridHestonHullWhiteProcess `Derives` StochasticProcess where cast = qlHybridHestonHullWhiteProcessAsStochasticProcess
{#fun qlKlugeExtOUProcessAsStochasticProcess {`KlugeExtOUProcess'} -> `StochasticProcess'#}
instance KlugeExtOUProcess `Derives` StochasticProcess where cast = qlKlugeExtOUProcessAsStochasticProcess
{#fun qlLiborForwardModelProcessAsStochasticProcess {`LiborForwardModelProcess'} -> `StochasticProcess'#}
instance LiborForwardModelProcess `Derives` StochasticProcess where cast = qlLiborForwardModelProcessAsStochasticProcess
{#fun qlStochasticProcessArrayAsStochasticProcess {`StochasticProcessArray'} -> `StochasticProcess'#}
instance StochasticProcessArray `Derives` StochasticProcess where cast = qlStochasticProcessArrayAsStochasticProcess

{#fun qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D {`ExtendedOrnsteinUhlenbeckProcess'} -> `StochasticProcess1D'#}
instance ExtendedOrnsteinUhlenbeckProcess `Derives` StochasticProcess1D where cast = qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D
{#fun qlGeneralizedBlackScholesProcessAsStochasticProcess1D {`GeneralizedBlackScholesProcess'} -> `StochasticProcess1D'#}
instance GeneralizedBlackScholesProcess `Derives` StochasticProcess1D where cast = qlGeneralizedBlackScholesProcessAsStochasticProcess1D
{#fun qlHullWhiteForwardProcessAsStochasticProcess1D {`HullWhiteForwardProcess'} -> `StochasticProcess1D'#}
instance HullWhiteForwardProcess `Derives` StochasticProcess1D where cast = qlHullWhiteForwardProcessAsStochasticProcess1D
{#fun qlHullWhiteProcessAsStochasticProcess1D {`HullWhiteProcess'} -> `StochasticProcess1D'#}
instance HullWhiteProcess `Derives` StochasticProcess1D where cast = qlHullWhiteProcessAsStochasticProcess1D
{#fun qlMerton76ProcessAsStochasticProcess1D {`Merton76Process'} -> `StochasticProcess1D'#}
instance Merton76Process `Derives` StochasticProcess1D where cast = qlMerton76ProcessAsStochasticProcess1D
{#fun qlVarianceGammaProcessAsStochasticProcess1D {`VarianceGammaProcess'} -> `StochasticProcess1D'#}
instance VarianceGammaProcess `Derives` StochasticProcess1D where cast = qlVarianceGammaProcessAsStochasticProcess1D

{#fun qlBlackProcess as blackProcess {withComplexType *`Quote', `YieldTermStructure', `BlackVolTermStructure', `ProcessDiscretization', preErrorCheck- `String' errorCheck*-} -> `BlackProcess'#}

{#fun qlBlackScholesMertonProcess as blackScholesMertonProcess {withComplexType *`Quote', `YieldTermStructure', `YieldTermStructure', `BlackVolTermStructure', `ProcessDiscretization', preErrorCheck- `String' errorCheck*-} -> `GeneralizedBlackScholesProcess'#}

{#fun qlBlackScholesProcess as blackScholesProcess {withComplexType *`Quote', `YieldTermStructure', `BlackVolTermStructure', `ProcessDiscretization', preErrorCheck- `String' errorCheck*-} -> `GeneralizedBlackScholesProcess'#}

{#fun qlExtendedBlackScholesMertonProcess as extendedBlackScholesMertonProcess {withComplexType *`Quote', `YieldTermStructure', `YieldTermStructure', `BlackVolTermStructure', `ProcessDiscretization', `ExtendedBlackScholesMertonProcessDiscretization', preErrorCheck- `String' errorCheck*-} -> `GeneralizedBlackScholesProcess'#}

{#fun qlGarmanKohlagenProcess as garmanKohlagenProcess {withComplexType *`Quote', `YieldTermStructure', `YieldTermStructure', `BlackVolTermStructure', `ProcessDiscretization', preErrorCheck- `String' errorCheck*-} -> `GeneralizedBlackScholesProcess'#}

{#fun qlGeneralizedBlackScholesProcess as generalizedBlackScholesProcess {withComplexType *`Quote', `YieldTermStructure', `YieldTermStructure', `BlackVolTermStructure', `ProcessDiscretization', preErrorCheck- `String' errorCheck*-} -> `GeneralizedBlackScholesProcess'#}

{#fun qlSquareRootProcess as squareRootProcess {`Double', `Double', `Double', `Double', `ProcessDiscretization', preErrorCheck- `String' errorCheck*-} -> `StochasticProcess1D'#}

{#fun qlVegaStressedBlackScholesProcess as vegaStressedBlackScholesProcess {withComplexType *`Quote', `YieldTermStructure', `YieldTermStructure', `BlackVolTermStructure', `Double', `Double', `Double', `Double', `Double', `ProcessDiscretization', preErrorCheck- `String' errorCheck*-} -> `GeneralizedBlackScholesProcess'#}

{#fun qlBatesProcess as batesProcess {`YieldTermStructure', `YieldTermStructure', withComplexType *`Quote', `Double', `Double', `Double', `Double', `Double', `Double', `Double', `Double', `HestonProcessDiscretization', preErrorCheck- `String' errorCheck*-} -> `BatesProcess'#}

{#fun qlExtOUWithJumpsProcess as extOUWithJumpsProcess {`ExtendedOrnsteinUhlenbeckProcess', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `ExtOUWithJumpsProcess'#}

{#fun qlG2ForwardProcess as g2ForwardProcess {`Double', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `StochasticProcess'#}

{#fun qlG2Process as g2Process {`Double', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `StochasticProcess'#}

{#fun qlGemanRoncoroniProcess as gemanRoncoroniProcess {`Double', `Double', `Double', `Double', `Double', `Double', `Double', `Double', `Double', `Double', `Double', `Double', `Double', `Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `StochasticProcess1D'#}

{#fun qlGeometricBrownianMotionProcess as geometricBrownianMotionProcess {`Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `StochasticProcess1D'#}

{#fun qlGJRGARCHProcess as gjrGARCHProcess {`YieldTermStructure', `YieldTermStructure', withComplexType *`Quote', `Double', `Double', `Double', `Double', `Double', `Double', `Double', `GJRGARCHProcessDiscretization', preErrorCheck- `String' errorCheck*-} -> `GJRGARCHProcess'#}

{#fun qlHestonProcess as hestonProcess {`YieldTermStructure', `YieldTermStructure', withComplexType *`Quote', `Double', `Double', `Double', `Double', `Double', `HestonProcessDiscretization', preErrorCheck- `String' errorCheck*-} -> `HestonProcess'#}

{#fun qlHullWhiteForwardProcess as hullWhiteForwardProcess {`YieldTermStructure', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `HullWhiteForwardProcess'#}

{#fun qlHullWhiteProcess as hullWhiteProcess {`YieldTermStructure', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `HullWhiteProcess'#}

{#fun qlHybridHestonHullWhiteProcess as hybridHestonHullWhiteProcess {`HestonProcess', `HullWhiteForwardProcess', `Double', `HybridHestonHullWhiteProcessDiscretization', preErrorCheck- `String' errorCheck*-} -> `HybridHestonHullWhiteProcess'#}

{#fun qlKlugeExtOUProcess as klugeExtOUProcess {`Double', `ExtOUWithJumpsProcess', `ExtendedOrnsteinUhlenbeckProcess', preErrorCheck- `String' errorCheck*-} -> `KlugeExtOUProcess'#}

{#fun qlLiborForwardModelProcess as liborForwardModelProcess {fromIntegral `Word', `IborIndex', preErrorCheck- `String' errorCheck*-} -> `LiborForwardModelProcess'#}

{#fun qlMerton76Process as merton76Process {withComplexType *`Quote', `YieldTermStructure', `YieldTermStructure', `BlackVolTermStructure', withComplexType *`Quote', withComplexType *`Quote', withComplexType *`Quote', `ProcessDiscretization', preErrorCheck- `String' errorCheck*-} -> `Merton76Process'#}

{#fun qlOrnsteinUhlenbeckProcess as ornsteinUhlenbeckProcess {`Double', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `StochasticProcess1D'#}

{#fun qlVarianceGammaProcess as varianceGammaProcess {withComplexType *`Quote', `YieldTermStructure', `YieldTermStructure', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `VarianceGammaProcess'#}

stochasticProcessArray :: [StochasticProcess1D] -> Matrix Double -> IO StochasticProcessArray
stochasticProcessArray a (Matrix mr mc md) = qlStochasticProcessArray a mr mc md
{#fun qlStochasticProcessArray {withObjectArray* `[StochasticProcess1D]'&, fromIntegral `Word', fromIntegral `Word', withDoubleArrayRaw* `[Double]', preErrorCheck- `String' errorCheck*-} -> `StochasticProcessArray'#}

-- |default theta calculation for Black-Scholes options
{#fun qlQuantLibBlackScholesTheta as blackScholesTheta {`GeneralizedBlackScholesProcess', `Double', `Double', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
