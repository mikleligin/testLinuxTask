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
#include <structs.h>
#include <Groups.h>
#pragma once

#define typeOferflowFlag 2




class objectList{
    public:
    
        void addObject(Object object);
        void printObjects();
        Groups groupByDistance();
        Groups groupByName();
        Groups groupByType();
        Groups groupByTime();
    private:
        std::vector<Object> _objectList;
        std::string countOfSame(std::string strTemplate){
            
            int counter = 0;
            for (const Object& obj : _objectList) {
                counter += obj._type == strTemplate?1:0;
            }
            return counter>=typeOferflowFlag?strTemplate:"Разное";
        }

};