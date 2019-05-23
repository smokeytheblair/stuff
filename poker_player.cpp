#include "poker_player.h"

#include <future>
#include <vector>


PokerPlayer::PokerPlayer(const std::string& name, size_t player_num)
{
    playerName = name;
    playerNumber = player_num;
}

PokerPlayer::~PokerPlayer()
{
}

PokerPlayer::Action PokerPlayer::DeterminePlayerAction()
{
    //Determine if the hand has any poker hands in it and how strong that is.
    //Return an Action of FOLD, BET, RAISE, or CALL
    return (PokerPlayer::Action::FOLD);
}

PokerPlayer::PokerHand PokerPlayer::EvaluateHand()
{
    std::vector<std::future<float> > futures;
    std::vector<float> hand_results;

    futures.push_back(std::async(std::launch::async, [=]{return IsNothing(this->playerHand);}));

    for (std::vector<std::future<float> >::iterator it;
        it != futures.end();
        it++)
    {
        (*it).wait();
        hand_results.push_back((*it).get());
    }
    return (PokerPlayer::PokerHand::NOTHING);
}

void PokerPlayer::ReceiveCard(Card card)
{
    playerHand.push_back(card);
    // std::cout << playerName << " receiving " << card.toString() 
    //           << ". HandSize = " << playerHand.size() << std::endl;
}

void PokerPlayer::ReceiveHand(CARDS hand)
{
    playerHand = hand;
}

CARDS PokerPlayer::ReturnCardsToDealer()
{
    CARDS oldHand = playerHand;
    playerHand.clear();

    return (oldHand);
}

std::string PokerPlayer::HandToString()
{
    std::string output;
    // std::cout << "HandToString: handSize = " << playerHand.size() << std::endl;

    for (Card card : playerHand)
    {
        output += card.toString() + " ";
    }

    return (output);
}


float PokerPlayer::IsNothing(CARDS& hand)
{
    float confidence = 0.0;

    return (confidence);
}

float PokerPlayer::IsPair(CARDS& hand)
{
    float confidence = 0.0;

    return (confidence);
}

float PokerPlayer::IsTwoPairs(CARDS& hand)
{
    float confidence = 0.0;

    return (confidence);
}

float PokerPlayer::IsThreeOfaKind(CARDS& hand)
{
    float confidence = 0.0;

    return (confidence);
}

float PokerPlayer::IsStraight(CARDS& hand)
{
    float confidence = 0.0;

    return (confidence);
}

float PokerPlayer::IsFlush(CARDS& hand)
{
    float confidence = 0.0;

    return (confidence);
}

float PokerPlayer::IsFullHouse(CARDS& hand)
{
    float confidence = 0.0;

    return (confidence);
}

float PokerPlayer::IsFourOfaKind(CARDS& hand)
{
    float confidence = 0.0;

    return (confidence);
}

float PokerPlayer::IsStraightFlush(CARDS& hand)
{
    float confidence = 0.0;

    return (confidence);
}

float PokerPlayer::IsRoyalFlush(CARDS& hand)
{
    float confidence = 0.0;

    return (confidence);
}

float PokerPlayer::IsFiveOfaKind(CARDS& hand)
{
    float confidence = 0.0;

    return (confidence);
}
