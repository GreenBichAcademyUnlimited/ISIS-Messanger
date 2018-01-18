#ifndef SAM_H
#define SAM_H

typedef enum{
    stream, datagram, raw
}SAMstyle;

class sam
{

private:
    void connect(const char * host, int port);


protected:
    int m_sock, m_port;
    bool error;
    char * m_host=0, * pubkey=0, * privkey=0;

    //TODO: From Friend List get count of incoming/ outcoming

    int c_incoming, c_outcoming;
    int c_m_incoming, c_m_outcoming;
    int * incoming=0, * outcoming=0;

protected:
    bool getStatus(int socket);
public:
   bool accept(const char * nickname="Isis");
   bool connect(const char * destination,const char * nickname="Isis");

public: // sesions
    void DeleteSession(const char * nickname);
    void CreateSession(const char * nickname="Isis", SAMstyle s = stream );
    void WhileSession(void);

public: // keys
    void loadKeys(const char * pubkey, const char * privkey);
    void generateDestination(void);
    char * getPubkey(void);
    char * getPrivkey(void);
//last connectings
public:
    int getIncoming(void){
        return c_incoming;
    }
    int getOutcoming(void){
        return c_outcoming;
    }

public: // errors/is sam
    bool isSam(const char * host, int port);
    bool isSam(int sock, bool closeConnect=true);
    bool getError(void);


    int& operator[] (int x){
        if(c_incoming > x && incoming)
            return incoming[x];
        this->error=true;
        throw "Overflow of SAM::operator[]";
        return incoming[0];
    }

public: // construct/destruct
   explicit sam(const char * host, int port);
   ~sam();
};

#endif // SAM_H
