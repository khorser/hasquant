# Memory-safety investigation, September 2026

Baseline: `30b2d580`; historical crash hardening: `96d40db2` and its layout/diagnostic follow-ups.
The original Windows access violation remains **unattributed**. No matching historical binary,
symbol map, or minidump was available. Passing a different build does not symbolize that binary.

## Assessment of 96d40db

The single-record callback ABI and header-derived field offsets are reasonable hardening.
The inspected historical C and Haskell callback signatures agree, however, and both old
and new forms pass the isolated ABI probe on macOS ARM64. A Windows run is still needed
to test the original ABI hypothesis. Neither the unwinder warning nor the unsymbolized
stack establishes an ABI mismatch. Keep the hardening, but do not label the original
access violation fixed on this evidence alone.

## Established findings

| Finding | Status | Connection to historical crash |
| --- | --- | --- |
| MultiCurve pricing indexes used non-owning internal handles after all external owners became unreachable | Fixed in fixtures and the native ownership boundary; original member handles retain the group, expired internal handles become empty | Reproduced a native SIGSEGV on macOS with `-A64k`; no established connection to the historical Windows failure |
| FDM step conditions can return borrowed overlapping storage to `copyArray` | Fixed with `moveArray`; the identity result has a smoke probe, and other lengths throw `CallbackResultLength` (Hspec) | The example's `zipWith` returns fresh storage; no demonstrated trigger there |
| Allocation analyzer could lose an intermediate over-free after address reuse balanced the ledger | Fixed; chronological unmatched-release events retain line numbers; malformed/empty traces fail | Diagnostic blind spot, not a runtime cause |
| Raw unwinder PC omitted by symbolizer | Fixed when consistent frames establish the runtime base and bound the address inside the image | Supplied base is `0x7ff7636a0000`; unwinder PC RVA is `0x3fab94` |
| Identity hierarchy conversions installed independent finalizers on the same wrapper | Already fixed by `ab00c678`; extended its ownership probe with nested callback quotes and updates | A credible intermittent corruption mechanism, but the triggering conversion/test order is unknown |
| Factory allocation/adoption and result/temporary cleanup windows | Already addressed by `e03772d8`, `de602ee0`, and `30b2d580`; existing probes retained | These are distinct mechanisms, not evidence that the ABI change cured the crash |
| Haskell exceptions escape callback entry points | Fixed with callback containment and structured per-call errors; exact Haskell exception types survive native unwinding | No exception trigger established in the original fixture |
| Continuation-scoped callbacks can outlive their function pointers if an object or native dependent escapes | Fixed with managed Haskell and native shared owners; direct, ADT, and dependent escape probes pass | Inspected example uses remain within their brackets; no escape established |

