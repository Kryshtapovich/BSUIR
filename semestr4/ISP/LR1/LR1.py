def factorial(num):
    if num == 0:
        return 1
    else:
        return num * factorial(num - 1)

try:
    number = int(input('Enter the number: '))
    print(number, '! =', factorial(number))
except ValueError:
    print('Error!')
