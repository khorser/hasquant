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

import Foreign.C.String(withCString, CString, peekCString)
import Foreign.ForeignPtr(ForeignPtr, withForeignPtr)
import Foreign.Ptr(Ptr, FunPtr)

import QuantLib.Internal(c_freeString, Finalizable, finalize, construct)

import System.IO.Unsafe(unsafePerformIO)

data CDayCounter

type DayCounter = ForeignPtr CDayCounter

foreign import ccall safe "ql.h qlDayCounter"
    c_dayCounter :: CString -> Ptr CString -> IO (Ptr CDayCounter)
foreign import ccall safe "ql.h &qlFreeDayCounter"
    p_freeDayCounter :: FunPtr (Ptr CDayCounter -> IO ())
foreign import ccall safe "ql.h qlDayCounterName"
    c_dayCounterName :: Ptr CDayCounter -> IO CString

instance Finalizable CDayCounter
  where finalize = p_freeDayCounter

constructDayCounter :: String -> IO DayCounter
constructDayCounter cname = withCString cname $ construct . c_dayCounter

name :: DayCounter -> String
name c = unsafePerformIO
          $ withForeignPtr
              c
              (\cc -> do n <- c_dayCounterName cc
                         str <- peekCString n
                         c_freeString n
                         return str)

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

dayCounter         = unsafePerformIO $ constructDayCounter "DayCounter"
noDayCounter       = unsafePerformIO $ constructDayCounter "NoDayCounter"
actual365Fixed     = unsafePerformIO $ constructDayCounter "Actual/365 (Fixed)"
act365Fixed        = unsafePerformIO $ constructDayCounter "Act/365 (Fixed)"
a365Fixed          = unsafePerformIO $ constructDayCounter "A/365 (Fixed)"
a365F              = unsafePerformIO $ constructDayCounter "A/365F"
one                = unsafePerformIO $ constructDayCounter "1/1"
actualActualISDA   = unsafePerformIO $ constructDayCounter "Actual/Actual (ISDA)"
actualActual       = unsafePerformIO $ constructDayCounter "Actual/Actual"
actual365          = unsafePerformIO $ constructDayCounter "Actual/365"
act365             = unsafePerformIO $ constructDayCounter "Act/365"
a365               = unsafePerformIO $ constructDayCounter "A/365"
actAct             = unsafePerformIO $ constructDayCounter "Act/Act"
actual360          = unsafePerformIO $ constructDayCounter "Actual/360"
act360             = unsafePerformIO $ constructDayCounter "Act/360"
a360               = unsafePerformIO $ constructDayCounter "A/360"
thirty360BondBasis = unsafePerformIO $ constructDayCounter "30/360 (Bond Basis)"
bondBasis          = unsafePerformIO $ constructDayCounter "Bond Basis"
thirty360          = unsafePerformIO $ constructDayCounter "30/360"
threeSixty360      = unsafePerformIO $ constructDayCounter "360/360"
thirty360EurobondBasis = unsafePerformIO $ constructDayCounter "30/360 (Eurobond Basis)"
eurobondBasis      = unsafePerformIO $ constructDayCounter "Eurobond Basis"
thirtyE360         = unsafePerformIO $ constructDayCounter "30E/360"
thirtyE360EurobondBasis= unsafePerformIO $ constructDayCounter "30E/360 (Eurobond Basis)"
actualActualISMA   = unsafePerformIO $ constructDayCounter "Actual/Actual (ISMA)"
actualActualBond   = unsafePerformIO $ constructDayCounter "Actual/Actual (Bond)"
actualActualAFB    = unsafePerformIO $ constructDayCounter "Actual/Actual (AFB)"
actualActualEuro   = unsafePerformIO $ constructDayCounter "Actual/Actual (Euro)"
thirty360Italian   = unsafePerformIO $ constructDayCounter "30/360 (Italian)"
simple             = unsafePerformIO $ constructDayCounter "Simple"
lin30360           = unsafePerformIO $ constructDayCounter "LIN 30/360"
linACT360          = unsafePerformIO $ constructDayCounter "LIN ACT/360"
linACT365          = unsafePerformIO $ constructDayCounter "LIN ACT/365"
linACTACT          = unsafePerformIO $ constructDayCounter "LIN ACT/ACT"
linACTACTISDA      = unsafePerformIO $ constructDayCounter "LIN ACTACT ISDA"
linACTACTISMA      = unsafePerformIO $ constructDayCounter "LIN ACTACT ISMA"
business252        = unsafePerformIO $ constructDayCounter "Business252"
