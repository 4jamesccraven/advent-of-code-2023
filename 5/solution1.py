import argparse
from typing import List, Dict, Tuple

SeedMap = Dict[Tuple[str, str], List[Tuple[int, int, int]]]


def parse_file(filename: str) -> SeedMap:
    try:
        with open(filename, 'r') as f:
            lines: List[str] = [line for line in f]
    except FileNotFoundError:
        print(f'{filename} is not a valid file.')

    # Break into sub-lists on based on empty lines
    maps: List[List[str]] = []
    while True:
        try:
            next_newline = lines.index('\n')
            maps.append(lines[:next_newline])

            lines = lines[next_newline + 1:]
        except ValueError:
            maps.append(lines)
            break

    # Remove all newlines
    maps = [[line.replace('\n', '') for line in m] for m in maps]

    # Create the seed list by removing 'seeds: ' and then splitting
    seeds = maps[0][0][7:].split(' ')
    seeds = [int(seed) for seed in seeds]

    maps.pop(0)

    # Convert to a dictionary that maps the 'type' of map (e.g., seed to soil)
    # to the range data as ints
    maps_final = {}
    for m in maps:
        # Header; e.g., ('seed', 'soil')
        header = m[0][:-5]
        header = tuple(header.split('-to-'))

        # Convert all other lines to tuples of ints
        ranges = [tuple(int(x) for x in line.split(' ')) for line in m[1:]]

        # Place the ranges in the dict at the mapping type
        maps_final[header] = ranges

    return maps_final, seeds


def cascading_search(starting_val: int,
                     seed_map: SeedMap,
                     source_type: str = 'seed') -> int:
    '''
    Searches recursively through a seed map to find a location value
    '''
    if source_type == 'location':
        return starting_val

    # Find the next applicable mapping and note its return type
    mapping = next(filter(lambda x: x[0] == source_type, seed_map))
    result_type = mapping[1]
    mapping = seed_map[mapping]

    # Appropriately map starting_val and then search the next map
    for dest, source, length in mapping:
        valid_upper = source + length
        if starting_val >= source and starting_val < valid_upper:
            return cascading_search(dest + (starting_val - source),
                                    seed_map, result_type)
    else:
        return cascading_search(starting_val, seed_map, result_type)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('file', help='Input file')
    args = parser.parse_args()

    seed_map, seeds = parse_file(args.file)

    seed_locations = [cascading_search(seed, seed_map) for seed in seeds]

    result = min(seed_locations)

    print(result)


if __name__ == '__main__':
    main()
