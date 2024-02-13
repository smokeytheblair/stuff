import asyncio
from enum import Enum
import copy
from deck_of_cards import VALUES, VALUE_IDS
from collections import defaultdict
import itertools

class Action(Enum):
    FOLD = 0
    BET = 1
    RAISE = 2
    CALL = 3

class PokerHand(Enum):
    NOTHING = 0
    PAIR = 1
    TWO_PAIR = 2
    THREE_OF_A_KIND = 3
    STRAIGHT = 4
    FLUSH = 5
    FULL_HOUSE = 6
    FOUR_OF_A_KIND = 7
    STRAIGHT_FLUSH = 8
    ROYAL_FLUSH = 9

POKER_HANDS = {
        PokerHand.NOTHING : 'Nothing',
        PokerHand.PAIR : 'Pair',
        PokerHand.TWO_PAIR : 'Two Pair',
        PokerHand.THREE_OF_A_KIND : 'Three of a Kind',
        PokerHand.STRAIGHT : 'Straight',
        PokerHand.FLUSH : 'Flush',
        PokerHand.FULL_HOUSE : 'Full House',
        PokerHand.FOUR_OF_A_KIND : 'Four of a Kind',
        PokerHand.STRAIGHT_FLUSH : 'Straight Flush',
        PokerHand.ROYAL_FLUSH : 'Royal Flush'
        }

