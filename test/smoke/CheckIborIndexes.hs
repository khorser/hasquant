-- Smoke test: construct every "plain" IborConstructor case (Standard tenor-based,
-- DailyTenor, and Overnight shapes -- i.e. everything deriveIborConstructor generates from
-- IborIndexType/IborDailyTenorIndexType/IborONIndexType, not the shortcut/generic Extra
-- cases) and assert the constructed index's tenor accessor round-trips the requested tenor.
--
-- This catches missing tenor propagation and wrong factory-table offsets, both of which can build
-- successfully while constructing the wrong underlying index.
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

-- Spot-check one fixed-tenor shortcut per family and every SW shortcut. This pins each synonym to
-- the intended family and tenor.
shortcutCases :: [((Word, TimeUnit), IborConstructor)]
shortcutCases =
  [ ((1, Weeks), BiborSW), ((1, Weeks), EuriborSW)
  , ((1, Weeks), Euribor365_SW), ((1, Weeks), EurLiborSW)
  , ((3, Months), Bbsw3M), ((6, Months), Bibor6M), ((3, Months), Bkbm3M)
  , ((3, Months), Euribor3M), ((1, Years), Euribor1Y)
  , ((11, Months), Euribor365_11M), ((3, Months), EurLibor3M)
  ]

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
  forM_ shortcutCases (uncurry check)
