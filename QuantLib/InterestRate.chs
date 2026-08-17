module QuantLib.InterestRate
  (

    Compounding(..)
  , VolatilityType(..)

  , InterestRate
  , interestRate
  , compoundFactor
  , compoundFactor'
  , discountFactor
  , discountFactor'
  , equivalentRate
  , equivalentRate'
  , impliedRate
  , impliedRate'
  , rate
  ) where
import QuantLib.Internal
{#import QuantLib.Time.Schedule#}(Frequency)
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

{#pointer *InterestRate foreign -> CInterestRate nocode#}

{#enum Compounding{} deriving(Show, Eq)#}
{#enum VolatilityType{} deriving(Show, Eq)#}

-- |construct an interest rate from a rate value, a day counter, a compounding convention and a frequency.
{#fun qlInterestRate as interestRate{`Double' -- ^r
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}
-- |compound factor implied by the rate compounded between two dates
-- returns the compound (a.k.a capitalization) factor implied by the rate compounded between two dates.
{#fun qlInterestRateCompoundFactor1 as compoundFactor'{withInterestRate*`InterestRate',withDay*`Day' -- ^d1
  ,withDay*`Day' -- ^d2
  ,withDay*`Day' -- ^refStart
  ,withDay*`Day' -- ^refEnd
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |compound factor implied by the rate compounded at time t.
-- returns the compound (a.k.a capitalization) factor implied by the rate compounded at time t. /Warning/ Time must be measured using InterestRate's own day counter.
{#fun qlInterestRateCompoundFactor as compoundFactor{withInterestRate*`InterestRate',`Double' -- ^t
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |discount factor implied by the rate compounded between two dates
{#fun qlInterestRateDiscountFactor1 as discountFactor'{withInterestRate*`InterestRate',withDay*`Day' -- ^d1
  ,withDay*`Day' -- ^d2
  ,withDay*`Day' -- ^refStart
  ,withDay*`Day' -- ^refEnd
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |discount factor implied by the rate compounded at time t.
-- /Warning/ Time must be measured using InterestRate's own day counter.
{#fun qlInterestRateDiscountFactor as discountFactor{withInterestRate*`InterestRate',`Double',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |equivalent rate for a compounding period between two dates
-- The resulting rate is calculated taking the required day-counting rule into account.
{#fun qlInterestRateEquivalentRate1 as equivalentRate'{withInterestRate*`InterestRate',withDayCounter*`DayCounter' -- ^resultDC
  ,`Compounding',`Frequency',withDay*`Day' -- ^d1
  ,withDay*`Day' -- ^d2
  ,withDay*`Day' -- ^refStart
  ,withDay*`Day' -- ^refEnd
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}
-- |equivalent interest rate for a compounding period t.
-- The resulting InterestRate shares the same implicit day-counting rule of the original InterestRate instance. /Warning/ Time must be measured using the InterestRate's own day counter.
{#fun qlInterestRateEquivalentRate as equivalentRate{withInterestRate*`InterestRate',`Compounding',`Frequency',`Double' -- ^t
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}
-- |implied rate for a given compound factor between two dates.
-- The resulting rate is calculated taking the required day-counting rule into account.
{#fun qlInterestRateImpliedRate1 as impliedRate'{withInterestRate*`InterestRate',`Double' -- ^compound
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',withDay*`Day' -- ^d1
  ,withDay*`Day' -- ^d2
  ,withDay*`Day' -- ^refStart
  ,withDay*`Day' -- ^refEnd
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}
-- |implied interest rate for a given compound factor at a given time.
-- The resulting InterestRate has the day-counter provided as input. /Warning/ Time must be measured using the day-counter provided as input.
{#fun qlInterestRateImpliedRate as impliedRate{withInterestRate*`InterestRate',`Double' -- ^compound
  ,withDayCounter*`DayCounter',`Compounding',`Frequency',`Double' -- ^t
  ,preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}
-- |the rate value of an interest rate.
{#fun pure qlInterestRateRate as rate{withInterestRate*`InterestRate'}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
