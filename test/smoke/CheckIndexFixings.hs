-- Smoke test: exercises the historical-fixings getters (fixing, hasHistoricalFixing,
-- isValidFixingDate) and the batch/clear mutators (addFixings, clearFixings) added
-- alongside the pre-existing addFixing/fixingCalendar. A clean build only proves the
-- shims link; it doesn't prove the fixing actually round-trips through QuantLib's
-- IndexManager singleton, or that clearFixings really empties it out again.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckIndexFixings.hs -o /tmp/checkindexfixings -outputdir /tmp/checkindexfixings_build && /tmp/checkindexfixings
import Data.Time (fromGregorian)

import QuantLib.Index
import qualified QuantLib.Index.InterestRate as IR
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule (TimeUnit(..))

import SmokeCheck (checkClose, checkWith)

main :: IO ()
main = do
  idx <- IR.iborIndex (IR.Euribor (6, Months)) Nothing
  cal <- fixingCalendar idx
  d1 <- adjust cal (fromGregorian 2023 01 02) Following
  d2 <- adjust cal (fromGregorian 2023 02 01) Following
  d3 <- adjust cal (fromGregorian 2023 03 01) Following

  before <- hasHistoricalFixing idx d1
  checkWith "hasHistoricalFixing before addFixing" "should be False" (not before)

  valid <- isValidFixingDate idx d1
  checkWith "isValidFixingDate on adjusted business day" "should be True" valid

  addFixing idx d1 0.01 False
  after1 <- hasHistoricalFixing idx d1
  checkWith "hasHistoricalFixing after addFixing" "should be True" after1
  v1 <- fixing idx d1 False
  checkClose "fixing round-trips addFixing" 0.01 v1 1e-12

  addFixings idx [(d2, 0.02), (d3, 0.03)] False
  v2 <- fixing idx d2 False
  checkClose "fixing after addFixings (d2)" 0.02 v2 1e-12
  v3 <- fixing idx d3 False
  checkClose "fixing after addFixings (d3)" 0.03 v3 1e-12

  clearFixings idx
  after2 <- hasHistoricalFixing idx d1
  checkWith "hasHistoricalFixing after clearFixings" "should be False" (not after2)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
