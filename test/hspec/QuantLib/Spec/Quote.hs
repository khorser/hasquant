module QuantLib.Spec.Quote (spec) where

import Test.Hspec

import QuantLib.Quote
import QuantLib.Spec.Helpers(closePrec)

spec :: Spec
spec =
  -- Ported from quotes.cpp:testObservable's core mechanic (the value round-trip); the
  -- Flag/registerWith observer-notification check in that test has no hasquant binding.
  describe "SimpleQuote" $
    it "round-trips value/setValue, with setValue returning the change" $ do
      q <- simpleQuote 0.0
      value q `shouldReturn` 0.0
      setValue q 3.14 `shouldReturn` 3.14
      value q `shouldReturn` 3.14
      diff <- setValue q 1.0
      diff `shouldSatisfy` closePrec (1.0 - 3.14) 1.0e-9
      value q `shouldReturn` 1.0
