#include <deque>
#include <iostream>
#include <algorithm>
#include <locale>
#include <ctime>
#include <experimental/random>

#include "deck_of_cards.h"
#include "poker_player.h"


uint16_t DeckOfCards::NUM_SUITS = sizeof(SUITS)/sizeof(std::string);
uint16_t DeckOfCards::NUM_VALUES = sizeof(VALUES)/sizeof(std::string);

DeckOfCards::DeckOfCards(int numDecks)
{

    // std::wcout  << L"Building a deck of cards.\n"
    //             << L"Suits: " << NUM_SUITS << L"\n"
    //             << L"Values: " << NUM_VALUES
    //             << std::endl;

    this->numDecks = numDecks;

    for (int num_decks = 0; num_decks<numDecks; num_decks++)
    {
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
