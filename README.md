# Ariadne Symbolic

[![macOS Status](https://github.com/ariadne-cps/symbolic/actions/workflows/macos.yml/badge.svg)](https://github.com/ariadne-cps/symbolic/actions/workflows/macos.yml)
[![Ubuntu Status](https://github.com/ariadne-cps/symbolic/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/ariadne-cps/symbolic/actions/workflows/ubuntu.yml)
[![Windows Status](https://github.com/ariadne-cps/symbolic/actions/workflows/win.yml/badge.svg)](https://github.com/ariadne-cps/symbolic/actions/workflows/win.yml)
[![Sanitizers Status](https://github.com/ariadne-cps/symbolic/actions/workflows/sanitizers.yml/badge.svg)](https://github.com/ariadne-cps/symbolic/actions/workflows/sanitizers.yml)
[![Coverage Status](https://github.com/ariadne-cps/symbolic/actions/workflows/coverage.yml/badge.svg)](https://github.com/ariadne-cps/symbolic/actions/workflows/coverage.yml)
[![codecov](https://codecov.io/gh/ariadne-cps/symbolic/branch/main/graph/badge.svg)](https://codecov.io/gh/ariadne-cps/symbolic)

Ariadne Symbolic is the standalone C++20 symbolic-expression layer used by Ariadne. It provides named variables and spaces, expressions, valuations, assignments, conversions from symbolic descriptions to callable functions on top of Ariadne Function.

## Layout

Public headers live under `include/symbolic`, implementations under `src`, C++ tests under `tests`, Python bindings and tests under `python`, and standalone examples under `tutorials`.

The umbrella header is `include/ariadne-symbolic.hpp`.

## Dependencies

Symbolic depends directly on:

- [ariadne-cps/function](https://github.com/ariadne-cps/function), included as a Git submodule.
- [ariadne-cps/configuration](https://github.com/ariadne-cps/configuration), used for shared build configuration.

Function supplies the lower Ariadne layers and their external dependencies.

## Build

```bash
git clone --recurse-submodules https://github.com/ariadne-cps/symbolic.git
cd symbolic
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel --target everything
ctest --test-dir build --output-on-failure
```

## Python bindings

When a compatible Python development environment is available, the standalone build produces `pyariadne` from the Function bindings plus the Symbolic bindings.

## Contribution guidelines

If you would like to contribute to Ariadne Symbolic, please contact the developer:

- Luca Geretti <luca.geretti@univr.it>

## License

Ariadne Symbolic is released under the GNU General Public License v3.0.
