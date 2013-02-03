{-# LANGUAGE FlexibleInstances,OverlappingInstances #-}
{-# OPTIONS_GHC -fno-warn-orphans #-} -- for Show instances
module QuantLib.Types
  (
  -- cashflows
    Leg
  , FloatingRateCouponPricer

  -- curencies
  , Currency

  -- indexes
  , Index
  , IborIndex

  -- instruments
  , Instrument
  , Bond
  , FixedRateBond

  -- pricingengines
  , PricingEngine

  -- termstructures
  , RateHelper
  , YieldTermStructure
  , VolTermStructure
  , OptionletVolStructure

  -- time
  , Calendar
  , DayCounter
  , Period
  , Schedule

  -- common
  , InterestRate
  , Quote

  -- casts
  , asBond
  , withInstrument
  , withIndex
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

-- indexes
type Index = ForeignPtr CIndex
-- |Inter-Bank-Offered-Rate indexes (e.g. Libor, etc.)
type IborIndex = ForeignPtr CIborIndex

class IndexClass a where
  -- it is NOT ok to keep the argument of the function after the call
  withIndex :: a -> (Index -> IO b) -> IO b

foreign import ccall safe "ql.h qlIborAsIndex"
  c_iborAsIndex :: Ptr CIborIndex -> Ptr CIndex

instance IndexClass IborIndex where
  withIndex x f =
    withForeignPtr x
      (\p -> do ptr <- newForeignPtr_ (c_iborAsIndex p)
                f ptr)

-- instruments
type Instrument = ForeignPtr CInstrument
-- |Base bond type.
-- /Warning/ Most methods assume that the cash flows are stored sorted by date, the redemption(s) being after any cash flow at the same date. In particular, if there's one single redemption, it must be the last cash flow,Tests price\/yield calculations are cross-checked for consistency.price/yield calculations are checked against known good values.
type Bond = ForeignPtr CBond
-- |fixed-rate bond
type FixedRateBond = ForeignPtr CFixedRateBond

class BondClass a where
  -- it is ok to keep the result of the cast
  asBond :: a -> Bond

instance BondClass FixedRateBond where
  asBond = castForeignPtr

class InstrumentClass a where
  -- it is NOT ok to keep the argument of the function after the call
  withInstrument :: a -> (Instrument -> IO b) -> IO b

foreign import ccall safe "ql.h qlBondAsInstrument"
  c_bondAsInstrument :: Ptr CBond -> Ptr CInstrument

instance InstrumentClass Bond where
  withInstrument x f =
    withForeignPtr x
    (\p -> do ptr <- newForeignPtr_ (c_bondAsInstrument p)
              f ptr)

instance InstrumentClass FixedRateBond where
  withInstrument = withInstrument . asBond

-- pricingengines
type PricingEngine = ForeignPtr CPricingEngine

-- termstructures
type RateHelper = ForeignPtr CRateHelper
type YieldTermStructure = ForeignPtr CYieldTermStructure
type VolTermStructure = ForeignPtr CVolTermStructure
type OptionletVolStructure = ForeignPtr COptionletVolStructure

-- time
-- |Calendars provide the means for determining whether a date is a business day or a holiday for a given market, and for incrementing/decrementing a date of a given number of business days
type Calendar = ForeignPtr CCalendar
instance Show Calendar where
  show = name
type DayCounter = ForeignPtr CDayCounter
instance Show DayCounter where
  show = name
-- |A Period (length + TimeUnit) implementing a limited algebra
type Period = ForeignPtr CPeriod
-- |Payment schedule
type Schedule = ForeignPtr CSchedule

-- common
type InterestRate = ForeignPtr CInterestRate
-- |Market observable
type Quote = ForeignPtr CQuote
