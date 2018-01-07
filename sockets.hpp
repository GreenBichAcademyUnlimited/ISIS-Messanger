namespace MyOwnTCPSocket{

    int Connect(char*host,int portno);
    char Write(int socket,char*msg);
    char * Read(int socket, size_t readByte=1024);
    void setListen(int socket, unsigned long long int count);
    int acceptClient(int socket);
    void stopClient(int * socket);
}
