module QuantLib.Spec.Index.Inflation (spec) where

import Test.Hspec

import Data.Time.Calendar(fromGregorian)

import QuantLib.Currency(currency, Ccy(GBP))
import QuantLib.Index.Inflation
import QuantLib.Time.Schedule(Frequency(..), TimeUnit(..))

spec :: Spec
spec =
  describe "needsForecast" $ do
    it "answers for an index built with a frequency QuantLib supports" $ do
      idx <- supportedIndex
      -- A date decades before the availability lag can only be served from a stored fixing.
      needsForecast idx (fromGregorian 1990 1 1) `shouldReturn` False
      yoy <- yoyInflationIndexFromZero idx Nothing
      yoyNeedsForecast yoy (fromGregorian 1990 1 1) `shouldReturn` False

    -- The constructors accept any Frequency, but needsForecast reaches inflationPeriod, which
    -- QL_FAILs outside Annual..Monthly. Nothing on the Haskell side constrains the frequency, so
    -- the shim's own error channel is what makes this an exception rather than an abort through
    -- the FFI boundary.
    it "raises a C++ exception for an index whose frequency inflationPeriod rejects" $ do
      idx <- unsupportedIndex
      needsForecast idx (fromGregorian 1990 1 1) `shouldThrow` anyException
      yoy <- yoyInflationIndexFromZero idx Nothing
      yoyNeedsForecast yoy (fromGregorian 1990 1 1) `shouldThrow` anyException
  where
    mkIndex freq = do
      uk <- region UKRegion
      gbp <- currency GBP
      customZeroInflationIndex "smoke RPI" uk False freq (2, Months) gbp Nothing
    supportedIndex = mkIndex Monthly
    unsupportedIndex = mkIndex Weekly

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
