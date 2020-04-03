from collections import namedtuple

"""
simple lists
"""
lst1 = ['a', 2, 'c']
lst2 = [1, 2, 3, 4]

"""
simple dictionary
"""
dict1 = {'a': 1, 'b': 2}
exp_dict = namedtuple('object', ['a', 'b'])(*[1, 2])


class MyClass:
    def __init__(self):
        self.a = 'a'
        self.b = 1


"""
simple object
"""
obj1 = MyClass()
exp_obj1 = namedtuple('object', ['a', 'b'])(*['a', 1])

"""
complex object
"""
obj2 = MyClass()
obj2.c = obj1
exp_obj2 = namedtuple('object', ['a', 'b', 'c'])(*['a', 1, namedtuple('object', ['a', 'b'])(*['a', 1])])

"""
object list
"""
obj_lst = [obj1, obj2]
exp_obj_lst = [exp_obj1, exp_obj2]

"""
object dict
"""
obj_dict = {'obj1': obj1, 'obj2': obj2}
exp_obj_dict = namedtuple('object', ['obj1', 'obj2'])(*[exp_obj1, exp_obj2])

"""
simple function
"""
def hello():
    return 'Hello, world!'


exp_hello = 'Hello, world!'

"""
global variable
"""
name = 'Misha'

"""
function using globals variable
"""
def say_hello():
    return 'Hello, ' + name


exp_say_hello = 'Hello, Misha'

"""
function with parameters
"""
json_file = 'func.json'
pickle_file = 'func.pickle'

def add(a, b):
    return a + b


exp_add = 5

"""
recursive function
"""
def factorial(num):
    if num == 0:
        return 1
    else:
        return num * factorial(num - 1)


exp_factorial = 120

"""
lambda
"""
power = lambda num, p: num ** p
exp_power = 8
