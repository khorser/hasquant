-- Exercises callback coordinates and borrowed-result aliasing through the public binding.
import Control.Monad (unless)
import qualified Data.Vector.Storable as V
import QuantLib.Math (FdmScheme(Douglas))
import QuantLib.Method (fdmRollback)

check :: String -> V.Vector Double -> [Double] -> IO ()
check name actual expected = unless (V.toList actual == expected) $
  error (name ++ ": " ++ show actual ++ " /= " ++ show expected)

main :: IO ()
main = do
  let grid = V.fromList [1, 2, 3, 4]
      zero _ = V.map (const 0)
      directionZero _ = zero
      identitySolve _ _ _ = id
      roll condition = fdmRollback 1 zero directionZero identitySolve
        (Just condition) V.empty Douglas grid 1 0 1 0
  -- The step condition's input and output share one buffer; returning the input aliases both.
  roll (const id) >>= \v -> check "identity step" v [1, 2, 3, 4]
  -- One Douglas step: dt=2, theta=0.5, times=(1,3), directions=0,1, s=-1.
  let apply (t1, t2) = V.map (const (t1 + 10*t2))
      applyDir d (t1, t2) = V.map (const (fromIntegral d + t1 + 10*t2))
      solve d s (t1, t2) = V.map (+ (100*fromIntegral d + s + t1 + 10*t2))
      step t = V.map (+ (1000*t))
  fdmRollback 2 apply applyDir solve (Just step) V.empty Douglas grid 3 1 1 0
    >>= \v -> check "all callback fields" v [1160, 1161, 1162, 1163]
  putStrLn "FDM callback fields and aliasing: OK"
