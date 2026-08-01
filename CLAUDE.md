# hasquant

Haskell bindings to QuantLib via c2hs, with a C++ shim layer in `cbits/`.

## Development

- To test C++-only changes quickly (without a full Haskell rebuild), run `make`.
- To build and run the full test suite, use `stack build --test --no-haddock`.
