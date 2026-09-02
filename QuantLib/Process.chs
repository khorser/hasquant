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
  , HestonSLVProcess
  , BatesProcess
  , G2Process
  , G2ForwardProcess
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
  , diffusion
  , drift
  , expectation
  , extOUWithJumpsProcess
  , factors
  , initialValues
  , g2ForwardProcess
  , g2Process
  , gemanRoncoroniProcess
  , geometricBrownianMotionProcess
  , gjrGARCHProcess
  , hestonProcess
  , hestonSLVProcess
  , hullWhiteForwardProcess
  , hullWhiteProcess
  , hybridHestonHullWhiteProcess
  , klugeExtOUProcess
  , liborForwardModelProcess
  , liborForwardModelProcessFixingDates
  , liborForwardModelProcessFixingTimes
  , liborForwardModelProcessCashFlows
  , liborForwardModelProcessIndex
  , merton76Process
  , ornsteinUhlenbeckProcess
  , varianceGammaProcess
  , stochasticProcessArray

  , g2Phi
  , g2ShortRate
  , g2ForwardPhi
  , g2ForwardShortRate
  , setForwardMeasureTime

  , blackScholesTheta
  ) where
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

import QuantLib.Internal
import QuantLib.Internal.Type
import Data.List.NonEmpty(NonEmpty, toList)

