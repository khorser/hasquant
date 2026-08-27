-- |Minimizes a Haskell-defined cost function -- the classic 2D Rosenbrock function
-- @f(x,y) = (1-x)^2 + 100*(y-x^2)^2@, global minimum @f=0@ at @(1,1)@ -- via
-- 'QuantLib.Math.optimize', hasquant's first real callback into Haskell from C++ (see
-- CLAUDE.md's "coarsen the language-boundary crossing" bullet and
-- 'QuantLib.Internal.Type.withCostFunction'). Demonstrates minimizing an arbitrary objective
-- outside 'QuantLib.Model.calibrate''s fixed calibration-error path.
module QuantLib.Example.Optimizer
  (
    Result(..)
  , run
  ) where
import QuantLib.Math

data Result = Result
  { solution :: ![Double]
  , cost :: !Double
  , endCriteriaType :: !EndCriteriaType
  }

rosenbrock :: [Double] -> Double
rosenbrock [x, y] = (1 - x)^(2 :: Int) + 100 * (y - x * x)^(2 :: Int)
rosenbrock _ = error "rosenbrock: expected 2 arguments"

run :: IO Result
run = do
  (sol, c, ec) <- optimize rosenbrock x0 Nothing method endCrit
  return $ Result sol c ec
  where
    x0 = [-1.2, 1.0]
    method = Simplex 0.1
    endCrit = EndCriteria 1000 100 1e-8 1e-8 1e-8

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
