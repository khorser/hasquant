module QuantLib.Internal
  (
    Day -- reexport for simplicity
  , minDate
  , maxDate

  -- marshalling helpers
  , prePtr
  , preErrorCheck
  , errorCheck

  , fromMaybeBool
  , toMaybeBool
  , peekDynString
  , peekEnum
  , peekDouble
  , preEnum
  , preNum
  , preArray
  , withEnumArray
  , withIntArray
  , withBoolArray
  , withDoubleArray
  , withNonEmptyDoubleArray
  , withDoubleArrayRaw
  , withBoolArrayRaw
  , withDayPtr
  , withStringArray
  , peekCStringArray
  , fromEnumQuantity
  , toEnumQuantity
  , fromEnumDouble
  , toEnumDouble
  , fromEnumC
  , toEnumC

  , withDay
  , toDay
  , withMaybeDay
  , fromMaybeInt
  , toMaybeDay
  , peekDayArray
  , peekBoolArray
  , withDayArray
  , peekDoubleArray
  , peekDoubleVector

  , toSerial
  , fromSerial
  , qlSavedSettings
  , qlFreeSavedSettings
  , fromMaybeDouble
  , fromMaybeEnum
  , fromMaybeEnumQuantity
  , peekIntArray
  , peekIntArray'
  , peekUIntArray
  , peekWord
  , peekStructArray
  , peekPtrArray
  , Matrix(..)
  , realMatrix
  , objectMatrix
  , qlNullInteger
  , qlFreeAdditionalResults

  , uncurryNested
  , zipWith6
  )
where

import Foreign.C.Types(CUInt(..), CInt(..), CDouble(..))
import Foreign.C.String(CString, peekCString, withCString)
import Foreign.Ptr(Ptr, nullPtr, castPtr)
import Foreign.ForeignPtr(FinalizerPtr, newForeignPtr)
import Foreign.Marshal.Array(peekArray, withArray)
import Foreign.Marshal.Utils(with, toBool, fromBool, withMany)
import Foreign.Storable(peek, Storable)
import Foreign.Marshal.Alloc(alloca)

import Control.Exception(throwIO)
import Control.Monad(when)
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, fromGregorian)
import Data.List.NonEmpty(NonEmpty, toList)

import Data.Vector.Storable(Vector, unsafeFromForeignPtr0)

import QuantLib.Type(Error(DateConversion, CPlusPlusException))

errorCheck :: Ptr CString -> IO ()
errorCheck p = do
  a <- peek p
  when
    (a /= nullPtr)
    ((peekCString a <* qlFreeString a) >>= throwIO . CPlusPlusException)

-- like alloca but initializes the allocated pointer with zero
preErrorCheck :: (Ptr (Ptr a) -> IO b) -> IO b
preErrorCheck = with nullPtr

fromMaybeBool :: Maybe Bool -> CInt
fromMaybeBool = maybe (-1) fromBool

foreign import ccall safe "ql.h qlNullInteger" qlNullInteger :: CInt
foreign import ccall safe "ql.h qlNullReal" qlNullReal :: CDouble

fromMaybeInt :: (Integral a, Integral b) => Maybe a -> b
fromMaybeInt = maybe (fromIntegral qlNullInteger) fromIntegral

fromMaybeDouble :: Maybe Double -> CDouble
fromMaybeDouble = maybe qlNullReal realToFrac

-- |Marshals a Maybe of a plain by-value C++ enum whose lowest member maps to 0
-- (true of every by-value enum bound so far) as a C int, using -1 as the
-- ext::nullopt sentinel -- mirrors fromMaybeBool's convention.
fromMaybeEnum :: Enum a => Maybe a -> CInt
fromMaybeEnum = maybe (-1) (fromIntegral . fromEnum)

-- |'Nothing' emits the enum's -1 sentinel (same convention as 'fromMaybeEnum'), paired with a
-- placeholder quantity of 0 -- for enums like 'TimeUnit' that start at 0 and can't self-sentinel.
fromMaybeEnumQuantity :: Enum a => Maybe (Word, a) -> (CInt, CInt)
fromMaybeEnumQuantity = maybe (0, -1) fromEnumQuantity

toMaybeBool :: CInt -> Maybe Bool
toMaybeBool x = if x == -1 then Nothing else Just $ toBool x

peekDynString :: CString -> IO String
peekDynString x = peekCString x <* qlFreeString x

peekEnum :: (Enum a) => Ptr CInt -> IO a
peekEnum x = toEnum . fromIntegral <$> peek x

peekDouble :: Ptr CDouble -> IO Double
peekDouble x = realToFrac <$> peek x

