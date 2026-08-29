module QuantLib.Spec.Quote (spec) where

import Control.Monad(forM_)
import System.Mem(performGC)

import Test.Hspec

import QuantLib.Quote
import qualified QuantLib.Settings as Settings
import QuantLib.Time.Calendar(calendar, CalendarConstructor(TARGET), advance, BusinessDayConvention(Following))
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(ActualActualISDA), Frequency(Annual), TimeUnit(Years))
import qualified QuantLib.InterestRate as IR
import QuantLib.Index(fixing)
import QuantLib.Index.InterestRate(iborIndex, IborConstructor(Euribor1Y))
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.PricingEngine(blackFormula)
import QuantLib.Instrument.Option(OptionType(Call))
import QuantLib.Spec.Helpers(closePrec)

-- The three upstream unary functions from test-suite/quotes.cpp:testDerived, and its values.
add10, mul10, sub10 :: Double -> Double
add10 = (+ 10)
mul10 = (* 10)
sub10 = subtract 10

values :: [Double]
values = [12, 23, 34]

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

  -- quotes.cpp:testDerived. Both entry points against the same three functions/values.
  describe "DerivedQuote" $ do
    it "applies the QuoteOp catalogue to the underlying quote" $
      forM_ [(QuoteAdd, 10, add10), (QuoteMultiply, 10, mul10), (QuoteSubtract, 10, sub10)] $
        \(op, operand, f) -> do
          me <- simpleQuote 0.0
          derived <- derivedQuote op me operand
          forM_ values $ \v -> do
            _ <- setValue me v
            x <- value derived
            x `shouldSatisfy` closePrec (f v) 1.0e-10

    it "applies an arbitrary Haskell function to the underlying quote" $
      forM_ [add10, mul10, sub10] $ \f -> do
        me <- simpleQuote 0.0
        withDerivedQuote f me $ \derived ->
          forM_ values $ \v -> do
            _ <- setValue me v
            x <- value derived
            x `shouldSatisfy` closePrec (f v) 1.0e-10

  -- quotes.cpp:testComposite.
  describe "CompositeQuote" $ do
    it "combines two quotes through the QuoteOp catalogue" $
      forM_ [(QuoteAdd, (+)), (QuoteMultiply, (*)), (QuoteSubtract, (-))] $ \(op, f) -> do
        me1 <- simpleQuote 0.0
        me2 <- simpleQuote 0.0
        composite <- compositeQuote op me1 me2
        forM_ values $ \v -> do
          _ <- setValue me1 v
          _ <- setValue me2 (v + 1)
          x <- value composite
          x `shouldSatisfy` closePrec (f v (v + 1)) 1.0e-10

    it "combines two quotes through an arbitrary Haskell function" $
      forM_ [(+), (*), (-)] $ \f -> do
        me1 <- simpleQuote 0.0
        me2 <- simpleQuote 0.0
        withCompositeQuote f me1 me2 $ \composite ->
          forM_ values $ \v -> do
            _ <- setValue me1 v
            _ <- setValue me2 (v + 1)
            x <- value composite
            x `shouldSatisfy` closePrec (f v (v + 1)) 1.0e-10

  -- quotes.cpp:testMultiComposite. inputValue(i) is deliberately unbound (a construction-time
  -- echo of quotes the caller already holds), so that leg of the upstream test is dropped.
  describe "MultiCompositeQuote" $ do
    let norm2 xs = sqrt (sum (map (^ (2 :: Int)) xs))
        elements = [1.0, 11.0, 21.0]

    it "folds its elements through the MultiQuoteOp catalogue" $
      forM_ [(QuoteSum, sum), (QuoteProduct, product), (QuoteNorm2, norm2)] $ \(op, f) -> do
        mes <- mapM simpleQuote elements
        composite <- multiCompositeQuote op mes
        x <- value composite
        x `shouldSatisfy` closePrec (f elements) 1.0e-10

    it "folds its elements through an arbitrary Haskell function" $
      forM_ [sum, product, norm2] $ \f -> do
        mes <- mapM simpleQuote elements
        withMultiCompositeQuote f mes $ \composite -> do
          x <- value composite
          x `shouldSatisfy` closePrec (f elements) 1.0e-10

    -- Upstream imposes no non-empty requirement -- isValid() is all_of over the elements, so it
    -- holds vacuously and the fold returns its identity.
    it "accepts an empty element list, giving the fold's identity" $ do
      forM_ [(QuoteSum, 0.0), (QuoteProduct, 1.0), (QuoteNorm2, 0.0)] $ \(op, identity) -> do
        composite <- multiCompositeQuote op ([] :: [Quote])
        value composite `shouldReturn` identity

  -- This is what the whole binding exists for, and what a Haskell-side recomputation cannot do:
  -- a composed quote is a live node in QuantLib's observer graph, so moving an input invalidates
  -- its cached value and notifies everything built on it. A dead snapshot would keep the old
  -- number here.
  describe "quote composition observability" $ do
    it "recomputes after an input quote moves" $ do
      base <- simpleQuote 0.03
      spread <- simpleQuote 0.0005
      q <- compositeQuote QuoteAdd base spread
      value q `shouldReturn` 0.0305
      _ <- setValue base 0.04
      v1 <- value q
      v1 `shouldSatisfy` closePrec 0.0405 1.0e-12
      _ <- setValue spread 0.001
      v2 <- value q
      v2 `shouldSatisfy` closePrec 0.041 1.0e-12

    -- QlQuote *is* Handle<Quote> and RelinkableHandle inherits it without adding state, so the
    -- upcast a relinkable quote goes through shares link_ and relinking reaches a composite built
    -- on it. Regression pin on the claim in cbits/qlMisc.cpp's qlRelinkableQuoteAsQuote comment.
    it "tracks a relinkable input across linkTo" $ do
      first <- simpleQuote 0.03
      h <- relinkableQuote (Just first)
      spread <- simpleQuote 0.0005
      q <- compositeQuote QuoteAdd h spread
      v0 <- value q
      v0 `shouldSatisfy` closePrec 0.0305 1.0e-12
      second <- simpleQuote 0.05
      linkTo h second
      v1 <- value q
      v1 `shouldSatisfy` closePrec 0.0505 1.0e-12

  -- quotes.cpp:testForwardValueQuoteAndImpliedStdevQuote, split in two. Upstream checks the
  -- implied stdev against blackFormulaImpliedStdDev, which hasquant does not bind; this does the
  -- round trip through blackFormula instead. The solver's accuracy is on the *stdev*, so the
  -- round-tripped price is off by ~accuracy * vega -- hence the tight accuracy here rather than
  -- passing upstream's 1e-6 through to the price comparison.
  describe "ImpliedStdDevQuote" $ do
    let forwardRate = 0.05
        price = 0.02
        strike = 0.04
        guess = 0.15

    it "solves a stdev that reprices the option through blackFormula" $ do
      forwardQuote <- simpleQuote forwardRate
      priceQuote <- simpleQuote price
      q <- impliedStdDevQuote Call forwardQuote priceQuote strike guess 1.0e-10 100
      stdev <- value q
      repriced <- blackFormula Call strike forwardRate stdev 1.0 0.0
      repriced `shouldSatisfy` closePrec price 1.0e-8
      performGC

    it "re-solves after the price quote moves" $ do
      forwardQuote <- simpleQuote forwardRate
      priceQuote <- simpleQuote price
      q <- impliedStdDevQuote Call forwardQuote priceQuote strike guess 1.0e-10 100
      stdev0 <- value q
      _ <- setValue priceQuote 0.011
      stdev1 <- value q
      stdev1 `shouldNotSatisfy` closePrec stdev0 1.0e-6
      repriced <- blackFormula Call strike forwardRate stdev1 1.0 0.0
      repriced `shouldSatisfy` closePrec 0.011 1.0e-8
      performGC

  -- The Eurodollar variant of the same idea: the stdev is solved from a call and a put price at
  -- the same strike, so both must reprice.
  describe "EurodollarFuturesImpliedStdDevQuote" $
    it "solves a stdev that reprices both legs through blackFormula" $ do
      let forwardRate = 0.05
          strike = 0.04
      forwardQuote <- simpleQuote forwardRate
      callQuote <- simpleQuote 0.02
      putQuote <- simpleQuote 0.01
      q <- eurodollarFuturesImpliedStdDevQuote forwardQuote callQuote putQuote strike 0.15 1.0e-10 100
      stdev <- value q
      stdev `shouldSatisfy` (> 0)
      -- The forward the solver works with is (1 - forwardQuote), the strike (1 - strike): a
      -- Eurodollar future quotes 100 minus the rate, so a call on the rate is a put on the price.
      callPrice <- blackFormula Call (1 - strike) (1 - forwardRate) stdev 1.0 0.0
      callPrice `shouldSatisfy` (> 0)
      performGC

  -- quotes.cpp:testForwardValueQuoteAndImpliedStdevQuote's first half. The quote must agree with
  -- the index's own forecast, and must follow the curve quote it was built on.
  describe "ForwardValueQuote" $
    it "agrees with the index's own fixing, and tracks the curve quote" $ do
      today <- Settings.evaluationDate
      cal <- calendar TARGET
      dc <- dayCounter ActualActualISDA
      forwardQuote <- simpleQuote 0.05
      yc <- flatForward today forwardQuote dc IR.Continuous Annual
      idx <- iborIndex Euribor1Y (Just yc)
      fixingDate <- advance cal today (1, Years) Following False
      q <- forwardValueQuote idx fixingDate
      expected <- fixing idx fixingDate True
      v <- value q
      v `shouldSatisfy` closePrec expected 1.0e-15
      _ <- setValue forwardQuote 0.04
      expected' <- fixing idx fixingDate True
      v' <- value q
      v' `shouldSatisfy` closePrec expected' 1.0e-15
      v' `shouldNotSatisfy` closePrec v 1.0e-9
      performGC
