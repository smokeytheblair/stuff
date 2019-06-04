#include "poker_dealer.h"
#include "poker_player.h"
#include "deck_of_cards.h"

#include <getopt.h>
#include <deque>

int PokerDealer::handSize = 5;
int PokerDealer::numPlayers = 1;
int PokerDealer::numDecks = 1;


PokerDealer::PokerDealer(DeckOfCards& newDeck, std::deque<PokerPlayer>& newPlayers)
    : deck(newDeck),
      players(newPlayers)
{

}

PokerDealer::~PokerDealer()
{

}

Card PokerDealer::DealCard()
{
    return (deck.DrawCard());
}

void PokerDealer::DealCards()
{
    // std::cout << "Dealing " << PokerDealer::handSize << " cards to " << players.size() << " players." << std::endl;

    for (int i=0; i<PokerDealer::handSize; i++)
    {
        for (PokerPlayer& player : players)    
        {
            player.ReceiveCard(deck.DrawCard());
        }
    } 
}

void PokerDealer::ProcessArgs(int argc, char* argv[])
{
     if (1 < argc)
    {
        static struct option long_options [] =
        {
            {"num-cards", required_argument, 0, 'n'},
            {"decks", required_argument, 0, 'd'},
            {"players", required_argument, 0, 'p'},
            {0,0,0,0}  
        };

        int option_index = 0;
        int c;

        while((c = getopt_long(argc, argv, "n:", long_options, &option_index)) != -1)
        {
            switch (c)
            {
                case 0:
                break;
                case 'd':
                    if (long_options[option_index].has_arg)
                    {
                        PokerDealer::numDecks = std::stoi(optarg);
                        std::cout << "Using " << PokerDealer::numDecks << " deck(s)." << std::endl;
                    }
                break;
                case 'n':
                    if (long_options[option_index].has_arg)
                    {
                        PokerDealer::handSize = std::stoi(optarg);
                        std::cout << "Being told to draw " << PokerDealer::handSize << " cards." << std::endl;
                    }

                break;
                case 'p':
                    if (long_options[option_index].has_arg)
                    {
                        PokerDealer::numPlayers = std::stoi(optarg);
                        std::cout << "There are " << PokerDealer::numPlayers << " players." << std::endl;
                    }
                break;
                case 'h':
                case '?':
                    std::cout << "Help message." << std::endl;
                break;
                default:
                break;
            }
        }
    }
    else
    {
        /* code */
    }

    return;
}