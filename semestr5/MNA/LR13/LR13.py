import sympy
from sympy.solvers import solve
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import cm
import math

import pylab
from mpl_toolkits.mplot3d import Axes3D

from numpy import linspace
from collections import namedtuple

POWER = 5
POWER5 = 25
POWER_1 = 35
POWER_2 = 15
POWER_3 = 10
POWER_4 = 30
ITER_COUNT = 150
LINSPACE_SIZE = 100
x = sympy.Symbol('x')

a = 0.2
b = 1.2
u_a = 4
u_b = 1
my_k = 1


def k_1(x, c):
    return x ** 3


def function_1(x):
    return 1.0 + x ** (1 / 3)


def sweep_method(a, b, c, d):
    AlphaS = [-c[0] / b[0]]
    BetaS = [d[0] / b[0]]
    GammaS = [b[0]]
    n = len(d)
    result = [0 for i in range(n)]

    for i in range(1, n - 1):
        GammaS.append(b[i] + a[i] * AlphaS[i - 1])
        AlphaS.append(-c[i] / GammaS[i])
        BetaS.append((d[i] - a[i] * BetaS[i - 1]) / GammaS[i])

    GammaS.append(b[n - 1] + a[n - 1] * AlphaS[n - 2])
    BetaS.append((d[n - 1] - a[n - 1] * BetaS[n - 2]) / GammaS[n - 1])

    result[n - 1] = BetaS[n - 1]
    for i in reversed(range(n - 1)):
        result[i] = AlphaS[i] * result[i + 1] + BetaS[i]

    return result


def check_eps(current, prev, eps, debuging=True):
    eps_t = max([math.fabs(current[i*2]-prev[i]) for i in range(len(prev))])
    if debuging:
        print('Check: ', eps_t)
    if eps_t > eps:
        return False
    return True


def deep_copy(system):
    return [item for item in system]


def get_h(a, b, n):
    return (b - a) / n


def build_final_equation(f, k, c, c1, c2):
    first_iter = (-(sympy.integrate(f(x), x) + c1) / k(x, c)).expand()
    second_iter = sympy.integrate(first_iter, x) + c2
    return second_iter


def func_for_partition_2(yk_m1, yk, yk_p1, h, k=1, func=None):
    if not func:
        func = function_1

    func = -k * (yk_p1 - 2 * yk + yk_m1) / h ** 2 - func(x)
    return func


def solve_thermal_conductivity_equation(f, k, c, a, b, u_a, u_b):
    c1, c2 = sympy.Symbol('c1'), sympy.Symbol('c2')
    true_eq = build_final_equation(f, k, c, c1, c2)
    c2_val = solve(true_eq.subs(x, b) - u_b, c2)[0]
    true_eq = true_eq.subs(c2, c2_val)

    c1_val = solve(true_eq.subs(x, a) - u_a, c1)[0]
    true_eq = true_eq.subs(c1, c1_val)
    print(true_eq)
    return true_eq


def differences_method(start_variables_count,
                       a,
                       b,
                       y_a,
                       y_b,
                       func_for_partition,
                       points_k,
                       func=None):
    h = (b - a) / start_variables_count
    points = linspace(a + h, b - h, start_variables_count).tolist()

    a_k = []
    b_k = []
    c = []
    d = []
    if func is None:
        func = function_1
    print(func)
    selected_k = 0
    for i in range(start_variables_count):
        if points[i] > points_k[selected_k][0]:
            selected_k += 1
        a_k.append(-points_k[selected_k][1] / (h ** 2))
        b_k.append(2 * points_k[selected_k][1] / h ** 2)
        c.append(-points_k[selected_k][1] / h ** 2)
        d.append(func(points[i]))
    d[0] = d[0] - a_k[0] * y_a
    d[-1] = d[-1] - c[-1] * y_b
    answer = sweep_method(a_k, b_k, c, d)
    data_type = namedtuple('data',
                           ('points', 'answer', 'step'))
    points.insert(0, a)
    points.append(b)

    answer.insert(0, y_a)
    answer.append(y_b)
    return data_type(points, answer, h)


