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

  -- pricingengines
  , PricingEngine

  -- termstructures
  , RateHelper
  , SwapRateHelper
  , YieldTermStructure
  , VolTermStructure
  , OptionletVolStructure
  , BondHelper
  , FittedBondDiscountCurveFittingMethod
  , FittedBondDiscountCurve
  , OISRateHelper
  , TermStructure

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

  , asPayoff
  , asTypePayoff
  , asStrikedTypePayoff
  , asExercise

  , asQuote

  , asIndex
  , asInterestRateIndex
  , asIborIndex
  , asSwapIndex

  , asRateHelper

  , asYieldTermStructure
  , asTermStructure
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

-- pricingengines
type PricingEngine = ForeignPtr CPricingEngine

-- termstructures
type RateHelper = ForeignPtr CRateHelper
type YieldTermStructure = ForeignPtr CYieldTermStructure
type VolTermStructure = ForeignPtr CVolTermStructure
type OptionletVolStructure = ForeignPtr COptionletVolStructure

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
