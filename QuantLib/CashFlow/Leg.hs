{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.CashFlow.Leg
  (
    Leg
  , leg
  , startDate
  , CLeg
  , ptr
  )
where

import Control.Monad(liftM)
import Data.Time.Calendar(Day)

import Foreign.C.Types(CInt(CInt), CDouble)
import Foreign.C.String(CString)
import Foreign.ForeignPtr(ForeignPtr, withForeignPtr)
import Foreign.Marshal.Array(withArray)
import Foreign.Ptr(Ptr, FunPtr)

import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Internal(handleExceptions, construct, fromQlDateSerialNumber, toQlDateSerialNumber, Finalizable, finalize)

data CLeg

newtype Leg = Leg{ptr::ForeignPtr CLeg}

foreign import ccall safe "ql.h qlLeg"
  c_leg :: CInt -> Ptr CDouble -> Ptr CInt -> Ptr CString -> IO (Ptr CLeg)
foreign import ccall safe "ql.h qlLegStartDate"
  c_legStartDate :: Ptr CLeg -> Ptr CString -> IO CInt
foreign import ccall safe "ql.h &qlFreeLeg"
  p_freeLeg :: FunPtr (Ptr CLeg -> IO ())

instance Finalizable CLeg where
  finalize = p_freeLeg

legM :: IO (ForeignPtr CLeg) -> IO Leg
legM = liftM Leg

-- | (qlLeg)
leg :: [(Double, Day)] -> IO Leg
leg flows = legM . construct
            $ leg' (fromIntegral $ length amounts)
                   (map realToFrac amounts)
                   (map toQlDateSerialNumber dates)
  where (amounts, dates) = unzip flows

leg' ::CInt -> [CDouble] -> [CInt] -> Ptr CString -> IO (Ptr CLeg)
leg' len amounts dates e =
  withArray
  amounts
  (\ams -> (withArray
            dates
            (\ds -> c_leg len ams ds e)))

-- |Returns the start (i.e. first accrual) date for the given Leg object (qlLegStartDate)
-- XXX assuming legs are immutable
startDate :: Leg -> Day
startDate l = fromQlDateSerialNumber $ unsafePerformIO (withForeignPtr (ptr l) (handleExceptions . c_legStartDate))
