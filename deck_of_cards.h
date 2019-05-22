#pragma once
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
        return (Value);
    }
};

typedef std::deque<Card> CARDS;
const std::string SUITS[] = {"\u2665", "\u2660", "\u2666", "\u2663"};
const std::string VALUES[] = {"A", "K", "Q", "J", "10", "9", "8", "7", "6", "5", "4", "3", "2"};

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
    
private:
    CARDS myCards;
};