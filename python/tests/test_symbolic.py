from pyariadne_symbolic import *


def test_symbolic():
    x = RealVariable("x")
    y = RealVariable("y")
    expression = x * x + y

    derivative(expression, x)
    make_function([x, y], expression)
    # Predicate composition belongs to symbolic; variable bounds belong to expression-set.
    predicate = (expression >= Real(0)) & (expression <= Real(1))
    assert str(predicate)


def test_sigmoid_softplus_expressions():
    x = RealVariable("x")
    expr = RealExpression(x)
    s = sigmoid(expr)
    p = softplus(expr)
    assert str(s) and str(p)
    assert identical(s, sigmoid(expr))
    assert identical(p, softplus(expr))
    assert str(simplify(derivative(s, x)))
    assert str(simplify(derivative(p, x)))
