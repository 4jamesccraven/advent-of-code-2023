#include<iostream>
#include<iomanip>
#include<grid.h>

int main (int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Invalid number of arguments; expected file name" << std::endl;
        return -1;
    }

    std::string filename(argv[1]);
    try {
        grid mainGrid(filename);
        if (mainGrid.getHeight() <= 50 && mainGrid.getWidth() <= 50) mainGrid.printGrid(std::cout);
        mainGrid.findNumbers();
        mainGrid.validateNumbers();
        std::cout << mainGrid.getValidSum() << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}