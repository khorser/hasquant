module QuantLib.Internal.TermStructure(withTermStructure, withYieldTermStructure, withBlackVolTermStructure, withOptionletVolatilityStructure, withSwaptionVolatilityStructure) where

import Foreign.Ptr(Ptr)
import QuantLib.TermStructure(TermStructure)
import QuantLib.TermStructure.Yield(YieldTermStructure)
import {-# SOURCE #-} QuantLib.TermStructure.Volatility(BlackVolTermStructure, OptionletVolatilityStructure, SwaptionVolatilityStructure)
import QuantLib.Internal(ForeignObject(withObject))

-- i didn't want to expose withT functions so here we go with more boilerplate
withTermStructure :: TermStructure -> (Ptr TermStructure -> IO b) -> IO b
withTermStructure = withObject

withYieldTermStructure :: YieldTermStructure -> (Ptr YieldTermStructure -> IO b) -> IO b
withYieldTermStructure = withObject

withBlackVolTermStructure :: BlackVolTermStructure -> (Ptr BlackVolTermStructure -> IO b) -> IO b
withBlackVolTermStructure = withObject

withOptionletVolatilityStructure :: OptionletVolatilityStructure -> (Ptr OptionletVolatilityStructure -> IO b) -> IO b
withOptionletVolatilityStructure = withObject

withSwaptionVolatilityStructure :: SwaptionVolatilityStructure -> (Ptr SwaptionVolatilityStructure -> IO b) -> IO b
withSwaptionVolatilityStructure = withObject

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
