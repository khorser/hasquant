{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument
  (
    npv
  , errorEstimate
  , isExpired
  , valuationDate
  , composite

  , assetOrNothingPayoff
  , averageBasketPayoff
  , averageBasketPayoff'
  , cashOrNothingPayoff
  , doubleStickyRatchetPayoff
  , floatingTypePayoff
  , forwardTypePayoff
  , gapPayoff
  , maxBasketPayoff
  , minBasketPayoff
  , percentageStrikePayoff
  , plainVanillaPayoff
  , ratchetMaxPayoff
  , ratchetMinPayoff
  , ratchetPayoff
  , spreadBasketPayoff
  , stickyMaxPayoff
  , stickyMinPayoff
  , stickyPayoff
  , superFundPayoff
  , superSharePayoff

  , americanExercise
  , americanExercise'
  , bermudanExercise
  , earlyExercise
  , exercise
  , europeanExercise
  , swingExercise
  , swingExercise'

  , callabilityPrice
  , callability
  )
where

import QuantLib.ExerciseType(ExerciseType)
import QuantLib.Instrument.CallabilityType(CallabilityType, CallabilityPriceType)
import QuantLib.Instrument.OptionType(OptionType)
import QuantLib.Internal.Syntax
import QuantLib.Internal.Date
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.PositionType(PositionType)
import QuantLib.Types

foreign import ccall safe "ql.h qlInstrumentNPV"
  c_npv :: Ptr CInstrument -> Ptr CString -> IO CDouble

-- |Returns the net present value of the given Instrument. QuantLibXL: qlInstrumentNPV
npv :: Instrument -> IO Double
npv = $(ffiCallX 'npv) c_npv

-- |returns the error estimate on the NPV when available.
errorEstimate :: Instrument -> IO Double
errorEstimate = $(ffiCallX 'errorEstimate) c_errorEstimate

foreign import ccall safe "ql.h qlInstrumentErrorEstimate"
  c_errorEstimate :: Ptr CInstrument -> Ptr CString -> IO CDouble

-- |returns whether the instrument might have value greater than zero.
isExpired :: Instrument -> IO Bool
isExpired = $(ffiCallX 'isExpired) c_isExpired

foreign import ccall safe "ql.h qlInstrumentIsExpired"
  c_isExpired :: Ptr CInstrument -> Ptr CString -> IO CInt

-- |returns the date the net present value refers to.
valuationDate :: Instrument -> IO Day
valuationDate = $(ffiCallX 'valuationDate) c_valuationDate

foreign import ccall safe "ql.h qlInstrumentValuationDate"
  c_valuationDate :: Ptr CInstrument -> Ptr CString -> IO CDate

composite :: [(Instrument, Double)] -> IO Instrument
composite = $(ffiCall 'composite) c_composite

foreign import ccall safe "ql.h qlCompositeInstrument"
  c_composite :: CUInt -> Ptr (Ptr CInstrument) -> Ptr CDouble -> Ptr CString -> IO (Ptr CInstrument)

assetOrNothingPayoff :: OptionType -- ^type
  -> Double -- ^strike
  -> IO StrikedTypePayoff
assetOrNothingPayoff = $(ffiCall 'assetOrNothingPayoff) c_assetOrNothingPayoff

foreign import ccall safe "ql.h qlAssetOrNothingPayoff"
  c_assetOrNothingPayoff :: CInt -> CDouble -> Ptr CString -> IO (Ptr CStrikedTypePayoff)

averageBasketPayoff :: Payoff -- ^p
  -> Word -- ^n
  -> IO BasketPayoff
averageBasketPayoff = $(ffiCall 'averageBasketPayoff) c_averageBasketPayoff

foreign import ccall safe "ql.h qlAverageBasketPayoff"
  c_averageBasketPayoff :: Ptr CPayoff -> CUInt -> Ptr CString -> IO (Ptr CBasketPayoff)

cashOrNothingPayoff :: OptionType -- ^type
  -> Double -- ^strike
  -> Double -- ^cashPayoff
  -> IO StrikedTypePayoff
cashOrNothingPayoff = $(ffiCall 'cashOrNothingPayoff) c_cashOrNothingPayoff

foreign import ccall safe "ql.h qlCashOrNothingPayoff"
  c_cashOrNothingPayoff :: CInt -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CStrikedTypePayoff)

doubleStickyRatchetPayoff :: Double -- ^type1
  -> Double -- ^type2
  -> Double -- ^gearing1
  -> Double -- ^gearing2
  -> Double -- ^gearing3
  -> Double -- ^spread1
  -> Double -- ^spread2
  -> Double -- ^spread3
  -> Double -- ^initialValue1
  -> Double -- ^initialValue2
  -> Double -- ^accrualFactor
  -> IO Payoff
doubleStickyRatchetPayoff = $(ffiCall 'doubleStickyRatchetPayoff) c_doubleStickyRatchetPayoff

foreign import ccall safe "ql.h qlDoubleStickyRatchetPayoff"
  c_doubleStickyRatchetPayoff :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CPayoff)

floatingTypePayoff :: OptionType -- ^type
  -> IO TypePayoff
floatingTypePayoff = $(ffiCall 'floatingTypePayoff) c_floatingTypePayoff

foreign import ccall safe "ql.h qlFloatingTypePayoff"
  c_floatingTypePayoff :: CInt -> Ptr CString -> IO (Ptr CTypePayoff)

forwardTypePayoff :: PositionType -- ^type
  -> Double -- ^strike
  -> IO Payoff
forwardTypePayoff = $(ffiCall 'forwardTypePayoff) c_forwardTypePayoff

foreign import ccall safe "ql.h qlForwardTypePayoff"
  c_forwardTypePayoff :: CInt -> CDouble -> Ptr CString -> IO (Ptr CPayoff)

gapPayoff :: OptionType -- ^type
  -> Double -- ^strike
  -> Double -- ^secondStrike
  -> IO StrikedTypePayoff
gapPayoff = $(ffiCall 'gapPayoff) c_gapPayoff

foreign import ccall safe "ql.h qlGapPayoff"
  c_gapPayoff :: CInt -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CStrikedTypePayoff)

maxBasketPayoff :: Payoff -- ^p
  -> IO BasketPayoff
maxBasketPayoff = $(ffiCall 'maxBasketPayoff) c_maxBasketPayoff

foreign import ccall safe "ql.h qlMaxBasketPayoff"
  c_maxBasketPayoff :: Ptr CPayoff -> Ptr CString -> IO (Ptr CBasketPayoff)

minBasketPayoff :: Payoff -- ^p
  -> IO BasketPayoff
minBasketPayoff = $(ffiCall 'minBasketPayoff) c_minBasketPayoff

foreign import ccall safe "ql.h qlMinBasketPayoff"
  c_minBasketPayoff :: Ptr CPayoff -> Ptr CString -> IO (Ptr CBasketPayoff)

percentageStrikePayoff :: OptionType -- ^type
  -> Double -- ^moneyness
  -> IO PercentageStrikePayoff
percentageStrikePayoff = $(ffiCall 'percentageStrikePayoff) c_percentageStrikePayoff

foreign import ccall safe "ql.h qlPercentageStrikePayoff"
  c_percentageStrikePayoff :: CInt -> CDouble -> Ptr CString -> IO (Ptr CPercentageStrikePayoff)

plainVanillaPayoff :: OptionType -- ^type
  -> Double -- ^strike
  -> IO PlainVanillaPayoff
plainVanillaPayoff = $(ffiCall 'plainVanillaPayoff) c_plainVanillaPayoff

foreign import ccall safe "ql.h qlPlainVanillaPayoff"
  c_plainVanillaPayoff :: CInt -> CDouble -> Ptr CString -> IO (Ptr CPlainVanillaPayoff)

ratchetMaxPayoff :: Double -- ^gearing1
  -> Double -- ^gearing2
  -> Double -- ^gearing3
  -> Double -- ^spread1
  -> Double -- ^spread2
  -> Double -- ^spread3
  -> Double -- ^initialValue1
  -> Double -- ^initialValue2
  -> Double -- ^accrualFactor
  -> IO Payoff
ratchetMaxPayoff = $(ffiCall 'ratchetMaxPayoff) c_ratchetMaxPayoff

foreign import ccall safe "ql.h qlRatchetMaxPayoff"
  c_ratchetMaxPayoff :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CPayoff)

ratchetMinPayoff :: Double -- ^gearing1
  -> Double -- ^gearing2
  -> Double -- ^gearing3
  -> Double -- ^spread1
  -> Double -- ^spread2
  -> Double -- ^spread3
  -> Double -- ^initialValue1
  -> Double -- ^initialValue2
  -> Double -- ^accrualFactor
  -> IO Payoff
ratchetMinPayoff = $(ffiCall 'ratchetMinPayoff) c_ratchetMinPayoff

foreign import ccall safe "ql.h qlRatchetMinPayoff"
  c_ratchetMinPayoff :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CPayoff)

ratchetPayoff :: Double -- ^gearing1
  -> Double -- ^gearing2
  -> Double -- ^spread1
  -> Double -- ^spread2
  -> Double -- ^initialValue
  -> Double -- ^accrualFactor
  -> IO Payoff
ratchetPayoff = $(ffiCall 'ratchetPayoff) c_ratchetPayoff

foreign import ccall safe "ql.h qlRatchetPayoff"
  c_ratchetPayoff :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CPayoff)

spreadBasketPayoff :: Payoff -- ^p
  -> IO BasketPayoff
spreadBasketPayoff = $(ffiCall 'spreadBasketPayoff) c_spreadBasketPayoff

foreign import ccall safe "ql.h qlSpreadBasketPayoff"
  c_spreadBasketPayoff :: Ptr CPayoff -> Ptr CString -> IO (Ptr CBasketPayoff)

stickyMaxPayoff :: Double -- ^gearing1
  -> Double -- ^gearing2
  -> Double -- ^gearing3
  -> Double -- ^spread1
  -> Double -- ^spread2
  -> Double -- ^spread3
  -> Double -- ^initialValue1
  -> Double -- ^initialValue2
  -> Double -- ^accrualFactor
  -> IO Payoff
stickyMaxPayoff = $(ffiCall 'stickyMaxPayoff) c_stickyMaxPayoff

foreign import ccall safe "ql.h qlStickyMaxPayoff"
  c_stickyMaxPayoff :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CPayoff)

stickyMinPayoff :: Double -- ^gearing1
  -> Double -- ^gearing2
  -> Double -- ^gearing3
  -> Double -- ^spread1
  -> Double -- ^spread2
  -> Double -- ^spread3
  -> Double -- ^initialValue1
  -> Double -- ^initialValue2
  -> Double -- ^accrualFactor
  -> IO Payoff
stickyMinPayoff = $(ffiCall 'stickyMinPayoff) c_stickyMinPayoff

foreign import ccall safe "ql.h qlStickyMinPayoff"
  c_stickyMinPayoff :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CPayoff)

stickyPayoff :: Double -- ^gearing1
  -> Double -- ^gearing2
  -> Double -- ^spread1
  -> Double -- ^spread2
  -> Double -- ^initialValue
  -> Double -- ^accrualFactor
  -> IO Payoff
stickyPayoff = $(ffiCall 'stickyPayoff) c_stickyPayoff

foreign import ccall safe "ql.h qlStickyPayoff"
  c_stickyPayoff :: CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CPayoff)

superFundPayoff :: Double -- ^strike
  -> Double -- ^secondStrike
  -> IO StrikedTypePayoff
superFundPayoff = $(ffiCall 'superFundPayoff) c_superFundPayoff

foreign import ccall safe "ql.h qlSuperFundPayoff"
  c_superFundPayoff :: CDouble -> CDouble -> Ptr CString -> IO (Ptr CStrikedTypePayoff)

superSharePayoff :: Double -- ^strike
  -> Double -- ^secondStrike
  -> Double -- ^cashPayoff
  -> IO StrikedTypePayoff
superSharePayoff = $(ffiCall 'superSharePayoff) c_superSharePayoff

foreign import ccall safe "ql.h qlSuperSharePayoff"
  c_superSharePayoff :: CDouble -> CDouble -> CDouble -> Ptr CString -> IO (Ptr CStrikedTypePayoff)

americanExercise :: Day -- ^earliestDate
  -> Day -- ^latestDate
  -> Bool -- ^payoffAtExpiry
  -> IO AmericanExercise
americanExercise = $(ffiCall 'americanExercise) c_americanExercise

foreign import ccall safe "ql.h qlAmericanExercise"
  c_americanExercise :: CDate -> CDate -> CInt -> Ptr CString -> IO (Ptr CAmericanExercise)

americanExercise' :: Day -- ^latestDate
  -> Bool -- ^payoffAtExpiry
  -> IO AmericanExercise
americanExercise' = $(ffiCall 'americanExercise') c_americanExercise'

foreign import ccall safe "ql.h qlAmericanExercise1"
  c_americanExercise' :: CDate -> CInt -> Ptr CString -> IO (Ptr CAmericanExercise)

bermudanExercise :: [Day] -- ^dates
  -> Bool -- ^payoffAtExpiry
  -> IO BermudanExercise
bermudanExercise = $(ffiCall 'bermudanExercise) c_bermudanExercise

foreign import ccall safe "ql.h qlBermudanExercise"
  c_bermudanExercise :: CUInt -> Ptr CDate -> CInt -> Ptr CString -> IO (Ptr CBermudanExercise)

earlyExercise :: ExerciseType -- ^type
  -> Bool -- ^payoffAtExpiry
  -> IO Exercise
earlyExercise = $(ffiCall 'earlyExercise) c_earlyExercise

foreign import ccall safe "ql.h qlEarlyExercise"
  c_earlyExercise :: CInt -> CInt -> Ptr CString -> IO (Ptr CExercise)

exercise :: ExerciseType -- ^type
  -> IO Exercise
exercise = $(ffiCall 'exercise) c_exercise

foreign import ccall safe "ql.h qlExercise"
  c_exercise :: CInt -> Ptr CString -> IO (Ptr CExercise)

europeanExercise :: Day -- ^date
  -> IO EuropeanExercise
europeanExercise = $(ffiCall 'europeanExercise) c_europeanExercise

foreign import ccall safe "ql.h qlEuropeanExercise"
  c_europeanExercise :: CDate -> Ptr CString -> IO (Ptr CEuropeanExercise)

averageBasketPayoff' :: Payoff -- ^p
  -> [Double] -- ^a
  -> IO BasketPayoff
averageBasketPayoff' = $(ffiCall 'averageBasketPayoff') c_averageBasketPayoff'

foreign import ccall safe "ql.h qlAverageBasketPayoff1"
  c_averageBasketPayoff' :: Ptr CPayoff -> CUInt -> Ptr CDouble -> Ptr CString -> IO (Ptr CBasketPayoff)

swingExercise :: [(Day, Word)] -- ^(dates, seconds)
  -> IO SwingExercise
swingExercise = $(ffiCall 'swingExercise) c_swingExercise

foreign import ccall safe "ql.h qlSwingExercise"
  c_swingExercise :: CUInt -> Ptr CDate -> Ptr CUInt -> Ptr CString -> IO (Ptr CSwingExercise)

swingExercise' :: Day -- ^from
  -> Day -- ^to
  -> Word -- ^stepSizeSecs
  -> IO SwingExercise
swingExercise' = $(ffiCall 'swingExercise') c_swingExercise'

foreign import ccall safe "ql.h qlSwingExercise1"
  c_swingExercise' :: CDate -> CDate -> CUInt -> Ptr CString -> IO (Ptr CSwingExercise)

callabilityPrice :: Double -- ^amount
  -> CallabilityPriceType -- ^type
  -> IO CallabilityPrice
callabilityPrice = $(ffiCall 'callabilityPrice) c_callabilityPrice

foreign import ccall safe "ql.h qlCallabilityPrice"
  c_callabilityPrice :: CDouble -> CInt -> Ptr CString -> IO (Ptr CCallabilityPrice)

callability :: CallabilityPrice -- ^price
  -> CallabilityType -- ^type
  -> Day -- ^date
  -> IO Callability
callability = $(ffiCall 'callability) c_callability

foreign import ccall safe "ql.h qlCallability"
  c_callability :: Ptr CCallabilityPrice -> CInt -> CDate -> Ptr CString -> IO (Ptr CCallability)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
