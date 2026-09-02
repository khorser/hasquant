module QuantLib.Model
  (
    CalibrationErrorType(..)
  , SobolBrownianOrdering(..)
  , HestonSLVGreensAlgorithm(..)
  , HestonSLVVarianceTransformation(..)
  , HestonSLVFokkerPlanckFdmParams(..)
  , HestonSLVFDMLogEntry(..)
  , BrownianGeneratorFactory
  , HestonSLVMCModel
  , HestonSLVFDMModel
  , GJRGARCHModel
  , HestonModel
  , GenHestonModel
  , BatesModel
  , GenBatesModel
  , PiecewiseTimeDependentHestonModel
  , ShortRateModel
  , GenShortRateModel
  , AffineModel
  , Gaussian1dModel
  , OneFactorAffineModel
  , GenOneFactorAffineModel
  , LiborForwardModel
  , LfmHullWhiteParameterization
  , HullWhite
  , Gsr
  , MarkovFunctional
  , CalibratedModel
  , GenCalibratedModel
  , G2
  , ShortRateDynamics
  , g2Dynamics
  , shortRate
  , BatesDetJumpModel
  , BatesDoubleExpDetJumpModel
  , BatesDoubleExpModel
  , GenBatesDoubleExpModel
  , LmCorrelationModel(..)
  , LmVolatilityModel(..)
  , CalibrationHelper
  , BlackCalibrationHelper
  , GenBlackCalibrationHelper
  , SwaptionHelper
  , GenCalibrationHelper
  , asCalibrationHelper
  , asBlackCalibrationHelper

  , asCalibratedModel
  , asHestonModel
  , asShortRateModel
  , asOneFactorAffineModel
  , asBatesModel
  , asBatesDoubleExpModel
  , hullWhiteAsAffineModel
  , g2AsAffineModel
  , oneFactorAffineModelAsAffineModel
  , liborForwardModelAsAffineModel
  , gsrAsGaussian1dModel
  , markovFunctionalAsGaussian1dModel

  , batesModel
  , blackKarasinski
  , coxIngersollRoss
  , extendedCoxIngersollRoss
  , g2
  , generalizedHullWhite
  , gJRGARCHModel
  , hestonModel
  , mtBrownianGeneratorFactory
  , sobolBrownianGeneratorFactory
  , hestonSLVMCModel
  , hestonSLVMCLeverageFunction
  , hestonSLVFDMModel
  , hestonSLVFDMLeverageFunction
  , hestonSLVFDMLogEntries
  , hullWhite
  , varianceGammaModel
  , vasicek
  , liborForwardModel
  , lfmHullWhiteParameterization
  , lfmHullWhiteCovariance
  , gsr
  , markovFunctional
  , markovFunctionalCaplet

  , calibrate
  , calibrateVolatilitiesIterative
  , capHelper
  , hestonModelHelper
  , swaptionHelper
  , swaptionHelperFromDate
  , swaptionHelperFromDates
  , swaptionHelperUnderlying
  , swaptionHelperSwaption
  , times

  , discountBond
  , convexityBias
  , fixedReversion
  , gsrVolatility
  , markovFunctionalVolatility
  , params
  , value
  , blackPrice
  , calibrationError
  , impliedVolatility
  , marketValue
  , modelValue
  , volatility
  , setPricingEngine
  ) where
#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "qlEnumObjects.h"

#include "ql.h"

