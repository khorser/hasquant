{-# LANGUAGE MultiParamTypeClasses #-}
module QuantLib.Internal.Types
  (
  -- cashflow
    CLeg
  , CFloatingRateCouponPricer

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

  -- pricingengines
  , CPricingEngine

  -- processes
  , CBlackProcess
  , CGeneralizedBlackScholesProcess
  , CStochasticProcess
  , CStochasticProcess1D

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

  -- time
  , CCalendar
  , CDayCounter
  , CPeriod
  , CSchedule

  -- common
  , CInterestRate
  , CQuote
  , CSimpleQuote
  )
where

import QuantLib.Internal.Utils

-- cashflows
data CLeg

instance Finalizable CLeg where
  finalize = p_freeLeg
foreign import ccall safe "ql.h &qlFreeLeg"
  p_freeLeg :: FunPtr (Ptr CLeg -> IO ())

data CFloatingRateCouponPricer

instance Finalizable CFloatingRateCouponPricer where
  finalize = p_freeFloatingCouponPricer
foreign import ccall safe "ql.h &qlFreeFloatingCouponPricer"
  p_freeFloatingCouponPricer :: FunPtr (Ptr CFloatingRateCouponPricer -> IO ())

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

-- pricingengines
data CPricingEngine

instance Finalizable CPricingEngine where
  finalize = p_freePricingEngine
foreign import ccall safe "ql.h &qlFreePricingEngine"
  p_freePricingEngine :: FunPtr (Ptr CPricingEngine -> IO ())

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

-- time
data CCalendar
data CDayCounter
data CPeriod
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

instance Finalizable CPeriod where
  finalize = p_freePeriod
foreign import ccall safe "ql.h &qlFreePeriod"
  p_freePeriod :: FunPtr (Ptr CPeriod -> IO ())

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

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
