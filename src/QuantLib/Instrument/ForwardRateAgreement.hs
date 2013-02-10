{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
module QuantLib.Instrument.ForwardRateAgreement
  (
    forwardRateAgreement
  )
where

import QuantLib.Internal.Date
import QuantLib.Internal.Syntax
import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Types
import QuantLib.PositionType

forwardRateAgreement :: Day -- ^valueDate
  -> Day -- ^maturityDate
  -> PositionType -- ^type
  -> Double -- ^strikeForwardRate
  -> Double -- ^notionalAmount
  -> IborIndex -- ^index
  -> Maybe YieldTermStructure -- ^discountCurve
  -> IO ForwardRateAgreement
forwardRateAgreement = $(ffiConstruct 'forwardRateAgreement) c_forwardRateAgreement

foreign import ccall safe "ql.h qlForwardRateAgreement"
  c_forwardRateAgreement :: CDate -> CDate -> CInt -> CDouble -> CDouble -> Ptr CIborIndex -> Ptr CYieldTermStructure -> Ptr CString -> IO (Ptr CForwardRateAgreement)
