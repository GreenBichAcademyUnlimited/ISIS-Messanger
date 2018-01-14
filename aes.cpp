#include "aes.h"

bool AES::aes_init(const char * key, const char * salt, int nrounds){
    return this->aes_init((unsigned char*)key,(unsigned char*)salt,nrounds);
}

bool AES::aes_init(unsigned char *key, unsigned char *salt, int nrounds){
    unsigned char keytmp[32], iv[32]; // 32*8 = 256 bits
    if(    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, key, strlen((const char*)key), nrounds, keytmp, iv) != 32 )
        return false;
     EVP_CIPHER_CTX_init(&encrypter);
     EVP_EncryptInit_ex(&encrypter, EVP_aes_256_cbc(), NULL, keytmp, iv);
     EVP_CIPHER_CTX_init(&decrypter);
     EVP_DecryptInit_ex(&decrypter, EVP_aes_256_cbc(), NULL, keytmp, iv);
     return true;


}


unsigned char * AES::decrypt(const char * msg){
    int mlen = strlen((const char*)msg), final_len;
    unsigned char * returns = (unsigned char*)malloc(mlen);
    EVP_DecryptInit_ex(&decrypter, NULL, NULL, NULL, NULL);
    EVP_DecryptUpdate(&decrypter, (unsigned char*)msg, &mlen, returns, mlen);
    EVP_DecryptFinal_ex(&decrypter, (unsigned char*)msg+mlen, &final_len);
    return returns;
}

unsigned char * AES::encrypt(const char * msg){
    int mlen = strlen((const char*)msg), final_len;
    unsigned char * returns = (unsigned char*)malloc(mlen); // char is 1 byte.
    EVP_EncryptInit_ex(&encrypter, NULL, NULL, NULL, NULL);
    EVP_EncryptUpdate(&encrypter, (unsigned char*)msg, &mlen, returns, mlen);
    EVP_EncryptFinal_ex(&decrypter, (unsigned char*)msg+mlen, &final_len);
    return returns;
}

AES::AES(const char * key, const char * salt)
{
    // Load the necessary cipher
    EVP_add_cipher(EVP_aes_256_cbc());
    this->error = !this->aes_init((unsigned char*)key, (unsigned char*)salt);
}









