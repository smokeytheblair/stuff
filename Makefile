CC = clang
FLAGS = -O2 
FILES = prime_numbers.c

all: prime_numbers big_switch sizeof_types

prime_numbers: $(FILES)
	$(CC) $(FLAGS) $(FILES) -o prime_numbers

big_switch: big_switch.c
	$(CC) $(FLAGS) big_switch.c -o big_switch
	
sizeof_types: sizeof_types.cpp
	$(CC) $(FLAGS) -std=c++17 sizeof_types.cpp -o sizeof_types

clean:
	rm -f prime_numbers big_switch sizeof_types
