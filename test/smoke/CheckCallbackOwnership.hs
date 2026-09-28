-- Exercise callbacks after both their continuation and intermediate owners have disappeared.
import Control.Exception (ErrorCall, try)
import Control.Monad (unless)
import Data.Time.Calendar (fromGregorian)
import QuantLib.Context (collectGarbage)
import QuantLib.Method
import QuantLib.Instrument.Option (withCustomPayoff)
import qualified QuantLib.Quote as Q
import qualified QuantLib.Process as P
import qualified QuantLib.TermStructure.Yield as Y
import qualified QuantLib.InterestRate as IR
import QuantLib.Time.Schedule (dayCounter, DayCounterConstructor(Actual365FixedStandard), Frequency(Annual))

check :: String -> Double -> Double -> IO ()
check label expected actual = unless (abs (actual - expected) < 1.0e-10) $
  error (label ++ ": " ++ show actual ++ " /= " ++ show expected)

main :: IO ()
main = do
  q <- Q.simpleQuote 2
  direct <- Q.withDerivedQuote (* 3) q pure
  dependent <- Q.withCompositeQuote (+) q q $ \custom ->
    Q.derivedQuote Q.QuoteMultiply custom 5
  array <- Q.withMultiCompositeQuote sum [q, q] pure
  mesh <- uniform1dMesher 0 2 3 >>= fdmMesherComposite . (: [])
  calculator <- withCustomFdmInnerValueCalculator mesh
    (\t xs -> t + sum xs) (\t xs -> 2*t + sum xs) pure
  payoff <- withCustomPayoff "escaped" "escaped callback owner" (* 7) pure
  collectGarbage
  -- The ADT itself must own the callback, even before any native payoff exists.
  payoffCalculator <- fdmCellAveragingInnerValue payoff mesh 0
  mapped <- withCustomCellAveragingInnerValue payoff mesh 0 (+ 1) pure
  collectGarbage
  Q.value direct >>= check "direct quote" 6
  Q.value dependent >>= check "native dependent" 20
  Q.value array >>= check "array quote" 4
  _ <- Q.setValue q 4
  Q.value direct >>= check "live direct quote" 12
  Q.value dependent >>= check "live native dependent" 40
  fdmInnerValue calculator mesh [1] 3 >>= check "inner value" 4
  fdmAvgInnerValue calculator mesh [1] 3 >>= check "average inner value" 7
  fdmInnerValue payoffCalculator mesh [1] 0 >>= check "escaped payoff ADT" 7
  fdmInnerValue mapped mesh [1] 0 >>= check "escaped grid mapping" 14
  process <- P.withExtendedOrnsteinUhlenbeckProcess 1 0.2 0 (const 3) P.MidPoint 1e-6 pure
  collectGarbage
  values <- P.evolve process 0 [0] 0.1 [0]
  case values of
    [v] -> check "escaped extended OU callback" (3 * (1 - exp (-0.1))) v
    _ -> error "unexpected OU state shape"
  dc <- dayCounter Actual365FixedStandard
  q1 <- Q.simpleQuote 0.03
  q2 <- Q.simpleQuote 0.01
  c1 <- Y.flatForward (Y.ReferenceDate (fromGregorian 2025 10 23)) q1 dc IR.Continuous Annual
  c2 <- Y.flatForward (Y.ReferenceDate (fromGregorian 2025 10 23)) q2 dc IR.Continuous Annual
  curve <- Y.withCompositeZeroYieldStructure (-) c1 c2 IR.Continuous Annual pure
  broken <- Y.withCompositeZeroYieldStructure (\_ _ -> error "curve callback failure")
    c1 c2 IR.Continuous Annual pure
  collectGarbage
  Y.discount curve (Y.TimePoint 1) False >>= check "escaped composite yield callback" (exp (-0.02))
  failure <- try (Y.discount broken (Y.TimePoint 1) False) :: IO (Either ErrorCall Double)
  case failure of
    Left _ -> pure ()
    Right _ -> error "composite yield callback exception was lost"
  collectGarbage
  putStrLn "Callback ownership: OK"
