-- Shared Hspec fixture; compile with -i -itest/smoke -itest/hspec -package hspec -package QuickCheck.
-- This probes model-tag marshalling; numerical repricing belongs in the YoY specifications.
module Main (main) where

import Control.Exception (SomeException, displayException, try)
import Control.Monad (unless)
import Data.List (isInfixOf)
import qualified QuantLib.Context as Context
import QuantLib.Spec.TermStructure.InflationVolatility (setup)
import QuantLib.Math (Interpolation(Linear))
import QuantLib.TermStructure.InflationVolatility
import QuantLib.Time.Calendar (advance, BusinessDayConvention(..))
import QuantLib.Time.Schedule (TimeUnit(Years))

main :: IO ()
main = Context.keepingSettingsGc $ do
  (_, calendar, counter, nominal, index, prices) <- setup
  base <- yoyCapFloorBaseDate prices
  date <- advance calendar base (3, Years) Unadjusted False
  let probe model = do
        surface <- kInterpolatedYoyOptionletVolatilitySurface model 0 calendar ModifiedFollowing counter
                     prices index nominal (-0.5) (Just (1e-6, 0.2)) Linear
        yoyOptionletVolatility surface date 0.025 Nothing True
  black <- try (probe YoyBlack) :: IO (Either SomeException Double)
  unless (case black of Left exception -> "strike + displacement" `isInfixOf` displayException exception; Right _ -> False)
    (fail "Black must reject the fixture's negative floor strikes")
  putStrLn "YoyBlack: native negative-strike domain check reached"
  unit <- probe YoyUnitDisplacedBlack
  normal <- probe YoyBachelier
  unless (unit > 0 && normal > 0 && abs (unit - normal) > 1e-7)
    (fail "unit-displaced Black and Bachelier selectors must reach distinct native models")
  putStrLn ("YoyUnitDisplacedBlack: " ++ show unit)
  putStrLn ("YoyBachelier: " ++ show normal)
