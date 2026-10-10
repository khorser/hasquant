-- Longstaff-Schwartz regression split into fit and evaluate: stored coefficients must reproduce
-- the combined calls bit for bit, the one-column scalar basis included. States stay inside (-1, 1),
-- where Chebyshev's weighted basis is defined.
module QuantLib.Spec.Method (spec) where

import Control.Exception (evaluate, try, SomeException)
import Control.Monad (forM_)
import Data.Either (isLeft)
import qualified Data.Vector.Storable as V
import GHC.Float (castDoubleToWord64)
import Test.Hspec

import QuantLib.Math
import QuantLib.Method

spec :: Spec
spec = describe "Longstaff-Schwartz fit and evaluate (QuantLib.Method)" $ do
  it "reproduces the combined regression bit for bit" $
    forM_ [(p, o, d) | p <- [Monomial, Laguerre, Hermite, Legendre, Chebyshev], o <- [1, 2, 3], d <- [1, 2, 3]] $ \(p, o, d) -> do
      let fitStates = states d fitRows 0.6180339887
          evalStates = states d evalRows 0.4142135623
          targets = V.fromList [target (row d 0.6180339887 i) | i <- [0 .. fitRows - 1]]
      coefficients <- lsmFit p o (matrix d fitRows fitStates) targets
      split <- lsmEvaluate p o coefficients (matrix d evalRows evalStates)
      combined <- if d == 1
        then lsmRegress p o (V.fromList fitStates) targets (V.fromList evalStates)
        else lsmRegressMulti p o (matrix d fitRows fitStates) targets (matrix d evalRows evalStates)
      (p, o, d, V.length coefficients) `shouldBe` (p, o, d, fromIntegral (lsmBasisSize d o))
      (p, o, d, bits split) `shouldBe` (p, o, d, bits combined)
  it "refuses coefficients that do not fit the basis" $ do
    coefficients <- lsmFit Monomial 2 (matrix 2 fitRows (states 2 fitRows 0.6180339887))
      (V.fromList [target (row 2 0.6180339887 i) | i <- [0 .. fitRows - 1]])
    result <- try (lsmEvaluate Monomial 2 (V.init coefficients) (matrix 2 evalRows (states 2 evalRows 0.4142135623)) >>= evaluate)
    isLeft (result :: Either SomeException RealVector) `shouldBe` True
  it "names its build" $
    lsmEvaluatorIdentity `shouldContain` "QuantLib"
  where
    fitRows = 40
    evalRows = 7
    bits = map castDoubleToWord64 . V.toList
    target xs = sum (map (exp . negate) xs) + product xs
    row :: Word -> Double -> Word -> [Double]
    row d step i = [1.6 * snd (properFraction (fromIntegral (i + 1) * step * fromIntegral k) :: (Int, Double)) - 0.8 | k <- [1 .. d]]
    states d n step = concat [row d step i | i <- [0 .. n - 1]]
    matrix d n xs = either error id (realMatrixFromVector n d (V.fromList xs))
