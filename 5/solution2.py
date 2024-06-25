# THIS SOLUTION IS INCOMPLETE
import argparse
import solution1
from typing import List, Tuple


def parse_seed_ranges(seeds: List[int]) -> List[Tuple[int, int]]:
    assert len(seeds) % 2 == 0

    # Makes ranges of form [m, n)
    r_val = []
    for i in range(len(seeds) // 2):
        r_val.append((seeds[i * 2], seeds[i * 2] + seeds[(i * 2) + 1]))

    return r_val


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('file', help='Input file')
    args = parser.parse_args()

    seed_map, no_fmt_seeds = solution1.parse_file(args.file)
    seeds = parse_seed_ranges(no_fmt_seeds)

    seeds = [tuple(solution1.cascading_search(x, seed_map) for x in val)
             for val in seeds]

    print(min(seeds, key=lambda x: x[0]))


if __name__ == '__main__':
    main()
