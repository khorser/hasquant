{-# OPTIONS_GHC -F -pgmF htfpp #-}
module QuantLib.Test.InterestRates (htf_thisModulesTests)
-- interestrates.cpp
where

import Test.Framework

import Control.Monad.IO.Class
import Data.Time.Calendar

import QuantLib.Compounding
import QuantLib.InterestRate
import QuantLib.Math.Rounding
import QuantLib.Math.RoundingType
import QuantLib.Settings
import QuantLib.Time.Date
import QuantLib.Time.DayCounter
import QuantLib.Time.Frequency
import QuantLib.Types

{-# ANN module "HLint: ignore Use camelCase" #-}

test_Conversions :: IO ()
test_Conversions = keepingSettings' $
  mapM_ testCase cases

  where
    testCase :: (Double, Compounding, Frequency, YearFraction, Compounding, Frequency, Double, Int) -> IO ()
    testCase (r, comp, freq, t, comp2, freq2, expected, prec) = runQLE' $ do
      d1 <- liftIO today
      dc <- actual360
      ir <- interestRate r dc comp freq
      let d2 = addDays (truncate $ 360 * t + 0.5) d1
          (Right compoundf) = compoundFactor' ir d1 d2 d1 d2
          (Right disc) = discountFactor' ir d1 d2 d1 d2
      liftIO $ assertBool $ abs (disc - 1.0/compoundf) <= 1.0e-15
      ir2 <- equivalentRate' ir dc comp freq d1 d2 d1 d2
      liftIO $ assertBool $ abs (rate ir - rate ir2) <= 1.0e-15

      ir3 <- equivalentRate' ir dc comp2 freq2 d1 d2 d1 d2
      expectedIR <- interestRate expected dc comp2 freq2

      roundingPrecision <- rounding' prec Closest 5
      let r3 = applyRounding roundingPrecision (rate ir3)
      liftIO $ assertBool $ abs(r3 - rate expectedIR) <= 1.0e-17

      ir3' <- equivalentRate' ir dc comp2 freq2 d1 d2 d1 d2
      let r3' = applyRounding roundingPrecision (rate ir3')
      liftIO $ assertBool $ abs(r3' - expected) <= 1.0e-17
      return ()

    cases=[
        (0.0800, Compounded,        Quarterly,   1.00, Continuous,            Annual, 0.0792, 4),
        (0.1200, Continuous,           Annual,   1.00, Compounded,            Annual, 0.1275, 4),
        (0.0800, Compounded,        Quarterly,   1.00, Compounded,            Annual, 0.0824, 4),
        (0.0700, Compounded,        Quarterly,   1.00, Compounded,        Semiannual, 0.0706, 4),
        (0.0100, Compounded,           Annual,   1.00,     Simple,            Annual, 0.0100, 4),
        (0.0200,     Simple,           Annual,   1.00, Compounded,            Annual, 0.0200, 4),
        (0.0300, Compounded,       Semiannual,   0.50,     Simple,            Annual, 0.0300, 4),
        (0.0400,     Simple,           Annual,   0.50, Compounded,        Semiannual, 0.0400, 4),
        (0.0500, Compounded, EveryFourthMonth,  1.0/3,     Simple,            Annual, 0.0500, 4),
        (0.0600,     Simple,           Annual,  1.0/3, Compounded,  EveryFourthMonth, 0.0600, 4),
        (0.0500, Compounded,        Quarterly,   0.25,     Simple,            Annual, 0.0500, 4),
        (0.0600,     Simple,           Annual,   0.25, Compounded,         Quarterly, 0.0600, 4),
        (0.0700, Compounded,        Bimonthly,  1.0/6,     Simple,            Annual, 0.0700, 4),
        (0.0800,     Simple,           Annual,  1.0/6, Compounded,         Bimonthly, 0.0800, 4),
        (0.0900, Compounded,          Monthly, 1.0/12,     Simple,            Annual, 0.0900, 4),
        (0.1000,     Simple,           Annual, 1.0/12, Compounded,           Monthly, 0.1000, 4),
        (0.0300, SimpleThenCompounded,       Semiannual,   0.25,               Simple,            Annual, 0.0300, 4),
        (0.0300, SimpleThenCompounded,       Semiannual,   0.25,               Simple,        Semiannual, 0.0300, 4),
        (0.0300, SimpleThenCompounded,       Semiannual,   0.25,               Simple,         Quarterly, 0.0300, 4),
        (0.0300, SimpleThenCompounded,       Semiannual,   0.50,               Simple,            Annual, 0.0300, 4),
        (0.0300, SimpleThenCompounded,       Semiannual,   0.50,               Simple,        Semiannual, 0.0300, 4),
        (0.0300, SimpleThenCompounded,       Semiannual,   0.75,           Compounded,        Semiannual, 0.0300, 4),
        (0.0400,               Simple,       Semiannual,   0.25, SimpleThenCompounded,         Quarterly, 0.0400, 4),
        (0.0400,               Simple,       Semiannual,   0.25, SimpleThenCompounded,        Semiannual, 0.0400, 4),
        (0.0400,               Simple,       Semiannual,   0.25, SimpleThenCompounded,            Annual, 0.0400, 4),
        (0.0400,           Compounded,        Quarterly,   0.50, SimpleThenCompounded,         Quarterly, 0.0400, 4),
        (0.0400,               Simple,       Semiannual,   0.50, SimpleThenCompounded,        Semiannual, 0.0400, 4),
        (0.0400,               Simple,       Semiannual,   0.50, SimpleThenCompounded,            Annual, 0.0400, 4),
        (0.0400,           Compounded,        Quarterly,   0.75, SimpleThenCompounded,         Quarterly, 0.0400, 4),
        (0.0400,           Compounded,       Semiannual,   0.75, SimpleThenCompounded,        Semiannual, 0.0400, 4),
        (0.0400,               Simple,       Semiannual,   0.75, SimpleThenCompounded,            Annual, 0.0400, 4)]

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
