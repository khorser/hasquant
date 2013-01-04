{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Time.DayCounter
  (
    DayCounter
  , name
  , CDayCounter

  , dayCounter
  , noDayCounter
  , actual365Fixed
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
  )

where

import Foreign.C.String(CString)
import Foreign.Ptr(Ptr, FunPtr)

import QuantLib.Internal(Object, Finalizable, finalize, c_construct, NamedSingleton, c_name, name, constructNamed)

data CDayCounter

type DayCounter = Object CDayCounter

foreign import ccall safe "ql.h qlDayCounter"
  c_dayCounter :: CString -> Ptr CString -> IO (Ptr CDayCounter)
foreign import ccall safe "ql.h &qlFreeDayCounter"
  p_freeDayCounter :: FunPtr (Ptr CDayCounter -> IO ())
foreign import ccall safe "ql.h qlDayCounterName"
  c_dayCounterName :: Ptr CDayCounter -> IO CString

instance Finalizable CDayCounter where
  finalize = p_freeDayCounter

instance NamedSingleton CDayCounter where
  c_construct = c_dayCounter
  c_name = c_dayCounterName

dayCounter      ::DayCounter
noDayCounter    ::DayCounter
actual365Fixed  ::DayCounter
act365Fixed     ::DayCounter
a365Fixed       ::DayCounter
a365F           ::DayCounter
one             ::DayCounter
actualActualISDA::DayCounter
actualActual    ::DayCounter
actual365       ::DayCounter
act365          ::DayCounter
a365            ::DayCounter
actAct          ::DayCounter
actual360       ::DayCounter
act360          ::DayCounter
a360            ::DayCounter
thirty360BondBasis  ::DayCounter
bondBasis       ::DayCounter
thirty360       ::DayCounter
threeSixty360   ::DayCounter
thirty360EurobondBasis::DayCounter
eurobondBasis   ::DayCounter
thirtyE360      ::DayCounter
thirtyE360EurobondBasis::DayCounter
actualActualISMA::DayCounter
actualActualBond::DayCounter
actualActualAFB ::DayCounter
actualActualEuro::DayCounter
thirty360Italian::DayCounter
simple          ::DayCounter
lin30360        ::DayCounter
linACT360       ::DayCounter
linACT365       ::DayCounter
linACTACT       ::DayCounter
linACTACTISDA   ::DayCounter
linACTACTISMA   ::DayCounter
business252     ::DayCounter

dayCounter         = constructNamed "DayCounter"
noDayCounter       = constructNamed "NoDayCounter"
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
bondBasis          = constructNamed "Bond Basis"
thirty360          = constructNamed "30/360"
threeSixty360      = constructNamed "360/360"
thirty360EurobondBasis = constructNamed "30/360 (Eurobond Basis)"
eurobondBasis      = constructNamed "Eurobond Basis"
thirtyE360         = constructNamed "30E/360"
thirtyE360EurobondBasis= constructNamed "30E/360 (Eurobond Basis)"
actualActualISMA   = constructNamed "Actual/Actual (ISMA)"
actualActualBond   = constructNamed "Actual/Actual (Bond)"
actualActualAFB    = constructNamed "Actual/Actual (AFB)"
actualActualEuro   = constructNamed "Actual/Actual (Euro)"
thirty360Italian   = constructNamed "30/360 (Italian)"
simple             = constructNamed "Simple"
lin30360           = constructNamed "LIN 30/360"
linACT360          = constructNamed "LIN ACT/360"
linACT365          = constructNamed "LIN ACT/365"
linACTACT          = constructNamed "LIN ACT/ACT"
linACTACTISDA      = constructNamed "LIN ACTACT ISDA"
linACTACTISMA      = constructNamed "LIN ACTACT ISMA"
business252        = constructNamed "Business252"
