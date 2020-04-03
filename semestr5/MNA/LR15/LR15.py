import numpy as np
import matplotlib.pyplot as plt
import typing as tp
import scipy.sparse.linalg as spa_linalg

from math import *


width = 150
height = 90
radius = 15
thickness = 5
P = 80 * 10**9
E = 50
v = 0.33
function = lambda x, y: P / (E * thickness**3 / (12 * (1 - v**2)))


def solve(width: float, height: float, radius: float,
          function: tp.Callable[[float, float], float], step: float) -> np.array:
    cols_amount = int(ceil(width / step)) + 1
    rows_amount = int(ceil(height / step)) + 1

    total_equations_amount = cols_amount * rows_amount
    A = np.zeros((total_equations_amount, total_equations_amount))

    b = np.zeros(total_equations_amount)

    def get_mapped_index(i: int, j: int) -> int:
        return cols_amount * i + j

    def is_bound_point(i: int, j: int) -> bool:
        x, y = i * step, j * step
        if np.isclose(x, 0) or np.isclose(y, 0):
            return True
        elif x >= height or y >= width:
            return True
        elif x ** 2 + (y - width / 2) ** 2 <= radius ** 2:
            return True
        else:
            return False

    for i in range(rows_amount):
        for j in range(cols_amount):
            if not is_bound_point(i, j):
                A[get_mapped_index(i, j), get_mapped_index(i, j - 1)] = 1
                A[get_mapped_index(i, j), get_mapped_index(i, j + 1)] = 1
                A[get_mapped_index(i, j), get_mapped_index(i - 1, j)] = 1
                A[get_mapped_index(i, j), get_mapped_index(i + 1, j)] = 1
                A[get_mapped_index(i, j), get_mapped_index(i, j)] = -4

                b[get_mapped_index(i, j)] = function(i * step, j * step) * step ** 2
            else:
                A[get_mapped_index(i, j), get_mapped_index(i, j)] = 1

    solution = spa_linalg.cg(A, b)[0]
    return solution.reshape((rows_amount, cols_amount))


def plot_solution(solution: np.array, width: float, height: float, step: float):
    y = np.arange(0, height + step, step)
    x = np.arange(0, width + step, step)
    X, Y = np.meshgrid(x, y)

    fig = plt.figure(figsize=(10, 10))
    ax = plt.axes(projection='3d')
    ax.plot_surface(X, Y, solution, cmap='rainbow')
    plt.show()


if __name__ == '__main__':

    solution = solve(width, height, radius, function, 4)
    plot_solution(solution, width, height, 4)

    solution = solve(width, height, radius, function, 8)
    plot_solution(solution, width, height, 8)

    solution = solve(width, height, radius, function, 16)
    plot_solution(solution, width, height, 16)