#include "sam.h"
#include<sockets.hpp>
#include<string.h>
#include<QString>
#include<QStringList>
#include<QDebug>

bool
sam::isSam(const char * host, int port){
    int fds = MyOwnTCPSocket::Connect( (char*)host, port );
    if(fds == -1) return false;
    return isSam(fds);
}bool
sam::isSam(int sock,bool closeConnect){
    if( MyOwnTCPSocket::Write(sock,(char*)"HELLO VERSION") == -1) return false ;
    char * data = MyOwnTCPSocket::Read(sock,40);
    if (data == 0) return false;
    QStringList listdata = QString(data).split(" ");
    if(closeConnect)
        MyOwnTCPSocket::stopClient(&sock);
    delete [] data;
    if(listdata.size() > 3 && listdata[2] == "RESULT=OK")
           return true;
    return false;
}

void sam::connect(const char *host, int port){
    this->m_sock = MyOwnTCPSocket::Connect( (char*)host, port );
    m_host = new char[strlen(host)];
    strcpy((char*)m_host,(char*)host);
    this->m_port=port;
}

bool sam::getError(){
    qDebug() << "sam::getError() = " << this->error;
    return this->error;
}

sam::sam(const char * host, int port)
{
    qDebug() << host << ":" << port;
    if(!isSam(host,port))
    {
        qDebug() << "\nsam::sam Is not SAM";
        this->error=true;
    }
    else{
        qDebug() << "\nsam::sam Is SAM";
        this->error = false;
        this->connect(host,port);
    }
}

sam::~sam(){
    if(!this->error){
        MyOwnTCPSocket::stopClient(&this->m_sock);
        delete [] this->m_host;
    }

}

