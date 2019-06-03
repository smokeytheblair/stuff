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
    DeckOfCards::ProcessArgs(argc, argv);

    DeckOfCards deck;

    deck.Shuffle();
    std::deque<PokerPlayer> players;

    for (size_t i=1; i<=DeckOfCards::numPlayers; i++)
    {
        PokerPlayer player("Player " + std::to_string(i), i);
        players.push_back(player);

        // std::cout << "Added " << player.GetName() << std::endl;
    }
/*    
    CARDS hand;

    Card card;
    card.Suit = SUITS[SPADES];
    card.Value = VALUES[SIX];
    hand.push_back(card);

    card.Value = VALUES[FIVE];
    hand.push_back(card);

    card.Value = VALUES[SEVEN];
    hand.push_back(card);

    card.Value = VALUES[EIGHT];
    hand.push_back(card);

    card.Value = VALUES[NINE];
    hand.push_back(card);
*/

    for (int i; i<DeckOfCards::handSize; i++)
    {
        for (PokerPlayer& player : players)    
        {
            Card card = deck.DrawCard();
            // std::cout << "Drawing card: " << card.Value << card.Suit << std::endl;

/*          if (1 == player.GetPlayerNumber())
            {
              player.ReceiveCard(hand.front());
              hand.pop_front();
            }
            else
*/          {            
              player.ReceiveCard(card);
            }
        }
    } 

    int player_num = 1;
    for (PokerPlayer& player : players)   
    {
        std::cout << player.GetName() << ": " << player.HandToString()// << std::endl;
                  << " \t: " << PokerPlayer::HandNameToString(player.EvaluateHand()) << std::endl;
    }

    return 0;
}