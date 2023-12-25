#include<iostream>
#include<fstream>
#include<numeric>
#include<gameInstance.h>

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
        bool validGame = validateGame(parseGameLine(game, id));
        if (validGame) validGames.push_back(id);
    }

    std::cout << std::accumulate(validGames.begin(), validGames.end(), 0);

    return 0;
}
