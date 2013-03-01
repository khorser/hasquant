module QuantLib.Internal.Enum
  (
    QLEnum
  , toQlEnum
  , fromQlEnum
  , QLLitEnum
  , withLitEnum
  , withOptLitEnum
  )
where

import Data.List(elemIndex)
import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Internal.Utils

foreign import ccall safe "ql.h qlEnumerationValue"
  c_values :: CString -> Ptr CUInt -> IO (Ptr CStaticInt)

values :: String -> [CInt]
values ename = if null vals
                 then signalError ("Enumeration " ++ ename ++ " is not known")
                 else map getStaticInt vals
  where vals = unsafePerformIO $
                withCString ename (getArray . c_values)

-- when declaring new QLEnum instances, add them into Internal.Enum too!
class (Enum a, Show a) => QLEnum a

class (Show a) => QLLitEnum a -- enum passed literally as a string to QL

toQlEnum :: (QLEnum a) => String -> a -> CInt
toQlEnum typename x =
  if index >= length vals
    then signalError $ "Constructor " ++ show x ++ " is not found"
    else vals !! index
  where
    index = fromEnum x
    vals = values typename

fromQlEnum :: (QLEnum a) => String -> CInt -> a
fromQlEnum typename x =
  maybe (signalError $ "Unknown enumeration code: " ++ show x)
  toEnum
  (elemIndex x $ values typename)

withLitEnum :: (QLLitEnum a) => a -> (CString -> IO b) -> IO b
withLitEnum = withCString . show

withOptLitEnum :: (QLLitEnum a) => Maybe a -> (CString -> IO b) -> IO b
withOptLitEnum = maybe ($ nullPtr) withLitEnum

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
