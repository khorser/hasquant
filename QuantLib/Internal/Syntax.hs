{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Internal.Syntax
  (
    mergeEnums
  )
  where

import Language.Haskell.TH.Syntax
import Language.Haskell.TH.Lib
import Data.List.Split
import Control.Monad((>=>))

getConstructors :: Name -> Q [(Name, [BangType])] -- [(data constructor, constructor args)]
getConstructors x = do
  (TyConI (DataD _ _tCon _ _ dCons _)) <- reify x
  return $ map (\(NormalC dCon dConArgs) -> (dCon, dConArgs)) dCons

-- try to get constructors for a type d. return empty list if not found
getConstructors' :: String -> Q [Name]
getConstructors' d = lookupTypeName d >>= maybe (return []) (getConstructors >=> (return . map fst))
  
stripPrefix :: String -> String
stripPrefix x = if length res < 2
                   then error "Error splitting " ++ x
                   else res !! 1
                     where res = splitOn "_" x

-- merge a set of enums into a big one providing a function to map values back to ordinal numbers of original enums
-- e.g. for mainEnum data CalendarCountry = Country_Australia | Country_UnitedStated,
-- subEnum suffix "Market" and UnitedStatesMarket = UnitedStates_NYSE | UnitedStates_Settlement
-- NB I use prefixes separated from the main entry with underscore, in final enum they are stripped off
-- the function will build Australia | UnitedStatesNYSE | UnitedStatesSettlement
-- initially I constructed calendars with Australia | ...| UnitedStates UnitedStatesMarket where UnitedStatesMarket = NYSE | Settlement
-- but too many country calendars contain Settlement and UnitedStates UnitedStatesSettlement 
-- (or Actual365Fixed Actual365FixedStandard) looks really awful
mergeEnums :: String -> String -> Name -> String -> Name -> [Name] -> DecsQ
mergeEnums resName mapper mainEnum subSuffix extra deriv = do
  mainValues <- map fst <$> getConstructors mainEnum
  -- allValues contains all required information (mainName, sub Name, []), the third member will hold arguments for extra constructors
  allValues <- concat <$> mapM (\d -> do
    vals <- getConstructors' (stripPrefix (nameBase d) ++ subSuffix)
    return $ if null vals then [(d, Nothing, [])] else zip3 (repeat d) (map Just vals) (repeat [])) mainValues
  e <- getConstructors extra
  let es :: [(Name, Maybe Name, [BangType])]
      es = map (\(n, as) -> (n, Nothing, as)) e
  let clauses = map (\(x, y, _) -> makeClause x y) allValues ++ [defaultClause]
 
  return [DataD [] resNameType [] Nothing (map (\(x, y, a) -> NormalC (concatNames x y) a) (allValues ++ es)) [DerivClause Nothing (map ConT deriv)]
            , SigD mapperName (AppT (AppT ArrowT (ConT resNameType)) (AppT (AppT (TupleT 2) (ConT ''Int)) (ConT ''Int)))
            , FunD mapperName clauses
            ]
  where concatNames :: Name -> Maybe Name -> Name
        concatNames x y = mkName (stripPrefix (nameBase x) ++ maybe "" (stripPrefix . nameBase) y)
        resNameType = mkName resName
        mapperName = mkName mapper
        makeClause x y = Clause [ConP (concatNames x y) []] (NormalB (TupE [Just (AppE (VarE 'fromEnum) (ConE x)), Just (maybe (LitE (IntegerL 0)) (AppE (VarE 'fromEnum) . ConE) y)])) []
        defaultClause = Clause [WildP] (NormalB (AppE (VarE 'error) (LitE (StringL "Internal error: mapper called on an non-enumerable data constructor, probably, an exta one")))) []

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
