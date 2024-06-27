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


def map_val(val: int,
            mapper: List[Tuple[int, int, int]]) -> int:
    for dest, source, length in mapper:
        if source <= val and val < (source + length):
            return dest + (val - source)
    else:
        return val


def break_range(vals: Tuple[int, int],
                map: List[Tuple[int, int, int]]) -> List[Tuple[int, int]]:
    ...


def solve(seed_map: solution1.SeedMap,
          ranges: List[Tuple[int, int]]) -> int:
    data_type = 'seed'

    while data_type != 'location':
        next_map = next(filter(lambda x: x[0] == data_type, seed_map))
        data_type = next_map[1]
        next_map = seed_map[next_map]
        new_ranges = []

        for r in ranges:
            x, y = r
            x_0 = map_val(x, next_map)
            y_0 = map_val(y, next_map)

            if y_0 - x_0 == y - x:
                new_ranges.append((x_0, y_0))

            else:
                for br in break_range(r, next_map):
                    new_ranges.append(br)

        ranges = new_ranges

    ranges = [r[0] for r in ranges]
    return min(ranges)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('file', help='Input file')
    args = parser.parse_args()

    seed_map, no_fmt_seeds = solution1.parse_file(args.file)
    seeds = parse_seed_ranges(no_fmt_seeds)

    print(solve(seed_map, seeds))


if __name__ == '__main__':
    main()
