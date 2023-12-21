#include <gameInstance.h>

instance::instance(validSet inCriteria, unsigned int inID) : game_id_(inID), criteria_(inCriteria) {
    for (unsigned int i = 0; i < 3; i++)
        highest_possibility_[criteria_.colours[i]] = 0;
}

void instance::newPull(std::string colour, int count) {

}

bool instance::isValid() {

    return false;
}
