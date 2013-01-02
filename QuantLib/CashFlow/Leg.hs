{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.CashFlow.Leg
  (
    Leg
  , leg
  , startDate
  )
where

import Data.Time.Calendar(Day)

import Foreign.C.Types(CInt(CInt), CDouble)
import Foreign.C.String(CString)
import Foreign.ForeignPtr(ForeignPtr, newForeignPtr, withForeignPtr)
import Foreign.Marshal.Array(withArray)
import Foreign.Ptr(Ptr, FunPtr)

import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Internal(handleExceptions, fromQlDateSerialNumber, toQlDateSerialNumber)

data CLeg

type Leg = ForeignPtr CLeg

foreign import ccall safe "ql.h qlLeg"
    c_leg :: CInt -> Ptr CDouble -> Ptr CInt -> Ptr CString -> IO (Ptr CLeg)
foreign import ccall safe "ql.h qlLegStartDate"
    c_legStartDate :: Ptr CLeg -> Ptr CString -> IO CInt
foreign import ccall safe "ql.h &qlFreeLeg"
    p_freeLeg :: FunPtr (Ptr CLeg -> IO ())

-- | (qlLeg)
leg :: [(Double, Day)] -> IO Leg
leg flows =
  do l <- handleExceptions
            $ leg' (fromIntegral $ length amounts)
                   (map realToFrac amounts)
                   (map toQlDateSerialNumber dates)
     newForeignPtr p_freeLeg l
  where (amounts, dates) = unzip flows

leg' ::CInt -> [CDouble] -> [CInt] -> Ptr CString -> IO (Ptr CLeg)
leg' len amounts dates e =
  withArray
  amounts
  (\ams -> (withArray
            dates
            (\ds -> c_leg len ams ds e)))

-- |Returns the start (i.e. first accrual) date for the given Leg object (qlLegStartDate)
-- XXX Assuming that legs are immutable. Otherwise we will need to add IO to the type
startDate :: Leg -> Day
startDate l = fromQlDateSerialNumber $ unsafePerformIO
                (withForeignPtr l startDate')

startDate' :: Ptr CLeg -> IO CInt
startDate' = handleExceptions . c_legStartDate
