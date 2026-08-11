{-# LANGUAGE TemplateHaskell #-}
module QuantLib.TermStructure.Volatility
  (
    BlackVarianceSurfaceExtrapolation
  , ExtendedBlackVarianceSurfaceExtrapolation

  , BlackVarianceCurve
  , BlackVolTermStructure
  , GenBlackVolTermStructure
  , CallableBondVolatilityStructure
  , CapFloorTermVolSurface
  , LocalVolTermStructure
  , OptionletVolatilityStructure
  , SmileSection
  , SwaptionVolatilityStructure
  , VolatilityTermStructure
  , GenVolatilityTermStructure

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
  , sabrSmileSection
  , smileSectionVolatility
  , smileSectionVariance
  , SabrInterpolatedSmileSectionOpts(..)
  , defaultSabrInterpolatedSmileSectionOpts
  , sabrInterpolatedSmileSection
  , sabrInterpolatedSmileSectionAlpha
  , sabrInterpolatedSmileSectionBeta
  , sabrInterpolatedSmileSectionNu
  , sabrInterpolatedSmileSectionRho
  , sabrInterpolatedSmileSectionRmsError
  , sabrInterpolatedSmileSectionMaxError
  , sabrInterpolatedSmileSectionEndCriteria
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
  ) where
import QuantLib.Internal
{#import QuantLib.Time.Calendar#}(BusinessDayConvention)
{#import QuantLib.InterestRate#}(VolatilityType)
{#import QuantLib.Math#}(EndCriteriaType)
import QuantLib.Internal.Type
import QuantLib.Internal.Enum
import QuantLib.Internal.Syntax(deriveOptionsRecord)
import QuantLib.Time.Schedule(dayCounter, DayCounterConstructor(..))

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "ql.h"
#include "qlEnumObjects.h"

{#pointer *DayCounter foreign -> CDayCounter nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlSmileSection as SmileSection foreign -> CSmileSection nocode#}

{#pointer *QlVolatilityTermStructure as VolatilityTermStructure foreign -> CVolatilityTermStructure' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlTermStructure as TermStructure foreign -> CTermStructure' nocode#}
{#pointer *QlOptionletVolatilityStructure as OptionletVolatilityStructure foreign -> COptionletVolatilityStructure' nocode#}
{#pointer *QlLocalVolTermStructure as LocalVolTermStructure foreign -> CLocalVolTermStructure' nocode#}
{#pointer *QlBlackVarianceCurve as BlackVarianceCurve foreign -> CBlackVarianceCurve' nocode#}
{#pointer *QlBlackVolTermStructure as BlackVolTermStructure foreign -> CBlackVolTermStructure' nocode#}
{#pointer *QlCallableBondVolatilityStructure as CallableBondVolatilityStructure foreign -> CCallableBondVolatilityStructure' nocode#}
{#pointer *QlCapFloorTermVolSurface as CapFloorTermVolSurface foreign -> CCapFloorTermVolSurface' nocode#}
{#pointer *QlSwaptionVolatilityStructure as SwaptionVolatilityStructure foreign -> CSwaptionVolatilityStructure' nocode#}

{#enum BlackVarianceSurfaceExtrapolation{} deriving(Show, Eq)#}
{#enum ExtendedBlackVarianceSurfaceExtrapolation{} deriving(Show, Eq)#}

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
  , ("sabrDayCounter", [t|Maybe DayCounter|], [|Nothing|])
  , ("sabrShift", [t|Double|], [|0.0|])
  ])

{#fun qlLocalVolSurface as localVolSurface{withBlackVolTermStructure*`GenBlackVolTermStructure v'
  ,withYieldTermStructure*`GenYieldTermStructure b' -- ^riskFreeTS
  ,withYieldTermStructure*`GenYieldTermStructure c' -- ^dividendTS
  ,withQuote*`GenQuote a' -- ^underlying
  ,preErrorCheck-`String'errorCheck*-}->`LocalVolTermStructure'peekLocalVolTermStructure*#}

-- |Constant caplet volatility, no time-strike dependence
-- floating reference date, floating market data
{#fun qlConstantOptionletVol1 as constantOptionletVolatility'{fromIntegral`Word',withCalendar*`Calendar',`BusinessDayConvention',withQuote*`GenQuote a',withDayCounter*`DayCounter'
  ,`VolatilityType' -- ^type
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`OptionletVolatilityStructure'peekOptionletVolatilityStructure*#}

-- |fixed reference date, floating market data
{#fun qlConstantOptionletVolatility as constantOptionletVolatility{withDay*`Day',withCalendar*`Calendar',`BusinessDayConvention',withQuote*`GenQuote a',withDayCounter*`DayCounter'
  ,`VolatilityType' -- ^type
  ,`Double' -- ^displacement
  ,preErrorCheck-`String'errorCheck*-}->`OptionletVolatilityStructure'peekOptionletVolatilityStructure*#}
{#fun qlBlackConstantVol1 as blackConstantVol'{fromIntegral`Word',withCalendar*`Calendar',withQuote*`GenQuote a',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`BlackVolTermStructure'peekBlackVolTermStructure*#}
{#fun qlBlackConstantVol as blackConstantVol{withDay*`Day',withCalendar*`Calendar',withQuote*`GenQuote a',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`BlackVolTermStructure'peekBlackVolTermStructure*#}

-- |fixed reference date, floating market data
{#fun qlConstantSwaptionVolatility1 as constantSwaptionVolatility'{withDay*`Day',withCalendar*`Calendar',`BusinessDayConvention',withQuote*`GenQuote a',withDayCounter*`DayCounter'
  ,`VolatilityType' -- ^type
  ,`Double' -- ^shift
  ,preErrorCheck-`String'errorCheck*-}->`SwaptionVolatilityStructure'peekSwaptionVolatilityStructure*#}
-- |floating reference date, floating market data
{#fun qlConstantSwaptionVolatility as constantSwaptionVolatility{fromIntegral`Word',withCalendar*`Calendar',`BusinessDayConvention',withQuote*`GenQuote a',withDayCounter*`DayCounter'
  ,`VolatilityType' -- ^type
  ,`Double' -- ^shift
  ,preErrorCheck-`String'errorCheck*-}->`SwaptionVolatilityStructure'peekSwaptionVolatilityStructure*#}

-- |returns the Black variance for a given option date and swap tenor
{#fun qlSwaptionVolatilityStructureBlackVariance1 as blackVarianceForPeriod'{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,withDay*`Day' -- ^optionDate
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns the Black variance for a given option time and swap tenor
{#fun qlSwaptionVolatilityStructureBlackVariance2 as blackVarianceForPeriod{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,`Double' -- optionTime
  ,fromEnumQuantity`(Word,TimeUnit)'& -- swapTenor
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns the Black variance for a given option tenor and swap length
{#fun qlSwaptionVolatilityStructureBlackVariance3 as blackVarianceForTenor{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,`Double' -- ^swapLength
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns the Black variance for a given option date and swap length
{#fun qlSwaptionVolatilityStructureBlackVariance4 as blackVariance'{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,withDay*`Day' -- ^optionDate
  ,`Double' -- ^swapLength
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns the Black variance for a given option time and swap length
{#fun qlSwaptionVolatilityStructureBlackVariance5 as blackVariance{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,`Double' -- ^optionTime
  ,`Double' -- ^swapLength
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns the Black variance for a given option tenor and swap tenor
{#fun qlSwaptionVolatilityStructureBlackVariance as blackVarianceForPeriods{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |the largest swapLength for which the term structure can return vols
{#fun qlSwaptionVolatilityStructureMaxSwapLength as maxSwapLength{withGenVolatilityTermStructure*`SwaptionVolatilityStructure',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |the largest length for which the term structure can return vols
{#fun qlSwaptionVolatilityStructureMaxSwapTenor as maxSwapTenor{withGenVolatilityTermStructure*`SwaptionVolatilityStructure',preEnum-`TimeUnit'peekEnum*,preErrorCheck-`String'errorCheck*-}->`Int'#}
-- |returns the smile for a given option date and swap tenor
{#fun qlSwaptionVolatilityStructureSmileSection1 as smileSectionForPeriod'{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,withDay*`Day' -- ^optionDate
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}
-- |returns the smile for a given option time and swap tenor
{#fun qlSwaptionVolatilityStructureSmileSection2 as smileSectionForPeriod{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,`Double' -- ^optionTime
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}
-- |returns the smile for a given option tenor and swap length
{#fun qlSwaptionVolatilityStructureSmileSection3 as smileSectionForTenor{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,`Double' -- ^swapLength
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}
-- |returns the smile for a given option date and swap length
{#fun qlSwaptionVolatilityStructureSmileSection4 as smileSection'{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,withDay*`Day' -- ^optionDate
  ,`Double' -- ^swapLength
  ,`Bool' -- ^extr
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}
-- |returns the smile for a given option time and swap length
{#fun qlSwaptionVolatilityStructureSmileSection5 as smileSection{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,`Double' -- ^optionTime
  ,`Double' -- ^swapLength
  ,`Bool' -- ^extr
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}
-- |returns the smile for a given option tenor and swap tenor
{#fun qlSwaptionVolatilityStructureSmileSection as smileSectionForPeriods{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
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
-- |the volatility for the given strike, for any 'SmileSection' (however it was constructed)
{#fun qlSmileSectionVolatility as smileSectionVolatility{withSmileSection*`SmileSection'
  ,`Double' -- ^strike
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |the Black variance for the given strike, for any 'SmileSection' (however it was constructed)
{#fun qlSmileSectionVariance as smileSectionVariance{withSmileSection*`SmileSection'
  ,`Double' -- ^strike
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |a smile section calibrated to a market smile (strikes/vols given directly, not as live
-- quotes -- calibration runs once, eagerly, at construction). alpha\/beta\/nu\/rho\/vegaWeighted
-- are the SABR calibration's initial guess and fixed\/free flags; endCriteria\/optimization
-- method are left at QuantLib's own internal defaults (a raw, Haskell-finalized EndCriteria or
-- OptimizationMethod handle can't safely be stored for this object's full lifetime -- see the
-- qlXxxFitting comment in "QuantLib.Internal.Enum" for the same ownership hazard elsewhere).
sabrInterpolatedSmileSection :: Day -- ^optionDate
  -> Double -- ^forward
  -> [Double] -- ^strikes
  -> Bool -- ^hasFloatingStrikes
  -> Double -- ^atmVolatility
  -> [Double] -- ^vols
  -> Double -- ^alpha
  -> Double -- ^beta
  -> Double -- ^nu
  -> Double -- ^rho
  -> SabrInterpolatedSmileSectionOpts -> IO SmileSection
sabrInterpolatedSmileSection optionDate forward strikes hasFloatingStrikes atmVolatility vols
  alpha beta nu rho opts = do
  dc <- maybe (dayCounter Actual365FixedStandard) return (sabrDayCounter opts)
  sabrInterpolatedSmileSection_ optionDate forward strikes hasFloatingStrikes atmVolatility vols
    alpha beta nu rho (sabrIsAlphaFixed opts) (sabrIsBetaFixed opts) (sabrIsNuFixed opts)
    (sabrIsRhoFixed opts) (sabrVegaWeighted opts) dc (sabrShift opts)

{#fun qlSabrInterpolatedSmileSection as sabrInterpolatedSmileSection_{withDay*`Day'
  ,`Double' -- ^forward
  ,withDoubleArray*`[Double]'& -- ^strikes
  ,`Bool' -- ^hasFloatingStrikes
  ,`Double' -- ^atmVolatility
  ,withDoubleArray*`[Double]'& -- ^vols
  ,`Double' -- ^alpha
  ,`Double' -- ^beta
  ,`Double' -- ^nu
  ,`Double' -- ^rho
  ,`Bool' -- ^isAlphaFixed
  ,`Bool' -- ^isBetaFixed
  ,`Bool' -- ^isNuFixed
  ,`Bool' -- ^isRhoFixed
  ,`Bool' -- ^vegaWeighted
  ,withDayCounter*`DayCounter'
  ,`Double' -- ^shift
  ,preErrorCheck-`String'errorCheck*-}->`SmileSection'peekSmileSection*#}

-- |calibrated alpha (post-fit; can differ from the initial guess passed to
-- 'sabrInterpolatedSmileSection' unless @sabrIsAlphaFixed@ was set). Only valid for a
-- 'SmileSection' built by 'sabrInterpolatedSmileSection'.
{#fun qlSabrInterpolatedSmileSectionAlpha as sabrInterpolatedSmileSectionAlpha{withSmileSection*`SmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |calibrated beta, see 'sabrInterpolatedSmileSectionAlpha'
{#fun qlSabrInterpolatedSmileSectionBeta as sabrInterpolatedSmileSectionBeta{withSmileSection*`SmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |calibrated nu, see 'sabrInterpolatedSmileSectionAlpha'
{#fun qlSabrInterpolatedSmileSectionNu as sabrInterpolatedSmileSectionNu{withSmileSection*`SmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |calibrated rho, see 'sabrInterpolatedSmileSectionAlpha'
{#fun qlSabrInterpolatedSmileSectionRho as sabrInterpolatedSmileSectionRho{withSmileSection*`SmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |root-mean-square calibration error
{#fun qlSabrInterpolatedSmileSectionRmsError as sabrInterpolatedSmileSectionRmsError{withSmileSection*`SmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |maximum calibration error
{#fun qlSabrInterpolatedSmileSectionMaxError as sabrInterpolatedSmileSectionMaxError{withSmileSection*`SmileSection',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |the reason the SABR calibration's optimizer stopped
{#fun qlSabrInterpolatedSmileSectionEndCriteria as sabrInterpolatedSmileSectionEndCriteria{withSmileSection*`SmileSection',preErrorCheck-`String'errorCheck*-}->`EndCriteriaType'#}
-- |implements the conversion between swap dates and swap (time) length
{#fun qlSwaptionVolatilityStructureSwapLength1 as swapLength'{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,withDay*`Day' -- ^start
  ,withDay*`Day' -- ^end
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |implements the conversion between swap tenor and swap (time) length
{#fun qlSwaptionVolatilityStructureSwapLength as swapLength{withGenVolatilityTermStructure*`SwaptionVolatilityStructure',fromEnumQuantity`(Word,TimeUnit)'&,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns the volatility for a given option date and swap tenor
{#fun qlSwaptionVolatilityStructureVolatility1 as volatilityForPeriod'{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,withDay*`Day' -- ^optionDate
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns the volatility for a given option time and swap tenor
{#fun qlSwaptionVolatilityStructureVolatility2 as volatilityForPeriod{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,`Double' -- ^optionTime
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns the volatility for a given option tenor and swap length
{#fun qlSwaptionVolatilityStructureVolatility3 as volatilityForTenor{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,`Double' -- ^swapLength
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the volatility for a given option date and swap length
{#fun qlSwaptionVolatilityStructureVolatility4 as volatilityForTenor'{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,withDay*`Day' -- ^optionDate
  ,`Double' -- ^swapLength
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the volatility for a given option time and swap length
{#fun qlSwaptionVolatilityStructureVolatility5 as volatility{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,`Double' -- ^optionTime
  ,`Double' -- ^swapLength
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |returns the volatility for a given option tenor and swap tenor
{#fun qlSwaptionVolatilityStructureVolatility as volatilityForPeriods{withGenVolatilityTermStructure*`SwaptionVolatilityStructure'
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^optionTenor
  ,fromEnumQuantity`(Word,TimeUnit)'& -- ^swapTenor
  ,`Double' -- ^strike
  ,`Bool' -- ^extrapolate
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

{#fun qlCallableBondConstantVolatility1 as callableBondConstantVolatility'{fromIntegral`Word',withCalendar*`Calendar',withQuote*`GenQuote a',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`CallableBondVolatilityStructure'peekCallableBondVolatilityStructure*#}
{#fun qlCallableBondConstantVolatility as callableBondConstantVolatility{withDay*`Day',withQuote*`GenQuote a',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`CallableBondVolatilityStructure'peekCallableBondVolatilityStructure*#}
-- |fixed reference date, floating market data
{#fun qlConstantCapFloorTermVolatility1 as constantCapFloorTermVolatility'{withDay*`Day',withCalendar*`Calendar',`BusinessDayConvention',withQuote*`GenQuote a',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`VolatilityTermStructure'peekVolatilityTermStructure*#}
-- |floating reference date, floating market data
{#fun qlConstantCapFloorTermVolatility as constantCapFloorTermVolatility{fromIntegral`Word',withCalendar*`Calendar',`BusinessDayConvention',withQuote*`GenQuote a',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`VolatilityTermStructure'peekVolatilityTermStructure*#}
{#fun qlSpreadedSwaptionVolatility as spreadedSwaptionVolatility{withGenVolatilityTermStructure*`SwaptionVolatilityStructure',withQuote*`GenQuote a',preErrorCheck-`String'errorCheck*-}->`SwaptionVolatilityStructure'peekSwaptionVolatilityStructure*#}
{#fun qlLocalConstantVol1 as localConstantVol'{fromIntegral`Word',withCalendar*`Calendar',withQuote*`GenQuote a',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`LocalVolTermStructure'peekLocalVolTermStructure*#}
{#fun qlLocalConstantVol as localConstantVol{withDay*`Day',withQuote*`GenQuote a',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`LocalVolTermStructure'peekLocalVolTermStructure*#}
{#fun qlLocalVolCurve as localVolCurve{withBlackVarianceCurve*`BlackVarianceCurve',preErrorCheck-`String'errorCheck*-}->`LocalVolTermStructure'peekLocalVolTermStructure*#}
{#fun qlImpliedVolTermStructure as impliedVolTermStructure{withBlackVolTermStructure*`GenBlackVolTermStructure a',withDay*`Day',preErrorCheck-`String'errorCheck*-}->`BlackVolTermStructure'peekBlackVolTermStructure*#}

-- |fixed reference date, floating market data
capFloorTermVolCurve' :: Day -> Calendar -> BusinessDayConvention -> [(Word, TimeUnit, GenQuote a)] -> DayCounter -> IO VolatilityTermStructure
capFloorTermVolCurve' d c bd ntq = qlCapFloorTermVolCurve1 d c bd n t q where (n, t, q) = unzip3 ntq
{#fun qlCapFloorTermVolCurve1{withDay*`Day',withCalendar*`Calendar',`BusinessDayConvention',withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&,withQuoteArray*`[GenQuote a]'&,withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`VolatilityTermStructure'peekVolatilityTermStructure*#}

-- |floating reference date, floating market data
capFloorTermVolCurve :: Word -> Calendar -> BusinessDayConvention -> [(Word, TimeUnit, GenQuote a)] -> DayCounter -> IO VolatilityTermStructure
capFloorTermVolCurve d c bd ntq = qlCapFloorTermVolCurve d c bd n t q where (n, t, q) = unzip3 ntq
{#fun qlCapFloorTermVolCurve{fromIntegral`Word',withCalendar*`Calendar',`BusinessDayConvention',withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&,withQuoteArray*`[GenQuote a]'&,withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`VolatilityTermStructure'peekVolatilityTermStructure*#}

blackVarianceCurve :: Day -> [(Day, Double)] -> DayCounter -> Bool -- ^forceMonotoneVariance
  -> Maybe Interpolation -> IO BlackVarianceCurve
blackVarianceCurve d dq dc f i = uncurryNested (qlBlackVarianceCurve d dd q dc f) (qlInterpolation' i) where (dd, q) = unzip dq
{#fun qlBlackVarianceCurve{withDay*`Day',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,withDayCounter*`DayCounter',`Bool',`Int',`Int',`Int',preErrorCheck-`String'errorCheck*-}->`BlackVarianceCurve'peekBlackVarianceCurve*#}

blackVarianceSurface :: Day -> Calendar -> [Day] -- ^dates
  -> [Double] -- ^strikes
  -> Matrix Double -- ^blackVolMatrix
  -> DayCounter
  -> BlackVarianceSurfaceExtrapolation -- ^lowerExtrapolation
  -> BlackVarianceSurfaceExtrapolation -- ^upperExtrapolation
  -> IO BlackVolTermStructure
blackVarianceSurface d c ds s (Matrix mr mc md) = qlBlackVarianceSurface d c ds s mr mc md
{#fun qlBlackVarianceSurface{withDay*`Day',withCalendar*`Calendar',withDayArray*`[Day]'&,withDoubleArray*`[Double]'&,fromIntegral`Word',fromIntegral`Word',withDoubleArrayRaw*`[Double]',withDayCounter*`DayCounter',`BlackVarianceSurfaceExtrapolation',`BlackVarianceSurfaceExtrapolation',preErrorCheck-`String'errorCheck*-}->`BlackVolTermStructure'peekBlackVolTermStructure*#}

-- |floating reference date, floating market data
capFloorTermVolSurface :: Word -> Calendar -> BusinessDayConvention -> [(Word, TimeUnit)] -- ^optionTenors
  -> [Double] -- ^strikes
  -> Matrix (GenQuote a) -- ^volatilities
  -> DayCounter -> IO CapFloorTermVolSurface
capFloorTermVolSurface d c bd t s (Matrix mr mc md) = qlCapFloorTermVolSurface d c bd pl pu s mr mc md where (pl, pu) = unzip t
{#fun qlCapFloorTermVolSurface{fromIntegral`Word',withCalendar*`Calendar',`BusinessDayConvention',withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&,withDoubleArray*`[Double]'&,fromIntegral`Word',fromIntegral`Word',withQuoteArrayRaw*`[GenQuote a]',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`CapFloorTermVolSurface'peekCapFloorTermVolSurface*#}

-- |fixed reference date, floating market data
capFloorTermVolSurface' :: Day -> Calendar -> BusinessDayConvention -> [(Word, TimeUnit)] -- ^optionTenors
  -> [Double] -- ^strikes
  -> Matrix (GenQuote a) -- ^volatilities
  -> DayCounter -> IO CapFloorTermVolSurface
capFloorTermVolSurface' d c bd t s (Matrix mr mc md) = qlCapFloorTermVolSurface1 d c bd pl pu s mr mc md where (pl, pu) = unzip t
{#fun qlCapFloorTermVolSurface1{withDay*`Day',withCalendar*`Calendar',`BusinessDayConvention',withIntArray*`[Word]'&,withEnumArray*`[TimeUnit]'&,withDoubleArray*`[Double]'&,fromIntegral`Word',fromIntegral`Word',withQuoteArrayRaw*`[GenQuote a]',withDayCounter*`DayCounter',preErrorCheck-`String'errorCheck*-}->`CapFloorTermVolSurface'peekCapFloorTermVolSurface*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
