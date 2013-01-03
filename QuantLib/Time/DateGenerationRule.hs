{-# LANGUAGE ForeignFunctionInterface #-}
module QuantLib.Time.DateGenerationRule
  (
    DateGenerationRule(..)
  , fromDateGenerationRule
  )
where

import Foreign.C.Types(CInt(CInt))

data DateGenerationRule = Backward | Forward | Zero | ThirdWednesday | Twentieth | TwentiethIMM | OldCDS | CDS
  deriving (Show, Eq)

-- use some preprocessor instead?
foreign import ccall safe "ql.h qlDateGenerationRuleBackward"
    c_backward :: CInt
foreign import ccall safe "ql.h qlDateGenerationRuleForward"
    c_forward :: CInt
foreign import ccall safe "ql.h qlDateGenerationRuleZero"
    c_zero :: CInt
foreign import ccall safe "ql.h qlDateGenerationRuleThirdWednesday"
    c_thirdWednesday :: CInt
foreign import ccall safe "ql.h qlDateGenerationRuleTwentieth"
    c_twentieth :: CInt
foreign import ccall safe "ql.h qlDateGenerationRuleTwentiethIMM"
    c_twentiethIMM :: CInt
foreign import ccall safe "ql.h qlDateGenerationRuleOldCDS"
    c_oldCDS :: CInt
foreign import ccall safe "ql.h qlDateGenerationRuleCDS"
    c_cds :: CInt

fromDateGenerationRule :: DateGenerationRule -> CInt
fromDateGenerationRule Backward = c_backward
fromDateGenerationRule Forward = c_forward
fromDateGenerationRule Zero = c_zero
fromDateGenerationRule ThirdWednesday = c_thirdWednesday
fromDateGenerationRule Twentieth = c_twentieth
fromDateGenerationRule TwentiethIMM = c_twentiethIMM
fromDateGenerationRule OldCDS = c_oldCDS
fromDateGenerationRule CDS = c_cds
