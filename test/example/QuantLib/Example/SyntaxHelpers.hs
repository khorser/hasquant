module QuantLib.Example.SyntaxHelpers
  (
    syntaxTestF
  , HasSyntaxLabel(..)
  ) where

-- plain arity-4 function and a typeclass method, used by MainTest.hs to check
-- QuantLib.Syntax's TH combinators (kept in their own module: TH reify can't target
-- a binding defined in the same module as the splice using it)
syntaxTestF :: Int -> Int -> Int -> Int -> Int
syntaxTestF a b c d = a*1000 + b*100 + c*10 + d

class HasSyntaxLabel a where
  syntaxLabelWith :: a -> Int -> Int -> Int -> String

instance HasSyntaxLabel Bool where
  syntaxLabelWith b x y z = show b ++ "-" ++ show x ++ show y ++ show z
