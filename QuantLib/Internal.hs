{-# LANGUAGE ForeignFunctionInterface,FlexibleInstances #-}
module QuantLib.Internal
  (
  -- types
    Object
  , CDate
  -- information
  , c_maxDateSerialNumber
  , c_minDateSerialNumber
  -- memory management
  , c_freeString
  , c_freeInts
  -- exceptions
  , signalError
  , handleExceptions
  -- object construction and access
  , Finalizable
  , finalize
  , construct
  , NamedSingleton
  , c_construct
  , c_name
  , constructNamed
  , name
  -- utils
  , isValid
  , withObject
  , withObject2
  , withObject3
  , withObject4
  , withDays
  , withAmounts
  , withObjects
  -- convertors
  , fromQlDate
  , toQlDate
  , fromQlEnum
  , toQlEnum
  -- re-exporting some popular FFI stuff
  , CInt(CInt), CDouble(CDouble), CUInt(CUInt), CString, Ptr, FunPtr
  -- and standard day class
  , Day
  )

where

import Control.Exception(throw)
import Control.Monad(liftM)
import Data.List(elemIndex)
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, fromGregorian)
import Data.Typeable(Typeable, typeOf)

import Foreign.C.String
import Foreign.ForeignPtr(ForeignPtr, newForeignPtr, withForeignPtr)
import Foreign.C.Types
import Foreign.Marshal.Alloc(alloca)
import Foreign.Marshal.Array(peekArray, withArrayLen)
import Foreign.Ptr(nullPtr, Ptr, FunPtr)
import Foreign.Storable(peek)

import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Error(Error(Error))

foreign import ccall safe "ql.h qlFreeString"
  c_freeString :: CString -> IO ()
foreign import ccall safe "ql.h qlFreeInts"
  c_freeInts :: Ptr CInt -> IO ()

foreign import ccall safe "ql.h qlMinDateSerialNumber"
  c_minDateSerialNumber :: CDate
foreign import ccall safe "ql.h qlMaxDateSerialNumber"
  c_maxDateSerialNumber :: CDate
foreign import ccall safe "ql.h qlMinYear"
  c_minYear :: CInt
foreign import ccall safe "ql.h qlMinMonth"
  c_minMonth :: CInt
foreign import ccall safe "ql.h qlMinDay"
  c_minDay :: CInt

signalError :: String -> a
signalError = throw . Error

newtype Object a = Object{ptr :: ForeignPtr a}

type CDate = CInt

-- |Julian day of the QuantLib zero date
qlStart :: Integer
qlStart = minDateJulianDays - fromIntegral c_minDateSerialNumber
            where minDateJulianDays = toModifiedJulianDay
                    $ fromGregorian (fromIntegral c_minYear)
                                    (fromIntegral c_minMonth)
                                    (fromIntegral c_minDay)

toQlDateUnsafe :: Day -> CDate
toQlDateUnsafe x = fromIntegral $ toModifiedJulianDay x - qlStart

withObject :: Object a -> (Ptr a -> IO b) -> IO b
withObject = withForeignPtr . ptr

withObject2 :: Object a1 -> Object a2 -> (Ptr a1 -> Ptr a2 -> IO b) -> IO b
withObject2 o1 o2 f = withObject o1 (withObject o2 . f)

withObject3 :: Object a1 -> Object a2 -> Object a3
  -> (Ptr a1 -> Ptr a2 -> Ptr a3 -> IO b) -> IO b
withObject3 o1 o2 o3 f = withObject o1 (withObject2 o2 o3 . f)

withObject4 :: Object a1 -> Object a2 -> Object a3 -> Object a4
  -> (Ptr a1 -> Ptr a2 -> Ptr a3 -> Ptr a4 -> IO b) -> IO b
withObject4 o1 o2 o3 o4 f = withObject o1 (withObject3 o2 o3 o4 . f)

