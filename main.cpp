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
#include "objectList.h"
#include "Groups.h"
#include "dbSql.h"

// Group "Type" owerflow, when this value set 
#define typeOferflowFlag 2


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

// Grouping menu finction
void groupChoise(objectList objList, std::string outputFileName){

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
        group.saveToFile(outputFileName);
        std::cout << "Результаты сохранены в файл.\n";
    }
}

int main(int argc, char* argv[]){
    
    if(argc<2){
        std::cerr << "Usage 'Inputfilename' 'outputFileName'";
        return 0;
    }
    objectList objList;
    Groups group = objList.groupByName();
    group.printGroups();
    objList = readObjectsFromFile(argv[1]);
    int choice;
    do {
        
        std::cout << "\n Выберите действие:\n";
        std::cout << "1. Прочитать из файла\n";
        std::cout << "2. Добавить объект\n";
        std::cout << "3. Группировка\n";
        std::cout << "4. Вывод всех объектов\n";
        std::cout << "5. Выгрузить из базы\n";
        std::cout << "6. Выход\n";
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
                
                groupChoise(objList, argv[2]);
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
                sqlite3* db;
                dataBase sql;
                int exit = sqlite3_open("../test.db", &db);
                if (exit) {
                    std::cerr << "Error open DB: " << sqlite3_errmsg(db) << std::endl;
                    return exit;
                }
                std::cout << "\n\nУспешно выгружено из базы\n\n";
                objList = sql.loadFromDatabase(db, "SELECT name, x, y, type, creation_time FROM objects;");
                objList.printObjects();
                break;
            }
            case 6:{

                std::cout << "Выход из программы.\n";
                break;
            }
            default:
                std::cout << "Неверный выбор. Повторите попытку.\n";
        }
    }
    while (choice != 6);
    return 0;
}