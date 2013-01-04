{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Instrument.Bond
  (
    Bond
  , bond
  , bond'
  , issueDate
  , maturityDate
  )

where

import Data.Word(Word)
import Data.Time.Calendar(Day)

import Foreign.C.Types(CDouble(CDouble), CUInt(CUInt))
import Foreign.C.String(CString)
import Foreign.Ptr(Ptr, FunPtr)

import System.IO.Unsafe(unsafePerformIO)

import QuantLib.CashFlow.Leg(Leg, CLeg)
import QuantLib.Internal(CDate, withObject, Object, construct, Finalizable, finalize, toQlDateSerialNumber, fromQlDateSerialNumber)
import QuantLib.Time.Calendar(Calendar, CCalendar)

data CBond

type Bond = Object CBond

foreign import ccall safe "ql.h qlBond"
  c_bond :: CUInt -> Ptr CCalendar -> CDate -> Ptr CLeg -> Ptr CString -> IO (Ptr CBond)
foreign import ccall safe "ql.h qlBond2"
  c_bond2 :: CUInt -> Ptr CCalendar -> CDouble -> CDate -> CDate -> Ptr CLeg -> Ptr CString -> IO (Ptr CBond)
foreign import ccall safe "ql.h &qlFreeBond"
  p_freeBond :: FunPtr (Ptr CBond -> IO ())
foreign import ccall safe "ql.h qlBondMaturityDate"
  c_maturityDate :: Ptr CBond -> IO CDate
foreign import ccall safe "ql.h qlBondIssueDate"
  c_issueDate :: Ptr CBond -> IO CDate

instance Finalizable CBond where
  finalize = p_freeBond

-- | (qlBond)
-- these signatures would be more approrpriate (see QuantLib::Bond::Bond)
bond :: Word -> Calendar -> Maybe Day -> Leg -> IO Bond
bond settl cal issue coupons =
  withObject
  cal
  (\c ->
    withObject
    coupons
    (construct . c_bond (fromIntegral settl) c (toQlDateSerialNumber issue)))

bond' :: Word -> Calendar -> Double -> Maybe Day -> Maybe Day -> Leg -> IO Bond
bond' settl cal face maturity issue flows =
  withObject
  cal
  (\c ->
    withObject
    flows
    (construct . c_bond2 (fromIntegral settl) c (realToFrac face) (toQlDateSerialNumber maturity) (toQlDateSerialNumber issue)))

-- |Returns the maturity date of the bond (qlBondMaturityDate)
-- XXX exceptions?
maturityDate :: Bond -> Maybe Day
maturityDate b = fromQlDateSerialNumber $ unsafePerformIO (withObject b c_maturityDate)

-- |Returns the issue date of the bond (qlBondIssueDate)
-- XXX exceptions?
issueDate :: Bond -> Maybe Day
issueDate b = fromQlDateSerialNumber $ unsafePerformIO (withObject b c_issueDate)
