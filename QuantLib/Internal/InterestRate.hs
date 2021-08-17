module QuantLib.Internal.InterestRate(withInterestRate) where

import Foreign.Ptr(Ptr)
import QuantLib.InterestRate(InterestRate)
import QuantLib.Internal(ForeignObject(withObject))

-- i didn't want to expose withT functions so here we go with more boilerplate
withInterestRate :: InterestRate -> (Ptr InterestRate -> IO b) -> IO b
withInterestRate = withObject
