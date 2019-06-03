#include <deque>
#include <iostream>
#include <algorithm>
#include <locale>
#include <ctime>
#include <experimental/random>
#include <getopt.h>

#include "deck_of_cards.h"
#include "poker_player.h"
#include "poker_dealer.h"


int main(int argc, char* argv[])
{
    PokerDealer::ProcessArgs(argc, argv);

    DeckOfCards deck(PokerDealer::numDecks, 0 != PokerDealer::INCLUDE_JOKERS);

    deck.Shuffle();
    std::deque<PokerPlayer> players;

    for (size_t i=1; i<=PokerDealer::numPlayers; i++)
    {
        PokerPlayer player("Player " + std::to_string(i), i);
        players.push_back(player);
    }

    PokerDealer dealer(deck, players);

    dealer.DealCards();

    for (PokerPlayer& player : dealer.GetPlayers())   
    {
        std::cout << player.GetName() << ": " << player.HandToString()// << std::endl;
                  << " \t: " << PokerPlayer::HandNameToString(player.EvaluateHand()) << std::endl;
    }

    return 0;
}