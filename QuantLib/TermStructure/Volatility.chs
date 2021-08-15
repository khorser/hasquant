module QuantLib.TermStructure.Volatility
  (
    BlackVarianceSurfaceExtrapolation
  , ExtendedBlackVarianceSurfaceExtrapolation

  , BlackVarianceCurve
  , BlackVolTermStructure
  , CallableBondVolatilityStructure
  , CapFloorTermVolSurface
  , LocalVolTermStructure
  , OptionletVolatilityStructure
  , SmileSection
  , SwaptionVolatilityStructure
  , TermStructure
  , VolatilityTermStructure

  , optionletVolatilityStructureAsVolatilityTermStructure
  , volatilityTermStructureAsTermStructure
  , blackVolTermStructureAsVolatilityTermStructure
  , swaptionVolatilityStructureAsVolatilityTermStructure
  , capFloorTermVolSurfaceAsVolatilityTermStructure
  , localVolTermStructureAsVolatilityTermStructure
  , blackVarianceCurveAsBlackVolTermStructure
  , callableBondVolatilityStructureAsTermStructure

  , localVolSurface
  )
  where

import QuantLib.Internal
{#import QuantLib.TermStructure#}(TermStructure)
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
{#import QuantLib.Quote#}(Quote)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

{#pointer *QlBlackVarianceCurve as BlackVarianceCurve foreign finalizer qlFreeBlackVarianceCurve newtype#}
instance ForeignObject BlackVarianceCurve where
  withObject = withBlackVarianceCurve
  peekObject = newForeignPtr qlFreeBlackVarianceCurve >=> return . BlackVarianceCurve

{#pointer *QlBlackVolTermStructure as BlackVolTermStructure foreign finalizer qlFreeBlackVolTermStructure newtype#}
instance ForeignObject BlackVolTermStructure where
  withObject = withBlackVolTermStructure
  peekObject = newForeignPtr qlFreeBlackVolTermStructure >=> return . BlackVolTermStructure
{#pointer *QlCallableBondVolatilityStructure as CallableBondVolatilityStructure foreign finalizer qlFreeCallableBondVolatilityStructure newtype#}
instance ForeignObject CallableBondVolatilityStructure where
  withObject = withCallableBondVolatilityStructure
  peekObject = newForeignPtr qlFreeCallableBondVolatilityStructure >=> return . CallableBondVolatilityStructure

{#pointer *QlCapFloorTermVolSurface as CapFloorTermVolSurface foreign finalizer qlFreeCapFloorTermVolSurface newtype#}
instance ForeignObject CapFloorTermVolSurface where
  withObject = withCapFloorTermVolSurface
  peekObject = newForeignPtr qlFreeCapFloorTermVolSurface >=> return . CapFloorTermVolSurface

{#pointer *QlLocalVolTermStructure as LocalVolTermStructure foreign finalizer qlFreeLocalVolTermStructure newtype#}
instance ForeignObject LocalVolTermStructure where
  withObject = withLocalVolTermStructure
  peekObject = newForeignPtr qlFreeLocalVolTermStructure >=> return . LocalVolTermStructure

{#pointer *QlOptionletVolatilityStructure as OptionletVolatilityStructure foreign finalizer qlFreeOptionletVolatilityStructure newtype#}
instance ForeignObject OptionletVolatilityStructure where
  withObject = withOptionletVolatilityStructure
  peekObject = newForeignPtr qlFreeOptionletVolatilityStructure >=> return . OptionletVolatilityStructure

{#pointer *QlSmileSection as SmileSection foreign finalizer qlFreeSmileSection newtype#}
instance ForeignObject SmileSection where
  withObject = withSmileSection
  peekObject = newForeignPtr qlFreeSmileSection >=> return . SmileSection

{#pointer *QlSwaptionVolatilityStructure as SwaptionVolatilityStructure foreign finalizer qlFreeSwaptionVolatilityStructure newtype#}
instance ForeignObject SwaptionVolatilityStructure where
  withObject = withSwaptionVolatilityStructure
  peekObject = newForeignPtr qlFreeSwaptionVolatilityStructure >=> return . SwaptionVolatilityStructure

{#pointer *QlVolatilityTermStructure as VolatilityTermStructure foreign finalizer qlFreeVolatilityTermStructure newtype#}
instance ForeignObject VolatilityTermStructure where
  withObject = withVolatilityTermStructure
  peekObject = newForeignPtr qlFreeVolatilityTermStructure >=> return . VolatilityTermStructure

{#enum BlackVarianceSurfaceExtrapolation {} deriving(Show, Eq)#}

{#enum ExtendedBlackVarianceSurfaceExtrapolation {} deriving(Show, Eq)#}

{#fun qlOptionletVolatilityStructureAsVolatilityTermStructure as optionletVolatilityStructureAsVolatilityTermStructure {`OptionletVolatilityStructure'} -> `VolatilityTermStructure'#}
{#fun qlVolatilityTermStructureAsTermStructure as volatilityTermStructureAsTermStructure {`VolatilityTermStructure'} -> `TermStructure' peekObject*#}
{#fun qlBlackVolTermStructureAsVolatilityTermStructure as blackVolTermStructureAsVolatilityTermStructure {`BlackVolTermStructure'} -> `VolatilityTermStructure'#}
{#fun qlSwaptionVolatilityStructureAsVolatilityTermStructure as swaptionVolatilityStructureAsVolatilityTermStructure {`SwaptionVolatilityStructure'} -> `VolatilityTermStructure'#}
{#fun qlCapFloorTermVolSurfaceAsVolatilityTermStructure as capFloorTermVolSurfaceAsVolatilityTermStructure {`CapFloorTermVolSurface'} -> `VolatilityTermStructure'#}
{#fun qlLocalVolTermStructureAsVolatilityTermStructure as localVolTermStructureAsVolatilityTermStructure {`LocalVolTermStructure'} -> `VolatilityTermStructure'#}
{#fun qlBlackVarianceCurveAsBlackVolTermStructure as blackVarianceCurveAsBlackVolTermStructure {`BlackVarianceCurve'} -> `BlackVolTermStructure'#}
{#fun qlCallableBondVolatilityStructureAsTermStructure as callableBondVolatilityStructureAsTermStructure {`CallableBondVolatilityStructure'} -> `TermStructure' peekObject*#}

{#fun qlLocalVolSurface as localVolSurface {`BlackVolTermStructure', withObject* `YieldTermStructure', withObject* `YieldTermStructure', withObject* `Quote', preErrorCheck- `String' errorCheck*-} -> `LocalVolTermStructure'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
