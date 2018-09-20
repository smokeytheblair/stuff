prime_numbers: prime_numbers.c
	clang -O2 prime_numbers.c -o prime_numbers

clean:
	rm prime_numbers
