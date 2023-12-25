#include <gameInstance.h>

std::vector<std::string> parseGameLine(std::string line, int& id) {
    //erase "Game"
    line.erase(0, 4);

    //get game ID
    id = std::stoi(line.substr(0, line.find(":")));
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

bool validatePull(std::vector<cubes_t> pulls, std::array<cubes_t, 3> validationSet) {
    return false;
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
