#include "poker_dealer.h"
#include "poker_player.h"
#include "deck_of_cards.h"

#include <getopt.h>
#include <deque>


PokerDealer::PokerDealer()
{

}

PokerDealer::~PokerDealer()
{

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
            {"jokers", no_argument, &DeckOfCards::INCLUDE_JOKERS, 'j'},
            {0,0,0,0}  
        };

        int option_index = 0;
        int c;

        while((c = getopt_long(argc, argv, "n:", long_options, &option_index)) != -1)
        {
            switch (c)
            {
                case 0:
                    if (0 < DeckOfCards::INCLUDE_JOKERS)
                    {
                        std::cout << "Including Jokers." << std::endl;
                    }
                break;
                case 'd':
                    if (long_options[option_index].has_arg)
                    {
                        DeckOfCards::numDecks = std::stoi(optarg);
                        std::cout << "Using " << DeckOfCards::numDecks << " deck(s)." << std::endl;
                    }
                break;
                case 'n':
                    if (long_options[option_index].has_arg)
                    {
                        DeckOfCards::handSize = std::stoi(optarg);
                        std::cout << "Being told to draw " << DeckOfCards::handSize << " cards." << std::endl;
                    }

                break;
                case 'p':
                    if (long_options[option_index].has_arg)
                    {
                        DeckOfCards::numPlayers = std::stoi(optarg);
                        std::cout << "There are " << DeckOfCards::numPlayers << " players." << std::endl;
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