import math

import numpy
import pylab
import sympy
from sympy.solvers.solveset import linsolve
from numpy import linspace
import functools

x = sympy.Symbol('x')

VARIANT = 11
VARIABLES = 5
DIFF_POINTS = 5

a = -1
b = 1


def func_for_substantiation(subs):
    func = sympy.sin(VARIANT) * sympy.diff(subs, x, x) + ((1 + sympy.cos(VARIANT) * x ** 2) * subs + 1)
    return func


def generate_basis_sequence(n):
    sequence = []
    for i in range(n):
        sequence.append((x ** i) * (1 - x ** 2))
    return sequence


def build_function_from_basis(basis):
    result = 0
    for i in range(len(basis)):
        current_a = sympy.Symbol('a' + str(i))
        result += current_a * basis[i]
    return result


def collocations_method(basis, points):
    func = build_function_from_basis(basis)
    psi_func = func_for_substantiation(func)
    symbols = [sympy.Symbol('a' + str(i)) for i in range(len(points))]
    lin_system = []
    for point in points:
        lin_system.append(psi_func.subs(x, point).evalf())
    answer = linsolve(lin_system, *symbols)
    return answer


def integral_least_square_method(basis, a, b):
    func = build_function_from_basis(basis)
    psi_func = func_for_substantiation(func)
    symbols = [sympy.Symbol('a' + str(i)) for i in range(len(basis))]
    lin_system = []
    for i in range(len(basis)):
        lin_system.append(sympy.integrate(2 * sympy.diff(
            psi_func, symbols[i]) * psi_func, (x, a, b)).evalf())
    answer = linsolve(lin_system, *symbols)
    return answer


def discrete_least_square_method(basis, points_num, a, b):
    func = build_function_from_basis(basis)
    psi_func = func_for_substantiation(func)
    seq = [psi_func.subs(x, point) ** 2 for point in linspace(a + 0.05, b - 0.05, points_num)]
    psi_sqr_sum = functools.reduce((lambda a, b: a + b), seq)
    symbols = [sympy.Symbol('a' + str(i)) for i in range(len(basis))]
    lin_system = []
    for i in range(len(basis)):
        lin_system.append(sympy.diff(psi_sqr_sum, symbols[i]).evalf())
    answer = linsolve(lin_system, *symbols)
    return answer


def galerkin_method(basis, a, b):
    func = build_function_from_basis(basis)
    psi_func = func_for_substantiation(func)
    symbols = [sympy.Symbol('a' + str(i)) for i in range(len(basis))]
    lin_system = []
    for i in range(len(basis)):
        lin_system.append(sympy.integrate(
            psi_func * basis[i], (x, a, b)).evalf())
    answer = linsolve(lin_system, *symbols)
    return answer


def get_basis_function(n):
    if not n:
        return lambda x: 0
    return lambda x: x ** (n - 1) * (1 - x ** 2)


def get_basis_system(num_of_basis_functions):
    return [get_basis_function(n) for n in range(num_of_basis_functions)]


def numerical_integration(f, a, b):
    n = 100
    dx = (b - a) / n
    xlist = numpy.arange(a, b, dx)
    ylist = [f(p) for p in xlist]
    return numpy.trapz(ylist, dx=dx)


def numerical_diff(f, x, n):
    h = 0.001
    if not n:
        return f(x)
    elif n == 1:
        return (f(x + h) - f(x - h)) / (2 * h)
    elif n == 2:
        return (f(x - h) - 2 * f(x) + f(x + h)) / (h ** 2)
    else:
        raise NotImplementedError


def integral_LSM(coefficients, f, num_of_basis_functions, a, b):
    basis = get_basis_system(num_of_basis_functions)

    def resudial_part_diff(a):
        return lambda x: sum(coefficients[i](x) * numerical_diff(basis[a], x, i)
                             for i in range(len(coefficients)))

    part_diffs = [resudial_part_diff(i) for i in range(num_of_basis_functions)]

    matrix = [[numerical_integration(lambda x: part_diffs[i](x) * part_diffs[j](x), a, b)
               for j in range(1, num_of_basis_functions)]
              for i in range(1, num_of_basis_functions)]
    right_side = [numerical_integration(
        lambda x: (f(x) - part_diffs[0](x)) * part_diffs[i](x), a, b)
        for i in range(1, num_of_basis_functions)]
    answer = numpy.linalg.solve(numpy.matrix(matrix), numpy.array(right_side))
    return lambda x: basis[0](x) + sum(answer[i - 1] * basis[i](x)
                                       for i in range(1, num_of_basis_functions))


import time


