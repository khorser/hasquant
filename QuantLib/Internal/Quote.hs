module QuantLib.Internal.Quote(withQuote) where

import Foreign.Ptr(Ptr)
import QuantLib.Quote(Quote)
import QuantLib.Internal(ForeignObject(withObject))

-- i didn't want to expose withT functions so here we go with more boilerplate
withQuote :: Quote -> (Ptr Quote -> IO b) -> IO b
withQuote = withObject
