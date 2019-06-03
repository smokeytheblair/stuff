#ifndef DECK_OF_CARDS_H
#define DECK_OF_CARDS_H

#include <iostream>
#include <string>
#include <deque>

struct Card
{
    std::string Suit;
    std::string Value;

    std::string toString() 
    {
        std::string cardName;
        cardName += Value + Suit;
        //std::cout << "Printing: " << Value << Suit << " as " << cardName << std::endl;
        return (cardName);
    }
};

enum SUIT_IDS
{
    HEARTS = 0,
    SPADES = 1,
    DIAMONDS = 2,
    CLUBS = 3
};

enum VALUD_IDS
{
    ACE = 0,
    KING = 1,
    QUEEN = 2,
    JACK = 3,
    TEN = 4,
    NINE = 5,
    EIGHT = 6,
    SEVEN = 7,
    SIX = 8,
    FIVE = 9,
    FOUR = 10,
    THREE = 11,
    TWO = 12
};

typedef std::deque<Card> CARDS;
const std::string SUITS[] = {"\u2665", "\u2660", "\u2666", "\u2663"};
const std::string VALUES[] = {"A", "K", "Q", "J", "10", "9", "8", "7", "6", "5", "4", "3", "2"};
const std::string JOKERS[] = {"Joker(tm)", "Joker"};

class DeckOfCards 
{
public:
    DeckOfCards();
    DeckOfCards(const DeckOfCards&) = delete;
    ~DeckOfCards();

    static void ProcessArgs(int argc, char* argv[]);

    void PrintCards(CARDS cards);
    CARDS DrawCards(int num);
    Card DrawCard();
    void Shuffle();
    uint16_t Size();

    static int handSize;
    static int numPlayers;
    static int numDecks;

    static uint16_t NUM_SUITS;
    static uint16_t NUM_VALUES;
    static int INCLUDE_JOKERS;

    
private:
    CARDS myCards;
};

#endif //DECK_OF_CARDS_H