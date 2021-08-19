module QuantLib.Instrument.Forward
  (
    Forward
  , asForward
  , ForwardRateAgreement
  , FixedRateBondForward

  , forwardRateAgreement
  , fixedRateBondForward

  , cleanForwardPrice
  , forwardPrice
  , forwardValue
  , impliedYield
  , settlementDate
  , spotIncome
  , spotValue

  , forwardRate
  )
  where

import QuantLib.Internal
{#import QuantLib.Instrument#}
{#import QuantLib.Time.Calendar#}(Calendar, BusinessDayConvention)
{#import QuantLib.Time.Schedule#}(DayCounter)
{#import QuantLib.Index.InterestRate#}(IborIndex)
{#import QuantLib.Instrument.Bond#}(FixedRateBond)
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
import QuantLib.Internal.Schedule
import QuantLib.Internal.Calendar
import QuantLib.Internal.Index
{#import QuantLib.InterestRate#}
import QuantLib.Internal.TermStructure

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlForward as Forward foreign finalizer qlFreeForward newtype#}
instance ForeignObject Forward where
  withObject = withForward
  constructor = Forward
  finalizer=qlFreeForward

{#fun qlForwardAsInstrument {`Forward'} -> `Instrument' peekObject*#}
instance IsInstrument Forward where asInstrument = qlForwardAsInstrument

class IsForward a where asForward :: a -> IO Forward

{#pointer *QlForwardRateAgreement as ForwardRateAgreement foreign finalizer qlFreeForwardRateAgreement newtype#}
instance ForeignObject ForwardRateAgreement where
  withObject = withForwardRateAgreement
  constructor = ForwardRateAgreement
  finalizer=qlFreeForwardRateAgreement

{#fun qlForwardRateAgreementAsForward {`ForwardRateAgreement'} -> `Forward'#}
instance IsForward ForwardRateAgreement where asForward = qlForwardRateAgreementAsForward

{#pointer *QlFixedRateBondForward as FixedRateBondForward foreign finalizer qlFreeFixedRateBondForward newtype#}
instance ForeignObject FixedRateBondForward where
  withObject = withFixedRateBondForward
  constructor = FixedRateBondForward
  finalizer=qlFreeFixedRateBondForward

{#fun qlFixedRateBondForwardAsForward {`FixedRateBondForward'} -> `Forward'#}
instance IsForward FixedRateBondForward where asForward = qlFixedRateBondForwardAsForward

{#fun qlForwardRateAgreement as forwardRateAgreement {withDay* `Day', withDay* `Day', fromEnumC `PositionType', `Double', `Double', `IborIndex', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `ForwardRateAgreement'#}

-- |If strike is given in the constructor, can calculate the NPV of the contract via NPV().If strike/forward price is desired, it can be obtained via forwardPrice(). In this case, the strike variable in the constructor is irrelevant and will be ignored.
{#fun qlFixedRateBondForward as fixedRateBondForward {withDay* `Day', withDay* `Day', fromEnumC `PositionType', `Double', fromIntegral `Word', `DayCounter', `Calendar', `BusinessDayConvention', withObject* `FixedRateBond', withMaybeObject* `Maybe YieldTermStructure', withMaybeObject* `Maybe YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `FixedRateBondForward'#}

-- |(dirty) forward bond price minus accrued on bond at delivery
{#fun qlFixedRateBondForwardCleanForwardPrice as cleanForwardPrice {`FixedRateBondForward', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |(dirty) forward bond price
{#fun qlFixedRateBondForwardForwardPrice as forwardPrice {`FixedRateBondForward', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |forward value/price of underlying, discounting income/dividends
-- if this is a bond forward price, is must be a dirty forward price.
{#fun qlForwardForwardValue as forwardValue {`Forward', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Simple yield calculation based on underlying spot and forward values, taking into account underlying income. When $ t>0 $, call with: underlyingSpotValue=spotValue(t), forwardValue=strikePrice, to get current yield. For a repo, if $ t=0 $, impliedYield should reproduce the spot repo rate. For FRA's, this should reproduce the relevant zero rate at the FRA's maturityDate_;
{#fun qlForwardImpliedYield as impliedYield {`Forward', `Double', `Double', withDay* `Day', `Compounding', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `InterestRate' peekObject*#}

{#fun qlForwardSettlementDate as settlementDate {`Forward', preErrorCheck- `String' errorCheck*-} -> `Day' toDay#}

-- |NPV of income/dividends/storage-costs etc. of underlying instrument.
{#fun qlForwardSpotIncome as spotIncome {`Forward', `YieldTermStructure', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns spot value/price of an underlying financial instrument
{#fun qlForwardSpotValue as spotValue {`Forward', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |Returns the relevant forward rate associated with the FRA term.
{#fun qlForwardRateAgreementForwardRate as forwardRate {`ForwardRateAgreement', preErrorCheck- `String' errorCheck*-} -> `InterestRate' peekObject*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
