module QuantLib.Internal.Index(withIndex, withIborIndex, withSwapIndex, withBMAIndex, withOvernightIborIndex) where

import Foreign.Ptr(Ptr)
import QuantLib.Index(Index)
import {-# SOURCE #-} QuantLib.Index.InterestRate(IborIndex, SwapIndex, BMAIndex, OvernightIborIndex)
import QuantLib.Internal(ForeignObject(withObject))

-- i didn't want to expose withT functions so here we go with more boilerplate
withIndex :: Index -> (Ptr Index -> IO b) -> IO b
withIndex = withObject

withIborIndex :: IborIndex -> (Ptr IborIndex -> IO b) -> IO b
withIborIndex = withObject

withSwapIndex :: SwapIndex -> (Ptr SwapIndex -> IO b) -> IO b
withSwapIndex = withObject

withOvernightIborIndex :: OvernightIborIndex -> (Ptr OvernightIborIndex -> IO b) -> IO b
withOvernightIborIndex = withObject

withBMAIndex :: BMAIndex -> (Ptr BMAIndex -> IO b) -> IO b
withBMAIndex = withObject

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