peekWord :: Ptr CUInt -> IO Word
peekWord x = fromIntegral <$> peek x

-- initialize pointer to a enum with a valid value before passing it to the function
preEnum :: (Storable a, Bounded a) => (Ptr a -> IO b) -> IO b
preEnum = with minBound

preNum :: (Storable a, Num a) => (Ptr a -> IO b) -> IO b
preNum = with 0

foreign import ccall safe "ql.h qlFreeString" qlFreeString :: CString -> IO ()
foreign import ccall safe "ql.h qlFreeInts" qlFreeInts :: Ptr CInt -> IO ()
foreign import ccall safe "ql.h qlFreeUInts" qlFreeUInts :: Ptr CUInt -> IO ()
foreign import ccall safe "ql.h qlFreeDoubles" qlFreeDoubles :: Ptr CDouble -> IO ()
foreign import ccall safe "ql.h &qlFreeDoubles" qlFreeDoublesFin :: FinalizerPtr CDouble
foreign import ccall safe "ql.h qlFreePointerArray" qlFreePointerArray :: Ptr (Ptr ()) -> IO ()
foreign import ccall safe "ql.h qlFreeAdditionalResults" qlFreeAdditionalResults :: CUInt -> Ptr () -> IO ()
foreign import ccall safe "ql.h qlFreeStringArray" qlFreeStringArray :: CUInt -> Ptr CString -> IO ()
foreign import ccall safe "ql.h qlSavedSettings" qlSavedSettings :: IO (Ptr ())
foreign import ccall safe "ql.h qlFreeSavedSettings" qlFreeSavedSettings :: Ptr () -> IO ()

withLArray :: (Storable b) => (a -> b) -> [a] -> ((CUInt, Ptr b) -> IO c) -> IO c
withLArray c x f = withArray (map c x) (\px -> f (fromIntegral $ length x, px))

withEnumArray :: (Enum a) => [a] -> ((CUInt, Ptr CInt) -> IO b) -> IO b
withEnumArray = withLArray (fromIntegral . fromEnum)

withIntArray :: (Integral a, Num n, Storable n) => [a] -> ((CUInt, Ptr n) -> IO b) -> IO b
withIntArray = withLArray fromIntegral

withBoolArray :: [Bool] -> ((CUInt, Ptr CInt) -> IO b) -> IO b
withBoolArray = withLArray fromBool

withDoubleArray :: [Double] -> ((CUInt, Ptr CDouble) -> IO b) -> IO b
withDoubleArray = withLArray realToFrac

withNonEmptyDoubleArray :: NonEmpty Double -> ((CUInt, Ptr CDouble) -> IO b) -> IO b
withNonEmptyDoubleArray x = withLArray realToFrac (toList x)

withDoubleArrayRaw :: [Double] -> (Ptr CDouble -> IO b) -> IO b
withDoubleArrayRaw x = withArray (map realToFrac x)

withBoolArrayRaw :: [Bool] -> (Ptr CInt -> IO b) -> IO b
withBoolArrayRaw x = withArray (map fromBool x)

withDayArray :: [Day] -> ((CUInt, Ptr CInt) -> IO b) -> IO b
withDayArray x f = mapM toSerial x >>= (`withArray` (\px -> f (fromIntegral $ length x, px)))

withDayPtr :: [Day] -> (Ptr CInt -> IO a) -> IO a
withDayPtr x f = mapM toSerial x >>= (`withArray` f)

-- |An array of plain C strings, for a function taking a @std::vector<std::string>@-shaped
-- argument as a flat @(count, char**)@ pair (the input-side counterpart of 'peekCStringArray'
-- below) -- first needed for @SecondaryCosts@' string keys (@QuantLib.Instrument.Energy@).
withStringArray :: [String] -> ((CUInt, Ptr CString) -> IO b) -> IO b
withStringArray xs f = withMany withCString xs (\ps -> withArray ps (\p -> f (fromIntegral (length xs), p)))

prePtr :: (Storable a) => (Ptr a -> IO b) -> IO b
prePtr = alloca

preArray :: ((Ptr CUInt, Ptr (Ptr a)) -> IO b) -> IO b
preArray f = with 0 $
  \x -> with nullPtr $
    \y -> f (x, y)

peekIntArray' :: (CInt -> b) -> Ptr CUInt -> Ptr (Ptr CInt) -> IO [b]
peekIntArray' f pl pp = do
  l <- peek pl
  p <- peek pp
  map f <$> peekArray (fromIntegral l) p <* qlFreeInts p

