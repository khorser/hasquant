-- Smoke test for the quote-composition bindings (derivedQuote / compositeQuote /
-- multiCompositeQuote and their withX callback forms).
--
-- The hspec specs check the arithmetic. What they cannot check is the claim the bindings exist
-- for: a composed quote is a live node in QuantLib's observer graph, so a *curve* bootstrapped
-- off one keeps tracking its inputs. This drives that end to end -- build a flatForward off
-- `base + spread`, read a discount factor, move `base`, read again -- which is exactly the thing
-- a Haskell-side recomputation could not do, since a snapshot quote never notifies the curve.
--
-- Also pins the FunPtr-lifetime contract for the callback forms: everything that reads the quote
-- must happen inside the continuation, and the curve built inside one keeps working there.
--
-- Run with:
--   cabal exec -- ghc -package hasquant test/smoke/CheckQuoteComposition.hs \
--     -o /tmp/checkquotecomp -outputdir /tmp/checkquotecomp_build && /tmp/checkquotecomp
import Data.Time.Calendar(Day, fromGregorian)
import System.Mem(performGC)

import QuantLib.InterestRate
import QuantLib.Quote
import QuantLib.Settings
import QuantLib.Time.Schedule
import QuantLib.TermStructure.Yield(flatForward, discount')


import SmokeCheck

evalDate :: Day
evalDate = fromGregorian 2024 3 15

maturity :: Day
maturity = fromGregorian 2029 3 15

main :: IO ()
main = do
  setEvaluationDate (Just evalDate)
  dc <- dayCounter Actual365FixedStandard

  -- 1. A curve built on a catalogue composite tracks both of its inputs.
  base <- simpleQuote 0.03
  spread <- simpleQuote 0.0005
  q <- compositeQuote QuoteAdd base spread
  checkClose "composite quote value" 0.0305 `flip` 1.0e-12 =<< value q

  curve <- flatForward evalDate q dc Continuous Annual
  df0 <- discount' curve maturity True
  _ <- setValue base 0.04
  df1 <- discount' curve maturity True
  checkWith "curve reprices after base quote moves"
    "discount factor must change, i.e. the curve heard the notification" (df0 /= df1)
  -- The whole point: not merely "different", but exactly the curve for the new composed rate.
  ref <- simpleQuote 0.0405 >>= \r -> flatForward evalDate r dc Continuous Annual
  dfRef <- discount' ref maturity True
  checkClose "curve matches the composed rate 0.0405" dfRef df1 1.0e-14

  _ <- setValue spread 0.001
  df2 <- discount' curve maturity True
  ref2 <- simpleQuote 0.041 >>= \r -> flatForward evalDate r dc Continuous Annual
  dfRef2 <- discount' ref2 maturity True
  checkClose "curve matches after the spread quote moves too" dfRef2 df2 1.0e-14

  -- 2. Same, through an arbitrary Haskell function. Everything that reads the quote -- curve
  -- construction *and* every discount call -- stays inside the continuation.
  base' <- simpleQuote 0.03
  withDerivedQuote (\x -> x * 1.5) base' $ \dq -> do
    checkClose "derived quote value" 0.045 `flip` 1.0e-12 =<< value dq
    curve' <- flatForward evalDate dq dc Continuous Annual
    dfA <- discount' curve' maturity True
    _ <- setValue base' 0.02
    dfB <- discount' curve' maturity True
    refB <- simpleQuote 0.03 >>= \r -> flatForward evalDate r dc Continuous Annual
    dfRefB <- discount' refB maturity True
    checkWith "callback-derived curve moved" "discount factor must change" (dfA /= dfB)
    checkClose "callback-derived curve matches f(0.02) = 0.03" dfRefB dfB 1.0e-14

  -- 3. A multi-composite fold, catalogue and callback, over three live inputs.
  q1 <- simpleQuote 0.01
  q2 <- simpleQuote 0.02
  q3 <- simpleQuote 0.03
  let qs = [q1, q2, q3]
  s <- multiCompositeQuote QuoteSum qs
  checkClose "multi-composite sum" 0.06 `flip` 1.0e-12 =<< value s
  _ <- setValue q1 0.04
  checkClose "multi-composite sum after an input moves" 0.09 `flip` 1.0e-12 =<< value s

  withMultiCompositeQuote (\xs -> sum xs / fromIntegral (length xs)) qs $ \avg -> do
    checkClose "multi-composite average (callback)" 0.03 `flip` 1.0e-12 =<< value avg
    _ <- setValue q1 0.01
    checkClose "multi-composite average after an input moves" 0.02 `flip` 1.0e-12 =<< value avg

  performGC
  putStrLn "all quote-composition checks passed"
