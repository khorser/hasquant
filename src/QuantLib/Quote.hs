{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Quote
  (
    simpleQuote
  , value
  , setValue
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

foreign import ccall safe "ql.h qlSimpleQuote"
  c_simpleQuote :: CDouble -> Ptr CString -> IO (Ptr CSimpleQuote)
foreign import ccall safe "ql.h qlQuoteValue"
  c_quoteValue :: Ptr CQuote -> Ptr CString -> IO CDouble

-- |market element returning a stored value. QuantLibXL: qlSimpleQuote
simpleQuote :: Double -- ^value
  -> IO SimpleQuote
simpleQuote = $(ffiConstruct 'simpleQuote) c_simpleQuote

-- |Returns the current value of the given Quote object. QuantLibXL: qlQuoteValue
value :: Quote -> IO Double
value = $(ffiCallX 'value) c_quoteValue

-- |returns the difference between the new value and the old value
-- /NB/ The change will propagate to all users of the quote
setValue :: SimpleQuote
  -> Double -- ^value
  -> IO Double
setValue = $(ffiCallX 'setValue) c_setValue

foreign import ccall safe "ql.h qlSimpleQuoteSetValue"
  c_setValue :: Ptr CSimpleQuote -> CDouble -> Ptr CString -> IO CDouble
