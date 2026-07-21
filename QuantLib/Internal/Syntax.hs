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

-- try to get constructors for a type d. return empty list if not found
getConstructors' :: String -> Q [Name]
getConstructors' d = lookupTypeName d >>= maybe (return []) (getConstructors >=> (return . map fst))

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
mergeEnums :: String -> String -> Name -> String -> Name -> DecsQ
mergeEnums resName mapper mainEnum subSuffix extra = do
  mainValues <- map fst <$> getConstructors mainEnum

  mergedValues <- concat <$> mapM (\d -> do -- (mainName, subName, []), the third member will hold arguments for extra constructors
    vals <- getConstructors' (stripEnumPrefix (nameBase d) ++ subSuffix)
    return $ if null vals then [(d, Nothing, [])] else zip3 (repeat d) (map Just vals) (repeat [])) mainValues

  extraConstructors <- map (\(con, args) -> (con, Nothing, args)) <$> getConstructors extra

  caseClauses <- mapM (\(mainVal, subVal, _) -> clause [conP (concatNames mainVal subVal) []] (normalB [|(fromEnum $(conE mainVal), $(enumVal subVal))|]) []) mergedValues
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

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