def task_1():
    print("Задача №1")

    var_1 = solve_thermal_conductivity_equation(function_1, k_1, 1, a, b, u_a, u_b)
    var_2 = solve_thermal_conductivity_equation(function_1,
                                                lambda x, c: c * k_1(x, c),
                                                2, a, b, u_a, u_b)
    var_3 = solve_thermal_conductivity_equation(function_1,
                                                lambda x, c: c * k_1(x, c),
                                                0.1, a, b, u_a, u_b)

    D = linspace(a, b, LINSPACE_SIZE)
    func_y1, func_y2, func_y3, func_y4 = [], [], [], []
    for i in range(len(D)):
        func_y1.append(var_1.subs(x, D[i]))
        func_y2.append(var_2.subs(x, D[i]))
        func_y3.append(var_3.subs(x, D[i]))

    fig, _ = plt.subplots()
    plt.plot(D, func_y1, c='red', label='c=1')
    plt.plot(D, func_y2, c='green', label='c=2')
    plt.plot(D, func_y3, c='blue', label='c=0.1')

    plt.legend()
    plt.show()

    var_4 = solve_thermal_conductivity_equation(function_1,
                                                lambda x, c: 1 / k_1(x, c),
                                                1, a, b, u_a, u_b)

    for i in range(len(D)):
        func_y4.append(var_4.subs(x, D[i]))

    fig, _ = plt.subplots()
    plt.plot(D, func_y1, c='red', label='набор 1')
    plt.plot(D, func_y4, c='green', label='набор 2')

    plt.legend()
    plt.show()

    var_5 = solve_thermal_conductivity_equation(function_1, k_1, 1, a, b, -u_a,
                                                u_b)
    var_6 = solve_thermal_conductivity_equation(function_1, k_1, 1, a, b, u_a,
                                                -u_b)
    var_7 = solve_thermal_conductivity_equation(function_1, k_1, 1, a, b, -u_a,
                                                -u_b)

    func_y5, func_y6, func_y7 = [], [], []
    for i in range(len(D)):
        func_y5.append(var_5.subs(x, D[i]))
        func_y6.append(var_6.subs(x, D[i]))
        func_y7.append(var_7.subs(x, D[i]))

    fig, _ = plt.subplots()
    plt.plot(D, func_y5, c='red', label='набор 5')
    plt.plot(D, func_y6, c='green', label='набор 6')
    plt.plot(D, func_y7, c='blue', label='набор 7')

    plt.legend()
    plt.show()


