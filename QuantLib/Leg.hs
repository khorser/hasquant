{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Leg
  (
    Leg
  , leg
  , startDate
  )
where

import Control.Monad(when)
import Control.Exception(throw)
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
import QuantLib.Internal(c_freeString, fromQlDateSerialNumber, toQlDateSerialNumber)

data CLeg

type Leg = ForeignPtr CLeg

foreign import ccall safe "ql.h qlLeg"
    c_leg :: Ptr CString -> CInt -> Ptr CDouble -> Ptr CInt -> IO (Ptr CLeg)
foreign import ccall safe "ql.h qlLegStartDate"
    c_legStartDate :: Ptr CLeg -> IO CInt
foreign import ccall safe "ql.h &qlFreeLeg"
    p_freeLeg :: FunPtr (Ptr CLeg -> IO ())

-- | (qlLeg)
leg :: [(Double, Day)] -> IO Leg
leg flows =
  do when (null flows) $ throw (Error "Empty list of flows")
     alloca $
       \errptr ->
       do l <-leg' errptr
                   (fromIntegral $ length amounts)
                   (map realToFrac amounts)
                   (map toQlDateSerialNumber dates)
          if l == nullPtr 
            then do msg <- peek errptr
                    err <- peekCString msg
                    c_freeString msg
                    throw $ Error err
            else newForeignPtr p_freeLeg l
  where amounts = map fst flows
        dates   = map snd flows

leg' :: Ptr CString -> CInt -> [CDouble] -> [CInt] -> IO (Ptr CLeg)
leg' e len amounts dates = withArray amounts (withArray dates . c_leg e len)

-- |Returns the start (i.e. first accrual) date for the given Leg object (qlLegStartDate)
-- XXX Assuming that legs are immutable. Otherwise we will need to add IO to the type
startDate :: Leg -> Day
startDate l = fromQlDateSerialNumber
  $ unsafePerformIO (withForeignPtr l c_legStartDate)
