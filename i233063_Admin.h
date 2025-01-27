#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include<time.h>
using namespace std;


class Admin {
    const string adminKey = "Fitness is gold";

public:
    bool authenticateAdmin(const string& inputKey) {
        return inputKey == adminKey;
    }
};
