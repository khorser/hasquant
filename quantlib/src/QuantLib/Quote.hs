{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Quote
  (
    simpleQuote
  , value
  , isValid

  , setValue
  , eurodollarFuturesImpliedStdDevQuote
  , forwardSwapQuote
  , forwardValueQuote
  , futuresConvAdjustmentQuote'
  , futuresConvAdjustmentQuote
  , impliedStdDevQuote
  , lastFixingQuote
  )
where

import QuantLib.Instrument.OptionType(OptionType)
import QuantLib.Internal.Syntax
import QuantLib.Internal.Date(Day, CDate)
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Time.Unit(Unit)
import QuantLib.Types

foreign import ccall safe "ql.h qlSimpleQuote"
  c_simpleQuote :: CDouble -> Ptr CString -> IO (Ptr CSimpleQuote)
foreign import ccall safe "ql.h qlQuoteValue"
  c_value :: Ptr CQuote -> Ptr CString -> IO CDouble

-- |market element returning a stored value
simpleQuote :: Double -- ^value
  -> IO SimpleQuote
simpleQuote = $(ffiCall 'simpleQuote) c_simpleQuote

-- |Returns the current value of the given Quote object
value :: Quote -> IO Double
value = $(ffiCallX 'value) c_value

-- |returns the difference between the new value and the old value
-- /NB/ The change will propagate to all users of the quote
setValue :: SimpleQuote
  -> Double -- ^value
  -> IO Double
setValue = $(ffiCallX 'setValue) c_setValue

foreign import ccall safe "ql.h qlSimpleQuoteSetValue"
  c_setValue :: Ptr CSimpleQuote -> CDouble -> Ptr CString -> IO CDouble

eurodollarFuturesImpliedStdDevQuote :: Quote -- ^forward
  -> Quote -- ^callPrice
  -> Quote -- ^putPrice
  -> Double -- ^strike
  -> Double -- ^guess
  -> Double -- ^accuracy
  -> Word -- ^maxIter
  -> IO Quote
eurodollarFuturesImpliedStdDevQuote = $(ffiCall 'eurodollarFuturesImpliedStdDevQuote) c_eurodollarFuturesImpliedStdDevQuote

foreign import ccall safe "ql.h qlEurodollarFuturesImpliedStdDevQuote"
  c_eurodollarFuturesImpliedStdDevQuote :: Ptr CQuote -> Ptr CQuote -> Ptr CQuote -> CDouble -> CDouble -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CQuote)

forwardSwapQuote :: SwapIndex -- ^swapIndex
  -> Quote -- ^spread
  -> (Int, Unit) -- ^fwdStart
  -> IO Quote
forwardSwapQuote = $(ffiCall 'forwardSwapQuote) c_forwardSwapQuote

foreign import ccall safe "ql.h qlForwardSwapQuote"
  c_forwardSwapQuote :: Ptr CSwapIndex -> Ptr CQuote -> CInt -> CInt -> Ptr CString -> IO (Ptr CQuote)

forwardValueQuote :: Index -- ^index
  -> Day -- ^fixingDate
  -> IO Quote
forwardValueQuote = $(ffiCall 'forwardValueQuote) c_forwardValueQuote

foreign import ccall safe "ql.h qlForwardValueQuote"
  c_forwardValueQuote :: Ptr CIndex -> CDate -> Ptr CString -> IO (Ptr CQuote)

futuresConvAdjustmentQuote' :: IborIndex -- ^index
  -> String -- ^immCode
  -> Quote -- ^futuresQuote
  -> Quote -- ^volatility
  -> Quote -- ^meanReversion
  -> IO Quote
futuresConvAdjustmentQuote' = $(ffiCall 'futuresConvAdjustmentQuote') c_futuresConvAdjustmentQuote'

foreign import ccall safe "ql.h qlFuturesConvAdjustmentQuote1"
  c_futuresConvAdjustmentQuote' :: Ptr CIborIndex -> CString -> Ptr CQuote -> Ptr CQuote -> Ptr CQuote -> Ptr CString -> IO (Ptr CQuote)

futuresConvAdjustmentQuote :: IborIndex -- ^index
  -> Day -- ^futuresDate
  -> Quote -- ^futuresQuote
  -> Quote -- ^volatility
  -> Quote -- ^meanReversion
  -> IO Quote
futuresConvAdjustmentQuote = $(ffiCall 'futuresConvAdjustmentQuote) c_futuresConvAdjustmentQuote

foreign import ccall safe "ql.h qlFuturesConvAdjustmentQuote"
  c_futuresConvAdjustmentQuote :: Ptr CIborIndex -> CDate -> Ptr CQuote -> Ptr CQuote -> Ptr CQuote -> Ptr CString -> IO (Ptr CQuote)

impliedStdDevQuote :: OptionType -- ^optionType
  -> Quote -- ^forward
  -> Quote -- ^price
  -> Double -- ^strike
  -> Double -- ^guess
  -> Double -- ^accuracy
  -> Word -- ^maxIter
  -> IO Quote
impliedStdDevQuote = $(ffiCall 'impliedStdDevQuote) c_impliedStdDevQuote

foreign import ccall safe "ql.h qlImpliedStdDevQuote"
  c_impliedStdDevQuote :: CInt -> Ptr CQuote -> Ptr CQuote -> CDouble -> CDouble -> CDouble -> CUInt -> Ptr CString -> IO (Ptr CQuote)

lastFixingQuote :: Index -- ^index
  -> IO Quote
lastFixingQuote = $(ffiCall 'lastFixingQuote) c_lastFixingQuote

foreign import ccall safe "ql.h qlLastFixingQuote"
  c_lastFixingQuote :: Ptr CIndex -> Ptr CString -> IO (Ptr CQuote)

-- |returns true if the Quote holds a valid value
isValid :: Quote
  -> IO Bool
isValid = $(ffiCallX 'isValid) c_isValid

foreign import ccall safe "ql.h qlQuoteIsValid"
  c_isValid :: Ptr CQuote -> Ptr CString -> IO CInt

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
