#include "poker_player.h"

#include <future>
#include <vector>
#include <map>
#include <algorithm>

typedef std::map<PokerPlayer::PokerHand, std::future<float>> POKER_FUTURES;

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
   	FindPossibleHands();

    
    std::map<std::string, POKER_FUTURES> everything;
    std::map<std::string, PokerHand> highest_hands;

    for (CardCombo hand_set : possibleHands)
    {
      CARDS hand = GetPossibleHandasCARDS(hand_set);

      std::string handStr = DeckOfCards::CardsToString(hand);

    	float hand_results[11] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    	PokerHand highestHand = PokerHand::NOTHING;

    	everything[handStr][NOTHING] 			= (std::async(std::launch::async, [this, hand]{return IsNothing(hand);}));
    	everything[handStr][PAIR] 				= (std::async(std::launch::async, [this, hand]{return IsPair(hand);}));
    	everything[handStr][TWO_PAIR] 			= (std::async(std::launch::async, [this, hand]{return IsTwoPairs(hand);}));
    	everything[handStr][THREE_OF_A_KIND] 	= (std::async(std::launch::async, [this, hand]{return IsThreeOfaKind(hand);}));
    	everything[handStr][STRAIGHT] 			= (std::async(std::launch::async, [this, hand]{return IsStraight(hand);}));
    	everything[handStr][FLUSH] 				= (std::async(std::launch::async, [this, hand]{return IsFlush(hand);}));
    	everything[handStr][FULL_HOUSE] 		= (std::async(std::launch::async, [this, hand]{return IsFullHouse(hand);}));
    	everything[handStr][FOUR_OF_A_KIND] 	= (std::async(std::launch::async, [this, hand]{return IsFourOfaKind(hand);}));
    	everything[handStr][STRAIGHT_FLUSH] 	= (std::async(std::launch::async, [this, hand]{return IsStraightFlush(hand);}));
    	everything[handStr][ROYAL_FLUSH] 		= (std::async(std::launch::async, [this, hand]{return IsRoyalFlush(hand);}));
    	everything[handStr][FIVE_OF_A_KIND] 	= (std::async(std::launch::async, [this, hand]{return IsFiveOfaKind(hand);}));

    	// std::cout << "Is<HAND> functions have been started." << std::endl;

    	for (std::map<PokerHand, std::future<float> >::iterator it = everything[handStr].begin();
        	it != everything[handStr].end();
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

      highest_hands[handStr] = highestHand;
    }

    std::string hand_cards;
    PokerHand ultimateHand = PokerHand::NOTHING;
    for (std::map<std::string, PokerHand>::iterator it = highest_hands.begin(); 
          it != highest_hands.end();
          it++)
    {
      if ( (*it).second > ultimateHand)
      {
        ultimateHand = (*it).second;
        hand_cards = (*it).first;
      } 
    }
    
    std::cout << "Ultimate hand: " << hand_cards;
    return (ultimateHand);
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


CARDS PokerPlayer::GetPossibleHandasCARDS(CardCombo& card_set)
{
	CARDS hand;
	
	for (Card card : card_set)
	{
		hand.push_back(card);
	}

	return hand;
}


void PokerPlayer::FindPossibleHands()
{
    if ( 5 == playerHand.size() )
    {
      CardCombo combo;
      for (Card card : playerHand)
      {
        combo.insert(card);
      }

    	possibleHands.insert(combo);
      return;
    }
    CARDS allCards = playerHand;
    allCards.insert(allCards.end(), tableCards.cbegin(), tableCards.cend());

    //std::cout << "7 cards: " << std::endl;
    //DeckOfCards::PrintCards(allCards);

    do
    {
    	CardCombo combo;
    	for (int i=0; i<5; i++)
    	{
       		combo.insert(allCards[i]);
    	}

    	possibleHands.insert(combo);

    } while (std::next_permutation(allCards.begin(), allCards.end()));

//    std::cout << "Possible Hands: " << possibleHands.size() << std::endl;
}


std::string PokerPlayer::HandToString()
{
    std::string output = "[";
    // std::cout << "HandToString: handSize = " << playerHand.size() << std::endl;

    for (Card card : playerHand)
    {
        output += card.toString() + " ";
    }

    if (0 < tableCards.size())
    {
        output += "][";

        for (Card card : tableCards)
        {
            output += card.toString() + " ";
        }
    }

    output += "]";

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

float PokerPlayer::IsNothing(CARDS cards)
{
    float confidence = 1.0;
    return (confidence);
}

float PokerPlayer::IsPair(CARDS cards)
{
    float confidence = 0.0;

    std::map<std::string, size_t> value_counts;

    for (Card& card : cards)
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

float PokerPlayer::IsTwoPairs(CARDS cards)
{
    float confidence = 0.0;

    std::map<std::string, size_t> value_counts;

    for (Card& card : cards)
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

float PokerPlayer::IsThreeOfaKind(CARDS cards)
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (Card& card : cards)
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

float PokerPlayer::IsStraight(CARDS cards)
{
    float confidence = 0.0;
    float highest_confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (int i=0; i<DeckOfCards::NUM_VALUES; i++)
    {
        value_counts[VALUES[i]] = 0;
    }
    for (Card& card : cards)
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

float PokerPlayer::IsFlush(CARDS cards)
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> suit_counts;

    for (Card& card : cards)
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

float PokerPlayer::IsFullHouse(CARDS cards)
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (Card& card : cards)
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

float PokerPlayer::IsFourOfaKind(CARDS cards)
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (Card& card : cards)
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

float PokerPlayer::IsStraightFlush(CARDS cards)
{
    float confidence = 0.0;

    if (1.0 == IsStraight(cards))
    {
        confidence += 0.5;
    }

    if (1.0 == IsFlush(cards))
    {
        confidence += 0.5;
    }

    return (confidence);
}

float PokerPlayer::IsRoyalFlush(CARDS cards)
{
    float confidence = 0.0;

    if (1.0 == IsStraightFlush(cards))
    {
        confidence += 0.5;

        for (Card& card : cards)
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

float PokerPlayer::IsFiveOfaKind(CARDS cards)
{
    float confidence = 0.0;
 
    std::map<std::string, size_t> value_counts;

    for (Card& card : cards)
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
