{-# LANGUAGE ForeignFunctionInterface #-}
module QuantLib.Time.Frequency
  (
    Frequency(..)
  , fromFrequency
  , toFrequency
  )

where

import Control.Exception(throw)

import Foreign.C.Types(CInt(CInt))

import QuantLib.Error(Error(Error))

data Frequency = NoFrequency | Annual | Semiannual | EveryFourthMonth | Quarterly
 | Bimonthly | Monthly | Biweekly | EveryFourthWeek | Weekly | Daily | Once | Other
 deriving (Show, Eq)

-- use some preprocessor instead?
foreign import ccall safe "ql.h qlFrequencyNoFrequency"
  c_noFrequency :: CInt
foreign import ccall safe "ql.h qlFrequencyAnnual"
  c_annual :: CInt
foreign import ccall safe "ql.h qlFrequencySemiannual"
  c_semiannual :: CInt
foreign import ccall safe "ql.h qlFrequencyEveryFourthMonth"
  c_everyFourthMonth :: CInt
foreign import ccall safe "ql.h qlFrequencyQuarterly"
  c_quarterly :: CInt
foreign import ccall safe "ql.h qlFrequencyBimonthly"
  c_biMonthly :: CInt
foreign import ccall safe "ql.h qlFrequencyMonthly"
  c_monthly :: CInt
foreign import ccall safe "ql.h qlFrequencyBiweekly"
  c_biWeekly :: CInt
foreign import ccall safe "ql.h qlFrequencyEveryFourthWeek"
  c_everyFourthWeek :: CInt
foreign import ccall safe "ql.h qlFrequencyWeekly"
  c_weekly :: CInt
foreign import ccall safe "ql.h qlFrequencyDaily"
  c_daily :: CInt
foreign import ccall safe "ql.h qlFrequencyOnce"
  c_once :: CInt
foreign import ccall safe "ql.h qlFrequencyOtherFrequency"
  c_other :: CInt

fromFrequency :: Frequency -> CInt
fromFrequency NoFrequency      = c_noFrequency
fromFrequency Annual           = c_annual
fromFrequency Semiannual       = c_semiannual
fromFrequency EveryFourthMonth = c_everyFourthMonth
fromFrequency Quarterly        = c_quarterly
fromFrequency Bimonthly        = c_biMonthly
fromFrequency Monthly          = c_monthly
fromFrequency Biweekly         = c_biWeekly
fromFrequency EveryFourthWeek  = c_everyFourthWeek
fromFrequency Weekly           = c_weekly
fromFrequency Daily            = c_daily
fromFrequency Once             = c_once
fromFrequency Other            = c_other

toFrequency :: CInt -> Frequency
toFrequency n | n == c_noFrequency     = NoFrequency
              | n == c_annual          = Annual
              | n == c_semiannual      = Semiannual
              | n == c_everyFourthMonth = EveryFourthMonth
              | n == c_quarterly       = Quarterly
              | n == c_biMonthly       = Bimonthly
              | n == c_monthly         = Monthly
              | n == c_biWeekly        = Biweekly
              | n == c_everyFourthWeek = EveryFourthWeek
              | n == c_weekly          = Weekly
              | n == c_daily           = Daily
              | n == c_once            = Once
              | n == c_other           = Other
              | otherwise = throw (Error $ "Unknown frequency code: " ++ show n)
