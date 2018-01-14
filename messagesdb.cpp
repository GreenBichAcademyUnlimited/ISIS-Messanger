#include "messagesdb.h"
#include"aes.h"
#include"config.h"

DB_ABSTRACT_CPP(message);

void dbmessage::install(void){
    this->query(
                "CREATE TABLE Messages(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "message varhcar(255),"
                " `from` id INTEGER, `to` ID INTEGER );"
                );
}



void dbmessage::addMessage(const char *message, int to, int from){
    AES aes( PassOfGuy, UsernameOfGuy );


    this->q.prepare("INSERT INTO Messages(message, from, to) values(:message, :from, :to);");
    char * msgecnrypted = (char*)aes.encrypt(message);
    this->q.bindValue(":message", msgecnrypted);
    this->q.bindValue(":from", from);
    this->q.bindValue(":to", to);
    this->q.exec();
    delete [] msgecnrypted;
}

dbmessage::dbmessage()
{

}

