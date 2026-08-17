module QuantLib.Instrument.Forward
  (
    Forward
  , asForward
  , ForwardRateAgreement
  , BondForward
  , FxForward

  , forwardRateAgreement
  , bondForward
  , fxForward
  , fxForward'

  , cleanForwardPrice
  , forwardPrice
  , forwardValue
  , impliedYield
  , settlementDate
  , spotIncome
  , spotValue

  , forwardRate
  , fairForwardRate
  , npvSourceCurrency
  , npvTargetCurrency
  ) where
import QuantLib.Internal
{#import QuantLib.Instrument#}
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
import QuantLib.Internal.Type
{#import QuantLib.InterestRate#}

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlBond as Bond foreign -> CBond' nocode#}
{#pointer *QlForward as Forward foreign -> CForward' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}
{#pointer *QlFixedRateBond as FixedRateBond foreign -> CFixedRateBond' nocode#}
{#pointer *QlForwardRateAgreement as ForwardRateAgreement foreign -> CForwardRateAgreement' nocode#}
{#pointer *QlBondForward as BondForward foreign -> CBondForward' nocode#}
{#pointer *QlFxForward as FxForward foreign -> CFxForward' nocode#}
{#pointer *Currency foreign -> CCurrency nocode#}

-- |FRA with a par-rate approximation: the forward rate is forecast from valueDate to maturityDate by the index's forecast curve (useIndexedCoupon=false).
{#fun qlForwardRateAgreement as forwardRateAgreement{withIborIndex*`GenIborIndex ibor'
  ,withDay*`Day' -- ^valueDate
  ,withDay*`Day' -- ^maturityDate
  ,fromEnumC`PositionType',`Double' -- ^strikeForwardRate
  ,`Double' -- ^notionalAmount
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discountCurve
  ,preErrorCheck-`String'errorCheck*-}->`ForwardRateAgreement'peekForwardRateAgreement*#}

-- |If strike is given in the constructor, can calculate the NPV of the contract via NPV().If strike/forward price is desired, it can be obtained via forwardPrice(). In this case, the strike variable in the constructor is irrelevant and will be ignored.
{#fun qlBondForward as bondForward{withDay*`Day' -- ^valueDate
  ,withDay*`Day' -- ^maturityDate
  ,fromEnumC`PositionType',`Double' -- ^strike
  ,fromIntegral`Word' -- ^settlementDays
  ,withDayCounter*`DayCounter',withCalendar*`Calendar',`BusinessDayConvention',withBond*`GenBond b',withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y1)' -- ^discountCurve
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y2)' -- ^incomeDiscountCurve
  ,preErrorCheck-`String'errorCheck*-}->`BondForward'peekBondForward*#}

-- |(dirty) forward bond price minus accrued on bond at delivery
{#fun qlBondForwardCleanForwardPrice as cleanForwardPrice{withBondForward*`BondForward',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |(dirty) forward bond price
{#fun qlBondForwardForwardPrice as forwardPrice{withBondForward*`BondForward',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |forward value/price of underlying, discounting income/dividends
-- if this is a bond forward price, is must be a dirty forward price.
{#fun qlForwardForwardValue as forwardValue{withForward*`GenForward f',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Simple yield calculation based on underlying spot and forward values, taking into account underlying income. When $ t>0 $, call with: underlyingSpotValue=spotValue(t), forwardValue=strikePrice, to get current yield. For a repo, if $ t=0 $, impliedYield should reproduce the spot repo rate. For FRA's, this should reproduce the relevant zero rate at the FRA's maturityDate_;
{#fun qlForwardImpliedYield as impliedYield{withForward*`GenForward f',`Double' -- ^underlyingSpotValue
  ,`Double' -- ^forwarValue
  ,withDay*`Day' -- ^settlementDate
  ,`Compounding',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |Date on which the forward contract settles.
{#fun qlForwardSettlementDate as settlementDate{withForward*`GenForward f',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |NPV of income/dividends/storage-costs etc. of underlying instrument.
{#fun qlForwardSpotIncome as spotIncome{withForward*`GenForward f',withYieldTermStructure*`GenYieldTermStructure y',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns spot value/price of an underlying financial instrument
{#fun qlForwardSpotValue as spotValue{withForward*`GenForward f',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Returns the relevant forward rate associated with the FRA term.
{#fun qlForwardRateAgreementForwardRate as forwardRate{withGenInstrument*`ForwardRateAgreement',preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- |FX forward using nominal amounts in both currencies.
{#fun qlFxForward as fxForward{`Double' -- ^sourceNominal
  ,withCurrency*`Currency' -- ^sourceCurrency
  ,`Double' -- ^targetNominal
  ,withCurrency*`Currency' -- ^targetCurrency
  ,withDay*`Day' -- ^maturityDate
  ,`Bool' -- ^paySourceCurrency
  ,fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,preErrorCheck-`String'errorCheck*-}->`FxForward'peekFxForward*#}

-- |FX forward using a source nominal amount and a contracted forward rate (target/source).
{#fun qlFxForward1 as fxForward'{`Double' -- ^sourceNominal
  ,withCurrency*`Currency' -- ^sourceCurrency
  ,withCurrency*`Currency' -- ^targetCurrency
  ,`Double' -- ^forwardRate
  ,withDay*`Day' -- ^maturityDate
  ,`Bool' -- ^paySourceCurrency
  ,fromIntegral`Word' -- ^settlementDays
  ,withCalendar*`Calendar' -- ^paymentCalendar
  ,preErrorCheck-`String'errorCheck*-}->`FxForward'peekFxForward*#}

-- |The market-implied fair forward rate, computed by the pricing engine.
{#fun qlFxForwardFairForwardRate as fairForwardRate{withGenInstrument*`FxForward',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV in source currency terms.
{#fun qlFxForwardNpvSourceCurrency as npvSourceCurrency{withGenInstrument*`FxForward',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |NPV in target currency terms.
{#fun qlFxForwardNpvTargetCurrency as npvTargetCurrency{withGenInstrument*`FxForward',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
