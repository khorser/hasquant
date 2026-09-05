-- | Coverage for the two new getters bound onto 'QuantLib.Instrument.Forward': the FRA's
-- settlement payoff ('amount') and the nominal-ratio FX forward rate ('fxForwardRate'). Both
-- are self-consistency checks against upstream's own closed-form definitions
-- (forwardrateagreement.cpp's @calculateAmount@, fxforward.hpp's inline @forwardRate@) rather
-- than golden values ported from QuantLib's test-suite, which has no dedicated fixture for
-- either.
module QuantLib.Spec.Instrument.Forward (spec) where

import Test.Hspec

import qualified QuantLib.Settings as Settings
import QuantLib.Time.Date
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import QuantLib.InterestRate(Compounding(..))
import qualified QuantLib.InterestRate as IR
import QuantLib.Currency
import qualified QuantLib.Index.InterestRate as I
import QuantLib.Index(fixingCalendar)
import QuantLib.Quote
import QuantLib.TermStructure.Yield hiding(forwardRate)
import QuantLib.Instrument(PositionType(..))
import QuantLib.Instrument.Forward

import QuantLib.Spec.Helpers(closePrec)

spec :: Spec
spec = do
  describe "ForwardRateAgreement" $
    it "amount matches upstream's closed form: notional*sign*(F-K)*T/(1+F*T)" $
      Settings.keepingSettings' $ do
        let today' = 23 `may` 2006
        Settings.setEvaluationDate (Just today')
        q <- simpleQuote 0.035
        dc <- dayCounter (Actual360 False)
        ts <- flatForward today' q dc Continuous Annual
        eu3m <- I.iborIndex I.Euribor3M (Just ts)
        cal <- fixingCalendar eu3m
        idxDC <- I.dayCounter eu3m
        valueDate <- advance cal today' (3, Months) Following False
        maturityDate <- advance cal valueDate (3, Months) Following False
        let strike = 0.03
            notional = 100.0
        fra <- forwardRateAgreement eu3m valueDate maturityDate Long strike notional (Just ts)
        fwdRate <- forwardRate fra
        let f = IR.rate fwdRate
        t <- years idxDC valueDate maturityDate Nothing Nothing
        let expected = notional * (f - strike) * t / (1 + f * t)
        actual <- amount fra
        actual `shouldSatisfy` closePrec expected 1e-8

  describe "FxForward" $
    it "fxForwardRate equals targetNominal/sourceNominal for the nominal-based constructor" $
      Settings.keepingSettings' $ do
        let today' = 23 `may` 2006
        Settings.setEvaluationDate (Just today')
        usd <- currency USD
        eur <- currency EUR
        cal <- calendar TARGET
        maturity <- advance cal today' (6, Months) Following False
        let sourceNominal = 100.0
            targetNominal = 112.34
        fwd <- fxForward sourceNominal usd targetNominal eur maturity True 2 cal
        let r = fxForwardRate fwd
        r `shouldSatisfy` closePrec (targetNominal / sourceNominal) 1e-12

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
