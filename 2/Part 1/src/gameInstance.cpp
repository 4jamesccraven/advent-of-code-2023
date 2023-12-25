#include <gameInstance.h>

std::vector<std::string> parseGameLine(std::string line, int* id) {
    //erase "Game"
    line.erase(0, 4);

    //get game ID
    if (id != nullptr) *id = std::stoi(line.substr(0, line.find(":")));
    line.erase(0, line.find(":") + 2);
    
    //find all areas between the ';'s
    std::vector<std::string> pulls = split(line, "; ");

    return pulls;
}

std::vector<std::string> split(std::string line, std::string delimiter) {    
    //convert delimiter to regex iterator
    std::regex delimiterAsRegex(delimiter);
    std::sregex_token_iterator it(line.begin(), line.end(), delimiterAsRegex, -1);
    std::sregex_token_iterator end;
    
    //take result of iterations and add it to the return vector
    std::vector<std::string> splitString;
    while (it != end) {
        splitString.push_back(*it);
        ++it;
    }
    
    return splitString;
}

cubes_t toCubes(std::string cubeString) {
    cubes_t cubesFormatted = {0, green};
    
    std::stringstream cubeStream;
    cubeStream.str(cubeString);
    
    std::string colour;
    int quantity;

    cubeStream >> quantity >> colour;

    if (cubeStream.fail()) {
        throw std::runtime_error("Bad cube read");
    }

    std::unordered_map<std::string, cube_colours> colourMap = {
        {"red", red},
        {"green", green},
        {"blue", blue}
    };

    auto conversion = colourMap.find(colour);
    if (conversion != colourMap.end()) {
        cubesFormatted.quantity = quantity;
        cubesFormatted.colour = conversion->second;
    }
    else {
        throw std::runtime_error("Bad conversion");
    }

    return cubesFormatted;
}
