module QuantLib.Leg
  (
    Leg
  , leg
  , startDate
  )
where

import Control.Monad(when)
import Control.Exception(throw)
import Data.List(sortBy)
import Data.Function(on)
import Data.Time.Calendar(Day)
import Foreign.C.Types(CInt(CInt), CDouble)
import Foreign.C.String(CString, peekCString)
import Foreign.ForeignPtr
import Foreign.Marshal.Alloc(alloca)
import Foreign.Marshal.Array(withArray)
import Foreign.Ptr(Ptr, FunPtr, nullPtr)
import Foreign.Storable(peek)
import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Error(Error(Error))
import QuantLib.Internal(CDate, c_freeString, allocateDates, freeDates, fromQlDateSerialNumber)

data CLeg

type Leg = ForeignPtr CLeg

foreign import ccall safe "ql.h qlLeg"
    c_leg :: CInt -> Ptr CDouble -> Ptr (Ptr CDate) -> Ptr CString -> IO (Ptr CLeg)
foreign import ccall safe "ql.h qlLegStartDate"
    c_legStartDate :: Ptr CLeg -> IO CInt
foreign import ccall safe "ql.h &qlFreeLeg"
    p_freeLeg :: FunPtr (Ptr CLeg -> IO ())

-- | (qlLeg)
leg :: [(Double, Day)] -> Bool -> IO Leg
leg flows s =
  do when (null flows) $ throw (Error "Empty list of flows")
     let sorted = (if s then sortBy (compare `on` snd) else id) flows
     ds <- allocateDates (map snd sorted)
     case ds of
       Left m  -> throw $ Error m
       Right d -> alloca $
                    \errptr ->
                    do l <-leg' (fromIntegral $ length sorted) (map (realToFrac . fst) sorted) d errptr
                       freeDates d
                       if l == nullPtr 
                         then do msg <- peek errptr
                                 err <- peekCString msg
                                 c_freeString msg
                                 throw $ Error err
                          else newForeignPtr p_freeLeg l

leg' :: CInt -> [CDouble] -> [Ptr CDate] -> Ptr CString -> IO (Ptr CLeg)
leg' len amounts dates e =
  withArray
    amounts
    (\ams -> (withArray
                dates
                (\ds -> c_leg len ams ds e)))

-- |Returns the start (i.e. first accrual) date for the given Leg object (qlLegStartDate)
-- XXX Assuming that legs are immutable. Otherwise the type shoule be Leg -> IO Day
startDate :: Leg -> Day
startDate l = fromQlDateSerialNumber
  $ unsafePerformIO (withForeignPtr l c_legStartDate)
