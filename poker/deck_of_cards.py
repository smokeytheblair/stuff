# import asyncio
from enum import Enum
import random

class SUIT_IDS(Enum):
    HEARTS = 0
    SPADES = 1
    DIAMONDS = 2
    CLUBS = 3

class VALUE_IDS(Enum):
    ACE = 0
    KING = 1
    QUEEN = 2
    JACK = 3
    TEN = 4
    NINE = 5
    EIGHT = 6
    SEVEN = 7
    SIX = 8
    FIVE = 9
    FOUR = 10
    THREE = 11
    TWO = 12

SUITS = {
    SUIT_IDS.HEARTS: '\u2665',
    SUIT_IDS.SPADES: '\u2660',
    SUIT_IDS.DIAMONDS: '\u2666',
    SUIT_IDS.CLUBS: '\u2663' }

VALUES = {
    VALUE_IDS.ACE: 'A', 
    VALUE_IDS.KING: 'K',
    VALUE_IDS.QUEEN: 'Q',
    VALUE_IDS.JACK: 'J',
    VALUE_IDS.TEN: '10',
    VALUE_IDS.NINE: '9',
    VALUE_IDS.EIGHT: '8',
    VALUE_IDS.SEVEN: '7',
    VALUE_IDS.SIX: '6',
    VALUE_IDS.FIVE: '5',
    VALUE_IDS.FOUR: '4',
    VALUE_IDS.THREE: '3',
    VALUE_IDS.TWO: '2' }

class Card:

    def __init__(self, new_suit, new_value):
        self.suit = new_suit
        self.value = new_value

    def to_string(self):
        return f'{self.value}{self.suit}'
    

class DeckOfCards:
    def __init__(self, num_new_decks):
        #fill out the cards list
        self.num_decks = num_new_decks
        self.cards = []

        for i in range(self.num_decks):
            for suit in SUITS.values():
                for value in VALUES.values():
                    card = Card(suit, value)
                    self.cards.append(card)

    def shuffle(self):
        for i in range(random.randint(17,51)): 
            random.shuffle(self.cards)
        
    def draw_card(self):
        card = self.cards.pop(0)
        # print(f'Drawing {card.to_string()} from the deck. Deck has {len(self.cards)} left.')
        return card



TEST_HANDS = [
    [Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.KING]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.ACE]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.QUEEN]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.JACK]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.TEN])],
    [Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.KING]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.NINE]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.QUEEN]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.JACK]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.TEN])],
    [Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.TWO]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.KING]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.QUEEN]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.JACK]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.TEN])],
    [Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.ACE]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.KING]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.QUEEN]), Card(SUITS[SUIT_IDS.DIAMONDS], VALUES[VALUE_IDS.JACK]), Card(SUITS[SUIT_IDS.CLUBS], VALUES[VALUE_IDS.TEN])],
    [Card(SUITS[SUIT_IDS.CLUBS], VALUES[VALUE_IDS.JACK]), Card(SUITS[SUIT_IDS.DIAMONDS], VALUES[VALUE_IDS.THREE]), Card(SUITS[SUIT_IDS.SPADES], VALUES[VALUE_IDS.THREE]), Card(SUITS[SUIT_IDS.CLUBS], VALUES[VALUE_IDS.THREE]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.THREE])],
    [Card(SUITS[SUIT_IDS.SPADES], VALUES[VALUE_IDS.KING]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.KING]), Card(SUITS[SUIT_IDS.SPADES], VALUES[VALUE_IDS.THREE]), Card(SUITS[SUIT_IDS.CLUBS], VALUES[VALUE_IDS.THREE]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.THREE])],
    [Card(SUITS[SUIT_IDS.SPADES], VALUES[VALUE_IDS.KING]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.SEVEN]), Card(SUITS[SUIT_IDS.SPADES], VALUES[VALUE_IDS.THREE]), Card(SUITS[SUIT_IDS.CLUBS], VALUES[VALUE_IDS.THREE]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.THREE])],
    [Card(SUITS[SUIT_IDS.SPADES], VALUES[VALUE_IDS.KING]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.KING]), Card(SUITS[SUIT_IDS.SPADES], VALUES[VALUE_IDS.NINE]), Card(SUITS[SUIT_IDS.CLUBS], VALUES[VALUE_IDS.NINE]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.EIGHT])],
    [Card(SUITS[SUIT_IDS.SPADES], VALUES[VALUE_IDS.KING]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.KING]), Card(SUITS[SUIT_IDS.SPADES], VALUES[VALUE_IDS.NINE]), Card(SUITS[SUIT_IDS.CLUBS], VALUES[VALUE_IDS.THREE]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.EIGHT])],
    [Card(SUITS[SUIT_IDS.SPADES], VALUES[VALUE_IDS.KING]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.SEVEN]), Card(SUITS[SUIT_IDS.SPADES], VALUES[VALUE_IDS.FIVE]), Card(SUITS[SUIT_IDS.CLUBS], VALUES[VALUE_IDS.TWO]), Card(SUITS[SUIT_IDS.HEARTS], VALUES[VALUE_IDS.THREE])]    
]
