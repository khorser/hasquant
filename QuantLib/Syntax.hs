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
import Control.Monad.Trans.Class(lift)
import Control.Monad.Trans.State.Strict(StateT, modify', runStateT)
import Data.Data(Data, gmapM, cast)
import Data.List(isPrefixOf, nub)
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

-- |like 'free1st', but for a target 'reify' can't see — a local @where@\/@let@ binding, or an
-- expression that isn't a name at all (a lambda, a section, an operator) — so the arity is
-- supplied explicitly and the target becomes the generated function's first argument instead.
-- Top-level bindings and typeclass methods don't need this; 'free1st' handles both.
--
-- > -- parRate is a local where-binding here, so 'parRate wouldn't reify
-- > forM curves $ $(free1st' 3) parRate (bondSettle :| ds) dc
free1st' :: Int -> ExpQ
free1st' = freeNth' 1

-- |same as 'free1st'', but frees the second argument instead of the first
free2nd' :: Int -> ExpQ
free2nd' = freeNth' 2

-- |the general form behind 'free1st'\/'free2nd': frees the @i@-th (1-based) argument of a
-- reified function, moving it to the trailing position
--
-- > $(freeNth 3 'f) a1 a2 a4 a3  ==  f a1 a2 a3 a4
freeNth :: Int -> Name -> ExpQ
freeNth i = cutAt [i]

-- |the general form behind 'free1st''\/'free2nd'': like 'freeNth', but with a user-supplied
-- arity instead of one discovered via 'reify', and taking the target as its first argument
-- (see 'free1st'')
freeNth' :: Int -> Int -> ExpQ
freeNth' i = cutAt' [i]

-- |number of arguments a reified signature takes
arity :: Type -> Q Int
arity as = go as
  where
    go (AppT (AppT ArrowT _) x) = (1 +) <$> go x
    go (ForallT _ _ a) = go a
    go (AppT _ _) = return 0
    go (ConT _) = return 0
    go (VarT _) = return 0
    go x = fail $ "QuantLib.Syntax: unsupported signature part: " ++ show x
                  ++ ", full signature: " ++ show as

-- ClassOpI covers typeclass methods: their reified type carries the class context as a
-- ForallT, which 'arity' skips over, so those work just as well as plain bindings here
reifiedArity :: Name -> Q Int
reifiedArity n = do
  info <- reify n
  case info of
    VarI _ as _ -> arity as
    ClassOpI _ as _ -> arity as
    _ -> fail $ "QuantLib.Syntax: " ++ show n ++ " is not a function binding, reified as: "
                ++ show info

checkIndices :: [Int] -> Int -> Q ()
checkIndices is an
  | null is = fail "QuantLib.Syntax: no argument positions given"
  | length (nub is) /= length is = fail $ "QuantLib.Syntax: duplicate argument positions in " ++ show is
  | any (\i -> i < 1 || i > an) is = fail $ "QuantLib.Syntax: position(s) out of range [1," ++ show an ++ "]: " ++ show is
  | otherwise = return ()

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
cutAt is n = reifiedArity n >>= \an -> genCutAt is an n

-- |like 'cutAt', but with a user-supplied arity instead of one discovered via 'reify', for a
-- target 'reify' can't see (same reason as 'free1st''); the target becomes the generated
-- function's first argument
cutAt' :: [Int] -> Int -> ExpQ
cutAt' is an = do
  n <- newName "f"
  LamE [VarP n] <$> genCutAt is an n

isHole :: Name -> Bool
isHole n = "_" `isPrefixOf` nameBase n

-- collected holes are accumulated in reverse order of occurrence, see 'cut'
type HoleQ = StateT [Name] Q

-- a hole appearing inside a *nested* quotation bracket within the cut'd expression would also
-- get replaced, since this doesn't track quotation depth -- not expected to matter for any call
-- site in this codebase, so not worth the extra bookkeeping
replaceHoles :: Exp -> HoleQ Exp
replaceHoles = go
  where
    go :: Exp -> HoleQ Exp
    go (UnboundVarE n) | isHole n = do
      v <- lift (newName "h")
      modify' (v :)
      return (VarE v)
    go e = gmapM step e
      where
        step :: forall d. Data d => d -> HoleQ d
        step x = case cast x of
          Just (ex :: Exp) -> do
            ex' <- go ex
            case cast ex' of
              Just r -> return r
              Nothing -> fail "QuantLib.Syntax.cut: impossible cast"
          Nothing -> gmapM step x

-- |'cut'-style partial application via placeholders (in the spirit of SRFI's @cut@): mark the
-- argument(s) to leave free with a bare @_@ or a named hole (@_x@) -- GHC's own typed-hole
-- syntax, valid in any expression position -- inside a quoted expression. Each hole becomes a
-- fresh trailing lambda parameter, in left-to-right order of occurrence; a hole's name is a
-- label for the reader only, so repeating the same one (@_x ... _x@) yields two independent
-- parameters rather than sharing one. Unlike 'freeNth'\/'cutAt', this never reifies the target,
-- so it works equally well on ordinary functions, typeclass methods, and operators.
--
-- > $(cut [| advance _ (3, Months) Following False |]) `fmap` calendar Null
cut :: ExpQ -> ExpQ
cut eq = do
  e <- eq
  (e', holes) <- runStateT (replaceHoles e) []
  return $ LamE (map VarP (reverse holes)) e'

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
