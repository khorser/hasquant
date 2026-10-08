# QuantLib 1.44 binding audit

Source: upstream tag `v1.44-rc` (`2897626`), compared with `v1.43`.
`ql-methods-1.44.txt` is extracted from the complete RC header tree with
`dump_signatures.py`; `reconcile_signatures.py` carries the curated 1.43 statuses.
The extractor filters deprecated and duplicate inherited methods; out-of-line template
definitions can also appear in the inventory and require review against the header.
The status audit checks the actual declarations in `cbits/*.h`.

## New neighboring bindings

- InterestRate: first and second discount-factor derivatives with respect to the rate.
- Gaussian1dModel: compounded overnight coupon rate.
- ImpliedTermStructure: settlement-days/calendar construction.
- OvernightOvernightBasisSwapRateHelper and OvernightIndexedFundingRateHelper:
  constructors returning the existing RateHelper type, with fixing-dependency extraction.
- Malaysia and Philippines calendars, with stable enum ordinals on both supported versions.
- StubIndexSelection and standalone StubIborCoupon construction returning IborCoupon.
  Composite stub fixing dependencies resolve to their component index histories.
- RoughHestonModel and AnalyticRoughHestonEngine: calibrated parameters, all three Riccati
  approximations, all twelve Fourier integration configurations, direct date/time pricing,
  characteristic/log-characteristic functions, Riccati solutions and evaluation counts.
- MtMCrossCurrencyBasisSwap and its discounting engine: default and full options constructors,
  fair spreads, reset rates/notionals, and currency-denominated leg results shared with
  constant-notional swaps through capability classes.
- FX reset observations and conventions, discounting FX reset pricers, FX reset coupons and
  netted notional exchanges, including per-flow and whole-leg pricer assignment. Coupon.nominal
  is now bound because FX reset coupons calculate their notional from the observed/projected FX rate.
- PricingEngine is now a GenPricingEngine family. Instrument and calibration-helper wiring
  accept GenPricingEngine pe; existing factories still return the PricingEngine alias.

## Added arguments

| Upstream API | Added configuration |
| --- | --- |
| OvernightIndexedSwap | Rounding precision |
| NonstandardSwap | Payment lag and calendar |
| IborLeg | Stub index selection |
| IborIborBasisSwapRateHelper | Indexed coupons, schedule rule, payment lag, two stub selections |
| OvernightIborBasisSwapRateHelper | Curve to bootstrap, payment lag/frequency, indexed coupons, rule, averaging, telescopic dates, basis leg, stub selection |
| Constant-notional XCCY basis swap/helper | Indexed coupons, lag on notional exchanges, two stub selections |
| MTM XCCY basis helper | FX reset days/calendar, indexed coupons, two stub selections |
| Constant-notional XCCY fixed/floating swap/helper | Indexed coupons and stub selection; helper floating payment frequency |
| OISRateHelper | Fixed-leg day counter |
| SpreadCdsHelper / UpfrontCdsHelper | Trade date |
| OptionletStripper1 (including the fused Stripper2 constructor) | Payment lag |
| SABR, no-arbitrage SABR and ZABR cubes | Single-pass calibration |
| GlobalBootstrap, including spread curves | Whole-curve initial guess; full additional-helper form also exposes instrument weights |

Existing small tails are widened; wide constructor options records gain fields. Initial guesses
receive borrowed times and previous data, return one trait-specific value per non-reference
pillar, and retain native shared ownership for lazy calculation and recalculation.
On 1.43, new arguments accept only their upstream 1.44 defaults, meaning whatever the linked
QuantLib does; any other value, including a stub selection, reports `UnsupportedQuantLibVersion`
for the public call. The bootstrap initial guess is the exception: it is skipped without execution.
New calls report `UnsupportedQuantLibVersion` on 1.43. Direct mixed-compounding restrictions and non-finite
fair-rate/spread guards apply to both supported versions.

## Reviewed scope

The new overnight helpers' instrument accessors serve the existing fixing-dependency visitor. They do not
require new public helper leaf types. Stub coupons return the existing IborCoupon type;
WeightedIndex remains internal to native stub selection and the fixing-dependency visitor.
FX reset observations/conventions and Fourier integration configuration are structural values,
materialized by the native consumers; they have no separate held-object interface.

Rough Heston belongs directly to CalibratedModel. Its engine retains a concrete native interface
under GenPricingEngine. MTM swaps belong to GenSwap; the new upstream CrossCurrencySwap base
is represented by shared result capabilities so the 1.43 hierarchy remains usable. All public
1.44 cash-flow additions are covered; the older cash-flow backlog is unchanged.

Constructor-echo getters remain excluded per producer. The detector was also run on
fxresetcashflows.hpp, mtmcrosscurrencybasisswap.hpp, discountingmtmcrosscurrencybasisswapengine.hpp
and stubiborcoupon.hpp. It confirmed the new field-echo exclusions in the inventories. MTM
pay/receive aliases and reset leg/index selectors were reviewed individually: they select
construction inputs or duplicate Swap.leg with the construction-time reset flag. FX reset
observation aliases and attached-pricer getters likewise echo inputs/wiring. Engine update/calculate
are reached through normal observer wiring and Instrument.npv. FourierIntegration's callback
calculation primitives and internal inspectors are outside the construction/pricing surface.

`detect_trivial_getters.py` verified nine new exclusions against the RC declarations and
implementations: `StubIndexSelection::convention/indices`, `StubIborCoupon::stubIndexSelection`,
the MTM basis helper's `fxResetFixingDays/fxResetFixingCalendar`, the constant-notional basis
swap's `payStubIndexSelection/recStubIndexSelection`, the fixed/floating swap's
`floatStubIndexSelection`, and `OvernightIndexedSwap::roundingPrecision`.

Signature reconciliation treats `ext::optional` and `std::optional` as equivalent and
preserves parameter prefixes when choosing among widened overloads. Reviewed curve-handle
echo getters retain their exclusions when upstream changes their return type to a const reference.

## Verification

Pricing regressions use the RC Rough Heston reference prices and Hurst calibration, and the MTM
helper-curve repricing fixture across all collateral/basis/reset flag combinations. FX reset tests
check overnight accrual scaling, netted exchanges, historical direct/inverse/triangulated rates,
spot settlement, and component fixing dependencies. Both 1.43 version errors and 1.44 calculations
run in the normal Hspec suite; ownership and integration-factory dispatch have separate smoke probes.

The combined overnight/stub options fixture checks payment dates, component dependencies and
currency-leg NPV against independently discounted live cash flows. With compoundSpread enabled,
the RC's BPS-based fair spread does not exactly reprice that fixture; a raw C++ reproduction
matches the binding. Ordinary non-compounded fair-spread repricing remains covered separately.
