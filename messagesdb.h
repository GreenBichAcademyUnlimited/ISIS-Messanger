#ifndef MESSAGESDB_H
#define MESSAGESDB_H
#include"dbabstract.h"

class dbmessage : public dbAbstract
{
private:
    void query(void){};
    DB_ABSTRACT_HPP;
    void install(void);

public:
    dbmessage();
    void addMessage(const char * message, int to, int from=0); // zero = self

};

#endif // MESSAGESDB_H
