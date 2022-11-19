{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts, TypeOperators #-}
module QuantLib.Instrument.Forward
  (
    Forward
  , asForward
  , ForwardRateAgreement
  , BondForward

  , forwardRateAgreement
  , bondForward

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

import QuantLib.Type
import QuantLib.Internal
{#import QuantLib.Instrument#}
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
import QuantLib.Internal.Type
{#import QuantLib.InterestRate#}

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlBond as Bond foreign -> CBond nocode#}
{#pointer *QlForward as Forward foreign -> CForward nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}
{#pointer *QlFixedRateBond as FixedRateBond foreign -> CFixedRateBond nocode#}

{#fun qlForwardAsInstrument{withForward*`Forward'}->`Instrument'peekInstrument*#}
instance Forward`Derives` Instrument where cast = qlForwardAsInstrument

asForward :: (a`Derives` Forward) => a -> IO Forward
asForward = cast

{#pointer *QlForwardRateAgreement as ForwardRateAgreement foreign -> CForwardRateAgreement nocode#}

{#fun qlForwardRateAgreementAsInstrument{withForwardRateAgreement*`ForwardRateAgreement'}->`Instrument'peekInstrument*#}
instance ForwardRateAgreement`Derives` Instrument where cast = qlForwardRateAgreementAsInstrument

{#pointer *QlBondForward as BondForward foreign -> CBondForward nocode#}

{#fun qlBondForwardAsForward{withBondForward*`BondForward'}->`Forward'peekForward*#}
instance BondForward`Derives` Forward where cast = qlBondForwardAsForward

{#fun qlForwardRateAgreement as forwardRateAgreement{withDay*`Day' -- ^valueDate
  ,withDay*`Day' -- ^maturityDate
  ,fromEnumC`PositionType',`Double' -- ^strikeForwardRate
  ,`Double' -- ^notionalAmount
  ,withIborIndex*`GenIborIndex a',withMaybeYieldTermStructure*`Maybe YieldTermStructure' -- ^discountCurve
  ,preErrorCheck-`String'errorCheck*-}->`ForwardRateAgreement'peekForwardRateAgreement*#}

-- |If strike is given in the constructor, can calculate the NPV of the contract via NPV().If strike/forward price is desired, it can be obtained via forwardPrice(). In this case, the strike variable in the constructor is irrelevant and will be ignored.
{#fun qlBondForward as bondForward{withDay*`Day' -- ^valueDate
  ,withDay*`Day' -- ^maturityDate
  ,fromEnumC`PositionType',`Double' -- ^strike
  ,fromIntegral`Word' -- ^settlementDays
  ,withDayCounter*`DayCounter',withCalendar*`Calendar',`BusinessDayConvention',withBond*`Bond',withMaybeYieldTermStructure*`Maybe YieldTermStructure' -- ^discountCurve
  ,withMaybeYieldTermStructure*`Maybe YieldTermStructure' -- ^incomeDiscountCurve
  ,preErrorCheck-`String'errorCheck*-}->`BondForward'peekBondForward*#}

-- |(dirty) forward bond price minus accrued on bond at delivery
{#fun qlBondForwardCleanForwardPrice as cleanForwardPrice{withBondForward*`BondForward',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |(dirty) forward bond price
{#fun qlBondForwardForwardPrice as forwardPrice{withBondForward*`BondForward',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |forward value/price of underlying, discounting income/dividends
-- if this is a bond forward price, is must be a dirty forward price.
{#fun qlForwardForwardValue as forwardValue{withForward*`Forward',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Simple yield calculation based on underlying spot and forward values, taking into account underlying income. When $ t>0 $, call with: underlyingSpotValue=spotValue(t), forwardValue=strikePrice, to get current yield. For a repo, if $ t=0 $, impliedYield should reproduce the spot repo rate. For FRA's, this should reproduce the relevant zero rate at the FRA's maturityDate_;
{#fun qlForwardImpliedYield as impliedYield{withForward*`Forward',`Double' -- ^underlyingSpotValue
  ,`Double' -- ^forwarValue
  ,withDay*`Day' -- ^settlementDate
  ,`Compounding',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}
{#fun qlForwardSettlementDate as settlementDate{withForward*`Forward',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}
-- |NPV of income/dividends/storage-costs etc. of underlying instrument.
{#fun qlForwardSpotIncome as spotIncome{withForward*`Forward',withYieldTermStructure*`YieldTermStructure',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns spot value/price of an underlying financial instrument
{#fun qlForwardSpotValue as spotValue{withForward*`Forward',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Returns the relevant forward rate associated with the FRA term.
{#fun qlForwardRateAgreementForwardRate as forwardRate{withForwardRateAgreement*`ForwardRateAgreement',preErrorCheck-`String'errorCheck*-}->`InterestRate'peekInterestRate*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
