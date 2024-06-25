#include<iostream>
#include<string>
#include<vector>

typedef unsigned long long index_t;

struct coordinate {
    index_t x;
    index_t y;
};

struct number {
    coordinate begin;
    coordinate end;
    unsigned int length;
};

class grid {
public:
    grid(std::string inFilename);

    index_t getHeight();
    index_t getWidth();

    void findNumbers();
    bool hasSymbol(coordinate begin, coordinate end);
    index_t getValidSum();
    void validateNumbers();
    index_t toInteger(number num);

    void printGrid(std::ostream& os);
    void printNumbers(std::ostream& os);
protected:
    std::vector<std::vector<char>> internal_grid_;
    std::vector<number> numbers_;
    std::vector<index_t> valid_numbers_;
    index_t width, height;
};

std::ostream& operator<<(std::ostream &os, number num);