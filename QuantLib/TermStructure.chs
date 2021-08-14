module QuantLib.TermStructure
  (
    TermStructure
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
  peekObject = newForeignPtr qlFreeTermStructure >=> return . TermStructure

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
