{-# LANGUAGE TemplateHaskell #-}
module QuantLib.TermStructure.Volatility
  (
    BlackVarianceSurfaceExtrapolation(..)
  , ExtendedBlackVarianceSurfaceExtrapolation(..)
  , FixedLocalVolSurfaceExtrapolation(..)
  , AndreasenHugeInterpolationType(..)
  , AndreasenHugeCalibrationType(..)
  , ZabrEvaluation(..)

  , BlackVarianceCurve
  , BlackVolatilitySurfaceDelta
  , SmileInterpolationMethod(..)
  , BlackVolTimeExtrapolationType(..)
  , BlackVolatilitySurfaceDeltaOpts(..)
  , defaultBlackVolatilitySurfaceDeltaOpts
  , BlackVolTermStructure
  , GenBlackVolTermStructure
  , RelinkableBlackVolTermStructure
  , CallableBondVolatilityStructure
  , CapFloorTermVolatilityStructure
  , GenCapFloorTermVolatilityStructure
  , CapFloorTermVolCurve
  , CapFloorTermVolSurface
  , LocalVolTermStructure
  , GenLocalVolTermStructure
  , GridModelLocalVolSurface
  , AndreasenHugeVolatilityInterpl
  , OptionletVolatilityStructure
  , GenOptionletVolatilityStructure
  , RelinkableOptionletVolatilityStructure
  , SmileSection
  , SabrInterpolatedSmileSection
  , SviInterpolatedSmileSection
  , NoArbSabrInterpolatedSmileSection
  , SwaptionVolatilityStructure
  , RelinkableSwaptionVolatilityStructure
  , VolatilityTermStructure
  , GenVolatilityTermStructure
  , BlackAtmVolCurve
  , GenBlackAtmVolCurve
  , BlackVolSurface
  , GenBlackVolSurface
  , AbcdAtmVolCurve
  , SabrVolSurface
  , OptionletStripper2

  , asVolatilityTermStructure
  , asBlackVolTermStructure

  , localVolSurface
  , constantOptionletVolatility
  , constantOptionletVolatility'
  , capletVarianceCurve
  , optionletStripper1
  , optionletStripper2
  , optionletStripper2AsOptionletVolatilityStructure
  , optionletStripper2AtmCapFloorStrikes
  , optionletStripper2AtmCapFloorPrices
  , optionletStripper2SpreadsVol

  , impliedVolTermStructure
  , blackConstantVol'
  , blackConstantVol
  , relinkableBlackVolTermStructure
  , linkBlackVolTo
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
  , sabrSmileSection
  , sabrSmileSection'
  , noArbSabrSmileSection
  , noArbSabrSmileSection'
  , smileSectionVolatility
  , smileSectionVariance
  , SabrInterpolatedSmileSectionOpts(..)
  , defaultSabrInterpolatedSmileSectionOpts
  , sabrInterpolatedSmileSection
  , sabrInterpolatedSmileSectionAsSmileSection
  , sabrInterpolatedSmileSectionAlpha
  , sabrInterpolatedSmileSectionBeta
  , sabrInterpolatedSmileSectionNu
  , sabrInterpolatedSmileSectionRho
  , sabrInterpolatedSmileSectionRmsError
  , sabrInterpolatedSmileSectionMaxError
  , sabrInterpolatedSmileSectionEndCriteria
  , sviInterpolatedSmileSection
  , sviInterpolatedSmileSectionAsSmileSection
  , sviInterpolatedSmileSectionA
  , sviInterpolatedSmileSectionB
  , sviInterpolatedSmileSectionSigma
  , sviInterpolatedSmileSectionRho
  , sviInterpolatedSmileSectionM
  , sviInterpolatedSmileSectionRmsError
  , sviInterpolatedSmileSectionMaxError
  , sviInterpolatedSmileSectionEndCriteria
  , noArbSabrInterpolatedSmileSection
  , noArbSabrInterpolatedSmileSectionAsSmileSection
  , noArbSabrInterpolatedSmileSectionAlpha
  , noArbSabrInterpolatedSmileSectionBeta
  , noArbSabrInterpolatedSmileSectionNu
  , noArbSabrInterpolatedSmileSectionRho
  , noArbSabrInterpolatedSmileSectionRmsError
  , noArbSabrInterpolatedSmileSectionMaxError
  , noArbSabrInterpolatedSmileSectionEndCriteria
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
  , capFloorVolatilityForPeriod
  , capFloorVolatilityForDate
  , capFloorVolatilityForTime
  , capFloorTermVolCurveOptionDates
  , capFloorTermVolCurveOptionTimes
  , capFloorTermVolSurfaceOptionDates
  , capFloorTermVolSurfaceOptionTimes
  , atmVolForPeriod
  , atmVolForDate
  , atmVolForTime
  , atmVarianceForPeriod
  , atmVarianceForDate
  , atmVarianceForTime
  , blackVolSurfaceSmileSectionForPeriod
  , blackVolSurfaceSmileSectionForDate
  , blackVolSurfaceSmileSectionForTime
  , abcdAtmVolCurve
  , abcdAtmVolCurveA
  , abcdAtmVolCurveB
  , abcdAtmVolCurveC
  , abcdAtmVolCurveD
  , abcdAtmVolCurveRmsError
  , abcdAtmVolCurveMaxError
  , abcdAtmVolCurveEndCriteria
  , abcdAtmVolCurveK
  , abcdAtmVolCurveKAtTime
  , abcdAtmVolCurveOptionTenors
  , abcdAtmVolCurveOptionTenorsInInterpolation
  , abcdAtmVolCurveOptionDates
  , abcdAtmVolCurveOptionTimes
  , sabrVolSurface
  , sabrVolSurfaceAtmCurve
  , sabrVolSurfaceVolatilitySpreadsForPeriod
  , sabrVolSurfaceVolatilitySpreadsForDate
  , sabrVolSurfaceIndex
  , sabrVolSurfaceOptionDateFromTenor
  , spreadedSwaptionVolatility
  , relinkableSwaptionVolatilityStructure
  , linkSwaptionVolTo
  , relinkableOptionletVolatilityStructure
  , linkOptionletVolTo
  , localConstantVol'
  , localConstantVol
  , localVolCurve
  , capFloorTermVolCurve
  , capFloorTermVolCurve'
  , blackVarianceCurve
  , capFloorTermVolSurface
  , capFloorTermVolSurface'
  , blackVarianceSurface
  , piecewiseBlackVarianceSurface
  , blackVolatilitySurfaceDelta
  , blackVolatilitySurfaceDeltaFull
  , blackVolSmile
  , blackVolSmile'
  , swaptionVolatilityMatrix'
  , SabrSwaptionVolatilityCube
  , NoArbSabrSwaptionVolatilityCube
  , InterpolatedSwaptionVolatilityCube
  , sabrSwaptionVolatilityCube
  , noArbSabrSwaptionVolatilityCube
  , interpolatedSwaptionVolatilityCube
  , sparseSabrParameters
  , denseSabrParameters
  , marketVolCube
  , volCubeAtmCalibrated
  , sabrSwaptionVolatilityCubeAtmStrike'
  , sabrSwaptionVolatilityCubeAtmStrike
  , noArbSabrSparseSabrParameters
  , noArbSabrDenseSabrParameters
  , noArbSabrMarketVolCube
  , noArbSabrVolCubeAtmCalibrated
  , noArbSabrSwaptionVolatilityCubeAtmStrike'
  , noArbSabrSwaptionVolatilityCubeAtmStrike
  , interpolatedSwaptionVolatilityCubeAtmStrike'
  , interpolatedSwaptionVolatilityCubeAtmStrike
  , swaptionVolatilityMatrix
  , noExceptLocalVolSurface
  , fixedLocalVolSurface
  , gridModelLocalVolSurface
  , gridModelLocalVolSurfaceAsCalibratedModel
  , hestonBlackVolSurface
  , andreasenHugeVolatilityInterpl
  , andreasenHugeVolatilityInterplCalibrationError
  , andreasenHugeVolatilityInterplFwd
  , andreasenHugeVolatilityInterplOptionPrice
  , andreasenHugeVolatilityInterplLocalVol
  , andreasenHugeVolatilityAdapter
  , andreasenHugeLocalVolAdapter
  , spreadedOptionletVol
  , localVol
  , smileSectionAtmLevel
  , smileSectionOptionPrice
  , smileSectionDigitalOptionPrice
  , smileSectionDensity
  , flatSmileSection
  , spreadedSmileSection
  , atmSmileSection
  , sviSmileSection
  , zabrSmileSection
  , zabrSmileSection'
  ) where
import QuantLib.Internal
{#import QuantLib.InterestRate#}(VolatilityType)
{#import QuantLib.Math#}(EndCriteriaType, ComplexLogFormula)
{#import QuantLib.Quote#}(DeltaType(..), AtmType(..))
import QuantLib.Internal.Type
import QuantLib.Internal.Common
import QuantLib.Internal.Syntax(deriveOptionsRecord)
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..))
import Data.List.NonEmpty(NonEmpty, toList)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *DayCounter foreign -> CDayCounter nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlIborIndex as IborIndex foreign -> CIborIndex' nocode#}
{#pointer *QlSmileSection as SmileSection foreign -> CSmileSection nocode#}
{#pointer *QlSabrInterpolatedSmileSection as SabrInterpolatedSmileSection foreign -> CSabrInterpolatedSmileSection nocode#}
{#pointer *QlSviInterpolatedSmileSection as SviInterpolatedSmileSection foreign -> CSviInterpolatedSmileSection nocode#}
{#pointer *QlNoArbSabrInterpolatedSmileSection as NoArbSabrInterpolatedSmileSection foreign -> CNoArbSabrInterpolatedSmileSection nocode#}

{#pointer *QlVolatilityTermStructure as VolatilityTermStructure foreign -> CVolatilityTermStructure' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlTermStructure as TermStructure foreign -> CTermStructure' nocode#}
{#pointer *QlOptionletVolatilityStructure as OptionletVolatilityStructure foreign -> COptionletVolatilityStructure' nocode#}
{#pointer *QlRelinkableOptionletVolatilityStructure as RelinkableOptionletVolatilityStructure foreign -> CRelinkableOptionletVolatilityStructure' nocode#}
{#pointer *QlLocalVolTermStructure as LocalVolTermStructure foreign -> CLocalVolTermStructure' nocode#}
{#pointer *QlGridModelLocalVolSurface as GridModelLocalVolSurface foreign -> CGridModelLocalVolSurface' nocode#}
{#pointer *QlAndreasenHugeVolatilityInterpl as AndreasenHugeVolatilityInterpl foreign -> CAndreasenHugeVolatilityInterpl nocode#}
{#pointer *QlCalibratedModel as CalibratedModel foreign -> CCalibratedModel' nocode#}
{#pointer *QlHestonModel as HestonModel foreign -> CHestonModel' nocode#}
{#pointer *QlVanillaOption as VanillaOption foreign -> CVanillaOption' nocode#}
{#pointer *QlOptimizationMethod as OptimizationMethod foreign -> COptimizationMethod nocode#}
{#pointer *QlEndCriteria as EndCriteria foreign -> CEndCriteria nocode#}
{#pointer *QlBlackVarianceCurve as BlackVarianceCurve foreign -> CBlackVarianceCurve' nocode#}
{#pointer *QlBlackVolatilitySurfaceDelta as BlackVolatilitySurfaceDelta foreign -> CBlackVolatilitySurfaceDelta' nocode#}
{#pointer *QlBlackVolTermStructure as BlackVolTermStructure foreign -> CBlackVolTermStructure' nocode#}
{#pointer *QlRelinkableBlackVolTermStructure as RelinkableBlackVolTermStructure foreign -> CRelinkableBlackVolTermStructure' nocode#}
{#pointer *QlCallableBondVolatilityStructure as CallableBondVolatilityStructure foreign -> CCallableBondVolatilityStructure' nocode#}
{#pointer *QlCapFloorTermVolatilityStructure as CapFloorTermVolatilityStructure foreign -> CCapFloorTermVolatilityStructure' nocode#}
{#pointer *QlCapFloorTermVolCurve as CapFloorTermVolCurve foreign -> CCapFloorTermVolCurve' nocode#}
{#pointer *QlCapFloorTermVolSurface as CapFloorTermVolSurface foreign -> CCapFloorTermVolSurface' nocode#}
{#pointer *QlSwaptionVolatilityStructure as SwaptionVolatilityStructure foreign -> CSwaptionVolatilityStructure' nocode#}
{#pointer *QlRelinkableSwaptionVolatilityStructure as RelinkableSwaptionVolatilityStructure foreign -> CRelinkableSwaptionVolatilityStructure' nocode#}
{#pointer *QlSabrSwaptionVolatilityCube as SabrSwaptionVolatilityCube foreign -> CSabrSwaptionVolatilityCube' nocode#}
{#pointer *QlNoArbSabrSwaptionVolatilityCube as NoArbSabrSwaptionVolatilityCube foreign -> CNoArbSabrSwaptionVolatilityCube' nocode#}
{#pointer *QlInterpolatedSwaptionVolatilityCube as InterpolatedSwaptionVolatilityCube foreign -> CInterpolatedSwaptionVolatilityCube' nocode#}
{#pointer *QlSwapIndex as SwapIndex foreign -> CSwapIndex' nocode#}
{#pointer *QlBlackAtmVolCurve as BlackAtmVolCurve foreign -> CBlackAtmVolCurve' nocode#}
{#pointer *QlBlackVolSurface as BlackVolSurface foreign -> CBlackVolSurface' nocode#}
{#pointer *QlAbcdAtmVolCurve as AbcdAtmVolCurve foreign -> CAbcdAtmVolCurve' nocode#}
{#pointer *QlSabrVolSurface as SabrVolSurface foreign -> CSabrVolSurface' nocode#}
{#pointer *QlInterestRateIndex as InterestRateIndex foreign -> CInterestRateIndex' nocode#}
{#pointer *QlOptionletStripper2 as OptionletStripper2 foreign -> COptionletStripper2 nocode#}

{#enum BlackVarianceSurfaceExtrapolation{} deriving(Show, Eq, Read)#}
{#enum ExtendedBlackVarianceSurfaceExtrapolation{} deriving(Show, Eq, Read)#}

-- |'BlackVolatilitySurfaceDelta::SmileInterpolationMethod', local to that class -- not shared
-- with any other binding, so declared here rather than in 'QuantLib.Internal.Common'.
{#enum SmileInterpolationMethod{} deriving(Show, Eq, Read)#}

-- |'BlackVolTimeExtrapolation::Type', consumed only by 'blackVolatilitySurfaceDelta' today --
-- same local-declaration treatment as 'SmileInterpolationMethod'. Named
-- @BlackVolTimeExtrapolationType@ (rather than reusing the bare @Type@ c2hs would otherwise
-- emit) to avoid a top-level name clash.
{#enum BlackVolTimeExtrapolationType{} deriving(Show, Eq, Read)#}

-- |'FixedLocalVolSurface::Extrapolation', local to that class -- not shared with any other
-- binding, same local-declaration treatment as 'SmileInterpolationMethod'.
{#enum FixedLocalVolSurfaceExtrapolation{} deriving(Show, Eq, Read)#}
{#enum AndreasenHugeInterpolationType{} add prefix="AndreasenHugeInterpolation" deriving(Show, Eq, Read)#}

-- |'ZabrSmileSection'\'s evaluation-tag axis (Andreasen\/Huge 2011): 'ZabrShortMaturityLognormal'\/
-- 'ZabrShortMaturityNormal' are closed-form short-maturity expansions (fast, less accurate away
-- from short maturities); 'ZabrLocalVolatility' and 'ZabrFullFd' solve a finite-difference PDE
-- (slower, more accurate). Local to this binding -- not shared with any other cross-cutting enum.
{#enum ZabrEvaluation{} deriving(Show, Eq, Read)#}
{#enum AndreasenHugeCalibrationType{} add prefix="AndreasenHugeCalibration" deriving(Show, Eq, Read)#}

-- SabrInterpolatedSmileSectionOpts bundles every trailing param
-- sabrInterpolatedSmileSection_ hardcodes, pre-populated with upstream's own defaults,
-- overridden through record-update syntax -- see OISRateHelperOpts (QuantLib.TermStructure.Yield)
-- for the worked example this follows. dayCounter is Maybe here (unlike the raw binding's
-- plain DayCounter) since a real DayCounter is only obtainable in IO (`dayCounter
-- Actual365FixedStandard`) and can't live in a pure default record value;
-- sabrInterpolatedSmileSection substitutes a fresh Actual365Fixed for Nothing, same as
-- OISRateHelperOpts does for its Calendar fields. This splice must stay textually before
-- every {#fun#}-generated binding in this file -- see the comment above OISRateHelperOpts
-- for why (c2hs always appends its raw foreign-import stubs at the physical end of the
-- generated module regardless of where a {#fun#} hook appears in the source).
$(deriveOptionsRecord "SabrInterpolatedSmileSectionOpts" []
  [ ("sabrIsAlphaFixed", [t|Bool|], [|False|])
  , ("sabrIsBetaFixed", [t|Bool|], [|False|])
  , ("sabrIsNuFixed", [t|Bool|], [|False|])
  , ("sabrIsRhoFixed", [t|Bool|], [|False|])
  , ("sabrVegaWeighted", [t|Bool|], [|True|])
  , ("sabrEndCriteria", [t|Maybe EndCriteria|], [|Nothing|])
  , ("sabrOptimizationMethod", [t|Maybe OptimizationMethod|], [|Nothing|])
  , ("sabrDayCounter", [t|Maybe DayCounter|], [|Nothing|])
  , ("sabrShift", [t|Double|], [|0.0|])
  ])

-- BlackVolatilitySurfaceDeltaOpts bundles every trailing defaulted param of
-- 'BlackVolatilitySurfaceDelta''s one constructor (deltaType through longTermAtmDeltaType),
-- pre-populated with upstream's own defaults via defaultBlackVolatilitySurfaceDeltaOpts,
-- overridden through record-update syntax at the call site -- see OISRateHelperOpts
-- (QuantLib.TermStructure.Yield) for the worked example this follows. Same
-- splice-placement constraint as SabrInterpolatedSmileSectionOpts above.
$(deriveOptionsRecord "BlackVolatilitySurfaceDeltaOpts" []
  [ ("bvsdDeltaType", [t|DeltaType|], [|Spot|])
  , ("bvsdAtmType", [t|AtmType|], [|AtmDeltaNeutral|])
  , ("bvsdAtmDeltaType", [t|Maybe DeltaType|], [|Nothing|])
  , ("bvsdInterpolationMethod", [t|SmileInterpolationMethod|], [|SmileLinear|])
  , ("bvsdFlatStrikeExtrapolation", [t|Bool|], [|False|])
  , ("bvsdTimeExtrapolationType", [t|BlackVolTimeExtrapolationType|], [|FlatVolatility|])
  , ("bvsdSwitchTenor", [t|(Int, TimeUnit)|], [|(0, Days)|])
  , ("bvsdLongTermDeltaType", [t|DeltaType|], [|Fwd|])
  , ("bvsdLongTermAtmType", [t|AtmType|], [|AtmDeltaNeutral|])
  , ("bvsdLongTermAtmDeltaType", [t|Maybe DeltaType|], [|Nothing|])
  ])

-- |A local vol surface derived from a Black vol surface via Dupire's formula (Gatheral's
-- implementation).
{#fun qlLocalVolSurface as localVolSurface{withBlackVolTermStructure*`GenBlackVolTermStructure bv'
  ,withYieldTermStructure*`GenYieldTermStructure y1' -- ^riskFreeTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^dividendTS
  ,withQuote*`GenQuote q' -- ^underlying
  ,preErrorCheck-`String'errorCheck*-}->`LocalVolTermStructure'peekLocalVolTermStructure*#}

-- |as 'localVolSurface', but a local vol calculation that would otherwise throw returns
-- @illegalLocalVolOverwrite@ instead
{#fun qlNoExceptLocalVolSurface as noExceptLocalVolSurface{withBlackVolTermStructure*`GenBlackVolTermStructure bv'
  ,withYieldTermStructure*`GenYieldTermStructure y1' -- ^riskFreeTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^dividendTS
  ,withQuote*`GenQuote q' -- ^underlying
  ,`Double' -- ^illegalLocalVolOverwrite
  ,preErrorCheck-`String'errorCheck*-}->`LocalVolTermStructure'peekLocalVolTermStructure*#}

-- |a local vol surface fed directly from a matrix of local vols (rather than derived from a
-- Black vol surface, as 'localVolSurface' is) -- one flat strike grid shared across all dates,
-- same shape as 'blackVarianceSurface'.
fixedLocalVolSurface :: Day -> [Day] -- ^dates
  -> [Double] -- ^strikes
  -> RealMatrix -- ^localVolMatrix
  -> DayCounter
  -> FixedLocalVolSurfaceExtrapolation -- ^lowerExtrapolation
  -> FixedLocalVolSurfaceExtrapolation -- ^upperExtrapolation
  -> IO LocalVolTermStructure
fixedLocalVolSurface d ds s (RealMatrix mr mc md) = qlFixedLocalVolSurface d ds s mr mc md
{#fun qlFixedLocalVolSurface{withDay*`Day',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,fromIntegral`Word',fromIntegral`Word',withRealVectorRaw*`RealVector',withDayCounter*`DayCounter',`FixedLocalVolSurfaceExtrapolation',`FixedLocalVolSurfaceExtrapolation',preErrorCheck-`String'errorCheck*-}->`LocalVolTermStructure'peekLocalVolTermStructure*#}

-- |A local-volatility surface whose node values are model parameters. Each date is paired with
-- its non-empty strike row, so this genuinely ragged grid does not masquerade as a rectangular
-- 'Matrix'. Use 'gridModelLocalVolSurfaceAsCalibratedModel' to access QuantLib's generic
-- calibrated-model operations.
gridModelLocalVolSurface :: Day -> NonEmpty (Day, NonEmpty Double) -> DayCounter
  -> FixedLocalVolSurfaceExtrapolation -> FixedLocalVolSurfaceExtrapolation
  -> IO GridModelLocalVolSurface
gridModelLocalVolSurface d nodes = qlGridModelLocalVolSurface d dates rowSizes values
  where
    (dates, rows) = unzip (toList nodes)
    rowLists = map toList rows
    rowSizes = map (fromIntegral . length) rowLists
    values = concat rowLists
{#fun qlGridModelLocalVolSurface{withDay*`Day',withDayArray*`[Day]'&,withIntArray*`[Word]'&,withDoubleArrayRaw*`[Double]',withDayCounter*`DayCounter',`FixedLocalVolSurfaceExtrapolation',`FixedLocalVolSurfaceExtrapolation',preErrorCheck-`String'errorCheck*-}->`GridModelLocalVolSurface'peekGridModelLocalVolSurface*#}

-- |View a grid local-vol surface through its secondary 'CalibratedModel' interface. This is a
-- safe C++ multiple-inheritance upcast, materialized as an independently owned shared pointer.
{#fun qlGridModelLocalVolSurfaceAsCalibratedModel as gridModelLocalVolSurfaceAsCalibratedModel{withGridModelLocalVolSurface*`GridModelLocalVolSurface' -- ^surface
  ,preErrorCheck-`String'errorCheck*-}->`CalibratedModel'peekCalibratedModel*#}

-- |A Black implied-volatility surface computed from a Heston model. The integration argument is
-- the order of QuantLib's Gauss-Laguerre quadrature; the supplied complex-log formula controls
-- the characteristic-function representation.
{#fun qlHestonBlackVolSurface as hestonBlackVolSurface{withHestonModel*`GenHestonModel hm' -- ^model
  ,`ComplexLogFormula' -- ^complexLogFormula
  ,fromIntegral`Word' -- ^integrationOrder
  ,preErrorCheck-`String'errorCheck*-}->`BlackVolTermStructure'peekBlackVolTermStructure*#}

-- |Interpolation choice for Andreasen-Huge local-volatility calibration.
-- |Calibration choice for Andreasen-Huge local-volatility calibration.
andreasenHugeVolatilityInterpl :: NonEmpty (VanillaOption, GenQuote q) -> GenQuote q
  -> GenYieldTermStructure y1 -> GenYieldTermStructure y2
  -> AndreasenHugeInterpolationType -> AndreasenHugeCalibrationType -> Word
  -> Maybe Double -> Maybe Double -> OptimizationMethod -> EndCriteria
  -> IO AndreasenHugeVolatilityInterpl
andreasenHugeVolatilityInterpl xs spot r q = qlAndreasenHugeVolatilityInterpl os qs spot r q
  where (os, qs) = unzip (toList xs)
{#fun qlAndreasenHugeVolatilityInterpl{withVanillaOptionArray*`[VanillaOption]'&,withQuoteArrayRaw*`[GenQuote q1]'
  ,withQuote*`GenQuote q2',withYieldTermStructure*`GenYieldTermStructure y1',withYieldTermStructure*`GenYieldTermStructure y2'
  ,`AndreasenHugeInterpolationType',`AndreasenHugeCalibrationType',fromIntegral`Word',fromMaybeDouble`Maybe Double',fromMaybeDouble`Maybe Double'
  ,withOptimizationMethod*`OptimizationMethod',withEndCriteria*`EndCriteria',preErrorCheck-`String'errorCheck*-}->`AndreasenHugeVolatilityInterpl'peekAndreasenHugeVolatilityInterpl*#}

-- |Minimum, maximum, and average calibration errors, expressed in volatility units.
andreasenHugeVolatilityInterplCalibrationError :: AndreasenHugeVolatilityInterpl -> IO (Double, Double, Double)
andreasenHugeVolatilityInterplCalibrationError x = do
  [mn, mx, av] <- qlAndreasenHugeVolatilityInterplCalibrationError x
  pure (mn, mx, av)
{#fun qlAndreasenHugeVolatilityInterplCalibrationError{withAndreasenHugeVolatilityInterpl*`AndreasenHugeVolatilityInterpl',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Forward level implied by an Andreasen-Huge calibration at time @t@.
{#fun qlAndreasenHugeVolatilityInterplFwd as andreasenHugeVolatilityInterplFwd{withAndreasenHugeVolatilityInterpl*`AndreasenHugeVolatilityInterpl' -- ^interpolation
  ,`Double' -- ^t
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Calibrated option price at time, strike, and put/call type.
{#fun qlAndreasenHugeVolatilityInterplOptionPrice as andreasenHugeVolatilityInterplOptionPrice{withAndreasenHugeVolatilityInterpl*`AndreasenHugeVolatilityInterpl' -- ^interpolation
  ,`Double' -- ^t
  ,`Double' -- ^strike
  ,fromEnumC`OptionType' -- ^optionType
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |Calibrated local volatility at time and strike.
{#fun qlAndreasenHugeVolatilityInterplLocalVol as andreasenHugeVolatilityInterplLocalVol{withAndreasenHugeVolatilityInterpl*`AndreasenHugeVolatilityInterpl' -- ^interpolation
  ,`Double' -- ^t
  ,`Double' -- ^strike
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Adapts an Andreasen-Huge interpolation to QuantLib's Black-volatility term-structure interface.
{#fun qlAndreasenHugeVolatilityAdapter as andreasenHugeVolatilityAdapter{withAndreasenHugeVolatilityInterpl*`AndreasenHugeVolatilityInterpl' -- ^interpolation
  ,`Double' -- ^eps
  ,preErrorCheck-`String'errorCheck*-}->`BlackVolTermStructure'peekBlackVolTermStructure*#}
-- |Adapts an Andreasen-Huge interpolation to QuantLib's local-volatility term-structure interface.
{#fun qlAndreasenHugeLocalVolAdapter as andreasenHugeLocalVolAdapter{withAndreasenHugeVolatilityInterpl*`AndreasenHugeVolatilityInterpl' -- ^interpolation
  ,preErrorCheck-`String'errorCheck*-}->`LocalVolTermStructure'peekLocalVolTermStructure*#}

-- |the local vol at a given date and underlying level, for any 'LocalVolTermStructure' (however
-- it was constructed) -- the only way to observe what a local vol surface actually computes.
{#fun qlLocalVolTermStructureLocalVol as localVol{withGenLocalVolTermStructure*`GenLocalVolTermStructure lv'
  ,withDay*`Day'
  ,`Double' -- ^underlyingLevel
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Constant caplet volatility, no time-strike dependence
-- floating reference date, floating market data
{#fun qlConstantOptionletVol1 as constantOptionletVolatility'{fromIntegral`Word',withCalendar*`Calendar',fromEnumC`BusinessDayConvention',withQuote*`GenQuote q',withDayCounter*`DayCounter'
  ,`VolatilityType' -- ^type
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`OptionletVolatilityStructure'peekOptionletVolatilityStructure*#}

-- |fixed reference date, floating market data
{#fun qlConstantOptionletVolatility as constantOptionletVolatility{withDay*`Day',withCalendar*`Calendar',fromEnumC`BusinessDayConvention',withQuote*`GenQuote q',withDayCounter*`DayCounter'
  ,`VolatilityType' -- ^type
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`OptionletVolatilityStructure'peekOptionletVolatilityStructure*#}

-- |Optionlet volatility curve interpolating the supplied caplet-volatility nodes by variance.
-- Each node pairs an option date with its volatility, so mismatched date/value inputs are
-- unrepresentable.
capletVarianceCurve :: Day -> NonEmpty (Day, Double) -> DayCounter -> VolatilityType -> Double
  -> IO OptionletVolatilityStructure
capletVarianceCurve referenceDate nodes = qlCapletVarianceCurve referenceDate dates vols
  where (dates, vols) = unzip (toList nodes)
{#fun qlCapletVarianceCurve{withDay*`Day' -- ^referenceDate
  ,withDayArray*`[Day]'& -- ^dates
  ,withDoubleArray*`[Double]'& -- ^capletVolCurve
  ,withDayCounter*`DayCounter' -- ^dayCounter
  ,`VolatilityType' -- ^type
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`OptionletVolatilityStructure'peekOptionletVolatilityStructure*#}

-- |Strips a 'CapFloorTermVolSurface' (quoted cap\/floor term vols) into caplet\/floorlet vols via
-- 'OptionletStripper1', immediately wrapping the result behind 'StrippedOptionletAdapter' in one
-- step -- 'OptionletStripper1' itself is never exposed as a Haskell type, since none of its own
-- getters (capFloorPrices\/capletVols\/etc.) are needed beyond feeding the adapter, per the "bind
-- few inspectors" rule.
{#fun qlOptionletStripper1 as optionletStripper1{withCapFloorTermVolSurface*`CapFloorTermVolSurface'
  ,withIborIndex*`GenIborIndex ibor'
  ,fromMaybeDouble`Maybe Double' -- ^switchStrikes
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxIter
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discount
  ,`VolatilityType' -- ^type
  ,`Double' -- ^displacement
  ,`Bool' -- ^dontThrow
  ,fromMaybeEnumQuantity`Maybe (Word, TimeUnit)'& -- ^optionletFrequency
  ,preErrorCheck-`String'errorCheck*-}->`OptionletVolatilityStructure'peekOptionletVolatilityStructure*#}

-- |Extends an 'OptionletStripper1' (built internally, never exposed as its own Haskell type --
-- same fusion as 'optionletStripper1') by reconciling it against an ATM 'CapFloorTermVolCurve',
-- producing forward-forward optionlet vols. Unlike 'optionletStripper1', this keeps its own
-- concrete 'OptionletStripper2' object around, since it has real diagnostic getters
-- ('optionletStripper2AtmCapFloorStrikes'\/'optionletStripper2AtmCapFloorPrices'\/
-- 'optionletStripper2SpreadsVol') not reachable through the generic
-- 'OptionletVolatilityStructure' interface. Use 'optionletStripper2AsOptionletVolatilityStructure'
-- to pass one into anything expecting the generic interface.
{#fun qlOptionletStripper2 as optionletStripper2{withCapFloorTermVolSurface*`CapFloorTermVolSurface'
  ,withIborIndex*`GenIborIndex ibor'
  ,fromMaybeDouble`Maybe Double' -- ^switchStrikes
  ,`Double' -- ^accuracy
  ,fromIntegral`Word' -- ^maxIter
  ,withMaybeYieldTermStructure*`Maybe (GenYieldTermStructure y)' -- ^discount
  ,`VolatilityType' -- ^type
  ,`Double' -- ^displacement
  ,`Bool' -- ^dontThrow
  ,fromMaybeEnumQuantity`Maybe (Word, TimeUnit)'& -- ^optionletFrequency
  ,withCapFloorTermVolCurve*`CapFloorTermVolCurve' -- ^atmCapFloorTermVolCurve
  ,preErrorCheck-`String'errorCheck*-}->`OptionletStripper2'peekOptionletStripper2*#}

-- |Fresh construction (a 'StrippedOptionletAdapter' wrapping the 'OptionletStripper2' itself),
-- never a cast -- same idiom as 'sabrInterpolatedSmileSectionAsSmileSection'.
{#fun qlOptionletStripper2AsOptionletVolatilityStructure as optionletStripper2AsOptionletVolatilityStructure{withOptionletStripper2*`OptionletStripper2',preErrorCheck-`String'errorCheck*-}->`OptionletVolatilityStructure'peekOptionletVolatilityStructure*#}

{#fun qlOptionletStripper2AtmCapFloorStrikes as optionletStripper2AtmCapFloorStrikes{withOptionletStripper2*`OptionletStripper2',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

{#fun qlOptionletStripper2AtmCapFloorPrices as optionletStripper2AtmCapFloorPrices{withOptionletStripper2*`OptionletStripper2',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

{#fun qlOptionletStripper2SpreadsVol as optionletStripper2SpreadsVol{withOptionletStripper2*`OptionletStripper2',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |An optionlet vol surface behind a relinkable handle. The result /is/ an
-- 'OptionletVolatilityStructure': pass it anywhere one is expected and everything built on it
-- keeps tracking whatever the handle currently points at, so a later 'linkOptionletVolTo'
-- reprices already-constructed instruments without rebuilding them. Mirrors
-- 'relinkableSwaptionVolatilityStructure'.
{#fun qlRelinkableOptionletVolatilityStructure as relinkableOptionletVolatilityStructure{withMaybeOptionletVolatilityStructure*`Maybe (GenOptionletVolatilityStructure ov)'
  ,preErrorCheck-`String'errorCheck*-}->`RelinkableOptionletVolatilityStructure'peekRelinkableOptionletVolatilityStructure*#}

-- |Point a relinkable optionlet vol handle at a different surface. Everything already built on
-- the handle reprices against the new surface, with no engine rebuilt. Named distinctly from
-- 'QuantLib.TermStructure.Yield.linkTo'\/'linkBlackVolTo'\/'linkSwaptionVolTo' for the same
-- reason as those: all four relinkable vol types live in this one module.
{#fun qlRelinkableOptionletVolatilityStructureLinkTo as linkOptionletVolTo{withRelinkableOptionletVolatilityStructure*`RelinkableOptionletVolatilityStructure'
  ,withOptionletVolatilityStructure*`GenOptionletVolatilityStructure ov',preErrorCheck-`String'errorCheck*-}->`()'#}

-- |A constant Black volatility, no time-strike dependence -- floating reference date, floating
-- market data
{#fun qlBlackConstantVol1 as blackConstantVol'{fromIntegral`Word',withCalendar*`Calendar',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`BlackVolTermStructure'peekBlackVolTermStructure*#}

-- |as 'blackConstantVol\'', but a fixed reference date
{#fun qlBlackConstantVol as blackConstantVol{withDay*`Day',withCalendar*`Calendar',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`BlackVolTermStructure'peekBlackVolTermStructure*#}

-- |A Black vol surface behind a relinkable handle. The result /is/ a 'BlackVolTermStructure':
-- pass it anywhere one is expected and everything built on it keeps tracking whatever the
-- handle currently points at, so a later 'linkBlackVolTo' reprices already-constructed
-- instruments without rebuilding them. Mirrors
-- 'QuantLib.TermStructure.Yield.relinkableYieldTermStructure'.
{#fun qlRelinkableBlackVolTermStructure as relinkableBlackVolTermStructure{withMaybeBlackVolTermStructure*`Maybe (GenBlackVolTermStructure bv)'
  ,preErrorCheck-`String'errorCheck*-}->`RelinkableBlackVolTermStructure'peekRelinkableBlackVolTermStructure*#}

-- |Point a relinkable Black vol handle at a different surface. Everything already built on the
-- handle reprices against the new surface, with no engine rebuilt. Mirrors
-- 'QuantLib.TermStructure.Yield.linkTo' -- see its haddock for why this mutator is justified.
{#fun qlRelinkableBlackVolTermStructureLinkTo as linkBlackVolTo{withRelinkableBlackVolTermStructure*`RelinkableBlackVolTermStructure'
  ,withBlackVolTermStructure*`GenBlackVolTermStructure bv',preErrorCheck-`String'errorCheck*-}->`()'#}

-- |fixed reference date, floating market data
{#fun qlConstantSwaptionVolatility1 as constantSwaptionVolatility'{withDay*`Day',withCalendar*`Calendar',fromEnumC`BusinessDayConvention',withQuote*`GenQuote q',withDayCounter*`DayCounter'
  ,`VolatilityType' -- ^type
  ,`Double' -- ^shift
  ,preErrorCheck-`String'errorCheck*-}->`SwaptionVolatilityStructure'peekSwaptionVolatilityStructure*#}

-- |floating reference date, floating market data
{#fun qlConstantSwaptionVolatility as constantSwaptionVolatility{fromIntegral`Word',withCalendar*`Calendar',fromEnumC`BusinessDayConvention',withQuote*`GenQuote q',withDayCounter*`DayCounter'
  ,`VolatilityType' -- ^type
  ,`Double' -- ^shift
  ,preErrorCheck-`String'errorCheck*-}->`SwaptionVolatilityStructure'peekSwaptionVolatilityStructure*#}

-- |returns the Black variance for a given option date and swap tenor
{#fun qlSwaptionVolatilityStructureBlackVariance1 as blackVarianceForPeriod'{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,withDay*`Day' -- ^optionDate
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the Black variance for a given option time and swap tenor
{#fun qlSwaptionVolatilityStructureBlackVariance2 as blackVarianceForPeriod{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,`Double' -- optionTime
  ,fromEnumQuantity`(Word,TimeUnit)'& -- swapTenor
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the Black variance for a given option tenor and swap length
{#fun qlSwaptionVolatilityStructureBlackVariance3 as blackVarianceForTenor{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,`Double' -- ^swapLength
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the Black variance for a given option date and swap length
{#fun qlSwaptionVolatilityStructureBlackVariance4 as blackVariance'{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,withDay*`Day' -- ^optionDate
  ,`Double' -- ^swapLength
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the Black variance for a given option time and swap length
{#fun qlSwaptionVolatilityStructureBlackVariance5 as blackVariance{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,`Double' -- ^optionTime
  ,`Double' -- ^swapLength
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the Black variance for a given option tenor and swap tenor
{#fun qlSwaptionVolatilityStructureBlackVariance as blackVarianceForPeriods{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the largest swapLength for which the term structure can return vols
{#fun qlSwaptionVolatilityStructureMaxSwapLength as maxSwapLength{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the largest length for which the term structure can return vols
{#fun qlSwaptionVolatilityStructureMaxSwapTenor as maxSwapTenor{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',preEnum-`TimeUnit'peekEnum*,preErrorCheck-`String'errorCheck*-}->`Int'#}

-- |returns the smile for a given option date and swap tenor
{#fun qlSwaptionVolatilityStructureSmileSection1 as smileSectionForPeriod'{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,withDay*`Day' -- ^optionDate
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |returns the smile for a given option time and swap tenor
{#fun qlSwaptionVolatilityStructureSmileSection2 as smileSectionForPeriod{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,`Double' -- ^optionTime
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |returns the smile for a given option tenor and swap length
{#fun qlSwaptionVolatilityStructureSmileSection3 as smileSectionForTenor{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,`Double' -- ^swapLength
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |returns the smile for a given option date and swap length
{#fun qlSwaptionVolatilityStructureSmileSection4 as smileSection'{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,withDay*`Day' -- ^optionDate
  ,`Double' -- ^swapLength
  ,`Bool' -- ^extr
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |returns the smile for a given option time and swap length
{#fun qlSwaptionVolatilityStructureSmileSection5 as smileSection{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,`Double' -- ^optionTime
  ,`Double' -- ^swapLength
  ,`Bool' -- ^extr
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |returns the smile for a given option tenor and swap tenor
{#fun qlSwaptionVolatilityStructureSmileSection as smileSectionForPeriods{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Bool' -- ^extr
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |a smile section built directly from SABR parameters (Hagan et al. 2002), rather than
-- interpolated from a 'SwaptionVolatilityStructure'
{#fun qlSabrSmileSection as sabrSmileSection{`Double' -- ^timeToExpiry
  ,`Double' -- ^forward
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,`Double' -- ^shift
  ,`VolatilityType' -- ^volatilityType
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |as 'sabrSmileSection', but the time to expiry is derived from a date, reference date and day
-- counter rather than given directly
{#fun qlSabrSmileSection1 as sabrSmileSection'{withDay*`Day' -- ^optionDate
  ,`Double' -- ^forward
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,withMaybeDay*`Maybe Day' -- ^referenceDate
  ,withDayCounter*`DayCounter'
  ,`Double' -- ^shift
  ,`VolatilityType' -- ^volatilityType
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |an arbitrage-free SABR smile section (Doust's approach via 'NoArbSabrSmileSection'), built
-- directly from SABR parameters like 'sabrSmileSection' but guaranteeing a proper terminal density
{#fun qlNoArbSabrSmileSection as noArbSabrSmileSection{`Double' -- ^timeToExpiry
  ,`Double' -- ^forward
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,`Double' -- ^shift
  ,`VolatilityType' -- ^volatilityType
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |as 'noArbSabrSmileSection', but the time to expiry is derived from a date and day counter
-- rather than given directly
{#fun qlNoArbSabrSmileSection1 as noArbSabrSmileSection'{withDay*`Day' -- ^optionDate
  ,`Double' -- ^forward
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,withDayCounter*`DayCounter'
  ,`Double' -- ^shift
  ,`VolatilityType' -- ^volatilityType
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |the volatility for the given strike, for any 'SmileSection' (however it was constructed)
{#fun qlSmileSectionVolatility as smileSectionVolatility{withSmileSection*`SmileSection'
  ,`Double' -- ^strike
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the Black variance for the given strike, for any 'SmileSection' (however it was constructed)
{#fun qlSmileSectionVariance as smileSectionVariance{withSmileSection*`SmileSection'
  ,`Double' -- ^strike
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the ATM level baked into the 'SmileSection' at construction (or later re-anchored via
-- 'atmSmileSection'), for any 'SmileSection' (however it was constructed)
{#fun qlSmileSectionAtmLevel as smileSectionAtmLevel{withSmileSection*`SmileSection'
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the (non-discounted-by-default) price of a European option with the given strike\/type,
-- for any 'SmileSection' (however it was constructed)
{#fun qlSmileSectionOptionPrice as smileSectionOptionPrice{withSmileSection*`SmileSection'
  ,`Double' -- ^strike
  ,fromEnumC`OptionType' -- ^type
  ,`Double' -- ^discount
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the price of a cash-or-nothing digital option with the given strike\/type, approximated via a
-- call\/put spread of width @gap@, for any 'SmileSection' (however it was constructed)
{#fun qlSmileSectionDigitalOptionPrice as smileSectionDigitalOptionPrice{withSmileSection*`SmileSection'
  ,`Double' -- ^strike
  ,fromEnumC`OptionType' -- ^type
  ,`Double' -- ^discount
  ,`Double' -- ^gap
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the risk-neutral probability density at the given strike, approximated via a finite difference
-- of width @gap@ on 'smileSectionOptionPrice', for any 'SmileSection' (however it was constructed)
{#fun qlSmileSectionDensity as smileSectionDensity{withSmileSection*`SmileSection'
  ,`Double' -- ^strike
  ,`Double' -- ^discount
  ,`Double' -- ^gap
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |a flat-volatility smile section: 'volatility' returns @vol@ for every strike.
-- 'Nothing'\/'Nothing' reproduce upstream's own defaults for @referenceDate@\/@atmLevel@.
{#fun qlFlatSmileSection as flatSmileSection{withDay*`Day'
  ,`Double' -- ^vol
  ,withDayCounter*`DayCounter'
  ,withMaybeDay*`Maybe Day' -- ^referenceDate
  ,fromMaybeDouble`Maybe Double' -- ^atmLevel
  ,`VolatilityType' -- ^type
  ,`Double' -- ^shift
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |a 'SmileSection' whose volatility at every strike is @source@'s plus @spread@ (which may
-- change over time, since it's a live 'GenQuote' rather than a fixed number)
{#fun qlSpreadedSmileSection as spreadedSmileSection{withSmileSection*`SmileSection'
  ,withQuote*`GenQuote q'
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |@source@ re-anchored to a different ATM level ('Nothing' reproduces upstream's own default,
-- which recomputes the ATM level from @source@ itself). @source@'s volatility at every other
-- strike is unchanged -- use 'smileSectionAtmLevel' to observe what this changed.
{#fun qlAtmSmileSection as atmSmileSection{withSmileSection*`SmileSection'
  ,fromMaybeDouble`Maybe Double' -- ^atm
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |a Stochastic Volatility Inspired (SVI) smile section: total variance at
-- log-moneyness @k = log(strike\/forward)@ is @a + b*(rho*(k-m) + sqrt((k-m)^2 + sigma^2))@.
-- Direct evaluation, no calibration.
{#fun qlSviSmileSection as sviSmileSection{withDay*`Day'
  ,`Double' -- ^forward
  ,`Double' -- ^a
  ,`Double' -- ^b
  ,`Double' -- ^sigma
  ,`Double' -- ^rho
  ,`Double' -- ^m
  ,withDayCounter*`DayCounter'
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |a ZABR (Andreasen\/Huge 2011) smile section: direct evaluation (no calibration) of a SABR-like
-- model widened by a fifth parameter, @gamma@, that controls the backbone shape away from
-- @gamma = 1@ (which reduces exactly to Hagan\'s SABR). @evaluation@ selects how the price\/vol at
-- a strike is computed -- see 'ZabrEvaluation'. @moneyness@ is the strike grid (as multiples of
-- the forward) used only by 'ZabrLocalVolatility'\/'ZabrFullFd' to build their finite-difference
-- solve; an empty list reproduces upstream\'s own 21-point default grid, and it is ignored by the
-- two closed-form evaluation modes. @fdRefinement@ subdivides each grid interval for the FD
-- solve\'s accuracy\/speed tradeoff (upstream\'s own default is 5).
{#fun qlZabrSmileSection as zabrSmileSection{`ZabrEvaluation'
  ,`Double' -- ^timeToExpiry
  ,`Double' -- ^forward
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,`Double' -- ^gamma
  ,withDoubleArray*`[Double]'& -- ^moneyness
  ,fromIntegral`Word' -- ^fdRefinement
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |as 'zabrSmileSection', but the time to expiry is derived from a date and day counter rather
-- than given directly.
{#fun qlZabrSmileSection1 as zabrSmileSection'{`ZabrEvaluation'
  ,withDay*`Day' -- ^optionDate
  ,`Double' -- ^forward
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,`Double' -- ^gamma
  ,withDayCounter*`DayCounter'
  ,withDoubleArray*`[Double]'& -- ^moneyness
  ,fromIntegral`Word' -- ^fdRefinement
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |a smile section calibrated to a market smile (strikes/vols given directly, not as live
-- quotes -- calibration runs once, eagerly, at construction). alpha\/beta\/nu\/rho\/vegaWeighted
-- are the SABR calibration's initial guess and fixed\/free flags; 'sabrEndCriteria'\/
-- 'sabrOptimizationMethod' default to 'Nothing', which falls back to QuantLib's own internal
-- defaults -- a caller-supplied 'EndCriteria'\/'OptimizationMethod' is safe to pass here since
-- both are shared_ptr-boxed on the C++ side (see the qlaux.h comment above the
-- QlEndCriteria\/QlOptimizationMethod typedefs), so the copy this object's constructor keeps
-- survives regardless of when Haskell's own handle is collected.
sabrInterpolatedSmileSection :: Day -- ^optionDate
  -> GenQuote q1 -- ^forward
  -> NonEmpty (Double, GenQuote q3) -- ^strike/volatility quotes
  -> Bool -- ^hasFloatingStrikes
  -> GenQuote q2 -- ^atmVolatility
  -> Double -- ^alpha
  -> Double -- ^beta
  -> Double -- ^nu
  -> Double -- ^rho
  -> SabrInterpolatedSmileSectionOpts -> IO SabrInterpolatedSmileSection
sabrInterpolatedSmileSection optionDate forward strikeVols hasFloatingStrikes atmVolatility
  alpha beta nu rho opts = do
  dc <- maybe (dayCounter Actual365FixedStandard) return (sabrDayCounter opts)
  sabrInterpolatedSmileSection_ optionDate forward strikes hasFloatingStrikes atmVolatility vols
    alpha beta nu rho (sabrIsAlphaFixed opts) (sabrIsBetaFixed opts) (sabrIsNuFixed opts)
    (sabrIsRhoFixed opts) (sabrVegaWeighted opts) (sabrEndCriteria opts) (sabrOptimizationMethod opts)
    dc (sabrShift opts)
  where (strikes, vols) = unzip (toList strikeVols)

{#fun qlSabrInterpolatedSmileSection as sabrInterpolatedSmileSection_{withDay*`Day'
  ,withQuote*`GenQuote q1' -- ^forward
  ,withDoubleArray*`[Double]'& -- ^strikes
  ,`Bool' -- ^hasFloatingStrikes
  ,withQuote*`GenQuote q2' -- ^atmVolatility
  ,withQuoteArray*`[GenQuote q3]'& -- ^vols
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,`Bool' -- ^isAlphaFixed
  ,`Bool' -- ^isBetaFixed
  ,`Bool' -- ^isNuFixed
  ,`Bool' -- ^isRhoFixed
  ,`Bool' -- ^vegaWeighted
  ,withMaybeEndCriteria*`Maybe EndCriteria'
  ,withMaybeOptimizationMethod*`Maybe OptimizationMethod'
  ,withDayCounter*`DayCounter'
  ,`Double' -- ^shift
  ,preErrorCheck-`String'errorCheck*-}->`SabrInterpolatedSmileSection'peekSabrInterpolatedSmileSection*#}

-- |upcast to the generic 'SmileSection' interface (e.g. for 'smileSectionVolatility'\/'smileSectionVariance').
-- A fresh-@shared_ptr@ upcast, always safe -- not the reverse (downcast) direction.
{#fun qlSabrInterpolatedSmileSectionAsSmileSection as sabrInterpolatedSmileSectionAsSmileSection{withSabrInterpolatedSmileSection*`SabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |calibrated alpha (post-fit; can differ from the initial guess passed to
-- 'sabrInterpolatedSmileSection' unless @sabrIsAlphaFixed@ was set).
{#fun qlSabrInterpolatedSmileSectionAlpha as sabrInterpolatedSmileSectionAlpha{withSabrInterpolatedSmileSection*`SabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |calibrated beta, see 'sabrInterpolatedSmileSectionAlpha'
{#fun qlSabrInterpolatedSmileSectionBeta as sabrInterpolatedSmileSectionBeta{withSabrInterpolatedSmileSection*`SabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |calibrated nu, see 'sabrInterpolatedSmileSectionAlpha'
{#fun qlSabrInterpolatedSmileSectionNu as sabrInterpolatedSmileSectionNu{withSabrInterpolatedSmileSection*`SabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |calibrated rho, see 'sabrInterpolatedSmileSectionAlpha'
{#fun qlSabrInterpolatedSmileSectionRho as sabrInterpolatedSmileSectionRho{withSabrInterpolatedSmileSection*`SabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |root-mean-square calibration error
{#fun qlSabrInterpolatedSmileSectionRmsError as sabrInterpolatedSmileSectionRmsError{withSabrInterpolatedSmileSection*`SabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |maximum calibration error
{#fun qlSabrInterpolatedSmileSectionMaxError as sabrInterpolatedSmileSectionMaxError{withSabrInterpolatedSmileSection*`SabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the reason the SABR calibration's optimizer stopped
{#fun qlSabrInterpolatedSmileSectionEndCriteria as sabrInterpolatedSmileSectionEndCriteria{withSabrInterpolatedSmileSection*`SabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`EndCriteriaType'#}

-- |a smile section calibrated to a market smile using Stochastic Volatility Inspired (SVI, Gatheral
-- 2004) parameterization: total variance at log-moneyness @k = log(strike\/forward)@ is
-- @a + b*(rho*(k-m) + sqrt((k-m)^2 + sigma^2))@. Strikes\/vols are given directly (not as live
-- quotes) -- calibration runs once, eagerly, at construction, same as 'sabrInterpolatedSmileSection'.
-- @a@\/@b@\/@sigma@\/@rho@\/@m@ are the SVI calibration's initial guess;
-- @aIsFixed@\/@bIsFixed@\/@sigmaIsFixed@\/@rhoIsFixed@\/@mIsFixed@ have no upstream default (unlike
-- SABR's fixed flags, which default to 'False') and so are always required here. Calibration
-- enforces, at construction: @b >= 0@, @|rho| < 1@, @sigma > 0@,
-- @a + b*sigma*sqrt(1-rho^2) >= 0@, and @b*(1+|rho|) <= 4@.
sviInterpolatedSmileSection :: Day -- ^optionDate
  -> GenQuote q1 -- ^forward
  -> NonEmpty (Double, GenQuote q3) -- ^strike/volatility quotes
  -> Bool -- ^hasFloatingStrikes
  -> GenQuote q2 -- ^atmVolatility
  -> Double -- ^a
  -> Double -- ^b
  -> Double -- ^sigma
  -> Double -- ^rho
  -> Double -- ^m
  -> Bool -- ^aIsFixed
  -> Bool -- ^bIsFixed
  -> Bool -- ^sigmaIsFixed
  -> Bool -- ^rhoIsFixed
  -> Bool -- ^mIsFixed
  -> Bool -- ^vegaWeighted
  -> Maybe EndCriteria
  -> Maybe OptimizationMethod
  -> DayCounter -> IO SviInterpolatedSmileSection
sviInterpolatedSmileSection optionDate forward strikeVols hasFloatingStrikes atmVolatility
  a b sigma rho m aIsFixed bIsFixed sigmaIsFixed rhoIsFixed mIsFixed vegaWeighted
  endCriteria method dc =
  sviInterpolatedSmileSection_ optionDate forward strikes hasFloatingStrikes atmVolatility vols
    a b sigma rho m aIsFixed bIsFixed sigmaIsFixed rhoIsFixed mIsFixed vegaWeighted
    endCriteria method dc
  where (strikes, vols) = unzip (toList strikeVols)

{#fun qlSviInterpolatedSmileSection as sviInterpolatedSmileSection_{withDay*`Day'
  ,withQuote*`GenQuote q1' -- ^forward
  ,withDoubleArray*`[Double]'& -- ^strikes
  ,`Bool' -- ^hasFloatingStrikes
  ,withQuote*`GenQuote q2' -- ^atmVolatility
  ,withQuoteArray*`[GenQuote q3]'& -- ^vols
  ,`Double' -- ^a
  ,`Double' -- ^b
  ,`Double' -- ^sigma
  ,`Double' -- ^rho
  ,`Double' -- ^m
  ,`Bool' -- ^aIsFixed
  ,`Bool' -- ^bIsFixed
  ,`Bool' -- ^sigmaIsFixed
  ,`Bool' -- ^rhoIsFixed
  ,`Bool' -- ^mIsFixed
  ,`Bool' -- ^vegaWeighted
  ,withMaybeEndCriteria*`Maybe EndCriteria'
  ,withMaybeOptimizationMethod*`Maybe OptimizationMethod'
  ,withDayCounter*`DayCounter'
  ,preErrorCheck-`String'errorCheck*-}->`SviInterpolatedSmileSection'peekSviInterpolatedSmileSection*#}

-- |upcast to the generic 'SmileSection' interface (e.g. for 'smileSectionVolatility'\/'smileSectionVariance').
-- A fresh-@shared_ptr@ upcast, always safe -- not the reverse (downcast) direction.
{#fun qlSviInterpolatedSmileSectionAsSmileSection as sviInterpolatedSmileSectionAsSmileSection{withSviInterpolatedSmileSection*`SviInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |calibrated @a@ (post-fit; can differ from the initial guess passed to
-- 'sviInterpolatedSmileSection' unless @aIsFixed@ was set).
{#fun qlSviInterpolatedSmileSectionA as sviInterpolatedSmileSectionA{withSviInterpolatedSmileSection*`SviInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |calibrated @b@, see 'sviInterpolatedSmileSectionA'
{#fun qlSviInterpolatedSmileSectionB as sviInterpolatedSmileSectionB{withSviInterpolatedSmileSection*`SviInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |calibrated @sigma@, see 'sviInterpolatedSmileSectionA'
{#fun qlSviInterpolatedSmileSectionSigma as sviInterpolatedSmileSectionSigma{withSviInterpolatedSmileSection*`SviInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |calibrated @rho@, see 'sviInterpolatedSmileSectionA'
{#fun qlSviInterpolatedSmileSectionRho as sviInterpolatedSmileSectionRho{withSviInterpolatedSmileSection*`SviInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |calibrated @m@, see 'sviInterpolatedSmileSectionA'
{#fun qlSviInterpolatedSmileSectionM as sviInterpolatedSmileSectionM{withSviInterpolatedSmileSection*`SviInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |root-mean-square calibration error
{#fun qlSviInterpolatedSmileSectionRmsError as sviInterpolatedSmileSectionRmsError{withSviInterpolatedSmileSection*`SviInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |maximum calibration error
{#fun qlSviInterpolatedSmileSectionMaxError as sviInterpolatedSmileSectionMaxError{withSviInterpolatedSmileSection*`SviInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the reason the SVI calibration's optimizer stopped
{#fun qlSviInterpolatedSmileSectionEndCriteria as sviInterpolatedSmileSectionEndCriteria{withSviInterpolatedSmileSection*`SviInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`EndCriteriaType'#}

-- |a smile section calibrated to a market smile using the arbitrage-free SABR parameterization
-- (Doust's approach, via 'NoArbSabrModel' -- see 'noArbSabrSmileSection'). Unlike
-- 'noArbSabrSmileSection', which takes fixed calibrated parameters directly, this runs the
-- alpha\/beta\/nu\/rho calibration itself against the given strike\/volatility quotes -- eagerly,
-- at construction, same as 'sabrInterpolatedSmileSection'. @alpha@\/@beta@\/@nu@\/@rho@ are the
-- calibration's initial guess; @isAlphaFixed@\/@isBetaFixed@\/@isNuFixed@\/@isRhoFixed@ default to
-- 'False' upstream (unlike SVI's fixed flags, which have no default), and there is no @shift@
-- parameter (unlike 'sabrInterpolatedSmileSection').
noArbSabrInterpolatedSmileSection :: Day -- ^optionDate
  -> GenQuote q1 -- ^forward
  -> NonEmpty (Double, GenQuote q3) -- ^strike/volatility quotes
  -> Bool -- ^hasFloatingStrikes
  -> GenQuote q2 -- ^atmVolatility
  -> Double -- ^alpha
  -> Double -- ^beta
  -> Double -- ^nu
  -> Double -- ^rho
  -> Bool -- ^isAlphaFixed
  -> Bool -- ^isBetaFixed
  -> Bool -- ^isNuFixed
  -> Bool -- ^isRhoFixed
  -> Bool -- ^vegaWeighted
  -> Maybe EndCriteria
  -> Maybe OptimizationMethod
  -> DayCounter -> IO NoArbSabrInterpolatedSmileSection
noArbSabrInterpolatedSmileSection optionDate forward strikeVols hasFloatingStrikes atmVolatility
  alpha beta nu rho isAlphaFixed isBetaFixed isNuFixed isRhoFixed vegaWeighted
  endCriteria method dc =
  noArbSabrInterpolatedSmileSection_ optionDate forward strikes hasFloatingStrikes atmVolatility vols
    alpha beta nu rho isAlphaFixed isBetaFixed isNuFixed isRhoFixed vegaWeighted
    endCriteria method dc
  where (strikes, vols) = unzip (toList strikeVols)

{#fun qlNoArbSabrInterpolatedSmileSection as noArbSabrInterpolatedSmileSection_{withDay*`Day'
  ,withQuote*`GenQuote q1' -- ^forward
  ,withDoubleArray*`[Double]'& -- ^strikes
  ,`Bool' -- ^hasFloatingStrikes
  ,withQuote*`GenQuote q2' -- ^atmVolatility
  ,withQuoteArray*`[GenQuote q3]'& -- ^vols
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,`Bool' -- ^isAlphaFixed
  ,`Bool' -- ^isBetaFixed
  ,`Bool' -- ^isNuFixed
  ,`Bool' -- ^isRhoFixed
  ,`Bool' -- ^vegaWeighted
  ,withMaybeEndCriteria*`Maybe EndCriteria'
  ,withMaybeOptimizationMethod*`Maybe OptimizationMethod'
  ,withDayCounter*`DayCounter'
  ,preErrorCheck-`String'errorCheck*-}->`NoArbSabrInterpolatedSmileSection'peekNoArbSabrInterpolatedSmileSection*#}

-- |upcast to the generic 'SmileSection' interface (e.g. for 'smileSectionVolatility'\/'smileSectionVariance').
-- A fresh-@shared_ptr@ upcast, always safe -- not the reverse (downcast) direction.
{#fun qlNoArbSabrInterpolatedSmileSectionAsSmileSection as noArbSabrInterpolatedSmileSectionAsSmileSection{withNoArbSabrInterpolatedSmileSection*`NoArbSabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |calibrated @alpha@ (post-fit; can differ from the initial guess passed to
-- 'noArbSabrInterpolatedSmileSection' unless @isAlphaFixed@ was set).
{#fun qlNoArbSabrInterpolatedSmileSectionAlpha as noArbSabrInterpolatedSmileSectionAlpha{withNoArbSabrInterpolatedSmileSection*`NoArbSabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |calibrated @beta@, see 'noArbSabrInterpolatedSmileSectionAlpha'
{#fun qlNoArbSabrInterpolatedSmileSectionBeta as noArbSabrInterpolatedSmileSectionBeta{withNoArbSabrInterpolatedSmileSection*`NoArbSabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |calibrated @nu@, see 'noArbSabrInterpolatedSmileSectionAlpha'
{#fun qlNoArbSabrInterpolatedSmileSectionNu as noArbSabrInterpolatedSmileSectionNu{withNoArbSabrInterpolatedSmileSection*`NoArbSabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |calibrated @rho@, see 'noArbSabrInterpolatedSmileSectionAlpha'
{#fun qlNoArbSabrInterpolatedSmileSectionRho as noArbSabrInterpolatedSmileSectionRho{withNoArbSabrInterpolatedSmileSection*`NoArbSabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |root-mean-square calibration error
{#fun qlNoArbSabrInterpolatedSmileSectionRmsError as noArbSabrInterpolatedSmileSectionRmsError{withNoArbSabrInterpolatedSmileSection*`NoArbSabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |maximum calibration error
{#fun qlNoArbSabrInterpolatedSmileSectionMaxError as noArbSabrInterpolatedSmileSectionMaxError{withNoArbSabrInterpolatedSmileSection*`NoArbSabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |the reason the calibration's optimizer stopped
{#fun qlNoArbSabrInterpolatedSmileSectionEndCriteria as noArbSabrInterpolatedSmileSectionEndCriteria{withNoArbSabrInterpolatedSmileSection*`NoArbSabrInterpolatedSmileSection',preErrorCheck-`String'errorCheck*-}->`EndCriteriaType'#}

-- |implements the conversion between swap dates and swap (time) length
{#fun qlSwaptionVolatilityStructureSwapLength1 as swapLength'{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,withDay*`Day' -- ^start
  ,withDay*`Day' -- ^end
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |implements the conversion between swap tenor and swap (time) length
{#fun qlSwaptionVolatilityStructureSwapLength as swapLength{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',fromEnumQuantity`(Word,TimeUnit)'&,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the volatility for a given option date and swap tenor
{#fun qlSwaptionVolatilityStructureVolatility1 as volatilityForPeriod'{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,withDay*`Day' -- ^optionDate
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the volatility for a given option time and swap tenor
{#fun qlSwaptionVolatilityStructureVolatility2 as volatilityForPeriod{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,`Double' -- ^optionTime
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the volatility for a given option tenor and swap length
{#fun qlSwaptionVolatilityStructureVolatility3 as volatilityForTenor{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,`Double' -- ^swapLength
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the volatility for a given option date and swap length
{#fun qlSwaptionVolatilityStructureVolatility4 as volatilityForTenor'{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,withDay*`Day' -- ^optionDate
  ,`Double' -- ^swapLength
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the volatility for a given option time and swap length
{#fun qlSwaptionVolatilityStructureVolatility5 as volatility{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,`Double' -- ^optionTime
  ,`Double' -- ^swapLength
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the volatility for a given option tenor and swap tenor
{#fun qlSwaptionVolatilityStructureVolatility as volatilityForPeriods{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |A constant callable-bond volatility, no time-strike dependence -- floating reference date,
-- floating market data
{#fun qlCallableBondConstantVolatility1 as callableBondConstantVolatility'{fromIntegral`Word',withCalendar*`Calendar',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`CallableBondVolatilityStructure'peekCallableBondVolatilityStructure*#}

-- |as 'callableBondConstantVolatility\'', but a fixed reference date
{#fun qlCallableBondConstantVolatility as callableBondConstantVolatility{withDay*`Day',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`CallableBondVolatilityStructure'peekCallableBondVolatilityStructure*#}

-- |fixed reference date, floating market data
{#fun qlConstantCapFloorTermVolatility1 as constantCapFloorTermVolatility'{withDay*`Day',withCalendar*`Calendar',fromEnumC`BusinessDayConvention',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`CapFloorTermVolatilityStructure'peekCapFloorTermVolatilityStructure*#}

-- |floating reference date, floating market data
{#fun qlConstantCapFloorTermVolatility as constantCapFloorTermVolatility{fromIntegral`Word',withCalendar*`Calendar',fromEnumC`BusinessDayConvention',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`CapFloorTermVolatilityStructure'peekCapFloorTermVolatilityStructure*#}

-- |returns the volatility for a given option tenor and strike
{#fun qlCapFloorTermVolatilityStructureVolatilityForPeriod as capFloorVolatilityForPeriod{withGenCapFloorTermVolatilityStructure*`GenCapFloorTermVolatilityStructure c'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the volatility for a given option date and strike
{#fun qlCapFloorTermVolatilityStructureVolatilityForDate as capFloorVolatilityForDate{withGenCapFloorTermVolatilityStructure*`GenCapFloorTermVolatilityStructure c'
  ,withDay*`Day' -- ^optionDate
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the volatility for a given option time and strike
{#fun qlCapFloorTermVolatilityStructureVolatilityForTime as capFloorVolatilityForTime{withGenCapFloorTermVolatilityStructure*`GenCapFloorTermVolatilityStructure c'
  ,`Double' -- ^optionTime
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The option-tenor grid's dates, calendar-advanced from the curve's reference date.
{#fun qlCapFloorTermVolCurveOptionDates as capFloorTermVolCurveOptionDates{withCapFloorTermVolCurve*`CapFloorTermVolCurve',preArray-`[Day]'&peekDayArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |As 'capFloorTermVolCurveOptionDates', in year fractions from the curve's reference date.
{#fun qlCapFloorTermVolCurveOptionTimes as capFloorTermVolCurveOptionTimes{withCapFloorTermVolCurve*`CapFloorTermVolCurve',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |The option-tenor grid's dates, calendar-advanced from the surface's reference date.
{#fun qlCapFloorTermVolSurfaceOptionDates as capFloorTermVolSurfaceOptionDates{withCapFloorTermVolSurface*`CapFloorTermVolSurface',preArray-`[Day]'&peekDayArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |As 'capFloorTermVolSurfaceOptionDates', in year fractions from the surface's reference date.
{#fun qlCapFloorTermVolSurfaceOptionTimes as capFloorTermVolSurfaceOptionTimes{withCapFloorTermVolSurface*`CapFloorTermVolSurface',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |spot at-the-money volatility for a given option tenor
{#fun qlBlackAtmVolCurveAtmVolForPeriod as atmVolForPeriod{withGenBlackAtmVolCurve*`GenBlackAtmVolCurve b'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |spot at-the-money volatility for a given option maturity date
{#fun qlBlackAtmVolCurveAtmVolForDate as atmVolForDate{withGenBlackAtmVolCurve*`GenBlackAtmVolCurve b'
  ,withDay*`Day' -- ^maturity
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |spot at-the-money volatility for a given option maturity time
{#fun qlBlackAtmVolCurveAtmVolForTime as atmVolForTime{withGenBlackAtmVolCurve*`GenBlackAtmVolCurve b'
  ,`Double' -- ^maturity
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |spot at-the-money variance for a given option tenor
{#fun qlBlackAtmVolCurveAtmVarianceForPeriod as atmVarianceForPeriod{withGenBlackAtmVolCurve*`GenBlackAtmVolCurve b'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |spot at-the-money variance for a given option maturity date
{#fun qlBlackAtmVolCurveAtmVarianceForDate as atmVarianceForDate{withGenBlackAtmVolCurve*`GenBlackAtmVolCurve b'
  ,withDay*`Day' -- ^maturity
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |spot at-the-money variance for a given option maturity time
{#fun qlBlackAtmVolCurveAtmVarianceForTime as atmVarianceForTime{withGenBlackAtmVolCurve*`GenBlackAtmVolCurve b'
  ,`Double' -- ^maturity
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the smile for a given option tenor
{#fun qlBlackVolSurfaceSmileSectionForPeriod as blackVolSurfaceSmileSectionForPeriod{withGenBlackVolSurface*`GenBlackVolSurface b'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |returns the smile for a given option date
{#fun qlBlackVolSurfaceSmileSectionForDate as blackVolSurfaceSmileSectionForDate{withGenBlackVolSurface*`GenBlackVolSurface b'
  ,withDay*`Day' -- ^optionDate
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |returns the smile for a given option time
{#fun qlBlackVolSurfaceSmileSectionForTime as blackVolSurfaceSmileSectionForTime{withGenBlackVolSurface*`GenBlackVolSurface b'
  ,`Double' -- ^optionTime
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |Abcd-interpolated at-the-money (no-smile) volatility curve -- floating reference date,
-- floating market data. @inclusionInInterpolationFlag@ selects which quotes feed the ABCD fit
-- (upstream defaults this to all-'True' when omitted; hasquant always requires it explicitly,
-- per the widen-in-place convention for a handful of trailing defaulted params).
abcdAtmVolCurve :: Word -> Calendar
  -> NonEmpty ((Word, TimeUnit), GenQuote q, Bool) -- ^tenor, volatility, inclusion flag
  -> BusinessDayConvention -> DayCounter -> IO AbcdAtmVolCurve
abcdAtmVolCurve d c points bdc dc = qlAbcdAtmVolCurve d c n t qs flags bdc dc
  where (ntenors, qs, flags) = unzip3 (toList points)
        (n, t) = unzip ntenors
{#fun qlAbcdAtmVolCurve{fromIntegral`Word',withCalendar*`Calendar',withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&,withQuoteArray*`[GenQuote q]'&,withBoolArray*`[Bool]'&,fromEnumC`BusinessDayConvention',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`AbcdAtmVolCurve'peekAbcdAtmVolCurve*#}

{#fun qlAbcdAtmVolCurveA as abcdAtmVolCurveA{withAbcdAtmVolCurve*`AbcdAtmVolCurve',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAbcdAtmVolCurveB as abcdAtmVolCurveB{withAbcdAtmVolCurve*`AbcdAtmVolCurve',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAbcdAtmVolCurveC as abcdAtmVolCurveC{withAbcdAtmVolCurve*`AbcdAtmVolCurve',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAbcdAtmVolCurveD as abcdAtmVolCurveD{withAbcdAtmVolCurve*`AbcdAtmVolCurve',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAbcdAtmVolCurveRmsError as abcdAtmVolCurveRmsError{withAbcdAtmVolCurve*`AbcdAtmVolCurve',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAbcdAtmVolCurveMaxError as abcdAtmVolCurveMaxError{withAbcdAtmVolCurve*`AbcdAtmVolCurve',preErrorCheck-`String'errorCheck*-}->`Double'#}
{#fun qlAbcdAtmVolCurveEndCriteria as abcdAtmVolCurveEndCriteria{withAbcdAtmVolCurve*`AbcdAtmVolCurve',preErrorCheck-`String'errorCheck*-}->`EndCriteriaType'#}

-- |@k@ adjustment factor at a given time
{#fun qlAbcdAtmVolCurveKAtTime as abcdAtmVolCurveKAtTime{withAbcdAtmVolCurve*`AbcdAtmVolCurve',`Double',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |@k@ adjustment factors for every option tenor used in interpolation
{#fun qlAbcdAtmVolCurveK as abcdAtmVolCurveK{withAbcdAtmVolCurve*`AbcdAtmVolCurve',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

abcdAtmVolCurveOptionTenors :: AbcdAtmVolCurve -> IO [(Word, TimeUnit)]
abcdAtmVolCurveOptionTenors o = do
  (ns, us) <- qlAbcdAtmVolCurveOptionTenors o
  pure $ zip (map fromIntegral ns) (map toEnum us)
{#fun qlAbcdAtmVolCurveOptionTenors{withAbcdAtmVolCurve*`AbcdAtmVolCurve',preArray-`[Int]'&peekIntArray*,preArray-`[Int]'&peekIntArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |As 'abcdAtmVolCurveOptionTenors', but only the tenors actually used in the ABCD fit.
abcdAtmVolCurveOptionTenorsInInterpolation :: AbcdAtmVolCurve -> IO [(Word, TimeUnit)]
abcdAtmVolCurveOptionTenorsInInterpolation o = do
  (ns, us) <- qlAbcdAtmVolCurveOptionTenorsInInterpolation o
  pure $ zip (map fromIntegral ns) (map toEnum us)
{#fun qlAbcdAtmVolCurveOptionTenorsInInterpolation{withAbcdAtmVolCurve*`AbcdAtmVolCurve',preArray-`[Int]'&peekIntArray*,preArray-`[Int]'&peekIntArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

{#fun qlAbcdAtmVolCurveOptionDates as abcdAtmVolCurveOptionDates{withAbcdAtmVolCurve*`AbcdAtmVolCurve',preArray-`[Day]'&peekDayArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |As 'abcdAtmVolCurveOptionDates', in year fractions from the curve's reference date.
{#fun qlAbcdAtmVolCurveOptionTimes as abcdAtmVolCurveOptionTimes{withAbcdAtmVolCurve*`AbcdAtmVolCurve',preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |SABR-smile 'BlackVolSurface' built from an interest-rate index, an ATM 'BlackAtmVolCurve', and
-- per-tenor ATM-rate spreads\/vol-spread matrix. @volSpreads@'s rows follow @optionTenors@ and
-- columns follow @atmRateSpreads@ (same row\/column convention as 'sabrSwaptionVolatilityCube's
-- @volSpreads@).
sabrVolSurface :: GenInterestRateIndex ix -> GenBlackAtmVolCurve b -> NonEmpty (Word, TimeUnit) -- ^optionTenors
  -> NonEmpty Double -- ^atmRateSpreads
  -> Matrix (GenQuote q) -- ^volSpreads
  -> IO SabrVolSurface
sabrVolSurface ix atm ntenors spreads (Matrix vr vc vd) =
  qlSabrVolSurface ix atm n t (toList spreads) vr vc vd
  where (n, t) = unzip (toList ntenors)
{#fun qlSabrVolSurface{withInterestRateIndex*`GenInterestRateIndex ix',withGenBlackAtmVolCurve*`GenBlackAtmVolCurve b'
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&
  ,withDoubleArray*`[Double]'&
  ,fromIntegral`Word',fromIntegral`Word',withQuoteArrayRaw*`[GenQuote q]'
  ,preErrorCheck-`String'errorCheck*-}->`SabrVolSurface'peekSabrVolSurface*#}

-- |the 'BlackAtmVolCurve' this surface's ATM level is anchored to
{#fun qlSabrVolSurfaceAtmCurve as sabrVolSurfaceAtmCurve{withSabrVolSurface*`SabrVolSurface',preErrorCheck-`String'errorCheck*-}->`BlackAtmVolCurve'peekBlackAtmVolCurve*#}

-- |per-@atmRateSpreads@-column volatility spreads for a given option tenor
{#fun qlSabrVolSurfaceVolatilitySpreadsForPeriod as sabrVolSurfaceVolatilitySpreadsForPeriod{withSabrVolSurface*`SabrVolSurface'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |as 'sabrVolSurfaceVolatilitySpreadsForPeriod', for a given option date
{#fun qlSabrVolSurfaceVolatilitySpreadsForDate as sabrVolSurfaceVolatilitySpreadsForDate{withSabrVolSurface*`SabrVolSurface'
  ,withDay*`Day' -- ^optionDate
  ,preArray-`[Double]'&peekDoubleArray*,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |the interest rate index this surface was built from (folded in from upstream's
-- @InterestRateVolSurface@, not given its own hierarchy level here -- see 'SabrVolSurface').
{#fun qlSabrVolSurfaceIndex as sabrVolSurfaceIndex{withSabrVolSurface*`SabrVolSurface',preErrorCheck-`String'errorCheck*-}->`InterestRateIndex'peekInterestRateIndex*#}

-- |as 'sabrVolSurfaceIndex', converts an option tenor to its option date (folded in from
-- @InterestRateVolSurface@)
{#fun qlSabrVolSurfaceOptionDateFromTenor as sabrVolSurfaceOptionDateFromTenor{withSabrVolSurface*`SabrVolSurface'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |A 'SwaptionVolatilityStructure' whose volatility at every point is @source@'s plus @spread@
-- (which may change over time, since it's a live 'GenQuote' rather than a fixed number)
{#fun qlSpreadedSwaptionVolatility as spreadedSwaptionVolatility{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',withQuote*`GenQuote q',preErrorCheck-`String'errorCheck*-}->`SwaptionVolatilityStructure'peekSwaptionVolatilityStructure*#}

-- |as 'spreadedSwaptionVolatility', for 'OptionletVolatilityStructure' rather than
-- 'SwaptionVolatilityStructure'
{#fun qlSpreadedOptionletVolatility as spreadedOptionletVol{withOptionletVolatilityStructure*`GenOptionletVolatilityStructure ov',withQuote*`GenQuote q',preErrorCheck-`String'errorCheck*-}->`OptionletVolatilityStructure'peekOptionletVolatilityStructure*#}

-- |A swaption vol surface behind a relinkable handle. The result /is/ a
-- 'SwaptionVolatilityStructure': pass it anywhere one is expected and everything built on it
-- keeps tracking whatever the handle currently points at, so a later 'linkSwaptionVolTo'
-- reprices already-constructed instruments without rebuilding them. Mirrors
-- 'QuantLib.TermStructure.Yield.relinkableYieldTermStructure'.
{#fun qlRelinkableSwaptionVolatilityStructure as relinkableSwaptionVolatilityStructure{withMaybeSwaptionVolatilityStructure*`Maybe (GenSwaptionVolatilityStructure sv)'
  ,preErrorCheck-`String'errorCheck*-}->`RelinkableSwaptionVolatilityStructure'peekRelinkableSwaptionVolatilityStructure*#}

-- |Point a relinkable swaption vol handle at a different surface. Everything already built on
-- the handle reprices against the new surface, with no engine rebuilt. Named distinctly from
-- 'QuantLib.TermStructure.Yield.linkTo' and 'linkBlackVolTo' because
-- 'BlackVolTermStructure'\/'SwaptionVolatilityStructure'\/'OptionletVolatilityStructure' all
-- live in this one module and a bare 'linkTo' per type would collide with its own siblings,
-- not just with 'Yield.chs'\/'Quote.chs'.
{#fun qlRelinkableSwaptionVolatilityStructureLinkTo as linkSwaptionVolTo{withRelinkableSwaptionVolatilityStructure*`RelinkableSwaptionVolatilityStructure'
  ,withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv',preErrorCheck-`String'errorCheck*-}->`()'#}

-- |A constant local volatility, no time-asset dependence -- floating reference date, floating
-- market data. Local and Black volatility coincide when volatility is at most time dependent, so
-- this is effectively a proxy for 'blackConstantVol''.
{#fun qlLocalConstantVol1 as localConstantVol'{fromIntegral`Word',withCalendar*`Calendar',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`LocalVolTermStructure'peekLocalVolTermStructure*#}

-- |as 'localConstantVol\'', but a fixed reference date
{#fun qlLocalConstantVol as localConstantVol{withDay*`Day',withQuote*`GenQuote q',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`LocalVolTermStructure'peekLocalVolTermStructure*#}

-- |a local vol term structure derived from a 'BlackVarianceCurve' (no strike dependence): local
-- vol at time @t@ is the derivative of the Black variance curve's total variance
{#fun qlLocalVolCurve as localVolCurve{withBlackVarianceCurve*`BlackVarianceCurve',preErrorCheck-`String'errorCheck*-}->`LocalVolTermStructure'peekLocalVolTermStructure*#}

-- |@origTS@ re-anchored to a new reference date, tracking @origTS@ for later changes. Only
-- financially sensible for a time-dependent (not asset-dependent) source structure.
{#fun qlImpliedVolTermStructure as impliedVolTermStructure{withBlackVolTermStructure*`GenBlackVolTermStructure bv',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`BlackVolTermStructure'peekBlackVolTermStructure*#}

-- |fixed reference date, floating market data
capFloorTermVolCurve' :: Day -> Calendar -> BusinessDayConvention -> NonEmpty (Word, TimeUnit, GenQuote q) -> DayCounter -> IO CapFloorTermVolCurve
capFloorTermVolCurve' d c bd ntq = qlCapFloorTermVolCurve1 d c bd n t q where (n, t, q) = unzip3 (toList ntq)
{#fun qlCapFloorTermVolCurve1{withDay*`Day',withCalendar*`Calendar',fromEnumC`BusinessDayConvention',withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&,withQuoteArray*`[GenQuote q]'&,withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`CapFloorTermVolCurve'peekCapFloorTermVolCurve*#}

-- |floating reference date, floating market data
capFloorTermVolCurve :: Word -> Calendar -> BusinessDayConvention -> NonEmpty (Word, TimeUnit, GenQuote q) -> DayCounter -> IO CapFloorTermVolCurve
capFloorTermVolCurve d c bd ntq = qlCapFloorTermVolCurve d c bd n t q where (n, t, q) = unzip3 (toList ntq)
{#fun qlCapFloorTermVolCurve{fromIntegral`Word',withCalendar*`Calendar',fromEnumC`BusinessDayConvention',withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&,withQuoteArray*`[GenQuote q]'&,withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`CapFloorTermVolCurve'peekCapFloorTermVolCurve*#}

-- |A Black volatility curve built from time-dependent (ATM) market vols, interpolating on total
-- variance (linear by default, or the given 'Interpolation') -- no strike dependence; see
-- 'blackVarianceSurface' for that.
blackVarianceCurve :: Day -> NonEmpty (Day, Double) -> DayCounter -> Bool -- ^forceMonotoneVariance
  -> Maybe Interpolation -> IO BlackVarianceCurve
blackVarianceCurve d dq dc f i = uncurryNested (qlBlackVarianceCurve d dd q dc f) (qlInterpolation' i) where (dd, q) = unzip (toList dq)
{#fun qlBlackVarianceCurve{withDay*`Day',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,withDayCounter*`DayCounter',`Bool',`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`BlackVarianceCurve'peekBlackVarianceCurve*#}

-- |The @interpolator@ is applied through @BlackVarianceSurface::setInterpolation@ right after
-- construction; 'Bilinear' reproduces upstream's default. Both interpolators reproduce
-- @blackVolMatrix@ exactly at its own (date, strike) nodes -- they only differ between them.
blackVarianceSurface :: Day -> Calendar -> [Day] -- ^dates
  -> [Double] -- ^strikes
  -> RealMatrix -- ^blackVolMatrix
  -> DayCounter
  -> BlackVarianceSurfaceExtrapolation -- ^lowerExtrapolation
  -> BlackVarianceSurfaceExtrapolation -- ^upperExtrapolation
  -> Interpolation2D -- ^interpolator
  -> IO BlackVolTermStructure
blackVarianceSurface d c ds s (RealMatrix mr mc md) = qlBlackVarianceSurface d c ds s mr mc md
{#fun qlBlackVarianceSurface{withDay*`Day',withCalendar*`Calendar',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,fromIntegral`Word',fromIntegral`Word',withRealVectorRaw*`RealVector',withDayCounter*`DayCounter',`BlackVarianceSurfaceExtrapolation',`BlackVarianceSurfaceExtrapolation',fromEnumC`Interpolation2D',preErrorCheck-`String'errorCheck*-}->`BlackVolTermStructure'peekBlackVolTermStructure*#}

-- |Builds a Black volatility surface from a rectangular vol grid via
-- 'PiecewiseBlackVarianceSurface::makeFromGrid': one interpolated smile section per date
-- column, linear in total variance between columns -- a fixed interpolation scheme, unlike
-- 'blackVarianceSurface''s configurable 2-D interpolator.
piecewiseBlackVarianceSurface :: Day -> [Day] -- ^dates
  -> [Double] -- ^strikes
  -> RealMatrix -- ^blackVols
  -> DayCounter
  -> IO BlackVolTermStructure
piecewiseBlackVarianceSurface d ds s (RealMatrix mr mc md) dc = qlPiecewiseBlackVarianceSurface d ds s mr mc md dc
{#fun qlPiecewiseBlackVarianceSurface{withDay*`Day',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,fromIntegral`Word',fromIntegral`Word',withRealVectorRaw*`RealVector',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`BlackVolTermStructure'peekBlackVolTermStructure*#}

-- |A Black volatility surface parameterized by market deltas (put\/call deltas and, optionally,
-- an ATM quote) rather than fixed strikes -- the standard FX vol quoting convention. Constructed
-- with upstream's own defaults for the trailing options; use 'blackVolatilitySurfaceDeltaFull'
-- to override them.
blackVolatilitySurfaceDelta :: Day -> [Day] -- ^dates
  -> [Double] -- ^putDeltas
  -> [Double] -- ^callDeltas
  -> Bool -- ^hasAtm
  -> RealMatrix -- ^blackVolMatrix
  -> DayCounter -> Calendar -> GenQuote q -- ^spot
  -> GenYieldTermStructure y1 -- ^domesticTS
  -> GenYieldTermStructure y2 -- ^foreignTS
  -> IO BlackVolatilitySurfaceDelta
blackVolatilitySurfaceDelta d ds pd cd hasAtm (RealMatrix mr mc md) dc cal spot dts fts =
  blackVolatilitySurfaceDelta_ d ds pd cd hasAtm mr mc md dc cal spot dts fts
    Spot AtmDeltaNeutral Nothing SmileLinear False FlatVolatility (0, Days) Fwd AtmDeltaNeutral Nothing

-- |As 'blackVolatilitySurfaceDelta', but takes a 'BlackVolatilitySurfaceDeltaOpts' record for
-- the trailing options instead of hardcoding upstream's defaults.
blackVolatilitySurfaceDeltaFull :: Day -> [Day] -> [Double] -> [Double] -> Bool -> RealMatrix
  -> DayCounter -> Calendar -> GenQuote q -> GenYieldTermStructure y1 -> GenYieldTermStructure y2
  -> BlackVolatilitySurfaceDeltaOpts -> IO BlackVolatilitySurfaceDelta
blackVolatilitySurfaceDeltaFull d ds pd cd hasAtm (RealMatrix mr mc md) dc cal spot dts fts opts =
  blackVolatilitySurfaceDelta_ d ds pd cd hasAtm mr mc md dc cal spot dts fts
    (bvsdDeltaType opts) (bvsdAtmType opts) (bvsdAtmDeltaType opts)
    (bvsdInterpolationMethod opts) (bvsdFlatStrikeExtrapolation opts) (bvsdTimeExtrapolationType opts)
    (bvsdSwitchTenor opts) (bvsdLongTermDeltaType opts) (bvsdLongTermAtmType opts) (bvsdLongTermAtmDeltaType opts)

{#fun qlBlackVolatilitySurfaceDelta as blackVolatilitySurfaceDelta_{withDay*`Day',withDayArray*`[Day]'&
  ,withDoubleArray*`[Double]'& -- ^putDeltas
  ,withDoubleArray*`[Double]'& -- ^callDeltas
  ,`Bool' -- ^hasAtm
  ,fromIntegral`Word',fromIntegral`Word',withRealVectorRaw*`RealVector' -- ^blackVolMatrix
  ,withDayCounter*`DayCounter',withCalendar*`Calendar',withQuote*`GenQuote q' -- ^spot
  ,withYieldTermStructure*`GenYieldTermStructure y1' -- ^domesticTS
  ,withYieldTermStructure*`GenYieldTermStructure y2' -- ^foreignTS
  ,fromEnumC`DeltaType' -- ^deltaType
  ,fromEnumC`AtmType' -- ^atmType
  ,fromMaybeEnum`Maybe DeltaType' -- ^atmDeltaType
  ,fromEnumC`SmileInterpolationMethod' -- ^interpolationMethod
  ,`Bool' -- ^flatStrikeExtrapolation
  ,fromEnumC`BlackVolTimeExtrapolationType' -- ^timeExtrapolationType
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^switchTenor
  ,fromEnumC`DeltaType' -- ^longTermDeltaType
  ,fromEnumC`AtmType' -- ^longTermAtmType
  ,fromMaybeEnum`Maybe DeltaType' -- ^longTermAtmDeltaType
  ,preErrorCheck-`String'errorCheck*-}->`BlackVolatilitySurfaceDelta'peekBlackVolatilitySurfaceDelta*#}

-- |The Black vol smile at a given time to expiry (year fraction from the reference date), built
-- by interpolating\/extrapolating the delta-quoted surface. The returned 'SmileSection' does not
-- track later changes to the surface's spot\/curve handles -- recreate it if those change.
{#fun qlBlackVolatilitySurfaceDeltaSmile1 as blackVolSmile{withBlackVolatilitySurfaceDelta*`BlackVolatilitySurfaceDelta'
  ,`Double' -- ^t
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |As 'blackVolSmile', for a given expiry 'Day' instead of a year fraction.
{#fun qlBlackVolatilitySurfaceDeltaSmile as blackVolSmile'{withBlackVolatilitySurfaceDelta*`BlackVolatilitySurfaceDelta'
  ,withDay*`Day' -- ^d
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |floating reference date, floating market data
capFloorTermVolSurface :: Word -> Calendar -> BusinessDayConvention -> [(Word, TimeUnit)] -- ^optionTenors
  -> [Double] -- ^strikes
  -> Matrix (GenQuote q) -- ^volatilities
  -> DayCounter -> IO CapFloorTermVolSurface
capFloorTermVolSurface d c bd t s (Matrix mr mc md) = qlCapFloorTermVolSurface d c bd pl pu s mr mc md where (pl, pu) = unzip t
{#fun qlCapFloorTermVolSurface{fromIntegral`Word',withCalendar*`Calendar',fromEnumC`BusinessDayConvention',withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&,withDoubleArray*`[Double]'&,fromIntegral`Word',fromIntegral`Word',withQuoteArrayRaw*`[GenQuote q]',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`CapFloorTermVolSurface'peekCapFloorTermVolSurface*#}

-- |fixed reference date, floating market data
capFloorTermVolSurface' :: Day -> Calendar -> BusinessDayConvention -> [(Word, TimeUnit)] -- ^optionTenors
  -> [Double] -- ^strikes
  -> Matrix (GenQuote q) -- ^volatilities
  -> DayCounter -> IO CapFloorTermVolSurface
capFloorTermVolSurface' d c bd t s (Matrix mr mc md) = qlCapFloorTermVolSurface1 d c bd pl pu s mr mc md where (pl, pu) = unzip t
{#fun qlCapFloorTermVolSurface1{withDay*`Day',withCalendar*`Calendar',fromEnumC`BusinessDayConvention',withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&,withDoubleArray*`[Double]'&,fromIntegral`Word',fromIntegral`Word',withQuoteArrayRaw*`[GenQuote q]',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`CapFloorTermVolSurface'peekCapFloorTermVolSurface*#}

-- |fixed reference date, floating market data. Pass an empty 'RealMatrix'
-- (@realMatrixFromVector 0 0 Data.Vector.Storable.empty@) for @shifts@
-- when no shift is needed -- upstream treats a zero-row shift matrix as all-zero.
swaptionVolatilityMatrix' :: Day -> Calendar -> BusinessDayConvention
  -> [(Word, TimeUnit)] -- ^optionTenors
  -> [(Word, TimeUnit)] -- ^swapTenors
  -> Matrix (GenQuote q) -- ^volatilities
  -> DayCounter
  -> Bool -- ^flatExtrapolation
  -> VolatilityType
  -> RealMatrix -- ^shifts
  -> IO SwaptionVolatilityStructure
swaptionVolatilityMatrix' d c bdc ot st (Matrix vr vc vd) dc' fe ty (RealMatrix sr sc sd) =
  qlSwaptionVolatilityMatrix d c bdc opl opu spl spu vr vc vd dc' fe ty sr sc sd
  where (opl, opu) = unzip ot; (spl, spu) = unzip st
{#fun qlSwaptionVolatilityMatrix{withDay*`Day',withCalendar*`Calendar',fromEnumC`BusinessDayConvention'
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&
  ,fromIntegral`Word',fromIntegral`Word',withQuoteArrayRaw*`[GenQuote q]'
  ,withDayCounter*`DayCounter',`Bool',`VolatilityType'
  ,fromIntegral`Word',fromIntegral`Word',withRealVectorRaw*`RealVector'
  ,preErrorCheck-`String'errorCheck*-}->`SwaptionVolatilityStructure'peekSwaptionVolatilityStructure*#}

-- |floating reference date, floating market data. See 'swaptionVolatilityMatrix\'' for the
-- @shifts@ convention
-- (@realMatrixFromVector 0 0 Data.Vector.Storable.empty@ for "no shift").
swaptionVolatilityMatrix :: Calendar -> BusinessDayConvention
  -> [(Word, TimeUnit)] -- ^optionTenors
  -> [(Word, TimeUnit)] -- ^swapTenors
  -> Matrix (GenQuote q) -- ^volatilities
  -> DayCounter
  -> Bool -- ^flatExtrapolation
  -> VolatilityType
  -> RealMatrix -- ^shifts
  -> IO SwaptionVolatilityStructure
swaptionVolatilityMatrix c bdc ot st (Matrix vr vc vd) dc' fe ty (RealMatrix sr sc sd) =
  qlSwaptionVolatilityMatrix1 c bdc opl opu spl spu vr vc vd dc' fe ty sr sc sd
  where (opl, opu) = unzip ot; (spl, spu) = unzip st
{#fun qlSwaptionVolatilityMatrix1{withCalendar*`Calendar',fromEnumC`BusinessDayConvention'
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&
  ,fromIntegral`Word',fromIntegral`Word',withQuoteArrayRaw*`[GenQuote q]'
  ,withDayCounter*`DayCounter',`Bool',`VolatilityType'
  ,fromIntegral`Word',fromIntegral`Word',withRealVectorRaw*`RealVector'
  ,preErrorCheck-`String'errorCheck*-}->`SwaptionVolatilityStructure'peekSwaptionVolatilityStructure*#}

-- |A SABR-calibrated swaption volatility cube: fits a SABR smile at every (option tenor, swap
-- tenor) node from an ATM surface plus a grid of vol spreads. The result /is/ a
-- 'SwaptionVolatilityStructure' -- pass it anywhere one is expected (pricing engines,
-- 'smileSection'\/'volatilityForPeriod''\/etc.) -- but its own extra getters
-- ('sparseSabrParameters', 'denseSabrParameters', 'marketVolCube', 'volCubeAtmCalibrated',
-- 'sabrSwaptionVolatilityCubeAtmStrike'\/'\'') only accept this concrete type, not the generic one.
--
-- @endCriteria@\/@optMethod@ default to 'Nothing', which falls back to upstream's own internal
-- Levenberg-Marquardt\/EndCriteria defaults at every calibrated node. A caller-supplied
-- 'EndCriteria'\/'OptimizationMethod' is safe here since both are @shared_ptr@-boxed on the C++
-- side (see the qlaux.h comment above the QlEndCriteria\/QlOptimizationMethod typedefs) -- the
-- copy 'SabrSwaptionVolatilityCube' keeps as its own @shared_ptr@ member survives regardless of
-- when Haskell's own handle is collected, same as 'sabrInterpolatedSmileSection' and
-- 'QuantLib.TermStructure.Yield.fittedBondDiscountCurve''s fitting methods.
--
-- @volSpreads@ and @parametersGuess@ are both flattened over the (optionTenor x swapTenor)
-- product as the *outer* index (row = j*nSwapTenors+k, j over @optionTenors@, k over
-- @swapTenors@) -- not one row per @optionTenor@ the way 'swaptionVolatilityMatrix'''s grid is:
-- @matrixRows == length optionTenors * length swapTenors@ for both. @volSpreads@'s columns are
-- one per @strikeSpreads@ entry; @parametersGuess@'s columns are always exactly 4, in order
-- alpha\/beta\/nu\/rho.
--
-- Calibration is lazy: unlike 'sabrInterpolatedSmileSection', construction here does /not/ force
-- an eager fit, so this call can succeed even for inputs that will later fail to calibrate -- the
-- error only surfaces on the first 'smileSection'\/'volatilityForPeriod''\/diagnostic call.
sabrSwaptionVolatilityCube :: GenSwaptionVolatilityStructure sv -- ^atmVolStructure
  -> [(Word, TimeUnit)] -- ^optionTenors
  -> [(Word, TimeUnit)] -- ^swapTenors
  -> [Double] -- ^strikeSpreads
  -> Matrix (GenQuote q1) -- ^volSpreads
  -> GenSwapIndex sidx1 -- ^swapIndexBase
  -> GenSwapIndex sidx2 -- ^shortSwapIndexBase
  -> Bool -- ^vegaWeightedSmileFit
  -> Matrix (GenQuote q2) -- ^parametersGuess (alpha, beta, nu, rho per node)
  -> Bool -- ^isAlphaFixed
  -> Bool -- ^isBetaFixed
  -> Bool -- ^isNuFixed
  -> Bool -- ^isRhoFixed
  -> Bool -- ^isAtmCalibrated: if 'True', @atmVolStructure@ must be a discrete grid structure
  -- (e.g. 'swaptionVolatilityMatrix'' or another cube) -- upstream's ATM-recalibration path
  -- ('denseSabrParameters'\/one branch of 'volCubeAtmCalibrated') downcasts it to
  -- @SwaptionVolatilityDiscrete@ and dereferences the result unchecked, which crashes given a
  -- flat 'constantSwaptionVolatility'\/'\''.
  -> Maybe Double -- ^maxErrorTolerance
  -> Maybe Double -- ^errorAccept
  -> Bool -- ^useMaxError
  -> Word -- ^maxGuesses
  -> Bool -- ^backwardFlat
  -> Double -- ^cutoffStrike
  -> Maybe EndCriteria -- ^endCriteria
  -> Maybe OptimizationMethod -- ^optMethod
  -> IO SabrSwaptionVolatilityCube
sabrSwaptionVolatilityCube atm ot st ss (Matrix vr vc vd) sidx1 sidx2 vw (Matrix pr pc pd)
  iaf ibf inf irf iac met eat ume mg bf cs ec om =
  qlSabrSwaptionVolatilityCube atm opl opu spl spu ss vr vc vd sidx1 sidx2 vw pr pc pd
    iaf ibf inf irf iac ec om met eat ume mg bf cs
  where (opl, opu) = unzip ot; (spl, spu) = unzip st
{#fun qlSabrSwaptionVolatilityCube{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&
  ,withDoubleArray*`[Double]'&
  ,fromIntegral`Word',fromIntegral`Word',withQuoteArrayRaw*`[GenQuote q1]'
  ,withSwapIndex*`GenSwapIndex sidx1',withSwapIndex*`GenSwapIndex sidx2'
  ,`Bool'
  ,fromIntegral`Word',fromIntegral`Word',withQuoteArrayRaw*`[GenQuote q2]'
  ,`Bool',`Bool',`Bool',`Bool'
  ,`Bool'
  ,withMaybeEndCriteria*`Maybe EndCriteria'
  ,withMaybeOptimizationMethod*`Maybe OptimizationMethod'
  ,fromMaybeDouble`Maybe Double',fromMaybeDouble`Maybe Double',`Bool',fromIntegral`Word'
  ,`Bool',`Double'
  ,preErrorCheck-`String'errorCheck*-}->`SabrSwaptionVolatilityCube'peekSabrSwaptionVolatilityCube*#}

-- |An arbitrage-free SABR (Doust) swaption volatility cube: the same
-- @XabrSwaptionVolatilityCube@ construction as 'sabrSwaptionVolatilityCube', one model policy
-- over -- fits an arbitrage-free SABR smile (via 'NoArbSabrModel') at every node instead of the
-- Hagan-formula SABR smile. Same argument shapes, flattening conventions, lazy calibration, and
-- 'EndCriteria'\/'OptimizationMethod' safety as 'sabrSwaptionVolatilityCube'; its own extra
-- getters ('noArbSabrSparseSabrParameters', 'noArbSabrDenseSabrParameters',
-- 'noArbSabrMarketVolCube', 'noArbSabrVolCubeAtmCalibrated',
-- 'noArbSabrSwaptionVolatilityCubeAtmStrike'\/'\'') only accept this concrete type.
noArbSabrSwaptionVolatilityCube :: GenSwaptionVolatilityStructure sv -- ^atmVolStructure
  -> [(Word, TimeUnit)] -- ^optionTenors
  -> [(Word, TimeUnit)] -- ^swapTenors
  -> [Double] -- ^strikeSpreads
  -> Matrix (GenQuote q1) -- ^volSpreads
  -> GenSwapIndex sidx1 -- ^swapIndexBase
  -> GenSwapIndex sidx2 -- ^shortSwapIndexBase
  -> Bool -- ^vegaWeightedSmileFit
  -> Matrix (GenQuote q2) -- ^parametersGuess (alpha, beta, nu, rho per node)
  -> Bool -- ^isAlphaFixed
  -> Bool -- ^isBetaFixed
  -> Bool -- ^isNuFixed
  -> Bool -- ^isRhoFixed
  -> Bool -- ^isAtmCalibrated, see 'sabrSwaptionVolatilityCube'
  -> Maybe Double -- ^maxErrorTolerance
  -> Maybe Double -- ^errorAccept
  -> Bool -- ^useMaxError
  -> Word -- ^maxGuesses
  -> Bool -- ^backwardFlat
  -> Double -- ^cutoffStrike
  -> Maybe EndCriteria -- ^endCriteria
  -> Maybe OptimizationMethod -- ^optMethod
  -> IO NoArbSabrSwaptionVolatilityCube
noArbSabrSwaptionVolatilityCube atm ot st ss (Matrix vr vc vd) sidx1 sidx2 vw (Matrix pr pc pd)
  iaf ibf inf irf iac met eat ume mg bf cs ec om =
  qlNoArbSabrSwaptionVolatilityCube atm opl opu spl spu ss vr vc vd sidx1 sidx2 vw pr pc pd
    iaf ibf inf irf iac ec om met eat ume mg bf cs
  where (opl, opu) = unzip ot; (spl, spu) = unzip st
{#fun qlNoArbSabrSwaptionVolatilityCube{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&
  ,withDoubleArray*`[Double]'&
  ,fromIntegral`Word',fromIntegral`Word',withQuoteArrayRaw*`[GenQuote q1]'
  ,withSwapIndex*`GenSwapIndex sidx1',withSwapIndex*`GenSwapIndex sidx2'
  ,`Bool'
  ,fromIntegral`Word',fromIntegral`Word',withQuoteArrayRaw*`[GenQuote q2]'
  ,`Bool',`Bool',`Bool',`Bool'
  ,`Bool'
  ,withMaybeEndCriteria*`Maybe EndCriteria'
  ,withMaybeOptimizationMethod*`Maybe OptimizationMethod'
  ,fromMaybeDouble`Maybe Double',fromMaybeDouble`Maybe Double',`Bool',fromIntegral`Word'
  ,`Bool',`Double'
  ,preErrorCheck-`String'errorCheck*-}->`NoArbSabrSwaptionVolatilityCube'peekNoArbSabrSwaptionVolatilityCube*#}

-- |The non-SABR, linear-interpolation swaption volatility cube: interpolates the given
-- @volSpreads@ rather than calibrating a smile model. No 'EndCriteria'\/'OptimizationMethod'
-- hazard here -- this class never calibrates anything. See 'sabrSwaptionVolatilityCube' for the
-- @volSpreads@ flattening convention (identical here, minus @parametersGuess@).
interpolatedSwaptionVolatilityCube :: GenSwaptionVolatilityStructure sv -- ^atmVolStructure
  -> [(Word, TimeUnit)] -- ^optionTenors
  -> [(Word, TimeUnit)] -- ^swapTenors
  -> [Double] -- ^strikeSpreads
  -> Matrix (GenQuote q) -- ^volSpreads
  -> GenSwapIndex sidx1 -- ^swapIndexBase
  -> GenSwapIndex sidx2 -- ^shortSwapIndexBase
  -> Bool -- ^vegaWeightedSmileFit
  -> IO InterpolatedSwaptionVolatilityCube
interpolatedSwaptionVolatilityCube atm ot st ss (Matrix vr vc vd) sidx1 sidx2 vw =
  qlInterpolatedSwaptionVolatilityCube atm opl opu spl spu ss vr vc vd sidx1 sidx2 vw
  where (opl, opu) = unzip ot; (spl, spu) = unzip st
{#fun qlInterpolatedSwaptionVolatilityCube{withSwaptionVolatilityStructure*`GenSwaptionVolatilityStructure sv'
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&
  ,withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&
  ,withDoubleArray*`[Double]'&
  ,fromIntegral`Word',fromIntegral`Word',withQuoteArrayRaw*`[GenQuote q]'
  ,withSwapIndex*`GenSwapIndex sidx1',withSwapIndex*`GenSwapIndex sidx2'
  ,`Bool'
  ,preErrorCheck-`String'errorCheck*-}->`InterpolatedSwaptionVolatilityCube'peekInterpolatedSwaptionVolatilityCube*#}

toRealMatrix :: (Word, Word, RealVector) -> RealMatrix
toRealMatrix (r, c, d) = RealMatrix r c d

-- |Per-node calibrated SABR parameters (alpha, beta, nu, rho columns) before ATM recalibration.
sparseSabrParameters :: SabrSwaptionVolatilityCube -> IO RealMatrix
sparseSabrParameters sv = toRealMatrix <$> qlSabrSwaptionVolatilityCubeSparseSabrParameters sv
{#fun qlSabrSwaptionVolatilityCubeSparseSabrParameters{withSabrSwaptionVolatilityCube*`SabrSwaptionVolatilityCube'
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`RealVector'&peekRealVector*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-node calibrated SABR parameters, meaningfully populated only when the cube was built with
-- @isAtmCalibrated = True@ (see 'sabrSwaptionVolatilityCube').
denseSabrParameters :: SabrSwaptionVolatilityCube -> IO RealMatrix
denseSabrParameters sv = toRealMatrix <$> qlSabrSwaptionVolatilityCubeDenseSabrParameters sv
{#fun qlSabrSwaptionVolatilityCubeDenseSabrParameters{withSabrSwaptionVolatilityCube*`SabrSwaptionVolatilityCube'
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`RealVector'&peekRealVector*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |The raw market vol grid the cube's SABR fit targets: ATM vol (interpolated from
-- @atmVolStructure@ at each node) plus @volSpreads@.
marketVolCube :: SabrSwaptionVolatilityCube -> IO RealMatrix
marketVolCube sv = toRealMatrix <$> qlSabrSwaptionVolatilityCubeMarketVolCube sv
{#fun qlSabrSwaptionVolatilityCubeMarketVolCube{withSabrSwaptionVolatilityCube*`SabrSwaptionVolatilityCube'
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`RealVector'&peekRealVector*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Like 'marketVolCube', adjusted so the cube's own ATM row is consistent with @atmVolStructure@;
-- meaningfully populated only when the cube was built with @isAtmCalibrated = True@.
volCubeAtmCalibrated :: SabrSwaptionVolatilityCube -> IO RealMatrix
volCubeAtmCalibrated sv = toRealMatrix <$> qlSabrSwaptionVolatilityCubeVolCubeAtmCalibrated sv
{#fun qlSabrSwaptionVolatilityCubeVolCubeAtmCalibrated{withSabrSwaptionVolatilityCube*`SabrSwaptionVolatilityCube'
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`RealVector'&peekRealVector*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |ATM strike at a given (option date, swap tenor) node.
{#fun qlSabrSwaptionVolatilityCubeAtmStrike1 as sabrSwaptionVolatilityCubeAtmStrike'{withSabrSwaptionVolatilityCube*`SabrSwaptionVolatilityCube'
  ,withDay*`Day' -- ^optionDate
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |ATM strike at a given (option tenor, swap tenor) node, see 'sabrSwaptionVolatilityCubeAtmStrike\''
{#fun qlSabrSwaptionVolatilityCubeAtmStrike as sabrSwaptionVolatilityCubeAtmStrike{withSabrSwaptionVolatilityCube*`SabrSwaptionVolatilityCube'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Per-node calibrated no-arb SABR parameters (alpha, beta, nu, rho columns) before ATM
-- recalibration, see 'sparseSabrParameters'.
noArbSabrSparseSabrParameters :: NoArbSabrSwaptionVolatilityCube -> IO RealMatrix
noArbSabrSparseSabrParameters sv = toRealMatrix <$> qlNoArbSabrSwaptionVolatilityCubeSparseSabrParameters sv
{#fun qlNoArbSabrSwaptionVolatilityCubeSparseSabrParameters{withNoArbSabrSwaptionVolatilityCube*`NoArbSabrSwaptionVolatilityCube'
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`RealVector'&peekRealVector*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Per-node calibrated no-arb SABR parameters, meaningfully populated only when the cube was
-- built with @isAtmCalibrated = True@, see 'denseSabrParameters'.
noArbSabrDenseSabrParameters :: NoArbSabrSwaptionVolatilityCube -> IO RealMatrix
noArbSabrDenseSabrParameters sv = toRealMatrix <$> qlNoArbSabrSwaptionVolatilityCubeDenseSabrParameters sv
{#fun qlNoArbSabrSwaptionVolatilityCubeDenseSabrParameters{withNoArbSabrSwaptionVolatilityCube*`NoArbSabrSwaptionVolatilityCube'
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`RealVector'&peekRealVector*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |The raw market vol grid the cube's no-arb SABR fit targets, see 'marketVolCube'.
noArbSabrMarketVolCube :: NoArbSabrSwaptionVolatilityCube -> IO RealMatrix
noArbSabrMarketVolCube sv = toRealMatrix <$> qlNoArbSabrSwaptionVolatilityCubeMarketVolCube sv
{#fun qlNoArbSabrSwaptionVolatilityCubeMarketVolCube{withNoArbSabrSwaptionVolatilityCube*`NoArbSabrSwaptionVolatilityCube'
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`RealVector'&peekRealVector*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Like 'noArbSabrMarketVolCube', adjusted so the cube's own ATM row is consistent with
-- @atmVolStructure@; meaningfully populated only when the cube was built with
-- @isAtmCalibrated = True@, see 'volCubeAtmCalibrated'.
noArbSabrVolCubeAtmCalibrated :: NoArbSabrSwaptionVolatilityCube -> IO RealMatrix
noArbSabrVolCubeAtmCalibrated sv = toRealMatrix <$> qlNoArbSabrSwaptionVolatilityCubeVolCubeAtmCalibrated sv
{#fun qlNoArbSabrSwaptionVolatilityCubeVolCubeAtmCalibrated{withNoArbSabrSwaptionVolatilityCube*`NoArbSabrSwaptionVolatilityCube'
  ,prePtr-`Word'peekWord*,prePtr-`Word'peekWord*,preArray-`RealVector'&peekRealVector*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |ATM strike at a given (option date, swap tenor) node, see 'sabrSwaptionVolatilityCubeAtmStrike\''.
{#fun qlNoArbSabrSwaptionVolatilityCubeAtmStrike1 as noArbSabrSwaptionVolatilityCubeAtmStrike'{withNoArbSabrSwaptionVolatilityCube*`NoArbSabrSwaptionVolatilityCube'
  ,withDay*`Day' -- ^optionDate
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |ATM strike at a given (option tenor, swap tenor) node, see 'noArbSabrSwaptionVolatilityCubeAtmStrike\''
{#fun qlNoArbSabrSwaptionVolatilityCubeAtmStrike as noArbSabrSwaptionVolatilityCubeAtmStrike{withNoArbSabrSwaptionVolatilityCube*`NoArbSabrSwaptionVolatilityCube'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |ATM strike at a given (option date, swap tenor) node.
{#fun qlInterpolatedSwaptionVolatilityCubeAtmStrike1 as interpolatedSwaptionVolatilityCubeAtmStrike'{withInterpolatedSwaptionVolatilityCube*`InterpolatedSwaptionVolatilityCube'
  ,withDay*`Day' -- ^optionDate
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |ATM strike at a given (option tenor, swap tenor) node, see
-- 'interpolatedSwaptionVolatilityCubeAtmStrike\''
{#fun qlInterpolatedSwaptionVolatilityCubeAtmStrike as interpolatedSwaptionVolatilityCubeAtmStrike{withInterpolatedSwaptionVolatilityCube*`InterpolatedSwaptionVolatilityCube'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
