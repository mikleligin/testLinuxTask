
#include "iostream"
#include <vector>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <set>
#include <string>
#include <clocale>
#include <ctime>
#include <fstream>
#include <sstream>
//#include <objectList.h>
#include "structs.h"

#pragma once

class Groups{
    
    public:

        void addGroup(Group group);
        void printGroups();
        void saveToFile(const std::string filename);

    private:
        std::vector<Group> _groupList;
};