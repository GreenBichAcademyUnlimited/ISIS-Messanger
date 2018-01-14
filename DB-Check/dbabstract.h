#ifndef DBABSTRACT_H
#define DBABSTRACT_H
#include <QtSql>
#include<QDebug>


class dbAbstract
{
protected:
    bool error=false;
    QSqlDatabase db;
    QSqlQuery q;
    bool getError(void){
        return this->error;
    }

    void getDB(const char * driver="QSQLITE", const char * dbname="local.sqlite");
    void virtual query( void ) = 0;

public:
    ~dbAbstract();
};

#endif // DBABSTRACT_H
