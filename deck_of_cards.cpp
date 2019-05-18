#include <deque>
#include <iostream>
#include <algorithm>
#include <locale>
#include <ctime>
#include <experimental/random>
#include <getopt.h>

#include "deck_of_cards.h"

DeckOfCards::DeckOfCards()
{
    uint16_t num_suits = sizeof(SUITS)/sizeof(std::string);
    uint16_t num_values = sizeof(VALUES)/sizeof(std::string);

    // std::wcout << L"User-preferred locale setting is " << std::locale("").name().c_str() << std::endl;
    // std::locale::global(std::locale("en_US.UTF-8"));
    // std::wcout.imbue(std::locale());

    std::wcout  << L"Building a deck of cards.\n"
                << L"Suits: " << num_suits << L"\n"
                << L"Values: " << num_values
                << std::endl;

    for( int i=0; i<num_suits; i++)
    {
        for( int j=0; j<num_values; j++)
        {
            // std::cout << VALUES[j] << SUITS[i] << std::endl;

            Card card;
            card.Suit = SUITS[i];
            card.Value = VALUES[j];
            // std::cout << "Adding card: " << card.Value << card.Suit << std::endl;

            myCards.push_back(card);
        }
    }

    std::wcout << L"Deck has " << myCards.size() << std::endl;   
}

DeckOfCards::~DeckOfCards()
{

}

void DeckOfCards::PrintCards(CARDS cards)
{
    for (CARDS::iterator i = cards.begin(); i != cards.end(); i++)
    {
        Card* card = &(*i);
        std::cout << card->Value << card->Suit << " ";
    }
    std::cout << std::endl;
}

CARDS DeckOfCards::DrawCards(int num)
{
    std::wcout << L"Drawing " << num << L" cards." << std::endl;

    CARDS hand;

    hand.insert(hand.begin(), myCards.begin(), myCards.begin() + num);

    std::wcout << L"Return hand of " << hand.size() << L" cards." << std::endl;

    return hand;
}

void DeckOfCards::Shuffle()
{
    auto shuffler = [=] 
    {
        int shuffles = std::experimental::randint(17, 51);

        for(int i=0; i<shuffles; i++)
        {
            std::srand(std::time(nullptr));
            uint32_t seed = std::rand();
            std::shuffle(myCards.begin(), myCards.end(), std::default_random_engine(seed));
            std::random_shuffle(myCards.begin(), myCards.end());
        }
    };

    shuffler();
}

int main(int argc, char* argv[])
{
    int num_cards_to_draw = 5;

    if (1 < argc)
    {
        static struct option long_options [] =
        {
            {"num-cards", required_argument, 0, 'n'}    
        };

        int option_index = 0;
        int c;

        while((c = getopt_long(argc, argv, "hn:", long_options, &option_index)) != -1)
        {
            switch (c)
            {
                case 'n':
                    if (long_options[option_index].has_arg)
                    {
                        num_cards_to_draw = long_options[option_index].val;
                        std::cout << "Being told to draw " << num_cards_to_draw << " cards." << std::endl;
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
    
    DeckOfCards deck;

    deck.Shuffle();
    deck.PrintCards(deck.DrawCards(num_cards_to_draw));

    return 0;
}