#include "friendsdb.h"
#include<QMessageBox>

DB_ABSTRACT_CPP(friends);

void dbfriends::install(void){
    this->query(
                "CREATE TABLE Friends(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "nick varchar(255),"
                " publickey varchar(255) );"
                );
}

dbfriends::dbfriends()
{
    getDB("friends.sqlite");

}

