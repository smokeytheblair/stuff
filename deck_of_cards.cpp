#include <deque>
#include <iostream>
#include <algorithm>
#include <locale>
#include <ctime>
#include <experimental/random>
#include <getopt.h>

#include "deck_of_cards.h"
#include "poker_player.h"

int DeckOfCards::handSize = 5;
int DeckOfCards::numPlayers = 1;
int DeckOfCards::numDecks = 1;

uint16_t DeckOfCards::NUM_SUITS = sizeof(SUITS)/sizeof(std::string);
uint16_t DeckOfCards::NUM_VALUES = sizeof(VALUES)/sizeof(std::string);
int      DeckOfCards::INCLUDE_JOKERS = false;

DeckOfCards::DeckOfCards()
{

    // std::wcout  << L"Building a deck of cards.\n"
    //             << L"Suits: " << NUM_SUITS << L"\n"
    //             << L"Values: " << NUM_VALUES
    //             << std::endl;



    for (int num_decks = 0; num_decks<DeckOfCards::numDecks; num_decks++)
    {
        if (0 < INCLUDE_JOKERS)
        {
            Card card;
            card.Value = JOKERS[0];
            myCards.push_back(card);

            card.Value = JOKERS[1];
            myCards.push_back(card);
        }

        for( int i=0; i<NUM_SUITS; i++)
        {
            for( int j=0; j<NUM_VALUES; j++)
            {
                // std::cout << VALUES[j] << SUITS[i] << std::endl;

                Card card;
                card.Suit = SUITS[i];
                card.Value = VALUES[j];
                // std::cout << "Adding card: " << card.Value << card.Suit << std::endl;

                myCards.push_back(card);
            }
        }
    }
    std::wcout << L"Deck has " << myCards.size() << std::endl;   
}

DeckOfCards::~DeckOfCards()
{

}

void DeckOfCards::PrintCards(CARDS cards)
{
    for (Card card : cards)
    {
        std::cout << card.Value << card.Suit << " ";
    }
    std::cout << std::endl;
}

Card DeckOfCards::DrawCard()
{
    return (DrawCards(1)[0]);
}

CARDS DeckOfCards::DrawCards(int num)
{
    // std::wcout << L"Drawing " << num << L" cards." << std::endl;

    CARDS hand;

    if (myCards.size() < num)
    {
        num = myCards.size();
    }

    hand.insert(hand.begin(), myCards.begin(), myCards.begin() + num);
    myCards.erase(myCards.begin(), myCards.begin()+num);

    // std::cout << "Returning  " << hand.size() << " cards." << std::endl;
    // std::cout << "Deck has " << Size() << " remaining." << std::endl;

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

uint16_t DeckOfCards::Size()
{
    return myCards.size();
}

 void DeckOfCards::ProcessArgs(int argc, char* argv[])
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

    for (int i; i<DeckOfCards::handSize; i++)
    {
        for (PokerPlayer& player : players)    
        {
            Card card = deck.DrawCard();
            // std::cout << "Drawing card: " << card.Value << card.Suit << std::endl;

            player.ReceiveCard(card);
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