def task_2():
    POWER = 200
    POWER_1 = 100
    POWER_2 = 150
    POWER_3 = 100
    POWER_4 = 300

    a = 0.2
    b = 1.2
    u_a = 4
    u_b = 1
    my_k = 1
    eps = 0.007
    print("Задача №2")
    data_a1 = differences_method(ITER_COUNT, a, b, u_a, u_b, func_for_partition_2,
                                 [(0.5 * (b + a), 0.01), (b, 150)])
    print('h=', data_a1.step)
    data_a2 = differences_method(ITER_COUNT, a, b, u_a, u_b, func_for_partition_2,
                                 [(0.5 * (b + a), 150), (b, 0.01)])

    D1, y1 = data_a1.points, data_a1.answer
    D2, y2 = data_a2.points, data_a2.answer

    plt.figure()
    plt.plot(D1, y1, color='red', label='k1 << k2')
    plt.plot(D2, y2, label='k1 >> k2')
    plt.title('задача 2 пункт 3.1')
    plt.grid(True)
    plt.legend()
    plt.show()

    data_b1 = differences_method(ITER_COUNT, a, b, u_a, u_b, func_for_partition_2,
                                 [(a + (1 / 3) * (b - a), 0.2),
                                  (a + (2 / 3) * (b - a), 0.6),
                                  (b, 0.9)])
    data_b2 = differences_method(ITER_COUNT, a, b, u_a, u_b, func_for_partition_2,
                                 [(a + (1 / 3) * (b - a), 0.9),
                                  (a + (2 / 3) * (b - a), 0.6),
                                  (b, 0.2)])
    data_b3 = differences_method(ITER_COUNT, a, b, u_a, u_b, func_for_partition_2,
                                 [(a + (1 / 3) * (b - a), my_k),
                                  (a + (2 / 3) * (b - a), 2 * my_k),
                                  (b, my_k)])
    data_b4 = differences_method(ITER_COUNT, a, b, u_a, u_b, func_for_partition_2,
                                 [(a + (1 / 3) * (b - a), 20 * my_k),
                                  (a + (2 / 3) * (b - a), my_k),
                                  (b, 20 * my_k)])

    D1, y1 = data_b1.points, data_b1.answer
    D2, y2 = data_b2.points, data_b2.answer
    D3, y3 = data_b3.points, data_b3.answer
    D4, y4 = data_b4.points, data_b4.answer
    plt.figure()
    plt.plot(D1, y1, color='red', label='k1<k2<k3')
    plt.plot(D2, y2, color='green', label='k1>k2>k3')
    plt.plot(D3, y3, color='blue', label='k1=k, k2=2k, k3=k')
    plt.plot(D4, y4, color='yellow', label='k1=20k, k2=k, k3=20k')
    plt.title('задача 2 пункт 3.2')
    plt.grid(True)
    plt.legend()
    plt.show()

    def delta_1(x):
        if x > (a + (b - a) * 0.5):
            return POWER
        return 0

    def delta_2(x):
        p = 0
        if x > (a + (b - a) / 3):
            p = POWER5
        if x > (a + 2 * (b - a) / 3):
            p += POWER5
        if p != 0:
            return p
        return 0

    def delta_3(x):

        p = 0
        if x > (a + (b - a) / 3):
            p += POWER_1
        if x > (a + 2 * (b - a) / 3):
            p += POWER_2
        if p != 0:
            return p
        return 0

    def delta_4(x):
        p = 0
        if x > (a + (b - a) * 0.2):
            p = POWER_3
        if x > (a + (b - a) * 0.8):
            p += POWER_4
        if p != 0:
            return p
        return 0

    data_c1 = differences_method(ITER_COUNT, a, b, u_a, u_b, func_for_partition_2,
                                 [(b, my_k)], delta_1)

    data_c2 = differences_method(ITER_COUNT, a, b, u_a, u_b, func_for_partition_2,
                                 [(b, my_k)], delta_2)
    data_c3 = differences_method(ITER_COUNT, a, b, u_a, u_b, func_for_partition_2,
                                 [(b, my_k)], delta_3)
    data_c4 = differences_method(ITER_COUNT, a, b, u_a, u_b, func_for_partition_2,
                                 [(b, my_k)], delta_4)

    D1, y1 = data_c1.points, data_c1.answer
    D2, y2 = data_c2.points, data_c2.answer
    D3, y3 = data_c3.points, data_c3.answer
    D4, y4 = data_c4.points, data_c4.answer
    plt.figure()
    plt.plot(D1, y1, color='red', label='источник в середине')
    plt.plot(D2, y2, color='green', label='одинаковые источники симметрично')
    plt.plot(D3, y3, color='yellow', label='разные источники симметрично')
    plt.plot(D4, y4, label='Разные источники на 0.2 и 0.8')
    plt.title('задача №2 пункт 3.4: ')
    plt.legend()
    plt.grid(True)
    plt.show()


