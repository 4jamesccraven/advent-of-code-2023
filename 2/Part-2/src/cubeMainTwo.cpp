#include<iostream>
#include<fstream>
#include<gameInstance.h>

unsigned long long determineMinimums(std::vector<std::string> pulls);

std::vector<std::string> getInstances(std::vector<std::string> pulls);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Invalid number of arguments; expected file name" << std::endl;
        return -1;
    }
    
    std::ifstream fin;
    std::string filename = argv[1];

    bool validFile = false;
    while (!validFile) {
        fin.open(filename);
        if (fin.is_open()) validFile = true;
        else {
            std::cerr << "Invalid filename, try again." << std::endl;
            std::getline(std::cin >> std::ws, filename);
        }
    }

    std::vector<std::string> games;
    while (!fin.eof()) {
        std::string line;
        std::getline(fin >> std::ws, line);

        games.push_back(line);
    }

    int trash = 0;
    unsigned long long total = 0;
    for (auto game : games) {
        total += determineMinimums(getInstances(parseGameLine(game, &trash)));
    }

    std::cout << total << std::endl;

    return 0;
}

unsigned long long determineMinimums(std::vector<std::string> pulls) {
    cubes_t greenMax = {0, green};
    cubes_t redMax = {0, red};
    cubes_t blueMax = {0, blue};

    for (auto pull : pulls) {
        try {
            cubes_t comparison = toCubes(pull);
            switch(comparison.colour) {
            case red:
                if (comparison.quantity > redMax.quantity) redMax.quantity = comparison.quantity;
                break;
            case green:
                if (comparison.quantity > greenMax.quantity) greenMax.quantity = comparison.quantity;
                break;
            case blue:
                if (comparison.quantity > blueMax.quantity) blueMax.quantity = comparison.quantity;
                break;
            }
        }
        catch (std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    unsigned long long total = greenMax.quantity * redMax.quantity * blueMax.quantity;

    return total;
}

std::vector<std::string> getInstances(std::vector<std::string> pulls) {
    std::vector<std::string> instances;
    
    for (auto pull : pulls) {
        std::vector<std::string> toAppend = split(pull, ", ");
        for (auto instance : toAppend) {
            instances.push_back(instance);
        }
    }

    return instances;
}
