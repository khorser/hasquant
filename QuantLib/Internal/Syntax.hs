-- TemplateHaskellQuotes, not TemplateHaskell: dropping the quotation brackets in favour of raw
-- constructors left only 'name / ''Name quotes, which the narrower extension covers
{-# LANGUAGE TemplateHaskellQuotes, LambdaCase #-}
module QuantLib.Internal.Syntax
  (
    CrossEnumSpec(..)
  , deriveCrossEnum
  , IborConstructorSpec(..)
  , deriveIborConstructor
  , deriveOptionsRecord
  ) where
import Language.Haskell.TH.Syntax
import Language.Haskell.TH.Lib(DecsQ, TypeQ, ExpQ, conP, plainTV)
import Data.List(isPrefixOf, isSuffixOf)
import Control.Monad((>=>))

-- All three derive functions below build their output as raw Dec/Con/Exp/Pat constructors
-- rather than quotation brackets or the Q combinators from TH.Lib, so the shape of what is
-- generated is visible in one style throughout. Names inside the generated code still come
-- from 'name / ''Name quotes, which resolve at *this* module's scope exactly as a quotation
-- bracket would, so nothing is lost to capture by dropping the brackets.
--
-- Two constructors resist this and stay as TH.Lib combinators, both for the same reason --
-- template-haskell changed their arity inside the GHC range this package supports (8.10's
-- 2.16 through 9.10's 2.22), so a literal application of either fails to compile on one end
-- or the other:
--   * ConP gained a [Type] field for visible type application in 2.18 (GHC 9.2) -- see conPat.
--   * TyVarBndr gained a flag parameter in 2.17, so PlainTV took a second argument -- hence
--     plainTV in deriveOptionsRecord.
--
-- Every generated top-level name (the merged ADTs, the mapper/ordinal/tenor functions, the
-- options record and its default value) goes through mkName rather than newName *by design*:
-- these are exactly the names the splice site then refers to by hand, so they must not be
-- freshened. newName is used only where it belongs -- pattern variables inside the generated
-- clauses, which nothing outside refers to.

-- the one non-portable Pat constructor, see the note above
conPat :: Name -> [Pat] -> Q Pat
conPat n ps = conP n (map pure ps)

arrowT :: Type -> Type -> Type
arrowT a = AppT (AppT ArrowT a)

pairT :: Type -> Type -> Type
pairT a = AppT (AppT (TupleT 2) a)

-- TupE has taken [Maybe Exp] (for tuple sections) since template-haskell 2.16, i.e. across
-- the whole supported GHC range, so unlike ConP/PlainTV it needs no combinator
pairE :: Exp -> Exp -> Exp
pairE a b = TupE [Just a, Just b]

fromEnumE :: Exp -> Exp
fromEnumE = AppE (VarE 'fromEnum)

-- One data constructor of a reified plain data type, plus its argument types.
normalConstructor :: Con -> Q (Name, [BangType])
normalConstructor (NormalC dCon dConArgs) = return (dCon, dConArgs)
normalConstructor c = fail $ "Unsupported constructor: " ++ show c

-- An explicit case rather than a refutable `(TyConI (DataD ...)) <- reify x` pattern bind:
-- handing this a newtype, a type synonym or a class would otherwise fail in Q's MonadFail
-- with a "Pattern match failure" naming neither the argument nor what was actually found.
getConstructors :: Name -> Q [(Name, [BangType])] -- [(data constructor, constructor args)]
getConstructors x = reify x >>= \case
  TyConI (DataD _ _tCon _ _ dCons _) -> mapM normalConstructor dCons
  info -> fail $ "Expected a plain data declaration for " ++ show x ++ ", got: " ++ show info

-- what a main enum value's sub-choice looks like, once we go find the type named
-- <mainValue><subSuffix>: nothing there at all, a proper enum to cross-product with,
-- or just a `type X = Bool` marker (see the deriveCrossEnum comment below)
data SubKind = NoSub | EnumSub [Name] | BoolSub

classifySub :: String -> Q SubKind
classifySub d = lookupTypeName d >>= maybe (return NoSub) (reify >=> classify)
  where
    classify (TyConI (DataD _ _ _ _ dCons _)) = EnumSub . map fst <$> mapM normalConstructor dCons
    classify (TyConI (TySynD _ _ (ConT b))) | b == ''Bool = return BoolSub
    classify info = fail $ "deriveCrossEnum: unsupported sub-type declaration for " ++ d ++ ": " ++ show info

-- Strips the "<Prefix>__" that a c2hs `add prefix = "Prefix__"` puts on every constructor of
-- a generated enum. Takes the Name rather than its nameBase purely so the failure can say
-- which constructor it choked on -- the type it came from isn't recoverable from a Name.
stripEnumPrefix :: Name -> String
stripEnumPrefix name = go (nameBase name)
  where
    go str@(_:cs)
      | "__" `isPrefixOf` str = drop 2 str
      | otherwise = go cs
    -- error, not fail: this is pure, called from pure positions (concatNames, dropIborSentinel).
    -- It still surfaces at compile time, since TH forces it while building the splice's output.
    go [] = error $ "Expected a c2hs enum constructor carrying a \"Prefix__\" prefix, but "
                    ++ show name ++ " has no __ separator"

-- The body baked into the catch-all clause of every generated dispatch function: those
-- functions map a constructor back to its C enum ordinal(s), which the "extra" constructors
-- (built from their own dedicated C shim) don't have. It's a bug if this ever fires, so the
-- message names the generated function that fired it.
unenumerableError :: String -> Body
unenumerableError fnName = NormalB (AppE (VarE 'error) (LitE (StringL msg)))
  where msg = "Internal error: " ++ fnName ++
              " called on a non-enumerable data constructor, probably an extra one"

-- merge a set of enums into a big one providing a function to map values back to ordinal numbers of original enums
-- e.g. for mainEnum data CalendarCountry = Country__Australia | Country__UnitedStated,
-- subEnum suffix "Market" and UnitedStatesMarket = UnitedStates__NYSE | UnitedStates__Settlement
-- NB I use prefixes separated from the main entry with underscore, in final enum they are stripped off
-- the function will build Australia | UnitedStatesNYSE | UnitedStatesSettlement
-- initially I constructed calendars with Australia | ...| UnitedStates UnitedStatesMarket where UnitedStatesMarket = NYSE | Settlement
-- but too many country calendars contain Settlement and UnitedStates UnitedStatesSettlement
-- (or Actual365Fixed Actual365FixedStandard) looks really awful
--
-- for every main value I go look for a type named <mainValue><subSuffix>, and there are three
-- possible outcomes (classifySub above): nothing by that name -> plain nullary constructor, as
-- above; a real enum -> cross-product like above; or a `type <mainValue><subSuffix> = Bool`
-- synonym -> this main value doesn't have a fixed set of named sub-values at all, it just wraps
-- whatever Bool the caller passes in (e.g. Actual360's includeLastDay flag), so instead of picking
-- a named sub-constructor I give it a single constructor with a runtime Bool field. That's also why
-- caseClauses can't reuse enumVal's conE trick for these: enumVal grabs a sub-value that's fixed at
-- compile time (a named constructor), but a Bool only exists once someone calls the generated
-- constructor, so its clause has to bind a pattern variable and fromEnum that at runtime instead.
-- stripEnumPrefix doesn't need to know about any of this -- it's still only ever run on the
-- __-containing main enum name, never on the Bool value itself (True/False have no __ in them).
--
-- what comes out the other end (the three Decs returned below): a merged data type named
-- resName holding all of the above plus the extra constructors verbatim, and a mapper function
-- named mapper :: resName -> (Int, Int) that turns any of its non-extra constructors back into
-- (ordinal of the main value, ordinal of the sub value) -- that pair is exactly what the two-int
-- C dispatch functions (qlDayCounter, qlCalendar, ...) expect, so callers just go
-- `uncurry qlDayCounter $ mapDayCounter x`. Extra constructors have no such pair (they're built
-- from their own dedicated C shim instead), so mapper blows up on them via the defaultClause --
-- it's a bug if that ever actually fires.
-- A record rather than five positional arguments, for the same reason as IborConstructorSpec
-- below: resName/mapperFn/subSuffix are three interchangeable Strings and mainEnum/extraType
-- two interchangeable Names, so a transposition type-checks and silently generates the wrong
-- thing.
data CrossEnumSpec = CrossEnumSpec
  { crossTypeName :: String   -- ^the merged ADT to generate
  , crossMapperFn :: String   -- ^generated @\<ADT\> -> (Int, Int)@ main/sub ordinal pair
  , crossMainEnum :: Name     -- ^the main C enum
  , crossSubSuffix :: String  -- ^appended to a stripped main value to find its sub-type
  , crossExtraType :: Name    -- ^data type holding the non-enumerable extra constructors
  }

deriveCrossEnum :: CrossEnumSpec -> DecsQ
deriveCrossEnum spec = do
  mainValues <- map fst <$> getConstructors (crossMainEnum spec)

  mergedValues <- concat <$> mapM (\d -> do -- (mainName, subName, []), the third member holds constructor arguments (extras, or a lone Bool for BoolSub)
    sub <- classifySub (stripEnumPrefix d ++ crossSubSuffix spec)
    return $ case sub of
      NoSub -> [(d, Nothing, [])]
      EnumSub vals -> zip3 (repeat d) (map Just vals) (repeat [])
      BoolSub -> [(d, Nothing, [(Bang NoSourceUnpackedness SourceStrict, ConT ''Bool)])]) mainValues

  extraConstructors <- map (\(con, args) -> (con, Nothing, args)) <$> getConstructors (crossExtraType spec)

  caseClauses <- mapM mkClause mergedValues

  let defaultClause = Clause [WildP] (unenumerableError (crossMapperFn spec)) []
      dataDecl = DataD [] resNameType [] Nothing (map (\(x, y, a) -> NormalC (concatNames x y) a) (mergedValues ++ extraConstructors)) []
      mapperSignature = SigD mapperName (arrowT (ConT resNameType) (pairT (ConT ''Int) (ConT ''Int)))
      mapperBody = FunD mapperName (caseClauses ++ [defaultClause])

  return [dataDecl, mapperSignature, mapperBody]

  where concatNames :: Name -> Maybe Name -> Name
        concatNames x y = mkName (stripEnumPrefix x ++ maybe "" stripEnumPrefix y)
        resNameType = mkName (crossTypeName spec)
        mapperName = mkName (crossMapperFn spec)
        enumVal :: Maybe Name -> Exp
        enumVal Nothing = LitE (IntegerL 0)
        enumVal (Just n) = fromEnumE (ConE n)
        mkClause :: (Name, Maybe Name, [BangType]) -> Q Clause
        mkClause (mainVal, subVal, []) = do
          pat <- conPat (concatNames mainVal subVal) []
          return $ Clause [pat] (NormalB (pairE (fromEnumE (ConE mainVal)) (enumVal subVal))) []
        mkClause (mainVal, Nothing, [_]) = do
          x <- newName "x"
          pat <- conPat (concatNames mainVal Nothing) [VarP x]
          return $ Clause [pat] (NormalB (pairE (fromEnumE (ConE mainVal)) (fromEnumE (VarE x)))) []
        mkClause (mainVal, _, _) = fail $ "deriveCrossEnum: unsupported sub-choice shape for " ++ show mainVal

-- Unlike deriveCrossEnum's cross-product of two ordinal dimensions (a main enum times a
-- per-value sub-enum/bool), this concatenates several *sibling* enums -- normalEnum,
-- dailyEnum, onEnum -- each of which contributes one fixed constructor "shape" to a single
-- merged ADT, plus one flat Int dispatch ordinal per value (their positions in the shared
-- flat C array), computed here in Haskell rather than trusted from the C side. The three
-- enums are each independent, plain, zero-based C enums (no cross-enum value chaining); the
-- first two may carry a trailing sentinel constructor whose stripped name ends in "Last"
-- (e.g. IborIndexTypeLast), which exists purely as an "insert real values above this line"
-- marker in the C header and is dropped here via dropIborSentinel -- both to exclude it from
-- the merged ADT and so its group's real (sentinel-excluded) length becomes the next group's
-- ordinal offset, with no count ever hand-written on either side of the FFI boundary.
data IborShape = ShapeTenor | ShapeDailyTenor | ShapeOvernight

dropIborSentinel :: [(Name, [BangType])] -> [(Name, [BangType])]
dropIborSentinel = filter (not . ("Last" `isSuffixOf`) . stripEnumPrefix . fst)

-- A record rather than seven positional arguments: three Strings followed by four Names meant
-- any two same-typed arguments could be transposed with nothing to catch it -- swapping the
-- ordinal and tenor function names, or the daily-tenor and overnight enums, type-checks
-- silently and yields wrong-but-compiling generated code.
data IborConstructorSpec = IborConstructorSpec
  { iborTypeName :: String        -- ^the merged ADT to generate
  , iborOrdinalFn :: String       -- ^generated @\<ADT\> -> Int@ flat C dispatch ordinal
  , iborTenorFn :: String         -- ^generated @\<ADT\> -> (Word, TimeUnit)@ tenor accessor
  , iborTenorEnum :: Name         -- ^C enum of the tenor-carrying indices
  , iborDailyTenorEnum :: Name    -- ^C enum of the daily-tenor indices
  , iborOvernightEnum :: Name     -- ^C enum of the overnight indices
  , iborExtraType :: Name         -- ^data type holding the non-enum-ordinal extra constructors
  }

deriveIborConstructor :: IborConstructorSpec -> DecsQ
deriveIborConstructor spec = do
  normalCtors <- dropIborSentinel <$> getConstructors (iborTenorEnum spec)
  dailyCtors <- dropIborSentinel <$> getConstructors (iborDailyTenorEnum spec)
  onCtors <- dropIborSentinel <$> getConstructors (iborOvernightEnum spec)

  -- resolved against the splice site's scope (InterestRate.chs, where TimeUnit(..) and Days
  -- are already imported/in scope), not this module's own imports -- Syntax.hs must not import
  -- QuantLib.Time.Schedule directly, since Schedule -> CalendarEnum -> Syntax already, and that
  -- would close an import cycle
  timeUnit <- lookupTypeName "TimeUnit" >>= maybe (fail "deriveIborConstructor: TimeUnit not in scope at splice site") return
  days <- lookupValueName "Days" >>= maybe (fail "deriveIborConstructor: Days not in scope at splice site") return

  let dailyOffset = length normalCtors
      onOffset = dailyOffset + length dailyCtors

  normalGroups <- mapM (mkGroup ShapeTenor timeUnit days 0) normalCtors
  dailyGroups <- mapM (mkGroup ShapeDailyTenor timeUnit days dailyOffset) dailyCtors
  onGroups <- mapM (mkGroup ShapeOvernight timeUnit days onOffset) onCtors

  extraConstructors <- getConstructors (iborExtraType spec)

  let extraCon (con, args) = NormalC (mkName (stripEnumPrefix con)) args
      ordinalDefault = Clause [WildP] (unenumerableError (iborOrdinalFn spec)) []
      tenorDefault = Clause [WildP] (unenumerableError (iborTenorFn spec)) []
      groups = normalGroups ++ dailyGroups ++ onGroups
      dataDecl = DataD [] resNameType [] Nothing
                   (map (\(con, _, _) -> con) groups ++ map extraCon extraConstructors) []
      ordinalSig = SigD ordinalName (arrowT (ConT resNameType) (ConT ''Int))
      tenorSig = SigD tenorName (arrowT (ConT resNameType) (pairT (ConT ''Word) (ConT timeUnit)))
      ordinalBody = FunD ordinalName (map (\(_, o, _) -> o) groups ++ [ordinalDefault])
      tenorBody = FunD tenorName (map (\(_, _, t) -> t) groups ++ [tenorDefault])

  return [dataDecl, ordinalSig, ordinalBody, tenorSig, tenorBody]

  where
    resNameType = mkName (iborTypeName spec)
    ordinalName = mkName (iborOrdinalFn spec)
    tenorName = mkName (iborTenorFn spec)

    mkGroup :: IborShape -> Name -> Name -> Int -> (Name, [BangType]) -> Q (Con, Clause, Clause)
    mkGroup shape timeUnit days offset (origName, _) = do
      let strippedName = mkName (stripEnumPrefix origName)
          ordinalBody' = NormalB (InfixE (Just (LitE (IntegerL (toInteger offset)))) (VarE '(+))
                                         (Just (fromEnumE (ConE origName))))
      case shape of
        ShapeTenor -> do
          let con = NormalC strippedName
                [(Bang NoSourceUnpackedness SourceStrict, pairT (ConT ''Word) (ConT timeUnit))]
          ordinalPat <- conPat strippedName [WildP]
          p <- newName "p"
          tenorPat <- conPat strippedName [VarP p]
          return (con, Clause [ordinalPat] ordinalBody' [], Clause [tenorPat] (NormalB (VarE p)) [])
        ShapeDailyTenor -> do
          let con = NormalC strippedName [(Bang NoSourceUnpackedness SourceStrict, ConT ''Word)]
          ordinalPat <- conPat strippedName [WildP]
          d <- newName "d"
          tenorPat <- conPat strippedName [VarP d]
          return ( con
                 , Clause [ordinalPat] ordinalBody' []
                 , Clause [tenorPat] (NormalB (pairE (VarE d) (ConE days))) [] )
        ShapeOvernight -> do
          let con = NormalC strippedName []
          pat <- conPat strippedName []
          return ( con
                 , Clause [pat] ordinalBody' []
                 , Clause [pat] (NormalB (pairE (LitE (IntegerL 0)) (ConE days))) [] )

-- A wide C++ constructor's trailing, upstream-defaulted params are turned into
-- one record type (one field per param, in the order given) plus a `default<recName>`
-- value built from the supplied default exprs. Unlike deriveCrossEnum/deriveIborConstructor,
-- this deliberately does NOT reify the target binding's type to recover field types --
-- doing so for a c2hs-generated function whose distinct trailing params can each carry
-- their own independent type variable (e.g. OISRateHelper's fixedRate :: GenQuote a vs.
-- overnightSpread :: Maybe (GenQuote m)) would mean decomposing a ForallT, working out
-- which of its bound variables occur free in just the trailing slice, and re-quantifying
-- the generated record/wrapper over exactly those -- real complexity with no precedent
-- elsewhere in this module (both existing helpers only reify enum/data-constructor
-- *shapes*, never a function's type). Taking explicit field types (and, since a field's
-- type may itself mention a fresh type variable, the record's own type parameters) at
-- the splice site sidesteps all of that; the actual drift protection this exists for --
-- "the record's fields must match the underlying binding" -- still comes for free from
-- the type checker at the hand-written wrapper that applies the record's fields to that
-- binding, so nothing is lost by not reifying.
deriveOptionsRecord :: String -> [String] -> [(String, TypeQ, ExpQ)] -> DecsQ
deriveOptionsRecord recName tyVarNames fields = do
  -- the field types and default exprs are the caller's own Q values, so unlike the two
  -- functions above these have to be run before the raw Decs can be assembled
  fieldTypes <- sequence [t | (_, t, _) <- fields]
  fieldDefaults <- sequence [e | (_, _, e) <- fields]

  let tyVars = map (plainTV . mkName) tyVarNames
      recFields = zipWith (\n t -> (n, strictness, t)) fieldNames fieldTypes
  return
    [ DataD [] recTypeName tyVars Nothing [RecC recTypeName recFields] []
    , SigD defaultName (foldl AppT (ConT recTypeName) (map (VarT . mkName) tyVarNames))
    , FunD defaultName [Clause [] (NormalB (RecConE recTypeName (zip fieldNames fieldDefaults))) []]
    ]
  where
    recTypeName = mkName recName
    defaultName = mkName ("default" ++ recName)
    fieldNames = [mkName n | (n, _, _) <- fields]
    -- lazy fields, unlike the strict (!) ones the two enum-merging functions above generate
    strictness = Bang NoSourceUnpackedness NoSourceStrictness

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
