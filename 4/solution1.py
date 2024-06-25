from sys import argv


def main() -> None:
    assert argv[1]

    with open(argv[1], 'r') as f:
        cards = [line.strip() for line in f]

    cards = [card[card.index(':') + 1:].strip() for card in cards]

    cards = [card.split(' | ') for card in cards]

    cards = [[side.split(' ') for side in card] for card in cards]

    cards = [[[val for val in side if val != '']
             for side in card]
             for card in cards]

    cards = [[[int(val) for val in side]
             for side in card]
             for card in cards]

    cards = [len([val for val in card[1] if val in card[0]]) for card in cards]

    cards = [val if val < 2 else 2**(val - 1) for val in cards]

    cards = sum(cards)

    print(cards)


if __name__ == '__main__':
    main()
