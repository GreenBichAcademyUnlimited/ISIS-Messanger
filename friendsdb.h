#ifndef FRIENDSDB_H
#define FRIENDSDB_H
#include"dbabstract.h"

class dbfriends : public dbAbstract
{
private:
    DB_ABSTRACT_HPP;
    void query(void){};

public:
    QMap<QString, QVariant> getFriend(const char * nickname){
        this->q.prepare("Select * from friends where nick=:nick");
        this->q.bindValue(":nick", nickname);
        this->q.exec();
        return this->q.boundValues();
    }

    void install(void);
    dbfriends();

};

#endif // FRIENDSDB_H
