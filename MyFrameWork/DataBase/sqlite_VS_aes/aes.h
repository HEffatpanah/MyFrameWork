#ifndef _AES_H
#define _AES_H

#ifndef uint8
#define uint8  unsigned char
#endif

#ifndef uint32
#define uint32 unsigned long int
#endif

#include <iostream>
#include <cstring>
using namespace std;

typedef struct {
    uint32 erk[64];     /* encryption round keys */
    uint32 drk[64];     /* decryption round keys */
    int nr;             /* number of rounds */
} aes_context;


class aes {
private:
    aes_context *ctx;
public:
    static unsigned char default_key[32];
    aes();
    ~aes();
    //for nbits 128 key len is 16, for nbits 196 key len is 24, for nbits 256 key len is 32
    int aes_set_key(uint8 *key, int nbits);

    void aes_encrypt(uint8 input[16], uint8 output[16]);

    void aes_decrypt(uint8 input[16], uint8 output[16]);

};

#endif //TESTCLASS_AES_H


