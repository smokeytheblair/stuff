#include "poker_player.h"

#include <future>
#include <vector>
#include <map>


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
    std::map<PokerHand, std::future<float> > futures;
    float hand_results[11] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    PokerHand highestHand = PokerHand::NOTHING;

    futures[NOTHING] = (std::async(std::launch::async, [=]{return IsNothing();}));
    futures[PAIR] = (std::async(std::launch::async, [=]{return IsPair();}));
    futures[TWO_PAIR] = (std::async(std::launch::async, [=]{return IsTwoPairs();}));
    futures[THREE_OF_A_KIND] = (std::async(std::launch::async, [=]{return IsThreeOfaKind();}));
    futures[STRAIGHT] = (std::async(std::launch::async, [=]{return IsStraight();}));
    futures[FLUSH] = (std::async(std::launch::async, [=]{return IsFlush();}));
    futures[FULL_HOUSE] = (std::async(std::launch::async, [=]{return IsFullHouse();}));
    futures[FOUR_OF_A_KIND] = (std::async(std::launch::async, [=]{return IsFourOfaKind();}));
    futures[STRAIGHT_FLUSH] = (std::async(std::launch::async, [=]{return IsStraightFlush();}));
    futures[ROYAL_FLUSH] = (std::async(std::launch::async, [=]{return IsRoyalFlush();}));
    futures[FIVE_OF_A_KIND] = (std::async(std::launch::async, [=]{return IsFiveOfaKind();}));

    // std::cout << "Is<HAND> functions have been started." << std::endl;

    for (std::map<PokerHand, std::future<float> >::iterator it = futures.begin();
        it != futures.end();
        it++)
    {
        (*it).second.wait();

        hand_results[(*it).first] = (*it).second.get();
        // std::cout << "Hand score[" << HandNameToString((*it).first) << "] = " << hand_results[(*it).first] << std::endl;

        if (1.0 == hand_results[(*it).first])
        {
            highestHand = (*it).first;
        }
    }    
    
    return (highestHand);
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

std::string PokerPlayer::HandNameToString(PokerHand hand)
{
    std::string name;
    switch (hand)
    {
        case PokerHand::NOTHING:
            name = "Nothing";
            break;
        case PokerHand::PAIR:
            name = "Pair";
            break;
        case PokerHand::TWO_PAIR:
            name = "Two Pairs";
            break;
        case PokerHand::THREE_OF_A_KIND:
            name = "Three of a Kind";
            break;
        case PokerHand::STRAIGHT:
            name = "Straight";
            break;
        case PokerHand::FLUSH:
            name = "Flush";
            break;
        case PokerHand::FULL_HOUSE:
            name = "Full House";
            break;
        case PokerHand::FOUR_OF_A_KIND:
            name = "Four of a Kind";
            break;
        case PokerHand::STRAIGHT_FLUSH:
            name = "Straight Flush";
            break;
        case PokerHand::ROYAL_FLUSH:
            name = "Royal Flush";
            break;
        case PokerHand::FIVE_OF_A_KIND:
            name = "Five of a Kind";
            break;
        default:
            name = "Nothing (default)";
            break;

    }

    return (name);
}

float PokerPlayer::IsNothing()
{
    float confidence = 1.0;
    return (confidence);
}

float PokerPlayer::IsPair()
{
    float confidence = 0.0;

    std::map<std::string, size_t> value_counts;

    for (Card& card : playerHand)
    {
        value_counts[card.Value] += 1;
    }

    for (std::map<std::string, size_t>::iterator it = value_counts.begin();
         it != value_counts.end();
         it++)
    {
        if ((*it).second >= 2)
        {
            confidence = 1.0;
        }
    }
    return (confidence);
}

float PokerPlayer::IsTwoPairs()
{
    float confidence = 0.0;

    std::map<std::string, size_t> value_counts;

    for (Card& card : playerHand)
    {
        value_counts[card.Value] += 1;
    }

    for (std::map<std::string, size_t>::iterator it = value_counts.begin();
         it != value_counts.end();
         it++)
    {
        if ((*it).second >= 2)
        {
            confidence += 0.5;
        }
    }
    return (confidence);
}

