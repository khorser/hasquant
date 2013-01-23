{-# LANGUAGE FlexibleInstances,MultiParamTypeClasses #-}
module QuantLib.Internal
  (
  -- types
    CDate
  -- information
  , c_maxDateSerialNumber
  , c_minDateSerialNumber
  -- exceptions
  , signalError
  , handleExceptions
  -- object construction and access
  , Finalizable(..)
  , construct
  , NamedSingleton(..)
  , constructNamed
  , name
  -- utils
  , isValid
  , withObject
  , withObject2
  , withObject3
  , withObject4
  , withObject5
  , withObject6
  , withObject7
  , withObject8
  , maybeWithObject
  , withDays
  , withAmounts
  , withObjects
  , withString2
  , getDynIntArray

  , c_weekday
  -- convertors
  , fromQlDate
  , toQlDate
  , fromQlEnum
  , toQlEnum
  -- re-exporting some popular system stuff
  , withCString
  , CInt(CInt), CDouble(CDouble), CUInt(CUInt)
  , CString
  , Ptr, FunPtr
  , castPtr, castFunPtr
  , fromBool, toBool
  , unsafePerformIO
  , Word
  , ForeignPtr
  -- and the standard day type
  , Day
  )

where

import Control.Exception(throw)
import Data.List(elemIndex)
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, fromGregorian)
import Data.Typeable(Typeable, typeOf)
import Data.Word(Word)

import Foreign.C.String
import Foreign.C.Types
import Foreign.ForeignPtr(ForeignPtr, newForeignPtr, withForeignPtr)
import Foreign.Marshal.Alloc(alloca)
import Foreign.Marshal.Array(peekArray, withArrayLen)
import Foreign.Marshal.Utils(fromBool, toBool)
import Foreign.Ptr(nullPtr, Ptr, FunPtr, castPtr, castFunPtr)
import Foreign.Storable(peek, poke)

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

foreign import ccall safe "ql.h qlWeekday"
  c_weekday :: CInt -> CInt

signalError :: String -> a
signalError = throw . Error

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

withObject :: ForeignPtr a -> (Ptr a -> IO b) -> IO b
withObject = withForeignPtr

maybeWithObject :: Maybe (ForeignPtr a) -> (Ptr a -> IO b) -> IO b
maybeWithObject (Just o) f = withObject o f
maybeWithObject Nothing f  = f nullPtr

withObject2 :: ForeignPtr a1 -> ForeignPtr a2 -> (Ptr a1 -> Ptr a2 -> IO b) -> IO b
withObject2 o1 o2 f = withObject o1 (withObject o2 . f)

withObject3 :: ForeignPtr a1 -> ForeignPtr a2 -> ForeignPtr a3
  -> (Ptr a1 -> Ptr a2 -> Ptr a3 -> IO b) -> IO b
withObject3 o1 o2 o3 f = withObject o1 (withObject2 o2 o3 . f)

withObject4 :: ForeignPtr a1 -> ForeignPtr a2 -> ForeignPtr a3 -> ForeignPtr a4
  -> (Ptr a1 -> Ptr a2 -> Ptr a3 -> Ptr a4 -> IO b) -> IO b
withObject4 o1 o2 o3 o4 f = withObject o1 (withObject3 o2 o3 o4 . f)

withObject5 :: ForeignPtr a1 -> ForeignPtr a2 -> ForeignPtr a3 -> ForeignPtr a4 -> ForeignPtr a5
  -> (Ptr a1 -> Ptr a2 -> Ptr a3 -> Ptr a4 -> Ptr a5 -> IO b) -> IO b
withObject5 o1 o2 o3 o4 o5 f = withObject o1 (withObject4 o2 o3 o4 o5 . f)

withObject6 :: ForeignPtr a1 -> ForeignPtr a2 -> ForeignPtr a3 -> ForeignPtr a4 -> ForeignPtr a5
  -> ForeignPtr a6
  -> (Ptr a1 -> Ptr a2 -> Ptr a3 -> Ptr a4 -> Ptr a5 -> Ptr a6 -> IO b) -> IO b
