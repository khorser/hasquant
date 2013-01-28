{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Internal.Syntax
  (
    args
  , ffiCall
  )
where

import Control.Monad(liftM, liftM2)
import Language.Haskell.TH
import QuantLib.Internal.Date
import QuantLib.Internal.Utils
import QuantLib.Internal.Enum

-- All QLEnum instances should be imported here!
import QuantLib.Compounding()
import QuantLib.Time.BusinessDayConvention()
import QuantLib.Time.Date()
import QuantLib.Time.DateGenerationRule()
import QuantLib.Time.Frequency()
import QuantLib.Time.Unit()

data NestedArg = IntN | DayN | DoubleN | ForeignPtrN
  deriving (Show, Eq)

-- XXX use GADTs/SYB/Uniplate?
data TopArg = IntA | WordA | DayA | StringA | DoubleA
  | OptDayA | ForeignPtrA | OptForeignPtrA
  | ListA NestedArg | ListA2 NestedArg NestedArg
  | EnumA
  deriving (Show, Eq)

isAtomicTop :: Name -> Bool
isAtomicTop x = x `elem` [''Int, ''Word, ''Day, ''String, ''Double]

isEnum :: Name -> Q Bool
isEnum n = do
  ClassI _ instances <- reify ''QLEnum
  return $ n `elem` map getEnumTypeName instances
  where getEnumTypeName (InstanceD [] (AppT _ (ConT x)) []) = x
        getEnumTypeName x = error $ "Error getting QLEnum instances: " ++ show x

nameToTop :: Name -> TopArg
nameToTop n | n == ''Int = IntA
nameToTop n | n == ''Word = WordA
nameToTop n | n == ''Day = DayA
nameToTop n | n == ''String = StringA
nameToTop n | n == ''Double = DoubleA
nameToTop n = error $ "Not supported top type: " ++ show n

nestedNameToTop :: Name -> Q NestedArg
nestedNameToTop n | n == ''Int = return IntN
nestedNameToTop n | n == ''Day = return DayN
nestedNameToTop n | n == ''Double = return DoubleN
nestedNameToTop n =
  tryForeignPtr n >>=
    either (\x -> fail $ "Error parsing nested arg" ++ show x)
      (\_ -> return ForeignPtrN)

topArgs :: Type -> Q TopArg
topArgs (ConT n) | isAtomicTop n = return $ nameToTop n
topArgs (ConT n) = do
  e <- isEnum n
  if e
    then return EnumA
    else tryForeignPtr n >>=
          either (\x -> fail $ "Error parsing top arg: " ++ x)
          (\_ -> return ForeignPtrA)
topArgs (AppT (ConT m) (ConT n)) | m == ''Maybe =
  if n == ''Day
    then return OptDayA
  else
    tryForeignPtr n >>=
      either (\x -> fail $ "Error parsing optional top arg: " ++ x)
        (\_ -> return OptForeignPtrA)
topArgs (AppT ListT (ConT n)) = liftM ListA (nestedNameToTop n)
topArgs (AppT
          ListT
          (AppT
            (AppT (TupleT 2) (ConT n1))
            (ConT n2))) =
              liftM2 ListA2 (nestedNameToTop n1) (nestedNameToTop n2)
topArgs t = fail $ "Unsupported top-level arg type: " ++ show t

data AtomicRet = IntR | WordR | DayR | DoubleR | StringR
  | EnumR | OptDayR | ForeignPtrR
  deriving (Show, Eq)

data RetVal = AtomicRV AtomicRet | IORV AtomicRet
  deriving (Show, Eq)

tryForeignPtr :: Name -> Q (Either String Name)
tryForeignPtr n = do
  r <- reify n
  return $
    case r of
      TyConI (TySynD _ [] (AppT (ConT p) (ConT target)))
        -> if p == ''ForeignPtr
             then Right target
             else Left $ "Unsupported synonym type: " ++ show n
                ++ " reified as " ++ show r
      _ -> Left $ "Unsupported type: " ++ show n ++ " reified as "
              ++ show r

nameToRetVal :: Name -> Q AtomicRet
nameToRetVal n | n == ''Int = return IntR
nameToRetVal n | n == ''Word = return WordR
nameToRetVal n | n == ''Day = return DayR
nameToRetVal n | n == ''Double = return DoubleR
nameToRetVal n | n == ''String = return StringR
nameToRetVal n = do
  e <- isEnum n
  if e
    then return EnumR
    else tryForeignPtr n >>=
          either (\x -> fail $ "Error parsing ret type: " ++ x)
            (\_ -> return ForeignPtrR)

compArgToRetVal :: Type -> Q AtomicRet
compArgToRetVal (AppT (ConT m) (ConT d)) | m == ''Maybe && d == ''Day =
  return OptDayR
compArgToRetVal (ConT n) = nameToRetVal n
compArgToRetVal t = fail $ "Unsupported compound type arg: " ++ show t

compToRetVal :: Type -> Q RetVal
compToRetVal (AppT (ConT n1) t2) | n1 == ''IO =
  liftM IORV $ compArgToRetVal t2
compToRetVal t = liftM AtomicRV $ compArgToRetVal t

-- use WriterT?
args :: Type -> Q ([TopArg], RetVal)
args (AppT (AppT ArrowT t1) t2) = do
  top <- topArgs t1
  (rest, ret) <- args t2
  return (top : rest, ret)
args (ConT n) = liftM ((,) [] . AtomicRV) $ nameToRetVal n
args t@(AppT _ _) = liftM ((,) []) $ compToRetVal t 
args t = fail $ "Unsupported type: " ++ show t

ffiCall :: Name -> Name -> ExpQ
ffiCall hFun cFun = do
  r <- reify hFun
  case r of
    VarI _ ft _ _  -> args ft >>= uncurry (genFfiCall cFun)
    _ -> fail $ "Cannot reify type of " ++ show hFun

genFfiCall :: Name -> [TopArg] -> RetVal -> ExpQ
genFfiCall n a r = genFfiCallImpl (reverse a) [|$(unmarshal (null a) r (varE n)) |]

unmarshalA :: AtomicRet -> ExpQ
unmarshalA IntR    = [|fromIntegral :: CInt -> Int|]
unmarshalA WordR   = [|fromIntegral :: CUInt -> Word|]
unmarshalA DayR    = [|fromQlDate|]
unmarshalA DoubleR = [|realToFrac :: CDouble -> Double|]
unmarshalA StringR = [|undefined|]
unmarshalA EnumR   = [|fromQlEnum|]
unmarshalA OptDayR = [|fromQlDate|]
unmarshalA ForeignPtrR = [|undefined|]

un1 :: Bool -> ExpQ
un1 True = [| ($) |]
un1 False = [| (.) |]

unmarshal :: Bool -> RetVal -> ExpQ -> ExpQ
unmarshal b (AtomicRV r) code = [|$(un1 b) $(unmarshalA r) $ $code|]
unmarshal b (IORV r) code = [|$(un1 b) (liftM $(unmarshalA r)) $ $code|]

marshal :: TopArg -> ExpQ -> ExpQ
marshal IntA code         = [|\x -> $code ((fromIntegral :: Int -> CInt) x)|]
marshal WordA   _code      = [|fromIntegral :: Word -> CUInt |]
marshal DayA _code         = [|fromQlDate|]
marshal StringA _code      = [|undefined|]
marshal DoubleA _code      = [|realToFrac :: Double -> CDouble|]
marshal OptDayA _code      = [|fromQlDate|]
marshal ForeignPtrA _code  = [|withObject|]
marshal OptForeignPtrA _code = [|undefined|]
marshal (ListA _x)  _code  = [|undefined|] 
marshal (ListA2 _x1 _x2) _code = [|undefined|]
marshal EnumA  _code       = [|fromQlEnum|]

genFfiCallImpl :: [TopArg] -> ExpQ -> ExpQ
genFfiCallImpl [] code = code
genFfiCallImpl (a:as) code = genFfiCallImpl as (marshal a code)

{-
{-# LANGUAGE TemplateHaskell #-}
module Main where

import Control.Monad(liftM)
import QuantLib.Types
import QuantLib.Internal.Syntax
import QuantLib.Internal.Utils

data AA = AA | BB deriving (Show, Enum)

--f :: [Int] -> Maybe Day -> [(Day, Double)] -> Frequency -> Bond -> [Day] -> [InterestRate]
--  -> Maybe Schedule -> String -> IO Bond -- -> IO Frequency
f :: CInt
f = 5

fi :: IO CInt
fi = return 6

f1 :: CInt -> CInt
f1 = (+1)

fi1 :: CInt -> IO CInt
fi1 x = return (x + 1)

f2 :: CInt -> CInt -> CInt
f2 = div

ff :: Int
--ff = $(ffiCall 'ff 'f)
ff = (fromIntegral :: CInt -> Int) $ f

ffi :: IO Int
--ffi = $(ffiCall 'ffi 'fi)
ffi = liftM (fromIntegral :: CInt -> Int) $ fi

ff1 :: Int -> Int
--ff1 = $(ffiCall 'ff1 'f1)
ff1 = \x -> (fromIntegral :: CInt -> Int)
  $ f1 ((fromIntegral :: Int -> CInt ) x)

ffi1 :: Int -> IO Int
--ffi1 = $(ffiCall 'ffi1 'fi1)
ffi1 = \x -> liftM (fromIntegral :: CInt -> Int)
  $ fi1 ((fromIntegral :: Int -> CInt ) x)

ff2 :: Int -> Int -> Int
--ff2 = $(ffiCall 'ff2 'f2)
ff2 = \x1 -> \x2 -> (fromIntegral :: CInt -> Int)
  $ f2 ((fromIntegral :: Int -> CInt) x1) ((fromIntegral :: Int -> CInt) x2)

b1 :: Ptr CBond -> IO CInt
b1 _ = return 11

b2 :: Ptr CBond -> Ptr CSchedule -> IO CInt
b2 _ _ = return 12

b3 :: Ptr CBond -> CInt -> Ptr CSchedule -> IO CInt
b3 _ _ _ = return 13

bb1 :: Bond -> IO Int
bb1 = \x -> withObject x (\y -> liftM (fromIntegral :: CInt -> Int) $ b1 y)

bb2 :: Bond -> Schedule -> IO Int
bb2 =
  \x1 ->
    \x2 ->
      withObject x1
        (\y1 ->
          withObject x2
            (\y2 ->
              liftM (fromIntegral :: CInt -> Int) $ b2 y1 y2))

bb3 :: Bond -> Int -> Schedule -> IO Int
bb3 =
  \x1 ->
    \x2 ->
      \x3 ->
        withObject x1
          (\y1 ->
            flip ($) ((fromIntegral :: Int -> CInt) x2)
              (\y2 ->
                withObject x3
                  (\y3 ->
                    liftM (fromIntegral :: CInt -> Int) $ b3 y1 y2 y3)))

main :: IO ()
main = do
  print ff
  ffi >>= print
  print $ ff1 7
  ffi1 8 >>= print
  print $ ff2 10 5
-}
