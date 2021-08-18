-- internal utilities to convert special enums
module QuantLib.Internal.Enum
  (
    qlInterpolation
  , qlInterpolation'
  , Approximation(..)
  , Interpolation(..)

  , QlExercise
  , QlAmericanExercise
  , QlBermudanExercise
  , QlEuropeanExercise
  , QlSwingExercise

  , Exercise(..)
  , withQlExercise
  , asExercise
  , exercise
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
  peekObject = newForeignPtr qlFreeExercise >=> return . QlExercise

class IsExercise a where
  asExercise :: a -> IO QlExercise

{#pointer *QlEuropeanExercise foreign finalizer qlFreeEuropeanExercise newtype#}
instance ForeignObject QlEuropeanExercise where
  withObject = withQlEuropeanExercise
  peekObject = newForeignPtr qlFreeEuropeanExercise >=> return . QlEuropeanExercise
{#fun qlEuropeanExerciseAsExercise {`QlEuropeanExercise'} -> `QlExercise'#}
instance IsExercise QlEuropeanExercise where asExercise = qlEuropeanExerciseAsExercise

{#pointer *QlAmericanExercise foreign finalizer qlFreeAmericanExercise newtype#}
instance ForeignObject QlAmericanExercise where
  withObject = withQlAmericanExercise
  peekObject = newForeignPtr qlFreeAmericanExercise >=> return . QlAmericanExercise
{#fun qlAmericanExerciseAsExercise {`QlAmericanExercise'} -> `QlExercise'#}
instance IsExercise QlAmericanExercise where asExercise = qlAmericanExerciseAsExercise

{#pointer *QlSwingExercise foreign finalizer qlFreeSwingExercise newtype#}
instance ForeignObject QlSwingExercise where
  withObject = withQlSwingExercise
  peekObject = newForeignPtr qlFreeSwingExercise >=> return . QlSwingExercise
{#fun qlSwingExerciseAsExercise {`QlSwingExercise'} -> `QlExercise'#}
instance IsExercise QlSwingExercise where asExercise = qlSwingExerciseAsExercise

{#pointer *QlBermudanExercise foreign finalizer qlFreeBermudanExercise newtype#}
instance ForeignObject QlBermudanExercise where
  withObject = withQlBermudanExercise
  peekObject = newForeignPtr qlFreeBermudanExercise >=> return . QlBermudanExercise
{#fun qlBermudanExerciseAsExercise {`QlBermudanExercise'} -> `QlExercise'#}
instance IsExercise QlBermudanExercise where asExercise = qlBermudanExerciseAsExercise

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
exercise (AmericanExercise Nothing d p) = qlAmericanExercise1 d p >>= asExercise
exercise (AmericanExercise (Just d0) d p) = qlAmericanExercise d0 d p >>= asExercise
exercise (BermudanExercise d p) = qlBermudanExercise d p >>= asExercise
exercise (EarlyExercise t p) = qlEarlyExercise t p
exercise (VanillaExercise t) = qlExercise t
exercise (EuropeanExercise d) = qlEuropeanExercise d >>= asExercise
exercise (SwingListExercise ds) = qlSwingExercise d s >>= asExercise where (d, s) = unzip ds
exercise (SwingIntervalExercise d1 d2 s) = qlSwingExercise1 d1 d2 s >>= asExercise

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
