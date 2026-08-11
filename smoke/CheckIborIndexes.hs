-- Smoke test: construct every "plain" IborConstructor case (Standard tenor-based,
-- DailyTenor, and Overnight shapes -- i.e. everything deriveIborConstructor generates from
-- IborIndexType/IborDailyTenorIndexType/IborONIndexType, not the shortcut/generic Extra
-- cases) and assert the constructed index's tenor accessor round-trips the requested tenor.
--
-- This specifically targets two failure modes a successful build alone wouldn't reveal:
-- (1) the original bug where a constructor was added to IborConstructor/iborIndexOrdinal but
-- its iborIndexTenor clause was forgotten (Nibor silently got tenor (0, Days) instead of the
-- requested one); (2) a wrong flat-array offset or a lambda left in the wrong slot in
-- cbits/qlTermStructure.cpp:iborIndices after the IborIndexType/IborDailyTenorIndexType/
-- IborONIndexType split -- either would silently construct the wrong underlying index.
--
-- Run with: cabal exec -- ghc -ismoke -package hasquant smoke/CheckIborIndexes.hs -o /tmp/checkibor -outputdir /tmp/checkibor_build && /tmp/checkibor
import QuantLib.Index.InterestRate
import QuantLib.Time.Schedule (TimeUnit(..))
import Control.Monad

import SmokeCheck (checkEq)

standardCases :: [IborConstructor]
standardCases =
  [ Bbsw t, Bibor t, Bkbm t, Cdor t
  , EurLibor t, AudLibor t, CadLibor t, ChfLibor t, DkkLibor t, GbpLibor t
  , JpyLibor t, NzdLibor t, SekLibor t, UsdLibor t
  , Euribor t, Euribor365 t, Jibar t, Mosprime t, Pribor t, Robor t, Shibor t
  , THBFIX t, TRLibor t, Tibor t, Wibor t, Zibor t, Nibor t
  ]
  where t = (3, Months)

dailyTenorCases :: [IborConstructor]
dailyTenorCases =
  [EurDailyTenorLibor 1, ChfDailyTenorLibor 1, GbpDailyTenorLibor 1, JpyDailyTenorLibor 1, UsdDailyTenorLibor 1]

overnightCases :: [IborConstructor]
overnightCases = [CadLiborON, EurLiborON, GbpLiborON, UsdLiborON]

check :: (Word, TimeUnit) -> IborConstructor -> IO ()
check expected ctor = do
  idx <- iborIndex ctor Nothing
  actual <- tenor idx
  checkEq (show ctor ++ " tenor") expected actual

main :: IO ()
main = do
  forM_ standardCases (check (3, Months))
  -- DailyTenor/Overnight indices' *actual* QuantLib tenor() is always 1 day (that's what
  -- "daily tenor"/overnight means) regardless of the settlement-days argument we pass --
  -- unlike Standard-shape indices, that argument isn't a Period at all, so it can't be
  -- round-tripped through tenor(); this still catches a wrong flat-array offset routing one
  -- of these constructors into the wrong block (which would report (3,Months) or throw).
  forM_ dailyTenorCases (check (1, Days))
  forM_ overnightCases (check (1, Days))
