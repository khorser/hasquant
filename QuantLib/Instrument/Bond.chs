module QuantLib.Instrument.Bond
  (
    Bond
  , FixedRateBond
  , ConvertibleBond
  , CallableBond

  , asInstrument
  , asBond

  , atmRate
  )
  where
import QuantLib.Internal
{#import QuantLib.Instrument#}
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *QlBond as Bond foreign finalizer qlFreeBond newtype#}
instance ForeignObject Bond where
  withObject = withBond
  peekObject = newForeignPtr qlFreeBond >=> return . Bond

{#fun qlBondAsInstrument {`Bond'} -> `Instrument' peekObject*#}
instance IsInstrument Bond where asInstrument = qlBondAsInstrument

class IsBond a where asBond :: a -> IO Bond

{#pointer *QlFixedRateBond as FixedRateBond foreign finalizer qlFreeFixedRateBond newtype#}
instance ForeignObject FixedRateBond where
  withObject = withFixedRateBond
  peekObject = newForeignPtr qlFreeFixedRateBond >=> return . FixedRateBond
{#fun qlFixedRateBondAsBond {`FixedRateBond'} -> `Bond'#}
instance IsBond FixedRateBond where asBond = qlFixedRateBondAsBond

{#pointer *QlCallableBond as CallableBond foreign finalizer qlFreeCallableBond newtype#}
instance ForeignObject CallableBond where
  withObject = withCallableBond
  peekObject = newForeignPtr qlFreeCallableBond >=> return . CallableBond
{#fun qlCallableBondAsBond {`CallableBond'} -> `Bond'#}
instance IsBond CallableBond where asBond = qlCallableBondAsBond

{#pointer *QlConvertibleBond as ConvertibleBond foreign finalizer qlFreeConvertibleBond newtype#}
instance ForeignObject ConvertibleBond where
  withObject = withConvertibleBond
  peekObject = newForeignPtr qlFreeConvertibleBond >=> return . ConvertibleBond
{#fun qlConvertibleBondAsBond {`ConvertibleBond'} -> `Bond'#}
instance IsBond ConvertibleBond where asBond = qlConvertibleBondAsBond

{#fun qlBondFunctionsAtmRate as atmRate {`Bond', withObject* `YieldTermStructure', fromDay* `Day', `Double', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
