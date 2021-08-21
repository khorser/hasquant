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
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

import QuantLib.Internal

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

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
