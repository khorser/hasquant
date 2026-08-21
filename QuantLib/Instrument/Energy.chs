module QuantLib.Instrument.Energy
  (
    SecondaryCosts
  , SecondaryCostAmounts
  , PricingErrorLevel(..)
  , PricingError(..)
  , PricingErrors
  , EnergyDailyPosition(..)
  , EnergyDailyPositions
  , CommodityCashFlow
  , CommodityCashFlows

  , commodityCashFlowDate
  , commodityCashFlowDiscountedAmount
  , commodityCashFlowUndiscountedAmount
  , commodityCashFlowDiscountedPaymentAmount
  , commodityCashFlowUndiscountedPaymentAmount
  , commodityCashFlowDiscountFactor
  , commodityCashFlowPaymentDiscountFactor
  , commodityCashFlowFinalized

  , addPricingError
  , secondaryCostAmounts
  , pricingErrors

  , quantity

  , EnergyFuture
  , energyFuture

  , EnergySwap
  , dailyPositions
  , paymentCashFlows

  , EnergyVanillaSwap
  , energyVanillaSwap

  , EnergyBasisSwap
  , energyBasisSwap

  , DeliverySchedule(..)
  , QuantityPeriodicity(..)
  , createPricingPeriods
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type
import QuantLib.Internal.Enum
import QuantLib.Time.Date(Day)
import QuantLib.Commodity(CommodityType, UnitOfMeasure, PaymentTerm, Quantity, CommodityUnitCost,
  PricingPeriod, PricingPeriods, pricingPeriod,
  pricingPeriodStartDate, pricingPeriodEndDate, pricingPeriodPaymentDate, pricingPeriodQuantity)
import QuantLib.Index.Commodity(CommodityIndex)
import Foreign.Ptr(Ptr)
import Foreign.C.Types(CUInt, CInt)
import Foreign.Marshal.Alloc(alloca)
import Foreign.Marshal.Utils(fromBool)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"
#include "qlEnumObjects.h"

#include "ql.h"

{#pointer *Calendar foreign -> CCalendar nocode#}
{#pointer *Currency foreign -> CCurrency nocode#}
{#pointer *CommodityType foreign -> CCommodityType nocode#}
{#pointer *UnitOfMeasure foreign -> CUnitOfMeasure nocode#}
{#pointer *PaymentTerm foreign -> CPaymentTerm nocode#}
{#pointer *QlCommodityIndex as CommodityIndex foreign -> CCommodityIndex' nocode#}
{#pointer *QlYieldTermStructure as YieldTermStructure foreign -> CYieldTermStructure' nocode#}
{#pointer *QlCommodity as Commodity foreign -> CCommodity' nocode#}
{#pointer *QlEnergyCommodity as EnergyCommodity foreign -> CEnergyCommodity' nocode#}
{#pointer *QlEnergyFuture as EnergyFuture foreign -> CEnergyFuture' nocode#}
{#pointer *QlEnergySwap as EnergySwap foreign -> CEnergySwap' nocode#}
{#pointer *QlEnergyVanillaSwap as EnergyVanillaSwap foreign -> CEnergyVanillaSwap' nocode#}
{#pointer *QlEnergyBasisSwap as EnergyBasisSwap foreign -> CEnergyBasisSwap' nocode#}
{#pointer *QlCommodityCashFlow as CommodityCashFlow foreign -> CCommodityCashFlow nocode#}

-- |QuantLib's @map<string, ext::any>@, used with exactly two concrete alternatives across the
-- module (@CommodityUnitCost@\/@Money@, confirmed from @energycommodity.cpp@'s two @any_cast@
-- branches) -- bound as a real 2-variant sum rather than a generic @any@. Passed optionally to
-- every energy-instrument constructor below; @[]@ stands in for upstream's null @shared_ptr@.
type SecondaryCosts = [(String, Either CommodityUnitCost (Double, Currency))]

-- |The computed, currency-resolved output of 'SecondaryCosts' -- @Commodity::secondaryCostAmounts()@,
-- a @map<string, Money>@.
type SecondaryCostAmounts = [(String, (Double, Currency))]

-- |A single entry of 'PricingErrors' -- @tradeId@ is never set by any constructor path that
-- reaches 'addPricingError' (upstream's own call sites all default it to empty), so it isn't
-- bound.
data PricingError = PricingError
  { pricingErrorLevel :: PricingErrorLevel
  , pricingErrorMessage :: String
  , pricingErrorDetail :: String
  } deriving (Show, Eq)

type PricingErrors = [PricingError]

-- |One day's position detail from an 'EnergySwap' leaf's @dailyPositions()@ -- a flat record
-- rather than a @(Day, ...)@ pair, since 'edpDate' already carries the map key.
data EnergyDailyPosition = EnergyDailyPosition
  { edpDate :: Day
  , edpQuantityAmount :: Double
  , edpPayLegPrice :: Double
  , edpReceiveLegPrice :: Double
  , edpRiskDelta :: Double
  , edpUnrealized :: Bool
  } deriving (Show, Eq)

type EnergyDailyPositions = [EnergyDailyPosition]

type CommodityCashFlows = [CommodityCashFlow]

-- |The cash flow's date -- also the @paymentCashFlows()@ map's own key, so it isn't duplicated as
-- a separate tuple field alongside the list of 'CommodityCashFlow's.
{#fun pure qlCommodityCashFlowDate as commodityCashFlowDate{withCommodityCashFlow*`CommodityCashFlow'}->`Day'toDay#}

-- |The discounted amount, in the global commodity base currency ('QuantLib.Commodity.commoditySettingsCurrency').
{#fun pure qlCommodityCashFlowDiscountedAmount as commodityCashFlowDiscountedAmount{withCommodityCashFlow*`CommodityCashFlow',alloca-`Currency'peekCurrencyPtr*}->`Double'#}
-- |As 'commodityCashFlowDiscountedAmount', without the discount factor applied.
{#fun pure qlCommodityCashFlowUndiscountedAmount as commodityCashFlowUndiscountedAmount{withCommodityCashFlow*`CommodityCashFlow',alloca-`Currency'peekCurrencyPtr*}->`Double'#}
-- |The discounted amount, in the payment (leg) currency.
{#fun pure qlCommodityCashFlowDiscountedPaymentAmount as commodityCashFlowDiscountedPaymentAmount{withCommodityCashFlow*`CommodityCashFlow',alloca-`Currency'peekCurrencyPtr*}->`Double'#}
-- |As 'commodityCashFlowDiscountedPaymentAmount', without the discount factor applied.
{#fun pure qlCommodityCashFlowUndiscountedPaymentAmount as commodityCashFlowUndiscountedPaymentAmount{withCommodityCashFlow*`CommodityCashFlow',alloca-`Currency'peekCurrencyPtr*}->`Double'#}
-- |The discount factor applied to the base-currency amount.
{#fun pure qlCommodityCashFlowDiscountFactor as commodityCashFlowDiscountFactor{withCommodityCashFlow*`CommodityCashFlow'}->`Double'#}
-- |The discount factor applied to the payment-currency amount.
{#fun pure qlCommodityCashFlowPaymentDiscountFactor as commodityCashFlowPaymentDiscountFactor{withCommodityCashFlow*`CommodityCashFlow'}->`Double'#}
-- |Whether this cash flow's payment date has already occurred as of the evaluation date.
{#fun pure qlCommodityCashFlowFinalized as commodityCashFlowFinalized{withCommodityCashFlow*`CommodityCashFlow'}->`Bool'#}

-- |Record a pricing diagnostic against a 'Commodity'\/'EnergyCommodity' leaf (any of 'EnergyFuture',
-- 'EnergyVanillaSwap', 'EnergyBasisSwap'), retrievable afterwards via 'pricingErrors'. Mirrors
-- upstream's own default empty @detail@ with a plain @\"\"@ argument.
{#fun qlCommodityAddPricingError as addPricingError
  {withCommodity*`GenCommodity c'
  ,fromEnumC`PricingErrorLevel'
  ,`String'
  ,`String'}->`()'#}

{#fun qlCommoditySecondaryCostAmounts as qlCommoditySecondaryCostAmounts_
  {withCommodity*`GenCommodity c'
  ,preArray-`[String]'&peekCStringArray*
  ,preArray-`[Double]'&peekDoubleArray*
  ,preArray-`[Currency]'&peekCurrencyArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |The currency-resolved secondary costs computed during the most recent pricing
-- (@performCalculations()@) of this 'Commodity'\/'EnergyCommodity' leaf -- a plain member read, not
-- itself a pricing trigger, so call 'QuantLib.Instrument.npv' first if it hasn't been priced yet.
secondaryCostAmounts :: GenCommodity c -> IO SecondaryCostAmounts
secondaryCostAmounts o = do
  (keys, amts, ccys) <- qlCommoditySecondaryCostAmounts_ o
  pure $ zip keys (zip amts ccys)

{#fun qlCommodityPricingErrors as qlCommodityPricingErrors_
  {withCommodity*`GenCommodity c'
  ,preArray-`[PricingErrorLevel]'&peekPricingErrorLevelArray*
  ,preArray-`[String]'&peekCStringArray*
  ,preArray-`[String]'&peekCStringArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

peekPricingErrorLevelArray :: Ptr CUInt -> Ptr (Ptr CInt) -> IO [PricingErrorLevel]
peekPricingErrorLevelArray = peekIntArray' toEnumC

-- |Every pricing diagnostic recorded so far (via upstream's own internal calls, or via
-- 'addPricingError') against this 'Commodity'\/'EnergyCommodity' leaf.
pricingErrors :: GenCommodity c -> IO PricingErrors
pricingErrors o = do
  (levels, errs, details) <- qlCommodityPricingErrors_ o
  pure $ zipWith3 PricingError levels errs details

{#fun qlEnergyCommodityQuantity as qlEnergyCommodityQuantity_
  {withEnergyCommodity*`GenEnergyCommodity e'
  ,alloca-`CommodityType'peekCommodityTypePtr*
  ,alloca-`UnitOfMeasure'peekUnitOfMeasurePtr*
  ,preErrorCheck-`String'errorCheck*-}->`Double'#}

-- |The commodity quantity of this 'EnergyCommodity' leaf -- either the plain quantity given at
-- construction ('EnergyFuture') or the sum across every 'PricingPeriod' ('EnergySwap' and its
-- leaves, a real computed sum -- see @energyswap.cpp@). One binding covers both, dispatched
-- virtually on the C++ side.
quantity :: GenEnergyCommodity e -> IO Quantity
quantity o = do
  (amt, ct, uom) <- qlEnergyCommodityQuantity_ o
  pure (ct, uom, amt)

-- |Construct an energy future: a single mark-to-market position against a 'CommodityIndex',
-- struck at a fixed 'CommodityUnitCost' trade price. @buySell@ is a signed multiplier (@1@ to buy,
-- @-1@ to sell), matching upstream's own @Integer buySell@ (not a @Bool@). @tradePrice@\/@index@
-- are not bound as getters -- both are plain, never-mutated echoes of these same constructor
-- arguments (per CLAUDE.md's trivial-getter rule); use 'quantity' for the one genuinely-shared
-- accessor.
energyFuture :: Int -- ^buySell
             -> Quantity
             -> CommodityUnitCost -- ^tradePrice
             -> CommodityIndex
             -> CommodityType
             -> SecondaryCosts
             -> IO EnergyFuture
energyFuture buySell (qCt, qUom, qAmt) (tpAmt, tpCcy, tpUom) index commodityType secCosts =
  qlEnergyFuture_ buySell qCt qUom qAmt tpAmt tpCcy tpUom index commodityType
    scKeys scIsUnitCost scAmts scCcys scUoms
  where (scKeys, scIsUnitCost, scAmts, scCcys, scUoms) = secondaryCostsFields secCosts

{#fun qlEnergyFuture as qlEnergyFuture_
  {`Int'
  ,withCommodityType*`CommodityType',withUnitOfMeasure*`UnitOfMeasure',`Double'
  ,`Double',withCurrency*`Currency',withUnitOfMeasure*`UnitOfMeasure'
  ,withCommodityIndex*`CommodityIndex'
  ,withCommodityType*`CommodityType'
  ,withStringArray*`[String]'&
  ,withBoolArray*`[Bool]'&
  ,withDoubleArray*`[Double]'&
  ,withCurrencyArray*`[Currency]'&
  ,withMaybeUnitOfMeasureArray*`[Maybe UnitOfMeasure]'&
  ,preErrorCheck-`String'errorCheck*-}->`EnergyFuture'peekEnergyFuture*#}

{#fun qlEnergySwapDailyPositions as qlEnergySwapDailyPositions_
  {withEnergySwap*`GenEnergySwap s'
  ,preArray-`[Day]'&peekDayArray*
  ,preArray-`[Double]'&peekDoubleArray*
  ,preArray-`[Double]'&peekDoubleArray*
  ,preArray-`[Double]'&peekDoubleArray*
  ,preArray-`[Double]'&peekDoubleArray*
  ,preArray-`[Bool]'&peekBoolArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |The per-day pricing breakdown computed during this 'EnergySwap' leaf's most recent
-- @performCalculations()@ -- populated only after pricing (call 'QuantLib.Instrument.npv' first).
dailyPositions :: GenEnergySwap s -> IO EnergyDailyPositions
dailyPositions s = do
  (dates, qtyAmts, payPrices, recvPrices, riskDeltas, unrealized) <- qlEnergySwapDailyPositions_ s
  pure $ zipWith6 EnergyDailyPosition dates qtyAmts payPrices recvPrices riskDeltas unrealized

zipWith6 :: (a -> b -> c -> d -> e -> f -> g) -> [a] -> [b] -> [c] -> [d] -> [e] -> [f] -> [g]
zipWith6 f (a:as) (b:bs) (c:cs) (d:ds) (e:es) (g:gs) = f a b c d e g : zipWith6 f as bs cs ds es gs
zipWith6 _ _ _ _ _ _ _ = []

-- |The realized\/unrealized payment cash flows computed during this 'EnergySwap' leaf's most
-- recent @performCalculations()@ -- populated only after pricing.
{#fun qlEnergySwapPaymentCashFlows as paymentCashFlows
  {withEnergySwap*`GenEnergySwap s'
  ,preArray-`[CommodityCashFlow]'&peekCommodityCashFlowArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Split a 'SecondaryCosts' list into the five parallel arrays every energy-instrument
-- constructor's C shim consumes it as (keys, is-a-'CommodityUnitCost'-flag, amounts, currencies,
-- units-of-measure -- 'Nothing' for a plain 'Money' entry).
secondaryCostsFields :: SecondaryCosts -> ([String], [Bool], [Double], [Currency], [Maybe UnitOfMeasure])
secondaryCostsFields entries =
  ( map fst entries
  , map (either (const True) (const False) . snd) entries
  , map (either (\(a,_,_) -> a) fst . snd) entries
  , map (either (\(_,c,_) -> c) snd . snd) entries
  , map (either (\(_,_,u) -> Just u) (const Nothing) . snd) entries
  )

-- |Split a 'PricingPeriods' list into the six parallel arrays every energy-swap constructor's C
-- shim consumes it as (start dates, end dates, payment dates, quantity commodity types, quantity
-- units of measure, quantity amounts).
pricingPeriodsFields :: PricingPeriods -> ([Day], [Day], [Day], [CommodityType], [UnitOfMeasure], [Double])
pricingPeriodsFields pps =
  ( map pricingPeriodStartDate pps
  , map pricingPeriodEndDate pps
  , map pricingPeriodPaymentDate pps
  , map (\(t,_,_) -> t) qtys
  , map (\(_,u,_) -> u) qtys
  , map (\(_,_,a) -> a) qtys
  )
  where qtys = map pricingPeriodQuantity pps

-- |Construct a vanilla energy swap: fixed 'CommodityUnitCost' price against a floating
-- 'CommodityIndex' quote, over one or more 'PricingPeriod's. @payer@ selects which leg (fixed or
-- floating) is paid. @payReceive@\/@fixedPrice@\/@fixedPriceUnitOfMeasure@\/@index@ are not bound
-- as getters -- all are plain, never-mutated echoes of this constructor's own arguments (per
-- CLAUDE.md's trivial-getter rule; @payReceive@ specifically is just @if payer then 1 else 0@,
-- reproducible with no C++ call at all).
energyVanillaSwap :: Bool -- ^payer
                  -> Calendar
                  -> (Double, Currency) -- ^fixedPrice
                  -> UnitOfMeasure -- ^fixedPriceUnitOfMeasure
                  -> CommodityIndex
                  -> Currency -- ^payCurrency
                  -> Currency -- ^receiveCurrency
                  -> PricingPeriods
                  -> CommodityType
                  -> SecondaryCosts
                  -> GenYieldTermStructure y1 -- ^payLegTermStructure
                  -> GenYieldTermStructure y2 -- ^receiveLegTermStructure
                  -> GenYieldTermStructure y3 -- ^discountTermStructure
                  -> IO EnergyVanillaSwap
energyVanillaSwap payer calendar (fpAmt, fpCcy) fpUom index payCcy receiveCcy pps commodityType secCosts
                  payLegTS receiveLegTS discountTS =
  qlEnergyVanillaSwap_ payer calendar fpAmt fpCcy fpUom index payCcy receiveCcy
    ppStarts ppEnds ppPays ppTypes ppUoms ppAmts
    commodityType scKeys scIsUnitCost scAmts scCcys scUoms
    payLegTS receiveLegTS discountTS
  where
    (ppStarts, ppEnds, ppPays, ppTypes, ppUoms, ppAmts) = pricingPeriodsFields pps
    (scKeys, scIsUnitCost, scAmts, scCcys, scUoms) = secondaryCostsFields secCosts

{#fun qlEnergyVanillaSwap as qlEnergyVanillaSwap_
  {fromBool`Bool'
  ,withCalendar*`Calendar'
  ,`Double',withCurrency*`Currency'
  ,withUnitOfMeasure*`UnitOfMeasure'
  ,withCommodityIndex*`CommodityIndex'
  ,withCurrency*`Currency'
  ,withCurrency*`Currency'
  ,withDayArray*`[Day]'&
  ,withDayArray*`[Day]'&
  ,withDayArray*`[Day]'&
  ,withCommodityTypeArray*`[CommodityType]'&
  ,withUnitOfMeasureArray*`[UnitOfMeasure]'&
  ,withDoubleArray*`[Double]'&
  ,withCommodityType*`CommodityType'
  ,withStringArray*`[String]'&
  ,withBoolArray*`[Bool]'&
  ,withDoubleArray*`[Double]'&
  ,withCurrencyArray*`[Currency]'&
  ,withMaybeUnitOfMeasureArray*`[Maybe UnitOfMeasure]'&
  ,withYieldTermStructure*`GenYieldTermStructure y1'
  ,withYieldTermStructure*`GenYieldTermStructure y2'
  ,withYieldTermStructure*`GenYieldTermStructure y3'
  ,preErrorCheck-`String'errorCheck*-}->`EnergyVanillaSwap'peekEnergyVanillaSwap*#}

-- |Construct an energy basis swap: two floating 'CommodityIndex' legs (pay\/receive), one of them
-- offset by a fixed 'CommodityUnitCost' basis, over one or more 'PricingPeriod's. @spreadToPayLeg@
-- selects which leg the basis is added to. @payIndex@\/@receiveIndex@\/@basis@ are not bound as
-- getters -- all are plain, never-mutated echoes of this constructor's own arguments.
energyBasisSwap :: Calendar
                -> CommodityIndex -- ^spreadIndex
                -> CommodityIndex -- ^payIndex
                -> CommodityIndex -- ^receiveIndex
                -> Bool -- ^spreadToPayLeg
                -> Currency -- ^payCurrency
                -> Currency -- ^receiveCurrency
                -> PricingPeriods
                -> CommodityUnitCost -- ^basis
                -> CommodityType
                -> SecondaryCosts
                -> GenYieldTermStructure y1 -- ^payLegTermStructure
                -> GenYieldTermStructure y2 -- ^receiveLegTermStructure
                -> GenYieldTermStructure y3 -- ^discountTermStructure
                -> IO EnergyBasisSwap
energyBasisSwap calendar spreadIndex payIndex receiveIndex spreadToPayLeg payCcy receiveCcy pps
                (basisAmt, basisCcy, basisUom) commodityType secCosts payLegTS receiveLegTS discountTS =
  qlEnergyBasisSwap_ calendar spreadIndex payIndex receiveIndex spreadToPayLeg payCcy receiveCcy
    ppStarts ppEnds ppPays ppTypes ppUoms ppAmts
    basisAmt basisCcy basisUom
    commodityType scKeys scIsUnitCost scAmts scCcys scUoms
    payLegTS receiveLegTS discountTS
  where
    (ppStarts, ppEnds, ppPays, ppTypes, ppUoms, ppAmts) = pricingPeriodsFields pps
    (scKeys, scIsUnitCost, scAmts, scCcys, scUoms) = secondaryCostsFields secCosts

{#fun qlEnergyBasisSwap as qlEnergyBasisSwap_
  {withCalendar*`Calendar'
  ,withCommodityIndex*`CommodityIndex'
  ,withCommodityIndex*`CommodityIndex'
  ,withCommodityIndex*`CommodityIndex'
  ,fromBool`Bool'
  ,withCurrency*`Currency'
  ,withCurrency*`Currency'
  ,withDayArray*`[Day]'&
  ,withDayArray*`[Day]'&
  ,withDayArray*`[Day]'&
  ,withCommodityTypeArray*`[CommodityType]'&
  ,withUnitOfMeasureArray*`[UnitOfMeasure]'&
  ,withDoubleArray*`[Double]'&
  ,`Double',withCurrency*`Currency',withUnitOfMeasure*`UnitOfMeasure'
  ,withCommodityType*`CommodityType'
  ,withStringArray*`[String]'&
  ,withBoolArray*`[Bool]'&
  ,withDoubleArray*`[Double]'&
  ,withCurrencyArray*`[Currency]'&
  ,withMaybeUnitOfMeasureArray*`[Maybe UnitOfMeasure]'&
  ,withYieldTermStructure*`GenYieldTermStructure y1'
  ,withYieldTermStructure*`GenYieldTermStructure y2'
  ,withYieldTermStructure*`GenYieldTermStructure y3'
  ,preErrorCheck-`String'errorCheck*-}->`EnergyBasisSwap'peekEnergyBasisSwap*#}

{#fun qlCreatePricingPeriods as qlCreatePricingPeriods_
  {withDay*`Day'
  ,withDay*`Day'
  ,withCommodityType*`CommodityType',withUnitOfMeasure*`UnitOfMeasure',`Double'
  ,fromEnumC`DeliverySchedule'
  ,fromEnumC`QuantityPeriodicity'
  ,withPaymentTerm*`PaymentTerm'
  ,preArray-`[Day]'&peekDayArray*
  ,preArray-`[Day]'&peekDayArray*
  ,preArray-`[Day]'&peekDayArray*
  ,preArray-`[CommodityType]'&peekCommodityTypeArray*
  ,preArray-`[UnitOfMeasure]'&peekUnitOfMeasureArray*
  ,preArray-`[Double]'&peekDoubleArray*
  ,preErrorCheck-`String'errorCheck*-}->`()'#}

-- |Split @[startDate, endDate)@ into 'PricingPeriod's of the given quantity, per a
-- 'DeliverySchedule'\/'QuantityPeriodicity'\/'PaymentTerm' combination --
-- @CommodityPricingHelper::createPricingPeriods@. Upstream only actually implements two
-- combinations ('Monthly' with 'PerMonth', 'Daily' with 'PerDay'); every other 'DeliverySchedule'
-- silently returns @[]@ (no periods, no error -- checked directly against
-- @commoditypricinghelpers.cpp@, not assumed from the header).
createPricingPeriods :: Day -> Day -> Quantity -> DeliverySchedule -> QuantityPeriodicity -> PaymentTerm -> IO PricingPeriods
createPricingPeriods startDate endDate (ct, uom, amt) deliverySchedule qtyPeriodicity paymentTerm = do
  (starts, ends, pays, types, uoms, amts) <-
    qlCreatePricingPeriods_ startDate endDate ct uom amt deliverySchedule qtyPeriodicity paymentTerm
  pure $ zipWith6 (\s e p t u a -> pricingPeriod s e p (t, u, a)) starts ends pays types uoms amts

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
