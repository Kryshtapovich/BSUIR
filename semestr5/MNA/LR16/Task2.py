import math
import numpy as np
import chart_studio.plotly as py
import plotly.graph_objs as graph_objs
import plotly
import time

a = 2
b = 2
T = 4

p = lambda x, y: 2 * np.cos(np.pi * x / a)
q = lambda x, y: np.tan(np.sin(2 * np.pi * x / a)) * np.sin(np.pi * y / b)

def solve(NX, NY, M, build_plot=False):
    tau = T / M
    hx = a / NX
    hy = b / NY
    C = tau / hx + tau / hy 
    
    x_values = np.linspace(-a / 2, a / 2, NX)
    y_values = np.linspace(-b / 2, b / 2, NY)
    matrix = np.zeros((M, NX, NY))

    for i in range(NX):
        for j in range(NY):
            matrix[0][i][j] = p(x_values[i], y_values[j])
            
    for i in range(1, NX - 1):
        for j in range(1, NY - 1):
            matrix[1][i][j] = p(x_values[i], y_values[j]) + q(x_values[i], y_values[j]) * tau
            matrix[1][i][j] += tau ** 2 / (2 * hx ** 2) * (matrix[0][i + 1][j] - 2 * matrix[0][i][j] + matrix[0][i - 1][j])
            matrix[1][i][j] += tau ** 2 / (2 * hy ** 2) * (matrix[0][i][j + 1] - 2 * matrix[0][i][j] + matrix[0][i][j - 1])
            
    matrix[1, 1:-1, 0] = matrix[1, 1:-1, 1]
    matrix[1, 1:-1, -1] = matrix[1, 1:-1, -2]
    
    for t in range(1, M - 1):
        matrix[t + 1, 1:-1, 1:-1] = 2 * matrix[t, 1:-1, 1:-1] - matrix[t-1, 1:-1, 1:-1] 
        matrix[t + 1, 1:-1, 1:-1] += tau ** 2 / hx ** 2 * (matrix[t, :-2, 1:-1]- 2 * matrix[t, 1:-1, 1:-1] + matrix[t, 2:, 1:-1])
        matrix[t + 1, 1:-1, 1:-1] += tau ** 2 / hy ** 2 * (matrix[t, 1:-1, :-2] - 2 * matrix[t, 1:-1, 1:-1] + matrix[t, 1:-1, 2:])
        matrix[t + 1, 1:-1, 0] = matrix[t + 1, 1:-1, 1]
        matrix[t + 1, 1:-1, -1] = matrix[t + 1, 1:-1, -2]

    for i in range(0, M, 999):
        x_grid, y_grid = np.meshgrid(x_values, y_values)
        surface = graph_objs.Surface(x=x_grid, y=y_grid, z=matrix[i])

        fig = graph_objs.Figure([surface])
        plotly.offline.plot(fig, auto_open=True)

        time.sleep(0.5)

solve(100, 100, 4000, build_plot=True)