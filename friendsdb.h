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
        this->q.prepare("Select * from Friends where nick=:nick");
        this->q.bindValue(":nick", nickname);
        this->q.exec();
        return this->q.boundValues();
    }
    bool addFriend(const char * nickname, const char * pubkey){
        if (getIDFromNickname(nickname) != -1 ) return false;
        this->q.prepare("Insert into Friends(nickname, pubkey) values(:nickname, :pubkey);");
        this->q.bindValue(":nickname",nickname);
        this->q.bindValue(":pubkey",pubkey);
        return true;
    }

    void install(void);
    dbfriends();

};

#endif // FRIENDSDB_H
