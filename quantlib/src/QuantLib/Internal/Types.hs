{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE GeneralizedNewtypeDeriving #-}
{-# LANGUAGE DeriveDataTypeable #-}
module QuantLib.Internal.Types
  (
    Finalizable(..)
  , Upcastable(..)
  , NamedSingleton(..)
  , QLT
  , runQLT
  , QL
  , QLSettings(..)
  , runQL
  , QLError(..)
  , CStaticInt(..)
  , CArrayable(..)

  -- re-exporting some popular types
  , Word
  , CInt(CInt), CDouble(CDouble), CUInt(CUInt)
  , CString
  , Ptr, FunPtr
  , ForeignPtr
  , Storable

  , Matrix(..)

  -- cashflow
  , CLeg
  , CCouponLeg
  , CFloatingRateCouponPricer
  , CDividend

  -- currency
  , CCurrency
  , CRounding

  -- indices
  , CIndex
  , CInterestRateIndex
  , CIborIndex
  , CSwapIndex
  , COvernightIndex
  , COvernightIndexedSwapIndex
  , CBMAIndex

  -- instruments
  , CInstrument
  , CBond
  , CFixedRateBond
  , CForward
  , CFixedRateBondForward
  , CForwardRateAgreement
  , CSwap
  , CVanillaSwap
  , COvernightIndexedSwap
  , CBMASwap
  , CAssetSwap
  , CPayoff
  , CTypePayoff
  , CStrikedTypePayoff
  , CBasketPayoff
  , CPercentageStrikePayoff
  , CPlainVanillaPayoff
  , CExercise
  , CAmericanExercise
  , CBermudanExercise
  , CEuropeanExercise
  , CBarrierOption
  , CCdsOption
  , CCreditDefaultSwap
  , CDividendVanillaOption
  , CForwardVanillaOption
  , CMargrabeOption
  , CMultiAssetOption
  , COneAssetOption
  , COption
  , CQuantoVanillaOption
  , CSwaption
  , CSwingExercise
  , CVanillaOption
  , CClaim
  , CQuantoBarrierOption
  , CQuantoForwardVanillaOption
  , CCapFloor
  , CCallabilityPrice
  , CCallability
  , CCallableBond
  , CConvertibleBond

  -- math
  , CConstraint
  , COptimizationMethod
  , CEndCriteria

  -- methods
  , CFdmSchemeDesc

  -- models
  , CGJRGARCHModel
  , CHestonModel
  , CBatesModel
  , CPiecewiseTimeDependentHestonModel
  , CShortRateModel
  , CAffineModel
  , COneFactorAffineModel
  , CLiborForwardModel
  , CHullWhite
  , CCalibratedModel
  , CG2
  , CBatesDetJumpModel
  , CBatesDoubleExpDetJumpModel
  , CBatesDoubleExpModel
  , CLmCorrelationModel
  , CLmVolatilityModel
  , CCalibrationHelper

  -- pricingengines
  , CPricingEngine
  , CBlackCalculator
  , CBlackScholesCalculator

  -- processes
  , CBlackProcess
  , CGeneralizedBlackScholesProcess
  , CStochasticProcess
  , CStochasticProcess1D
  , CExtOUWithJumpsProcess
  , CExtendedOrnsteinUhlenbeckProcess
  , CGJRGARCHProcess
  , CHestonProcess
  , CBatesProcess
  , CHybridHestonHullWhiteProcess
  , CKlugeExtOUProcess
  , CLiborForwardModelProcess
  , CStochasticProcessArray
  , CVarianceGammaProcess
  , CMerton76Process
  , CHullWhiteProcess
  , CHullWhiteForwardProcess

  -- termstructures
  , CRateHelper
  , CSwapRateHelper
  , COISRateHelper
  , CYieldTermStructure
  , CVolTermStructure
  , COptionletVolatilityStructure
  , CBondHelper
  , CFittedBondDiscountCurveFittingMethod
  , CFittedBondDiscountCurve
  , CTermStructure
  , CBlackVolTermStructure
  , CVolatilityTermStructure
  , CDefaultProbabilityTermStructure
  , CSwaptionVolatilityStructure
  , CSmileSection
  , CCapFloorTermVolSurface
  , CLocalVolTermStructure
  , CBlackVarianceCurve
  , CDefaultProbabilityHelper
  , CCallableBondVolatilityStructure

  -- time
  , CCalendar
  , CDayCounter
  , CSchedule

  -- common
  , CInterestRate
  , CQuote
  , CSimpleQuote

  , CTimeGrid
  )
where

import Control.Applicative
import Control.Exception(Exception, IOException)
import Data.Functor.Identity
import Control.Monad.Trans.Reader
import Control.Monad.Trans.Class(MonadTrans)
import Control.Monad.IO.Class(MonadIO)
import Data.Time.Calendar(Day)
import Data.Typeable(Typeable)
import Data.Word(Word)
import Foreign.C.String(CString)
import Foreign.C.Types(CInt(CInt), CDouble(CDouble), CUInt(CUInt))
import Foreign.ForeignPtr(ForeignPtr)
import Foreign.Ptr(Ptr, FunPtr, castPtr)
import Foreign.Storable(Storable)

class Finalizable a where
  finalize :: FunPtr (Ptr a -> IO ())

class (Finalizable a, Finalizable b) => Upcastable a b where
  c_upcast :: Ptr a -> IO (Ptr b)

class Finalizable a => NamedSingleton a where
  c_construct :: CString -> Ptr CString -> IO (Ptr a)
  c_name :: Ptr a -> IO CString

data QLSettings = QLSettings {
    evaluationDate :: Day
  , enforceTodaysHistoricFixings :: Bool
  , includeTodaysCashFlows :: Bool
  , includeReferenceDateEvents :: Bool}

newtype QLT m a = QLT (ReaderT QLSettings m a)
  deriving (Monad, MonadTrans, MonadIO, Applicative, Alternative, Functor)

runQLT :: QLT m a -> QLSettings -> m a
runQLT (QLT r) = runReaderT r

type QL a = QLT Identity a

runQL :: QL a -> QLSettings -> a
runQL (QLT r) = runReader r

data QLError = CPlusPlusException String
  | DateConversion Day
  | NullPointerReturned
  | UnknownEnum String
  | EnumConversion String String
  | CEnumConversion String Int
  | IncorrectSize
  | IoException IOException
  deriving (Typeable, Show, Eq)

instance Exception QLError

newtype CStaticInt = CStaticInt{getStaticInt::CInt} deriving (Eq, Show, Storable)

class (Storable a) => CArrayable a where
  freeArray :: Ptr a -> IO ()

instance CArrayable CInt where
  freeArray = c_freeInts
instance CArrayable CDouble where
  freeArray = c_freeDoubles
instance CArrayable CStaticInt where
  freeArray = const $ return ()
instance CArrayable (Ptr a) where
  freeArray = c_freePointerArray . castPtr

foreign import ccall safe "ql.h qlFreeInts"
  c_freeInts :: Ptr CInt -> IO ()
foreign import ccall safe "ql.h qlFreeDoubles"
  c_freeDoubles :: Ptr CDouble -> IO ()
foreign import ccall safe "ql.h qlFreePointerArray"
  c_freePointerArray :: Ptr (Ptr ()) -> IO ()

-- cashflows
data CLeg

instance Finalizable CLeg where
  finalize = p_freeLeg
foreign import ccall safe "ql.h &qlFreeLeg"
  p_freeLeg :: FunPtr (Ptr CLeg -> IO ())

data CCouponLeg
instance Finalizable CCouponLeg where
  finalize = p_freeCouponLeg
foreign import ccall safe "ql.h &qlFreeCouponLeg"
  p_freeCouponLeg :: FunPtr (Ptr CCouponLeg -> IO ())
instance Upcastable CCouponLeg CLeg where
  c_upcast = c_CouponLegAsLeg
foreign import ccall safe "ql.h qlCouponLegAsLeg"
  c_CouponLegAsLeg :: Ptr CCouponLeg -> IO (Ptr CLeg)

data CFloatingRateCouponPricer

instance Finalizable CFloatingRateCouponPricer where
  finalize = p_freeFloatingCouponPricer
foreign import ccall safe "ql.h &qlFreeFloatingCouponPricer"
  p_freeFloatingCouponPricer :: FunPtr (Ptr CFloatingRateCouponPricer -> IO ())

data CDividend
instance Finalizable CDividend where
  finalize = p_freeDividend
foreign import ccall safe "ql.h &qlFreeDividend"
  p_freeDividend :: FunPtr (Ptr CDividend -> IO ())

-- currencies
data CCurrency

instance Finalizable CCurrency where
  finalize = p_freeCurrency
foreign import ccall safe "ql.h &qlFreeCurrency"
  p_freeCurrency :: FunPtr (Ptr CCurrency -> IO ())

instance NamedSingleton CCurrency where
  c_construct = c_currency
  c_name = c_currencyName
foreign import ccall safe "ql.h qlCurrency"
  c_currency :: CString -> Ptr CString -> IO (Ptr CCurrency)
foreign import ccall safe "ql.h qlCurrencyName"
  c_currencyName :: Ptr CCurrency -> IO CString

data CRounding
instance Finalizable CRounding where
  finalize = p_freeRounding
foreign import ccall safe "ql.h &qlFreeRounding"
  p_freeRounding :: FunPtr (Ptr CRounding -> IO ())

-- indexes
data CIndex
data CInterestRateIndex
data CIborIndex
data CSwapIndex

instance Finalizable CIborIndex where
  finalize = p_freeIborIndex
instance Finalizable CIndex where
  finalize = p_freeIndex
foreign import ccall safe "ql.h &qlFreeIborIndex"
  p_freeIborIndex :: FunPtr (Ptr CIborIndex -> IO ())
foreign import ccall safe "ql.h &qlFreeIndex"
  p_freeIndex :: FunPtr (Ptr CIndex -> IO ())

instance Upcastable CIborIndex CInterestRateIndex where
  c_upcast = c_IborIndexAsInterestRateIndex
foreign import ccall safe "ql.h qlIborIndexAsInterestRateIndex"
  c_IborIndexAsInterestRateIndex :: Ptr CIborIndex -> IO (Ptr CInterestRateIndex)

instance Finalizable CInterestRateIndex where
  finalize = p_freeInterestRateIndex
foreign import ccall safe "ql.h &qlFreeInterestRateIndex"
  p_freeInterestRateIndex :: FunPtr (Ptr CInterestRateIndex -> IO ())
instance Upcastable CInterestRateIndex CIndex where
  c_upcast = c_InterestRateIndexAsIndex
foreign import ccall safe "ql.h qlInterestRateIndexAsIndex"
  c_InterestRateIndexAsIndex :: Ptr CInterestRateIndex -> IO (Ptr CIndex)

instance Finalizable CSwapIndex where
  finalize = p_freeSwapIndex
foreign import ccall safe "ql.h &qlFreeSwapIndex"
  p_freeSwapIndex :: FunPtr (Ptr CSwapIndex -> IO ())
instance Upcastable CSwapIndex CInterestRateIndex where
  c_upcast = c_SwapIndexAsInterestRateIndex
foreign import ccall safe "ql.h qlSwapIndexAsInterestRateIndex"
  c_SwapIndexAsInterestRateIndex :: Ptr CSwapIndex -> IO (Ptr CInterestRateIndex)

data COvernightIndex
instance Finalizable COvernightIndex where
  finalize = p_freeOvernightIndex
foreign import ccall safe "ql.h &qlFreeOvernightIndex"
  p_freeOvernightIndex :: FunPtr (Ptr COvernightIndex -> IO ())
instance Upcastable COvernightIndex CIborIndex where
  c_upcast = c_OvernightIndexAsIborIndex
foreign import ccall safe "ql.h qlOvernightIndexAsIborIndex"
  c_OvernightIndexAsIborIndex :: Ptr COvernightIndex -> IO (Ptr CIborIndex)

data COvernightIndexedSwapIndex
instance Finalizable COvernightIndexedSwapIndex where
  finalize = p_freeOvernightIndexedSwapIndex
foreign import ccall safe "ql.h &qlFreeOvernightIndexedSwapIndex"
  p_freeOvernightIndexedSwapIndex :: FunPtr (Ptr COvernightIndexedSwapIndex -> IO ())
instance Upcastable COvernightIndexedSwapIndex CSwapIndex where
  c_upcast = c_OvernightIndexedSwapIndexAsSwapIndex
foreign import ccall safe "ql.h qlOvernightIndexedSwapIndexAsSwapIndex"
  c_OvernightIndexedSwapIndexAsSwapIndex :: Ptr COvernightIndexedSwapIndex -> IO (Ptr CSwapIndex)

data CBMAIndex
instance Finalizable CBMAIndex where
  finalize = p_freeBMAIndex
foreign import ccall safe "ql.h &qlFreeBMAIndex"
  p_freeBMAIndex :: FunPtr (Ptr CBMAIndex -> IO ())
instance Upcastable CBMAIndex CInterestRateIndex where
  c_upcast = c_BMAIndexAsInterestRateIndex
foreign import ccall safe "ql.h qlBMAIndexAsInterestRateIndex"
  c_BMAIndexAsInterestRateIndex :: Ptr CBMAIndex -> IO (Ptr CInterestRateIndex)

-- instruments
data CInstrument
data CBond
data CFixedRateBond
data CForward
data CFixedRateBondForward
data CForwardRateAgreement

instance Finalizable CBond where
  finalize = p_freeBond
instance Finalizable CFixedRateBond where
  finalize = p_freeFixedRateBond
instance Finalizable CInstrument where
  finalize = p_freeInstrument
instance Finalizable CForward where
  finalize = p_freeForward
instance Finalizable CFixedRateBondForward where
  finalize = p_freeFixedRateBondForward
instance Finalizable CForwardRateAgreement where
  finalize = p_freeForwardRateAgreement
foreign import ccall safe "ql.h &qlFreeBond"
  p_freeBond :: FunPtr (Ptr CBond -> IO ())
foreign import ccall safe "ql.h &qlFreeFixedRateBond"
  p_freeFixedRateBond :: FunPtr (Ptr CFixedRateBond -> IO ())
foreign import ccall safe "ql.h &qlFreeInstrument"
  p_freeInstrument :: FunPtr (Ptr CInstrument -> IO ())
foreign import ccall safe "ql.h &qlFreeForward"
  p_freeForward :: FunPtr (Ptr CForward -> IO ())
foreign import ccall safe "ql.h &qlFreeFixedRateBondForward"
  p_freeFixedRateBondForward :: FunPtr (Ptr CFixedRateBondForward -> IO ())
foreign import ccall safe "ql.h &qlFreeForwardRateAgreement"
  p_freeForwardRateAgreement :: FunPtr (Ptr CForwardRateAgreement -> IO ())

instance Upcastable CFixedRateBond CBond where
  c_upcast = c_fixedRateBondAsBond
instance Upcastable CBond CInstrument where
  c_upcast = c_bondAsInstrument
instance Upcastable CFixedRateBondForward CForward where
  c_upcast = c_fixedRateBondForwardAsForward
instance Upcastable CForwardRateAgreement CForward where
  c_upcast = c_forwardRateAgreementAsForward
instance Upcastable CForward CInstrument where
  c_upcast = c_forwardAsInstrument
foreign import ccall safe "ql.h qlFixedRateBondAsBond"
  c_fixedRateBondAsBond :: Ptr CFixedRateBond -> IO (Ptr CBond)
foreign import ccall safe "ql.h qlBondAsInstrument"
  c_bondAsInstrument :: Ptr CBond -> IO (Ptr CInstrument)
foreign import ccall safe "ql.h qlFixedRateBondForwardAsForward"
  c_fixedRateBondForwardAsForward :: Ptr CFixedRateBondForward -> IO (Ptr CForward)
foreign import ccall safe "ql.h qlForwardAsInstrument"
  c_forwardAsInstrument :: Ptr CForward -> IO (Ptr CInstrument)
foreign import ccall safe "ql.h qlForwardRateAgreementAsForward"
  c_forwardRateAgreementAsForward :: Ptr CForwardRateAgreement -> IO (Ptr CForward)

data CVanillaSwap
instance Finalizable CVanillaSwap where
  finalize = p_freeVanillaSwap
foreign import ccall safe "ql.h &qlFreeVanillaSwap"
  p_freeVanillaSwap :: FunPtr (Ptr CVanillaSwap -> IO ())
instance Upcastable CVanillaSwap CSwap where
  c_upcast = c_VanillaSwapAsSwap
foreign import ccall safe "ql.h qlVanillaSwapAsSwap"
  c_VanillaSwapAsSwap :: Ptr CVanillaSwap -> IO (Ptr CSwap)

data CSwap
instance Finalizable CSwap where
  finalize = p_freeSwap
foreign import ccall safe "ql.h &qlFreeSwap"
  p_freeSwap :: FunPtr (Ptr CSwap -> IO ())
instance Upcastable CSwap CInstrument where
  c_upcast = c_SwapAsInstrument
foreign import ccall safe "ql.h qlSwapAsInstrument"
  c_SwapAsInstrument :: Ptr CSwap -> IO (Ptr CInstrument)

data CAssetSwap
instance Finalizable CAssetSwap where
  finalize = p_freeAssetSwap
foreign import ccall safe "ql.h &qlFreeAssetSwap"
  p_freeAssetSwap :: FunPtr (Ptr CAssetSwap -> IO ())
instance Upcastable CAssetSwap CSwap where
  c_upcast = c_AssetSwapAsSwap
foreign import ccall safe "ql.h qlAssetSwapAsSwap"
  c_AssetSwapAsSwap :: Ptr CAssetSwap -> IO (Ptr CSwap)

data COvernightIndexedSwap
instance Finalizable COvernightIndexedSwap where
  finalize = p_freeOvernightIndexedSwap
foreign import ccall safe "ql.h &qlFreeOvernightIndexedSwap"
  p_freeOvernightIndexedSwap :: FunPtr (Ptr COvernightIndexedSwap -> IO ())
instance Upcastable COvernightIndexedSwap CSwap where
  c_upcast = c_OvernightIndexedSwapAsSwap
foreign import ccall safe "ql.h qlOvernightIndexedSwapAsSwap"
  c_OvernightIndexedSwapAsSwap :: Ptr COvernightIndexedSwap -> IO (Ptr CSwap)

data CBMASwap
instance Finalizable CBMASwap where
  finalize = p_freeBMASwap
foreign import ccall safe "ql.h &qlFreeBMASwap"
  p_freeBMASwap :: FunPtr (Ptr CBMASwap -> IO ())
instance Upcastable CBMASwap CSwap where
  c_upcast = c_BMASwapAsSwap
foreign import ccall safe "ql.h qlBMASwapAsSwap"
  c_BMASwapAsSwap :: Ptr CBMASwap -> IO (Ptr CSwap)

data CPayoff
instance Finalizable CPayoff where
  finalize = p_freePayoff
foreign import ccall safe "ql.h &qlFreePayoff"
  p_freePayoff :: FunPtr (Ptr CPayoff -> IO ())

data CBasketPayoff
instance Finalizable CBasketPayoff where
  finalize = p_freeBasketPayoff
foreign import ccall safe "ql.h &qlFreeBasketPayoff"
  p_freeBasketPayoff :: FunPtr (Ptr CBasketPayoff -> IO ())
instance Upcastable CBasketPayoff CPayoff where
  c_upcast = c_BasketPayoffAsPayoff
foreign import ccall safe "ql.h qlBasketPayoffAsPayoff"
  c_BasketPayoffAsPayoff :: Ptr CBasketPayoff -> IO (Ptr CPayoff)

data CStrikedTypePayoff
instance Finalizable CStrikedTypePayoff where
  finalize = p_freeStrikedTypePayoff
foreign import ccall safe "ql.h &qlFreeStrikedTypePayoff"
  p_freeStrikedTypePayoff :: FunPtr (Ptr CStrikedTypePayoff -> IO ())
instance Upcastable CStrikedTypePayoff CTypePayoff where
  c_upcast = c_StrikedTypePayoffAsTypePayoff
foreign import ccall safe "ql.h qlStrikedTypePayoffAsTypePayoff"
  c_StrikedTypePayoffAsTypePayoff :: Ptr CStrikedTypePayoff -> IO (Ptr CTypePayoff)

data CTypePayoff
instance Finalizable CTypePayoff where
  finalize = p_freeTypePayoff
foreign import ccall safe "ql.h &qlFreeTypePayoff"
  p_freeTypePayoff :: FunPtr (Ptr CTypePayoff -> IO ())
instance Upcastable CTypePayoff CPayoff where
  c_upcast = c_TypePayoffAsPayoff
foreign import ccall safe "ql.h qlTypePayoffAsPayoff"
  c_TypePayoffAsPayoff :: Ptr CTypePayoff -> IO (Ptr CPayoff)

data CPercentageStrikePayoff
instance Finalizable CPercentageStrikePayoff where
  finalize = p_freePercentageStrikePayoff
foreign import ccall safe "ql.h &qlFreePercentageStrikePayoff"
  p_freePercentageStrikePayoff :: FunPtr (Ptr CPercentageStrikePayoff -> IO ())
instance Upcastable CPercentageStrikePayoff CStrikedTypePayoff where
  c_upcast = c_PercentageStrikePayoffAsStrikedTypePayoff
foreign import ccall safe "ql.h qlPercentageStrikePayoffAsStrikedTypePayoff"
  c_PercentageStrikePayoffAsStrikedTypePayoff :: Ptr CPercentageStrikePayoff -> IO (Ptr CStrikedTypePayoff)

data CPlainVanillaPayoff
instance Finalizable CPlainVanillaPayoff where
  finalize = p_freePlainVanillaPayoff
foreign import ccall safe "ql.h &qlFreePlainVanillaPayoff"
  p_freePlainVanillaPayoff :: FunPtr (Ptr CPlainVanillaPayoff -> IO ())
instance Upcastable CPlainVanillaPayoff CStrikedTypePayoff where
  c_upcast = c_PlainVanillaPayoffAsStrikedTypePayoff
foreign import ccall safe "ql.h qlPlainVanillaPayoffAsStrikedTypePayoff"
  c_PlainVanillaPayoffAsStrikedTypePayoff :: Ptr CPlainVanillaPayoff -> IO (Ptr CStrikedTypePayoff)

data CAmericanExercise
instance Finalizable CAmericanExercise where
  finalize = p_freeAmericanExercise
foreign import ccall safe "ql.h &qlFreeAmericanExercise"
  p_freeAmericanExercise :: FunPtr (Ptr CAmericanExercise -> IO ())
instance Upcastable CAmericanExercise CExercise where
  c_upcast = c_AmericanExerciseAsExercise
foreign import ccall safe "ql.h qlAmericanExerciseAsExercise"
  c_AmericanExerciseAsExercise :: Ptr CAmericanExercise -> IO (Ptr CExercise)

data CBermudanExercise
instance Finalizable CBermudanExercise where
  finalize = p_freeBermudanExercise
foreign import ccall safe "ql.h &qlFreeBermudanExercise"
  p_freeBermudanExercise :: FunPtr (Ptr CBermudanExercise -> IO ())
instance Upcastable CBermudanExercise CExercise where
  c_upcast = c_BermudanExerciseAsExercise
foreign import ccall safe "ql.h qlBermudanExerciseAsExercise"
  c_BermudanExerciseAsExercise :: Ptr CBermudanExercise -> IO (Ptr CExercise)

data CEuropeanExercise
instance Finalizable CEuropeanExercise where
  finalize = p_freeEuropeanExercise
foreign import ccall safe "ql.h &qlFreeEuropeanExercise"
  p_freeEuropeanExercise :: FunPtr (Ptr CEuropeanExercise -> IO ())
instance Upcastable CEuropeanExercise CExercise where
  c_upcast = c_EuropeanExerciseAsExercise
foreign import ccall safe "ql.h qlEuropeanExerciseAsExercise"
  c_EuropeanExerciseAsExercise :: Ptr CEuropeanExercise -> IO (Ptr CExercise)

data CExercise
instance Finalizable CExercise where
  finalize = p_freeExercise
foreign import ccall safe "ql.h &qlFreeExercise"
  p_freeExercise :: FunPtr (Ptr CExercise -> IO ())

data CBarrierOption
instance Finalizable CBarrierOption where
  finalize = p_freeBarrierOption
foreign import ccall safe "ql.h &qlFreeBarrierOption"
  p_freeBarrierOption :: FunPtr (Ptr CBarrierOption -> IO ())
instance Upcastable CBarrierOption COneAssetOption where
  c_upcast = c_BarrierOptionAsOneAssetOption
foreign import ccall safe "ql.h qlBarrierOptionAsOneAssetOption"
  c_BarrierOptionAsOneAssetOption :: Ptr CBarrierOption -> IO (Ptr COneAssetOption)

data CCdsOption
instance Finalizable CCdsOption where
  finalize = p_freeCdsOption
foreign import ccall safe "ql.h &qlFreeCdsOption"
  p_freeCdsOption :: FunPtr (Ptr CCdsOption -> IO ())
instance Upcastable CCdsOption COption where
  c_upcast = c_CdsOptionAsOption
foreign import ccall safe "ql.h qlCdsOptionAsOption"
  c_CdsOptionAsOption :: Ptr CCdsOption -> IO (Ptr COption)

data CCreditDefaultSwap
instance Finalizable CCreditDefaultSwap where
  finalize = p_freeCreditDefaultSwap
foreign import ccall safe "ql.h &qlFreeCreditDefaultSwap"
  p_freeCreditDefaultSwap :: FunPtr (Ptr CCreditDefaultSwap -> IO ())
instance Upcastable CCreditDefaultSwap CInstrument where
  c_upcast = c_CreditDefaultSwapAsInstrument
foreign import ccall safe "ql.h qlCreditDefaultSwapAsInstrument"
  c_CreditDefaultSwapAsInstrument :: Ptr CCreditDefaultSwap -> IO (Ptr CInstrument)

data CDividendVanillaOption
instance Finalizable CDividendVanillaOption where
  finalize = p_freeDividendVanillaOption
foreign import ccall safe "ql.h &qlFreeDividendVanillaOption"
  p_freeDividendVanillaOption :: FunPtr (Ptr CDividendVanillaOption -> IO ())
instance Upcastable CDividendVanillaOption COneAssetOption where
  c_upcast = c_DividendVanillaOptionAsOneAssetOption
foreign import ccall safe "ql.h qlDividendVanillaOptionAsOneAssetOption"
  c_DividendVanillaOptionAsOneAssetOption :: Ptr CDividendVanillaOption -> IO (Ptr COneAssetOption)

data CMargrabeOption
instance Finalizable CMargrabeOption where
  finalize = p_freeMargrabeOption
foreign import ccall safe "ql.h &qlFreeMargrabeOption"
  p_freeMargrabeOption :: FunPtr (Ptr CMargrabeOption -> IO ())
instance Upcastable CMargrabeOption CMultiAssetOption where
  c_upcast = c_MargrabeOptionAsMultiAssetOption
foreign import ccall safe "ql.h qlMargrabeOptionAsMultiAssetOption"
  c_MargrabeOptionAsMultiAssetOption :: Ptr CMargrabeOption -> IO (Ptr CMultiAssetOption)

data CMultiAssetOption
instance Finalizable CMultiAssetOption where
  finalize = p_freeMultiAssetOption
foreign import ccall safe "ql.h &qlFreeMultiAssetOption"
  p_freeMultiAssetOption :: FunPtr (Ptr CMultiAssetOption -> IO ())
instance Upcastable CMultiAssetOption COption where
  c_upcast = c_MultiAssetOptionAsOption
foreign import ccall safe "ql.h qlMultiAssetOptionAsOption"
  c_MultiAssetOptionAsOption :: Ptr CMultiAssetOption -> IO (Ptr COption)

data COneAssetOption
instance Finalizable COneAssetOption where
  finalize = p_freeOneAssetOption
foreign import ccall safe "ql.h &qlFreeOneAssetOption"
  p_freeOneAssetOption :: FunPtr (Ptr COneAssetOption -> IO ())
instance Upcastable COneAssetOption COption where
  c_upcast = c_OneAssetOptionAsOption
foreign import ccall safe "ql.h qlOneAssetOptionAsOption"
  c_OneAssetOptionAsOption :: Ptr COneAssetOption -> IO (Ptr COption)

data COption
instance Finalizable COption where
  finalize = p_freeOption
foreign import ccall safe "ql.h &qlFreeOption"
  p_freeOption :: FunPtr (Ptr COption -> IO ())
instance Upcastable COption CInstrument where
  c_upcast = c_OptionAsInstrument
foreign import ccall safe "ql.h qlOptionAsInstrument"
  c_OptionAsInstrument :: Ptr COption -> IO (Ptr CInstrument)

data CQuantoVanillaOption
instance Finalizable CQuantoVanillaOption where
  finalize = p_freeQuantoVanillaOption
foreign import ccall safe "ql.h &qlFreeQuantoVanillaOption"
  p_freeQuantoVanillaOption :: FunPtr (Ptr CQuantoVanillaOption -> IO ())
instance Upcastable CQuantoVanillaOption COneAssetOption where
  c_upcast = c_QuantoVanillaOptionAsOneAssetOption
foreign import ccall safe "ql.h qlQuantoVanillaOptionAsOneAssetOption"
  c_QuantoVanillaOptionAsOneAssetOption :: Ptr CQuantoVanillaOption -> IO (Ptr COneAssetOption)

data CSwaption
instance Finalizable CSwaption where
  finalize = p_freeSwaption
foreign import ccall safe "ql.h &qlFreeSwaption"
  p_freeSwaption :: FunPtr (Ptr CSwaption -> IO ())
instance Upcastable CSwaption COption where
  c_upcast = c_SwaptionAsOption
foreign import ccall safe "ql.h qlSwaptionAsOption"
  c_SwaptionAsOption :: Ptr CSwaption -> IO (Ptr COption)

data CSwingExercise
instance Finalizable CSwingExercise where
  finalize = p_freeSwingExercise
foreign import ccall safe "ql.h &qlFreeSwingExercise"
  p_freeSwingExercise :: FunPtr (Ptr CSwingExercise -> IO ())
instance Upcastable CSwingExercise CBermudanExercise where
  c_upcast = c_SwingExerciseAsBermudanExercise
foreign import ccall safe "ql.h qlSwingExerciseAsBermudanExercise"
  c_SwingExerciseAsBermudanExercise :: Ptr CSwingExercise -> IO (Ptr CBermudanExercise)

data CVanillaOption
instance Finalizable CVanillaOption where
  finalize = p_freeVanillaOption
foreign import ccall safe "ql.h &qlFreeVanillaOption"
  p_freeVanillaOption :: FunPtr (Ptr CVanillaOption -> IO ())
instance Upcastable CVanillaOption COneAssetOption where
  c_upcast = c_VanillaOptionAsOneAssetOption
foreign import ccall safe "ql.h qlVanillaOptionAsOneAssetOption"
  c_VanillaOptionAsOneAssetOption :: Ptr CVanillaOption -> IO (Ptr COneAssetOption)

data CForwardVanillaOption
instance Finalizable CForwardVanillaOption where
  finalize = p_freeForwardVanillaOption
foreign import ccall safe "ql.h &qlFreeForwardVanillaOption"
  p_freeForwardVanillaOption :: FunPtr (Ptr CForwardVanillaOption -> IO ())
instance Upcastable CForwardVanillaOption COneAssetOption where
  c_upcast = c_ForwardVanillaOptionAsOneAssetOption
foreign import ccall safe "ql.h qlForwardVanillaOptionAsOneAssetOption"
  c_ForwardVanillaOptionAsOneAssetOption :: Ptr CForwardVanillaOption -> IO (Ptr COneAssetOption)

data CClaim
instance Finalizable CClaim where
  finalize = p_freeClaim
foreign import ccall safe "ql.h &qlFreeClaim"
  p_freeClaim :: FunPtr (Ptr CClaim -> IO ())

data CQuantoBarrierOption
instance Finalizable CQuantoBarrierOption where
  finalize = p_freeQuantoBarrierOption
foreign import ccall safe "ql.h &qlFreeQuantoBarrierOption"
  p_freeQuantoBarrierOption :: FunPtr (Ptr CQuantoBarrierOption -> IO ())
instance Upcastable CQuantoBarrierOption CBarrierOption where
  c_upcast = c_QuantoBarrierOptionAsBarrierOption
foreign import ccall safe "ql.h qlQuantoBarrierOptionAsBarrierOption"
  c_QuantoBarrierOptionAsBarrierOption :: Ptr CQuantoBarrierOption -> IO (Ptr CBarrierOption)

data CQuantoForwardVanillaOption
instance Finalizable CQuantoForwardVanillaOption where
  finalize = p_freeQuantoForwardVanillaOption
foreign import ccall safe "ql.h &qlFreeQuantoForwardVanillaOption"
  p_freeQuantoForwardVanillaOption :: FunPtr (Ptr CQuantoForwardVanillaOption -> IO ())
instance Upcastable CQuantoForwardVanillaOption CForwardVanillaOption where
  c_upcast = c_QuantoForwardVanillaOptionAsForwardVanillaOption
foreign import ccall safe "ql.h qlQuantoForwardVanillaOptionAsForwardVanillaOption"
  c_QuantoForwardVanillaOptionAsForwardVanillaOption :: Ptr CQuantoForwardVanillaOption -> IO (Ptr CForwardVanillaOption)

data CCapFloor
instance Finalizable CCapFloor where
  finalize = p_freeCapFloor
foreign import ccall safe "ql.h &qlFreeCapFloor"
  p_freeCapFloor :: FunPtr (Ptr CCapFloor -> IO ())
instance Upcastable CCapFloor CInstrument where
  c_upcast = c_CapFloorAsInstrument
foreign import ccall safe "ql.h qlCapFloorAsInstrument"
  c_CapFloorAsInstrument :: Ptr CCapFloor -> IO (Ptr CInstrument)

data CCallability
instance Finalizable CCallability where
  finalize = p_freeCallability
foreign import ccall safe "ql.h &qlFreeCallability"
  p_freeCallability :: FunPtr (Ptr CCallability -> IO ())

data CCallabilityPrice
instance Finalizable CCallabilityPrice where
  finalize = p_freeCallabilityPrice
foreign import ccall safe "ql.h &qlFreeCallabilityPrice"
  p_freeCallabilityPrice :: FunPtr (Ptr CCallabilityPrice -> IO ())

data CCallableBond
instance Finalizable CCallableBond where
  finalize = p_freeCallableBond
foreign import ccall safe "ql.h &qlFreeCallableBond"
  p_freeCallableBond :: FunPtr (Ptr CCallableBond -> IO ())
instance Upcastable CCallableBond CBond where
  c_upcast = c_CallableBondAsBond
foreign import ccall safe "ql.h qlCallableBondAsBond"
  c_CallableBondAsBond :: Ptr CCallableBond -> IO (Ptr CBond)

data CConvertibleBond
instance Finalizable CConvertibleBond where
  finalize = p_freeConvertibleBond
foreign import ccall safe "ql.h &qlFreeConvertibleBond"
  p_freeConvertibleBond :: FunPtr (Ptr CConvertibleBond -> IO ())
instance Upcastable CConvertibleBond CBond where
  c_upcast = c_ConvertibleBondAsBond
foreign import ccall safe "ql.h qlConvertibleBondAsBond"
  c_ConvertibleBondAsBond :: Ptr CConvertibleBond -> IO (Ptr CBond)

-- math
data CConstraint
instance Finalizable CConstraint where
  finalize = p_freeConstraint
foreign import ccall safe "ql.h &qlFreeConstraint"
  p_freeConstraint :: FunPtr (Ptr CConstraint -> IO ())

data COptimizationMethod
instance Finalizable COptimizationMethod where
  finalize = p_freeOptimizationMethod
foreign import ccall safe "ql.h &qlFreeOptimizationMethod"
  p_freeOptimizationMethod :: FunPtr (Ptr COptimizationMethod -> IO ())

data CEndCriteria
instance Finalizable CEndCriteria where
  finalize = p_freeEndCriteria
foreign import ccall safe "ql.h &qlFreeEndCriteria"
  p_freeEndCriteria :: FunPtr (Ptr CEndCriteria -> IO ())

-- pricingengines
data CPricingEngine

instance Finalizable CPricingEngine where
  finalize = p_freePricingEngine
foreign import ccall safe "ql.h &qlFreePricingEngine"
  p_freePricingEngine :: FunPtr (Ptr CPricingEngine -> IO ())

data CBlackCalculator
instance Finalizable CBlackCalculator where
  finalize = p_freeBlackCalculator
foreign import ccall safe "ql.h &qlFreeBlackCalculator"
  p_freeBlackCalculator :: FunPtr (Ptr CBlackCalculator -> IO ())

data CBlackScholesCalculator
instance Finalizable CBlackScholesCalculator where
  finalize = p_freeBlackScholesCalculator
foreign import ccall safe "ql.h &qlFreeBlackScholesCalculator"
  p_freeBlackScholesCalculator :: FunPtr (Ptr CBlackScholesCalculator -> IO ())
instance Upcastable CBlackScholesCalculator CBlackCalculator where
  c_upcast = c_BlackScholesCalculatorAsBlackCalculator
foreign import ccall safe "ql.h qlBlackScholesCalculatorAsBlackCalculator"
  c_BlackScholesCalculatorAsBlackCalculator :: Ptr CBlackScholesCalculator -> IO (Ptr CBlackCalculator)

-- methods
data CFdmSchemeDesc
instance Finalizable CFdmSchemeDesc where
  finalize = p_freeFdmSchemeDesc
foreign import ccall safe "ql.h &qlFreeFdmSchemeDesc"
  p_freeFdmSchemeDesc :: FunPtr (Ptr CFdmSchemeDesc -> IO ())

-- models
data CGJRGARCHModel
instance Finalizable CGJRGARCHModel where
  finalize = p_freeGJRGARCHModel
foreign import ccall safe "ql.h &qlFreeGJRGARCHModel"
  p_freeGJRGARCHModel :: FunPtr (Ptr CGJRGARCHModel -> IO ())

data CHestonModel
instance Finalizable CHestonModel where
  finalize = p_freeHestonModel
foreign import ccall safe "ql.h &qlFreeHestonModel"
  p_freeHestonModel :: FunPtr (Ptr CHestonModel -> IO ())

data CBatesModel
instance Finalizable CBatesModel where
  finalize = p_freeBatesModel
foreign import ccall safe "ql.h &qlFreeBatesModel"
  p_freeBatesModel :: FunPtr (Ptr CBatesModel -> IO ())

data CPiecewiseTimeDependentHestonModel
instance Finalizable CPiecewiseTimeDependentHestonModel where
  finalize = p_freePiecewiseTimeDependentHestonModel
foreign import ccall safe "ql.h &qlFreePiecewiseTimeDependentHestonModel"
  p_freePiecewiseTimeDependentHestonModel :: FunPtr (Ptr CPiecewiseTimeDependentHestonModel -> IO ())

data CShortRateModel
instance Finalizable CShortRateModel where
  finalize = p_freeShortRateModel
foreign import ccall safe "ql.h &qlFreeShortRateModel"
  p_freeShortRateModel :: FunPtr (Ptr CShortRateModel -> IO ())

data CAffineModel
instance Finalizable CAffineModel where
  finalize = p_freeAffineModel
foreign import ccall safe "ql.h &qlFreeAffineModel"
  p_freeAffineModel :: FunPtr (Ptr CAffineModel -> IO ())

data COneFactorAffineModel
instance Finalizable COneFactorAffineModel where
  finalize = p_freeOneFactorAffineModel
foreign import ccall safe "ql.h &qlFreeOneFactorAffineModel"
  p_freeOneFactorAffineModel :: FunPtr (Ptr COneFactorAffineModel -> IO ())
instance Upcastable COneFactorAffineModel CAffineModel where
  c_upcast = c_OneFactorAffineModelAsAffineModel
foreign import ccall safe "ql.h qlOneFactorAffineModelAsAffineModel"
  c_OneFactorAffineModelAsAffineModel :: Ptr COneFactorAffineModel -> IO (Ptr CAffineModel)

data CLiborForwardModel
instance Finalizable CLiborForwardModel where
  finalize = p_freeLiborForwardModel
foreign import ccall safe "ql.h &qlFreeLiborForwardModel"
  p_freeLiborForwardModel :: FunPtr (Ptr CLiborForwardModel -> IO ())
instance Upcastable CLiborForwardModel CAffineModel where
  c_upcast = c_LiborForwardModelAsAffineModel
foreign import ccall safe "ql.h qlLiborForwardModelAsAffineModel"
  c_LiborForwardModelAsAffineModel :: Ptr CLiborForwardModel -> IO (Ptr CAffineModel)

data CHullWhite
instance Finalizable CHullWhite where
  finalize = p_freeHullWhite
foreign import ccall safe "ql.h &qlFreeHullWhite"
  p_freeHullWhite :: FunPtr (Ptr CHullWhite -> IO ())
instance Upcastable CHullWhite COneFactorAffineModel where
  c_upcast = c_HullWhiteAsOneFactorAffineModel
foreign import ccall safe "ql.h qlHullWhiteAsOneFactorAffineModel"
  c_HullWhiteAsOneFactorAffineModel :: Ptr CHullWhite -> IO (Ptr COneFactorAffineModel)

data CCalibratedModel
instance Finalizable CCalibratedModel where
  finalize = p_freeCalibratedModel
foreign import ccall safe "ql.h &qlFreeCalibratedModel"
  p_freeCalibratedModel :: FunPtr (Ptr CCalibratedModel -> IO ())

data CG2
instance Finalizable CG2 where
  finalize = p_freeG2
foreign import ccall safe "ql.h &qlFreeG2"
  p_freeG2 :: FunPtr (Ptr CG2 -> IO ())
instance Upcastable CG2 CAffineModel where
  c_upcast = c_G2AsAffineModel
foreign import ccall safe "ql.h qlG2AsAffineModel"
  c_G2AsAffineModel :: Ptr CG2 -> IO (Ptr CAffineModel)
instance Upcastable CG2 CShortRateModel where
  c_upcast = c_G2AsShortRateModel
foreign import ccall safe "ql.h qlG2AsShortRateModel"
  c_G2AsShortRateModel :: Ptr CG2 -> IO (Ptr CShortRateModel)

data CBatesDetJumpModel
instance Finalizable CBatesDetJumpModel where
  finalize = p_freeBatesDetJumpModel
foreign import ccall safe "ql.h &qlFreeBatesDetJumpModel"
  p_freeBatesDetJumpModel :: FunPtr (Ptr CBatesDetJumpModel -> IO ())
instance Upcastable CBatesDetJumpModel CBatesModel where
  c_upcast = c_BatesDetJumpModelAsBatesModel
foreign import ccall safe "ql.h qlBatesDetJumpModelAsBatesModel"
  c_BatesDetJumpModelAsBatesModel :: Ptr CBatesDetJumpModel -> IO (Ptr CBatesModel)

data CBatesDoubleExpDetJumpModel
instance Finalizable CBatesDoubleExpDetJumpModel where
  finalize = p_freeBatesDoubleExpDetJumpModel
foreign import ccall safe "ql.h &qlFreeBatesDoubleExpDetJumpModel"
  p_freeBatesDoubleExpDetJumpModel :: FunPtr (Ptr CBatesDoubleExpDetJumpModel -> IO ())
instance Upcastable CBatesDoubleExpDetJumpModel CBatesDoubleExpModel where
  c_upcast = c_BatesDoubleExpDetJumpModelAsBatesDoubleExpModel
foreign import ccall safe "ql.h qlBatesDoubleExpDetJumpModelAsBatesDoubleExpModel"
  c_BatesDoubleExpDetJumpModelAsBatesDoubleExpModel :: Ptr CBatesDoubleExpDetJumpModel -> IO (Ptr CBatesDoubleExpModel)

data CBatesDoubleExpModel
instance Finalizable CBatesDoubleExpModel where
  finalize = p_freeBatesDoubleExpModel
foreign import ccall safe "ql.h &qlFreeBatesDoubleExpModel"
  p_freeBatesDoubleExpModel :: FunPtr (Ptr CBatesDoubleExpModel -> IO ())
instance Upcastable CBatesDoubleExpModel CHestonModel where
  c_upcast = c_BatesDoubleExpModelAsHestonModel
foreign import ccall safe "ql.h qlBatesDoubleExpModelAsHestonModel"
  c_BatesDoubleExpModelAsHestonModel :: Ptr CBatesDoubleExpModel -> IO (Ptr CHestonModel)

data CLmCorrelationModel
instance Finalizable CLmCorrelationModel where
  finalize = p_freeLmCorrelationModel
foreign import ccall safe "ql.h &qlFreeLmCorrelationModel"
  p_freeLmCorrelationModel :: FunPtr (Ptr CLmCorrelationModel -> IO ())

data CLmVolatilityModel
instance Finalizable CLmVolatilityModel where
  finalize = p_freeLmVolatilityModel
foreign import ccall safe "ql.h &qlFreeLmVolatilityModel"
  p_freeLmVolatilityModel :: FunPtr (Ptr CLmVolatilityModel -> IO ())

instance Upcastable CGJRGARCHModel CCalibratedModel where
  c_upcast = c_GJRGARCHModelAsCalibratedModel
foreign import ccall safe "ql.h qlGJRGARCHModelAsCalibratedModel"
  c_GJRGARCHModelAsCalibratedModel :: Ptr CGJRGARCHModel -> IO (Ptr CCalibratedModel)

instance Upcastable CHestonModel CCalibratedModel where
  c_upcast = c_HestonModelAsCalibratedModel
foreign import ccall safe "ql.h qlHestonModelAsCalibratedModel"
  c_HestonModelAsCalibratedModel :: Ptr CHestonModel -> IO (Ptr CCalibratedModel)

instance Upcastable CBatesModel CHestonModel where
  c_upcast = c_BatesModelAsHestonModel
foreign import ccall safe "ql.h qlBatesModelAsHestonModel"
  c_BatesModelAsHestonModel :: Ptr CBatesModel -> IO (Ptr CHestonModel)

instance Upcastable CLiborForwardModel CCalibratedModel where
  c_upcast = c_LiborForwardModelAsCalibratedModel
foreign import ccall safe "ql.h qlLiborForwardModelAsCalibratedModel"
  c_LiborForwardModelAsCalibratedModel :: Ptr CLiborForwardModel -> IO (Ptr CCalibratedModel)

instance Upcastable CPiecewiseTimeDependentHestonModel CCalibratedModel where
  c_upcast = c_PiecewiseTimeDependentHestonModelAsCalibratedModel
foreign import ccall safe "ql.h qlPiecewiseTimeDependentHestonModelAsCalibratedModel"
  c_PiecewiseTimeDependentHestonModelAsCalibratedModel :: Ptr CPiecewiseTimeDependentHestonModel -> IO (Ptr CCalibratedModel)

instance Upcastable CShortRateModel CCalibratedModel where
  c_upcast = c_ShortRateModelAsCalibratedModel
foreign import ccall safe "ql.h qlShortRateModelAsCalibratedModel"
  c_ShortRateModelAsCalibratedModel :: Ptr CShortRateModel -> IO (Ptr CCalibratedModel)

instance Upcastable COneFactorAffineModel CShortRateModel where
  c_upcast = c_OneFactorAffineModelAsShortRateModel
foreign import ccall safe "ql.h qlOneFactorAffineModelAsShortRateModel"
  c_OneFactorAffineModelAsShortRateModel :: Ptr COneFactorAffineModel -> IO (Ptr CShortRateModel)

data CCalibrationHelper
instance Finalizable CCalibrationHelper where
  finalize = p_freeCalibrationHelper
foreign import ccall safe "ql.h &qlFreeCalibrationHelper"
  p_freeCalibrationHelper :: FunPtr (Ptr CCalibrationHelper -> IO ())

-- processes
data CStochasticProcess1D
instance Finalizable CStochasticProcess1D where
  finalize = p_freeStochasticProcess1D
foreign import ccall safe "ql.h &qlFreeStochasticProcess1D"
  p_freeStochasticProcess1D :: FunPtr (Ptr CStochasticProcess1D -> IO ())
instance Upcastable CStochasticProcess1D CStochasticProcess where
  c_upcast = c_StochasticProcess1DAsStochasticProcess
foreign import ccall safe "ql.h qlStochasticProcess1DAsStochasticProcess"
  c_StochasticProcess1DAsStochasticProcess :: Ptr CStochasticProcess1D -> IO (Ptr CStochasticProcess)

data CBlackProcess
instance Finalizable CBlackProcess where
  finalize = p_freeBlackProcess
foreign import ccall safe "ql.h &qlFreeBlackProcess"
  p_freeBlackProcess :: FunPtr (Ptr CBlackProcess -> IO ())
instance Upcastable CBlackProcess CGeneralizedBlackScholesProcess where
  c_upcast = c_BlackProcessAsGeneralizedBlackScholesProcess
foreign import ccall safe "ql.h qlBlackProcessAsGeneralizedBlackScholesProcess"
  c_BlackProcessAsGeneralizedBlackScholesProcess :: Ptr CBlackProcess -> IO (Ptr CGeneralizedBlackScholesProcess)

data CGeneralizedBlackScholesProcess
instance Finalizable CGeneralizedBlackScholesProcess where
  finalize = p_freeGeneralizedBlackScholesProcess
foreign import ccall safe "ql.h &qlFreeGeneralizedBlackScholesProcess"
  p_freeGeneralizedBlackScholesProcess :: FunPtr (Ptr CGeneralizedBlackScholesProcess -> IO ())
instance Upcastable CGeneralizedBlackScholesProcess CStochasticProcess1D where
  c_upcast = c_GeneralizedBlackScholesProcessAsStochasticProcess1D
foreign import ccall safe "ql.h qlGeneralizedBlackScholesProcessAsStochasticProcess1D"
  c_GeneralizedBlackScholesProcessAsStochasticProcess1D :: Ptr CGeneralizedBlackScholesProcess -> IO (Ptr CStochasticProcess1D)

data CStochasticProcess
instance Finalizable CStochasticProcess where
  finalize = p_freeStochasticProcess
foreign import ccall safe "ql.h &qlFreeStochasticProcess"
  p_freeStochasticProcess :: FunPtr (Ptr CStochasticProcess -> IO ())

data CExtOUWithJumpsProcess
instance Finalizable CExtOUWithJumpsProcess where
  finalize = p_freeExtOUWithJumpsProcess
foreign import ccall safe "ql.h &qlFreeExtOUWithJumpsProcess"
  p_freeExtOUWithJumpsProcess :: FunPtr (Ptr CExtOUWithJumpsProcess -> IO ())
instance Upcastable CExtOUWithJumpsProcess CStochasticProcess where
  c_upcast = c_ExtOUWithJumpsProcessAsStochasticProcess
foreign import ccall safe "ql.h qlExtOUWithJumpsProcessAsStochasticProcess"
  c_ExtOUWithJumpsProcessAsStochasticProcess :: Ptr CExtOUWithJumpsProcess -> IO (Ptr CStochasticProcess)

data CExtendedOrnsteinUhlenbeckProcess
instance Finalizable CExtendedOrnsteinUhlenbeckProcess where
  finalize = p_freeExtendedOrnsteinUhlenbeckProcess
foreign import ccall safe "ql.h &qlFreeExtendedOrnsteinUhlenbeckProcess"
  p_freeExtendedOrnsteinUhlenbeckProcess :: FunPtr (Ptr CExtendedOrnsteinUhlenbeckProcess -> IO ())
instance Upcastable CExtendedOrnsteinUhlenbeckProcess CStochasticProcess1D where
  c_upcast = c_ExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D
foreign import ccall safe "ql.h qlExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D"
  c_ExtendedOrnsteinUhlenbeckProcessAsStochasticProcess1D :: Ptr CExtendedOrnsteinUhlenbeckProcess -> IO (Ptr CStochasticProcess1D)

data CGJRGARCHProcess
instance Finalizable CGJRGARCHProcess where
  finalize = p_freeGJRGARCHProcess
foreign import ccall safe "ql.h &qlFreeGJRGARCHProcess"
  p_freeGJRGARCHProcess :: FunPtr (Ptr CGJRGARCHProcess -> IO ())
instance Upcastable CGJRGARCHProcess CStochasticProcess where
  c_upcast = c_GJRGARCHProcessAsStochasticProcess
foreign import ccall safe "ql.h qlGJRGARCHProcessAsStochasticProcess"
  c_GJRGARCHProcessAsStochasticProcess :: Ptr CGJRGARCHProcess -> IO (Ptr CStochasticProcess)

data CHestonProcess
instance Finalizable CHestonProcess where
  finalize = p_freeHestonProcess
foreign import ccall safe "ql.h &qlFreeHestonProcess"
  p_freeHestonProcess :: FunPtr (Ptr CHestonProcess -> IO ())
instance Upcastable CHestonProcess CStochasticProcess where
  c_upcast = c_HestonProcessAsStochasticProcess
foreign import ccall safe "ql.h qlHestonProcessAsStochasticProcess"
  c_HestonProcessAsStochasticProcess :: Ptr CHestonProcess -> IO (Ptr CStochasticProcess)

data CBatesProcess
instance Finalizable CBatesProcess where
  finalize = p_freeBatesProcess
foreign import ccall safe "ql.h &qlFreeBatesProcess"
  p_freeBatesProcess :: FunPtr (Ptr CBatesProcess -> IO ())
instance Upcastable CBatesProcess CHestonProcess where
  c_upcast = c_BatesProcessAsHestonProcess
foreign import ccall safe "ql.h qlBatesProcessAsHestonProcess"
  c_BatesProcessAsHestonProcess :: Ptr CBatesProcess -> IO (Ptr CHestonProcess)

data CHybridHestonHullWhiteProcess
instance Finalizable CHybridHestonHullWhiteProcess where
  finalize = p_freeHybridHestonHullWhiteProcess
foreign import ccall safe "ql.h &qlFreeHybridHestonHullWhiteProcess"
  p_freeHybridHestonHullWhiteProcess :: FunPtr (Ptr CHybridHestonHullWhiteProcess -> IO ())
instance Upcastable CHybridHestonHullWhiteProcess CStochasticProcess where
  c_upcast = c_HybridHestonHullWhiteProcessAsStochasticProcess
foreign import ccall safe "ql.h qlHybridHestonHullWhiteProcessAsStochasticProcess"
  c_HybridHestonHullWhiteProcessAsStochasticProcess :: Ptr CHybridHestonHullWhiteProcess -> IO (Ptr CStochasticProcess)

data CKlugeExtOUProcess
instance Finalizable CKlugeExtOUProcess where
  finalize = p_freeKlugeExtOUProcess
foreign import ccall safe "ql.h &qlFreeKlugeExtOUProcess"
  p_freeKlugeExtOUProcess :: FunPtr (Ptr CKlugeExtOUProcess -> IO ())
instance Upcastable CKlugeExtOUProcess CStochasticProcess where
  c_upcast = c_KlugeExtOUProcessAsStochasticProcess
foreign import ccall safe "ql.h qlKlugeExtOUProcessAsStochasticProcess"
  c_KlugeExtOUProcessAsStochasticProcess :: Ptr CKlugeExtOUProcess -> IO (Ptr CStochasticProcess)

data CLiborForwardModelProcess
instance Finalizable CLiborForwardModelProcess where
  finalize = p_freeLiborForwardModelProcess
foreign import ccall safe "ql.h &qlFreeLiborForwardModelProcess"
  p_freeLiborForwardModelProcess :: FunPtr (Ptr CLiborForwardModelProcess -> IO ())
instance Upcastable CLiborForwardModelProcess CStochasticProcess where
  c_upcast = c_LiborForwardModelProcessAsStochasticProcess
foreign import ccall safe "ql.h qlLiborForwardModelProcessAsStochasticProcess"
  c_LiborForwardModelProcessAsStochasticProcess :: Ptr CLiborForwardModelProcess -> IO (Ptr CStochasticProcess)

data CStochasticProcessArray
instance Finalizable CStochasticProcessArray where
  finalize = p_freeStochasticProcessArray
foreign import ccall safe "ql.h &qlFreeStochasticProcessArray"
  p_freeStochasticProcessArray :: FunPtr (Ptr CStochasticProcessArray -> IO ())
instance Upcastable CStochasticProcessArray CStochasticProcess where
  c_upcast = c_StochasticProcessArrayAsStochasticProcess
foreign import ccall safe "ql.h qlStochasticProcessArrayAsStochasticProcess"
  c_StochasticProcessArrayAsStochasticProcess :: Ptr CStochasticProcessArray -> IO (Ptr CStochasticProcess)

data CVarianceGammaProcess
instance Finalizable CVarianceGammaProcess where
  finalize = p_freeVarianceGammaProcess
foreign import ccall safe "ql.h &qlFreeVarianceGammaProcess"
  p_freeVarianceGammaProcess :: FunPtr (Ptr CVarianceGammaProcess -> IO ())
instance Upcastable CVarianceGammaProcess CStochasticProcess1D where
  c_upcast = c_VarianceGammaProcessAsStochasticProcess1D
foreign import ccall safe "ql.h qlVarianceGammaProcessAsStochasticProcess1D"
  c_VarianceGammaProcessAsStochasticProcess1D :: Ptr CVarianceGammaProcess -> IO (Ptr CStochasticProcess1D)

data CMerton76Process
instance Finalizable CMerton76Process where
  finalize = p_freeMerton76Process
foreign import ccall safe "ql.h &qlFreeMerton76Process"
  p_freeMerton76Process :: FunPtr (Ptr CMerton76Process -> IO ())
instance Upcastable CMerton76Process CStochasticProcess1D where
  c_upcast = c_Merton76ProcessAsStochasticProcess1D
foreign import ccall safe "ql.h qlMerton76ProcessAsStochasticProcess1D"
  c_Merton76ProcessAsStochasticProcess1D :: Ptr CMerton76Process -> IO (Ptr CStochasticProcess1D)

data CHullWhiteProcess
instance Finalizable CHullWhiteProcess where
  finalize = p_freeHullWhiteProcess
foreign import ccall safe "ql.h &qlFreeHullWhiteProcess"
  p_freeHullWhiteProcess :: FunPtr (Ptr CHullWhiteProcess -> IO ())
instance Upcastable CHullWhiteProcess CStochasticProcess1D where
  c_upcast = c_HullWhiteProcessAsStochasticProcess1D
foreign import ccall safe "ql.h qlHullWhiteProcessAsStochasticProcess1D"
  c_HullWhiteProcessAsStochasticProcess1D :: Ptr CHullWhiteProcess -> IO (Ptr CStochasticProcess1D)

data CHullWhiteForwardProcess
instance Finalizable CHullWhiteForwardProcess where
  finalize = p_freeHullWhiteForwardProcess
foreign import ccall safe "ql.h &qlFreeHullWhiteForwardProcess"
  p_freeHullWhiteForwardProcess :: FunPtr (Ptr CHullWhiteForwardProcess -> IO ())
instance Upcastable CHullWhiteForwardProcess CStochasticProcess1D where
  c_upcast = c_HullWhiteForwardProcessAsStochasticProcess1D
foreign import ccall safe "ql.h qlHullWhiteForwardProcessAsStochasticProcess1D"
  c_HullWhiteForwardProcessAsStochasticProcess1D :: Ptr CHullWhiteForwardProcess -> IO (Ptr CStochasticProcess1D)

-- termstructures
data CRateHelper
data CYieldTermStructure
data CVolTermStructure

instance Finalizable CRateHelper where
  finalize = p_freeRateHelper
foreign import ccall safe "ql.h &qlFreeRateHelper"
  p_freeRateHelper :: FunPtr (Ptr CRateHelper -> IO ())

data CSwapRateHelper
instance Finalizable CSwapRateHelper where
  finalize = p_freeSwapRateHelper
foreign import ccall safe "ql.h &qlFreeSwapRateHelper"
  p_freeSwapRateHelper :: FunPtr (Ptr CSwapRateHelper -> IO ())
instance Upcastable CSwapRateHelper CRateHelper where
  c_upcast = c_SwapRateHelperAsRateHelper
foreign import ccall safe "ql.h qlSwapRateHelperAsRateHelper"
  c_SwapRateHelperAsRateHelper :: Ptr CSwapRateHelper -> IO (Ptr CRateHelper)

instance Finalizable CYieldTermStructure
  where finalize = p_freeYieldTermStructure
foreign import ccall safe "ql.h &qlFreeYieldTermStructure"
  p_freeYieldTermStructure :: FunPtr (Ptr CYieldTermStructure -> IO ())

data COptionletVolatilityStructure
instance Finalizable COptionletVolatilityStructure where
  finalize = p_freeOptionletVolatilityStructure
foreign import ccall safe "ql.h &qlFreeOptionletVolatilityStructure"
  p_freeOptionletVolatilityStructure :: FunPtr (Ptr COptionletVolatilityStructure -> IO ())
instance Upcastable COptionletVolatilityStructure CVolatilityTermStructure where
  c_upcast = c_OptionletVolatilityStructureAsVolatilityTermStructure
foreign import ccall safe "ql.h qlOptionletVolatilityStructureAsVolatilityTermStructure"
  c_OptionletVolatilityStructureAsVolatilityTermStructure :: Ptr COptionletVolatilityStructure -> IO (Ptr CVolatilityTermStructure)

data CBondHelper
instance Finalizable CBondHelper where
  finalize = p_freeBondHelper
foreign import ccall safe "ql.h &qlFreeBondHelper"
  p_freeBondHelper :: FunPtr (Ptr CBondHelper -> IO ())
instance Upcastable CBondHelper CRateHelper where
  c_upcast = c_BondHelperAsRateHelper
foreign import ccall safe "ql.h qlBondHelperAsRateHelper"
  c_BondHelperAsRateHelper :: Ptr CBondHelper -> IO (Ptr CRateHelper)

data COISRateHelper
instance Finalizable COISRateHelper where
  finalize = p_freeOISRateHelper
foreign import ccall safe "ql.h &qlFreeOISRateHelper"
  p_freeOISRateHelper :: FunPtr (Ptr COISRateHelper -> IO ())
instance Upcastable COISRateHelper CRateHelper where
  c_upcast = c_OISRateHelperAsRateHelper
foreign import ccall safe "ql.h qlOISRateHelperAsRateHelper"
  c_OISRateHelperAsRateHelper :: Ptr COISRateHelper -> IO (Ptr CRateHelper)

data CFittedBondDiscountCurveFittingMethod
instance Finalizable CFittedBondDiscountCurveFittingMethod where
  finalize = p_freeFittedBondDiscountCurveFittingMethod
foreign import ccall safe "ql.h &qlFreeFittedBondDiscountCurveFittingMethod"
  p_freeFittedBondDiscountCurveFittingMethod :: FunPtr (Ptr CFittedBondDiscountCurveFittingMethod -> IO ())

data CFittedBondDiscountCurve
instance Finalizable CFittedBondDiscountCurve where
  finalize = p_freeFittedBondDiscountCurve
foreign import ccall safe "ql.h &qlFreeFittedBondDiscountCurve"
  p_freeFittedBondDiscountCurve :: FunPtr (Ptr CFittedBondDiscountCurve -> IO ())
instance Upcastable CFittedBondDiscountCurve CYieldTermStructure where
  c_upcast = c_FittedBondDiscountCurveAsYieldTermStructure
foreign import ccall safe "ql.h qlFittedBondDiscountCurveAsYieldTermStructure"
  c_FittedBondDiscountCurveAsYieldTermStructure :: Ptr CFittedBondDiscountCurve -> IO (Ptr CYieldTermStructure)

data CTermStructure
instance Finalizable CTermStructure where
  finalize = p_freeTermStructure
foreign import ccall safe "ql.h &qlFreeTermStructure"
  p_freeTermStructure :: FunPtr (Ptr CTermStructure -> IO ())
instance Upcastable CYieldTermStructure CTermStructure where
  c_upcast = c_YieldTermStructureAsTermStructure
foreign import ccall safe "ql.h qlYieldTermStructureAsTermStructure"
  c_YieldTermStructureAsTermStructure :: Ptr CYieldTermStructure -> IO (Ptr CTermStructure)

data CBlackVolTermStructure
instance Finalizable CBlackVolTermStructure where
  finalize = p_freeBlackVolTermStructure
foreign import ccall safe "ql.h &qlFreeBlackVolTermStructure"
  p_freeBlackVolTermStructure :: FunPtr (Ptr CBlackVolTermStructure -> IO ())
instance Upcastable CBlackVolTermStructure CVolatilityTermStructure where
  c_upcast = c_BlackVolTermStructureAsVolatilityTermStructure
foreign import ccall safe "ql.h qlBlackVolTermStructureAsVolatilityTermStructure"
  c_BlackVolTermStructureAsVolatilityTermStructure :: Ptr CBlackVolTermStructure -> IO (Ptr CVolatilityTermStructure)

data CVolatilityTermStructure
instance Finalizable CVolatilityTermStructure where
  finalize = p_freeVolatilityTermStructure
foreign import ccall safe "ql.h &qlFreeVolatilityTermStructure"
  p_freeVolatilityTermStructure :: FunPtr (Ptr CVolatilityTermStructure -> IO ())
instance Upcastable CVolatilityTermStructure CTermStructure where
  c_upcast = c_VolatilityTermStructureAsTermStructure
foreign import ccall safe "ql.h qlVolatilityTermStructureAsTermStructure"
  c_VolatilityTermStructureAsTermStructure :: Ptr CVolatilityTermStructure -> IO (Ptr CTermStructure)

data CDefaultProbabilityTermStructure
instance Finalizable CDefaultProbabilityTermStructure where
  finalize = p_freeDefaultProbabilityTermStructure
foreign import ccall safe "ql.h &qlFreeDefaultProbabilityTermStructure"
  p_freeDefaultProbabilityTermStructure :: FunPtr (Ptr CDefaultProbabilityTermStructure -> IO ())
instance Upcastable CDefaultProbabilityTermStructure CTermStructure where
  c_upcast = c_DefaultProbabilityTermStructureAsTermStructure
foreign import ccall safe "ql.h qlDefaultProbabilityTermStructureAsTermStructure"
  c_DefaultProbabilityTermStructureAsTermStructure :: Ptr CDefaultProbabilityTermStructure -> IO (Ptr CTermStructure)

data CSwaptionVolatilityStructure
instance Finalizable CSwaptionVolatilityStructure where
  finalize = p_freeSwaptionVolatilityStructure
foreign import ccall safe "ql.h &qlFreeSwaptionVolatilityStructure"
  p_freeSwaptionVolatilityStructure :: FunPtr (Ptr CSwaptionVolatilityStructure -> IO ())
instance Upcastable CSwaptionVolatilityStructure CVolatilityTermStructure where
  c_upcast = c_SwaptionVolatilityStructureAsVolatilityTermStructure
foreign import ccall safe "ql.h qlSwaptionVolatilityStructureAsVolatilityTermStructure"
  c_SwaptionVolatilityStructureAsVolatilityTermStructure :: Ptr CSwaptionVolatilityStructure -> IO (Ptr CVolatilityTermStructure)

data CSmileSection
instance Finalizable CSmileSection where
  finalize = p_freeSmileSection
foreign import ccall safe "ql.h &qlFreeSmileSection"
  p_freeSmileSection :: FunPtr (Ptr CSmileSection -> IO ())

data CCapFloorTermVolSurface
instance Finalizable CCapFloorTermVolSurface where
  finalize = p_freeCapFloorTermVolSurface
foreign import ccall safe "ql.h &qlFreeCapFloorTermVolSurface"
  p_freeCapFloorTermVolSurface :: FunPtr (Ptr CCapFloorTermVolSurface -> IO ())
instance Upcastable CCapFloorTermVolSurface CVolatilityTermStructure where
  c_upcast = c_CapFloorTermVolSurfaceAsVolatilityTermStructure
foreign import ccall safe "ql.h qlCapFloorTermVolSurfaceAsVolatilityTermStructure"
  c_CapFloorTermVolSurfaceAsVolatilityTermStructure :: Ptr CCapFloorTermVolSurface -> IO (Ptr CVolatilityTermStructure)

data CLocalVolTermStructure
instance Finalizable CLocalVolTermStructure where
  finalize = p_freeLocalVolTermStructure
foreign import ccall safe "ql.h &qlFreeLocalVolTermStructure"
  p_freeLocalVolTermStructure :: FunPtr (Ptr CLocalVolTermStructure -> IO ())
instance Upcastable CLocalVolTermStructure CVolatilityTermStructure where
  c_upcast = c_LocalVolTermStructureAsVolatilityTermStructure
foreign import ccall safe "ql.h qlLocalVolTermStructureAsVolatilityTermStructure"
  c_LocalVolTermStructureAsVolatilityTermStructure :: Ptr CLocalVolTermStructure -> IO (Ptr CVolatilityTermStructure)

data CBlackVarianceCurve
instance Finalizable CBlackVarianceCurve where
  finalize = p_freeBlackVarianceCurve
foreign import ccall safe "ql.h &qlFreeBlackVarianceCurve"
  p_freeBlackVarianceCurve :: FunPtr (Ptr CBlackVarianceCurve -> IO ())
instance Upcastable CBlackVarianceCurve CBlackVolTermStructure where
  c_upcast = c_BlackVarianceCurveAsBlackVolTermStructure
foreign import ccall safe "ql.h qlBlackVarianceCurveAsBlackVolTermStructure"
  c_BlackVarianceCurveAsBlackVolTermStructure :: Ptr CBlackVarianceCurve -> IO (Ptr CBlackVolTermStructure)

data CDefaultProbabilityHelper
instance Finalizable CDefaultProbabilityHelper where
  finalize = p_freeDefaultProbabilityHelper
foreign import ccall safe "ql.h &qlFreeDefaultProbabilityHelper"
  p_freeDefaultProbabilityHelper :: FunPtr (Ptr CDefaultProbabilityHelper -> IO ())

data CCallableBondVolatilityStructure
instance Finalizable CCallableBondVolatilityStructure where
  finalize = p_freeCallableBondVolatilityStructure
foreign import ccall safe "ql.h &qlFreeCallableBondVolatilityStructure"
  p_freeCallableBondVolatilityStructure :: FunPtr (Ptr CCallableBondVolatilityStructure -> IO ())
instance Upcastable CCallableBondVolatilityStructure CTermStructure where
  c_upcast = c_CallableBondVolatilityStructureAsTermStructure
foreign import ccall safe "ql.h qlCallableBondVolatilityStructureAsTermStructure"
  c_CallableBondVolatilityStructureAsTermStructure :: Ptr CCallableBondVolatilityStructure -> IO (Ptr CTermStructure)

-- time
data CCalendar
data CDayCounter
data CSchedule

instance Finalizable CCalendar where
  finalize = p_freeCalendar
foreign import ccall safe "ql.h &qlFreeCalendar"
  p_freeCalendar :: FunPtr (Ptr CCalendar -> IO ())

instance NamedSingleton CCalendar where
  c_construct = c_calendar
  c_name = c_calendarName
foreign import ccall safe "ql.h qlCalendar"
  c_calendar :: CString -> Ptr CString -> IO (Ptr CCalendar)
foreign import ccall safe "ql.h qlCalendarName"
  c_calendarName :: Ptr CCalendar -> IO CString

instance Finalizable CDayCounter where
  finalize = p_freeDayCounter
foreign import ccall safe "ql.h &qlFreeDayCounter"
  p_freeDayCounter :: FunPtr (Ptr CDayCounter -> IO ())

instance NamedSingleton CDayCounter where
  c_construct = c_dayCounter
  c_name = c_dayCounterName
foreign import ccall safe "ql.h qlDayCounter"
  c_dayCounter :: CString -> Ptr CString -> IO (Ptr CDayCounter)
foreign import ccall safe "ql.h qlDayCounterName"
  c_dayCounterName :: Ptr CDayCounter -> IO CString

instance Finalizable CSchedule where
  finalize = p_freeSchedule
foreign import ccall safe "ql.h &qlFreeSchedule"
  p_freeSchedule :: FunPtr (Ptr CSchedule -> IO ())

-- common
data CInterestRate
data CQuote

instance Finalizable CInterestRate where
  finalize = p_freeInterestRate
foreign import ccall safe "ql.h &qlFreeInterestRate"
  p_freeInterestRate :: FunPtr (Ptr CInterestRate -> IO ())

instance Finalizable CQuote where
  finalize = p_freeQuote
foreign import ccall safe "ql.h &qlFreeQuote"
  p_freeQuote :: FunPtr (Ptr CQuote -> IO ())

data CSimpleQuote
instance Finalizable CSimpleQuote where
  finalize = p_freeSimpleQuote
foreign import ccall safe "ql.h &qlFreeSimpleQuote"
  p_freeSimpleQuote :: FunPtr (Ptr CSimpleQuote -> IO ())
instance Upcastable CSimpleQuote CQuote where
  c_upcast = c_SimpleQuoteAsQuote
foreign import ccall safe "ql.h qlSimpleQuoteAsQuote"
  c_SimpleQuoteAsQuote :: Ptr CSimpleQuote -> IO (Ptr CQuote)

data Matrix a = Matrix{matrixRows::Word, matrixColumns::Word, matrixData::[a]}
  deriving (Eq, Show)

data CTimeGrid
instance Finalizable CTimeGrid where
  finalize = p_freeTimeGrid
foreign import ccall safe "ql.h &qlFreeTimeGrid"
  p_freeTimeGrid :: FunPtr (Ptr CTimeGrid -> IO ())

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
