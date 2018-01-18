#ifndef DBABSTRACT_H
#define DBABSTRACT_H
#include <QtSql>
#include<QDebug>


#define DB_ABSTRACT_HPP\
    template < class Arg, class ... Args> void query(Arg arg, Args ... args);\
    template <class ... Args>  void query( Args ... args );



#define DB_ABSTRACT_CPP(classname)\
    \
template < class Arg, class ... Args> void db##classname ::query(Arg arg, Args ... args){\
    this->q.exec(arg);\
    qDebug() << "query::" << arg;\
    qDebug() << q.lastError().text();\
    this->query(args...);\
}\
template < class ... Args> void db##classname ::query(Args ... args ){\
    this->query(args...);\
}



/*
 * but what for?xD
 * */

class dbAbstract
{
protected:
    bool error=false;
    QSqlDatabase db;
    bool getError(void){
        return this->error;
    }

    void getDB(const char * dbname="local.sqlite", const char * driver="QSQLITE");

    void virtual query( void ) = 0;
    void virtual install(void)=0;
public:
    void reopen(void){
        this->q = QSqlQuery(this->db);
    }

    int getIDFromNickname(const char * nickname){
        this->q.prepare("Select id from Friends where nick=:nick");
        this->q.bindValue(":nick", nickname);
        this->q.exec();
        if( q.next() ){
            qDebug() << "ID FROM " << nickname << ":" << q.value(0).toInt();
            qDebug() << q.lastError();

            return q.value(0).toInt();
        }
        return -1;
    }

    QSqlQuery q;
    ~dbAbstract();
};

#endif // DBABSTRACT_H
