module QuantLib.Quote
  (
     Quote
   , SimpleQuote
   , DeltaVolQuote
   , RelinkableQuote
   , GenQuote

   , asQuote
   , PriceType(..)
   , IntervalPriceType(..)
   , AtmType(..)
   , DeltaType(..)

  , simpleQuote
  , deltaVolQuote
  , atmVolQuote
  , value
  , isValid
  , setValue
  , eurodollarFuturesImpliedStdDevQuote
  , forwardSwapQuote
  , forwardValueQuote
  , futuresConvAdjustmentQuote'
  , futuresConvAdjustmentQuote
  , impliedStdDevQuote
  , lastFixingQuote
  , relinkableQuote
  , linkTo
  ) where
import QuantLib.Internal
import QuantLib.Internal.Enum
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

{#enum IntervalPriceType{} add prefix="IntervalPrice" deriving(Show, Eq)#}
{#enum AtmType{} deriving(Show, Eq)#}
{#enum PriceType{} deriving(Show, Eq)#}
{#enum DeltaType{} deriving(Show, Eq)#}

{#pointer *QlIndex as Index foreign -> CIndex' nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign -> CSwapIndex' nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlSimpleQuote as Quote foreign -> CSimpleQuote' nocode#}
{#pointer *QlDeltaVolQuote as DeltaVolQuote foreign -> CDeltaVolQuote' nocode#}
{#pointer *QlRelinkableQuote as RelinkableQuote foreign -> CRelinkableQuote' nocode#}

-- |market element returning a stored value
{#fun qlSimpleQuote as simpleQuote{`Double',preErrorCheck-`String'errorCheck*-}->`SimpleQuote'peekSimpleQuote*#}

-- |quotation of an FX delta vs vol, e.g. a 25-delta risk-reversal/butterfly point
{#fun qlDeltaVolQuote1 as deltaVolQuote{`Double' -- ^delta
  ,withQuote*`GenQuote q' -- ^vol
  ,`Double' -- ^maturity
  ,fromEnumC`DeltaType'
  ,preErrorCheck-`String'errorCheck*-}->`DeltaVolQuote'peekDeltaVolQuote*#}

-- |quotation of an FX at-the-money vol point (e.g. ATM straddle)
{#fun qlDeltaVolQuote2 as atmVolQuote{withQuote*`GenQuote q' -- ^vol
  ,fromEnumC`DeltaType'
  ,`Double' -- ^maturity
  ,fromEnumC`AtmType'
  ,preErrorCheck-`String'errorCheck*-}->`DeltaVolQuote'peekDeltaVolQuote*#}

-- |Returns the current value of the given Quote object
{#fun qlQuoteValue as value{withQuote*`GenQuote q',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the difference between the new value and the old value
-- /NB/ The change will propagate to all users of the quote
{#fun qlSimpleQuoteSetValue as setValue{withGenQuote*`SimpleQuote',`Double',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |implied standard deviation of a Eurodollar future's underlying, solved from its call/put prices
{#fun qlEurodollarFuturesImpliedStdDevQuote as eurodollarFuturesImpliedStdDevQuote{withQuote*`GenQuote q1' -- ^forward
  ,withQuote*`GenQuote q2' -- ^callPrice
  ,withQuote*`GenQuote q3' -- ^putPrice
  ,`Double' -- ^strike
  ,`Double' -- ^guess
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxIter
  ,preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

-- |implied rate of a forward-starting swap on the given swap index, offset by a spread quote
{#fun qlForwardSwapQuote as forwardSwapQuote{withSwapIndex*`GenSwapIndex sidx',withQuote*`GenQuote q' -- ^spread
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^fwdStart
  ,preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

-- |forward value of an index as of a given fixing date
{#fun qlForwardValueQuote as forwardValueQuote{withIndex*`GenIndex idx',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

-- |futures-convexity adjustment for an Ibor future identified by its IMM code
{#fun qlFuturesConvAdjustmentQuote1 as futuresConvAdjustmentQuote'{withIborIndex*`GenIborIndex ibor',`String' -- ^immCode
  ,withQuote*`GenQuote q1' -- ^futuresQuote
  ,withQuote*`GenQuote q2' -- ^volatility
  ,withQuote*`GenQuote q3' -- ^meanReversion
  ,preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

-- |futures-convexity adjustment for an Ibor future identified by its futures (IMM) date
{#fun qlFuturesConvAdjustmentQuote as futuresConvAdjustmentQuote{withIborIndex*`GenIborIndex ibor',withDay*`Day' -- ^futuresDate
  ,withQuote*`GenQuote q1' -- ^futuresQuote
  ,withQuote*`GenQuote q2' -- ^volatility
  ,withQuote*`GenQuote q3' -- ^meanReversion
  ,preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

-- |implied standard deviation of an underlying, solved from its option price at a given strike
{#fun qlImpliedStdDevQuote as impliedStdDevQuote{fromEnumC`OptionType',withQuote*`GenQuote q1' -- ^forward
  ,withQuote*`GenQuote q2' -- ^price
  ,`Double' -- &strike
  ,`Double' -- ^guess
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxIter
  ,preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

-- |last available fixing of the given index, updating whenever a new fixing is added
{#fun qlLastFixingQuote as lastFixingQuote{withIndex*`GenIndex idx',preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

-- |returns true if the Quote holds a valid value
{#fun qlQuoteIsValid as isValid{withQuote*`GenQuote q',preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- |A quote behind a relinkable handle. The result /is/ a 'Quote': pass it to any quote-taking
-- function and everything built on it keeps tracking whatever the handle currently points at,
-- so a later 'linkTo' reprices already-constructed instruments without rebuilding them.
-- 'Nothing' gives an empty handle -- meaningful rather than an error -- but reading a value
-- through one throws until it is linked. Mirrors 'QuantLib.TermStructure.Yield.relinkableYieldTermStructure'.
{#fun qlRelinkableQuote as relinkableQuote{withMaybeQuote*`Maybe (GenQuote q)'
  ,preErrorCheck-`String'errorCheck*-}->`RelinkableQuote'peekRelinkableQuote*#}

-- |Point a relinkable handle at a different quote. Everything already built on the handle
-- reprices against the new quote, with no object rebuilt.
--
-- This is the one mutator in the module besides 'setValue'. The API rules here otherwise
-- forbid new setters and prefer constructing a fresh object, but relinking /is/ the capability
-- being bound -- the same justification as 'QuantLib.TermStructure.Yield.linkTo'. Note the
-- narrower payoff versus curves: 'SimpleQuote.setValue' already covers the common bump case,
-- so this buys swapping in a different quote object, not a different value.
{#fun qlRelinkableQuoteLinkTo as linkTo{withRelinkableQuote*`RelinkableQuote'
  ,withQuote*`GenQuote q',preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
