{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts, TypeOperators #-}
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
import QuantLib.Type
{#import QuantLib.Time.Schedule#}(TimeUnit)
{#import QuantLib.Index#}(Index)
import {-# SOURCE #-} QuantLib.Index.InterestRate
import QuantLib.Internal.Index
import QuantLib.Internal.Enum

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

{#pointer *QlIborIndex as IborIndex foreign newtype nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign newtype nocode#}

{#pointer *QlQuote as Quote foreign finalizer qlFreeQuote newtype#}
instance ForeignObject Quote where
  withObject = withQuote
  constructor = Quote
  finalizer = qlFreeQuote

{#pointer *QlSimpleQuote as SimpleQuote foreign finalizer qlFreeSimpleQuote newtype#}
instance ForeignObject SimpleQuote where
  withObject = withSimpleQuote
  constructor = SimpleQuote
  finalizer = qlFreeSimpleQuote

{#enum IntervalPriceType{} add prefix="IntervalPrice" deriving(Show, Eq)#}

{#enum AtmType {} deriving(Show, Eq)#}

{#enum DeltaType {} deriving(Show, Eq)#}

instance SimpleQuote `Derives` Quote where cast = qlSimpleQuoteAsQuote
asQuote :: (a `Derives` Quote) => a -> IO Quote
asQuote = cast

{#fun qlSimpleQuoteAsQuote {`SimpleQuote'} -> `Quote'#}

-- |market element returning a stored value
{#fun qlSimpleQuote as simpleQuote {`Double', preErrorCheck- `String' errorCheck*-} -> `SimpleQuote'#}

-- |Returns the current value of the given Quote object
{#fun qlQuoteValue as value {`Quote', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the difference between the new value and the old value
-- /NB/ The change will propagate to all users of the quote
{#fun qlSimpleQuoteSetValue as setValue {`SimpleQuote', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlEurodollarFuturesImpliedStdDevQuote as eurodollarFuturesImpliedStdDevQuote {`Quote', `Quote' , `Quote' , `Double' , `Double' , `Double' , fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `Quote'#}

{#fun qlForwardSwapQuote as forwardSwapQuote {`SwapIndex', `Quote', fromEnumQuantity `(Int, TimeUnit)'&, preErrorCheck- `String' errorCheck*-} -> `Quote'#}

{#fun qlForwardValueQuote as forwardValueQuote {`Index', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Quote'#}

{#fun qlFuturesConvAdjustmentQuote1 as futuresConvAdjustmentQuote' {`IborIndex', `String' , `Quote' , `Quote' , `Quote', preErrorCheck- `String' errorCheck*-} -> `Quote'#}

{#fun qlFuturesConvAdjustmentQuote as futuresConvAdjustmentQuote {`IborIndex', withDay* `Day', `Quote', `Quote', `Quote', preErrorCheck- `String' errorCheck*-} -> `Quote'#}

{#fun qlImpliedStdDevQuote as impliedStdDevQuote {fromEnumC `OptionType', `Quote' , `Quote' , `Double' , `Double' , `Double' , fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `Quote'#}

{#fun qlLastFixingQuote as lastFixingQuote {`Index', preErrorCheck- `String' errorCheck*-} -> `Quote'#}

-- |returns true if the Quote holds a valid value
{#fun qlQuoteIsValid as isValid {`Quote', preErrorCheck- `String' errorCheck*-} -> `Bool'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
