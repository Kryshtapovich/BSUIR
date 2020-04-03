import numpy as np
np.set_printoptions(suppress = True, precision = 4, floatmode = "fixed")

def input():
    variant = 13
    C = np.array([[0.2, 0.0, 0.2, 0.0, 0.0], 
                  [0.0, 0.2, 0.0, 0.2, 0.0], 
                  [0.2, 0.0, 0.2, 0.0, 0.2], 
                  [0.0, 0.2, 0.0, 0.2, 0.0], 
                  [0.0, 0.0, 0.2, 0.0, 0.2]])

    D = np.array([[ 2.33,  0.81,  0.67,  0.92, -0.53], 
                  [ 0.81,  2.33,  0.81,  0.67,  0.92], 
                  [ 0.67,  0.81,  2.33,  0.81,  0.92], 
                  [ 0.92,  0.67,  0.81,  2.33, -0.53], 
                  [-0.53,  0.92,  0.92, -0.53,  2.33]])
    A = variant * C + D
    return A

A = input()
n = len(A)

EPS = 10.0 ** -4
ansV = np.eye(n)
while True:
    maxelem = (0, 1)
    for i in range(n):
        for j in range(i + 1, n):
            if (abs(A[i][j]) > abs(A[maxelem])):
                maxelem = (i, j)
    (i, j) = maxelem
    if (A[i][i] == A[j][j]):
        p = np.pi / 4
    else:
        p = 2 * A[i][j] / (A[i][i] - A[j][j])
    c = np.cos(1/2 * np.arctan(p))
    s = np.sin(1/2 * np.arctan(p))
    V = np.eye(n)
    V[i][i] = c
    V[i][j] = -s
    V[j][i] = s
    V[j][j] = c
    A = V.T @ A @ V 
    ansV = ansV @ V
    if ((A ** 2).sum() - (np.diag(A) ** 2).sum() < EPS):
        ansW = np.diag(A)
        break

A = input()

(W, V) = (ansW, ansV)
print("Вектор собственных значений:")
print(W)
print("Столбцы - собственные векторы:")
print(V)

print("Проверка:")
(W, V) = np.linalg.eig(A)
print(W)
print(V)