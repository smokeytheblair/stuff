import sys
import math
from numpy import arange
from datetime import *


def print_usage(name):
    print('python3 {} <max_number>'.format(name))

def create_number_list(max: int):
    numbers = arange(1, max, 2)
    return numbers

def mark_multiples_of_prime(numbers, prime_index: int, max: int):
    # print('Checking prime:{}'.format(prime))
    
    for i in range(prime_index,len(numbers),numbers[prime_index]):
        if (i<len(numbers) and i>prime_index):
            numbers[i] = 0

def compute_primes(max: int):
    start_time = datetime.now()

    numbers = create_number_list(max)

    # print('Numbers = {}'.format(numbers))

    print('Computing primes from 0 to {}'.format(max))

    for index in range(int(1), int(len(numbers)/2)):
        if (numbers[index] > 1):
            # print('index: {}, prime: {}'.format(index, numbers[index]))
            mark_multiples_of_prime(numbers, index, max)

    primes = [i for i in numbers if i>0]

    mid_time = datetime.now()

    # print('Primes = {}'.format(primes))

    finish_time = datetime.now()

    print('Start: {}, Mid: {}, Finish: {}'.format(start_time, mid_time, finish_time))
    print('Compute time: {}. \nFound {} prime numbers less than {}'.format(mid_time - start_time, len(primes), max))
    # print('Print time: {}'.format(finish_time - mid_time))

def main():
    if (len(sys.argv) > 1):
        compute_primes(int(sys.argv[1]))
    else:
        print_usage(sys.argv[0])


if __name__ == "__main__":
    main()
