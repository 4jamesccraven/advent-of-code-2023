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


def map_val(value: int,
            seed_map: solution1.SeedMap,
            source_type: str) -> Tuple[int, str]:
    '''
    Maps a value one level of depth into the Seedmap
    '''
    _, map_to = next(filter(lambda x: x[0] == source_type, seed_map))

    next_map = seed_map[(source_type, map_to)]

    for dest, source, length in next_map:
        source_upper = source + length
        if source <= value and value < source_upper:
            return dest + (value - source)
    else:
        return value, map_to


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('file', help='Input file')
    args = parser.parse_args()

    seed_map, no_fmt_seeds = solution1.parse_file(args.file)
    seeds = parse_seed_ranges(no_fmt_seeds)


if __name__ == '__main__':
    main()
