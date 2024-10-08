#include "objectList.h"


void objectList::addObject(Object object){
    _objectList.push_back(object);
}

void objectList::printObjects(){
    for(Object& obj: _objectList){
            printf("%s %f %f %s %f\n", obj._name.c_str(), obj._x, obj._y, obj._type.c_str(), obj._creationTime);  
        }
    
}
Groups objectList::groupByDistance(){
    Groups groups;
    std::vector<std::pair<double, std::string>> distanceThresholds = {
        {100, "До 100ед"},
        {1000, "До 1000ед"},
        {10000, "До 10000ед"},
    };

    std::vector<Group> groupList(distanceThresholds.size() + 1);
    for (size_t i = 0; i < distanceThresholds.size(); ++i) {
        groupList[i]._name = distanceThresholds[i].second;
    }
    groupList.back()._name = "Слишком далеко";
    for (const Object& obj : _objectList) {
        double distance = std::sqrt(pow(obj._x, 2) + pow(obj._y, 2));
        bool placed = false;
        for (size_t i = 0; i < distanceThresholds.size(); ++i) {
            if (distance < distanceThresholds[i].first) {
                groupList[i]._objectListGroup.push_back(obj);
                placed = true;
                break;
            }
        }
        if (!placed) {
            groupList.back()._objectListGroup.push_back(obj);
        }
    }
    for (Group& group : groupList) {
        groups.addGroup(group);
    }

    return groups;
}
Groups objectList::groupByName(){

    Groups groups;
    std::set<std::string> letterGroup;
    for (const Object& obj : _objectList) {
        std::string firstLetter = obj._name.substr(0, 2);
        unsigned char firstByte = firstLetter[0];
        unsigned char secondByte = firstLetter[1];
        if (firstByte == 0xD0) {
            if(secondByte >= 0x90 && secondByte <= 0xBF){

                letterGroup.insert(firstLetter);
                
            }
        }
    }
    std::vector<Group> groupLetter(letterGroup.size() + 1);
    size_t index = 0;
    for (std::string letter : letterGroup) {
        groupLetter[index]._name = letter;
        ++index;
    }
    groupLetter.back()._name = "#";

    for (const Object& obj : _objectList) {
        std::string firstLetter = obj._name.substr(0, 2);
        bool placed = false;
        
        for (size_t i = 0; i < letterGroup.size(); ++i) {
            if (firstLetter == groupLetter[i]._name) {
                groupLetter[i]._objectListGroup.push_back(obj);
                placed = true;
                break;
            }
        }
        
        if (!placed) {
            groupLetter.back()._objectListGroup.push_back(obj);
        }
    }

    for (Group& group : groupLetter) {
        groups.addGroup(group);
    }
    return groups;
}
Groups objectList::groupByType(){
    Groups groups;
    std::vector<std::string> typeGroup;
    for (const Object& obj : _objectList) {
    
        std::string x = countOfSame(obj._type);
        typeGroup.push_back(x);
    }
    
    std::sort(typeGroup.begin(), typeGroup.end());
    auto last = std::unique(typeGroup.begin(), typeGroup.end());
    typeGroup.erase(last, typeGroup.end());

    std::vector<Group> groupType(typeGroup.size() + 1);
    size_t index = 0;
    for (std::string type : typeGroup) {
        groupType[index]._name = type;
        ++index;
    }
    
    for (const Object& obj : _objectList) {
        bool placed = false;
        
        for (size_t i = 0; i < typeGroup.size(); ++i) {
            if (obj._type == groupType[i]._name) {
                groupType[i]._objectListGroup.push_back(obj);
                placed = true;
                break;
            }
        }
        
        if (!placed) {
            for (size_t i = 0; i < typeGroup.size(); ++i){
                if(typeGroup[i]=="Разное"){
                    groupType[i]._objectListGroup.push_back(obj);
                }
            }
        }
    }

    for (Group& group : groupType) {
        groups.addGroup(group);
    }
    return groups;
}
Groups objectList::groupByTime(){
    Groups groups;
    time_t currentTime = time(0);
    std::vector<std::pair<double, std::string>> timeThresholds = {
        {86400, "Сегодня"},
        {604800, "На этой неделе"},
        {2592000, "В этом месяце"},
    };

    std::vector<Group> groupList(timeThresholds.size() + 1);
    for (size_t i = 0; i < timeThresholds.size(); ++i) {
        groupList[i]._name = timeThresholds[i].second;
    }
    groupList.back()._name = "Ранее";
    for (const Object& obj : _objectList) {
        bool placed = false;
        for (size_t i = 0; i < timeThresholds.size(); i++) {
            if (obj._creationTime > timeThresholds[i].first) {
                
                groupList[i]._objectListGroup.push_back(obj);
                placed = true;
                break;
            }
        }
        if (!placed) {
            groupList.back()._objectListGroup.push_back(obj);
        }
    }
    for (Group& group : groupList) {
        groups.addGroup(group);
    }

    return groups;
}