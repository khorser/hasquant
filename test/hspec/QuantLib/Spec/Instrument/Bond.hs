-- No upstream test-suite fixture exists for BTP or RendistatoCalculator (checked
-- ~/Src/QuantLib/test-suite for btp/rendistato, neither exists), so 'btp' is checked against a
-- hand-built 'fixedRateBond' using btp.cpp's own hardcoded constructor arguments verbatim: the
-- two must agree on everything except accruedAmount, where BTP additionally applies
-- ClosestRounding(5) via its C++ override.
module QuantLib.Spec.Instrument.Bond (spec) where

import Test.Hspec
import Data.List.NonEmpty(fromList)

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import QuantLib.Quote
import QuantLib.TermStructure.Yield(flatForward)
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Instrument.Bond
import qualified QuantLib.CashFlow as CF

import QuantLib.Spec.Helpers(closePrec)

spec :: Spec
spec = describe "Bond (BTP, Rendistato)" $ do
  btpSpec
  rendistatoSpec

btpSpec :: Spec
btpSpec = describe "BTP" $ do
  it "matches a hand-built FixedRateBond using btp.cpp's own hardcoded conventions, except accruedAmount's ClosestRounding(5)" $
    Settings.keepingSettings' $ do
      let maturity = 1 `september` 2030
          start = 1 `september` 2020
          fixedRate = 0.03
          settle = 15 `march` 2025
      Settings.setEvaluationDate (Just start)
      target <- calendar TARGET
      nullCal <- calendar Null
      isma <- dayCounter ActualActualISMA
      sched <- schedule (Just start) maturity (6, Months) nullCal Unadjusted Unadjusted Backward True Nothing Nothing

      b <- btp maturity fixedRate (Just start) Nothing
      ref <- fixedRateBond 2 100.0 sched (fromList [fixedRate]) isma ModifiedFollowing 100.0 Nothing target
        (0, Days) target Unadjusted False isma

      bMat <- maturityDate b
      refMat <- maturityDate ref
      bMat `shouldBe` refMat

      bNotionals <- notionals b
      refNotionals <- notionals ref
      bNotionals `shouldBe` refNotionals

      rawAccrued <- accruedAmount ref settle
      bAccrued <- accruedAmount b settle
      let rounded = fromIntegral (round (rawAccrued * 1e5) :: Integer) / (1e5 :: Double)
      bAccrued `shouldSatisfy` closePrec rounded 1e-9
      -- and the rounding must have actually moved the value -- otherwise this doesn't exercise
      -- ClosestRounding(5) at all.
      abs (rawAccrued - bAccrued) `shouldSatisfy` (> 1e-9)

  it "btpWithRedemption overrides the par redemption" $ do
    b <- btpWithRedemption (1 `september` 2030) 0.03 95.0 (Just (1 `september` 2020)) Nothing
    reds <- redemptions b
    cfs <- CF.cashFlows reds Nothing Nothing
    map (\(_, amt, _) -> amt) cfs `shouldBe` [95.0]

-- Fixture: three BTPs of increasing maturity, equal outstanding, live clean-price quotes, priced
-- against a flat 3% EUR curve. No upstream cached values exist, so these are structural
-- invariants (upstream's own inline formulas for yield\/spread, plus the hardcoded 1..15Y swap
-- ladder, both genuinely pinnable) rather than golden values.
rendistatoSpec :: Spec
rendistatoSpec = describe "RendistatoBasket / RendistatoCalculator" $
  it "aggregates a basket of BTPs against a flat EUR curve" $
    Settings.keepingSettings' $ do
      let today' = 1 `september` 2024
      Settings.setEvaluationDate (Just today')
      dc <- dayCounter Actual365FixedStandard
      q <- simpleQuote 0.03
      curve <- flatForward today' q dc Continuous NoFrequency

      b1 <- btp (1 `september` 2027) 0.025 Nothing Nothing
      b2 <- btp (1 `september` 2030) 0.03 Nothing Nothing
      b3 <- btp (1 `september` 2034) 0.035 Nothing Nothing
      p1 <- simpleQuote 98.0
      p2 <- simpleQuote 97.0
      p3 <- simpleQuote 95.0
      basket <- rendistatoBasket (fromList [(b1, 100.0, p1), (b2, 100.0, p2), (b3, 100.0, p3)])
      rc <- rendistatoCalculator basket (6, Months) (Just curve) curve

      lengths <- rendistatoCalculatorSwapLengths rc
      lengths `shouldBe` [1 .. 15]

      yields <- rendistatoCalculatorYields rc
      length yields `shouldBe` 3

      durations <- rendistatoCalculatorDurations rc
      length durations `shouldBe` 3

      y <- rendistatoCalculatorYield rc
      rate <- rendistatoCalculatorEquivalentSwapRate rc
      spread <- rendistatoCalculatorEquivalentSwapSpread rc
      spread `shouldSatisfy` closePrec (y - rate) 1e-9

      len <- rendistatoCalculatorEquivalentSwapLength rc
      lengthQuote <- rendistatoEquivalentSwapLengthQuote rc
      lengthQuoteValue <- value lengthQuote
      lengthQuoteValue `shouldSatisfy` closePrec len 1e-9

      spreadQuote <- rendistatoEquivalentSwapSpreadQuote rc
      spreadQuoteValue <- value spreadQuote
      spreadQuoteValue `shouldSatisfy` closePrec spread 1e-9

      _ <- rendistatoCalculatorEquivalentSwap rc
      _ <- rendistatoCalculatorSwapRates rc
      _ <- rendistatoCalculatorSwapYields rc
      _ <- rendistatoCalculatorSwapDurations rc
      pure ()
