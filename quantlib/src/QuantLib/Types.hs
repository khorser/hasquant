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
  , QL(..)
  , QLE
  , runQLE
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

objectMatrix :: (Finalizable a) => Word -> Word -> [Object s a] -> Either QLError (Matrix (Object s a))
objectMatrix rows cols d =
  if rows * cols /= fromIntegral (length d)
    then Left IncorrectSize
    else Right $ Matrix rows cols d

-- cashflows
type Leg s = Object s CLeg
type CouponLeg s = Object s CCouponLeg
type FloatingRateCouponPricer s = Object s CFloatingRateCouponPricer
type Dividend s = Object s CDividend

-- currencies
type Currency s = Object s CCurrency
instance Show (Currency s) where
  show = name
instance Eq (Currency s) where
  (==) x y = name x == name y

type Rounding s = Object s CRounding
-- indexes
type Index s = Object s CIndex
type InterestRateIndex s = Object s CInterestRateIndex

-- |Inter-Bank-Offered-Rate indexes (e.g. Libor, etc.)
type IborIndex s = Object s CIborIndex

asInterestRateIndex :: (Upcastable a CInterestRateIndex) => Object s a -> QLE s (InterestRateIndex s)
asInterestRateIndex = upcast

asIndex :: (Upcastable a CIndex) => Object s a -> QLE s (Index s)
asIndex = upcast

type SwapIndex s = Object s CSwapIndex
type OvernightIndex s = Object s COvernightIndex
type OvernightIndexedSwapIndex s = Object s COvernightIndexedSwapIndex
type BMAIndex s = Object s CBMAIndex

asIborIndex :: (Upcastable a CIborIndex) => Object s a -> QLE s (IborIndex s)
asIborIndex = upcast

asSwapIndex :: (Upcastable a CSwapIndex) => Object s a -> QLE s (SwapIndex s)
asSwapIndex = upcast

-- instruments
type Instrument s = Object s CInstrument
-- |Base bond type.
-- /Warning/ Most methods assume that the cash flows are stored sorted by date, the redemption(s) being after any cash flow at the same date. In particular, if there's one single redemption, it must be the last cash flow,Tests price\/yield calculations are cross-checked for consistency.price/yield calculations are checked against known good values.
type Bond s = Object s CBond
-- |fixed-rate bond
type FixedRateBond s = Object s CFixedRateBond
-- |base forward type
type Forward s = Object s CForward
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
type FixedRateBondForward s = Object s CFixedRateBondForward

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
type ForwardRateAgreement s = Object s CForwardRateAgreement

-- 'as' casting style composes poorly with functions accepting
-- several arguments with the first being a Bond
-- XXX use applicative style?
asBond :: (Upcastable a CBond) => Object s a -> QLE s (Bond s)
asBond = upcast

asInstrument :: (Upcastable a CInstrument) => Object s a -> QLE s (Instrument s)
asInstrument = upcast

asForward :: (Upcastable a CForward) => Object s a -> QLE s (Forward s)
asForward = upcast

type Swap s = Object s CSwap
type VanillaSwap s = Object s CVanillaSwap
type BMASwap s = Object s CBMASwap
type OvernightIndexedSwap s = Object s COvernightIndexedSwap
type AssetSwap s = Object s CAssetSwap

asSwap :: (Upcastable a CSwap) => Object s a -> QLE s (Swap s)
asSwap = upcast

type Payoff s = Object s CPayoff
type BasketPayoff s = Object s CBasketPayoff
type StrikedTypePayoff s = Object s CStrikedTypePayoff
type TypePayoff s = Object s CTypePayoff
type PercentageStrikePayoff s = Object s CPercentageStrikePayoff
type PlainVanillaPayoff s = Object s CPlainVanillaPayoff

asPayoff :: (Upcastable a CPayoff) => Object s a -> QLE s (Payoff s)
asPayoff = upcast

asTypePayoff :: (Upcastable a CTypePayoff) => Object s a -> QLE s (TypePayoff s)
asTypePayoff = upcast

asStrikedTypePayoff :: (Upcastable a CStrikedTypePayoff) => Object s a -> QLE s (StrikedTypePayoff s)
asStrikedTypePayoff = upcast

type AmericanExercise s = Object s CAmericanExercise
type BermudanExercise s = Object s CBermudanExercise
type EuropeanExercise s = Object s CEuropeanExercise
type Exercise s = Object s CExercise

asExercise :: (Upcastable a CExercise) => Object s a -> QLE s (Exercise s)
asExercise = upcast

asBermudanExercise :: (Upcastable a CBermudanExercise) => Object s a -> QLE s (BermudanExercise s)
asBermudanExercise = upcast