import QuantLib.Internal
{#import QuantLib.Time.Schedule#}(Frequency)
{#import QuantLib.InterestRate#}(VolatilityType)
{#import QuantLib.CashFlow#}(RateAveragingType)
import QuantLib.Internal.Type
import QuantLib.Internal.Common
import QuantLib.Math(SobolDirectionIntegers)
import Data.List(genericTake)
import Data.List.NonEmpty(NonEmpty, toList)

{#enum CalibrationErrorType{} deriving(Show, Eq, Read)#}

-- |Sobol Brownian-bridge coordinate ordering.
data SobolBrownianOrdering = Factors | Steps | Diagonal deriving (Show, Eq, Read, Enum, Bounded)

-- |Initial-density approximation used by the Heston SLV Fokker--Planck calibrator.
data HestonSLVGreensAlgorithm = ZeroCorrelation | Gaussian | SemiAnalytical deriving (Show, Eq, Read, Enum, Bounded)

-- |Variance-coordinate transformation used by the Heston SLV Fokker--Planck calibrator.
data HestonSLVVarianceTransformation = Plain | Power | Log deriving (Show, Eq, Read, Enum, Bounded)

-- |Full numerical configuration for QuantLib's Fokker--Planck SLV calibration.
data HestonSLVFokkerPlanckFdmParams = HestonSLVFokkerPlanckFdmParams
  { hestonSLVXGrid :: !Word, hestonSLVVGrid :: !Word
  , hestonSLVTMaxStepsPerYear :: !Word, hestonSLVTMinStepsPerYear :: !Word, hestonSLVTStepNumberDecay :: !Double
  , hestonSLVNRannacherTimeSteps :: !Word, hestonSLVPredictionCorrectionSteps :: !Word
  , hestonSLVX0Density :: !Double, hestonSLVLocalVolEpsProb :: !Double, hestonSLVMaxIntegrationIterations :: !Word
  , hestonSLVVLowerEps :: !Double, hestonSLVVUpperEps :: !Double, hestonSLVVMin :: !Double
  , hestonSLVV0Density :: !Double, hestonSLVVLowerBoundDensity :: !Double, hestonSLVVUpperBoundDensity :: !Double
  , hestonSLVLeverageFctPropEps :: !Double, hestonSLVGreensAlgorithm :: !HestonSLVGreensAlgorithm
  , hestonSLVVarianceTransformation :: !HestonSLVVarianceTransformation, hestonSLVSchemeDesc :: !FdmScheme
  }

-- |A copied FDM diagnostic snapshot. Coordinates are the native mesher coordinates: the spot
-- axis is log-spot and the variance axis follows 'hestonSLVVarianceTransformation'. Density rows
-- correspond to variance coordinates and columns to log-spot coordinates.
data HestonSLVFDMLogEntry = HestonSLVFDMLogEntry
  { hestonSLVLogTime :: !Double, hestonSLVLogSpotCoordinates :: !RealVector
  , hestonSLVLogVarianceCoordinates :: !RealVector, hestonSLVLogDensity :: !RealMatrix
  } deriving (Show, Eq)

{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlPricingEngine as PricingEngine foreign -> CPricingEngine nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}
{#pointer *QlOptimizationMethod as QlOptimizationMethod foreign -> COptimizationMethod nocode#}
{#pointer *QlEndCriteria as QlEndCriteria foreign -> CEndCriteria nocode#}
{#pointer *Constraint as QlConstraint foreign -> CConstraint nocode#}
{#pointer *QlLmCorrelationModel foreign -> CLmCorrelationModel nocode#}
{#pointer *QlLmVolatilityModel foreign -> CLmVolatilityModel nocode#}
{#pointer *QlLfmHullWhiteParameterization as LfmHullWhiteParameterization foreign -> CLfmHullWhiteParameterization nocode#}

{#pointer *QlGJRGARCHModel as GJRGARCHModel foreign -> CGJRGARCHModel' nocode#}
{#pointer *QlHestonModel as HestonModel foreign -> CHestonModel' nocode#}
{#pointer *QlLocalVolTermStructure as LocalVolTermStructure foreign -> CLocalVolTermStructure' nocode#}
{#pointer *QlBrownianGeneratorFactory as BrownianGeneratorFactory foreign -> CBrownianGeneratorFactory' nocode#}
{#pointer *QlHestonSLVMCModel as HestonSLVMCModel foreign -> CHestonSLVMCModel' nocode#}
{#pointer *QlHestonSLVFDMModel as HestonSLVFDMModel foreign -> CHestonSLVFDMModel' nocode#}
{#pointer *HestonSLVFDMLogEntries as HestonSLVFDMLogEntries foreign -> CHestonSLVFDMLogEntries nocode#}
{#pointer *FdmSchemeDesc as QlFdmSchemeDesc foreign -> CFdmSchemeDesc nocode#}
{#pointer *QlBatesModel as BatesModel foreign -> CBatesModel' nocode#}
{#pointer *QlPiecewiseTimeDependentHestonModel as PiecewiseTimeDependentHestonModel foreign -> CPiecewiseTimeDependentHestonModel' nocode#}
{#pointer *QlShortRateModel as ShortRateModel foreign -> CShortRateModel' nocode#}
{#pointer *QlOneFactorAffineModel as OneFactorAffineModel foreign -> COneFactorAffineModel' nocode#}
{#pointer *QlLiborForwardModel as LiborForwardModel foreign -> CLiborForwardModel' nocode#}
{#pointer *QlHullWhite as HullWhite foreign -> CHullWhite' nocode#}
{#pointer *QlCalibratedModel as CalibratedModel foreign -> CCalibratedModel' nocode#}
{#pointer *QlG2 as G2 foreign -> CG2' nocode#}
{#pointer *QlShortRateDynamics as ShortRateDynamics foreign -> CShortRateDynamics' nocode#}
{#pointer *QlBatesDetJumpModel as BatesDetJumpModel foreign -> CBatesDetJumpModel' nocode#}
{#pointer *QlBatesDoubleExpDetJumpModel as BatesDoubleExpDetJumpModel foreign -> CBatesDoubleExpDetJumpModel' nocode#}
{#pointer *QlBatesDoubleExpModel as BatesDoubleExpModel foreign -> CBatesDoubleExpModel' nocode#}
{#pointer *QlGsr as Gsr foreign -> CGsr' nocode#}
{#pointer *QlMarkovFunctional as MarkovFunctional foreign -> CMarkovFunctional' nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign -> CSwapIndex' nocode#}
{#pointer *QlSwaptionVolatilityStructure as SwaptionVolatilityStructure foreign -> CSwaptionVolatilityStructure' nocode#}

{#pointer *QlCalibrationHelper as CalibrationHelper foreign -> CCalibrationHelper' nocode#}
{#pointer *QlBlackCalibrationHelper as BlackCalibrationHelper foreign -> CBlackCalibrationHelper' nocode#}
{#pointer *QlSwaptionHelper as SwaptionHelper foreign -> CSwaptionHelper' nocode#}
{#pointer *QlFixedVsFloatingSwap as FixedVsFloatingSwap foreign -> CFixedVsFloatingSwap' nocode#}
{#pointer *QlSwaption as Swaption foreign -> CSwaption' nocode#}

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

-- |Bates stochastic-volatility model: extends Heston with jumps in the underlying's return process.
{#fun qlBatesModel as batesModel{withBatesProcess*`BatesProcess',preErrorCheck-`String'errorCheck*-}->`BatesModel'peekBatesModel*#}

-- |Black-Karasinski short-rate model: d(ln r) = (theta(t) - a ln r) dt + sigma dW, with constant reversion @a@ and volatility @sigma@.
{#fun qlBlackKarasinski as blackKarasinski{withYieldTermStructure*`GenYieldTermStructure y',`Double' -- ^y
  ,`Double' -- ^sigma
  ,preErrorCheck-`String'errorCheck*-}->`ShortRateModel'peekShortRateModel*#}

-- |Cox-Ingersoll-Ross short-rate model: dr = k(theta - r) dt + sigma sqrt(r) dW.
{#fun qlCoxIngersollRoss as coxIngersollRoss{`Double' -- ^r0
  ,`Double' -- ^theta
  ,`Double' -- ^k
  ,`Double' -- ^sigma
  ,`Bool' -- ^withFellerConstraint
  ,preErrorCheck-`String'errorCheck*-}->`OneFactorAffineModel'peekOneFactorAffineModel*#}

-- |Extended CIR model: adds a deterministic term-structure-fitting shift to a standard Cox-Ingersoll-Ross process.
{#fun qlExtendedCoxIngersollRoss as extendedCoxIngersollRoss{withYieldTermStructure*`GenYieldTermStructure y',`Double' -- ^theta
  ,`Double' -- ^k
  ,`Double' -- ^sigma
  ,`Double' -- ^x0
  ,`Bool' -- ^withFellerConstraint
  ,preErrorCheck-`String'errorCheck*-}->`OneFactorAffineModel'peekOneFactorAffineModel*#}

-- |Price of a discount bond paying 1 at @maturity@, given the short rate @rate@ at time @now@.
-- Not 'pure': the model's short-rate fitting function depends on its 'YieldTermStructure' handle,
-- which can be relinked after construction, so the result at fixed arguments can change between
-- two calls -- a genuine 'IO' action, not a value fixed at construction time like the other
-- @{#fun pure ...#}@ bindings in this codebase.
{#fun qlOneFactorAffineModelDiscountBond as discountBond{withOneFactorAffineModel*`GenOneFactorAffineModel om',`Double' -- ^now
  ,`Double' -- ^maturity
  ,`Double' -- ^rate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Two-additive-factor Gaussian (G2) short-rate model: the sum of two correlated Ornstein-Uhlenbeck factors.
{#fun qlG2 as g2{withYieldTermStructure*`GenYieldTermStructure y',`Double' -- ^y
  ,`Double' -- ^sigma
  ,`Double' -- ^b
  ,`Double' -- ^eta
  ,`Double' -- ^rho
  ,preErrorCheck-`String'errorCheck*-}->`G2'peekG2*#}

-- |The two-factor short-rate dynamics underlying a 'G2' model (@TwoFactorModel::dynamics()@).
{#fun qlG2Dynamics as g2Dynamics{withG2*`G2',preErrorCheck-`String'errorCheck*-}->`ShortRateDynamics'peekStandalone*#}

-- |Short rate implied by a 'ShortRateDynamics''s two state variables x, y at time t: @fitting_(t) + x + y@. At @x = y = 0@ this collapses to the model's fitting parameter @phi(t)@.
{#fun qlShortRateDynamicsShortRate as shortRate{withStandalone*`ShortRateDynamics'
  ,`Double' -- ^t
  ,`Double' -- ^x
  ,`Double' -- ^y
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Generalized Hull-White model: like 'hullWhite', but reversion and volatility are piecewise-linear functions of time given at @speedstructure@/@volstructure@ dates.
generalizedHullWhite :: GenYieldTermStructure y -> NonEmpty (Day, Double) -- ^speedstructure
  -> NonEmpty (Day, Double) -- ^volstructure
  -> IO ShortRateModel
generalizedHullWhite ts s v = qlGeneralizedHullWhite ts sd vd sq vq where {(sd, sq) = unzip (toList s); (vd, vq) = unzip (toList v)}
{#fun qlGeneralizedHullWhite{withYieldTermStructure*`GenYieldTermStructure y',withDayArray*`[Day]'&,withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,withDoubleArray*`[Double]'&,preErrorCheck-`String'errorCheck*-}->`ShortRateModel'peekShortRateModel*#}

-- |GJR-GARCH stochastic-volatility model, extending GARCH(1,1) with an asymmetric response to negative return shocks.
{#fun qlGJRGARCHModel as gJRGARCHModel{withGenStochasticProcess*`GJRGARCHProcess',preErrorCheck-`String'errorCheck*-}->`GJRGARCHModel'peekGJRGARCHModel*#}

-- |Heston stochastic-volatility model, calibrated from a 'HestonProcess'.
{#fun qlHestonModel as hestonModel{withHestonProcess*`GenHestonProcess hp',preErrorCheck-`String'errorCheck*-}->`HestonModel'peekHestonModel*#}

-- |Pseudo-random Mersenne-Twister Brownian increments for SLV Monte-Carlo calibration. Use a
-- fixed nonzero @seed@ for reproducible calibration output; QuantLib treats zero as entropy.
{#fun qlMTBrownianGeneratorFactory as mtBrownianGeneratorFactory{fromIntegral`Word' -- ^seed
  ,preErrorCheck-`String'errorCheck*-}->`BrownianGeneratorFactory'peekBrownianGeneratorFactory*#}

-- |Low-discrepancy Sobol Brownian increments for SLV Monte-Carlo calibration. Supply a fixed
-- nonzero @seed@ to make the resulting leverage function reproducible.
{#fun qlSobolBrownianGeneratorFactory as sobolBrownianGeneratorFactory{fromEnumC`SobolBrownianOrdering' -- ^ordering
  ,fromIntegral`Word' -- ^seed
  ,fromEnumC`SobolDirectionIntegers' -- ^directionIntegers
  ,preErrorCheck-`String'errorCheck*-}->`BrownianGeneratorFactory'peekBrownianGeneratorFactory*#}

-- |Monte-Carlo calibration of a Heston stochastic-local-volatility leverage function. The
-- trailing arguments mirror QuantLib's defaults explicitly; @mandatoryDates@ are inserted into
-- the calibration time grid.
{#fun qlHestonSLVMCModel as hestonSLVMCModel{withGenLocalVolTermStructure*`GenLocalVolTermStructure lv' -- ^localVol
  ,withHestonModel*`GenHestonModel hm' -- ^hestonModel
  ,withBrownianGeneratorFactory*`BrownianGeneratorFactory' -- ^brownianGeneratorFactory
  ,withDay*`Day' -- ^endDate
  ,fromIntegral`Word' -- ^timeStepsPerYear
  ,fromIntegral`Word' -- ^nBins
  ,fromIntegral`Word' -- ^calibrationPaths
  ,withDayArray*`[Day]'& -- ^mandatoryDates
  ,`Double' -- ^mixingFactor
  ,preErrorCheck-`String'errorCheck*-}->`HestonSLVMCModel'peekHestonSLVMCModel*#}

-- |Forces MC calibration if necessary and returns its local-volatility leverage function.
{#fun qlHestonSLVMCModelLeverageFunction as hestonSLVMCLeverageFunction{withHestonSLVMCModel*`HestonSLVMCModel' -- ^model
  ,preErrorCheck-`String'errorCheck*-}->`LocalVolTermStructure'peekLocalVolTermStructure*#}

-- |Fokker--Planck finite-difference calibration of a Heston stochastic-local-volatility
-- leverage function. @logging@ retains diagnostic density snapshots for
-- 'hestonSLVFDMLogEntries'; @mandatoryDates@ are added to its adaptive time grid.
hestonSLVFDMModel :: GenLocalVolTermStructure lv -> GenHestonModel hm -> Day
  -> HestonSLVFokkerPlanckFdmParams -> Bool -> [Day] -> Double -> IO HestonSLVFDMModel
hestonSLVFDMModel localVol model endDate p logging mandatoryDates mixingFactor =
  hestonSLVFDMModelRaw localVol model endDate
    (hestonSLVXGrid p) (hestonSLVVGrid p) (hestonSLVTMaxStepsPerYear p) (hestonSLVTMinStepsPerYear p)
    (hestonSLVTStepNumberDecay p) (hestonSLVNRannacherTimeSteps p) (hestonSLVPredictionCorrectionSteps p)
    (hestonSLVX0Density p) (hestonSLVLocalVolEpsProb p) (hestonSLVMaxIntegrationIterations p)
    (hestonSLVVLowerEps p) (hestonSLVVUpperEps p) (hestonSLVVMin p) (hestonSLVV0Density p)
    (hestonSLVVLowerBoundDensity p) (hestonSLVVUpperBoundDensity p) (hestonSLVLeverageFctPropEps p)
    (hestonSLVGreensAlgorithm p) (hestonSLVVarianceTransformation p) (hestonSLVSchemeDesc p)
    logging mandatoryDates mixingFactor
{#fun qlHestonSLVFDMModel as hestonSLVFDMModelRaw{withGenLocalVolTermStructure*`GenLocalVolTermStructure lv' -- ^localVol
  ,withHestonModel*`GenHestonModel hm' -- ^hestonModel
  ,withDay*`Day' -- ^endDate
  ,fromIntegral`Word' -- ^xGrid
  ,fromIntegral`Word' -- ^vGrid
  ,fromIntegral`Word' -- ^tMaxStepsPerYear
  ,fromIntegral`Word' -- ^tMinStepsPerYear
  ,`Double' -- ^tStepNumberDecay
  ,fromIntegral`Word' -- ^nRannacherTimeSteps
  ,fromIntegral`Word' -- ^predictionCorrectionSteps
  ,`Double' -- ^x0Density
  ,`Double' -- ^localVolEpsProb
  ,fromIntegral`Word' -- ^maxIntegrationIterations
  ,`Double' -- ^vLowerEps
  ,`Double' -- ^vUpperEps
  ,`Double' -- ^vMin
  ,`Double' -- ^v0Density
  ,`Double' -- ^vLowerBoundDensity
  ,`Double' -- ^vUpperBoundDensity
  ,`Double' -- ^leverageFctPropEps
  ,fromEnumC`HestonSLVGreensAlgorithm' -- ^greensAlgorithm
  ,fromEnumC`HestonSLVVarianceTransformation' -- ^trafoType
  ,withFdmSchemeDesc*`FdmScheme' -- ^schemeDesc
  ,`Bool' -- ^logging
  ,withDayArray*`[Day]'& -- ^mandatoryDates
  ,`Double' -- ^mixingFactor
  ,preErrorCheck-`String'errorCheck*-}->`HestonSLVFDMModel'peekHestonSLVFDMModel*#}

-- |Forces FDM calibration if necessary and returns its local-volatility leverage function.
{#fun qlHestonSLVFDMModelLeverageFunction as hestonSLVFDMLeverageFunction{withHestonSLVFDMModel*`HestonSLVFDMModel' -- ^model
  ,preErrorCheck-`String'errorCheck*-}->`LocalVolTermStructure'peekLocalVolTermStructure*#}

-- |Copies retained FDM density diagnostics. Returns @[]@ when the model was built with
-- @logging = False@. Calling this makes one fresh QuantLib diagnostic calculation, then decodes
-- its owned snapshot without retaining the model's mesh objects.
hestonSLVFDMLogEntries :: HestonSLVFDMModel -> IO [HestonSLVFDMLogEntry]
hestonSLVFDMLogEntries model = do
  snapshot <- hestonSLVFDMLogEntriesSnapshot model
  let n = hestonSLVFDMLogEntriesSize snapshot
  mapM (hestonSLVFDMLogEntry snapshot) (genericTake n [0 ..])

hestonSLVFDMLogEntry :: HestonSLVFDMLogEntries -> Word -> IO HestonSLVFDMLogEntry
hestonSLVFDMLogEntry snapshot i = do
  let t = hestonSLVFDMLogEntriesTime snapshot i
  x <- hestonSLVFDMLogEntriesSpotGrid snapshot i
  v <- hestonSLVFDMLogEntriesVarianceGrid snapshot i
  (r, c, d) <- hestonSLVFDMLogEntriesDensity snapshot i
  pure $ HestonSLVFDMLogEntry t x v (RealMatrix r c d)

{#fun qlHestonSLVFDMModelLogEntries as hestonSLVFDMLogEntriesSnapshot{withHestonSLVFDMModel*`HestonSLVFDMModel',preErrorCheck-`String'errorCheck*-}->`HestonSLVFDMLogEntries'peekHestonSLVFDMLogEntries*#}
{#fun pure qlHestonSLVFDMLogEntriesSize as hestonSLVFDMLogEntriesSize{withHestonSLVFDMLogEntries*`HestonSLVFDMLogEntries'}->`Word'fromIntegral#}
{#fun pure qlHestonSLVFDMLogEntriesTime as hestonSLVFDMLogEntriesTime{withHestonSLVFDMLogEntries*`HestonSLVFDMLogEntries',fromIntegral`Word'}->`Double'#}
{#fun qlHestonSLVFDMLogEntriesSpotGrid as hestonSLVFDMLogEntriesSpotGrid{withHestonSLVFDMLogEntries*`HestonSLVFDMLogEntries',fromIntegral`Word',preArray-`RealVector'&peekRealVector*}->`()'#}
{#fun qlHestonSLVFDMLogEntriesVarianceGrid as hestonSLVFDMLogEntriesVarianceGrid{withHestonSLVFDMLogEntries*`HestonSLVFDMLogEntries',fromIntegral`Word',preArray-`RealVector'&peekRealVector*}->`()'#}
{#fun qlHestonSLVFDMLogEntriesDensity as hestonSLVFDMLogEntriesDensity{withHestonSLVFDMLogEntries*`HestonSLVFDMLogEntries',fromIntegral`Word',prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`RealVector'&peekRealVector*}->`()'#}

-- |Single-factor Hull-White (extended Vasicek) short-rate model: dr = (theta(t) - a r) dt + sigma dW, fitted to the given term structure.
{#fun qlHullWhite as hullWhite{withYieldTermStructure*`GenYieldTermStructure y',`Double' -- ^y
  ,`Double' -- ^sigma
  ,preErrorCheck-`String'errorCheck*-}->`HullWhite'peekHullWhite*#}

-- |Futures convexity bias (difference between futures implied rate and forward rate), per G. Kirikos, D. Novak, \"Convexity Conundrums\", Risk Magazine, March 1997. @t@/@T@ are in yearfraction using the deposit day counter, @futurePrice@ is the futures' market price.
-- Not 'pure': 'HullWhite.convexityBias' can throw ('QL_REQUIRE' on its inputs), and letting a C++
-- exception unwind across the FFI boundary from an 'unsafePerformIO'-backed pure binding is undefined
-- behavior, so this needs the same 'char **e'/'preErrorCheck' error channel as any other throwing call.
{#fun qlHullWhiteConvexityBias as convexityBias{`Double' -- ^futurePrice
  ,`Double' -- ^t
  ,`Double' -- ^T
  ,`Double' -- ^sigma
  ,`Double' -- ^a
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Marks the reversion (@a@) fixed and volatility (@sigma@) free for 'calibrate''s @fixParameters@ argument. Mirrors @HullWhite::FixedReversion()@.
fixedReversion :: [Bool]
fixedReversion = [True, False]
-- |One-factor GSR model (formulated in the forward measure), with an initial volatility and
-- piecewise-constant changes at the given dates, plus a single constant reversion.
gsr :: GenYieldTermStructure y -> GenQuote q1 -> [(Day, GenQuote q1)] -> GenQuote q2 -> Double -> IO Gsr
gsr ts initialVol subsequentVols reversion horizon =
  qlGsr ts dates (initialVol : vols) reversion horizon
  where (dates, vols) = unzip subsequentVols
{#fun qlGsr{withYieldTermStructure*`GenYieldTermStructure y',withDayArray*`[Day]'& -- ^volstepdates
  ,withQuoteArray*`[GenQuote q1]'& -- ^volatilities
  ,withQuote*`GenQuote q2' -- ^reversion
  ,`Double' -- ^T
  ,preErrorCheck-`String'errorCheck*-}->`Gsr'peekGsr*#}

-- |Volatility step values, as calibrated so far.
{#fun qlGsrVolatility as gsrVolatility{withGenCalibratedModel*`Gsr',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Iteratively calibrates the volatility step values, one at a time, to the given helpers (assumed to have step dates matching the model's volatility step dates).
{#fun qlGsrCalibrateVolatilitiesIterative as calibrateVolatilitiesIterative{withGenCalibratedModel*`Gsr',withBlackCalibrationHelperArray*`[GenBlackCalibrationHelper bch]'&,withOptimizationMethod*`OptimizationMethod',withEndCriteria*`EndCriteria'
  ,withMaybeConstraint*`Maybe Constraint'
  ,withDoubleArray*`[Double]'&
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Markov-functional interest-rate model, calibrated to a swaption volatility cube against @swapIndexBase@.
markovFunctional :: GenYieldTermStructure y -> Double -- ^reversion
  -> Double -- ^initial volatility
  -> [(Day, Double)] -- ^subsequent volatility steps
  -> SwaptionVolatilityStructure
  -> NonEmpty (Day, (Word, TimeUnit)) -- ^swaption expiry/tenor calibration points
  -> GenSwapIndex sidx -- ^swapIndexBase
  -> Word -- ^yGridPoints
  -> IO MarkovFunctional
markovFunctional ts reversion initialVol steps svol points = qlMarkovFunctional ts reversion dates (initialVol : vols) svol expiries tq tu
  where (dates, vols) = unzip steps
        (expiries, tenors) = unzip (toList points)
        (tq, tu) = unzip tenors
{#fun qlMarkovFunctional{withYieldTermStructure*`GenYieldTermStructure y',`Double'
  ,withDayArray*`[Day]'&,withDoubleArray*`[Double]'&
  ,withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,withDayArray*`[Day]'&
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&
  ,withSwapIndex*`GenSwapIndex sidx'
  ,fromIntegral`Word'
  ,preErrorCheck-`String'errorCheck*-}->`MarkovFunctional'peekMarkovFunctional*#}

-- |Markov-functional interest-rate model, calibrated to a caplet volatility structure against @iborIndex@.
markovFunctionalCaplet :: GenYieldTermStructure y -> Double -> Double -> [(Day, Double)]
  -> OptionletVolatilityStructure -> NonEmpty Day -> GenIborIndex ibor -> Word -> IO MarkovFunctional
markovFunctionalCaplet ts reversion initialVol steps capletVol expiries ibor gridPoints =
  qlMarkovFunctionalCaplet ts reversion dates (initialVol : vols) capletVol (toList expiries) ibor gridPoints
  where (dates, vols) = unzip steps
{#fun qlMarkovFunctionalCaplet{withYieldTermStructure*`GenYieldTermStructure y',`Double' -- ^reversion
  ,withDayArray*`[Day]'& -- ^volstepdates
  ,withDoubleArray*`[Double]'& -- ^volatilities
  ,withOptionletVolatilityStructure*`OptionletVolatilityStructure' -- ^capletVol
  ,withDayArray*`[Day]'& -- ^capletExpiries
  ,withIborIndex*`GenIborIndex ibor' -- ^iborIndex
  ,fromIntegral`Word' -- ^yGridPoints
  ,preErrorCheck-`String'errorCheck*-}->`MarkovFunctional'peekMarkovFunctional*#}

-- |Volatility step values, as calibrated so far.
{#fun qlMarkovFunctionalVolatility as markovFunctionalVolatility{withGenCalibratedModel*`MarkovFunctional',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Variance Gamma model for the underlying's log-return process (Madan-Carr-Chang).
{#fun qlVarianceGammaModel as varianceGammaModel{withGenStochasticProcess1D*`VarianceGammaProcess',preErrorCheck-`String'errorCheck*-}->`CalibratedModel'peekCalibratedModel*#}

-- |Vasicek short-rate model: dr = a(b - r) dt + sigma dW, with an optional risk premium @lambda@.
{#fun qlVasicek as vasicek{`Double' -- ^r0
  ,`Double' -- ^a
  ,`Double' -- ^b
  ,`Double' -- ^sigma
  ,`Double' -- ^lambda
  ,preErrorCheck-`String'errorCheck*-}->`OneFactorAffineModel'peekOneFactorAffineModel*#}

-- |Libor market (BGM) forward-rate model, built from a 'LiborForwardModelProcess' plus volatility and correlation models.
{#fun qlLiborForwardModel as liborForwardModel{withGenStochasticProcess*`LiborForwardModelProcess',withLmVolatilityModel*`LmVolatilityModel',withLmCorrelationModel*`LmCorrelationModel',preErrorCheck-`String'errorCheck*-}->`LiborForwardModel'peekLiborForwardModel*#}

-- |Hull-White caplet-volatility parameterization for a Libor forward model. The correlation
-- matrix and factor count are explicit, mirroring QuantLib's defaulted constructor arguments;
-- pass an empty matrix and @1@ for its standard one-factor default.
lfmHullWhiteParameterization :: LiborForwardModelProcess -> GenOptionletVolatilityStructure ov
  -> Matrix Double -- ^correlation
  -> Word -- ^factors
  -> IO LfmHullWhiteParameterization
lfmHullWhiteParameterization process capletVol (Matrix rows cols values) factors = qlLfmHullWhiteParameterization process capletVol rows cols values factors
{#fun qlLfmHullWhiteParameterization{withGenStochasticProcess*`LiborForwardModelProcess' -- ^process
  ,withOptionletVolatilityStructure*`GenOptionletVolatilityStructure ov' -- ^capletVol
  ,fromIntegral`Word' -- ^correlationRows
  ,fromIntegral`Word' -- ^correlationColumns
  ,withDoubleArrayRaw*`[Double]' -- ^correlation
  ,fromIntegral`Word' -- ^factors
  ,preErrorCheck-`String'errorCheck*-}->`LfmHullWhiteParameterization'peekLfmHullWhiteParameterization*#}

-- |Instantaneous covariance matrix at @t@ for the supplied forward-rate state @x@.
lfmHullWhiteCovariance :: LfmHullWhiteParameterization -> Double -> [Double] -> IO (Matrix Double)
lfmHullWhiteCovariance p t x = toMatrixDouble <$> qlLfmHullWhiteCovariance p t x
  where toMatrixDouble (r, c, d) = Matrix r c d
{#fun qlLfmHullWhiteCovariance{withStandalone*`LfmHullWhiteParameterization' -- ^parameterization
  ,`Double' -- ^t
  ,withDoubleArray*`[Double]'& -- ^x
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Calibrate to a set of market instruments (caps/swaptions)
-- An additional constraint can be passed which must be satisfied in addition to the constraints of the model.
calibrate :: GenCalibratedModel m -> NonEmpty (GenCalibrationHelper ch, Double) -- ^(instrument, weight)
  -> OptimizationMethod -> EndCriteria -> Maybe Constraint
  -> [Bool] -- ^fixParameters, e.g. 'fixedReversion'; @[]@ leaves nothing fixed
  -> IO ()
calibrate m h o e c fp = qlCalibratedModelCalibrate m hh hw o e c fp where (hh, hw) = unzip (toList h)
{#fun qlCalibratedModelCalibrate{withCalibratedModel*`GenCalibratedModel m',withCalibrationHelperArray*`[GenCalibrationHelper ch]'&,withDoubleArray*`[Double]'&
  ,withOptimizationMethod*`OptimizationMethod',withEndCriteria*`EndCriteria',withMaybeConstraint*`Maybe Constraint',withBoolArray*`[Bool]'&,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Objective function value at @params@ for the given calibration instruments.
{#fun qlCalibratedModelValue as value{withCalibratedModel*`GenCalibratedModel m',withDoubleArray*`[Double]'&,withCalibrationHelperArray*`[GenCalibrationHelper ch]'&,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Calibration helper for an at-the-money interest-rate cap.
{#fun qlCapHelper as capHelper{fromEnumQuantity`(Word,TimeUnit)'& -- ^length
  ,withQuote*`GenQuote q' -- ^volatility
  ,withIborIndex*`GenIborIndex ibor',`Frequency' -- ^fixedLegFrequency
  ,withDayCounter*`DayCounter',`Bool' -- ^includeFirstSwaplet
  ,withYieldTermStructure*`GenYieldTermStructure y',`CalibrationErrorType'
  ,`VolatilityType' -- ^type
  ,`Double' -- ^shift
  ,preErrorCheck-`String'errorCheck*-}->`BlackCalibrationHelper'peekBlackCalibrationHelper*#}

-- |Calibration helper for the Heston model, from a European option's market volatility.
{#fun qlHestonModelHelper as hestonModelHelper{fromEnumQuantity`(Word,TimeUnit)'& -- ^maturity
  ,withCalendar*`Calendar',withQuote*`GenQuote q1' -- ^s0
  ,`Double' -- ^strikePrice
  ,withQuote*`GenQuote q2' -- ^volatility
  ,withYieldTermStructure*`GenYieldTermStructure y1' -- ^riskFreeRate
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^dividendYield
  ,`CalibrationErrorType',preErrorCheck-`String'errorCheck*-}->`BlackCalibrationHelper'peekBlackCalibrationHelper*#}

-- |Calibration helper for a European swaption, with the exercise given as a maturity 'Period' from today.
{#fun qlSwaptionHelper as swaptionHelper{fromEnumQuantity`(Word,TimeUnit)'& -- ^maturity
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^length
  ,withQuote*`GenQuote q' -- ^maturity
  ,withIborIndex*`GenIborIndex ibor',fromEnumQuantity`(Word,TimeUnit)'& -- ^fixedLegTenor
  ,withDayCounter*`DayCounter' -- ^fixedLegDayCounter
  ,withDayCounter*`DayCounter' -- ^floatingLegDayCounter
  ,withYieldTermStructure*`GenYieldTermStructure y',`CalibrationErrorType'
  ,fromMaybeDouble`Maybe Double' -- ^strike
  ,`Double' -- ^nominal
  ,`VolatilityType' -- ^type
  ,`Double' -- ^shift
  ,fromMaybeInt`Maybe Word' -- ^settlementDays
  ,`RateAveragingType' -- ^averagingMethod
  ,preErrorCheck-`String'errorCheck*-}->`SwaptionHelper'peekSwaptionHelper*#}

-- |Like 'swaptionHelper', but the option's exercise is given as an explicit date rather than a maturity 'Period'.
{#fun qlSwaptionHelperFromDate as swaptionHelperFromDate{withDay*`Day' -- ^exerciseDate
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^length
  ,withQuote*`GenQuote q' -- ^maturity
  ,withIborIndex*`GenIborIndex ibor',fromEnumQuantity`(Word,TimeUnit)'& -- ^fixedLegTenor
  ,withDayCounter*`DayCounter' -- ^fixedLegDayCounter
  ,withDayCounter*`DayCounter' -- ^floatingLegDayCounter
  ,withYieldTermStructure*`GenYieldTermStructure y',`CalibrationErrorType'
  ,fromMaybeDouble`Maybe Double' -- ^strike
  ,`Double' -- ^nominal
  ,`VolatilityType' -- ^type
  ,`Double' -- ^shift
  ,fromMaybeInt`Maybe Word' -- ^settlementDays
  ,`RateAveragingType' -- ^averagingMethod
  ,preErrorCheck-`String'errorCheck*-}->`SwaptionHelper'peekSwaptionHelper*#}

-- |Like 'swaptionHelper', but both the option's exercise and the underlying swap's end are given as explicit dates.
{#fun qlSwaptionHelperFromDates as swaptionHelperFromDates{withDay*`Day' -- ^exerciseDate
  ,withDay*`Day' -- ^endDate
  ,withQuote*`GenQuote q' -- ^maturity
  ,withIborIndex*`GenIborIndex ibor',fromEnumQuantity`(Word,TimeUnit)'& -- ^fixedLegTenor
  ,withDayCounter*`DayCounter' -- ^fixedLegDayCounter
  ,withDayCounter*`DayCounter' -- ^floatingLegDayCounter
  ,withYieldTermStructure*`GenYieldTermStructure y',`CalibrationErrorType'
  ,fromMaybeDouble`Maybe Double' -- ^strike
  ,`Double' -- ^nominal
  ,`VolatilityType' -- ^type
  ,`Double' -- ^shift
  ,fromMaybeInt`Maybe Word' -- ^settlementDays
  ,`RateAveragingType' -- ^averagingMethod
  ,preErrorCheck-`String'errorCheck*-}->`SwaptionHelper'peekSwaptionHelper*#}

-- |Upstream's own vanilla swap underlying this helper's swaption.
{#fun qlSwaptionHelperUnderlying as swaptionHelperUnderlying{withSwaptionHelper*`SwaptionHelper',preErrorCheck-`String'errorCheck*-}->`FixedVsFloatingSwap'peekFixedVsFloatingSwap*#}

-- |The 'QuantLib.Instrument.Swap.Swaption' this helper prices internally to compute 'modelValue'.
{#fun qlSwaptionHelperSwaption as swaptionHelperSwaption{withSwaptionHelper*`SwaptionHelper',preErrorCheck-`String'errorCheck*-}->`Swaption'peekSwaption*#}

-- |Times relevant to pricing this calibration helper's instrument, to be added to the model's evolution time grid.
{#fun qlBlackCalibrationHelperTimes as times{withBlackCalibrationHelper*`GenBlackCalibrationHelper bch',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Returns array of arguments on which calibration is done.
{#fun qlCalibratedModelParams as params{withCalibratedModel*`GenCalibratedModel m',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Black price given a volatility.
{#fun qlBlackCalibrationHelperBlackPrice as blackPrice{withBlackCalibrationHelper*`GenBlackCalibrationHelper bch',`Double' -- ^volatility
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the error resulting from the model valuation
{#fun qlBlackCalibrationHelperCalibrationError as calibrationError{withBlackCalibrationHelper*`GenBlackCalibrationHelper bch',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Black volatility implied by the model.
{#fun qlBlackCalibrationHelperImpliedVolatility as impliedVolatility{withBlackCalibrationHelper*`GenBlackCalibrationHelper bch',`Double' -- ^targetValue
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxEvaluations
  ,`Double' -- ^minVol
  ,`Double' -- ^maxVol
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the actual price of the instrument (from volatility)
{#fun qlBlackCalibrationHelperMarketValue as marketValue{withBlackCalibrationHelper*`GenBlackCalibrationHelper bch',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the price of the instrument according to the model
{#fun qlBlackCalibrationHelperModelValue as modelValue{withBlackCalibrationHelper*`GenBlackCalibrationHelper bch',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The quoted market volatility this helper was built with.
{#fun qlBlackCalibrationHelperVolatility as volatility{withBlackCalibrationHelper*`GenBlackCalibrationHelper bch',preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

-- |Sets the pricing engine used to compute this calibration helper's model value.
{#fun qlBlackCalibrationHelperSetPricingEngine as setPricingEngine{withBlackCalibrationHelper*`GenBlackCalibrationHelper bch',withPricingEngine*`PricingEngine',preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
