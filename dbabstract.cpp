#include "dbabstract.h"

void dbAbstract::getDB(const char * dbname, const char * driver){
    this->db = QSqlDatabase::addDatabase(driver);
    db.setHostName("localhost");
    db.setDatabaseName(dbname);
   if (!db.open()) {
       error=true;
       qDebug() << db.lastError().text();
   }
   else{
       q = QSqlQuery(this->db);
       qDebug() << "database was open";
   }
}



dbAbstract::~dbAbstract(){
   // if(this->q) delete [] q;
}


