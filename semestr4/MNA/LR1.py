import numpy

def default_gauss(matrix, b):
    a = numpy.copy(matrix)
    b = numpy.copy(b)
    n = len(b)

    for k in range (0, n - 1):
        for i in range(k + 1, n):
            if a[i, k] != 0.0:
                div = a[i, k] / a[k, k]
                a[i, k + 1 : n] -= div * a[k, k + 1 : n]
                b[i] -= div * b[k]

    for k in range(n - 1, -1, -1):
        b[k] = (b[k] - numpy.dot(a[k, k + 1 : n], b[k + 1 : n])) / a[k, k]

    print(b)

def gauss_via_columns(matrix, b):
    a = numpy.copy(matrix)
    b = numpy.copy(b)
    n = len(b)
    s = numpy.zeros(n); 

    for i in range (n):
        s[i] = max(numpy.abs(a[i, :]))

    for k in range (0, n - 1):

        p = numpy.argmax(numpy.abs(a[k : n, k]) / s[k : n])

        if p != k:
            a[[k, p + k], :] = a[[p + k, k], :]
            b[k], b[p + k] = b[p + k], b[k] 
            s[k], s[p + k] = s[p + k], s[k]

        for i in range(k + 1, n):
            if a[i, k] != 0.0:
                div = a[i, k] / a[k, k]
                a[i, k : n] -= div * a[k, k : n]
                b[i] -= div * b[k]

    x = numpy.zeros_like(b)
    x[n - 1] = b[n - 1] / a[n - 1, n - 1]
    for k in range(n - 2, -1, -1):
        x[k] = (b[k] - numpy.dot(a[k, k + 1 : n], x[k + 1 : n])) / a[k, k]

    print(x)
    
numpy.set_printoptions(precision = 4, floatmode = 'fixed')
k = 13.0

C = numpy.array([[0.2,   0,   0.2,    0,    0],
                 [  0,  0.2,    0,  0.2,    0],
                 [0.2,    0,  0.2,    0,  0.2],
                 [  0,  0.2,    0,  0.2,    0],
                 [  0,    0,  0.2,    0,  0.2]], dtype = numpy.float64)

D = numpy.array([[ 2.33,  0.81,  0.67,  0.92, -0.53],
                 [-0.53,  2.33,  0.81,  0.67,  0.92],
                 [ 0.92, -0.53,  2.33,  0.81,  0.67],
                 [ 0.67,  0.92, -0.53,  2.33,  0.81],
                 [ 0.81,  0.67,  0.92, -0.53,  2.33]], dtype = numpy.float64)

b = numpy.array([4.2, 4.2, 4.2, 4.2, 4.2], dtype = numpy.float64)

A = numpy.add(numpy.multiply(C, k), D)
print('A-matrix:\n', A, '\n\n')

print('First method(default)\nX-vector:')
default_gauss(A, b)
print('\n')
print('Second method(columns)\nX-vector:')
gauss_via_columns(A, b)
print('\n')
