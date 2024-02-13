import asyncio

from deck_of_cards import DeckOfCards
from poker_dealer import PokerDealer
from poker_player import PokerPlayer


async def play_poker(hub):
    num_decks = int(hub.OPT['poppy']['decks'])
    num_players = int(hub.OPT['poppy']['players'])
    hand_size = int(hub.OPT['poppy']['hand'])

    print(f'Shuffling {num_decks} decks together.')
    print(f'{num_players} players sitting down at the table.')
    print(f'Dealing {hand_size} cards to each player.')

    deck = DeckOfCards(num_decks)
    players = []

    for i in range(num_players):
        players.append(PokerPlayer("Player", i))

    dealer = PokerDealer(deck, players, hand_size)

    dealer.shuffle_cards()

    run_tests = hub.OPT['poppy']['tests']

    if run_tests is False:
        dealer.deal_cards()
    else:
        print(f'test == {run_tests}')
        dealer.deal_cards_tests()

    for player in players:
        hand_as_string = player.hand_to_string()
        player_hand = await player.evaluate_hand()
        hand_name = player.hand_name_to_string(player_hand)
        print(f'{player.name} {player.number} : {hand_as_string}\t{hand_name}')


def __init__(hub):
    print('Let\'s play poker!')

    hub.tools.conf.integrate('poppy', loader='yaml', roots=True)

    asyncio.run(hub.poker.init.play_poker())
