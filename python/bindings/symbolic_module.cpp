#include "pybind11.hpp"
void symbolic_submodule(pybind11::module& module);
void symbolic_module(pybind11::module& module) { symbolic_submodule(module); }
