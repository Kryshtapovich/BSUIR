import sympy
import numpy
from matplotlib import pyplot
from prettytable import PrettyTable
from sympy import true

x = sympy.Symbol('x')
start = -1
finish = 1
y_arrays = []
k = 0.2
T = 1
Y2 = []
g1 = lambda t: 0
g2 = lambda t: 0
f = lambda x: 1 - x**2
data_table = []


def solve(tau, h, t, last_layer = None):
    fx = 1
    A = []
    B = []
    Y = []
    i = 0
    if true:
        pass
    xi = start
    while xi < finish - 1e-5:
        if t != 0:
            a = -k * tau
            b = h**2 + 2 * k * tau
            c = -k * tau
            d = tau * h**2 * fx + h**2 * last_layer[i]

            if i == 0:
                Ai = - c / b
                Bi = (d - a * g1(t)) / b
            else:
                Ai = -c / (b + a * A[-1])
                Bi = (d - a * B[-1]) / (b + a * A[-1])

            A.append(Ai)
            B.append(Bi)
        else:
            Y.append(f(xi))
        xi += h
        i += 1

    if t == 0:
        Y.append(finish ** 2)
        return Y

    Y = [0] * 11

    Y[0] = g1(t)
    Y[-2] = (A[-2] * h * g2(t) + B[-2]) / (1 - A[-2])
    Y[-1] = Y[-2] + 4*h  # yb

    while i > 1:
        i -= 1
        Y[i] = A[i] * Y[i + 1] + B[i]

    return Y


def solve2(tau, h, t, j):
    Y = [0] * 11
    fx = 1
    xi = start

    if j == 0:
        i = 0
        while xi < finish:
            Y[i] = f(xi)
            i += 1
            xi += h
    else:
        Y[0] = g1(t)
        for i in range(1, 10):
            Y[i] = Y2[j - 1][i] + tau / h ** 2 * (Y2[j - 1][i + 1] - 2 * Y2[j - 1][i] + Y2[j - 1][i - 1])
            xi += h

        Y[-2] = Y2[j - 1][-2] + tau / h ** 2 * (2 * h * g2(t) - Y2[j - 1][-2] + Y2[j - 1][-3])
        Y[-1] = Y[-2] + 2 * h *g2(t)

    Y2.append(Y)


def implicit_function(h, tau):
    y_arrays.clear()
    t = 0
    for i in range(0, 10):
        if i == 0:
            y_arrays.append(solve(tau, h, t))
        else:
            y_arrays.append(solve(tau, h, t, y_arrays[-1]))
        print(t)
        if t == 0:
            t = 2 * tau
        else:
            t *= 2
        if t > T:
            break


def explicit_function(h, tau):
    t = 0
    Y2.clear()
    for i in range(0, 10):
        solve2(tau, h, t, i)
        print(t)
        if t == 0:
            t = 2 * tau
        else:
            t *= 2
        if t > T:
            break


def print_grafic(array, h, method, t):
    x = numpy.arange(start, finish + h, h)
    pyplot.plot(x, array)
    pyplot.title(method + " метод (t = " + t + ")")
    pyplot.show()


def create_table():
    table = PrettyTable(["N", "tau", "S(t=2tau)", "S(t=4tau)", "Mmod(t=2tau)", "Mmod(t=4tau)"])
    for data in data_table:
        table.add_row(data)
    print(table)


def my_round(value):
    return "{:.5f}".format(value)


def main():
    h = (finish - start) / 10
    tau = 0.5 * h ** 2 / k
    tau_test = tau
    N = h
    j = 1
    for i in range(0, 4):
        implicit_function(h, tau_test)
        max_2_tau = 0
        for u in y_arrays[1]:
            if max_2_tau < u:
                max_2_tau = u

        max_4_tau = 0
        for u in y_arrays[2]:
            if max_4_tau < u:
                max_4_tau = u

        data_table.append([N, my_round(tau_test), my_round(y_arrays[1][j]), my_round(y_arrays[2][j]), max_2_tau, max_4_tau])
        N *= 2
        j += 2
        tau_test /= 4

    create_table()

    implicit_function(h, tau)
    t = 0
    for array in y_arrays:
        print_grafic(array, h, "Неявный", "{t:.9f}".format(t=t))
        if t == 0:
            t = 2 * tau
        else:
            t *= 2

    data_table.clear()
    tau_test = tau
    N = h
    j = 1
    for i in range(0, 4):
        explicit_function(h, tau_test)
        max_2_tau = 0
        for u in Y2[1]:
            if max_2_tau < u:
                max_2_tau = u

        max_4_tau = 0
        for u in Y2[2]:
            if max_4_tau < u:
                max_4_tau = u

        data_table.append([N, my_round(tau_test), my_round(Y2[1][j]), my_round(Y2[2][j]), max_2_tau, max_4_tau])
        N *= 2
        j += 2
        tau_test /= 4

    create_table()
    explicit_function(h, tau)
    t = 0
    for array in Y2:
        print_grafic(array, h, "Явный", "{t:.9f}".format(t=t))
        if t == 0:
            t = 2 * tau
        else:
            t *= 2

    tau = h ** 2 / 6
    data_table.clear()
    tau_test = tau
    N = h
    j = 1
    for i in range(0, 4):
        implicit_function(h, tau_test)
        max_2_tau = 0
        for u in y_arrays[1]:
            if max_2_tau < u:
                max_2_tau = u

        max_4_tau = 0
        for u in y_arrays[2]:
            if max_4_tau < u:
                max_4_tau = u

        data_table.append([N, my_round(tau_test), my_round(y_arrays[1][j]), my_round(y_arrays[2][j]), max_2_tau, max_4_tau])
        N *= 2
        j += 2
        tau_test /= 4

    create_table()
    explicit_function(h, tau)
    t = 0
    for array in Y2:
        print_grafic(array, h, "Явный", "{t:.9f}".format(t=t))
        if t == 0:
            t = 2 * tau
        else:
            t *= 2


if __name__ == "__main__":
    main()

