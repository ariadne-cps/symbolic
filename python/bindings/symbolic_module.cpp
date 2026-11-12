/***************************************************************************
 *            python/bindings/symbolic_module.cpp
 *
 *  Copyright  2026  Luca Geretti
 *
 ****************************************************************************/

/*
 *  This file is part of Ariadne Symbolic.
 *
 *  Ariadne Symbolic is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Ariadne Symbolic is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Ariadne Symbolic. If not, see <https://www.gnu.org/licenses/>.
 */

/** @file python/bindings/symbolic_module.cpp
 *  @brief Register the Symbolic Python extension module.
 */

#include "pybind11.hpp"
void symbolic_submodule(pybind11::module& module);
void symbolic_module(pybind11::module& module) { symbolic_submodule(module); }
