-- Smoke test: the newly-added AnalyticDigitalAmericanKOEngine binding
-- (analyticDigitalAmericanKOEngine, alongside the pre-existing
-- analyticDigitalAmericanEngine).
--
-- Golden values are lifted verbatim from QuantLib's own
-- test-suite/digitaloption.cpp -- testCashAtExpiryOrNothingAmericanValues
-- and testAssetAtExpiryOrNothingAmericanValues -- which is exactly this
-- pair of engines (knockin picks AnalyticDigitalAmericanEngine vs
-- AnalyticDigitalAmericanKOEngine), on a payoff-at-expiry American
-- exercise (only that branch of AnalyticDigitalAmericanEngine::calculate
-- consults knock_in() at all -- the payoff-at-hit branch ignores it).
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckDigitalAmericanKO.hs -o /tmp/checkdigko -outputdir /tmp/checkdigko_build && /tmp/checkdigko
import Control.Monad (forM_)
import Data.Time.Calendar (Day, addDays, fromGregorian)

import SmokeCheck (checkClose)

import QuantLib.Instrument
import QuantLib.Instrument.Option
import QuantLib.InterestRate
import QuantLib.PricingEngine
import QuantLib.Process
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule (dayCounter, DayCounterConstructor(..), Frequency(..))
import QuantLib.TermStructure.Volatility
import QuantLib.TermStructure.Yield

-- (optionType, strike, spot, q, r, tDays, vol, knockIn, expected)
cashOrNothingCases :: [(OptionType, Double, Double, Double, Double, Integer, Double, Bool, Double)]
cashOrNothingCases =
  [ (Put,  100, 105, 0.00, 0.10, 180, 0.20, True,   9.3604)
  , (Call, 100,  95, 0.00, 0.10, 180, 0.20, True,  11.2223)
  , (Put,  100, 105, 0.00, 0.10, 180, 0.20, False,  4.9081)
  , (Call, 100,  95, 0.00, 0.10, 180, 0.20, False,  3.0461)
  ]

assetOrNothingCases :: [(OptionType, Double, Double, Double, Double, Integer, Double, Bool, Double)]
assetOrNothingCases =
  [ (Put,  100, 105, 0.00, 0.10, 180, 0.20, True,  64.8426)
  , (Call, 100,  95, 0.00, 0.10, 180, 0.20, True,  77.7017)
  , (Put,  100, 105, 0.00, 0.10, 180, 0.20, False, 40.1574)
  , (Call, 100,  95, 0.00, 0.10, 180, 0.20, False, 17.2983)
  ]

priceCase :: Day -> (OptionType -> Double -> StrikedPayoff)
          -> (OptionType, Double, Double, Double, Double, Integer, Double, Bool, Double) -> IO Double
priceCase today mkPayoff (ty, strike, spot, q, r, tDays, vol, knockIn, _) = do
  setEvaluationDate $ Just today
  dc <- dayCounter (Actual360 False)
  cal <- calendar Null
  spotQ <- simpleQuote spot
  qQ <- simpleQuote q
  rQ <- simpleQuote r
  volQ <- simpleQuote vol
  qTS <- flatForward' 0 cal qQ dc Continuous Annual
  rTS <- flatForward' 0 cal rQ dc Continuous Annual
  volTS <- blackConstantVol' 0 cal volQ dc
  process <- blackScholesMertonProcess spotQ qTS rTS volTS EulerDiscretization False
  engine <- if knockIn then analyticDigitalAmericanEngine process
                        else analyticDigitalAmericanKOEngine process
  let exDate = addDays tDays today
  opt <- europeanOption (mkPayoff ty strike) (American Nothing exDate True)
    >>= asOneAssetOption >>= asOption >>= asInstrument
  setPricingEngine opt engine
  npv opt

today :: Day
today = fromGregorian 2026 8 28

main :: IO ()
main = do
  putStrLn "Cash-(at-expiry)-or-nothing American digital, vs digitaloption.cpp"
  forM_ cashOrNothingCases $ \c@(_,_,_,_,_,_,_,knockIn,expected) -> do
    v <- priceCase today (\ty s -> CashOrNothing ty s 15.0) c
    checkClose ("cashOrNothing knockIn=" ++ show knockIn) expected v 1e-4

  putStrLn "Asset-(at-expiry)-or-nothing American digital, vs digitaloption.cpp"
  forM_ assetOrNothingCases $ \c@(_,_,_,_,_,_,_,knockIn,expected) -> do
    v <- priceCase today (\ty s -> AssetOrNothing ty s) c
    checkClose ("assetOrNothing knockIn=" ++ show knockIn) expected v 1e-4

  putStrLn "DigitalAmericanKO: OK"
