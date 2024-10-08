#include <iostream>
#include <vector>

#pragma once

struct Object{
    std::string _name;
    double _x;
    double _y;
    std::string _type;
    double _creationTime;
};

struct Group{
    std::string _name;
    std::vector<Object> _objectListGroup;
};