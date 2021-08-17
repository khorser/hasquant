module QuantLib.Internal.TermStructure(withTermStructure, withYieldTermStructure) where

import Foreign.Ptr(Ptr)
import QuantLib.TermStructure(TermStructure)
import QuantLib.TermStructure.Yield(YieldTermStructure)
import QuantLib.Internal(ForeignObject(withObject))

-- i didn't want to expose withT functions so here we go with more boilerplate
withTermStructure :: TermStructure -> (Ptr TermStructure -> IO b) -> IO b
withTermStructure = withObject

withYieldTermStructure :: YieldTermStructure -> (Ptr YieldTermStructure -> IO b) -> IO b
withYieldTermStructure = withObject
