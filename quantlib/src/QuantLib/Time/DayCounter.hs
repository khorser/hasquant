{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Time.DayCounter
  (
    actual365Fixed

  , one

  , actualActualISMA
  , actualActualBond
  , actualActualISDA
  , actualActualHistorical
  , actualActualAct365
  , actualActualAFB
  , actualActualEuro

  , actual360

  , thirty360USA
  , thirty360BondBasis
  , thirty360European
  , thirty360EurobondBasis
  , thirty360Italian

  , simple
  , business252

  , dayCount
  , yearFraction
  )

where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types

-- |Actual\/365 (Fixed) day count convention, also know as Act\/365 (Fixed), A\/365 (Fixed), or A\/365F. /Warning/ According to ISDA, Actual\/365 (without Fixed) is an alias for Actual\/Actual (ISDA) (see ActualActual.) If Actual\/365 is not explicitly specified as fixed in an instrument specification, you might want to double-check its meaning.
actual365Fixed  :: IO DayCounter
-- |1/1 day count convention
one             :: IO DayCounter
actualActualISDA:: IO DayCounter
-- |Actual\/Actual day count.
-- The day count can be calculated according to: - the ISDA convention, also known as Actual\/Actual (Historical), Actual\/Actual, Act\/Act, and according to ISDA also Actual\/365, Act\/365, and A\/365; - the ISMA and US Treasury convention, also known as Actual\/Actual (Bond); - the AFB convention, also known as Actual\/Actual (Euro). For more details, refer to http://www.isda.org/publications/pdf/Day-Count-Fracation1999.pdf
-- |Actual\/360 day count convention, also known as Act\/360, or A\/360.
actual360       :: IO DayCounter
thirty360USA    :: IO DayCounter
thirty360BondBasis  :: IO DayCounter
-- |30\/360 day count convention
-- The 30\/360 day count can be calculated according to US, European, or Italian conventions.US (NASD) convention: if the starting date is the 31st of a month, it becomes equal to the 30th of the same month. If the ending date is the 31st of a month and the starting date is earlier than the 30th of a month, the ending date becomes equal to the 1st of the next month, otherwise the ending date becomes equal to the 30th of the same month. Also known as 30\/360, 360\/360, or Bond BasisEuropean convention: starting dates or ending dates that occur on the 31st of a month become equal to the 30th of the same month. Also known as 30E\/360, or Eurobond BasisItalian convention: starting dates or ending dates that occur on February and are grater than 27 become equal to 30 for computational sake.
thirty360EurobondBasis:: IO DayCounter
actualActualISMA:: IO DayCounter
actualActualBond:: IO DayCounter
actualActualHistorical:: IO DayCounter
actualActualAct365:: IO DayCounter
actualActualAFB :: IO DayCounter
actualActualEuro:: IO DayCounter
thirty360Italian:: IO DayCounter
-- |Simple day counter for reproducing theoretical calculations.
-- This day counter tries to ensure that whole-month distances are returned as a simple fraction, i.e., 1 year = 1.0, 6 months = 0.5, 3 months = 0.25 and so forth. /Warning/ this day counter should be used together with NullCalendar, which ensures that dates at whole-month distances share the same day of month. It is not guaranteed to work with any other calendar.Teststhe correctness of the results is checked against known good values.
simple          :: IO DayCounter
thirty360European:: IO DayCounter

actual365Fixed     = constructNamed "Actual/365 (Fixed)"
one                = constructNamed "1/1"
actualActualISDA   = constructNamed "Actual/Actual (ISDA)"
actual360          = constructNamed "Actual/360"
thirty360BondBasis = constructNamed "30/360 (Bond Basis)"
thirty360USA       = constructNamed "30/360 (USA)"
thirty360EurobondBasis = constructNamed "30/360 (Eurobond Basis)"
actualActualISMA   = constructNamed "Actual/Actual (ISMA)"
actualActualBond   = constructNamed "Actual/Actual (Bond)"
actualActualAct365    = constructNamed "Actual/Actual (Actual365)"
actualActualAFB    = constructNamed "Actual/Actual (AFB)"
actualActualEuro   = constructNamed "Actual/Actual (Euro)"
actualActualHistorical   = constructNamed "Actual/Actual (Historical)"
thirty360Italian   = constructNamed "30/360 (Italian)"
simple             = constructNamed "Simple"
thirty360European  = constructNamed "30/360 (European)"

-- |Business\/252 day count convention.
foreign import ccall safe "ql.h qlDayCounterBusiness252"
  c_business252 :: Ptr CCalendar -> Ptr CString -> IO (Ptr CDayCounter)
business252     :: Calendar -> IO DayCounter
business252 = $(ffiCall 'business252) c_business252

-- |Returns the number of days between two dates.
dayCount :: DayCounter -> Day -> Day -> Int
dayCount = $(ffiCallPure 'dayCount) c_dayCount

foreign import ccall safe "ql.h qlDayCounterDayCount"
  c_dayCount :: Ptr CDayCounter -> CDate -> CDate -> IO CInt

-- |Returns the period between two dates as a fraction of year.
yearFraction :: DayCounter
  -> Day
  -> Day
  -> Maybe Day -- ^refPeriodStart
  -> Maybe Day -- ^refPeriodEnd
  -> Either String YearFraction
yearFraction = $(ffiCallPureX 'yearFraction) c_yearFraction

foreign import ccall safe "ql.h qlDayCounterYearFraction"
  c_yearFraction :: Ptr CDayCounter -> CDate -> CDate -> CDate -> CDate -> Ptr CString -> IO CYearFraction

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
