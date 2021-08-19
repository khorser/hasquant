module QuantLib.TermStructure
  (
    TermStructure
  , IsTermStructure(..)
  )
  where
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

class IsTermStructure a where
  asTermStructure :: a -> IO TermStructure

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
