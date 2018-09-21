CC = clang

prime_numbers: prime_numbers.c
	$(CC) -O2 prime_numbers.c -o prime_numbers

clean:
	rm -f prime_numbers
