{-# LANGUAGE ForeignFunctionInterface,FlexibleInstances #-}
module QuantLib.Internal
  (
    fromQlDateSerialNumber
  , toQlDateSerialNumber
  , c_maxDateSerialNumber
  , c_minDateSerialNumber
  , c_freeString
  , handleExceptions
  , isValid
  , Finalizable
  , finalize
  , NamedSingleton
  , c_construct
  , c_name
  , constructNamed
  , name
  , Object
  , construct
  , withObject
  , CDate
  , toQlEnum
  , fromQlEnum
  )

where

import Control.Exception(throw)
import Control.Monad(liftM)
import Data.List(elemIndex)
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, fromGregorian)
import Data.Typeable(Typeable, typeOf)
import Foreign.C.String(CString, peekCString, withCString)
import Foreign.C.Types(CInt(CInt))
import Foreign.ForeignPtr(ForeignPtr, newForeignPtr, withForeignPtr)
import Foreign.Marshal.Alloc(alloca)
import Foreign.Marshal.Array(peekArray)
import Foreign.Ptr(nullPtr, Ptr, FunPtr)
import Foreign.Storable(peek)
import System.IO.Unsafe(unsafePerformIO)

import QuantLib.Error(Error(Error))

foreign import ccall safe "ql.h qlFreeString"
  c_freeString :: CString -> IO ()

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

newtype Object a = Object{ptr :: ForeignPtr a}

type CDate = Int

-- |Julian day of the QuantLib zero date
qlStart :: Integer
qlStart = minDateJulianDays - fromIntegral c_minDateSerialNumber
            where minDateJulianDays = toModifiedJulianDay
                    $ fromGregorian (fromIntegral c_minYear)
                                    (fromIntegral c_minMonth)
                                    (fromIntegral c_minDay)

toQlDateSerialNumberUnsafe :: Day -> CDate
toQlDateSerialNumberUnsafe x = fromInteger $ toModifiedJulianDay x - qlStart

handleExceptions :: (Ptr CString -> IO a) -> IO a
handleExceptions f =
   alloca $
     \errptr ->
     do r <- f errptr
        msg <- peek errptr
        if msg /= nullPtr 
          then do err <- peekCString msg
                  c_freeString msg
                  throw (Error err)
          else return r

class Finalizable a where
  finalize :: FunPtr (Ptr a -> IO ())

  -- |Run a C function returning a new object that needs a finalizer. The function might signal an error
  construct :: (Ptr CString -> IO (Ptr a)) -> IO (Object a)
  construct f = handleExceptions f >>= liftM Object . newForeignPtr finalize


withObject :: Object a -> (Ptr a -> IO b) -> IO b
withObject o = withForeignPtr (ptr o)

class Finalizable a => NamedSingleton a where
  c_construct :: CString -> Ptr CString -> IO (Ptr a)
  c_name :: Ptr a -> IO CString

  constructNamed :: String -> Object a
  constructNamed n = unsafePerformIO (withCString n $ construct . c_construct)

  name :: Object a -> String
  name c = unsafePerformIO
          $ withForeignPtr
              (ptr c)
              (\cc -> do n <- c_name cc
                         str <- peekCString n
                         c_freeString n
                         return str)

class QLDate a where
  isValid :: a -> Bool
  toQlDateSerialNumber :: a -> CDate
  fromQlDateSerialNumber :: CDate -> a


instance QLDate Day where
  isValid x = num >= c_minDateSerialNumber && num <= c_maxDateSerialNumber
                where num = toQlDateSerialNumberUnsafe x
  -- return Either instead?
  toQlDateSerialNumber x | isValid x = fromInteger $ toModifiedJulianDay x - qlStart
                         | otherwise = throw $ Error ("Invalid QuantLib date: " ++ show x)
  fromQlDateSerialNumber p = ModifiedJulianDay $
                fromIntegral p + qlStart

  

instance QLDate (Maybe Day) where
  isValid = maybe True isValid
  toQlDateSerialNumber = maybe 0 toQlDateSerialNumber
  fromQlDateSerialNumber 0 = Nothing
  fromQlDateSerialNumber x = Just $ fromQlDateSerialNumber x

foreign import ccall safe "ql.h qlEnumerationValue"
  c_values :: CString -> Ptr CInt -> IO (Ptr CInt)

values :: String -> [CInt]
values ename = if null vals
                 then throw $ Error ("Enumeration " ++ ename ++ " is not known")
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
    then throw $ Error ("Constructor " ++ show x ++ " is not found")
    else vals !! index
  where
    index = fromEnum x
    vals = values (show $ typeOf x) 

fromQlEnum :: (Typeable a, Enum a) => CInt -> a
fromQlEnum x = enum
               where enum = result index
                     result Nothing  = throw
                       $ Error ("Unknown enumeration code: " ++ show x)
                     result (Just i) = toEnum i
                     index = elemIndex x $ values (show $ typeOf enum)
               -- NB: intermediate computations are using the type of the
               -- result here, thank laziness (?)
               -- Looks like fixed point operator. Are we abusing the type system?
