#include<fstream>
#include<sstream>
#include<grid.h>

grid::grid(std::string inFilename) {
    std::ifstream input;
    input.open(inFilename);

    if(!input.is_open()) {
        throw std::runtime_error("Invalid file, could not be opened.");
    }

    while (!input.eof()) {
        std::string line;
        std::getline(input >> std::ws, line);

        if (!input.fail()) {
            std::stringstream rowBuffer;
            rowBuffer.str(line);
            
            std::vector<char> newRow;
            char extracted;
            for (index_t i = 0; i < static_cast<index_t>(line.size()); i++) {
                rowBuffer >> extracted;
                newRow.push_back(extracted);
            }
            internal_grid_.push_back(newRow);
        }
    }

    this->height = internal_grid_.size();
    (height > 0) ? this->width = internal_grid_.at(0).size() : this->width = 0;
}

index_t grid::getHeight() {
    return this->height;
}

index_t grid::getWidth() {
    return this->width;
}

void grid::findNumbers() {
    index_t currY = 0;
    for (auto row : internal_grid_) {
        for(auto it = row.begin(); it != row.end(); it++) {
            if (std::isdigit(*it)) {
                index_t beginX = std::distance(row.begin(), it);
                while (std::isdigit(*it)) {
                    it++;
                }
                it--;
                index_t endX = std::distance(row.begin(), it);

                number toAppend = {{beginX, currY}, {endX, currY}, static_cast<unsigned int>(endX - beginX + 1)};
                numbers_.push_back(toAppend);
            }
        }
        currY++;
    }
}

bool grid::hasSymbol(coordinate begin, coordinate end) {
    bool validTop = begin.y != 0;
    bool validBottom = begin.y < internal_grid_.size() - 1;
    bool validRight = end.x < internal_grid_.at(begin.y).size() - 1;
    bool validLeft = begin.x != 0;

    bool usedNumber = false;

    if (validLeft && !usedNumber) usedNumber = (internal_grid_.at(begin.y).at(begin.x - 1) != '.');
    if (validRight && !usedNumber) usedNumber = (internal_grid_.at(end.y).at(end.x + 1) != '.');
    if (validTop && !usedNumber) {
        for (index_t i = begin.x; i < (end.x + 1); i++) {
            usedNumber = (internal_grid_.at(begin.y - 1).at(i) != '.');
            if (usedNumber) break;
        }
    }
    if (validBottom && !usedNumber) {
        for (index_t i = begin.x; i < (end.x + 1); i++) {
            usedNumber = (internal_grid_.at(begin.y + 1).at(i) != '.');
            if (usedNumber) break;
        }
    }
    if (validRight && validTop && !usedNumber) usedNumber = (internal_grid_.at(begin.y - 1).at(end.x + 1) != '.');
    if (validRight && validBottom && !usedNumber) usedNumber = (internal_grid_.at(begin.y + 1).at(end.x + 1) != '.');
    if (validLeft && validTop && !usedNumber) usedNumber = (internal_grid_.at(begin.y - 1).at(begin.x - 1) != '.');
    if (validLeft && validBottom && !usedNumber) usedNumber = (internal_grid_.at(begin.y + 1).at(begin.x - 1) != '.');

    return usedNumber;
}

index_t grid::getValidSum() {
    index_t sum = 0;
    for (auto num : valid_numbers_) {
        sum += num;
    }
    return sum;
}

void grid::validateNumbers() {
    for (auto num : numbers_) {
        if (this->hasSymbol(num.begin, num.end)) valid_numbers_.push_back(this->toInteger(num)); 
    }
}

index_t grid::toInteger(number num) {
    std::string numAsString = "";
    for (index_t i = 0; i < num.length; i++) {
        numAsString += internal_grid_.at(num.begin.y).at(num.begin.x + i);
    }

    return static_cast<index_t>(std::stoi(numAsString));
}

void grid::printGrid(std::ostream &os) {
    for(auto line : internal_grid_) {
        for (auto character : line) {
            os << character;
        }
        os << std::endl;
    }
}

void grid::printNumbers(std::ostream &os) {
    for (auto num : numbers_) {
        os << num << std::endl;
    }
}

std::ostream& operator<<(std::ostream &os, number num) {
    os << '(' << num.begin.x << ',' << num.begin.y << "), (" << num.end.x << ',' << num.end.y << "), Length: " << num.length;
    return os;
}