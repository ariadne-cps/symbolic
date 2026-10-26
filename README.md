# Ariadne Symbolic

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Unix Status](https://github.com/ariadne-cps/symbolic/actions/workflows/unix.yml/badge.svg)](https://github.com/ariadne-cps/symbolic/actions/workflows/unix.yml)
[![Windows Status](https://github.com/ariadne-cps/symbolic/actions/workflows/win.yml/badge.svg)](https://github.com/ariadne-cps/symbolic/actions/workflows/win.yml)
[![Sanitizers Status](https://github.com/ariadne-cps/symbolic/actions/workflows/sanitizers.yml/badge.svg)](https://github.com/ariadne-cps/symbolic/actions/workflows/sanitizers.yml)
[![Coverage Status](https://github.com/ariadne-cps/symbolic/actions/workflows/coverage.yml/badge.svg)](https://github.com/ariadne-cps/symbolic/actions/workflows/coverage.yml)
[![codecov](https://codecov.io/gh/ariadne-cps/symbolic/branch/main/graph/badge.svg)](https://codecov.io/gh/ariadne-cps/symbolic)

Ariadne Symbolic is the standalone C++20 symbolic-expression layer used by Ariadne. It provides named variables and spaces, expressions, valuations, assignments, symbolic sets and conversions from symbolic descriptions to callable and validated computational objects on top of Ariadne Kernel.

## Layout

Public headers live under `include/symbolic`, implementations under `src`, C++ tests under `tests`, Python bindings and tests under `python`, and standalone examples under `tutorials`.

The umbrella header is `include/ariadne-symbolic.hpp`.

## Dependencies

Symbolic depends directly on:

- [ariadne-cps/kernel](https://github.com/ariadne-cps/kernel), included as a Git submodule.
- [ariadne-cps/configuration](https://github.com/ariadne-cps/configuration), used for shared build configuration.

Kernel supplies the lower Ariadne layers and their external dependencies.

## Build

```bash
git clone --recurse-submodules https://github.com/ariadne-cps/symbolic.git
cd symbolic
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel --target everything
ctest --test-dir build --output-on-failure
```

## Python bindings

When a compatible Python development environment is available, the standalone build produces `pyariadne` from the Kernel bindings plus the Symbolic bindings.

## Contribution guidelines

If you would like to contribute to Ariadne Symbolic, please contact the developer:

- Luca Geretti <luca.geretti@univr.it>

## License

Ariadne Symbolic is released under the GNU General Public License v3.0.
