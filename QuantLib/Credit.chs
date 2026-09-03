-- |Portfolio credit scaffolding (@ql\/experimental\/credit@): the pool\/issuer\/basket
-- machinery a synthetic CDO or nth-to-default basket is built on, plus the Gaussian large
-- homogeneous pool (LHP) loss model. This is a deliberately minimal slice -- @ql\/experimental\/credit@
-- exposes far more (bucketed copula loss models, CDO-squared, base correlation, ...) than is
-- bound here; see the plan this module was built against for what was deliberately left out and
-- why.
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
  , basket
  , basketNotional
  , basketExpectedTrancheLoss

  , DefaultLossModel
  , gaussianLHPLossModel
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
{#pointer *QlDefaultLossModel as DefaultLossModel foreign -> CDefaultLossModel nocode#}

-- |ISDA standard default contractual key for corporate US debt. @restructuringType@ may be
-- 'NoRestructuring' to disable restructuring as a trigger.
{#fun qlNorthAmericaCorpDefaultKey as northAmericaCorpDefaultKey{withCurrency*`Currency' -- ^currency
  ,`Seniority' -- ^seniority
  ,fromEnumQuantity`(Int,TimeUnit)'& -- ^graceFailureToPay
  ,`Double' -- ^amountFailure
  ,`RestructuringType' -- ^restructuringType
  ,preErrorCheck-`String'errorCheck*-}->`DefaultProbKey'peekDefaultProbKey*#}

-- |An issuer's default-probability term structures, keyed by the contract terms
-- ('DefaultProbKey') they apply to. This binds only the @(key, curve)@-list constructor; the
-- default-event-history overload is not bound.
issuer :: NonEmpty (DefaultProbKey, DefaultProbabilityTermStructure) -> IO Issuer
issuer probs = qlIssuer keys curves
  where (keys, curves) = unzip (toList probs)
{#fun qlIssuer{withDefaultProbKeyArray*`[DefaultProbKey]'&
  ,withDefaultProbabilityTermStructureArrayRaw*`[DefaultProbabilityTermStructure]'
  ,preErrorCheck-`String'errorCheck*-}->`Issuer'peekIssuer*#}

-- |A named collection of issuers, each entered under its own default-probability key. There is
-- no @add@ mutator here (unlike upstream's @Pool::add@): the whole membership is passed in one
-- call, per CLAUDE.md's \"prefer constructing a new object over mutating one\".
pool :: NonEmpty (String, Issuer, DefaultProbKey) -> IO Pool
pool entries = qlPool names issuers keys
  where (names, issuers, keys) = unzip3 (toList entries)
{#fun qlPool{withStringArray*`[String]'&
  ,withIssuerArrayRaw*`[Issuer]'
  ,withDefaultProbKeyArrayRaw*`[DefaultProbKey]'
  ,preErrorCheck-`String'errorCheck*-}->`Pool'peekPool*#}

-- |A basket of named notional positions drawn from a 'Pool', tranched between
-- @attachmentRatio@ and @detachmentRatio@ (as fractions of the basket's total notional), with a
-- 'DefaultLossModel' attached. The loss model is a constructor argument here rather than a
-- separate @setLossModel@ call: upstream's @Basket@ takes it as a mutator, but every use in the
-- reference fixtures (@cdo.cpp@, @nthtodefault.cpp@) sets it once at construction and never
-- changes it afterwards, so the shim calls @setLossModel@ internally and no mutator is exposed
-- to Haskell.
basket :: Day -> NonEmpty (String, Double) -> Pool -> Double -> Double -> Claim -> DefaultLossModel -> IO Basket
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
  ,preErrorCheck-`String'errorCheck*-}->`Basket'peekBasket*#}

-- |Basket total notional at inception (sum of the positions' notionals, ignoring any losses).
{#fun qlBasketNotional as basketNotional{withBasket*`Basket',preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Expected tranche loss on date @d@, according to the basket's attached loss model.
{#fun qlBasketExpectedTrancheLoss as basketExpectedTrancheLoss{withBasket*`Basket',withDay*`Day' -- ^d
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |Gaussian large homogeneous pool (LHP) loss model: an analytical one-factor Gaussian-copula
-- approximation, exact in the limit of a large, homogeneous portfolio (Kalemanova, Schmid,
-- Werner, \"The Normal Inverse Gaussian Distribution for Synthetic CDO Pricing\", Journal of
-- Derivatives 14(3), 2007). Only the @Handle\<Quote\>@ correlation overload is bound, per
-- CLAUDE.md's @std::variant@\/@Handle\<Quote\>@ convention -- a caller with a bare correlation
-- number can get the other overload for free via 'QuantLib.Quote.simpleQuote'. @recoveries@ is
-- one recovery rate per basket name, in the same order the basket's own names appear.
gaussianLHPLossModel :: GenQuote q -> NonEmpty Double -> IO DefaultLossModel
gaussianLHPLossModel correlQuote recoveries = qlGaussianLHPLossModel correlQuote (toList recoveries)
{#fun qlGaussianLHPLossModel{withQuote*`GenQuote q' -- ^correlQuote
  ,withDoubleArray*`[Double]'&
  ,preErrorCheck-`String'errorCheck*-}->`DefaultLossModel'peekDefaultLossModel*#}

-- |One-factor Gaussian- or Student-T-copula constant-loss latent model (John Hull and Alan
-- White, \"Valuation of a CDO and nth to default CDS without Monte Carlo simulation\", Journal
-- of Derivatives 12, 2, 2004), exact (no large-pool approximation) but limited to digital-type
-- payoffs (e.g. 'QuantLib.Instrument.Credit.NthToDefault') since it has no distribution-type
-- loss integration of its own. @recoveries@ is one recovery rate per basket name, in the same
-- order the basket's own names appear (@nVariables@ is taken from its length). @tOrders@
-- selects the copula: @[]@ uses a Gaussian copula; a non-empty list selects a Student-T copula
-- with these degrees of freedom -- upstream requires exactly one entry per systemic factor plus
-- one for the idiosyncratic factor, which for this one-factor model is always two entries (e.g.
-- @[5,5]@), and throws if the count is wrong. Only the @Handle\<Quote\>@ correlation overload is
-- bound, per CLAUDE.md's @std::variant@\/@Handle\<Quote\>@ convention.
constantLossModel :: GenQuote q -> NonEmpty Double -> LatentModelIntegrationType -> [Int] -> IO DefaultLossModel
constantLossModel correlQuote recoveries integralType tOrders =
  qlConstantLossModel correlQuote (toList recoveries) integralType tOrders
{#fun qlConstantLossModel{withQuote*`GenQuote q'
  ,withDoubleArray*`[Double]'&
  ,`LatentModelIntegrationType'
  ,withIntArray*`[Int]'&
  ,preErrorCheck-`String'errorCheck*-}->`DefaultLossModel'peekDefaultLossModel*#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
