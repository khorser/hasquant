{-# LANGUAGE MultiParamTypeClasses #-}
-- internal utilities to convert special enums
module QuantLib.Internal.Enum
  (
    qlInterpolation
  , qlInterpolation'
  , Approximation(..)
  , Interpolation(..)

  , ExerciseType(..)
  , Exercise(..)
  , QlExercise

  , OptionType(..)
  , PositionType(..)
  , PriceType(..)
  , Payoff(..)

  , CallabilityType(..)
  , Callability(..)
  , QlCallability
  )
where

import QuantLib.Internal
import Foreign.Marshal.Utils(fromBool)

#include "qlTypesC2HS.h"
#include "ql.h"

#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

{#enum ApproximationType {} add prefix="Approximation" deriving(Show, Eq)#}

{#enum InterpolationType {} add prefix="Interpolation" deriving(Show, Eq)#}

qlApproximation :: Approximation -> (Int, Int)
qlApproximation (NaturalSpline x) = (fromEnum ApproximationNaturalSpline, fromBool x)
qlApproximation (Parabolic x) = (fromEnum ApproximationParabolic, fromBool x)
qlApproximation Kruger = (fromEnum ApproximationKruger, 0)
qlApproximation FritschButland = (fromEnum ApproximationFritschButland, 0)

qlInterpolation :: Interpolation -> (Int, (Int, Int))
qlInterpolation BackwardFlat = (fromEnum InterpolationBackwardFlat, (0, 0))
qlInterpolation ForwardFlat = (fromEnum InterpolationForwardFlat, (0, 0))
qlInterpolation Linear = (fromEnum InterpolationLinear, (0, 0))
qlInterpolation LogLinear = (fromEnum InterpolationLogLinear, (0, 0))
qlInterpolation (Cubic x) = (fromEnum InterpolationCubic, qlApproximation x)
qlInterpolation (LogCubic x) = (fromEnum InterpolationLogCubic, qlApproximation x)
qlInterpolation Abcd = (fromEnum InterpolationAbcd, (0, 0))

qlInterpolation' :: Maybe Interpolation -> (Int, (Int, Int))
qlInterpolation' Nothing = (fromIntegral qlNullInteger, (0, 0))
qlInterpolation' (Just i) = qlInterpolation i

data Approximation =
  NaturalSpline Bool
  | Parabolic Bool
  | Kruger
  | FritschButland
  deriving (Show, Eq)

data Interpolation =
  BackwardFlat
  | ForwardFlat
  | Linear
  | LogLinear
  | Cubic Approximation
  | LogCubic Approximation
  | Abcd
  deriving (Show, Eq)

{#pointer *QlExercise foreign finalizer qlFreeExercise newtype#}
instance ForeignObject QlExercise where
  withObject = withQlExercise
  constructor = QlExercise
  finalizer = qlFreeExercise

class IsQlExercise a where
  asQlExercise :: a -> IO QlExercise

-- TODO check if we really need this hierarchy
{#pointer *QlEuropeanExercise foreign finalizer qlFreeEuropeanExercise newtype#}
instance ForeignObject QlEuropeanExercise where
  withObject = withQlEuropeanExercise
  constructor = QlEuropeanExercise
  finalizer = qlFreeEuropeanExercise
{#fun qlEuropeanExerciseAsExercise {`QlEuropeanExercise'} -> `QlExercise'#}
instance IsQlExercise QlEuropeanExercise where asQlExercise = qlEuropeanExerciseAsExercise

{#pointer *QlAmericanExercise foreign finalizer qlFreeAmericanExercise newtype#}
instance ForeignObject QlAmericanExercise where
  withObject = withQlAmericanExercise
  constructor = QlAmericanExercise
  finalizer = qlFreeAmericanExercise
{#fun qlAmericanExerciseAsExercise {`QlAmericanExercise'} -> `QlExercise'#}
instance IsQlExercise QlAmericanExercise where asQlExercise = qlAmericanExerciseAsExercise

{#pointer *QlSwingExercise foreign finalizer qlFreeSwingExercise newtype#}
instance ForeignObject QlSwingExercise where
  withObject = withQlSwingExercise
  constructor = QlSwingExercise
  finalizer = qlFreeSwingExercise
{#fun qlSwingExerciseAsExercise {`QlSwingExercise'} -> `QlExercise'#}
instance IsQlExercise QlSwingExercise where asQlExercise = qlSwingExerciseAsExercise

{#pointer *QlBermudanExercise foreign finalizer qlFreeBermudanExercise newtype#}
instance ForeignObject QlBermudanExercise where
  withObject = withQlBermudanExercise
  constructor = QlBermudanExercise
  finalizer = qlFreeBermudanExercise
{#fun qlBermudanExerciseAsExercise {`QlBermudanExercise'} -> `QlExercise'#}
instance IsQlExercise QlBermudanExercise where asQlExercise = qlBermudanExerciseAsExercise

{#enum ExerciseType {} deriving (Show, Eq)#}
data Exercise =
    AmericanExercise
      (Maybe Day) -- ^earliestDate
      Day -- ^latestDate
      Bool -- ^paoffAtExpiry
    | BermudanExercise [Day] Bool
    | EarlyExercise ExerciseType Bool
    | VanillaExercise ExerciseType
    | EuropeanExercise Day
    | SwingListExercise [(Day, Word)] -- ^(dates, seconds)
    | SwingIntervalExercise Day Day Word -- ^stepSizeSecs

{#fun qlExercise {`ExerciseType', preErrorCheck- `String' errorCheck*-} -> `QlExercise'#}

{#fun qlAmericanExercise {withDay* `Day', withDay* `Day', `Bool', preErrorCheck- `String' errorCheck*-} -> `QlAmericanExercise'#}

{#fun qlAmericanExercise1 {withDay* `Day', `Bool', preErrorCheck- `String' errorCheck*-} -> `QlAmericanExercise'#}

{#fun qlBermudanExercise {withDayArray* `[Day]'&, `Bool', preErrorCheck- `String' errorCheck*-} -> `QlBermudanExercise'#}

{#fun qlEarlyExercise {`ExerciseType', `Bool', preErrorCheck- `String' errorCheck*-} -> `QlExercise'#}

{#fun qlEuropeanExercise {withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `QlEuropeanExercise'#}

{#fun qlSwingExercise {withDayArray* `[Day]'&, withIntArray* `[Word]'&, preErrorCheck- `String' errorCheck*-} -> `QlSwingExercise'#}

{#fun qlSwingExercise1 {withDay* `Day', withDay* `Day', fromIntegral `Word', preErrorCheck- `String' errorCheck*-} -> `QlSwingExercise'#}

exercise :: Exercise -> IO QlExercise
exercise (AmericanExercise Nothing d p) = qlAmericanExercise1 d p >>= asQlExercise
exercise (AmericanExercise (Just d0) d p) = qlAmericanExercise d0 d p >>= asQlExercise
exercise (BermudanExercise d p) = qlBermudanExercise d p >>= asQlExercise
exercise (EarlyExercise t p) = qlEarlyExercise t p
exercise (VanillaExercise t) = qlExercise t
exercise (EuropeanExercise d) = qlEuropeanExercise d >>= asQlExercise
exercise (SwingListExercise ds) = qlSwingExercise d s >>= asQlExercise where (d, s) = unzip ds
exercise (SwingIntervalExercise d1 d2 s) = qlSwingExercise1 d1 d2 s >>= asQlExercise

instance EnumObject Exercise QlExercise where withEnumObject x f = exercise x >>= (`withObject` f)

{#enum OptionType {} deriving (Show, Eq)#}

{#enum PositionType {} deriving (Show, Eq)#}

{#enum PriceType {} deriving (Show, Eq)#}

data Payoff =
  AssetOrNothing
    OptionType -- ^type
    Double -- ^strike
  | AverageBasket
      Payoff -- ^p
      Word -- ^n
  | AverageBasketMultiple
      Payoff -- ^p
      [Double] -- ^a
  | CashOrNothing
      OptionType -- ^type
      Double -- ^strike
      Double -- ^cashPayoff
  | DoubleStickyRatchet
      Double -- ^type1
      Double -- ^type2
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | FloatingType
      OptionType -- ^type
  | ForwardType
      PositionType -- ^type
      Double -- ^strike
  | Gap
      OptionType -- ^type
      Double -- ^strike
      Double -- ^secondStrike
  | MaxBasket
      Payoff -- ^p
  | MinBasket
      Payoff -- ^p
  | PercentageStrike
      OptionType -- ^type
      Double -- ^moneyness
  | PlainVanilla
      OptionType -- ^type
      Double -- ^strike
  | RatchetMax
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | RatchetMin
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | Ratchet
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^initialValue
      Double -- ^accrualFactor
  | SpreadBasket
      Payoff -- ^p
  | StickyMax
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | StickyMin
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^gearing3
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^spread3
      Double -- ^initialValue1
      Double -- ^initialValue2
      Double -- ^accrualFactor
  | Sticky
      Double -- ^gearing1
      Double -- ^gearing2
      Double -- ^spread1
      Double -- ^spread2
      Double -- ^initialValue
      Double -- ^accrualFactor
  | SuperFund
      Double -- ^strike
      Double -- ^secondStrike
  | SuperSharePayoff
      Double -- ^strike
      Double -- ^secondStrike
      Double -- ^cashPayoff

{#pointer *QlPayoff foreign finalizer qlFreePayoff newtype#}
instance ForeignObject QlPayoff where
  withObject = withQlPayoff
  constructor = QlPayoff
  finalizer = qlFreePayoff

class IsQlPayoff a where
  asQlPayoff :: a -> IO QlPayoff

{#pointer *QlBasketPayoff foreign finalizer qlFreeBasketPayoff newtype#}
instance ForeignObject QlBasketPayoff where
  withObject = withQlBasketPayoff
  constructor = QlBasketPayoff
  finalizer = qlFreeBasketPayoff
{#fun qlBasketPayoffAsPayoff {`QlBasketPayoff'} -> `QlPayoff'#}
instance IsQlPayoff QlBasketPayoff where asQlPayoff = qlBasketPayoffAsPayoff

{#pointer *QlTypePayoff foreign finalizer qlFreeTypePayoff newtype#}
instance ForeignObject QlTypePayoff where
  withObject = withQlTypePayoff
  constructor = QlTypePayoff
  finalizer = qlFreeTypePayoff
{#fun qlTypePayoffAsPayoff {`QlTypePayoff'} -> `QlPayoff'#}
instance IsQlPayoff QlTypePayoff where asQlPayoff = qlTypePayoffAsPayoff

{#pointer *QlStrikedTypePayoff foreign finalizer qlFreeStrikedTypePayoff newtype#}
instance ForeignObject QlStrikedTypePayoff where
  withObject = withQlStrikedTypePayoff
  constructor = QlStrikedTypePayoff
  finalizer = qlFreeStrikedTypePayoff
{#fun qlStrikedTypePayoffAsTypePayoff {`QlStrikedTypePayoff'} -> `QlTypePayoff'#}
instance IsQlPayoff QlStrikedTypePayoff where asQlPayoff x = qlStrikedTypePayoffAsTypePayoff x >>= asQlPayoff

{#pointer *QlPercentageStrikePayoff foreign finalizer qlFreePercentageStrikePayoff newtype#}
instance ForeignObject QlPercentageStrikePayoff where
  withObject = withQlPercentageStrikePayoff
  constructor = QlPercentageStrikePayoff
  finalizer = qlFreePercentageStrikePayoff
{#fun qlPercentageStrikePayoffAsStrikedTypePayoff {`QlPercentageStrikePayoff'} -> `QlStrikedTypePayoff'#}
instance IsQlPayoff QlPercentageStrikePayoff where asQlPayoff x = qlPercentageStrikePayoffAsStrikedTypePayoff x >>= asQlPayoff

{#pointer *QlPlainVanillaPayoff foreign finalizer qlFreePlainVanillaPayoff newtype#}
instance ForeignObject QlPlainVanillaPayoff where
  withObject = withQlPlainVanillaPayoff
  constructor = QlPlainVanillaPayoff
  finalizer = qlFreePlainVanillaPayoff
{#fun qlPlainVanillaPayoffAsStrikedTypePayoff {`QlPlainVanillaPayoff'} -> `QlStrikedTypePayoff'#}
instance IsQlPayoff QlPlainVanillaPayoff where asQlPayoff x = qlPlainVanillaPayoffAsStrikedTypePayoff x >>= asQlPayoff

data Callability =
  Soft
    Double -- ^price
    PriceType
    Day
    Double -- ^trigger
  | Callability
      Double
      PriceType
      CallabilityType
      Day

{#enum CallabilityType {} add prefix="Callability" deriving(Show, Eq)#}

{#pointer *QlCallability foreign finalizer qlFreeCallability newtype#}
instance ForeignObject QlCallability where
  withObject = withQlCallability
  constructor = QlCallability
  finalizer = qlFreeCallability

callability :: Callability -> IO QlCallability
callability (Soft p t d tg) = qlSoftCallability p t d tg
callability (Callability p t ct d) = qlCallability p t ct d

instance EnumObject Callability QlCallability where withEnumObject x f = callability x >>= (`withObject` f)

-- |callability leaving to the holder the possibility to convert
{#fun qlSoftCallability {`Double', `PriceType', withDay* `Day', `Double', preErrorCheck- `String' errorCheck*-} -> `QlCallability'#}

{#fun qlCallability {`Double', `PriceType', `CallabilityType', withDay* `Day', preErrorCheck- `String' errorCheck*-} -> `QlCallability'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
