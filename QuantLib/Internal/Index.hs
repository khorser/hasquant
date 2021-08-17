module QuantLib.Internal.Index(withIndex, withIborIndex, withSwapIndex) where

import Foreign.Ptr(Ptr)
import QuantLib.Index(Index)
import {-# SOURCE #-} QuantLib.Index.InterestRate(IborIndex, SwapIndex)
import QuantLib.Internal(ForeignObject(withObject))

-- i didn't want to expose withT functions so here we go with more boilerplate
withIndex :: Index -> (Ptr Index -> IO b) -> IO b
withIndex = withObject

withIborIndex :: IborIndex -> (Ptr IborIndex -> IO b) -> IO b
withIborIndex = withObject

withSwapIndex :: SwapIndex -> (Ptr SwapIndex -> IO b) -> IO b
withSwapIndex = withObject
