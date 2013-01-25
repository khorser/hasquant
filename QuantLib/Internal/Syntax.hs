{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Internal.Syntax
where

import Language.Haskell.TH
import QuantLib.Types

topLevel :: Name -> Bool
topLevel n = n `elem` [''Int, ''Word, ''Day, ''String,
  ''Bond, ''Leg, ''FloatingRateCouponPricer, ''Currency, ''Index, ''IborIndex,
  ''Instrument, ''FixedRateBond, ''PricingEngine, ''RateHelper,
  ''YieldTermStructure, ''VolTermStructure, ''OptionletVolStructure,
  ''Calendar, ''DayCounter, ''Period, ''Schedule, ''InterestRate, ''Quote]

data Arg = Top Name | OptTop Name | List Name | List2 Name Name
