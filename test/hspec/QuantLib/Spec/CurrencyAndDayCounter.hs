{-# LANGUAGE ScopedTypeVariables, OverloadedLists #-}
module QuantLib.Spec.CurrencyAndDayCounter (spec) where

import Prelude hiding(tail)

import Test.Hspec

import Data.List.NonEmpty(NonEmpty, toList, tail)

import QuantLib.Time.Date
import qualified QuantLib.Settings as Settings
import QuantLib.Currency
import QuantLib.Time.Calendar(calendar, CalendarConstructor(..))
import QuantLib.Time.Schedule
import QuantLib.Math

import QuantLib.Spec.Helpers(listClose, areClose, closePrec)

spec :: Spec
spec = do
    describe "currency" $ do
      it "GBP name" $ do
        c <- currency GBP
        show c `shouldBe` "British pound sterling"

    describe "exchange rate" $ do
      it "direct" $ do
        eur <- currency EUR
        usd <- currency USD
        eurUsd <- exchangeRate eur usd 1.2042
        exchangeRateType eurUsd `shouldReturn` Direct

        (v1, c1) <- exchange eurUsd (50000, eur)
        v1 `shouldSatisfy` closePrec (50000 * 1.2042) (abs (50000 * 1.2042) * 1.0e-6)
        show c1 `shouldBe` show usd

        (v2, c2) <- exchange eurUsd (100000, usd)
        v2 `shouldSatisfy` closePrec (100000 / 1.2042) (abs (100000 / 1.2042) * 1.0e-6)
        show c2 `shouldBe` show eur

      it "derived (chain)" $ do
        eur <- currency EUR
        usd <- currency USD
        gbp <- currency GBP
        eurUsd <- exchangeRate eur usd 1.2042
        eurGbp <- exchangeRate eur gbp 0.6612
        derived <- chainExchangeRate eurUsd eurGbp
        exchangeRateType derived `shouldReturn` Derived

        (v1, c1) <- exchange derived (50000, gbp)
        v1 `shouldSatisfy` closePrec (50000 * 1.2042 / 0.6612) (abs (50000 * 1.2042 / 0.6612) * 1.0e-6)
        show c1 `shouldBe` show usd

        (v2, c2) <- exchange derived (100000, usd)
        v2 `shouldSatisfy` closePrec (100000 * 0.6612 / 1.2042) (abs (100000 * 0.6612 / 1.2042) * 1.0e-6)
        show c2 `shouldBe` show gbp

      it "manager lookup (direct, dated)" $ do
        clearExchangeRates
        eur <- currency EUR
        usd <- currency USD
        eurUsd1 <- exchangeRate eur usd 1.1983
        eurUsd2 <- exchangeRate usd eur (1.0 / 1.2042)
        let d1 = 4 `august` 2004
            d2 = 5 `august` 2004
        addExchangeRate eurUsd1 d1 d1
        addExchangeRate eurUsd2 d2 d2

        r1 <- lookupExchangeRate eur usd (Just d1) Direct
        (v1, _) <- exchange r1 (50000, eur)
        v1 `shouldSatisfy` closePrec (50000 * 1.1983) (abs (50000 * 1.1983) * 1.0e-6)

        r2 <- lookupExchangeRate eur usd (Just d2) Direct
        (v2, _) <- exchange r2 (50000, eur)
        v2 `shouldSatisfy` closePrec (50000 / (1.0 / 1.2042)) (abs (50000 / (1.0 / 1.2042)) * 1.0e-6)

        r3 <- lookupExchangeRate usd eur (Just d1) Direct
        (v3, _) <- exchange r3 (100000, usd)
        v3 `shouldSatisfy` closePrec (100000 / 1.1983) (abs (100000 / 1.1983) * 1.0e-6)

        r4 <- lookupExchangeRate usd eur (Just d2) Direct
        (v4, _) <- exchange r4 (100000, usd)
        v4 `shouldSatisfy` closePrec (100000 * (1.0 / 1.2042)) (abs (100000 * (1.0 / 1.2042)) * 1.0e-6)
        clearExchangeRates

    describe "money settings" $ do
      it "conversion type round-trips" $ do
        setMoneyConversionType AutomatedConversion
        moneyConversionType `shouldReturn` AutomatedConversion
        setMoneyConversionType NoConversion
        moneyConversionType `shouldReturn` NoConversion

      it "base currency round-trips, and drives convertToBaseCurrency" $ do
        usd <- currency USD
        eur <- currency EUR
        setMoneyBaseCurrency usd
        base <- moneyBaseCurrency
        fmap show base `shouldBe` Just (show usd)

        clearExchangeRates
        eurUsd <- exchangeRate eur usd 1.2042
        addExchangeRate eurUsd minDate maxDate
        (v, c) <- convertToBaseCurrency (50000, eur)
        v `shouldSatisfy` closePrec (50000 * 1.2042) (abs (50000 * 1.2042) * 1.0e-6)
        show c `shouldBe` show usd
        clearExchangeRates

    describe "day counter" $ do
      let checkCounter :: DayCounter -> [Day] -> [(Int, TimeUnit)] -> [Double] -> IO ()
          checkCounter dc ds periods expected = Settings.keepingSettings' $
            mapM_ (\d -> do
              calculated <- mapM (\p -> do
                end <- addPeriod d p
                years dc d end Nothing Nothing)
                periods
              calculated `shouldSatisfy` listClose id expected 1.0e-12)
              ds
      it "Actual/Actual" $
        Settings.keepingSettings' $
          mapM_ (\(c, s, e, rs, re, t) -> do
                    dc <- dayCounter c
                    f <- years dc s e rs re
                    abs(t - f) `shouldSatisfy` (<= 1.0e-10))
            ([(ActualActualISDA, 1 `november` 2003, 1 `may` 2004, Nothing, Nothing, 0.497724380567),
              (ActualActualISMA, 1 `november` 2003, 1 `may` 2004, Just $ 1 `november` 2003, Just $ 1 `may` 2004, 0.500000000000),
              (ActualActualAFB, 1 `november` 2003, 1 `may` 2004, Nothing, Nothing, 0.497267759563),
              (ActualActualISDA, 1 `february` 1999, 1 `july` 1999, Nothing, Nothing, 0.410958904110),
              (ActualActualISMA, 1 `february` 1999, 1 `july` 1999, Just $ 1 `july` 1998, Just $ 1 `july` 1999, 0.410958904110),
              (ActualActualAFB, 1 `february` 1999, 1 `july` 1999, Nothing, Nothing, 0.410958904110),
              (ActualActualISDA, 1 `july` 1999, 1 `july` 2000, Nothing, Nothing, 1.001377348600),
              (ActualActualISMA, 1 `july` 1999, 1 `july` 2000, Just $ 1 `july` 1999, Just $ 1 `july` 2000, 1.000000000000),
              (ActualActualAFB, 1 `july` 1999, 1 `july` 2000, Nothing, Nothing, 1.000000000000),
              (ActualActualISDA, 15 `august` 2002, 15 `july` 2003, Nothing, Nothing, 0.915068493151),
              (ActualActualISMA, 15 `august` 2002, 15 `july` 2003, Just $ 15 `january` 2003, Just $ 15 `july` 2003, 0.915760869565),
              (ActualActualAFB, 15 `august` 2002, 15 `july` 2003, Nothing, Nothing, 0.915068493151),
              (ActualActualISDA, 15 `july` 2003, 15 `january` 2004, Nothing, Nothing, 0.504004790778),
              (ActualActualISMA, 15 `july` 2003, 15 `january` 2004, Just $ 15 `july` 2003, Just $ 15 `january` 2004, 0.500000000000),
              (ActualActualAFB, 15 `july` 2003, 15 `january` 2004, Nothing, Nothing, 0.504109589041),
              (ActualActualISDA, 30 `july` 1999, 30 `january` 2000, Nothing, Nothing, 0.503892506924),
              (ActualActualISMA, 30 `july` 1999, 30 `january` 2000, Just $ 30 `july` 1999, Just $ 30 `january` 2000, 0.500000000000),
              (ActualActualAFB, 30 `july` 1999, 30 `january` 2000, Nothing, Nothing, 0.504109589041),
              (ActualActualISDA, 30 `january` 2000, 30 `june` 2000, Nothing, Nothing, 0.415300546448),
              (ActualActualISMA, 30 `january` 2000, 30 `june` 2000, Just $ 30 `january` 2000, Just $ 30 `july` 2000, 0.417582417582),
              (ActualActualAFB, 30 `january` 2000, 30 `june` 2000, Nothing, Nothing, 0.41530054644)] :: [(DayCounterConstructor, Day, Day, Maybe Day, Maybe Day, Double)])

      it "simple" $ do
        dc <- dayCounter Simple
        checkCounter dc
          [1 `january` 2002 .. 31 `december` 2005]
          [(3, Months), (6, Months), (1, Years)]
          [0.25, 0.5, 1.0]

      it "one" $ do
        dc <- dayCounter One
        checkCounter dc
          [1 `january` 2004 .. 31 `december` 2004]
          [(3, Months), (6, Months), (1, Years)]
          [1.0, 1.0, 1.0]

      it "Business 252" $
        Settings.keepingSettings' $ do
          let ds :: NonEmpty Day = [1 `february` 2002,
                        4 `february` 2002,
                        16 `may` 2003,
                        17 `december` 2003,
                        17 `december` 2004,
                        19 `december` 2005,
                         2 `january` 2006,
                        13 `march` 2006,
                        15 `may` 2006,
                        17 `march` 2006,
                        15 `may` 2006,
                        26 `july` 2006,
                        28 `june` 2007,
                        16 `september` 2009,
                        26 `july` 2016]
              expected = [0.0039682539683,
                        1.2738095238095,
                        0.6031746031746,
                        0.9960317460317,
                        1.0000000000000,
                        0.0396825396825,
                        0.1904761904762,
                        0.1666666666667,
                        -0.1507936507937,
                        0.1507936507937,
                        0.2023809523810,
                        0.912698412698,
                        2.214285714286,
                        6.84126984127]
          dc <- calendar BrazilSettlement >>= dayCounter . Business252
          fractions <- mapM (\(s, e) -> years dc s e Nothing Nothing) (zip (toList ds) (tail ds))
          fractions `shouldSatisfy` listClose id expected 1.0e-12

    describe "rounding" $ do
      let testData :: [(Double, Int, Double, Double, Double, Double, Double)]
          testData =
            [(  0.86313513, 5,  0.86314,  0.86314,  0.86313,  0.86314,  0.86313 ),
             (  0.86313,    5,  0.86313,  0.86313,  0.86313,  0.86313,  0.86313 ),
             ( -7.64555346, 1, -7.6,     -7.7,     -7.6,     -7.6,     -7.6     ),
             (  0.13961605, 2,  0.14,     0.14,     0.13,     0.14,     0.13    ),
             (  0.14344179, 4,  0.1434,   0.1435,   0.1434,   0.1434,   0.1434  ),
             ( -4.74315016, 2, -4.74,    -4.75,    -4.74,    -4.74,    -4.74    ),
             ( -7.82772074, 5, -7.82772, -7.82773, -7.82772, -7.82772, -7.82772 ),
             (  2.74137947, 3,  2.741,    2.742,    2.741,    2.741,    2.741   ),
             (  2.13056714, 1,  2.1,      2.2,      2.1,      2.1,      2.1     ),
             ( -1.06228670, 1, -1.1,     -1.1,     -1.0,     -1.0,     -1.1     ),
             (  8.29234094, 4,  8.2923,   8.2924,   8.2923,   8.2923,   8.2923  ),
             (  7.90185598, 2,  7.90,     7.91,     7.90,     7.90,     7.90    ),
             ( -0.26738058, 1, -0.3,     -0.3,     -0.2,     -0.2,     -0.3     ),
             (  1.78128713, 1,  1.8,      1.8,      1.7,      1.8,      1.7     ),
             (  4.23537260, 1,  4.2,      4.3,      4.2,      4.2,      4.2     ),
             (  3.64369953, 4,  3.6437,   3.6437,   3.6436,   3.6437,   3.6436  ),
             (  6.34542470, 2,  6.35,     6.35,     6.34,     6.35,     6.34    ),
             ( -0.84754962, 4, -0.8475,  -0.8476,  -0.8475,  -0.8475,  -0.8475  ),
             (  4.60998652, 1,  4.6,      4.7,      4.6,      4.6,      4.6     ),
             (  6.28794223, 3,  6.288,    6.288,    6.287,    6.288,    6.287   ),
             (  7.89428221, 2,  7.89,     7.90,     7.89,     7.89,     7.89    )]
          testRounding :: RoundingType -> Double -> Int -> Double -> IO ()
          testRounding rt x prec expected = do
            applyRounding (Rounding prec rt 5) x `shouldSatisfy` areClose expected
      it "closest" $
        mapM_ (\(x, p, x1, _x2, _x3, _x4, _x5) -> testRounding Closest x p x1) testData
      it "up" $
        mapM_ (\(x, p, _x1, x2, _x3, _x4, _x5) -> testRounding Up x p x2) testData
      it "down" $
        mapM_ (\(x, p, _x1, _x2, x3, _x4, _x5) -> testRounding Down x p x3) testData
      it "floor" $
        mapM_ (\(x, p, _x1, _x2, _x3, x4, _x5) -> testRounding Floor x p x4) testData
      it "celing" $
        mapM_ (\(x, p, _x1, _x2, _x3, _x4, x5) -> testRounding Ceiling x p x5) testData

    -- Read instances exist so a future text/JSON-driven caller (e.g. a term-sheet
    -- parser) has a name->value path into these enums; spot-check the round-trip
    -- rather than assuming c2hs's derived Show output is Read's exact inverse.
    describe "enum Read instances round-trip through Show" $ do
      it "Ccy" $
        mapM_ (\c -> read (show c) `shouldBe` c) ([minBound .. maxBound] :: [Ccy])
      it "TimeUnit" $
        mapM_ (\u -> read (show u) `shouldBe` u) ([minBound .. maxBound] :: [TimeUnit])
      it "Frequency" $
        mapM_ (\f -> read (show f) `shouldBe` f) ([minBound .. maxBound] :: [Frequency])
      it "Month" $
        mapM_ (\m -> read (show m) `shouldBe` m) ([minBound .. maxBound] :: [Month])
      it "Weekday" $
        mapM_ (\w -> read (show w) `shouldBe` w) ([minBound .. maxBound] :: [Weekday])
