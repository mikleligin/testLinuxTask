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
#define typeOferflowFlag 2


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
class Groups{
    
    public:

        void addGroup(Group group) {
            _groupList.push_back(group);
        }
        void printGroups(){
                for(Group& gr: _groupList){
                    std::cout << gr._name << std::endl;
                    for(Object& obj: gr._objectListGroup){
                        std::cout << "\t" << obj._name << std::endl;
                    }
            }
        }
        void saveToFile()
        {
            std::ofstream out("log.txt", std::ios::app);
            if (out.is_open())
            {
                for(Group& gr: _groupList){
                out << gr._name << std::endl;
                for(Object& obj: gr._objectListGroup){
                    out << "\t" << obj._name << " " << obj._x << " " << std::endl;
                }
            }
            }
        }

    private:
        std::vector<Group> _groupList;
};

class objectList{
    public:
    
        void addObject(Object object){
            _objectList.push_back(object);
        }
        void printObjects(){
            for(Object& obj: _objectList){
                printf("%s %f %f %s %f\n", obj._name.c_str(), obj._x, obj._y, obj._type.c_str(), obj._creationTime);  
            }
        }
        Groups groupByDistance(){
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
        Groups groupByName(){
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

        Groups groupByType(){
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
        Groups groupByTime(){
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


objectList readObjectsFromFile(const std::string& filename) {
    objectList objects;
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Object obj;
        iss >> obj._name >> obj._x >> obj._y >> obj._type >> obj._creationTime;
        objects.addObject(obj);
    }
    
    return objects;
}

Object addObject() {
    Object newObj;
    std::cout << "Введите имя объекта: ";
    std::cin >> newObj._name;
    std::cout << "Введите координаты (x, y): ";
    std::cin >> newObj._x >> newObj._y;
    std::cout << "Введите тип объекта: ";
    std::cin >> newObj._type;
    return newObj;
}
void groupChoise(objectList objList){

    system("clear");
    Groups group = objList.groupByName();
    int choice;
    do {
        
        std::cout << "1. Группировка по расстоянию\n";
        std::cout << "2. Группировка по первой букве\n";
        std::cout << "3. Группировка по типу\n";
        std::cout << "4. Группировка по времени\n";
        std::cout << "5. Выйти\n";
        std::cin >> choice;
        system("clear");
        switch (choice) {
            case 1:{
                std::cout << "\n\n\n\n";
                group = objList.groupByDistance();
                group.printGroups();
                std::cout << "\n\n";
                break;
            }
            case 2:{
                
                std::cout << "\n\n\n\n";
                group = objList.groupByName();
                group.printGroups();
                std::cout << "\n\n";

                break;
            }
            case 3:{

                std::cout << "\n\n\n\n";
                group = objList.groupByType();
                group.printGroups();
                std::cout << "\n\n";
                
                break;
            }
            case 4:{

                std::cout << "\n\n\n\n";
                group = objList.groupByTime();
                group.printGroups();
                std::cout << "\n\n";
                break;
            }
            case 5:{

                break;
            }
            default:{

                std::cout << "Неверный выбор. Повторите попытку.\n";
            }
        }
    }
    while(choice!=5);
    std::cout << "Сохранить в файл? \n 1. Да\n 2. Нет" << std::endl; 
    std::cin >> choice;
    if(choice == 1){
        group.saveToFile();
        std::cout << "Результаты сохранены в файл.\n";
    }
}

int main(int argc, char* argv[]){
    
    if(argc<2){
        std::cerr << "Usage -filename";
        return 0;
    }
    objectList objList;
    
    Groups group = objList.groupByName();
    group.printGroups();
    objList = readObjectsFromFile("1.txt");
    int choice;
    do {
        
        std::cout << "\n Выберите действие:\n";
        std::cout << "1. Прочитать из файла\n";
        std::cout << "2. Добавить объект\n";
        std::cout << "3. Группировка\n";
        std::cout << "4. Вывод всех объектов\n";
        std::cout << "5. Выход\n";
        std::cin >> choice;
        switch (choice) {
            case 1:{
                
                std::cout << "\n\n\n\n";
                system("clear");
                objList = readObjectsFromFile("1.txt");
                objList.printObjects();
                std::cout << "\n\n";
                break;
            }
            case 2:{

                system("clear");
                Object obj = addObject();
                objList.addObject(obj);

                break;
            }
            case 3:{
                
                groupChoise(objList);
                std::cout << "Результаты сохранены в файл.\n";
                break;
            }
            case 4:{

                std::cout << "Вывожу информацию\n";
                objList.printObjects();
                std::cout << "\n\n";
                break;
            }
            case 5:{

                std::cout << "Выход из программы.\n";
                break;
            }
            default:
                std::cout << "Неверный выбор. Повторите попытку.\n";
        }
    }
    while (choice != 5);
    return 0;
}