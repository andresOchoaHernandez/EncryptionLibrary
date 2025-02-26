#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Hello world" << std::endl;

    return 0;
}

EVP_PKEY *generate_key_pair();

bool encrypt(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext, int &ciphertext_len);

bool decrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, const unsigned char *iv, unsigned char *plaintext, int &plaintext_len);

bool sign(EVP_PKEY *private_key, const unsigned char *message, int message_len, unsigned char *signature, unsigned int &signature_len);

bool verify(EVP_PKEY *public_key, const unsigned char *message, int message_len, const unsigned char *signature, unsigned int signature_len);