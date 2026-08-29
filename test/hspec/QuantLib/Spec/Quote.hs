module QuantLib.Spec.Quote (spec) where

import Test.Hspec

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date
import QuantLib.Time.Calendar(calendar, advance, CalendarConstructor(..), BusinessDayConvention(..))
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..), TimeUnit(..), Frequency(..))
import QuantLib.InterestRate(Compounding(..))
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.Index(fixing)
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(..))
import QuantLib.Quote
import QuantLib.Spec.Helpers(closePrec)

spec :: Spec
spec = do
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

  -- Ported from quotes.cpp::testForwardValueQuoteAndImpliedStdevQuote's forward-value-quote
  -- half only: 'CompositeQuote'/'DerivedQuote'/'ImpliedStdDevQuote' have no hasquant binding, so
  -- the observer-chain and implied-stdev portions of that test aren't portable.
  describe "ForwardValueQuote" $
    it "matches the underlying index's own forecast fixing, before and after the forward curve moves" $
      Settings.keepingSettings' $ do
        evalDate <- today
        Settings.setEvaluationDate (Just evalDate)
        dc <- dayCounter ActualActualISDA
        forwardQ <- simpleQuote 0.05
        yc <- flatForward evalDate forwardQ dc Continuous Annual
        euribor <- iborIndex Euribor1Y (Just yc)
        tgt <- calendar TARGET
        fixingDate <- advance tgt evalDate (1, Years) Following False
        fvQ <- forwardValueQuote euribor fixingDate
        forwardValue <- value fvQ
        expectedForwardValue <- fixing euribor fixingDate True
        forwardValue `shouldSatisfy` closePrec expectedForwardValue 1.0e-12

        -- the observer chain: moving the underlying quote moves the forward-value quote too
        _ <- setValue forwardQ 0.04
        forwardValue' <- value fvQ
        expectedForwardValue' <- fixing euribor fixingDate True
        forwardValue' `shouldSatisfy` closePrec expectedForwardValue' 1.0e-12
        forwardValue' `shouldNotSatisfy` closePrec forwardValue 1.0e-6
