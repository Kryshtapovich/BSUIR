import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate

def split(a, b, nodes):
    x = list(range(nodes))
    h = (b - a) / (nodes)
    for i in range(nodes):
        x[i] = a + i * h
    return x


a = 0
b = 4
nodes = 5
x = np.array(split(a, b, nodes))
y = np.sqrt(x)
tck = interpolate.splrep(x, y, s=0)

print('\nЗначение в точке (b - a) / 2 = 2 (через сплайн):', interpolate.splev((b - a) / 2, tck, der=0).round(6))
print('Значение в точке (b - a) / 2 = 2 (через функцию):',  (np.sqrt((b - a) / 2)).round(6))
print('\nЗначение в точке 2 (через сплайн):', interpolate.splev(2, tck, der=0).round(6))
print('Значение в точке 2 (через функцию):', (np.sqrt(2)).round(6))

xnew = np.arange(0, 4, 1/20)
ynew = interpolate.splev(xnew, tck, der=0)
plt.figure()
plt.plot(x, y, 'x', xnew, ynew, linewidth=3)
plt.plot(xnew, (np.sqrt(xnew)), linewidth=1, color='b')
plt.legend(['Узлы', 'Кубический сплайн', 'Функция sqrt(x)'])
plt.show()
