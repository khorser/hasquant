-- Repeated base conversions must share ownership, including intermediate hierarchy levels.
import Control.Monad (replicateM_, unless)
import Data.Time.Calendar (fromGregorian)
import qualified QuantLib.Context as Context
import qualified QuantLib.Quote as Quote
import qualified QuantLib.Instrument as Instrument
import qualified QuantLib.Instrument.Option as Option

check :: Bool -> IO ()
check ok = unless ok (error "hierarchy conversion changed a live object")

main :: IO ()
main = Context.keepingSettingsGc $ do
  Context.setEvaluationDate (Just (fromGregorian 2026 1 1))
  replicateM_ 100 $ do
    q <- Quote.simpleQuote 7 >>= Quote.asQuote
    q2 <- Quote.asQuote q
    q3 <- Quote.asQuote q2
    Quote.value q >>= check . (== 7)
    Quote.value q2 >>= check . (== 7)
    Quote.value q3 >>= check . (== 7)
    Context.collectGarbage
  survivor <- do
    q <- Quote.simpleQuote 11 >>= Quote.asQuote
    Quote.asQuote q >>= Quote.asQuote
  Context.collectGarbage
  Quote.value survivor >>= check . (== 11)
  original <- Quote.simpleQuote 13 >>= Quote.asQuote
  do
    temporary <- Quote.asQuote original
    Quote.value temporary >>= check . (== 13)
  Context.collectGarbage
  Quote.value original >>= check . (== 13)
  let payoff = Option.Type (Option.Striked (Option.PlainVanilla (Option.PlainVanillaPayoff Option.Call 100)))
      exercise = Option.European (Option.EuropeanExercise (fromGregorian 2027 1 1))
  option <- Option.oneAssetOption payoff exercise
  base <- Option.asOption option >>= Option.asOption
  instrument <- Instrument.asInstrument base >>= Instrument.asInstrument
  Context.collectGarbage
  Instrument.isExpired option >>= check . not
  Instrument.isExpired base >>= check . not
  Instrument.isExpired instrument >>= check . not
  putStrLn "Hierarchy ownership: OK"
