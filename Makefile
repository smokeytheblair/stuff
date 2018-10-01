CC = clang
FLAGS = -O2 
FILES = prime_numbers.c

all: prime_numbers big_switch

prime_numbers: $(FILES)
	$(CC) $(FLAGS) $(FILES) -o prime_numbers

big_switch: big_switch.c
	$(CC) $(FLAGS) big_switch.c -o big_switch

clean:
	rm -f prime_numbers big_switch
