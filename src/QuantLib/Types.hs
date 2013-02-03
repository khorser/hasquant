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
  , asInstrument
  , asIndex
  , withBond
  , withInstrument
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
  asIndex :: a -> IO Index

foreign import ccall safe "ql.h qlIborAsIndex"
  c_iborAsIndex :: Ptr CIborIndex -> IO (Ptr CIndex)

instance IndexClass IborIndex where
  asIndex x = withObject x c_iborAsIndex >>= newForeignPtr finalize

-- instruments
type Instrument = ForeignPtr CInstrument
-- |Base bond type.
-- /Warning/ Most methods assume that the cash flows are stored sorted by date, the redemption(s) being after any cash flow at the same date. In particular, if there's one single redemption, it must be the last cash flow,Tests price\/yield calculations are cross-checked for consistency.price/yield calculations are checked against known good values.
type Bond = ForeignPtr CBond
-- |fixed-rate bond
type FixedRateBond = ForeignPtr CFixedRateBond

class BondClass a where
  asBond :: a -> IO Bond
  withBond :: a -> (Bond -> IO b) -> IO b
  withBond x f = asBond x >>= f

foreign import ccall safe "ql.h qlFixedRateBondAsBond"
  c_fixedRateBondAsBond :: Ptr CFixedRateBond -> IO (Ptr CBond)
instance BondClass FixedRateBond where
  asBond x = withObject x c_fixedRateBondAsBond >>= newForeignPtr finalize

class InstrumentClass a where
  asInstrument :: a -> IO Instrument
  withInstrument :: a -> (Instrument -> IO b) -> IO b
  withInstrument x f = asInstrument x >>= f

foreign import ccall safe "ql.h qlBondAsInstrument"
  c_bondAsInstrument :: Ptr CBond -> IO (Ptr CInstrument)

instance InstrumentClass Bond where
  asInstrument x = withObject x c_bondAsInstrument >>= newForeignPtr finalize

instance InstrumentClass FixedRateBond where
  asInstrument x = asBond x >>= asInstrument

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
