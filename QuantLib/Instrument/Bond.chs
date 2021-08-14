module QuantLib.Instrument.Bond
  (
    Bond
  )
  where
import QuantLib.Internal

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlBond as Bond foreign finalizer qlFreeBond newtype#}
instance ForeignObject Bond where
  withObject = withBond
  peekObject = newForeignPtr qlFreeBond >=> return . Bond

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
