-- Smoke test: construct a Direct exchange rate and a Derived (chain-built)
-- one, and exercise `exchange` on each -- catching a stale/mismatched
-- ExchangeRateType enum dispatch that a successful build alone wouldn't
-- reveal.
--
-- Run with: cabal exec -- ghc -package hasquant smoke/CheckExchangeRate.hs -o /tmp/checkexchangerate -outputdir /tmp/checkexchangerate_build && /tmp/checkexchangerate
import QuantLib.Currency
import QuantLib.Internal(minDate, maxDate)

main :: IO ()
main = do
  eur <- currency EUR
  usd <- currency USD
  gbp <- currency GBP

  direct <- exchangeRate eur usd 1.2042
  directTy <- exchangeRateType direct
  putStrLn ("Direct type: " ++ show directTy)
  (v1, c1) <- exchange direct (50000, eur)
  putStrLn ("50000 EUR -> " ++ show v1 ++ " " ++ code c1)
  (v2, c2) <- exchange direct (100000, usd)
  putStrLn ("100000 USD -> " ++ show v2 ++ " " ++ code c2)

  eurGbp <- exchangeRate eur gbp 0.6612
  derived <- chainExchangeRate direct eurGbp
  derivedTy <- exchangeRateType derived
  putStrLn ("Derived type: " ++ show derivedTy)
  (v3, c3) <- exchange derived (50000, gbp)
  putStrLn ("50000 GBP -> " ++ show v3 ++ " " ++ code c3)
  (v4, c4) <- exchange derived (100000, usd)
  putStrLn ("100000 USD -> " ++ show v4 ++ " " ++ code c4)

  clearExchangeRates
  addExchangeRate direct minDate maxDate
  looked <- lookupExchangeRate eur usd Nothing Direct
  lookedRate <- rate looked
  putStrLn ("looked-up EUR/USD rate: " ++ show lookedRate)

  setMoneyBaseCurrency usd
  setMoneyConversionType NoConversion
  base <- moneyBaseCurrency
  putStrLn ("base currency: " ++ maybe "(none)" code base)
  (bv, bc) <- convertToBaseCurrency (50000, eur)
  putStrLn ("convertToBaseCurrency 50000 EUR -> " ++ show bv ++ " " ++ code bc)
