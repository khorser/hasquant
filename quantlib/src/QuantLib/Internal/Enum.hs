{-# LANGUAGE MultiParamTypeClasses #-}
module QuantLib.Internal.Enum
  (
    QLEnum
  , toQlEnum
  , fromQlEnum
  , QLLitEnum
  , withEnum
  , getEnum
  , withLitEnum
  , withOptLitEnum
  , values

  , QLObjEnum(..)
  , withObjEnum
  )
where

import Data.List(elemIndex)
import Foreign.Marshal.Utils(maybeWith)

import QuantLib.Internal.Types(Finalizable, QLError(UnknownEnum, EnumConversion, CEnumConversion), CStaticInt(..))
import QuantLib.Internal.Utils

foreign import ccall safe "ql.h qlEnumerationValue"
  c_values :: CString -> Ptr CUInt -> IO (Ptr CStaticInt)

values :: String -> IO [CInt]
values ename = do
  v <- withCString ename (getArray . c_values)
  if null v
     then throwIO $ UnknownEnum ename
     else mapM (return . getStaticInt) v

-- when declaring new QLEnum/QLLitEnum instances, add them into Internal.Enum too!
class (Enum a, Show a) => QLEnum a
-- no Enum constraint on QLLitEnum because some have constructors with arguments
class (Show a) => QLLitEnum a -- enum passed literally as a string to QL

toQlEnum :: (QLEnum a) => String -> a -> IO CInt
toQlEnum typename x = do
  let index = fromEnum x
  vals <- values typename
  if index >= length vals
    then throwIO $ EnumConversion typename (show x)
    else return $ vals !! index

fromQlEnum :: (QLEnum a) => String -> CInt -> IO a
fromQlEnum typename x = do
  v <- values typename
  maybe (throwIO $ CEnumConversion typename (fromIntegral x))
    (return . toEnum)
    (elemIndex x v)

withEnum :: (QLEnum a) => String -> a -> (CInt -> IO b) -> IO b
withEnum n e f = toQlEnum n e >>= f

getEnum :: (QLEnum a) => String -> IO CInt -> IO a
getEnum n x = x >>= fromQlEnum n

withLitEnum :: (QLLitEnum a) => a -> (CString -> IO b) -> IO b
withLitEnum = withCString . show

withOptLitEnum :: (QLLitEnum a) => Maybe a -> (CString -> IO b) -> IO b
withOptLitEnum = maybeWith withLitEnum

-- enum representing a QuantLib C++ object
class (Finalizable o) => QLObjEnum e o where
  enumToObject :: e -> IO (ForeignPtr o)
  objectToEnum :: o -> e

withObjEnum :: (QLObjEnum a o) => a -> (Ptr o -> IO b) -> IO b
withObjEnum x f = enumToObject x >>= (`withObject` f)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
