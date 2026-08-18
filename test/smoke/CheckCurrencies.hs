-- Smoke test: construct every Ccy case and print its ISO code, catching
-- a stale c2hs-generated enum or a wrong Ccy/ccys[] factory-table order
-- mismatch (see the reconcile-currencies skill's "gotcha" note) that a
-- successful build alone wouldn't reveal.
--
-- Run with: cabal exec -- ghc -package hasquant smoke/CheckCurrencies.hs -o /tmp/checkccy -outputdir /tmp/checkccy_build && /tmp/checkccy
import QuantLib.Currency
import Control.Monad

-- c2hs only derives Show/Eq for this enum (no Bounded), so the case list
-- is spelled out explicitly, in the same order as `enum Ccy` in
-- cbits/qlEnumObjects.h.
allCcys :: [Ccy]
allCcys =
  [ARS, ATS, AUD, BCH, BDT, BEF, BGL, BRL, BTC, BYR, CAD, CHF, CLP, CNY, COP
  ,CYP, CZK, DASH, DEM, DKK, EEK, ESP, ETC, ETH, EUR, FIM, FRF, GBP, GRD, HKD
  ,HUF, IDR, IEP, ILS, INR, IQD, IRR, ISK, ITL, JPY, KRW, KWD, KZT, LTC, LTL
  ,LUF, LVL, MTL, MXN, MYR, NGN, NLG, NOK, NPR, NZD, PEH, PEI, PEN, PKR, PLN
  ,PTE, ROL, RON, RUB, SAR, SEK, SGD, SIT, SKK, THB, TRL, TRY, TTD, TWD, UAH
  ,USD, VEB, VND, XRP, ZAR, ZEC
  ,AED, AOA, BGN, BHD, BWP, CLF, CNH, COU, EGP, ETB, GEL, GHS, HRK, JOD, KES
  ,LKR, MAD, MKD, MUR, MXV, OMR, PHP, QAR, RSD, TND, UGX, UYU, UZS, XOF, ZMW
  ]

main :: IO ()
main = forM_ allCcys $ \ty -> do
  c <- currency ty
  putStrLn (show ty ++ " -> " ++ code c)
