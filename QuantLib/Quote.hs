{-# LANGUAGE ForeignFunctionInterface #-}
{-# OPTIONS_GHC -fno-warn-orphans #-}
module QuantLib.Quote
  (
  -- makers
    simpleQuote
  -- accessors
  , value
  )
where

import QuantLib.Internal
import QuantLib.Types

foreign import ccall safe "ql.h qlSimpleQuote"
  c_simpleQuote :: CDouble -> Ptr CString -> IO (Ptr CQuote)
foreign import ccall safe "ql.h qlQuoteValue"
  c_quoteValue :: Ptr CQuote -> Ptr CString -> IO CDouble
foreign import ccall safe "ql.h &qlFreeQuote"
  p_freeQuote :: FunPtr (Ptr CQuote -> IO ())

instance Finalizable CQuote where
  finalize = p_freeQuote

-- | (qlSimpleQuote)
simpleQuote :: Double -> IO Quote
simpleQuote v = construct $ c_simpleQuote (realToFrac v)

-- |Returns the current value of the given Quote object (qlQuoteValue)
-- XXX assuming quotes are immutable
value :: Quote -> Double
value q = realToFrac $ unsafePerformIO (withObject q (handleExceptions . c_quoteValue))
