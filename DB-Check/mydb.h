#ifndef MYDB_H
#define MYDB_H
#include"dbabstract.h"


class mydb : public dbAbstract
{
public:
     void query(void){};
     template < class Arg, class ... Args> void query(Arg arg, Args ... args);
     template <class ... Args>  void query( Args ... args );
    mydb();
};

#endif // MYDB_H
