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

  , asVolatilityTermStructure
  , asBlackVolTermStructure

  , localVolSurface
  , constantOptionletVolatility
  , constantOptionletVolatility'

  , impliedVolTermStructure
  , blackConstantVol'
  , blackConstantVol
  , constantSwaptionVolatility'
  , constantSwaptionVolatility
  , blackVarianceForPeriod'
  , blackVarianceForPeriod
  , blackVarianceForTenor
  , blackVariance'
  , blackVariance
  , blackVarianceForPeriods
  , maxSwapLength
  , maxSwapTenor
  , smileSectionForPeriod'
  , smileSectionForPeriod
  , smileSectionForTenor
  , smileSection'
  , smileSection
  , smileSectionForPeriods
  , swapLength'
  , swapLength
  , volatilityForPeriod'
  , volatilityForPeriod
  , volatilityForTenor
  , volatilityForTenor'
  , volatility
  , volatilityForPeriods
  , callableBondConstantVolatility'
  , callableBondConstantVolatility
  , constantCapFloorTermVolatility'
  , constantCapFloorTermVolatility
  , spreadedSwaptionVolatility
  , localConstantVol'
  , localConstantVol
  , localVolCurve
  , capFloorTermVolCurve
  , capFloorTermVolCurve'
  , blackVarianceCurve
  , capFloorTermVolSurface
  , capFloorTermVolSurface'
  , blackVarianceSurface
  )
  where

