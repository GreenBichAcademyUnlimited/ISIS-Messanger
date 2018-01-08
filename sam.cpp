#include "sam.h"
#include<sockets.hpp>
#include<string.h>
#include<QString>
#include<QStringList>
#include<QDebug>

//errors / is sam

bool sam::getError(){
    qDebug() << "sam::getError() = " << this->error;
    return this->error;
}

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

//connect
void sam::connect(const char *host, int port){
    this->m_sock = MyOwnTCPSocket::Connect( (char*)host, port );
    m_host = new char[strlen(host)];
    strcpy((char*)m_host,(char*)host);
    this->m_port=port;
}


//keys
char * sam::getPubkey(void){
    return this->pubkey;
}char * sam::getPrivkey(void){
    return this->privkey;
}

void sam::loadKeys(const char * pubkey, const char * privkey){
    this->pubkey = new char[strlen(pubkey) + 1];
    this->privkey = new char[strlen(privkey) + 1];

    strcpy(this->pubkey, pubkey);
    strcpy(this->privkey, privkey);
}

void sam::generateDestination(void){
    if(!this->m_sock) this->connect(this->m_host,this->m_port);
    if(!this->error){
        MyOwnTCPSocket::Write(this->m_sock,(char*)"DEST GENERATE");
        QString Data = MyOwnTCPSocket::Read(this->m_sock);
        QStringList SplitedData = Data.split(" ");
        if(SplitedData.size() < 4){
            this->error=true;
        }
        else{
            QString pubkey = SplitedData[2].split("=")[1];
            QString privkey = SplitedData[3].split("=")[1];
            this->loadKeys(pubkey.toStdString().c_str(),privkey.toStdString().c_str());
        }
    }
}


//sessions

void sam :: DeleteSession(const char * nickname){
    if(!this->m_sock) this->connect(this->m_host,this->m_port);
    if(!this->error){
        QString data = QString("SESSION REMOVE ID=%1").arg(nickname);
        MyOwnTCPSocket::Write(this->m_sock,data.toStdString().c_str());
    }
}

void sam :: CreateSession(const char * nickname, SAMstyle s ){
    if(!this->m_sock) this->connect(this->m_host,this->m_port);
    if(!this->error){
        if(!this->privkey) this->generateDestination();
        if(s == stream){
            QString data = QString("SESSION CREATE STYLE=%1 ID=%2 DESTINATION={%3,TRANSIENT}")
                    .arg("STREAM",nickname,this->privkey);
        }else{
            QString data = QString("SESSION CREATE STYLE=%1 ID=%2 DESTINATION={%3,TRANSIENT}")
                    .arg(s == datagram ? "DATAGRAM" : "RAW",nickname,this->privkey);
        }
    }
}


//constuct/destruct
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
        MyOwnTCPSocket::Write(this->m_sock,"QUIT");
        MyOwnTCPSocket::stopClient(&this->m_sock);
        delete [] this->m_host;
    }
    if(privkey) delete [] privkey;
    if(pubkey) delete [] pubkey;

}

