{-# LANGUAGE RankNTypes, ScopedTypeVariables #-}
module QuantLib.Syntax
  (
    free1st
  , free2nd
  , free1st'
  , free2nd'
  , freeNth
  , freeNth'
  , cutAt
  , cutAt'
  , cut
  )
where

import Control.Monad(replicateM)
import Data.Data(Data, gmapM, cast)
import Data.IORef
import Data.List(isPrefixOf)
import Language.Haskell.TH

-- |make a function with the first argument put at the last position, sort of any arity flip to
-- make it easier to chain monadic calls
--
-- > -- advance :: Calendar -> Date -> (Int, TimeUnit) -> BusinessDayConvention -> Bool -> IO Date
-- > calendar Null >>= $(free1st 'advance) d (3, Months) Following False
free1st :: Name -> ExpQ
free1st = freeNth 1

-- |same as 'free1st', but frees the second argument instead of the first
--
-- > -- blackConstantVol :: Calendar -> Date -> Quote -> DayCounter -> IO BlackVolTermStructure
-- > calendar TARGET >>= $(free2nd 'blackConstantVol) settl volQ dc
free2nd :: Name -> ExpQ
free2nd = freeNth 2

-- |like 'free1st', but for a target whose arity can't be discovered via 'reify' (e.g. a
-- typeclass method), so the arity is supplied explicitly instead
--
-- > -- parRate :: HasParRate a => Date -> NonEmpty Date -> DayCounter -> a -> IO Rate, arity 4
-- > forM curves $ $(free1st' 3) parRate (bondSettle :| ds) dc
free1st' :: Int -> ExpQ
free1st' = freeNth' 1

-- |same as 'free1st'', but frees the second argument instead of the first
free2nd' :: Int -> ExpQ
free2nd' = freeNth' 2

genFreeNth :: Int -> Int -> Name -> ExpQ
genFreeNth i an fn = do
  vars <- replicateM an (newName "x")
  let (h, t) = splitAt i $ reverse vars
      (hh, ht) = splitAt (i-1) h
  return $ LamE (map VarP (hh ++ t ++ ht)) (foldr (\v e -> AppE e (VarE v)) (VarE fn) vars)

arity :: Type -> Int
arity as = arity' as
  where
    arity' (AppT (AppT ArrowT _) x) = 1 + arity' x
    arity' (ForallT _ _ a@(AppT _ _)) = arity' a
    arity' (AppT _ _) = 0
    arity' (ConT _) = 0
    arity' (VarT _) = 0
    arity' x = error $ "Unsupported signature part: " ++ show x ++ ", full arguments: " ++ show as

-- |the general form behind 'free1st'\/'free2nd': frees the @i@-th (1-based) argument of a
-- reified function, moving it to the trailing position
--
-- > $(freeNth 3 'f) a1 a2 a4 a3  ==  f a1 a2 a3 a4
freeNth :: Int -> Name -> ExpQ
freeNth i n = do
  VarI _ as _ <- reify n
  genFreeNth i (arity as) n

-- |the general form behind 'free1st''\/'free2nd'': like 'freeNth', but with a user-supplied
-- arity instead of one discovered via 'reify' (needed for typeclass methods, see 'free1st'')
freeNth' :: Int -> Int -> ExpQ
freeNth' i an = do
  n <- newName "f"
  LamE [VarP n] <$> genFreeNth i an n

checkIndices :: [Int] -> Int -> Q ()
checkIndices is an
  | null is = fail "cutAt: no argument positions given"
  | length (nub is) /= length is = fail $ "cutAt: duplicate argument positions in " ++ show is
  | any (\i -> i < 1 || i > an) is = fail $ "cutAt: position(s) out of range [1," ++ show an ++ "]: " ++ show is
  | otherwise = return ()
  where nub = foldr (\x acc -> if x `elem` acc then acc else x : acc) []

genCutAt :: [Int] -> Int -> Name -> ExpQ
genCutAt is an fn = do
  checkIndices is an
  vars <- replicateM an (newName "x")
  let idxVars = zip [1..] vars
      free = [v | (i, v) <- idxVars, i `elem` is]
      bound = [v | (i, v) <- idxVars, i `notElem` is]
  return $ LamE (map VarP (bound ++ free)) (foldl AppE (VarE fn) (map VarE vars))

-- |generalizes 'free1st'\/'free2nd'\/'freeNth': frees an arbitrary subset of argument positions
-- (by 1-based index) instead of a single hardcoded one, moving them to the trailing position in
-- their original relative order
--
-- > -- f :: A -> B -> C -> D -> R
-- > $(cutAt [1,3] 'f) b d a c  ==  f a b c d
cutAt :: [Int] -> Name -> ExpQ
cutAt is n = do
  VarI _ as _ <- reify n
  genCutAt is (arity as) n

-- |like 'cutAt', but with a user-supplied arity instead of one discovered via 'reify' (needed
-- for typeclass methods, same reason as 'freeNth'')
cutAt' :: [Int] -> Int -> ExpQ
cutAt' is an = do
  n <- newName "f"
  LamE [VarP n] <$> genCutAt is an n

isHole :: Name -> Bool
isHole n = "_" `isPrefixOf` nameBase n

-- a hole appearing inside a *nested* quotation bracket within the cut'd expression would also
-- get replaced, since this doesn't track quotation depth -- not expected to matter for any call
-- site in this codebase, so not worth the extra bookkeeping
replaceHoles :: IORef [Name] -> Exp -> Q Exp
replaceHoles ref = go
  where
    go :: Exp -> Q Exp
    go (UnboundVarE n) | isHole n = do
      v <- newName "h"
      runIO (modifyIORef' ref (v :))
      return (VarE v)
    go e = gmapM step e
      where
        step :: forall d. Data d => d -> Q d
        step x = case cast x of
          Just (ex :: Exp) -> do
            ex' <- go ex
            case cast ex' of
              Just r -> return r
              Nothing -> error "QuantLib.Syntax.cut: impossible cast"
          Nothing -> gmapM step x

-- |'cut'-style partial application via placeholders (in the spirit of SRFI's @cut@): mark the
-- argument(s) to leave free with a bare @_@ or a named hole (@_x@) -- GHC's own typed-hole
-- syntax, valid in any expression position -- inside a quoted expression. Each hole becomes a
-- fresh trailing lambda parameter, in left-to-right order of occurrence. Unlike 'freeNth'\/
-- 'cutAt', this never reifies the target, so it works equally well on ordinary functions,
-- typeclass methods, and operators.
--
-- > $(cut [| advance _ (3, Months) Following False |]) `fmap` calendar Null
cut :: ExpQ -> ExpQ
cut eq = do
  e <- eq
  ref <- runIO (newIORef [])
  e' <- replaceHoles ref e
  vars <- reverse <$> runIO (readIORef ref)
  return $ LamE (map VarP vars) e'

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
