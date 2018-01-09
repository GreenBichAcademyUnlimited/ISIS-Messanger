#ifndef AES_H
#define AES_H
#include <openssl/evp.h>
#include <openssl/aes.h>
#include<string.h>


class AES
{
protected:
    EVP_CIPHER_CTX encrypter, decrypter;
    bool aes_init(unsigned char *key, unsigned char *salt, int nrounds=1);
public:
    AES(const char * key, const char * salt);
    unsigned char * decrypt(const char * msg);
    unsigned char * encrypt(const char * msg);
    bool error;
};

#endif // AES_H
