#include "sam.h"
#include<sockets.hpp>
#include<string.h>
#include<QString>
#include<QStringList>
#include<QDebug>

//errors / is sam

#define DEFALT_INCOMING_COUNT 12
#define DEFAULT_OUTCOMING_COUNT 12

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

//accept, connect, status


//TODO: From Friend List get count of incoming/ outcoming


bool sam::getStatus(int socket){
    QString data = MyOwnTCPSocket::Read(socket);
   if ( data.split(" ")[2] != "RESULT=OK" ) return false;
   return true;

}

bool sam::accept(const char * nickname){
    if(!c_incoming)
    {
        incoming = new int[DEFALT_INCOMING_COUNT];
    }
    else{
        if( c_incoming/DEFALT_INCOMING_COUNT > c_m_incoming){
            c_m_incoming++;
            incoming = (int*)realloc((void*)incoming, DEFALT_INCOMING_COUNT*c_m_incoming);
        }
    }
    incoming[c_incoming] = MyOwnTCPSocket::Connect( m_host, m_port );
    if(!this->isSam(incoming[c_incoming])) return false;
    MyOwnTCPSocket::Write(incoming[c_incoming], QString("STREAM ACCEPT ID=%1").arg(nickname).toStdString().c_str() );
    return this->getStatus(incoming[c_incoming]);
}

bool sam::connect(const char * destination,const char * nickname){

    if(!c_outcoming)
    {
        outcoming = new int[DEFAULT_OUTCOMING_COUNT];
    }
    else{
        if( c_outcoming/DEFAULT_OUTCOMING_COUNT > c_m_outcoming){
            c_m_outcoming++;
            outcoming = (int*)realloc((void*)outcoming,DEFALT_INCOMING_COUNT*c_m_outcoming);
        }
    }
    outcoming[c_outcoming] = MyOwnTCPSocket::Connect( m_host, m_port );
    MyOwnTCPSocket::Write(outcoming[c_outcoming], QString("STREAM CONNECT ID=%1 DESTINATION=%2").arg(nickname, destination).toStdString().c_str() );
    return this->getStatus(outcoming[c_outcoming]);
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
            QString data = QString("SESSION CREATE STYLE=%1 ID=%2 DESTINATION=%3")
                    .arg("STREAM",nickname,this->privkey);
        }else{
            QString data = QString("SESSION CREATE STYLE=%1 ID=%2 DESTINATION=%3")
                    .arg(s == datagram ? "DATAGRAM" : "RAW",nickname,this->privkey);
        }
        QString data = MyOwnTCPSocket::Read(this->m_sock);
        if ( data.split(" ")[2] != "RESULT=OK" && data.split(" ")[2] != "RESULT=DUPLICATED_ID"  ) this->error=true;
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

