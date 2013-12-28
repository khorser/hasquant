{-# LANGUAGE TemplateHaskell #-}
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
import QuantLib.Types

barrierOption :: BarrierType -- ^barrierType
  -> Double -- ^barrier
  -> Double -- ^rebate
  -> StrikedTypePayoff s -- ^payoff
  -> Exercise s -- ^exercise
  -> QLE s (BarrierOption s)
barrierOption = $(ffiCall 'barrierOption) c_barrierOption

foreign import ccall safe "ql.h qlBarrierOption"
  c_barrierOption :: CInt -> CDouble -> CDouble -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CBarrierOption)

dividendVanillaOption :: StrikedTypePayoff s -- ^payoff
  -> Exercise s -- ^exercise
  -> [Day] -- ^dividendDates
  -> [Double] -- ^dividends
  -> QLE s (DividendVanillaOption s)
dividendVanillaOption = $(ffiCall 'dividendVanillaOption) c_dividendVanillaOption

foreign import ccall safe "ql.h qlDividendVanillaOption"
  c_dividendVanillaOption :: Ptr CStrikedTypePayoff -> Ptr CExercise -> CUInt -> Ptr CDate -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CDividendVanillaOption)

forwardVanillaOption :: Double -- ^moneyness
  -> Day -- ^resetDate
  -> StrikedTypePayoff s -- ^payoff
  -> Exercise s -- ^exercise
  -> QLE s (ForwardVanillaOption s)
forwardVanillaOption = $(ffiCall 'forwardVanillaOption) c_forwardVanillaOption

foreign import ccall safe "ql.h qlForwardVanillaOption"
  c_forwardVanillaOption :: CDouble -> CDate -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CForwardVanillaOption)

delta1 :: MargrabeOption s -> QLE s Double
delta1 = $(ffiCallX 'delta1) c_delta1

foreign import ccall safe "ql.h qlMargrabeOptionDelta1"
  c_delta1 :: Ptr CMargrabeOption -> Ptr CString -> IO CDouble

delta2 :: MargrabeOption s -> QLE s Double
delta2 = $(ffiCallX 'delta2) c_delta2

foreign import ccall safe "ql.h qlMargrabeOptionDelta2"
  c_delta2 :: Ptr CMargrabeOption -> Ptr CString -> IO CDouble

gamma1 :: MargrabeOption s -> QLE s Double
gamma1 = $(ffiCallX 'gamma1) c_gamma1

foreign import ccall safe "ql.h qlMargrabeOptionGamma1"
  c_gamma1 :: Ptr CMargrabeOption -> Ptr CString -> IO CDouble

gamma2 :: MargrabeOption s -> QLE s Double
gamma2 = $(ffiCallX 'gamma2) c_gamma2

foreign import ccall safe "ql.h qlMargrabeOptionGamma2"
  c_gamma2 :: Ptr CMargrabeOption -> Ptr CString -> IO CDouble

margrabeOption :: Int -- ^Q1
  -> Int -- ^Q2
  -> Exercise s
  -> QLE s (MargrabeOption s)
margrabeOption = $(ffiCall 'margrabeOption) c_margrabeOption

foreign import ccall safe "ql.h qlMargrabeOption"
  c_margrabeOption :: CInt -> CInt -> Ptr CExercise -> Ptr CString -> IO (Ptr CMargrabeOption)

multiAssetOption :: Payoff s -> Exercise s -> QLE s (MultiAssetOption s)
multiAssetOption = $(ffiCall 'multiAssetOption) c_multiAssetOption

foreign import ccall safe "ql.h qlMultiAssetOption"
  c_multiAssetOption :: Ptr CPayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CMultiAssetOption)

deltaForward :: OneAssetOption s -> QLE s Double
deltaForward = $(ffiCallX 'deltaForward) c_deltaForward

foreign import ccall safe "ql.h qlOneAssetOptionDeltaForward"
  c_deltaForward :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

elasticity :: OneAssetOption s -> QLE s Double
elasticity = $(ffiCallX 'elasticity) c_elasticity

foreign import ccall safe "ql.h qlOneAssetOptionElasticity"
  c_elasticity :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

itmCashProbability :: OneAssetOption s -> QLE s Double
itmCashProbability = $(ffiCallX 'itmCashProbability) c_itmCashProbability

foreign import ccall safe "ql.h qlOneAssetOptionItmCashProbability"
  c_itmCashProbability :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

oneAssetOption :: Payoff s -> Exercise s -> QLE s (OneAssetOption s)
oneAssetOption = $(ffiCall 'oneAssetOption) c_oneAssetOption

foreign import ccall safe "ql.h qlOneAssetOption"
  c_oneAssetOption :: Ptr CPayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr COneAssetOption)

strikeSensitivity :: OneAssetOption s -> QLE s Double
strikeSensitivity = $(ffiCallX 'strikeSensitivity) c_strikeSensitivity

foreign import ccall safe "ql.h qlOneAssetOptionStrikeSensitivity"
  c_strikeSensitivity :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

thetaPerDay :: OneAssetOption s -> QLE s Double
thetaPerDay = $(ffiCallX 'thetaPerDay) c_thetaPerDay

foreign import ccall safe "ql.h qlOneAssetOptionThetaPerDay"
  c_thetaPerDay :: Ptr COneAssetOption -> Ptr CString -> IO CDouble

quantoBarrierOption :: BarrierType -- ^barrierType
  -> Double -- ^barrier
  -> Double -- ^rebate
  -> StrikedTypePayoff s -- ^payoff
  -> Exercise s -- ^exercise
  -> QLE s (QuantoBarrierOption s)
quantoBarrierOption = $(ffiCall 'quantoBarrierOption) c_quantoBarrierOption

foreign import ccall safe "ql.h qlQuantoBarrierOption"
  c_quantoBarrierOption :: CInt -> CDouble -> CDouble -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CQuantoBarrierOption)

quantoForwardVanillaOption :: Double -- ^moneyness
  -> Day -- ^resetDate
  -> StrikedTypePayoff s
  -> Exercise s
  -> QLE s (QuantoForwardVanillaOption s)
quantoForwardVanillaOption = $(ffiCall 'quantoForwardVanillaOption) c_quantoForwardVanillaOption

foreign import ccall safe "ql.h qlQuantoForwardVanillaOption"
  c_quantoForwardVanillaOption :: CDouble -> CDate -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CQuantoForwardVanillaOption)

quantoVanillaOption :: StrikedTypePayoff s -> Exercise s -> QLE s (QuantoVanillaOption s)
quantoVanillaOption = $(ffiCall 'quantoVanillaOption) c_quantoVanillaOption

foreign import ccall safe "ql.h qlQuantoVanillaOption"
  c_quantoVanillaOption :: Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CQuantoVanillaOption)

vanillaOption :: StrikedTypePayoff s -> Exercise s -> QLE s (VanillaOption s)
vanillaOption = $(ffiCall 'vanillaOption) c_vanillaOption

foreign import ccall safe "ql.h qlVanillaOption"
  c_vanillaOption :: Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CVanillaOption)

dividendBarrierOption :: BarrierType -- ^barrierType
  -> Double -- ^barrier
  -> Double -- ^rebate
  -> StrikedTypePayoff s -- ^payoff
  -> Exercise s -- ^exercise
  -> [Day] -- ^dividendDates
  -> [Double] -- ^dividends
  -> QLE s (BarrierOption s)
dividendBarrierOption = $(ffiCall 'dividendBarrierOption) c_dividendBarrierOption

foreign import ccall safe "ql.h qlDividendBarrierOption"
  c_dividendBarrierOption :: CInt -> CDouble -> CDouble -> Ptr CStrikedTypePayoff -> Ptr CExercise -> CUInt -> Ptr CDate -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CBarrierOption)

basketOption :: BasketPayoff s -> Exercise s -> QLE s (MultiAssetOption s)
basketOption = $(ffiCall 'basketOption) c_basketOption

foreign import ccall safe "ql.h qlBasketOption"
  c_basketOption :: Ptr CBasketPayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CMultiAssetOption)

himalayaOption :: [Day] -- ^fixingDates
  -> Double -- ^strike
  -> QLE s (MultiAssetOption s)
himalayaOption = $(ffiCall 'himalayaOption) c_himalayaOption

foreign import ccall safe "ql.h qlHimalayaOption"
  c_himalayaOption :: CUInt -> Ptr CDate -> CDouble -> Ptr CString -> IO (Ptr CMultiAssetOption)

pagodaOption :: [Day] -- ^fixingDates
  -> Double -- ^roof
  -> Double -- ^fraction
  -> QLE s (MultiAssetOption s)
pagodaOption = $(ffiCall 'pagodaOption) c_pagodaOption

foreign import ccall safe "ql.h qlPagodaOption"
  c_pagodaOption :: CUInt -> Ptr CDate -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CMultiAssetOption)

spreadOption :: PlainVanillaPayoff s -- ^payoff
  -> Exercise s -- ^exercise
  -> QLE s (MultiAssetOption s)
spreadOption = $(ffiCall 'spreadOption) c_spreadOption

foreign import ccall safe "ql.h qlSpreadOption"
  c_spreadOption :: Ptr CPlainVanillaPayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CMultiAssetOption)

cliquetOption :: PercentageStrikePayoff s
  -> EuropeanExercise s -- ^maturity
  -> [Day] -- ^resetDates
  -> QLE s (OneAssetOption s)
cliquetOption = $(ffiCall 'cliquetOption) c_cliquetOption

foreign import ccall safe "ql.h qlCliquetOption"
  c_cliquetOption :: Ptr CPercentageStrikePayoff -> Ptr CEuropeanExercise -> CUInt -> Ptr CDate -> Ptr CString -> IO (Ptr COneAssetOption)

continuousAveragingAsianOption :: AverageType -- ^averageType
  -> StrikedTypePayoff s -- ^payoff
  -> Exercise s -- ^exercise
  -> QLE s (OneAssetOption s)
continuousAveragingAsianOption = $(ffiCall 'continuousAveragingAsianOption) c_continuousAveragingAsianOption

foreign import ccall safe "ql.h qlContinuousAveragingAsianOption"
  c_continuousAveragingAsianOption :: CInt -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr COneAssetOption)

continuousFixedLookbackOption :: Double -- ^currentMinmax
  -> StrikedTypePayoff s -- ^payoff
  -> Exercise s -- ^exercise
  -> QLE s (OneAssetOption s)
continuousFixedLookbackOption = $(ffiCall 'continuousFixedLookbackOption) c_continuousFixedLookbackOption

foreign import ccall safe "ql.h qlContinuousFixedLookbackOption"
  c_continuousFixedLookbackOption :: CDouble -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr COneAssetOption)

continuousFloatingLookbackOption :: Double -- ^currentMinmax
  -> TypePayoff s -- ^payoff
  -> Exercise s -- ^exercise
  -> QLE s (OneAssetOption s)
continuousFloatingLookbackOption = $(ffiCall 'continuousFloatingLookbackOption) c_continuousFloatingLookbackOption

foreign import ccall safe "ql.h qlContinuousFloatingLookbackOption"
  c_continuousFloatingLookbackOption :: CDouble -> Ptr CTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr COneAssetOption)

discreteAveragingAsianOption :: AverageType -- ^averageType
  -> Double -- ^runningAccumulator
  -> Word -- ^pastFixings
  -> [Day] -- ^fixingDates
  -> StrikedTypePayoff s -- ^payoff
  -> Exercise s -- ^exercise
  -> QLE s (OneAssetOption s)
discreteAveragingAsianOption = $(ffiCall 'discreteAveragingAsianOption) c_discreteAveragingAsianOption

foreign import ccall safe "ql.h qlDiscreteAveragingAsianOption"
  c_discreteAveragingAsianOption :: CInt -> CDouble -> CUInt -> CUInt -> Ptr CDate -> Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr COneAssetOption)

vanillaStorageOption :: BermudanExercise s -- ^ex
  -> Double -- ^capacity
  -> Double -- ^load
  -> Double -- ^changeRate
  -> QLE s (OneAssetOption s)
vanillaStorageOption = $(ffiCall 'vanillaStorageOption) c_vanillaStorageOption

foreign import ccall safe "ql.h qlVanillaStorageOption"
  c_vanillaStorageOption :: Ptr CBermudanExercise -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr COneAssetOption)

vanillaSwingOption :: StrikedTypePayoff s -- ^payoff
  -> SwingExercise s -- ^ex
  -> Word -- ^minExerciseRights
  -> Word -- ^maxExerciseRights
  -> QLE s (OneAssetOption s)
vanillaSwingOption = $(ffiCall 'vanillaSwingOption) c_vanillaSwingOption

foreign import ccall safe "ql.h qlVanillaSwingOption"
  c_vanillaSwingOption :: Ptr CStrikedTypePayoff -> Ptr CSwingExercise -> CUInt -> CUInt -> Ptr CString -> IO (Ptr COneAssetOption)

europeanOption :: StrikedTypePayoff s -> Exercise s -> QLE s (VanillaOption s)
europeanOption = $(ffiCall 'europeanOption) c_europeanOption

foreign import ccall safe "ql.h qlEuropeanOption"
  c_europeanOption :: Ptr CStrikedTypePayoff -> Ptr CExercise -> Ptr CString -> IO (Ptr CVanillaOption)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
