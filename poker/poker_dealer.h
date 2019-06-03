#ifndef POKER_DEALER_H
#define POKER_DEALER_H

#include <deque>

#include "deck_of_cards.h"
#include "poker_player.h"

class PokerDealer
{
public: 
    PokerDealer(DeckOfCards&, std::deque<PokerPlayer>&);
    ~PokerDealer();

    void DealCards();
    Card DealCard();
    std::deque<PokerPlayer>& GetPlayers() {return players;}

    static void ProcessArgs(int argc, char* argv[]);

    static int handSize;
    static int numPlayers;
    static int numDecks;
    static int INCLUDE_JOKERS;

private:    
    DeckOfCards& deck;
    std::deque<PokerPlayer>& players;
};

#endif //POKER_DEALER_H