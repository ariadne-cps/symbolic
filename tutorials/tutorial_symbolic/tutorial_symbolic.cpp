#include <iostream>
#include <string>

#include "ariadne-symbolic.hpp"

using namespace Ariadne;
using std::cout;

namespace {

void section(const std::string& title) {
    cout << "\n== " << title << " ==\n";
}

template<class T>
void show(const std::string& label, const T& value) {
    cout << label << ": " << value << "\n";
}

} // namespace

int main() {
    section("Named variables and spaces");

    RealVariable x("x");
    RealVariable y("y");
    RealVariable z("z");
    RealVariables state("state",3);
    IntegerVariable mode("mode");
    BooleanVariable enabled("enabled");

    RealSpace xyz({x,y,z});

    show("space", xyz);
    show("space dimension", xyz.dimension());
    show("index of y", xyz.index(y));
    show("generated state variables", state);
    show("integer variable", mode);
    show("boolean variable", enabled);

    section("Building symbolic real expressions");

    // Symbolic expressions keep variable names rather than committing to a
    // coordinate order.  They can therefore be manipulated before deciding
    // how they should be embedded in Euclidean space.
    RealExpression expression =
        sqr(x) + Real(2)*y + sin(z);

    RealExpression redundant =
        expression + (x-x) + log(exp(y));
    RealExpression simplified = simplify(redundant);

    show("expression", expression);
    show("redundant expression", redundant);
    show("simplified expression", simplified);

    section("Differentiation and structural analysis");

    RealExpression dx = simplify(derivative(expression,x));
    RealExpression dy = simplify(derivative(expression,y));
    RealExpression dz = simplify(derivative(expression,z));

    show("d/dx", dx);
    show("d/dy", dy);
    show("d/dz", dz);

    RealExpression repeated =
        sqr(x+y) + sin(x+y) + (x+y);
    show("expression with repeated subexpressions", repeated);
    show("nodes before CSE", count_nodes(repeated));
    show("distinct nodes", count_distinct_nodes(repeated));
    show("distinct node pointers before CSE",
         count_distinct_node_pointers(repeated));

    eliminate_common_subexpressions(repeated);

    show("distinct node pointers after CSE",
         count_distinct_node_pointers(repeated));

    section("Substitution and valuation");

    List<RealAssignment> substitutions({
        let(y)=x+Real(1),
        let(z)=Real(0)
    });
    RealExpression substituted =
        substitute(expression,substitutions);

    show("substituted expression", substituted);

    // A Valuation gives concrete values to named variables without changing
    // the expression itself.
    RealValuation valuation;
    valuation.set(x,Real(Rational(1,2)));
    valuation.set(y,Real(1));
    valuation.set(z,Real(0));

    show("valuation", valuation);
    show("evaluated expression", evaluate(expression,valuation));

    section("Assignments describe algebraic, discrete and differential rules");

    RealAssignment algebraic_rule =
        let(x)=y+Real(1);
    PrimedRealAssignment discrete_update =
        prime(x)=x+y;
    DottedRealAssignment differential_rule =
        dot(x)=-x+y;

    show("algebraic assignment", algebraic_rule);
    show("discrete update", discrete_update);
    show("differential equation", differential_rule);

    section("From symbolic expressions to callable functions");

    EffectiveScalarMultivariateFunction scalar_function =
        make_function(xyz,expression);

    Vector<RealExpression> vector_expression({
        x+y,
        sqr(z)+x
    });
    EffectiveVectorMultivariateFunction vector_function =
        make_function(xyz,vector_expression);

    show("scalar function", scalar_function);
    show("vector function", vector_function);

    // RealSpace fixes the argument ordering.  The expression remains
    // name-based, but the resulting functions use coordinates [x,y,z].
    show("x coordinate index", xyz.index(x));
    show("z coordinate index", xyz.index(z));

    section("Choosing a symbolic abstraction");
    cout
        << "Variable / RealSpace: give names to quantities and define coordinate order.\n"
        << "Expression: build and manipulate formulas before numerical evaluation.\n"
        << "Valuation: evaluate named expressions at concrete values.\n"
        << "let / prime / dot assignments: describe algebraic, discrete and differential rules.\n"
        << "make_function: compile named expressions into coordinate-based functions.\n";

    return 0;
}
