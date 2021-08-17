module QuantLib.Internal.CashFlow(withLeg) where

import Foreign.Ptr(Ptr)
import QuantLib.CashFlow(Leg)
import QuantLib.Internal(ForeignObject(withObject))

-- i didn't want to expose withT functions so here we go with more boilerplate
withLeg :: Leg -> (Ptr Leg -> IO b) -> IO b
withLeg = withObject
