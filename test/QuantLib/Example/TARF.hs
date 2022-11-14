module QuantLib.Example.TARF
  (
    run
  )
where

import Control.Monad(replicateM)
import Data.Time.Calendar(fromGregorian)

import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Time.Schedule
import QuantLib.CashFlow
import QuantLib.Math
import QuantLib.Process
import QuantLib.Quote
import QuantLib.TermStructure.Yield
import QuantLib.TermStructure.Volatility
import QuantLib.Method
import QuantLib.Settings

data State = State{_remPL :: !Double, _flows :: ![Double]}

roundTo :: Double -> Int -> Double
roundTo x n = fromIntegral (round (x*mult) :: Int) / mult where mult = 10.0**fromIntegral n

run :: IO ()
run = do
  setEvaluationDate (Just valDate)
  calILS <- calendar IsraelSettlement
  calEUR <- calendar TARGET
  calEURILS <- calendar $ Joint2 calILS calEUR JoinHolidays
  dcEUR <- dayCounter Actual360
  dcILS <- dayCounter Actual365FixedStandard
  sched <- schedule (Just $ 2 `november` 2022) (2 `october` 2023) (1, Months) calEUR ModifiedFollowing ModifiedFollowing Forward False Nothing Nothing
  ds <- dates sched
  grid <- mapM (\x -> years dcILS valDate x Nothing Nothing) ds >>= timeGridFromList
  spotQuote <- simpleQuote spot
  vols <- mapM (\(d, q) -> parse d >>= \x -> advance calEURILS valDate x ModifiedFollowing False >>= \dd -> return (dd, q/100)) vEURILS
  volEURILS <- blackVarianceCurve valDate vols dcILS True (Just Linear) >>= asBlackVolTermStructure
  ycILS <- interpolatedDiscountCurve dfILS dcILS calILS [] LogLinear
  ycEUR <- interpolatedDiscountCurve dfEUR dcEUR calEUR [] LogLinear
  proc <- blackScholesMertonProcess spotQuote ycILS ycEUR volEURILS EulerDiscretization >>= asStochasticProcess1D >>= asStochasticProcess
  gen <- pathGenerator PseudoRandom proc grid 0 (size grid - 1) False
  ps <- replicateM trials $ nextNPV gen ds ycILS
  print $ (sum ps)/fromIntegral trials/spot
  where
    valDate = 15 `august` 2022
    strike = 3.2
    spot = 3.3084
    eurNotional = 500000
    ilsTarget = 0.4 * eurNotional
    leverage = 2.0
    notionalDigits = 2
    fxrateDigits = 4
    trials = 2^(15::Int)

    nextNPV :: PathGenerator -> [Day] -> YieldTermStructure -> IO Double
    nextNPV g ds yc = do
      s <- next g
      sim <- asset s 0
      let State _ fs = foldl genFlows (State ilsTarget []) $ map (`roundTo` fxrateDigits) sim
      l <- leg $ zip ds fs
      (`roundTo` notionalDigits) <$> npv l yc True Nothing Nothing

    genFlows :: State -> Double -> State
    genFlows s@(State 0 _) _ = s
    genFlows (State tgt fs) spt | spt > strike = State (tgt-cash) (fs ++ [cash])
      where cash = min (roundTo ((spt-strike)*eurNotional) notionalDigits) tgt
    genFlows (State tgt fs) spt = State tgt (fs ++ [cash])
      where cash = roundTo ((spt-strike)*eurNotional*leverage) notionalDigits

    dfEUR = [(valDate, 1.0),
      (fromGregorian 2022 09 16, 0.999910),
      (fromGregorian 2022 10 18, 0.999818),
      (fromGregorian 2022 11 16, 0.999734),
      (fromGregorian 2022 12 16, 0.999520),
      (fromGregorian 2023 01 16, 0.999267),
      (fromGregorian 2023 02 16, 0.999013),
      (fromGregorian 2023 03 16, 0.998445),
      (fromGregorian 2023 04 17, 0.997667),
      (fromGregorian 2023 05 16, 0.996962),
      (fromGregorian 2023 06 16, 0.996122),
      (fromGregorian 2023 07 17, 0.995263),
      (fromGregorian 2023 08 16, 0.994432),
      (fromGregorian 2023 09 18, 0.993524),
      (fromGregorian 2023 10 16, 0.992756),
      (fromGregorian 2023 11 16, 0.991907),
      (fromGregorian 2023 12 18, 0.991030),
      (fromGregorian 2024 01 16, 0.990237),
      (fromGregorian 2024 02 16, 0.989389),
      (fromGregorian 2024 03 18, 0.988542),
      (fromGregorian 2024 04 16, 0.987751),
      (fromGregorian 2024 05 16, 0.986933),
      (fromGregorian 2024 06 17, 0.986061),
      (fromGregorian 2024 07 16, 0.985271),
      (fromGregorian 2024 08 16, 0.984428),
      (fromGregorian 2024 09 16, 0.983618),
      (fromGregorian 2024 10 16, 0.982840),
      (fromGregorian 2024 11 18, 0.981986),
      (fromGregorian 2024 12 16, 0.981261),
      (fromGregorian 2025 01 16, 0.980460),
      (fromGregorian 2025 02 17, 0.979633),
      (fromGregorian 2025 03 17, 0.978911),
      (fromGregorian 2025 04 16, 0.978137),
      (fromGregorian 2025 05 16, 0.977364),
      (fromGregorian 2025 06 16, 0.976565),
      (fromGregorian 2025 07 16, 0.975794),
      (fromGregorian 2025 08 18, 0.974945),
      (fromGregorian 2025 09 16, 0.974162),
      (fromGregorian 2025 10 16, 0.973349),
      (fromGregorian 2025 11 17, 0.972484)]
    dfILS = [(valDate, 1.0),
      (fromGregorian 2022 09 16, 0.999573),
      (fromGregorian 2022 10 18, 0.999132),
      (fromGregorian 2022 11 16, 0.998733),
      (fromGregorian 2022 12 16, 0.997864),
      (fromGregorian 2023 01 16, 0.996849),
      (fromGregorian 2023 02 16, 0.995835),
      (fromGregorian 2023 03 16, 0.994821),
      (fromGregorian 2023 04 17, 0.993626),
      (fromGregorian 2023 05 16, 0.992544),
      (fromGregorian 2023 06 16, 0.991427),
      (fromGregorian 2023 07 17, 0.990321),
      (fromGregorian 2023 08 16, 0.989251),
      (fromGregorian 2023 09 18, 0.988081),
      (fromGregorian 2023 10 16, 0.987090),
      (fromGregorian 2023 11 16, 0.985994),
      (fromGregorian 2023 12 18, 0.984864),
      (fromGregorian 2024 01 16, 0.983841),
      (fromGregorian 2024 02 16, 0.982748),
      (fromGregorian 2024 03 18, 0.981657),
      (fromGregorian 2024 04 16, 0.980638),
      (fromGregorian 2024 05 16, 0.979584),
      (fromGregorian 2024 06 17, 0.978461),
      (fromGregorian 2024 07 16, 0.977445),
      (fromGregorian 2024 08 16, 0.976360),
      (fromGregorian 2024 09 16, 0.975416),
      (fromGregorian 2024 10 16, 0.974531),
      (fromGregorian 2024 11 18, 0.973557),
      (fromGregorian 2024 12 16, 0.972732),
      (fromGregorian 2025 01 16, 0.971819),
      (fromGregorian 2025 02 17, 0.970878),
      (fromGregorian 2025 03 17, 0.970055),
      (fromGregorian 2025 04 16, 0.969174),
      (fromGregorian 2025 05 16, 0.968294),
      (fromGregorian 2025 06 16, 0.967386),
      (fromGregorian 2025 07 16, 0.966507),
      (fromGregorian 2025 08 18, 0.965542),
      (fromGregorian 2025 09 16, 0.964752),
      (fromGregorian 2025 10 16, 0.963940),
      (fromGregorian 2025 11 17, 0.963074)]
    vEURILS = [
      ("1D",  8.885),
      ("1W",  9.690),
      ("2W",  9.900),
      ("3W",  9.680),
      ("1M",  9.915),
      ("2M",  9.750),
      ("3M",  9.535),
      ("4M",  9.440),
      ("5M",  9.374),
      ("6M",  9.295),
      ("9M",  9.185),
      ("1Y",  9.130),
      ("18M", 9.295),
      ("2Y",  9.385),
      ("3Y",  9.300),
      ("4Y",  9.197),
      ("5Y",  9.115),
      ("6Y",  9.117),
      ("7Y",  9.122),
      ("10Y", 9.133),
      ("15Y", 9.148),
      ("20Y", 9.164),
      ("25Y", 9.180),
      ("30Y", 9.196)]

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
