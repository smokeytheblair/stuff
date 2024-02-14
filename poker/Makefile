CC = g++
FLAGS = -std=c++17 
CPP_FILES = main.cpp deck_of_cards.cpp poker_player.cpp poker_dealer.cpp
H_FILES = deck_of_cards.h poker_player.h poker_dealer.h
FILES = $(CPP_FILES) $(H_FILES)

all: poker

poker: $(FILES)
	$(CC) $(FLAGS) $(CPP_FILES) -o poker

clean:
	rm -f poker
