CC = g++-9
FLAGS = -std=c++17 
FILES = deck_of_cards.cpp deck_of_cards.h poker_player.cpp poker_player.h

all: poker

poker: $(FILES)
	$(CC) $(FLAGS) deck_of_cards.cpp poker_player.cpp -o poker

clean:
	rm -f prime_numbers big_switch sizeof_types luhn poker
