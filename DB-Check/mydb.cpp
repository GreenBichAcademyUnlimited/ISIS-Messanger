#include "mydb.h"

template < class Arg, class ... Args> void mydb::query(Arg arg, Args ... args){
    q.exec(arg);
    qDebug() << "query::" << arg;

    qDebug() << q.lastError().text();
    this->query(args...);
}

template < class ... Args> void mydb::query(Args ... args ){
    this->query(args...);
}


mydb::mydb()
{
       this->getDB();
       this->query("CREATE TABLE checktable ( id INTEGER PRIMARY KEY AUTOINCREMENT, nick varchar(255) ); ", "someshit");
       qDebug() << this->getError();
}