[`copyArray`](https://downloads.haskell.org/ghc/9.6-latest/docs/libraries/base-4.18.3.0/Foreign-Marshal-Array.html) forbids overlap; returning `id` is valid for the public callback signature, and any other
length throws. The regression probe also exercises all record coordinates, including direction 1,
unequal nonzero times and a nonzero splitting scalar. The old pricing fixture ignored several.

## Audit coverage and limits

The review follows shared mechanisms rather than claiming exhaustive verification of every
pricing formula. It covers `GenForeignPtr` ownership/transfer and nested upcasts, standalone
handles, callback wrappers, vector borrowing/adoption, array/string/struct conversion, output
staging, and representative multi-output and factory producers. Searches covered all binding
modules and `cbits` for raw memory operations, casts, callback signatures, and pointer returns.

- Current identity conversions reuse the original `ForeignPtr`; native upcasts allocate distinct
  wrappers sharing the payload. The two must never acquire ownership by the same rule.
- Array result slots are initialized before upstream work, staged by RAII, and cleared when
  Haskell adopts them. `peekPtrArray` clears each adopted element separately. Existing probes
  inject conversion failure and cancellation after production, including multiple outputs.
- `borrowRealVector` carries no native owner. FDM forces storable output before returning; the
  optimizer returns a scalar. Neither permits a borrowed view to be retained after the callback.
- Callback families inspected: optimizer, four FDM operator/condition forms, inner-value and
  grid-mapping calculators, scalar/striked/basket payoffs, unary/binary/array quotes, extended OU
  processes, and composite yield curves. All use the shared managed callback/error machinery. The generated FDM imports
  are `safe`; a scan of all generated binding modules found zero unsafe callable imports
  (excluding finalizer addresses); address-only finalizer imports are not evidence of an unsafe callback call.
- Native allocation/deallocation searches found centralized string/array frees and Aux deletes
  delegated through `delWith`. Native internal shared objects are not comprehensively covered
  by wrapper tracing (for example leg cashflows, local smile sections, and RNG internals).
  Balanced wrapper counts are therefore not proof of all payloads' lifetimes or absence of UAF.
- Settings restoration is bracketed; its GC helper is best-effort. Native `DerivedQuote::update`
  invalidates and notifies; its user function runs from `value`. Callback re-entry can allocate
  and run GC before native code returns, even without `-threaded`. An observer-iteration hazard
  would additionally require a reachable notification/recalculation path; none was reproduced.
- QuantLib's non-thread-safe observer pattern remains the configured baseline. This task does
  not claim support for concurrent graph mutation or switch the runtime to threaded mode.
- Count narrowing to C `unsigned`, allocation-failure-only shims without error channels, and
  deliberate retention of borrowed vector views remain audit limitations.

## Test-order findings

The first full-suite randomized run (`--randomize --seed 1`) had three assertion failures,
without an access violation. Settings specs left an evaluation date behind; historical-rates
analysis depended on an inherited date after its sample; commodity-index specs shared a named
fixing history. Settings specs now use `around_ keepingSettingsGc`, historical analysis explicitly
sets its date after the final sample inside its existing bracket, and commodity tests use distinct
names and bracket fixing cleanup. Seed 1 passes with these fixes. This demonstrates global-state
sensitivity but does not identify the historical memory fault.

## Reproduced MultiCurve use-after-free

The first small-nursery full-suite run (`--randomize --seed 1 +RTS -A64k -RTS`)
terminated with SIGSEGV. The single test matching `3m/6m ibor-ibor basis swaps` also
crashed under `-A64k`:

```sh
PATH_TO_HASQUANT_TEST --match "3m/6m ibor-ibor basis swaps" +RTS -A64k -RTS
```

The macOS crash report and LLDB both identify
`BlackIborCouponPricer::initialize`, dereferencing the forwarding curve's invalid vtable
while valuing a swap. Default-nursery seeds 1–10 and 200 isolated FDM processes passed
before this failure; successful normal runs had concealed a lifetime bug.

QuantLib's `MultiCurve::addCurve` links internal handles with `null_deleter`, removing
ownership to break cycles. External handles use aliasing shared pointers that retain the
whole MultiCurve. The fixture returned indexes built from internal handles, while the
basis-swap test discarded both external handles. Once GC collected the MultiCurve owner,
those live indexes pointed into freed curves. The same fixture mistake exists in the
parent of `96d40db`, so it predates the historical ABI hardening. This establishes a
historical lifetime defect, but not that it produced the reported FDM crash.
C++'s upstream fixture keeps its local
MultiCurve alive until scope exit; Haskell does not preserve unused locals that way.

Both MultiCurve fixture builders now construct pricing indexes from external handles.
The native managed wrapper also promotes the original member handles' shared links to retain
the group, including indexes constructed before insertion. On group destruction it clears the
non-owning internal links before destroying curves. An escaped internal index then reports a
null term structure rather than dereferencing freed memory; external pricing should still use
owning handles because internal handles suppress notifications. Duplicate member insertion is
rejected before retaining an alias that would make the group own itself.

`CheckMultiCurve` returns only a dependent swap, collects garbage, then first values it.
External and original-member indexes price successfully under `-A64k`; an internal index raises
the expected null-term-structure exception. A temporary control using the original implementation
and internal indexes previously crashed with exit 139.

## Reproduction and diagnostics

Run the normal build first. The test executable accepts RTS options, without enabling threading:

```sh
python3 -m unittest discover -s tools -p test_memory_diagnostics.py
.claude/skills/run-hasquant/driver.sh test/smoke/CheckFdmCallbacks.hs
.claude/skills/run-hasquant/driver.sh test/smoke/CheckCallbackFailure.hs
.claude/skills/run-hasquant/driver.sh test/smoke/CheckCallbackOwnership.hs
.claude/skills/run-hasquant/driver.sh test/smoke/CheckHierarchyOwnership.hs
.claude/skills/run-hasquant/driver.sh test/smoke/CheckMultiCurve.hs
.claude/skills/run-hasquant/driver.sh test/smoke/CheckResultMarshalling.hs
.claude/skills/run-hasquant/driver.sh test/smoke/CheckTemporaryOwnership.hs
```

The ABI probe is independent of QuantLib and hasquant, using the historical signatures alongside
the current shared header. It invokes every form 1,000 times with guards around output storage:

```sh
c++ -std=c++17 -Icbits -c test/smoke/FdmCallbackFixture.cpp -o /tmp/fdm-callback.o
ghc -Wall -package-env - -hide-all-packages -package base -i test/smoke/CheckCallbackAbi.hs /tmp/fdm-callback.o -outputdir /tmp/callback-build -o /tmp/callback-abi
/tmp/callback-abi
```

On Windows use GHC's bundled `clang++`, `.exe` output names, and the Windows workflow's link
options for library-linked probes. Every Windows CI job runs the ABI, public FDM, callback exception/ownership, MultiCurve ownership, and Python
regressions. The manual `memory_stress` input additionally runs the stress matrix:

```sh
python3 tools/stress-memory.py PATH_TO_HASQUANT_TEST --output NEW_LOG_DIRECTORY --compiler 'GHC VERSION'
```

This runs 100 isolated FDM processes and ten full-suite seeds under both the default nursery
and `-A64k`, stopping at the first failure. Logs contain commands, seeds, exit status, revision,
working-tree status and binary SHA-256. `HASQUANT_TRACE_FDM=1` emits flushed stage markers inside
the example, distinguishing rollbacks from native engines and other calculators. It is off by
default. Windows uploads retain these logs with the matching binaries/maps/DLLs and crash dumps.

For tracing use a fresh build directory; toggling the flag alone can leave uninstrumented objects:

```sh
stack --work-dir .stack-work/memory-audit build --test --no-run-tests --no-haddock --flag hasquant:trackAllocations
# Verify an object contains tracing strings before running the resulting test executable.
QLTRACK_ALLOCATIONS=/tmp/hasquant-memory.trace PATH_TO_TRACED_TEST
python3 tools/alloc-summary.py /tmp/hasquant-memory.trace
```

Investigate unbalanced classes rather than suppressing them: the suite may still hold owners at
exit, while a targeted ownership fixture can delimit lifetime precisely. Do not treat traces from
an abruptly terminated process as a completed lifetime ledger.

## Callback ownership and exception transport

`QuantLib.Internal.Callback` owns the Haskell function pointer through a managed native shared
owner. Callback-bearing ADTs retain it before materialization; native consumers copy it and
release it only after their last dependent dies. The last owner calls the RTS C cleanup function,
never Haskell code, so native finalization does not re-enter the runtime. GHC permits these
cleanup functions from finalizers after releasing its stable-pointer-table lock.

Callbacks catch `SomeException`, including forcing/copying their result, and return a stable
pointer as a failure status. Native adapters throw a C++ sentinel only after Haskell returns.
`QlCallScope` records the first failure in the actual C entry's `QlError **` slot, retaining it
even if an upstream algorithm catches the sentinel. Nested C entries save/restore the current
scope. Haskell result adoption and cleanup run under masking; the enclosing call then rethrows
the original exception. This replaces the C shim's string error slots and callback signatures:
**the C ABI changes and downstream native callers must rebuild**. Public continuation APIs remain.

`CheckCallbackFailure` verifies original exception type/payload through escaped quotes and every
FDM callback position. `CheckCallbackOwnership` checks escaped native quotes/dependents, payoff
ADTs, inner values, and grid mappings after GC. `CheckNativeCallbacks.cpp` additionally checks
last-owner destruction, nested error slots, upstream catches, and unconsumed exception cleanup.

Both bound FD vanilla engine families validate `StrikedTypePayoff` before calling upstream;
QuantLib 1.43 otherwise dereferences a failed cast. A CI Hspec regression verifies rejection for
Black-Scholes and Heston. This does not extend which payoff types those engines can price.

## Validation status

The first audit pass (before the broader callback redesign) passed 200 isolated FDM processes
and 20 full-suite randomized runs across default and 64 KB nurseries, allocation tracing,
factory fault injection, and GHC 8.10/9.10 builds. Those results are historical controls, not
validation of later changes.

The callback redesign passed 633-example suites on macOS/GHC 9.10.3 and Linux/GHC 8.10.6.
The final macOS clean build passed 634 examples, including the FD payoff rejection regression.
A randomized full-suite run with tracing and a 64 KB nursery also passed all 634 examples:
1,532,787 tracked acquisitions across 657 classes balanced, with no malformed trace records.
All six callback/ownership smoke probes passed under tracing with balanced ledgers; the native
callback, ABI, result/temporary ownership, and six factory-allocation-failure checks passed.
The final Linux/GHC 8.10.6 build passed all 634 examples. The final callback/MultiCurve stress
matrix passed 200 isolated FDM processes and 20 randomized full-suite runs, split evenly across
default and 64 KB nurseries. Its last seed was interrupted without an exit result and rerun
successfully against the identical binary (SHA-256 verified). A final duplicate-member guard
has a separate MultiCurve regression. Both flagged executables build; real source warnings were
fixed and `hlint .` passes. GCC tracing checks and the 15 diagnostic-tool tests pass.

Windows execution remains outstanding; the CI probes and artifact collection are prepared,
but no Windows workflow has been dispatched from this session.