type BarrierOption s = Object s CBarrierOption
type CdsOption s = Object s CCdsOption
type CreditDefaultSwap s = Object s CCreditDefaultSwap
type DividendVanillaOption s = Object s CDividendVanillaOption
type ForwardVanillaOption s = Object s CForwardVanillaOption
type MargrabeOption s = Object s CMargrabeOption
type MultiAssetOption s = Object s CMultiAssetOption
type OneAssetOption s = Object s COneAssetOption
type Option s = Object s COption
type QuantoVanillaOption s = Object s CQuantoVanillaOption
type Swaption s = Object s CSwaption
type SwingExercise s = Object s CSwingExercise
type VanillaOption s = Object s CVanillaOption
type Claim s = Object s CClaim

asOption :: (Upcastable a COption) => Object s a -> QLE s (Option s)
asOption = upcast

asMultiAssetOption :: (Upcastable a CMultiAssetOption) => Object s a -> QLE s (MultiAssetOption s)
asMultiAssetOption = upcast

asOneAssetOption :: (Upcastable a COneAssetOption) => Object s a -> QLE s (OneAssetOption s)
asOneAssetOption = upcast

asBarrierOption :: (Upcastable a CBarrierOption) => Object s a -> QLE s (BarrierOption s)
asBarrierOption = upcast

asForwardVanillaOption :: (Upcastable a CForwardVanillaOption) => Object s a -> QLE s (ForwardVanillaOption s)
asForwardVanillaOption = upcast

asVanillaOption :: (Upcastable a CVanillaOption) => Object s a -> QLE s (VanillaOption s)
asVanillaOption = upcast

type QuantoBarrierOption s = Object s CQuantoBarrierOption
type QuantoForwardVanillaOption s = Object s CQuantoForwardVanillaOption

type CapFloor s = Object s CCapFloor

type Callability s = Object s CCallability
type CallabilityPrice s = Object s CCallabilityPrice

type CallableBond s = Object s CCallableBond
type ConvertibleBond s = Object s CConvertibleBond

-- math
type Constraint s = Object s CConstraint
type OptimizationMethod s = Object s COptimizationMethod
type EndCriteria s = Object s CEndCriteria

-- method
type FdmSchemeDesc s = Object s CFdmSchemeDesc

-- models
type GJRGARCHModel s = Object s CGJRGARCHModel
type HestonModel s = Object s CHestonModel
type BatesModel s = Object s CBatesModel
type PiecewiseTimeDependentHestonModel s = Object s CPiecewiseTimeDependentHestonModel
type ShortRateModel s = Object s CShortRateModel
type AffineModel s = Object s CAffineModel
type OneFactorAffineModel s = Object s COneFactorAffineModel
type LiborForwardModel s = Object s CLiborForwardModel
type HullWhite s = Object s CHullWhite
type CalibrationHelper s = Object s CCalibrationHelper

type CalibratedModel s = Object s CCalibratedModel

type G2 s = Object s CG2

asAffineModel :: (Upcastable a CAffineModel) => Object s a -> QLE s (AffineModel s)
asAffineModel = upcast

asOneFactorAffineModel :: (Upcastable a COneFactorAffineModel) => Object s a -> QLE s (OneFactorAffineModel s)
asOneFactorAffineModel = upcast

asShortRateModel :: (Upcastable a CShortRateModel) => Object s a -> QLE s (ShortRateModel s)
asShortRateModel = upcast

asCalibratedModel :: (Upcastable a CCalibratedModel) => Object s a -> QLE s (CalibratedModel s)
asCalibratedModel = upcast

type BatesDetJumpModel s = Object s CBatesDetJumpModel
type BatesDoubleExpDetJumpModel s = Object s CBatesDoubleExpDetJumpModel
type BatesDoubleExpModel s = Object s CBatesDoubleExpModel

asBatesDoubleExpModel :: (Upcastable a CBatesDoubleExpModel) => Object s a -> QLE s (BatesDoubleExpModel s)
asBatesDoubleExpModel = upcast

asBatesModel :: (Upcastable a CBatesModel) => Object s a -> QLE s (BatesModel s)
asBatesModel = upcast

asHestonModel :: (Upcastable a CHestonModel) => Object s a -> QLE s (HestonModel s)
asHestonModel = upcast

type LmCorrelationModel s = Object s CLmCorrelationModel
type LmVolatilityModel s = Object s CLmVolatilityModel

-- pricingengines
type PricingEngine s = Object s CPricingEngine
type BlackCalculator s = Object s CBlackCalculator
type BlackScholesCalculator s = Object s CBlackScholesCalculator

asBlackCalculator :: (Upcastable a CBlackCalculator) => Object s a -> QLE s (BlackCalculator s)
asBlackCalculator = upcast

-- processes
type StochasticProcess1D s = Object s CStochasticProcess1D
type BlackProcess s = Object s CBlackProcess
type GeneralizedBlackScholesProcess s = Object s CGeneralizedBlackScholesProcess
type StochasticProcess s = Object s CStochasticProcess

asStochasticProcess :: (Upcastable a CStochasticProcess) => Object s a -> QLE s (StochasticProcess s)
asStochasticProcess = upcast

