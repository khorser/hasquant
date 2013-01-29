{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Quote
  (
  -- makers
    simpleQuote
  -- accessors
  , value
  )
where

import QuantLib.Internal.Syntax
import QuantLib.Internal.Utils
import QuantLib.Types

foreign import ccall safe "ql.h qlSimpleQuote"
  c_simpleQuote :: CDouble -> Ptr CString -> IO (Ptr CQuote)
foreign import ccall safe "ql.h qlQuoteValue"
  c_quoteValue :: Ptr CQuote -> Ptr CString -> IO CDouble

-- | (qlSimpleQuote)
simpleQuote :: Double -> IO Quote
simpleQuote = $(ffiCallConstruct 'simpleQuote 'c_simpleQuote)

-- |Returns the current value of the given Quote object (qlQuoteValue)
value :: Quote -> Double
value = $(ffiCallHandleXIO 'value 'c_quoteValue)
-- XXX assuming quotes are immutable
