#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<gameInstance.h>

int main() {
    validSet queryCriteria = {{"Red", "Green", "Blue"}, {12, 13, 14}};
    
    std::string filename;
    std::ifstream fin;

    bool validFile = false;
    while(!validFile) {
        std::getline(std::cin >> std::ws, filename);
        fin.open(filename);
        validFile = fin.is_open();
        if (!validFile) std::cerr << "Invalid file name, try again." << std::endl;
    }

    std::vector<instance> validGames;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream buffer;
        buffer.str(line);
        
        std::string stringFromBuffer;
        buffer >> stringFromBuffer;

        if(stringFromBuffer != "Game") continue;

        int id = 0;
        buffer >> id;

        

    } 

    return 0;
}