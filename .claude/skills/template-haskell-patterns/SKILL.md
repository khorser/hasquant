---
name: template-haskell-patterns
description: Maintain or extend the Template Haskell generators in QuantLib.Internal.Syntax, including deriveCrossEnum, deriveIborConstructor, deriveOptionsRecord, generated Read instances, or splice placement in c2hs .chs modules.
---

# Template Haskell patterns

Use this skill for changes to `QuantLib/Internal/Syntax.hs` or its splice sites. Generated declarations are ABI-adjacent: values may still work when strictness, constructor order, or dispatch ordinals are wrong.

## Preserve the established representation

- Build output with raw `Dec`, `Con`, `Exp`, and `Pat` constructors. Keep the existing compatibility helpers only where `template-haskell` changed constructor arity within the supported GHC range: `conPat` for `ConP` and `plainTV` for `TyVarBndr`. Check any newly used TH constructor against both GHC 8.10 and the current compiler.
- Use `mkName` for generated top-level names that splice-site code refers to. Use `newName` for generated local binders.
- Give a generator a named specification record when it has multiple same-typed arguments; positional `String` and `Name` arguments can transpose while still compiling.
- Preserve strictness deliberately: merged enum ADTs use strict fields, while options-record fields are lazy.

## Enum ordinals and offsets

Keep each c2hs/C enum independently zero-based. When a generated Haskell ADT merges sibling enums into one flat C dispatch space, compute group offsets in TH from the lengths of the reified, sentinel-filtered constructor lists. Do not chain one C enum's first value to a constant from another enum and do not hard-code group sizes.

`deriveIborConstructor` is the reference: `dailyOffset = length normalCtors` and `onOffset = dailyOffset + length dailyCtors`.

## Splices in `.chs` files

A top-level splice must precede every `{#fun#}` hook in the file. c2hs places generated foreign-import stubs at the physical end of its output; a mid-file splice creates declaration groups in which earlier wrappers cannot see those stubs. If the splice cannot be placed before all hooks, generate the safe declaration at the type site and hand-write the part that depends on the hook, or move it to a cycle-free module.

## Verification

For any `derive*` refactor, compare normalized `-ddump-splices` output before and after. Strip source positions and normalize TH unique suffixes, then require byte-identical output unless the generated API is intentionally changing. Value tests do not detect field strictness or declaration-shape drift.

GHC may skip splice dumping when it considers modules up to date, even with `--force-dirty`. Remove the affected generated modules' `.hi` and `.o` files under `.stack-work/dist/*/build/`, then rebuild with `--ghc-options=-ddump-splices`.

Run the normal local build and tests, followed by the GHC 8.10 gate from `run-hasquant`. The older gate is required for `template-haskell` compatibility.