class PokerPlayer:
    def __init__(self, new_name, new_number):
        self.name = new_name
        self.number = new_number
        self.hand = []

        # print(f'{self.name} {self.number} sitting down at the table.')

    def determine_player_action(self):
        return Action.FOLD

    def receive_hand(self, new_hand):
        self.hand = new_hand

    def receive_card(self, new_card):
        self.hand.append(new_card)
        # print(f'{self.name}{self.number} getting {new_card.to_string()}, have {len(self.hand)} cards.')

    def return_cards_to_dealer(self):
        old_hand = copy.deep_copy(self.hand) 
        self.hand.clear()
        return old_hand

    def get_name(self):
        return self.name

    def get_number(self):
        return self.number

    def get_hand(self):
        return self.hand

    def hand_to_string(self, hand):
        hand_as_string = ''
        for card in hand:
            hand_as_string += f'{card.to_string()} '

        return hand_as_string

    def hand_name_to_string(self, hand_name):
        return POKER_HANDS[hand_name]

    async def _is_nothing(self, hand):
        return 1.0

    async def _is_pair(self, hand):
        confidence = 0.0

        value_counts = defaultdict(int)

        for card in hand:
            value_counts[card.value] += 1

        for key,val in value_counts.items():
            if val >= 2:
                confidence = 1.0

        return confidence

    async def _is_two_pair(self, hand):
        confidence = 0.0

        value_counts = {}

        for card in hand:
            value_counts.setdefault(card.value, 0)
            value_counts[card.value] += 1

        for key,val in value_counts.items():
            if val >= 2:
                confidence += 0.5

            if confidence == 1.0:
                break

        return confidence

    async def _is_three_of_a_kind(self, hand):
        confidence = 0.0

        value_counts = defaultdict(int)

        for card in hand:
            value_counts[card.value] += 1

        for key,val in value_counts.items():
            if val >= 3:
                confidence = 1.0

        return confidence

    async def _is_straight(self, hand):
        confidence = 0.0
        highest_confidence = 0.0

        value_counts = defaultdict(int)

        for card in hand:
            value_counts[card.value] += 1

        for value in VALUES.values():
            if 1 == value_counts[value]:
                confidence += 0.2
                if confidence > highest_confidence:
                    highest_confidence = confidence
            else:
                confidence = 0.0

        return highest_confidence

    async def _is_flush(self, hand):
        confidence = 0.0

        suit_counts = defaultdict(int)

        for card in hand:
            suit_counts[card.suit] += 1

        for suit_count in suit_counts.values():
            if 5 == suit_count:
                confidence = 1.0
            #     break
            # elif 3 <= suit_count:
            #     confidence = 0.2 * suit_count

        return confidence

    async def _is_full_house(self, hand):
        confidence = 0.0

        value_counts = defaultdict(int)

        for card in hand:
            value_counts[card.value] += 1

        pair_found = False

        for count in value_counts.values():
            if 3 == count:
                confidence  += 0.6
            if 2 == count and not pair_found:
                pair_found = True
                confidence += 0.4

        return confidence

    async def _is_four_of_a_kind(self, hand):
        confidence = 0.0

        value_counts = defaultdict(int)

        for card in hand:
            value_counts[card.value] += 1

        for val in value_counts.values():
            if val >= 4:
                confidence = 1.0

        return confidence

    async def _is_straight_flush(self, hand):
        confidence = 0.0

        if 1.0 == await self._is_flush():
            confidence += 0.5

        if 1.0 == await self._is_straight():
            confidence += 0.5

        return confidence

    async def _is_royal_flush(self, hand):
        confidence = 0.0

        if 1.0 == await self._is_straight_flush():
            confidence += 0.8

        for card in hand:
            if VALUES[VALUE_IDS.ACE] == card.value:
                confidence += 0.2
                break

        return confidence

    async def evaluate_hand(self):
        if len(self.hand) < 5:
            return (self.hand, PokerHand.NOTHING)
        elif len(self.hand) > 5:
            highest_hand = PokerHand.NOTHING
            highest_cards = {}

            # make sets of 5 cards and test them
            # then pick the highest hand from the sets
            hands = itertools.combinations(self.hand, 5)

            for current_hand in hands:
                # print(f'current hand: {self.hand_to_string(current_hand)}')
                hand_results = await asyncio.gather(self._is_nothing(current_hand),
                                                    self._is_pair(current_hand),
                                                    self._is_two_pair(current_hand),
                                                    self._is_three_of_a_kind(current_hand),
                                                    self._is_straight(current_hand),
                                                    self._is_flush(current_hand),
                                                    self._is_full_house(current_hand),
                                                    self._is_four_of_a_kind(current_hand),
                                                    self._is_straight_flush(current_hand),
                                                    self._is_royal_flush(current_hand),
                                                    return_exceptions=True)

                # print(f'evaluate_hand({self.hand_to_string()} ={hand_results})')
                highest_hand = PokerHand.NOTHING
                highest_cards[current_hand] = PokerHand.NOTHING
                i = 0
                for hand_value in POKER_HANDS.keys():
                    if 1.0 == hand_results[i]:
                        highest_hand = hand_value

                    i += 1

                highest_cards[current_hand] = highest_hand
                # print(f"Player {self.number}, hand[{self.hand_to_string(current_hand)}] = {self.hand_name_to_string(highest_cards[current_hand])}")

            hight_hand_key = ''
            highest_hand_value = PokerHand.NOTHING
            for hand_key, hand_value in highest_cards.items():
                if hand_value.value >= highest_hand_value.value:
                    highest_hand_value = hand_value
                    hight_hand_key = hand_key

            # print(f'Possible hands: {hands}')
            return (hight_hand_key, highest_hand_value)
        else:
            hand_results = await asyncio.gather(self._is_nothing(self.hand),
                    self._is_pair(self.hand),
                    self._is_two_pair(self.hand),
                    self._is_three_of_a_kind(self.hand),
                    self._is_straight(self.hand),
                    self._is_flush(self.hand),
                    self._is_full_house(self.hand),
                    self._is_four_of_a_kind(self.hand),
                    self._is_straight_flush(self.hand),
                    self._is_royal_flush(self.hand),
                    return_exceptions=True)

            # print(f'evaluate_hand({self.hand_to_string()} ={hand_results})')
            highest_hand = PokerHand.NOTHING

            i = 0
            for hand in POKER_HANDS.keys():
                if 1.0 == hand_results[i]:
                    highest_hand = hand

                i += 1

            return (self.hand, highest_hand)

        return (self.hand, PokerHand.NOTHING)
