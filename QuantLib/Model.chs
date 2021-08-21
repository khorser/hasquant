module QuantLib.Model
  (
   CalibrationErrorType(..)
  , GJRGARCHModel
  , HestonModel
  , BatesModel
  , PiecewiseTimeDependentHestonModel
  , ShortRateModel
  , AffineModel
  , OneFactorAffineModel
  , LiborForwardModel
  , HullWhite
  , CalibratedModel
  , G2
  , BatesDetJumpModel
  , BatesDoubleExpDetJumpModel
  , BatesDoubleExpModel
  , LmCorrelationModel
  , LmVolatilityModel
  , CalibrationHelper
  )
  where

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "qlEnumObjects.h"

#include "ql.h"

import QuantLib.Internal

{#enum CalibrationErrorType {} deriving(Show, Eq)#}

{#pointer *QlGJRGARCHModel as GJRGARCHModel foreign finalizer qlFreeGJRGARCHModel newtype#}
instance ForeignObject GJRGARCHModel where
  withObject = withGJRGARCHModel
  constructor = GJRGARCHModel
  finalizer = qlFreeGJRGARCHModel

{#pointer *QlHestonModel as HestonModel foreign finalizer qlFreeHestonModel newtype#}
instance ForeignObject HestonModel where
  withObject = withHestonModel
  constructor = HestonModel
  finalizer = qlFreeHestonModel

{#pointer *QlBatesModel as BatesModel foreign finalizer qlFreeBatesModel newtype#}
instance ForeignObject BatesModel where
  withObject = withBatesModel
  constructor = BatesModel
  finalizer = qlFreeBatesModel

{#pointer *QlPiecewiseTimeDependentHestonModel as PiecewiseTimeDependentHestonModel foreign finalizer qlFreePiecewiseTimeDependentHestonModel newtype#}
instance ForeignObject PiecewiseTimeDependentHestonModel where
  withObject = withPiecewiseTimeDependentHestonModel
  constructor = PiecewiseTimeDependentHestonModel
  finalizer = qlFreePiecewiseTimeDependentHestonModel

{#pointer *QlShortRateModel as ShortRateModel foreign finalizer qlFreeShortRateModel newtype#}
instance ForeignObject ShortRateModel where
  withObject = withShortRateModel
  constructor = ShortRateModel
  finalizer = qlFreeShortRateModel

{#pointer *QlAffineModel as AffineModel foreign finalizer qlFreeAffineModel newtype#}
instance ForeignObject AffineModel where
  withObject = withAffineModel
  constructor = AffineModel
  finalizer = qlFreeAffineModel

{#pointer *QlOneFactorAffineModel as OneFactorAffineModel foreign finalizer qlFreeOneFactorAffineModel newtype#}
instance ForeignObject OneFactorAffineModel where
  withObject = withOneFactorAffineModel
  constructor = OneFactorAffineModel
  finalizer = qlFreeOneFactorAffineModel

{#pointer *QlLiborForwardModel as LiborForwardModel foreign finalizer qlFreeLiborForwardModel newtype#}
instance ForeignObject LiborForwardModel where
  withObject = withLiborForwardModel
  constructor = LiborForwardModel
  finalizer = qlFreeLiborForwardModel

{#pointer *QlHullWhite as HullWhite foreign finalizer qlFreeHullWhite newtype#}
instance ForeignObject HullWhite where
  withObject = withHullWhite
  constructor = HullWhite
  finalizer = qlFreeHullWhite

{#pointer *QlCalibratedModel as CalibratedModel foreign finalizer qlFreeCalibratedModel newtype#}
instance ForeignObject CalibratedModel where
  withObject = withCalibratedModel
  constructor = CalibratedModel
  finalizer = qlFreeCalibratedModel

{#pointer *QlG2 as G2 foreign finalizer qlFreeG2 newtype#}
instance ForeignObject G2 where
  withObject = withG2
  constructor = G2
  finalizer = qlFreeG2

{#pointer *QlBatesDetJumpModel as BatesDetJumpModel foreign finalizer qlFreeBatesDetJumpModel newtype#}
instance ForeignObject BatesDetJumpModel where
  withObject = withBatesDetJumpModel
  constructor = BatesDetJumpModel
  finalizer = qlFreeBatesDetJumpModel

{#pointer *QlBatesDoubleExpDetJumpModel as BatesDoubleExpDetJumpModel foreign finalizer qlFreeBatesDoubleExpDetJumpModel newtype#}
instance ForeignObject BatesDoubleExpDetJumpModel where
  withObject = withBatesDoubleExpDetJumpModel
  constructor = BatesDoubleExpDetJumpModel
  finalizer = qlFreeBatesDoubleExpDetJumpModel

{#pointer *QlBatesDoubleExpModel as BatesDoubleExpModel foreign finalizer qlFreeBatesDoubleExpModel newtype#}
instance ForeignObject BatesDoubleExpModel where
  withObject = withBatesDoubleExpModel
  constructor = BatesDoubleExpModel
  finalizer = qlFreeBatesDoubleExpModel

{#pointer *QlLmCorrelationModel as LmCorrelationModel foreign finalizer qlFreeLmCorrelationModel newtype#}
instance ForeignObject LmCorrelationModel where
  withObject = withLmCorrelationModel
  constructor = LmCorrelationModel
  finalizer = qlFreeLmCorrelationModel

{#pointer *QlLmVolatilityModel as LmVolatilityModel foreign finalizer qlFreeLmVolatilityModel newtype#}
instance ForeignObject LmVolatilityModel where
  withObject = withLmVolatilityModel
  constructor = LmVolatilityModel
  finalizer = qlFreeLmVolatilityModel

{#pointer *QlCalibrationHelper as CalibrationHelper foreign finalizer qlFreeCalibrationHelper newtype#}
instance ForeignObject CalibrationHelper where
  withObject = withCalibrationHelper
  constructor = CalibrationHelper
  finalizer = qlFreeCalibrationHelper


-- vim: set ff=unix ts=8 sts=2 sw=2 et:
