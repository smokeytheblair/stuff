#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include <string>
#include <deque>
#include <map>
#include <set>
#include "deck_of_cards.h"

typedef std::set<Card> CardCombo;

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
        STRAIGHT_FLUSH,
        ROYAL_FLUSH,
        FIVE_OF_A_KIND
    };

    Action DeterminePlayerAction();
    PokerHand EvaluateHand();
    void ReceiveHand(CARDS hand);
    void ReceiveCard(Card card);
    CARDS ReturnCardsToDealer();
    void FindPossibleHands();

    std::string GetName() {return (playerName);}
    size_t GetPlayerNumber() {return(playerNumber);}
    CARDS GetHand() {return(playerHand);}
    std::string HandToString();
	CARDS GetPossibleHandasCARDS(CardCombo&);

    void SetTableCards(CARDS& table_cards) {tableCards = table_cards;}

    static std::string HandNameToString(PokerHand hand);

private:
   float IsNothing(CARDS);
   float IsPair(CARDS);
   float IsTwoPairs(CARDS);
   float IsThreeOfaKind(CARDS);
   float IsStraight(CARDS);
   float IsFlush(CARDS);
   float IsFullHouse(CARDS);
   float IsFourOfaKind(CARDS);
   float IsStraightFlush(CARDS);
   float IsRoyalFlush(CARDS);
   float IsFiveOfaKind(CARDS);


    CARDS playerHand;
    CARDS tableCards;
    size_t playerNumber;
    std::string playerName;
    std::map<PokerHand, float> hand_results;
    std::set<CardCombo> possibleHands;
};

#endif //POKER_PLAYER_H
