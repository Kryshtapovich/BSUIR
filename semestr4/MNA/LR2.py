import numpy as np
from functools import reduce

np.set_printoptions(precision = 4, floatmode = 'fixed')

def jacobi(A, b, init_vector = None):
    B = np.eye(A.shape[0]) - A / np.diag(A).reshape(-1, 1)
    if min(np.linalg.norm(B, ord=norm) for norm in (np.inf, 1, 'fro')) >= 1:
        raise ValueError("Jacobi method cannot be performed")
    c = b / np.diag(A).reshape(-1, 1)
    if init_vector is None:
        c.dtype = float
        xk = c.copy()
    else:
        init_vector.dtype = float
        xk = init_vector.copy()
    k = 1
    while True:
        xk_1 = xk.copy()
        xk = B @ xk_1 + c
        error = np.linalg.norm(B) * np.linalg.norm(xk - xk_1) / (1 - np.linalg.norm(B))
        if error < 1e-3:
            break
        xk_1 = xk.copy()
        k += 1
    return xk

def gauss_zeidel(A, b, init_vector = None):
    B = np.eye(A.shape[0]) - A / np.diag(A).reshape(-1, 1)
    if min(np.linalg.norm(B, ord=norm) for norm in (np.inf, 1)) >= 1:
        raise ValueError("Gauss-Seidel method cannot be performed")
    c = (b / np.diag(A).reshape(-1,1)).reshape(-1)
    if init_vector is None:
        c.dtype = float
        xk = c.copy().reshape(-1)
    else:
        init_vector.dtype = float
        xk = init_vector.copy().reshape(-1)
    k = 1
    while True:
        xk_1 = xk.copy()
        for i in range(B.shape[0]):
            t = np.sum(B[i, :i] * xk[:i])
            m = np.sum(B[i, i:] * xk_1[i:])
            xk[i] = t + m + c[i]
        error = np.linalg.norm(B) * np.linalg.norm(xk - xk_1) / (1 - np.linalg.norm(B))
        if error < 1e-3:
            break
        k += 1
    return xk.reshape(-1, 1)

def compare_answers(func, arg = None):
    _true_x = (np.linalg.inv(A) @ b).reshape(-1)
    print(f"{'True answer':<45} : {_true_x},\n{func.__name__ + ' answer':<45}:" 
    + f"{(func(A, b) if arg is None else func(A, b, arg)).reshape(-1)}")

k = 13

C = np.array([[0.01,     0, -0.02,    0,     0],
              [0.01,  0.01, -0.02,    0,     0],
              [   0,  0.01,  0.01,    0, -0.02],
              [   0,     0,  0.01, 0.01,     0],
              [   0,     0,     0, 0.01,  0.01]], dtype = float)

D = np.array([[ 1.33,  0.21,  0.17,  0.12, -0.13],
              [-0.13, -1.33,  0.11,  0.17,  0.12],
              [ 0.12, -0.13, -1.33,  0.11,  0.17],
              [ 0.17,  0.12, -0.13, -1.33,  0.11],
              [ 0.11,  0.67,  0.12, -0.13, -1.33]], dtype = float)

b = np.array([[1.2], [2.2], [4.0], [0.0], [-1.2]], dtype = float)

A = np.add(np.multiply(C, k), D)

for method in (jacobi, gauss_zeidel):
    compare_answers(method)
    print()
