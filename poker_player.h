#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include <string>
#include <deque>
#include "deck_of_cards.h"

class PokerPlayer
{
public:
    PokerPlayer(const std::string& name, size_t player_num);
    ~PokerPlayer();

    enum Action {
        FOLD,
        BET,
        RAISE,
        CALL
    };

    enum PokerHand {
        NOTHING,
        PAIR,
        TWO_PAIR,
        THREE_OF_A_KIND,
        STRAIGHT,
        FLUSH,
        FULL_HOUSE,
        FOUR_OF_A_KIND,
        STRAIGH_FLUSH,
        ROYAL_FLUSH,
        FIVE_OF_A_KIND
    };

    Action DeterminePlayerAction();
    PokerHand EvaluateHand();
    void ReceiveHand(CARDS hand);
    void ReceiveCard(Card card);
    CARDS ReturnCardsToDealer();

    std::string GetName() {return (playerName);}
    size_t GetPlayerNumer() {return(playerNumber);}
    CARDS GetHand() {return(playerHand);}
    std::string HandToString();

    static std::string HandNameToString(PokerHand hand);

private:
   static float IsNothing(CARDS&);
   static float IsPair(CARDS&);
   static float IsTwoPairs(CARDS&);
   static float IsThreeOfaKind(CARDS&);
   static float IsStraight(CARDS&);
   static float IsFlush(CARDS&);
   static float IsFullHouse(CARDS&);
   static float IsFourOfaKind(CARDS&);
   static float IsStraightFlush(CARDS&);
   static float IsRoyalFlush(CARDS&);
   static float IsFiveOfaKind(CARDS&);


    CARDS playerHand;
    size_t playerNumber;
    std::string playerName;
};

#endif //POKER_PLAYER_H