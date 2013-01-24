{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Internal.Syntax
where

import Language.Haskell.TH

ftest :: Name -> DecsQ
ftest _ = return []
