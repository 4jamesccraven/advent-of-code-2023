#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>

int parseLine(std::string line);

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
    while(!fin.eof()) {
        std::string line = "";

        //get line from file
        std::getline(fin >> std::ws, line);

        //if the line isn't empty, parse it
        if(!line.empty()) numbersFromLines.push_back(parseLine(line));
    }

    //sum all the values
    int total = 0;
    for (auto num : numbersFromLines) {
        total += num;
    }

    //output result
    std::cout << total << std::flush;
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
