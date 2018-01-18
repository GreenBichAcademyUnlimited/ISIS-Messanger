#ifndef FRIENDSDB_H
#define FRIENDSDB_H
#include"dbabstract.h"

class dbmain : public dbAbstract
{
private:
    void install(void);
    bool installed;
public:
    DB_ABSTRACT_HPP;
    void query(void){};

    QMap<QString, QVariant> getFriend(const char * nickname){
        this->q.prepare("Select * from Friends where nick=:nick");
        this->q.bindValue(":nick", nickname);
        this->q.exec();
        return this->q.boundValues();
    }

    bool getInstalled(void){
        return this->installed;
    }

    bool addFriend(const char * nickname, const char * pubkey){
        if (getIDFromNickname(nickname) != -1 ) return false;
        this->q.prepare("Insert into Friends(nickname, pubkey) values(:nickname, :pubkey);");
        this->q.bindValue(":nickname",nickname);
        this->q.bindValue(":pubkey",pubkey);
        return true;
    }

    QMap<QString, QVariant> getLastMessage(const char * nickname){
        this->q.prepare("Select * from Messages where from=:nick");
        this->q.bindValue(":nick", nickname);
        this->q.exec();
        return this->q.boundValues();
    }

    void addMessage(const char * message, int, bool); // one = self
    QList<QString> * getMessages(const char * nickname);


    dbmain();
    dbmain(bool installing);

};

#endif // FRIENDSDB_H
