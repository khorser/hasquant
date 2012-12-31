module QuantLib.Leg
  (
    Leg
  , leg
  , startDate
  )
where

import Control.Exception(throw)
import Data.List(sortBy)
import Data.Function(on)
import Data.Time.Calendar(Day)
import Foreign.C.Types(CInt(CInt), CDouble)
import Foreign.Marshal.Array(withArray)
import Foreign.Ptr(Ptr, FunPtr)
import Foreign.ForeignPtr
import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Error(Error(Error))
import QuantLib.Internal(CDate, allocateDates, freeDates, fromQlDateSerialNumber)

data CLeg

type Leg = ForeignPtr CLeg

foreign import ccall safe "ql.h qlLeg"
    c_leg :: CInt -> Ptr CDouble -> Ptr (Ptr CDate) -> IO (Ptr CLeg)
foreign import ccall safe "ql.h qlLegStartDate"
    c_legStartDate :: Ptr CLeg -> IO CInt
foreign import ccall safe "ql.h &qlFreeLeg"
    p_freeLeg :: FunPtr (Ptr CLeg -> IO ())

-- | (qlLeg)
leg :: [(Double, Day)] -> Bool -> IO Leg
leg flows s =
  do let sorted = (if s then sortBy (compare `on` snd) else id) flows
     ds <- allocateDates (map snd sorted)
     case ds of
       Left m  -> throw $ Error m
       Right d -> 
        do l <-leg' (fromIntegral $ length sorted) (map (realToFrac . fst) sorted) d
           freeDates d
           newForeignPtr p_freeLeg l

leg' :: CInt -> [CDouble] -> [Ptr CDate] -> IO (Ptr CLeg)
leg' len amounts dates =
  withArray amounts (withArray dates . c_leg len)

-- |Returns the start (i.e. first accrual) date for the given Leg object (qlLegStartDate)
-- XXX Assume that legs are immutable. Otherwise the type shoule be Leg -> IO Day
startDate :: Leg -> Day
startDate l = fromQlDateSerialNumber
  $ unsafePerformIO (withForeignPtr l c_legStartDate)