withObject6 o1 o2 o3 o4 o5 o6 f =
  withObject o1 (withObject5 o2 o3 o4 o5 o6 . f)

withObject7 :: ForeignPtr a1 -> ForeignPtr a2 -> ForeignPtr a3 -> ForeignPtr a4 -> ForeignPtr a5
  -> ForeignPtr a6 -> ForeignPtr a7
  -> (Ptr a1 -> Ptr a2 -> Ptr a3 -> Ptr a4 -> Ptr a5 -> Ptr a6 -> Ptr a7 -> IO b) -> IO b
withObject7 o1 o2 o3 o4 o5 o6 o7 f =
  withObject o1 (withObject6 o2 o3 o4 o5 o6 o7 . f)

withObject8 :: ForeignPtr a1 -> ForeignPtr a2 -> ForeignPtr a3 -> ForeignPtr a4 -> ForeignPtr a5
  -> ForeignPtr a6 -> ForeignPtr a7 -> ForeignPtr a8
  -> (Ptr a1 -> Ptr a2 -> Ptr a3 -> Ptr a4 -> Ptr a5 -> Ptr a6 -> Ptr a7 -> Ptr a8 -> IO b) -> IO b
withObject8 o1 o2 o3 o4 o5 o6 o7 o8 f =
  withObject o1 (withObject7 o2 o3 o4 o5 o6 o7 o8 . f)

withObjects :: [ForeignPtr a] -> (CUInt -> Ptr (Ptr a) -> IO b) -> IO b
-- XXX rewrite using folds?
withObjects objs fn = go objs []
  where go [] ps     = withArrayLen ps (\n p -> fn (fromIntegral n) p)
        go (o:os) ps = withForeignPtr o
                        (\p -> go os (ps ++ [p]))

withDays :: [Day] -> (CUInt -> Ptr CDate -> IO b) -> IO b
withDays days f = withArrayLen
                      (map toQlDate days)
                      (\n d -> f (fromIntegral n) d)

withAmounts :: [Double] -> (CUInt -> Ptr CDouble -> IO b) -> IO b
withAmounts amounts f = withArrayLen
                        (map realToFrac amounts)
                        (\n a -> f (fromIntegral n) a)

withString2 :: String -> String -> (CString -> CString -> IO b) -> IO b
withString2 s1 s2 f = withCString s1 (withCString s2 . f)

getDynIntArray :: (Ptr CInt -> IO (Ptr CInt)) -> IO [CInt]
getDynIntArray = getIntArray c_freeInts

getStaticIntArray :: (Ptr CInt -> IO (Ptr CInt)) -> IO [CInt]
getStaticIntArray = getIntArray (const $ return ())

-- get a function that returns an array of ints, the number of items
-- is returned via the first argument
getIntArray :: (Ptr CInt -> IO ()) -> (Ptr CInt -> IO (Ptr CInt)) -> IO [CInt]
getIntArray fin f =
  alloca
  (\pcnt -> do array <- f pcnt
               count <- peek pcnt
               ints <- peekArray (fromIntegral count) array
               fin array
               return ints)

handleExceptions :: (Ptr CString -> IO a) -> IO a
handleExceptions f =
   alloca $
     \errptr ->
     do poke errptr nullPtr
        r <- f errptr
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
construct :: Finalizable a => (Ptr CString -> IO (Ptr a)) -> IO (ForeignPtr a)
construct f = handleExceptions f >>= newForeignPtr finalize

class Finalizable a => NamedSingleton a where
  c_construct :: CString -> Ptr CString -> IO (Ptr a)
  c_name :: Ptr a -> IO CString

-- XXX ???Create non-finalizable objects and then we won't have to use IO monad
constructNamed :: NamedSingleton a => String -> IO (ForeignPtr a)
constructNamed n = withCString n $ construct . c_construct

name :: NamedSingleton a => ForeignPtr a -> String
name c = unsafePerformIO
          $ withForeignPtr c
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
                withCString ename (getStaticIntArray . c_values)

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
