from scipy.integrate import odeint
import numpy
from matplotlib import pylab
a = 0
b = 1
y0 = 0
epsilon = 0.0001


def f(y, x):
    return (0.9*(1-y**2))/((1+1.0)*(x**2)+(y**2)+1)


def runge_kutta(x, step):
    if x <= a:  
        return y0
    prev_x = x - step
    prev_y = runge_kutta(prev_x, step)
    F1 = f(prev_y, prev_x)
    F2 = f(prev_y + (step / 2) * F1, prev_x + step / 2)
    F3 = f(prev_y + (step / 2) * F2, prev_x + step / 2)
    F4 = f(prev_y + step * F3, x)
    return prev_y + step * (F1 + 2 * F2 + 2 * F3 + F4) / 6
    

def find_step(epsilon):
    h0 = epsilon ** (1/4)
    n = int((b - a) // h0)
    if n % 2 != 0 :
        n += 1
    while check_step(n, epsilon):
        n = n // 4 * 2
    while not check_step(n, epsilon):
        n += 2
    return (b - a) / n


def check_step(n, epsilon):
    h = (b - a) / n     
    y2 = runge_kutta(a + 2 * h, h)
    y2e = runge_kutta(a + 2 * h, h * 2)
    eps = (1/15) * abs(y2 - y2e)
    return eps < epsilon


step = find_step(epsilon)


def accurate_solution(x):
    sol = odeint(f, y0, [a, x])
    return sol[1][0]


def plot_curve(xlist, ylist, text):
    pylab.cla()
    pylab.plot (xlist, ylist, label = text)
    pylab.grid(True)
    pylab.legend()
    pylab.show()


def show_curve(method, step, text):
    xlist = numpy.arange(a, b + step, step)
    ylist = []
    x = a
    while x <= b:
        r = method(x, step)
        ylist.append(r)
        x += step
    plot_curve(xlist, ylist, text)
    print(f"{text}")
    print(ylist)
    ylist2 = ylist
    ylist = []
    x = a
    while x <= b:
        r = accurate_solution(x)
        ylist.append(r)
        x += step
    plot_curve(xlist, ylist, "Точное решение")
    print("Точное решение")
    print(ylist)
    rez = []
    for item in range(len(ylist)):
        rez.append(abs(ylist[item]-ylist2[item]))
    print(f"Погрешность между зачениями: {rez}")


def adams(x, step):
    if x <= a:
        return y0
    prev = runge_kutta(x - step, step)
    prevprev = runge_kutta(x - step * 2, step)
    predictor = prev + (step / 2) * (3 * f(prev, x - step) - f(prevprev, x - step * 2))
    corrector = prev + (step / 2) * (f(prev, x - step) + f(predictor, x))
    return corrector


show_curve(adams, step, "Метод Адамса") 