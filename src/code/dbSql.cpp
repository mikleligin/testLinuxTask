#include "dbSql.h"

int dataBase::callback(void* data, int argc, char** argv, char** azColName) {
    std::vector<Object>* objects = reinterpret_cast<std::vector<Object>*>(data);
    Object obj;

    for (int i = 0; i < argc; i++) {
        if (azColName[i] == std::string("name")) {
            obj._name = argv[i] ? argv[i] : "NULL";
        } else if (azColName[i] == std::string("x")) {
            obj._x = argv[i] ? atof(argv[i]) : 0.0;
        } else if (azColName[i] == std::string("y")) {
            obj._y = argv[i] ? atof(argv[i]) : 0.0;
        } else if (azColName[i] == std::string("type")) {
            obj._type = argv[i] ? argv[i] : "NULL";
        } else if (azColName[i] == std::string("creation_time")) {
            obj._creationTime = argv[i] ? atol(argv[i]) : 0;
        }
    }

    objects->push_back(obj);
    return 0;
}

void dataBase::getObjects(sqlite3* db, std::vector<Object>& objects, const char* sql) {
    char* errorMessage;
    if (sqlite3_exec(db, sql, callback, &objects, &errorMessage) != SQLITE_OK) {
        std::cerr << "Error retrieving data: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

objectList dataBase::loadFromDatabase(sqlite3* db, const char* query) {
    objectList objList;
    std::vector<Object> tempObjects;
    getObjects(db, tempObjects, query);

    for (const auto& obj : tempObjects) {
        objList.addObject(obj);
    }

    return objList;
}
