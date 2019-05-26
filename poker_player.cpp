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
    std::map<PokerHand, float> hand_results;

    PokerHand highestHand = PokerHand::NOTHING;

    // futures[NOTHING] = (std::async(std::launch::async, [=]{return IsNothing(this->playerHand);}));
    // futures[PAIR] = (std::async(std::launch::async, [=]{return IsPair(this->playerHand);}));
    // futures[TWO_PAIR] = (std::async(std::launch::async, [=]{return IsTwoPairs(this->playerHand);}));
    // futures[THREE_OF_A_KIND] = (std::async(std::launch::async, [=]{return IsThreeOfaKind(this->playerHand);}));
    // futures[STRAIGHT] = (std::async(std::launch::async, [=]{return IsStraight(this->playerHand);}));
    // futures[FLUSH] = (std::async(std::launch::async, [=]{return IsFlush(this->playerHand);}));
    // futures[FULL_HOUSE] = (std::async(std::launch::async, [=]{return IsFullHouse(this->playerHand);}));

    // for (std::map<PokerHand, std::future<float> >::iterator it = futures.begin();
    //     it != futures.end();
    //     it++)
    // {
    //     (*it).second.wait();
    //     hand_results[(*it).first] = (*it).second.get();

    //     if (1.0 == (*it).second.get())
    //     {
    //         highestHand = (*it).first;
    //     }
    // }    
    
    hand_results[NOTHING]           = IsNothing(this->playerHand);
    hand_results[PAIR]              = IsPair(this->playerHand);
    hand_results[TWO_PAIR]          = IsTwoPairs(this->playerHand);
    hand_results[THREE_OF_A_KIND]   = IsThreeOfaKind(this->playerHand);
    hand_results[STRAIGHT]          = IsStraight(this->playerHand);
    hand_results[FLUSH]             = IsFlush(this->playerHand);
    hand_results[FULL_HOUSE]        = IsFullHouse(this->playerHand);
    hand_results[STRAIGHT_FLUSH]    = IsStraightFlush(this->playerHand);
    hand_results[ROYAL_FLUSH]       = IsRoyalFlush(this->playerHand);
    hand_results[FIVE_OF_A_KIND]    = IsFiveOfaKind(this->playerHand);

    for (std::map<PokerHand, float>::iterator it = hand_results.begin();
         it != hand_results.end();
         it++)
    {
        // std::cout << "Hand score[" << HandNameToString((*it).first) << "] = " << (*it).second << std::endl;

        if (1.0 == (*it).second)
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

float PokerPlayer::IsNothing(CARDS& hand)
{
    float confidence = 1.0;
    return (confidence);
}

float PokerPlayer::IsPair(CARDS& hand)
{
    float confidence = 0.0;

    std::map<std::string, size_t> value_counts;

    for (Card& card : hand)
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

float PokerPlayer::IsTwoPairs(CARDS& hand)
{
    float confidence = 0.0;

    std::map<std::string, size_t> value_counts;

    for (Card& card : hand)
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

float PokerPlayer::IsThreeOfaKind(CARDS& hand)
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (Card& card : hand)
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

float PokerPlayer::IsStraight(CARDS& hand)
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (int i=0; i<DeckOfCards::NUM_VALUES; i++)
    {
        value_counts[VALUES[i]] = 0;
    }
    for (Card& card : hand)
    {
        value_counts[card.Value] += 1;
    }

    size_t num_in_sequence = 0;
    for (size_t i=0; i<DeckOfCards::NUM_VALUES && 5 > num_in_sequence; i++)
    {
        std::string value = VALUES[i];
        size_t value_count = value_counts[value];

        // std::cout << "Value[" << value << "] = " << value_count << std::endl;

        switch (value_count)
        {
            case 0:
                num_in_sequence = 0;
                // std::cout << "num_in_sequence = " << num_in_sequence << std::endl;
                break;
            case 1:
                ++num_in_sequence;
                // std::cout << "num_in_sequence = " << num_in_sequence << std::endl;
                break;
                break;
            default:
                num_in_sequence = 0;
                // std::cout << "num_in_sequence = " << num_in_sequence << std::endl;
                break;
                break;
        }
    }

    confidence = 0.2 * num_in_sequence;

    return (confidence);
}

float PokerPlayer::IsFlush(CARDS& hand)
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> suit_counts;

    for (Card& card : hand)
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

float PokerPlayer::IsFullHouse(CARDS& hand)
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (Card& card : hand)
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

float PokerPlayer::IsFourOfaKind(CARDS& hand)
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (Card& card : hand)
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

float PokerPlayer::IsStraightFlush(CARDS& hand)
{
    float confidence = 0.0;

    if (1.0 == IsStraight(hand))
    {
        confidence += 0.5;
    }

    if (1.0 == IsFlush(hand))
    {
        confidence += 0.5;
    }

    return (confidence);
}

float PokerPlayer::IsRoyalFlush(CARDS& hand)
{
    float confidence = 0.0;

    if (1.0 == IsStraightFlush(hand))
    {
        confidence += 0.5;
    }

    for (Card& card : hand)
    {
        if (VALUES[ACE] == card.Value)
        {
            confidence += 0.5;
            break;
        }
    }

    return (confidence);
}

float PokerPlayer::IsFiveOfaKind(CARDS& hand)
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (Card& card : hand)
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
