-- Smoke test: construct the newly-reconciled calendar countries and check
-- a basic weekend query, catching a stale c2hs-generated enum or a wrong
-- CalendarCountry/calendars[] factory-table order mismatch (see the
-- reconcile-calendars skill's "gotcha" note) that a successful build
-- alone wouldn't reveal.
--
-- Run with: cabal exec -- ghc -package hasquant smoke/CheckCalendars.hs -o /tmp/checkcal -outputdir /tmp/checkcal_build && /tmp/checkcal
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import Control.Monad

-- All market-less (single-market, so no separate Market enum exposed --
-- see reconcile-calendars skill) countries added by reconciling against
-- ql/time/calendars/*.hpp.
newCountries :: [CalendarConstructor]
newCountries = [Chile, Croatia, Malta, Montenegro, NorthMacedonia, Serbia, Slovenia, Uzbekistan]

-- New Market values on already-parameterized countries, plus countries
-- promoted from market-less to parameterized after gaining a multi-value
-- Market enum upstream (reconciled separately from adding whole new
-- countries above).
newMarkets :: [CalendarConstructor]
newMarkets = [UnitedStatesSOFR, IsraelSHIR, IsraelTelbor
             ,AustraliaSettlement, AustraliaASX
             ,NewZealandWellington, NewZealandAuckland
             ,PolandSettlement, PolandWSE]

main :: IO ()
main = do
  forM_ newCountries $ \ty -> do
    cal <- calendar ty
    isWknd <- isWeekend cal Saturday
    putStrLn (show ty ++ ": Saturday is weekend = " ++ show isWknd)
  forM_ newMarkets $ \ty -> do
    cal <- calendar ty
    isWknd <- isWeekend cal Saturday
    putStrLn (show ty ++ ": Saturday is weekend = " ++ show isWknd)
