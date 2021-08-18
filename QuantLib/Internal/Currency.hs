module QuantLib.Internal.Currency(withCurrency) where

import Foreign.Ptr(Ptr)
import QuantLib.Currency(Currency)
import QuantLib.Internal(ForeignObject(withObject))

-- i didn't want to expose withT functions so here we go with more boilerplate
withCurrency :: Currency -> (Ptr Currency -> IO b) -> IO b
withCurrency = withObject

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
