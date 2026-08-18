-- Smoke test for the two new SwaptionHelper constructors, swaptionHelperFromDate
-- and swaptionHelperFromDates (QuantLib/Model.chs), added alongside the existing
-- Period-based swaptionHelper.
--
-- SwaptionHelper::performCalculations (swaptionhelper.cpp) derives exerciseDate/
-- startDate/endDate from (maturity, length) when built via the Period-based
-- constructor. This test reproduces that derivation independently in Haskell via
-- Calendar.advance, then feeds the resulting Dates into swaptionHelperFromDate/
-- swaptionHelperFromDates and checks the three constructors -- which take the
-- exercise/tenor in three different shapes but the same trailing 12 params --
-- price identically. A swapped constructor argument (e.g. exerciseDate/endDate
-- transposed in the cbits shim) would either make this fail to build or make
-- the prices diverge; a wrong trailing-param wire-up (e.g. shift and strike
-- transposed) would also break the match against the Period-based baseline.
--
-- It also checks that transposing exerciseDate/endDate in
-- swaptionHelperFromDates (endDate before exerciseDate) is rejected, which
-- guards against exactly that kind of argument-order bug going undetected.
--
-- Run with: cabal exec -- ghc -package hasquant smoke/SwaptionHelperConstructors.hs -o /tmp/swhctors -outputdir /tmp/swhctors_build && /tmp/swhctors
import Control.Exception (SomeException, try)
import Control.Monad (unless)
import System.Exit (exitFailure)

import qualified QuantLib.CashFlow as CF
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.InterestRate
import QuantLib.Model
import QuantLib.Quote
import qualified QuantLib.TermStructure.Yield as TS
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

main :: IO ()
main = do
  cal <- calendar TARGET
  today <- evaluationDate >>= \d -> adjust cal d Following
  setEvaluationDate (Just today)
  settl <- advance cal today (2, Days) Following False
  dc365 <- dayCounter Actual365FixedStandard
  thirty360bb <- dayCounter Thirty360BondBasis
  act360 <- dayCounter (Actual360 False)
  flatQ <- simpleQuote 0.03
  ts <- TS.flatForward settl flatQ dc365 Continuous Annual
  euribor6m <- IR.iborIndex IR.Euribor6M (Just ts)
  volQ <- simpleQuote 0.15

  let maturity = (5, Years) :: (Word, TimeUnit)
      len = (5, Years) :: (Word, TimeUnit)
      fixedLegTenor = (1, Years) :: (Word, TimeUnit)
      maturityI = (5, Years) :: (Int, TimeUnit)
      lenI = (5, Years) :: (Int, TimeUnit)
      settlementDays = Just 2 -- avoids index valueDate lookup; matches the Euribor6M fixing-days branch below
      mkHelper h = h volQ euribor6m fixedLegTenor thirty360bb act360 ts RelativePriceError Nothing 1.0 ShiftedLognormal 0.0 settlementDays CF.AveragingCompound

  hPeriod <- mkHelper (swaptionHelper maturity len)

  -- Reproduce SwaptionHelper::performCalculations' date derivation.
  exerciseDate <- advance cal settl maturityI ModifiedFollowing False
  hFromDate <- mkHelper (swaptionHelperFromDate exerciseDate len)

  startDate <- advance cal exerciseDate (2, Days) ModifiedFollowing False
  endDate <- advance cal startDate lenI ModifiedFollowing False
  hFromDates <- mkHelper (swaptionHelperFromDates exerciseDate endDate)

  let vol = 0.15
  pPeriod <- blackPrice hPeriod vol
  pFromDate <- blackPrice hFromDate vol
  pFromDates <- blackPrice hFromDates vol
  putStrLn ("swaptionHelper blackPrice: " ++ show pPeriod)
  putStrLn ("swaptionHelperFromDate blackPrice: " ++ show pFromDate)
  putStrLn ("swaptionHelperFromDates blackPrice: " ++ show pFromDates)

  let close a b = abs (a - b) < 1e-8 * max 1 (abs a)
  unless (close pPeriod pFromDate && close pPeriod pFromDates) $ do
    putStrLn "MISMATCH: the three SwaptionHelper constructors should price identically for equivalent dates"
    exitFailure

  -- exerciseDate/endDate transposed should be rejected (end before start).
  r <- try (mkHelper (swaptionHelperFromDates endDate exerciseDate) >>= \h -> blackPrice h vol) :: IO (Either SomeException Double)
  case r of
    Left _ -> putStrLn "OK: transposed exerciseDate/endDate correctly rejected"
    Right v -> do
      putStrLn ("MISMATCH: transposed exerciseDate/endDate should have failed, got " ++ show v)
      exitFailure

  putStrLn "SwaptionHelperConstructors smoke test passed"
