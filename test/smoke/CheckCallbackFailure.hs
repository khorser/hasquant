-- Callback exceptions must return through C++, preserving their Haskell type and payload.
import Control.Exception (Exception, throw, try)
import Control.Monad (unless, void)
import qualified Data.Vector.Storable as V
import QuantLib.Context (collectGarbage)
import QuantLib.Math (FdmScheme(Douglas), optimize, OptimizationMethod(Simplex), EndCriteria(..))
import QuantLib.Instrument.Option (withCustomPayoff, withCustomBasketPayoff)
import qualified QuantLib.Process as P
import QuantLib.Method
import qualified QuantLib.Quote as Q

newtype CallbackFailure = CallbackFailure Int deriving (Eq, Show)
instance Exception CallbackFailure

checkFailure :: String -> IO a -> IO ()
checkFailure label action = do
  result <- try (void action)
  unless (result == Left (CallbackFailure 73)) $
    error (label ++ ": callback exception was lost: " ++ show result)

main :: IO ()
main = do
  q <- Q.simpleQuote 2
  let failure = throw (CallbackFailure 73)
      zero _ = V.map (const 0)
      directionZero _ = zero
      identitySolve _ _ _ = id
      roll apply direction solve step = fdmRollback 1 apply direction solve step
        V.empty Douglas (V.fromList [1, 2, 3]) 1 0 1 0
  broken <- Q.withDerivedQuote (const failure) q pure
  collectGarbage
  checkFailure "escaped quote" (Q.value broken)
  checkFailure "composite quote" (Q.withCompositeQuote (\_ _ -> failure) q q Q.value)
  checkFailure "array quote" (Q.withMultiCompositeQuote (const failure) [q, q] Q.value)
  checkFailure "FDM apply" (roll (\_ _ -> failure) directionZero identitySolve Nothing)
  checkFailure "FDM direction" (roll zero (\_ _ _ -> failure) identitySolve Nothing)
  checkFailure "FDM solve" (roll zero directionZero (\_ _ _ _ -> failure) Nothing)
  checkFailure "FDM step" (roll zero directionZero identitySolve (Just (\_ _ -> failure)))
  mesh <- uniform1dMesher 0 2 3 >>= fdmMesherComposite . (: [])
  inner <- withCustomFdmInnerValueCalculator mesh (\_ _ -> failure) (\_ _ -> failure) pure
  checkFailure "inner value" (fdmInnerValue inner mesh [1] 0)
  checkFailure "average inner value" (fdmAvgInnerValue inner mesh [1] 0)
  payoff <- withCustomPayoff "failure" "failure" (const failure) pure
  payoffCalc <- fdmCellAveragingInnerValue payoff mesh 0
  checkFailure "payoff" (fdmInnerValue payoffCalc mesh [1] 0)
  base <- withCustomPayoff "identity" "identity" id pure
  mapped <- withCustomCellAveragingInnerValue base mesh 0 (const failure) pure
  checkFailure "grid mapping" (fdmInnerValue mapped mesh [1] 0)
  basket <- withCustomBasketPayoff base (const failure) pure
  basketCalc <- fdmLogBasketInnerValue basket mesh
  checkFailure "basket accumulation" (fdmInnerValue basketCalc mesh [1] 0)
  process <- P.withExtendedOrnsteinUhlenbeckProcess 1 0.2 0 (const failure) P.MidPoint 1e-6 pure
  checkFailure "extended OU level" (P.evolve process 0 [0] 0.1 [0])
  checkFailure "optimizer" (optimize (const failure) (V.fromList [0, 1]) Nothing
    (Simplex 0.1) (EndCriteria 100 10 1e-8 1e-8 1e-8))
  -- A subsequent call must not inherit the previous native error slot.
  Q.value q >>= \v -> unless (v == 2) (error "error state leaked into a later call")
  collectGarbage
  putStrLn "Callback exceptions: OK"
