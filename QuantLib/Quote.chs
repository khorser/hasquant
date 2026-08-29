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

  , QuoteOp(..)
  , MultiQuoteOp(..)
  , derivedQuote
  , compositeQuote
  , multiCompositeQuote
  , withDerivedQuote
  , withCompositeQuote
  , withMultiCompositeQuote
  ) where
import Foreign.Ptr(FunPtr)

import QuantLib.Internal
import QuantLib.Internal.Common
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#enum IntervalPriceType{} add prefix="IntervalPrice" deriving(Show, Eq, Read)#}
{#enum AtmType{} deriving(Show, Eq, Read)#}
{#enum PriceType{} deriving(Show, Eq, Read)#}
{#enum DeltaType{} deriving(Show, Eq, Read)#}

-- |Which binary operation a catalogue 'derivedQuote'\/'compositeQuote' applies. 'derivedQuote'
-- applies it as @quote \`op\` operand@; 'compositeQuote' as @quote1 \`op\` quote2@. The reversed
-- unary forms (@operand \/ quote@, i.e. an FX inversion) are deliberately absent -- that is what
-- 'withDerivedQuote' is for.
{#enum QuoteOp{} deriving(Show, Eq, Read, Bounded)#}

-- |Which fold a catalogue 'multiCompositeQuote' applies over its elements.
{#enum MultiQuoteOp{} deriving(Show, Eq, Read, Bounded)#}

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

-- The quotes below are the only ones here that are not leaf values: they register with their
-- inputs and notify their own observers when one moves. That is the whole reason they are bound
-- rather than done in Haskell -- a quote hasquant hands out is a live node in QuantLib's observer
-- graph, so a curve or instrument built on one of these keeps tracking its inputs, where a value
-- recomputed on the Haskell side would be a dead snapshot the curve never hears about.

-- |A quote derived from another by applying @quote \`op\` operand@, live: it recomputes whenever
-- the underlying quote moves, and notifies everything built on it.
--
-- @'derivedQuote' 'QuoteAdd' base 0.0005@ is the "base plus 5bp" spread quote for a rate helper.
-- For anything outside the 'QuoteOp' catalogue -- @1\/x@, a cap, a nonlinear transform -- use
-- 'withDerivedQuote'.
{#fun qlDerivedQuote as derivedQuote{fromEnumC`QuoteOp',withQuote*`GenQuote q'
  ,`Double' -- ^operand
  ,preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

-- |A quote combining two others as @quote1 \`op\` quote2@, live in both: it recomputes whenever
-- either moves. Use 'withCompositeQuote' for an operation outside the 'QuoteOp' catalogue.
{#fun qlCompositeQuote as compositeQuote{fromEnumC`QuoteOp',withQuote*`GenQuote q1'
  ,withQuote*`GenQuote q2',preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

-- |A quote folding any number of others, live in all of them. An empty list is accepted and
-- gives the fold's identity (@0@ for 'QuoteSum' and 'QuoteNorm2', @1@ for 'QuoteProduct') --
-- upstream imposes no non-empty requirement. Use 'withMultiCompositeQuote' for a fold outside
-- the 'MultiQuoteOp' catalogue.
{#fun qlMultiCompositeQuote as multiCompositeQuote{fromEnumC`MultiQuoteOp'
  ,withQuoteArray*`[GenQuote q]'&,preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

{#fun qlDerivedQuoteFromFunction{withQuote*`GenQuote q',id`FunPtr QuoteUnaryFun'
  ,preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}
{#fun qlCompositeQuoteFromFunction{withQuote*`GenQuote q1',withQuote*`GenQuote q2'
  ,id`FunPtr QuoteBinaryFun',preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}
{#fun qlMultiCompositeQuoteFromFunction{withQuoteArray*`[GenQuote q]'&
  ,id`FunPtr QuoteArrayFun',preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

-- |As 'derivedQuote', but applying an arbitrary Haskell function to the underlying quote's value.
--
-- __The quote is valid only inside the continuation, which must span the whole use -- not just
-- construction.__ QuantLib calls back into @f@ from @Quote::value()@, from wherever the quote was
-- stored, so everything built on it -- every curve, rate helper and instrument, and every pricing
-- call -- must happen before the continuation returns. Leaving it frees the underlying function
-- pointer, and a later read crashes the process. Same rule and same reason as
-- 'QuantLib.Internal.Common.withCustomPayoff'.
--
-- @f@ must be total: an exception thrown inside it propagates out through C++, potentially from
-- the middle of a curve bootstrap. Prefer 'derivedQuote' whenever its 'QuoteOp' catalogue fits --
-- it has neither restriction.
withDerivedQuote :: (Double -> Double) -- ^f(value)
  -> GenQuote q -> (Quote -> IO b) -> IO b
withDerivedQuote f q k = withPayoffFun f (\fp -> qlDerivedQuoteFromFunction q fp >>= k)

-- |As 'compositeQuote', but combining the two quotes with an arbitrary Haskell function. Same
-- continuation-lifetime and totality rules as 'withDerivedQuote'.
withCompositeQuote :: (Double -> Double -> Double) -- ^f(value1, value2)
  -> GenQuote q1 -> GenQuote q2 -> (Quote -> IO b) -> IO b
withCompositeQuote f q1 q2 k = withQuoteBinaryFun f (\fp -> qlCompositeQuoteFromFunction q1 q2 fp >>= k)

-- |As 'multiCompositeQuote', but folding with an arbitrary Haskell function. The whole element
-- vector is passed per evaluation, so this crosses into Haskell once per value, not once per
-- element. Same continuation-lifetime and totality rules as 'withDerivedQuote'.
withMultiCompositeQuote :: ([Double] -> Double) -- ^f(values)
  -> [GenQuote q] -> (Quote -> IO b) -> IO b
withMultiCompositeQuote f qs k = withBasketAccumulateFun f (\fp -> qlMultiCompositeQuoteFromFunction qs fp >>= k)

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
