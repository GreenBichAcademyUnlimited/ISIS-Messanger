#include "dbabstract.h"

void dbAbstract::getDB(const char * type, const char * dbname){
    this->db = new QSqlDatabase;
    this->db->addDatabase(type);
    db->setDatabaseName(dbname);//"DBQ=friends.sql"
   if (!db->open()) {
       error=true;
   }
}

dbAbstract::~dbAbstract(){
    delete [] db;
}


