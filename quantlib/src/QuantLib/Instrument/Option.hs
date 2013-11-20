{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument.Option
  (
    barrierOption
  , dividendVanillaOption
  , forwardVanillaOption
  , delta1
  , delta2
  , gamma1
  , gamma2
  , margrabeOption

  , multiAssetOption
  , deltaForward
  , elasticity
  , itmCashProbability
  , oneAssetOption
  , strikeSensitivity
  , thetaPerDay
  , quantoBarrierOption
  , quantoForwardVanillaOption
  , quantoVanillaOption
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

import QuantLib.Instrument.AverageType(AverageType)
import QuantLib.Instrument.BarrierType(BarrierType)
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

dividendVanillaOption :: StrikedTypePayoff -- ^payoff
  -> Exercise -- ^exercise
  -> [Day] -- ^dividendDates
  -> [Double] -- ^dividends
  -> IO DividendVanillaOption
dividendVanillaOption = $(ffiCall 'dividendVanillaOption) c_dividendVanillaOption

foreign import ccall safe "ql.h qlDividendVanillaOption"
  c_dividendVanillaOption :: Ptr CStrikedTypePayoff -> Ptr CExercise -> CUInt -> Ptr CDate -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CDividendVanillaOption)

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

multiAssetOption :: Payoff -> Exercise -> IO MultiAssetOption
multiAssetOption = $(ffiCall 'multiAssetOption) c_multiAssetOption

foreign import ccall safe "ql.h qlMultiAssetOption"
  c_multiAssetOption :: Ptr CPayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CMultiAssetOption)

deltaForward :: OneAssetOption -> IO Double
deltaForward = $(ffiCallX 'deltaForward) c_deltaForward

foreign import ccall safe "ql.h qlOneAssetOptionDeltaForward"
  c_deltaForward :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

elasticity :: OneAssetOption -> IO Double
elasticity = $(ffiCallX 'elasticity) c_elasticity

foreign import ccall safe "ql.h qlOneAssetOptionElasticity"
  c_elasticity :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

itmCashProbability :: OneAssetOption
  -> IO Double
itmCashProbability = $(ffiCallX 'itmCashProbability) c_itmCashProbability

foreign import ccall safe "ql.h qlOneAssetOptionItmCashProbability"
  c_itmCashProbability :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

oneAssetOption :: Payoff -> Exercise -> IO OneAssetOption
oneAssetOption = $(ffiCall 'oneAssetOption) c_oneAssetOption

foreign import ccall safe "ql.h qlOneAssetOption"
  c_oneAssetOption :: Ptr CPayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr COneAssetOption)

strikeSensitivity :: OneAssetOption -> IO Double
strikeSensitivity = $(ffiCallX 'strikeSensitivity) c_strikeSensitivity

foreign import ccall safe "ql.h qlOneAssetOptionStrikeSensitivity"
  c_strikeSensitivity :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

thetaPerDay :: OneAssetOption -> IO Double
thetaPerDay = $(ffiCallX 'thetaPerDay) c_thetaPerDay

foreign import ccall safe "ql.h qlOneAssetOptionThetaPerDay"
  c_thetaPerDay :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

quantoBarrierOption :: BarrierType -- ^barrierType
  -> Double -- ^barrier
  -> Double -- ^rebate
  -> StrikedTypePayoff -- ^payoff
  -> Exercise -- ^exercise
  -> IO QuantoBarrierOption
quantoBarrierOption = $(ffiCall 'quantoBarrierOption) c_quantoBarrierOption

foreign import ccall safe "ql.h qlQuantoBarrierOption"
  c_quantoBarrierOption :: CInt -> CDouble -> CDouble -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CQuantoBarrierOption)

quantoForwardVanillaOption :: Double -- ^moneyness
  -> Day -- ^resetDate
  -> StrikedTypePayoff
  -> Exercise
  -> IO QuantoForwardVanillaOption
quantoForwardVanillaOption = $(ffiCall 'quantoForwardVanillaOption) c_quantoForwardVanillaOption

foreign import ccall safe "ql.h qlQuantoForwardVanillaOption"
  c_quantoForwardVanillaOption :: CDouble -> CDate -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CQuantoForwardVanillaOption)

quantoVanillaOption :: StrikedTypePayoff -> Exercise -> IO QuantoVanillaOption
quantoVanillaOption = $(ffiCall 'quantoVanillaOption) c_quantoVanillaOption

foreign import ccall safe "ql.h qlQuantoVanillaOption"
  c_quantoVanillaOption :: Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CQuantoVanillaOption)

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
