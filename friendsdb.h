#ifndef FRIENDSDB_H
#define FRIENDSDB_H
#include"dbabstract.h"

class friendsDB : public dbAbstract
{
private:
public:
    bool error;
    friendsDB();
};

#endif // FRIENDSDB_H