{#enum ProcessDiscretization{} deriving(Show,Eq, Read)#}
{#enum ExtendedBlackScholesMertonProcessDiscretization{} deriving(Show, Eq, Read)#}
{#enum HestonProcessDiscretization{} deriving(Show, Eq, Read)#}
{#enum GJRGARCHProcessDiscretization{} deriving(Show, Eq, Read)#}
{#enum HybridHestonHullWhiteProcessDiscretization{} deriving(Show, Eq, Read)#}

{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *Leg foreign -> CLeg' nocode#}
{#pointer *QlBlackVolTermStructure as BlackVolTermStructure foreign -> CBlackVolTermStructure' nocode#}
{#pointer *QlLocalVolTermStructure as LocalVolTermStructure foreign -> CLocalVolTermStructure' nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}

{#pointer *QlGeneralizedBlackScholesProcess as GeneralizedBlackScholesProcess foreign -> CGeneralizedBlackScholesProcess' nocode#}
{#pointer *QlStochasticProcess1D as StochasticProcess1D foreign -> CStochasticProcess1D' nocode#}
{#pointer *QlStochasticProcess as StochasticProcess foreign -> CStochasticProcess' nocode#}
{#pointer *QlBlackProcess as BlackProcess foreign -> CBlackProcess' nocode#}
{#pointer *QlExtOUWithJumpsProcess as ExtOUWithJumpsProcess foreign -> CExtOUWithJumpsProcess' nocode#}
{#pointer *QlExtendedOrnsteinUhlenbeckProcess as ExtendedOrnsteinUhlenbeckProcess foreign -> CExtendedOrnsteinUhlenbeckProcess' nocode#}
{#pointer *QlGJRGARCHProcess as GJRGARCHProcess foreign -> CGJRGARCHProcess' nocode#}
{#pointer *QlHestonProcess as HestonProcess foreign -> CHestonProcess' nocode#}
{#pointer *QlHestonSLVProcess as HestonSLVProcess foreign -> CHestonSLVProcess' nocode#}
{#pointer *QlG2Process as G2Process foreign -> CG2Process' nocode#}
{#pointer *QlG2ForwardProcess as G2ForwardProcess foreign -> CG2ForwardProcess' nocode#}
{#pointer *QlBatesProcess as BatesProcess foreign -> CBatesProcess' nocode#}
{#pointer *QlHybridHestonHullWhiteProcess as HybridHestonHullWhiteProcess foreign -> CHybridHestonHullWhiteProcess' nocode#}
{#pointer *QlKlugeExtOUProcess as KlugeExtOUProcess foreign -> CKlugeExtOUProcess' nocode#}
{#pointer *QlLiborForwardModelProcess as LiborForwardModelProcess foreign -> CLiborForwardModelProcess' nocode#}
{#pointer *QlStochasticProcessArray as StochasticProcessArray foreign -> CStochasticProcessArray' nocode#}
{#pointer *QlVarianceGammaProcess as VarianceGammaProcess foreign -> CVarianceGammaProcess' nocode#}
{#pointer *QlMerton76Process as Merton76Process foreign -> CMerton76Process' nocode#}
{#pointer *QlHullWhiteProcess as HullWhiteProcess foreign -> CHullWhiteProcess' nocode#}
{#pointer *QlHullWhiteForwardProcess as HullWhiteForwardProcess foreign -> CHullWhiteForwardProcess' nocode#}

-- |Black (1976) process for a forward or futures contract: d(ln S) = -sigma^2\/2 dt + sigma dW.
{#fun qlBlackProcess as blackProcess{withQuote*`GenQuote q' -- ^x0
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^riskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv' -- ^blackVolTS
  ,`ProcessDiscretization'
  ,`Bool' -- ^forceDiscretization
  ,preErrorCheck-`String'errorCheck*-}->`BlackProcess'peekBlackProcess*#}

-- |Merton (1973) extension of Black-Scholes for a continuous-dividend-paying stock:
-- d(ln S) = (r - q - sigma^2\/2) dt + sigma dW.
{#fun qlBlackScholesMertonProcess as blackScholesMertonProcess{withQuote*`GenQuote q' -- ^x0
  ,withYieldTermStructure*`GenYieldTermStructure y1' -- ^dividendTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^riskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv' -- ^blackVolTS
  ,`ProcessDiscretization'
  ,`Bool' -- ^forceDiscretization
  ,preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}

-- |Black-Scholes (1973) process for a stock: d(ln S) = (r - sigma^2\/2) dt + sigma dW.
{#fun qlBlackScholesProcess as blackScholesProcess{withQuote*`GenQuote q' -- ^x0
  ,withYieldTermStructure*`GenYieldTermStructure y' -- ^riskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv' -- ^blackVolTS
  ,`ProcessDiscretization'
  ,`Bool' -- ^forceDiscretization
  ,preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}

-- |'blackScholesMertonProcess' with a choice of evolution scheme (Euler\/Milstein\/predictor-corrector)
-- on top of the discretization argument.
{#fun qlExtendedBlackScholesMertonProcess as extendedBlackScholesMertonProcess{withQuote*`GenQuote q' -- ^x0
  ,withYieldTermStructure*`GenYieldTermStructure y1' -- ^dividendTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^riskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv' -- ^blackVolTS
  ,`ProcessDiscretization',`ExtendedBlackScholesMertonProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}

-- |Garman-Kohlhagen (1983) process for an exchange rate: d(ln S) = (r - r_f - sigma^2\/2) dt + sigma dW.
{#fun qlGarmanKohlagenProcess as garmanKohlagenProcess{withQuote*`GenQuote q' -- ^x0
  ,withYieldTermStructure*`GenYieldTermStructure y1' -- ^foreignRiskFreeTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^domesticRiskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv' -- ^blackVolTS
  ,`ProcessDiscretization'
  ,`Bool' -- ^forceDiscretization
  ,preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}

-- |Generalized Black-Scholes process with separate dividend and risk-free curves:
-- d(ln S) = (r - q - sigma^2\/2) dt + sigma dW.
{#fun qlGeneralizedBlackScholesProcess as generalizedBlackScholesProcess{withQuote*`GenQuote q' -- ^x0
  ,withYieldTermStructure*`GenYieldTermStructure y1' -- ^dividendTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^riskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv' -- ^blackVolTS
  ,`ProcessDiscretization'
  ,`Bool' -- ^forceDiscretization
  ,preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}

-- |square-root process: dx = a (b - x) dt + sigma sqrt(x) dW.
{#fun qlSquareRootProcess as squareRootProcess{`Double' -- ^b
  ,`Double' -- ^a
  ,`Double' -- ^sigma
  ,`Double' -- ^x0
  ,`ProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`StochasticProcess1D'peekStochasticProcess1D*#}

-- |'blackScholesMertonProcess' variant supporting local vega stress tests over a given
-- time\/asset border and stress level.
{#fun qlVegaStressedBlackScholesProcess as vegaStressedBlackScholesProcess{withQuote*`GenQuote q' -- ^x0
  ,withYieldTermStructure*`GenYieldTermStructure y1' -- ^dividendTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^riskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv' -- ^blackVolTS
  ,`Double' -- ^lowerTimeBorderForStressTest
  ,`Double' -- ^upperTimeBorderForStressTest
  ,`Double' -- ^lowerAssetBorderForStressTest
  ,`Double' -- ^upperAssetBorderForStressTest
  ,`Double' -- ^stressLevel
  ,`ProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`GeneralizedBlackScholesProcess'peekGeneralizedBlackScholesProcess*#}

-- |square-root stochastic-volatility Bates process: a Heston process plus a compound Poisson
-- jump component with log-normally distributed jump size.
{#fun qlBatesProcess as batesProcess{withYieldTermStructure*`GenYieldTermStructure y1' -- ^riskFreeTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^dividendYield
  ,withQuote*`GenQuote q' -- ^s0
  ,`Double' -- ^v0
  ,`Double' -- ^kappa
  ,`Double' -- ^theta
  ,`Double' -- ^sigma
  ,`Double' -- ^rho
  ,`Double' -- ^lambda
  ,`Double' -- ^nu
  ,`Double' -- ^delta
  ,`HestonProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`BatesProcess'peekBatesProcess*#}

-- |Kluge model: an extended Ornstein-Uhlenbeck process plus an exponential-jump component,
-- S = exp(X + Y) with dX = alpha (mu(t) - X) dt + sigma dW and dY = -beta Y dt + J dN.
{#fun qlExtOUWithJumpsProcess as extOUWithJumpsProcess{withGenStochasticProcess1D*`ExtendedOrnsteinUhlenbeckProcess',`Double' -- ^Y0
  ,`Double' -- ^beta
  ,`Double' -- ^jumpIntensity
  ,`Double' -- ^eta
  ,preErrorCheck-`String'errorCheck*-}->`ExtOUWithJumpsProcess'peekExtOUWithJumpsProcess*#}

-- |T-forward-measure counterpart of 'g2Process': the two-factor G2++ short-rate model, with
-- the simulated state again shifted so its components sum to the short rate.
{#fun qlG2ForwardProcess as g2ForwardProcess{`Double' -- ^a
  ,`Double' -- ^sigma
  ,`Double' -- ^b
  ,`Double' -- ^eta
  ,`Double' -- ^rho
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^termStructure
  ,preErrorCheck-`String'errorCheck*-}->`G2ForwardProcess'peekG2ForwardProcess*#}

-- |two-factor G2++ short-rate process, state shifted so its two OU components sum to the
-- short rate; degenerates to a pair of zero-mean OU processes if no term structure is given.
{#fun qlG2Process as g2Process{`Double' -- ^a
  ,`Double' -- ^sigma
  ,`Double' -- ^b
  ,`Double' -- ^eta
  ,`Double' -- ^rho
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^termStructure
  ,preErrorCheck-`String'errorCheck*-}->`G2Process'peekG2Process*#}

-- |the deterministic offset phi(t) that fits 'g2Process''s initial term structure -- throws if
-- the process was constructed with no term structure.
{#fun qlG2ProcessPhi as g2Phi{withGenStochasticProcess*`G2Process',`Double' -- ^t
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the short rate implied by a simulated 'g2Process' state @(z1, z2)@ at time /t/: just
-- @z1 + z2@, since 'g2Phi''s offset is already baked into the first simulated component.
{#fun pure qlG2ProcessShortRate as g2ShortRate{withGenStochasticProcess*`G2Process',`Double' -- ^t
  ,`Double' -- ^z1
  ,`Double' -- ^z2
  }->`Double'#}

-- |the deterministic offset phi(t) that fits 'g2ForwardProcess''s initial term structure --
-- throws if the process was constructed with no term structure.
{#fun qlG2ForwardProcessPhi as g2ForwardPhi{withGenStochasticProcess*`G2ForwardProcess',`Double' -- ^t
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the short rate implied by a simulated 'g2ForwardProcess' state @(z1, z2)@ at time /t/: just
-- @z1 + z2@, since 'g2ForwardPhi''s offset is already baked into the first simulated component.
{#fun pure qlG2ForwardProcessShortRate as g2ForwardShortRate{withGenStochasticProcess*`G2ForwardProcess',`Double' -- ^t
  ,`Double' -- ^z1
  ,`Double' -- ^z2
  }->`Double'#}

-- |the number of independent Brownian factors driving a stochastic process -- e.g. 2 for
-- 'g2Process', matching its state size; used to size a 'QuantLib.Method.pathGenerator''s
-- underlying sequence generator (@process->factors() * steps@, mirroring upstream's own usage).
{#fun qlStochasticProcessFactors as factors{withStochasticProcess*`GenStochasticProcess p',preErrorCheck-`String'errorCheck*-}->`Word'fromIntegral#}

-- |the process's state at time 0, e.g. @(0, 0)@ for a curveless 'g2Process' or
-- @(phi(0), 0)@ once a term structure is given.
{#fun qlStochasticProcessInitialValues as initialValues{withStochasticProcess*`GenStochasticProcess p',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |the drift part of the process's SDE at state /x/ and time /t/, i.e. @mu(t, x_t)@ in
-- @dx_t = mu(t, x_t) dt + sigma(t, x_t) dW_t@.
{#fun qlStochasticProcessDrift as drift{withStochasticProcess*`GenStochasticProcess p'
  ,`Double' -- ^t
  ,withDoubleArray*`[Double]'& -- ^x
  ,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

toMatrixDouble :: (Word, Word, [Double]) -> Matrix Double
toMatrixDouble (r, c, d) = Matrix r c d

-- |the diffusion part of the process's SDE at state /x/ and time /t/, i.e. @sigma(t, x_t)@ in
-- @dx_t = mu(t, x_t) dt + sigma(t, x_t) dW_t@.
diffusion :: GenStochasticProcess p -> Double -> [Double] -> IO (Matrix Double)
diffusion p t x = toMatrixDouble <$> qlStochasticProcessDiffusion p t x
{#fun qlStochasticProcessDiffusion{withStochasticProcess*`GenStochasticProcess p'
  ,`Double' -- ^t
  ,withDoubleArray*`[Double]'& -- ^x
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |E[x_(t0+dt) | x_t0 = x0], the expected state at /t0+dt/ given state /x0/ at time /t0/.
{#fun qlStochasticProcessExpectation as expectation{withStochasticProcess*`GenStochasticProcess p'
  ,`Double' -- ^t0
  ,withDoubleArray*`[Double]'& -- ^x0
  ,`Double' -- ^dt
  ,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Geman-Roncoroni process, a mean-reverting jump-diffusion model for electricity spot prices
-- with a seasonal deterministic mean and an asymmetric jump term.
{#fun qlGemanRoncoroniProcess as gemanRoncoroniProcess{`Double'-- ^x0
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^gamma
  ,`Double' -- ^delta
  ,`Double' -- ^eps
  ,`Double' -- ^zeta
  ,`Double' -- ^d
  ,`Double' -- ^k
  ,`Double' -- ^tau
  ,`Double' -- ^sig2
  ,`Double' -- ^a
  ,`Double' -- ^b
  ,`Double' -- ^theta1
  ,`Double' -- ^theta2
  ,`Double' -- ^theta3
  ,`Double' -- ^psi
  ,preErrorCheck-`String'errorCheck*-}->`StochasticProcess1D'peekStochasticProcess1D*#}

-- |geometric Brownian motion process: dS = mue S dt + sigma S dW.
{#fun qlGeometricBrownianMotionProcess as geometricBrownianMotionProcess{`Double' -- ^initialValue
  ,`Double' -- ^mue
  ,`Double' -- ^sigma
  ,preErrorCheck-`String'errorCheck*-}->`StochasticProcess1D'peekStochasticProcess1D*#}

-- |stochastic-volatility GJR-GARCH(1,1) process; parameters are supplied as daily constants
-- and annualized internally via daysPerYear.
{#fun qlGJRGARCHProcess as gjrGARCHProcess{withYieldTermStructure*`GenYieldTermStructure y1' -- ^riskFreeRate
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^dividendYield
  ,withQuote*`GenQuote q' -- ^s0
  ,`Double' -- ^v0
  ,`Double' -- ^omega
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^gamma
  ,`Double' -- ^lambda
  ,`Double' -- ^daysPerYear
  ,`GJRGARCHProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`GJRGARCHProcess'peekGJRGARCHProcess*#}

-- |/dividendYield/ may be 'Nothing' (an empty term-structure handle) -- required e.g. by
-- 'QuantLib.PricingEngine.integralHestonVarianceOptionEngine', which rejects a process with a
-- non-empty dividend handle.
{#fun qlHestonProcess as hestonProcess{withYieldTermStructure*`GenYieldTermStructure y1' -- ^riskFreeRate
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y2)' -- ^dividendYield
  ,withQuote*`GenQuote q' -- ^s0
  ,`Double' -- ^v0
  ,`Double' -- ^kappa
  ,`Double' -- ^theta
  ,`Double' -- ^sigma
  ,`Double' -- ^rho
  ,`HestonProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`HestonProcess'peekHestonProcess*#}

-- |Two-factor Heston stochastic-local-volatility process using the supplied calibrated leverage
-- function. It is a generic 'StochasticProcess', so it composes with path generators and the
-- existing drift/diffusion operations.
{#fun qlHestonSLVProcess as hestonSLVProcess{withHestonProcess*`GenHestonProcess hp' -- ^hestonProcess
  ,withGenLocalVolTermStructure*`GenLocalVolTermStructure lv' -- ^leverageFct
  ,`Double' -- ^mixingFactor
  ,preErrorCheck-`String'errorCheck*-}->`HestonSLVProcess'peekHestonSLVProcess*#}

-- |T-forward-measure counterpart of 'hullWhiteProcess'.
{#fun qlHullWhiteForwardProcess as hullWhiteForwardProcess{withYieldTermStructure*`GenYieldTermStructure y' -- ^h
  ,`Double' -- ^y
  ,`Double' -- ^sigma
  ,preErrorCheck-`String'errorCheck*-}->`HullWhiteForwardProcess'peekHullWhiteForwardProcess*#}

-- |sets the T-forward measure's maturity time: a required post-construction call before a
-- 'hullWhiteForwardProcess' can be used for forward-measure pricing (e.g. as the short-rate leg
-- of 'hybridHestonHullWhiteProcess') -- upstream calls it immediately after construction, once
-- the pricing horizon is known.
{#fun qlHullWhiteForwardProcessSetForwardMeasureTime as setForwardMeasureTime{withGenStochasticProcess1D*`HullWhiteForwardProcess',`Double' -- ^t
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Hull-White one-factor short-rate process, fitted to the given initial term structure.
{#fun qlHullWhiteProcess as hullWhiteProcess{withYieldTermStructure*`GenYieldTermStructure y' -- ^h
  ,`Double' -- ^y
  ,`Double' -- ^sigma
  ,preErrorCheck-`String'errorCheck*-}->`HullWhiteProcess'peekHullWhiteProcess*#}

-- |three-factor hybrid model combining a Heston equity process with a Hull-White short-rate
-- process, correlated via corrEquityShortRate.
{#fun qlHybridHestonHullWhiteProcess as hybridHestonHullWhiteProcess{withHestonProcess*`GenHestonProcess hp',withGenStochasticProcess1D*`HullWhiteForwardProcess'
  ,`Double' -- ^corrEquityShortRate
  ,`HybridHestonHullWhiteProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`HybridHestonHullWhiteProcess'peekHybridHestonHullWhiteProcess*#}

-- |joint correlated Kluge ('extOUWithJumpsProcess') and extended Ornstein-Uhlenbeck process.
{#fun qlKlugeExtOUProcess as klugeExtOUProcess{`Double' -- ^rho
  ,withGenStochasticProcess*`ExtOUWithJumpsProcess',withGenStochasticProcess1D*`ExtendedOrnsteinUhlenbeckProcess',preErrorCheck-`String'errorCheck*-}->`KlugeExtOUProcess'peekKlugeExtOUProcess*#}

-- |Libor market model process, evolving /size/ forward rates of /index/ under the rolling
-- forward measure with a predictor-corrector step.
{#fun qlLiborForwardModelProcess as liborForwardModelProcess{fromIntegral`Word' -- ^size
  ,withIborIndex*`GenIborIndex ibor',preErrorCheck-`String'errorCheck*-}->`LiborForwardModelProcess'peekLiborForwardModelProcess*#}

-- |the reset (fixing) dates of the forward rates this process evolves
{#fun qlLiborForwardModelProcessFixingDates as liborForwardModelProcessFixingDates{withGenStochasticProcess*`LiborForwardModelProcess'
  ,preArray-`[Day]'&peekDayArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |the reset (fixing) times of the forward rates this process evolves, in the process's own
-- day count fraction from the evaluation date
{#fun qlLiborForwardModelProcessFixingTimes as liborForwardModelProcessFixingTimes{withGenStochasticProcess*`LiborForwardModelProcess'
  ,preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |the leg of Ibor coupons (notional @amount@ each) this process's forward rates reset -- used
-- e.g. to build the 'QuantLib.Instrument.CapFloor.cap' this process prices via 'liborForwardModel'
{#fun qlLiborForwardModelProcessCashFlows as liborForwardModelProcessCashFlows{withGenStochasticProcess*`LiborForwardModelProcess'
  ,`Double' -- ^amount
  ,preErrorCheck-`String'errorCheck*-}->`Leg'peekLeg*#}

-- |the underlying 'IborIndex' this process was constructed with
{#fun qlLiborForwardModelProcessIndex as liborForwardModelProcessIndex{withGenStochasticProcess*`LiborForwardModelProcess'
  ,preErrorCheck-`String'errorCheck*-}->`IborIndex'peekIborIndex*#}

-- |Merton (1976) jump-diffusion process: a Black-Scholes process plus a log-normal jump
-- component with Poisson jump intensity jumpInt.
{#fun qlMerton76Process as merton76Process{withQuote*`GenQuote q1' -- ^stateVariable
  ,withYieldTermStructure*`GenYieldTermStructure y1' -- ^dividendTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^riskFreeTS
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv' -- ^blackVolTS
  ,withQuote*`GenQuote q2' -- ^jumpInt
  ,withQuote*`GenQuote q3' -- ^logJMean
  ,withQuote*`GenQuote q4' -- ^logJVol
  ,`ProcessDiscretization',preErrorCheck-`String'errorCheck*-}->`Merton76Process'peekMerton76Process*#}

-- |Ornstein-Uhlenbeck process: dx = a (level - x) dt + sigma dW.
{#fun qlOrnsteinUhlenbeckProcess as ornsteinUhlenbeckProcess{`Double' -- ^speed
  ,`Double' -- ^vol
  ,`Double' -- ^x0
  ,`Double' -- ^level
  ,preErrorCheck-`String'errorCheck*-}->`StochasticProcess1D'peekStochasticProcess1D*#}

-- |Variance Gamma process: a Brownian motion db = theta dt + sigma dW time-changed by an
-- independent Gamma process with mean 1 and variance rate nu.
{#fun qlVarianceGammaProcess as varianceGammaProcess{withQuote*`GenQuote q' -- ^s0
  ,withYieldTermStructure*`GenYieldTermStructure y1' -- ^dividendYield
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^riskFreeRate
  ,`Double' -- ^sigma
  ,`Double' -- ^nu
  ,`Double' -- ^theta
  ,preErrorCheck-`String'errorCheck*-}->`VarianceGammaProcess'peekVarianceGammaProcess*#}

-- |array of correlated 1-D stochastic processes, driven by a joint correlation matrix.
stochasticProcessArray :: NonEmpty (GenStochasticProcess1D p1d) -> Matrix Double -- ^correlation
  -> IO StochasticProcessArray
stochasticProcessArray a (Matrix mr mc md) = qlStochasticProcessArray (toList a) mr mc md
{#fun qlStochasticProcessArray{withStochasticProcess1DArray*`[GenStochasticProcess1D p1d]'&,fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]',preErrorCheck-`String'errorCheck*-}->`StochasticProcessArray'peekStochasticProcessArray*#}

-- |default theta calculation for Black-Scholes options
{#fun qlQuantLibBlackScholesTheta as blackScholesTheta{withGeneralizedBlackScholesProcess*`GeneralizedBlackScholesProcess',`Double' -- ^value
  ,`Double' -- ^delta
  ,`Double' -- ^gamma
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
