-- Native ownership, hierarchy conversion and Fourier factory dispatch.
import Control.Monad(forM_, unless)
import Data.Complex(Complex((:+)), magnitude)
import Data.List(isPrefixOf)
import Data.Time.Calendar(Day, fromGregorian, addDays)
import qualified QuantLib.Context as Context
import QuantLib.Time.Schedule
import QuantLib.Time.Calendar
import QuantLib.InterestRate(Compounding(..))
import QuantLib.Currency(currency, Ccy(..))
import QuantLib.Quote
import QuantLib.TermStructure.Yield
import QuantLib.Process
import QuantLib.Model(RoughHestonModel, roughHestonModel)
import QuantLib.PricingEngine
import QuantLib.Instrument(npv, setPricingEngine)
import QuantLib.Instrument.Option
import qualified QuantLib.Index.InterestRate as IR
import qualified QuantLib.CashFlow as CF

check :: String -> Bool -> IO ()
check label success = unless success (error label)

today :: Day
today = fromGregorian 2024 7 1

makeModel :: IO RoughHestonModel
makeModel = do
  dc <- dayCounter Actual365FixedStandard
  r <- simpleQuote 0.03 >>= \q -> flatForward (ReferenceDate today) q dc Continuous Annual
  q <- simpleQuote 0 >>= \s -> flatForward (ReferenceDate today) s dc Continuous Annual
  spot <- simpleQuote 100
  process <- hestonProcess r (Just q) spot 0.04 0.3 0.04 0.4 (-0.7) QuadraticExponentialMartingale
  roughHestonModel process 0.1

escapedOption :: IO VanillaOption
escapedOption = do
  model <- makeModel
  engine <- analyticRoughHestonEngine model 64 128 Pade
  base <- asPricingEngine engine
  option <- vanillaOption (PlainVanilla (PlainVanillaPayoff Call 100)) (European (EuropeanExercise (addDays 365 today)))
  setPricingEngine option base
  pure option

escapedCoupon :: IO CF.Coupon
escapedCoupon = do
  dc <- dayCounter (Actual360 False)
  eur <- currency EUR
  usd <- currency USD
  curve <- simpleQuote 0.03 >>= \q -> flatForward (ReferenceDate today) q dc Continuous Annual
  idx <- IR.overnightIborIndex IR.Sofr (Just curve)
  let start = addDays 7 today
      end = addDays 100 today
  underlying <- CF.overnightIndexedCoupon end 100 start end idx 1 0 Nothing Nothing dc False CF.AveragingCompound 0 0 False False Nothing Nothing Nothing Nothing
  wrapped <- CF.fxResetCoupon underlying 100 (CF.FxReset start start)
  spot <- simpleQuote 1.1
  pricer <- CF.discountingFxResetPricer eur usd curve curve spot True Nothing
  CF.setFxResetPricer wrapped pricer
  CF.asCoupon wrapped

main :: IO ()
main = Context.keepingSettingsGc $
  if "1.43" `isPrefixOf` Context.version then putStrLn "1.44 ownership probe skipped on 1.43" else do
    Context.setEvaluationDate (Just today)
    option <- escapedOption
    Context.collectGarbage
    npv option >>= check "engine/model/curve ownership after upcast" . (> 0)
    coupon <- escapedCoupon
    Context.collectGarbage
    CF.couponNominal coupon >>= check "FX reset pricer ownership" . (\n -> abs (n - 110) < 1e-10)
    CF.amount coupon >>= check "underlying coupon ownership" . (> 0)
    forM_ [FourierGaussLaguerre 64, FourierGaussLegendre 128,
           FourierGaussChebyshev 128, FourierGaussChebyshev2nd 128,
           FourierGaussLobatto 1e-6 1e-6 5000 False, FourierGaussKronrod 1e-6 5000,
           FourierSimpson 1e-6 5000, FourierTrapezoid 1e-6 5000,
           FourierDiscreteSimpson 1000, FourierDiscreteTrapezoid 1000,
           FourierExpSinh 1e-6, FourierTanhSinh 1e-6] $ \configuration -> do
      engine <- makeModel >>= \model -> analyticRoughHestonEngineWithIntegration model configuration 128 1e-25 (-0.5) Pade
      Context.collectGarbage
      value <- roughHestonPriceVanillaPayoff engine (PlainVanillaPayoff Call 100) (TimePoint 1)
      check (show configuration) (value > 0 && not (isInfinite value))
      evaluations <- roughHestonNumberOfEvaluations engine
      check "Fourier factory evaluation count" (evaluations > 0)
      z <- roughHestonCharacteristicFunction engine (1.2 :+ (-0.5)) 1
      check "complex result marshalling after GC" (magnitude z > 0 && not (isNaN (magnitude z)))
      putStrLn (show configuration ++ ": " ++ show evaluations ++ " evaluations")
