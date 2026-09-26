module QuantLib.Internal
  (
    Error(..)

  , Day -- reexport for simplicity
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
  , preArrayWith
  , preIntArray
  , preDoubleArray
  , preCStringArray
  , prePtrArray
  , withEnumArray
  , withIntArray
  , withBoolArray
  , withDoubleArray
  , withRealVector
  , withRealVectorRaw
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
  , peekRealVector
  , borrowRealVector
  , RealVector
  , NonEmptyVector
  , singletonNonEmptyVector
  , consNonEmptyVector
  , nonEmptyVector
  , nonEmptyVectorToVector
  , withNonEmptyRealVector

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
  , RealMatrix(..)
  , boxedRealMatrix
  , realMatrixFromVector
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
import Foreign.ForeignPtr(FinalizerPtr, newForeignPtr, newForeignPtr_, castForeignPtr)
import Foreign.Marshal.Array(peekArray, withArray)
import Foreign.Marshal.Utils(with, toBool, fromBool, withMany)
import Foreign.Storable(peek, poke, peekElemOff, pokeElemOff, Storable)
import Foreign.Marshal.Alloc(alloca)

import Control.Exception(Exception, throwIO, mask, mask_, finally, onException)
import Control.Monad(when, (>=>))
import Data.Time.Calendar(Day(ModifiedJulianDay), toModifiedJulianDay, fromGregorian)
import Data.List.NonEmpty(NonEmpty, toList)

import Data.Vector.Storable(Vector, unsafeFromForeignPtr0)
import qualified Data.Vector.Storable as V

data Error = CPlusPlusException String
           | DateConversion Day
           | EnumConversion String
           deriving (Show, Eq)

instance Exception Error

errorCheck :: Ptr CString -> IO ()
errorCheck p = do
  a <- peek p
  when
    (a /= nullPtr)
    (poke p nullPtr >> peekDynString a >>= throwIO . CPlusPlusException)

-- like alloca but initializes the allocated pointer with zero
preErrorCheck :: (Ptr CString -> IO b) -> IO b
preErrorCheck f = mask_ $ with nullPtr $ \p ->
  f p `finally` (peek p >>= qlFreeString)

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
peekDynString x
  | x == nullPtr = pure "" -- The following errorCheck reports a failed C++ call.
  | otherwise = peekCString x `finally` qlFreeString x

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

-- |Contiguous numeric data for APIs whose natural size is hundreds or thousands
-- of values.  The public element type stays 'Double'; C's @double@ representation
-- is used only at the FFI boundary.
type RealVector = Vector Double

-- |A storable vector known not to be empty.  The constructor is deliberately
-- hidden; build one with 'singletonNonEmptyVector', 'consNonEmptyVector', or
-- 'nonEmptyVector'.
newtype NonEmptyVector a = NonEmptyVector (Vector a)

singletonNonEmptyVector :: Storable a => a -> NonEmptyVector a
singletonNonEmptyVector = NonEmptyVector . V.singleton

consNonEmptyVector :: Storable a => a -> Vector a -> NonEmptyVector a
consNonEmptyVector x = NonEmptyVector . V.cons x

nonEmptyVector :: Storable a => Vector a -> Maybe (NonEmptyVector a)
nonEmptyVector x
  | V.null x = Nothing
  | otherwise = Just (NonEmptyVector x)

nonEmptyVectorToVector :: NonEmptyVector a -> Vector a
nonEmptyVectorToVector (NonEmptyVector x) = x

withNonEmptyRealVector :: NonEmptyVector Double -> ((CUInt, Ptr CDouble) -> IO b) -> IO b
withNonEmptyRealVector (NonEmptyVector x) = withRealVector x

-- |Borrows the vector's storage for one FFI call.  QuantLib copies every
-- input vector it receives, so the vector need not outlive the continuation.
withRealVector :: RealVector -> ((CUInt, Ptr CDouble) -> IO b) -> IO b
withRealVector x f = V.unsafeWith x $ \p -> f (fromIntegral (V.length x), castPtr p)

-- |Like 'withRealVector', for an FFI argument whose length is carried separately.
withRealVectorRaw :: RealVector -> (Ptr CDouble -> IO b) -> IO b
withRealVectorRaw x f = V.unsafeWith x $ f . castPtr

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

-- Protect every output from the FFI return, including arrays not yet converted by c2hs.
preArrayWith :: (CUInt -> Ptr a -> IO ()) -> ((Ptr CUInt, Ptr (Ptr a)) -> IO b) -> IO b
preArrayWith freeFn f = mask_ $ preArray $ \slots@(pl, pp) ->
  f slots `finally` (do n <- peek pl; p <- peek pp; when (p /= nullPtr) (freeFn n p))

preIntArray :: ((Ptr CUInt, Ptr (Ptr CInt)) -> IO b) -> IO b
preIntArray = preArrayWith (const qlFreeInts)

preDoubleArray :: ((Ptr CUInt, Ptr (Ptr CDouble)) -> IO b) -> IO b
preDoubleArray = preArrayWith (const qlFreeDoubles)

preCStringArray :: ((Ptr CUInt, Ptr (Ptr CString)) -> IO b) -> IO b
preCStringArray = preArrayWith qlFreeStringArray

freePtrArray :: (Ptr a -> IO ()) -> CUInt -> Ptr (Ptr a) -> IO ()
freePtrArray freeOne n p = do
  mapM_ (peekElemOff p >=> \x -> when (x /= nullPtr) (freeOne x)) [0 .. fromIntegral n - 1]
  qlFreePointerArray (castPtr p)

prePtrArray :: (Ptr a -> IO ()) -> ((Ptr CUInt, Ptr (Ptr (Ptr a))) -> IO b) -> IO b
prePtrArray = preArrayWith . freePtrArray

-- Clear the slot while masked before taking responsibility for releasing its allocation.
consumeArray :: (CUInt -> Ptr a -> IO ()) -> Ptr CUInt -> Ptr (Ptr a) -> (CUInt -> Ptr a -> IO b) -> IO b
consumeArray freeFn pl pp convert = mask $ \restore -> do
  n <- peek pl
  p <- peek pp
  poke pp nullPtr
  restore (convert n p) `finally` freeFn n p

peekIntArray' :: (CInt -> b) -> Ptr CUInt -> Ptr (Ptr CInt) -> IO [b]
peekIntArray' f pl pp = consumeArray (const qlFreeInts) pl pp $ \n p ->
  map f <$> peekArray (fromIntegral n) p

peekUIntArray :: Ptr CUInt -> Ptr (Ptr CUInt) -> IO [Word]
peekUIntArray pl pp = consumeArray (const qlFreeUInts) pl pp $ \n p ->
  map fromIntegral <$> peekArray (fromIntegral n) p

peekIntArray :: Ptr CUInt -> Ptr (Ptr CInt) -> IO [Int]
peekIntArray = peekIntArray' fromIntegral

peekCStringArray :: Ptr CUInt -> Ptr (Ptr CString) -> IO [String]
peekCStringArray pl pp = consumeArray qlFreeStringArray pl pp $ \n p ->
  peekArray (fromIntegral n) p >>= mapM peekCString

peekBoolArray :: Ptr CUInt -> Ptr (Ptr CInt) -> IO [Bool]
peekBoolArray = peekIntArray' toBool

peekDayArray :: Ptr CUInt -> Ptr (Ptr CInt) -> IO [Day]
peekDayArray = peekIntArray' fromSerial

peekDoubleArray :: Ptr CUInt -> Ptr (Ptr CDouble) -> IO [Double]
peekDoubleArray pl pp = consumeArray (const qlFreeDoubles) pl pp $ \n p ->
  map realToFrac <$> peekArray (fromIntegral n) p

-- |Takes ownership of a C++-allocated @double[]@ result without copying it.
peekRealVector :: Ptr CUInt -> Ptr (Ptr CDouble) -> IO RealVector
peekRealVector pl pp = mask_ $ do
  n <- fromIntegral <$> peek pl
  p <- peek pp
  poke pp nullPtr
  fp <- newForeignPtr qlFreeDoublesFin p `onException` qlFreeDoubles p
  pure (unsafeFromForeignPtr0 (castForeignPtr fp) n)

-- |A non-owning vector view valid only during the C++ callback.
borrowRealVector :: Ptr CDouble -> CUInt -> IO RealVector
borrowRealVector p n = do
  fp <- castForeignPtr <$> newForeignPtr_ p
  pure (unsafeFromForeignPtr0 fp (fromIntegral n))

-- |Convert before freeing: struct fields may borrow buffers owned by the aggregate.
peekStructArray :: Storable a => (a -> IO b) -> (CUInt -> Ptr a -> IO ()) -> Ptr CUInt -> Ptr (Ptr a) -> IO [b]
peekStructArray convert freeFn pl pp = consumeArray freeFn pl pp $ \n p ->
  peekArray (fromIntegral n) p >>= mapM convert

-- |The converter owns an element only on success; cleared slots mark completed handoffs.
peekPtrArray :: (Ptr a -> IO ()) -> (Ptr a -> IO b) -> Ptr CUInt -> Ptr (Ptr (Ptr a)) -> IO [b]
peekPtrArray freeOne peekOne pl pp = mask_ $
  consumeArray (freePtrArray freeOne) pl pp $ \n p ->
    mapM (\i -> do
      raw <- peekElemOff p i
      x <- peekOne raw
      pokeElemOff p i nullPtr
      pure x) [0 .. fromIntegral n - 1]

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

-- |Row-major numeric matrix backed by contiguous storage.  Use this for
-- large dense grids such as regression and volatility-surface data; small
-- process/correlation matrices remain boxed 'Matrix' values; object
-- matrices retain 'Matrix' because their elements need continuation-based FFI
-- marshalling rather than a raw contiguous pointer.
--
-- This representation interoperates directly with @hmatrix@ without making
-- @hasquant@ depend on it: @Numeric.LinearAlgebra.reshape cols
-- realMatrixData@ makes a row-major hmatrix matrix view with no element copy.
-- The reverse conversion through @flatten@ is zero-copy only for a contiguous
-- row-major hmatrix matrix; BLAS-produced or sliced matrices can require a
-- reorder/copy.
data RealMatrix = RealMatrix
  { realMatrixRows :: Word
  , realMatrixColumns :: Word
  , realMatrixData :: RealVector
  }
  deriving (Eq, Show)

-- |Construct a list-backed numeric matrix for small-dimensional APIs such as process
-- correlation and diffusion matrices. Returns a boxed 'Matrix' 'Double', /not/ a
-- 'RealMatrix' -- despite the shared @RealMatrix@ spelling this is not the pair of
-- 'realMatrixFromVector', which is the constructor for the contiguous 'RealMatrix' type.
-- Reach for this one when the dimensions are small and fixed (a correlation or diffusion
-- matrix), and for 'realMatrixFromVector' for large dense numerical grids such as
-- volatility surfaces and multi-asset LSM data.
boxedRealMatrix :: Word -> Word -> [Double] -> Either String (Matrix Double)
boxedRealMatrix = objectMatrix

-- |Construct a row-major numeric matrix backed by contiguous storage. This is the
-- constructor for 'RealMatrix'; for a small correlation\/diffusion matrix use
-- 'boxedRealMatrix', which yields a boxed 'Matrix' 'Double' instead.
realMatrixFromVector :: Word -> Word -> RealVector -> Either String RealMatrix
realMatrixFromVector rows cols d
  | matrixDimensionsMatch rows cols (V.length d) = Right $ RealMatrix rows cols d
  | otherwise = Left $ "Data length " ++ show (V.length d)
      ++ " does not match dimensions " ++ show rows ++ "x" ++ show cols

objectMatrix :: Word -> Word -> [a] -> Either String (Matrix a)
objectMatrix rows cols d
  | matrixDimensionsMatch rows cols (length d) = Right $ Matrix rows cols d
  | otherwise = Left $ "Data length " ++ show (length d)
      ++ " does not match dimensions " ++ show rows ++ "x" ++ show cols

-- |Checks a matrix shape without overflowing the public 'Word' dimensions.
matrixDimensionsMatch :: Word -> Word -> Int -> Bool
matrixDimensionsMatch rows cols dataLength =
  toInteger rows * toInteger cols == toInteger dataLength

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