asStochasticProcess1D :: (Upcastable a CStochasticProcess1D) => Object s a -> QLE s (StochasticProcess1D s)
asStochasticProcess1D = upcast

asGeneralizedBlackScholesProcess :: (Upcastable a CGeneralizedBlackScholesProcess) => Object s a -> QLE s (GeneralizedBlackScholesProcess s)
asGeneralizedBlackScholesProcess = upcast

asHestonProcess :: (Upcastable a CHestonProcess) => Object s a -> QLE s (HestonProcess s)
asHestonProcess = upcast

type ExtOUWithJumpsProcess s = Object s CExtOUWithJumpsProcess
type ExtendedOrnsteinUhlenbeckProcess s = Object s CExtendedOrnsteinUhlenbeckProcess
type GJRGARCHProcess s = Object s CGJRGARCHProcess
type HestonProcess s = Object s CHestonProcess
type BatesProcess s = Object s CBatesProcess
type HybridHestonHullWhiteProcess s = Object s CHybridHestonHullWhiteProcess
type KlugeExtOUProcess s = Object s CKlugeExtOUProcess
type LiborForwardModelProcess s = Object s CLiborForwardModelProcess
type StochasticProcessArray s = Object s CStochasticProcessArray
type VarianceGammaProcess s = Object s CVarianceGammaProcess
type Merton76Process s = Object s CMerton76Process
type HullWhiteProcess s = Object s CHullWhiteProcess
type HullWhiteForwardProcess s = Object s CHullWhiteForwardProcess

-- termstructures
type RateHelper s = Object s CRateHelper
type YieldTermStructure s = Object s CYieldTermStructure
type VolTermStructure s = Object s CVolTermStructure
type OptionletVolatilityStructure s = Object s COptionletVolatilityStructure

type BondHelper s = Object s CBondHelper
type SwapRateHelper s = Object s CSwapRateHelper
type OISRateHelper s = Object s COISRateHelper

asRateHelper :: (Upcastable a CRateHelper) => Object s a -> QLE s (RateHelper s)
asRateHelper = upcast

type FittedBondDiscountCurveFittingMethod s = Object s CFittedBondDiscountCurveFittingMethod

type FittedBondDiscountCurve s = Object s CFittedBondDiscountCurve

asYieldTermStructure :: (Upcastable a CYieldTermStructure) => Object s a -> QLE s (YieldTermStructure s)
asYieldTermStructure = upcast

type TermStructure s = Object s CTermStructure

asTermStructure :: (Upcastable a CTermStructure) => Object s a -> QLE s (TermStructure s)
asTermStructure = upcast

type BlackVolTermStructure s = Object s CBlackVolTermStructure
type VolatilityTermStructure s = Object s CVolatilityTermStructure

asVolatilityTermStructure :: (Upcastable a CVolatilityTermStructure) => Object s a -> QLE s (VolatilityTermStructure s)
asVolatilityTermStructure = upcast

type DefaultProbabilityTermStructure s = Object s CDefaultProbabilityTermStructure
type SwaptionVolatilityStructure s = Object s CSwaptionVolatilityStructure
type SmileSection s = Object s CSmileSection

type CapFloorTermVolSurface s = Object s CCapFloorTermVolSurface
type LocalVolTermStructure s = Object s CLocalVolTermStructure

type BlackVarianceCurve s = Object s CBlackVarianceCurve

asBlackVolTermStructure :: (Upcastable a CBlackVolTermStructure) => Object s a -> QLE s (BlackVolTermStructure s)
asBlackVolTermStructure = upcast

type DefaultProbabilityHelper s = Object s CDefaultProbabilityHelper

type CallableBondVolatilityStructure s = Object s CCallableBondVolatilityStructure

-- time
-- |Calendars provide the means for determining whether a date is a business day or a holiday for a given market, and for incrementing/decrementing a date of a given number of business days
type Calendar s = Object s CCalendar
instance Show (Calendar s) where
  show = name
instance Eq (Calendar s) where
  (==) x y = name x == name y

type DayCounter s = Object s CDayCounter
instance Show (DayCounter s) where
  show = name
instance Eq (DayCounter s) where
  (==) x y = name x == name y

-- |Payment schedule
type Schedule s = Object s CSchedule

type YearFraction = Double

-- common
type InterestRate s = Object s CInterestRate
-- |Market observable
type Quote s = Object s CQuote
type SimpleQuote s = Object s CSimpleQuote

asQuote :: (Upcastable a CQuote) => Object s a -> QLE s (Quote s)
asQuote = upcast

type TimeGrid s = Object s CTimeGrid

foreign import ccall safe "ql.h qlNullInteger"
  nullInteger :: CInt
foreign import ccall safe "ql.h qlNullReal"
  nullReal :: CDouble

qlEpsilon :: Double
qlEpsilon = realToFrac c_qlEpsilon

foreign import ccall safe "ql.h qlEpsilon"
  c_qlEpsilon :: CDouble

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
