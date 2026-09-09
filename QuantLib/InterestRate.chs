module QuantLib.InterestRate
  (

    Compounding(..)
  , VolatilityType(..)

  , InterestRate
  , interestRate
  , AccrualPeriod(..)
  , EquivalentPeriod(..)
  , compoundFactor
  , discountFactor
  , equivalentRate
  , impliedRate
  , rate
  ) where
import QuantLib.Internal
{#import QuantLib.Time.Schedule#}(Frequency)
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

{#pointer *InterestRate foreign -> CInterestRate nocode#}

{#enum Compounding{} deriving(Show, Eq, Read)#}
{#enum VolatilityType{} deriving(Show, Eq, Read)#}

-- |A compounding period: a year fraction in the rate's own day counter, or a date range.
data AccrualPeriod
  = AccrualAtTime !Double
  | AccrualBetween !Day !Day !(Maybe Day) !(Maybe Day) -- ^d1, d2, refStart, refEnd
  deriving (Eq, Show)

-- |As 'AccrualPeriod', for 'equivalentRate': only the date form takes a result day counter,
-- the time form keeps the rate's own.
data EquivalentPeriod
  = EquivalentAtTime !Double
  | EquivalentBetween !DayCounter !Day !Day !(Maybe Day) !(Maybe Day) -- ^resultDC, d1, d2, refStart, refEnd

-- |construct an interest rate from a rate value, a day counter, a compounding convention and a frequency.
{#fun qlInterestRate as interestRate{`Double' -- ^r
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |compound factor implied by the rate compounded between two dates
-- returns the compound (a.k.a capitalization) factor implied by the rate compounded between two dates.
{#fun qlInterestRateCompoundFactor1 as compoundFactorBetweenRaw{withInterestRate*`InterestRate',withDay*`Day' -- ^d1
  ,withDay*`Day' -- ^d2
  ,withMaybeDay*`Maybe Day' -- ^refStart
  ,withMaybeDay*`Maybe Day' -- ^refEnd
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |compound factor implied by the rate compounded at time t.
-- returns the compound (a.k.a capitalization) factor implied by the rate compounded at time t. /Warning/ Time must be measured using InterestRate's own day counter.
{#fun qlInterestRateCompoundFactor as compoundFactorAtTimeRaw{withInterestRate*`InterestRate',`Double' -- ^t
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |discount factor implied by the rate compounded between two dates
{#fun qlInterestRateDiscountFactor1 as discountFactorBetweenRaw{withInterestRate*`InterestRate',withDay*`Day' -- ^d1
  ,withDay*`Day' -- ^d2
  ,withMaybeDay*`Maybe Day' -- ^refStart
  ,withMaybeDay*`Maybe Day' -- ^refEnd
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |discount factor implied by the rate compounded at time t.
-- /Warning/ Time must be measured using InterestRate's own day counter.
{#fun qlInterestRateDiscountFactor as discountFactorAtTimeRaw{withInterestRate*`InterestRate',`Double',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |equivalent rate for a compounding period between two dates
-- The resulting rate is calculated taking the required day-counting rule into account.
{#fun qlInterestRateEquivalentRate1 as equivalentRateBetweenRaw{withInterestRate*`InterestRate',withDayCounter*`DayCounter' -- ^resultDC
  ,`Compounding',`Frequency',withDay*`Day' -- ^d1
  ,withDay*`Day' -- ^d2
  ,withMaybeDay*`Maybe Day' -- ^refStart
  ,withMaybeDay*`Maybe Day' -- ^refEnd
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |equivalent interest rate for a compounding period t.
-- The resulting InterestRate shares the same implicit day-counting rule of the original InterestRate instance. /Warning/ Time must be measured using the InterestRate's own day counter.
{#fun qlInterestRateEquivalentRate as equivalentRateAtTimeRaw{withInterestRate*`InterestRate',`Compounding',`Frequency',`Double' -- ^t
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |implied rate for a given compound factor between two dates.
-- The resulting rate is calculated taking the required day-counting rule into account.
{#fun qlInterestRateImpliedRate1 as impliedRateBetweenRaw{withInterestRate*`InterestRate',`Double' -- ^compound
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day' -- ^d1
  ,withDay*`Day' -- ^d2
  ,withMaybeDay*`Maybe Day' -- ^refStart
  ,withMaybeDay*`Maybe Day' -- ^refEnd
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |implied interest rate for a given compound factor at a given time.
-- The resulting InterestRate has the day-counter provided as input. /Warning/ Time must be measured using the day-counter provided as input.
{#fun qlInterestRateImpliedRate as impliedRateAtTimeRaw{withInterestRate*`InterestRate',`Double' -- ^compound
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`Double' -- ^t
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |the rate value of an interest rate.
{#fun pure qlInterestRateRate as rate{withInterestRate*`InterestRate'}->`Double'#}

-- |Compound (capitalization) factor implied by the rate over the given period.
compoundFactor :: InterestRate -> AccrualPeriod -> IO Double
compoundFactor ir period = case period of
  AccrualAtTime t -> compoundFactorAtTimeRaw ir t
  AccrualBetween d1 d2 rs re -> compoundFactorBetweenRaw ir d1 d2 rs re

-- |Discount factor implied by the rate over the given period.
discountFactor :: InterestRate -> AccrualPeriod -> IO Double
discountFactor ir period = case period of
  AccrualAtTime t -> discountFactorAtTimeRaw ir t
  AccrualBetween d1 d2 rs re -> discountFactorBetweenRaw ir d1 d2 rs re

-- |Equivalent rate under a different compounding and frequency over the given period.
equivalentRate :: InterestRate -> Compounding -> Frequency -> EquivalentPeriod -> IO InterestRate
equivalentRate ir comp freq period = case period of
  EquivalentAtTime t -> equivalentRateAtTimeRaw ir comp freq t
  EquivalentBetween dc d1 d2 rs re -> equivalentRateBetweenRaw ir dc comp freq d1 d2 rs re

-- |Rate implied by a given compound factor over the given period, in the supplied day counter.
impliedRate :: InterestRate -> Double -> DayCounter -> Compounding -> Frequency -> AccrualPeriod
  -> IO InterestRate
impliedRate ir compound dc comp freq period = case period of
  AccrualAtTime t -> impliedRateAtTimeRaw ir compound dc comp freq t
  AccrualBetween d1 d2 rs re -> impliedRateBetweenRaw ir compound dc comp freq d1 d2 rs re

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
