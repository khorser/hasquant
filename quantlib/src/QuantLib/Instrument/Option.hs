{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument.Option
  (
    barrierOption
  , impliedVolatility
  , dividendVanillaOption
  , impliedVolatility'
  , forwardVanillaOption
  , delta1
  , delta2
  , gamma1
  , gamma2
  , margrabeOption
  , delta
  , dividendRho
  , gamma
  , multiAssetOption
  , rho
  , theta
  , vega
  , delta'
  , deltaForward
  , dividendRho'
  , elasticity
  , gamma'
  , itmCashProbability
  , oneAssetOption
  , rho'
  , strikeSensitivity
  , theta'
  , thetaPerDay
  , vega'
  , qlambda
  , qrho
  , quantoBarrierOption
  , qvega
  , qlambda'
  , qrho'
  , quantoForwardVanillaOption
  , qvega'
  , qlambda''
  , qrho''
  , quantoVanillaOption
  , qvega''
  , impliedVolatility''
  , vanillaOption
  , dividendBarrierOption
  , basketOption
  , himalayaOption
  , pagodaOption
  , spreadOption
  , cliquetOption
  , continuousAveragingAsianOption
  , continuousFixedLookbackOption
  , continuousFloatingLookbackOption
  , discreteAveragingAsianOption
  , vanillaStorageOption
  , vanillaSwingOption
  , europeanOption
  )
where

import QuantLib.Instrument.AverageType
import QuantLib.Instrument.BarrierType
import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

barrierOption :: BarrierType -- ^barrierType
  -> Double -- ^barrier
  -> Double -- ^rebate
  -> StrikedTypePayoff -- ^payoff
  -> Exercise -- ^exercise
  -> IO BarrierOption
barrierOption = $(ffiCall 'barrierOption) c_barrierOption

foreign import ccall safe "ql.h qlBarrierOption"
  c_barrierOption :: CInt -> CDouble -> CDouble -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CBarrierOption)

-- |/Warning/ see VanillaOption for notes on implied-volatility calculation.
impliedVolatility :: BarrierOption
  -> Double -- ^price
  -> GeneralizedBlackScholesProcess -- ^process
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> Double -- ^minVol
  -> Double -- ^maxVol
  -> IO Double
impliedVolatility = $(ffiCallX 'impliedVolatility) c_impliedVolatility

foreign import ccall safe "ql.h qlBarrierOptionImpliedVolatility"
  c_impliedVolatility :: Ptr CBarrierOption -> CDouble -> Ptr CGeneralizedBlackScholesProcess -> CDouble -> CUInt -> CDouble -> CDouble -> Ptr CString -> IO CDouble

dividendVanillaOption :: StrikedTypePayoff -- ^payoff
  -> Exercise -- ^exercise
  -> [Day] -- ^dividendDates
  -> [Double] -- ^dividends
  -> IO DividendVanillaOption
dividendVanillaOption = $(ffiCall 'dividendVanillaOption) c_dividendVanillaOption

foreign import ccall safe "ql.h qlDividendVanillaOption"
  c_dividendVanillaOption :: Ptr CStrikedTypePayoff -> Ptr CExercise -> CUInt -> Ptr CDate -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CDividendVanillaOption)

-- |/Warning/ see VanillaOption for notes on implied-volatility calculation.
impliedVolatility' :: DividendVanillaOption
  -> Double -- ^price
  -> GeneralizedBlackScholesProcess -- ^process
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> Double -- ^minVol
  -> Double -- ^maxVol
  -> IO Double
impliedVolatility' = $(ffiCallX 'impliedVolatility') c_impliedVolatility'

foreign import ccall safe "ql.h qlDividendVanillaOptionImpliedVolatility"
  c_impliedVolatility' :: Ptr CDividendVanillaOption -> CDouble -> Ptr CGeneralizedBlackScholesProcess -> CDouble -> CUInt -> CDouble -> CDouble -> Ptr CString -> IO CDouble

forwardVanillaOption :: Double -- ^moneyness
  -> Day -- ^resetDate
  -> StrikedTypePayoff -- ^payoff
  -> Exercise -- ^exercise
  -> IO ForwardVanillaOption
forwardVanillaOption = $(ffiCall 'forwardVanillaOption) c_forwardVanillaOption

foreign import ccall safe "ql.h qlForwardVanillaOption"
  c_forwardVanillaOption :: CDouble -> CDate -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CForwardVanillaOption)

delta1 :: MargrabeOption -> IO Double
delta1 = $(ffiCallX 'delta1) c_delta1

foreign import ccall safe "ql.h qlMargrabeOptionDelta1"
  c_delta1 :: Ptr CMargrabeOption -> Ptr CString -> IO CDouble

delta2 :: MargrabeOption -> IO Double
delta2 = $(ffiCallX 'delta2) c_delta2

foreign import ccall safe "ql.h qlMargrabeOptionDelta2"
  c_delta2 :: Ptr CMargrabeOption -> Ptr CString -> IO CDouble

gamma1 :: MargrabeOption -> IO Double
gamma1 = $(ffiCallX 'gamma1) c_gamma1

foreign import ccall safe "ql.h qlMargrabeOptionGamma1"
  c_gamma1 :: Ptr CMargrabeOption -> Ptr CString -> IO CDouble

gamma2 :: MargrabeOption -> IO Double
gamma2 = $(ffiCallX 'gamma2) c_gamma2

foreign import ccall safe "ql.h qlMargrabeOptionGamma2"
  c_gamma2 :: Ptr CMargrabeOption -> Ptr CString -> IO CDouble

margrabeOption :: Int -- ^Q1
  -> Int -- ^Q2
  -> Exercise
  -> IO MargrabeOption
margrabeOption = $(ffiCall 'margrabeOption) c_margrabeOption

foreign import ccall safe "ql.h qlMargrabeOption"
  c_margrabeOption :: CInt -> CInt -> Ptr CExercise -> Ptr CString -> IO (Ptr CMargrabeOption)

delta :: MultiAssetOption -> IO Double
delta = $(ffiCallX 'delta) c_delta

foreign import ccall safe "ql.h qlMultiAssetOptionDelta"
  c_delta :: Ptr CMultiAssetOption -> Ptr CString -> IO CDouble

dividendRho :: MultiAssetOption -> IO Double
dividendRho = $(ffiCallX 'dividendRho) c_dividendRho

foreign import ccall safe "ql.h qlMultiAssetOptionDividendRho"
  c_dividendRho :: Ptr CMultiAssetOption -> Ptr CString -> IO CDouble

gamma :: MultiAssetOption -> IO Double
gamma = $(ffiCallX 'gamma) c_gamma

foreign import ccall safe "ql.h qlMultiAssetOptionGamma"
  c_gamma :: Ptr CMultiAssetOption -> Ptr CString -> IO CDouble

multiAssetOption :: Payoff -> Exercise -> IO MultiAssetOption
multiAssetOption = $(ffiCall 'multiAssetOption) c_multiAssetOption

foreign import ccall safe "ql.h qlMultiAssetOption"
  c_multiAssetOption :: Ptr CPayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CMultiAssetOption)

rho :: MultiAssetOption -> IO Double
rho = $(ffiCallX 'rho) c_rho

foreign import ccall safe "ql.h qlMultiAssetOptionRho"
  c_rho :: Ptr CMultiAssetOption -> Ptr CString -> IO CDouble

theta' :: MultiAssetOption -> IO Double
theta' = $(ffiCallX 'theta') c_theta'

foreign import ccall safe "ql.h qlMultiAssetOptionTheta"
  c_theta' :: Ptr CMultiAssetOption -> Ptr CString -> IO CDouble

vega :: MultiAssetOption -> IO Double
vega = $(ffiCallX 'vega) c_vega

foreign import ccall safe "ql.h qlMultiAssetOptionVega"
  c_vega :: Ptr CMultiAssetOption -> Ptr CString -> IO CDouble

delta' :: OneAssetOption -> IO Double
delta' = $(ffiCallX 'delta') c_delta'

foreign import ccall safe "ql.h qlOneAssetOptionDelta"
  c_delta' :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

deltaForward :: OneAssetOption -> IO Double
deltaForward = $(ffiCallX 'deltaForward) c_deltaForward

foreign import ccall safe "ql.h qlOneAssetOptionDeltaForward"
  c_deltaForward :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

dividendRho' :: OneAssetOption -> IO Double
dividendRho' = $(ffiCallX 'dividendRho') c_dividendRho'

foreign import ccall safe "ql.h qlOneAssetOptionDividendRho"
  c_dividendRho' :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

elasticity :: OneAssetOption -> IO Double
elasticity = $(ffiCallX 'elasticity) c_elasticity

foreign import ccall safe "ql.h qlOneAssetOptionElasticity"
  c_elasticity :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

gamma' :: OneAssetOption -> IO Double
gamma' = $(ffiCallX 'gamma') c_gamma'

foreign import ccall safe "ql.h qlOneAssetOptionGamma"
  c_gamma' :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

itmCashProbability :: OneAssetOption
  -> IO Double
itmCashProbability = $(ffiCallX 'itmCashProbability) c_itmCashProbability

foreign import ccall safe "ql.h qlOneAssetOptionItmCashProbability"
  c_itmCashProbability :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

oneAssetOption :: Payoff -> Exercise -> IO OneAssetOption
oneAssetOption = $(ffiCall 'oneAssetOption) c_oneAssetOption

foreign import ccall safe "ql.h qlOneAssetOption"
  c_oneAssetOption :: Ptr CPayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr COneAssetOption)

rho' :: OneAssetOption -> IO Double
rho' = $(ffiCallX 'rho') c_rho'

foreign import ccall safe "ql.h qlOneAssetOptionRho"
  c_rho' :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

strikeSensitivity :: OneAssetOption -> IO Double
strikeSensitivity = $(ffiCallX 'strikeSensitivity) c_strikeSensitivity

foreign import ccall safe "ql.h qlOneAssetOptionStrikeSensitivity"
  c_strikeSensitivity :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

theta :: OneAssetOption -> IO Double
theta = $(ffiCallX 'theta) c_theta

foreign import ccall safe "ql.h qlOneAssetOptionTheta"
  c_theta :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

thetaPerDay :: OneAssetOption -> IO Double
thetaPerDay = $(ffiCallX 'thetaPerDay) c_thetaPerDay

foreign import ccall safe "ql.h qlOneAssetOptionThetaPerDay"
  c_thetaPerDay :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

vega' :: OneAssetOption -> IO Double
vega' = $(ffiCallX 'vega') c_vega'

foreign import ccall safe "ql.h qlOneAssetOptionVega"
  c_vega' :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

qlambda :: QuantoBarrierOption -> IO Double
qlambda = $(ffiCallX 'qlambda) c_qlambda

foreign import ccall safe "ql.h qlQuantoBarrierOptionQlambda"
  c_qlambda :: Ptr CQuantoBarrierOption -> Ptr CString -> IO CDouble

qrho :: QuantoBarrierOption -> IO Double
qrho = $(ffiCallX 'qrho) c_qrho

foreign import ccall safe "ql.h qlQuantoBarrierOptionQrho"
  c_qrho :: Ptr CQuantoBarrierOption -> Ptr CString -> IO CDouble

quantoBarrierOption :: BarrierType -- ^barrierType
  -> Double -- ^barrier
  -> Double -- ^rebate
  -> StrikedTypePayoff -- ^payoff
  -> Exercise -- ^exercise
  -> IO QuantoBarrierOption
quantoBarrierOption = $(ffiCall 'quantoBarrierOption) c_quantoBarrierOption

foreign import ccall safe "ql.h qlQuantoBarrierOption"
  c_quantoBarrierOption :: CInt -> CDouble -> CDouble -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CQuantoBarrierOption)

qvega :: QuantoBarrierOption -> IO Double
qvega = $(ffiCallX 'qvega) c_qvega

foreign import ccall safe "ql.h qlQuantoBarrierOptionQvega"
  c_qvega :: Ptr CQuantoBarrierOption -> Ptr CString -> IO CDouble

qlambda' :: QuantoForwardVanillaOption -> IO Double
qlambda' = $(ffiCallX 'qlambda') c_qlambda'

foreign import ccall safe "ql.h qlQuantoForwardVanillaOptionQlambda"
  c_qlambda' :: Ptr CQuantoForwardVanillaOption -> Ptr CString -> IO CDouble

qrho' :: QuantoForwardVanillaOption -> IO Double
qrho' = $(ffiCallX 'qrho') c_qrho'

foreign import ccall safe "ql.h qlQuantoForwardVanillaOptionQrho"
  c_qrho' :: Ptr CQuantoForwardVanillaOption -> Ptr CString -> IO CDouble

quantoForwardVanillaOption :: Double -- ^moneyness
  -> Day -- ^resetDate
  -> StrikedTypePayoff
  -> Exercise
  -> IO QuantoForwardVanillaOption
quantoForwardVanillaOption = $(ffiCall 'quantoForwardVanillaOption) c_quantoForwardVanillaOption

foreign import ccall safe "ql.h qlQuantoForwardVanillaOption"
  c_quantoForwardVanillaOption :: CDouble -> CDate -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CQuantoForwardVanillaOption)

qvega' :: QuantoForwardVanillaOption -> IO Double
qvega' = $(ffiCallX 'qvega') c_qvega'

foreign import ccall safe "ql.h qlQuantoForwardVanillaOptionQvega"
  c_qvega' :: Ptr CQuantoForwardVanillaOption -> Ptr CString -> IO CDouble

qlambda'' :: QuantoVanillaOption -> IO Double
qlambda'' = $(ffiCallX 'qlambda'') c_qlambda''

foreign import ccall safe "ql.h qlQuantoVanillaOptionQlambda"
  c_qlambda'' :: Ptr CQuantoVanillaOption -> Ptr CString -> IO CDouble

qrho'' :: QuantoVanillaOption -> IO Double
qrho'' = $(ffiCallX 'qrho'') c_qrho''

foreign import ccall safe "ql.h qlQuantoVanillaOptionQrho"
  c_qrho'' :: Ptr CQuantoVanillaOption -> Ptr CString -> IO CDouble

quantoVanillaOption :: StrikedTypePayoff -> Exercise -> IO QuantoVanillaOption
quantoVanillaOption = $(ffiCall 'quantoVanillaOption) c_quantoVanillaOption

foreign import ccall safe "ql.h qlQuantoVanillaOption"
  c_quantoVanillaOption :: Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CQuantoVanillaOption)

qvega'' :: QuantoVanillaOption -> IO Double
qvega'' = $(ffiCallX 'qvega'') c_qvega''

foreign import ccall safe "ql.h qlQuantoVanillaOptionQvega"
  c_qvega'' :: Ptr CQuantoVanillaOption -> Ptr CString -> IO CDouble

-- |/Warning/ currently, this method returns the Black-Scholes implied volatility using analytic formulas for European options and a finite-difference method for American and Bermudan options. It will give unconsistent results if the pricing was performed with any other methods (such as jump-diffusion models.)Warningoptions with a gamma that changes sign (e.g., binary options) have values that are not monotonic in the volatility. In these cases, the calculation can fail and the result (if any) is almost meaningless. Another possible source of failure is to have a target value that is not attainable with any volatility, e.g., a target value lower than the intrinsic value in the case of American options.
impliedVolatility'' :: VanillaOption
  -> Double -- ^price
  -> GeneralizedBlackScholesProcess -- ^process
  -> Double -- ^accuracy
  -> Word -- ^maxEvaluations
  -> Double -- ^minVol
  -> Double -- ^maxVol
  -> IO Double
impliedVolatility'' = $(ffiCallX 'impliedVolatility'') c_impliedVolatility''

foreign import ccall safe "ql.h qlVanillaOptionImpliedVolatility"
  c_impliedVolatility'' :: Ptr CVanillaOption -> CDouble -> Ptr CGeneralizedBlackScholesProcess -> CDouble -> CUInt -> CDouble -> CDouble -> Ptr CString -> IO CDouble

vanillaOption :: StrikedTypePayoff -> Exercise -> IO VanillaOption
vanillaOption = $(ffiCall 'vanillaOption) c_vanillaOption

foreign import ccall safe "ql.h qlVanillaOption"
  c_vanillaOption :: Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CVanillaOption)

dividendBarrierOption :: BarrierType -- ^barrierType
  -> Double -- ^barrier
  -> Double -- ^rebate
  -> StrikedTypePayoff -- ^payoff
  -> Exercise -- ^exercise
  -> [Day] -- ^dividendDates
  -> [Double] -- ^dividends
  -> IO BarrierOption
dividendBarrierOption = $(ffiCall 'dividendBarrierOption) c_dividendBarrierOption

foreign import ccall safe "ql.h qlDividendBarrierOption"
  c_dividendBarrierOption :: CInt -> CDouble -> CDouble -> Ptr CStrikedTypePayoff -> Ptr CExercise -> CUInt -> Ptr CDate -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CBarrierOption)

basketOption :: BasketPayoff -> Exercise -> IO MultiAssetOption
basketOption = $(ffiCall 'basketOption) c_basketOption

foreign import ccall safe "ql.h qlBasketOption"
  c_basketOption :: Ptr CBasketPayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CMultiAssetOption)

himalayaOption :: [Day] -- ^fixingDates
  -> Double -- ^strike
  -> IO MultiAssetOption
himalayaOption = $(ffiCall 'himalayaOption) c_himalayaOption

foreign import ccall safe "ql.h qlHimalayaOption"
  c_himalayaOption :: CUInt -> Ptr CDate -> CDouble -> Ptr CString -> IO (Ptr CMultiAssetOption)

pagodaOption :: [Day] -- ^fixingDates
  -> Double -- ^roof
  -> Double -- ^fraction
  -> IO MultiAssetOption
pagodaOption = $(ffiCall 'pagodaOption) c_pagodaOption

foreign import ccall safe "ql.h qlPagodaOption"
  c_pagodaOption :: CUInt -> Ptr CDate -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CMultiAssetOption)

spreadOption :: PlainVanillaPayoff -- ^payoff
  -> Exercise -- ^exercise
  -> IO MultiAssetOption
spreadOption = $(ffiCall 'spreadOption) c_spreadOption

foreign import ccall safe "ql.h qlSpreadOption"
  c_spreadOption :: Ptr CPlainVanillaPayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CMultiAssetOption)

cliquetOption :: PercentageStrikePayoff
  -> EuropeanExercise -- ^maturity
  -> [Day] -- ^resetDates
  -> IO OneAssetOption
cliquetOption = $(ffiCall 'cliquetOption) c_cliquetOption

foreign import ccall safe "ql.h qlCliquetOption"
  c_cliquetOption :: Ptr CPercentageStrikePayoff -> Ptr CEuropeanExercise -> CUInt -> Ptr CDate -> Ptr CString -> IO (Ptr COneAssetOption)

continuousAveragingAsianOption :: AverageType -- ^averageType
  -> StrikedTypePayoff -- ^payoff
  -> Exercise -- ^exercise
  -> IO OneAssetOption
continuousAveragingAsianOption = $(ffiCall 'continuousAveragingAsianOption) c_continuousAveragingAsianOption

foreign import ccall safe "ql.h qlContinuousAveragingAsianOption"
  c_continuousAveragingAsianOption :: CInt -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr COneAssetOption)

continuousFixedLookbackOption :: Double -- ^currentMinmax
  -> StrikedTypePayoff -- ^payoff
  -> Exercise -- ^exercise
  -> IO OneAssetOption
continuousFixedLookbackOption = $(ffiCall 'continuousFixedLookbackOption) c_continuousFixedLookbackOption

foreign import ccall safe "ql.h qlContinuousFixedLookbackOption"
  c_continuousFixedLookbackOption :: CDouble -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr COneAssetOption)

continuousFloatingLookbackOption :: Double -- ^currentMinmax
  -> TypePayoff -- ^payoff
  -> Exercise -- ^exercise
  -> IO OneAssetOption
continuousFloatingLookbackOption = $(ffiCall 'continuousFloatingLookbackOption) c_continuousFloatingLookbackOption

foreign import ccall safe "ql.h qlContinuousFloatingLookbackOption"
  c_continuousFloatingLookbackOption :: CDouble -> Ptr CTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr COneAssetOption)

discreteAveragingAsianOption :: AverageType -- ^averageType
  -> Double -- ^runningAccumulator
  -> Word -- ^pastFixings
  -> [Day] -- ^fixingDates
  -> StrikedTypePayoff -- ^payoff
  -> Exercise -- ^exercise
  -> IO OneAssetOption
discreteAveragingAsianOption = $(ffiCall 'discreteAveragingAsianOption) c_discreteAveragingAsianOption

foreign import ccall safe "ql.h qlDiscreteAveragingAsianOption"
  c_discreteAveragingAsianOption :: CInt -> CDouble -> CUInt -> CUInt -> Ptr CDate -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr COneAssetOption)

vanillaStorageOption :: BermudanExercise -- ^ex
  -> Double -- ^capacity
  -> Double -- ^load
  -> Double -- ^changeRate
  -> IO OneAssetOption
vanillaStorageOption = $(ffiCall 'vanillaStorageOption) c_vanillaStorageOption

foreign import ccall safe "ql.h qlVanillaStorageOption"
  c_vanillaStorageOption :: Ptr CBermudanExercise -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr COneAssetOption)

vanillaSwingOption :: StrikedTypePayoff -- ^payoff
  -> SwingExercise -- ^ex
  -> Word -- ^minExerciseRights
  -> Word -- ^maxExerciseRights
  -> IO OneAssetOption
vanillaSwingOption = $(ffiCall 'vanillaSwingOption) c_vanillaSwingOption

foreign import ccall safe "ql.h qlVanillaSwingOption"
  c_vanillaSwingOption :: Ptr CStrikedTypePayoff -> Ptr CSwingExercise -> CUInt -> CUInt -> Ptr CString -> IO (Ptr COneAssetOption)

europeanOption :: StrikedTypePayoff -> Exercise -> IO VanillaOption
europeanOption = $(ffiCall 'europeanOption) c_europeanOption

foreign import ccall safe "ql.h qlEuropeanOption"
  c_europeanOption :: Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CVanillaOption)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
