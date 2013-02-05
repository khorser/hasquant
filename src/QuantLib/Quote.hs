{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Quote
  (
    simpleQuote
  , value
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

foreign import ccall safe "ql.h qlSimpleQuote"
  c_simpleQuote :: CDouble -> Ptr CString -> IO (Ptr CQuote)
foreign import ccall safe "ql.h qlQuoteValue"
  c_quoteValue :: Ptr CQuote -> Ptr CString -> IO CDouble

-- |market element returning a stored value. QuantLibXL: qlSimpleQuote
simpleQuote :: Double -- ^value
  -> IO Quote
simpleQuote = $(ffiConstruct 'simpleQuote) c_simpleQuote

-- |Returns the current value of the given Quote object. QuantLibXL: qlQuoteValue
value :: Quote -> IO Double
value = $(ffiCallX 'value) c_quoteValue
