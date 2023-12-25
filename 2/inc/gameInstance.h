#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<regex>
#include<sstream>
#include<unordered_map>

enum cube_colours {
    green = 0,
    red = 1,
    blue = 2
};

struct cubes_t {
    int quantity;
    cube_colours colour;
};

namespace instance {
    const std::array<cubes_t, 3> validationSet = {{ {13, green}, {12, red}, {14, blue} }};
}

//Extracts a game id and appends it to an external vector, then calls the split function
//to return a vector of pulls
std::vector<std::string> parseGameLine (std::string line, int& id);

//Splits a string by a delimiter and puts it in a vector
std::vector<std::string> split(std::string line, std::string delimiter);

//Validates a game to determine if it exceeds the validation set
bool validateGame(std::vector<std::string> game, std::array<cubes_t, 3> validationSet = instance::validationSet);

bool validatePull(std::vector<cubes_t> pulls, std::array<cubes_t, 3> validationSet);

//converts a formatted string to a cube data type
cubes_t toCubes(std::string cubeString);