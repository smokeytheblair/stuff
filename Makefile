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
