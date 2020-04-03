import numpy as np
import sympy as sp
from sympy.plotting import plot
from sympy.abc import x

a = sp.Float(-14.4621)
b = sp.Float(60.6959)
c = sp.Float(-70.9238)
base_poly = sp.poly(x**3 + a*x**2 + b*x + c)

def shturm_amount_of_roots(poly = None, left_border = None, right_border = None):
    def shturm_range_value(_poly_range_, value):
        counter = 0
        size = len(_poly_range_)
        current_sgn = _poly_range_[0](value) > 0
        for i in range(size - 1):
            new_sgn = _poly_range_[i + 1](value) > 0
            if new_sgn != current_sgn:
                counter += 1
            current_sgn = new_sgn
        return counter
    shturm_sequence = []
    shturm_sequence.append(poly)
    shturm_sequence.append(sp.diff(poly))
    sequence_range = sp.degree(poly, gen = x)
    for i in range(sequence_range - 1):
        shturm_sequence.append(-sp.div(shturm_sequence[i], shturm_sequence[i + 1])[1])
    return shturm_range_value(shturm_sequence, left_border) - shturm_range_value(shturm_sequence, right_border)

def printPlot(poly = None, left_border = None, right_border = None):
    plot(x**3 + a*x**2 + b*x + c, left_border, right_border)
    return

def bisection(poly, left_border, right_border, accuracy):
    counter = 0
    while abs((left_border - right_border)) > accuracy:
            average = (left_border + right_border) / 2
            if poly(left_border) * poly(average) <= 0:
                right_border = average
            else:
                left_border = average
            counter += 1
    return average, counter
    
def chord(poly, left_border, right_border, accuracy):
    temp = 0
    average = 10 * accuracy
    counter = 0
    while abs(temp - average) > accuracy:
        temp = average
        average = left_border - (poly(left_border) / (poly(right_border) - poly(left_border))) * (right_border - left_border)
        if poly(left_border) * poly(average) <= 0:
            right_border = average
        else:
                left_border = average
        counter += 1
    return average, counter

def newton(poly, entrypoint, accuracy):
    derivative_func = sp.diff(poly)
    temp = entrypoint + accuracy*10
    counter = 0
    while abs(entrypoint - temp) > accuracy:
        temp = entrypoint
        entrypoint = entrypoint - poly(entrypoint) / derivative_func(entrypoint)
        counter += 1
    return entrypoint, counter
    
print(shturm_amount_of_roots(base_poly, -10, 10))
printPlot(poly = base_poly, left_border = -10, right_border = 10)
print(bisection(base_poly, -5, -2.5, 1e-5))
print(chord(base_poly, -5, -2.5, 1e-5))
print(newton(base_poly, -5, 1e-5))
