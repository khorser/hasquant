{-# LANGUAGE TemplateHaskell #-}
{-# OPTIONS_GHC -F -pgmF htfpp #-}
-- test unexposed functionality
module QuantLib.Test.Internal.HUnit (htf_thisModulesTests)
where

import Test.Framework

import QuantLib.Internal.Enum(values)
import QuantLib.Internal.Syntax

-- |check that enumerations are marshalled consistently
checkEnums :: IO [(String, Bool)]
checkEnums = mapM checkEnum $(qlEnumsInfo)
  where
    checkEnum :: (String, Integer) -> IO (String, Bool)
    checkEnum (n, l) = do
      v <- values n
      return (n, length v == fromIntegral l)

test_Enums :: IO ()
test_Enums = checkEnums >>=
  mapM_ (\(n, l) -> assertBoolVerbose ("Error checking " ++ n ++ " length") l)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
