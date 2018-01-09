
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#ifdef WIN32
   #include <winsock.h>
   #include <winsock2.h>
   #include <ws2tcpip.h>
   #define MSG_NOSIGNAL 0
   #pragma comment(lib, "ws2_32.lib")
#else
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <netdb.h>
#endif

#ifndef bzero
    #define bzero(d,n) memset((d),0,(n))
    #define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)
#endif



namespace MyOwnTCPSocket{

inline int error(const char * string){
    fprintf(stderr, string);
    return -1;
}

int
Connect(char*host,int portno)
{
    #ifdef WIN32
     WSADATA wsaData;
     DWORD dwError;
    // Initialize Winsock
    if ( (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) )
        error("WSAStartup failed\n");
    #endif

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    struct hostent * server;

    if(sockfd == -1)
        return error("No can create socket");

    server = gethostbyname(host);
    if (server == NULL)
        return error("No such host");

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr,

         (char *)&serv_addr.sin_addr.s_addr,

         server->h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,
                (struct sockaddr *) &serv_addr,
                sizeof(serv_addr)) < 0)
       return error("ERROR connecting");

    return sockfd;
}

char
Write(int socket,char const * msg)
{
    if(send(socket,msg,strlen(msg),MSG_NOSIGNAL) == -1)
        return error("cannot write to socket. ");
    if(send(socket,"\n",1,MSG_NOSIGNAL) == -1)
        return error("cannot write to socket. ");
    return 1;
}

char * Read(int socket, size_t readByte=1024)
{
    char * returnString = (char*)calloc(readByte,1);
    #ifdef WIN32
    if((recv(socket, returnString, readByte-2, 0)) <=0 ){
       error("No can read from socket");
       return 0;
    }
    #else
    if(read(socket,returnString,readByte-2) == -1){
        error("No can read from socket");
        return 0;
    }
    #endif
    return returnString;
}

void setListen(int socket, unsigned long long int count){
    listen(socket, count);
}

int acceptClient(int socket)
{
    struct sockaddr_in cli_addr;
    size_t clilen = sizeof(cli_addr);
    int socket_user = accept(socket,
                 (struct sockaddr *) &cli_addr,
                 (socklen_t*)&clilen);
    return socket_user;
}

void
stopClient(int * socket)
{
    close(*socket);
    *socket=0;
}

}// myOwnSocket namespace end
