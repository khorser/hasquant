{-# LANGUAGE ForeignFunctionInterface #-}

module QuantLib.Settings(evaluationDate, setEvaluationDate)
where

import Foreign.C.Types
import Foreign.C.String

import Data.Time.Calendar
import Control.Monad

import QuantLib.Internal

foreign import ccall safe "ql.h qlSettingsEvaluationDate"
    c_evaluationDate :: IO CInt
foreign import ccall safe "ql.h qlSettingsSetEvaluationDate"
    c_setEvaluationDate :: CInt -> IO CString

evaluationDate :: IO Day
evaluationDate = liftM fromQlDate c_evaluationDate

setEvaluationDate :: Day -> IO ()
setEvaluationDate x = c_setEvaluationDate (toQlDate x) >>= checkError
