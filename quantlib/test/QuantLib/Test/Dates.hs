{-# OPTIONS_GHC -F -pgmF htfpp #-}
module QuantLib.Test.Dates (htf_thisModulesTests)
-- dates.cpp
where

import Test.Framework

import Control.Monad.IO.Class
import Data.Time.Calendar
import Data.Time.Format()

import QuantLib.Settings
import QuantLib.Time.Date
import QuantLib.Types

{-# ANN module "HLint: ignore Use camelCase" #-}

test_ECBDates :: IO ()
test_ECBDates = keepingSettings' $ runQLE $ do
  knownDates <- knownECBDates
  liftIO $ assertBool (not $ null knownDates)
  knownDates' <- nextECBDates (Just minDate)
  liftIO $ assertEqual knownDates knownDates'
  mapM_ (\(d, p) -> do
    i <- isECBDate d
    liftIO $ assertBool i
    let d1 = addDays (-1) d
    i1 <- isECBDate d1
    liftIO $ assertBool (not i1)
    n <- nextECBDate (Just d1)
    liftIO $ assertEqual d n
    dd <- nextECBDate (Just p)
    liftIO $ assertEqual d dd)
    (zip knownDates (minDate:knownDates))
  let h = head knownDates
  removeECBDate h
  i <- isECBDate h
  liftIO $ assertBool (not i)
  addECBDate h
  i1 <- isECBDate h
  liftIO $ assertBool i1

test_IMMDatesLongRunning :: IO ()
test_IMMDatesLongRunning = keepingSettings' $ do
  mapM_ (\d -> do
    let (Right imm) = nextIMMDate d False
        (Right isImm) = isIMMDate imm False
        (Right n) = nextIMMDate d True

    assertBool (imm > d)
    assertBool isImm
    assertBool (imm <= n)
    let (Right code) = immCode imm
    let (Right dd) = immDate code d
    assertEqual dd imm

    mapM_ (\i -> do
      let (Right immd) = immDate i d
      assertBool (immd >= d))
      $ take 40 immCodes)
    [minDate .. (addGregorianMonthsClip (-121) maxDate)]
  return ()
  where immCodes = [
          "F0", "G0", "H0", "J0", "K0", "M0", "N0", "Q0", "U0", "V0", "X0", "Z0",
          "F1", "G1", "H1", "J1", "K1", "M1", "N1", "Q1", "U1", "V1", "X1", "Z1",
          "F2", "G2", "H2", "J2", "K2", "M2", "N2", "Q2", "U2", "V2", "X2", "Z2",
          "F3", "G3", "H3", "J3", "K3", "M3", "N3", "Q3", "U3", "V3", "X3", "Z3",
          "F4", "G4", "H4", "J4", "K4", "M4", "N4", "Q4", "U4", "V4", "X4", "Z4",
          "F5", "G5", "H5", "J5", "K5", "M5", "N5", "Q5", "U5", "V5", "X5", "Z5",
          "F6", "G6", "H6", "J6", "K6", "M6", "N6", "Q6", "U6", "V6", "X6", "Z6",
          "F7", "G7", "H7", "J7", "K7", "M7", "N7", "Q7", "U7", "V7", "X7", "Z7",
          "F8", "G8", "H8", "J8", "K8", "M8", "N8", "Q8", "U8", "V8", "X8", "Z8",
          "F9", "G9", "H9", "J9", "K9", "M9", "N9", "Q9", "U9", "V9", "X9", "Z9"]

test_IsoDates :: IO ()
test_IsoDates = keepingSettings' $
  assertEqual (read "2006-01-15") (15 `january` 2006)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
