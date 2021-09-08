module QuantLib.Quote
  (
     Quote
   , SimpleQuote

   , asQuote
   , PriceType(..)
   , IntervalPriceType(..)
   , AtmType(..)
   , DeltaType(..)

  , simpleQuote
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
  )

  where

import QuantLib.Internal
{#import QuantLib.Index#}(Index)
import{-# SOURCE #-} QuantLib.Index.InterestRate
import QuantLib.Internal.Index
import QuantLib.Internal.Enum
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

{#pointer *QlIborIndex as IborIndex foreign newtype nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign newtype nocode#}

{#pointer *QlQuote as Quote foreign -> CQuote nocode#}
{#pointer *QlSimpleQuote as Quote foreign -> CSimpleQuote nocode#}

{#enum IntervalPriceType{} add prefix="IntervalPrice" deriving(Show, Eq)#}

{#enum AtmType{} deriving(Show, Eq)#}

{#enum PriceType{} deriving(Show, Eq)#}

{#enum DeltaType{} deriving(Show, Eq)#}

-- |market element returning a stored value
{#fun qlSimpleQuote as simpleQuote{`Double', preErrorCheck-`String'errorCheck*-}->`SimpleQuote'peekSimpleQuote*#}

-- |Returns the current value of the given Quote object
{#fun qlQuoteValue as value{withQuote*`GenQuote a', preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the difference between the new value and the old value
-- /NB/ The change will propagate to all users of the quote
{#fun qlSimpleQuoteSetValue as setValue{withSimpleQuote*`SimpleQuote',`Double', preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlEurodollarFuturesImpliedStdDevQuote as eurodollarFuturesImpliedStdDevQuote{withQuote*`GenQuote a', withQuote*`GenQuote b', withQuote*`GenQuote c',`Double',`Double',`Double', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

{#fun qlForwardSwapQuote as forwardSwapQuote{`SwapIndex', withQuote*`GenQuote a', fromEnumQuantity`(Int, TimeUnit)'&, preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

{#fun qlForwardValueQuote as forwardValueQuote{`Index', withDay*`Day', preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

{#fun qlFuturesConvAdjustmentQuote1 as futuresConvAdjustmentQuote'{`IborIndex',`String', withQuote*`GenQuote a', withQuote*`GenQuote b', withQuote*`GenQuote c', preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

{#fun qlFuturesConvAdjustmentQuote as futuresConvAdjustmentQuote{`IborIndex', withDay*`Day', withQuote*`GenQuote a', withQuote*`GenQuote b', withQuote*`GenQuote c', preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

{#fun qlImpliedStdDevQuote as impliedStdDevQuote{fromEnumC`OptionType', withQuote*`GenQuote a', withQuote*`GenQuote b',`Double',`Double',`Double', fromIntegral`Word', preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

{#fun qlLastFixingQuote as lastFixingQuote{`Index', preErrorCheck-`String'errorCheck*-}->`Quote'peekQuote*#}

-- |returns true if the Quote holds a valid value
{#fun qlQuoteIsValid as isValid{withQuote*`GenQuote a', preErrorCheck-`String'errorCheck*-}->`Bool'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
