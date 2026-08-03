{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Internal.Syntax
  (
    mergeEnums
  ) where
import Language.Haskell.TH.Syntax
import Language.Haskell.TH.Lib
import Data.List(isPrefixOf)
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
-- or just a `type X = Bool` marker (see the mergeEnums comment below)
data SubKind = NoSub | EnumSub [Name] | BoolSub

classifySub :: String -> Q SubKind
classifySub d = lookupTypeName d >>= maybe (return NoSub) (reify >=> classify)
  where
    classify (TyConI (DataD _ _ _ _ dCons _)) = EnumSub . map fst <$> mapM constr dCons
    classify (TyConI (TySynD _ _ (ConT b))) | b == ''Bool = return BoolSub
    classify info = fail $ "mergeEnums: unsupported sub-type declaration for " ++ d ++ ": " ++ show info
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
mergeEnums :: String -> String -> Name -> String -> Name -> DecsQ
mergeEnums resName mapper mainEnum subSuffix extra = do
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
        mkClause (mainVal, _, _) = fail $ "mergeEnums: unsupported sub-choice shape for " ++ show mainVal

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
