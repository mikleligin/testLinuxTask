#include "Groups.h"


void Groups::addGroup(Group group) {
            _groupList.push_back(group);
        }
void Groups::printGroups(){
        for(Group& gr: _groupList){
            std::cout << gr._name << std::endl;
            for(Object& obj: gr._objectListGroup){
                std::cout << "\t" << obj._name << " " << obj._x << " " << obj._y << " " << obj._type << " " << obj._creationTime << std::endl;
            }
    }
}
void Groups::saveToFile(const std::string filename)
{
    std::ofstream out(filename);
    if (out.is_open())
    {
        for(Group& gr: _groupList){
        out << gr._name << std::endl;
        for(Object& obj: gr._objectListGroup){
            out << "\t" << obj._name << " " << obj._x << " " << obj._y << " " << obj._type << " " << obj._creationTime << std::endl;
        }
    }
    }
}
