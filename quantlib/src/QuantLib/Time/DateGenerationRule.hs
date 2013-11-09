module QuantLib.Time.DateGenerationRule
  (
    DateGenerationRule(..)
  )
where

import QuantLib.Internal.Enum(QLEnum)

instance QLEnum DateGenerationRule

-- |Date-generation rule.
-- These conventions specify the rule used to generate dates in a 'QuantLib.Time.Schedule.Schedule'
data DateGenerationRule = Backward  -- ^Backward from termination date to effective date
  | Forward -- ^Forward from effective date to termination date
  | Zero -- ^No intermediate dates between effective date and termination date
  | ThirdWednesday -- ^All dates but effective date and termination date are taken to be on the third wednesday of their month (with forward calculation)
  | Twentieth -- ^All dates but the effective date are taken to be the twentieth of their month (used for CDS schedules in emerging markets.) The termination date is also modified
  | TwentiethIMM -- ^All dates but the effective date are taken to be the twentieth of an IMM month (used for CDS schedules.) The termination date is also modified
  | OldCDS -- ^Same as TwentiethIMM with unrestricted date ends and log/short stub coupon period (old CDS convention)
  | CDS -- ^Credit derivatives standard rule since 'Big Bang' changes in 2009
  deriving (Show, Eq, Enum, Bounded)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