float PokerPlayer::IsThreeOfaKind()
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (Card& card : playerHand)
    {
        value_counts[card.Value] += 1;
    }

    for (std::map<std::string, size_t>::iterator it = value_counts.begin();
         it != value_counts.end();
         it++)
    {
        if ((*it).second >= 3)
        {
            confidence = 1.0;
        }
    }
    return (confidence);
}

float PokerPlayer::IsStraight()
{
    float confidence = 0.0;
    float highest_confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (int i=0; i<DeckOfCards::NUM_VALUES; i++)
    {
        value_counts[VALUES[i]] = 0;
    }
    for (Card& card : playerHand)
    {
        value_counts[card.Value] += 1;
    }

    for (size_t i=0; i<DeckOfCards::NUM_VALUES && 1.0 != confidence; i++)
    {
        std::string value = VALUES[i];
        size_t value_count = value_counts[value];

        // std::cout << "Value[" << value << "] = " << value_count << std::endl;

        switch (value_count)
        {
            case 0:
                confidence = 0.0;
                break;
            case 1:
                confidence += 0.2;
                if (confidence > highest_confidence)
                {
                    highest_confidence = confidence;
                }
                // std::cout << "confidence = " << confidence << std::endl;
                break;
            default:
                confidence = 0.0;
                break;
        }
    }

    return (highest_confidence);
}

float PokerPlayer::IsFlush()
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> suit_counts;

    for (Card& card : playerHand)
    {
        suit_counts[card.Suit] += 1;
    }

    for (std::map<std::string, size_t>::iterator it = suit_counts.begin();
         it != suit_counts.end();
         it++)
    {
        if ((*it).second == 5)
        {
            confidence = 1.0;
        }
        else if ((*it).second >=3)
        {
            confidence = 0.2 * (*it).second;
        }
    }
    return (confidence);
}

float PokerPlayer::IsFullHouse()
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (Card& card : playerHand)
    {
        value_counts[card.Value] += 1;
    }

    bool pairFound = false;

    for (std::map<std::string, size_t>::iterator it = value_counts.begin();
         it != value_counts.end();
         it++)
    {
        if ((*it).second == 3)
        {
            confidence += 0.6;
        }

        if ((*it).second == 2 && !pairFound)
        {
            pairFound = true;
            confidence += 0.4;
        }
    }
    return (confidence);
}

float PokerPlayer::IsFourOfaKind()
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (Card& card : playerHand)
    {
        value_counts[card.Value] += 1;
    }

    for (std::map<std::string, size_t>::iterator it = value_counts.begin();
         it != value_counts.end();
         it++)
    {
        if ((*it).second >= 4)
        {
            confidence = 1.0;
        }
    }

    return (confidence);
}

float PokerPlayer::IsStraightFlush()
{
    float confidence = 0.0;

    if (1.0 == IsStraight())
    {
        confidence += 0.5;
    }

    if (1.0 == IsFlush())
    {
        confidence += 0.5;
    }

    return (confidence);
}

float PokerPlayer::IsRoyalFlush()
{
    float confidence = 0.0;

    if (1.0 == IsStraightFlush())
    {
        confidence += 0.5;

        for (Card& card : playerHand)
        {
            if (VALUES[ACE] == card.Value)
            {
                confidence += 0.5;
                break;
            }
        }
    }

    return (confidence);
}

float PokerPlayer::IsFiveOfaKind()
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (Card& card : playerHand)
    {
        value_counts[card.Value] += 1;
    }

    for (std::map<std::string, size_t>::iterator it = value_counts.begin();
         it != value_counts.end();
         it++)
    {
        if ((*it).second >= 5)
        {
            confidence = 1.0;
        }
    }

    return (confidence);
}
