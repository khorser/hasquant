-- Smoke test: construct every OvernightIborIndexType case and print its
-- QuantLib-native name/day-count so a stale c2hs-generated enum (see the
-- reconcile-currencies/reconcile-calendars/add-quantlib-index skills'
-- "gotcha" notes) or a wrong factory-table entry shows up immediately,
-- not just "the build succeeded".
--
-- Run with: cabal exec -- ghc -package hasquant smoke/CheckOvernightIndexes.hs -o /tmp/checkidx -outputdir /tmp/checkidx_build && /tmp/checkidx
import QuantLib.Index.InterestRate
import QuantLib.Index
import Control.Monad

-- c2hs only derives Show/Eq for this enum (no Bounded), so the case list
-- is spelled out explicitly here rather than via [minBound .. maxBound].
main :: IO ()
main = forM_ [Aonia, Eonia, Estr, FedFunds, Nzocr, Sofr, Sonia
             ,Cdi, Corra, Kofr, Destr, Swestr, Shir, Tonar, Saron, Zaronia] $ \ty -> do
  idx <- overnightIborIndex ty Nothing
  ix <- asIndex idx
  putStrLn (show ty ++ " -> " ++ show ix)
