#include<iostream>
#include<fstream>
#include<numeric>
#include<gameInstance.h>

//Validates a game to determine if it exceeds the validation set
bool validateGame(std::vector<std::string> game, std::array<cubes_t, 3> validationSet = instance::validationSet);

int main(int argc, char *argv[]) {
    //make sure there is at least one argument past the .exe
    if (argc != 2) {
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

    std::vector<std::string> games;
    while (!fin.eof()) {
        std::string game;
        std::getline(fin >> std::ws, game);
        games.push_back(game);
    }

    std::vector<int> validGames;
    for (auto game : games) {
        int id = 0;
        bool validGame = validateGame(parseGameLine(game, &id));
        if (validGame) validGames.push_back(id);
    }

    std::cout << std::accumulate(validGames.begin(), validGames.end(), 0);

    return 0;
}

bool validateGame(std::vector<std::string> game, std::array<cubes_t, 3> validationSet) {
    bool continueSignal = true;
    for (auto pull : game) {
        std::vector<std::string> cubeGroups = split(pull, ", ");
        for (auto group : cubeGroups){ 
            try {
                cubes_t comparison = toCubes(group);

                switch(comparison.colour) {
                    case green:
                        continueSignal = comparison.quantity <= validationSet[0].quantity;
                        break;
                    case red:
                        continueSignal = comparison.quantity <= validationSet[1].quantity;
                        break;
                    case blue:
                        continueSignal = comparison.quantity <= validationSet[2].quantity;
                        break;
                }

                if (!continueSignal) {
                    return continueSignal;
                }
            }
            catch (std::runtime_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
    return continueSignal;
}