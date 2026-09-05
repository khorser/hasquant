module QuantLib.Quote
  (
     Quote
   , SimpleQuote
   , DeltaVolQuote
   , FuturesConvAdjustmentQuote
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
  , futuresConvAdjustmentQuoteFuturesValue
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

-- |Operation used by 'derivedQuote' or 'compositeQuote'. The former applies
-- @quote \`op\` operand@; the latter applies @quote1 \`op\` quote2@. Use
-- 'withDerivedQuote' for reversed unary operations such as FX inversion.
{#enum QuoteOp{} deriving(Show, Eq, Read, Bounded)#}

-- |Which fold a catalogue 'multiCompositeQuote' applies over its elements.
{#enum MultiQuoteOp{} deriving(Show, Eq, Read, Bounded)#}

{#pointer *QlIndex as Index foreign -> CIndex' nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign -> CSwapIndex' nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlSimpleQuote as Quote foreign -> CSimpleQuote' nocode#}
{#pointer *QlDeltaVolQuote as DeltaVolQuote foreign -> CDeltaVolQuote' nocode#}
{#pointer *QlFuturesConvAdjustmentQuote as FuturesConvAdjustmentQuote foreign -> CFuturesConvAdjustmentQuote' nocode#}
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
  ,preErrorCheck-`String'errorCheck*-}->`FuturesConvAdjustmentQuote'peekFuturesConvAdjustmentQuote*#}

-- |futures-convexity adjustment for an Ibor future identified by its futures (IMM) date
{#fun qlFuturesConvAdjustmentQuote as futuresConvAdjustmentQuote{withIborIndex*`GenIborIndex ibor',withDay*`Day' -- ^futuresDate
  ,withQuote*`GenQuote q1' -- ^futuresQuote
  ,withQuote*`GenQuote q2' -- ^volatility
  ,withQuote*`GenQuote q3' -- ^meanReversion
  ,preErrorCheck-`String'errorCheck*-}->`FuturesConvAdjustmentQuote'peekFuturesConvAdjustmentQuote*#}

-- |The futures-vs-forward-rate value implied by the futures quote alone (@futuresQuote_->value()@).
{#fun qlFuturesConvAdjustmentQuoteFuturesValue as futuresConvAdjustmentQuoteFuturesValue{withGenQuote*`FuturesConvAdjustmentQuote',preErrorCheck-`String'errorCheck*-}->`Double'#}

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

-- |A relinkable quote handle. Objects built from it follow later 'linkTo' calls.
-- 'Nothing' creates an empty handle; reading it throws until linked.
{#fun qlRelinkableQuote as relinkableQuote{withMaybeQuote*`Maybe (GenQuote q)'
  ,preErrorCheck-`String'errorCheck*-}->`RelinkableQuote'peekRelinkableQuote*#}

-- |Point a relinkable handle at another quote. Existing dependents reprice without reconstruction.
-- Use 'setValue' for a value bump; this swaps the quote object.
{#fun qlRelinkableQuoteLinkTo as linkTo{withRelinkableQuote*`RelinkableQuote'
  ,withQuote*`GenQuote q',preErrorCheck-`String'errorCheck*-}->`()'#}

-- These composite quotes are live observer-graph nodes. Haskell-side recomputation would be a snapshot and would not notify dependent curves or instruments.

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

-- |As 'derivedQuote', with an arbitrary Haskell function.
--
-- __The continuation must span the whole use, not only construction.__ QuantLib calls @f@ later from @Quote::value()@. Returning frees its function pointer, so a later read crashes.
--
-- @f@ must be total: exceptions cross C++, including during bootstrap. Prefer 'derivedQuote' when its 'QuoteOp' fits.
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
