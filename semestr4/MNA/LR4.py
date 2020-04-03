from numpy.lib import math
import matplotlib.pyplot as plt
import numpy as np


def iter_method():

    x = 0.9
    y = 0.4
    dif = 1

    k = 0
    X = x
    Y = y
    while dif > 0.0001:
        y = np.sqrt((1 - 0.7 * (X ** 2)) / 2)
        x = np.sqrt(np.tan(X * Y + 0.2))
        dif = np.abs(x - X)
        X = x
        Y = y
        k += 1
    return x, y, k

def jacobian(x, y):
    J = [[0, 0], [0, 0]]
    J[0][0] = y / ((np.cos(x * y + 0.2)) ** 2) - 1
    J[0][1] = x / ((np.cos(x * y + 0.2)) ** 2)
    J[1][0] = 1.4 * x
    J[1][1] = 4 * y
    return J

def newton_method():

    k = 0
    x = 0.9
    y = 0.4
    dif = 1

    while dif > 0.0001:
        j = np.array(np.linalg.inv(jacobian(x, y)))
        mas = np.array([np.tan(x * y + 0.2) - x ** 2, 0.7 * (x ** 2) + 2 * (y ** 2) - 1])
        res = mas.dot(j)
        x1 = x
        x -= res[0]
        y -= res[1]
        dif = np.abs(x - x1)
        k += 1
    return x, y, k

def plot_method():
    x = np.arange(-1.5, 1.5, 0.1)
    y = np.arange(-1.5, 1.5, 0.1)

    a = np.tan(x * y + 0.2) - x
    b = 0.7 * (x ** 2) + 2 * (y ** 2) - 1

    plt.plot(a)
    plt.plot(b)
    plt.show()

iter_res = iter_method()
newton_res = newton_method()
plot_method()

print(f"Метод простых итераций: x = {iter_res[0]}, y = {iter_res[1]} n = {iter_res[2]} шагов")
print(f"Метод Ньютона: x = {newton_res[0]}, y = {newton_res[1]} n = {newton_res[2]} шагов")
