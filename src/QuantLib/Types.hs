{-# LANGUAGE FlexibleInstances,OverlappingInstances,FlexibleContexts #-}
{-# OPTIONS_GHC -fno-warn-orphans #-} -- for Show and Eq instances of named singletons
module QuantLib.Types
  (
  -- cashflows
    Leg
  , FloatingRateCouponPricer

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

  -- time
  , Calendar
  , DayCounter
  , Period
  , Schedule
  , YearFraction

  -- common
  , InterestRate
  , Quote
  , SimpleQuote

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

  , asStochasticProcess
  , asStochasticProcess1D
  , asGeneralizedBlackScholesProcess
  , asHestonProcess

  , asAffineModel
  , asOneFactorAffineModel
  , asShortRateModel

  , asBlackCalculator
  )
where

import QuantLib.Internal.Types
import QuantLib.Internal.Utils

-- cashflows
type Leg = ForeignPtr CLeg
type FloatingRateCouponPricer = ForeignPtr CFloatingRateCouponPricer

-- currencies
type Currency = ForeignPtr CCurrency
instance Show Currency where
  show = name
instance Eq Currency where
  (==) x y = name x == name y

type Rounding = ForeignPtr CRounding
-- indexes
type Index = ForeignPtr CIndex
type InterestRateIndex = ForeignPtr CInterestRateIndex

-- |Inter-Bank-Offered-Rate indexes (e.g. Libor, etc.)
type IborIndex = ForeignPtr CIborIndex

asInterestRateIndex :: (Upcastable a CInterestRateIndex) => ForeignPtr a -> IO InterestRateIndex
asInterestRateIndex = upcast

asIndex :: (Upcastable a CIndex) => ForeignPtr a -> IO Index
asIndex = upcast

type SwapIndex = ForeignPtr CSwapIndex
type OvernightIndex = ForeignPtr COvernightIndex
type OvernightIndexedSwapIndex = ForeignPtr COvernightIndexedSwapIndex
type BMAIndex = ForeignPtr CBMAIndex

asIborIndex :: (Upcastable a CIborIndex) => ForeignPtr a -> IO IborIndex
asIborIndex = upcast

asSwapIndex :: (Upcastable a CSwapIndex) => ForeignPtr a -> IO SwapIndex
asSwapIndex = upcast

-- instruments
type Instrument = ForeignPtr CInstrument
-- |Base bond type.
-- /Warning/ Most methods assume that the cash flows are stored sorted by date, the redemption(s) being after any cash flow at the same date. In particular, if there's one single redemption, it must be the last cash flow,Tests price\/yield calculations are cross-checked for consistency.price/yield calculations are checked against known good values.
type Bond = ForeignPtr CBond
-- |fixed-rate bond
type FixedRateBond = ForeignPtr CFixedRateBond
-- |base forward type
type Forward = ForeignPtr CForward
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
type FixedRateBondForward = ForeignPtr CFixedRateBondForward

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
type ForwardRateAgreement = ForeignPtr CForwardRateAgreement

-- 'as' casting style composes poorly with functions accepting
-- several arguments with first being a Bond
-- XXX use applicative style?
asBond :: (Upcastable a CBond) => ForeignPtr a -> IO Bond
asBond = upcast

asInstrument :: (Upcastable a CInstrument) => ForeignPtr a -> IO Instrument
asInstrument = upcast

asForward :: (Upcastable a CForward) => ForeignPtr a -> IO Forward
asForward = upcast

type Swap = ForeignPtr CSwap
type VanillaSwap = ForeignPtr CVanillaSwap
type BMASwap = ForeignPtr CBMASwap
type OvernightIndexedSwap = ForeignPtr COvernightIndexedSwap
type AssetSwap = ForeignPtr CAssetSwap

asSwap :: (Upcastable a CSwap) => ForeignPtr a -> IO Swap
asSwap = upcast

type Payoff = ForeignPtr CPayoff
type BasketPayoff = ForeignPtr CBasketPayoff
type StrikedTypePayoff = ForeignPtr CStrikedTypePayoff
type TypePayoff = ForeignPtr CTypePayoff
type PercentageStrikePayoff = ForeignPtr CPercentageStrikePayoff
type PlainVanillaPayoff = ForeignPtr CPlainVanillaPayoff

asPayoff :: (Upcastable a CPayoff) => ForeignPtr a -> IO Payoff
asPayoff = upcast

asTypePayoff :: (Upcastable a CTypePayoff) => ForeignPtr a -> IO TypePayoff
asTypePayoff = upcast

asStrikedTypePayoff :: (Upcastable a CStrikedTypePayoff) => ForeignPtr a -> IO StrikedTypePayoff
asStrikedTypePayoff = upcast

type AmericanExercise = ForeignPtr CAmericanExercise
type BermudanExercise = ForeignPtr CBermudanExercise
type EuropeanExercise = ForeignPtr CEuropeanExercise
type Exercise = ForeignPtr CExercise

asExercise :: (Upcastable a CExercise) => ForeignPtr a -> IO Exercise
asExercise = upcast

asBermudanExercise :: (Upcastable a CBermudanExercise) => ForeignPtr a -> IO BermudanExercise
asBermudanExercise = upcast

type BarrierOption = ForeignPtr CBarrierOption
type CdsOption = ForeignPtr CCdsOption
type CreditDefaultSwap = ForeignPtr CCreditDefaultSwap
type DividendVanillaOption = ForeignPtr CDividendVanillaOption
type ForwardVanillaOption = ForeignPtr CForwardVanillaOption
type MargrabeOption = ForeignPtr CMargrabeOption
type MultiAssetOption = ForeignPtr CMultiAssetOption
type OneAssetOption = ForeignPtr COneAssetOption
type Option = ForeignPtr COption
type QuantoVanillaOption = ForeignPtr CQuantoVanillaOption
type Swaption = ForeignPtr CSwaption
type SwingExercise = ForeignPtr CSwingExercise
type VanillaOption = ForeignPtr CVanillaOption
type Claim = ForeignPtr CClaim

asOption :: (Upcastable a COption) => ForeignPtr a -> IO Option
asOption = upcast

asMultiAssetOption :: (Upcastable a CMultiAssetOption) => ForeignPtr a -> IO MultiAssetOption
asMultiAssetOption = upcast

asOneAssetOption :: (Upcastable a COneAssetOption) => ForeignPtr a -> IO OneAssetOption
asOneAssetOption = upcast

asBarrierOption :: (Upcastable a CBarrierOption) => ForeignPtr a -> IO BarrierOption
asBarrierOption = upcast

asForwardVanillaOption :: (Upcastable a CForwardVanillaOption) => ForeignPtr a -> IO ForwardVanillaOption
asForwardVanillaOption = upcast

asVanillaOption :: (Upcastable a CVanillaOption) => ForeignPtr a -> IO VanillaOption
asVanillaOption = upcast

type QuantoBarrierOption = ForeignPtr CQuantoBarrierOption
type QuantoForwardVanillaOption = ForeignPtr CQuantoForwardVanillaOption

-- models
type GJRGARCHModel = ForeignPtr CGJRGARCHModel
type HestonModel = ForeignPtr CHestonModel
type BatesModel = ForeignPtr CBatesModel
type PiecewiseTimeDependentHestonModel = ForeignPtr CPiecewiseTimeDependentHestonModel
type ShortRateModel = ForeignPtr CShortRateModel
type AffineModel = ForeignPtr CAffineModel
type OneFactorAffineModel = ForeignPtr COneFactorAffineModel
type LiborForwardModel = ForeignPtr CLiborForwardModel
type HullWhite = ForeignPtr CHullWhite

type CalibratedModel = ForeignPtr CCalibratedModel

type G2 = ForeignPtr CG2

asAffineModel :: (Upcastable a CAffineModel) => ForeignPtr a -> IO AffineModel
asAffineModel = upcast

asOneFactorAffineModel :: (Upcastable a COneFactorAffineModel) => ForeignPtr a -> IO OneFactorAffineModel
asOneFactorAffineModel = upcast

asShortRateModel :: (Upcastable a CShortRateModel) => ForeignPtr a -> IO ShortRateModel
asShortRateModel = upcast

-- pricingengines
type PricingEngine = ForeignPtr CPricingEngine
type BlackCalculator = ForeignPtr CBlackCalculator
type BlackScholesCalculator = ForeignPtr CBlackScholesCalculator

asBlackCalculator :: (Upcastable a CBlackCalculator) => ForeignPtr a -> IO BlackCalculator
asBlackCalculator = upcast

-- processes
type StochasticProcess1D = ForeignPtr CStochasticProcess1D
type BlackProcess = ForeignPtr CBlackProcess
type GeneralizedBlackScholesProcess = ForeignPtr CGeneralizedBlackScholesProcess
type StochasticProcess = ForeignPtr CStochasticProcess

asStochasticProcess :: (Upcastable a CStochasticProcess) => ForeignPtr a -> IO StochasticProcess
asStochasticProcess = upcast

asStochasticProcess1D :: (Upcastable a CStochasticProcess1D) => ForeignPtr a -> IO StochasticProcess1D
asStochasticProcess1D = upcast

asGeneralizedBlackScholesProcess :: (Upcastable a CGeneralizedBlackScholesProcess) => ForeignPtr a -> IO GeneralizedBlackScholesProcess
asGeneralizedBlackScholesProcess = upcast

asHestonProcess :: (Upcastable a CHestonProcess) => ForeignPtr a -> IO HestonProcess
asHestonProcess = upcast

type ExtOUWithJumpsProcess = ForeignPtr CExtOUWithJumpsProcess
type ExtendedOrnsteinUhlenbeckProcess = ForeignPtr CExtendedOrnsteinUhlenbeckProcess
type GJRGARCHProcess = ForeignPtr CGJRGARCHProcess
type HestonProcess = ForeignPtr CHestonProcess
type BatesProcess = ForeignPtr CBatesProcess
type HybridHestonHullWhiteProcess = ForeignPtr CHybridHestonHullWhiteProcess
type KlugeExtOUProcess = ForeignPtr CKlugeExtOUProcess
type LiborForwardModelProcess = ForeignPtr CLiborForwardModelProcess
type StochasticProcessArray = ForeignPtr CStochasticProcessArray
type VarianceGammaProcess = ForeignPtr CVarianceGammaProcess
type Merton76Process = ForeignPtr CMerton76Process
type HullWhiteProcess = ForeignPtr CHullWhiteProcess
type HullWhiteForwardProcess = ForeignPtr CHullWhiteForwardProcess

-- termstructures
type RateHelper = ForeignPtr CRateHelper
type YieldTermStructure = ForeignPtr CYieldTermStructure
type VolTermStructure = ForeignPtr CVolTermStructure
type OptionletVolatilityStructure = ForeignPtr COptionletVolatilityStructure

type BondHelper = ForeignPtr CBondHelper
type SwapRateHelper = ForeignPtr CSwapRateHelper
type OISRateHelper = ForeignPtr COISRateHelper

asRateHelper :: (Upcastable a CRateHelper) => ForeignPtr a -> IO RateHelper
asRateHelper = upcast

type FittedBondDiscountCurveFittingMethod = ForeignPtr CFittedBondDiscountCurveFittingMethod

type FittedBondDiscountCurve = ForeignPtr CFittedBondDiscountCurve

asYieldTermStructure :: (Upcastable a CYieldTermStructure) => ForeignPtr a -> IO YieldTermStructure
asYieldTermStructure = upcast

type TermStructure = ForeignPtr CTermStructure

asTermStructure :: (Upcastable a CTermStructure) => ForeignPtr a -> IO TermStructure
asTermStructure = upcast

type BlackVolTermStructure = ForeignPtr CBlackVolTermStructure
type VolatilityTermStructure = ForeignPtr CVolatilityTermStructure

asVolatilityTermStructure :: (Upcastable a CVolatilityTermStructure) => ForeignPtr a -> IO VolatilityTermStructure
asVolatilityTermStructure = upcast

type DefaultProbabilityTermStructure = ForeignPtr CDefaultProbabilityTermStructure
type SwaptionVolatilityStructure = ForeignPtr CSwaptionVolatilityStructure
type SmileSection = ForeignPtr CSmileSection

-- time
-- |Calendars provide the means for determining whether a date is a business day or a holiday for a given market, and for incrementing/decrementing a date of a given number of business days
type Calendar = ForeignPtr CCalendar
instance Show Calendar where
  show = name
instance Eq Calendar where
  (==) x y = name x == name y

type DayCounter = ForeignPtr CDayCounter
instance Show DayCounter where
  show = name
instance Eq DayCounter where
  (==) x y = name x == name y

-- |A Period (length + TimeUnit) implementing a limited algebra
type Period = ForeignPtr CPeriod
-- |Payment schedule
type Schedule = ForeignPtr CSchedule

type YearFraction = Double

-- common
type InterestRate = ForeignPtr CInterestRate
-- |Market observable
type Quote = ForeignPtr CQuote
type SimpleQuote = ForeignPtr CSimpleQuote

asQuote :: (Upcastable a CQuote) => ForeignPtr a -> IO Quote
asQuote = upcast

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
