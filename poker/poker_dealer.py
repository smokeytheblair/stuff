import argparse
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
    parser = argparse.ArgumentParser(description="Pick a name")
    parser.add_argument('--hand-size', type=int, default=5, help='number of cards per player')
    parser.add_argument('--num-players', type=int, default=5, help='number of players')
    parser.add_argument('--num-decks', type=int, default=1, help='number of decks to shuffle together')

    args = parser.parse_args()
    num_players = args.num_players
    hand_size = args.hand_size
    num_decks = args.num_decks

    deck = DeckOfCards(num_decks)
    players = []

    for i in range(num_players):
        players.append(PokerPlayer("Player", i))

    dealer = PokerDealer(deck, players, hand_size)    

    dealer.shuffle_cards()

    dealer.deal_cards()
    # dealer.deal_cards_tests()

    for player in players:
        hand_as_string = player.hand_to_string(player.hand)
        print(f'{player.name} {player.number} : {hand_as_string}')

    print('==========')

    if hand_size == 2:
        # playing Texas Hold'em
        #deal the flop
        flop = []
        # burn a card
        dealer.deal_card()
        for i in range(3):
            flop.append(dealer.deal_card())

        print(f"Flop: {[card.to_string() for card in flop]}")

        #deal turn
        # burn a card
        dealer.deal_card()
        turn = dealer.deal_card()
        print(f"Turn: {turn.to_string()}")

        #deal river
        # burn a card
        dealer.deal_card()
        river = dealer.deal_card()
        print(f"River: {river.to_string()}")

        for player in players:
            player.receive_card(flop[0])
            player.receive_card(flop[1])
            player.receive_card(flop[2])
            player.receive_card(turn)
            player.receive_card(river)

    print('==========')

    for player in players:
        hand_key, hand_value = await player.evaluate_hand()
        hand_as_string = player.hand_to_string(hand_key)
        hand_name = player.hand_name_to_string(hand_value)
        print(f'{player.name} {player.number} : {hand_as_string}\t{hand_name}')


if __name__ == "__main__":
    asyncio.run(main())
