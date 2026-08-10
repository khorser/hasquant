{-# LANGUAGE TemplateHaskell, TupleSections #-}
module QuantLib.Internal.Syntax
  (
    deriveCrossEnum
  , deriveIborConstructor
  , deriveOptionsRecord
  ) where
import Language.Haskell.TH.Syntax
import Language.Haskell.TH.Lib
import Data.List(isPrefixOf, isSuffixOf)
import Control.Monad((>=>))

getConstructors :: Name -> Q [(Name, [BangType])] -- [(data constructor, constructor args)]
getConstructors x = do
  (TyConI (DataD _ _tCon _ _ dCons _)) <- reify x
  mapM constr dCons
    where
      constr (NormalC dCon dConArgs) = return (dCon, dConArgs)
      constr c = fail $ "Unsupported constructor: " ++ show c

-- what a main enum value's sub-choice looks like, once we go find the type named
-- <mainValue><subSuffix>: nothing there at all, a proper enum to cross-product with,
-- or just a `type X = Bool` marker (see the deriveCrossEnum comment below)
data SubKind = NoSub | EnumSub [Name] | BoolSub

classifySub :: String -> Q SubKind
classifySub d = lookupTypeName d >>= maybe (return NoSub) (reify >=> classify)
  where
    classify (TyConI (DataD _ _ _ _ dCons _)) = EnumSub . map fst <$> mapM constr dCons
    classify (TyConI (TySynD _ _ (ConT b))) | b == ''Bool = return BoolSub
    classify info = fail $ "deriveCrossEnum: unsupported sub-type declaration for " ++ d ++ ": " ++ show info
    constr (NormalC dCon dConArgs) = return (dCon, dConArgs)
    constr c = fail $ "Unsupported constructor: " ++ show c

stripEnumPrefix :: String -> String
stripEnumPrefix str@(_:cs)
  | "__" `isPrefixOf` str = drop 2 str
  | otherwise = stripEnumPrefix cs
stripEnumPrefix [] = fail "Enum prefix not found"

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
deriveCrossEnum :: String -> String -> Name -> String -> Name -> DecsQ
deriveCrossEnum resName mapper mainEnum subSuffix extra = do
  mainValues <- map fst <$> getConstructors mainEnum

  mergedValues <- concat <$> mapM (\d -> do -- (mainName, subName, []), the third member holds constructor arguments (extras, or a lone Bool for BoolSub)
    sub <- classifySub (stripEnumPrefix (nameBase d) ++ subSuffix)
    return $ case sub of
      NoSub -> [(d, Nothing, [])]
      EnumSub vals -> zip3 (repeat d) (map Just vals) (repeat [])
      BoolSub -> [(d, Nothing, [(Bang NoSourceUnpackedness SourceStrict, ConT ''Bool)])]) mainValues

  extraConstructors <- map (\(con, args) -> (con, Nothing, args)) <$> getConstructors extra

  caseClauses <- mapM mkClause mergedValues
  defaultClause <- clause [[p|_|]] (normalB [|error "Internal error: mapper called on an non-enumerable data constructor, probably, an exta one"|]) []

  let dataDecl = DataD [] resNameType [] Nothing (map (\(x, y, a) -> NormalC (concatNames x y) a) (mergedValues ++ extraConstructors)) []
  mapperSignature <- sigD mapperName [t|$(conT resNameType) -> (Int, Int)|]
  let mapperBody = FunD mapperName (caseClauses ++ [defaultClause])

  return [dataDecl, mapperSignature, mapperBody]

  where concatNames :: Name -> Maybe Name -> Name
        concatNames x y = mkName (stripEnumPrefix (nameBase x) ++ maybe "" (stripEnumPrefix . nameBase) y)
        resNameType = mkName resName
        mapperName = mkName mapper
        enumVal :: Maybe Name -> ExpQ
        enumVal Nothing = [|0|]
        enumVal (Just n) = [|fromEnum $(conE n)|]
        mkClause :: (Name, Maybe Name, [BangType]) -> Q Clause
        mkClause (mainVal, subVal, []) =
          clause [conP (concatNames mainVal subVal) []] (normalB [|(fromEnum $(conE mainVal), $(enumVal subVal))|]) []
        mkClause (mainVal, Nothing, [_]) = do
          x <- newName "x"
          clause [conP (concatNames mainVal Nothing) [varP x]] (normalB [|(fromEnum $(conE mainVal), fromEnum $(varE x))|]) []
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
dropIborSentinel = filter (not . ("Last" `isSuffixOf`) . stripEnumPrefix . nameBase . fst)

deriveIborConstructor :: String -> String -> String -> Name -> Name -> Name -> Name -> DecsQ
deriveIborConstructor resName ordinalFn tenorFn normalEnum dailyEnum onEnum extra = do
  normalCtors <- dropIborSentinel <$> getConstructors normalEnum
  dailyCtors <- dropIborSentinel <$> getConstructors dailyEnum
  onCtors <- dropIborSentinel <$> getConstructors onEnum

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

  extraConstructors <- getConstructors extra
  let extraCon (con, args) = NormalC (mkName (stripEnumPrefix (nameBase con))) args
      errMsg = "Internal error: " ++ ordinalFn ++ "/" ++ tenorFn ++
               " called on a non-enumerable data constructor, probably an extra one"
      errBody = normalB [|error $(litE (stringL errMsg))|]
  ordinalDefault <- clause [[p|_|]] errBody []
  tenorDefault <- clause [[p|_|]] errBody []

  let groups = normalGroups ++ dailyGroups ++ onGroups
      dataDecl = DataD [] resNameType [] Nothing
                   (map (\(con, _, _) -> con) groups ++ map extraCon extraConstructors) []
  ordinalSig <- sigD ordinalName [t|$(conT resNameType) -> Int|]
  tenorSig <- sigD tenorName [t|$(conT resNameType) -> (Word, $(conT timeUnit))|]
  let ordinalBody = FunD ordinalName (map (\(_, o, _) -> o) groups ++ [ordinalDefault])
      tenorBody = FunD tenorName (map (\(_, _, t) -> t) groups ++ [tenorDefault])

  return [dataDecl, ordinalSig, ordinalBody, tenorSig, tenorBody]

  where
    resNameType = mkName resName
    ordinalName = mkName ordinalFn
    tenorName = mkName tenorFn

    offsetLit :: Int -> ExpQ
    offsetLit = litE . integerL . toInteger

    mkGroup :: IborShape -> Name -> Name -> Int -> (Name, [BangType]) -> Q (Con, Clause, Clause)
    mkGroup shape timeUnit days offset (origName, _) = do
      let strippedName = mkName (stripEnumPrefix (nameBase origName))
          ordinalBody' = normalB [|$(offsetLit offset) + fromEnum $(conE origName)|]
      case shape of
        ShapeTenor -> do
          let con = NormalC strippedName
                [(Bang NoSourceUnpackedness SourceStrict, AppT (AppT (TupleT 2) (ConT ''Word)) (ConT timeUnit))]
          ordinalClause <- clause [conP strippedName [wildP]] ordinalBody' []
          p <- newName "p"
          tenorClause <- clause [conP strippedName [varP p]] (normalB (varE p)) []
          return (con, ordinalClause, tenorClause)
        ShapeDailyTenor -> do
          let con = NormalC strippedName [(Bang NoSourceUnpackedness SourceStrict, ConT ''Word)]
          ordinalClause <- clause [conP strippedName [wildP]] ordinalBody' []
          d <- newName "d"
          tenorClause <- clause [conP strippedName [varP d]] (normalB [|($(varE d), $(conE days))|]) []
          return (con, ordinalClause, tenorClause)
        ShapeOvernight -> do
          let con = NormalC strippedName []
          ordinalClause <- clause [conP strippedName []] ordinalBody' []
          tenorClause <- clause [conP strippedName []] (normalB [|(0, $(conE days))|]) []
          return (con, ordinalClause, tenorClause)

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
deriveOptionsRecord recName tyVarNames fields = sequence
  [ dataD (cxt []) recTypeName tyVars Nothing
      [recC recTypeName [varBangType (mkName n) (bangType strictness t) | (n, t, _) <- fields]] []
  , sigD defaultName (foldl appT (conT recTypeName) (map (varT . mkName) tyVarNames))
  , funD defaultName [clause [] (normalB (recConE recTypeName [(mkName n,) <$> e | (n, _, e) <- fields])) []]
  ]
  where
    recTypeName = mkName recName
    tyVars = map (plainTV . mkName) tyVarNames
    defaultName = mkName ("default" ++ recName)
    strictness = bang noSourceUnpackedness noSourceStrictness

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
