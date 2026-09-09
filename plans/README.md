# Subplan status

- **BlackVolTermStructure blackVol/blackVariance/blackForwardVol/blackForwardVariance**: done
  (via `TermPoint`/`TermInterval`, exported as `blackVol`/`blackVolVariance`/`blackForwardVol`/
  `blackForwardVariance` in `QuantLib.TermStructure.Volatility`). Along the way, generalized
  `minStrike`/`maxStrike` into a `HasStrikeBounds` capability class (mirroring `HasVolatility`/
  `HasBlackVariance`) with two instances: the existing `CallableBondVolatilityStructure` shim
  (unchanged) and one new shared shim (`qlVolatilityTermStructureMinStrike`/`MaxStrike`) covering
  every real `VolatilityTermStructure` subtype (`BlackVolTermStructure`, `OptionletVolatilityStructure`,
  `SwaptionVolatilityStructure`, `CapFloorTermVolatilityStructure`, `BlackAtmVolCurve`,
  `SabrVolSurface`, `LocalVolTermStructure`) via the existing `GenVolatilityTermStructure`
  multi-hop upcast machinery — no per-leaf shim needed. `optionDateFromTenor` was *not* joined to
  this: it's non-virtual on `VolatilityTermStructure`, and `InterestRateVolSurface`/`SabrVolSurface`
  hide it with a genuinely different, index-fixing-based computation — a generic call would
  silently return wrong dates for that family, so the narrow `sabrVolSurfaceOptionDateFromTenor`
  binding stays separate.

  One follow-up surfaced but not built: `EquityFXVolSurface::atmForwardVol`/`atmForwardVariance`
  (`ql/experimental/volatility/equityfxvolsurface.hpp:70-82`) are structurally identical
  `TermInterval` consumers, but `EquityFXVolSurface` is abstract with no concrete subclass shipped
  in the installed QuantLib — its `BlackVolSurface` parent has a pure-virtual `smileSectionImpl`.
  Blocked on a concrete subclass becoming available (upstream QuantLib update, or a future
  hasquant-provided concrete smile-section implementation).
