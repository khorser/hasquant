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
  , deriveReadPlain
  , deriveReadInstance
  ) where
import Language.Haskell.TH.Syntax
import Language.Haskell.TH.Lib(DecsQ, TypeQ, ExpQ, conP, plainTV)
import Data.List(isPrefixOf, isSuffixOf)
import Data.Maybe(catMaybes)
import Data.Char(toUpper)
import Control.Monad((>=>))
import System.IO.Unsafe(unsafePerformIO)

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
-- Calendar market choices are represented by a separate per-country type.
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

-- A merged ADT from deriveCrossEnum/deriveIborConstructor can't get a plain `deriving
-- (Read)` when any of its "extra" constructors carries a live QuantLib object (Calendar,
-- Currency, DayCounter, Schedule -- see the newtype declarations in QuantLib.Internal.Type):
-- those are opaque ForeignPtr handles with no Read instance and no realistic way to acquire
-- one, and GHC's stock deriving needs Read for every field type across *every* constructor
-- of the type, not just the ones actually being parsed.
--
-- This generates a plain `Int -> ReadS <targetTy>` function, *not* a `Read` instance, that
-- covers every constructor whose fields are all directly Read (every deriveCrossEnum
-- cross-product tag, every BoolSub case, and any "extra" constructor with no live-object
-- field -- Bespoke, for CalendarConstructor). Constructors with a
-- Calendar/Currency/DayCounter/Schedule field are left out entirely: the actual `Read
-- <targetTy>` instance is hand-written at the splice site that has the live-object
-- materializer in scope (`calendar`/`currency`/`dayCounter`), as this generated function's
-- alternatives `++`-ed with one hand-written alternative per proxy-backed live field, e.g.
--   instance Read CalendarConstructor where
--     readsPrec d r = readCalendarConstructorPlain d r
--       ++ readParen (d > 10) (\r' -> [(Joint2 c1 c2 rule, s3)
--            | ("Joint2", s0) <- lex r', (p1, s1) <- readsPrec 11 s0
--            , let c1 = unsafePerformIO (calendar p1), (p2, s2) <- readsPrec 11 s1
--            , let c2 = unsafePerformIO (calendar p2), (rule, s3) <- readsPrec 11 s2]) r
-- (`unsafePerformIO` here mirrors `Show Calendar`/`Show Currency`/`Show DayCounter`'s own
-- `showStandalone`, `QuantLib/Internal/Type.hs` -- calling into C++ from pure code is already
-- this codebase's idiom for these types, and the shim functions underneath already catch
-- `std::exception` and turn it into an ordinary `throwIO`, `errorCheck` in
-- `QuantLib/Internal.hs`, so no raw C++ exception crosses it.) Skipping
-- ActualActualBond'/ActualActualISMA' (Schedule fields, no readable proxy at all) from
-- DayCounterConstructor's hand-written instance leaves them permanently unparseable by
-- design: no alternative means `read`/`reads` falls through to the standard "no parse".
--
-- Generating the *function* here but hand-writing the *instance* elsewhere (rather than
-- generating the whole instance in one place, as deriveReadInstance below does for
-- IborConstructor) works around a genuine c2hs constraint: c2hs appends every
-- `{#fun#}`-generated `foreign import ..._'_` stub at the *physical end* of the file it
-- preprocesses, regardless of where the `{#fun#}` pragma establishing it sits. A top-level TH
-- splice forces GHC to split the module into declaration groups at that point, so any
-- `{#fun#}` wrapper function textually before the splice loses sight of its own stub (still
-- to come, in the final group) -- "Variable not in scope: qlJointCalendar2'_" and
-- similarly-named errors, in a module (QuantLib.Time.Calendar) that compiled fine before a
-- splice referencing `calendar` was added there. A splice is only safe in a `.chs` file if it
-- comes before every `{#fun#}` pragma in that file, or the file has none at all. CalendarEnum
-- has no `{#fun#}` pragmas, but the *instance* needs `calendar`/`dayCounter` -- defined in
-- Calendar.chs/Schedule.chs, which both have `{#fun#}` pragmas splattered throughout and
-- already import CalendarEnum back (so splicing the instance there too would also be a
-- cycle) -- hence generating only the live-object-free *function* here, splicing that where
-- it's declared, and hand-writing the *instance* where the materializer lives.
liveObjectTypeNames :: [String]
liveObjectTypeNames = ["Calendar", "Currency", "DayCounter", "Schedule"]

isDirectlyReadable :: Type -> Bool
isDirectlyReadable (ConT n) = nameBase n `notElem` liveObjectTypeNames
isDirectlyReadable _ = True

deriveReadPlain :: String -> Name -> DecsQ
deriveReadPlain fnName targetTy = do
  cons <- getConstructors targetTy
  let readableCons = [(con, map snd args) | (con, args) <- cons, all (isDirectlyReadable . snd) args]
  d <- newName "d"
  r <- newName "r"
  alts <- mapM (mkAlt d) readableCons
  let appliedAlts = [AppE a (VarE r) | a <- alts]
      body = case appliedAlts of
        [] -> ListE []
        (a0:as) -> foldl (\acc x -> InfixE (Just acc) (VarE '(++)) (Just x)) a0 as
      resultTy = AppT ListT (pairT (ConT targetTy) (ConT ''String))
      sig = SigD fn (arrowT (ConT ''Int) (arrowT (ConT ''String) resultTy))
      def = FunD fn [Clause [VarP d, VarP r] (NormalB body) []]
  return [sig, def]
  where
    fn = mkName fnName
    appPrec = 10 :: Integer

    mkAlt :: Name -> (Name, [Type]) -> Q Exp
    mkAlt d (con, tys) = do
      r0 <- newName "r0"
      r1 <- newName "r1"
      let lexStmt = BindS (TupP [LitP (StringL (nameBase con)), VarP r1]) (AppE (VarE 'lex) (VarE r0))
      (fieldStmts, xs, sLast) <- foldFields r1 tys
      let yieldExp = pairE (foldl AppE (ConE con) (map VarE xs)) (VarE sLast)
          comp = CompE (lexStmt : fieldStmts ++ [NoBindS yieldExp])
          lam = LamE [VarP r0] comp
          cond | null tys = ConE 'False
               | otherwise = InfixE (Just (VarE d)) (VarE '(>)) (Just (LitE (IntegerL appPrec)))
      return (AppE (AppE (VarE 'readParen) cond) lam)

    -- threads the "remaining input" variable through one readsPrec call per field, returning
    -- the field-binding Stmts, the Names holding each field's parsed value (in order), and
    -- the Name holding what's left of the input.
    foldFields :: Name -> [Type] -> Q ([Stmt], [Name], Name)
    foldFields cur [] = return ([], [], cur)
    foldFields cur (_:tys) = do
      x <- newName "x"
      sNext <- newName "s"
      let readStmt = BindS (TupP [VarP x, VarP sNext])
                           (AppE (AppE (VarE 'readsPrec) (LitE (IntegerL (appPrec + 1)))) (VarE cur))
      (restStmts, restXs, finalS) <- foldFields sNext tys
      return (readStmt : restStmts, x : restXs, finalS)

-- Generates a *full* `Read <targetTy>` instance in one splice, unlike deriveReadPlain above
-- (whose function still needs a hand-written instance layered on top elsewhere). This is only
-- legal where deriveReadPlain's comment says a splice is safe (before any `{#fun#}` pragma in
-- the file, or none at all) *and* the field materializers named in `table` (e.g. `[("Calendar",
-- 'calendar)]`) already live in other, separately-compiled modules -- so this file isn't the
-- one closing an import cycle by needing them. IborConstructor (spliced from
-- QuantLib.Index.InterestRate, before that file's first `{#fun#}`, needing
-- `calendar`/`currency`/`dayCounter` from three *other* already-compiled modules) is the one
-- user of this today; CalendarConstructor/DayCounterConstructor can't use it precisely because
-- their materializers are declared in modules that import CalendarEnum back.
--
-- A field whose type name is in `table` is parsed as its proxy type and materialized via a
-- generated top-level `unsafe<Fn>` binding (`unsafeCalendar = unsafePerformIO . calendar`,
-- etc, one per distinct materializer, each NOINLINE for the same reason as
-- `showStandalone`/the hand-written `unsafeCalendar`s in Calendar.chs/Schedule.chs). A field
-- whose type name is in `liveObjectTypeNames` but not `table` (or any other live type this
-- table doesn't cover) makes its whole constructor unparseable, exactly as in deriveReadPlain.
deriveReadInstance :: Name -> [(String, Name)] -> DecsQ
deriveReadInstance targetTy table = do
  cons <- getConstructors targetTy
  d <- newName "d"
  r <- newName "r"
  altsMaybe <- mapM (\(con, args) -> mkAlt d (map snd args) con) cons
  wrapperDecs <- concat <$> mapM mkWrapper (nubNames (map snd table))
  let alts = catMaybes altsMaybe
      appliedAlts = [AppE a (VarE r) | a <- alts]
      body = case appliedAlts of
        [] -> ListE []
        (a0:as) -> foldl (\acc x -> InfixE (Just acc) (VarE '(++)) (Just x)) a0 as
      readsPrecDec = FunD 'readsPrec [Clause [VarP d, VarP r] (NormalB body) []]
      instanceDec = InstanceD Nothing [] (AppT (ConT ''Read) (ConT targetTy)) [readsPrecDec]
  return (wrapperDecs ++ [instanceDec])
  where
    appPrec = 10 :: Integer

    nubNames = foldr (\n acc -> if n `elem` acc then acc else n : acc) []

    wrapperName :: Name -> Name
    wrapperName fn = mkName ("unsafe" ++ capitalize (nameBase fn))
      where capitalize (c:cs) = toUpper c : cs
            capitalize [] = []

    -- reifies `fn :: <proxy> -> IO <live>` to give the generated `unsafe<Fn>` wrapper an
    -- explicit signature (a bare `deriving`-adjacent, unsigned top-level binding would trip
    -- -Wmissing-signatures) without having to thread the proxy type's own Name through
    -- `table` -- `table` only ever needs to name the materializer, this recovers its type.
    mkWrapper :: Name -> Q [Dec]
    mkWrapper fn = do
      (dom, cod) <- reifyFnType fn
      let wname = wrapperName fn
      return
        [ SigD wname (arrowT dom cod)
        , FunD wname [Clause [] (NormalB (InfixE (Just (VarE 'unsafePerformIO)) (VarE '(.)) (Just (VarE fn)))) []]
        , PragmaD (InlineP wname NoInline FunLike AllPhases)
        ]

    reifyFnType :: Name -> Q (Type, Type)
    reifyFnType fn = reify fn >>= \case
      VarI _ (AppT (AppT ArrowT dom) (AppT (ConT io) cod)) _ | io == ''IO -> return (dom, cod)
      info -> fail $ "deriveReadInstance: expected `<proxy> -> IO <live>` for "
                       ++ show fn ++ ", got: " ++ show info

    classifyReadField :: Type -> Maybe FieldReadPlan
    classifyReadField (ConT n)
      | Just fn <- lookup (nameBase n) table = Just (ReadViaProxy fn)
      | nameBase n `elem` liveObjectTypeNames = Nothing
    classifyReadField _ = Just ReadDirect

    mkAlt :: Name -> [Type] -> Name -> Q (Maybe Exp)
    mkAlt d tys con = case mapM classifyReadField tys of
      Nothing -> return Nothing
      Just plans -> do
          r0 <- newName "r0"
          r1 <- newName "r1"
          let lexStmt = BindS (TupP [LitP (StringL (nameBase con)), VarP r1]) (AppE (VarE 'lex) (VarE r0))
          (fieldStmts, xs, sLast) <- foldFieldsProxy r1 plans
          let yieldExp = pairE (foldl AppE (ConE con) (map VarE xs)) (VarE sLast)
              comp = CompE (lexStmt : fieldStmts ++ [NoBindS yieldExp])
              lam = LamE [VarP r0] comp
              cond | null tys = ConE 'False
                   | otherwise = InfixE (Just (VarE d)) (VarE '(>)) (Just (LitE (IntegerL appPrec)))
          return (Just (AppE (AppE (VarE 'readParen) cond) lam))

    -- like deriveReadPlain's foldFields, but a ReadViaProxy field also materializes the
    -- parsed proxy value via the field's generated `unsafe<Fn>` wrapper.
    foldFieldsProxy :: Name -> [FieldReadPlan] -> Q ([Stmt], [Name], Name)
    foldFieldsProxy cur [] = return ([], [], cur)
    foldFieldsProxy cur (p:ps) = do
      xRaw <- newName "x"
      sNext <- newName "s"
      let readStmt = BindS (TupP [VarP xRaw, VarP sNext])
                           (AppE (AppE (VarE 'readsPrec) (LitE (IntegerL (appPrec + 1)))) (VarE cur))
      case p of
        ReadDirect -> do
          (restStmts, restXs, finalS) <- foldFieldsProxy sNext ps
          return (readStmt : restStmts, xRaw : restXs, finalS)
        ReadViaProxy fn -> do
          xVal <- newName "x"
          let letStmt = LetS [ValD (VarP xVal) (NormalB (AppE (VarE (wrapperName fn)) (VarE xRaw))) []]
          (restStmts, restXs, finalS) <- foldFieldsProxy sNext ps
          return (readStmt : letStmt : restStmts, xVal : restXs, finalS)

data FieldReadPlan = ReadDirect | ReadViaProxy Name

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
