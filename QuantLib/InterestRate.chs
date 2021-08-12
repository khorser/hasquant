module QuantLib.InterestRate
  (

    Compounding(..)

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
  )
  where

import QuantLib.Internal
{#import QuantLib.Period#}(Frequency)
{#import QuantLib.Schedule#}(DayCounter)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

{#enum Compounding {} deriving(Show, Eq, Bounded)#}

{#pointer *InterestRate foreign finalizer qlFreeInterestRate newtype#}

instance ForeignObject InterestRate where
  withObject = withInterestRate

{#fun qlInterestRate as interestRate {`Double', withObject* `DayCounter', `Compounding', `Frequency', preErrorCheck- `String' errorCheck*-} -> `InterestRate'#}

-- |compound factor implied by the rate compounded between two dates
-- returns the compound (a.k.a capitalization) factor implied by the rate compounded between two dates.
{#fun qlInterestRateCompoundFactor1 as compoundFactor' {`InterestRate', fromDay* `Day', fromDay* `Day', fromDay* `Day', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |compound factor implied by the rate compounded at time t.
-- returns the compound (a.k.a capitalization) factor implied by the rate compounded at time t. /Warning/ Time must be measured using InterestRate's own day counter.
{#fun qlInterestRateCompoundFactor as compoundFactor {`InterestRate', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |discount factor implied by the rate compounded between two dates
{#fun qlInterestRateDiscountFactor1 as discountFactor' {`InterestRate', fromDay* `Day', fromDay* `Day', fromDay* `Day', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |discount factor implied by the rate compounded at time t.
-- /Warning/ Time must be measured using InterestRate's own day counter.
{#fun qlInterestRateDiscountFactor as discountFactor {`InterestRate', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |equivalent rate for a compounding period between two dates
-- The resulting rate is calculated taking the required day-counting rule into account.
{#fun qlInterestRateEquivalentRate1 as equivalentRate' {`InterestRate', withObject* `DayCounter', `Compounding', `Frequency', fromDay* `Day', fromDay* `Day', fromDay* `Day', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `InterestRate'#}

-- |equivalent interest rate for a compounding period t.
-- The resulting InterestRate shares the same implicit day-counting rule of the original InterestRate instance. /Warning/ Time must be measured using the InterestRate's own day counter.
{#fun qlInterestRateEquivalentRate as equivalentRate {`InterestRate', `Compounding', `Frequency', `Double', preErrorCheck- `String' errorCheck*-} -> `InterestRate'#}

-- |implied rate for a given compound factor between two dates.
-- The resulting rate is calculated taking the required day-counting rule into account.
{#fun qlInterestRateImpliedRate1 as impliedRate' {`InterestRate', `Double', withObject* `DayCounter', `Compounding', `Frequency', fromDay* `Day', fromDay* `Day', fromDay* `Day', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `InterestRate'#}

-- |implied interest rate for a given compound factor at a given time.
-- The resulting InterestRate has the day-counter provided as input. /Warning/ Time must be measured using the day-counter provided as input.
{#fun qlInterestRateImpliedRate as impliedRate {`InterestRate', `Double', withObject* `DayCounter', `Compounding', `Frequency', `Double', preErrorCheck- `String' errorCheck*-} -> `InterestRate'#}

{#fun pure qlInterestRateRate as rate {`InterestRate'} -> `Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
