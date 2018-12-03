CC = g++
FLAGS = -O2 
FILES = prime_numbers.cpp

all: prime_numbers big_switch sizeof_types

prime_numbers: $(FILES)
	$(CC) $(FLAGS) $(FILES) -o prime_numbers

big_switch: big_switch.cpp
	$(CC) $(FLAGS) big_switch.cpp -o big_switch
	
sizeof_types: sizeof_types.cpp
	$(CC) $(FLAGS) -std=c++17 sizeof_types.cpp -o sizeof_types

luhn: luhn.cpp
	$(CC) $(FLAGS) luhn.cpp -o luhn

clean:
	rm -f prime_numbers big_switch sizeof_types luhn

cpp_primes: prime_numbers
	@echo '=========================='
	@echo 'testing 1,000'
	- ./prime_numbers 1000
	@echo '=========================='
	@echo 'testing 10,000'
	- ./prime_numbers 10000
	@echo '==========================' 
	@echo 'testing 100,000'
	- ./prime_numbers 100000
	@echo '=========================='
	@echo 'testing 1,000,000'
	- ./prime_numbers 1000000
	@echo '=========================='
	@echo 'testing 10,000,000'
	- ./prime_numbers 10000000
	@echo '=========================='
	@echo 'testing 100,000,000'
	- ./prime_numbers 100000000
	@echo '=========================='
	@echo 'testing 1,000,000,000'
	- ./prime_numbers 1000000000
	@echo '=========================='
	@echo 'testing 10,000,000,000'
	- ./prime_numbers 10000000000

py_primes: 
	@echo '=========================='
	@echo 'testing 1,000'
	- python3 prime_numbers.py 1000
	@echo '=========================='
	@echo 'testing 10,000'
	- python3 prime_numbers.py 10000
	@echo '==========================' 
	@echo 'testing 100,000'
	- python3 prime_numbers.py 100000
	@echo '=========================='
	@echo 'testing 1,000,000'
	- python3 prime_numbers.py 1000000
	@echo '=========================='
	@echo 'testing 10,000,000'
	- python3 prime_numbers.py 10000000
	@echo '=========================='
	@echo 'testing 100,000,000'
	- python3 prime_numbers.py 100000000
	@echo '=========================='
	@echo 'testing 1,000,000,000'
	- python3 prime_numbers.py 1000000000
	@echo '=========================='
	@echo 'testing 10,000,000,000'
	- python3 prime_numbers.py 10000000000

jl_primes: 
	@echo '=========================='
	@echo 'testing 1,000'
	- julia prime_numbers.jl  1000
	@echo '=========================='
	@echo 'testing 10,000'
	- julia prime_numbers.jl 10000
	@echo '==========================' 
	@echo 'testing 100,000'
	- julia prime_numbers.jl 100000
	@echo '=========================='
	@echo 'testing 1,000,000'
	- julia prime_numbers.jl 1000000
	@echo '=========================='
	@echo 'testing 10,000,000'
	- julia prime_numbers.jl 10000000
	@echo '=========================='
	@echo 'testing 100,000,000'
	- julia prime_numbers.jl 100000000
	@echo '=========================='
	@echo 'testing 1,000,000,000'
	- julia prime_numbers.jl 1000000000
	@echo '=========================='
	@echo 'testing 10,000,000,000'
	- julia prime_numbers.jl 10000000000

js_primes: 
	@echo '=========================='
	@echo 'testing 1,000'
	- node prime_numbers.js 1000
	@echo '=========================='
	@echo 'testing 10,000'
	- node prime_numbers.js 10000
	@echo '==========================' 
	@echo 'testing 100,000'
	- node prime_numbers.js 100000
	@echo '=========================='
	@echo 'testing 1,000,000'
	- node prime_numbers.js 1000000
	@echo '=========================='
	@echo 'testing 10,000,000'
	- node prime_numbers.js 10000000
	@echo '=========================='
	@echo 'testing 100,000,000'
	- node prime_numbers.js 100000000
	@echo '=========================='
	@echo 'testing 1,000,000,000'
	- node prime_numbers.js 1000000000
	@echo '=========================='
	@echo 'testing 10,000,000,000'
	- node prime_numbers.js 10000000000
