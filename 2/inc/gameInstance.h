#include<unordered_map>
#include<string>

struct validSet{
    std::string colours[3];
    int values[3];
};

class instance {
public:
    instance(validSet inCriteria, unsigned int inID);
    void newPull(std::string colour, int count);
    bool isValid();
private:
    unsigned int game_id_;
    std::unordered_map<std::string, int> highest_possibility_;
    validSet criteria_;
};