withObjects :: [Object a] -> (CInt -> Ptr (Ptr a) -> IO b) -> IO b
-- XXX rewrite using fold?
withObjects objs fn = go objs []
  where go (o:os) ps = withForeignPtr
                        (ptr o)
                        (\p -> go os (ps ++ [p]))
        go _ ps = withArrayLen ps (\n p -> fn (fromIntegral n) p)

withDays :: [Day] -> (CInt -> Ptr CDate -> IO b) -> IO b
withDays days f = withArrayLen
                      (map toQlDate days)
                      (\n d -> f (fromIntegral n) d)

withAmounts :: [Double] -> (CInt -> Ptr CDouble -> IO b) -> IO b
withAmounts amounts f = withArrayLen
                        (map realToFrac amounts)
                        (\n a -> f (fromIntegral n) a)

handleExceptions :: (Ptr CString -> IO a) -> IO a
handleExceptions f =
   alloca $
     \errptr ->
     do r <- f errptr
        msg <- peek errptr
        if msg /= nullPtr 
          then do err <- peekCString msg
                  c_freeString msg
                  signalError err
          else return r

class Finalizable a where
  finalize :: FunPtr (Ptr a -> IO ())

-- |Run a C function returning a new object that needs a finalizer.
-- The function might signal an error
construct :: Finalizable a => (Ptr CString -> IO (Ptr a)) -> IO (Object a)
construct f = handleExceptions f >>= liftM Object . newForeignPtr finalize

class Finalizable a => NamedSingleton a where
  c_construct :: CString -> Ptr CString -> IO (Ptr a)
  c_name :: Ptr a -> IO CString

constructNamed :: NamedSingleton a => String -> IO (Object a)
constructNamed n = withCString n $ construct . c_construct

name :: NamedSingleton a => Object a -> String
name c = unsafePerformIO
          $ withForeignPtr
              (ptr c)
              (\cc -> do n <- c_name cc
                         str <- peekCString n
                         c_freeString n
                         return str)

class QLDate a where
  isValid :: a -> Bool
  toQlDate :: a -> CDate
  fromQlDate :: CDate -> a

instance QLDate Day where
  isValid x = num >= c_minDateSerialNumber && num <= c_maxDateSerialNumber
                where num = toQlDateUnsafe x
  -- return Either instead?
  toQlDate x | isValid x = fromIntegral $ toModifiedJulianDay x - qlStart
                         | otherwise = signalError ("Invalid QuantLib date: " ++ show x)
  fromQlDate p = ModifiedJulianDay $ fromIntegral p + qlStart

instance QLDate (Maybe Day) where
  isValid = maybe True isValid
  toQlDate = maybe 0 toQlDate
  fromQlDate 0 = Nothing
  fromQlDate x = Just $ fromQlDate x

foreign import ccall safe "ql.h qlEnumerationValue"
  c_values :: CString -> Ptr CInt -> IO (Ptr CInt)

values :: String -> [CInt]
values ename = if null vals
                 then signalError ("Enumeration " ++ ename ++ " is not known")
                 else vals
  where vals = unsafePerformIO $
                withCString
                ename 
                (\n -> alloca $
                           \pcount ->
                           do v <- c_values n pcount
                              count <- peek pcount
                              peekArray (fromIntegral count) v)

toQlEnum :: (Typeable a, Enum a, Show a) => a -> CInt
toQlEnum x =
  if index >= length vals
    then signalError ("Constructor " ++ show x ++ " is not found")
    else vals !! index
  where
    index = fromEnum x
    vals = values (show $ typeOf x) 

fromQlEnum :: (Typeable a, Enum a) => CInt -> a
-- NB: intermediate computations are using the type of the result:
fromQlEnum x = enum
               where enum = result index
                     result Nothing  =
                       signalError ("Unknown enumeration code: " ++ show x)
                     result (Just i) = toEnum i
                     index = elemIndex x $ values (show $ typeOf enum)
