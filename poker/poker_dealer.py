import asyncio
from deck_of_cards import DeckOfCards
from deck_of_cards import TEST_HANDS
from poker_player import PokerPlayer

class PokerDealer:

    def __init__(self, new_deck, new_players, new_hand_size):
        self.deck = new_deck
        self.players = new_players
        self.hand_size = new_hand_size

    def deal_card(self):
        return self.deck.draw_card()

    def deal_cards(self):
        # print(f'dealing {self.hand_size} cards to {len(self.players)} players.')
        for i in range(self.hand_size):
            for player in self.players:
                player.receive_card(self.deal_card())
    
    def deal_cards_tests(self):
        i = 0
        for player in self.players:
            player.receive_hand(TEST_HANDS[i%len(TEST_HANDS)])
            i += 1

    def shuffle_cards(self):
        self.deck.shuffle()


async def main():
    num_players = 10
    hand_size = 5
    num_decks = 10

    deck = DeckOfCards(num_decks)
    players = []

    for i in range(num_players):
        players.append(PokerPlayer("Player", i))

    dealer = PokerDealer(deck, players, hand_size)    

    dealer.shuffle_cards()

    dealer.deal_cards()
    # dealer.deal_cards_tests()

    for player in players:
        hand_as_string = player.hand_to_string()
        player_hand = await player.evaluate_hand()
        hand_name = player.hand_name_to_string(player_hand)
        print(f'{player.name} {player.number} : {hand_as_string}\t{hand_name}')
        

if __name__ == "__main__":
    asyncio.run(main())
