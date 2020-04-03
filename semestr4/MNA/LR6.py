import numpy as np
import math
import matplotlib as plot

p = [0.0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01]
m = 5.33
k = 13

data = [
    [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0],
    [p[i] + ((-1) ** k) * m for i in range(len(p))]
]

print(data)


def weight_coefficient(data_src=None, x=0, exclude=None, top_value=None):
    result = 1
    if top_value is None:
        top_value = len(data_src)
    for i in range(top_value):
        if i == exclude:
            continue
        result *= (x - data_src[0][i])
    return result


def lagrange_interpolation(_data_, x=0.1):
    result = 0
    for i in range(len(_data_)):
        result += _data_[1][i] * (
                    weight_coefficient(data_src=_data_, x=x, exclude=i) /
                    weight_coefficient(data_src=_data_, x=data[0][i], exclude=i))
    return result


def newton_interpolation(_data_, x=0.1):
    def _a_(_data=None, top_idx=None):
        result = 0
        for k in range(top_idx + 1):
            result += _data_[1][k] / weight_coefficient(data_src=_data_, x=_data[0][k],
            exclude=k, top_value=top_idx + 1)
        return result

    result = 0
    for i in range(len(_data_)):
        result += _a_(_data_, i) * weight_coefficient(data_src=_data_, x=x, top_value=i)
    return result


print(newton_interpolation(data, x=0.47))
print(lagrange_interpolation(data, x=0.47))
