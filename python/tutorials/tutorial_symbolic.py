#!/usr/bin/python3

from pyariadne import *


def section(title):
    print(f"\n== {title} ==")


def show(label, value):
    print(f"{label}: {value}")


def real(numerator, denominator=1):
    return Real(Rational(numerator, denominator))


def tutorial_symbolic():
    section("Named variables and spaces")

    x = RealVariable("x")
    y = RealVariable("y")
    z = RealVariable("z")
    state = RealVariables("state", 3)
    mode = IntegerVariable("mode")
    enabled = BooleanVariable("enabled")

    xyz = RealSpace([x, y, z])

    show("space", xyz)
    show("space dimension", xyz.dimension())
    show("index of y", xyz.index(y))
    show("generated state variables", state)
    show("number of generated state variables", len(state))
    show("integer variable", mode)
    show("boolean variable", enabled)

    section("Building symbolic real expressions")

    expression = sqr(x) + real(2) * y + sin(z)
    redundant = expression + (x - x) + log(exp(y))
    simplified = simplify(redundant)

    show("expression", expression)
    show("redundant expression", redundant)
    show("simplified expression", simplified)

    section("Differentiation and structural analysis")

    dx = simplify(derivative(expression, x))
    dy = simplify(derivative(expression, y))
    dz = simplify(derivative(expression, z))

    show("d/dx", dx)
    show("d/dy", dy)
    show("d/dz", dz)

    repeated = sqr(x + y) + sin(x + y) + (x + y)
    show("expression with repeated subexpressions", repeated)
    show("nodes before CSE", count_nodes(repeated))
    show("distinct nodes", count_distinct_nodes(repeated))
    show(
        "distinct node pointers before CSE",
        count_distinct_node_pointers(repeated),
    )

    eliminate_common_subexpressions(repeated)

    show(
        "distinct node pointers after CSE",
        count_distinct_node_pointers(repeated),
    )

    section("Substitution and valuation")

    substitutions = [
        let(y) << (x + real(1)),
        let(z) << RealExpression(real(0)),
    ]
    substituted = substitute(expression, substitutions)

    show("substituted expression", substituted)

    valuation = RealValuation()
    valuation[x] = real(1, 2)
    valuation[y] = real(1)
    valuation[z] = real(0)

    show("valuation", valuation)
    show("number of assigned variables", len(valuation))
    show("evaluated expression", evaluate(expression, valuation))

    section("Assignments describe algebraic, discrete and differential rules")

    algebraic_rule = let(x) << (y + real(1))
    discrete_update = prime(x) << (x + y)
    differential_rule = dot(x) << (-x + y)

    show("algebraic assignment", algebraic_rule)
    show("discrete update", discrete_update)
    show("differential equation", differential_rule)

    section("From symbolic expressions to callable functions")

    scalar_function = make_function(xyz, expression)
    vector_expression = RealExpressionVector([
        x + y,
        sqr(z) + x,
    ])
    vector_function = make_function(xyz, vector_expression)

    show("scalar function", scalar_function)
    show("vector function", vector_function)
    show("x coordinate index", xyz.index(x))
    show("z coordinate index", xyz.index(z))

    section("Choosing a symbolic abstraction")
    print("Variable / RealSpace: give names to quantities and define coordinate order.")
    print("Expression: build and manipulate formulas before numerical evaluation.")
    print("Valuation: evaluate named expressions at concrete values.")
    print("let / prime / dot assignments: describe algebraic, discrete and differential rules.")
    print("make_function: compile named expressions into coordinate-based functions.")


if __name__ == "__main__":
    tutorial_symbolic()
