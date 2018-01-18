#include "dbmain.hpp"
#include"aes.h"
#include"config.h"
#include<QMessageBox>

DB_ABSTRACT_CPP(main);



void dbmain::install(void){
    this->query(
                "CREATE TABLE Friends(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "nick varchar(255),"
                " publickey varchar(255) );",
                "insert into Friends(nick,publickey) values(\"Self\",'Self'); ",
                "CREATE TABLE Messages(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "message varhcar(255),"
                " `chat_id` id INTEGER, from_me BOOLEAN );",
                "insert into Messages(message, `chat_id`, `from_me`) values('Welcome to ISIS-Mess(e)anger, is your self messages', 1, 1); "
                );


    installed=true;
}

QList<QString> * dbmain::getMessages(const char * nickname){
    AES aes( PassOfGuy, UsernameOfGuy );

    QList<QString> * returns = new QList<QString>();

//msgs

    QSqlQuery msgQuery(this->db);
    msgQuery.prepare("SELECT message, from_me FROM Messages WHERE chat_id=:id ;");

    msgQuery.bindValue(":id", getIDFromNickname(nickname));
    msgQuery.exec();
    qDebug() <<  msgQuery.lastError();


//QSqlRecord rec;
//rec = q.record();
//index = rec.indexOf("message");
//int from_me = rec.indexOf("from_me");



    qDebug() << "To first" <<  msgQuery.value(0).toString();

    while(  msgQuery.next() ){
        qDebug() << "Add";

        qDebug() <<  msgQuery.value(0).toString() <<  msgQuery.value(1).toString();

        if( msgQuery.value(1).toBool())
            returns->append( QString("I: ") +  msgQuery.value(0).toString() + "\n");
        else
            returns->append(QString(nickname) + QString(": ") +  msgQuery.value(0).toString() + "\n");
    }



return returns;

}

void dbmain::addMessage(const char *message, int chat_id, bool FromMe){
    AES aes( PassOfGuy, UsernameOfGuy );


    this->q.prepare("INSERT INTO Messages(message, chat_id, from_me) values(:message, :chat_id, :from_me);");
    char * msgecnrypted = (char*)aes.encrypt(message);
    this->q.bindValue(":message", msgecnrypted);
    this->q.bindValue(":chat_id", chat_id);
    this->q.bindValue(":from_me", FromMe);
    this->q.exec();
    delete [] msgecnrypted;
}

dbmain::dbmain(bool installing){
    getDB("main.sqlite");
    if(installing){
        qDebug() << "Installing";
        this->install();
    }
}

dbmain::dbmain()
{
    getDB("main.sqlite");
}