def discrete_LSM(coefficients, f, num_of_basis_functions, points):
    basis = get_basis_system(num_of_basis_functions)

    def resudial_part_diff(a, x):
        return sum(coefficients[i](x) * numerical_diff(basis[a], x, i)
                   for i in range(len(coefficients)))

    part_diffs_x = {(i, x): resudial_part_diff(i, x) for i in range(num_of_basis_functions)
                    for x in points}

    matrix = [[sum(part_diffs_x[(i, x)] * part_diffs_x[(j, x)] for x in points)
               for j in range(1, num_of_basis_functions)]
              for i in range(1, num_of_basis_functions)]
    right_side = [sum([(f(x) - part_diffs_x[(0, x)]) * part_diffs_x[(i, x)] for x in points])
                  for i in range(1, num_of_basis_functions)]
    answer = numpy.linalg.solve(numpy.matrix(matrix), numpy.array(right_side))
    return lambda x: basis[0](x) + sum(answer[i - 1] * basis[i](x)
                                       for i in range(1, num_of_basis_functions))


def Galerkin_method(coefficients, f, num_of_basis_functions, a, b):
    basis = get_basis_system(num_of_basis_functions)

    def resudial_part_diff(a):
        return lambda x: sum(coefficients[i](x) * numerical_diff(basis[a], x, i)
                             for i in range(len(coefficients)))

    part_diffs = [resudial_part_diff(i) for i in range(num_of_basis_functions)]

    def optimal_numerical_integration(f1, f2, points):
        dx = 2 / len(points)
        return sum([(f1[i] * f2[i] * dx) for i in range(0, len(points))])

    points = numpy.linspace(a, b, 100)
    points = [(points[i] + points[i - 1]) / 2 for i in range(1, len(points))]

    opt_part_diffs = [None] * num_of_basis_functions
    opt_basis = [None] * num_of_basis_functions
    for i in range(1, num_of_basis_functions):
        opt_part_diffs[i] = []
        opt_basis[i] = []
        for point in points:
            opt_part_diffs[i].append(part_diffs[i](point))
            opt_basis[i].append(basis[i](point))

    matrix = [[optimal_numerical_integration(opt_part_diffs[j], opt_basis[i], points)
               for j in range(1, num_of_basis_functions)]
              for i in range(1, num_of_basis_functions)]
    right_side = [numerical_integration(
        lambda x: (f(x) - part_diffs[0](x)) * basis[i](x), a, b)
        for i in range(1, num_of_basis_functions)]
    answer = numpy.linalg.solve(numpy.matrix(matrix), numpy.array(right_side))
    return lambda x: basis[0](x) + sum(answer[i - 1] * basis[i](x)
                                       for i in range(1, num_of_basis_functions))


def collocation_method(coefficients, f, collocation_points):
    num_of_basis_functions = len(collocation_points) + 1
    basis = get_basis_system(num_of_basis_functions)

    def resudial_part_diff(a):
        return lambda x: sum(coefficients[i](x) * numerical_diff(basis[a], x, i)
                             for i in range(len(coefficients)))

    matrix = [[resudial_part_diff(i)(point) for i in range(1, num_of_basis_functions)]
              for point in collocation_points]
    right_side = [f(point) - resudial_part_diff(0)(point)
                  for point in collocation_points]
    answer = numpy.linalg.solve(numpy.matrix(matrix), numpy.array(right_side))
    return lambda x: basis[0](x) + sum(answer[i - 1] * basis[i](x)
                                       for i in range(1, num_of_basis_functions))


print('collocations method: \n',
      collocations_method(generate_basis_sequence(VARIABLES),
                          linspace(a + 0.2, b - 0.2, VARIABLES)))

print('integral least square method: \n',
      integral_least_square_method(generate_basis_sequence(VARIABLES), a, b))

print('discrete least square method: \n',
      discrete_least_square_method(generate_basis_sequence(VARIABLES),
                                   VARIABLES + DIFF_POINTS, a, b))

print('galerkin method: \n',
      galerkin_method(generate_basis_sequence(VARIABLES), a, b))

coeffs = [lambda x: 1 + math.cos(VARIANT) * x ** 2,
          lambda x: 0,
          lambda x: math.sin(VARIANT)]
f = lambda x: -1


def show_plots(functions, start_x, end_x, dx, title):
    for function in functions:
        x_list = numpy.arange(start_x, end_x, dx)
        y_list = [function(p) for p in x_list]
        pylab.plot(x_list, y_list)
        pylab.title(title)
    pylab.grid(True)
    pylab.show()


collocation_points = numpy.linspace(a, b, 100)
answer_2_with_collocation_method = \
    collocation_method(coeffs, f, collocation_points)
show_plots([answer_2_with_collocation_method], a, b, 0.01, "Collocations method")

answer_2_with_integral_LSM_method = \
    integral_LSM(coeffs, f, 50, a, b)
show_plots([answer_2_with_integral_LSM_method], a, b, 0.01, "Integral least squared method")

points = numpy.linspace(a, b, 200)
answer_2_with_discrete_LSM_method = \
    discrete_LSM(coeffs, f, 100, points)
show_plots([answer_2_with_discrete_LSM_method], a, b, 0.01, "Discrete least squared method")

answer_2_with_Galerkin_method = Galerkin_method(coeffs, f, 50, a, b)
show_plots([answer_2_with_Galerkin_method], a, b, 0.01, "Galerkin method")
