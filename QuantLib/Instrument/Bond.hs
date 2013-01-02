{-# LANGUAGE ForeignFunctionInterface,EmptyDataDecls #-}
module QuantLib.Instrument.Bond
  (
    Bond
  , bond
  , issueDate
  , maturityDate
  )

where

import Data.Word(Word)
import Data.Time.Calendar(Day)

import Foreign.C.Types(CInt(CInt), CDouble(CDouble), CUInt(CUInt))
import Foreign.C.String(CString)
import Foreign.ForeignPtr(ForeignPtr, withForeignPtr)
import Foreign.Ptr(Ptr, FunPtr)

import System.IO.Unsafe(unsafePerformIO)

import QuantLib.CashFlow.Leg(Leg, CLeg)
import QuantLib.Internal(Finalizable, finalize, construct, toQlDateSerialNumber, fromQlDateSerialNumber)
import QuantLib.Time.Calendar(Calendar, CCalendar)

data CBond

type Bond = ForeignPtr CBond

foreign import ccall safe "ql.h qlBond"
    c_bond :: CUInt -> Ptr CCalendar -> CDouble -> CInt -> CInt -> Ptr CLeg -> Ptr CString -> IO (Ptr CBond)
foreign import ccall safe "ql.h &qlFreeBond"
    p_freeBond :: FunPtr (Ptr CBond -> IO ())
foreign import ccall safe "ql.h qlBondMaturityDate"
    c_maturityDate :: Ptr CBond -> IO CInt
foreign import ccall safe "ql.h qlBondIssueDate"
    c_issueDate :: Ptr CBond -> IO CInt

instance Finalizable CBond
  where finalize = p_freeBond

-- | (qlBond)
-- these signatures would be more approrpriate (see QuantLib::Bond::Bond)
--bond :: Word -> Calendar -> Maybe Day {-issue-} -> Maybe Leg -> IO Bond
--bond :: Word -> Calendar -> Double -> Day -> Maybe Day -> Maybe Leg -> IO Bond
bond :: Word -> Calendar -> Double -> Day -> Day -> Leg -> IO Bond
bond settl cal face maturity issue flows =
  withForeignPtr
  cal
  (\c ->
    withForeignPtr
    flows
    (construct . c_bond (fromIntegral settl) c (realToFrac face) (toQlDateSerialNumber maturity) (toQlDateSerialNumber issue)))

-- |Returns the maturity date of the bond (qlBondMaturityDate)
-- XXX exceptions?
maturityDate :: Bond -> Day
maturityDate b = fromQlDateSerialNumber $ unsafePerformIO (withForeignPtr b c_maturityDate)

-- |Returns the issue date of the bond (qlBondIssueDate)
-- XXX exceptions?
issueDate :: Bond -> Day
issueDate b = fromQlDateSerialNumber $ unsafePerformIO (withForeignPtr b c_issueDate)
