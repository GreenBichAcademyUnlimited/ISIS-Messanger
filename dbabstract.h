#ifndef DBABSTRACT_H
#define DBABSTRACT_H
#include <QtSql>


class dbAbstract
{
protected:
    bool error;
    QSqlDatabase * db;
    bool getError(void){
        return this->error;
    }

    void getDB(const char * type="QSQLITE", const char * dbname="DBQ=friends.sql");
    void virtual query(const char * ) = 0;

public:
    ~dbAbstract();
};

#endif // DBABSTRACT_H