import QuantLib.Internal
{#import QuantLib.TermStructure#}
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
{#import QuantLib.Quote#}(Quote)
{#import QuantLib.Time.Calendar#}(Calendar, BusinessDayConvention)
{#import QuantLib.Time.Schedule#}(TimeUnit, DayCounter)
import QuantLib.Enum
import QuantLib.Math(Interpolation)

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

class IsVolatilityTermStructure a where asVolatilityTermStructure :: a -> IO VolatilityTermStructure

{#fun qlOptionletVolatilityStructureAsVolatilityTermStructure {`OptionletVolatilityStructure'} -> `VolatilityTermStructure'#}
instance IsVolatilityTermStructure OptionletVolatilityStructure where asVolatilityTermStructure = qlOptionletVolatilityStructureAsVolatilityTermStructure

{#fun qlVolatilityTermStructureAsTermStructure {`VolatilityTermStructure'} -> `TermStructure' peekObject*#}
instance IsTermStructure VolatilityTermStructure where asTermStructure = qlVolatilityTermStructureAsTermStructure

{#fun qlBlackVolTermStructureAsVolatilityTermStructure {`BlackVolTermStructure'} -> `VolatilityTermStructure'#}
instance IsVolatilityTermStructure BlackVolTermStructure where asVolatilityTermStructure = qlBlackVolTermStructureAsVolatilityTermStructure

{#fun qlSwaptionVolatilityStructureAsVolatilityTermStructure {`SwaptionVolatilityStructure'} -> `VolatilityTermStructure'#}
instance IsVolatilityTermStructure SwaptionVolatilityStructure where asVolatilityTermStructure = qlSwaptionVolatilityStructureAsVolatilityTermStructure

{#fun qlCapFloorTermVolSurfaceAsVolatilityTermStructure {`CapFloorTermVolSurface'} -> `VolatilityTermStructure'#}
instance IsVolatilityTermStructure CapFloorTermVolSurface where asVolatilityTermStructure = qlCapFloorTermVolSurfaceAsVolatilityTermStructure

{#fun qlLocalVolTermStructureAsVolatilityTermStructure {`LocalVolTermStructure'} -> `VolatilityTermStructure'#}
instance IsVolatilityTermStructure LocalVolTermStructure where asVolatilityTermStructure = qlLocalVolTermStructureAsVolatilityTermStructure

{#fun qlBlackVarianceCurveAsBlackVolTermStructure as asBlackVolTermStructure {`BlackVarianceCurve'} -> `BlackVolTermStructure'#}

{#fun qlCallableBondVolatilityStructureAsTermStructure {`CallableBondVolatilityStructure'} -> `TermStructure' peekObject*#}
instance IsTermStructure CallableBondVolatilityStructure where asTermStructure = qlCallableBondVolatilityStructureAsTermStructure;

{#fun qlLocalVolSurface as localVolSurface {`BlackVolTermStructure', withObject* `YieldTermStructure', withObject* `YieldTermStructure', withObject* `Quote', preErrorCheck- `String' errorCheck*-} -> `LocalVolTermStructure'#}

-- |Constant caplet volatility, no time-strike dependence
-- floating reference date, floating market data
{#fun qlConstantOptionletVol1 as constantOptionletVolatility' {fromIntegral `Word', withObject* `Calendar', `BusinessDayConvention', withObject* `Quote', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `OptionletVolatilityStructure'#}

-- |fixed reference date, floating market data
{#fun qlConstantOptionletVolatility as constantOptionletVolatility {fromDay* `Day', withObject* `Calendar', `BusinessDayConvention', withObject* `Quote', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `OptionletVolatilityStructure'#}

{#fun qlBlackConstantVol1 as blackConstantVol' {fromIntegral `Word', withObject* `Calendar', withObject* `Quote', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `BlackVolTermStructure'#}

{#fun qlBlackConstantVol as blackConstantVol {fromDay* `Day', withObject* `Calendar', withObject* `Quote', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `BlackVolTermStructure'#}

-- |fixed reference date, floating market data
{#fun qlConstantSwaptionVolatility1 as constantSwaptionVolatility' {fromDay* `Day', withObject* `Calendar', `BusinessDayConvention', withObject* `Quote', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `SwaptionVolatilityStructure'#}

-- |floating reference date, floating market data
{#fun qlConstantSwaptionVolatility as constantSwaptionVolatility {fromIntegral `Word', withObject* `Calendar', `BusinessDayConvention', withObject* `Quote', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `SwaptionVolatilityStructure'#}

-- |returns the Black variance for a given option date and swap tenor
{#fun qlSwaptionVolatilityStructureBlackVariance1 as blackVarianceForPeriod' {`SwaptionVolatilityStructure', fromDay* `Day', fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the Black variance for a given option time and swap tenor
{#fun qlSwaptionVolatilityStructureBlackVariance2 as blackVarianceForPeriod {`SwaptionVolatilityStructure', `Double', fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the Black variance for a given option tenor and swap length
{#fun qlSwaptionVolatilityStructureBlackVariance3 as blackVarianceForTenor {`SwaptionVolatilityStructure', fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the Black variance for a given option date and swap length
{#fun qlSwaptionVolatilityStructureBlackVariance4 as blackVariance' {`SwaptionVolatilityStructure', fromDay* `Day', `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the Black variance for a given option time and swap length
{#fun qlSwaptionVolatilityStructureBlackVariance5 as blackVariance {`SwaptionVolatilityStructure', `Double', `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the Black variance for a given option tenor and swap tenor
{#fun qlSwaptionVolatilityStructureBlackVariance as blackVarianceForPeriods {`SwaptionVolatilityStructure', fromEnumQuantity `(Word, TimeUnit)'&, fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |the largest swapLength for which the term structure can return vols
{#fun qlSwaptionVolatilityStructureMaxSwapLength as maxSwapLength {`SwaptionVolatilityStructure', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |the largest length for which the term structure can return vols
{#fun qlSwaptionVolatilityStructureMaxSwapTenor as maxSwapTenor {`SwaptionVolatilityStructure', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#}

-- |returns the smile for a given option date and swap tenor
{#fun qlSwaptionVolatilityStructureSmileSection1 as smileSectionForPeriod' {`SwaptionVolatilityStructure', fromDay* `Day', fromEnumQuantity `(Word, TimeUnit)'&, `Bool', preErrorCheck- `String' errorCheck*-} -> `SmileSection'#}

-- |returns the smile for a given option time and swap tenor
{#fun qlSwaptionVolatilityStructureSmileSection2 as smileSectionForPeriod {`SwaptionVolatilityStructure', `Double', fromEnumQuantity `(Word, TimeUnit)'&, `Bool', preErrorCheck- `String' errorCheck*-} -> `SmileSection'#}

-- |returns the smile for a given option tenor and swap length
{#fun qlSwaptionVolatilityStructureSmileSection3 as smileSectionForTenor {`SwaptionVolatilityStructure', fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `SmileSection'#}

-- |returns the smile for a given option date and swap length
{#fun qlSwaptionVolatilityStructureSmileSection4 as smileSection' {`SwaptionVolatilityStructure', fromDay* `Day', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `SmileSection'#}

-- |returns the smile for a given option time and swap length
{#fun qlSwaptionVolatilityStructureSmileSection5 as smileSection {`SwaptionVolatilityStructure', `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `SmileSection'#}

-- |returns the smile for a given option tenor and swap tenor
{#fun qlSwaptionVolatilityStructureSmileSection as smileSectionForPeriods {`SwaptionVolatilityStructure', fromEnumQuantity `(Word, TimeUnit)'&, fromEnumQuantity `(Word, TimeUnit)'&, `Bool', preErrorCheck- `String' errorCheck*-} -> `SmileSection'#}

-- |implements the conversion between swap dates and swap (time) length
{#fun qlSwaptionVolatilityStructureSwapLength1 as swapLength' {`SwaptionVolatilityStructure', fromDay* `Day', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |implements the conversion between swap tenor and swap (time) length
{#fun qlSwaptionVolatilityStructureSwapLength as swapLength {`SwaptionVolatilityStructure', fromEnumQuantity `(Word, TimeUnit)'&, preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the volatility for a given option date and swap tenor
{#fun qlSwaptionVolatilityStructureVolatility1 as volatilityForPeriod' {`SwaptionVolatilityStructure', fromDay* `Day', fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the volatility for a given option time and swap tenor
{#fun qlSwaptionVolatilityStructureVolatility2 as volatilityForPeriod {`SwaptionVolatilityStructure', `Double', fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the volatility for a given option tenor and swap length
{#fun qlSwaptionVolatilityStructureVolatility3 as volatilityForTenor {`SwaptionVolatilityStructure', fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the volatility for a given option date and swap length
{#fun qlSwaptionVolatilityStructureVolatility4 as volatilityForTenor' {`SwaptionVolatilityStructure', fromDay* `Day', `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the volatility for a given option time and swap length
{#fun qlSwaptionVolatilityStructureVolatility5 as volatility {`SwaptionVolatilityStructure', `Double', `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the volatility for a given option tenor and swap tenor
{#fun qlSwaptionVolatilityStructureVolatility as volatilityForPeriods {`SwaptionVolatilityStructure', fromEnumQuantity `(Word, TimeUnit)'&, fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCallableBondConstantVolatility1 as callableBondConstantVolatility' {fromIntegral `Word', withObject* `Calendar', withObject* `Quote', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `CallableBondVolatilityStructure'#}

{#fun qlCallableBondConstantVolatility as callableBondConstantVolatility {fromDay* `Day', withObject* `Quote', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `CallableBondVolatilityStructure'#}

-- |fixed reference date, floating market data
{#fun qlConstantCapFloorTermVolatility1 as constantCapFloorTermVolatility' {fromDay* `Day', withObject* `Calendar', `BusinessDayConvention', withObject* `Quote', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `VolatilityTermStructure'#}

-- |floating reference date, floating market data
{#fun qlConstantCapFloorTermVolatility as constantCapFloorTermVolatility {fromIntegral `Word', withObject* `Calendar', `BusinessDayConvention', withObject* `Quote', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `VolatilityTermStructure'#}

{#fun qlSpreadedSwaptionVolatility as spreadedSwaptionVolatility {`SwaptionVolatilityStructure' , withObject* `Quote' , preErrorCheck- `String' errorCheck*-} -> `SwaptionVolatilityStructure'#}

{#fun qlLocalConstantVol1 as localConstantVol' {fromIntegral `Word', withObject* `Calendar', withObject* `Quote', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `LocalVolTermStructure'#}

{#fun qlLocalConstantVol as localConstantVol {fromDay* `Day', withObject* `Quote', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `LocalVolTermStructure'#}

{#fun qlLocalVolCurve as localVolCurve {`BlackVarianceCurve', preErrorCheck- `String' errorCheck*-} -> `LocalVolTermStructure'#}

{#fun qlImpliedVolTermStructure as impliedVolTermStructure {`BlackVolTermStructure', fromDay* `Day', preErrorCheck- `String' errorCheck*-} -> `BlackVolTermStructure'#}

-- |fixed reference date, floating market data
capFloorTermVolCurve' :: Day -> Calendar -> BusinessDayConvention -> [(Word, TimeUnit, Quote)] -> DayCounter -> IO VolatilityTermStructure
capFloorTermVolCurve' d c bd ntq = qlCapFloorTermVolCurve1 d c bd n t q where (n, t, q) = unzip3 ntq

{#fun qlCapFloorTermVolCurve1 {fromDay* `Day', withObject* `Calendar', `BusinessDayConvention', withIntArray* `[Word]'&, withEnumArray* `[TimeUnit]'&, withObjectArray* `[Quote]'&, withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `VolatilityTermStructure'#}

-- |floating reference date, floating market data
capFloorTermVolCurve :: Word -> Calendar -> BusinessDayConvention -> [(Word, TimeUnit, Quote)] -> DayCounter -> IO VolatilityTermStructure
capFloorTermVolCurve d c bd ntq = qlCapFloorTermVolCurve d c bd n t q where (n, t, q) = unzip3 ntq

{#fun qlCapFloorTermVolCurve {fromIntegral `Word', withObject* `Calendar', `BusinessDayConvention', withIntArray* `[Word]'&, withEnumArray* `[TimeUnit]'&, withObjectArray* `[Quote]'&, withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `VolatilityTermStructure'#}

blackVarianceCurve :: Day -> [(Day, Double)] -> DayCounter -> Bool -> Maybe Interpolation -> IO BlackVarianceCurve
blackVarianceCurve d dq dc f i = qlBlackVarianceCurve d dd q dc f i1 i2 i3
  where (dd, q) = unzip dq
        (i1, (i2, i3)) = qlInterpolation' i

{#fun qlBlackVarianceCurve {fromDay* `Day' , withDayArray* `[Day]'& , withDoubleArray* `[Double]'& , withObject* `DayCounter' , `Bool' , `Int', `Int', `Int' , preErrorCheck- `String' errorCheck*-} -> `BlackVarianceCurve'#}
 
blackVarianceSurface :: Day -> Calendar -> [Day] -> [Double] -> Matrix Double -> DayCounter -> BlackVarianceSurfaceExtrapolation -> BlackVarianceSurfaceExtrapolation -> IO BlackVolTermStructure
blackVarianceSurface d c ds s (Matrix mr mc md) = qlBlackVarianceSurface d c ds s mr mc md

{#fun qlBlackVarianceSurface {fromDay* `Day', withObject* `Calendar', withDayArray* `[Day]'&, withDoubleArray* `[Double]'&, fromIntegral `Word', fromIntegral `Word', withDoubleArrayRaw* `[Double]', withObject* `DayCounter', `BlackVarianceSurfaceExtrapolation', `BlackVarianceSurfaceExtrapolation', preErrorCheck- `String' errorCheck*-} -> `BlackVolTermStructure'#}
 
-- |floating reference date, floating market data
capFloorTermVolSurface :: Word -> Calendar -> BusinessDayConvention -> [(Word, TimeUnit)] -> [Double] -> Matrix Quote -> DayCounter -> IO CapFloorTermVolSurface
capFloorTermVolSurface d c bd t s (Matrix mr mc md) = qlCapFloorTermVolSurface d c bd pl pu s mr mc md where (pl, pu) = unzip t

{#fun qlCapFloorTermVolSurface {fromIntegral `Word', withObject* `Calendar', `BusinessDayConvention', withIntArray* `[Word]'&, withEnumArray* `[TimeUnit]'&, withDoubleArray* `[Double]'&, fromIntegral `Word', fromIntegral `Word', withObjectArrayRaw* `[Quote]', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `CapFloorTermVolSurface'#}
 
-- |fixed reference date, floating market data
capFloorTermVolSurface' :: Day -> Calendar -> BusinessDayConvention -> [(Word, TimeUnit)] -> [Double] -> Matrix Quote -> DayCounter -> IO CapFloorTermVolSurface
capFloorTermVolSurface' d c bd t s (Matrix mr mc md) = qlCapFloorTermVolSurface1 d c bd pl pu s mr mc md where (pl, pu) = unzip t

{#fun qlCapFloorTermVolSurface1 {fromDay* `Day', withObject* `Calendar', `BusinessDayConvention', withIntArray* `[Word]'&, withEnumArray* `[TimeUnit]'&, withDoubleArray* `[Double]'&, fromIntegral `Word', fromIntegral `Word', withObjectArrayRaw* `[Quote]', withObject* `DayCounter', preErrorCheck- `String' errorCheck*-} -> `CapFloorTermVolSurface'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
