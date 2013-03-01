{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Time.DayCounter
  (
    actual365Fixed
  , act365Fixed
  , a365Fixed
  , a365F
  , one
  , actualActualISDA
  , actualActual
  , actual365
  , act365
  , a365
  , actAct
  , actual360
  , act360
  , a360
  , thirty360BondBasis
  , bondBasis
  , thirty360
  , threeSixty360
  , thirty360EurobondBasis
  , eurobondBasis
  , thirtyE360
  , thirtyE360EurobondBasis
  , actualActualISMA
  , actualActualBond
  , actualActualAFB
  , actualActualEuro
  , thirty360Italian
  , simple
  , lin30360
  , linACT360
  , linACT365
  , linACTACT
  , linACTACTISDA
  , linACTACTISMA
  , business252
  , thirty360European
  , thirty360USA
  , actualActualAct365
  , actualActualHistorical

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
act365Fixed     :: IO DayCounter
a365Fixed       :: IO DayCounter
a365F           :: IO DayCounter
-- |1/1 day count convention
one             :: IO DayCounter
actualActualISDA:: IO DayCounter
-- |Actual\/Actual day count.
-- The day count can be calculated according to: - the ISDA convention, also known as Actual\/Actual (Historical), Actual\/Actual, Act\/Act, and according to ISDA also Actual\/365, Act\/365, and A\/365; - the ISMA and US Treasury convention, also known as Actual\/Actual (Bond); - the AFB convention, also known as Actual\/Actual (Euro). For more details, refer to http://www.isda.org/publications/pdf/Day-Count-Fracation1999.pdf
actualActual    :: IO DayCounter
actual365       :: IO DayCounter
act365          :: IO DayCounter
a365            :: IO DayCounter
actAct          :: IO DayCounter
-- |Actual\/360 day count convention, also known as Act\/360, or A\/360.
actual360       :: IO DayCounter
act360          :: IO DayCounter
a360            :: IO DayCounter
thirty360USA    :: IO DayCounter
thirty360BondBasis  :: IO DayCounter
bondBasis       :: IO DayCounter
-- |30\/360 day count convention
-- The 30\/360 day count can be calculated according to US, European, or Italian conventions.US (NASD) convention: if the starting date is the 31st of a month, it becomes equal to the 30th of the same month. If the ending date is the 31st of a month and the starting date is earlier than the 30th of a month, the ending date becomes equal to the 1st of the next month, otherwise the ending date becomes equal to the 30th of the same month. Also known as 30\/360, 360\/360, or Bond BasisEuropean convention: starting dates or ending dates that occur on the 31st of a month become equal to the 30th of the same month. Also known as 30E\/360, or Eurobond BasisItalian convention: starting dates or ending dates that occur on February and are grater than 27 become equal to 30 for computational sake.
thirty360       :: IO DayCounter
threeSixty360   :: IO DayCounter
thirty360EurobondBasis:: IO DayCounter
eurobondBasis   :: IO DayCounter
thirtyE360      :: IO DayCounter
thirtyE360EurobondBasis:: IO DayCounter
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
lin30360        :: IO DayCounter
linACT360       :: IO DayCounter
linACT365       :: IO DayCounter
linACTACT       :: IO DayCounter
linACTACTISDA   :: IO DayCounter
linACTACTISMA   :: IO DayCounter
thirty360European:: IO DayCounter

actual365Fixed     = constructNamed "Actual/365 (Fixed)"
act365Fixed        = constructNamed "Act/365 (Fixed)"
a365Fixed          = constructNamed "A/365 (Fixed)"
a365F              = constructNamed "A/365F"
one                = constructNamed "1/1"
actualActualISDA   = constructNamed "Actual/Actual (ISDA)"
actualActual       = constructNamed "Actual/Actual"
actual365          = constructNamed "Actual/365"
act365             = constructNamed "Act/365"
a365               = constructNamed "A/365"
actAct             = constructNamed "Act/Act"
actual360          = constructNamed "Actual/360"
act360             = constructNamed "Act/360"
a360               = constructNamed "A/360"
thirty360BondBasis = constructNamed "30/360 (Bond Basis)"
thirty360USA       = constructNamed "30/360 (USA)"
bondBasis          = constructNamed "Bond Basis"
thirty360          = constructNamed "30/360"
threeSixty360      = constructNamed "360/360"
thirty360EurobondBasis = constructNamed "30/360 (Eurobond Basis)"
eurobondBasis      = constructNamed "Eurobond Basis"
thirtyE360         = constructNamed "30E/360"
thirtyE360EurobondBasis= constructNamed "30E/360 (Eurobond Basis)"
actualActualISMA   = constructNamed "Actual/Actual (ISMA)"
actualActualBond   = constructNamed "Actual/Actual (Bond)"
actualActualAct365    = constructNamed "Actual/Actual (Actual365)"
actualActualAFB    = constructNamed "Actual/Actual (AFB)"
actualActualEuro   = constructNamed "Actual/Actual (Euro)"
actualActualHistorical   = constructNamed "Actual/Actual (Historical)"
thirty360Italian   = constructNamed "30/360 (Italian)"
simple             = constructNamed "Simple"
lin30360           = constructNamed "LIN 30/360"
linACT360          = constructNamed "LIN ACT/360"
linACT365          = constructNamed "LIN ACT/365"
linACTACT          = constructNamed "LIN ACT/ACT"
linACTACTISDA      = constructNamed "LIN ACTACT ISDA"
linACTACTISMA      = constructNamed "LIN ACTACT ISMA"
thirty360European  = constructNamed "30/360 (European)"

-- |Business\/252 day count convention.
foreign import ccall safe "ql.h qlDayCounterBusiness252"
  c_business252 :: Ptr CCalendar -> Ptr CString -> IO (Ptr CDayCounter)
business252     :: Calendar -> IO DayCounter
business252 = $(ffiCall 'business252) c_business252

-- |Returns the number of days between two dates.
dayCount :: DayCounter -> Day -> Day -> IO Int
dayCount = $(ffiCallX 'dayCount) c_dayCount

foreign import ccall safe "ql.h qlDayCounterDayCount"
  c_dayCount :: Ptr CDayCounter -> CDate -> CDate -> Ptr CString -> IO CInt

-- |Returns the period between two dates as a fraction of year.
yearFraction :: DayCounter
  -> Day
  -> Day
  -> Maybe Day -- ^refPeriodStart
  -> Maybe Day -- ^refPeriodEnd
  -> IO YearFraction
yearFraction = $(ffiCallX 'yearFraction) c_yearFraction

foreign import ccall safe "ql.h qlDayCounterYearFraction"
  c_yearFraction :: Ptr CDayCounter -> CDate -> CDate -> CDate -> CDate -> Ptr CString -> IO CYearFraction

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