peekUIntArray :: Ptr CUInt -> Ptr (Ptr CUInt) -> IO [Word]
peekUIntArray pl pp = do
  l <- peek pl
  p <- peek pp
  map fromIntegral <$> peekArray (fromIntegral l) p <* qlFreeUInts p

peekIntArray :: Ptr CUInt -> Ptr (Ptr CInt) -> IO [Int]
peekIntArray = peekIntArray' fromIntegral

-- |An array of freshly heap-allocated (@DUP@'d) C strings -- the output-side counterpart of
-- 'withStringArray'. Each element is read via 'peekCString' and the whole array (including every
-- individual string) is then released via 'qlFreeStringArray' in one call, mirroring
-- 'peekDoubleArray'\/'peekIntArray'\''s read-then-free shape.
peekCStringArray :: Ptr CUInt -> Ptr (Ptr CString) -> IO [String]
peekCStringArray pl pp = do
  l <- peek pl
  p <- peek pp
  raws <- peekArray (fromIntegral l) p
  strs <- mapM peekCString raws
  strs <$ qlFreeStringArray l p

peekBoolArray :: Ptr CUInt -> Ptr (Ptr CInt) -> IO [Bool]
peekBoolArray = peekIntArray' toBool

peekDayArray :: Ptr CUInt -> Ptr (Ptr CInt) -> IO [Day]
peekDayArray = peekIntArray' fromSerial

peekDoubleArray :: Ptr CUInt -> Ptr (Ptr CDouble) -> IO [Double]
peekDoubleArray pl pp = do
  l <- peek pl
  p <- peek pp
  map realToFrac <$> peekArray (fromIntegral l) p <* qlFreeDoubles p

peekDoubleVector :: Ptr CUInt -> Ptr (Ptr CDouble) -> IO (Vector CDouble)
peekDoubleVector pl pp = unsafeFromForeignPtr0 <$> (peek pp >>= newForeignPtr qlFreeDoublesFin) <*> (fromIntegral <$> peek pl)

-- |Like 'peekIntArray'\''/'peekDoubleArray', but for an array of a C struct rather than a C
-- primitive: reads the length and pointer out-params, walks the array via 'peekArray' (so the
-- element type just needs a 'Storable' instance -- e.g. one built from c2hs @{#get#}@/@{#sizeof#}@
-- hooks), converts every element via @convert@, /then/ hands the whole array to @freeFn@ to
-- release. The conversion must run before the free -- unlike 'peekIntArray'\''/'peekDoubleArray',
-- whose elements are self-contained primitives, a struct element read here may itself own
-- further heap buffers (e.g. a @char*@/@double*@ field) that @convert@ still needs to dereference
-- (via 'peekCString'/'peekArray' etc.); freeing first would leave it reading already-freed
-- memory. @freeFn@ takes the element count because some frees need it (e.g.
-- 'qlFreeAdditionalResults'); one that doesn't can ignore it.
peekStructArray :: Storable a => (a -> IO b) -> (CUInt -> Ptr a -> IO ()) -> Ptr CUInt -> Ptr (Ptr a) -> IO [b]
peekStructArray convert freeFn pl pp = do
  l <- peek pl
  p <- peek pp
  raws <- peekArray (fromIntegral l) p
  results <- mapM convert raws
  results <$ freeFn l p

-- |Like 'peekStructArray' but for a @T**@ array of C++-owned pointers to live objects: peeks the
-- length/pointer out-params, converts each raw pointer to a live Haskell value via @peekOne@
-- (installing that value's own finalizer over the pointee), then frees only the array spine via
-- 'qlFreePointerArray' -- not the pointees, whose lifetime @peekOne@ has now taken over.
peekPtrArray :: (Ptr a -> IO b) -> Ptr CUInt -> Ptr (Ptr (Ptr a)) -> IO [b]
peekPtrArray peekOne pl pp = do
  l <- peek pl
  p <- peek pp
  ptrs <- peekArray (fromIntegral l) p
  xs <- mapM peekOne ptrs
  xs <$ qlFreePointerArray (castPtr p)

fromEnumQuantity :: (Enum a, Integral b, Integral c) => (b, a) -> (CInt, c)
fromEnumQuantity (x, u) = (fromIntegral x, fromIntegral $ fromEnum u)

toEnumQuantity :: (Enum a, Integral b, Integral c) => (CInt, c) -> (b, a)
toEnumQuantity (x, u) = (fromIntegral x, toEnum $ fromIntegral u)

fromEnumDouble :: (Enum a, Integral c) => (Double, a) -> (CDouble, c)
fromEnumDouble (x, u) = (realToFrac x, fromIntegral $ fromEnum u)

toEnumDouble :: (Enum a, Integral c) => (CDouble, c) -> (Double, a)
toEnumDouble (x, u) = (realToFrac x, toEnum $ fromIntegral u)

foreign import ccall safe "ql.h qlMinYear" qlMinYear :: CInt
foreign import ccall safe "ql.h qlMinMonth" qlMinMonth :: CInt
foreign import ccall safe "ql.h qlMinDay" qlMinDay :: CInt
foreign import ccall safe "ql.h qlMinDateSerialNumber" qlMinDateSerialNumber :: CInt
foreign import ccall safe "ql.h qlMaxDateSerialNumber" qlMaxDateSerialNumber :: CInt

-- |Julian day of the QuantLib zero date
qlStart :: CInt
qlStart = minDateJulianDays - qlMinDateSerialNumber
  where minDateJulianDays = toModifiedJulianDay' $ fromGregorian (fromIntegral qlMinYear) (fromIntegral qlMinMonth) (fromIntegral qlMinDay)

toModifiedJulianDay' :: Day -> CInt
toModifiedJulianDay' = fromIntegral . toModifiedJulianDay

fromSerial :: CInt -> Day
fromSerial x = ModifiedJulianDay $ fromIntegral (x + qlStart)

dayIsValid :: Day -> Bool
dayIsValid x = s >= qlMinDateSerialNumber && s <= qlMaxDateSerialNumber
  where s = toModifiedJulianDay' x - qlStart

toSerial :: Day -> IO CInt
toSerial x | dayIsValid x = return $ toModifiedJulianDay' x - qlStart
           | otherwise = throwIO $ DateConversion x

withDay :: Day -> (CInt -> IO a) -> IO a
withDay x f = toSerial x >>= f

toDay :: CInt -> Day
toDay = fromSerial

withMaybeDay :: Maybe Day -> (CInt -> IO a) -> IO a
withMaybeDay x f = maybe (f 0) (`withDay` f) x

-- |Unlike the -1 sentinel used by 'fromMaybeBool'/'fromMaybeEnum'/'toMaybeBool', the
-- absent-date sentinel is 0: QuantLib serial 0 is not a representable date (serials
-- start at 'qlMinDateSerialNumber'), so it is free to mean "no date". This matches
-- 'withMaybeDay', which passes 0 in the other direction.
toMaybeDay :: CInt -> Maybe Day
toMaybeDay 0 = Nothing
toMaybeDay x = Just $ fromSerial x

-- |earliest allowed date in QuantLib
minDate :: Day
minDate = fromSerial qlMinDateSerialNumber

-- |latest date allowed in QuantLib
maxDate :: Day
maxDate = fromSerial qlMaxDateSerialNumber

data Matrix a = Matrix {matrixRows::Word, matrixColumns::Word, matrixData::[a]}
  deriving (Eq, Show)

-- |'objectMatrix' specialised to 'Double'. Kept as a separate name for callers that
-- need the element type pinned; the check and construction are identical.
realMatrix :: Word -> Word -> [Double] -> Either String (Matrix Double)
realMatrix = objectMatrix

objectMatrix :: Word -> Word -> [a] -> Either String (Matrix a)
objectMatrix rows cols d
  | rows * cols == fromIntegral (length d) = Right $ Matrix rows cols d
  | otherwise = Left $ "Data length " ++ show (length d)
      ++ " does not match dimensions " ++ show rows ++ "x" ++ show cols

-- just a generic implementation to help when it's difficult to have Enum declaration due to complex module deps
fromEnumC :: (Enum a, Integral b) => a -> b
fromEnumC = fromIntegral . fromEnum

-- output-direction counterpart to 'fromEnumC', for a {#fun#} returning a bare enum value
-- (not through a pointer out-param, see 'peekEnum' for that case) across the same module-dep boundary
toEnumC :: (Enum a, Integral b) => b -> a
toEnumC = toEnum . fromIntegral

uncurryNested :: (a -> b -> c -> d) -> (a, (b, c)) -> d
uncurryNested f (x, (y, z)) = f x y z

-- |'Prelude' only goes up to 'zipWith3'; this fills the gap for unpacking a C-side
-- structure-of-parallel-arrays result into one Haskell record/tuple per element.
zipWith6 :: (a -> b -> c -> d -> e -> f -> g) -> [a] -> [b] -> [c] -> [d] -> [e] -> [f] -> [g]
zipWith6 f (a:as) (b:bs) (c:cs) (d:ds) (e:es) (g:gs) = f a b c d e g : zipWith6 f as bs cs ds es gs
zipWith6 _ _ _ _ _ _ _ = []

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
