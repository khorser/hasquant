-- Smoke test: Read instances for CalendarConstructor/DayCounterConstructor/IborConstructor.
-- These are hand-written (not `deriving`), since some of their constructors carry live
-- Calendar/Currency/DayCounter objects with no Read instance of their own -- see
-- deriveReadPlain's comment in QuantLib/Internal/Syntax.hs.
--
-- Note the asymmetry this implies, caught by an earlier version of this very test: `show`
-- and `read` are NOT inverses for Joint2/Joint3/Joint4/Business252/Ibor/Libor/
-- DailyTenorLibor/CustomIbor. `deriving instance Show CalendarConstructor` prints a live
-- Calendar field via *its own* Show instance -- the calendar's actual QuantLib name (e.g.
-- "New York stock exchange"), not anything shaped like a CalendarConstructor -- while `Read`
-- expects that field written as a nested CalendarConstructor expression (e.g.
-- "UnitedStatesNYSE"). `read (show x) == x` genuinely fails for these constructors; it's not
-- a bug, it's what "no readable proxy for a live object's *display* form, only for
-- *constructing* one" looks like in practice. So this checks two different things depending
-- on the constructor: `read (show x) == x` for the plain tags and Bespoke (all fields
-- directly Read, so Show/Read really are inverses there), and `read <literal text> ==
-- <independently-constructed value>` for everything with a live field.
{-# LANGUAGE ScopedTypeVariables #-}
import QuantLib.Time.Calendar
import QuantLib.Time.Schedule
import QuantLib.Time.Date
import QuantLib.Currency
import QuantLib.Index.InterestRate hiding (currency, dayCounter)
import Control.Monad

checkRoundTrip :: forall a. (Show a, Read a, Eq a) => String -> a -> IO ()
checkRoundTrip label x
  | read (show x) == x = putStrLn ("OK   " ++ label ++ " round-trips: " ++ show x)
  | otherwise = error ("FAILED round-trip for " ++ label ++ ": " ++ show x
                        ++ " /= read (show ...) = " ++ show (read (show x) :: a))

checkRead :: (Show a, Read a, Eq a) => String -> String -> a -> IO ()
checkRead label literal expected
  | read literal == expected = putStrLn ("OK   " ++ label ++ ": read " ++ show literal)
  | otherwise = error ("FAILED parse for " ++ label ++ ": read " ++ show literal
                        ++ " /= expected value")

main :: IO ()
main = do
  -- plain cross-product tags and Bespoke: all fields directly Read, so show/read really are
  -- inverses here.
  checkRoundTrip "calendar tag" UnitedStatesNYSE
  checkRoundTrip "day counter tag" Thirty360European
  checkRoundTrip "Bespoke" (Bespoke "MyCal" [Saturday, Sunday])

  -- Live values for the Joint2/3/4/Business252/Ibor* Extra constructors, which take actual
  -- Calendar/Currency/DayCounter objects (not tags), same as any other caller would build.
  usd <- currency USD
  nyse <- calendar UnitedStatesNYSE
  lse <- calendar UnitedKingdomExchange
  bespokeCal <- calendar (Bespoke "X" [Saturday])
  govBond <- calendar UnitedStatesGovernmentBond
  thirty360 <- dayCounter Thirty360European
  actual360 <- dayCounter (Actual360 True)

  nestedJoint2 <- calendar (Joint2 bespokeCal lse JoinHolidays)
  checkRead "Joint2 (nested)" "Joint2 UnitedStatesNYSE (Joint2 (Bespoke \"X\" [Saturday]) UnitedKingdomExchange JoinHolidays) JoinBusinessDays"
    (Joint2 nyse nestedJoint2 JoinBusinessDays)
  checkRead "Joint3" "Joint3 UnitedStatesNYSE UnitedKingdomExchange (Bespoke \"X\" [Saturday]) JoinHolidays"
    (Joint3 nyse lse bespokeCal JoinHolidays)
  checkRead "Joint4" "Joint4 UnitedStatesNYSE UnitedKingdomExchange (Bespoke \"X\" [Saturday]) UnitedStatesGovernmentBond JoinHolidays"
    (Joint4 nyse lse bespokeCal govBond JoinHolidays)
  checkRead "Business252" "Business252 UnitedStatesNYSE" (Business252 nyse)

  -- a read-then-materialized live Calendar actually works, not just parses
  let parsedJoint2 = read "Joint2 UnitedStatesNYSE UnitedKingdomExchange JoinBusinessDays" :: CalendarConstructor
  cal <- calendar parsedJoint2
  isWknd <- isWeekend cal Saturday
  putStrLn ("OK   materialized read Joint2: Saturday is weekend = " ++ show isWknd)

  checkRead "Ibor" "Ibor \"MyIndex\" (3,Months) 2 USD UnitedStatesNYSE Following True Thirty360European"
    (Ibor "MyIndex" (3, Months) 2 usd nyse Following True thirty360)
  checkRead "Libor" "Libor \"MyLibor\" (6,Months) 2 USD UnitedKingdomExchange (Actual360 True)"
    (Libor "MyLibor" (6, Months) 2 usd lse actual360)
  checkRead "DailyTenorLibor" "DailyTenorLibor \"MyDaily\" 0 USD UnitedStatesNYSE (Actual360 True)"
    (DailyTenorLibor "MyDaily" 0 usd nyse actual360)
  checkRead "CustomIbor" "CustomIbor \"MyCustom\" (1,Years) 2 USD UnitedStatesNYSE UnitedStatesNYSE UnitedStatesNYSE Following False Thirty360European"
    (CustomIbor "MyCustom" (1, Years) 2 usd nyse nyse nyse Following False thirty360)

  -- ActualActualBond'/ActualActualISMA' carry a Schedule, which has no readable proxy: they
  -- must stay unparseable by design, not silently succeed with a bogus value.
  let noParse = reads "ActualActualBond' (some schedule)" :: [(DayCounterConstructor, String)]
  unless (null noParse) $
    error ("expected no parse for ActualActualBond', got: " ++ show noParse)
  putStrLn "OK   ActualActualBond' is deliberately unparseable (no Schedule proxy)"

  putStrLn "CheckReadConstructors: OK"
