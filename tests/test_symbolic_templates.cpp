/***************************************************************************
 *            tests/test_symbolic_templates.cpp
 *
 *  Copyright  2009-20  Pieter Collins
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

/** @file tests/test_symbolic_templates.cpp
 *  @brief Test symbolic operation-node expression templates.
 */

#include <sstream>
#include "numeric/numeric.hpp"
#include "algebra/algebra.hpp"
#include "function/formula.hpp"
#include "symbolic/expression.hpp"
#include "symbolic/valuation.hpp"
#include "symbolic/templates.tpl.hpp"
#include "symbolic/expression.tpl.hpp"
#include "ariadne-testing.hpp"

using namespace Ariadne;

class TestSymbolicTemplates : public Ariadne::Testing::ContextFixture {
    RealVariable x{"x"}, y{"y"}, z{"z"};
  public:
    using ContextFixture::ContextFixture;

    Void test_symbolic_template_operations() {
        RealExpression ex(x), ey(y), zero(0);
        ARIADNE_TESTING_PROVE(identical(simplify(zero/ex),zero));
        ARIADNE_TESTING_PROVE(is_affine_in(pos(ex),{x}));
        ARIADNE_TESTING_PROVE(not is_affine_in(pos(sqr(ex)),{x}));

        // Construct the supported Nul node explicitly: nul(ex) eagerly returns a constant.
        RealExpression null_node=make_expression<Real>(Nul(),sqr(ex));
        ARIADNE_TESTING_PROVE(is_affine_in(null_node,{x}));
        ARIADNE_TESTING_PROVE(is_polynomial_in(null_node,{x}));
        // These integer-valued Real results have exact representations.
        RealValuation values;
        values.set(x,Real(3));
        ARIADNE_TESTING_EXPECT_SAME(evaluate(null_node,values),Real(0));

        std::ostringstream product_stream, quotient_stream;
        product_stream << OperatorExpressionWriter()(ex*(ey-RealExpression(z)));
        quotient_stream << OperatorExpressionWriter()(ex/(ey+RealExpression(z)));
        ARIADNE_TESTING_EXPECT_EQUAL(product_stream.str(),"x*(y-z)");
        ARIADNE_TESTING_EXPECT_EQUAL(quotient_stream.str(),"x/(y+z)");

        BooleanVariable p("p");
        BooleanExpression ep(p);
        std::ostringstream logical_stream;
        logical_stream << OperatorExpressionWriter()(!ep);
        ARIADNE_TESTING_EXPECT_EQUAL(logical_stream.str(),"!(p)");
        StringVariable label("label");
        StringValuation labels;
        labels.set(label,String("ok"));
        ARIADNE_TESTING_PROVE(evaluate(!(label==String("ok")),labels)==Boolean(false));
        ARIADNE_TESTING_PROVE(evaluate(!(label==String("other")),labels)==Boolean(true));

        RealVectorExpression vector({x,y});
        RealVectorExpression constants(RealVector({1,2}));
        // Same operator code, different node types: structural identity is not commutativity.
        RealVectorExpression left_scaled=RealExpression(2)*vector;
        RealVectorExpression right_scaled=vector*RealExpression(2);
        ARIADNE_TESTING_PROVE(not identical(left_scaled,right_scaled));
        ARIADNE_TESTING_PROVE(not identical(right_scaled,left_scaled));
        values.set(y,Real(4));
        // Preserve the evaluated vectors while same() checks their components.
        // Otherwise operator[] exposes references to already-destroyed temporaries.
        RealVector const left_scaled_values=evaluate(left_scaled,values);
        RealVector const right_scaled_values=evaluate(right_scaled,values);
        ARIADNE_TESTING_EXPECT_SAME(left_scaled_values[0],Real(6));
        ARIADNE_TESTING_EXPECT_SAME(right_scaled_values[1],Real(8));
        ARIADNE_TESTING_PROVE(not identical(vector,constants));
        ARIADNE_TESTING_PROVE(not identical(constants,vector));
        ARIADNE_TESTING_PROVE(is_constant_in(neg(vector),{z}));
        ARIADNE_TESTING_PROVE(not is_constant_in(neg(vector),{x}));
        ARIADNE_TESTING_PROVE(is_constant_in(vector+constants,{z}));
        ARIADNE_TESTING_PROVE(not is_constant_in(vector+constants,{x}));
        ARIADNE_TESTING_PROVE(not is_constant_in(constants+vector,{x}));
        ARIADNE_TESTING_PROVE(is_constant_in(vector-constants,{z}));
        ARIADNE_TESTING_PROVE(is_constant_in(RealExpression(2)*vector,{z}));
        ARIADNE_TESTING_PROVE(not is_constant_in(ex*vector,{x}));
        ARIADNE_TESTING_PROVE(not is_constant_in(vector/ex,{x}));
        ARIADNE_TESTING_PROVE(is_affine_in(vector[0],{x,y}));
        RealVectorExpression nonlinear({sqr(ex),ey});
        ARIADNE_TESTING_PROVE(not is_affine_in(nonlinear[0],{x,y}));
    }

};

int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_symbolic_templates");
    ARIADNE_TESTING_ADD_TEST(TestSymbolicTemplates, test_symbolic_template_operations);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc, argv);
}
