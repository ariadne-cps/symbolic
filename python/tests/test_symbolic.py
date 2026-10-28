from pyariadne import *


def test_symbolic():
    x = RealVariable("x")
    y = RealVariable("y")
    expression = x * x + y

    derivative(expression, x)
    make_function([x, y], expression)
    # Predicate composition belongs to symbolic; variable bounds belong to expression-set.
    predicate = (expression >= Real(0)) & (expression <= Real(1))
    assert str(predicate)
