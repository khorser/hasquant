module QuantLib.Instrument.Option
  (
    ExerciseType(..)
  , Option
  , CdsOption
  , asOption
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

import QuantLib.Internal
{#import QuantLib.Instrument#}

{#enum ExerciseType {} deriving(Show, Eq)#}

{#pointer *QlOption as Option foreign finalizer qlFreeOption newtype#}
instance ForeignObject Option where
  withObject = withOption
  peekObject = newForeignPtr qlFreeOption >=> return . Option
instance IsInstrument Option where asInstrument = qlOptionAsInstrument
{#fun qlOptionAsInstrument {`Option'} -> `Instrument' peekObject*#}

class IsOption a where
  asOption :: a -> IO Option

{#pointer *QlCdsOption as CdsOption foreign finalizer qlFreeCdsOption newtype#}
instance ForeignObject CdsOption where
  withObject = withCdsOption
  peekObject = newForeignPtr qlFreeCdsOption >=> return . CdsOption
instance IsOption CdsOption where asOption = qlCdsOptionAsOption
{#fun qlCdsOptionAsOption {`CdsOption'} -> `Option'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
