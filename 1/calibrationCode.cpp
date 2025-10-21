#include <algorithm>
#include <cctype>
#include <cstddef>
#include <numeric>
#include <print>
#include <ranges>
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

const std::array<std::string, 9> ENGLISH_DIGITS {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};

int parseLine(std::string line);
int parsePermissive(const std::string &line);

int main (int arc, char *argv[]) {
    //make sure there is at least one argument past the .exe
    if (arc != 2) {
        std::cerr << "Invalid number of arguments; expected file name" << std::endl;
        return -1;
    }

    std::ifstream fin;
    std::string filename = argv[1];

    //validate input filename
    bool validFile = false;
    while (!validFile) {
        fin.open(filename);
        if (fin.is_open()) validFile = true;
        else {
            std::cerr << "Invalid filename, try again." << std::endl;
            std::getline(std::cin >> std::ws, filename);
        }
    }

    //create a vector of numbers from lines for the final sum
    std::vector<int> numbersFromLines;
    std::vector<int> numbersPermissive;
    while(!fin.eof()) {
        std::string line = "";

        //get line from file
        std::getline(fin >> std::ws, line);

        //if the line isn't empty, parse it
        if(!line.empty()) {
            numbersFromLines.push_back(parseLine(line));
            numbersPermissive.push_back(parsePermissive(line));
        }
    }

    //sum all the values
    int p1 = std::accumulate(numbersFromLines.begin(), numbersFromLines.end(), 0);
    int p2 = std::accumulate(numbersPermissive.begin(), numbersPermissive.end(), 0);

    //output result
    std::println("Part 1: {}", p1);
    std::println("Part 2: {}", p2);
    return 0;
}

int parseLine(std::string line) {
    std::stringstream buffer;
    buffer.str(line);
    char first = ' ', last = ' ', charRead = ' ';
    bool firstFound = false;

    while (buffer >> charRead) {
        if (std::isdigit(charRead)) {
            if (!firstFound) {
                first = charRead;
                firstFound = true;
            } else {
                last = charRead;
            }
        }
    }
    if (last == ' ') last = first;

    //cast characters to string for concatenation
    std::string firstString = std::string(1, first);
    std::string lastString = std::string(1, last);

    std::string output =  firstString + lastString;

    //return the value only if the string isn't "  "
    return (first != ' ' && last !=' ') ? std::stoi(output) : 0;
}

int parsePermissive(const std::string &line) {
    using pair_t = std::pair<std::size_t, char>;

    auto candidates = std::views::iota(std::size_t{0}, line.size())
        | std::views::transform([&line](std::size_t i) -> std::optional<pair_t> {
              char c = line[i];

              if (std::isdigit(c))
                  return pair_t{i, c};

              for (std::size_t d = 0; d < ENGLISH_DIGITS.size(); d++) {
                  const auto &word = ENGLISH_DIGITS[d];
                  if (line.compare(i, word.size(), word) == 0) {
                      char digit_char = '1' + d;
                      return pair_t{i, digit_char};
                  }
              }
              return std::nullopt;
          })
        | std::views::filter([](const auto &opt) {return opt.has_value(); })
        | std::views::transform([](const auto &opt) { return *opt; });

    auto [min_pair, max_pair] = std::ranges::minmax(candidates, {}, &pair_t::first);

    return ((min_pair.second - '0') * 10) + (max_pair.second - '0');
}
