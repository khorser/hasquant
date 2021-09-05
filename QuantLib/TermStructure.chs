{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts, TypeOperators #-}
module QuantLib.TermStructure
  (
    TermStructure
  , asTermStructure
  )
  where

import QuantLib.Type
import QuantLib.Internal

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlTermStructure as TermStructure foreign finalizer qlFreeTermStructure newtype#}
instance ForeignObject TermStructure where
  withObject = withTermStructure
  constructor = TermStructure
  finalizer = qlFreeTermStructure

asTermStructure :: (a`Derives` TermStructure) => a -> IO TermStructure
asTermStructure = cast

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