def task_3():
    def specified(a, b, t_0, t_n, h, tetta, fi, g1, g2, k, f, func_for_partition):
        columns = int((b - a) / h) + 1
        rows = int((t_n - t_0) / tetta) + 1
        solving = np.zeros((rows, columns))

        for index, value in enumerate(j for j in np.arange(a, b + h, h)):
            solving[0][index] = fi(value)
        for index, value in enumerate(j for j in np.arange(t_0, t_n, tetta)):
            solving[index][0] = g1(value)
            solving[index][-1] = g2(value)
        alfa = tetta / (h ** 2)
        a_k = [k * alfa] * columns
        b_k = [-(1 + 2 * k * alfa)] * columns
        c_k = [alfa] * columns
        x_points = linspace(a, b, columns).tolist()
        for index_t, time in enumerate((j for j in np.arange(t_0, t_n, tetta)), 1):
            d_k = []
            for index_x, coord in enumerate((j for j in x_points)):
                d_k.append(-tetta * f(coord, time) - solving[index_t - 1][index_x])
            d_k[0] = d_k[0] - a_k[0] * g1(time)
            d_k[-1] = d_k[-1] - c_k[-1] * g2(time)
            solving[index_t] = sweep_method(a_k, b_k, c_k, d_k)
        return solving

    print('Задача № 3')
    a = 1
    ua = 3
    b = 2
    ub = 3
    h = 0.01
    tetta = 0.05
    k = 1
    fi = lambda x: 0
    T1 = 0
    T = 10
    f = lambda x, t: (x ** 3) + 2

    def func_for_partition(coord, time, T_prev, T_cur, T_next, h, tetta, f):
        return tetta / (h ** 2) * T_prev + (1 - 2 * tetta / (h ** 2)) * T_cur + tetta / (h ** 2) * T_next + tetta * f(
            coord, time)

    solving = specified(a, b, T1, T, h, tetta, fi, lambda t: ua, lambda t: ub, k, f, func_for_partition)
    points = np.arange(a, b + h, h)

    plt.plot(points, solving[0], color='red', label='t=0')
    plt.legend()

    plt.plot(points, solving[5], color='green', label='t=5t')
    plt.legend()

    plt.plot(points, solving[20], color='blue', label='t=20t')
    plt.legend()

    plt.plot(points, solving[199], color='black', label='t=200t')
    plt.title('задача 3: ')
    plt.legend()
    plt.grid(True)
    plt.show()

    def plot_3d():
        x = np.arange(a, b + h, h)
        y = np.arange(T1, T + tetta, tetta)

        xgrid, ygrid = np.meshgrid(x, y)
        fig = pylab.figure()
        axes = Axes3D(fig)
        axes.plot_surface(xgrid, ygrid, solving, rstride=4, cstride=4, cmap=cm.jet)
        pylab.show()

    plot_3d()
    solving = specified(a, b, 0, T, h, tetta, lambda x: math.sin(x) * (2 - x) / 5, lambda t: ua, lambda t: ub,
                        k, f, func_for_partition)

    plt.plot(points, solving[0], color='red', label='t=0')
    plt.legend()

    plt.plot(points, solving[5], color='green', label='t=5t')
    plt.legend()

    plt.plot(points, solving[20], color='blue', label='t=20t')
    plt.legend()

    plt.plot(points, solving[199], color='black', label='t=200t')
    plt.title('')
    plt.legend()
    plt.grid(True)
    plt.show()

    plot_3d()


def task_4():
    print('Задача № 4')
    a = -1
    b = 1
    ua = lambda t: 0
    ub = lambda t: 0
    u = lambda x: 0
    T = 10
    h = 0.1
    tetta = (h ** 2) / 4
    f = lambda x, t: x ** 2

    def specified(a, b, t_0, t_n, h, tetta, u, g1, g2, f, func_for_partition):
        columns = int((b - a) / h) + 1
        rows = int((t_n - t_0) / tetta) + 1
        solving = np.zeros((rows, columns))

        for index, value in enumerate(j for j in np.arange(a, b + h, h)):
            solving[0][index] = u(value)
        for index, value in enumerate(j for j in np.arange(t_0, t_n, tetta)):
            solving[index][0] = g1(value)
            solving[index][-1] = g2(value)

        for index_x, coord in enumerate((j for j in np.arange(a + h, b - h, h)), 1):
            for index_t, time in enumerate((j for j in np.arange(t_0 + tetta, t_n, tetta)), 1):
                solving[index_t][index_x] = func_for_partition(coord,
                                                               time - tetta,
                                                               solving[index_t - 1][index_x - 1],
                                                               solving[index_t - 1][index_x],
                                                               solving[index_t - 1][index_x + 1],
                                                               h,
                                                               tetta,
                                                               f)

        return solving

    def func3_for_partition_2(coord, time, T_prev, T_cur, T_next, h, tetta):
        return 2 * tetta / (h ** 2) * (T_next - 2 * T_cur + T_prev) + T_cur

    def func_for_partition_2(coord, time, T_prev, T_cur, T_next, h, tetta, f):
        return 0.05 * tetta / (h ** 2) * (T_next - 2 * T_cur + T_prev) + T_cur + tetta * f(
            coord, time)

    solving = specified(a, b, 0, T, h, tetta, u, ua, ub, f, func_for_partition_2)


    def plot_3d():
        x = np.arange(a, b + h, h)
        y = np.arange(0, T, tetta)

        xgrid, ygrid = np.meshgrid(x, y)
        fig = pylab.figure()
        axes = Axes3D(fig)
        print(len(x))
        print(len(y))
        print(len(solving[0]))
        print(len(solving))

        axes.plot_surface(xgrid, ygrid, solving, rstride=4, cstride=4, cmap=cm.jet)
        pylab.show()

    plot_3d()


task_1()
task_2()
task_3()
task_4()
