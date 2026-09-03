-- |Portfolio-credit types, baskets, and loss models.
module QuantLib.Credit
  (
    Seniority(..)
  , RestructuringType(..)
  , LatentModelIntegrationType(..)

  , DefaultProbKey
  , northAmericaCorpDefaultKey

  , Issuer
  , issuer

  , Pool
  , pool

  , Basket
  , basketNotional
  , basketRemainingNotional
  , basketRecoveryRate

  , TrancheBasket
  , basket
  , trancheBasketAsBasket
  , basketExpectedTrancheLoss
  , basketProbOverLoss
  , basketPercentile
  , basketExpectedShortfall

  , DigitalBasket
  , digitalBasket
  , digitalBasketAsBasket
  , basketDefaultCorrelation
  , basketProbAtLeastNEvents

  , DefaultLossModel
  , gaussianLHPLossModel

  , DigitalLossModel
  , constantLossModel
  ) where
import Data.List.NonEmpty(NonEmpty, toList)

import QuantLib.Internal
import QuantLib.Internal.Common
import QuantLib.Internal.Type

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

-- |Seniority of a bond; also used as the ISDA tier\/seniority for CDS conventional spreads.
{#enum Seniority{} deriving (Show, Eq, Read, Bounded)#}

-- |Restructuring clause of a default-probability key (ISDA @XR@\/@MR@\/@MM@\/@CR@).
{#enum RestructuringType{} deriving (Show, Eq, Read, Bounded)#}

-- |Numerical-integration scheme used by a 'QuantLib.Credit.LatentModel'-based copula loss
-- model (e.g. the gaussian\/student constant-loss dispatcher bound alongside 'NthToDefault').
{#enum LatentModelIntegrationType{} deriving (Show, Eq, Read, Bounded)#}

{#pointer *Currency foreign -> CCurrency nocode#}
{#pointer *QlQuote as Quote foreign -> CQuote' nocode#}
{#pointer *QlClaim as Claim foreign -> CQlClaim nocode#}
{#pointer *QlDefaultProbabilityTermStructure as DefaultProbabilityTermStructure foreign -> CDefaultProbabilityTermStructure' nocode#}
{#pointer *DefaultProbKey foreign -> CDefaultProbKey nocode#}
{#pointer *Issuer foreign -> CIssuer nocode#}
{#pointer *QlPool as Pool foreign -> CPool nocode#}
{#pointer *QlBasket as Basket foreign -> CBasket nocode#}
{#pointer *QlBasket as TrancheBasket foreign -> CBasket nocode#}
{#pointer *QlBasket as DigitalBasket foreign -> CBasket nocode#}
{#pointer *QlDefaultLossModel as DefaultLossModel foreign -> CDefaultLossModel nocode#}
{#pointer *QlDefaultLossModel as DigitalLossModel foreign -> CDefaultLossModel nocode#}

-- |ISDA standard default contractual key for corporate US debt. @restructuringType@ may be
-- 'NoRestructuring' to disable restructuring as a trigger.
{#fun qlNorthAmericaCorpDefaultKey as northAmericaCorpDefaultKey{withCurrency*`Currency' -- ^currency
  ,`Seniority' -- ^seniority
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^graceFailureToPay
  ,`Double' -- ^amountFailure
  ,`RestructuringType' -- ^restructuringType
  ,preErrorCheck-`String'errorCheck*-}->`DefaultProbKey'peekDefaultProbKey*#}

-- |An issuer's default-probability term structures, keyed by contract terms.
issuer :: NonEmpty (DefaultProbKey, DefaultProbabilityTermStructure) -> IO Issuer
issuer probs = qlIssuer keys curves
  where (keys, curves) = unzip (toList probs)
{#fun qlIssuer{withDefaultProbKeyArray*`[DefaultProbKey]'&
  ,withDefaultProbabilityTermStructureArrayRaw*`[DefaultProbabilityTermStructure]'
  ,preErrorCheck-`String'errorCheck*-}->`Issuer'peekIssuer*#}

-- |A named collection of issuers and their default-probability keys.
pool :: NonEmpty (String, Issuer, DefaultProbKey) -> IO Pool
pool entries = qlPool names issuers keys
  where (names, issuers, keys) = unzip3 (toList entries)
{#fun qlPool{withStringArray*`[String]'&
  ,withIssuerArrayRaw*`[Issuer]'
  ,withDefaultProbKeyArrayRaw*`[DefaultProbKey]'
  ,preErrorCheck-`String'errorCheck*-}->`Pool'peekPool*#}

-- |A tranched basket with a tranche-loss model; usable for CDO pricing.
basket :: Day -> NonEmpty (String, Double) -> Pool -> Double -> Double -> Claim -> DefaultLossModel -> IO TrancheBasket
basket refDate positions p attachmentRatio detachmentRatio cl lm =
  qlBasket refDate names notionals p attachmentRatio detachmentRatio cl lm
  where (names, notionals) = unzip (toList positions)
{#fun qlBasket{withDay*`Day' -- ^refDate
  ,withStringArray*`[String]'&
  ,withDoubleArrayRaw*`[Double]'
  ,withPool*`Pool'
  ,`Double' -- ^attachmentRatio
  ,`Double' -- ^detachmentRatio
  ,withClaim*`Claim'
  ,withDefaultLossModel*`DefaultLossModel'
  ,preErrorCheck-`String'errorCheck*-}->`TrancheBasket'peekTrancheBasket*#}

-- |Basket total notional at inception, before losses.
{#fun qlBasketNotional as basketNotional{withBasket*`Basket',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Live (undefaulted) notional remaining at date @d@. Loss-model-agnostic.
{#fun qlBasketRemainingNotional as basketRemainingNotional{withBasket*`Basket',withDay*`Day' -- ^d
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Expected recovery rate of the @iName@-th pool name (0-based, in basket-construction order),
-- conditional on default by date @d@. Loss-model-agnostic.
{#fun qlBasketRecoveryRate as basketRecoveryRate{withBasket*`Basket',withDay*`Day' -- ^d
  ,fromIntegral`Word' -- ^iName
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Expected tranche loss on date @d@; requires a tranche-loss model.
{#fun qlBasketExpectedTrancheLoss as basketExpectedTrancheLoss{withTrancheBasket*`TrancheBasket',withDay*`Day' -- ^d
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Probability the tranche loses at least @lossFraction@ of the tranche notional by date @d@.
{#fun qlBasketProbOverLoss as basketProbOverLoss{withTrancheBasket*`TrancheBasket',withDay*`Day' -- ^d
  ,`Double' -- ^lossFraction
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Tranche loss fraction at the given percentile of the loss distribution on date @d@ (VaR).
{#fun qlBasketPercentile as basketPercentile{withTrancheBasket*`TrancheBasket',withDay*`Day' -- ^d
  ,`Double' -- ^prob
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Expected tranche loss given loss exceeds the given percentile on date @d@.
{#fun qlBasketExpectedShortfall as basketExpectedShortfall{withTrancheBasket*`TrancheBasket',withDay*`Day' -- ^d
  ,`Double' -- ^prob
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Pearson default-probability correlation between pool names @iName@ and @jName@ (0-based) by
-- date @d@.
{#fun qlBasketDefaultCorrelation as basketDefaultCorrelation{withDigitalBasket*`DigitalBasket',withDay*`Day' -- ^d
  ,fromIntegral`Word' -- ^iName
  ,fromIntegral`Word' -- ^jName
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Probability of at least @n@ defaults in the basket by date @d@.
{#fun qlBasketProbAtLeastNEvents as basketProbAtLeastNEvents{withDigitalBasket*`DigitalBasket'
  ,fromIntegral`Word' -- ^n
  ,withDay*`Day' -- ^d
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |A digital-loss basket for nth-to-default pricing.
digitalBasket :: Day -> NonEmpty (String, Double) -> Pool -> Double -> Double -> Claim -> DigitalLossModel -> IO DigitalBasket
digitalBasket refDate positions p attachmentRatio detachmentRatio cl lm =
  qlDigitalBasket refDate names notionals p attachmentRatio detachmentRatio cl lm
  where (names, notionals) = unzip (toList positions)
{#fun qlDigitalBasket{withDay*`Day' -- ^refDate
  ,withStringArray*`[String]'&
  ,withDoubleArrayRaw*`[Double]'
  ,withPool*`Pool'
  ,`Double' -- ^attachmentRatio
  ,`Double' -- ^detachmentRatio
  ,withClaim*`Claim'
  ,withDigitalLossModel*`DigitalLossModel'
  ,preErrorCheck-`String'errorCheck*-}->`DigitalBasket'peekDigitalBasket*#}

-- |One-factor Gaussian-copula LHP loss model. @recoveries@ follow basket-name order.
gaussianLHPLossModel :: GenQuote q -> NonEmpty Double -> IO DefaultLossModel
gaussianLHPLossModel correlQuote recoveries = qlGaussianLHPLossModel correlQuote (toList recoveries)
{#fun qlGaussianLHPLossModel{withQuote*`GenQuote q' -- ^correlQuote
  ,withDoubleArray*`[Double]'&
  ,preErrorCheck-`String'errorCheck*-}->`DefaultLossModel'peekDefaultLossModel*#}

-- |One-factor Gaussian- or Student-T-copula model for digital-loss baskets.
-- @[]@ selects Gaussian; @tOrders@ selects Student-T degrees of freedom.
constantLossModel :: GenQuote q -> NonEmpty Double -> LatentModelIntegrationType -> [Int] -> IO DigitalLossModel
constantLossModel correlQuote recoveries integralType tOrders =
  qlConstantLossModel correlQuote (toList recoveries) integralType tOrders
{#fun qlConstantLossModel{withQuote*`GenQuote q'
  ,withDoubleArray*`[Double]'&
  ,`LatentModelIntegrationType'
  ,withIntArray*`[Int]'&
  ,preErrorCheck-`String'errorCheck*-}->`DigitalLossModel'peekDigitalLossModel*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
