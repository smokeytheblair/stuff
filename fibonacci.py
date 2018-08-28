# compute fibonacci sequence up to max value passed in 
# also compute the y' and y" to identify that the sequence
# approaches the golden ratio
#
# https://en.wikipedia.org/wiki/Golden_ratio


import sys
import math
from decimal import Decimal
from decimal import *

getcontext().prec = 75

def print_usage(name):
    print('python3 {} <max number>'.format(name))
    golden_ratio()

def golden_ratio():
    golden = (Decimal(1) + Decimal(5).sqrt()) / Decimal(2)
    print(f'Golden Ratio : {golden}')

def fib(num):
    golden_ratio()
    print('{: <30} |  {: <76} | {: <76}'.format('Fibonacci', 'y\'', 'y\"'))
    print(''.center(30, '=') + ' | '.ljust(80, '=') + ' | '.ljust(80, '='))
    fib_worker(0, 1, 1, num)

def fib_worker(last, current, last_ratio,  max):
    if (current < max):
        temp = current
        current = current + last
        last = temp
        ratio = Decimal(current)/Decimal(last) 
        diff = Decimal(ratio) - Decimal(last_ratio)
        print('{: <30} |  {: <76} | {: <76}'.format(current, ratio, diff))
        fib_worker(last, current, ratio, max)

def main():
    if (len(sys.argv) > 1):
        fib(Decimal(sys.argv[1]))
    else:
        print_usage(sys.argv[0])

if __name__ == "__main__":
    main()
