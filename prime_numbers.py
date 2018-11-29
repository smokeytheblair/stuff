# compute primes up to max number using the Sieve algorithm
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
#

import sys
import math
import numpy as np
# from numpy import ones, dtype, np.bool
from datetime import *


def print_usage(name):
    print('python3 {} <max_number>'.format(name))

def create_boolean_list(max: int):
    numbers = np.ones(int(max/2), dtype=np.bool)
    numbers[1] = False
    return numbers

def mark_multiples_of_prime(numbers, prime_index: int, max: int):
    prime = (prime_index*2)-1
    array_length = len(numbers)
    
    # print('Checking prime:{}'.format(prime))

    # the for loop will start at one multiple past the current prime
    # it will walk the list of numbers by multiples of prime
    # this logic removes the need for any if statements inside the loop
    for i in range(prime_index+prime, array_length, prime):
        numbers[i] = False

def compute_primes(max: int):
    start_time = datetime.now()

    numbers = create_boolean_list(max)

    # print('Numbers = {}'.format(numbers))

    print('Computing primes from 0 to {}'.format(max))

    half_length = int(len(numbers)/2)

    for index in range(int(1), half_length):
        if (numbers[index] ==  True):
            # print('index: {}, prime: {}'.format(index, (index*2)-1))
            mark_multiples_of_prime(numbers, index, max)

    primes = [i for i in numbers if i == True]

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
