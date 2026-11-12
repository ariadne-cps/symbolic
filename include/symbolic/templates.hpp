/***************************************************************************
 *            symbolic/templates.hpp
 *
 *  Copyright  2013-20  Pieter Collins
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

/** @file symbolic/templates.hpp
 *  @brief Symbolic operation nodes and expression-template adapters.
 */

#ifndef ARIADNE_EXPRESSION_TEMPLATES_HPP
#define ARIADNE_EXPRESSION_TEMPLATES_HPP

#include "function/operation_node.hpp"
#include "numeric/integer.hpp"
#include "numeric/sequence.hpp"

namespace Ariadne {

template<class T>
class Expression;

/** @brief Retrieve a component of a vector expression. */
struct Get {
    static constexpr OperatorCode code() { return OperatorCode::GET; }
    static OperatorKind kind() { return OperatorKind::COORDINATE; }
    template<class V, class I>
    decltype(auto) operator()(const V& v, I i) { return v.operator[](i); }
    friend OutputStream& operator<<(OutputStream& os, const Get&) { return os << "get"; }
};

/** @brief Convert an array to a symbolic vector. */
struct Vec {
    static constexpr OperatorCode code() { return OperatorCode::VEC; }
    static OperatorKind kind() { return OperatorKind::NULLARY; }
    template<class X>
    decltype(auto) operator()(const Array<X>& a) { return Vector<X>(a); }
    friend OutputStream& operator<<(OutputStream& os, const Vec&) { return os << "Vector"; }
};

/************ Symbolic expression extensions ***************************/

template<class OP, class... AS>
using Symbolic = OperationNode<OP, AS...>;

template<class O, class... Args>
OperationNode<O, Args...> make_expression_template(O o, Args... as) {
    return OperationNode<O, Args...>(o, as...);
}

/** @brief Store alternative symbolic expressions in a discriminated union. */
template<class... SS>
class SymbolicVariant : public Variant<SS...> {
    template<class VIS>
    decltype(auto) accept(VIS&& vis) const { return std::visit(std::forward<VIS>(vis), static_cast<const Variant<SS...>&>(*this)); }
};

/** @brief Tag a symbolic while-loop expression. */
struct While {};
/** @brief Tag a symbolic iteration expression. */
struct Iterate {};
/** @brief Tag a symbolic conditional expression. */
struct IfThnEls {};

template<class O>
concept AGetter = Same<O, Get> or Same<O, OperatorVariant<Get>>;

/** @brief Represent a symbolic indexed access. */
template<class O, class V, class I>
    requires AGetter<O>
struct OperationNode<O, V, I> {
    O _op;
    V _vec;
    I _ind;
    O op() const { return _op; }
    V arg() const { return _vec; }
    V arg1() const { return _vec; }
    I arg2() const { return _ind; }
    V vec() const { return _vec; }
    I ind() const { return _ind; }
    OperationNode(O o, V v, I i) : _op(o), _vec(v), _ind(i) {}
    //    template<class T> explicit operator T() const { return _op(static_cast<T>(_vec),_ind); }
    template<class... AS>
    auto operator()(AS... vals) const -> decltype(_op(_vec(vals...), _ind)) {
        return _op(_vec(vals...), _ind);
    }
    friend OutputStream& operator<<(OutputStream& os, const OperationNode<O, V, I>& expr) {
        return os << expr._op.code() << "(" << expr._vec << "," << expr._ind << ")";
    }
};

/** @brief Represent a conditional symbolic operation. */
template<class C, class A>
struct OperationNode<IfThnEls, C, A> {
    IfThnEls _op;
    C _cnd;
    A _atru;
    A _afls;
    OperationNode(IfThnEls op, C cnd, A atru, A afls) : _op(op), _cnd(cnd), _atru(atru), _afls(afls) {}
    template<class... VS>
    decltype(auto) operator()(VS... vals) const {
        if (_cnd(vals...)) {
            return _atr(vals...);
        } else {
            return _afls(vals...);
        }
    }
    friend OutputStream& operator<<(OutputStream& os, const OperationNode<IfThnEls, C, A>& expr) {
        return os << "if(" << expr._cnd << ") { " << expr._atru << " } else { " << expr._afls << " }";
    }
};
/** @brief Represent repeated symbolic execution under a condition. */
template<class C, class F>
struct OperationNode<While, C, F> {
    While _op;
    C _cnd;
    F _fn;
    OperationNode(While op, C cnd, F fn) : _op(op), _cnd(cnd), _fn(fn) {}
    template<class S>
    S& operator()(S& s) const {
        while (_cnd(s)) {
            s = _fn(s);
        }
        return s;
    }
    friend OutputStream& operator<<(OutputStream& os, const OperationNode<While, C, F>& expr) {
        return os << "while(" << expr._cnd << ") { " << expr._fn << " }";
    }
};

/** @brief Represent iteration of a symbolic transition function. */
template<class F>
struct OperationNode<Iterate, F> {
    F _fn;
    OperationNode(Iterate, F fn) : _fn(fn) {}
    template<class S>
    Sequence<S> operator()(const S& s) const {
        // TODO: Use cache so that sequence does not always have to be recomputed
        return Sequence<S>([&](const Natural& n) { S t=s; for(Natural i=0u; i!=n; ++i) { t=_fn(t); } return t; });
    }
    friend OutputStream& operator<<(OutputStream& os, const OperationNode<Iterate, F>& expr) {
        return os << "iterate { " << expr._fn << " }";
    }
};

template<class O, class... Args>
struct TemporaryExpression;

/** @brief Hold a unary symbolic operation and its operand. */
template<class O, class A>
struct TemporaryExpression<O, A> {
    O _op;
    const A& _arg;
    TemporaryExpression(O o, const A& a) : _op(o), _arg(a) {}
};

/** @brief Hold a binary symbolic operation and operands. */
template<class O, class A1, class A2>
struct TemporaryExpression<O, A1, A2> {
    O _op;
    A1 const& _arg1;
    A2 const& _arg2;
    TemporaryExpression(O o, A1 const& a1, A2 const& a2) : _op(o), _arg1(a1), _arg2(a2) {}
};

/** @brief Hold a ternary symbolic operation and operands. */
template<class O, class A1, class A2, class A3>
struct TemporaryExpression<O, A1, A2, A3> {
    O _op;
    A1 const& _arg1;
    A2 const& _arg2;
    A3 const& _arg3;
    TemporaryExpression(O o, A1 const& a1, A2 const& a2, A3 const& a3) : _op(o), _arg1(a1), _arg2(a2), _arg3(a3) {}
};

} // namespace Ariadne

#endif
