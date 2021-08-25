{-# LANGUAGE MultiParamTypeClasses, FlexibleContexts, TypeOperators #-}
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

import QuantLib.Type
import QuantLib.Internal
{#import QuantLib.TermStructure#}
{#import QuantLib.TermStructure.Yield#}(YieldTermStructure)
import QuantLib.Internal.TermStructure(withYieldTermStructure)
{#import QuantLib.Quote#}(Quote)
import QuantLib.Internal.Quote
{#import QuantLib.Time.Calendar#}(Calendar, BusinessDayConvention)
import QuantLib.Internal.Calendar
{#import QuantLib.Time.Schedule#}(TimeUnit, DayCounter)
import QuantLib.Internal.Schedule
import QuantLib.Internal.Enum

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

{#pointer *QlBlackVarianceCurve as BlackVarianceCurve foreign finalizer qlFreeBlackVarianceCurve newtype#}
instance ForeignObject BlackVarianceCurve where
  withObject = withBlackVarianceCurve
  constructor = BlackVarianceCurve
  finalizer=qlFreeBlackVarianceCurve

{#pointer *QlBlackVolTermStructure as BlackVolTermStructure foreign finalizer qlFreeBlackVolTermStructure newtype#}
instance ForeignObject BlackVolTermStructure where
  withObject = withBlackVolTermStructure
  constructor = BlackVolTermStructure
  finalizer=qlFreeBlackVolTermStructure
{#pointer *QlCallableBondVolatilityStructure as CallableBondVolatilityStructure foreign finalizer qlFreeCallableBondVolatilityStructure newtype#}
instance ForeignObject CallableBondVolatilityStructure where
  withObject = withCallableBondVolatilityStructure
  constructor = CallableBondVolatilityStructure
  finalizer=qlFreeCallableBondVolatilityStructure

{#pointer *QlCapFloorTermVolSurface as CapFloorTermVolSurface foreign finalizer qlFreeCapFloorTermVolSurface newtype#}
instance ForeignObject CapFloorTermVolSurface where
  withObject = withCapFloorTermVolSurface
  constructor = CapFloorTermVolSurface
  finalizer=qlFreeCapFloorTermVolSurface

{#pointer *QlLocalVolTermStructure as LocalVolTermStructure foreign finalizer qlFreeLocalVolTermStructure newtype#}
instance ForeignObject LocalVolTermStructure where
  withObject = withLocalVolTermStructure
  constructor = LocalVolTermStructure
  finalizer=qlFreeLocalVolTermStructure

{#pointer *QlOptionletVolatilityStructure as OptionletVolatilityStructure foreign finalizer qlFreeOptionletVolatilityStructure newtype#}
instance ForeignObject OptionletVolatilityStructure where
  withObject = withOptionletVolatilityStructure
  constructor = OptionletVolatilityStructure
  finalizer=qlFreeOptionletVolatilityStructure

{#pointer *QlSmileSection as SmileSection foreign finalizer qlFreeSmileSection newtype#}
instance ForeignObject SmileSection where
  withObject = withSmileSection
  constructor = SmileSection
  finalizer=qlFreeSmileSection

{#pointer *QlSwaptionVolatilityStructure as SwaptionVolatilityStructure foreign finalizer qlFreeSwaptionVolatilityStructure newtype#}
instance ForeignObject SwaptionVolatilityStructure where
  withObject = withSwaptionVolatilityStructure
  constructor = SwaptionVolatilityStructure
  finalizer=qlFreeSwaptionVolatilityStructure

{#pointer *QlVolatilityTermStructure as VolatilityTermStructure foreign finalizer qlFreeVolatilityTermStructure newtype#}
instance ForeignObject VolatilityTermStructure where
  withObject = withVolatilityTermStructure
  constructor = VolatilityTermStructure
  finalizer=qlFreeVolatilityTermStructure

{#enum BlackVarianceSurfaceExtrapolation {} deriving(Show, Eq)#}

{#enum ExtendedBlackVarianceSurfaceExtrapolation {} deriving(Show, Eq)#}

asVolatilityTermStructure :: (a `Derives` VolatilityTermStructure) => a -> IO VolatilityTermStructure
asVolatilityTermStructure = cast

{#fun qlOptionletVolatilityStructureAsVolatilityTermStructure {`OptionletVolatilityStructure'} -> `VolatilityTermStructure'#}
instance OptionletVolatilityStructure `Derives` VolatilityTermStructure where cast = qlOptionletVolatilityStructureAsVolatilityTermStructure

{#fun qlVolatilityTermStructureAsTermStructure {`VolatilityTermStructure'} -> `TermStructure' peekObject*#}
instance VolatilityTermStructure `Derives` TermStructure where cast = qlVolatilityTermStructureAsTermStructure

{#fun qlBlackVolTermStructureAsVolatilityTermStructure {`BlackVolTermStructure'} -> `VolatilityTermStructure'#}
instance BlackVolTermStructure `Derives` VolatilityTermStructure where cast = qlBlackVolTermStructureAsVolatilityTermStructure

{#fun qlSwaptionVolatilityStructureAsVolatilityTermStructure {`SwaptionVolatilityStructure'} -> `VolatilityTermStructure'#}
instance SwaptionVolatilityStructure `Derives` VolatilityTermStructure where cast = qlSwaptionVolatilityStructureAsVolatilityTermStructure

{#fun qlCapFloorTermVolSurfaceAsVolatilityTermStructure {`CapFloorTermVolSurface'} -> `VolatilityTermStructure'#}
instance CapFloorTermVolSurface `Derives` VolatilityTermStructure where cast = qlCapFloorTermVolSurfaceAsVolatilityTermStructure

{#fun qlLocalVolTermStructureAsVolatilityTermStructure {`LocalVolTermStructure'} -> `VolatilityTermStructure'#}
instance LocalVolTermStructure `Derives` VolatilityTermStructure where cast = qlLocalVolTermStructureAsVolatilityTermStructure

{#fun qlBlackVarianceCurveAsBlackVolTermStructure {`BlackVarianceCurve'} -> `BlackVolTermStructure'#}

{#fun qlCallableBondVolatilityStructureAsTermStructure {`CallableBondVolatilityStructure'} -> `TermStructure' peekObject*#}
instance CallableBondVolatilityStructure `Derives` TermStructure where cast = qlCallableBondVolatilityStructureAsTermStructure;

instance BlackVarianceCurve `Derives` BlackVolTermStructure where cast = qlBlackVarianceCurveAsBlackVolTermStructure

asBlackVolTermStructure :: (a `Derives` BlackVolTermStructure) => a -> IO BlackVolTermStructure
asBlackVolTermStructure = cast

{#fun qlLocalVolSurface as localVolSurface {`BlackVolTermStructure', `YieldTermStructure', `YieldTermStructure', `Quote', preErrorCheck- `String' errorCheck*-} -> `LocalVolTermStructure'#}

-- |Constant caplet volatility, no time-strike dependence
-- floating reference date, floating market data
{#fun qlConstantOptionletVol1 as constantOptionletVolatility' {fromIntegral `Word', `Calendar', `BusinessDayConvention', `Quote', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `OptionletVolatilityStructure'#}

-- |fixed reference date, floating market data
{#fun qlConstantOptionletVolatility as constantOptionletVolatility {withDay* `Day', `Calendar', `BusinessDayConvention', `Quote', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `OptionletVolatilityStructure'#}

{#fun qlBlackConstantVol1 as blackConstantVol' {fromIntegral `Word', `Calendar', `Quote', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `BlackVolTermStructure'#}

{#fun qlBlackConstantVol as blackConstantVol {withDay* `Day', `Calendar', `Quote', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `BlackVolTermStructure'#}

-- |fixed reference date, floating market data
{#fun qlConstantSwaptionVolatility1 as constantSwaptionVolatility' {withDay* `Day', `Calendar', `BusinessDayConvention', `Quote', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `SwaptionVolatilityStructure'#}

-- |floating reference date, floating market data
{#fun qlConstantSwaptionVolatility as constantSwaptionVolatility {fromIntegral `Word', `Calendar', `BusinessDayConvention', `Quote', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `SwaptionVolatilityStructure'#}

-- |returns the Black variance for a given option date and swap tenor
{#fun qlSwaptionVolatilityStructureBlackVariance1 as blackVarianceForPeriod' {`SwaptionVolatilityStructure', withDay* `Day', fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the Black variance for a given option time and swap tenor
{#fun qlSwaptionVolatilityStructureBlackVariance2 as blackVarianceForPeriod {`SwaptionVolatilityStructure', `Double', fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the Black variance for a given option tenor and swap length
{#fun qlSwaptionVolatilityStructureBlackVariance3 as blackVarianceForTenor {`SwaptionVolatilityStructure', fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the Black variance for a given option date and swap length
{#fun qlSwaptionVolatilityStructureBlackVariance4 as blackVariance' {`SwaptionVolatilityStructure', withDay* `Day', `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the Black variance for a given option time and swap length
{#fun qlSwaptionVolatilityStructureBlackVariance5 as blackVariance {`SwaptionVolatilityStructure', `Double', `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the Black variance for a given option tenor and swap tenor
{#fun qlSwaptionVolatilityStructureBlackVariance as blackVarianceForPeriods {`SwaptionVolatilityStructure', fromEnumQuantity `(Word, TimeUnit)'&, fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |the largest swapLength for which the term structure can return vols
{#fun qlSwaptionVolatilityStructureMaxSwapLength as maxSwapLength {`SwaptionVolatilityStructure', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |the largest length for which the term structure can return vols
{#fun qlSwaptionVolatilityStructureMaxSwapTenor as maxSwapTenor {`SwaptionVolatilityStructure', preEnum- `TimeUnit' peekEnum*, preErrorCheck- `String' errorCheck*-} -> `Int'#}

-- |returns the smile for a given option date and swap tenor
{#fun qlSwaptionVolatilityStructureSmileSection1 as smileSectionForPeriod' {`SwaptionVolatilityStructure', withDay* `Day', fromEnumQuantity `(Word, TimeUnit)'&, `Bool', preErrorCheck- `String' errorCheck*-} -> `SmileSection'#}

-- |returns the smile for a given option time and swap tenor
{#fun qlSwaptionVolatilityStructureSmileSection2 as smileSectionForPeriod {`SwaptionVolatilityStructure', `Double', fromEnumQuantity `(Word, TimeUnit)'&, `Bool', preErrorCheck- `String' errorCheck*-} -> `SmileSection'#}

-- |returns the smile for a given option tenor and swap length
{#fun qlSwaptionVolatilityStructureSmileSection3 as smileSectionForTenor {`SwaptionVolatilityStructure', fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `SmileSection'#}

-- |returns the smile for a given option date and swap length
{#fun qlSwaptionVolatilityStructureSmileSection4 as smileSection' {`SwaptionVolatilityStructure', withDay* `Day', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `SmileSection'#}

-- |returns the smile for a given option time and swap length
{#fun qlSwaptionVolatilityStructureSmileSection5 as smileSection {`SwaptionVolatilityStructure', `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `SmileSection'#}

-- |returns the smile for a given option tenor and swap tenor
{#fun qlSwaptionVolatilityStructureSmileSection as smileSectionForPeriods {`SwaptionVolatilityStructure', fromEnumQuantity `(Word, TimeUnit)'&, fromEnumQuantity `(Word, TimeUnit)'&, `Bool', preErrorCheck- `String' errorCheck*-} -> `SmileSection'#}

-- |implements the conversion between swap dates and swap (time) length
{#fun qlSwaptionVolatilityStructureSwapLength1 as swapLength' {`SwaptionVolatilityStructure', withDay* `Day', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |implements the conversion between swap tenor and swap (time) length
{#fun qlSwaptionVolatilityStructureSwapLength as swapLength {`SwaptionVolatilityStructure', fromEnumQuantity `(Word, TimeUnit)'&, preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the volatility for a given option date and swap tenor
{#fun qlSwaptionVolatilityStructureVolatility1 as volatilityForPeriod' {`SwaptionVolatilityStructure', withDay* `Day', fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the volatility for a given option time and swap tenor
{#fun qlSwaptionVolatilityStructureVolatility2 as volatilityForPeriod {`SwaptionVolatilityStructure', `Double', fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the volatility for a given option tenor and swap length
{#fun qlSwaptionVolatilityStructureVolatility3 as volatilityForTenor {`SwaptionVolatilityStructure', fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the volatility for a given option date and swap length
{#fun qlSwaptionVolatilityStructureVolatility4 as volatilityForTenor' {`SwaptionVolatilityStructure', withDay* `Day', `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the volatility for a given option time and swap length
{#fun qlSwaptionVolatilityStructureVolatility5 as volatility {`SwaptionVolatilityStructure', `Double', `Double', `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

-- |returns the volatility for a given option tenor and swap tenor
{#fun qlSwaptionVolatilityStructureVolatility as volatilityForPeriods {`SwaptionVolatilityStructure', fromEnumQuantity `(Word, TimeUnit)'&, fromEnumQuantity `(Word, TimeUnit)'&, `Double', `Bool', preErrorCheck- `String' errorCheck*-} -> `Double'#}

{#fun qlCallableBondConstantVolatility1 as callableBondConstantVolatility' {fromIntegral `Word', `Calendar', `Quote', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `CallableBondVolatilityStructure'#}

{#fun qlCallableBondConstantVolatility as callableBondConstantVolatility {withDay* `Day', `Quote', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `CallableBondVolatilityStructure'#}

-- |fixed reference date, floating market data
{#fun qlConstantCapFloorTermVolatility1 as constantCapFloorTermVolatility' {withDay* `Day', `Calendar', `BusinessDayConvention', `Quote', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `VolatilityTermStructure'#}

-- |floating reference date, floating market data
{#fun qlConstantCapFloorTermVolatility as constantCapFloorTermVolatility {fromIntegral `Word', `Calendar', `BusinessDayConvention', `Quote', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `VolatilityTermStructure'#}

{#fun qlSpreadedSwaptionVolatility as spreadedSwaptionVolatility {`SwaptionVolatilityStructure' , `Quote' , preErrorCheck- `String' errorCheck*-} -> `SwaptionVolatilityStructure'#}

{#fun qlLocalConstantVol1 as localConstantVol' {fromIntegral `Word', `Calendar', `Quote', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `LocalVolTermStructure'#}

{#fun qlLocalConstantVol as localConstantVol {withDay* `Day', `Quote', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `LocalVolTermStructure'#}

{#fun qlLocalVolCurve as localVolCurve {`BlackVarianceCurve', preErrorCheck- `String' errorCheck*-} -> `LocalVolTermStructure'#}

{#fun qlImpliedVolTermStructure as impliedVolTermStructure {`BlackVolTermStructure', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `BlackVolTermStructure'#}

-- |fixed reference date, floating market data
capFloorTermVolCurve' :: Day -> Calendar -> BusinessDayConvention -> [(Word, TimeUnit, Quote)] -> DayCounter -> IO VolatilityTermStructure
capFloorTermVolCurve' d c bd ntq = qlCapFloorTermVolCurve1 d c bd n t q where (n, t, q) = unzip3 ntq

{#fun qlCapFloorTermVolCurve1 {withDay* `Day', `Calendar', `BusinessDayConvention', withIntArray* `[Word]'&, withEnumArray* `[TimeUnit]'&, withObjectArray* `[Quote]'&, `DayCounter', preErrorCheck- `String' errorCheck*-} -> `VolatilityTermStructure'#}

-- |floating reference date, floating market data
capFloorTermVolCurve :: Word -> Calendar -> BusinessDayConvention -> [(Word, TimeUnit, Quote)] -> DayCounter -> IO VolatilityTermStructure
capFloorTermVolCurve d c bd ntq = qlCapFloorTermVolCurve d c bd n t q where (n, t, q) = unzip3 ntq

{#fun qlCapFloorTermVolCurve {fromIntegral `Word', `Calendar', `BusinessDayConvention', withIntArray* `[Word]'&, withEnumArray* `[TimeUnit]'&, withObjectArray* `[Quote]'&, `DayCounter', preErrorCheck- `String' errorCheck*-} -> `VolatilityTermStructure'#}

blackVarianceCurve :: Day -> [(Day, Double)] -> DayCounter -> Bool -> Maybe Interpolation -> IO BlackVarianceCurve
blackVarianceCurve d dq dc f i = uncurry' (qlBlackVarianceCurve d dd q dc f) (qlInterpolation' i)
  where (dd, q) = unzip dq

{#fun qlBlackVarianceCurve {withDay* `Day' , withDayArray* `[Day]'& , withDoubleArray* `[Double]'& , `DayCounter' , `Bool' , `Int', `Int', `Int' , preErrorCheck- `String' errorCheck*-} -> `BlackVarianceCurve'#}

blackVarianceSurface :: Day -> Calendar -> [Day] -> [Double] -> Matrix Double -> DayCounter -> BlackVarianceSurfaceExtrapolation -> BlackVarianceSurfaceExtrapolation -> IO BlackVolTermStructure
blackVarianceSurface d c ds s (Matrix mr mc md) = qlBlackVarianceSurface d c ds s mr mc md

{#fun qlBlackVarianceSurface {withDay* `Day', `Calendar', withDayArray* `[Day]'&, withDoubleArray* `[Double]'&, fromIntegral `Word', fromIntegral `Word', withDoubleArrayRaw* `[Double]', `DayCounter', `BlackVarianceSurfaceExtrapolation', `BlackVarianceSurfaceExtrapolation', preErrorCheck- `String' errorCheck*-} -> `BlackVolTermStructure'#}

-- |floating reference date, floating market data
capFloorTermVolSurface :: Word -> Calendar -> BusinessDayConvention -> [(Word, TimeUnit)] -> [Double] -> Matrix Quote -> DayCounter -> IO CapFloorTermVolSurface
capFloorTermVolSurface d c bd t s (Matrix mr mc md) = qlCapFloorTermVolSurface d c bd pl pu s mr mc md where (pl, pu) = unzip t

{#fun qlCapFloorTermVolSurface {fromIntegral `Word', `Calendar', `BusinessDayConvention', withIntArray* `[Word]'&, withEnumArray* `[TimeUnit]'&, withDoubleArray* `[Double]'&, fromIntegral `Word', fromIntegral `Word', withObjectArrayRaw* `[Quote]', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `CapFloorTermVolSurface'#}

-- |fixed reference date, floating market data
capFloorTermVolSurface' :: Day -> Calendar -> BusinessDayConvention -> [(Word, TimeUnit)] -> [Double] -> Matrix Quote -> DayCounter -> IO CapFloorTermVolSurface
capFloorTermVolSurface' d c bd t s (Matrix mr mc md) = qlCapFloorTermVolSurface1 d c bd pl pu s mr mc md where (pl, pu) = unzip t

{#fun qlCapFloorTermVolSurface1 {withDay* `Day', `Calendar', `BusinessDayConvention', withIntArray* `[Word]'&, withEnumArray* `[TimeUnit]'&, withDoubleArray* `[Double]'&, fromIntegral `Word', fromIntegral `Word', withObjectArrayRaw* `[Quote]', `DayCounter', preErrorCheck- `String' errorCheck*-} -> `CapFloorTermVolSurface'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
