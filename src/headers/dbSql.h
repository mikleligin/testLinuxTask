#ifndef DBSQL_H
#define DBSQL_H

#include <sqlite3.h>
#include <vector>
#include <string>
#include "structs.h"
#include "objectList.h"
class dataBase {
    public:
    static int callback(void* data, int argc, char** argv, char** azColName);
    void getObjects(sqlite3* db, std::vector<Object>& objects, const char* sql);
    objectList loadFromDatabase(sqlite3* db, const char* query);
};

#endif
