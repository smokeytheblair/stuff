CC = clang
FLAGS = -O2 
FILES = prime_numbers.c

prime_numbers: $(FILES)
	$(CC) $(FLAGS) $(FILES) -o prime_numbers

clean:
	rm -f prime_numbers
