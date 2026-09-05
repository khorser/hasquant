-- Smoke test for the SwaptionVolatilityMatrix leaf type added alongside the exclusion-audit
-- leaf-widening pass (SwaptionVolatilityMatrix::locate). SwaptionVolatilityMatrix used to
-- construct straight to the generic SwaptionVolatilityStructure; it is now its own concrete
-- leaf one AnyOf layer under SwaptionVolatilityStructure (mirrors SabrSwaptionVolatilityCube/
-- InterpolatedSwaptionVolatilityCube), so this checks the upcast-on-peek machinery actually
-- resolves to the right concrete type at both the concrete leaf level and after widening two
-- AnyOf layers up to the ultimate VolatilityTermStructure root.
--
-- Checks:
--  1. swaptionVolatilityMatrixLocate (concrete-leaf-only) resolves correctly on a freshly
--     constructed matrix.
--  2. The same value, passed where a generic SwaptionVolatilityStructure is expected
--     (volatilityForPeriod'), upcasts correctly and recovers the exact input volatility.
--  3. asVolatilityTermStructure (two AnyOf layers up: SwaptionVolatilityMatrix ->
--     SwaptionVolatilityStructure -> VolatilityTermStructure) still resolves to a live object
--     whose referenceDate matches what the matrix was built with.
--
-- Run with: .claude/skills/run-hasquant/driver.sh test/smoke/SwaptionVolatilityMatrixLeaf.hs
import Control.Monad (unless)
import System.Exit (exitFailure)
import qualified Data.Vector.Storable as V

import QuantLib.InterestRate (VolatilityType(ShiftedLognormal))
import QuantLib.Math (Matrix(..), RealMatrix, realMatrixFromVector, objectMatrix)
import qualified QuantLib.Quote as Q
import QuantLib.TermStructure (referenceDate)
import qualified QuantLib.TermStructure.Volatility as Vol
import QuantLib.TermStructure.Volatility (asVolatilityTermStructure)
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.Settings

close :: Double -> Double -> Bool
close a b = abs (a - b) < 1e-9

main :: IO ()
main = do
  cal <- calendar TARGET
  today <- evaluationDate >>= \d -> adjust cal d Following
  setEvaluationDate (Just today)
  dc <- dayCounter Actual365FixedStandard

  let optionTenors = [(1, Years), (5, Years)]
      swapTenors = [(2, Years), (10, Years)]
      vols = [0.10, 0.20, 0.30, 0.40]
      shiftMatrix = either error id (realMatrixFromVector 0 0 V.empty) :: RealMatrix

  volQuotes <- mapM Q.simpleQuote vols
  let volMatrix = either error id (objectMatrix 2 2 volQuotes)

  grid <- Vol.swaptionVolatilityMatrix' today cal ModifiedFollowing optionTenors swapTenors
            volMatrix dc False ShiftedLognormal shiftMatrix

  -- 1. concrete-leaf-only getter
  optionDate0 <- advance cal today (1, Years) ModifiedFollowing False
  (i0, j0) <- Vol.swaptionVolatilityMatrixLocate grid optionDate0 (2, Years)
  unless (i0 == 0 && j0 == 0) $ do
    putStrLn ("MISMATCH: locate at the lowest grid corner should be (0,0), got " ++ show (i0, j0))
    exitFailure
  putStrLn "OK: swaptionVolatilityMatrixLocate resolves the concrete leaf"

  -- 2. one AnyOf layer up: passed where a generic SwaptionVolatilityStructure is expected
  v <- Vol.volatilityForPeriod' grid optionDate0 (2, Years) 0.02 False
  unless (close v 0.10) $ do
    putStrLn ("MISMATCH: volatilityForPeriod' should recover 0.10 at this node, got " ++ show v)
    exitFailure
  putStrLn "OK: volatilityForPeriod' upcasts SwaptionVolatilityMatrix to SwaptionVolatilityStructure"

  -- 3. two AnyOf layers up: SwaptionVolatilityMatrix -> SwaptionVolatilityStructure ->
  -- VolatilityTermStructure
  vts <- asVolatilityTermStructure grid
  rd <- referenceDate vts
  unless (rd == today) $ do
    putStrLn ("MISMATCH: asVolatilityTermStructure's referenceDate should be " ++ show today ++ ", got " ++ show rd)
    exitFailure
  putStrLn "OK: asVolatilityTermStructure upcasts two AnyOf layers to VolatilityTermStructure"

  putStrLn "SwaptionVolatilityMatrixLeaf smoke test passed"
