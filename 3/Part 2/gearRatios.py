#This code doesn't work, it falls just short of what it's supposed to find. I'll debug it in the futurem, perhaps.

import sys

class grid:
    def __init__(self, filename):
        with open(filename, "r") as f:
            self.internal_grid = [line.strip() for line in f]
        self.width = len(self.internal_grid[0])
        self.height = len(self.internal_grid)
        self.stars = [[index for index, char in enumerate(line) if char == '*'] for line in self.internal_grid]

    def __getitem__(self, index):
        return self.internal_grid[index]

    def __repr__(self):
        return '\n'.join(self.internal_grid)
    
    def locate_entire_number(self, x, y):
        num = self.internal_grid[y][x]
        if not num.isdigit():
            raise ValueError
        if x != 0:
            i = 1
            previous = self.internal_grid[y][x - i]
            while previous.isdigit():
                num = previous + num
                i += 1
                if x - i >= 0:
                    previous = self.internal_grid[y][x - i]
                else:
                    break

        if x != (self.width - 1):
            i = 1
            next = self.internal_grid[y][x + i]
            while next.isdigit():
                num = num + next
                i += 1
                if x + i <= (self.width - 1):
                    next = self.internal_grid[y][x + i]
                else:
                    break
        
        return int(num)

    
    def find_numbers_around_star(self, x , y):
        left, right, top_one, top_two, bottom_one, bottom_two = 0, 0, 0, 0, 0, 0
        
        if x != 0 and self.internal_grid[y][x - 1].isdigit():
            left = self.locate_entire_number(x - 1, y)

        if x != (self.width - 1) and self.internal_grid[y][x + 1].isdigit():
            right = self.locate_entire_number(x + 1, y)

        if y != 0:
            if self.internal_grid[y - 1][x].isdigit():
                top_one = self.locate_entire_number(x, y - 1)
            else:
                if x != 0 and self.internal_grid[y - 1][x - 1].isdigit():
                    top_two = self.locate_entire_number(x - 1, y - 1)
                if x !=(self.height - 1) and self.internal_grid[y - 1][x + 1].isdigit():
                    top_two = self.locate_entire_number(x + 1, y - 1)

        if y != (self.height - 1):
            if self.internal_grid[y + 1][x].isdigit():
                bottom_one = self.locate_entire_number(x, y + 1)
            else:
                if x != 0 and self.internal_grid[y + 1][x - 1].isdigit():
                    bottom_one = self.locate_entire_number(x - 1, y + 1)
                if x != (self.height - 1) and self.internal_grid[y + 1][x + 1].isdigit():
                    bottom_two = self.locate_entire_number(x + 1, y + 1)

        list = [left, right, top_one, top_two, bottom_one, bottom_two]
        list = [x for x in list if x != 0]

        return tuple(list)
    
    def find_gear_ratios(self):
        numbers = []
        for idx, line in enumerate(self.stars):
            for star in line:
                numbers.append(self.find_numbers_around_star(star, idx))

        print(len(numbers))
        numbers = [num for num in numbers if len(num) == 2]
        print(len(numbers))
        return [num[0] * num[1] for num in numbers]

        

            

def main():
    if len(sys.argv) != 2:
        print("Usage: python gearRatios.py <filename>")
        sys.exit(1)

    print(f'Opening \'{sys.argv[1]}\'')
    schematic = grid(sys.argv[1])

    #print(schematic)

    print(sum(schematic.find_gear_ratios()))

    return

if __name__ == "__main__":
    main()