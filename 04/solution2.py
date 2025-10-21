from sys import argv
from typing import List, Tuple, Dict

Card = Tuple[List[int], List[int]]


def process_line(line: str) -> Card:
    '''
    Processes a string of form \"Card n: n n n ... | n n n ....\"
    into two lists [n, n, n, ...] and [n, n, n, ...] where n represents
    any integer
    '''
    colon = line.index(':')
    line = line[colon + 2:]

    avail, win = line.split('|')

    avail = [int(val) for val in filter(lambda x: x != '', avail.split(' '))]
    win = [int(val) for val in filter(lambda x: x != '', win.split(' '))]

    return avail, win


# Concept for solution developed in conjunction with https://github.com/eagle79
def find_solution(cards: List[Card]) -> int:
    card_count: Dict[int, int] = {i: 1 for i in range(1, len(cards) + 1)}

    for card_no, card in enumerate(cards, start=1):
        avail, win = card

        matches = len([num for num in avail if num in win])

        if matches != 0:
            for i in range(1, matches + 1):
                card_count[card_no + i] += card_count[card_no]

    return sum(card_count.values())


def main() -> None:
    try:
        with open(argv[1], 'r') as f:
            lines: 'List[str]' = [line for line in f]
    except IndexError:
        print('No valid file provided')
        return
    except FileNotFoundError:
        print('No valid file provided')
        return

    cards = [process_line(line) for line in lines]

    number_of_cards: int = find_solution(cards)

    print(number_of_cards)


if __name__ == '__main__':
    main()
