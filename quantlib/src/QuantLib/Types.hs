{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE OverlappingInstances #-}
{-# OPTIONS_GHC -fno-warn-orphans #-} -- for Show and Eq instances of named singletons
module QuantLib.Types
  (
    Matrix
  , realMatrix
  , objectMatrix

  -- cashflows
  , Leg
  , CouponLeg
  , FloatingRateCouponPricer
  , Dividend

  -- currency
  , Currency
  , Rounding

  -- indices
  , Index
  , InterestRateIndex
  , IborIndex
  , SwapIndex
  , OvernightIndex
  , OvernightIndexedSwapIndex
  , BMAIndex

  -- instruments
  , Instrument
  , Bond
  , FixedRateBond
  , Forward
  , FixedRateBondForward
  , ForwardRateAgreement
  , Swap
  , VanillaSwap
  , OvernightIndexedSwap
  , BMASwap
  , AssetSwap
  , Payoff
  , BasketPayoff
  , StrikedTypePayoff
  , TypePayoff
  , PercentageStrikePayoff
  , PlainVanillaPayoff
  , AmericanExercise
  , BermudanExercise
  , EuropeanExercise
  , Exercise
  , SwingExercise
  , BarrierOption
  , CdsOption
  , CreditDefaultSwap
  , DividendVanillaOption
  , ForwardVanillaOption
  , MargrabeOption
  , MultiAssetOption
  , OneAssetOption
  , Option
  , QuantoVanillaOption
  , Swaption
  , VanillaOption
  , Claim
  , QuantoBarrierOption
  , QuantoForwardVanillaOption
  , CapFloor
  , Callability
  , CallabilityPrice
  , CallableBond
  , ConvertibleBond

  -- math
  , Constraint
  , OptimizationMethod
  , EndCriteria

  -- method
  , FdmSchemeDesc

  -- models
  , GJRGARCHModel
  , HestonModel
  , BatesModel
  , PiecewiseTimeDependentHestonModel
  , ShortRateModel
  , AffineModel
  , OneFactorAffineModel
  , LiborForwardModel
  , HullWhite
  , CalibratedModel
  , G2
  , BatesDetJumpModel
  , BatesDoubleExpDetJumpModel
  , BatesDoubleExpModel
  , LmCorrelationModel
  , LmVolatilityModel
  , CalibrationHelper

  -- pricingengines
  , PricingEngine
  , BlackCalculator
  , BlackScholesCalculator

  -- processes
  , GeneralizedBlackScholesProcess
  , StochasticProcess1D
  , StochasticProcess
  , BlackProcess
  , ExtOUWithJumpsProcess
  , ExtendedOrnsteinUhlenbeckProcess
  , GJRGARCHProcess
  , HestonProcess
  , BatesProcess
  , HybridHestonHullWhiteProcess
  , KlugeExtOUProcess
  , LiborForwardModelProcess
  , StochasticProcessArray
  , VarianceGammaProcess
  , Merton76Process
  , HullWhiteProcess
  , HullWhiteForwardProcess

  -- termstructures
  , RateHelper
  , SwapRateHelper
  , YieldTermStructure
  , VolTermStructure
  , OptionletVolatilityStructure
  , BondHelper
  , FittedBondDiscountCurveFittingMethod
  , FittedBondDiscountCurve
  , OISRateHelper
  , TermStructure
  , BlackVolTermStructure
  , VolatilityTermStructure
  , DefaultProbabilityTermStructure
  , SwaptionVolatilityStructure
  , SmileSection
  , CapFloorTermVolSurface
  , LocalVolTermStructure
  , BlackVarianceCurve
  , DefaultProbabilityHelper
  , CallableBondVolatilityStructure

  -- time
  , Calendar
  , DayCounter
  , Schedule
  , YearFraction

  -- common
  , InterestRate
  , Quote
  , SimpleQuote
  , TimeGrid

  -- casts
  , asInstrument
  , asBond
  , asForward
  , asSwap
  , asOption
  , asMultiAssetOption
  , asOneAssetOption
  , asBarrierOption
  , asForwardVanillaOption
  , asVanillaOption

  , asPayoff
  , asTypePayoff
  , asStrikedTypePayoff
  , asExercise
  , asBermudanExercise

  , asQuote

  , asIndex
  , asInterestRateIndex
  , asIborIndex
  , asSwapIndex

  , asRateHelper

  , asYieldTermStructure
  , asTermStructure
  , asVolatilityTermStructure
  , asBlackVolTermStructure

  , asStochasticProcess
  , asStochasticProcess1D
  , asGeneralizedBlackScholesProcess
  , asHestonProcess

  , asAffineModel
  , asOneFactorAffineModel
  , asShortRateModel
  , asCalibratedModel
  , asBatesModel
  , asHestonModel
  , asBatesDoubleExpModel

  , asBlackCalculator

  , nullInteger
  , nullReal
  , qlEpsilon

  , QLError(..)
  )
where

import QuantLib.Internal.Types
import QuantLib.Internal.Utils

-- do something more interesting using type system
realMatrix :: Word -> Word -> [Double] -> Either QLError (Matrix Double)
realMatrix rows cols d =
  if rows * cols /= fromIntegral (length d)
    then Left IncorrectSize
    else Right $ Matrix rows cols d

objectMatrix :: (Finalizable a) => Word -> Word -> [Object a] -> Either QLError (Matrix (Object a))
objectMatrix rows cols d =
  if rows * cols /= fromIntegral (length d)
    then Left IncorrectSize
    else Right $ Matrix rows cols d

-- cashflows
type Leg = Object CLeg
type CouponLeg = Object CCouponLeg
type FloatingRateCouponPricer = Object CFloatingRateCouponPricer
type Dividend = Object CDividend

-- currencies
type Currency = Object CCurrency
instance Show Currency where
  show = name
instance Eq Currency where
  (==) x y = name x == name y

type Rounding = Object CRounding
-- indexes
type Index = Object CIndex
type InterestRateIndex = Object CInterestRateIndex

-- |Inter-Bank-Offered-Rate indexes (e.g. Libor, etc.)
type IborIndex = Object CIborIndex

asInterestRateIndex :: (Upcastable a CInterestRateIndex) => Object a -> IO InterestRateIndex
asInterestRateIndex = upcast

asIndex :: (Upcastable a CIndex) => Object a -> IO Index
asIndex = upcast

type SwapIndex = Object CSwapIndex
type OvernightIndex = Object COvernightIndex
type OvernightIndexedSwapIndex = Object COvernightIndexedSwapIndex
type BMAIndex = Object CBMAIndex

asIborIndex :: (Upcastable a CIborIndex) => Object a -> IO IborIndex
asIborIndex = upcast

asSwapIndex :: (Upcastable a CSwapIndex) => Object a -> IO SwapIndex
asSwapIndex = upcast

-- instruments
type Instrument = Object CInstrument
-- |Base bond type.
-- /Warning/ Most methods assume that the cash flows are stored sorted by date, the redemption(s) being after any cash flow at the same date. In particular, if there's one single redemption, it must be the last cash flow,Tests price\/yield calculations are cross-checked for consistency.price/yield calculations are checked against known good values.
type Bond = Object CBond
-- |fixed-rate bond
type FixedRateBond = Object CFixedRateBond
-- |base forward type
type Forward = Object CForward
-- |Forward contract on a fixed-rate bond
-- 1. valueDate refers to the settlement date of the bond forward
--   contract.  maturityDate is the delivery (or repurchase)
--   date for the underlying bond (not the bond's maturity
--   date).
-- 2. Relevant formulas used in the calculations (\f$P\f$ refers
--    to a price):
--
--    a. \f$ P_{CleanFwd}(t) = P_{DirtyFwd}(t) -
--       AI(t=deliveryDate) \f$ where \f$ AI \f$ refers to the
--       accrued interest on the underlying bond.
--
--    b. \f$ P_{DirtyFwd}(t) = \frac{P_{DirtySpot}(t) -
--       SpotIncome(t)} {discountCurve->discount(t=deliveryDate)} \f$
--
--    c. \f$ SpotIncome(t) = \sum_i \left( CF_i \times
--       incomeDiscountCurve->discount(t_i) \right) \f$ where \f$
--       CF_i \f$ represents the ith bond cash flow (coupon
--       payment) associated with the underlying bond falling
--       between the settlementDate and the deliveryDate. (Note
--       the two different discount curves used in b. and c.)
type FixedRateBondForward = Object CFixedRateBondForward

-- |1. Unlike the forward contract conventions on carryable
--    financial assets (stocks, bonds, commodities), the
--    valueDate for a FRA is taken to be the day when the forward
--    loan or deposit begins and when full settlement takes place
--    (based on the NPV of the contract on that date).
--    maturityDate is the date when the forward loan or deposit
--    ends. In fact, the FRA settles and expires on the
--    valueDate, not on the (later) maturityDate. It follows that
--    (maturityDate - valueDate) is the tenor/term of the
--    underlying loan or deposit
--
-- 2. Choose position type = Long for an "FRA purchase" (future
--    long loan, short deposit [borrower])
--
-- 3. Choose position type = Short for an "FRA sale" (future short
--    loan, long deposit [lender])
--
-- 4. If strike is given in the constructor, can calculate the NPV
--    of the contract via NPV().
--
-- 5. If forward rate is desired/unknown, it can be obtained via
--    forwardRate(). In this case, the strike variable in the
--    constructor is irrelevant and will be ignored.
type ForwardRateAgreement = Object CForwardRateAgreement

-- 'as' casting style composes poorly with functions accepting
-- several arguments with the first being a Bond
-- XXX use applicative style?
asBond :: (Upcastable a CBond) => Object a -> IO Bond
asBond = upcast

asInstrument :: (Upcastable a CInstrument) => Object a -> IO Instrument
asInstrument = upcast

asForward :: (Upcastable a CForward) => Object a -> IO Forward
asForward = upcast

type Swap = Object CSwap
type VanillaSwap = Object CVanillaSwap
type BMASwap = Object CBMASwap
type OvernightIndexedSwap = Object COvernightIndexedSwap
type AssetSwap = Object CAssetSwap

asSwap :: (Upcastable a CSwap) => Object a -> IO Swap
asSwap = upcast

type Payoff = Object CPayoff
type BasketPayoff = Object CBasketPayoff
type StrikedTypePayoff = Object CStrikedTypePayoff
type TypePayoff = Object CTypePayoff
type PercentageStrikePayoff = Object CPercentageStrikePayoff
type PlainVanillaPayoff = Object CPlainVanillaPayoff

asPayoff :: (Upcastable a CPayoff) => Object a -> IO Payoff
asPayoff = upcast

asTypePayoff :: (Upcastable a CTypePayoff) => Object a -> IO TypePayoff
asTypePayoff = upcast

asStrikedTypePayoff :: (Upcastable a CStrikedTypePayoff) => Object a -> IO StrikedTypePayoff
asStrikedTypePayoff = upcast

type AmericanExercise = Object CAmericanExercise
type BermudanExercise = Object CBermudanExercise
type EuropeanExercise = Object CEuropeanExercise
type Exercise = Object CExercise

asExercise :: (Upcastable a CExercise) => Object a -> IO Exercise
asExercise = upcast

asBermudanExercise :: (Upcastable a CBermudanExercise) => Object a -> IO BermudanExercise
asBermudanExercise = upcast

type BarrierOption = Object CBarrierOption
type CdsOption = Object CCdsOption
type CreditDefaultSwap = Object CCreditDefaultSwap
type DividendVanillaOption = Object CDividendVanillaOption
type ForwardVanillaOption = Object CForwardVanillaOption
type MargrabeOption = Object CMargrabeOption
type MultiAssetOption = Object CMultiAssetOption
type OneAssetOption = Object COneAssetOption
type Option = Object COption
type QuantoVanillaOption = Object CQuantoVanillaOption
type Swaption = Object CSwaption
type SwingExercise = Object CSwingExercise
type VanillaOption = Object CVanillaOption
type Claim = Object CClaim

asOption :: (Upcastable a COption) => Object a -> IO Option
asOption = upcast

asMultiAssetOption :: (Upcastable a CMultiAssetOption) => Object a -> IO MultiAssetOption
asMultiAssetOption = upcast

asOneAssetOption :: (Upcastable a COneAssetOption) => Object a -> IO OneAssetOption
asOneAssetOption = upcast

asBarrierOption :: (Upcastable a CBarrierOption) => Object a -> IO BarrierOption
asBarrierOption = upcast

asForwardVanillaOption :: (Upcastable a CForwardVanillaOption) => Object a -> IO ForwardVanillaOption
asForwardVanillaOption = upcast

asVanillaOption :: (Upcastable a CVanillaOption) => Object a -> IO VanillaOption
asVanillaOption = upcast

type QuantoBarrierOption = Object CQuantoBarrierOption
type QuantoForwardVanillaOption = Object CQuantoForwardVanillaOption

type CapFloor = Object CCapFloor

type Callability = Object CCallability
type CallabilityPrice = Object CCallabilityPrice

type CallableBond = Object CCallableBond
type ConvertibleBond = Object CConvertibleBond

-- math
type Constraint = Object CConstraint
type OptimizationMethod = Object COptimizationMethod
type EndCriteria = Object CEndCriteria

-- method
type FdmSchemeDesc = Object CFdmSchemeDesc

-- models
type GJRGARCHModel = Object CGJRGARCHModel
type HestonModel = Object CHestonModel
type BatesModel = Object CBatesModel
type PiecewiseTimeDependentHestonModel = Object CPiecewiseTimeDependentHestonModel
type ShortRateModel = Object CShortRateModel
type AffineModel = Object CAffineModel
type OneFactorAffineModel = Object COneFactorAffineModel
type LiborForwardModel = Object CLiborForwardModel
type HullWhite = Object CHullWhite
type CalibrationHelper = Object CCalibrationHelper

type CalibratedModel = Object CCalibratedModel

type G2 = Object CG2

asAffineModel :: (Upcastable a CAffineModel) => Object a -> IO AffineModel
asAffineModel = upcast

asOneFactorAffineModel :: (Upcastable a COneFactorAffineModel) => Object a -> IO OneFactorAffineModel
asOneFactorAffineModel = upcast

asShortRateModel :: (Upcastable a CShortRateModel) => Object a -> IO ShortRateModel
asShortRateModel = upcast

asCalibratedModel :: (Upcastable a CCalibratedModel) => Object a -> IO CalibratedModel
asCalibratedModel = upcast

type BatesDetJumpModel = Object CBatesDetJumpModel
type BatesDoubleExpDetJumpModel = Object CBatesDoubleExpDetJumpModel
type BatesDoubleExpModel = Object CBatesDoubleExpModel

asBatesDoubleExpModel :: (Upcastable a CBatesDoubleExpModel) => Object a -> IO BatesDoubleExpModel
asBatesDoubleExpModel = upcast

asBatesModel :: (Upcastable a CBatesModel) => Object a -> IO BatesModel
asBatesModel = upcast

asHestonModel :: (Upcastable a CHestonModel) => Object a -> IO HestonModel
asHestonModel = upcast

type LmCorrelationModel = Object CLmCorrelationModel
type LmVolatilityModel = Object CLmVolatilityModel

-- pricingengines
type PricingEngine = Object CPricingEngine
type BlackCalculator = Object CBlackCalculator
type BlackScholesCalculator = Object CBlackScholesCalculator

asBlackCalculator :: (Upcastable a CBlackCalculator) => Object a -> IO BlackCalculator
asBlackCalculator = upcast

-- processes
type StochasticProcess1D = Object CStochasticProcess1D
type BlackProcess = Object CBlackProcess
type GeneralizedBlackScholesProcess = Object CGeneralizedBlackScholesProcess
type StochasticProcess = Object CStochasticProcess

asStochasticProcess :: (Upcastable a CStochasticProcess) => Object a -> IO StochasticProcess
asStochasticProcess = upcast

asStochasticProcess1D :: (Upcastable a CStochasticProcess1D) => Object a -> IO StochasticProcess1D
asStochasticProcess1D = upcast

asGeneralizedBlackScholesProcess :: (Upcastable a CGeneralizedBlackScholesProcess) => Object a -> IO GeneralizedBlackScholesProcess
asGeneralizedBlackScholesProcess = upcast

asHestonProcess :: (Upcastable a CHestonProcess) => Object a -> IO HestonProcess
asHestonProcess = upcast

type ExtOUWithJumpsProcess = Object CExtOUWithJumpsProcess
type ExtendedOrnsteinUhlenbeckProcess = Object CExtendedOrnsteinUhlenbeckProcess
type GJRGARCHProcess = Object CGJRGARCHProcess
type HestonProcess = Object CHestonProcess
type BatesProcess = Object CBatesProcess
type HybridHestonHullWhiteProcess = Object CHybridHestonHullWhiteProcess
type KlugeExtOUProcess = Object CKlugeExtOUProcess
type LiborForwardModelProcess = Object CLiborForwardModelProcess
type StochasticProcessArray = Object CStochasticProcessArray
type VarianceGammaProcess = Object CVarianceGammaProcess
type Merton76Process = Object CMerton76Process
type HullWhiteProcess = Object CHullWhiteProcess
type HullWhiteForwardProcess = Object CHullWhiteForwardProcess

-- termstructures
type RateHelper = Object CRateHelper
type YieldTermStructure = Object CYieldTermStructure
type VolTermStructure = Object CVolTermStructure
type OptionletVolatilityStructure = Object COptionletVolatilityStructure

type BondHelper = Object CBondHelper
type SwapRateHelper = Object CSwapRateHelper
type OISRateHelper = Object COISRateHelper

asRateHelper :: (Upcastable a CRateHelper) => Object a -> IO RateHelper
asRateHelper = upcast

type FittedBondDiscountCurveFittingMethod = Object CFittedBondDiscountCurveFittingMethod

type FittedBondDiscountCurve = Object CFittedBondDiscountCurve

asYieldTermStructure :: (Upcastable a CYieldTermStructure) => Object a -> IO YieldTermStructure
asYieldTermStructure = upcast

type TermStructure = Object CTermStructure

asTermStructure :: (Upcastable a CTermStructure) => Object a -> IO TermStructure
asTermStructure = upcast

type BlackVolTermStructure = Object CBlackVolTermStructure
type VolatilityTermStructure = Object CVolatilityTermStructure

asVolatilityTermStructure :: (Upcastable a CVolatilityTermStructure) => Object a -> IO VolatilityTermStructure
asVolatilityTermStructure = upcast

type DefaultProbabilityTermStructure = Object CDefaultProbabilityTermStructure
type SwaptionVolatilityStructure = Object CSwaptionVolatilityStructure
type SmileSection = Object CSmileSection

type CapFloorTermVolSurface = Object CCapFloorTermVolSurface
type LocalVolTermStructure = Object CLocalVolTermStructure

type BlackVarianceCurve = Object CBlackVarianceCurve

asBlackVolTermStructure :: (Upcastable a CBlackVolTermStructure) => Object a -> IO BlackVolTermStructure
asBlackVolTermStructure = upcast

type DefaultProbabilityHelper = Object CDefaultProbabilityHelper

type CallableBondVolatilityStructure = Object CCallableBondVolatilityStructure

-- time
-- |Calendars provide the means for determining whether a date is a business day or a holiday for a given market, and for incrementing/decrementing a date of a given number of business days
type Calendar = Object CCalendar
instance Show Calendar where
  show = name
instance Eq Calendar where
  (==) x y = name x == name y

type DayCounter = Object CDayCounter
instance Show DayCounter where
  show = name
instance Eq DayCounter where
  (==) x y = name x == name y

-- |Payment schedule
type Schedule = Object CSchedule

type YearFraction = Double

-- common
type InterestRate = Object CInterestRate
-- |Market observable
type Quote = Object CQuote
type SimpleQuote = Object CSimpleQuote

asQuote :: (Upcastable a CQuote) => Object a -> IO Quote
asQuote = upcast

type TimeGrid = Object CTimeGrid

foreign import ccall safe "ql.h qlNullInteger"
  nullInteger :: CInt
foreign import ccall safe "ql.h qlNullReal"
  nullReal :: CDouble

qlEpsilon :: Double
qlEpsilon = realToFrac c_qlEpsilon

foreign import ccall safe "ql.h qlEpsilon"
  c_qlEpsilon :: CDouble

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
